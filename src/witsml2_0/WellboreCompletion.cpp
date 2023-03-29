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

void WellboreCompletion::pushBackConnection(WellReservoirConnectionType wellReservoirConnection, const string & datum,
	eml21__LengthUom MdUnit,
	double TopMd,
	double BaseMd,
	const string & uid)
{
	witsml20__WellboreCompletion* wellboreCompletion = static_cast<witsml20__WellboreCompletion*>(gsoapProxy2_1);

	if (wellboreCompletion->ContactIntervalSet == nullptr) {
		wellboreCompletion->ContactIntervalSet = soap_new_witsml20__ContactIntervalSet(gsoapProxy2_1->soap);
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml20__PerforationSetInterval* perforationSetInterval = soap_new_witsml20__PerforationSetInterval(gsoapProxy2_1->soap);

		perforationSetInterval->uid = uid;

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
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		witsml20__GravelPackInterval* interval = soap_new_witsml20__GravelPackInterval(gsoapProxy2_1->soap);

		interval->uid = uid;

		interval->GravelPackMdInterval = soap_new_eml21__MdInterval(gsoapProxy2_1->soap);
		interval->GravelPackMdInterval->datum = datum;
		interval->GravelPackMdInterval->MdTop = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
		interval->GravelPackMdInterval->MdTop->uom = MdUnit;
		interval->GravelPackMdInterval->MdTop->__item = TopMd;
		interval->GravelPackMdInterval->MdBase = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
		interval->GravelPackMdInterval->MdBase->uom = MdUnit;
		interval->GravelPackMdInterval->MdBase->__item = BaseMd;

		wellboreCompletion->ContactIntervalSet->GravelPackInterval.push_back(interval);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		witsml20__OpenHoleInterval* interval = soap_new_witsml20__OpenHoleInterval(gsoapProxy2_1->soap);

		interval->uid = uid;

		interval->OpenHoleMdInterval = soap_new_eml21__MdInterval(gsoapProxy2_1->soap);
		interval->OpenHoleMdInterval->datum = datum;
		interval->OpenHoleMdInterval->MdTop = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
		interval->OpenHoleMdInterval->MdTop->uom = MdUnit;
		interval->OpenHoleMdInterval->MdTop->__item = TopMd;
		interval->OpenHoleMdInterval->MdBase = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
		interval->OpenHoleMdInterval->MdBase->uom = MdUnit;
		interval->OpenHoleMdInterval->MdBase->__item = BaseMd;

		wellboreCompletion->ContactIntervalSet->OpenHoleInterval.push_back(interval);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		witsml20__SlotsInterval* interval = soap_new_witsml20__SlotsInterval(gsoapProxy2_1->soap);

		interval->uid = uid;

		interval->SlottedMdInterval = soap_new_eml21__MdInterval(gsoapProxy2_1->soap);
		interval->SlottedMdInterval->datum = datum;
		interval->SlottedMdInterval->MdTop = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
		interval->SlottedMdInterval->MdTop->uom = MdUnit;
		interval->SlottedMdInterval->MdTop->__item = TopMd;
		interval->SlottedMdInterval->MdBase = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
		interval->SlottedMdInterval->MdBase->uom = MdUnit;
		interval->SlottedMdInterval->MdBase->__item = BaseMd;

		wellboreCompletion->ContactIntervalSet->SlotsInterval.push_back(interval);
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

void WellboreCompletion::pushBackConnectionExtraMetadata(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex,
	const std::string & key, const std::string & value)
{

	gsoap_eml2_1::eml21__ExtensionNameValue* stringPair = gsoap_eml2_1::soap_new_eml21__ExtensionNameValue(gsoapProxy2_1->soap);
	stringPair->Name = key;
	stringPair->Value = gsoap_eml2_1::soap_new_eml21__StringMeasure(gsoapProxy2_1->soap);
	stringPair->Value->__item = value;

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml20__PerforationSetInterval* interval = getPerforation(connectionIndex);
		interval->ExtensionNameValue.push_back(stringPair);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		witsml20__GravelPackInterval* interval = getGravelPack(connectionIndex);
		interval->ExtensionNameValue.push_back(stringPair);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		witsml20__OpenHoleInterval* interval = getOpenHole(connectionIndex);
		interval->ExtensionNameValue.push_back(stringPair);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		witsml20__SlotsInterval* interval = getSlots(connectionIndex);
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
		witsml20__PerforationStatusHistory* perforationStatusHistory = soap_new_witsml20__PerforationStatusHistory(gsoapProxy2_1->soap);
		perforationStatusHistory->uid = guid.empty()
			? std::to_string(getConnectionHistoryCount(wellReservoirConnection, connectionIndex))
			: guid;

		witsml20__PerforationSetInterval* interval = getPerforation(connectionIndex);
		interval->PerforationStatusHistory.push_back(perforationStatusHistory);
	}
	else {
		witsml20__IntervalStatusHistory* intervalStatusHistory = soap_new_witsml20__IntervalStatusHistory(gsoapProxy2_1->soap);
		intervalStatusHistory->uid = guid.empty()
			? std::to_string(getConnectionHistoryCount(wellReservoirConnection, connectionIndex))
			: guid;

		if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
			witsml20__GravelPackInterval* interval = getGravelPack(connectionIndex);
			interval->StatusHistory.push_back(intervalStatusHistory);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
			witsml20__OpenHoleInterval* interval = getOpenHole(connectionIndex);
			interval->StatusHistory.push_back(intervalStatusHistory);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
			witsml20__SlotsInterval* interval = getSlots(connectionIndex);
			interval->StatusHistory.push_back(intervalStatusHistory);
		}
		else {
			throw std::invalid_argument("This type of completion connection type is not supported");
		}
	}
}

