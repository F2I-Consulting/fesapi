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
#include "etp/Server.h"

#ifdef WITH_ETP_SSL
#include "ssl/server_certificate.h"
#endif

#include "MyServerInitializationParameters.h"

#include "common/EpcDocument.h"

#include "resqml2/AbstractRepresentation.h"
#include "resqml2_0_1/ContinuousProperty.h"

void generateProperties(RESQML2_NS::AbstractRepresentation* ijkgrid)
{
	for (unsigned short i = 0; i < (std::numeric_limits<unsigned short>::max)(); ++i) {
		auto name = "Two faulted sugar cubes timestamp " + std::to_string(i);
		RESQML2_NS::ContinuousProperty* continuousProp = ijkgrid->getRepository()->createContinuousProperty(ijkgrid, "", name, 1,
			gsoap_eml2_3::resqml22__IndexableElement__cells, gsoap_resqml2_0_1::resqml20__ResqmlUom__m, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind__length);

		double prop1Values[2] = { i, i };
		continuousProp->pushBackDoubleHdf5Array3dOfValues(prop1Values, 2, 1, 1, nullptr);

		std::cout << "A new discrete property has been added" << std::endl;

		const size_t secondCount = 10;
		std::cout << "New generated property in " << secondCount << " seconds" << std::endl;
		std::chrono::seconds dura(secondCount);
		std::this_thread::sleep_for(dura);
	}
}

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
	MyDataObjectRepository repo;
	std::string resqmlResult = epcDoc.deserializePartiallyInto(repo, COMMON_NS::DataObjectRepository::openingMode::READ_WRITE); // Do not open XML files. Simply rely on the EPC content type and rel files.
	repo.registerDataFeeder(&epcDoc); // Necessary to resolve partial objects
	if (!resqmlResult.empty()) {
		std::cerr << "Error when deserializing " << resqmlResult << std::endl;
	}

	if (argc > 4) {
		std::thread generatePropertiesThread(generateProperties, repo.getDataObjectByUuid<RESQML2_NS::AbstractRepresentation>("df2103a0-fa3d-11e5-b8d4-0002a5d5c51b"));
		generatePropertiesThread.detach(); // Detach the thread since we don't want it to be a blocking one.
	}

	MyServerInitializationParameters serverInitializationParams(&repo);

#ifdef WITH_ETP_SSL
	Server<ETP_NS::SslServerSession> etpServer(postSessionCreationOp.get());

	// The SSL context is required, and holds certificates
	boost::asio::ssl::context ctx{ boost::asio::ssl::context::tlsv12_server };

	// This holds the self-signed certificate used by the server
	load_server_certificate(ctx);

	etpServer.listen(argv[1], std::stoi(argv[2]), threadCount, ctx);
#else
	ETP_NS::Server<ETP_NS::PlainServerSession> etpServer(&serverInitializationParams);

	etpServer.listen(argv[1], std::stoi(argv[2]), threadCount);
#endif

	epcDoc.close();

#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
