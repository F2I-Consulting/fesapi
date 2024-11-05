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
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_3;

WellboreCompletion::WellboreCompletion(WITSML2_NS::Wellbore* witsmlWellbore,
	const string & guid,
	const string & title)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("A wellbore must be associated to a wellbore completion.");
	}

	gsoapProxy2_3 = soap_new_witsml21__WellboreCompletion(witsmlWellbore->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	witsmlWellbore->getRepository()->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
	setWellbore(witsmlWellbore);
}

COMMON_NS::DataObjectReference WellboreCompletion::getWellboreDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<witsml21__WellboreCompletion*>(gsoapProxy2_3)->ReferenceWellbore);
}

COMMON_NS::DataObjectReference WellboreCompletion::getWellCompletionDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<witsml21__WellboreCompletion*>(gsoapProxy2_3)->WellCompletion);
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

	static_cast<witsml21__WellboreCompletion*>(gsoapProxy2_3)->ReferenceWellbore = witsmlWellbore->newEml23Reference();

	getRepository()->addRelationship(this, witsmlWellbore);
}

void WellboreCompletion::setWellCompletion(WellCompletion* wellCompletion)
{
	if (wellCompletion == nullptr) {
		throw invalid_argument("Cannot set a null witsml well completion to a witsml wellbore completion");
	}

	// XML
	witsml21__WellboreCompletion* wellboreCompletion = static_cast<witsml21__WellboreCompletion*>(gsoapProxy2_3);
	wellboreCompletion->WellCompletion = wellCompletion->newEml23Reference();

	getRepository()->addRelationship(this, wellCompletion);
}

