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
#include "WellboreCompletion.h"
#include "Wellbore.h"
#include "WellCompletion.h"
#include "../tools/TimeTools.h"

using namespace std;
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;

WellboreCompletion::WellboreCompletion(WITSML2_NS::Wellbore* witsmlWellbore,
	class WellCompletion* wellCompletion,
	const string & guid,
	const string & title,
	const string & wellCompletionName)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("A wellbore must be associated to a wellbore completion.");
	}
	if (wellCompletion == nullptr) {
		throw invalid_argument("A well completion must be associated to a wellbore completion");
	}

	gsoapProxy2_1 = soap_new_witsml20__WellboreCompletion(witsmlWellbore->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	static_cast<witsml20__WellboreCompletion*>(gsoapProxy2_1)->NameWellCompletion = wellCompletionName;

	witsmlWellbore->getRepository()->addDataObject(this);
	setWellbore(witsmlWellbore);
	setWellCompletion(wellCompletion);
}

COMMON_NS::DataObjectReference WellboreCompletion::getWellboreDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<witsml20__WellboreCompletion*>(gsoapProxy2_1)->ReferenceWellbore);
}

COMMON_NS::DataObjectReference WellboreCompletion::getWellCompletionDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<witsml20__WellboreCompletion*>(gsoapProxy2_1)->WellCompletion);
}

class WellCompletion* WellboreCompletion::getWellCompletion() const
{
	return getRepository()->getDataObjectByUuid<WellCompletion>(getWellCompletionDor().getUuid());
}

void WellboreCompletion::setWellbore(WITSML2_NS::Wellbore* witsmlWellbore)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("Cannot set a null witsml well bore to a witsml wellbore completion");
	}

	static_cast<witsml20__WellboreCompletion*>(gsoapProxy2_1)->ReferenceWellbore = witsmlWellbore->newEmlReference();

	getRepository()->addRelationship(this, witsmlWellbore);
}

void WellboreCompletion::setWellCompletion(WellCompletion* wellCompletion)
{
	if (wellCompletion == nullptr) {
		throw invalid_argument("Cannot set a null witsml well completion to a witsml wellbore completion");
	}

	// XML
	witsml20__WellboreCompletion* wellboreCompletion = static_cast<witsml20__WellboreCompletion*>(gsoapProxy2_1);
	wellboreCompletion->WellCompletion = wellCompletion->newEmlReference();

	getRepository()->addRelationship(this, wellCompletion);
}

void WellboreCompletion::pushBackPerforation(const string & datum,
	eml21__LengthUom MdUnit,
	double TopMd,
	double BaseMd,
	const string & guid)
{
	witsml20__WellboreCompletion* wellboreCompletion = static_cast<witsml20__WellboreCompletion*>(gsoapProxy2_1);

	if (wellboreCompletion->ContactIntervalSet == nullptr) {
		wellboreCompletion->ContactIntervalSet = soap_new_witsml20__ContactIntervalSet(gsoapProxy2_1->soap);
	}

	witsml20__PerforationSetInterval* perforationSetInterval = soap_new_witsml20__PerforationSetInterval(gsoapProxy2_1->soap);

	perforationSetInterval->uid = guid.empty()
		? std::to_string(wellboreCompletion->ContactIntervalSet->PerforationSetInterval.size())
		: guid;

	perforationSetInterval->PerforationSetMdInterval = soap_new_eml21__MdInterval(gsoapProxy2_1->soap);
	perforationSetInterval->PerforationSetMdInterval->datum = datum;
	perforationSetInterval->PerforationSetMdInterval->MdTop = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
	perforationSetInterval->PerforationSetMdInterval->MdTop->uom = MdUnit;
	perforationSetInterval->PerforationSetMdInterval->MdTop->__item = TopMd;
	perforationSetInterval->PerforationSetMdInterval->MdBase = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
	perforationSetInterval->PerforationSetMdInterval->MdBase->uom = MdUnit;
	perforationSetInterval->PerforationSetMdInterval->MdBase->__item = BaseMd;

	wellboreCompletion->ContactIntervalSet->PerforationSetInterval.push_back(perforationSetInterval);
}

