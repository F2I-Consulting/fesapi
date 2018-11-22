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

#include "etp/DataArrayBlockingSession.h"

#include <vector>

#include <boost/asio/connect.hpp>
#include <boost/beast/http.hpp>

using namespace ETP_NS;

DataArrayBlockingSession::DataArrayBlockingSession(boost::asio::io_context& ioc,
		const std::string & host, const std::string & port,  const std::string & target)
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

	Energistics::Etp::v12::Datatypes::Version protocolVersion;
	protocolVersion.m_major = 1;
	protocolVersion.m_minor = 2;
	protocolVersion.m_patch = 0;
	protocolVersion.m_revision = 0;

	std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> requestedProtocols;
	Energistics::Etp::v12::Datatypes::SupportedProtocol requestedProtocol;
	requestedProtocol.m_protocol = Energistics::Etp::v12::Datatypes::Protocol::DataArray;
	requestedProtocol.m_protocolVersion = protocolVersion;
	requestedProtocol.m_role = "store";
	requestedProtocols.push_back(requestedProtocol);
	requestSession.m_requestedProtocols = requestedProtocols;

	std::vector<std::string> supportedObjects;
	requestSession.m_supportedObjects = supportedObjects;
}

void DataArrayBlockingSession::run()
{
	// Look up the domain name
	auto const results = resolver.resolve(host, port);

	// Make the connection on the IP address we get from a lookup
	boost::asio::connect(
		ws.next_layer(),
		results.begin(),
		results.end());

	websocket::response_type responseType;
	ws.handshake_ex(responseType,
		host + ":" + port, target,
		[](websocket::request_type& m)
		{
			m.insert(boost::beast::http::field::sec_websocket_protocol, "energistics-tp");
		});

	if (!responseType.count(boost::beast::http::field::sec_websocket_protocol) ||
		responseType[boost::beast::http::field::sec_websocket_protocol] != "energistics-tp")
		std::cerr << "The client MUST specify the Sec-Websocket-Protocol header value of energistics-tp, and the server MUST reply with the same" << std::endl;

	closed = false;

	send(requestSession);
	do_read();
	std::size_t bytes_transferred = future_bytes_transferred.get();
	boost::ignore_unused(bytes_transferred);
	if (bytes_transferred == 0) return;
	flushReceivingBuffer();

	do_read();
}

void DataArrayBlockingSession::do_read()
{
	if (closed) {
		std::cout << "CLOSED : NOTHING MORE TO DO" << std::endl;
		return;
	}

	// Read a message into our buffer
	future_bytes_transferred = ws.async_read(receivedBuffer, boost::asio::use_future);
}
