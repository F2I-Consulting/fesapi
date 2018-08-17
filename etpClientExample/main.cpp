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

#include <thread>
#include "MyOwnEtpClientSession.h"

using namespace ETP_NS;

int main(int argc, char **argv)
{
	if (argc < 3) {
		std::cerr << "The command must be : etpClientExample ipAddress port" << std::endl;

		return 1;
	}

	boost::asio::io_context ioc;

	Energistics::Etp::v12::Datatypes::Version protocolVersion;
	protocolVersion.m_major = 1;
	protocolVersion.m_minor = 2;
	protocolVersion.m_patch = 0;
	protocolVersion.m_revision = 0;
	// Requested protocol
	std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> requestedProtocols;
	Energistics::Etp::v12::Datatypes::SupportedProtocol protocol;
	protocol.m_protocol = Energistics::Etp::v12::Datatypes::Protocols::Core;
	protocol.m_protocolVersion = protocolVersion;
	protocol.m_role = "server";
	requestedProtocols.push_back(protocol);
	protocol.m_protocol = Energistics::Etp::v12::Datatypes::Protocols::DirectedDiscovery;
	protocol.m_protocolVersion = protocolVersion;
	protocol.m_role = "store";
	requestedProtocols.push_back(protocol);

	std::vector<std::string> supportedObjects;

	auto clientSession = std::make_shared<MyOwnEtpClientSession>(ioc, argv[1], argv[2], argc < 4 ? "/" : argv[3], requestedProtocols, supportedObjects);
	clientSession->run();

    // Run the I/O service. The call will return when the socket is closed.
	ioc.run();

#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
