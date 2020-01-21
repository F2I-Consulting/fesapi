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

#include "etp/AbstractServerSession.h"

#if BOOST_VERSION < 106800
#include "etp/ssl/ssl_stream.h"
#elif BOOST_VERSION < 107000
#include <boost/beast/experimental/core/ssl_stream.hpp>
#else
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket/ssl.hpp>
#endif

namespace ETP_NS
{
	class SslServerSession : public AbstractPlainOrSslServerSession<SslServerSession>
	{
	private:
		websocket::stream<boost::beast::ssl_stream<tcp::socket>> ws_;
		boost::asio::strand<boost::asio::io_context::executor_type> strand_;

	public:
		DLL_IMPORT_OR_EXPORT SslServerSession(tcp::socket socket, boost::asio::ssl::context& ctx);

		virtual ~SslServerSession() {}

		// Called by the base class
		DLL_IMPORT_OR_EXPORT websocket::stream<boost::beast::ssl_stream<tcp::socket>>& ws() { return ws_; }

		DLL_IMPORT_OR_EXPORT bool run() {
			// Perform the SSL handshake
			ws_.next_layer().async_handshake(
				boost::asio::ssl::stream_base::server,
				boost::asio::bind_executor(
					strand_,
					std::bind(
						&AbstractPlainOrSslServerSession::on_handshake,
						std::static_pointer_cast<AbstractPlainOrSslServerSession>(shared_from_this()),
						std::placeholders::_1)));
			return true;
		}
	};
}
