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

void MyOwnDiscoveryProtocolHandlers::on_GetDataspacesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetDataspacesResponse & msg, int64_t correlationId)
{
	std::cout << msg.m_dataspaces.size() << " dataspaces received." << std::endl;
	for (const auto & resource : msg.m_dataspaces) {
		std::cout << "*************************************************" << std::endl;
		std::cout << "uri : " << resource.m_uri << std::endl;
		if (!resource.m_dataspaceCount.is_null()) {
			std::cout << "dataspaceCount : " << resource.m_dataspaceCount.get_int() << std::endl;
		}
		std::cout << "name : " << resource.m_name << std::endl;
		for (const auto & ns : resource.m_namespaces) {
			std::cout << "namespace : " << ns << std::endl;
		}
		std::cout << "*************************************************" << std::endl;
	}
}

void MyOwnDiscoveryProtocolHandlers::on_GetNamespacesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetNamespacesResponse & msg, int64_t correlationId)
{
	std::cout << "*************************************************" << std::endl;
	std::cout << msg.m_uris.size() << " namespaces received." << std::endl;
	for (const auto & uri : msg.m_uris) {
		std::cout << "namespace uri : " << uri << std::endl;
	}
	std::cout << "*************************************************" << std::endl;
}

void MyOwnDiscoveryProtocolHandlers::on_GetSupportedTypesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypesResponse & msg, int64_t correlationId)
{
	std::cout << msg.m_supportedTypes.size() << " supported type received." << std::endl;
	for (const auto & st : msg.m_supportedTypes) {
		std::cout << "*************************************************" << std::endl;
		std::cout << "content type : " << st.m_contentType << std::endl;
		if (!st.m_objectCount.is_null()) {
			std::cout << "objectCount : " << st.m_objectCount.get_int() << std::endl;
		}
		std::cout << "*************************************************" << std::endl;
	}
}

void MyOwnDiscoveryProtocolHandlers::on_GetResourcesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse & msg, int64_t correlationId)
{
	Energistics::Etp::v12::Protocol::Store::GetDataObjects getO;
	unsigned int index = 0;

	std::cout << msg.m_resources.size() << " resources received." << std::endl;
	for (Energistics::Etp::v12::Datatypes::Object::Resource resource : msg.m_resources) {
		std::cout << "*************************************************" << std::endl;
		std::cout << "uri : " << resource.m_uri << std::endl;
		std::cout << "contentType : " << resource.m_contentType << std::endl;
		std::cout << "name : " << resource.m_name << std::endl;
		if (!resource.m_sourceCount.is_null())
			std::cout << "sourceCount : " << resource.m_sourceCount.get_int() << std::endl;
		if (!resource.m_targetCount.is_null())
			std::cout << "targetCount : " << resource.m_targetCount.get_int() << std::endl;
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
