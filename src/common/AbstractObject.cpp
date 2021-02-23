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

#include <limits>
#include <stdexcept>
#include <string>
#include <sstream>
#if (defined(_WIN32) || (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9))))
#include <regex>
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
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace COMMON_NS;

char AbstractObject::citationFormat[257] = "[F2I-CONSULTING:fesapi " FESAPI_VERSION "]";

void AbstractObject::cannotBePartial() const
{
	if (isPartial()) {
		throw logic_error("This method cannot be called on a partial object (" + getUuid() + ")");
	}
}

bool AbstractObject::isPartial() const {
	return partialObject != nullptr
		&& gsoapProxy2_0_1 == nullptr && gsoapProxy2_1 == nullptr
#if WITH_RESQML2_2
		&& gsoapProxy2_2 == nullptr
#endif
		;
}

void AbstractObject::changeToPartialObject()
{
	cannotBePartial();
	string uuid = getUuid();
	string title = getTitle();
	string contentType = getContentType();
	partialObject = gsoapProxy2_0_1 != nullptr ? gsoap_resqml2_0_1::soap_new_eml20__DataObjectReference(gsoapProxy2_0_1->soap, 1) : gsoap_resqml2_0_1::soap_new_eml20__DataObjectReference(gsoapProxy2_1->soap);
	partialObject->UUID = uuid;
	partialObject->Title = title;
	partialObject->ContentType = contentType;
}

soap* AbstractObject::getGsoapContext() const
{
	 if (gsoapProxy2_0_1 != nullptr) {
		return gsoapProxy2_0_1->soap;
	}
	else if (gsoapProxy2_1 != nullptr) {
		return gsoapProxy2_1->soap;
	}
	else if (gsoapProxy2_2 != nullptr) {
		return gsoapProxy2_2->soap;
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
	else if (gsoapProxy2_1 != nullptr) {
		return gsoapProxy2_1->soap_type();
	}
	else if (gsoapProxy2_2 != nullptr) {
		return gsoapProxy2_2->soap_type();
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
	else if (gsoapProxy2_1 != nullptr) {
		return gsoapProxy2_1->uuid;
	}
	else if (gsoapProxy2_2 != nullptr) {
		return gsoapProxy2_2->uuid;
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
	if (gsoapProxy2_0_1 != nullptr)
		return gsoapProxy2_0_1->Citation->Title;
	else if (gsoapProxy2_1 != nullptr)
		return gsoapProxy2_1->Citation->Title;
	else if (gsoapProxy2_2 != nullptr) {
		return gsoapProxy2_2->Citation->Title;
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
	if (isPartial())
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr && gsoapProxy2_0_1->Citation->Editor)
		return *gsoapProxy2_0_1->Citation->Editor;
	else if (gsoapProxy2_1 != nullptr && gsoapProxy2_1->Citation->Editor)
		return *gsoapProxy2_1->Citation->Editor;
	else if (gsoapProxy2_2 != nullptr && gsoapProxy2_2->Citation->Editor)
		return *gsoapProxy2_2->Citation->Editor;
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
	if (isPartial())
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr)
		return gsoapProxy2_0_1->Citation->Creation;
	else if (gsoapProxy2_1 != nullptr)
		return gsoapProxy2_1->Citation->Creation;
	else if (gsoapProxy2_2 != nullptr)
		return gsoapProxy2_2->Citation->Creation;
	else if (gsoapProxy2_3 != nullptr)
		return gsoapProxy2_3->Citation->Creation;

	throw invalid_argument("There is no available gsoap proxy instance.");
}

string AbstractObject::getOriginator() const
{
	if (isPartial())
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr)
		return gsoapProxy2_0_1->Citation->Originator;
	else if (gsoapProxy2_1 != nullptr)
		return gsoapProxy2_1->Citation->Originator;
	else if (gsoapProxy2_2 != nullptr)
		return gsoapProxy2_2->Citation->Originator;
	else if (gsoapProxy2_3 != nullptr)
		return gsoapProxy2_3->Citation->Originator;

	throw invalid_argument("There is no available gsoap proxy instance.");
}

string AbstractObject::getDescription() const
{
	if (isPartial())
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr && gsoapProxy2_0_1->Citation->Description)
		return *gsoapProxy2_0_1->Citation->Description;
	else if (gsoapProxy2_1 != nullptr && gsoapProxy2_1->Citation->Description)
		return *gsoapProxy2_1->Citation->Description;
	else if (gsoapProxy2_2 != nullptr && gsoapProxy2_2->Citation->Description)
		return *gsoapProxy2_2->Citation->Description;
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
	if (isPartial()) {
		throw invalid_argument("Cannot get the last update of a partial object.");
	}

	if (gsoapProxy2_0_1 != nullptr && gsoapProxy2_0_1->Citation->LastUpdate)
		return *gsoapProxy2_0_1->Citation->LastUpdate;
	else if (gsoapProxy2_1 != nullptr && gsoapProxy2_1->Citation->LastUpdate)
		return *gsoapProxy2_1->Citation->LastUpdate;
	else if (gsoapProxy2_2 != nullptr && gsoapProxy2_2->Citation->LastUpdate)
		return *gsoapProxy2_2->Citation->LastUpdate;
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
	if (isPartial())
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr)
		return gsoapProxy2_0_1->Citation->Format;
	else if (gsoapProxy2_1 != nullptr)
		return gsoapProxy2_1->Citation->Format;
	else if (gsoapProxy2_2 != nullptr)
		return gsoapProxy2_2->Citation->Format;
	else if (gsoapProxy2_3 != nullptr)
		return gsoapProxy2_3->Citation->Format;

	throw invalid_argument("There is no available gsoap proxy instance.");
}

