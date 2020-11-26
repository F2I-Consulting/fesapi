/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agceements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agceed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/
#include "MyOwnStoreProtocolHandlers.h"

#include <string>

#include <common/AbstractObject.h>
#include <etp/EtpHdfProxy.h>
#include <etp/PlainClientSession.h>

void MyOwnStoreProtocolHandlers::on_GetDataObjectsResponse(const Energistics::Etp::v12::Protocol::Store::GetDataObjectsResponse & obj, int64_t correlationId)
{
	for (const auto & graphResource : obj.dataObjects) {
		std::cout << "*************************************************" << std::endl;
		std::cout << "Resource received : " << std::endl;
		std::cout << "uri : " << graphResource.second.resource.uri << std::endl;
		std::cout << "datatype : " << graphResource.second.resource.dataObjectType << std::endl;
		std::cout << "name : " << graphResource.second.resource.name << std::endl;
		std::cout << "xml : " << graphResource.second.data << std::endl;
		std::cout << "*************************************************" << std::endl;

		COMMON_NS::AbstractObject* importedObj = repo->addOrReplaceGsoapProxy(graphResource.second.data, graphResource.second.resource.dataObjectType);

		importedObj->loadTargetRelationships();

		// Associate session with the newly created hdf proxy.
		// For now, also associate with all hdf proxies.
		for (auto* hdfProxy : repo->getHdfProxySet()) {
			auto* etpHdfProxy = dynamic_cast<ETP_NS::EtpHdfProxy*>(hdfProxy);
			if (etpHdfProxy != nullptr) {
				auto* plainClientSession = dynamic_cast<ETP_NS::PlainClientSession*>(session);
				if (plainClientSession != nullptr) {
					etpHdfProxy->setSession(plainClientSession->getIoContext(), plainClientSession->getHost(), plainClientSession->getPort(), plainClientSession->getTarget());
				}
			}
		}
	}
}
