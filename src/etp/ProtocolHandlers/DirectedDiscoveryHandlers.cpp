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

bool DirectedDiscoveryHandlers::validateUri(const std::string & uri)const
{
	return std::regex_match(uri, std::regex("^eml://((witsml|resqml|prodml|eml)([0-9]+))*.*", std::regex::ECMAScript));
}

void DirectedDiscoveryHandlers::decodeMessageBody(const Energistics ::Datatypes::MessageHeader & mh, avro::DecoderPtr d)
{
	if (mh.m_protocol != Energistics::Datatypes::Protocols::DirectedDiscovery) {
		std::cerr << "Error : This message header does not belong to the protocol Discovery" << std::endl;
		return;
	}

	if (mh.m_messageType == Energistics::Protocol::DirectedDiscovery::GetContent::messageTypeId) {
		Energistics::Protocol::DirectedDiscovery::GetContent gc;
		avro::decode(*d, gc);
		on_GetContent(gc, mh.m_messageId);
	}
	else if (mh.m_messageType == Energistics::Protocol::DirectedDiscovery::GetResourcesResponse::messageTypeId) {
		Energistics::Protocol::DirectedDiscovery::GetResourcesResponse grr;
		avro::decode(*d, grr);
		on_GetResourcesResponse(grr);
	}
	else if (mh.m_messageType == Energistics::Protocol::DirectedDiscovery::GetSourceFolders::messageTypeId) {
		Energistics::Protocol::DirectedDiscovery::GetSourceFolders gsf;
		avro::decode(*d, gsf);
		on_GetSourceFolders(gsf);
	}
	else if (mh.m_messageType == Energistics::Protocol::DirectedDiscovery::GetTargetFolders::messageTypeId) {
		Energistics::Protocol::DirectedDiscovery::GetTargetFolders gtf;
		avro::decode(*d, gtf);
		on_GetTargetFolders(gtf);
	}
	else {
		sendExceptionCode3();
	}
}

void DirectedDiscoveryHandlers::on_GetContent(const Energistics::Protocol::DirectedDiscovery::GetContent & gc, int64_t correlationId)
{
	std::cout << "on_GetContent" << std::endl;

	Energistics::Protocol::Core::ProtocolException error;
	error.m_errorCode = 7;
	error.m_errorMessage = "The DirectedDiscovery::on_GetContent method has not been overriden by the agent.";

	session->sendAndDoWhenFinished(error);
}

void DirectedDiscoveryHandlers::on_GetResourcesResponse(const Energistics::Protocol::DirectedDiscovery::GetResourcesResponse & grr)
{
	std::cout << '(' << grr.m_resource.m_name << ", " << grr.m_resource.m_contentType << ')' << std::endl;

	session->do_when_finished();
}

void DirectedDiscoveryHandlers::on_GetSourceFolders(const Energistics::Protocol::DirectedDiscovery::GetSourceFolders & gsf)
{
	std::cout << "on_GetSourceFolders" << std::endl;

	Energistics::Protocol::Core::ProtocolException error;
	error.m_errorCode = 7;
	error.m_errorMessage = "The DirectedDiscovery::on_GetSourceFolders method has not been overriden by the agent.";

	session->sendAndDoWhenFinished(error);
}

void DirectedDiscoveryHandlers::on_GetTargetFolders(const Energistics::Protocol::DirectedDiscovery::GetTargetFolders & gtf)
{
	std::cout << "on_GetTargetFolders" << std::endl;

	// Build GetResourcesResponse message
	Energistics::Protocol::Core::ProtocolException error;
	error.m_errorCode = 7;
	error.m_errorMessage = "The DirectedDiscovery::on_GetTargetFolders method has not been overriden by the agent.";

	session->sendAndDoWhenFinished(error);
}
