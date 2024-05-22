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

#include "AbstractObject.h"

#include <numeric>
#include <string>
#include <sstream>

#if !defined(__GLIBCXX__) || __GLIBCXX__ > 20150623 || __GLIBCXX__ == 20140422 || __GLIBCXX__ == 20140716 || __GLIBCXX__ == 20141030
#include <regex>
#else
#include <boost/regex.hpp>
#endif
#include <algorithm>

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "../tools/TimeTools.h"

#if defined(__gnu_linux__) || defined(__APPLE__)
#include <unistd.h>
#include <pwd.h>
#endif

#include "../version_config.h"

#include "../eml2/Activity.h"
#if WITH_RESQML2_2
#include "../eml2_3/HdfProxy.h"
#else
#include "../eml2/AbstractHdfProxy.h"
#endif

using namespace std;
using namespace COMMON_NS;

char AbstractObject::citationFormat[2001] = "F2I-CONSULTING:FESAPI:" FESAPI_VERSION_STR;

void AbstractObject::cannotBePartial() const
{
	if (isPartial()) {
		throw logic_error("You cannot get anything but a Title and an UUID from a partial " + getXmlTag() + " (" + getUuid() + ")");
	}
}

bool AbstractObject::isPartial() const {
	return partialObject != nullptr
		&& gsoapProxy2_0_1 == nullptr && gsoapProxy2_3 == nullptr;
}

void AbstractObject::changeToPartialObject()
{
	cannotBePartial();
	partialObject = gsoap_resqml2_0_1::soap_new_eml20__DataObjectReference(getGsoapContext());
	partialObject->UUID = getUuid();
	partialObject->Title = getTitle();
	partialObject->ContentType = getContentType();

	gsoapProxy2_0_1 = nullptr;
	gsoapProxy2_3 = nullptr;
}

soap* AbstractObject::getGsoapContext() const
{
	 if (gsoapProxy2_0_1 != nullptr) {
		return gsoapProxy2_0_1->soap;
	}
	else if (gsoapProxy2_3 != nullptr) {
		 return gsoapProxy2_3->soap;
	}
	else if (isPartial()) {
		return partialObject->soap;
	}
	else {
		return getRepository() == nullptr ? nullptr : getRepository()->getGsoapContext();
	}
}

int AbstractObject::getGsoapType() const {
	if (gsoapProxy2_0_1 != nullptr) {
		return gsoapProxy2_0_1->soap_type();
	}
	else if (gsoapProxy2_3 != nullptr) {
		return gsoapProxy2_3->soap_type();
	}
	else {
		return partialObject->soap_type();
	}
}

string AbstractObject::getUuid() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return gsoapProxy2_0_1->uuid;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return gsoapProxy2_3->uuid;
	}
	else if (isPartial()) { // partial transfer
		return partialObject->UUID;
	}

	throw invalid_argument("There is no available gsoap proxy instance.");
}

string AbstractObject::getTitle() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return gsoapProxy2_0_1->Citation->Title;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return gsoapProxy2_3->Citation->Title;
	}
	else if (isPartial()) { // partial transfer
		return partialObject->Title;
	}

	throw invalid_argument("There is no available gsoap proxy instance.");
}

string AbstractObject::getEditor() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr && gsoapProxy2_0_1->Citation->Editor)
		return *gsoapProxy2_0_1->Citation->Editor;
	else if (gsoapProxy2_3 != nullptr && gsoapProxy2_3->Citation->Editor)
		return *gsoapProxy2_3->Citation->Editor;
	else
		return "";
}

time_t AbstractObject::getCreation() const
{
	tm tmp = getCreationAsTimeStructure();
	return timeTools::timegm(tmp);
}

tm AbstractObject::getCreationAsTimeStructure() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr)
		return gsoapProxy2_0_1->Citation->Creation;
	else if (gsoapProxy2_3 != nullptr)
		return gsoapProxy2_3->Citation->Creation;

	throw invalid_argument("There is no available gsoap proxy instance.");
}

string AbstractObject::getOriginator() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr)
		return gsoapProxy2_0_1->Citation->Originator;
	else if (gsoapProxy2_3 != nullptr)
		return gsoapProxy2_3->Citation->Originator;

	throw invalid_argument("There is no available gsoap proxy instance.");
}

string AbstractObject::getDescription() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr && gsoapProxy2_0_1->Citation->Description)
		return *gsoapProxy2_0_1->Citation->Description;
	else if (gsoapProxy2_3 != nullptr && gsoapProxy2_3->Citation->Description)
		return *gsoapProxy2_3->Citation->Description;
	else
		return "";
}

time_t AbstractObject::getLastUpdate() const
{
	tm result = getLastUpdateAsTimeStructure();
	
	if (result.tm_mday == 0) {
		return -1;
	}

	return timeTools::timegm(result);
}

tm AbstractObject::getLastUpdateAsTimeStructure() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr && gsoapProxy2_0_1->Citation->LastUpdate)
		return *gsoapProxy2_0_1->Citation->LastUpdate;
	else if (gsoapProxy2_3 != nullptr && gsoapProxy2_3->Citation->LastUpdate)
		return *gsoapProxy2_3->Citation->LastUpdate;
	else {
		tm result;
		result.tm_hour = 0;
		result.tm_isdst = 0;
		result.tm_mday = 0;
		result.tm_min = 0;
		result.tm_mon = 0;
		result.tm_sec = 0;
		result.tm_wday = 0;
		result.tm_yday = 0;
		result.tm_year = 0;
		return result;
	}
}

string AbstractObject::getFormat() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr)
		return gsoapProxy2_0_1->Citation->Format;
	else if (gsoapProxy2_3 != nullptr)
		return gsoapProxy2_3->Citation->Format;

	throw invalid_argument("There is no available gsoap proxy instance.");
}

string AbstractObject::getDescriptiveKeywords() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr && gsoapProxy2_0_1->Citation->DescriptiveKeywords)
		return *gsoapProxy2_0_1->Citation->DescriptiveKeywords;
	else if (gsoapProxy2_3 != nullptr && gsoapProxy2_3->Citation->DescriptiveKeywords)
		return *gsoapProxy2_3->Citation->DescriptiveKeywords;
	else
		return string();
}

std::string AbstractObject::getVersion() const
{
	if (gsoapProxy2_0_1 != nullptr && gsoapProxy2_0_1->Citation->VersionString != nullptr && !gsoapProxy2_0_1->Citation->VersionString->empty()) {
		return *gsoapProxy2_0_1->Citation->VersionString;
	}
	else if (gsoapProxy2_3 != nullptr && gsoapProxy2_3->objectVersion != nullptr && !gsoapProxy2_3->objectVersion->empty()) {
		return *gsoapProxy2_3->objectVersion;
	}
	else if (partialObject != nullptr && partialObject->VersionString != nullptr && !partialObject->VersionString->empty()) {
		return *partialObject->VersionString;
	}

	return "";
}

void AbstractObject::setUuid(const std::string & uuid)
{
	cannotBePartial();

	if (uuid.empty()) {
		boost::uuids::random_generator gen;
		const std::string uuidStr = boost::uuids::to_string(gen());

		if (gsoapProxy2_0_1 != nullptr) { gsoapProxy2_0_1->uuid = uuidStr; }
		else if (gsoapProxy2_3 != nullptr) { gsoapProxy2_3->uuid = uuidStr; }
	}
	else
	{
		// https://stackoverflow.com/questions/12530406/is-gcc-4-8-or-earlier-buggy-about-regular-expressions
#if !defined(__GLIBCXX__) || __GLIBCXX__ > 20150623 || __GLIBCXX__ == 20140422 || __GLIBCXX__ == 20140716 || __GLIBCXX__ == 20141030
		if (!regex_match(uuid, regex("[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}"))) {
			throw invalid_argument("The uuid does not match the official uuid regular expression : " + uuid);
		}
#else
		if (!boost::regex_match(uuid, boost::regex("[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}"))) {
			throw invalid_argument("The uuid does not match the official uuid regular expression : " + uuid);
		}
#endif
		if (gsoapProxy2_0_1 != nullptr) { gsoapProxy2_0_1->uuid = uuid; }
		else if (gsoapProxy2_3 != nullptr) { gsoapProxy2_3->uuid = uuid; }
	}
}

void AbstractObject::setTitle(const std::string & title)
{
	cannotBePartial();
	if (title.size() > 256) {
		throw range_error("The title cannot be more than 256 chars long.");
	}

	if (title.empty()) {
		if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->Citation->Title = "unknown";
		else if (gsoapProxy2_3 != nullptr) gsoapProxy2_3->Citation->Title = "unknown";
	}
	else {
		if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->Citation->Title = title;
		else if (gsoapProxy2_3 != nullptr) gsoapProxy2_3->Citation->Title = title;
	}
}

