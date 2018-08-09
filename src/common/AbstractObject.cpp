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

#include "common/AbstractObject.h"

#include <stdexcept>
#include <string>
#include <sstream>
#if (defined(_WIN32) || (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9))))
#include <regex>
#endif
#include <algorithm>

#include "tools/GuidTools.h"

#if defined(__gnu_linux__) || defined(__APPLE__)
#include <unistd.h>
#include <pwd.h>
#endif

#include "resqml2/Activity.h"

using namespace std;
using namespace COMMON_NS;
using namespace gsoap_resqml2_0_1;

AbstractObject::AbstractObject() :
	partialObject(nullptr), gsoapProxy2_0_1(nullptr),
	gsoapProxy2_1(nullptr),
	epcDocument(nullptr), updateXml(true) {
}

/**
* Only for partial transfer
*/
AbstractObject::AbstractObject(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject):
	partialObject(partialObject), gsoapProxy2_0_1(nullptr),
	gsoapProxy2_1(nullptr),
	epcDocument (nullptr), updateXml(true) {
}

AbstractObject::AbstractObject(gsoap_resqml2_0_1::eml20__AbstractCitedDataObject* proxy):
	partialObject(nullptr), gsoapProxy2_0_1(proxy),
	gsoapProxy2_1(nullptr),
	epcDocument(nullptr), updateXml(true) {
}

AbstractObject::AbstractObject(gsoap_eml2_1::eml21__AbstractObject* proxy) :
	partialObject(nullptr), gsoapProxy2_0_1(nullptr),
	gsoapProxy2_1(proxy),
	epcDocument(nullptr), updateXml(true) {
}

void AbstractObject::cannotBePartial() const
{
	if (isPartial()) {
		throw logic_error("This method cannot be called on a partial object (" + getUuid() + ")");
	}
}

void AbstractObject::changeToPartialObject()
{
	cannotBePartial();
	string uuid = getUuid();
	string title = getTitle();
	string contentType = getContentType();
	partialObject = gsoapProxy2_0_1 != nullptr ? soap_new_eml20__DataObjectReference(gsoapProxy2_0_1->soap, 1) : soap_new_eml20__DataObjectReference(gsoapProxy2_1->soap, 1);
	partialObject->UUID = uuid;
	partialObject->Title = title;
	partialObject->ContentType = contentType;
}

soap* AbstractObject::getGsoapContext() const
{
	if (gsoapProxy2_0_1 == nullptr
		&& gsoapProxy2_1 == nullptr) {
		return getEpcDocument() == nullptr ? nullptr : getEpcDocument()->getGsoapContext();
	}
	else if (gsoapProxy2_0_1 != nullptr) {
		return gsoapProxy2_0_1->soap;
	}
	else if (gsoapProxy2_1 != nullptr) {
		return gsoapProxy2_1->soap;
	}

	throw invalid_argument("There is no available gsoap proxy instance.");
}

int AbstractObject::getGsoapType() const {
	if (gsoapProxy2_0_1 != nullptr) {
		return gsoapProxy2_0_1->soap_type();
	}
	else if (gsoapProxy2_1 != nullptr) {
		return gsoapProxy2_1->soap_type();
	}
	else {
		return partialObject->soap_type();
	}

	throw invalid_argument("There is no available gsoap proxy instance.");
}

string AbstractObject::getUuid() const
{
	if (partialObject != nullptr) // partial transfer
		return partialObject->UUID;
	else if (gsoapProxy2_0_1 != nullptr)
		return gsoapProxy2_0_1->uuid;
	else if (gsoapProxy2_1 != nullptr)
		return gsoapProxy2_1->uuid;

	throw invalid_argument("There is no available gsoap proxy instance.");
}

