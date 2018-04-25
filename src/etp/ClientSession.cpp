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
		const std::vector<Energistics::Datatypes::SupportedProtocol> & requestedProtocols,
		const std::vector<std::string>& supportedObjects)
	: AbstractSession(ioc)
	, resolver(ioc)
{
	ws.binary(true);

	// Build the request session
	requestSession.m_applicationName = "F2I ETP Client";
	requestSession.m_applicationVersion = "0.0";
	requestSession.m_requestedProtocols = requestedProtocols;
	requestSession.m_supportedObjects = supportedObjects;
}

void ClientSession::run(const std::string & host, const std::string port)
{
	// Save these for later
	this->host = host;

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
		host, "/",
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

	if(! responseType.count(boost::beast::http::field::sec_websocket_protocol) ||
			responseType[boost::beast::http::field::sec_websocket_protocol] != "energistics-tp")
		throw std::invalid_argument("the client MUST specify the Sec-Websocket-Protocol header value of energistics-tp, and the server MUST reply with the same");

	// Build Message Header
	Energistics ::Datatypes::MessageHeader mh;
	mh.m_protocol = Energistics::Datatypes::Protocols::Core;
	mh.m_messageType = Energistics::Protocol::Core::RequestSession::messageTypeId;
	mh.m_correlationId = 0;
	mh.m_messageId = messageId++;
	mh.m_messageFlags = 0;
	//Encode into avro
	std::auto_ptr<avro::OutputStream> out = avro::memoryOutputStream();
	avro::EncoderPtr e = avro::binaryEncoder();
	e->init(*out);
	avro::encode(*e, mh);
	avro::encode(*e, requestSession);
	boost::shared_ptr<std::vector<uint8_t> > bytes = avro::snapshot(*out);

	// Send Request session
	ws.async_write(
		boost::asio::buffer(*bytes),
		std::bind(
			&ClientSession::on_write,
			std::static_pointer_cast<ClientSession>(shared_from_this()),
			std::placeholders::_1,
			std::placeholders::_2));
}

void ClientSession::on_write(boost::system::error_code ec, std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);

	if(ec) {
		std::cerr << "on_write : " << ec.message() << std::endl;
	}

	// Read a message into our buffer
	ws.async_read(
		buffer,
		std::bind(
			&ClientSession::on_read,
			std::static_pointer_cast<ClientSession>(shared_from_this()),
			std::placeholders::_1,
			std::placeholders::_2));
}

void ClientSession::on_read(boost::system::error_code ec, std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);

	if(ec) {
		std::cerr << "on_read : " << ec.message() << std::endl;
	}
}

void ClientSession::close()
{
	ws.async_close(websocket::close_code::normal,
		std::bind(
			&ClientSession::on_close,
			std::static_pointer_cast<ClientSession>(shared_from_this()),
			std::placeholders::_1));
}

void ClientSession::on_close(boost::system::error_code ec)
{
	if(ec) {
			std::cerr << "on_close : " << ec.message() << std::endl;
		}

	// If we get here then the connection is closed gracefully
	std::cout << "!!! CLOSED !!!" << std::endl;
}