void AbstractObject::setEditor(const std::string & editor)
{
	cannotBePartial();
	if (editor.size() > 64) {
		throw range_error("The editor cannot be more than 64 chars long.");
	}

	if (!editor.empty()) {
		if (gsoapProxy2_0_1 != nullptr) {
			if (gsoapProxy2_0_1->Citation->Editor == nullptr)
				gsoapProxy2_0_1->Citation->Editor = gsoap_resqml2_0_1::soap_new_std__string(gsoapProxy2_0_1->soap);
			gsoapProxy2_0_1->Citation->Editor->assign(editor);
		}
		else if (gsoapProxy2_3 != nullptr) {
			if (gsoapProxy2_3->Citation->Editor == nullptr)
				gsoapProxy2_3->Citation->Editor = gsoap_eml2_3::soap_new_std__string(gsoapProxy2_3->soap);
			gsoapProxy2_3->Citation->Editor->assign(editor);
		}
	}
}

void AbstractObject::setCreation(time_t creation)
{
	if (creation > 0) {
		std::tm tmConversion = timeTools::to_calendar_time(timeTools::from_time_t(creation));
		setCreation(tmConversion);
	}
	else {
		time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		setCreation(now);
	}
}

void AbstractObject::setCreation(const tm & creation)
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		gsoapProxy2_0_1->Citation->Creation = creation;
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoapProxy2_3->Citation->Creation = creation;
	}
}

void AbstractObject::setOriginator(const std::string & originator)
{
	cannotBePartial();
	if (originator.size() > 64) {
		throw range_error("The originator cannot be more than 64 chars long.");
	}

	if (originator.empty()) {
#if defined(__gnu_linux__) || defined(__APPLE__)
		struct passwd *pw;
		uid_t uid;

		uid = geteuid();
		pw = getpwuid(uid);	// may rise a false positive memory leak with Valgrind
							// (https://stackoverflow.com/questions/40226297/struct-passwd-is-source-of-memory-leak-how-to-properly-free?rq=1)
		if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->Citation->Originator = pw != nullptr ? pw->pw_name : "unknown";
		else if (gsoapProxy2_3 != nullptr) gsoapProxy2_3->Citation->Originator = pw != nullptr ? pw->pw_name : "unknown";
#elif defined(_WIN32)
		char acUserName[32];
		DWORD nUserName = sizeof(acUserName);
		GetUserName(acUserName, &nUserName);
		if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->Citation->Originator = acUserName;
		else if (gsoapProxy2_3 != nullptr) gsoapProxy2_3->Citation->Originator = acUserName;
#endif	
	}
	else {
		if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->Citation->Originator = originator;
		else if (gsoapProxy2_3 != nullptr) gsoapProxy2_3->Citation->Originator = originator;
	}
}

void AbstractObject::setDescription(const std::string & description)
{
	cannotBePartial();

	if (!description.empty())
	{
		if (gsoapProxy2_0_1 != nullptr) {
			if (description.size() > 4000) {
				throw range_error("The description cannot be more than 4000 chars long.");
			}
			if (gsoapProxy2_0_1->Citation->Description == nullptr)
				gsoapProxy2_0_1->Citation->Description = gsoap_resqml2_0_1::soap_new_std__string(gsoapProxy2_0_1->soap);
			gsoapProxy2_0_1->Citation->Description->assign(description);
		}
		else if (gsoapProxy2_3 != nullptr) {
			if (description.size() > 2000) {
				throw range_error("The description cannot be more than 2000 chars long.");
			}
			if (gsoapProxy2_3->Citation->Description == nullptr)
				gsoapProxy2_3->Citation->Description = gsoap_eml2_3::soap_new_std__string(gsoapProxy2_3->soap);
			gsoapProxy2_3->Citation->Description->assign(description);
		}
	}
}

void AbstractObject::setLastUpdate(time_t lastUpdate)
{
	cannotBePartial();

	if (lastUpdate > 0) {
		
		if (lastUpdate < getCreation()) {
			throw invalid_argument("Last update cannot be inferior to creation date.");
		}

		std::tm tmConversion = timeTools::to_calendar_time(timeTools::from_time_t(lastUpdate));
		setLastUpdate(tmConversion);
	}
}

void AbstractObject::setLastUpdate(const tm & lastUpdate)
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		if (gsoapProxy2_0_1->Citation->LastUpdate == nullptr) {
			gsoapProxy2_0_1->Citation->LastUpdate = (tm*)soap_malloc(gsoapProxy2_0_1->soap, sizeof(tm));
		}
		*gsoapProxy2_0_1->Citation->LastUpdate = lastUpdate;
	}
	else if (gsoapProxy2_3 != nullptr) {
		if (gsoapProxy2_3->Citation->LastUpdate == nullptr) {
			gsoapProxy2_3->Citation->LastUpdate = (tm*)soap_malloc(gsoapProxy2_3->soap, sizeof(tm));
		}
		*gsoapProxy2_3->Citation->LastUpdate = lastUpdate;
	}
}

void AbstractObject::setFormat(const std::string & vendor, const std::string & applicationName, const std::string & applicationVersionNumber)
{
	string format = vendor;
	format += ':';
	format += applicationName;
	format += ':';
	format += applicationVersionNumber;
	if (vendor.size() + applicationName.size() + applicationVersionNumber.size() > 1998) {
		throw range_error("The format cannot be more than 2000 chars long");
	}

	format.copy(citationFormat, format.size());
	citationFormat[format.size()] = '\0';
}

void AbstractObject::setDescriptiveKeywords(const std::string & descriptiveKeywords)
{
	cannotBePartial();

	if (!descriptiveKeywords.empty())
	{
		if (gsoapProxy2_0_1 != nullptr) {
			if (descriptiveKeywords.size() > 4000) {
				throw range_error("The descriptiveKeywords cannot be more than 4000 chars long.");
			}
			if (gsoapProxy2_0_1->Citation->DescriptiveKeywords == nullptr)
				gsoapProxy2_0_1->Citation->DescriptiveKeywords = gsoap_resqml2_0_1::soap_new_std__string(gsoapProxy2_0_1->soap);
			gsoapProxy2_0_1->Citation->DescriptiveKeywords->assign(descriptiveKeywords);
		}
		else if (gsoapProxy2_3 != nullptr) {
			if (descriptiveKeywords.size() > 2000) {
				throw range_error("The descriptiveKeywords cannot be more than 2000 chars long.");
			}
			if (gsoapProxy2_3->Citation->DescriptiveKeywords == nullptr)
				gsoapProxy2_3->Citation->DescriptiveKeywords = gsoap_eml2_3::soap_new_std__string(gsoapProxy2_3->soap);
			gsoapProxy2_3->Citation->DescriptiveKeywords->assign(descriptiveKeywords);
		}
	}
}

void AbstractObject::setVersion(const std::string & version)
{
	if (version.empty()) {
		throw invalid_argument("Cannot set an empty version");
	}
	if (version.size() > 64) {
		throw range_error("The version cannot be more than 64 chars long.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		if (gsoapProxy2_0_1->Citation->VersionString == nullptr)
			gsoapProxy2_0_1->Citation->VersionString = gsoap_resqml2_0_1::soap_new_std__string(gsoapProxy2_0_1->soap);
		gsoapProxy2_0_1->Citation->VersionString->assign(version);
	}
	else if (gsoapProxy2_3 != nullptr) {
		if (gsoapProxy2_3->objectVersion == nullptr)
			gsoapProxy2_3->objectVersion = gsoap_eml2_3::soap_new_std__string(gsoapProxy2_3->soap);
		gsoapProxy2_3->objectVersion->assign(version);
	}
	else if (isPartial()) {
		if (partialObject->VersionString == nullptr)
			partialObject->VersionString = gsoap_resqml2_0_1::soap_new_std__string(partialObject->soap);
		partialObject->VersionString->assign(version);
	}
}

void AbstractObject::initMandatoryMetadata()
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		gsoapProxy2_0_1->schemaVersion = getXmlNamespaceVersion();
		gsoapProxy2_0_1->Citation = gsoap_resqml2_0_1::soap_new_eml20__Citation(gsoapProxy2_0_1->soap);
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoapProxy2_3->schemaVersion = getXmlNamespaceVersion();
		gsoapProxy2_3->Citation = gsoap_eml2_3::soap_new_eml23__Citation(gsoapProxy2_3->soap);
	}

	setMetadata(std::string(), std::string(), std::string(), -1, std::string(), std::string(), -1, std::string());
}

void AbstractObject::setMetadata(const std::string & guid, const std::string & title, const std::string & editor, time_t creation, const std::string & originator,
				const std::string & description, time_t lastUpdate, const std::string & descriptiveKeywords)
{
	setUuid(guid);
	setMetadata(title, editor, creation, originator, description, lastUpdate, descriptiveKeywords);
}

void AbstractObject::setMetadata(const std::string & title, const std::string & editor, time_t creation, const std::string & originator,
	const std::string & description, time_t lastUpdate, const std::string & descriptiveKeywords)
{
	cannotBePartial();

	setTitle(title);

	setEditor(editor);

	setCreation(creation);

	setOriginator(originator);

	setDescription(description);

	setLastUpdate(lastUpdate);

	setDescriptiveKeywords(descriptiveKeywords);

	if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->Citation->Format = citationFormat;
	else if (gsoapProxy2_3 != nullptr) gsoapProxy2_3->Citation->Format = citationFormat;
}

