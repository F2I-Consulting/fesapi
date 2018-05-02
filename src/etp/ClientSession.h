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

namespace ETP_NS
{
	class ClientSession : public ETP_NS::AbstractSession
	{
	private:
	    tcp::resolver resolver;
	    std::string host;
	    std::string port;
	    websocket::response_type responseType; // In order to check handshake sec_websocket_protocol
	    Energistics::Protocol::Core::RequestSession requestSession;

	public:
	    /**
	     * @param requestedProtocols An array of protocol IDs that the client expects to communicate on for this session. If the server does not support all of the protocols, the client may or may not continue with the protocols that are supported.
	     * @param supportedObjects		A list of the Data Objects supported by the client. This list MUST be empty if the client is a customer. This field MUST be supplied if the client is a Store and is requesting a customer role for the server.
	     */
		ClientSession(boost::asio::io_context& ioc,
				const std::string & host, const std::string & port,
				const std::vector<Energistics::Datatypes::SupportedProtocol> & requestedProtocols,
				const std::vector<std::string>& supportedObjects);

		virtual ~ClientSession() {}

		void run();

		void do_write() {
			ws.async_write(
				boost::asio::buffer(*bytesToSend),
				std::bind(
					&AbstractSession::on_write,
					shared_from_this(),
					std::placeholders::_1,
					std::placeholders::_2));
		}

		void do_writeAndRead() {
			ws.async_write(
				boost::asio::buffer(*bytesToSend),
				std::bind(
					&AbstractSession::on_writeAndRead,
					shared_from_this(),
					std::placeholders::_1,
					std::placeholders::_2));
		}

		void do_close() {
			ws.async_close(websocket::close_code::normal,
				std::bind(
					&AbstractSession::on_close,
					shared_from_this(),
					std::placeholders::_1));
		}

		virtual void do_when_finished();
		void do_read();

		void on_resolve(boost::system::error_code ec, tcp::resolver::results_type results);
		void on_connect(boost::system::error_code ec);
		void on_handshake(boost::system::error_code ec);
		void on_close(boost::system::error_code ec);
	};
}