string AbstractObject::getTitle() const
{
	if (partialObject != nullptr) // partial transfer
		return partialObject->Title;
	else if (gsoapProxy2_0_1 != nullptr)
		return gsoapProxy2_0_1->Citation->Title;
	else if (gsoapProxy2_1 != nullptr)
		return gsoapProxy2_1->Citation->Title;

	throw invalid_argument("There is no available gsoap proxy instance.");
}

string AbstractObject::getEditor() const
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr && gsoapProxy2_0_1->Citation->Editor)
		return *gsoapProxy2_0_1->Citation->Editor;
	else if (gsoapProxy2_1 != nullptr && gsoapProxy2_1->Citation->Editor)
		return *gsoapProxy2_1->Citation->Editor;
	else
		return "";
}

time_t AbstractObject::getCreation() const
{
	tm tmp = getCreationAsTimeStructure();
	return mktime(&tmp);
}

tm AbstractObject::getCreationAsTimeStructure() const
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr)
		return gsoapProxy2_0_1->Citation->Creation;
	else if (gsoapProxy2_1 != nullptr)
		return gsoapProxy2_1->Citation->Creation;

	throw invalid_argument("There is no available gsoap proxy instance.");
}

string AbstractObject::getOriginator() const
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr)
		return gsoapProxy2_0_1->Citation->Originator;
	else if (gsoapProxy2_1 != nullptr)
		return gsoapProxy2_1->Citation->Originator;

	throw invalid_argument("There is no available gsoap proxy instance.");
}

string AbstractObject::getDescription() const
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr && gsoapProxy2_0_1->Citation->Description)
		return *gsoapProxy2_0_1->Citation->Description;
	else if (gsoapProxy2_1 != nullptr && gsoapProxy2_1->Citation->Description)
		return *gsoapProxy2_1->Citation->Description;
	else
		return "";
}

time_t AbstractObject::getLastUpdate() const
{
	tm result = getLastUpdateAsTimeStructure();

	if (result.tm_mday == 0) {
		return -1;
	}

	return mktime(&result);
}

tm AbstractObject::getLastUpdateAsTimeStructure() const
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr && gsoapProxy2_0_1->Citation->LastUpdate)
		return *gsoapProxy2_0_1->Citation->LastUpdate;
	else if (gsoapProxy2_1 != nullptr && gsoapProxy2_1->Citation->LastUpdate)
		return *gsoapProxy2_1->Citation->LastUpdate;
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
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr)
		return gsoapProxy2_0_1->Citation->Format;
	else if (gsoapProxy2_1 != nullptr)
		return gsoapProxy2_1->Citation->Format;

	throw invalid_argument("There is no available gsoap proxy instance.");
}

string AbstractObject::getDescriptiveKeywords() const
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr && gsoapProxy2_0_1->Citation->DescriptiveKeywords)
		return *gsoapProxy2_0_1->Citation->DescriptiveKeywords;
	else if (gsoapProxy2_1 != nullptr && gsoapProxy2_1->Citation->DescriptiveKeywords)
		return *gsoapProxy2_1->Citation->DescriptiveKeywords;
	else
		return string();
}

std::string AbstractObject::getVersionString() const
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr && gsoapProxy2_0_1->Citation->VersionString)
		return *gsoapProxy2_0_1->Citation->VersionString;
	else if (gsoapProxy2_1 != nullptr && gsoapProxy2_1->Citation->VersionString)
		return *gsoapProxy2_1->Citation->VersionString;
	else
		return string();
}

void AbstractObject::setUuid(const std::string & uuid)
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (uuid.empty()) {
		if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->uuid = GuidTools::generateUidAsString();
		else if (gsoapProxy2_1 != nullptr) gsoapProxy2_1->uuid = GuidTools::generateUidAsString();
	}
	else
	{
#if (defined(_WIN32) || (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9))))
		if (!regex_match(uuid, regex("[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}")))
			throw invalid_argument("The uuid does not match the official uuid regular expression : " + uuid);
#endif
		if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->uuid = uuid;
		else if (gsoapProxy2_1 != nullptr) gsoapProxy2_1->uuid = uuid;
	}
}