string AbstractObject::getDescriptiveKeywords() const
{
	if (isPartial())
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr && gsoapProxy2_0_1->Citation->DescriptiveKeywords)
		return *gsoapProxy2_0_1->Citation->DescriptiveKeywords;
	else if (gsoapProxy2_1 != nullptr && gsoapProxy2_1->Citation->DescriptiveKeywords)
		return *gsoapProxy2_1->Citation->DescriptiveKeywords;
	else if (gsoapProxy2_2 != nullptr && gsoapProxy2_2->Citation->DescriptiveKeywords)
		return *gsoapProxy2_2->Citation->DescriptiveKeywords;
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
	else if (gsoapProxy2_1 != nullptr && gsoapProxy2_1->objectVersion != nullptr && !gsoapProxy2_1->objectVersion->empty()) {
		return *gsoapProxy2_1->objectVersion;
	}
	else if (gsoapProxy2_2 != nullptr && gsoapProxy2_2->objectVersion != nullptr && !gsoapProxy2_2->objectVersion->empty()) {
		return *gsoapProxy2_2->objectVersion;
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
	if (isPartial()) {
		throw invalid_argument("The wrapped gsoap proxy must not be null");
	}

	if (uuid.empty()) {
		boost::uuids::random_generator gen;
		const std::string uuidStr = boost::uuids::to_string(gen());

		if (gsoapProxy2_0_1 != nullptr) { gsoapProxy2_0_1->uuid = uuidStr; }
		else if (gsoapProxy2_1 != nullptr) { gsoapProxy2_1->uuid = uuidStr; }
		else if (gsoapProxy2_2 != nullptr) { gsoapProxy2_2->uuid = uuidStr; }
		else if (gsoapProxy2_3 != nullptr) { gsoapProxy2_3->uuid = uuidStr; }
	}
	else
	{
#if (defined(_WIN32) || (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9))))
		if (!regex_match(uuid, regex("[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}"))) {
			throw invalid_argument("The uuid does not match the official uuid regular expression : " + uuid);
	}
#endif
		if (gsoapProxy2_0_1 != nullptr) { gsoapProxy2_0_1->uuid = uuid; }
		else if (gsoapProxy2_1 != nullptr) { gsoapProxy2_1->uuid = uuid; }
		else if (gsoapProxy2_2 != nullptr) { gsoapProxy2_2->uuid = uuid; }
		else if (gsoapProxy2_3 != nullptr) { gsoapProxy2_3->uuid = uuid; }
	}
}

void AbstractObject::setTitle(const std::string & title)
{
	if (isPartial()) {
		throw invalid_argument("The wrapped gsoap proxy must not be null");
	}
	if (title.size() > 256) {
		throw range_error("The title cannot be more than 256 chars long.");
	}

	if (title.empty()) {
		if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->Citation->Title = "unknown";
		else if (gsoapProxy2_1 != nullptr) gsoapProxy2_1->Citation->Title = "unknown";
		else if (gsoapProxy2_2 != nullptr) gsoapProxy2_2->Citation->Title = "unknown";
		else if (gsoapProxy2_3 != nullptr) gsoapProxy2_3->Citation->Title = "unknown";
	}
	else {
		if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->Citation->Title = title;
		else if (gsoapProxy2_1 != nullptr) gsoapProxy2_1->Citation->Title = title;
		else if (gsoapProxy2_2 != nullptr) gsoapProxy2_2->Citation->Title = title;
		else if (gsoapProxy2_3 != nullptr) gsoapProxy2_3->Citation->Title = title;
	}
}

void AbstractObject::setEditor(const std::string & editor)
{
	if (isPartial()) {
		throw invalid_argument("The wrapped gsoap proxy must not be null");
	}
	if (editor.size() > 64) {
		throw range_error("The editor cannot be more than 64 chars long.");
	}

	if (!editor.empty()) {
		if (gsoapProxy2_0_1 != nullptr) {
			if (gsoapProxy2_0_1->Citation->Editor == nullptr)
				gsoapProxy2_0_1->Citation->Editor = gsoap_resqml2_0_1::soap_new_std__string(gsoapProxy2_0_1->soap);
			gsoapProxy2_0_1->Citation->Editor->assign(editor);
		}
		else if (gsoapProxy2_1 != nullptr) {
			if (gsoapProxy2_1->Citation->Editor == nullptr)
				gsoapProxy2_1->Citation->Editor = gsoap_eml2_1::soap_new_std__string(gsoapProxy2_1->soap);
			gsoapProxy2_1->Citation->Editor->assign(editor);
		}
		else if (gsoapProxy2_2 != nullptr) {
			if (gsoapProxy2_2->Citation->Editor == nullptr)
				gsoapProxy2_2->Citation->Editor = gsoap_eml2_2::soap_new_std__string(gsoapProxy2_2->soap);
			gsoapProxy2_2->Citation->Editor->assign(editor);
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
		std::tm tmConversion = timeTools::to_calendar_time(std::chrono::system_clock::from_time_t(creation));
		setCreation(tmConversion);
	}
	else {
		time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		setCreation(now);
	}
}

void AbstractObject::setCreation(const tm & creation)
{
	if (isPartial())
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr) {
		gsoapProxy2_0_1->Citation->Creation = creation;
	}
	else if (gsoapProxy2_1 != nullptr) {
		gsoapProxy2_1->Citation->Creation = creation;
	}
	else if (gsoapProxy2_2 != nullptr) {
		gsoapProxy2_2->Citation->Creation = creation;
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoapProxy2_3->Citation->Creation = creation;
	}
}