void WellboreCompletion::pushBackConnectionHistory(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex,
	witsml20__PhysicalStatus perforationStatus,
	time_t startDate,
	const std::string & guid)
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml20__PerforationStatusHistory* perforationStatusHistory = soap_new_witsml20__PerforationStatusHistory(gsoapProxy2_1->soap);
		perforationStatusHistory->uid = guid.empty()
			? std::to_string(getConnectionHistoryCount(wellReservoirConnection, connectionIndex))
			: guid;
		perforationStatusHistory->PerforationStatus = soap_new_witsml20__PerforationStatus(gsoapProxy2_1->soap);
		if (perforationStatus == witsml20__PhysicalStatus::open) {
			*perforationStatusHistory->PerforationStatus = witsml20__PerforationStatus::open;
		}
		else if (perforationStatus == witsml20__PhysicalStatus::closed) {
			*perforationStatusHistory->PerforationStatus = witsml20__PerforationStatus::squeezed;
		}
		else if (perforationStatus == witsml20__PhysicalStatus::proposed) {
			*perforationStatusHistory->PerforationStatus = witsml20__PerforationStatus::proposed;
		}

		if (startDate != -1) {
			perforationStatusHistory->StartDate = soap_new_std__string(gsoapProxy2_1->soap);
			perforationStatusHistory->StartDate->assign(timeTools::convertUnixTimestampToIso(startDate));
		}

		witsml20__PerforationSetInterval* interval = getPerforation(connectionIndex);
		interval->PerforationStatusHistory.push_back(perforationStatusHistory);
	}
	else {
		witsml20__IntervalStatusHistory* intervalStatusHistory = soap_new_witsml20__IntervalStatusHistory(gsoapProxy2_1->soap);
		intervalStatusHistory->uid = guid.empty()
			? std::to_string(getConnectionHistoryCount(wellReservoirConnection, connectionIndex))
			: guid;
		intervalStatusHistory->PhysicalStatus = soap_new_witsml20__PhysicalStatus(gsoapProxy2_1->soap);
		*intervalStatusHistory->PhysicalStatus = perforationStatus;

		if (startDate != -1) {
			intervalStatusHistory->StartDate = soap_new_std__string(gsoapProxy2_1->soap);
			intervalStatusHistory->StartDate->assign(timeTools::convertUnixTimestampToIso(startDate));
		}

		if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
			witsml20__GravelPackInterval* interval = getGravelPack(connectionIndex);
			interval->StatusHistory.push_back(intervalStatusHistory);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
			witsml20__OpenHoleInterval* interval = getOpenHole(connectionIndex);
			interval->StatusHistory.push_back(intervalStatusHistory);
		}
		else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
			witsml20__SlotsInterval* interval = getSlots(connectionIndex);
			interval->StatusHistory.push_back(intervalStatusHistory);
		}
		else {
			throw std::invalid_argument("This type of completion connection type is not supported");
		}
	}
}

