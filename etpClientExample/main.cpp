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

	std::vector<std::string> supportedObjects;

	// Requested protocol
	std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> requestedProtocols;
	Energistics::Etp::v12::Datatypes::SupportedProtocol protocol;

	protocol.m_protocol = Energistics::Etp::v12::Datatypes::Protocol::Core;
	protocol.m_protocolVersion = protocolVersion;
	protocol.m_role = "server";
	requestedProtocols.push_back(protocol);

	protocol.m_protocol = Energistics::Etp::v12::Datatypes::Protocol::Discovery;
	protocol.m_protocolVersion = protocolVersion;
	protocol.m_role = "store";
	requestedProtocols.push_back(protocol);

	protocol.m_protocol = Energistics::Etp::v12::Datatypes::Protocol::Store;
	protocol.m_protocolVersion = protocolVersion;
	protocol.m_role = "store";
	requestedProtocols.push_back(protocol);

	protocol.m_protocol = Energistics::Etp::v12::Datatypes::Protocol::DirectedDiscovery;
	protocol.m_protocolVersion = protocolVersion;
	protocol.m_role = "store";
	requestedProtocols.push_back(protocol);

	// We run the io_service off in its own thread so that it operates completely asynchronously with respect to the rest of the program.
	// This is particularly important regarding "std::future" usage in DataArrayBlockingSession
	auto work = boost::asio::make_work_guard(ioc);
	std::thread thread([&ioc]() { 
		std::cerr << "Start IOC" << std::endl;
		ioc.run(); // Run the I/O service. The call will never return since we have used boost::asio::make_work_guard. We need to reset the worker if we want it to return.
		std::cerr << "End IOC" << std::endl;
	});
	
	auto clientSession = std::make_shared<MyOwnEtpClientSession>(ioc, argv[1], argv[2], argc < 4 ? "/" : argv[3], requestedProtocols, supportedObjects);
	clientSession->run();
	
    // Resetting the work make ioc (in a separate thread) return when there will no more be any uncomplete operations (such as a reading operation for example)
	// ioc does no more honor boost::asio::make_work_guard.
	work.reset();
	// Wait for ioc.run() (in the other thread) to return
	thread.join();

#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
