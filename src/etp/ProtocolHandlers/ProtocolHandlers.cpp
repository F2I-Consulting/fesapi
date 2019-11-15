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
#include  "ProtocolHandlers.h"

#include "../AbstractSession.h"
#include "../EtpHelpers.h"

using namespace ETP_NS;

void ProtocolHandlers::sendExceptionCode3() {
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(3, "The message type ID is invalid for the given protocol."));
}

void ProtocolHandlers::printDataObject(const Energistics::Etp::v12::Datatypes::Object::DataObject & dataObject)
{
	std::cout << "uri : " << dataObject.m_resource.m_uri << std::endl;
	if (!dataObject.m_resource.m_alternateUris.empty()) {
		std::cout << "alternateUris :";
		for (const auto & alternateUri : dataObject.m_resource.m_alternateUris) {
			std::cout << " " << alternateUri;
		}
		std::cout << std::endl;
	}
	std::cout << "contentType : " << dataObject.m_resource.m_dataObjectType << std::endl;
	std::cout << "name : " << dataObject.m_resource.m_name << std::endl;
	if (!dataObject.m_resource.m_sourceCount.is_null()) {
		std::cout << "source count : " << dataObject.m_resource.m_sourceCount.get_int() << std::endl;
	}
	if (!dataObject.m_resource.m_targetCount.is_null()) {
		std::cout << "target count : " << dataObject.m_resource.m_targetCount.get_int() << std::endl;
	}
	std::cout << "lastChanged : " << (dataObject.m_resource.m_lastChanged >= 0 ? ctime(&dataObject.m_resource.m_lastChanged) : "unknown") << std::endl;
	std::cout << "*********** SERIALIZATION ***********************" << std::endl;
	std::cout << dataObject.m_data << std::endl;
	std::cout << "*************************************************" << std::endl;
}