void AbstractObject::setTitle(const std::string & title)
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (title.empty()) {
		if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->Citation->Title = "unknown";
		else if (gsoapProxy2_1 != nullptr) gsoapProxy2_1->Citation->Title = "unknown";
	}
	else {
		if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->Citation->Title = title;
		else if (gsoapProxy2_1 != nullptr) gsoapProxy2_1->Citation->Title = title;
	}
}

void AbstractObject::setEditor(const std::string & editor)
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (!editor.empty()) {
		if (gsoapProxy2_0_1 != nullptr) {
			if (gsoapProxy2_0_1->Citation->Editor == nullptr)
				gsoapProxy2_0_1->Citation->Editor = soap_new_std__string(gsoapProxy2_0_1->soap, 1);
			gsoapProxy2_0_1->Citation->Editor->assign(editor);
		}
		else {
			if (gsoapProxy2_1->Citation->Editor == nullptr)
				gsoapProxy2_1->Citation->Editor = soap_new_std__string(gsoapProxy2_1->soap, 1);
			gsoapProxy2_1->Citation->Editor->assign(editor);
		}
	}
}

void AbstractObject::setCreation(const time_t & creation)
{
	if (creation > 0) {
		setCreation(*gmtime(&creation));
	}
	else {
		time_t now;
		time(&now);
		setCreation(*gmtime(&now));
	}
}

void AbstractObject::setCreation(const tm & creation)
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr) {
		gsoapProxy2_0_1->Citation->Creation = creation;
	}
	else if (gsoapProxy2_1 != nullptr) {
		gsoapProxy2_1->Citation->Creation = creation;
	}
}

void AbstractObject::setOriginator(const std::string & originator)
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (originator.empty()) {
#if defined(__gnu_linux__) || defined(__APPLE__)
		struct passwd *pw;
		uid_t uid;

		uid = geteuid();
		pw = getpwuid(uid);
		if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->Citation->Originator = pw != nullptr ? pw->pw_name : "unknown";
		else if (gsoapProxy2_1 != nullptr) gsoapProxy2_1->Citation->Originator = pw != nullptr ? pw->pw_name : "unknown";
#elif defined(_WIN32)
		char acUserName[32];
		DWORD nUserName = sizeof(acUserName);
		GetUserName(acUserName, &nUserName);
		if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->Citation->Originator = acUserName;
		else if (gsoapProxy2_1 != nullptr) gsoapProxy2_1->Citation->Originator = acUserName;
#endif	
	}
	else {
		if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->Citation->Originator = originator;
		else if (gsoapProxy2_1 != nullptr) gsoapProxy2_1->Citation->Originator = originator;
	}
}

void AbstractObject::setDescription(const std::string & description)
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (!description.empty())
	{
		if (gsoapProxy2_0_1 != nullptr) {
			if (gsoapProxy2_0_1->Citation->Description == nullptr)
				gsoapProxy2_0_1->Citation->Description = soap_new_std__string(gsoapProxy2_0_1->soap, 1);
			gsoapProxy2_0_1->Citation->Description->assign(description);
		}
		else {
			if (gsoapProxy2_1->Citation->Description == nullptr)
				gsoapProxy2_1->Citation->Description = soap_new_std__string(gsoapProxy2_1->soap, 1);
			gsoapProxy2_1->Citation->Description->assign(description);
		}
	}
}

void AbstractObject::setLastUpdate(const time_t & lastUpdate)
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (lastUpdate > 0) {
		setLastUpdate(*gmtime(&lastUpdate));
	}
}

