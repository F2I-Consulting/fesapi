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

#include <boost/asio/strand.hpp>
#include <boost/asio/bind_executor.hpp>

namespace ETP_NS
{
	// Echoes back all received WebSocket messages.
	// This uses the Curiously Recurring Template Pattern so that the same code works with both SSL streams and regular sockets.
	template<class Derived>
	class AbstractServerSession : public ETP_NS::AbstractSession
	{
	private:
		// Access the derived class, this is part of the Curiously Recurring Template Pattern idiom.
		Derived& derived() { return static_cast<Derived&>(*this); }

	protected:
		boost::asio::strand<boost::asio::io_context::executor_type> strand;

	public:
		AbstractServerSession(boost::asio::io_context& ioc) : strand(ioc.get_executor()) {}

		virtual ~AbstractServerSession() {}

		boost::asio::io_context& getIoContext() {
			return derived().ws().get_executor().context();
		}

		DLL_IMPORT_OR_EXPORT void run() {
#ifndef NDEBUG
			// Show the HTTP request
			boost::beast::flat_buffer buffer;
			boost::beast::http::request<boost::beast::http::string_body> req;
			boost::beast::http::read(ws.next_layer(), buffer, req);
			if (boost::beast::websocket::is_upgrade(req))
			{
				std::cout << req << std::endl;
			}

			// Accept the websocket handshake
			derived().ws().async_accept_ex(req,
				[](websocket::response_type& m)
			{
				m.insert(boost::beast::http::field::sec_websocket_protocol, "etp12.energistics.org");
			},
				boost::asio::bind_executor(
					strand,
					std::bind(
						&ServerSession::on_accept,
						std::static_pointer_cast<ServerSession>(shared_from_this()),
						std::placeholders::_1)));
#else
			// does not show up the HTTP request
			derived().ws().async_accept_ex(
				[](websocket::response_type& m)
			{
				m.insert(boost::beast::http::field::sec_websocket_protocol, "etp12.energistics.org");
			},
				boost::asio::bind_executor(
					strand,
					std::bind(
						&AbstractServerSession::on_accept,
						std::static_pointer_cast<AbstractServerSession>(shared_from_this()),
						std::placeholders::_1)));
#endif
		}

		void do_write() {
			if (!sendingQueue[0].empty()) {
				derived().ws().async_write(
					boost::asio::buffer(sendingQueue[0]),
					boost::asio::bind_executor(
						strand,
						std::bind(
							&AbstractSession::on_write,
							shared_from_this(),
							std::placeholders::_1,
							std::placeholders::_2)));
			}
			else {
				do_close();
			}
		}

		 void do_close() {
			 derived().ws().async_close(websocket::close_code::normal,
				boost::asio::bind_executor(
					strand,
					std::bind(
						&AbstractSession::on_close,
						shared_from_this(),
						std::placeholders::_1)));
		 }

		 void on_accept(boost::system::error_code ec) {
			 if (ec) {
				 std::cerr << "on_accept : " << ec.message() << std::endl;
			 }

			 webSocketSessionClosed = false;

			 // Read a message
			 do_read();
		}

		void do_read()
		{
			if (webSocketSessionClosed) {
				std::cout << "CLOSED : NOTHING MORE TO DO" << std::endl;
				return;
			}

			// Read a message into our buffer
			derived().ws().async_read(
				receivedBuffer,
				boost::asio::bind_executor(
					strand,
					std::bind(
						&AbstractSession::on_read,
						shared_from_this(),
						std::placeholders::_1,
						std::placeholders::_2)));
		}
	};
}
