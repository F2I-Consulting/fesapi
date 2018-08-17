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
#include "tools/GuidTools.h"

void MyOwnCoreProtocolHandlers::on_RequestSession(const Energistics::Etp::v12::Protocol::Core::RequestSession & rs, int64_t correlationId)
{
	// Check requested protocols
	std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> supportedProtocols;
	Energistics::Etp::v12::Datatypes::Version protocolVersion;
	protocolVersion.m_major = 1;
	protocolVersion.m_minor = 1;
	protocolVersion.m_patch = 0;
	protocolVersion.m_revision = 0;
	for (auto& rp : rs.m_requestedProtocols) {
	    if (rp.m_protocol == 0 && rp.m_role == "server") {
	    	Energistics::Etp::v12::Datatypes::SupportedProtocol protocol;
	    	protocol.m_protocol = Energistics::Etp::v12::Datatypes::Protocols::Core;
	    	protocol.m_protocolVersion = protocolVersion;
	    	protocol.m_role = "server";
	    	supportedProtocols.push_back(protocol);
	    }
	    else if (rp.m_protocol == 3 && rp.m_role == "store") {
	    	Energistics::Etp::v12::Datatypes::SupportedProtocol protocol;
	    	protocol.m_protocol = Energistics::Etp::v12::Datatypes::Protocols::Discovery;
			protocol.m_protocolVersion = protocolVersion;
			protocol.m_role = "store";
			Energistics::Etp::v12::Datatypes::DataValue value;
			value.m_item.set_int(1000);
			protocol.m_protocolCapabilities.insert(std::make_pair("MaxGetResourcesResponse", value));
	    	supportedProtocols.push_back(protocol);
	    }
	}

	if (supportedProtocols.empty()) {
		Energistics::Etp::v12::Protocol::Core::ProtocolException error;
		error.m_errorCode = 2;
		error.m_errorMessage = "The server does not support any of the requested protocols.";

		session->send(error);
		return;
	}

	// Build Open Session message
	Energistics::Etp::v12::Protocol::Core::OpenSession openSession;
	openSession.m_applicationName = "F2I ETP Example Server";
	openSession.m_applicationVersion = "0.0";
	openSession.m_sessionId = GuidTools::generateUidAsString();
	openSession.m_supportedProtocols = supportedProtocols;
	std::vector<std::string> supportedObjects;
	supportedObjects.push_back("application/x-resqml+xml;version=2.0;type=*");
	openSession.m_supportedObjects = supportedObjects;

	session->send(openSession, correlationId);
}