void WellboreCompletion::pushBackConnection(WellReservoirConnectionType wellReservoirConnection,
	eml23__LengthUom MdUnit,
	double TopMd,
	double BaseMd,
	const string & uid)
{
	witsml21__WellboreCompletion* wellboreCompletion = static_cast<witsml21__WellboreCompletion*>(gsoapProxy2_3);

	if (wellboreCompletion->ContactIntervalSet == nullptr) {
		wellboreCompletion->ContactIntervalSet = soap_new_witsml21__ContactIntervalSet(gsoapProxy2_3->soap);
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml21__PerforationSetInterval* perforationSetInterval = soap_new_witsml21__PerforationSetInterval(gsoapProxy2_3->soap);

		perforationSetInterval->uid = uid;

		perforationSetInterval->PerforationSetMdInterval = soap_new_eml23__MdInterval(gsoapProxy2_3->soap);
		perforationSetInterval->PerforationSetMdInterval->MdMin = TopMd;
		perforationSetInterval->PerforationSetMdInterval->MdMax = BaseMd;
		perforationSetInterval->PerforationSetMdInterval->Uom = soap_eml23__LengthUom2s(gsoapProxy2_3->soap, MdUnit);

		wellboreCompletion->ContactIntervalSet->PerforationSetInterval.push_back(perforationSetInterval);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		witsml21__GravelPackInterval* interval = soap_new_witsml21__GravelPackInterval(gsoapProxy2_3->soap);

		interval->uid = uid;

		interval->GravelPackMdInterval = soap_new_eml23__MdInterval(gsoapProxy2_3->soap);
		interval->GravelPackMdInterval->MdMin = TopMd;
		interval->GravelPackMdInterval->MdMax = BaseMd;
		interval->GravelPackMdInterval->Uom = soap_eml23__LengthUom2s(gsoapProxy2_3->soap, MdUnit);

		wellboreCompletion->ContactIntervalSet->GravelPackInterval.push_back(interval);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		witsml21__OpenHoleInterval* interval = soap_new_witsml21__OpenHoleInterval(gsoapProxy2_3->soap);

		interval->uid = uid;

		interval->OpenHoleMdInterval = soap_new_eml23__MdInterval(gsoapProxy2_3->soap);
		interval->OpenHoleMdInterval->MdMin = TopMd;
		interval->OpenHoleMdInterval->MdMax = BaseMd;
		interval->OpenHoleMdInterval->Uom = soap_eml23__LengthUom2s(gsoapProxy2_3->soap, MdUnit);

		wellboreCompletion->ContactIntervalSet->OpenHoleInterval.push_back(interval);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		witsml21__SlotsInterval* interval = soap_new_witsml21__SlotsInterval(gsoapProxy2_3->soap);

		interval->uid = uid;

		interval->SlottedMdInterval = soap_new_eml23__MdInterval(gsoapProxy2_3->soap);
		interval->SlottedMdInterval->MdMin = TopMd;
		interval->SlottedMdInterval->MdMax = BaseMd;
		interval->SlottedMdInterval->Uom = soap_eml23__LengthUom2s(gsoapProxy2_3->soap, MdUnit);

		wellboreCompletion->ContactIntervalSet->SlotsInterval.push_back(interval);
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

void WellboreCompletion::pushBackConnectionExtraMetadata(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex,
	const std::string & key, const std::string & value)
{

	gsoap_eml2_3::eml23__ExtensionNameValue* stringPair = gsoap_eml2_3::soap_new_eml23__ExtensionNameValue(gsoapProxy2_3->soap);
	stringPair->Name = key;
	stringPair->Value = gsoap_eml2_3::soap_new_eml23__StringMeasure(gsoapProxy2_3->soap);
	stringPair->Value->__item = value;

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml21__PerforationSetInterval* interval = getPerforation(connectionIndex);
		interval->ExtensionNameValue.push_back(stringPair);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		witsml21__GravelPackInterval* interval = getGravelPack(connectionIndex);
		interval->ExtensionNameValue.push_back(stringPair);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		witsml21__OpenHoleInterval* interval = getOpenHole(connectionIndex);
		interval->ExtensionNameValue.push_back(stringPair);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		witsml21__SlotsInterval* interval = getSlots(connectionIndex);
		interval->ExtensionNameValue.push_back(stringPair);
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

std::vector<std::string> WellboreCompletion::getConnectionExtraMetadata(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex, const std::string & key) const
{
	vector<string> result;

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		for (auto const* pair : getPerforation(connectionIndex)->ExtensionNameValue) {
			if (pair->Name == key) {
				result.push_back(pair->Value->__item);
			}
		}
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		for (auto const* pair : getGravelPack(connectionIndex)->ExtensionNameValue) {
			if (pair->Name == key) {
				result.push_back(pair->Value->__item);
			}
		}
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		for (auto const* pair : getOpenHole(connectionIndex)->ExtensionNameValue) {
			if (pair->Name == key) {
				result.push_back(pair->Value->__item);
			}
		}
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		for (auto const* pair : getSlots(connectionIndex)->ExtensionNameValue) {
			if (pair->Name == key) {
				result.push_back(pair->Value->__item);
			}
		}
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}

	return result;
}

void WellboreCompletion::pushBackConnectionHistory(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex,
	const std::string & guid)
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml21__PerforationStatusHistory* perforationStatusHistory = soap_new_witsml21__PerforationStatusHistory(gsoapProxy2_3->soap);
		perforationStatusHistory->uid = guid.empty()
			? std::to_string(getConnectionHistoryCount(wellReservoirConnection, connectionIndex))
			: guid;

		witsml21__PerforationSetInterval* interval = getPerforation(connectionIndex);
		interval->PerforationStatusHistory.push_back(perforationStatusHistory);
	}
	else {
		witsml21__IntervalStatusHistory* intervalStatusHistory = soap_new_witsml21__IntervalStatusHistory(gsoapProxy2_3->soap);
		intervalStatusHistory->uid = guid.empty()
			? std::to_string(getConnectionHistoryCount(wellReservoirConnection, connectionIndex))
			: guid;

		if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
			witsml21__GravelPackInterval* interval = getGravelPack(connectionIndex);
			interval->StatusHistory.push_back(intervalStatusHistory);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
			witsml21__OpenHoleInterval* interval = getOpenHole(connectionIndex);
			interval->StatusHistory.push_back(intervalStatusHistory);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
			witsml21__SlotsInterval* interval = getSlots(connectionIndex);
			interval->StatusHistory.push_back(intervalStatusHistory);
		}
		else {
			throw std::invalid_argument("This type of completion connection type is not supported");
		}
	}
}