void AbstractObject::setOriginator(const std::string & originator)
{
	if (isPartial()){
		throw invalid_argument("The wrapped gsoap proxy must not be null");
	}
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
		else if (gsoapProxy2_1 != nullptr) gsoapProxy2_1->Citation->Originator = pw != nullptr ? pw->pw_name : "unknown";
		else if (gsoapProxy2_2 != nullptr) gsoapProxy2_2->Citation->Originator = pw != nullptr ? pw->pw_name : "unknown";
		else if (gsoapProxy2_3 != nullptr) gsoapProxy2_3->Citation->Originator = pw != nullptr ? pw->pw_name : "unknown";
#elif defined(_WIN32)
		char acUserName[32];
		DWORD nUserName = sizeof(acUserName);
		GetUserName(acUserName, &nUserName);
		if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->Citation->Originator = acUserName;
		else if (gsoapProxy2_1 != nullptr) gsoapProxy2_1->Citation->Originator = acUserName;
		else if (gsoapProxy2_2 != nullptr) gsoapProxy2_2->Citation->Originator = acUserName;
		else if (gsoapProxy2_3 != nullptr) gsoapProxy2_3->Citation->Originator = acUserName;
#endif	
	}
	else {
		if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->Citation->Originator = originator;
		else if (gsoapProxy2_1 != nullptr) gsoapProxy2_1->Citation->Originator = originator;
		else if (gsoapProxy2_2 != nullptr) gsoapProxy2_2->Citation->Originator = originator;
		else if (gsoapProxy2_3 != nullptr) gsoapProxy2_3->Citation->Originator = originator;
	}
}