void AbstractObject::serializeIntoStream(ostream * stream)
{
	cannotBePartial();

	if (stream == nullptr) {
		throw invalid_argument("The stream where the entity will be stored cannot be null.");
	}

	string xmlTagIncludingNamespace = getXmlNamespace() + ":" + getXmlTag();

	if (gsoapProxy2_0_1 != nullptr) {
		gsoapProxy2_0_1->soap->os = stream;
		(soap_begin_send(gsoapProxy2_0_1->soap) || soap_send(gsoapProxy2_0_1->soap, gsoapProxy2_0_1->soap->prolog ? gsoapProxy2_0_1->soap->prolog : "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n") ||
			(gsoapProxy2_0_1->soap_serialize(gsoapProxy2_0_1->soap), 0) ||
			gsoapProxy2_0_1->soap_put(gsoapProxy2_0_1->soap, xmlTagIncludingNamespace.c_str(), nullptr) ||
			soap_end_send(gsoapProxy2_0_1->soap));
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoapProxy2_3->soap->os = stream;
		(soap_begin_send(gsoapProxy2_3->soap) || soap_send(gsoapProxy2_3->soap, gsoapProxy2_3->soap->prolog ? gsoapProxy2_3->soap->prolog : "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n") ||
			(gsoapProxy2_3->soap_serialize(gsoapProxy2_3->soap), 0) ||
			gsoapProxy2_3->soap_put(gsoapProxy2_3->soap, xmlTagIncludingNamespace.c_str(), nullptr) ||
			soap_end_send(gsoapProxy2_3->soap));
	}
	else {
		throw invalid_argument("Cannot serialize a partial object.");
	}
}

gsoap_resqml2_0_1::eml20__DataObjectReference* AbstractObject::newResqmlReference() const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* result = gsoap_resqml2_0_1::soap_new_eml20__DataObjectReference(getGsoapContext());
	result->UUID = getUuid();
	result->Title = getTitle();
	result->ContentType = getContentType();
	if (!getVersion().empty()) {
		result->VersionString = gsoap_resqml2_0_1::soap_new_std__string(getGsoapContext());
		result->VersionString->assign(getVersion());
	}

	return result;
}

gsoap_eml2_3::eml23__DataObjectReference* AbstractObject::newEml23Reference() const
{
	gsoap_eml2_3::eml23__DataObjectReference* result = gsoap_eml2_3::soap_new_eml23__DataObjectReference(getGsoapContext());
	result->Uuid = getUuid();
	result->Title = getTitle();
	result->QualifiedType = getQualifiedType();
	if (!getVersion().empty()) // Not partial transfer
	{
		result->ObjectVersion = gsoap_eml2_3::soap_new_std__string(getGsoapContext());
		result->ObjectVersion->assign(getVersion());
	}

	return result;
}

gsoap_resqml2_0_1::resqml20__ContactElementReference* AbstractObject::newContactElementReference2_0_1() const
{
	cannotBePartial();

	gsoap_resqml2_0_1::resqml20__ContactElementReference* result = gsoap_resqml2_0_1::soap_new_resqml20__ContactElementReference(getGsoapContext());
	result->UUID = getUuid();
	if (!getVersion().empty()) // Not partial transfer
	{
		result->VersionString = gsoap_resqml2_0_1::soap_new_std__string(getGsoapContext());
		result->VersionString->assign(getVersion());
	}
	result->Title = getTitle();
	result->ContentType = getContentType();

	return result;
}

gsoap_eml2_3::resqml22__ContactElement* AbstractObject::newContactElementReference2_2() const
{
	if (partialObject != nullptr) {
		throw invalid_argument("The wrapped gsoap proxy must not be null");
	}

	gsoap_eml2_3::resqml22__ContactElement* result = gsoap_eml2_3::soap_new_resqml22__ContactElement(getGsoapContext());
	result->Uuid = getUuid();
	if (!getVersion().empty())
	{
		result->ObjectVersion = gsoap_eml2_3::soap_new_std__string(getGsoapContext());
		result->ObjectVersion->assign(getVersion());
	}
	result->Title = getTitle();
	result->QualifiedType = getQualifiedType();

	return result;
}

std::string AbstractObject::getXmlNamespaceVersion() const
{
	const std::string & xmlNs = getXmlNamespace();
	const size_t xmlNsSize = xmlNs.size();

	std::string result = "";
	result += xmlNs[xmlNsSize - 2];
	result +=  '.';
	result += xmlNs[xmlNsSize - 1];
	return result;
}

string AbstractObject::getContentType() const
{
	const std::string & xmlNs = getXmlNamespace();
	return "application/x-" + xmlNs.substr(0, xmlNs.size()-2) + "+xml;version=" + getXmlNamespaceVersion() + ";type=" + (xmlNs == "resqml20" || xmlNs == "eml20" ? "obj_" + getXmlTag() : getXmlTag());
}

string AbstractObject::getQualifiedType() const
{
	const std::string & xmlNs = getXmlNamespace();
	return getXmlNamespace() + "." + (xmlNs == "resqml20" || xmlNs == "eml20" ? "obj_" + getXmlTag() : getXmlTag());
}

std::string AbstractObject::getPartNameInEpcDocument() const
{
	const std::string partName = getXmlTag() + "_" + getUuid() + ".xml";
	const std::string & xmlNs = getXmlNamespace();
	return "namespace_" + xmlNs + "/" + (xmlNs == "resqml20" || xmlNs == "eml20" ? "obj_" + partName : partName);
}

string AbstractObject::serializeIntoString()
{
	ostringstream oss;

	serializeIntoStream(&oss);

	return oss.str();
}

void AbstractObject::addAlias(const std::string & authority, const std::string & title)
{
	cannotBePartial();
	if (authority.size() > 64) {
		throw range_error("The authority cannot be more than 64 chars long.");
	}
	if (title.size() > 64) {
		throw range_error("The identifier cannot be more than 64 chars long.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::eml20__ObjectAlias* alias = gsoap_resqml2_0_1::soap_new_eml20__ObjectAlias(gsoapProxy2_0_1->soap);
		alias->authority = gsoap_resqml2_0_1::soap_new_std__string(gsoapProxy2_0_1->soap);
		alias->authority->assign(authority);
		alias->Identifier = title;
		gsoapProxy2_0_1->Aliases.push_back(alias);
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::eml23__ObjectAlias* alias = gsoap_eml2_3::soap_new_eml23__ObjectAlias(gsoapProxy2_3->soap);
		alias->authority = authority;
		alias->Identifier = title;
		gsoapProxy2_3->Aliases.push_back(alias);
	}
}

uint64_t AbstractObject::getAliasCount() const
{
	if (isPartial()) {
		throw invalid_argument("The wrapped gsoap proxy must not be null");
	}

	size_t count = 0;

	if (gsoapProxy2_0_1 != nullptr) {
		count = gsoapProxy2_0_1->Aliases.size();
	}
	else if (gsoapProxy2_3 != nullptr) {
		count = gsoapProxy2_3->Aliases.size();
	}

	return count;
}

std::string AbstractObject::getAliasAuthorityAtIndex(uint64_t index) const
{
	if (isPartial())
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr) {
		return (gsoapProxy2_0_1->Aliases).at(index)->authority
			? *((gsoapProxy2_0_1->Aliases).at(index)->authority)
			: "";
	}
	else if (gsoapProxy2_3 != nullptr) {
		return gsoapProxy2_3->Aliases.at(index)->authority;
	}

	throw invalid_argument("No underlying gsoap proxy.");
}

std::string AbstractObject::getAliasTitleAtIndex(uint64_t index) const
{
	if (isPartial())
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr) {
		return (gsoapProxy2_0_1->Aliases).at(index)->Identifier;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return gsoapProxy2_3->Aliases.at(index)->Identifier;
	}

	throw invalid_argument("No underlying gsoap proxy.");
}

std::vector<EML2_NS::Activity*> AbstractObject::getActivitySet() const
{
	return getRepository()->getSourceObjects<EML2_NS::Activity>(this);
}

uint64_t AbstractObject::getActivityCount() const
{
	return getActivitySet().size();
}

EML2_NS::Activity* AbstractObject::getActivity(uint64_t index) const
{
	return getActivitySet().at(index);
}

void AbstractObject::pushBackExtraMetadata(const std::string & key, const std::string & value)
{
	if (gsoapProxy2_0_1 != nullptr)
	{
		gsoap_resqml2_0_1::resqml20__NameValuePair* stringPair = gsoap_resqml2_0_1::soap_new_resqml20__NameValuePair(gsoapProxy2_0_1->soap);
		stringPair->Name = key;
		stringPair->Value = value;
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata.push_back(stringPair);
	}
	else if (gsoapProxy2_3 != nullptr)
	{
		if (value.size() > 64) {
			throw invalid_argument("An extra metadata value cannot be greater than 64 chars.");
		}

		gsoap_eml2_3::eml23__ExtensionNameValue* stringPair = gsoap_eml2_3::soap_new_eml23__ExtensionNameValue(gsoapProxy2_3->soap);
		stringPair->Name = key;
		stringPair->Value = gsoap_eml2_3::soap_new_eml23__StringMeasure(gsoapProxy2_3->soap);
		stringPair->Value->__item = value;
		gsoapProxy2_3->ExtensionNameValue.push_back(stringPair);
	}
}