void WellboreCompletion::pushBackConnectionHistory(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex,
	witsml21__PhysicalStatus perforationStatus,
	time_t startDate,
	const std::string & guid)
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml21__PerforationStatusHistory* perforationStatusHistory = soap_new_witsml21__PerforationStatusHistory(gsoapProxy2_3->soap);
		perforationStatusHistory->uid = guid.empty()
			? std::to_string(getConnectionHistoryCount(wellReservoirConnection, connectionIndex))
			: guid;
		perforationStatusHistory->PerforationStatus = soap_new_witsml21__PerforationStatus(gsoapProxy2_3->soap);
		if (perforationStatus == witsml21__PhysicalStatus::open) {
			*perforationStatusHistory->PerforationStatus = witsml21__PerforationStatus::open;
		}
		else if (perforationStatus == witsml21__PhysicalStatus::closed) {
			*perforationStatusHistory->PerforationStatus = witsml21__PerforationStatus::squeezed;
		}
		else if (perforationStatus == witsml21__PhysicalStatus::proposed) {
			*perforationStatusHistory->PerforationStatus = witsml21__PerforationStatus::proposed;
		}

		if (startDate != -1) {
			perforationStatusHistory->StartDate = soap_new_tm(gsoapProxy2_3->soap);
			*perforationStatusHistory->StartDate = timeTools::to_calendar_time(timeTools::from_time_t(startDate));
		}

		witsml21__PerforationSetInterval* interval = getPerforation(connectionIndex);
		interval->PerforationStatusHistory.push_back(perforationStatusHistory);
	}
	else {
		witsml21__IntervalStatusHistory* intervalStatusHistory = soap_new_witsml21__IntervalStatusHistory(gsoapProxy2_3->soap);
		intervalStatusHistory->uid = guid.empty()
			? std::to_string(getConnectionHistoryCount(wellReservoirConnection, connectionIndex))
			: guid;
		intervalStatusHistory->PhysicalStatus = soap_new_witsml21__PhysicalStatus(gsoapProxy2_3->soap);
		*intervalStatusHistory->PhysicalStatus = perforationStatus;

		if (startDate != -1) {
			intervalStatusHistory->StartDate = soap_new_tm(gsoapProxy2_3->soap);
			*intervalStatusHistory->StartDate = timeTools::to_calendar_time(timeTools::from_time_t(startDate));
		}

		if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
			witsml21__GravelPackInterval* interval = getGravelPack(connectionIndex);
			interval->StatusHistory.push_back(intervalStatusHistory);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
			witsml21__OpenHoleInterval* interval = getOpenHole(connectionIndex);
			interval->StatusHistory.push_back(intervalStatusHistory);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
			witsml21__SlotsInterval* interval = getSlots(connectionIndex);
			interval->StatusHistory.push_back(intervalStatusHistory);
		}
		else {
			throw std::invalid_argument("This type of completion connection type is not supported");
		}
	}
}

