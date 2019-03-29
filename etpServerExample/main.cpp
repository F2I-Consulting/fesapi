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

#ifdef WITH_ETP_SSL
#include "ssl/MyOwnEtpSslServerSession.h"
#else
#include "MyOwnEtpPlainServerSession.h"
#endif
#include "etp/Server.h"

#ifdef WITH_ETP_SSL
#include "ssl/server_certificate.h"
#endif

#include "globalVariables.h"
const char* epcFileName = "../../testingPackageCpp.epc";

int main(int argc, char **argv)
{
	if (argc < 4) {
		std::cerr << "The command must be : etpServerExample ipAddress port epcFileName" << std::endl;
		std::cerr << "EXAMPLE : ./etpServerExample 127.0.0.1 8080 ../../testingPackageCpp.epc" << std::endl;

		return 1;
	}
	epcFileName = argv[3];

	const int threadCount = 2;

	std::cout << "Start listening on " << argv[1] << ":" << argv[2] << " with " << threadCount << " threads..." << std::endl;

#ifdef WITH_ETP_SSL
	ETP_NS::Server<MyOwnEtpSslServerSession> etpServer;

	// The SSL context is required, and holds certificates
	boost::asio::ssl::context ctx{ boost::asio::ssl::context::sslv23 };

	// This holds the self-signed certificate used by the server
	load_server_certificate(ctx);

	etpServer.listen(argv[1], std::stoi(argv[2]), threadCount, ctx);
#else
	ETP_NS::Server<MyOwnEtpPlainServerSession> etpServer;

	etpServer.listen(argv[1], std::stoi(argv[2]), threadCount);
#endif


#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