void AbstractObject::setDescription(const std::string & description)
{
	if (isPartial()) {
		throw invalid_argument("The wrapped gsoap proxy must not be null");
	}

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
		else if (gsoapProxy2_1 != nullptr) {
			if (description.size() > 2000) {
				throw range_error("The description cannot be more than 2000 chars long.");
			}
			if (gsoapProxy2_1->Citation->Description == nullptr)
				gsoapProxy2_1->Citation->Description = gsoap_eml2_1::soap_new_std__string(gsoapProxy2_1->soap);
			gsoapProxy2_1->Citation->Description->assign(description);
		}
		else if (gsoapProxy2_2 != nullptr) {
			if (description.size() > 2000) {
				throw range_error("The description cannot be more than 2000 chars long.");
			}
			if (gsoapProxy2_2->Citation->Description == nullptr)
				gsoapProxy2_2->Citation->Description = gsoap_eml2_2::soap_new_std__string(gsoapProxy2_2->soap);
			gsoapProxy2_2->Citation->Description->assign(description);
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
	if (isPartial()) {
		throw invalid_argument("The wrapped gsoap proxy must not be null");
	}

	if (lastUpdate > 0) {
		
		if (lastUpdate < getCreation()) {
			throw invalid_argument("Last update cannot be inferior to creation date.");
		}

		std::tm tmConversion = timeTools::to_calendar_time(std::chrono::system_clock::from_time_t(lastUpdate));
		setLastUpdate(tmConversion);
	}
}

void AbstractObject::setLastUpdate(const tm & lastUpdate)
{
	if (isPartial())
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr) {
		if (gsoapProxy2_0_1->Citation->LastUpdate == nullptr) {
			gsoapProxy2_0_1->Citation->LastUpdate = (tm*)soap_malloc(gsoapProxy2_0_1->soap, sizeof(tm));
		}
		*gsoapProxy2_0_1->Citation->LastUpdate = lastUpdate;
	}
	else if (gsoapProxy2_1 != nullptr) {
		if (gsoapProxy2_1->Citation->LastUpdate == nullptr) {
			gsoapProxy2_1->Citation->LastUpdate = (tm*)soap_malloc(gsoapProxy2_1->soap, sizeof(tm));
		}
		*gsoapProxy2_1->Citation->LastUpdate = lastUpdate;
	}
	else if (gsoapProxy2_2 != nullptr) {
		if (gsoapProxy2_2->Citation->LastUpdate == nullptr) {
			gsoapProxy2_2->Citation->LastUpdate = (tm*)soap_malloc(gsoapProxy2_2->soap, sizeof(tm));
		}
		*gsoapProxy2_2->Citation->LastUpdate = lastUpdate;
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
	string format = "[";
	format += vendor;
	format += ':';
	format += applicationName;
	format += ' ';
	format += applicationVersionNumber;
	format += ']';
	if (vendor.size() + applicationName.size() + applicationVersionNumber.size() > 256) {
		throw range_error("The format cannot be more than 256 chars long");
	}

	format.copy(citationFormat, format.size());
	citationFormat[format.size()] = '\0';
}

void AbstractObject::setDescriptiveKeywords(const std::string & descriptiveKeywords)
{
	if (isPartial()) {
		throw invalid_argument("The wrapped gsoap proxy must not be null");
	}

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
		else if(gsoapProxy2_1 != nullptr) {
			if (descriptiveKeywords.size() > 2000) {
				throw range_error("The descriptiveKeywords cannot be more than 2000 chars long.");
			}
			if (gsoapProxy2_1->Citation->DescriptiveKeywords == nullptr)
				gsoapProxy2_1->Citation->DescriptiveKeywords = gsoap_eml2_1::soap_new_std__string(gsoapProxy2_1->soap);
			gsoapProxy2_1->Citation->DescriptiveKeywords->assign(descriptiveKeywords);
		}
		else if (gsoapProxy2_2 != nullptr) {
			if (descriptiveKeywords.size() > 2000) {
				throw range_error("The descriptiveKeywords cannot be more than 2000 chars long.");
			}
			if (gsoapProxy2_2->Citation->DescriptiveKeywords == nullptr)
				gsoapProxy2_2->Citation->DescriptiveKeywords = gsoap_eml2_2::soap_new_std__string(gsoapProxy2_2->soap);
			gsoapProxy2_2->Citation->DescriptiveKeywords->assign(descriptiveKeywords);
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
	else if (gsoapProxy2_1 != nullptr) {
		if (gsoapProxy2_1->objectVersion == nullptr)
			gsoapProxy2_1->objectVersion = gsoap_eml2_1::soap_new_std__string(gsoapProxy2_1->soap);
		gsoapProxy2_1->objectVersion->assign(version);
	}
	else if (gsoapProxy2_2 != nullptr) {
		if (gsoapProxy2_2->objectVersion == nullptr)
			gsoapProxy2_2->objectVersion = gsoap_eml2_2::soap_new_std__string(gsoapProxy2_2->soap);
		gsoapProxy2_2->objectVersion->assign(version);
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
	if (isPartial())
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (gsoapProxy2_0_1 != nullptr) {
		gsoapProxy2_0_1->schemaVersion = getXmlNamespaceVersion();
		gsoapProxy2_0_1->Citation = gsoap_resqml2_0_1::soap_new_eml20__Citation(gsoapProxy2_0_1->soap);
	}
	else if (gsoapProxy2_1 != nullptr) {
		// currently, WITSML and RESQML are by chance in v2.0 as well
		gsoapProxy2_1->schemaVersion = getXmlNamespaceVersion();
		gsoapProxy2_1->Citation = gsoap_eml2_1::soap_new_eml21__Citation(gsoapProxy2_1->soap);
	}
	else if (gsoapProxy2_2 != nullptr) {
		gsoapProxy2_2->schemaVersion = getXmlNamespaceVersion();
		gsoapProxy2_2->Citation = gsoap_eml2_2::soap_new_eml22__Citation(gsoapProxy2_2->soap);
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
	if (isPartial())
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	setTitle(title);

	setEditor(editor);

	setCreation(creation);

	setOriginator(originator);

	setDescription(description);

	setLastUpdate(lastUpdate);

	setDescriptiveKeywords(descriptiveKeywords);

	if (gsoapProxy2_0_1 != nullptr) gsoapProxy2_0_1->Citation->Format = citationFormat;
	else if (gsoapProxy2_1 != nullptr) gsoapProxy2_1->Citation->Format = citationFormat;
	else if (gsoapProxy2_2 != nullptr) gsoapProxy2_2->Citation->Format = citationFormat;
	else if (gsoapProxy2_3 != nullptr) gsoapProxy2_3->Citation->Format = citationFormat;
}

void AbstractObject::serializeIntoStream(ostream * stream)
{
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
	else if (gsoapProxy2_1 != nullptr) {
		gsoapProxy2_1->soap->os = stream;
		(soap_begin_send(gsoapProxy2_1->soap) || soap_send(gsoapProxy2_1->soap, gsoapProxy2_1->soap->prolog ? gsoapProxy2_1->soap->prolog : "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n") ||
			(gsoapProxy2_1->soap_serialize(gsoapProxy2_1->soap), 0) ||
			gsoapProxy2_1->soap_put(gsoapProxy2_1->soap, xmlTagIncludingNamespace.c_str(), nullptr) ||
			soap_end_send(gsoapProxy2_1->soap));
	}
	else if (gsoapProxy2_2 != nullptr) {
		gsoapProxy2_2->soap->os = stream;
		(soap_begin_send(gsoapProxy2_2->soap) || soap_send(gsoapProxy2_2->soap, gsoapProxy2_2->soap->prolog ? gsoapProxy2_2->soap->prolog : "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n") ||
			(gsoapProxy2_2->soap_serialize(gsoapProxy2_2->soap), 0) ||
			gsoapProxy2_2->soap_put(gsoapProxy2_2->soap, xmlTagIncludingNamespace.c_str(), nullptr) ||
			soap_end_send(gsoapProxy2_2->soap));
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
	if (gsoapProxy2_0_1 != nullptr && !getVersion().empty()) {
		result->VersionString = gsoap_resqml2_0_1::soap_new_std__string(gsoapProxy2_0_1->soap);
		result->VersionString->assign(getVersion());
	}

	return result;
}

gsoap_eml2_1::eml21__DataObjectReference* AbstractObject::newEmlReference() const
{
	gsoap_eml2_1::eml21__DataObjectReference* result = gsoap_eml2_1::soap_new_eml21__DataObjectReference(getGsoapContext());
	result->Uuid = getUuid();
	result->Title = getTitle();
	result->ContentType = getContentType();
	if (gsoapProxy2_0_1 != nullptr && !getVersion().empty()) // Not partial transfer
	{
		result->VersionString = gsoap_eml2_1::soap_new_std__string(gsoapProxy2_0_1->soap);
		result->VersionString->assign(getVersion());
	}

	return result;
}

gsoap_eml2_2::eml22__DataObjectReference* AbstractObject::newEml22Reference() const
{
	ostringstream oss;

	gsoap_eml2_2::eml22__DataObjectReference* result = gsoap_eml2_2::soap_new_eml22__DataObjectReference(getGsoapContext());
	result->Uuid = getUuid();
	result->Title = getTitle();
	result->ContentType = getContentType();
	if (gsoapProxy2_2 != nullptr && !getVersion().empty()) // Not partial transfer
	{
		result->ObjectVersion = gsoap_eml2_2::soap_new_std__string(gsoapProxy2_2->soap);
		result->ObjectVersion->assign(getVersion());
	}

	return result;
}

gsoap_eml2_3::eml23__DataObjectReference* AbstractObject::newEml23Reference() const
{
	ostringstream oss;

	gsoap_eml2_3::eml23__DataObjectReference* result = gsoap_eml2_3::soap_new_eml23__DataObjectReference(getGsoapContext());
	result->Uuid = getUuid();
	result->Title = getTitle();
	result->ContentType = getContentType();
	if (gsoapProxy2_3 != nullptr && !getVersion().empty()) // Not partial transfer
	{
		result->ObjectVersion = gsoap_eml2_3::soap_new_std__string(gsoapProxy2_3->soap);
		result->ObjectVersion->assign(getVersion());
	}

	return result;
}

gsoap_resqml2_0_1::resqml20__ContactElementReference* AbstractObject::newContactElementReference2_0_1() const
{
	if (isPartial()) {
		throw invalid_argument("The wrapped gsoap proxy must not be null");
	}

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
	result->ContentType = getContentType();

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
	if (isPartial()) {
		throw invalid_argument("The wrapped gsoap proxy must not be null");
	}
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
	else if (gsoapProxy2_1 != nullptr) {
		gsoap_eml2_1::eml21__ObjectAlias* alias = gsoap_eml2_1::soap_new_eml21__ObjectAlias(gsoapProxy2_1->soap);
		alias->authority = authority;
		alias->Identifier = title;
		gsoapProxy2_1->Aliases.push_back(alias);
	}
	else if (gsoapProxy2_2 != nullptr) {
		gsoap_eml2_2::eml22__ObjectAlias* alias = gsoap_eml2_2::soap_new_eml22__ObjectAlias(gsoapProxy2_2->soap);
		alias->authority = authority;
		alias->Identifier = title;
		gsoapProxy2_2->Aliases.push_back(alias);
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::eml23__ObjectAlias* alias = gsoap_eml2_3::soap_new_eml23__ObjectAlias(gsoapProxy2_3->soap);
		alias->authority = authority;
		alias->Identifier = title;
		gsoapProxy2_3->Aliases.push_back(alias);
	}
}

unsigned int AbstractObject::getAliasCount() const
{
	if (isPartial())
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	size_t count = 0;
	
	if (gsoapProxy2_0_1 != nullptr) {
		count = gsoapProxy2_0_1->Aliases.size();
	}
	else if (gsoapProxy2_1 != nullptr) {
		count = gsoapProxy2_1->Aliases.size();
	}
	else if (gsoapProxy2_2 != nullptr) {
		count = gsoapProxy2_2->Aliases.size();
	}
	else if (gsoapProxy2_3 != nullptr) {
		count = gsoapProxy2_3->Aliases.size();
	}

	if (count > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("There is too much aliases for fesapi.");
	}

	return static_cast<unsigned int>(count);
}

std::string AbstractObject::getAliasAuthorityAtIndex(unsigned int index) const
{
	if (isPartial())
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (getAliasCount() <= index) {
		throw out_of_range("The index is out of range.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return (gsoapProxy2_0_1->Aliases)[index]->authority? *((gsoapProxy2_0_1->Aliases)[index]->authority): std::string();
	}
	else if (gsoapProxy2_1 != nullptr) {
		return gsoapProxy2_1->Aliases[index]->authority;
	}
	else if (gsoapProxy2_2 != nullptr) {
		return gsoapProxy2_2->Aliases[index]->authority;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return gsoapProxy2_3->Aliases[index]->authority;
	}

	throw invalid_argument("No underlying gsoap proxy.");
}

std::string AbstractObject::getAliasTitleAtIndex(unsigned int index) const
{
	if (isPartial())
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (getAliasCount() <= index)
		throw out_of_range("The index is out of range.");

	if (gsoapProxy2_0_1 != nullptr) {
		return (gsoapProxy2_0_1->Aliases)[index]->Identifier;
	}
	else if (gsoapProxy2_1 != nullptr) {
		return gsoapProxy2_1->Aliases[index]->Identifier;
	}
	else if (gsoapProxy2_2 != nullptr) {
		return gsoapProxy2_2->Aliases[index]->Identifier;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return gsoapProxy2_3->Aliases[index]->Identifier;
	}

	throw invalid_argument("No underlying gsoap proxy.");
}

std::vector<EML2_NS::Activity *> AbstractObject::getActivitySet() const
{
	return getRepository()->getSourceObjects<EML2_NS::Activity>(this);
}

unsigned int AbstractObject::getActivityCount() const
{
	const size_t result = getActivitySet().size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw out_of_range("There are too many associated activities.");
	}

	return static_cast<unsigned int>(result);
}

EML2_NS::Activity * AbstractObject::getActivity(unsigned int index) const
{
	if (isPartial()) {
		throw invalid_argument("The wrapped gsoap proxy must not be null");
	}

	const std::vector<EML2_NS::Activity *>& activites = getActivitySet();
	if (index >= activites.size())
		throw out_of_range("The index is out of range.");

	return activites[index];
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
	else if (gsoapProxy2_1 != nullptr)
	{
		if (value.size() > 64) {
			throw invalid_argument("An extra metadata value cannot be greater than 64 chars.");
		}

		gsoap_eml2_1::eml21__ExtensionNameValue* stringPair = gsoap_eml2_1::soap_new_eml21__ExtensionNameValue(gsoapProxy2_1->soap);
		stringPair->Name = key;
		stringPair->Value = gsoap_eml2_1::soap_new_eml21__StringMeasure(gsoapProxy2_1->soap);
		stringPair->Value->__item = value;
		gsoapProxy2_1->ExtensionNameValue.push_back(stringPair);
	}
	else if (gsoapProxy2_2 != nullptr)
	{
		if (value.size() > 64) {
			throw invalid_argument("An extra metadata value cannot be greater than 64 chars.");
		}

		gsoap_eml2_2::eml22__ExtensionNameValue* stringPair = gsoap_eml2_2::soap_new_eml22__ExtensionNameValue(gsoapProxy2_2->soap);
		stringPair->Name = key;
		stringPair->Value = gsoap_eml2_2::soap_new_eml22__StringMeasure(gsoapProxy2_2->soap);
		stringPair->Value->__item = value;
		gsoapProxy2_2->ExtensionNameValue.push_back(stringPair);
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
	else if (gsoapProxy2_1 != nullptr) {
		result = static_cast<gsoap_eml2_1::eml21__AbstractObject*>(gsoapProxy2_1)->ExtensionNameValue.size();
	}
	else if (gsoapProxy2_2 != nullptr) {
		result = static_cast<gsoap_eml2_2::eml22__AbstractObject*>(gsoapProxy2_2)->ExtensionNameValue.size();
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
	else if (gsoapProxy2_1 != nullptr) {
		return (static_cast<gsoap_eml2_1::eml21__AbstractObject*>(gsoapProxy2_1)->ExtensionNameValue)[index]->Name;
	}
	else if (gsoapProxy2_2 != nullptr) {
		return (static_cast<gsoap_eml2_2::eml22__AbstractObject*>(gsoapProxy2_2)->ExtensionNameValue)[index]->Name;
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
	else if (gsoapProxy2_1 != nullptr) {
		return (static_cast<gsoap_eml2_1::eml21__AbstractObject*>(gsoapProxy2_1)->ExtensionNameValue)[index]->Value->__item;
	}
	else if (gsoapProxy2_2 != nullptr) {
		return (static_cast<gsoap_eml2_2::eml22__AbstractObject*>(gsoapProxy2_2)->ExtensionNameValue)[index]->Value->__item;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return (static_cast<gsoap_eml2_3::eml23__AbstractObject*>(gsoapProxy2_3)->ExtensionNameValue)[index]->Value->__item;
	}

	throw logic_error("Not implemented yet.");
}

std::string AbstractObject::buildUri() const
{
	return "eml:///" + getQualifiedType() + "(" + getUuid() + ")";
}

void AbstractObject::readArrayNdOfDoubleValues(gsoap_resqml2_0_1::resqml20__AbstractDoubleArray * arrayInput, double * arrayOutput) const
{
	long soapType = arrayInput->soap_type();
	if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array)
	{
		EML2_NS::AbstractHdfProxy* hdfProxy = repository->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(arrayInput)->Values->HdfProxy->UUID);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The hdf proxy " + static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(arrayInput)->Values->HdfProxy->UUID + " is not available.");
		}
		hdfProxy->readArrayNdOfDoubleValues(static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(arrayInput)->Values->PathInHdfFile, arrayOutput);
	}
	else if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray)
	{
		gsoap_resqml2_0_1::resqml20__DoubleConstantArray* constantArray = static_cast<gsoap_resqml2_0_1::resqml20__DoubleConstantArray*>(arrayInput);
		for (size_t i = 0; i < constantArray->Count; ++i) {
			arrayOutput[i] = constantArray->Value;
		}
	}
	else if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
	{
		gsoap_resqml2_0_1::resqml20__DoubleLatticeArray* latticeArray = static_cast<gsoap_resqml2_0_1::resqml20__DoubleLatticeArray*>(arrayInput);
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

void AbstractObject::readArrayNdOfDoubleValues(gsoap_eml2_3::eml23__AbstractFloatingPointArray * arrayInput, double * arrayOutput) const
{
	switch (arrayInput->soap_type()) {
	case SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointExternalArray:
	case SOAP_TYPE_gsoap_eml2_3_eml23__DoubleExternalArray:
	case SOAP_TYPE_gsoap_eml2_3_eml23__FloatExternalArray:
	{
		for (auto dsPart : static_cast<gsoap_eml2_3::eml23__FloatingPointExternalArray*>(arrayInput)->Values->ExternalFileProxy) {
			EML2_NS::AbstractHdfProxy* hdfProxy = getHdfProxyFromDataset(dsPart);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The hdf proxy " + dsPart->EpcExternalPartReference->Uuid + " is not available.");
			}
			hdfProxy->readArrayNdOfDoubleValues(dsPart->PathInExternalFile, arrayOutput + dsPart->StartIndex);
		}
		break;
	}
	case SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray:
	{
		gsoap_eml2_3::eml23__FloatingPointConstantArray* constantArray = static_cast<gsoap_eml2_3::eml23__FloatingPointConstantArray*>(arrayInput);
		std::fill(arrayOutput, arrayOutput + constantArray->Count, constantArray->Value);
		break;
	}
	case SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray:
	{
		gsoap_eml2_3::eml23__FloatingPointLatticeArray* latticeArray = static_cast<gsoap_eml2_3::eml23__FloatingPointLatticeArray*>(arrayInput);
		if (latticeArray->Offset.size() > 1) {
			throw invalid_argument("The integer lattice array contains more than one offset.");
		}
		for (size_t i = 0; i <= latticeArray->Offset[0]->Count; ++i) {
			arrayOutput[i] = latticeArray->StartValue + (i * latticeArray->Offset[0]->Value);
		}
		break;
	}
	default: throw invalid_argument("The integer array type is not supported yet.");
	}
}

uint8_t AbstractObject::readArrayNdOfUInt8Values(gsoap_resqml2_0_1::resqml20__AbstractIntegerArray const * arrayInput, uint8_t * arrayOutput) const
{
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array const*>(arrayInput);
		EML2_NS::AbstractHdfProxy* hdfProxy = repository->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(hdfArray->Values->HdfProxy->UUID);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The hdf proxy " + hdfArray->Values->HdfProxy->UUID + " is not available.");
		}
		hdfProxy->readArrayNdOfUCharValues(hdfArray->Values->PathInHdfFile, arrayOutput);
		if (hdfArray->NullValue > (std::numeric_limits<uint8_t>::max)()) {
			throw range_error("The null value is greater than uint8_t max.");
		}
		return static_cast<uint8_t>(hdfArray->NullValue);
	}
	else {
		readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}

	return (std::numeric_limits<uint8_t>::max)();
}

uint8_t AbstractObject::readArrayNdOfUInt8Values(gsoap_eml2_3::eml23__AbstractIntegerArray const * arrayInput, uint8_t * arrayOutput) const
{
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		for (auto dsPart : static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->Values->ExternalFileProxy) {
			EML2_NS::AbstractHdfProxy* hdfProxy = getHdfProxyFromDataset(dsPart);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The hdf proxy " + dsPart->EpcExternalPartReference->Uuid + " is not available.");
			}
			hdfProxy->readArrayNdOfUCharValues(dsPart->PathInExternalFile, arrayOutput + dsPart->StartIndex);
		}
		if (static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue > (std::numeric_limits<uint8_t>::max)()) {
			throw range_error("The null value is greater than uint8_t max.");
		}
		return static_cast<uint8_t>(static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue);
	}
	else {
		readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}

	return (std::numeric_limits<uint8_t>::max)();
}

uint16_t AbstractObject::readArrayNdOfUInt16Values(gsoap_resqml2_0_1::resqml20__AbstractIntegerArray const * arrayInput, uint16_t * arrayOutput) const
{
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array const*>(arrayInput);
		EML2_NS::AbstractHdfProxy* hdfProxy = repository->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(hdfArray->Values->HdfProxy->UUID);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The hdf proxy " + hdfArray->Values->HdfProxy->UUID + " is not available.");
		}
		hdfProxy->readArrayNdOfUShortValues(hdfArray->Values->PathInHdfFile, arrayOutput);
		if (hdfArray->NullValue > (std::numeric_limits<uint16_t>::max)()) {
			throw range_error("The null value is greater than uint16_t max.");
		}
		return static_cast<uint16_t>(hdfArray->NullValue);
	}
	else {
		readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}

	return (std::numeric_limits<uint16_t>::max)();
}

