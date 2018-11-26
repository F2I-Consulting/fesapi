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
	Energistics::Etp::v12::Datatypes::Object::Resource2 buildResourceFromObject(COMMON_NS::AbstractObject * obj) {
		if (obj == nullptr) {
			throw std::invalid_argument("Cannot build resource from a null object.");
		}
		if (obj->isPartial()) {
			throw std::invalid_argument("Cannot build resource from a partial object.");
		}

		Energistics::Etp::v12::Datatypes::Object::Resource2 result;

		result.m_resourceType = Energistics::Etp::v12::Datatypes::Object::ResourceKind::DataObject;
		result.m_objectNotifiable = false;
		result.m_contentType = "application/x-resqml+xml;version=2.0;type=obj_" + obj->getXmlTag();
		// TODO : change the xml namespace to be the same as the etp one
		std::string etpNs = obj->getXmlNamespace();
		if (etpNs[etpNs.size() - 1] != '0') etpNs += '0';
		// END TODO
		result.m_uri = "eml://" + etpNs + "/obj_" + obj->getXmlTag() + "(" + obj->getUuid() + ")";
		result.m_name = obj->getTitle();

		result.m_sourceCount.set_int(obj->getAllSourceRelationshipUuids().size());
		result.m_targetCount.set_int(obj->getAllTargetRelationshipUuids().size());

		return result;
	}
}

class MyOwnDiscoveryProtocolHandlers : public ETP_NS::DiscoveryHandlers
{
private:
	void on_GetEmlColonSlashSlash(const Energistics::Etp::v12::Protocol::Discovery::GetResources2 & gr, int64_t correlationId,
		std::vector<Energistics::Etp::v12::Datatypes::Object::Resource2> & result);

	void on_GetEmlColonSlashSlashResqml20(const Energistics::Etp::v12::Protocol::Discovery::GetResources2 & gr, int64_t correlationId,
		std::vector<Energistics::Etp::v12::Datatypes::Object::Resource2> & result);
	
	void on_GetEmlColonSlashSlashEml20(const Energistics::Etp::v12::Protocol::Discovery::GetResources2 & gr, int64_t correlationId,
		std::vector<Energistics::Etp::v12::Datatypes::Object::Resource2> & result);

	void on_GetFolder(const Energistics::Etp::v12::Protocol::Discovery::GetResources2 & gr, int64_t correlationId,
		std::vector<Energistics::Etp::v12::Datatypes::Object::Resource2> & result);

	void on_GetDataObject(const Energistics::Etp::v12::Protocol::Discovery::GetResources2 & gr, int64_t correlationId,
		std::vector<Energistics::Etp::v12::Datatypes::Object::Resource2> & result);

public:
	MyOwnDiscoveryProtocolHandlers(MyOwnEtpServerSession* mySession): ETP_NS::DiscoveryHandlers(mySession) {}
	~MyOwnDiscoveryProtocolHandlers() {}

	void on_GetResources(const Energistics::Etp::v12::Protocol::Discovery::GetResources2 & gr, int64_t correlationId);
};