std::unordered_map< std::string, std::string > AbstractObject::getExtraMetadataSet() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		std::unordered_map< std::string, std::string > result;
		for (size_t i = 0; i < static_cast<gsoap_resqml2_0_1::resqml20__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata.size(); ++i) {
			result[static_cast<gsoap_resqml2_0_1::resqml20__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata[i]->Name] = static_cast<gsoap_resqml2_0_1::resqml20__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata[i]->Value;
		}

		return result;
	}
	
	throw logic_error("Not implemented yet.");
}

vector<string> AbstractObject::getExtraMetadata(const std::string & key) const
{
	vector<string> result;
	if (gsoapProxy2_0_1 != nullptr) {
		for (size_t i = 0; i < static_cast<gsoap_resqml2_0_1::resqml20__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata.size(); ++i) {
			if (static_cast<gsoap_resqml2_0_1::resqml20__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata[i]->Name.compare(key) == 0) {
				result.push_back(static_cast<gsoap_resqml2_0_1::resqml20__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata[i]->Value);
			}
		}
	}

	return result;
}

unsigned int AbstractObject::getExtraMetadataCount() const
{
	size_t result = 0;
	if (gsoapProxy2_0_1 != nullptr) {
		result = static_cast<gsoap_resqml2_0_1::resqml20__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata.size();
	}
	else if (gsoapProxy2_3 != nullptr) {
		result = static_cast<gsoap_eml2_3::eml23__AbstractObject*>(gsoapProxy2_3)->ExtensionNameValue.size();
	}
	else {
		throw logic_error("Not implemented yet.");
	}

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too much extra metadata.");
	}

	return static_cast<unsigned int>(result);
}

std::string AbstractObject::getExtraMetadataKeyAtIndex(unsigned int index) const
{
	if (getExtraMetadataCount() <= index) {
		throw out_of_range("The index is out of range.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return (static_cast<gsoap_resqml2_0_1::resqml20__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata)[index]->Name;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return (static_cast<gsoap_eml2_3::eml23__AbstractObject*>(gsoapProxy2_3)->ExtensionNameValue)[index]->Name;
	}
	
	throw logic_error("Not implemented yet.");
}

std::string AbstractObject::getExtraMetadataStringValueAtIndex(unsigned int index) const
{
	if (getExtraMetadataCount() <= index) {
		throw out_of_range("The index is out of range.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return (static_cast<gsoap_resqml2_0_1::resqml20__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata)[index]->Value;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return (static_cast<gsoap_eml2_3::eml23__AbstractObject*>(gsoapProxy2_3)->ExtensionNameValue)[index]->Value->__item;
	}

	throw logic_error("Not implemented yet.");
}

void AbstractObject::readArrayNdOfFloatValues(gsoap_resqml2_0_1::resqml20__AbstractDoubleArray const* arrayInput, float* arrayOutput) const
{
	long soapType = arrayInput->soap_type();
	if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array)
	{
		EML2_NS::AbstractHdfProxy* hdfProxy = repository->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array const*>(arrayInput)->Values->HdfProxy->UUID);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The hdf proxy " + static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array const*>(arrayInput)->Values->HdfProxy->UUID + " is not available.");
		}
		hdfProxy->readArrayNdOfFloatValues(static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array const*>(arrayInput)->Values->PathInHdfFile, arrayOutput);
	}
	else if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray)
	{
		gsoap_resqml2_0_1::resqml20__DoubleConstantArray const* constantArray = static_cast<gsoap_resqml2_0_1::resqml20__DoubleConstantArray const*>(arrayInput);
		if (constantArray->Value < (std::numeric_limits<float>::min)() || constantArray->Value > (std::numeric_limits<float>::max)()) {
			throw out_of_range("The double constant array " + std::to_string(constantArray->Value) + " is out of float range value");
		}
		std::fill(arrayOutput, arrayOutput + constantArray->Count, static_cast<float>(constantArray->Value));
	}
	else if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
	{
		gsoap_resqml2_0_1::resqml20__DoubleLatticeArray const* latticeArray = static_cast<gsoap_resqml2_0_1::resqml20__DoubleLatticeArray const*>(arrayInput);
		if (latticeArray->Offset.size() > 1) {
			throw invalid_argument("The integer lattice array contains more than one offset.");
		}
		for (size_t i = 0; i <= latticeArray->Offset[0]->Count; ++i) {
			arrayOutput[i] = latticeArray->StartValue + (i * latticeArray->Offset[0]->Value);
		}
	}
	else
		throw invalid_argument("The integer array type is not supported yet.");
}

void AbstractObject::readArrayNdOfFloatValues(gsoap_eml2_3::eml23__AbstractFloatingPointArray const* arrayInput, float* arrayOutput) const
{
	switch (arrayInput->soap_type()) {
	case SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray:
	{
		size_t offset = 0;
		for (auto* dataArrayPart : static_cast<gsoap_eml2_3::eml23__FloatingPointExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart) {
			EML2_NS::AbstractHdfProxy* hdfProxy = getOrCreateHdfProxyFromDataArrayPart(dataArrayPart);
			hdfProxy->readArrayNdOfFloatValues(dataArrayPart->PathInExternalFile, arrayOutput + offset);
			offset += std::accumulate(std::begin(dataArrayPart->Count), std::end(dataArrayPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>());
		}
		break;
	}
	case SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray:
	{
		gsoap_eml2_3::eml23__FloatingPointConstantArray const* constantArray = static_cast<gsoap_eml2_3::eml23__FloatingPointConstantArray const*>(arrayInput);
		std::fill(arrayOutput, arrayOutput + constantArray->Count, constantArray->Value);
		break;
	}
	case SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray:
	{
		gsoap_eml2_3::eml23__FloatingPointLatticeArray const* latticeArray = static_cast<gsoap_eml2_3::eml23__FloatingPointLatticeArray const*>(arrayInput);
		if (latticeArray->Offset.empty() || latticeArray->Offset.size() > 1) {
			throw invalid_argument("The integer lattice array of UUID " + getUuid() + " contains zero or more than one offset.");
		}
		if (latticeArray->Offset[0]->Count < 0) {
			throw invalid_argument("The count of the floating point lattice array of UUID " + getUuid() + " is negative which is not valid.");
		}
		for (size_t i = 0; i <= static_cast<size_t>(latticeArray->Offset[0]->Count); ++i) {
			arrayOutput[i] = latticeArray->StartValue + (i * latticeArray->Offset[0]->Value);
		}
		break;
	}
	case SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointXmlArray:
	{
		gsoap_eml2_3::eml23__FloatingPointXmlArray const* xmlArray = static_cast<gsoap_eml2_3::eml23__FloatingPointXmlArray const*>(arrayInput);
#if !defined(__GLIBCXX__) || __GLIBCXX__ > 20150623 || __GLIBCXX__ == 20140422 || __GLIBCXX__ == 20140716 || __GLIBCXX__ == 20141030
		const std::regex ws_re("\\s+"); // whitespace
		std::sregex_token_iterator it(xmlArray->Values.begin(), xmlArray->Values.end(), ws_re, -1);
		std::sregex_token_iterator endToken;
#else
		const boost::regex ws_re("\\s+"); // whitespace
		boost::sregex_token_iterator it(xmlArray->Values.begin(), xmlArray->Values.end(), ws_re, -1);
		boost::sregex_token_iterator endToken;
#endif
		size_t index = 0;
		while (it != endToken) {
			arrayOutput[index++] = std::stof(*it++);
		}
		break;
	}
	default: throw invalid_argument("The integer array type is not supported yet.");
	}
}

void AbstractObject::readArrayNdOfDoubleValues(gsoap_resqml2_0_1::resqml20__AbstractDoubleArray const* arrayInput, double * arrayOutput) const
{
	long soapType = arrayInput->soap_type();
	if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array)
	{
		EML2_NS::AbstractHdfProxy* hdfProxy = repository->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array const*>(arrayInput)->Values->HdfProxy->UUID);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The hdf proxy " + static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array const*>(arrayInput)->Values->HdfProxy->UUID + " is not available.");
		}
		hdfProxy->readArrayNdOfDoubleValues(static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array const*>(arrayInput)->Values->PathInHdfFile, arrayOutput);
	}
	else if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray)
	{
		gsoap_resqml2_0_1::resqml20__DoubleConstantArray const* constantArray = static_cast<gsoap_resqml2_0_1::resqml20__DoubleConstantArray const*>(arrayInput);
		for (size_t i = 0; i < constantArray->Count; ++i) {
			arrayOutput[i] = constantArray->Value;
		}
	}
	else if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
	{
		gsoap_resqml2_0_1::resqml20__DoubleLatticeArray const* latticeArray = static_cast<gsoap_resqml2_0_1::resqml20__DoubleLatticeArray const*>(arrayInput);
		if (latticeArray->Offset.size() > 1) {
			throw invalid_argument("The integer lattice array contains more than one offset.");
		}
		for (size_t i = 0; i <= latticeArray->Offset[0]->Count; ++i) {
			arrayOutput[i] = latticeArray->StartValue + (i * latticeArray->Offset[0]->Value);
		}
	}
	else
		throw invalid_argument("The integer array type is not supported yet.");
}