uint16_t AbstractObject::readArrayNdOfUInt16Values(gsoap_eml2_3::eml23__AbstractIntegerArray const * arrayInput, uint16_t * arrayOutput) const
{
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		for (auto dsPart : static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->Values->ExternalFileProxy) {
			EML2_NS::AbstractHdfProxy* hdfProxy = getHdfProxyFromDataset(dsPart);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The hdf proxy " + dsPart->EpcExternalPartReference->Uuid + " is not available.");
			}
			hdfProxy->readArrayNdOfUShortValues(dsPart->PathInExternalFile, arrayOutput + dsPart->StartIndex);
		}
		if (static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue > (std::numeric_limits<uint16_t>::max)()) {
			throw range_error("The null value is greater than uint16_t max.");
		}
		return static_cast<uint16_t>(static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue);
	}
	else {
		readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}

	return (std::numeric_limits<uint16_t>::max)();
}

uint32_t AbstractObject::readArrayNdOfUInt32Values(gsoap_resqml2_0_1::resqml20__AbstractIntegerArray const * arrayInput, uint32_t * arrayOutput) const
{
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array const*>(arrayInput);
		EML2_NS::AbstractHdfProxy* hdfProxy = repository->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(hdfArray->Values->HdfProxy->UUID);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The hdf proxy " + hdfArray->Values->HdfProxy->UUID + " is not available.");
		}
		hdfProxy->readArrayNdOfUIntValues(hdfArray->Values->PathInHdfFile, arrayOutput);
		if (hdfArray->NullValue > (std::numeric_limits<uint32_t>::max)()) {
			throw range_error("The null value is greater than uint32_t max.");
		}
		return static_cast<uint32_t>(hdfArray->NullValue);
	}
	else {
		readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}

	return (std::numeric_limits<uint32_t>::max)();
}

