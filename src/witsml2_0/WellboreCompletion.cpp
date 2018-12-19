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
#include "witsml2_0/WellboreCompletion.h"
#include "witsml2_0/Wellbore.h"
#include "witsml2_0/WellCompletion.h"
#include "tools/TimeTools.h"

#include <sstream>

using namespace std;
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;
using namespace epc;

const char* WellboreCompletion::XML_TAG = "WellboreCompletion";

WellboreCompletion::WellboreCompletion(Wellbore* witsmlWellbore,
	class WellCompletion* wellCompletion,
	const string & guid,
	const string & title,
	const string & wellCompletionName)
{
	if (witsmlWellbore == nullptr) throw invalid_argument("A wellbore must be associated to a wellbore wompletion.");
	if (wellCompletion == nullptr) throw invalid_argument("A well completion must be associated to a wellbore completion");

	gsoapProxy2_1 = soap_new_witsml2__WellboreCompletion(witsmlWellbore->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	setWellbore(witsmlWellbore);
	setWellCompletion(wellCompletion);

	witsml2__WellboreCompletion* wellboreCompletion = static_cast<witsml2__WellboreCompletion*>(gsoapProxy2_1);

	wellboreCompletion->NameWellCompletion = wellCompletionName;
}

gsoap_eml2_1::eml21__DataObjectReference* WellboreCompletion::getWellboreDor() const
{
	return static_cast<witsml2__WellboreCompletion*>(gsoapProxy2_1)->ReferenceWellbore;
}

class Wellbore* WellboreCompletion::getWellbore() const
{
	return getEpcDocument()->getResqmlAbstractObjectByUuid<Wellbore>(getWellboreDor()->Uuid);
}

gsoap_eml2_1::eml21__DataObjectReference* WellboreCompletion::getWellCompletionDor() const
{
	return static_cast<witsml2__WellboreCompletion*>(gsoapProxy2_1)->WellCompletion;
}

class WellCompletion* WellboreCompletion::getWellCompletion() const
{
	return getEpcDocument()->getResqmlAbstractObjectByUuid<WellCompletion>(getWellCompletionDor()->Uuid);
}

void WellboreCompletion::setWellbore(Wellbore* witsmlWellbore)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("Cannot set a null witsml well bore to a witsml wellbore completion");
	}

	// EPC
	witsmlWellbore->wellboreCompletionSet.push_back(this);

	// XML
	if (updateXml) {
		witsml2__WellboreCompletion* wellboreCompletion = static_cast<witsml2__WellboreCompletion*>(gsoapProxy2_1);
		wellboreCompletion->ReferenceWellbore = witsmlWellbore->newEmlReference();
	}
}

void WellboreCompletion::setWellCompletion(WellCompletion* wellCompletion)
{
	if (wellCompletion == nullptr) {
		throw invalid_argument("Cannot set a null witsml well completion to a witsml wellbore completion");
	}

	// EPC
	wellCompletion->wellboreCompletionSet.push_back(this);

	// XML
	if (updateXml) {
		witsml2__WellboreCompletion* wellboreCompletion = static_cast<witsml2__WellboreCompletion*>(gsoapProxy2_1);
		wellboreCompletion->WellCompletion = wellCompletion->newEmlReference();
	}
}

void WellboreCompletion::pushBackPerforation(const string & datum,
	eml21__LengthUom MdUnit,
	const double & TopMd,
	const double & BaseMd,
	const string & guid
)
{
	witsml2__WellboreCompletion* wellboreCompletion = static_cast<witsml2__WellboreCompletion*>(gsoapProxy2_1);

	if (wellboreCompletion->ContactIntervalSet == nullptr)
	{
		wellboreCompletion->ContactIntervalSet = soap_new_witsml2__ContactIntervalSet(gsoapProxy2_1->soap, 1);
	}

	witsml2__PerforationSetInterval* perforationSetInterval = soap_new_witsml2__PerforationSetInterval(gsoapProxy2_1->soap, 1);

	if (guid.size() == 0) {
		ostringstream oss;
		oss << wellboreCompletion->ContactIntervalSet->PerforationSetInterval.size();
		perforationSetInterval->uid = oss.str();
	}
	else {
		perforationSetInterval->uid = guid;
	}

	perforationSetInterval->PerforationSetMdInterval = soap_new_eml21__MdInterval(gsoapProxy2_1->soap, 1);
	perforationSetInterval->PerforationSetMdInterval->datum = datum;
	perforationSetInterval->PerforationSetMdInterval->MdTop = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap, 1);
	perforationSetInterval->PerforationSetMdInterval->MdTop->uom = MdUnit;
	perforationSetInterval->PerforationSetMdInterval->MdTop->__item = TopMd;
	perforationSetInterval->PerforationSetMdInterval->MdBase = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap, 1);
	perforationSetInterval->PerforationSetMdInterval->MdBase->uom = MdUnit;
	perforationSetInterval->PerforationSetMdInterval->MdBase->__item = BaseMd;

	wellboreCompletion->ContactIntervalSet->PerforationSetInterval.push_back(perforationSetInterval);
}