void AbstractObject::readArrayNdOfDoubleValues(gsoap_eml2_3::eml23__AbstractFloatingPointArray const* arrayInput, double * arrayOutput) const
{
	switch (arrayInput->soap_type()) {
	case SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray:
	{
		size_t offset = 0;
		for (auto* dataArrayPart : static_cast<gsoap_eml2_3::eml23__FloatingPointExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart) {
			EML2_NS::AbstractHdfProxy* hdfProxy = getOrCreateHdfProxyFromDataArrayPart(dataArrayPart);
			hdfProxy->readArrayNdOfDoubleValues(dataArrayPart->PathInExternalFile, arrayOutput + offset);
			offset += std::accumulate(std::begin(dataArrayPart->Count), std::end(dataArrayPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>());
		}
		break;
	}
	case SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray:
	{
		gsoap_eml2_3::eml23__FloatingPointConstantArray const* constantArray = static_cast<gsoap_eml2_3::eml23__FloatingPointConstantArray const*>(arrayInput);
		std::fill(arrayOutput, arrayOutput + constantArray->Count, constantArray->Value);
		break;
	}
	case SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray:
	{
		gsoap_eml2_3::eml23__FloatingPointLatticeArray const* latticeArray = static_cast<gsoap_eml2_3::eml23__FloatingPointLatticeArray const*>(arrayInput);
		if (latticeArray->Offset.size() > 1) {
			throw invalid_argument("The integer lattice array contains more than one offset.");
		}
		for (auto i = 0; i <= latticeArray->Offset[0]->Count; ++i) {
			arrayOutput[i] = latticeArray->StartValue + (i * latticeArray->Offset[0]->Value);
		}
		break;
	}
	case SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointXmlArray:
	{
		gsoap_eml2_3::eml23__FloatingPointXmlArray const* xmlArray = static_cast<gsoap_eml2_3::eml23__FloatingPointXmlArray const*>(arrayInput);
#if !defined(__GLIBCXX__) || __GLIBCXX__ > 20150623 || __GLIBCXX__ == 20140422 || __GLIBCXX__ == 20140716 || __GLIBCXX__ == 20141030
		const std::regex ws_re("\\s+"); // whitespace
		std::sregex_token_iterator it(xmlArray->Values.begin(), xmlArray->Values.end(), ws_re, -1);
		std::sregex_token_iterator endToken;
#else
		const boost::regex ws_re("\\s+"); // whitespace
		boost::sregex_token_iterator it(xmlArray->Values.begin(), xmlArray->Values.end(), ws_re, -1);
		boost::sregex_token_iterator endToken;
#endif
		size_t index = 0;
		while (it != endToken) {
			arrayOutput[index++] = std::stod(*it++);
		}
		break;
	}
	default: throw invalid_argument("The integer array type is not supported yet.");
	}
}

void AbstractObject::readArrayNdOfBooleanValues(gsoap_eml2_3::eml23__BooleanExternalArray const * arrayInput, int8_t* arrayOutput) const
{
	size_t offset = 0;
	for (auto const* dataArrayPart : arrayInput->Values->ExternalDataArrayPart) {
		EML2_NS::AbstractHdfProxy* hdfProxy = getOrCreateHdfProxyFromDataArrayPart(dataArrayPart);
		hdfProxy->readArrayNdOfInt8Values(dataArrayPart->PathInExternalFile, arrayOutput + offset);
		offset += std::accumulate(std::begin(dataArrayPart->Count), std::end(dataArrayPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>());
	}
}

uint8_t AbstractObject::readArrayNdOfUInt8Values(gsoap_resqml2_0_1::resqml20__AbstractValueArray const * arrayInput, uint8_t * arrayOutput) const
{
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const* dataset = nullptr;
	std::string pathInHdfFile = "";
	uint8_t nullValue = (std::numeric_limits<uint8_t>::max)();
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array const*>(arrayInput);
		if (hdfArray->NullValue > (std::numeric_limits<uint8_t>::max)()) {
			throw range_error("The null value is greater than uint8_t max.");
		}
		dataset = hdfArray->Values;
		pathInHdfFile = hdfArray->Values->PathInHdfFile;
		nullValue = static_cast<uint8_t>(hdfArray->NullValue);
	}
	else if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array const*>(arrayInput);
		dataset = hdfArray->Values;
		pathInHdfFile = hdfArray->Values->PathInHdfFile;
	}
	// DoubleHdf5Array is not supported because we should convert NaN to (std::numeric_limits<int32_t>::max)()
	// This would force to have to pass the count of values in the array.

	if (pathInHdfFile.empty()) {
		return readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}
	else {
		getHdfProxyFromDataset(dataset)->readArrayNdOfUInt8Values(pathInHdfFile, arrayOutput);
		return nullValue;
	}
}

uint8_t AbstractObject::readArrayNdOfUInt8Values(gsoap_eml2_3::eml23__AbstractValueArray const* arrayInput, uint8_t * arrayOutput) const
{
	std::vector<gsoap_eml2_3::eml23__ExternalDataArrayPart *> externalDataArrayParts;
	uint8_t nullValue = (std::numeric_limits<uint8_t>::max)();
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		externalDataArrayParts = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart;
		if (static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue > (std::numeric_limits<uint8_t>::max)()) {
			throw range_error("The null value is greater than uint8_t max.");
		}
		nullValue = static_cast<uint8_t>(static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue);
	}
	else if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
		externalDataArrayParts = static_cast<gsoap_eml2_3::eml23__BooleanExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart;
	}

	if (externalDataArrayParts.empty()) {
		return readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}
	else {
		size_t offset = 0;
		for (auto const* dataArrayPart : externalDataArrayParts) {
			getOrCreateHdfProxyFromDataArrayPart(dataArrayPart)->readArrayNdOfUInt8Values(dataArrayPart->PathInExternalFile, arrayOutput + offset);
			offset += std::accumulate(std::begin(dataArrayPart->Count), std::end(dataArrayPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>());
		}
		return nullValue;
	}
}

uint16_t AbstractObject::readArrayNdOfUInt16Values(gsoap_resqml2_0_1::resqml20__AbstractValueArray const * arrayInput, uint16_t * arrayOutput) const
{
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const* dataset = nullptr;
	std::string pathInHdfFile = "";
	uint16_t nullValue = (std::numeric_limits<uint16_t>::max)();
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array const*>(arrayInput);
		if (hdfArray->NullValue > (std::numeric_limits<uint16_t>::max)()) {
			throw range_error("The null value is greater than uint16_t max.");
		}
		dataset = hdfArray->Values;
		pathInHdfFile = hdfArray->Values->PathInHdfFile;
		nullValue = static_cast<uint16_t>(hdfArray->NullValue);
	}
	else if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array const*>(arrayInput);
		dataset = hdfArray->Values;
		pathInHdfFile = hdfArray->Values->PathInHdfFile;
	}
	// DoubleHdf5Array is not supported because we should convert NaN to (std::numeric_limits<int32_t>::max)()
	// This would force to have to pass the count of values in the array.

	if (pathInHdfFile.empty()) {
		return readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}
	else {
		getHdfProxyFromDataset(dataset)->readArrayNdOfUShortValues(pathInHdfFile, arrayOutput);
		return nullValue;
	}
}

uint16_t AbstractObject::readArrayNdOfUInt16Values(gsoap_eml2_3::eml23__AbstractValueArray const * arrayInput, uint16_t * arrayOutput) const
{
	std::vector<gsoap_eml2_3::eml23__ExternalDataArrayPart *> externalDataArrayParts;
	uint16_t nullValue = (std::numeric_limits<uint8_t>::max)();
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		externalDataArrayParts = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart;
		if (static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue > (std::numeric_limits<uint16_t>::max)()) {
			throw range_error("The null value is greater than uint16_t max.");
		}
		nullValue = static_cast<uint16_t>(static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue);
	}
	else if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
		externalDataArrayParts = static_cast<gsoap_eml2_3::eml23__BooleanExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart;
	}

	if (externalDataArrayParts.empty()) {
		return readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}
	else {
		size_t offset = 0;
		for (auto const* dataArrayPart : externalDataArrayParts) {
			getOrCreateHdfProxyFromDataArrayPart(dataArrayPart)->readArrayNdOfUShortValues(dataArrayPart->PathInExternalFile, arrayOutput + offset);
			offset += std::accumulate(std::begin(dataArrayPart->Count), std::end(dataArrayPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>());
		}
		return nullValue;
	}
}

