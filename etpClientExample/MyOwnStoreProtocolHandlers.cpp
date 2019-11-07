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

void MyOwnStoreProtocolHandlers::on_GetDataObjectsResponse(const Energistics::Etp::v12::Protocol::Store::GetDataObjectsResponse & obj, int64_t correlationId)
{
	for (const auto & graphResource : obj.m_dataObjects) {
		std::cout << "*************************************************" << std::endl;
		std::cout << "Resource received : " << std::endl;
		std::cout << "uri : " << graphResource.second.m_resource.m_uri << std::endl;
		std::cout << "contentType : " << graphResource.second.m_resource.m_contentType << std::endl;
		std::cout << "name : " << graphResource.second.m_resource.m_name << std::endl;
		std::cout << "xml : " << graphResource.second.m_data << std::endl;
		std::cout << "*************************************************" << std::endl;

		COMMON_NS::AbstractObject* importedObj = repo->addOrReplaceGsoapProxy(graphResource.second.m_data, graphResource.second.m_resource.m_contentType);

		importedObj->loadTargetRelationships();
	}
}
