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
	if (witsmlWellbore == nullptr) throw invalid_argument("A wellbore must be associated to a wellbore completion.");
	if (wellCompletion == nullptr) throw invalid_argument("A well completion must be associated to a wellbore completion");

	gsoapProxy2_1 = soap_new_witsml2__WellboreCompletion(witsmlWellbore->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setWellbore(witsmlWellbore);
	setWellCompletion(wellCompletion);

	static_cast<witsml2__WellboreCompletion*>(gsoapProxy2_1)->NameWellCompletion = wellCompletionName;
}

gsoap_eml2_1::eml21__DataObjectReference* WellboreCompletion::getWellboreDor() const
{
	return static_cast<witsml2__WellboreCompletion*>(gsoapProxy2_1)->ReferenceWellbore;
}

gsoap_eml2_1::eml21__DataObjectReference* WellboreCompletion::getWellCompletionDor() const
{
	return static_cast<witsml2__WellboreCompletion*>(gsoapProxy2_1)->WellCompletion;
}

class WellCompletion* WellboreCompletion::getWellCompletion() const
{
	return getEpcDocument()->getDataObjectByUuid<WellCompletion>(getWellCompletionDor()->Uuid);
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

void WellboreCompletion::pushBackPerforationHistory(unsigned int index,
	const std::string & guid)
{
	witsml2__PerforationSetInterval * perforationSetInterval = getPerforation(index);

	witsml2__PerforationStatusHistory* perforationStatusHistory = soap_new_witsml2__PerforationStatusHistory(gsoapProxy2_1->soap, 1);

	if (guid.size() == 0) {
		ostringstream oss;
		oss << perforationSetInterval->PerforationStatusHistory.size();
		perforationStatusHistory->uid = oss.str();
	}
	else {
		perforationStatusHistory->uid = guid;
	}

	perforationSetInterval->PerforationStatusHistory.push_back(perforationStatusHistory);
}

void WellboreCompletion::pushBackPerforationHistory(unsigned int index,
	gsoap_eml2_1::witsml2__PerforationStatus perforationStatus,
	const time_t & startDate,
	const std::string & guid)
{
	witsml2__PerforationSetInterval * perforationSetInterval = getPerforation(index);

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

bool WellboreCompletion::hasPerforationMdDatum(unsigned int index) const
{
	return (getPerforation(index)->PerforationSetMdInterval != nullptr);
}

string WellboreCompletion::getPerforationMdDatum(unsigned int index) const
{
	if (!hasPerforationMdDatum(index))
	{
		throw invalid_argument("No perforation md datum is defined.");
	}

	return getPerforation(index)->PerforationSetMdInterval->datum;
}

bool WellboreCompletion::hasPerforationMdUnit(unsigned int index) const
{
	witsml2__PerforationSetInterval * perforationSetInterval = getPerforation(index);

	if (perforationSetInterval->PerforationSetMdInterval == nullptr)
	{
		return false;
	}

	return perforationSetInterval->PerforationSetMdInterval->MdBase != nullptr ||
		perforationSetInterval->PerforationSetMdInterval->MdTop != nullptr;
}

eml21__LengthUom WellboreCompletion::getPerforationMdUnit(unsigned int index) const
{
	if (!hasPerforationMdUnit(index))
	{
		throw invalid_argument("No perforation md unit is defined.");
	}

	witsml2__PerforationSetInterval * perforationSetInterval = getPerforation(index);

	if (perforationSetInterval->PerforationSetMdInterval->MdBase != nullptr)
	{
		return perforationSetInterval->PerforationSetMdInterval->MdBase->uom;
	}
	else
	{
		return perforationSetInterval->PerforationSetMdInterval->MdTop->uom;
	}
}

string WellboreCompletion::getPerforationMdUnitAsString(unsigned int index) const
{
	return gsoap_eml2_1::soap_eml21__LengthUom2s(gsoapProxy2_1->soap, getPerforationMdUnit(index));
}

bool WellboreCompletion::hasPerforationTopMd(unsigned int index) const
{
	witsml2__PerforationSetInterval * perforationSetInterval = getPerforation(index);

	if (perforationSetInterval->PerforationSetMdInterval == nullptr)
	{
		return false;
	}

	return (perforationSetInterval->PerforationSetMdInterval->MdTop != nullptr);
}

double WellboreCompletion::getPerforationTopMd(unsigned int index) const
{
	if (!hasPerforationTopMd(index))
	{
		throw invalid_argument("No perforation top md is defined.");
	}

	return getPerforation(index)->PerforationSetMdInterval->MdTop->__item;
}

bool WellboreCompletion::hasPerforationBaseMd(unsigned int index) const
{
	witsml2__PerforationSetInterval * perforationSetInterval = getPerforation(index);

	if (perforationSetInterval->PerforationSetMdInterval == nullptr)
	{
		return false;
	}

	return (perforationSetInterval->PerforationSetMdInterval->MdBase != nullptr);
}

double WellboreCompletion::getPerforationBaseMd(unsigned int index) const
{
	if (!hasPerforationBaseMd(index))
	{
		throw invalid_argument("No perforation base md is defined.");
	}

	return getPerforation(index)->PerforationSetMdInterval->MdBase->__item;
}

unsigned int WellboreCompletion::getPerforationHistoryCount(unsigned int index) const
{
	return getPerforation(index)->PerforationStatusHistory.size();
}

bool WellboreCompletion::hasPerforationHistoryStatus(unsigned int historyIndex,
	unsigned int perforationIndex) const
{
	return getPerforationHistoryEntry(historyIndex, perforationIndex)->PerforationStatus != nullptr;
}

witsml2__PerforationStatus WellboreCompletion::getPerforationHistoryStatus(unsigned int historyIndex,
	unsigned int perforationIndex) const
{
	if (!hasPerforationHistoryStatus(historyIndex, perforationIndex))
	{
		throw invalid_argument("No perforation history entry is defined.");
	}

	return *getPerforationHistoryEntry(historyIndex, perforationIndex)->PerforationStatus;
}

string WellboreCompletion::getPerforationHistoryStatusToString(unsigned int historyIndex,
	unsigned int perforationIndex) const
{
	return gsoap_eml2_1::soap_witsml2__PerforationStatus2s(gsoapProxy2_1->soap, getPerforationHistoryStatus(historyIndex, perforationIndex));
}

void WellboreCompletion::setPerforationHistoryStatus(unsigned int historyIndex,
	unsigned int perforationIndex,
	gsoap_eml2_1::witsml2__PerforationStatus perforationStatus)
{
	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);

	if (perforationStatusHistory->PerforationStatus == nullptr)
	{
		perforationStatusHistory->PerforationStatus = soap_new_witsml2__PerforationStatus(gsoapProxy2_1->soap, 1);
	}

	*perforationStatusHistory->PerforationStatus = perforationStatus;
}

bool WellboreCompletion::hasPerforationHistoryStartDate(unsigned int historyIndex,
	unsigned int perforationIndex) const
{
	return getPerforationHistoryEntry(historyIndex, perforationIndex)->StartDate != nullptr;
}

time_t WellboreCompletion::getPerforationHistoryStartDate(unsigned int historyIndex,
	unsigned int perforationIndex) const
{
	if (!hasPerforationHistoryStartDate(historyIndex, perforationIndex))
	{
		throw invalid_argument("No perforation history entry start date is defined.");
	}

	string startDate = *getPerforationHistoryEntry(historyIndex, perforationIndex)->StartDate;

	return timeTools::convertIsoToUnixTimestamp(startDate);
}

void WellboreCompletion::setPerforationHistoryStartDate(unsigned int historyIndex,
	unsigned int perforationIndex, const time_t & startDate) const
{
	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);