void AbstractObject::setLastUpdate(const tm & lastUpdate)
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr) {
		if (gsoapProxy2_0_1->Citation->LastUpdate == nullptr) {
			gsoapProxy2_0_1->Citation->LastUpdate = (tm *)soap_malloc(gsoapProxy2_0_1->soap, sizeof(tm));
		}
		*gsoapProxy2_0_1->Citation->LastUpdate = lastUpdate;
	}
	else if (gsoapProxy2_1 != nullptr) {
		if (gsoapProxy2_1->Citation->LastUpdate == nullptr) {
			gsoapProxy2_1->Citation->LastUpdate = (tm *)soap_malloc(gsoapProxy2_1->soap, sizeof(tm));
		}
		*gsoapProxy2_1->Citation->LastUpdate = lastUpdate;
	}
}

void AbstractObject::setFormat(const std::string & format)
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (format.empty()) {
		if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->Citation->Format = "[F2I-CONSULTING:fesapi]";
		else if (gsoapProxy2_1 != nullptr) gsoapProxy2_1->Citation->Format = "[F2I-CONSULTING:fesapi]";
	}
	else {
		if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->Citation->Format = format;
		else if (gsoapProxy2_1 != nullptr) gsoapProxy2_1->Citation->Format = format;
	}
}

void AbstractObject::setDescriptiveKeywords(const std::string & descriptiveKeywords)
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (!descriptiveKeywords.empty())
	{
		if (gsoapProxy2_0_1 != nullptr) {
			if (gsoapProxy2_0_1->Citation->DescriptiveKeywords == nullptr)
				gsoapProxy2_0_1->Citation->DescriptiveKeywords = soap_new_std__string(gsoapProxy2_0_1->soap, 1);
			gsoapProxy2_0_1->Citation->DescriptiveKeywords->assign(descriptiveKeywords);
		}
		else {
			if (gsoapProxy2_1->Citation->DescriptiveKeywords == nullptr)
				gsoapProxy2_1->Citation->DescriptiveKeywords = soap_new_std__string(gsoapProxy2_1->soap, 1);
			gsoapProxy2_1->Citation->DescriptiveKeywords->assign(descriptiveKeywords);
		}
	}
}

void AbstractObject::setVersionString(const std::string & versionString)
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (!versionString.empty())
	{
		if (gsoapProxy2_0_1 != nullptr) {
			if (gsoapProxy2_0_1->Citation->VersionString == nullptr)
				gsoapProxy2_0_1->Citation->VersionString = soap_new_std__string(gsoapProxy2_0_1->soap, 1);
			gsoapProxy2_0_1->Citation->VersionString->assign(versionString);
		}
		else {
			if (gsoapProxy2_1->Citation->VersionString == nullptr)
				gsoapProxy2_1->Citation->VersionString = soap_new_std__string(gsoapProxy2_1->soap, 1);
			gsoapProxy2_1->Citation->VersionString->assign(versionString);
		}
	}
}

void AbstractObject::initMandatoryMetadata()
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr) {
		gsoapProxy2_0_1->schemaVersion = getResqmlVersion();
		gsoapProxy2_0_1->Citation = soap_new_eml20__Citation(gsoapProxy2_0_1->soap, 1);
	}
	else {
		gsoapProxy2_1->schemaVersion = getResqmlVersion();
		gsoapProxy2_1->Citation = gsoap_eml2_1::soap_new_eml21__Citation(gsoapProxy2_1->soap, 1);
	}

	setMetadata("", "", "", -1, "", "", -1, "", "");
}

void AbstractObject::setMetadata(const std::string & guid, const std::string & title, const std::string & editor, const time_t & creation, const std::string & originator,
				const std::string & description, const time_t & lastUpdate, const std::string & format, const std::string & descriptiveKeywords)
{
	setUuid(guid);
	setMetadata(title, editor, creation, originator, description, lastUpdate, format, descriptiveKeywords);
}

void AbstractObject::setMetadata(const std::string & title, const std::string & editor, const time_t & creation, const std::string & originator,
	const std::string & description, const time_t & lastUpdate, const std::string & format, const std::string & descriptiveKeywords)
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	setTitle(title);

	setEditor(editor);

	setCreation(creation);

	setOriginator(originator);

	setDescription(description);

	setLastUpdate(lastUpdate);

	setFormat(format);

	setDescriptiveKeywords(descriptiveKeywords);
}