uint32_t AbstractObject::readArrayNdOfUInt32Values(gsoap_eml2_3::eml23__AbstractIntegerArray const * arrayInput, uint32_t * arrayOutput) const
{
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		for (auto dsPart : static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->Values->ExternalFileProxy) {
			EML2_NS::AbstractHdfProxy* hdfProxy = getHdfProxyFromDataset(dsPart);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The hdf proxy " + dsPart->EpcExternalPartReference->Uuid + " is not available.");
			}
			hdfProxy->readArrayNdOfUIntValues(dsPart->PathInExternalFile, arrayOutput + dsPart->StartIndex);
		}
		if (static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue > (std::numeric_limits<uint32_t>::max)()) {
			throw range_error("The null value is greater than uint32_t max.");
		}
		return static_cast<uint32_t>(static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue);
	}
	else {
		readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}

	return (std::numeric_limits<uint32_t>::max)();
}

uint64_t AbstractObject::readArrayNdOfUInt64Values(gsoap_resqml2_0_1::resqml20__AbstractIntegerArray const * arrayInput, uint64_t * arrayOutput) const
{
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		auto const * hdfArray = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array const*>(arrayInput);
		EML2_NS::AbstractHdfProxy* hdfProxy = repository->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(hdfArray->Values->HdfProxy->UUID);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The hdf proxy " + hdfArray->Values->HdfProxy->UUID + " is not available.");
		}
		hdfProxy->readArrayNdOfUInt64Values(hdfArray->Values->PathInHdfFile, arrayOutput);
		if (hdfArray->NullValue > (std::numeric_limits<uint64_t>::max)()) {
			throw range_error("The null value is greater than uint64_t max.");
		}
		return static_cast<uint64_t>(hdfArray->NullValue);
	}
	else {
		readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}

	return (std::numeric_limits<uint64_t>::max)();
}