uint64_t WellboreCompletion::getConnectionCount(WellReservoirConnectionType wellReservoirConnection) const
{
	witsml20__WellboreCompletion* wellboreCompletion = static_cast<witsml20__WellboreCompletion*>(gsoapProxy2_1);

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

string WellboreCompletion::getConnectionMdDatum(WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionMdDatum(wellReservoirConnection, index)) {
		throw invalid_argument("No connection md datum is defined.");
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return getPerforation(index)->PerforationSetMdInterval->datum;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return getGravelPack(index)->GravelPackMdInterval->datum;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return getOpenHole(index)->OpenHoleMdInterval->datum;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return getSlots(index)->SlottedMdInterval->datum;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

bool WellboreCompletion::hasConnectionMdUnit(WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml20__PerforationSetInterval const * const interval = getPerforation(index);
		return interval->PerforationSetMdInterval == nullptr
			? false
			: interval->PerforationSetMdInterval->MdBase != nullptr || interval->PerforationSetMdInterval->MdTop != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		witsml20__GravelPackInterval const * const interval = getGravelPack(index);
		return interval->GravelPackMdInterval == nullptr
			? false
			: interval->GravelPackMdInterval->MdBase != nullptr || interval->GravelPackMdInterval->MdTop != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		witsml20__OpenHoleInterval const * const interval = getOpenHole(index);
		return interval->OpenHoleMdInterval == nullptr
			? false
			: interval->OpenHoleMdInterval->MdBase != nullptr || interval->OpenHoleMdInterval->MdTop != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		witsml20__SlotsInterval const * const interval = getSlots(index);
		return interval->SlottedMdInterval == nullptr
			? false
			: interval->SlottedMdInterval->MdBase != nullptr || interval->SlottedMdInterval->MdTop != nullptr;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

eml21__LengthUom WellboreCompletion::getConnectionMdUnit(WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionMdUnit(wellReservoirConnection, index)) {
		throw invalid_argument("No connection md unit is defined.");
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml20__PerforationSetInterval const * const interval = getPerforation(index);
		return interval->PerforationSetMdInterval->MdBase != nullptr
			? interval->PerforationSetMdInterval->MdBase->uom
			: interval->PerforationSetMdInterval->MdTop->uom;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		witsml20__GravelPackInterval const * const interval = getGravelPack(index);
		return interval->GravelPackMdInterval->MdBase != nullptr
			? interval->GravelPackMdInterval->MdBase->uom
			: interval->GravelPackMdInterval->MdTop->uom;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		witsml20__OpenHoleInterval const * const interval = getOpenHole(index);
		return interval->OpenHoleMdInterval->MdBase != nullptr
			? interval->OpenHoleMdInterval->MdBase->uom
			: interval->OpenHoleMdInterval->MdTop->uom;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		witsml20__SlotsInterval const * const interval = getSlots(index);
		return interval->SlottedMdInterval->MdBase != nullptr
			? interval->SlottedMdInterval->MdBase->uom
			: interval->SlottedMdInterval->MdTop->uom;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

string WellboreCompletion::getConnectionMdUnitAsString(WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	return gsoap_eml2_1::soap_eml21__LengthUom2s(gsoapProxy2_1->soap, getConnectionMdUnit(wellReservoirConnection, index));
}

bool WellboreCompletion::hasConnectionTopMd(WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml20__PerforationSetInterval const * const interval = getPerforation(index);
		return interval->PerforationSetMdInterval == nullptr
			? false
			: interval->PerforationSetMdInterval->MdTop != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		witsml20__GravelPackInterval const * const interval = getGravelPack(index);
		return interval->GravelPackMdInterval == nullptr
			? false
			: interval->GravelPackMdInterval->MdTop != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		witsml20__OpenHoleInterval const * const interval = getOpenHole(index);
		return interval->OpenHoleMdInterval == nullptr
			? false
			: interval->OpenHoleMdInterval->MdTop != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		witsml20__SlotsInterval const * const interval = getSlots(index);
		return interval->SlottedMdInterval == nullptr
			? false
			: interval->SlottedMdInterval->MdTop != nullptr;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

double WellboreCompletion::getConnectionTopMd(WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionTopMd(wellReservoirConnection, index)) {
		throw invalid_argument("No perforation top md is defined.");
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return getPerforation(index)->PerforationSetMdInterval->MdTop->__item;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return getGravelPack(index)->GravelPackMdInterval->MdTop->__item;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return getOpenHole(index)->OpenHoleMdInterval->MdTop->__item;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return getSlots(index)->SlottedMdInterval->MdTop->__item;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

bool WellboreCompletion::hasConnectionBaseMd(WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml20__PerforationSetInterval const * const interval = getPerforation(index);
		return interval->PerforationSetMdInterval == nullptr
			? false
			: interval->PerforationSetMdInterval->MdBase != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		witsml20__GravelPackInterval const * const interval = getGravelPack(index);
		return interval->GravelPackMdInterval == nullptr
			? false
			: interval->GravelPackMdInterval->MdBase != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		witsml20__OpenHoleInterval const * const interval = getOpenHole(index);
		return interval->OpenHoleMdInterval == nullptr
			? false
			: interval->OpenHoleMdInterval->MdBase != nullptr;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		witsml20__SlotsInterval const * const interval = getSlots(index);
		return interval->SlottedMdInterval == nullptr
			? false
			: interval->SlottedMdInterval->MdBase != nullptr;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

double WellboreCompletion::getConnectionBaseMd(WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionBaseMd(wellReservoirConnection, index)) {
		throw invalid_argument("No perforation base md is defined.");
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return getPerforation(index)->PerforationSetMdInterval->MdBase->__item;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return getGravelPack(index)->GravelPackMdInterval->MdBase->__item;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return getOpenHole(index)->OpenHoleMdInterval->MdBase->__item;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return getSlots(index)->SlottedMdInterval->MdBase->__item;
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

gsoap_eml2_1::witsml20__PhysicalStatus WellboreCompletion::getConnectionHistoryStatus(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionHistoryStatus(historyIndex, wellReservoirConnection, index)) {
		throw invalid_argument("No perforation history entry is defined.");
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		auto perfoStatus = *getPerforationHistoryEntry(historyIndex, index)->PerforationStatus;
		if (perfoStatus == gsoap_eml2_1::witsml20__PerforationStatus::open) {
			return gsoap_eml2_1::witsml20__PhysicalStatus::open;
		}
		else if (perfoStatus == gsoap_eml2_1::witsml20__PerforationStatus::proposed) {
			return gsoap_eml2_1::witsml20__PhysicalStatus::proposed;
		}
		else { //if (perfoStatus == gsoap_eml2_1::witsml20__PerforationStatus::squeezed)
			return gsoap_eml2_1::witsml20__PhysicalStatus::closed;
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
	return gsoap_eml2_1::soap_witsml20__PhysicalStatus2s(gsoapProxy2_1->soap, getConnectionHistoryStatus(historyIndex, wellReservoirConnection, index));
}

void WellboreCompletion::setConnectionHistoryStatus(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index,
	gsoap_eml2_1::witsml20__PhysicalStatus status)
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml20__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		if (perforationStatusHistory->PerforationStatus == nullptr) {
			perforationStatusHistory->PerforationStatus = soap_new_witsml20__PerforationStatus(gsoapProxy2_1->soap);
		}
		if (status == gsoap_eml2_1::witsml20__PhysicalStatus::open) {
			*perforationStatusHistory->PerforationStatus = gsoap_eml2_1::witsml20__PerforationStatus::open;
		}
		else if (status == gsoap_eml2_1::witsml20__PhysicalStatus::proposed) {
			*perforationStatusHistory->PerforationStatus = gsoap_eml2_1::witsml20__PerforationStatus::proposed;
		}
		else { //if (status == gsoap_eml2_1::witsml20__PhysicalStatus::closed)
			*perforationStatusHistory->PerforationStatus = gsoap_eml2_1::witsml20__PerforationStatus::squeezed;
		}
	}
	else {
		witsml20__IntervalStatusHistory* statusHistory;
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
			statusHistory->PhysicalStatus = soap_new_witsml20__PhysicalStatus(gsoapProxy2_1->soap);
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
		return timeTools::convertIsoToUnixTimestamp(*getPerforationHistoryEntry(historyIndex, index)->StartDate);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return timeTools::convertIsoToUnixTimestamp(*getGravelPackHistoryEntry(historyIndex, index)->StartDate);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return timeTools::convertIsoToUnixTimestamp(*getOpenHoleHistoryEntry(historyIndex, index)->StartDate);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return timeTools::convertIsoToUnixTimestamp(*getSlotsHistoryEntry(historyIndex, index)->StartDate);
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

void WellboreCompletion::setConnectionHistoryStartDate(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index, time_t startDate) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml20__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		if (perforationStatusHistory->StartDate == nullptr) {
			perforationStatusHistory->StartDate = soap_new_std__string(gsoapProxy2_1->soap);
		}
		perforationStatusHistory->StartDate->assign(timeTools::convertUnixTimestampToIso(startDate));
	}
	else {
		witsml20__IntervalStatusHistory* statusHistory;
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
			statusHistory->StartDate = soap_new_std__string(gsoapProxy2_1->soap);
		}
		statusHistory->StartDate->assign(timeTools::convertUnixTimestampToIso(startDate));
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
		return timeTools::convertIsoToUnixTimestamp(*getPerforationHistoryEntry(historyIndex, index)->EndDate);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return timeTools::convertIsoToUnixTimestamp(*getGravelPackHistoryEntry(historyIndex, index)->EndDate);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return timeTools::convertIsoToUnixTimestamp(*getOpenHoleHistoryEntry(historyIndex, index)->EndDate);
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return timeTools::convertIsoToUnixTimestamp(*getSlotsHistoryEntry(historyIndex, index)->EndDate);
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

void WellboreCompletion::setConnectionHistoryEndDate(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index, time_t endDate) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml20__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		if (perforationStatusHistory->EndDate == nullptr) {
			perforationStatusHistory->EndDate = soap_new_std__string(gsoapProxy2_1->soap);
		}
		perforationStatusHistory->EndDate->assign(timeTools::convertUnixTimestampToIso(endDate));
	}
	else {
		witsml20__IntervalStatusHistory* statusHistory;
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
			statusHistory->EndDate = soap_new_std__string(gsoapProxy2_1->soap);
		}
		statusHistory->EndDate->assign(timeTools::convertUnixTimestampToIso(endDate));
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

string WellboreCompletion::getConnectionHistoryMdDatum(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionHistoryMdDatum(historyIndex, wellReservoirConnection, index)) {
		throw invalid_argument("No perforation history entry md datum is defined.");
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return getPerforationHistoryEntry(historyIndex, index)->PerforationMdInterval->datum;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return getGravelPackHistoryEntry(historyIndex, index)->StatusMdInterval->datum;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return getOpenHoleHistoryEntry(historyIndex, index)->StatusMdInterval->datum;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return getSlotsHistoryEntry(historyIndex, index)->StatusMdInterval->datum;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

bool WellboreCompletion::hasConnectionHistoryMdUnit(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml20__PerforationStatusHistory const * const perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		return perforationStatusHistory->PerforationMdInterval == nullptr
			? false
			: perforationStatusHistory->PerforationMdInterval->MdBase != nullptr || perforationStatusHistory->PerforationMdInterval->MdTop != nullptr;
	}
	else {
		witsml20__IntervalStatusHistory const* statusHistory;
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
		return statusHistory->StatusMdInterval == nullptr
			? false
			: statusHistory->StatusMdInterval->MdBase != nullptr || statusHistory->StatusMdInterval->MdTop != nullptr;
	}
}

eml21__LengthUom WellboreCompletion::getConnectionHistoryMdUnit(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionHistoryMdUnit(historyIndex, wellReservoirConnection, index)) {
		throw invalid_argument("No perforation history entry md unit is defined.");
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml20__PerforationStatusHistory const * const perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		return perforationStatusHistory->PerforationMdInterval->MdBase != nullptr
			? perforationStatusHistory->PerforationMdInterval->MdBase->uom
			: perforationStatusHistory->PerforationMdInterval->MdTop->uom;
	}
	else {
		witsml20__IntervalStatusHistory const* statusHistory;
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
		return statusHistory->StatusMdInterval->MdBase != nullptr
			? statusHistory->StatusMdInterval->MdBase->uom
			: statusHistory->StatusMdInterval->MdTop->uom;
	}
}

string WellboreCompletion::getConnectionHistoryMdUnitAsString(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	return gsoap_eml2_1::soap_eml21__LengthUom2s(gsoapProxy2_1->soap, getConnectionHistoryMdUnit(historyIndex, wellReservoirConnection, index));
}

bool WellboreCompletion::hasConnectionHistoryTopMd(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml20__PerforationStatusHistory const * const perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		if (perforationStatusHistory == nullptr) {
			return false;
		}
		if (perforationStatusHistory->PerforationMdInterval == nullptr) {
			return false;
		}
		return perforationStatusHistory->PerforationMdInterval->MdTop != nullptr;
	}
	else {
		witsml20__IntervalStatusHistory const* statusHistory;
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
		if (statusHistory->StatusMdInterval == nullptr) {
			return false;
		}
		return statusHistory->StatusMdInterval->MdTop != nullptr;
	}
}

double WellboreCompletion::getConnectionHistoryTopMd(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionHistoryTopMd(historyIndex, wellReservoirConnection, index)) {
		throw invalid_argument("No perforation history entry top MD is defined.");
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return getPerforationHistoryEntry(historyIndex, index)->PerforationMdInterval->MdTop->__item;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return getGravelPackHistoryEntry(historyIndex, index)->StatusMdInterval->MdTop->__item;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return getOpenHoleHistoryEntry(historyIndex, index)->StatusMdInterval->MdTop->__item;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return getSlotsHistoryEntry(historyIndex, index)->StatusMdInterval->MdTop->__item;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

void WellboreCompletion::setConnectionHistoryTopMd(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index,
	const std::string & datum,
	gsoap_eml2_1::eml21__LengthUom MdUnit,
	double TopMd)
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml20__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		if (perforationStatusHistory->PerforationMdInterval == nullptr) {
			perforationStatusHistory->PerforationMdInterval = soap_new_eml21__MdInterval(gsoapProxy2_1->soap);
		}
		perforationStatusHistory->PerforationMdInterval->datum = datum;
		perforationStatusHistory->PerforationMdInterval->MdTop = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
		perforationStatusHistory->PerforationMdInterval->MdTop->uom = MdUnit;
		perforationStatusHistory->PerforationMdInterval->MdTop->__item = TopMd;
	}
	else {
		witsml20__IntervalStatusHistory* statusHistory;
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
			statusHistory->StatusMdInterval = soap_new_eml21__MdInterval(gsoapProxy2_1->soap);
		}
		statusHistory->StatusMdInterval->datum = datum;
		statusHistory->StatusMdInterval->MdTop = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
		statusHistory->StatusMdInterval->MdTop->uom = MdUnit;
		statusHistory->StatusMdInterval->MdTop->__item = TopMd;
	}
}

bool WellboreCompletion::hasConnectionHistoryBaseMd(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml20__PerforationStatusHistory const * const perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		if (perforationStatusHistory == nullptr) {
			return false;
		}
		if (perforationStatusHistory->PerforationMdInterval == nullptr) {
			return false;
		}
		return perforationStatusHistory->PerforationMdInterval->MdBase != nullptr;
	}
	else {
		witsml20__IntervalStatusHistory const* statusHistory;
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
		if (statusHistory->StatusMdInterval == nullptr) {
			return false;
		}
		return statusHistory->StatusMdInterval->MdBase != nullptr;
	}
}

double WellboreCompletion::getConnectionHistoryBaseMd(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (!hasConnectionHistoryBaseMd(historyIndex, wellReservoirConnection, index)) {
		throw invalid_argument("No perforation history entry base md is defined.");
	}

	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		return getPerforationHistoryEntry(historyIndex, index)->PerforationMdInterval->MdBase->__item;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::GRAVEL_PACK) {
		return getGravelPackHistoryEntry(historyIndex, index)->StatusMdInterval->MdBase->__item;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::OPEN_HOLE) {
		return getOpenHoleHistoryEntry(historyIndex, index)->StatusMdInterval->MdBase->__item;
	}
	else if (wellReservoirConnection == WellReservoirConnectionType::SLOTS) {
		return getSlotsHistoryEntry(historyIndex, index)->StatusMdInterval->MdBase->__item;
	}
	else {
		throw std::invalid_argument("This type of completion connection type is not supported");
	}
}

void WellboreCompletion::setConnectionHistoryBaseMd(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index,
	const std::string & datum,
	gsoap_eml2_1::eml21__LengthUom MdUnit,
	double BaseMd)
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml20__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		if (perforationStatusHistory->PerforationMdInterval == nullptr) {
			perforationStatusHistory->PerforationMdInterval = soap_new_eml21__MdInterval(gsoapProxy2_1->soap);
		}
		perforationStatusHistory->PerforationMdInterval->datum = datum;
		perforationStatusHistory->PerforationMdInterval->MdBase = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
		perforationStatusHistory->PerforationMdInterval->MdBase->uom = MdUnit;
		perforationStatusHistory->PerforationMdInterval->MdBase->__item = BaseMd;
	}
	else {
		witsml20__IntervalStatusHistory* statusHistory;
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
			statusHistory->StatusMdInterval = soap_new_eml21__MdInterval(gsoapProxy2_1->soap);
		}
		statusHistory->StatusMdInterval->datum = datum;
		statusHistory->StatusMdInterval->MdBase = soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap);
		statusHistory->StatusMdInterval->MdBase->uom = MdUnit;
		statusHistory->StatusMdInterval->MdBase->__item = BaseMd;
	}
}