void AbstractObject::serializeIntoStream(ostream * stream)
{
	if (partialObject != nullptr) {
		throw invalid_argument("The wrapped gsoap proxy must not be null");
	}

	if (stream == nullptr) {
		throw invalid_argument("The stream where the entity will be stored cannot be null.");
	}

	string xmlTagIncludingNamespace = getXmlNamespace() + ":"+ getXmlTag();

	if (gsoapProxy2_0_1 != nullptr) {
		gsoapProxy2_0_1->soap->os = stream;
		(soap_begin_send(gsoapProxy2_0_1->soap) || soap_send(gsoapProxy2_0_1->soap, gsoapProxy2_0_1->soap->prolog ? gsoapProxy2_0_1->soap->prolog : "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n") ||
			(gsoapProxy2_0_1->soap_serialize(gsoapProxy2_0_1->soap), 0) ||
			gsoapProxy2_0_1->soap_put(gsoapProxy2_0_1->soap, xmlTagIncludingNamespace.c_str(), nullptr) ||
			soap_end_send(gsoapProxy2_0_1->soap));
	}
	else {
		gsoapProxy2_1->soap->os = stream;
		(soap_begin_send(gsoapProxy2_1->soap) || soap_send(gsoapProxy2_1->soap, gsoapProxy2_1->soap->prolog ? gsoapProxy2_1->soap->prolog : "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n") ||
			(gsoapProxy2_1->soap_serialize(gsoapProxy2_1->soap), 0) ||
			gsoapProxy2_1->soap_put(gsoapProxy2_1->soap, xmlTagIncludingNamespace.c_str(), nullptr) ||
			soap_end_send(gsoapProxy2_1->soap));
	}
}

gsoap_resqml2_0_1::eml20__AbstractCitedDataObject* AbstractObject::getGsoapProxy() const {
	return gsoapProxy2_0_1;
}

eml20__DataObjectReference* AbstractObject::newResqmlReference() const
{
	eml20__DataObjectReference* result = soap_new_eml20__DataObjectReference(getGsoapContext(), 1);
	result->UUID = getUuid();
	result->Title = getTitle();
	result->ContentType = getContentType();
	if (gsoapProxy2_0_1 != nullptr && !getVersionString().empty())
	{
		result->VersionString = soap_new_std__string(gsoapProxy2_0_1->soap, 1);
		result->VersionString->assign(getVersionString());
	}

	return result;
}

gsoap_eml2_1::eml21__DataObjectReference* AbstractObject::newEmlReference() const
{
	gsoap_eml2_1::eml21__DataObjectReference* result = gsoap_eml2_1::soap_new_eml21__DataObjectReference(getGsoapContext(), 1);
	result->Uuid = getUuid();
	result->Title = getTitle();
	result->ContentType = getContentType();
	if (gsoapProxy2_0_1 != nullptr && !getVersionString().empty()) // Not partial transfer
	{
		result->VersionString = gsoap_eml2_1::soap_new_std__string(gsoapProxy2_0_1->soap, 1);
		result->VersionString->assign(getVersionString());
	}

	return result;
}

gsoap_resqml2_0_1::resqml2__ContactElementReference* AbstractObject::newResqmlContactElementReference() const
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	resqml2__ContactElementReference* result = soap_new_resqml2__ContactElementReference(gsoapProxy2_0_1->soap, 1);
	result->UUID = getUuid();
	if (gsoapProxy2_0_1 != nullptr && !getVersionString().empty()) // Not partial transfer
	{
		result->VersionString = gsoap_eml2_1::soap_new_std__string(gsoapProxy2_0_1->soap, 1);
		result->VersionString->assign(getVersionString());
	}
	result->Title = gsoapProxy2_0_1->Citation->Title;
	result->ContentType = getContentType();

	return result;
}

