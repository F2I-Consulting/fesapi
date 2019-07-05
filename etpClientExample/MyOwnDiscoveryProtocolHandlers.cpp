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

#include "etp/AbstractSession.h"

#include "common/AbstractObject.h"

#include <algorithm>

void MyOwnDiscoveryProtocolHandlers::on_GetResourcesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse & grr, int64_t correlationId)
{
	Energistics::Etp::v12::Protocol::Store::GetDataObjects getO;
	unsigned int index = 0;

	std::cout << grr.m_resources.size() << " resources received." << std::endl;
	for (Energistics::Etp::v12::Datatypes::Object::Resource resource : grr.m_resources) {
		std::cout << "*************************************************" << std::endl;
		std::cout << "uri : " << resource.m_uri << std::endl;
		std::cout << "contentType : " << resource.m_contentType << std::endl;
		std::cout << "name : " << resource.m_name << std::endl;
		std::cout << "type : " << static_cast<size_t>(resource.m_resourceType) << std::endl;
		if (!resource.m_sourceCount.is_null())
			std::cout << "sourceCount : " << resource.m_sourceCount.get_int() << std::endl;
		if (!resource.m_targetCount.is_null())
			std::cout << "targetCount : " << resource.m_targetCount.get_int() << std::endl;
		if (!resource.m_contentCount.is_null())
			std::cout << "contentCount : " << resource.m_contentCount.get_int() << std::endl;
		std::cout << "*************************************************" << std::endl;


		if (std::find(getObjectWhenDiscovered.begin(), getObjectWhenDiscovered.end(), correlationId) != getObjectWhenDiscovered.end()) {
			size_t openingParenthesis = resource.m_uri.find('(', 5);
			if (openingParenthesis != std::string::npos) {
				auto resqmlObj = repo->getDataObjectByUuid(resource.m_uri.substr(openingParenthesis + 1, 36));
				if (resqmlObj == nullptr || resqmlObj->isPartial()) {
					std::cout << "GET OBJECT -----------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;			
					getO.m_uris[std::to_string(index)] = resource.m_uri;
					++index;
				}
			}
		}
	}

	if (!getO.m_uris.empty()) {
		session->send(getO);
	}
}
