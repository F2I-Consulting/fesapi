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
#include "MyOwnCoreProtocolHandlers.h"

#include "etp/AbstractSession.h"
#include "etp/EtpHelpers.h"
#include "tools/GuidTools.h"

void MyOwnCoreProtocolHandlers::on_RequestSession(const Energistics::Etp::v12::Protocol::Core::RequestSession & rs, int64_t correlationId)
{
	// Check requested protocols
	std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> supportedProtocols;
	Energistics::Etp::v12::Datatypes::Version protocolVersion;
	protocolVersion.m_major = 1;
	protocolVersion.m_minor = 2;
	protocolVersion.m_patch = 0;
	protocolVersion.m_revision = 0;
	for (auto& rp : rs.m_requestedProtocols) {
	    if (rp.m_protocol == Energistics::Etp::v12::Datatypes::Protocol::Core && rp.m_role == "server") {
	    	Energistics::Etp::v12::Datatypes::SupportedProtocol protocol;
	    	protocol.m_protocol = Energistics::Etp::v12::Datatypes::Protocol::Core;
	    	protocol.m_protocolVersion = protocolVersion;
	    	protocol.m_role = "server";
	    	supportedProtocols.push_back(protocol);
	    }
	    else if (rp.m_protocol == Energistics::Etp::v12::Datatypes::Protocol::Discovery && rp.m_role == "store") {
	    	Energistics::Etp::v12::Datatypes::SupportedProtocol protocol;
	    	protocol.m_protocol = Energistics::Etp::v12::Datatypes::Protocol::Discovery;
			protocol.m_protocolVersion = protocolVersion;
			protocol.m_role = "store";
			Energistics::Etp::v12::Datatypes::DataValue value;
			value.m_item.set_int(1000);
			protocol.m_protocolCapabilities.insert(std::make_pair("MaxGetResourcesResponse", value));
	    	supportedProtocols.push_back(protocol);
	    }
	    else if (rp.m_protocol == Energistics::Etp::v12::Datatypes::Protocol::Store && rp.m_role == "store") {
	    	Energistics::Etp::v12::Datatypes::SupportedProtocol protocol;
	    	protocol.m_protocol = Energistics::Etp::v12::Datatypes::Protocol::Store;
			protocol.m_protocolVersion = protocolVersion;
			protocol.m_role = "store";
			Energistics::Etp::v12::Datatypes::DataValue value;
			value.m_item.set_int(1000);
			protocol.m_protocolCapabilities.insert(std::make_pair("MaxGetResourcesResponse", value));
	    	supportedProtocols.push_back(protocol);
	    }
	    else if (rp.m_protocol == Energistics::Etp::v12::Datatypes::Protocol::DataArray && rp.m_role == "store") {
	    	Energistics::Etp::v12::Datatypes::SupportedProtocol protocol;
	    	protocol.m_protocol = Energistics::Etp::v12::Datatypes::Protocol::DataArray;
			protocol.m_protocolVersion = protocolVersion;
			protocol.m_role = "store";
			Energistics::Etp::v12::Datatypes::DataValue value;
			value.m_item.set_int(1000);
			protocol.m_protocolCapabilities.insert(std::make_pair("MaxGetResourcesResponse", value));
	    	supportedProtocols.push_back(protocol);
	    }
	}

	if (supportedProtocols.empty()) {
		session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The server does not support any of the requested protocols."));
		return;
	}

	// Build Open Session message
	Energistics::Etp::v12::Protocol::Core::OpenSession openSession;
	openSession.m_applicationName = "F2I ETP Example Server";
	openSession.m_applicationVersion = "0.0";
	openSession.m_serverInstanceId.m_array = GuidTools::generateUidAsByteArray();
	openSession.m_supportedProtocols = supportedProtocols;
	std::vector<std::string> supportedObjects;
	supportedObjects.push_back("application/x-resqml+xml;version=2.0;type=*");
	supportedObjects.push_back("application/x-witsml+xml;version=2.0;type=Well");
	supportedObjects.push_back("application/x-witsml+xml;version=2.0;type=Wellbore");
	supportedObjects.push_back("application/x-witsml+xml;version=2.0;type=Trajectory");
	supportedObjects.push_back("application/x-witsml+xml;version=2.0;type=WellCompletion");
	supportedObjects.push_back("application/x-witsml+xml;version=2.0;type=WellboreCompletion");
	supportedObjects.push_back("application/x-witsml+xml;version=2.0;type=WellboreGeometry");
	supportedObjects.push_back("application/x-witsml+xml;version=2.0;type=Log");
	supportedObjects.push_back("application/x-witsml+xml;version=2.0;type=ChannelSet");
	supportedObjects.push_back("application/x-witsml+xml;version=2.0;type=Channel");
	supportedObjects.push_back("application/x-prodml+xml;version=2.1;type=FluidSystem");
	supportedObjects.push_back("application/x-prodml+xml;version=2.1;type=FluidCharacterization");
	supportedObjects.push_back("application/x-witsml+xml;version=2.1;type=ErrorTerm");
	supportedObjects.push_back("application/x-witsml+xml;version=2.1;type=ErrorTermDictionary");
	supportedObjects.push_back("application/x-witsml+xml;version=2.1;type=ToolErrorModel");
	supportedObjects.push_back("application/x-witsml+xml;version=2.1;type=ToolErrorModelDictionary");
	supportedObjects.push_back("application/x-witsml+xml;version=2.1;type=WeightingFunction");
	supportedObjects.push_back("application/x-witsml+xml;version=2.1;type=WeightingFunctionDictionary");
	openSession.m_supportedObjects = supportedObjects;

	session->send(openSession, correlationId);

	std::cout << "New session" << std::endl;
}