uint32_t AbstractObject::readArrayNdOfUInt32Values(gsoap_resqml2_0_1::resqml20__AbstractValueArray const * arrayInput, uint32_t * arrayOutput) const
{
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const* dataset = nullptr;
	std::string pathInHdfFile = "";
	uint32_t nullValue = (std::numeric_limits<int32_t>::max)();
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array const*>(arrayInput);
		if (hdfArray->NullValue > (std::numeric_limits<uint32_t>::max)()) {
			throw range_error("The null value is greater than uint32_t max.");
		}
		dataset = hdfArray->Values;
		pathInHdfFile = hdfArray->Values->PathInHdfFile;
		nullValue = static_cast<uint32_t>(hdfArray->NullValue);
	}
	else if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array const*>(arrayInput);
		dataset = hdfArray->Values;
		pathInHdfFile = hdfArray->Values->PathInHdfFile;
	}
	// DoubleHdf5Array is not supported because we should convert NaN to (std::numeric_limits<int32_t>::max)()
	// This would force to have to pass the count of values in the array.

	if (pathInHdfFile.empty()) {
		return readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}
	else {
		getHdfProxyFromDataset(dataset)->readArrayNdOfUIntValues(pathInHdfFile, arrayOutput);
		return nullValue;
	}
}

uint32_t AbstractObject::readArrayNdOfUInt32Values(gsoap_eml2_3::eml23__AbstractValueArray const * arrayInput, uint32_t * arrayOutput) const
{
	std::vector<gsoap_eml2_3::eml23__ExternalDataArrayPart *> externalDataArrayParts;
	uint32_t nullValue = (std::numeric_limits<uint8_t>::max)();
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		externalDataArrayParts = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart;
		if (static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue > (std::numeric_limits<uint32_t>::max)()) {
			throw range_error("The null value is greater than uint32_t max.");
		}
		nullValue = static_cast<uint32_t>(static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue);
	}
	else if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
		externalDataArrayParts = static_cast<gsoap_eml2_3::eml23__BooleanExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart;
	}

	if (externalDataArrayParts.empty()) {
		return readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}
	else {
		size_t offset = 0;
		for (auto const* dataArrayPart : externalDataArrayParts) {
			getOrCreateHdfProxyFromDataArrayPart(dataArrayPart)->readArrayNdOfUIntValues(dataArrayPart->PathInExternalFile, arrayOutput + offset);
			offset += std::accumulate(std::begin(dataArrayPart->Count), std::end(dataArrayPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>());
		}
		return nullValue;
	}
}

uint64_t AbstractObject::readArrayNdOfUInt64Values(gsoap_resqml2_0_1::resqml20__AbstractValueArray const * arrayInput, uint64_t * arrayOutput) const
{
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const* dataset = nullptr;
	std::string pathInHdfFile = "";
	uint64_t nullValue = (std::numeric_limits<int32_t>::max)();
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array const*>(arrayInput);
		dataset = hdfArray->Values;
		pathInHdfFile = hdfArray->Values->PathInHdfFile;
		nullValue = hdfArray->NullValue;
	}
	else if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array const*>(arrayInput);
		dataset = hdfArray->Values;
		pathInHdfFile = hdfArray->Values->PathInHdfFile;
	}
	// DoubleHdf5Array is not supported because we should convert NaN to (std::numeric_limits<int32_t>::max)()
	// This would force to have to pass the count of values in the array.

	if (pathInHdfFile.empty()) {
		return readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}
	else {
		getHdfProxyFromDataset(dataset)->readArrayNdOfUInt64Values(pathInHdfFile, arrayOutput);
		return nullValue;
	}
}

uint64_t AbstractObject::readArrayNdOfUInt64Values(gsoap_eml2_3::eml23__AbstractValueArray const * arrayInput, uint64_t * arrayOutput) const
{
	std::vector<gsoap_eml2_3::eml23__ExternalDataArrayPart *> externalDataArrayParts;
	uint64_t nullValue = (std::numeric_limits<uint8_t>::max)();
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		externalDataArrayParts = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart;
		nullValue = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue;
	}
	else if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
		externalDataArrayParts = static_cast<gsoap_eml2_3::eml23__BooleanExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart;
	}

	if (externalDataArrayParts.empty()) {
		return readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}
	else {
		size_t offset = 0;
		for (auto const* dataArrayPart : externalDataArrayParts) {
			getOrCreateHdfProxyFromDataArrayPart(dataArrayPart)->readArrayNdOfUInt64Values(dataArrayPart->PathInExternalFile, arrayOutput + offset);
			offset += std::accumulate(std::begin(dataArrayPart->Count), std::end(dataArrayPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>());
		}
		return nullValue;
	}
}

int8_t AbstractObject::readArrayNdOfInt8Values(gsoap_resqml2_0_1::resqml20__AbstractValueArray const * arrayInput, int8_t* arrayOutput) const
{
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const* dataset = nullptr;
	std::string pathInHdfFile = "";
	int8_t nullValue = (std::numeric_limits<int8_t>::max)();
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array const*>(arrayInput);
		if (hdfArray->NullValue < (std::numeric_limits<int8_t>::min)() ||
			hdfArray->NullValue >(std::numeric_limits<int8_t>::max)()) {
			throw invalid_argument("One of the integer array of UUID " + getUuid() + " has a null value which is out of range of int32_t.");
		}
		dataset = hdfArray->Values;
		pathInHdfFile = hdfArray->Values->PathInHdfFile;
		nullValue = static_cast<int8_t>(hdfArray->NullValue);
	}
	else if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array const*>(arrayInput);
		dataset = hdfArray->Values;
		pathInHdfFile = hdfArray->Values->PathInHdfFile;
	}
	// DoubleHdf5Array is not supported because we should convert NaN to (std::numeric_limits<int32_t>::max)()
	// This would force to have to pass the count of values in the array.

	if (pathInHdfFile.empty()) {
		return readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}
	else {
		getHdfProxyFromDataset(dataset)->readArrayNdOfInt8Values(pathInHdfFile, arrayOutput);
		return nullValue;
	}
}

int8_t AbstractObject::readArrayNdOfInt8Values(gsoap_eml2_3::eml23__AbstractValueArray const * arrayInput, int8_t* arrayOutput) const
{
	std::vector<gsoap_eml2_3::eml23__ExternalDataArrayPart *> externalDataArrayParts;
	int8_t nullValue = (std::numeric_limits<int8_t>::max)();
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		externalDataArrayParts = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart;
		if (static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue < (std::numeric_limits<int8_t>::min)() ||
			static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue >(std::numeric_limits<int8_t>::max)()) {
			throw invalid_argument("One of the integer array of UUID " + getUuid() + " has a null value which is out of range of int8_t.");
		}
		nullValue = static_cast<uint8_t>(static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue);
	}
	else if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
		externalDataArrayParts = static_cast<gsoap_eml2_3::eml23__BooleanExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart;
	}

	if (externalDataArrayParts.empty()) {
		return readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}
	else {
		size_t offset = 0;
		for (auto const* dataArrayPart : externalDataArrayParts) {
			getOrCreateHdfProxyFromDataArrayPart(dataArrayPart)->readArrayNdOfInt8Values(dataArrayPart->PathInExternalFile, arrayOutput + offset);
			offset += std::accumulate(std::begin(dataArrayPart->Count), std::end(dataArrayPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>());
		}
		return nullValue;
	}
}

int16_t AbstractObject::readArrayNdOfInt16Values(gsoap_resqml2_0_1::resqml20__AbstractValueArray const * arrayInput, int16_t* arrayOutput) const
{
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const* dataset = nullptr;
	std::string pathInHdfFile = "";
	int16_t nullValue = (std::numeric_limits<int16_t>::max)();
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array const*>(arrayInput);
		if (hdfArray->NullValue < (std::numeric_limits<int16_t>::min)() ||
			hdfArray->NullValue >(std::numeric_limits<int16_t>::max)()) {
			throw invalid_argument("One of the integer array of UUID " + getUuid() + " has a null value which is out of range of int32_t.");
		}
		dataset = hdfArray->Values;
		pathInHdfFile = hdfArray->Values->PathInHdfFile;
		nullValue = static_cast<int16_t>(hdfArray->NullValue);
	}
	else if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array const*>(arrayInput);
		dataset = hdfArray->Values;
		pathInHdfFile = hdfArray->Values->PathInHdfFile;
	}
	// DoubleHdf5Array is not supported because we should convert NaN to (std::numeric_limits<int32_t>::max)()
	// This would force to have to pass the count of values in the array.

	if (pathInHdfFile.empty()) {
		return readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}
	else {
		getHdfProxyFromDataset(dataset)->readArrayNdOfShortValues(pathInHdfFile, arrayOutput);
		return nullValue;
	}
}