uint64_t AbstractObject::readArrayNdOfUInt64Values(gsoap_eml2_3::eml23__AbstractIntegerArray const * arrayInput, uint64_t * arrayOutput) const
{
	if (arrayInput->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		for (auto dsPart : static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->Values->ExternalFileProxy) {
			EML2_NS::AbstractHdfProxy* hdfProxy = getHdfProxyFromDataset(dsPart);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The hdf proxy " + dsPart->EpcExternalPartReference->Uuid + " is not available.");
			}
			hdfProxy->readArrayNdOfUInt64Values(dsPart->PathInExternalFile, arrayOutput + dsPart->StartIndex);
		}
		if (static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue > (std::numeric_limits<uint64_t>::max)()) {
			throw range_error("The null value is greater than uint64_t max.");
		}
		return static_cast<uint64_t>(static_cast<gsoap_eml2_3::eml23__IntegerExternalArray const*>(arrayInput)->NullValue);
	}
	else {
		readArrayNdOfNonHdf5IntegerValues(arrayInput, arrayOutput);
	}

	return (std::numeric_limits<uint64_t>::max)();
}

uint64_t AbstractObject::getCountOfIntegerArray(gsoap_resqml2_0_1::resqml20__AbstractIntegerArray * arrayInput) const
{
	long soapType = arrayInput->soap_type();
	if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
	{
		EML2_NS::AbstractHdfProxy* hdfProxy = repository->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(arrayInput)->Values->HdfProxy->UUID);
		if (hdfProxy == nullptr) {
			throw invalid_argument("The hdf proxy " + static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(arrayInput)->Values->HdfProxy->UUID + " is not available.");
		}
		return hdfProxy->getElementCount(static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(arrayInput)->Values->PathInHdfFile);
	}
	else if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerRangeArray)
	{
		return static_cast<gsoap_resqml2_0_1::resqml20__IntegerRangeArray*>(arrayInput)->Count;
	}
	else if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
	{
		return static_cast<gsoap_resqml2_0_1::resqml20__IntegerConstantArray*>(arrayInput)->Count;
	}
	else if (soapType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray)
	{
		gsoap_resqml2_0_1::resqml20__IntegerLatticeArray* latticeArray = static_cast<gsoap_resqml2_0_1::resqml20__IntegerLatticeArray*>(arrayInput);
		if (latticeArray->Offset.size() > 1) {
			throw invalid_argument("The integer lattice array contains more than one offset.");
		}
		return static_cast<gsoap_resqml2_0_1::resqml20__IntegerLatticeArray*>(arrayInput)->Offset[0]->Count + 1;
	}

	throw invalid_argument("The integer array type is not supported yet.");
}