uint64_t WellboreCompletion::getConnectionCount(WellReservoirConnectionType wellReservoirConnection) const
{
	witsml21__WellboreCompletion* wellboreCompletion = static_cast<witsml21__WellboreCompletion*>(gsoapProxy2_3);

	if (wellboreCompletion->ContactIntervalSet == nullptr) {
		throw invalid_argument("No contact interval exists.");
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return wellboreCompletion->ContactIntervalSet->PerforationSetInterval.size();
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return wellboreCompletion->ContactIntervalSet->GravelPackInterval.size();
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return wellboreCompletion->ContactIntervalSet->OpenHoleInterval.size();
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return wellboreCompletion->ContactIntervalSet->SlotsInterval.size();
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

std::string WellboreCompletion::getConnectionUid(WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return getPerforation(index)->uid;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return getGravelPack(index)->uid;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return getOpenHole(index)->uid;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return getSlots(index)->uid;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

bool WellboreCompletion::hasConnectionMdDatum(WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return getPerforation(index)->PerforationSetMdInterval != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return getGravelPack(index)->GravelPackMdInterval != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return getOpenHole(index)->OpenHoleMdInterval != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return getSlots(index)->SlottedMdInterval != nullptr;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

bool WellboreCompletion::hasConnectionMdInterval(WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml21__PerforationSetInterval const * const interval = getPerforation(index);
		return interval->PerforationSetMdInterval != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		witsml21__GravelPackInterval const * const interval = getGravelPack(index);
		return interval->GravelPackMdInterval != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		witsml21__OpenHoleInterval const * const interval = getOpenHole(index);
		return interval->OpenHoleMdInterval != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		witsml21__SlotsInterval const * const interval = getSlots(index);
		return interval->SlottedMdInterval != nullptr;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

eml23__LengthUom WellboreCompletion::getConnectionMdUnit(WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionMdInterval(wellReservoirConnection, index)) {
		throw invalid_argument("No connection MD interval is defined.");
	}

	eml23__LengthUom result;
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml21__PerforationSetInterval const * const interval = getPerforation(index);
		soap_s2eml23__LengthUom(gsoapProxy2_3->soap, interval->PerforationSetMdInterval->Uom.c_str(), &result);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		witsml21__GravelPackInterval const * const interval = getGravelPack(index);
		soap_s2eml23__LengthUom(gsoapProxy2_3->soap, interval->GravelPackMdInterval->Uom.c_str(), &result);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		witsml21__OpenHoleInterval const * const interval = getOpenHole(index);
		soap_s2eml23__LengthUom(gsoapProxy2_3->soap, interval->OpenHoleMdInterval->Uom.c_str(), &result);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		witsml21__SlotsInterval const * const interval = getSlots(index);
		soap_s2eml23__LengthUom(gsoapProxy2_3->soap, interval->SlottedMdInterval->Uom.c_str(), &result);
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}

	return result;
}

string WellboreCompletion::getConnectionMdUnitAsString(WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	return gsoap_eml2_3::soap_eml23__LengthUom2s(gsoapProxy2_3->soap, getConnectionMdUnit(wellReservoirConnection, index));
}

double WellboreCompletion::getConnectionTopMd(WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionMdInterval(wellReservoirConnection, index)) {
		throw invalid_argument("No connection MD interval is defined.");
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return getPerforation(index)->PerforationSetMdInterval->MdMin;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return getGravelPack(index)->GravelPackMdInterval->MdMin;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return getOpenHole(index)->OpenHoleMdInterval->MdMin;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return getSlots(index)->SlottedMdInterval->MdMin;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

double WellboreCompletion::getConnectionBaseMd(WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionMdInterval(wellReservoirConnection, index)) {
		throw invalid_argument("No connection MD interval is defined.");
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return getPerforation(index)->PerforationSetMdInterval->MdMax;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return getGravelPack(index)->GravelPackMdInterval->MdMax;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return getOpenHole(index)->OpenHoleMdInterval->MdMax;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return getSlots(index)->SlottedMdInterval->MdMax;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

uint64_t WellboreCompletion::getConnectionHistoryCount(WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return getPerforation(index)->PerforationStatusHistory.size();
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return getGravelPack(index)->StatusHistory.size();
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return getOpenHole(index)->StatusHistory.size();
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return getSlots(index)->StatusHistory.size();
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

bool WellboreCompletion::hasConnectionHistoryStatus(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return getPerforationHistoryEntry(historyIndex, index)->PerforationStatus != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return getGravelPackHistoryEntry(historyIndex, index)->PhysicalStatus != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return getOpenHoleHistoryEntry(historyIndex, index)->PhysicalStatus != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return getSlotsHistoryEntry(historyIndex, index)->PhysicalStatus != nullptr;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

gsoap_eml2_3::witsml21__PhysicalStatus WellboreCompletion::getConnectionHistoryStatus(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionHistoryStatus(historyIndex, wellReservoirConnection, index)) {
		throw invalid_argument("No perforation history entry is defined.");
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		auto perfoStatus = *getPerforationHistoryEntry(historyIndex, index)->PerforationStatus;
		if (perfoStatus == gsoap_eml2_3::witsml21__PerforationStatus::open) {
			return gsoap_eml2_3::witsml21__PhysicalStatus::open;
		}
		else if (perfoStatus == gsoap_eml2_3::witsml21__PerforationStatus::proposed) {
			return gsoap_eml2_3::witsml21__PhysicalStatus::proposed;
		}
		else { //if (perfoStatus == gsoap_eml2_3::witsml21__PerforationStatus::squeezed)
			return gsoap_eml2_3::witsml21__PhysicalStatus::closed;
		}
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return *getGravelPackHistoryEntry(historyIndex, index)->PhysicalStatus;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return *getOpenHoleHistoryEntry(historyIndex, index)->PhysicalStatus;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return *getSlotsHistoryEntry(historyIndex, index)->PhysicalStatus;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

string WellboreCompletion::getConnectionHistoryStatusToString(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	return gsoap_eml2_3::soap_witsml21__PhysicalStatus2s(gsoapProxy2_3->soap, getConnectionHistoryStatus(historyIndex, wellReservoirConnection, index));
}

void WellboreCompletion::setConnectionHistoryStatus(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index,
	gsoap_eml2_3::witsml21__PhysicalStatus status)
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml21__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		if (perforationStatusHistory->PerforationStatus == nullptr) {
			perforationStatusHistory->PerforationStatus = soap_new_witsml21__PerforationStatus(gsoapProxy2_3->soap);
		}
		if (status == gsoap_eml2_3::witsml21__PhysicalStatus::open) {
			*perforationStatusHistory->PerforationStatus = gsoap_eml2_3::witsml21__PerforationStatus::open;
		}
		else if (status == gsoap_eml2_3::witsml21__PhysicalStatus::proposed) {
			*perforationStatusHistory->PerforationStatus = gsoap_eml2_3::witsml21__PerforationStatus::proposed;
		}
		else { //if (status == gsoap_eml2_3::witsml21__PhysicalStatus::closed)
			*perforationStatusHistory->PerforationStatus = gsoap_eml2_3::witsml21__PerforationStatus::squeezed;
		}
	}
	else {
		witsml21__IntervalStatusHistory* statusHistory;
		if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
			statusHistory = getGravelPackHistoryEntry(historyIndex, index);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
			statusHistory = getOpenHoleHistoryEntry(historyIndex, index);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
			statusHistory = getSlotsHistoryEntry(historyIndex, index);
		}
		else {
			throw std::invalid_argument("This type of completion connection type is not supported");
		}

		if (statusHistory->PhysicalStatus == nullptr) {
			statusHistory->PhysicalStatus = soap_new_witsml21__PhysicalStatus(gsoapProxy2_3->soap);
		}
		*statusHistory->PhysicalStatus = status;
	}
}

bool WellboreCompletion::hasConnectionHistoryStartDate(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return getPerforationHistoryEntry(historyIndex, index)->StartDate != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return getGravelPackHistoryEntry(historyIndex, index)->StartDate != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return getOpenHoleHistoryEntry(historyIndex, index)->StartDate != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return getSlotsHistoryEntry(historyIndex, index)->StartDate != nullptr;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

time_t WellboreCompletion::getConnectionHistoryStartDate(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionHistoryStartDate(historyIndex, wellReservoirConnection, index)) {
		throw invalid_argument("No perforation history entry start date is defined.");
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return timeTools::timegm(*getPerforationHistoryEntry(historyIndex, index)->StartDate);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return timeTools::timegm(*getGravelPackHistoryEntry(historyIndex, index)->StartDate);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return timeTools::timegm(*getOpenHoleHistoryEntry(historyIndex, index)->StartDate);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return timeTools::timegm(*getSlotsHistoryEntry(historyIndex, index)->StartDate);
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

void WellboreCompletion::setConnectionHistoryStartDate(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index, time_t startDate) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml21__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		if (perforationStatusHistory->StartDate == nullptr) {
			perforationStatusHistory->StartDate = soap_new_tm(gsoapProxy2_3->soap);
		}
		*perforationStatusHistory->StartDate = timeTools::to_calendar_time(timeTools::from_time_t(startDate));
	}
	else {
		witsml21__IntervalStatusHistory* statusHistory;
		if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
			statusHistory = getGravelPackHistoryEntry(historyIndex, index);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
			statusHistory = getOpenHoleHistoryEntry(historyIndex, index);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
			statusHistory = getSlotsHistoryEntry(historyIndex, index);
		}
		else {
			throw std::invalid_argument("This type of completion connection type is not supported");
		}

		if (statusHistory->StartDate == nullptr) {
			statusHistory->StartDate = soap_new_tm(gsoapProxy2_3->soap);
		}
		*statusHistory->StartDate = timeTools::to_calendar_time(timeTools::from_time_t(startDate));
	}
}

bool WellboreCompletion::hasConnectionHistoryEndDate(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return getPerforationHistoryEntry(historyIndex, index)->EndDate != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return getGravelPackHistoryEntry(historyIndex, index)->EndDate != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return getOpenHoleHistoryEntry(historyIndex, index)->EndDate != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return getSlotsHistoryEntry(historyIndex, index)->EndDate != nullptr;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

time_t WellboreCompletion::getConnectionHistoryEndDate(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionHistoryEndDate(historyIndex, wellReservoirConnection, index)) {
		throw invalid_argument("No perforation history entry end date is defined.");
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return timeTools::timegm(*getPerforationHistoryEntry(historyIndex, index)->EndDate);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return timeTools::timegm(*getGravelPackHistoryEntry(historyIndex, index)->EndDate);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return timeTools::timegm(*getOpenHoleHistoryEntry(historyIndex, index)->EndDate);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return timeTools::timegm(*getSlotsHistoryEntry(historyIndex, index)->EndDate);
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

void WellboreCompletion::setConnectionHistoryEndDate(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index, time_t endDate) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml21__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		if (perforationStatusHistory->EndDate == nullptr) {
			perforationStatusHistory->EndDate = soap_new_tm(gsoapProxy2_3->soap);
		}
		*perforationStatusHistory->EndDate = timeTools::to_calendar_time(timeTools::from_time_t(endDate));
	}
	else {
		witsml21__IntervalStatusHistory* statusHistory;
		if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
			statusHistory = getGravelPackHistoryEntry(historyIndex, index);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
			statusHistory = getOpenHoleHistoryEntry(historyIndex, index);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
			statusHistory = getSlotsHistoryEntry(historyIndex, index);
		}
		else {
			throw std::invalid_argument("This type of completion connection type is not supported");
		}

		if (statusHistory->EndDate == nullptr) {
			statusHistory->EndDate = soap_new_tm(gsoapProxy2_3->soap);
		}
		*statusHistory->StartDate = timeTools::to_calendar_time(timeTools::from_time_t(endDate));
	}
}

bool WellboreCompletion::hasConnectionHistoryMdDatum(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return getPerforationHistoryEntry(historyIndex, index)->PerforationMdInterval != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return getGravelPackHistoryEntry(historyIndex, index)->StatusMdInterval != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return getOpenHoleHistoryEntry(historyIndex, index)->StatusMdInterval != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return getSlotsHistoryEntry(historyIndex, index)->StatusMdInterval != nullptr;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

bool WellboreCompletion::hasConnectionHistoryMdInterval(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml21__PerforationStatusHistory const * const perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		return perforationStatusHistory->PerforationMdInterval != nullptr;
	}
	else {
		witsml21__IntervalStatusHistory const* statusHistory;
		if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
			statusHistory = getGravelPackHistoryEntry(historyIndex, index);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
			statusHistory = getOpenHoleHistoryEntry(historyIndex, index);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
			statusHistory = getSlotsHistoryEntry(historyIndex, index);
		}
		else {
			throw std::invalid_argument("This type of completion connection type is not supported");
		}
		return statusHistory->StatusMdInterval != nullptr;
	}
}

eml23__LengthUom WellboreCompletion::getConnectionHistoryMdUnit(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionHistoryMdInterval(historyIndex, wellReservoirConnection, index)) {
		throw invalid_argument("No perforation history entry md interval is defined.");
	}

	eml23__LengthUom result;
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml21__PerforationStatusHistory const * const perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		soap_s2eml23__LengthUom(gsoapProxy2_3->soap, perforationStatusHistory->PerforationMdInterval->Uom.c_str(), &result);
	}
	else {
		witsml21__IntervalStatusHistory const* statusHistory;
		if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
			statusHistory = getGravelPackHistoryEntry(historyIndex, index);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
			statusHistory = getOpenHoleHistoryEntry(historyIndex, index);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
			statusHistory = getSlotsHistoryEntry(historyIndex, index);
		}
		else {
			throw std::invalid_argument("This type of completion connection type is not supported");
		}
		soap_s2eml23__LengthUom(gsoapProxy2_3->soap, statusHistory->StatusMdInterval->Uom.c_str(), &result);
	}

	return result;
}