void WellboreCompletion::pushBackPerforationHistoryEntry(const std::string & perforationGuid,
	gsoap_eml2_1::witsml2__PerforationStatus perforationStatus,
	const string & datum,
	gsoap_eml2_1::eml21__LengthUom MdUnit,
	const double & TopMd,
	const double & BaseMd,
	const time_t & startDate,
	const time_t & endDate,
	const string & guid
)
{
	witsml2__WellboreCompletion* wellboreCompletion = static_cast<witsml2__WellboreCompletion*>(gsoapProxy2_1);

	witsml2__PerforationSetInterval * perforationSetInterval = getPerforation(perforationGuid);
	if (perforationSetInterval == nullptr)
	{
		throw invalid_argument("The perforation guid is invalid.");
	}

	witsml2__PerforationStatusHistory* perforationStatusHistory = soap_new_witsml2__PerforationStatusHistory(gsoapProxy2_1->soap, 1);

	if (guid.size() == 0) {
		ostringstream oss;
		oss << perforationSetInterval->PerforationStatusHistory.size();
		perforationStatusHistory->uid = oss.str();
	}
	else {
		perforationStatusHistory->uid = guid;
	}

	perforationStatusHistory->PerforationStatus = soap_new_witsml2__PerforationStatus(gsoapProxy2_1->soap, 1);
	*perforationStatusHistory->PerforationStatus = perforationStatus;

	if (startDate != -1)
	{
		perforationStatusHistory->StartDate = soap_new_std__string(gsoapProxy2_1->soap, 1);
		perforationStatusHistory->StartDate->assign(timeTools::convertUnixTimestampToIso(startDate));
	}

	if (endDate != -1)
	{
		perforationStatusHistory->EndDate = soap_new_std__string(gsoapProxy2_1->soap, 1);
		perforationStatusHistory->EndDate->assign(timeTools::convertUnixTimestampToIso(endDate));
	}

	perforationStatusHistory->PerforationMdInterval = soap_new_eml21__MdInterval(gsoapProxy2_1->soap, 1);
	perforationStatusHistory->PerforationMdInterval->datum = datum;
	perforationStatusHistory->PerforationMdInterval->MdTop = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap, 1);
	perforationStatusHistory->PerforationMdInterval->MdTop->uom = MdUnit;
	perforationStatusHistory->PerforationMdInterval->MdTop->__item = TopMd;
	perforationStatusHistory->PerforationMdInterval->MdBase = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap, 1);
	perforationStatusHistory->PerforationMdInterval->MdBase->uom = MdUnit;
	perforationStatusHistory->PerforationMdInterval->MdBase->__item = BaseMd;

	perforationSetInterval->PerforationStatusHistory.push_back(perforationStatusHistory);
}

unsigned int WellboreCompletion::getPerforationCount() const
{
	witsml2__WellboreCompletion* wellboreCompletion = static_cast<witsml2__WellboreCompletion*>(gsoapProxy2_1);

	if (wellboreCompletion->ContactIntervalSet == nullptr)
	{
		throw invalid_argument("No contact interval exists.");
	}

	return wellboreCompletion->ContactIntervalSet->PerforationSetInterval.size();
}

bool WellboreCompletion::hasPerforationMdDatum(const std::string & guid) const
{
	witsml2__PerforationSetInterval * perforationSetInterval = getPerforation(guid);
	if (perforationSetInterval == nullptr)
	{
		return false;
	}

	return (perforationSetInterval->PerforationSetMdInterval != nullptr);
}