void WellboreCompletion::pushBackPerforationExtraMetadata(uint64_t index,
	const std::string & key, const std::string & value)
{
	witsml20__PerforationSetInterval * perforationSetInterval = getPerforation(index);

	gsoap_eml2_1::eml21__ExtensionNameValue* stringPair = gsoap_eml2_1::soap_new_eml21__ExtensionNameValue(gsoapProxy2_1->soap);
	stringPair->Name = key;
	stringPair->Value = gsoap_eml2_1::soap_new_eml21__StringMeasure(gsoapProxy2_1->soap);
	stringPair->Value->__item = value;
	perforationSetInterval->ExtensionNameValue.push_back(stringPair);
}

std::vector<std::string> WellboreCompletion::getPerforationExtraMetadata(uint64_t index, const std::string & key) const
{
	vector<string> result;

	witsml20__PerforationSetInterval * perforationSetInterval = getPerforation(index);
	for (auto const* pair :perforationSetInterval->ExtensionNameValue) {
		if (pair->Name == key) {
			result.push_back(pair->Value->__item);
		}
	}

	return result;
}

void WellboreCompletion::pushBackPerforationHistory(uint64_t index,
	const std::string & guid)
{
	witsml20__PerforationSetInterval * perforationSetInterval = getPerforation(index);

	witsml20__PerforationStatusHistory* perforationStatusHistory = soap_new_witsml20__PerforationStatusHistory(gsoapProxy2_1->soap);
	perforationStatusHistory->uid = guid.empty()
		? std::to_string(perforationSetInterval->PerforationStatusHistory.size())
		: guid;

	perforationSetInterval->PerforationStatusHistory.push_back(perforationStatusHistory);
}

void WellboreCompletion::pushBackPerforationHistory(uint64_t index,
	gsoap_eml2_1::witsml20__PerforationStatus perforationStatus,
	time_t startDate,
	const std::string & guid)
{
	witsml20__PerforationSetInterval * perforationSetInterval = getPerforation(index);

	witsml20__PerforationStatusHistory* perforationStatusHistory = soap_new_witsml20__PerforationStatusHistory(gsoapProxy2_1->soap);
	perforationStatusHistory->uid = guid.empty()
		? std::to_string(perforationSetInterval->PerforationStatusHistory.size())
		: guid;

	perforationStatusHistory->PerforationStatus = soap_new_witsml20__PerforationStatus(gsoapProxy2_1->soap);
	*perforationStatusHistory->PerforationStatus = perforationStatus;

	if (startDate != -1) {
		perforationStatusHistory->StartDate = soap_new_std__string(gsoapProxy2_1->soap);
		perforationStatusHistory->StartDate->assign(timeTools::convertUnixTimestampToIso(startDate));
	}

	perforationSetInterval->PerforationStatusHistory.push_back(perforationStatusHistory);
}

uint64_t WellboreCompletion::getPerforationCount() const
{
	witsml20__WellboreCompletion* wellboreCompletion = static_cast<witsml20__WellboreCompletion*>(gsoapProxy2_1);

	if (wellboreCompletion->ContactIntervalSet == nullptr) {
		throw invalid_argument("No contact interval exists.");
	}

	return wellboreCompletion->ContactIntervalSet->PerforationSetInterval.size();
}

std::string WellboreCompletion::getPerforationUid(uint64_t index) const
{
	return getPerforation(index)->uid;
}

bool WellboreCompletion::hasPerforationMdDatum(uint64_t index) const
{
	return getPerforation(index)->PerforationSetMdInterval != nullptr;
}

string WellboreCompletion::getPerforationMdDatum(uint64_t index) const
{
	if (!hasPerforationMdDatum(index)) {
		throw invalid_argument("No perforation md datum is defined.");
	}

	return getPerforation(index)->PerforationSetMdInterval->datum;
}

bool WellboreCompletion::hasPerforationMdUnit(uint64_t index) const
{
	witsml20__PerforationSetInterval const * const perforationSetInterval = getPerforation(index);

	return perforationSetInterval->PerforationSetMdInterval == nullptr
		? false
		: perforationSetInterval->PerforationSetMdInterval->MdBase != nullptr || perforationSetInterval->PerforationSetMdInterval->MdTop != nullptr;
}

eml21__LengthUom WellboreCompletion::getPerforationMdUnit(uint64_t index) const
{
	if (!hasPerforationMdUnit(index)) {
		throw invalid_argument("No perforation md unit is defined.");
	}

	witsml20__PerforationSetInterval const * const perforationSetInterval = getPerforation(index);

	return perforationSetInterval->PerforationSetMdInterval->MdBase != nullptr
		? perforationSetInterval->PerforationSetMdInterval->MdBase->uom
		: perforationSetInterval->PerforationSetMdInterval->MdTop->uom;
}