string WellboreCompletion::getConnectionHistoryMdUnitAsString(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	return gsoap_eml2_3::soap_eml23__LengthUom2s(gsoapProxy2_3->soap, getConnectionHistoryMdUnit(historyIndex, wellReservoirConnection, index));
}

double WellboreCompletion::getConnectionHistoryTopMd(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionHistoryMdInterval(historyIndex, wellReservoirConnection, index)) {
		throw invalid_argument("No perforation history entry md interval is defined.");
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return getPerforationHistoryEntry(historyIndex, index)->PerforationMdInterval->MdMin;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return getGravelPackHistoryEntry(historyIndex, index)->StatusMdInterval->MdMin;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return getOpenHoleHistoryEntry(historyIndex, index)->StatusMdInterval->MdMin;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return getSlotsHistoryEntry(historyIndex, index)->StatusMdInterval->MdMin;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

void WellboreCompletion::setConnectionHistoryMdInterval(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index,
	gsoap_eml2_3::eml23__LengthUom MdUnit,
	double TopMd, double BaseMd)
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml21__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		if (perforationStatusHistory->PerforationMdInterval == nullptr) {
			perforationStatusHistory->PerforationMdInterval = soap_new_eml23__MdInterval(gsoapProxy2_3->soap);
		}
		perforationStatusHistory->PerforationMdInterval->MdMin = TopMd;
		perforationStatusHistory->PerforationMdInterval->MdMax = BaseMd;
		perforationStatusHistory->PerforationMdInterval->Uom = soap_eml23__LengthUom2s(gsoapProxy2_3->soap, MdUnit);
	}
	else {
		witsml21__IntervalStatusHistory* statusHistory;
		if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
			statusHistory = getGravelPackHistoryEntry(historyIndex, index);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
			statusHistory = getOpenHoleHistoryEntry(historyIndex, index);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
			statusHistory = getSlotsHistoryEntry(historyIndex, index);
		}
		else {
			throw std::invalid_argument("This type of completion connection type is not supported");
		}

		if (statusHistory->StatusMdInterval == nullptr) {
			statusHistory->StatusMdInterval = soap_new_eml23__MdInterval(gsoapProxy2_3->soap);
		}
		statusHistory->StatusMdInterval->MdMin = TopMd;
		statusHistory->StatusMdInterval->MdMax = BaseMd;
		statusHistory->StatusMdInterval->Uom = soap_eml23__LengthUom2s(gsoapProxy2_3->soap, MdUnit);
	}
}