string WellboreCompletion::getPerforationMdDatum(const string & guid) const
{
	if (!hasPerforationMdDatum(guid))
	{
		throw invalid_argument("No perforation md datum is defined.");
	}

	witsml2__PerforationSetInterval * perforationSetInterval = getPerforation(guid);
	return perforationSetInterval->PerforationSetMdInterval->datum;
}

bool WellboreCompletion::hasPerforationMdUnit(const std::string & guid) const
{
	witsml2__PerforationSetInterval * perforationSetInterval = getPerforation(guid);
	if (perforationSetInterval == nullptr)
	{
		return false;
	}

	if (perforationSetInterval->PerforationSetMdInterval == nullptr)
	{
		return false;
	}

	return perforationSetInterval->PerforationSetMdInterval->MdBase != nullptr ||
		perforationSetInterval->PerforationSetMdInterval->MdTop != nullptr;
}

eml21__LengthUom WellboreCompletion::getPerforationMdUnit(const string & guid) const
{
	if (!hasPerforationMdUnit(guid))
	{
		throw invalid_argument("No perforation md unit is defined.");
	}

	witsml2__PerforationSetInterval * perforationSetInterval = getPerforation(guid);	
	if (perforationSetInterval->PerforationSetMdInterval->MdBase != nullptr)
	{
		return perforationSetInterval->PerforationSetMdInterval->MdBase->uom;
	}
	else
	{
		return perforationSetInterval->PerforationSetMdInterval->MdTop->uom;
	}
}

bool WellboreCompletion::hasPerforationTopMd(const std::string & guid) const
{
	witsml2__PerforationSetInterval * perforationSetInterval = getPerforation(guid);
	if (perforationSetInterval == nullptr)
	{
		return false;
	}

	if (perforationSetInterval->PerforationSetMdInterval == nullptr)
	{
		return false;
	}

	return (perforationSetInterval->PerforationSetMdInterval->MdTop != nullptr);
}

double WellboreCompletion::getPerforationTopMd(const string & guid) const
{
	if (!hasPerforationTopMd(guid))
	{
		throw invalid_argument("No perforation top md is defined.");
	}

	witsml2__PerforationSetInterval * perforationSetInterval = getPerforation(guid);
	return perforationSetInterval->PerforationSetMdInterval->MdTop->__item;
}

bool WellboreCompletion::hasPerforationBaseMd(const std::string & guid) const
{
	witsml2__PerforationSetInterval * perforationSetInterval = getPerforation(guid);
	if (perforationSetInterval == nullptr)
	{
		return false;
	}

	if (perforationSetInterval->PerforationSetMdInterval == nullptr)
	{
		return false;
	}

	return (perforationSetInterval->PerforationSetMdInterval->MdBase != nullptr);
}

double WellboreCompletion::getPerforationBaseMd(const string & guid) const
{
	if (!hasPerforationBaseMd(guid))
	{
		throw invalid_argument("No perforation base md is defined.");
	}

	witsml2__PerforationSetInterval * perforationSetInterval = getPerforation(guid);
	return perforationSetInterval->PerforationSetMdInterval->MdBase->__item;
}

unsigned int WellboreCompletion::getHistoryEntryCount(const std::string & perforationGuid) const
{
	witsml2__PerforationSetInterval * perforation = getPerforation(perforationGuid);

	return perforation->PerforationStatusHistory.size();
}

bool WellboreCompletion::hasPerforationHistoryEntryStatus(const std::string & guid,
	const std::string & perforationGuid) const
{
	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(guid, perforationGuid);
	if (perforationStatusHistory == nullptr)
	{
		return false;
	}

	return perforationStatusHistory->PerforationStatus != nullptr;
}

witsml2__PerforationStatus WellboreCompletion::getPerforationHistoryEntryStatus(const string & guid,
	const string & perforationGuid) const
{
	if (!hasPerforationHistoryEntryStatus(guid, perforationGuid))
	{
		throw invalid_argument("No perforation history entry is defined.");
	}

	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(guid, perforationGuid);
	return *perforationStatusHistory->PerforationStatus;
}

string WellboreCompletion::getPerforationHistoryEntryStatusToString(const string & guid,
	const string & perforationGuid) const
{
	return gsoap_eml2_1::soap_witsml2__PerforationStatus2s(gsoapProxy2_1->soap, getPerforationHistoryEntryStatus(guid, perforationGuid));
}