bool WellboreCompletion::hasConnectionHistoryComment(uint64_t historyIndex,
	WellReservoirConnectionType wellReservoirConnection, uint64_t index) const
{
	if (wellReservoirConnection == WellReservoirConnectionType::PERFORATION) {
		witsml20__PerforationStatusHistory const * const perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		if (perforationStatusHistory == nullptr) {
			return false;
		}
		return perforationStatusHistory->Comment != nullptr;
	}
	else {
		witsml20__IntervalStatusHistory const* statusHistory;
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
		witsml20__PerforationStatusHistory* perforationStatusHistory = getPerforationHistoryEntry(historyIndex, index);
		if (perforationStatusHistory->Comment == nullptr) {
			perforationStatusHistory->Comment = soap_new_std__string(gsoapProxy2_1->soap, 1);
		}
		perforationStatusHistory->Comment->assign(comment);
	}
	else {
		witsml20__IntervalStatusHistory* statusHistory;
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
			statusHistory->Comment = soap_new_std__string(gsoapProxy2_1->soap, 1);
		}
		statusHistory->Comment->assign(comment);
	}
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

	return wellboreCompletion->ContactIntervalSet->PerforationSetInterval.at(index);
}

gsoap_eml2_1::witsml20__GravelPackInterval* WellboreCompletion::getGravelPack(uint64_t index) const
{
	witsml20__WellboreCompletion const * const wellboreCompletion = static_cast<witsml20__WellboreCompletion*>(gsoapProxy2_1);

	if (wellboreCompletion->ContactIntervalSet == nullptr) {
		throw invalid_argument("No contact interval exists.");
	}

	return wellboreCompletion->ContactIntervalSet->GravelPackInterval.at(index);
}
gsoap_eml2_1::witsml20__OpenHoleInterval* WellboreCompletion::getOpenHole(uint64_t index) const
{
	witsml20__WellboreCompletion const * const wellboreCompletion = static_cast<witsml20__WellboreCompletion*>(gsoapProxy2_1);

	if (wellboreCompletion->ContactIntervalSet == nullptr) {
		throw invalid_argument("No contact interval exists.");
	}

	return wellboreCompletion->ContactIntervalSet->OpenHoleInterval.at(index);
}

gsoap_eml2_1::witsml20__SlotsInterval* WellboreCompletion::getSlots(uint64_t index) const
{
	witsml20__WellboreCompletion const * const wellboreCompletion = static_cast<witsml20__WellboreCompletion*>(gsoapProxy2_1);

	if (wellboreCompletion->ContactIntervalSet == nullptr) {
		throw invalid_argument("No contact interval exists.");
	}

	return wellboreCompletion->ContactIntervalSet->SlotsInterval.at(index);
}