double WellboreCompletion::getConnectionHistoryBaseMd(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionHistoryMdInterval(historyIndex, wellReservoirConnection, index)) {
		throw invalid_argument("No perforation history entry md interval is defined.");
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return getPerforationHistoryEntry(historyIndex, index)->PerforationMdInterval->MdMax;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return getGravelPackHistoryEntry(historyIndex, index)->StatusMdInterval->MdMax;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return getOpenHoleHistoryEntry(historyIndex, index)->StatusMdInterval->MdMax;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return getSlotsHistoryEntry(historyIndex, index)->StatusMdInterval->MdMax;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

bool WellboreCompletion::hasConnectionHistoryComment(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml21__PerforationStatusHistory const * const perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		if (perforationStatusHistory == nullptr) {
			return false;
		}
		return perforationStatusHistory->Comment != nullptr;
	}
	else {
		witsml21__IntervalStatusHistory const* statusHistory;
		if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
			statusHistory = getGravelPackHistoryEntry(historyIndex, index);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
			statusHistory = getOpenHoleHistoryEntry(historyIndex, index);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
			statusHistory = getSlotsHistoryEntry(historyIndex, index);
		}
		else {
			throw std::invalid_argument("This type of completion connection type is not supported");
		}
		if (statusHistory == nullptr) {
			return false;
		}
		return statusHistory->Comment != nullptr;
	}
}

