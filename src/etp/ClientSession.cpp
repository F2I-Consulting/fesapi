/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/

#include "etp/ClientSession.h"

#include <boost/asio/connect.hpp>
#include <boost/beast/http.hpp>

using namespace ETP_NS;

ClientSession::ClientSession(boost::asio::io_context& ioc,
		const std::string & host, const std::string & port,  const std::string & target,
		const std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> & requestedProtocols,
		const std::vector<std::string>& supportedObjects)
	: AbstractSession(ioc),
	  resolver(ioc),
	  host(host),
	  port(port),
	  target(target)
{
	ws.binary(true);

	// Build the request session
	requestSession.m_applicationName = "F2I ETP Client";
	requestSession.m_applicationVersion = "0.0";
	requestSession.m_requestedProtocols = requestedProtocols;
	requestSession.m_supportedObjects = supportedObjects;
}

void ClientSession::run()
{
	// Look up the domain name
	resolver.async_resolve(
		host,
		port,
		std::bind(
			&ClientSession::on_resolve,
			std::static_pointer_cast<ClientSession>(shared_from_this()),
			std::placeholders::_1,
			std::placeholders::_2));
}

void ClientSession::on_resolve(
	boost::system::error_code ec,
	tcp::resolver::results_type results)
{
	if(ec) {
		std::cerr << "on_resolve : " << ec.message() << std::endl;
	}

	// Make the connection on the IP address we get from a lookup
	boost::asio::async_connect(
		ws.next_layer(),
		results.begin(),
		results.end(),
		std::bind(
			&ClientSession::on_connect,
			std::static_pointer_cast<ClientSession>(shared_from_this()),
			std::placeholders::_1));
}

void ClientSession::on_connect(boost::system::error_code ec)
{
	if(ec) {
		std::cerr << "on_connect : " << ec.message() << std::endl;
	}

	// Perform the websocket handshake
	ws.async_handshake_ex(responseType,
		host + ":" + port, target,
		[](websocket::request_type& m)
			{
				m.insert(boost::beast::http::field::sec_websocket_protocol, "energistics-tp");
			},
		std::bind(
			&ClientSession::on_handshake,
			std::static_pointer_cast<ClientSession>(shared_from_this()),
			std::placeholders::_1));
}

void ClientSession::on_handshake(boost::system::error_code ec)
{
	if(ec) {
		std::cerr << "on_handshake : " << ec.message() << std::endl;
	}

#ifndef NDEBUG
	std::cout << responseType << std::endl;
#endif

	if(! responseType.count(boost::beast::http::field::sec_websocket_protocol) ||
			responseType[boost::beast::http::field::sec_websocket_protocol] != "energistics-tp")
		std::cerr << "The client MUST specify the Sec-Websocket-Protocol header value of energistics-tp, and the server MUST reply with the same" << std::endl;

	closed = false;

	sendAndDoRead(requestSession);
}

void ClientSession::do_when_finished()
{
	if (closed) {
		std::cout << "CLOSED : NOTHING MORE TO DO" << std::endl;
		return;
	}

	// Read a message into our buffer
	do_read();
}

void ClientSession::do_read()
{
	// Read a message into our buffer
	ws.async_read(
		receivedBuffer,
		std::bind(
			&AbstractSession::on_read,
			shared_from_this(),
			std::placeholders::_1,
			std::placeholders::_2));
}
