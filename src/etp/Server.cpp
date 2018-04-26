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

#include "etp/Server.h"

#include <thread>

using namespace ETP_NS;

void Server::listen(const std::string & host, unsigned short port, int threadCount)
{
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

void Server::close()
{
	std::cout << "Should close the server" << std::endl;
}
