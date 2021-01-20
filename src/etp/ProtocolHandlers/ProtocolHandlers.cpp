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

#include "../../tools/date.h"

using namespace ETP_NS;

void ProtocolHandlers::printDataObject(const Energistics::Etp::v12::Datatypes::Object::DataObject & dataObject)
{
	std::cout << "uri : " << dataObject.resource.uri << std::endl;
	if (!dataObject.resource.alternateUris.empty()) {
		std::cout << "alternateUris :";
		for (const auto & alternateUri : dataObject.resource.alternateUris) {
			std::cout << " " << alternateUri;
		}
		std::cout << std::endl;
	}
	std::cout << "contentType : " << dataObject.resource.dataObjectType << std::endl;
	std::cout << "name : " << dataObject.resource.name << std::endl;
	if (dataObject.resource.sourceCount) {
		std::cout << "source count : " << dataObject.resource.sourceCount.get() << std::endl;
	}
	if (dataObject.resource.targetCount) {
		std::cout << "target count : " << dataObject.resource.targetCount.get() << std::endl;
	}

	std::cout << "lastChanged : ";
	if (dataObject.resource.lastChanged >= 0) {
		auto duration = std::chrono::microseconds(dataObject.resource.lastChanged);
		std::cout << date::format("%FT%TZ", date::floor<std::chrono::microseconds>(duration));
	}
	else {
		std::cout << "unknown";
	}
	std::cout << std::endl;

	std::cout << "*********** SERIALIZATION ***********************" << std::endl;
	std::cout << dataObject.data << std::endl;
	std::cout << "*************************************************" << std::endl;
}