	if (perforationStatusHistory->StartDate == nullptr)
	{
		perforationStatusHistory->StartDate = soap_new_std__string(gsoapProxy2_1->soap, 1);
	}

	perforationStatusHistory->StartDate->assign(timeTools::convertUnixTimestampToIso(startDate));
}

bool WellboreCompletion::hasPerforationHistoryEndDate(unsigned int historyIndex,
	unsigned int perforationIndex) const
{
	return getPerforationHistoryEntry(historyIndex, perforationIndex)->EndDate != nullptr;
}

time_t WellboreCompletion::getPerforationHistoryEndDate(unsigned int historyIndex,
	unsigned int perforationIndex) const
{
	if (!hasPerforationHistoryEndDate(historyIndex, perforationIndex))
	{
		throw invalid_argument("No perforation history entry end date is defined.");
	}

	string endDate = *getPerforationHistoryEntry(historyIndex, perforationIndex)->EndDate;

	return timeTools::convertIsoToUnixTimestamp(endDate);
}

void WellboreCompletion::setPerforationHistoryEndDate(unsigned int historyIndex,
	unsigned int perforationIndex, const time_t & endDate) const
{
	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);

	if (perforationStatusHistory->EndDate == nullptr)
	{
		perforationStatusHistory->EndDate = soap_new_std__string(gsoapProxy2_1->soap, 1);
	}

	perforationStatusHistory->EndDate->assign(timeTools::convertUnixTimestampToIso(endDate));
}