std::string AbstractObject::getXmlNamespace() const
{
	return "resqml2";
}

std::string AbstractObject::getResqmlVersion() const
{
	return getXmlNamespace() == "eml21" ? "2.1" : "2.0";
}

string AbstractObject::getContentType() const
{
	std::string xmlNs = getXmlNamespace();
	if (xmlNs == "resqml2")
		return "application/x-resqml+xml;version=2.0;type=obj_" + getXmlTag();
	else if (xmlNs == "eml20" )
		return "application/x-resqml+xml;version=2.0;type=obj_" + getXmlTag(); // This is clearly a mistake, the line below is the right one. However, this is needed the time readers can read the right content type.
		//return "application/x-eml+xml;version=2.0;type=obj_" + getXmlTag();
	else if (xmlNs == "eml21")
		return "application/x-eml+xml;version=2.1;type=" + getXmlTag();
	else
		throw invalid_argument("unknown xml namespace");
}

std::string AbstractObject::getPartNameInEpcDocument() const
{
	std::string result = getXmlTag() + "_" + getUuid() + ".xml";
	return getXmlNamespace() == "eml21" ? result : "obj_" + result;
}

string AbstractObject::serializeIntoString()
{
	ostringstream oss;

	serializeIntoStream(&oss);

	return oss.str();
}

void AbstractObject::addAlias(const std::string & authority, const std::string & title)
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	eml20__ObjectAlias* alias = soap_new_eml20__ObjectAlias(gsoapProxy2_0_1->soap, 1);
	alias->authority = soap_new_std__string(gsoapProxy2_0_1->soap, 1);
	alias->authority->assign(authority);
	alias->Identifier = title;
	static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->Aliases.push_back(alias);
}

unsigned int AbstractObject::getAliasCount() const
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	return static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->Aliases.size();
}

std::string AbstractObject::getAliasAuthorityAtIndex(const unsigned int & index) const
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (getAliasCount() <= index)
		throw out_of_range("The index is out of range.");

	if ((static_cast<eml20__AbstractCitedDataObject*>(gsoapProxy2_0_1)->Aliases)[index]->authority)
		return *((static_cast<eml20__AbstractCitedDataObject*>(gsoapProxy2_0_1)->Aliases)[index]->authority);
	else
		return "";
}

std::string AbstractObject::getAliasTitleAtIndex(const unsigned int & index) const
{
	if (partialObject != nullptr)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (getAliasCount() <= index)
		throw out_of_range("The index is out of range.");

	return (static_cast<eml20__AbstractCitedDataObject*>(gsoapProxy2_0_1)->Aliases)[index]->Identifier;
}

const std::vector<RESQML2_NS::Activity*> & AbstractObject::getActivitySet() const
{
	return activitySet;
}

unsigned int AbstractObject::getActivityCount() const
{
	return activitySet.size();
}

RESQML2_NS::Activity* AbstractObject::getActivity (const unsigned int & index) const
{
	if (partialObject != nullptr)
			throw invalid_argument("The wrapped gsoap proxy must not be null");

		if (getActivityCount() <= index)
			throw out_of_range("The index is out of range.");

	return activitySet[index];
}

void AbstractObject::addActivityToResqmlObject(RESQML2_NS::Activity* activity, AbstractObject* resqmlObject)
{
	if (activity == nullptr)
	{
		throw invalid_argument("The activity cannot be null");
	}
	if (resqmlObject == nullptr)
	{
		throw invalid_argument("The resqml object to add cannot be null");
	}

	bool alreadyInserted = (std::find(resqmlObject->activitySet.begin(), resqmlObject->activitySet.end(), activity) != resqmlObject->activitySet.end()); // In case the resqml object is both input and output of the activity
	if (!alreadyInserted)
	{
		resqmlObject->activitySet.push_back(activity);
	}
}

