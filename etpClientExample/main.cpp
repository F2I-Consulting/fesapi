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

#include "etp/ClientSession.h"

using namespace ETP_NS;

int main(int argc, char **argv)
{
	boost::asio::io_context ioc;

	Energistics::Datatypes::Version protocolVersion;
	protocolVersion.m_major = 1;
	protocolVersion.m_minor = 1;
	protocolVersion.m_patch = 0;
	protocolVersion.m_revision = 0;
	// Requested protocol
	std::vector<Energistics::Datatypes::SupportedProtocol> requestedProtocols;
	Energistics::Datatypes::SupportedProtocol protocol;
	protocol.m_protocol = Energistics::Datatypes::Protocols::Discovery;
	protocol.m_protocolVersion = protocolVersion;
	protocol.m_role = "customer";
	requestedProtocols.push_back(protocol);

	std::vector<std::string> supportedObjects;

	auto clientSession = std::make_shared<ClientSession>(ioc, "127.0.0.1", "8080", requestedProtocols, supportedObjects);
	clientSession->run();
/*
	std::string command;
	while (command != "quit") {
		std::cout << "What is your command ?" << std::endl;
		std::cin >> command;
	    if (command == "quit") {
	    	clientSession->close();
	    }
	    else if (command == "connect") {
	    	clientSession->run();
	    }
	}
*/
    // Run the I/O service. The call will return when the socket is closed.
	ioc.run();

	std::cout << "The socket is now closed. Close the program." << std::endl;

#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