int16_t AbstractObject::readArrayNdOfInt16Values(gsoap_eml2_3::eml23__AbstractValueArray const * arrayInput, int16_t* arrayOutput) const
{
	std::vector<gsoap_eml2_3::eml23__ExternalDataArrayPart *> externalDataArrayParts;
	int16_t nullValue = (std::numeric_limits<int16_t>::max)();
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		externalDataArrayParts = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart;
		if (static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue < (std::numeric_limits<int16_t>::min)() ||
			static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue >(std::numeric_limits<int16_t>::max)()) {
			throw invalid_argument("One of the integer array of UUID " + getUuid() + " has a null value which is out of range of int16_t.");
		}
		nullValue = static_cast<int16_t>(static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue);
	}
	else if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
		externalDataArrayParts = static_cast<gsoap_eml2_3::eml23__BooleanExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart;
	}

	if (externalDataArrayParts.empty()) {
		return readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}
	else {
		size_t offset = 0;
		for (auto const* dataArrayPart : externalDataArrayParts) {
			getOrCreateHdfProxyFromDataArrayPart(dataArrayPart)->readArrayNdOfShortValues(dataArrayPart->PathInExternalFile, arrayOutput + offset);
			offset += std::accumulate(std::begin(dataArrayPart->Count), std::end(dataArrayPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>());
		}
		return nullValue;
	}
}

int32_t AbstractObject::readArrayNdOfInt32Values(gsoap_resqml2_0_1::resqml20__AbstractValueArray const * arrayInput, int32_t* arrayOutput) const
{
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const* dataset = nullptr;
	std::string pathInHdfFile = "";
	int32_t nullValue = (std::numeric_limits<int32_t>::max)();
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array const*>(arrayInput);
		if (hdfArray->NullValue < (std::numeric_limits<int32_t>::min)() ||
			hdfArray->NullValue > (std::numeric_limits<int32_t>::max)()) {
			throw invalid_argument("One of the integer array of UUID " + getUuid() + " has a null value which is out of range of int32_t.");
		}
		dataset = hdfArray->Values;
		pathInHdfFile = hdfArray->Values->PathInHdfFile;
		nullValue = static_cast<int32_t>(hdfArray->NullValue);
	}
	else if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array const*>(arrayInput);
		dataset = hdfArray->Values;
		pathInHdfFile = hdfArray->Values->PathInHdfFile;
	}
	// DoubleHdf5Array is not supported because we should convert NaN to (std::numeric_limits<int32_t>::max)()
	// This would force to have to pass the count of values in the array.

	if (pathInHdfFile.empty()) {
		return readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}
	else {
		getHdfProxyFromDataset(dataset)->readArrayNdOfIntValues(pathInHdfFile, arrayOutput);
		return nullValue;
	}
}

int32_t AbstractObject::readArrayNdOfInt32Values(gsoap_eml2_3::eml23__AbstractValueArray const * arrayInput, int32_t* arrayOutput) const
{
	std::vector<gsoap_eml2_3::eml23__ExternalDataArrayPart *> externalDataArrayParts;
	int32_t nullValue = (std::numeric_limits<int32_t>::max)();
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		externalDataArrayParts = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart;
		if (static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue < (std::numeric_limits<int32_t>::min)() ||
			static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue >(std::numeric_limits<int32_t>::max)()) {
			throw invalid_argument("One of the integer array of UUID " + getUuid() + " has a null value which is out of range of int32_t.");
		}
		nullValue = static_cast<int32_t>(static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue);
	}
	else if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
		externalDataArrayParts = static_cast<gsoap_eml2_3::eml23__BooleanExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart;
	}

	if (externalDataArrayParts.empty()) {
		return readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}
	else {
		size_t offset = 0;
		for (auto const* dataArrayPart : externalDataArrayParts) {
			getOrCreateHdfProxyFromDataArrayPart(dataArrayPart)->readArrayNdOfIntValues(dataArrayPart->PathInExternalFile, arrayOutput + offset);
			offset += std::accumulate(std::begin(dataArrayPart->Count), std::end(dataArrayPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>());
		}
		return nullValue;
	}
}

int64_t AbstractObject::readArrayNdOfInt64Values(gsoap_resqml2_0_1::resqml20__AbstractValueArray const * arrayInput, int64_t * arrayOutput) const
{
	gsoap_resqml2_0_1::eml20__Hdf5Dataset const* dataset = nullptr;
	std::string pathInHdfFile = "";
	int64_t nullValue = (std::numeric_limits<int64_t>::max)();
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array const*>(arrayInput);
		dataset = hdfArray->Values;
		pathInHdfFile = hdfArray->Values->PathInHdfFile;
		nullValue = hdfArray->NullValue;
	}
	else if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array const*>(arrayInput);
		dataset = hdfArray->Values;
		pathInHdfFile = hdfArray->Values->PathInHdfFile;
	}
	// DoubleHdf5Array is not supported because we should convert NaN to (std::numeric_limits<int32_t>::max)()
	// This would force to have to pass the count of values in the array.

	if (pathInHdfFile.empty()) {
		return readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}
	else {
		getHdfProxyFromDataset(dataset)->readArrayNdOfInt64Values(pathInHdfFile, arrayOutput);
		return nullValue;
	}
}

int64_t AbstractObject::readArrayNdOfInt64Values(gsoap_eml2_3::eml23__AbstractValueArray const * arrayInput, int64_t * arrayOutput) const
{
	std::vector<gsoap_eml2_3::eml23__ExternalDataArrayPart *> externalDataArrayParts;
	int64_t nullValue = (std::numeric_limits<int64_t>::max)();
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		externalDataArrayParts = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart;
		nullValue = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue;
	}
	else if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
		externalDataArrayParts = static_cast<gsoap_eml2_3::eml23__BooleanExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart;
	}

	if (externalDataArrayParts.empty()) {
		return readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}
	else {
		size_t offset = 0;
		for (auto const* dataArrayPart : externalDataArrayParts) {
			getOrCreateHdfProxyFromDataArrayPart(dataArrayPart)->readArrayNdOfInt64Values(dataArrayPart->PathInExternalFile, arrayOutput + offset);
			offset += std::accumulate(std::begin(dataArrayPart->Count), std::end(dataArrayPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>());
		}
		return nullValue;
	}
}

uint64_t AbstractObject::getCountOfArray(gsoap_resqml2_0_1::resqml20__AbstractValueArray const* arrayInput) const
{
	const long soapType = arrayInput->soap_type();
	// *********** INTEGER ********
	if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
	{
		EML2_NS::AbstractHdfProxy* hdfProxy = repository->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array const*>(arrayInput)->Values->HdfProxy->UUID);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The hdf proxy " + static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array const*>(arrayInput)->Values->HdfProxy->UUID + " is not available.");
		}
		return hdfProxy->getElementCount(static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array const*>(arrayInput)->Values->PathInHdfFile);
	}
	else if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerRangeArray)
	{
		return static_cast<gsoap_resqml2_0_1::resqml20__IntegerRangeArray const*>(arrayInput)->Count;
	}
	else if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
	{
		return static_cast<gsoap_resqml2_0_1::resqml20__IntegerConstantArray const*>(arrayInput)->Count;
	}
	else if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray)
	{
		gsoap_resqml2_0_1::resqml20__IntegerLatticeArray const* latticeArray = static_cast<gsoap_resqml2_0_1::resqml20__IntegerLatticeArray const*>(arrayInput);
		if (latticeArray->Offset.size() > 1) {
			throw invalid_argument("The integer lattice array contains more than one offset.");
		}
		return latticeArray->Offset[0]->Count + 1;
	}
	// *********** FLOATING POINT ********
	else if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array)
	{
		EML2_NS::AbstractHdfProxy* hdfProxy = repository->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array const*>(arrayInput)->Values->HdfProxy->UUID);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The hdf proxy " + static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array const*>(arrayInput)->Values->HdfProxy->UUID + " is not available.");
		}
		return hdfProxy->getElementCount(static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array const*>(arrayInput)->Values->PathInHdfFile);
	}
	else if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray)
	{
		return static_cast<gsoap_resqml2_0_1::resqml20__DoubleConstantArray const*>(arrayInput)->Count;
	}
	else if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
	{
		gsoap_resqml2_0_1::resqml20__DoubleLatticeArray const* latticeArray = static_cast<gsoap_resqml2_0_1::resqml20__DoubleLatticeArray const*>(arrayInput);
		if (latticeArray->Offset.size() > 1) {
			throw invalid_argument("The lattice array contains more than one offset.");
		}
		return static_cast<gsoap_resqml2_0_1::resqml20__DoubleLatticeArray const*>(arrayInput)->Offset[0]->Count + 1;
	}
	// *********** BOOLEAN ********
	else if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array)
	{
		EML2_NS::AbstractHdfProxy* hdfProxy = repository->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array const*>(arrayInput)->Values->HdfProxy->UUID);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The hdf proxy " + static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array const*>(arrayInput)->Values->HdfProxy->UUID + " is not available.");
		}
		return hdfProxy->getElementCount(static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array const*>(arrayInput)->Values->PathInHdfFile);
	}
	else if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanConstantArray)
	{
		return static_cast<gsoap_resqml2_0_1::resqml20__BooleanConstantArray const*>(arrayInput)->Count;
	}
	// *********** STRING ********
	else if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StringHdf5Array)
	{
		EML2_NS::AbstractHdfProxy* hdfProxy = repository->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(static_cast<gsoap_resqml2_0_1::resqml20__StringHdf5Array const*>(arrayInput)->Values->HdfProxy->UUID);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The hdf proxy " + static_cast<gsoap_resqml2_0_1::resqml20__StringHdf5Array const*>(arrayInput)->Values->HdfProxy->UUID + " is not available.");
		}
		return hdfProxy->getElementCount(static_cast<gsoap_resqml2_0_1::resqml20__StringHdf5Array const*>(arrayInput)->Values->PathInHdfFile);
	}

	throw invalid_argument("The integer array type is not supported yet.");
}

