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
#include  "etp/ProtocolHandlers/DiscoveryHandlers.h"

#include "etp/AbstractSession.h"

using namespace ETP_NS;

void DiscoveryHandlers::decodeMessageBody(const Energistics ::Datatypes::MessageHeader & mh, avro::DecoderPtr d)
{
	if (mh.m_protocol != Energistics::Datatypes::Protocols::Discovery) {
		std::cerr << "Error : This message header does not belong to the protocol Discovery" << std::endl;
		return;
	}

	if (mh.m_messageType == 1) {
		Energistics::Protocol::Discovery::GetResources gr;
		avro::decode(*d, gr);
		on_GetResources(gr);
	}
	else if (mh.m_messageType == 2) {
		Energistics::Protocol::Discovery::GetResourcesResponse grr;
		avro::decode(*d, grr);
		on_GetResourcesResponse(grr);
	}
	else {
		sendExceptionCode3();
	}
}

void DiscoveryHandlers::on_GetResources(const Energistics::Protocol::Discovery::GetResources & gr)
{
	std::cout << "on_GetResources" << std::endl;
	// Build GetResourcesResponse message
	Energistics::Protocol::Core::ProtocolException error;
	error.m_errorCode = 7;
	error.m_errorMessage = "The Discovery::on_GetResources method has not been overriden by the agent.";

	session->send(error);
}

void DiscoveryHandlers::on_GetResourcesResponse(const Energistics::Protocol::Discovery::GetResourcesResponse & grr)
{
	std::cout << '(' << grr.m_resource.m_name << ", " << grr.m_resource.m_contentType << ')' << std::endl;

	session->do_when_finished();
}