bool WellboreCompletion::hasPerforationHistoryEntryStartDate(const std::string & guid,
	const std::string & perforationGuid) const
{
	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(guid, perforationGuid);
	if (perforationStatusHistory == nullptr)
	{
		return false;
	}

	return perforationStatusHistory->StartDate != nullptr;
}

time_t WellboreCompletion::getPerforationHistoryEntryStartDate(const string & guid,
	const string & perforationGuid) const
{
	if (!hasPerforationHistoryEntryStartDate(guid, perforationGuid))
	{
		throw invalid_argument("No perforation history entry start date is defined.");
	}

	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(guid, perforationGuid);
	string startDate = *perforationStatusHistory->StartDate;

	return timeTools::convertIsoToUnixTimestamp(startDate);
}

bool WellboreCompletion::hasPerforationHistoryEntryEndDate(const std::string & guid,
	const std::string & perforationGuid) const
{
	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(guid, perforationGuid);
	if (perforationStatusHistory == nullptr)
	{
		return false;
	}

	return perforationStatusHistory->EndDate != nullptr;
}

time_t WellboreCompletion::getPerforationHistoryEntryEndDate(const string & guid,
	const string & perforationGuid) const
{
	if (!hasPerforationHistoryEntryEndDate(guid, perforationGuid))
	{
		throw invalid_argument("No perforation history entry end date is defined.");
	}

	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(guid, perforationGuid);
	string endDate = *perforationStatusHistory->EndDate;

	return timeTools::convertIsoToUnixTimestamp(endDate);
}

bool WellboreCompletion::hasPerforationHistoryEntryMdDatum(const std::string & guid,
	const std::string & perforationGuid) const
{
	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(guid, perforationGuid);
	if (perforationStatusHistory == nullptr)
	{
		return false;
	}

	return (perforationStatusHistory->PerforationMdInterval != nullptr);
}

string WellboreCompletion::getPerforationHistoryEntryMdDatum(const string & guid,
	const string & perforationGuid) const
{
	if (!hasPerforationHistoryEntryMdDatum(guid, perforationGuid))
	{
		throw invalid_argument("No perforation history entry md datum is defined.");
	}

	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(guid, perforationGuid);
	return perforationStatusHistory->PerforationMdInterval->datum;
}

bool WellboreCompletion::hasPerforationHistoryEntryMdUnit(const std::string & guid,
	const std::string & perforationGuid) const
{
	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(guid, perforationGuid);
	if (perforationStatusHistory == nullptr)
	{
		return false;
	}

	if (perforationStatusHistory->PerforationMdInterval == nullptr)
	{
		return false;
	}

	return perforationStatusHistory->PerforationMdInterval->MdBase != nullptr ||
		perforationStatusHistory->PerforationMdInterval->MdTop != nullptr;
}

eml21__LengthUom WellboreCompletion::getPerforationHistoryEntryMdUnit(const std::string & guid,
	const std::string & perforationGuid) const
{
	if (!hasPerforationHistoryEntryMdUnit(guid, perforationGuid))
	{
		throw invalid_argument("No perforation history entry md unit is defined.");
	}

	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(guid, perforationGuid);
	if (perforationStatusHistory->PerforationMdInterval->MdBase != nullptr)
	{
		return perforationStatusHistory->PerforationMdInterval->MdBase->uom;
	}
	else
	{
		return perforationStatusHistory->PerforationMdInterval->MdTop->uom;
	}
}

bool WellboreCompletion::hasPerforationHistoryEntryTopMd(const std::string & guid,
	const std::string & perforationGuid) const
{
	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(guid, perforationGuid);
	if (perforationStatusHistory == nullptr)
	{
		return false;
	}

	if (perforationStatusHistory->PerforationMdInterval == nullptr)
	{
		return false;
	}

	return perforationStatusHistory->PerforationMdInterval->MdTop != nullptr;
}

double WellboreCompletion::getPerforationHistoryEntryTopMd(const std::string & guid,
	const std::string & perforationGuid) const
{
	if (!hasPerforationHistoryEntryTopMd(guid, perforationGuid))
	{
		throw invalid_argument("No perforation history entry top md is defined.");
	}

	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(guid, perforationGuid);
	return perforationStatusHistory->PerforationMdInterval->MdTop->__item;
}

