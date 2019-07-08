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
#include "etp/EtpHelpers.h"

#include "common/AbstractObject.h"

Energistics::Etp::v12::Datatypes::Object::Resource ETP_NS::EtpHelpers::buildEtpResourceFromEnergisticsObject(const COMMON_NS::AbstractObject * const obj)
{
	if (obj == nullptr) {
		throw std::invalid_argument("Cannot build resource from a null object.");
	}
	if (obj->isPartial()) {
		throw std::invalid_argument("Cannot build resource from a partial object.");
	}

	Energistics::Etp::v12::Datatypes::Object::Resource result;

	result.m_resourceType = Energistics::Etp::v12::Datatypes::Object::ResourceKind::DataObject;
	result.m_objectNotifiable = false;
	result.m_contentType = obj->getContentType();
	// TODO : change the xml namespace to be the same as the etp one
	std::string etpNs = obj->getXmlNamespace();
	if (etpNs == "resqml2") { etpNs += '0'; }
	else if (etpNs == "witsml2") { etpNs += '1'; }
	// END TODO
	result.m_uri = "eml://" + etpNs;
	if (etpNs == "resqml20" || etpNs == "eml20") { result.m_uri += "/obj_"; }
	else if (etpNs == "witsml21") { result.m_uri += "/"; }
	result.m_uri += obj->getXmlTag() + "(" + obj->getUuid() + ")";
	result.m_name = obj->getTitle();

	result.m_contentCount.set_null();
	result.m_sourceCount.set_int(obj->getRepository()->getSourceObjects(obj).size());
	result.m_targetCount.set_int(obj->getRepository()->getTargetObjects(obj).size());

	return result;
}

Energistics::Etp::v12::Datatypes::Object::DataObject ETP_NS::EtpHelpers::buildEtpDataObjectFromEnergisticsObject(COMMON_NS::AbstractObject * obj)
{
	Energistics::Etp::v12::Datatypes::Object::DataObject result;
	result.m_data = obj->serializeIntoString();
	result.m_resource = ETP_NS::EtpHelpers::buildEtpResourceFromEnergisticsObject(obj);

	return result;
}
