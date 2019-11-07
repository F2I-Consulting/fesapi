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

	if (mh.m_messageType == Energistics::Etp::v12::Protocol::Discovery::GetDataspaces::messageTypeId) {
		Energistics::Etp::v12::Protocol::Discovery::GetDataspaces msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_GetDataspaces(msg, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::Discovery::GetDataspacesResponse::messageTypeId) {
		Energistics::Etp::v12::Protocol::Discovery::GetDataspacesResponse msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_GetDataspacesResponse(msg, mh.m_correlationId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::Discovery::GetNamespaces::messageTypeId) {
		Energistics::Etp::v12::Protocol::Discovery::GetNamespaces msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_GetNamespaces(msg, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::Discovery::GetNamespacesResponse::messageTypeId) {
		Energistics::Etp::v12::Protocol::Discovery::GetNamespacesResponse msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_GetNamespacesResponse(msg, mh.m_correlationId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypes::messageTypeId) {
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
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::Discovery::GetDeletedResources::messageTypeId) {
		Energistics::Etp::v12::Protocol::Discovery::GetDeletedResources msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_GetDeletedResources(msg, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::Discovery::GetDeletedResourcesResponse::messageTypeId) {
		Energistics::Etp::v12::Protocol::Discovery::GetDeletedResourcesResponse msg;
		avro::decode(*d, msg);
		session->flushReceivingBuffer();
		on_GetDeletedResourcesResponse(msg, mh.m_correlationId);
	}
	else {
		session->flushReceivingBuffer();
		sendExceptionCode3();
	}
}

void DiscoveryHandlers::on_GetDataspaces(const Energistics::Etp::v12::Protocol::Discovery::GetDataspaces & msg, int64_t correlationId)
{
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The Discovery::on_GetDataspaces method has not been overriden by the agent."));
}

void DiscoveryHandlers::on_GetDataspacesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetDataspacesResponse & msg, int64_t correlationId)
{
	for (const auto & ds : msg.m_dataspaces) {
		std::cout << "DICOVERED DATASPACE (name=" << ds.m_name << ", uri=" << ds.m_uri;
		if (!ds.m_dataspaceCount.is_null()) {
			std::cout << ", dataspace count=" << ds.m_dataspaceCount.get_int();
		}
		if (!ds.m_lastChanged.is_null()) {
			std::cout << ", lastchanged=" << ds.m_lastChanged.get_long();
		}
		for (const auto & ns : ds.m_namespaces) {
			std::cout << ", namespace=" << ns;
		}
		std::cout << ')' << std::endl;
	}
}

void DiscoveryHandlers::on_GetNamespaces(const Energistics::Etp::v12::Protocol::Discovery::GetNamespaces & msg, int64_t correlationId)
{
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The Discovery::on_GetNamespaces method has not been overriden by the agent."));
}

void DiscoveryHandlers::on_GetNamespacesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetNamespacesResponse & msg, int64_t correlationId)
{
	for (const auto & uri : msg.m_uris) {
		std::cout << "DICOVERED NAMESPACE (" << uri << ')' << std::endl;
	}
}

void DiscoveryHandlers::on_GetSupportedTypes(const Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypes & msg, int64_t correlationId)
{
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The Discovery::on_GetSupportedTypes method has not been overriden by the agent."));
}

void DiscoveryHandlers::on_GetSupportedTypesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypesResponse & msg, int64_t correlationId)
{
	for (const auto & resource : msg.m_supportedTypes) {
		std::cout << "DICOVERED SUPPORTED TYPE (" << resource.m_contentType << " count == " << (resource.m_objectCount.is_null() ? "unknown" : std::to_string(resource.m_objectCount.get_int())) << ')' << std::endl;
	}
}

void DiscoveryHandlers::on_GetResources(const Energistics::Etp::v12::Protocol::Discovery::GetResources & msg, int64_t correlationId)
{
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The Discovery::on_GetResources method has not been overriden by the agent."));
}

void DiscoveryHandlers::on_GetResourcesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse & msg, int64_t correlationId)
{
	for (const auto & resource : msg.m_resources) {
		std::cout << "DISCOVERED RESOURCE (" << resource.m_name << ", " << resource.m_contentType << ')' << std::endl;
	}
}

void DiscoveryHandlers::on_GetDeletedResources(const Energistics::Etp::v12::Protocol::Discovery::GetDeletedResources & msg, int64_t correlationId)
{
	session->send(ETP_NS::EtpHelpers::buildSingleMessageProtocolException(7, "The Discovery::on_GetDeletedResources method has not been overriden by the agent."));
}

void DiscoveryHandlers::on_GetDeletedResourcesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetDeletedResourcesResponse & msg, int64_t correlationId)
{
	for (const auto & resource : msg.m_deletedResources) {
		std::cout << "DICOVERED DELETED (" << resource.m_uri << ", " << resource.m_contentType << ", timestamp:" << resource.m_lastChanged << ')' << std::endl;
	}
}
