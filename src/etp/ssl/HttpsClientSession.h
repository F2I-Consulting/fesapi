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
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <iostream>

using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
namespace http = boost::beast::http;    // from <boost/beast/http.hpp>

namespace ETP_NS
{
	// Performs an HTTP GET and stores the response
	class HttpsClientSession : public std::enable_shared_from_this<HttpsClientSession>
	{
		tcp::resolver resolver_;
		ssl::stream<tcp::socket> stream_;
		boost::beast::flat_buffer buffer_; // (Must persist between reads)
		http::request<http::empty_body> req_;
		http::response<http::string_body> res_;

	public:
		// Resolver and stream require an io_context
		explicit
			HttpsClientSession(boost::asio::io_context& ioc, ssl::context& ctx)
			: resolver_(ioc)
			, stream_(ioc, ctx)
		{
		}

		// Start the asynchronous operation
		void
			run(
				char const* host,
				char const* port,
				char const* target,
				int version,
				std::string authorization = "")
		{
			// Set SNI Hostname (many hosts need this to handshake successfully)
			if (!SSL_set_tlsext_host_name(stream_.native_handle(), host))
			{
				boost::system::error_code ec{ static_cast<int>(::ERR_get_error()), boost::asio::error::get_ssl_category() };
				std::cerr << ec.message() << "\n";
				return;
			}

			// Set up an HTTP GET request message
			req_.version(version);
			req_.method(http::verb::get);
			req_.target(target);
			req_.set(http::field::host, host);
			req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
			if (!authorization.empty()) {
				req_.set(http::field::authorization, authorization);
			}

			// Look up the domain name
			resolver_.async_resolve(
				host,
				port,
				std::bind(
					&HttpsClientSession::on_resolve,
					shared_from_this(),
					std::placeholders::_1,
					std::placeholders::_2));
		}

		void
			on_resolve(
				boost::system::error_code ec,
				tcp::resolver::results_type results)
		{
			if (ec) {
				std::cerr << "resolve : " << ec.message() << std::endl;
				return;
			}

			// Make the connection on the IP address we get from a lookup
			boost::asio::async_connect(
				stream_.next_layer(),
				results.begin(),
				results.end(),
				std::bind(
					&HttpsClientSession::on_connect,
					shared_from_this(),
					std::placeholders::_1));
		}

		void
			on_connect(boost::system::error_code ec)
		{
			if (ec) {
				std::cerr << "connect : " << ec.message() << std::endl;
				return;
			}

			// Perform the SSL handshake
			stream_.async_handshake(
				ssl::stream_base::client,
				std::bind(
					&HttpsClientSession::on_handshake,
					shared_from_this(),
					std::placeholders::_1));
		}

		void
			on_handshake(boost::system::error_code ec)
		{
			if (ec) {
				std::cerr << "handshake : " << ec.message() << std::endl;
				return;
			}

			// Send the HTTP request to the remote host
			http::async_write(stream_, req_,
				std::bind(
					&HttpsClientSession::on_write,
					shared_from_this(),
					std::placeholders::_1,
					std::placeholders::_2));
		}

		void
			on_write(
				boost::system::error_code ec,
				std::size_t bytes_transferred)
		{
			boost::ignore_unused(bytes_transferred);

			if (ec) {
				std::cerr << "write : " << ec.message() << std::endl;
				return;
			}

			// Receive the HTTP response
			http::async_read(stream_, buffer_, res_,
				std::bind(
					&HttpsClientSession::on_read,
					shared_from_this(),
					std::placeholders::_1,
					std::placeholders::_2));
		}

		void
			on_read(
				boost::system::error_code ec,
				std::size_t bytes_transferred)
		{
			boost::ignore_unused(bytes_transferred);

			if (ec) {
				std::cerr << "read : " << ec.message() << std::endl;
				return;
			}

			// Gracefully close the stream_
			stream_.async_shutdown(
				std::bind(
					&HttpsClientSession::on_shutdown,
					shared_from_this(),
					std::placeholders::_1));
		}

		void
			on_shutdown(boost::system::error_code ec)
		{
			if (ec == boost::asio::error::eof)
			{
				// Rationale:
				// http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
				ec.assign(0, ec.category());
			}
			if (ec) {
				std::cerr << "shutdown : " << ec.message() << std::endl;
				return;
			}

			// If we get here then the connection is closed gracefully
		}

		const http::response<http::string_body>& getResponse() const {
			return res_;
		}
	};
}
