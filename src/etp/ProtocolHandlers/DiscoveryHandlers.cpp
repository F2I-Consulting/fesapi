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

void DiscoveryHandlers::decodeMessageBody(const Energistics::Etp::v12::Datatypes::MessageHeader & mh, avro::DecoderPtr d)
{
	if (mh.m_protocol != Energistics::Etp::v12::Datatypes::Protocol::Discovery) {
		std::cerr << "Error : This message header does not belong to the protocol Discovery" << std::endl;
		return;
	}

	if (mh.m_messageType == Energistics::Etp::v12::Protocol::Discovery::GetTreeResources::messageTypeId) {
		Energistics::Etp::v12::Protocol::Discovery::GetTreeResources gr;
		avro::decode(*d, gr);
		session->flushReceivingBuffer();
		on_GetTreeResources(gr, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::Discovery::GetGraphResources::messageTypeId) {
		Energistics::Etp::v12::Protocol::Discovery::GetGraphResources gr;
		avro::decode(*d, gr);
		session->flushReceivingBuffer();
		on_GetGraphResources(gr, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse::messageTypeId) {
		Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse grr;
		avro::decode(*d, grr);
		session->flushReceivingBuffer();
		on_GetResourcesResponse(grr, mh.m_correlationId);
	}
	else {
		session->flushReceivingBuffer();
		sendExceptionCode3();
	}
}

void DiscoveryHandlers::on_GetTreeResources(const Energistics::Etp::v12::Protocol::Discovery::GetTreeResources & gr, int64_t correlationId)
{
	std::cout << "on_GetTreeResources" << std::endl;

	// Build GetResourcesResponse message
	Energistics::Etp::v12::Protocol::Core::ProtocolException error;
	error.m_errorCode = 7;
	error.m_errorMessage = "The Discovery::on_GetTreeResources method has not been overriden by the agent.";

	session->send(error);
}

void DiscoveryHandlers::on_GetGraphResources(const Energistics::Etp::v12::Protocol::Discovery::GetGraphResources & gr, int64_t correlationId)
{
	std::cout << "on_GetGraphResources" << std::endl;

	// Build GetResourcesResponse message
	Energistics::Etp::v12::Protocol::Core::ProtocolException error;
	error.m_errorCode = 7;
	error.m_errorMessage = "The Discovery::on_GetGraphResources method has not been overriden by the agent.";

	session->send(error);
}

void DiscoveryHandlers::on_GetResourcesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse & grr, int64_t correlationId)
{
	for (const auto & resource : grr.m_resources) {
		std::cout << '(' << resource.m_name << ", " << resource.m_contentType << ')' << std::endl;
	}
}
