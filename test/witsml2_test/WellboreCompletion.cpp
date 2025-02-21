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

#include <stdexcept>

#include "../catch.hpp"

#include "witsml2_1/Wellbore.h"
#include "witsml2_1/WellboreCompletion.h"

using namespace std;
using namespace witsml2_test;
using namespace COMMON_NS;

WellboreCompletion::WellboreCompletion(const string& epcDocPath)
	: AbstractTest(epcDocPath) {
}

void WellboreCompletion::initRepo() {
	WITSML2_NS::Wellbore* wellbore = repo->createPartial<WITSML2_1_NS::Wellbore>("", "");
	WITSML2_1_NS::WellboreCompletion* witsmlWbCompletion = repo->createWellboreCompletion(wellbore, defaultUuid, defaultTitle);

	witsmlWbCompletion->pushBackConnection(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, gsoap_eml2_3::eml23__LengthUom::m, 1000, 1100, "uid0");
	witsmlWbCompletion->pushBackConnection(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::GRAVEL_PACK, gsoap_eml2_3::eml23__LengthUom::m, 1200, 1300, "uid1");
	witsmlWbCompletion->pushBackConnection(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::OPEN_HOLE, gsoap_eml2_3::eml23__LengthUom::m, 1300, 1400, "uid2");
	witsmlWbCompletion->pushBackConnection(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::SLOTS, gsoap_eml2_3::eml23__LengthUom::ft, 5500, 5600, "uid3");
	witsmlWbCompletion->pushBackConnection(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, gsoap_eml2_3::eml23__LengthUom::m, 10000, 11000, "uid4");

	witsmlWbCompletion->pushBackConnectionHistory(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1);
	witsmlWbCompletion->pushBackConnectionHistory(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1);
	witsmlWbCompletion->pushBackConnectionHistory(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::GRAVEL_PACK, 0);
	witsmlWbCompletion->pushBackConnectionHistory(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::OPEN_HOLE, 0);
	witsmlWbCompletion->pushBackConnectionExtraMetadata(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::SLOTS, 0, "testingExtraMetadataKey", "testingExtraMetadataValue");

	witsmlWbCompletion->setConnectionHistoryMdInterval(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1, gsoap_eml2_3::eml23__LengthUom::m, 1000, 1100);
	witsmlWbCompletion->setConnectionHistoryMdInterval(1, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1, gsoap_eml2_3::eml23__LengthUom::m, 1000, 1100);
	witsmlWbCompletion->setConnectionHistoryStatus(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1, gsoap_eml2_3::witsml21__PhysicalStatus::open);
	witsmlWbCompletion->setConnectionHistoryStatus(1, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1, gsoap_eml2_3::witsml21__PhysicalStatus::closed);
	witsmlWbCompletion->setConnectionHistoryStartDate(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1, 0);
	witsmlWbCompletion->setConnectionHistoryEndDate(1, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1, 3600);
	witsmlWbCompletion->setConnectionHistoryStartDate(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::GRAVEL_PACK, 0, 7200);
	witsmlWbCompletion->setConnectionHistoryEndDate(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::GRAVEL_PACK, 0, 8000);
}

void WellboreCompletion::readRepo() {
	WITSML2_1_NS::WellboreCompletion* witsmlWbCompletion = repo->getDataObjectByUuid<WITSML2_1_NS::WellboreCompletion>(defaultUuid);
	REQUIRE (witsmlWbCompletion != nullptr);

	REQUIRE(witsmlWbCompletion->getConnectionCount(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION) == 2);
	REQUIRE(witsmlWbCompletion->getConnectionCount(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::GRAVEL_PACK) == 1);
	REQUIRE(witsmlWbCompletion->getConnectionCount(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::OPEN_HOLE) == 1);
	REQUIRE(witsmlWbCompletion->getConnectionCount(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::SLOTS) == 1);

	REQUIRE(witsmlWbCompletion->getConnectionHistoryCount(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0) == 0);
	REQUIRE(witsmlWbCompletion->getConnectionHistoryCount(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1) == 2);
	REQUIRE(witsmlWbCompletion->getConnectionHistoryCount(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::GRAVEL_PACK, 0) == 1);
	REQUIRE(witsmlWbCompletion->getConnectionHistoryCount(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::OPEN_HOLE, 0) == 1);
	REQUIRE(witsmlWbCompletion->getConnectionHistoryCount(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::SLOTS, 0) == 0);
	REQUIRE(witsmlWbCompletion->getConnectionExtraMetadata(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::SLOTS, 0, "testingExtraMetadataKey").size() == 1);
	REQUIRE(witsmlWbCompletion->getConnectionExtraMetadata(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::SLOTS, 0, "testingExtraMetadataKey")[0] == "testingExtraMetadataValue");
	REQUIRE_THROWS(witsmlWbCompletion->getConnectionHistoryCount(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::GRAVEL_PACK, 1) == 0);

	REQUIRE(witsmlWbCompletion->getConnectionHistoryTopMd(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1) == 1000);
	REQUIRE(witsmlWbCompletion->getConnectionHistoryBaseMd(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1) == 1100);
	REQUIRE(witsmlWbCompletion->getConnectionHistoryTopMd(1, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1) == 1000);
	REQUIRE(witsmlWbCompletion->getConnectionHistoryBaseMd(1, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1) == 1100);
	REQUIRE(witsmlWbCompletion->getConnectionHistoryStatus(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1) == gsoap_eml2_3::witsml21__PhysicalStatus::open);
	REQUIRE(witsmlWbCompletion->getConnectionHistoryStatus(1, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1) == gsoap_eml2_3::witsml21__PhysicalStatus::closed);
	REQUIRE(witsmlWbCompletion->getConnectionHistoryStartDate(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1) == 0);
	REQUIRE(!witsmlWbCompletion->hasConnectionHistoryEndDate(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1));
	REQUIRE(witsmlWbCompletion->getConnectionHistoryEndDate(1, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1) == 3600);
	REQUIRE(!witsmlWbCompletion->hasConnectionHistoryStartDate(1, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 1));
	REQUIRE(witsmlWbCompletion->getConnectionHistoryStartDate(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::GRAVEL_PACK, 0) == 7200);
	REQUIRE(witsmlWbCompletion->getConnectionHistoryEndDate(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::GRAVEL_PACK, 0) == 8000);
}
