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

#include "../AbstractClientSession.h"

#include <boost/version.hpp>
#if BOOST_VERSION < 106800
#include "ssl_stream.h"
#elif BOOST_VERSION < 107000
#include <boost/beast/experimental/core/ssl_stream.hpp>
#else
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket/ssl.hpp>
#endif

namespace ETP_NS
{
	class SslClientSession : public AbstractClientSession<SslClientSession>
	{
	private:
		websocket::stream<boost::beast::ssl_stream<tcp::socket>> ws_;

	public:
		DLL_IMPORT_OR_EXPORT SslClientSession(boost::asio::ssl::context& ctx,
			const std::string & host, const std::string & port, const std::string & target, const std::string & authorization,
			const std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> & requestedProtocols,
			const std::vector<Energistics::Etp::v12::Datatypes::SupportedDataObject>& supportedObjects);

		virtual ~SslClientSession() {}

		// Called by the base class
		DLL_IMPORT_OR_EXPORT websocket::stream<boost::beast::ssl_stream<tcp::socket>>& ws() { return ws_; }

		void on_resolve(boost::system::error_code ec, tcp::resolver::results_type results)
		{
			if (ec) {
				std::cerr << "on_resolve : " << ec.message() << std::endl;
			}

			// Make the connection on the IP address we get from a lookup
			boost::asio::async_connect(
				ws_.next_layer().next_layer(),
				results.begin(),
				results.end(),
				std::bind(
					&SslClientSession::on_ssl_connect,
					std::static_pointer_cast<SslClientSession>(shared_from_this()),
					std::placeholders::_1));
		}

		void on_ssl_connect(boost::system::error_code ec) {
			if (ec) {
				std::cerr << "on_ssl_connect : " << ec.message() << std::endl;
			}

			// Perform the SSL handshake
			ws_.next_layer().async_handshake(
				boost::asio::ssl::stream_base::client,
				std::bind(
					&AbstractClientSession::on_connect,
					std::static_pointer_cast<AbstractClientSession>(shared_from_this()),
					std::placeholders::_1));
		}
	};
}
