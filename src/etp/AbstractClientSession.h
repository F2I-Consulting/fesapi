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
#pragma once

#include "etp/AbstractSession.h"

#include <boost/asio/connect.hpp>

#include "etp/DataArrayBlockingSession.h"

namespace ETP_NS
{
	// Echoes back all received WebSocket messages.
	// This uses the Curiously Recurring Template Pattern so that the same code works with both SSL streams and regular sockets.
	template<class Derived>
	class AbstractClientSession : public ETP_NS::AbstractSession
	{
	protected:
	    tcp::resolver resolver;
	    std::string host;
	    std::string port;
	    std::string target;
	    websocket::response_type responseType; // In order to check handshake sec_websocket_protocol
	    Energistics::Etp::v12::Protocol::Core::RequestSession requestSession;

		// Access the derived class, this is part of the Curiously Recurring Template Pattern idiom.
		Derived& derived() { return static_cast<Derived&>(*this); }

	public:
	    /**
	     * @param host		The IP address on which the server is listening for etp (websocket) connection
	     * @param port		The port on which the server is listening for etp (websocket) connection
	     * @param target	usually "/" but a server can decide to serve etp on a particular target
	     * @param requestedProtocols An array of protocol IDs that the client expects to communicate on for this session. If the server does not support all of the protocols, the client may or may not continue with the protocols that are supported.
	     * @param supportedObjects		A list of the Data Objects supported by the client. This list MUST be empty if the client is a customer. This field MUST be supplied if the client is a Store and is requesting a customer role for the server.
	     */
		AbstractClientSession(boost::asio::io_context& ioc,
				const std::string & host, const std::string & port, const std::string & target,
				const std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> & requestedProtocols,
				const std::vector<std::string>& supportedObjects) :
			resolver(ioc),
			host(host),
			port(port),
			target(target)
		{
			// Build the request session
			requestSession.m_applicationName = "F2I ETP Client";
			requestSession.m_applicationVersion = "0.0";
			requestSession.m_requestedProtocols = requestedProtocols;
			requestSession.m_supportedObjects = supportedObjects;
		}

		virtual ~AbstractClientSession() {}

		boost::asio::io_context& getIoContext() {
			return derived().ws().get_executor().context();
		}

		DLL_IMPORT_OR_EXPORT const std::string& getHost() const { return host; }
		DLL_IMPORT_OR_EXPORT const std::string& getPort() const { return port; }
		DLL_IMPORT_OR_EXPORT const std::string& getTarget() const { return target; }

		DLL_IMPORT_OR_EXPORT void run() {
			// Look up the domain name
			resolver.async_resolve(
				host,
				port,
				std::bind(
					&AbstractClientSession::on_resolve,
					std::static_pointer_cast<AbstractClientSession>(shared_from_this()),
					std::placeholders::_1,
					std::placeholders::_2));
		}

		void on_connect(boost::system::error_code ec) {
			if (ec) {
				std::cerr << "on_connect : " << ec.message() << std::endl;
			}

			// Perform the websocket handshake
			derived().ws().async_handshake_ex(responseType,
				host + ":" + port, target,
				[](websocket::request_type& m)
			{
				m.insert(boost::beast::http::field::sec_websocket_protocol, "etp12.energistics.org");
			},
				std::bind(
					&AbstractClientSession::on_handshake,
					std::static_pointer_cast<AbstractClientSession>(shared_from_this()),
					std::placeholders::_1));
		}

		DLL_IMPORT_OR_EXPORT std::shared_ptr<DataArrayBlockingSession> createDataArrayBlockingSession() {
			return std::make_shared<DataArrayBlockingSession>(derived().ws().get_executor().context(), host, port, target);
		}

		DLL_IMPORT_OR_EXPORT void do_write() {
			if (!sendingQueue[0].empty()) {
				derived().ws().async_write(
					boost::asio::buffer(sendingQueue[0]),
					std::bind(
						&AbstractSession::on_write,
						shared_from_this(),
						std::placeholders::_1,
						std::placeholders::_2));
			}
			else {
				do_close();
			}
		}

		DLL_IMPORT_OR_EXPORT void do_close() {
			derived().ws().async_close(websocket::close_code::normal,
				std::bind(
					&AbstractSession::on_close,
					shared_from_this(),
					std::placeholders::_1));
		}
		
		DLL_IMPORT_OR_EXPORT void do_read()
		{
			if (webSocketSessionClosed) {
				std::cout << "CLOSED : NOTHING MORE TO DO" << std::endl;
				return;
			}

			// Read a message into our buffer
			derived().ws().async_read(
				receivedBuffer,
				std::bind(
					&AbstractSession::on_read,
					shared_from_this(),
					std::placeholders::_1,
					std::placeholders::_2));
		}
		
		virtual void on_resolve(boost::system::error_code ec, tcp::resolver::results_type results) = 0;

		void on_handshake(boost::system::error_code ec)
		{
			if (ec) {
				std::cerr << "on_handshake : " << ec.message() << std::endl;
				return;
			}

#ifndef NDEBUG
			std::cout << responseType << std::endl;
#endif

			if (!responseType.count(boost::beast::http::field::sec_websocket_protocol) ||
				responseType[boost::beast::http::field::sec_websocket_protocol] != "etp12.energistics.org")
				std::cerr << "The client MUST specify the Sec-Websocket-Protocol header value of etp12.energistics.org, and the server MUST reply with the same" << std::endl;

			webSocketSessionClosed = false;

			send(requestSession);
			do_read();
		}
	};
}