bool WellboreCompletion::hasPerforationHistoryEntryBaseMd(const std::string & guid,
	const std::string & perforationGuid) const
{
	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(guid, perforationGuid);
	if (perforationStatusHistory == nullptr)
	{
		return false;
	}

	if (perforationStatusHistory->PerforationMdInterval == nullptr)
	{
		return false;
	}

	return perforationStatusHistory->PerforationMdInterval->MdBase != nullptr;
}

double WellboreCompletion::getPerforationHistoryEntryBaseMd(const std::string & guid,
	const std::string & perforationGuid) const
{
	if (!hasPerforationHistoryEntryBaseMd(guid, perforationGuid))
	{
		throw invalid_argument("No perforation history entry base md is defined.");
	}

	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(guid, perforationGuid);
	return perforationStatusHistory->PerforationMdInterval->MdBase->__item;
}

void WellboreCompletion::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	gsoap_eml2_1::eml21__DataObjectReference* dor = getWellboreDor();
	Wellbore* wellbore = epcDoc->getResqmlAbstractObjectByUuid<Wellbore>(dor->Uuid);
	// TODO à mettre à jour (avec une nouvelle createPartial pour eml 21
	/*
	if (well == nullptr) { // partial transfer
	getEpcDocument()->createPartial(dor);
	well = getEpcDocument()->getResqmlAbstractObjectByUuid<well>(dor->Uuid);
	}
	*/
	if (wellbore == nullptr) {
		throw invalid_argument("The DOR looks invalid.");
	}

	dor = getWellCompletionDor();
	WellCompletion* wellCompletion = epcDoc->getResqmlAbstractObjectByUuid<WellCompletion>(dor->Uuid);
	// TODO à mettre à jour (avec une nouvelle createPartial pour eml 21
	/*
	if (well == nullptr) { // partial transfer
	getEpcDocument()->createPartial(dor);
	well = getEpcDocument()->getResqmlAbstractObjectByUuid<well>(dor->Uuid);
	}
	*/
	if (wellCompletion == nullptr) {
		throw invalid_argument("The DOR looks invalid.");
	}

	updateXml = false;
	setWellbore(wellbore);
	setWellCompletion(wellCompletion);
	updateXml = true;
}

vector<Relationship> WellboreCompletion::getAllEpcRelationships() const
{
	vector<Relationship> result;

	// XML forward relationship
	Wellbore* wellbore = getWellbore();
	Relationship relWellbore(wellbore->getPartNameInEpcDocument(), "", wellbore->getUuid());
	relWellbore.setDestinationObjectType();
	result.push_back(relWellbore);

	WellCompletion* wellCompletion = getWellCompletion();
	Relationship relWellCompletion(wellCompletion->getPartNameInEpcDocument(), "", wellCompletion->getUuid());
	relWellCompletion.setDestinationObjectType();
	result.push_back(relWellCompletion);

	return result;
}

witsml2__PerforationSetInterval * WellboreCompletion::getPerforation(const string & guid) const
{
	witsml2__WellboreCompletion* wellboreCompletion = static_cast<witsml2__WellboreCompletion*>(gsoapProxy2_1);

	if (wellboreCompletion->ContactIntervalSet == nullptr)
	{
		throw invalid_argument("No contact interval exists.");
	}

	for (unsigned int perforationIndex = 0; perforationIndex < wellboreCompletion->ContactIntervalSet->PerforationSetInterval.size(); ++perforationIndex)
	{
		if (wellboreCompletion->ContactIntervalSet->PerforationSetInterval[perforationIndex]->uid == guid)
		{
			return wellboreCompletion->ContactIntervalSet->PerforationSetInterval[perforationIndex];

		}
	}

	return nullptr;
}

witsml2__PerforationStatusHistory* WellboreCompletion::getPerforationHistoryEntry(const string & guid, 
	const string & perforationGuid) const
{
	witsml2__PerforationSetInterval* perforationSetInterval = getPerforation(perforationGuid);

	if (perforationSetInterval == nullptr)
	{
		throw invalid_argument("The perforation guid is invalid.");
	}

	for (unsigned int perforationStatusHistoryIndex = 0; perforationStatusHistoryIndex < perforationSetInterval->PerforationStatusHistory.size(); ++perforationStatusHistoryIndex)
	{
		if (perforationSetInterval->PerforationStatusHistory[perforationStatusHistoryIndex]->uid == guid)
		{
			return perforationSetInterval->PerforationStatusHistory[perforationStatusHistoryIndex];
		}
	}

	return nullptr;
}