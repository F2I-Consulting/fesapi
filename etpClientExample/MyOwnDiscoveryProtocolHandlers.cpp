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
#include "MyOwnDiscoveryProtocolHandlers.h"

#include <algorithm>

#include <etp/AbstractSession.h>
#include <common/AbstractObject.h>

void MyOwnDiscoveryProtocolHandlers::on_GetResourcesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse & msg, int64_t correlationId)
{
	Energistics::Etp::v12::Protocol::Store::GetDataObjects getO;
	unsigned int index = 0;

	std::cout << msg.resources.size() << " resources received." << std::endl;
	for (const Energistics::Etp::v12::Datatypes::Object::Resource & resource : msg.resources) {
		std::cout << "*************************************************" << std::endl;
		std::cout << "uri : " << resource.uri << std::endl;
		std::cout << "data type : " << resource.dataObjectType << std::endl;
		std::cout << "name : " << resource.name << std::endl;
		if (resource.sourceCount)
			std::cout << "sourceCount : " << resource.sourceCount.get() << std::endl;
		if (resource.targetCount)
			std::cout << "targetCount : " << resource.targetCount.get() << std::endl;
		std::cout << "*************************************************" << std::endl;


		if (std::find(getObjectWhenDiscovered.begin(), getObjectWhenDiscovered.end(), correlationId) != getObjectWhenDiscovered.end()) {
			const size_t openingParenthesis = resource.uri.find('(', 5);
			if (openingParenthesis != std::string::npos) {
				auto resqmlObj = repo->getDataObjectByUuid(resource.uri.substr(openingParenthesis + 1, 36));
				if (resqmlObj == nullptr || resqmlObj->isPartial()) {
					std::cout << "GET OBJECT -----------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;			
					getO.uris[std::to_string(index)] = resource.uri;
					++index;
				}
			}
		}
	}

	if (!getO.uris.empty()) {
		session->send(getO, 0, 0x02);
	}
}
