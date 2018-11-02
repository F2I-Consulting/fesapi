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
#include  "etp/ProtocolHandlers/DirectedDiscoveryHandlers.h"

#include <regex>

#include "etp/AbstractSession.h"

using namespace ETP_NS;

void DirectedDiscoveryHandlers::decodeMessageBody(const Energistics::Etp::v12::Datatypes::MessageHeader & mh, avro::DecoderPtr d)
{
	if (mh.m_protocol != Energistics::Etp::v12::Datatypes::Protocols::DirectedDiscovery) {
		std::cerr << "Error : This message header does not belong to the protocol Discovery" << std::endl;
		return;
	}

	if (mh.m_messageType == Energistics::Etp::v12::Protocol::DirectedDiscovery::GetContent::messageTypeId) {
		Energistics::Etp::v12::Protocol::DirectedDiscovery::GetContent gc;
		avro::decode(*d, gc);
		session->flushReceivingBuffer();
		on_GetContent(gc, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::DirectedDiscovery::GetResourcesResponse::messageTypeId) {
		Energistics::Etp::v12::Protocol::DirectedDiscovery::GetResourcesResponse grr;
		avro::decode(*d, grr);
		session->flushReceivingBuffer();
		on_GetResourcesResponse(grr, mh.m_correlationId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::DirectedDiscovery::GetSources::messageTypeId) {
		Energistics::Etp::v12::Protocol::DirectedDiscovery::GetSources gs;
		avro::decode(*d, gs);
		session->flushReceivingBuffer();
		on_GetSources(gs, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Etp::v12::Protocol::DirectedDiscovery::GetTargets::messageTypeId) {
		Energistics::Etp::v12::Protocol::DirectedDiscovery::GetTargets gt;
		avro::decode(*d, gt);
		session->flushReceivingBuffer();
		on_GetTargets(gt, mh.m_messageId);
	}
	else {
		session->flushReceivingBuffer();
		sendExceptionCode3();
	}
}

void DirectedDiscoveryHandlers::on_GetContent(const Energistics::Etp::v12::Protocol::DirectedDiscovery::GetContent & gc, int64_t correlationId)
{
	std::cout << "on_GetContent" << std::endl;

	Energistics::Etp::v12::Protocol::Core::ProtocolException error;
	error.m_errorCode = 7;
	error.m_errorMessage = "The DirectedDiscovery::on_GetContent method has not been overriden by the agent.";

	session->send(error);
}

void DirectedDiscoveryHandlers::on_GetResourcesResponse(const Energistics::Etp::v12::Protocol::DirectedDiscovery::GetResourcesResponse & grr, int64_t correlationId)
{
	Energistics::Etp::v12::Datatypes::Object::GraphResource graphResource =  grr.m_resource;
	std::cout << "*************************************************" << std::endl;
	std::cout << "GraphResource received : " << std::endl;
	std::cout << "uri : " << graphResource.m_uri << std::endl;
	std::cout << "contentType : " << graphResource.m_contentType << std::endl;
	std::cout << "name : " << graphResource.m_name << std::endl;
	std::cout << "type : " << graphResource.m_resourceType << std::endl;
	std::cout << "sourceCount : " << graphResource.m_sourceCount << std::endl;
	std::cout << "targetCount : " << graphResource.m_targetCount << std::endl;
	std::cout << "contentCount : " << graphResource.m_contentCount << std::endl;
	std::cout << "uuid : " << graphResource.m_uuid << std::endl;
	std::cout << "lastChanged : " << graphResource.m_lastChanged << std::endl;
	std::cout << "*************************************************" << std::endl;
}

void DirectedDiscoveryHandlers::on_GetSources(const Energistics::Etp::v12::Protocol::DirectedDiscovery::GetSources & gs, int64_t correlationId)
{
	std::cout << "on_GetSources" << std::endl;

	Energistics::Etp::v12::Protocol::Core::ProtocolException error;
	error.m_errorCode = 7;
	error.m_errorMessage = "The DirectedDiscovery::on_GetSources method has not been overriden by the agent.";

	session->send(error);
}

void DirectedDiscoveryHandlers::on_GetTargets(const Energistics::Etp::v12::Protocol::DirectedDiscovery::GetTargets & gt, int64_t correlationId)
{
	std::cout << "on_GetTargets" << std::endl;

	// Build GetResourcesResponse message
	Energistics::Etp::v12::Protocol::Core::ProtocolException error;
	error.m_errorCode = 7;
	error.m_errorMessage = "The DirectedDiscovery::on_GetTargets method has not been overriden by the agent.";

	session->send(error);
}
