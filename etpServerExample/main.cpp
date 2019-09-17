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
#include "etp/ssl/SslServerSession.h"
#else
#include "etp/PlainServerSession.h"
#endif
#include "Server.h"

#ifdef WITH_ETP_SSL
#include "ssl/server_certificate.h"
#endif

#include "common/DataObjectRepository.h"
#include "common/EpcDocument.h"

int main(int argc, char **argv)
{
	if (argc < 4) {
		std::cerr << "The command must be : etpServerExample ipAddress port epcFileName" << std::endl;
		std::cerr << "EXAMPLE : ./etpServerExample 127.0.0.1 8080 ../../testingPackageCpp.epc" << std::endl;

		return 1;
	}

	const int threadCount = 2;

	std::cout << "Start listening on " << argv[1] << ":" << argv[2] << " with " << threadCount << " threads..." << std::endl;

	COMMON_NS::EpcDocument epcDoc(argv[3]);
	COMMON_NS::DataObjectRepository repo;
	std::string resqmlResult = epcDoc.deserializePartiallyInto(repo);
	repo.registerDataFeeder(&epcDoc);
	if (!resqmlResult.empty()) {
		std::cerr << "Error when deserializing " << resqmlResult << std::endl;
	}

#ifdef WITH_ETP_SSL
	Server<ETP_NS::SslServerSession> etpServer(repo);

	// The SSL context is required, and holds certificates
	boost::asio::ssl::context ctx{ boost::asio::ssl::context::tlsv12_server };

	// This holds the self-signed certificate used by the server
	load_server_certificate(ctx);

	etpServer.listen(argv[1], std::stoi(argv[2]), threadCount, ctx);
#else
	Server<ETP_NS::PlainServerSession> etpServer(repo);

	etpServer.listen(argv[1], std::stoi(argv[2]), threadCount);
#endif

	epcDoc.close();

#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