void AbstractObject::pushBackExtraMetadataV2_0_1(const std::string & key, const std::string & value)
{
	resqml2__NameValuePair* stringPair = soap_new_resqml2__NameValuePair(gsoapProxy2_0_1->soap, 1);
	stringPair->Name = key;
	stringPair->Value = value;
	static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata.push_back(stringPair);
}

#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
std::unordered_map< std::string, std::string > AbstractObject::getExtraMetadataSetV2_0_1() const
{
	std::unordered_map< std::string, std::string > result;
#else
std::tr1::unordered_map< std::string, std::string > AbstractObject::getExtraMetadataSetV2_0_1() const
{
	std::tr1::unordered_map< std::string, std::string > result;
#endif
	for (size_t i = 0; i < static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata.size(); ++i) {
		result[static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata[i]->Name] = static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata[i]->Value;
	}

	return result;
}

vector<string> AbstractObject::getExtraMetadataV2_0_1(const std::string & key)  const
{
	vector<string> result;

	for (size_t i = 0; i < static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata.size(); ++i) {
		if (static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata[i]->Name.compare(key) == 0) {
			result.push_back(static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata[i]->Value);
		}
	}

	return result;
}

unsigned int AbstractObject::getExtraMetadataCountV2_0_1() const
{
	return static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata.size();
}

std::string AbstractObject::getExtraMetadataKeyAtIndexV2_0_1(const unsigned int & index) const
{
	if (getExtraMetadataCount() <= index) {
		throw out_of_range("The index is out of range.");
	}

	return (static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata)[index]->Name;
}

std::string AbstractObject::getExtraMetadataStringValueAtIndexV2_0_1(const unsigned int & index) const
{
	if (getExtraMetadataCount() <= index) {
		throw out_of_range("The index is out of range.");
	}

	return (static_cast<resqml2__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata)[index]->Value;
}

void AbstractObject::pushBackExtraMetadata(const std::string & key, const std::string & value)
{
	if (gsoapProxy2_0_1 != nullptr) {
		pushBackExtraMetadataV2_0_1(key, value);
	}
	else {
		throw logic_error("Not implemented yet.");
	}
}

/**
* Getter (in read only mode) of all the extra metadata
*/
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
std::unordered_map< std::string, std::string > AbstractObject::getExtraMetadataSet() const
#else
std::tr1::unordered_map< std::string, std::string > AbstractObject::getExtraMetadataSet() const
#endif
{
	if (gsoapProxy2_0_1 != nullptr) {
		return getExtraMetadataSetV2_0_1();
	}
	else {
		throw logic_error("Not implemented yet.");
	}
}

/**
* Get an extra metadata according its key.
* @return An empty string if the extra metadata does not exist. Or the extra metadata value if it exists
*/
vector<string> AbstractObject::getExtraMetadata(const std::string & key) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return getExtraMetadataV2_0_1(key);
	}
	else {
		throw logic_error("Not implemented yet.");
	}
}

/**
* Get the count of extra metadata in the instance.
*/
unsigned int AbstractObject::getExtraMetadataCount() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return getExtraMetadataCountV2_0_1();
	}
	else {
		throw logic_error("Not implemented yet.");
	}
}

/**
* Get the key of a string value pair at a particular index in the extra metadata set
*/
std::string AbstractObject::getExtraMetadataKeyAtIndex(const unsigned int & index) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return getExtraMetadataKeyAtIndexV2_0_1(index);
	}
	else {
		throw logic_error("Not implemented yet.");
	}
}

/**
* Get the string value of a string value pair at a particular index in the extra metadata set
*/
std::string AbstractObject::getExtraMetadataStringValueAtIndex(const unsigned int & index) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return getExtraMetadataStringValueAtIndexV2_0_1(index);
	}
	else {
		throw logic_error("Not implemented yet.");
	}
}

