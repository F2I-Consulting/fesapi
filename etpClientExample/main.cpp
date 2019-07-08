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

#include "MyOwnCoreProtocolHandlers.h"
#include "MyOwnDiscoveryProtocolHandlers.h"
#include "MyOwnStoreProtocolHandlers.h"
#include "etp/ProtocolHandlers/DataArrayHandlers.h"

using namespace ETP_NS;

int main(int argc, char **argv)
{
	if (argc < 3) {
		std::cerr << "The command must be : etpClientExample ipAddress port [target]" << std::endl;

		return 1;
	}

	std::cout << "Give your authorization to pass to the server (or hit enter if no authorization)" << std::endl;
	std::string authorization;
	std::getline(std::cin, authorization);
	
	COMMON_NS::DataObjectRepository repo;

	auto session = ClientSessionLaunchers::createClientSession(argv[1], argv[2], argc < 4 ? "/" : argv[3], authorization);
	session->setCoreProtocolHandlers(std::make_shared<MyOwnCoreProtocolHandlers>(session, &repo));
	session->setDiscoveryProtocolHandlers(std::make_shared<MyOwnDiscoveryProtocolHandlers>(session, &repo));
	session->setStoreProtocolHandlers(std::make_shared<MyOwnStoreProtocolHandlers>(session, &repo));
	session->setDataArrayProtocolHandlers(std::make_shared<ETP_NS::DataArrayHandlers>(session));
	
	session->run();

#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif
	
	return 0;
}
