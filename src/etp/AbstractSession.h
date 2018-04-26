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

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "nsDefinitions.h"

#include "etp/EtpMessages.hpp"

using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>

namespace ETP_NS
{
	class AbstractSession : public std::enable_shared_from_this<AbstractSession>
	{
	protected:
	    websocket::stream<tcp::socket> ws;
	    boost::beast::flat_buffer receivedBuffer;
	    boost::shared_ptr<std::vector<uint8_t> > bytesToSend;
	    long long messageId = 1;

	    // For client session
	    AbstractSession(boost::asio::io_context& ioc) : ws(ioc) {}
	    // For server session
	    AbstractSession(tcp::socket socket) : ws(std::move(socket)) {}

		virtual void run() = 0;
		virtual void close() = 0;
	};
}