std::string WellboreCompletion::getConnectionHistoryComment(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionHistoryComment(historyIndex, wellReservoirConnection, index)) {
		throw invalid_argument("No perforation history comment is defined.");
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return *getPerforationHistoryEntry(historyIndex, index)->Comment;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return *getGravelPackHistoryEntry(historyIndex, index)->Comment;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return *getOpenHoleHistoryEntry(historyIndex, index)->Comment;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return *getSlotsHistoryEntry(historyIndex, index)->Comment;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

void WellboreCompletion::setConnectionHistoryComment(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index,
	const std::string & comment)
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml21__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		if (perforationStatusHistory->Comment == nullptr) {
			perforationStatusHistory->Comment = soap_new_std__string(gsoapProxy2_3->soap, 1);
		}
		perforationStatusHistory->Comment->assign(comment);
	}
	else {
		witsml21__IntervalStatusHistory* statusHistory;
		if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
			statusHistory = getGravelPackHistoryEntry(historyIndex, index);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
			statusHistory = getOpenHoleHistoryEntry(historyIndex, index);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
			statusHistory = getSlotsHistoryEntry(historyIndex, index);
		}
		else {
			throw std::invalid_argument("This type of completion connection type is not supported");
		}

		if (statusHistory->Comment == nullptr) {
			statusHistory->Comment = soap_new_std__string(gsoapProxy2_3->soap, 1);
		}
		statusHistory->Comment->assign(comment);
	}
}

