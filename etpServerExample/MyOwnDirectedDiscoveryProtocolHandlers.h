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
#pragma once

#include "etp/ProtocolHandlers/DirectedDiscoveryHandlers.h"

#include "MyOwnEtpServerSession.h"

#include "common/AbstractObject.h"

namespace {
	Energistics::Etp::v12::Datatypes::Object::GraphResource buildGraphResourceFromObject(COMMON_NS::AbstractObject * obj) {
		if (obj == nullptr) {
			throw std::invalid_argument("Cannot build graph resource from a null object.");
		}
		if (obj->isPartial()) {
			throw std::invalid_argument("Cannot build graph resource from a partial object.");
		}

		Energistics::Etp::v12::Datatypes::Object::GraphResource result;

		result.m_resourceType = "DataObject";
		result.m_channelSubscribable = false;
		result.m_objectNotifiable = false;
		result.m_contentCount = -1;
		result.m_contentType = "application/x-resqml+xml;version=2.0;type=obj_" + obj->getXmlTag();
		// TODO : change the xml namespace to be the same as the etp one
		std::string etpNs =  obj->getXmlNamespace();
		if (etpNs[etpNs.size()-1] != '0') etpNs += '0';
		// END TODO
		result.m_uri = "eml://" + etpNs  + "/obj_" + obj->getXmlTag() + "(" + obj->getUuid() + ")";
		result.m_uuid = obj->getUuid();
		result.m_name = obj->getTitle();
		result.m_lastChanged = obj->getLastUpdate() == -1 ? obj->getCreation() : obj->getLastUpdate();

		std::vector<epc::Relationship> sourceRels = obj->getAllSourceRelationships();
		result.m_sourceCount = std::count_if(sourceRels.begin(), sourceRels.end(), [](const epc::Relationship& rel) {return rel.isInternalTarget();});
		sourceRels = obj->getAllTargetRelationships();
		result.m_targetCount = std::count_if(sourceRels.begin(), sourceRels.end(), [](const epc::Relationship& rel) {return rel.isInternalTarget();});

		return result;
	}
}

class MyOwnDirectedDiscoveryProtocolHandlers : public ETP_NS::DirectedDiscoveryHandlers
{
private:


	template <class T>
	void sendGraphResourcesFromObjects(const std::vector<T*> & objs, int64_t correlationId)
	{
		bool onlyPartial = true;
		for (auto i = 0; i < objs.size(); ++i) {
			if (!objs[i]->isPartial()) {
				onlyPartial = false;
				break;
			}
		}

		if (objs.empty() || onlyPartial) {
			Energistics::Etp::v12::Protocol::Core::ProtocolException error;
			error.m_errorCode = 11;
			error.m_errorMessage = "This folder has not got any content.";

			session->send(error);
			return;
		}

		Energistics::Etp::v12::Protocol::DirectedDiscovery::GetResourcesResponse mb;
		for (auto i = 0; i < objs.size(); ++i) {
			mb.m_resource = buildGraphResourceFromObject(objs[i]);
			session->send(mb, correlationId, i == objs.size() - 1 ? (0x01 | 0x02) : 0x01);
		}
	}

	void sendGraphResourcesFromRelationships(const std::vector<epc::Relationship> & rels, int64_t correlationId);

public:
	MyOwnDirectedDiscoveryProtocolHandlers(MyOwnEtpServerSession* mySession): ETP_NS::DirectedDiscoveryHandlers(mySession) {}
	~MyOwnDirectedDiscoveryProtocolHandlers() {}

	void on_GetContent(const Energistics::Etp::v12::Protocol::DirectedDiscovery::GetContent & gc, int64_t correlationId);
	void on_GetSources(const Energistics::Etp::v12::Protocol::DirectedDiscovery::GetSources & gs, int64_t correlationId);
	void on_GetTargets(const Energistics::Etp::v12::Protocol::DirectedDiscovery::GetTargets & gt, int64_t correlationId);
};
