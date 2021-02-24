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

#include "AbstractSession.h"

#include <boost/asio/connect.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "DataArrayBlockingSession.h"

namespace ETP_NS
{
	// Echoes back all received WebSocket messages.
	// This uses the Curiously Recurring Template Pattern so that the same code works with both SSL streams and regular sockets.
	template<class Derived>
	class AbstractClientSession : public ETP_NS::AbstractSession
	{
	protected:
		boost::asio::io_context ioc;
	    tcp::resolver resolver;
	    std::string host;
	    std::string port;
	    std::string target;
		std::string authorization;
	    websocket::response_type responseType; // In order to check handshake sec_websocket_protocol
	    Energistics::Etp::v12::Protocol::Core::RequestSession requestSession;
		bool successfulConnection;

		// Access the derived class, this is part of the Curiously Recurring Template Pattern idiom.
		Derived& derived() { return static_cast<Derived&>(*this); }

	public:
		AbstractClientSession() :
			ioc(),
			resolver(ioc),
			host(),
			port(),
			target(),
			authorization(),
			successfulConnection(false) {
			messageId = 2; // The client side of the connection MUST use ONLY non-zero even-numbered messageIds. 
		}

	    /**
	     * @param host		The IP address on which the server is listening for etp (websocket) connection
	     * @param port		The port on which the server is listening for etp (websocket) connection
	     * @param target	usually "/" but a server can decide to serve etp on a particular target
	     * @param authorization			The HTTP authorization attribute to send to the server. It may be empty if not needed.
	     * @param requestedProtocols	An array of protocol IDs that the client expects to communicate on for this session. If the server does not support all of the protocols, the client may or may not continue with the protocols that are supported.
	     * @param supportedDataObjects		A list of the Data Objects supported by the client. This list MUST be empty if the client is a customer. This field MUST be supplied if the client is a Store and is requesting a customer role for the server.
	     */
		AbstractClientSession(
				const std::string & host, const std::string & port, const std::string & target, const std::string & authorization,
				const std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> & requestedProtocols,
				const std::vector<Energistics::Etp::v12::Datatypes::SupportedDataObject>& supportedDataObjects) :
			ioc(),
			resolver(ioc),
			host(host),
			port(port),
			target(target),
			authorization(authorization),
			successfulConnection(false)
		{
			messageId = 2; // The client side of the connection MUST use ONLY non-zero even-numbered messageIds. 

			// Build the request session
			requestSession.applicationName = "F2I ETP Client";
			requestSession.applicationVersion = "0.0";
			requestSession.requestedProtocols = requestedProtocols;
			requestSession.supportedDataObjects = supportedDataObjects;
			requestSession.currentDateTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			requestSession.supportedFormats.push_back("xml");

			boost::uuids::random_generator gen;
			auto instanceUuid = gen();
			std::copy(std::begin(instanceUuid.data), std::end(instanceUuid.data), requestSession.clientInstanceId.array.begin());
		}

		virtual ~AbstractClientSession() = default;

		boost::asio::io_context& getIoContext() {
			return ioc;
		}

		const std::string& getHost() const { return host; }
		const std::string& getPort() const { return port; }
		const std::string& getTarget() const { return target; }
		const std::string& getAuthorization() const { return authorization; }

		bool run() {
			// We run the io_service off in its own thread so that it operates completely asynchronously with respect to the rest of the program.
			// This is particularly important regarding "std::future" usage in DataArrayBlockingSession
			auto work = boost::asio::make_work_guard(ioc);
			std::thread thread([this]() {
				std::cerr << "Start IOC" << std::endl;
				this->getIoContext().run(); // Run the I/O service. The call will never return since we have used boost::asio::make_work_guard. We need to reset the worker if we want it to return.
				std::cerr << "End IOC" << std::endl;
			});

			successfulConnection = false;
			// Look up the domain name
			resolver.async_resolve(
				host,
				port,
				std::bind(
					&AbstractClientSession::on_resolve,
					std::static_pointer_cast<AbstractClientSession>(shared_from_this()),
					std::placeholders::_1,
					std::placeholders::_2));

			// Resetting the work make ioc (in a separate thread) return when there will no more be any uncomplete operations (such as a reading operation for example)
			// ioc does no more honor boost::asio::make_work_guard.
			work.reset();
			// Wait for ioc.run() (in the other thread) to return
			thread.join();

			return successfulConnection;
		}

		void on_connect(boost::system::error_code ec) {
			if (ec) {
				std::cerr << "on_connect : " << ec.message() << std::endl;
			}

#if BOOST_VERSION < 107000
			// Perform the websocket handshake
			derived().ws().async_handshake_ex(responseType,
				host + ":" + port, target,
				[&](websocket::request_type& m)
				{
					m.insert(boost::beast::http::field::sec_websocket_protocol, "etp12.energistics.org");
					m.insert(boost::beast::http::field::authorization, authorization);
					m.insert("etp-encoding", "binary");
				},
				std::bind(
					&AbstractClientSession::on_handshake,
					std::static_pointer_cast<AbstractClientSession>(shared_from_this()),
					std::placeholders::_1));
#else
			derived().ws().set_option(websocket::stream_base::decorator(
				[&](websocket::request_type& m)
				{
					m.insert(boost::beast::http::field::sec_websocket_protocol, "etp12.energistics.org");
					m.insert(boost::beast::http::field::authorization, authorization);
				})
			);
			// Perform the websocket handshake
			derived().ws().async_handshake(responseType,
				host + ":" + port, target,
				std::bind(
					&AbstractClientSession::on_handshake,
					std::static_pointer_cast<AbstractClientSession>(shared_from_this()),
					std::placeholders::_1));
#endif
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
#ifndef NDEBUG
			std::cout << responseType << std::endl;
#endif

			if (ec) {
				std::cerr << "on_handshake : " << ec.message() << std::endl;
				return;
			}

			if (!responseType.count(boost::beast::http::field::sec_websocket_protocol) ||
				responseType[boost::beast::http::field::sec_websocket_protocol] != "etp12.energistics.org")
				std::cerr << "The client MUST specify the Sec-Websocket-Protocol header value of etp12.energistics.org, and the server MUST reply with the same" << std::endl;

			successfulConnection = true;
			webSocketSessionClosed = false;

			send(requestSession, 0, 0x02);
			do_read();
		}
	};
}