void WellboreCompletion::loadTargetRelationships()
{
	WellboreObject::loadTargetRelationships();

	auto dor = getWellCompletionDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<WellCompletion>(getWellCompletionDor());
	}
}

gsoap_eml2_3::witsml21__PerforationSetInterval* WellboreCompletion::getPerforation(uint64_t index) const
{
	witsml21__WellboreCompletion const * const wellboreCompletion = static_cast<witsml21__WellboreCompletion*>(gsoapProxy2_3);

	if (wellboreCompletion->ContactIntervalSet == nullptr) {
		throw invalid_argument("No contact interval exists.");
	}

	return wellboreCompletion->ContactIntervalSet->PerforationSetInterval.at(index);
}

gsoap_eml2_3::witsml21__GravelPackInterval* WellboreCompletion::getGravelPack(uint64_t index) const
{
	witsml21__WellboreCompletion const * const wellboreCompletion = static_cast<witsml21__WellboreCompletion*>(gsoapProxy2_3);

	if (wellboreCompletion->ContactIntervalSet == nullptr) {
		throw invalid_argument("No contact interval exists.");
	}

	return wellboreCompletion->ContactIntervalSet->GravelPackInterval.at(index);
}
gsoap_eml2_3::witsml21__OpenHoleInterval* WellboreCompletion::getOpenHole(uint64_t index) const
{
	witsml21__WellboreCompletion const * const wellboreCompletion = static_cast<witsml21__WellboreCompletion*>(gsoapProxy2_3);

	if (wellboreCompletion->ContactIntervalSet == nullptr) {
		throw invalid_argument("No contact interval exists.");
	}

	return wellboreCompletion->ContactIntervalSet->OpenHoleInterval.at(index);
}

gsoap_eml2_3::witsml21__SlotsInterval* WellboreCompletion::getSlots(uint64_t index) const
{
	witsml21__WellboreCompletion const * const wellboreCompletion = static_cast<witsml21__WellboreCompletion*>(gsoapProxy2_3);

	if (wellboreCompletion->ContactIntervalSet == nullptr) {
		throw invalid_argument("No contact interval exists.");
	}

	return wellboreCompletion->ContactIntervalSet->SlotsInterval.at(index);
}
