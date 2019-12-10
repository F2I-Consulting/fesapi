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

#if (defined(_WIN32) || (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9))))
#include <regex>
#endif

#include "../etp/AbstractSession.h"

#include "../common/AbstractObject.h"

Energistics::Etp::v12::Datatypes::ErrorInfo ETP_NS::EtpHelpers::validateUri(const std::string & uri, std::shared_ptr<ETP_NS::AbstractSession> session)
{
	Energistics::Etp::v12::Datatypes::ErrorInfo errorInfo;
	errorInfo.m_code = -1;
	// Regular expressions are not handled before GCC 4.9
	// https://stackoverflow.com/questions/12530406/is-gcc-4-8-or-earlier-buggy-about-regular-expressions
#if (defined(_WIN32) || (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9))))
	const bool result =
		std::regex_match(uri, std::regex("^eml:/(//)?(dataspace[(].*[)])?", std::regex::ECMAScript)) ||
		std::regex_match(uri, std::regex("^eml:/(//)?(dataspace[(].*[)]/)?(resqml20|eml20)\.obj_[a-zA-Z0-9]+[(][a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}(,.*)?[)]", std::regex::ECMAScript)) ||
		std::regex_match(uri, std::regex("^eml:/(//)?(dataspace[(].*[)]/)?(witsml|resqml|prodml|eml)([0-9]{2})\.obj_[a-zA-Z0-9]+[(][a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}(,.*)?[)]", std::regex::ECMAScript));
	if (!result) {
		std::cerr << "The URI \"" + uri + "\"  is invalid." << std::endl;
	}
#else
	const bool result = uri.find("eml:/") == 0;
#endif

	if (!result) {
		errorInfo.m_code = 9;
		errorInfo.m_message = "The URI " + uri + "  is invalid.";

		if (session != nullptr) {
			Energistics::Etp::v12::Protocol::Core::ProtocolException error;
			error.m_error.set_ErrorInfo(errorInfo);
			session->send(error);
		}
	}

	return errorInfo;

}

Energistics::Etp::v12::Datatypes::ErrorInfo ETP_NS::EtpHelpers::validateDataObjectUri(const std::string & uri, std::shared_ptr<ETP_NS::AbstractSession> session)
{
	Energistics::Etp::v12::Datatypes::ErrorInfo errorInfo;
	errorInfo.m_code = -1;
	// Regular expressions are not handled before GCC 4.9
	// https://stackoverflow.com/questions/12530406/is-gcc-4-8-or-earlier-buggy-about-regular-expressions
#if (defined(_WIN32) || (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9))))
	const bool result = (uri.find("resqml20") != std::string::npos || uri.find("eml20") != std::string::npos)
		? std::regex_match(uri, std::regex("^eml:/(//)?(dataspace[(].*[)]/)?(resqml20|eml20)\.obj_[a-zA-Z0-9]+[(][a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}(,.*)?[)]", std::regex::ECMAScript))
		: std::regex_match(uri, std::regex("^eml:/(//)?(dataspace[(].*[)]/)?(witsml|resqml|prodml|eml)([0-9]{2})\.[a-zA-Z0-9]+[(][a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}(,.*)?[)]", std::regex::ECMAScript));
	if (!result) {
		std::cerr << "The data object URI \"" + uri + "\"  is invalid." << std::endl;
	}
#else
	const bool result = uri.find("eml:/") == 0 && 
		(uri.find("resqml20.obj_") != std::string::npos || uri.find("eml20.obj_") != std::string::npos ||
		uri.find("witsml20.") != std::string::npos || uri.find("eml21.") != std::string::npos ||
		uri.find("prodml21.") != std::string::npos || uri.find("eml22.") != std::string::npos ||
		uri.find("witsml21.") != std::string::npos);
#endif

	if (!result) {
		errorInfo.m_code = 9;
		errorInfo.m_message = "The data object URI " + uri + "  is invalid.";

		if (session != nullptr) {
			Energistics::Etp::v12::Protocol::Core::ProtocolException error;
			error.m_error.set_ErrorInfo(errorInfo);
			session->send(error);
		}
	}

	return errorInfo;
}

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
		result.m_lastChanged = (lastUpdate > -1 ? lastUpdate : obj->getCreation()) * 1e6;
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

Energistics::Etp::v12::Datatypes::Object::DataObject ETP_NS::EtpHelpers::buildEtpDataObjectFromEnergisticsObject(COMMON_NS::AbstractObject * obj, bool includeSerialization)
{
	Energistics::Etp::v12::Datatypes::Object::DataObject result;
	if (includeSerialization) {
		if (obj->isPartial()) {
			obj = obj->getRepository()->resolvePartial(obj);
		}
		result.m_format = "xml";
		result.m_data = obj->serializeIntoString();
	}
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