uint64_t AbstractObject::getCountOfIntegerArray(gsoap_eml2_3::eml23__AbstractIntegerArray * arrayInput) const
{
	long soapType = arrayInput->soap_type();
	if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray)
	{
		uint64_t result = 0;
		for (auto dsPart : static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(arrayInput)->Values->ExternalFileProxy) {
			result += dsPart->Count;
		}
		return result;
	}
	else if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerRangeArray)
	{
		return static_cast<gsoap_eml2_3::eml23__IntegerRangeArray*>(arrayInput)->Count;
	}
	else if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray)
	{
		return static_cast<gsoap_eml2_3::eml23__IntegerConstantArray*>(arrayInput)->Count;
	}
	else if (soapType == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray)
	{
		gsoap_eml2_3::eml23__IntegerLatticeArray* latticeArray = static_cast<gsoap_eml2_3::eml23__IntegerLatticeArray*>(arrayInput);
		if (latticeArray->Offset.size() > 1) {
			throw invalid_argument("The integer lattice array contains more than one offset.");
		}
		return static_cast<gsoap_eml2_3::eml23__IntegerLatticeArray*>(arrayInput)->Offset[0]->Count + 1;
	}

	throw invalid_argument("The integer array type is not supported yet.");
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
	}
	getRepository()->addRelationship(this, targetObj);
}

EML2_NS::AbstractHdfProxy* AbstractObject::getHdfProxyFromDataset(gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset, bool throwException) const
{
	EML2_NS::AbstractHdfProxy * hdfProxy = getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
	if (throwException && hdfProxy == nullptr) {
		throw invalid_argument("The HDF proxy is missing.");
	}
	return hdfProxy;
}

EML2_NS::AbstractHdfProxy* AbstractObject::getHdfProxyFromDataset(gsoap_eml2_3::eml23__ExternalDatasetPart const * dataset, bool throwException) const
{
	EML2_NS::AbstractHdfProxy * hdfProxy = getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataset->EpcExternalPartReference->Uuid);
	if (throwException && hdfProxy == nullptr) {
		throw invalid_argument("The HDF proxy is missing.");
	}
	return hdfProxy;
}

gsoap_resqml2_0_1::resqml20__IndexableElements AbstractObject::mapIndexableElement(gsoap_eml2_3::resqml22__IndexableElement toMap) const
{
	size_t intVal = static_cast<size_t>(toMap);
	if (intVal == 0) {
		return static_cast<gsoap_resqml2_0_1::resqml20__IndexableElements>(toMap);
	}
	else if (toMap == gsoap_eml2_3::resqml22__IndexableElement__intervals_x0020from_x0020datum || intVal == gsoap_eml2_3::resqml22__IndexableElement__lines) {
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
