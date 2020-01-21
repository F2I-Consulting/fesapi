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
#include  "DiscoveryHandlers.h"

#include "../AbstractSession.h"
#include "../EtpHelpers.h"

using namespace ETP_NS;

void DiscoveryHandlers::decodeMessageBody(const Energistics::Etp::v12::Datatypes::MessageHeader & mh, avro::DecoderPtr d)
{
	if (mh.m_protocol != Energistics::Etp::v12::Datatypes::Protocol::Discovery) {
		std::cerr << "Error : This message header does not belong to the protocol Discovery" << std::endl;
		return;
	}
	if (mh.m_messageType == Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypes::messageTypeId) {
		Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypes msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_GetSupportedTypes(msg, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypesResponse::messageTypeId) {
		Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypesResponse msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_GetSupportedTypesResponse(msg, mh.m_correlationId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::Discovery::GetResources::messageTypeId) {
		Energistics::Etp::v12::Protocol::Discovery::GetResources msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_GetResources(msg, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse::messageTypeId) {
		Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_GetResourcesResponse(msg, mh.m_correlationId);
	}
	else {
		session->flushReceivingBuffer();
		sendExceptionCode3();
	}
}

void DiscoveryHandlers::on_GetSupportedTypes(const Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypes & msg, int64_t correlationId)
{
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The Discovery::on_GetSupportedTypes method has not been overriden by the agent."));
}

void DiscoveryHandlers::on_GetSupportedTypesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypesResponse & msg, int64_t correlationId)
{
	for (const auto & resource : msg.m_supportedTypes) {
		std::cout << "DICOVERED SUPPORTED TYPE (" << resource.m_dataObjectType << " count == " << (resource.m_objectCount.is_null() ? "unknown" : std::to_string(resource.m_objectCount.get_int())) << ')' << std::endl;
	}
}

void DiscoveryHandlers::on_GetResources(const Energistics::Etp::v12::Protocol::Discovery::GetResources & msg, int64_t correlationId)
{
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The Discovery::on_GetResources method has not been overriden by the agent."));
}

void DiscoveryHandlers::on_GetResourcesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse & msg, int64_t correlationId)
{
	for (const auto & resource : msg.m_resources) {
		std::cout << "DISCOVERED RESOURCE (" << resource.m_name << ", " << resource.m_dataObjectType << ')' << std::endl;
	}
}
