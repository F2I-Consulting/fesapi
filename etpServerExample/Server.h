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
#include <boost/asio/signal_set.hpp>
#ifdef WITH_ETP_SSL
#include <boost/asio/ssl.hpp>
#endif

#include <thread>
#include <stdexcept>
#include <vector>

#include "common/DataObjectRepository.h"

using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>

template <class T>
class Server
{
private:

	COMMON_NS::DataObjectRepository& repo;
	std::vector< std::shared_ptr<T> > sessions;

	// Accepts incoming connections and launches the sessions
	class listener : public std::enable_shared_from_this<listener>
	{
		tcp::acceptor acceptor_;
#ifdef WITH_ETP_SSL
		boost::asio::ssl::context& ctx_;
#endif
		tcp::socket socket_;
		std::vector< std::shared_ptr<T> >& sessions;
		COMMON_NS::DataObjectRepository& repo;

	public:
		listener(
			boost::asio::io_context& ioc,
#ifdef WITH_ETP_SSL
			boost::asio::ssl::context& ctx,
#endif
			tcp::endpoint endpoint,
			std::vector< std::shared_ptr<T> >& sessions_,
			COMMON_NS::DataObjectRepository& repo_)
			: acceptor_(ioc)
#ifdef WITH_ETP_SSL
			, ctx_(ctx)
#endif
			, socket_(ioc)
			, sessions(sessions_)
			, repo(repo_)
		{
			boost::beast::error_code ec;

			// Open the acceptor
			acceptor_.open(endpoint.protocol(), ec);
			if(ec) {
				std::cerr << "listener open : " << ec.message() << std::endl;
				return;
			}

			// Allow address reuse
			acceptor_.set_option(boost::asio::socket_base::reuse_address(true), ec);
			if(ec) {
				std::cerr << "listener set_option : " << ec.message() << std::endl;
				return;
			}

			// Bind to the server address
			acceptor_.bind(endpoint, ec);
			if(ec) {
				std::cerr << "listener bind : " << ec.message() << std::endl;
				return;
			}

			// Start listening for connections
			acceptor_.listen(
				boost::asio::socket_base::max_listen_connections, ec);
			if(ec) {
				std::cerr << "listener listen : " << ec.message() << std::endl;
				return;
			}
		}

		// Start accepting incoming connections
		void run() {
			if (!acceptor_.is_open()) { return; }
			do_accept();
		}

		void do_accept() {
			acceptor_.async_accept(
				socket_,
				std::bind(
					&listener::on_accept,
					this->shared_from_this(),
					std::placeholders::_1));
		}

		void on_accept(boost::system::error_code ec) {
			if(ec) {
				std::cerr << "listener on_accept : " << ec.message() << std::endl;
			}
			else {
				// Create the session and run it
				std::shared_ptr<T> session = std::make_shared<T>(std::move(socket_)
#ifdef WITH_ETP_SSL
					, ctx_
#endif
				, repo);
				session->run();
				sessions.push_back(session);
				std::cout << "Opening the session " << sessions.size() << std::endl;
			}

			// Accept another connection
			do_accept();
		}
	};

public:
	Server(COMMON_NS::DataObjectRepository & repo_): repo(repo_) {}

#ifdef WITH_ETP_SSL
	void listen(const std::string & host, unsigned short port, int threadCount, boost::asio::ssl::context & sslContext) {
#else
	void listen(const std::string & host, unsigned short port, int threadCount) {
#endif
		if (threadCount < 1) {
			throw std::invalid_argument("You need to run your server on at least one thread.");
		}
		auto const address = boost::asio::ip::make_address(host);

	    // The io_context is required for all I/O
		boost::asio::io_context ioc{threadCount};

#ifdef WITH_ETP_SSL
		// Create and launch a listening port
		std::make_shared<Server::listener>(ioc, sslContext, tcp::endpoint{ address, port }, sessions, repo)->run();
#else
		// Create and launch a listening port
		std::make_shared<Server::listener>(ioc, tcp::endpoint{ address, port }, sessions, repo)->run();
#endif

		// Capture SIGINT and SIGTERM to perform a clean shutdown
		boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
		signals.async_wait(
			[&](boost::beast::error_code const&, int)
		{
			// Stop the `io_context`. This will cause `run()`
			// to return immediately, eventually destroying the
			// `io_context` and all of the sockets in it.
			ioc.stop();
		});

		// Run the I/O service on the requested number of threads
		std::vector<std::thread> v;
		v.reserve(threadCount - 1);
		for(auto i = threadCount - 1; i > 0; --i)
			v.emplace_back(
			[&ioc]
			{
				auto handlersExecuted = ioc.run();
				std::cout << "The thread has executed " << handlersExecuted << " handlers." << std::endl;
			});
		auto handlersExecuted = ioc.run();
		std::cout << handlersExecuted << " handlers have been executed." << std::endl;
	}
};