uint64_t AbstractObject::getCountOfArray(gsoap_eml2_3::eml23__AbstractValueArray const* arrayInput) const
{
	const long soapType = arrayInput->soap_type();
	// *********** INTEGER ********
	if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray)
	{
		uint64_t result = 0;
		for (auto const* dataArrayPart : static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart) {
			result += std::accumulate(std::begin(dataArrayPart->Count), std::end(dataArrayPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>());
		}
		return result;
	}
	else if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray)
	{
		return static_cast<gsoap_eml2_3::eml23__IntegerConstantArray const*>(arrayInput)->Count;
	}
	else if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray)
	{
		gsoap_eml2_3::eml23__IntegerLatticeArray const* latticeArray = static_cast<gsoap_eml2_3::eml23__IntegerLatticeArray const*>(arrayInput);
		if (latticeArray->Offset.size() > 1) {
			throw invalid_argument("The lattice array contains more than one offset.");
		}
		return latticeArray->Offset[0]->Count + 1;
	}
	else if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerXmlArray)
	{
		gsoap_eml2_3::eml23__IntegerXmlArray const* xmlArray = static_cast<gsoap_eml2_3::eml23__IntegerXmlArray const*>(arrayInput);
		return std::count(xmlArray->Values.begin(), xmlArray->Values.end(), ' ') + 1;
	}
	// *********** FLOATING POINT ********
	else if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray)
	{
		uint64_t result = 0;
		for (auto const* dataArrayPart : static_cast<gsoap_eml2_3::eml23__FloatingPointExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart) {
			result += std::accumulate(std::begin(dataArrayPart->Count), std::end(dataArrayPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>());
		}
		return result;
	}
	else if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray)
	{
		return static_cast<gsoap_eml2_3::eml23__FloatingPointConstantArray const*>(arrayInput)->Count;
	}
	else if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
	{
		gsoap_eml2_3::eml23__FloatingPointLatticeArray const* latticeArray = static_cast<gsoap_eml2_3::eml23__FloatingPointLatticeArray const*>(arrayInput);
		if (latticeArray->Offset.size() > 1) {
			throw invalid_argument("The lattice array contains more than one offset.");
		}
		return static_cast<gsoap_eml2_3::eml23__FloatingPointLatticeArray const*>(arrayInput)->Offset[0]->Count + 1;
	}
	else if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointXmlArray)
	{
		gsoap_eml2_3::eml23__FloatingPointXmlArray const* xmlArray = static_cast<gsoap_eml2_3::eml23__FloatingPointXmlArray const*>(arrayInput);
		return std::count(xmlArray->Values.begin(), xmlArray->Values.end(), ' ') + 1;
	}
	// *********** BOOLEAN ********
	else if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray)
	{
		uint64_t result = 0;
		for (auto dataArrayPart : static_cast<gsoap_eml2_3::eml23__BooleanExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart) {
			result += std::accumulate(std::begin(dataArrayPart->Count), std::end(dataArrayPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>());
		}
		return result;
	}
	else if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanConstantArray)
	{
		return static_cast<gsoap_eml2_3::eml23__BooleanConstantArray const*>(arrayInput)->Count;
	}
	else if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanXmlArray)
	{
		gsoap_eml2_3::eml23__BooleanXmlArray const* xmlArray = static_cast<gsoap_eml2_3::eml23__BooleanXmlArray const*>(arrayInput);
		return std::count(xmlArray->Values.begin(), xmlArray->Values.end(), ' ') + 1;
	}
	// *********** STRING ********
	else if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__StringExternalArray)
	{
		uint64_t result = 0;
		for (auto const* dataArrayPart : static_cast<gsoap_eml2_3::eml23__StringExternalArray const*>(arrayInput)->Values->ExternalDataArrayPart) {
			result += std::accumulate(std::begin(dataArrayPart->Count), std::end(dataArrayPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>());
		}
		return result;
	}
	else if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__StringConstantArray)
	{
		return static_cast<gsoap_eml2_3::eml23__StringConstantArray const*>(arrayInput)->Count;
	}
	else if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__StringXmlArray)
	{
		return static_cast<gsoap_eml2_3::eml23__StringXmlArray const*>(arrayInput)->Values.size();
	}
	else if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__StringXmlArray)
	{
		gsoap_eml2_3::eml23__StringXmlArray const* xmlArray = static_cast<gsoap_eml2_3::eml23__StringXmlArray const*>(arrayInput);
		return xmlArray->Values.size();
	}

	throw invalid_argument("The array type is not supported yet.");
}

void AbstractObject::convertDorIntoRel(const DataObjectReference& dor)
{
	AbstractObject * targetObj = getRepository()->getDataObjectByUuid(dor.getUuid());
	if (targetObj == nullptr) { // partial transfer
		getRepository()->createPartial(dor);
		targetObj = getRepository()->getDataObjectByUuid(dor.getUuid());
		if (targetObj == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		targetObj->setUriSource(getUriSource());
	}
	getRepository()->addRelationship(this, targetObj);
}

EML2_NS::AbstractHdfProxy* AbstractObject::getHdfProxyFromDataset(gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset, bool throwException) const
{
	EML2_NS::AbstractHdfProxy * hdfProxy = getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
	if (throwException && hdfProxy == nullptr) {
		throw invalid_argument("The HDF proxy " + dataset->HdfProxy->UUID + " is missing.");
	}
	return hdfProxy;
}

EML2_NS::AbstractHdfProxy* AbstractObject::getOrCreateHdfProxyFromDataArrayPart(gsoap_eml2_3::eml23__ExternalDataArrayPart const * dataArrayPart) const
{
	EML2_NS::AbstractHdfProxy* hdfProxy = getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataArrayPart->URI);

#if WITH_RESQML2_2
	if (hdfProxy == nullptr) {
		hdfProxy = new EML2_3_NS::HdfProxy(getRepository(), "", "Fake eml23 HDF Proxy", getEpcSourceFolder(), dataArrayPart->URI);
		hdfProxy->setUriSource(getUriSource());
		getRepository()->addDataObject(hdfProxy);
	}
#endif

	return hdfProxy;
}

gsoap_resqml2_0_1::resqml20__IndexableElements AbstractObject::mapIndexableElement(gsoap_eml2_3::eml23__IndexableElement toMap) const
{
	const size_t intVal = static_cast<size_t>(toMap);
	if (intVal == 0) {
		return static_cast<gsoap_resqml2_0_1::resqml20__IndexableElements>(toMap);
	}
	else if (toMap == gsoap_eml2_3::eml23__IndexableElement::intervals_x0020from_x0020datum || intVal == static_cast<size_t>(gsoap_eml2_3::eml23__IndexableElement::lines)) {
		throw std::invalid_argument("There is no mapping for this indexable element in RESQML2.0.1");
	}
	else if (intVal < 18) {
		return static_cast<gsoap_resqml2_0_1::resqml20__IndexableElements>(intVal - 1);
	}
	else if (intVal < 29) {
		return static_cast<gsoap_resqml2_0_1::resqml20__IndexableElements>(intVal - 2);
	}
	else {
		throw std::invalid_argument("The RESQML2.2 indexable element is not part of the RESQML2.2 enumeration.");
	}
}

gsoap_eml2_3::eml23__ExternalDataArrayPart* AbstractObject::createExternalDataArrayPart(const std::string& datasetName, LONG64 count, EML2_NS::AbstractHdfProxy* proxy) const
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	if (count <= 0) {
		throw std::invalid_argument("You cannot create an external data array part whose count <= 0.");
	}
	if (datasetName.size() > 2000) {
		throw std::invalid_argument("The ExternalDataArrayPart.PathInExternalFile attribute cannot be longer than 2000 chars.");
	}

	auto* dataArrayPart = gsoap_eml2_3::soap_new_eml23__ExternalDataArrayPart(getGsoapContext());
	dataArrayPart->URI = proxy->getRelativePath();
	dataArrayPart->MimeType = gsoap_eml2_3::soap_new_std__string(gsoapProxy2_3->soap);
	dataArrayPart->MimeType->assign(EML2_NS::AbstractHdfProxy::MIME_TYPE);
	dataArrayPart->PathInExternalFile = datasetName;
	dataArrayPart->StartIndex.push_back(0);
	dataArrayPart->Count.push_back(count);
	return dataArrayPart;
}