bool WellboreCompletion::hasPerforationHistoryMdDatum(unsigned int historyIndex,
	unsigned int perforationIndex) const
{
	return (getPerforationHistoryEntry(historyIndex, perforationIndex)->PerforationMdInterval != nullptr);
}

string WellboreCompletion::getPerforationHistoryMdDatum(unsigned int historyIndex,
	unsigned int perforationIndex) const
{
	if (!hasPerforationHistoryMdDatum(historyIndex, perforationIndex))
	{
		throw invalid_argument("No perforation history entry md datum is defined.");
	}

	return getPerforationHistoryEntry(historyIndex, perforationIndex)->PerforationMdInterval->datum;
}

bool WellboreCompletion::hasPerforationHistoryMdUnit(unsigned int historyIndex,
	unsigned int perforationIndex) const
{
	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);

	if (perforationStatusHistory->PerforationMdInterval == nullptr)
	{
		return false;
	}

	return perforationStatusHistory->PerforationMdInterval->MdBase != nullptr ||
		perforationStatusHistory->PerforationMdInterval->MdTop != nullptr;
}

eml21__LengthUom WellboreCompletion::getPerforationHistoryMdUnit(unsigned int historyIndex,
	unsigned int perforationIndex) const
{
	if (!hasPerforationHistoryMdUnit(historyIndex, perforationIndex))
	{
		throw invalid_argument("No perforation history entry md unit is defined.");
	}

	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);

	return perforationStatusHistory->PerforationMdInterval->MdBase != nullptr ? perforationStatusHistory->PerforationMdInterval->MdBase->uom : perforationStatusHistory->PerforationMdInterval->MdTop->uom;
}

string WellboreCompletion::getPerforationHistoryMdUnitAsString(unsigned int historyIndex,
	unsigned int perforationIndex) const
{
	return gsoap_eml2_1::soap_eml21__LengthUom2s(gsoapProxy2_1->soap, getPerforationHistoryMdUnit(historyIndex, perforationIndex));
}

bool WellboreCompletion::hasPerforationHistoryTopMd(unsigned int historyIndex,
	unsigned int perforationIndex) const
{
	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);
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

double WellboreCompletion::getPerforationHistoryTopMd(unsigned int historyIndex,
	unsigned int perforationIndex) const
{
	if (!hasPerforationHistoryTopMd(historyIndex, perforationIndex))
	{
		throw invalid_argument("No perforation history entry top md is defined.");
	}

	return getPerforationHistoryEntry(historyIndex, perforationIndex)->PerforationMdInterval->MdTop->__item;
}

