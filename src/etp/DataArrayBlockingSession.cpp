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

#include "DataArrayBlockingSession.h"

#include <vector>

#include <boost/asio/connect.hpp>
#include <boost/beast/http.hpp>

using namespace ETP_NS;

DataArrayBlockingSession::DataArrayBlockingSession(boost::asio::io_context& ioc,
		const std::string & host, const std::string & port,  const std::string & target)
	: ws(ioc),
	  resolver(ioc),
	  host(host),
	  port(port),
	  target(target)
{
	ws.binary(true);

	// Build the request session
	requestSession.applicationName = "F2I ETP Client";
	requestSession.applicationVersion = "0.0";

	Energistics::Etp::v12::Datatypes::Version protocolVersion;
	protocolVersion.major = 1;
	protocolVersion.minor = 2;
	protocolVersion.patch = 0;
	protocolVersion.revision = 0;

	std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> requestedProtocols;
	Energistics::Etp::v12::Datatypes::SupportedProtocol requestedProtocol;
	requestedProtocol.protocol = Energistics::Etp::v12::Datatypes::Protocol::DataArray;
	requestedProtocol.protocolVersion = protocolVersion;
	requestedProtocol.role = "store";
	requestedProtocols.push_back(requestedProtocol);
	requestSession.requestedProtocols = requestedProtocols;

	Energistics::Etp::v12::Datatypes::SupportedDataObject supportedDataObject;
	supportedDataObject.qualifiedType = "eml20.obj_EpcExternalPartReference";
	std::vector<Energistics::Etp::v12::Datatypes::SupportedDataObject> supportedDataObjects;
	supportedDataObjects.push_back(supportedDataObject);
	requestSession.supportedDataObjects = supportedDataObjects;
}

bool DataArrayBlockingSession::run()
{
	// Look up the domain name
	auto const results = resolver.resolve(host, port);
	if (results.empty()) {
		return false;
	}

	// Make the connection on the IP address we get from a lookup
	boost::asio::connect(
		ws.next_layer(),
		results.begin(),
		results.end());

	websocket::response_type responseType;
#if BOOST_VERSION < 107000
	ws.handshake_ex(responseType,
		host + ":" + port, target,
		[](websocket::request_type& m)
		{
			m.insert(boost::beast::http::field::sec_websocket_protocol, "etp12.energistics.org");
		});
#else
	ws.set_option(websocket::stream_base::decorator(
		[](websocket::request_type& m)
		{
			m.insert(boost::beast::http::field::sec_websocket_protocol, "etp12.energistics.org");
		})
	);

	ws.handshake(responseType, host + ":" + port, target);
#endif

	if (!responseType.count(boost::beast::http::field::sec_websocket_protocol) ||
		responseType[boost::beast::http::field::sec_websocket_protocol] != "etp12.energistics.org") {
		std::cerr << "The client MUST specify the Sec-Websocket-Protocol header value of etp12.energistics.org, and the server MUST reply with the same" << std::endl;
		return false;
	}

	webSocketSessionClosed = false;

	send(requestSession);
	do_read();
	std::size_t bytes_transferred = future_bytes_transferred.get();
	boost::ignore_unused(bytes_transferred);
	if (bytes_transferred == 0) return false;
	flushReceivingBuffer();

	do_read();

	return true;
}

void DataArrayBlockingSession::do_read()
{
	if (webSocketSessionClosed) {
		std::cout << "CLOSED : NOTHING MORE TO DO" << std::endl;
		return;
	}

	// Read a message into our buffer
	future_bytes_transferred = ws.async_read(receivedBuffer, boost::asio::use_future);
}
