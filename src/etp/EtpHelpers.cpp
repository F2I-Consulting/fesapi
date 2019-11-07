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
#include "EtpHelpers.h"

#include "../common/AbstractObject.h"

std::string ETP_NS::EtpHelpers::buildUriFromEnergisticsObject(const COMMON_NS::AbstractObject * const obj)
{
	return "eml:///" + obj->getQualifiedType() + "(" + obj->getUuid() + ")";
}

Energistics::Etp::v12::Datatypes::Object::Resource ETP_NS::EtpHelpers::buildEtpResourceFromEnergisticsObject(const COMMON_NS::AbstractObject * const obj, bool countRels)
{
	if (obj == nullptr) {
		throw std::invalid_argument("Cannot build resource from a null object.");
	}

	Energistics::Etp::v12::Datatypes::Object::Resource result;

	result.m_dataObjectType = obj->getQualifiedType();
	result.m_uri = buildUriFromEnergisticsObject(obj);
	result.m_name = obj->getTitle();
	if (obj->isPartial()) {
		result.m_lastChanged = -1;
	}
	else {
		const time_t lastUpdate = obj->getLastUpdate();
		result.m_lastChanged = lastUpdate > -1 ? lastUpdate : obj->getCreation();
	}
	
	if (countRels) {
		result.m_sourceCount.set_int(obj->getRepository()->getSourceObjects(obj).size());
		result.m_targetCount.set_int(obj->getRepository()->getTargetObjects(obj).size());
	}
	else {
		result.m_sourceCount.set_null();
		result.m_targetCount.set_null();
	}

	return result;
}

Energistics::Etp::v12::Datatypes::Object::DataObject ETP_NS::EtpHelpers::buildEtpDataObjectFromEnergisticsObject(COMMON_NS::AbstractObject * obj)
{
	Energistics::Etp::v12::Datatypes::Object::DataObject result;
	result.m_data = obj->serializeIntoString();
	result.m_resource = ETP_NS::EtpHelpers::buildEtpResourceFromEnergisticsObject(obj);

	return result;
}

Energistics::Etp::v12::Protocol::Core::ProtocolException ETP_NS::EtpHelpers::buildSingleMessageProtocolException(int32_t m_code, const std::string & m_message)
{
	Energistics::Etp::v12::Datatypes::ErrorInfo errorInfo;
	errorInfo.m_code = m_code;
	errorInfo.m_message = m_message;
	Energistics::Etp::v12::Protocol::Core::ProtocolException peMessage;
	peMessage.m_error.set_ErrorInfo(errorInfo);

	return peMessage;
}