string WellboreCompletion::getPerforationMdUnitAsString(uint64_t index) const
{
	return gsoap_eml2_1::soap_eml21__LengthUom2s(gsoapProxy2_1->soap, getPerforationMdUnit(index));
}

bool WellboreCompletion::hasPerforationTopMd(uint64_t index) const
{
	witsml20__PerforationSetInterval const * const perforationSetInterval = getPerforation(index);

	return perforationSetInterval->PerforationSetMdInterval == nullptr
		? false
		: perforationSetInterval->PerforationSetMdInterval->MdTop != nullptr;
}

double WellboreCompletion::getPerforationTopMd(uint64_t index) const
{
	if (!hasPerforationTopMd(index)) {
		throw invalid_argument("No perforation top md is defined.");
	}

	return getPerforation(index)->PerforationSetMdInterval->MdTop->__item;
}

bool WellboreCompletion::hasPerforationBaseMd(uint64_t index) const
{
	witsml20__PerforationSetInterval const * const perforationSetInterval = getPerforation(index);

	return perforationSetInterval->PerforationSetMdInterval == nullptr
		? false
		: perforationSetInterval->PerforationSetMdInterval->MdBase != nullptr;
}

double WellboreCompletion::getPerforationBaseMd(uint64_t index) const
{
	if (!hasPerforationBaseMd(index)) {
		throw invalid_argument("No perforation base md is defined.");
	}

	return getPerforation(index)->PerforationSetMdInterval->MdBase->__item;
}

uint64_t WellboreCompletion::getPerforationHistoryCount(uint64_t index) const
{
	return getPerforation(index)->PerforationStatusHistory.size();
}

bool WellboreCompletion::hasPerforationHistoryStatus(uint64_t historyIndex,
	uint64_t perforationIndex) const
{
	return getPerforationHistoryEntry(historyIndex, perforationIndex)->PerforationStatus != nullptr;
}

witsml20__PerforationStatus WellboreCompletion::getPerforationHistoryStatus(uint64_t historyIndex,
	uint64_t perforationIndex) const
{
	if (!hasPerforationHistoryStatus(historyIndex, perforationIndex)) {
		throw invalid_argument("No perforation history entry is defined.");
	}

	return *getPerforationHistoryEntry(historyIndex, perforationIndex)->PerforationStatus;
}

string WellboreCompletion::getPerforationHistoryStatusToString(uint64_t historyIndex,
	uint64_t perforationIndex) const
{
	return gsoap_eml2_1::soap_witsml20__PerforationStatus2s(gsoapProxy2_1->soap, getPerforationHistoryStatus(historyIndex, perforationIndex));
}

void WellboreCompletion::setPerforationHistoryStatus(uint64_t historyIndex,
	uint64_t perforationIndex,
	gsoap_eml2_1::witsml20__PerforationStatus perforationStatus)
{
	witsml20__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);

	if (perforationStatusHistory->PerforationStatus == nullptr) {
		perforationStatusHistory->PerforationStatus = soap_new_witsml20__PerforationStatus(gsoapProxy2_1->soap);
	}

	*perforationStatusHistory->PerforationStatus = perforationStatus;
}

bool WellboreCompletion::hasPerforationHistoryStartDate(uint64_t historyIndex,
	uint64_t perforationIndex) const
{
	return getPerforationHistoryEntry(historyIndex, perforationIndex)->StartDate != nullptr;
}

time_t WellboreCompletion::getPerforationHistoryStartDate(uint64_t historyIndex,
	uint64_t perforationIndex) const
{
	if (!hasPerforationHistoryStartDate(historyIndex, perforationIndex)) {
		throw invalid_argument("No perforation history entry start date is defined.");
	}

	return timeTools::convertIsoToUnixTimestamp(*getPerforationHistoryEntry(historyIndex, perforationIndex)->StartDate);
}

void WellboreCompletion::setPerforationHistoryStartDate(uint64_t historyIndex,
	uint64_t perforationIndex, time_t startDate) const
{
	witsml20__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);

	if (perforationStatusHistory->StartDate == nullptr) {
		perforationStatusHistory->StartDate = soap_new_std__string(gsoapProxy2_1->soap);
	}

	perforationStatusHistory->StartDate->assign(timeTools::convertUnixTimestampToIso(startDate));
}

