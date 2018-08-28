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
	class DLL_IMPORT_OR_EXPORT ServerSession : public ETP_NS::AbstractSession
	{
	private:
		boost::asio::strand<boost::asio::io_context::executor_type> strand;

	public:
		ServerSession(tcp::socket socket);

		virtual ~ServerSession() {}

		void run();

		void do_write() {
			ws.async_write(
				boost::asio::buffer(sendingQueue[0]),
				boost::asio::bind_executor(
					 strand,
					 std::bind(
							 &AbstractSession::on_write,
							 shared_from_this(),
							 std::placeholders::_1,
							 std::placeholders::_2)));
		}

		 void do_close() {
			 ws.async_close(websocket::close_code::normal,
				boost::asio::bind_executor(
					strand,
					std::bind(
						&AbstractSession::on_close,
						shared_from_this(),
						std::placeholders::_1)));
		 }

		virtual void do_when_finished();

		void on_accept(boost::system::error_code ec);
		void do_read();
	};
}
