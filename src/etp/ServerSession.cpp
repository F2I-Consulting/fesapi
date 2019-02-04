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

#include "etp/ServerSession.h"

#include <boost/beast/http.hpp>

using namespace ETP_NS;

ServerSession::ServerSession(tcp::socket socket)
	: AbstractSession(std::move(socket)),
	  strand(ws.get_executor())
{
	ws.binary(true);
}

void ServerSession::run()
{
#ifndef NDEBUG
	// Show the HTTP request
	boost::beast::flat_buffer buffer;
	boost::beast::http::request<boost::beast::http::string_body> req;
	boost::beast::http::read(ws.next_layer(), buffer, req);
	if(boost::beast::websocket::is_upgrade(req))
	{
		std::cout << req << std::endl;
	}

	// Accept the websocket handshake
	ws.async_accept_ex(req,
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
	ws.async_accept_ex(
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
#endif
}

void ServerSession::on_accept(boost::system::error_code ec)
{
	if(ec) {
		std::cerr << "on_accept : " << ec.message() << std::endl;
	}

	webSocketSessionClosed = false;

	// Read a message
	do_read();
}

void ServerSession::do_read()
{
	if (webSocketSessionClosed) {
		std::cout << "CLOSED : NOTHING MORE TO DO" << std::endl;
		return;
	}

	// Read a message into our buffer
	ws.async_read(
		receivedBuffer,
		boost::asio::bind_executor(
			strand,
			std::bind(
				&AbstractSession::on_read,
				shared_from_this(),
				std::placeholders::_1,
				std::placeholders::_2)));
}
