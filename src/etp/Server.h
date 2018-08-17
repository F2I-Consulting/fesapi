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

#include <boost/asio/ip/tcp.hpp>
#include <thread>

#include "etp/ServerSession.h"

using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>

namespace ETP_NS
{
	template <class T>
	class Server
	{
	private:

		// Accepts incoming connections and launches the sessions
		class listener : public std::enable_shared_from_this<listener>
		{
			tcp::acceptor acceptor_;
			tcp::socket socket_;

		public:
			listener(
				boost::asio::io_context& ioc,
				tcp::endpoint endpoint) :
				  acceptor_(ioc)
				, socket_(ioc)
			{
				boost::system::error_code ec;

				// Open the acceptor
				acceptor_.open(endpoint.protocol(), ec);
				if(ec)
				{
					std::cerr << "listener open : " << ec.message() << std::endl;
					return;
				}

				// Allow address reuse
				acceptor_.set_option(boost::asio::socket_base::reuse_address(true));
				if(ec)
				{
					std::cerr << "listener set_option : " << ec.message() << std::endl;
					return;
				}

				// Bind to the server address
				acceptor_.bind(endpoint, ec);
				if(ec)
				{
					std::cerr << "listener bind : " << ec.message() << std::endl;
					return;
				}

				// Start listening for connections
				acceptor_.listen(
					boost::asio::socket_base::max_listen_connections, ec);
				if(ec)
				{
					std::cerr << "listener listen : " << ec.message() << std::endl;
					return;
				}
			}

			// Start accepting incoming connections
			void
			run()
			{
				if(! acceptor_.is_open())
					return;
				do_accept();
			}

			void
			do_accept()
			{
				acceptor_.async_accept(
					socket_,
					std::bind(
						&listener::on_accept,
						this->shared_from_this(),
						std::placeholders::_1));
			}

			void on_accept(boost::system::error_code ec)
			{
				if(ec)
				{
					std::cerr << "listener on_accept : " << ec.message() << std::endl;
				}
				else
				{
					// Create the session and run it
					std::make_shared<T>(std::move(socket_))->run();
				}

				// Accept another connection
				do_accept();
			}
		};

	public:
	    Server() {}

		void listen(const std::string & host, unsigned short port, int threadCount) {
	    	// The io_context is required for all I/O
			boost::asio::io_context ioc{threadCount};

			// Create and launch a listening port
			auto const address = boost::asio::ip::make_address(host);
			std::make_shared<Server::listener>(ioc, tcp::endpoint{address, port})->run();

			// Run the I/O service on the requested number of threads
			std::vector<std::thread> v;
			v.reserve(threadCount - 1);
			for(auto i = threadCount - 1; i > 0; --i)
				v.emplace_back(
				[&ioc]
				{
					ioc.run();
				});
			ioc.run();
		}
	};
}
