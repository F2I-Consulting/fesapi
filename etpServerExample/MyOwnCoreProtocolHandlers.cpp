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

#include "MyServerInitializationParameters.h"
#include "etp/AbstractSession.h"
#include "etp/EtpHelpers.h"
#include "tools/GuidTools.h"

void MyOwnCoreProtocolHandlers::on_RequestSession(const Energistics::Etp::v12::Protocol::Core::RequestSession & rs, int64_t correlationId)
{
	MyServerInitializationParameters serverInitializationParams(nullptr);
	auto supportedProtocols = serverInitializationParams.makeSupportedProtocols();

	// Check requested protocols
	std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> requestedAndSupportedProtocols;
	for (auto& rp : rs.requestedProtocols) {
		const auto validatedProtocol = std::find_if(supportedProtocols.begin(), supportedProtocols.end(),
			[rp](const Energistics::Etp::v12::Datatypes::SupportedProtocol & sp) -> bool {
				return sp.protocol == rp.protocol &&
					sp.role == rp.role &&
					sp.protocolVersion.major == rp.protocolVersion.major &&
					sp.protocolVersion.minor == rp.protocolVersion.minor &&
					sp.protocolVersion.patch == rp.protocolVersion.patch &&
					sp.protocolVersion.revision == rp.protocolVersion.revision;
			}
		);
		if (validatedProtocol != std::end(supportedProtocols)) {
			requestedAndSupportedProtocols.push_back(*validatedProtocol);
		}
	}

	if (requestedAndSupportedProtocols.empty()) {
		session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The server does not support any of the requested protocols."));
		return;
	}

	// Build Open Session message
	Energistics::Etp::v12::Protocol::Core::OpenSession openSession;
	openSession.applicationName = serverInitializationParams.getApplicationName();
	openSession.applicationVersion = serverInitializationParams.getApplicationVersion();
	openSession.serverInstanceId.array = GuidTools::generateUidAsByteArray();
	openSession.supportedFormats.push_back("xml");
	openSession.supportedProtocols = requestedAndSupportedProtocols;
	openSession.endpointCapabilities = serverInitializationParams.makeEndpointCapabilities();
	openSession.supportedDataObjects = serverInitializationParams.makeSupportedDataObjects();

	session->send(openSession, correlationId);

	std::cout << "New session" << std::endl;
}
