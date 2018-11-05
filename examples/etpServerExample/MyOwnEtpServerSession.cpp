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

#include "MyOwnEtpServerSession.h"

#include "MyOwnCoreProtocolHandlers.h"
#include "MyOwnDirectedDiscoveryProtocolHandlers.h"
#include "MyOwnStoreProtocolHandlers.h"
#include "MyOwnDataArrayProtocolHandlers.h"

using namespace std;

const char* MyOwnEtpServerSession::epcFileName = "../../testingPackageCpp.epc";

MyOwnEtpServerSession::MyOwnEtpServerSession(tcp::socket socket)
	: ETP_NS::ServerSession(std::move(socket)),
	  epcDoc(epcFileName, COMMON_NS::EpcDocument::READ_ONLY)
{
	setCoreProtocolHandlers(std::make_shared<MyOwnCoreProtocolHandlers>(this));
	setDirectedDiscoveryProtocolHandlers(std::make_shared<MyOwnDirectedDiscoveryProtocolHandlers>(this));
	setStoreProtocolHandlers(std::make_shared<MyOwnStoreProtocolHandlers>(this));
	setDataArrayProtocolHandlers(std::make_shared<MyOwnDataArrayProtocolHandlers>(this));

	cout << "Start deserialization of " << epcDoc.getName() << " in " << (epcDoc.getStorageDirectory().empty() ? "working directory." : epcDoc.getStorageDirectory()) << endl;
	string resqmlResult = epcDoc.deserialize();
	if (!resqmlResult.empty()) {
		cerr << resqmlResult << endl;
		cout << "Press enter to continue..." << endl;
		cin.get();
	}
}

MyOwnEtpServerSession::~MyOwnEtpServerSession()
{
	cout << "Close Epc Document" << endl;
	epcDoc.close();
}

COMMON_NS::AbstractObject* MyOwnEtpServerSession::getObjectFromUri(const std::string & uri) {
	if (!validateDataObjectUri(uri, true)) {
		return nullptr;
	}

	std::vector<std::string> tokens = tokenize(uri.substr(6), '/');
	if (tokens[0] != "resqml20" && tokens[0] != "eml20") {
		Energistics::Etp::v12::Protocol::Core::ProtocolException error;
		error.m_errorCode = 2;
		error.m_errorMessage = "The URI " + uri + "  uses some dataspaces or witsml or prodml. This agent does not support dataspace.";

		send(error);
		return nullptr;
	}

	tokens = tokenize(tokens[1], '(');
	tokens[1].pop_back();
	COMMON_NS::AbstractObject* result = epcDoc.getResqmlAbstractObjectByUuid(tokens[1]);
	if (result == nullptr) {
		Energistics::Etp::v12::Protocol::Core::ProtocolException error;
		error.m_errorCode = 11;
		error.m_errorMessage = tokens[1] + " cannot be resolved as a data object in this store";

		send(error);
	}

	return result;
}
