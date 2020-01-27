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

#include "ServerCapabilities.h"
#include "etp/AbstractSession.h"
#include "etp/EtpHelpers.h"
#include "tools/GuidTools.h"

void MyOwnCoreProtocolHandlers::on_RequestSession(const Energistics::Etp::v12::Protocol::Core::RequestSession & rs, int64_t correlationId)
{
	// Check requested protocols
	std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> requestedAndSupportedProtocols;
	for (auto& rp : rs.m_requestedProtocols) {
		const auto validatedProtocol = std::find_if(supportedProtocols.begin(), supportedProtocols.end(),
			[rp](const Energistics::Etp::v12::Datatypes::SupportedProtocol & sp) -> bool {
				return sp.m_protocol == rp.m_protocol &&
					sp.m_role == rp.m_role &&
					sp.m_protocolVersion.m_major == rp.m_protocolVersion.m_major &&
					sp.m_protocolVersion.m_minor == rp.m_protocolVersion.m_minor &&
					sp.m_protocolVersion.m_patch == rp.m_protocolVersion.m_patch &&
					sp.m_protocolVersion.m_revision == rp.m_protocolVersion.m_revision;
			}
		);
		requestedAndSupportedProtocols.push_back(*validatedProtocol);
	}

	if (requestedAndSupportedProtocols.empty()) {
		session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The server does not support any of the requested protocols."));
		return;
	}

	// Build Open Session message
	Energistics::Etp::v12::Protocol::Core::OpenSession openSession;
	openSession.m_applicationName = applicationName;
	openSession.m_applicationVersion = applicationVersion;
	openSession.m_serverInstanceId.m_array = GuidTools::generateUidAsByteArray();
	openSession.m_supportedFormats.push_back("xml");
	openSession.m_supportedProtocols = requestedAndSupportedProtocols;
	openSession.m_endpointCapabilities = endpointCapabilities;
	openSession.m_supportedObjects = supportedObjects;

	session->send(openSession, correlationId);

	std::cout << "New session" << std::endl;
}
