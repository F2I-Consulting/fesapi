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
#pragma once

#include "AbstractSession.h"

namespace ETP_NS
{
	class ServerInitializationParameters
	{
	public:
		ServerInitializationParameters() {}
		virtual ~ServerInitializationParameters() {}

		DLL_IMPORT_OR_EXPORT virtual std::string getApplicationName() { return "F2I-CONSULTING ETP SERVER"; }
		DLL_IMPORT_OR_EXPORT virtual std::string getApplicationVersion() { return "0.0"; }
		DLL_IMPORT_OR_EXPORT virtual std::string getContactEmail() { return "name@f2i-consulting.com"; }
		DLL_IMPORT_OR_EXPORT virtual std::string getContactName() { return "Philippe Verney"; }
		DLL_IMPORT_OR_EXPORT virtual std::string getContactPhone() { return "Please use Zoom or Slack"; }
		DLL_IMPORT_OR_EXPORT virtual std::string getOrganizationName() { return "F2I-CONSULTING"; }

		DLL_IMPORT_OR_EXPORT virtual std::vector<std::string> makeSupportedEncodings();
		DLL_IMPORT_OR_EXPORT virtual std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> makeEndpointCapabilities();
		DLL_IMPORT_OR_EXPORT virtual std::vector<Energistics::Etp::v12::Datatypes::SupportedDataObject> makeSupportedDataObjects();
		DLL_IMPORT_OR_EXPORT virtual std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> makeSupportedProtocols();

		DLL_IMPORT_OR_EXPORT virtual void postSessionCreationOperation(AbstractSession*) {}
	};
}
