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
/*
#ifdef WITH_ETP_SSL
#include "ssl/MyOwnEtpSslClientSession.h"
#else
#include "MyOwnEtpPlainClientSession.h"
#endif

#ifdef WITH_ETP_SSL
#include "ssl/root_certificates.h"
#endif
*/

#include "etp/ClientSessionLaunchers.h"
#include "etp/EtpHdfProxy.h"
#include "etp/HttpClientSession.h"

#include "MyOwnCoreProtocolHandlers.h"
#include "MyOwnDiscoveryProtocolHandlers.h"
#include "MyOwnStoreProtocolHandlers.h"
#include "etp/ProtocolHandlers/DataArrayHandlers.h"
#include "etp/ProtocolHandlers/StoreNotificationHandlers.h"

using namespace ETP_NS;

int main(int argc, char **argv)
{
	if (argc < 3) {
		std::cerr << "The command must be : etpClientExample ipAddress port [target]" << std::endl;

		return 1;
	}

	// Ask for Server capabilites
	boost::asio::io_context ioc;
	auto httpClientSession = std::make_shared<HttpClientSession>(ioc);
	std::string etpServerCapTarget = std::string(argc == 3 ? "" : argv[3]) + "/.well-known/etp-server-capabilities?GetVersion=etp12.energistics.org";
	httpClientSession->run(argv[1], argv[2], etpServerCapTarget.c_str(), 11);
	// Run the I/O service. The call will return when the get operation is complete.
	ioc.run();
	std::cout << httpClientSession->getResponse() << std::endl;

	std::cout << "Give your authorization to pass to the server (or hit enter if no authorization)" << std::endl;
	std::string authorization;
	std::getline(std::cin, authorization);
	
	COMMON_NS::DataObjectRepository repo;
	repo.setHdfProxyFactory(new EtpHdfProxyFactory());

	auto session = ClientSessionLaunchers::createClientSession(argv[1], argv[2], argc < 4 ? "/" : argv[3], authorization);
	session->setCoreProtocolHandlers(std::make_shared<MyOwnCoreProtocolHandlers>(session.get(), &repo));
	session->setDiscoveryProtocolHandlers(std::make_shared<MyOwnDiscoveryProtocolHandlers>(session.get(), &repo));
	session->setStoreProtocolHandlers(std::make_shared<MyOwnStoreProtocolHandlers>(session.get(), &repo));
	session->setDataArrayProtocolHandlers(std::make_shared<ETP_NS::DataArrayHandlers>(session.get()));
	session->setStoreNotificationProtocolHandlers(std::make_shared<ETP_NS::StoreNotificationHandlers>(session.get()));
	
	bool successfulConnection = session->run();

	if (!successfulConnection) {
		std::cout << "Could not connect to the server " << argv[1] << " " << argv[2] << std::endl;
	}

#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif
	
	return 0;
}