bool WellboreCompletion::hasPerforationHistoryEndDate(uint64_t historyIndex,
	uint64_t perforationIndex) const
{
	return getPerforationHistoryEntry(historyIndex, perforationIndex)->EndDate != nullptr;
}

time_t WellboreCompletion::getPerforationHistoryEndDate(uint64_t historyIndex,
	uint64_t perforationIndex) const
{
	if (!hasPerforationHistoryEndDate(historyIndex, perforationIndex)) {
		throw invalid_argument("No perforation history entry end date is defined.");
	}

	return timeTools::convertIsoToUnixTimestamp(*getPerforationHistoryEntry(historyIndex, perforationIndex)->EndDate);
}

void WellboreCompletion::setPerforationHistoryEndDate(uint64_t historyIndex,
	uint64_t perforationIndex, time_t endDate) const
{
	witsml20__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);

	if (perforationStatusHistory->EndDate == nullptr) {
		perforationStatusHistory->EndDate = soap_new_std__string(gsoapProxy2_1->soap);
	}

	perforationStatusHistory->EndDate->assign(timeTools::convertUnixTimestampToIso(endDate));
}

bool WellboreCompletion::hasPerforationHistoryMdDatum(uint64_t historyIndex,
	uint64_t perforationIndex) const
{
	return (getPerforationHistoryEntry(historyIndex, perforationIndex)->PerforationMdInterval != nullptr);
}

string WellboreCompletion::getPerforationHistoryMdDatum(uint64_t historyIndex,
	uint64_t perforationIndex) const
{
	if (!hasPerforationHistoryMdDatum(historyIndex, perforationIndex)) {
		throw invalid_argument("No perforation history entry md datum is defined.");
	}

	return getPerforationHistoryEntry(historyIndex, perforationIndex)->PerforationMdInterval->datum;
}

bool WellboreCompletion::hasPerforationHistoryMdUnit(uint64_t historyIndex,
	uint64_t perforationIndex) const
{
	witsml20__PerforationStatusHistory const * const perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);

	return perforationStatusHistory->PerforationMdInterval == nullptr
		? false
		: perforationStatusHistory->PerforationMdInterval->MdBase != nullptr ||perforationStatusHistory->PerforationMdInterval->MdTop != nullptr;
}

eml21__LengthUom WellboreCompletion::getPerforationHistoryMdUnit(uint64_t historyIndex,
	uint64_t perforationIndex) const
{
	if (!hasPerforationHistoryMdUnit(historyIndex, perforationIndex)) {
		throw invalid_argument("No perforation history entry md unit is defined.");
	}

	witsml20__PerforationStatusHistory const * const perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);

	return perforationStatusHistory->PerforationMdInterval->MdBase != nullptr 
		? perforationStatusHistory->PerforationMdInterval->MdBase->uom
		: perforationStatusHistory->PerforationMdInterval->MdTop->uom;
}

string WellboreCompletion::getPerforationHistoryMdUnitAsString(uint64_t historyIndex,
	uint64_t perforationIndex) const
{
	return gsoap_eml2_1::soap_eml21__LengthUom2s(gsoapProxy2_1->soap, getPerforationHistoryMdUnit(historyIndex, perforationIndex));
}

bool WellboreCompletion::hasPerforationHistoryTopMd(uint64_t historyIndex,
	uint64_t perforationIndex) const
{
	witsml20__PerforationStatusHistory const * const perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);
	if (perforationStatusHistory == nullptr) {
		return false;
	}

	if (perforationStatusHistory->PerforationMdInterval == nullptr) {
		return false;
	}

	return perforationStatusHistory->PerforationMdInterval->MdTop != nullptr;
}

double WellboreCompletion::getPerforationHistoryTopMd(uint64_t historyIndex,
	uint64_t perforationIndex) const
{
	if (!hasPerforationHistoryTopMd(historyIndex, perforationIndex)) {
		throw invalid_argument("No perforation history entry top md is defined.");
	}

	return getPerforationHistoryEntry(historyIndex, perforationIndex)->PerforationMdInterval->MdTop->__item;
}

void WellboreCompletion::setPerforationHistoryTopMd(uint64_t historyIndex,
	uint64_t perforationIndex,
	const std::string & datum,
	gsoap_eml2_1::eml21__LengthUom MdUnit,
	double TopMd)
{
	witsml20__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);

	if (perforationStatusHistory->PerforationMdInterval == nullptr) {
		perforationStatusHistory->PerforationMdInterval = soap_new_eml21__MdInterval(gsoapProxy2_1->soap);	
	}

	perforationStatusHistory->PerforationMdInterval->datum = datum;
	perforationStatusHistory->PerforationMdInterval->MdTop = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
	perforationStatusHistory->PerforationMdInterval->MdTop->uom = MdUnit;
	perforationStatusHistory->PerforationMdInterval->MdTop->__item = TopMd;
}