void WellboreCompletion::setPerforationHistoryTopMd(unsigned int historyIndex,
	unsigned int perforationIndex,
	const std::string & datum,
	gsoap_eml2_1::eml21__LengthUom MdUnit,
	const double & TopMd)
{
	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);

	if (perforationStatusHistory->PerforationMdInterval == nullptr) {
		perforationStatusHistory->PerforationMdInterval = soap_new_eml21__MdInterval(gsoapProxy2_1->soap, 1);	
	}

	perforationStatusHistory->PerforationMdInterval->datum = datum;
	perforationStatusHistory->PerforationMdInterval->MdTop = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap, 1);
	perforationStatusHistory->PerforationMdInterval->MdTop->uom = MdUnit;
	perforationStatusHistory->PerforationMdInterval->MdTop->__item = TopMd;
}

bool WellboreCompletion::hasPerforationHistoryBaseMd(unsigned int historyIndex,
	unsigned int perforationIndex) const
{
	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);
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

double WellboreCompletion::getPerforationHistoryBaseMd(unsigned int historyIndex,
	unsigned int perforationIndex) const
{
	if (!hasPerforationHistoryBaseMd(historyIndex, perforationIndex))
	{
		throw invalid_argument("No perforation history entry base md is defined.");
	}

	return getPerforationHistoryEntry(historyIndex, perforationIndex)->PerforationMdInterval->MdBase->__item;
}

void WellboreCompletion::setPerforationHistoryBaseMd(unsigned int historyIndex,
	unsigned int perforationIndex,
	const std::string & datum,
	gsoap_eml2_1::eml21__LengthUom MdUnit,
	const double & BaseMd)
{
	witsml2__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, perforationIndex);

	if (perforationStatusHistory->PerforationMdInterval == nullptr) {
		perforationStatusHistory->PerforationMdInterval = soap_new_eml21__MdInterval(gsoapProxy2_1->soap, 1);
	}

	perforationStatusHistory->PerforationMdInterval->datum = datum;
	perforationStatusHistory->PerforationMdInterval->MdBase = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap, 1);
	perforationStatusHistory->PerforationMdInterval->MdBase->uom = MdUnit;
	perforationStatusHistory->PerforationMdInterval->MdBase->__item = BaseMd;
}

std::vector<epc::Relationship> WellboreCompletion::getAllTargetRelationships() const
{
	vector<Relationship> result = WellboreObject::getAllTargetRelationships();
	
	WellCompletion* wellCompletion = getWellCompletion();
	Relationship relWellCompletion(wellCompletion->getPartNameInEpcDocument(), "", wellCompletion->getUuid());
	relWellCompletion.setDestinationObjectType();
	result.push_back(relWellCompletion);

	return result;
}

void WellboreCompletion::resolveTargetRelationships(COMMON_NS::EpcDocument * epcDoc)
{
	WellboreObject::resolveTargetRelationships(epcDoc);

	gsoap_eml2_1::eml21__DataObjectReference* dor = getWellCompletionDor();
	WellCompletion* wellCompletion = epcDoc->getDataObjectByUuid<WellCompletion>(dor->Uuid);

	if (wellCompletion == nullptr) {
		throw invalid_argument("The DOR looks invalid.");
	}

	updateXml = false;
	setWellCompletion(wellCompletion);
	updateXml = true;
}

gsoap_eml2_1::witsml2__PerforationSetInterval* WellboreCompletion::getPerforation(unsigned int index) const
{
	witsml2__WellboreCompletion* wellboreCompletion = static_cast<witsml2__WellboreCompletion*>(gsoapProxy2_1);

	if (wellboreCompletion->ContactIntervalSet == nullptr)
	{
		throw invalid_argument("No contact interval exists.");
	}

	if (index >= wellboreCompletion->ContactIntervalSet->PerforationSetInterval.size())
	{
		throw invalid_argument("Perforation index out of range.");
	}

	return wellboreCompletion->ContactIntervalSet->PerforationSetInterval[index];
}

gsoap_eml2_1::witsml2__PerforationStatusHistory* WellboreCompletion::getPerforationHistoryEntry(unsigned int index,
	unsigned int perforationIndex) const
{
	witsml2__PerforationSetInterval* perforationSetInterval = getPerforation(perforationIndex);

	if (index >= perforationSetInterval->PerforationStatusHistory.size())
	{
		throw invalid_argument("History index out of range.");
	}

	return perforationSetInterval->PerforationStatusHistory[index];
}