bool WellboreCompletion::hasPerforationHistoryBaseMd(uint64_t historyIndex,
	uint64_t perforationIndex) const
{
	witsml20__PerforationStatusHistory const * const perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);
	if (perforationStatusHistory == nullptr) {
		return false;
	}

	if (perforationStatusHistory->PerforationMdInterval == nullptr) {
		return false;
	}

	return perforationStatusHistory->PerforationMdInterval->MdBase != nullptr;
}

double WellboreCompletion::getPerforationHistoryBaseMd(uint64_t historyIndex,
	uint64_t perforationIndex) const
{
	if (!hasPerforationHistoryBaseMd(historyIndex, perforationIndex))
	{
		throw invalid_argument("No perforation history entry base md is defined.");
	}

	return getPerforationHistoryEntry(historyIndex, perforationIndex)->PerforationMdInterval->MdBase->__item;
}

void WellboreCompletion::setPerforationHistoryBaseMd(uint64_t historyIndex,
	uint64_t perforationIndex,
	const std::string & datum,
	gsoap_eml2_1::eml21__LengthUom MdUnit,
	double BaseMd)
{
	witsml20__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);

	if (perforationStatusHistory->PerforationMdInterval == nullptr) {
		perforationStatusHistory->PerforationMdInterval = soap_new_eml21__MdInterval(gsoapProxy2_1->soap);
	}

	perforationStatusHistory->PerforationMdInterval->datum = datum;
	perforationStatusHistory->PerforationMdInterval->MdBase = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
	perforationStatusHistory->PerforationMdInterval->MdBase->uom = MdUnit;
	perforationStatusHistory->PerforationMdInterval->MdBase->__item = BaseMd;
}

bool WellboreCompletion::hasPerforationHistoryComment(uint64_t historyIndex,
	uint64_t perforationIndex) const
{
	witsml20__PerforationStatusHistory const* const perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);
	if (perforationStatusHistory == nullptr) {
		return false;
	}

	return perforationStatusHistory->Comment != nullptr;
}

std::string WellboreCompletion::getPerforationHistoryComment(uint64_t historyIndex,
	uint64_t perforationIndex) const
{
	if (!hasPerforationHistoryComment(historyIndex, perforationIndex)) {
		throw invalid_argument("No perforation history comment is defined.");
	}

	return *getPerforationHistoryEntry(historyIndex, perforationIndex)->Comment;
}

void WellboreCompletion::setPerforationHistoryComment(uint64_t historyIndex,
	uint64_t perforationIndex,
	const std::string & comment)
{
	witsml20__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);

	if (perforationStatusHistory->Comment == nullptr) {
		perforationStatusHistory->Comment = soap_new_std__string(gsoapProxy2_1->soap);
	}
	perforationStatusHistory->Comment->assign(comment);
}

void WellboreCompletion::loadTargetRelationships()
{
	WellboreObject::loadTargetRelationships();

	convertDorIntoRel<WellCompletion>(getWellCompletionDor());
}

gsoap_eml2_1::witsml20__PerforationSetInterval* WellboreCompletion::getPerforation(uint64_t index) const
{
	witsml20__WellboreCompletion const * const wellboreCompletion = static_cast<witsml20__WellboreCompletion*>(gsoapProxy2_1);

	if (wellboreCompletion->ContactIntervalSet == nullptr) {
		throw invalid_argument("No contact interval exists.");
	}

	if (index >= wellboreCompletion->ContactIntervalSet->PerforationSetInterval.size()) {
		throw out_of_range("Perforation index out of range.");
	}

	return wellboreCompletion->ContactIntervalSet->PerforationSetInterval[index];
}

gsoap_eml2_1::witsml20__PerforationStatusHistory* WellboreCompletion::getPerforationHistoryEntry(uint64_t index,
	uint64_t perforationIndex) const
{
	witsml20__PerforationSetInterval const * const perforationSetInterval = getPerforation(perforationIndex);

	if (index >= perforationSetInterval->PerforationStatusHistory.size()) {
		throw invalid_argument("History index out of range.");
	}

	return perforationSetInterval->PerforationStatusHistory[index];
}
