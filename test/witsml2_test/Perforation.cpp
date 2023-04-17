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
#include "Perforation.h"
#include "../catch.hpp"
#include "witsml2_1/Well.h"
#include "witsml2_1/Wellbore.h"
#include "witsml2_1/WellCompletion.h"
#include "witsml2_1/WellboreCompletion.h"
#include <stdexcept>

using namespace std;
using namespace witsml2_test;
using namespace COMMON_NS;

const char* Perforation::defaultUuid = "d5a528c8-73e7-4bf3-9441-118f8111d56a";
const char* Perforation::defaultTitle = "WITSML Perforation Test";

Perforation::Perforation(const string & epcDocPath)
	: AbstractTest(epcDocPath) {
}

void Perforation::initRepo() {
	WITSML2_1_NS::Well* well = repo->createPartial<WITSML2_1_NS::Well>("", "");
	WITSML2_1_NS::Wellbore* wellbore = repo->createPartial<WITSML2_1_NS::Wellbore>("", "");
	WITSML2_1_NS::WellCompletion* wellCompletion = repo->createWellCompletion(well, "6593d580-2f44-4b18-97ce-8a9cf42a0414", "WellCompletion1");
	WITSML2_1_NS::WellboreCompletion* wellboreCompletion = repo->createWellboreCompletion(wellbore, "7bda8ecf-2037-4dc7-8c59-db6ca09f2008", "WellboreCompletion1");

	wellboreCompletion->pushBackConnection(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, gsoap_eml2_3::eml23__LengthUom::m, 1970, 1980, "myId");
	wellboreCompletion->pushBackConnection(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, gsoap_eml2_3::eml23__LengthUom::m, 1990, 2000, "myOtherUid");
	wellboreCompletion->pushBackConnectionHistory(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0);
	wellboreCompletion->setConnectionHistoryStatus(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0, gsoap_eml2_3::witsml21__PhysicalStatus::open);
	wellboreCompletion->setConnectionHistoryMdInterval(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0, gsoap_eml2_3::eml23__LengthUom::m, 1970, 1980);
	wellboreCompletion->setConnectionHistoryStartDate(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0, 407568645);
	wellboreCompletion->setConnectionHistoryEndDate(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0, 1514764800);
	wellboreCompletion->setConnectionHistoryComment(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0, "Comment");
}

void Perforation::readRepo() {
	WITSML2_1_NS::WellboreCompletion* wellboreCompletion = repo->getDataObjectByUuid<WITSML2_1_NS::WellboreCompletion>("7bda8ecf-2037-4dc7-8c59-db6ca09f2008");
	REQUIRE (wellboreCompletion != nullptr);

	REQUIRE(wellboreCompletion->getConnectionCount(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION) == 2);
	REQUIRE(wellboreCompletion->getConnectionUid(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0) == "myId");
	REQUIRE(wellboreCompletion->hasConnectionMdInterval(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0));
	REQUIRE(wellboreCompletion->getConnectionMdUnit(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0) == gsoap_eml2_3::eml23__LengthUom::m);
	REQUIRE(wellboreCompletion->getConnectionTopMd(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0) == 1970);
	REQUIRE(wellboreCompletion->getConnectionBaseMd(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0) == 1980);
	REQUIRE(wellboreCompletion->getConnectionHistoryCount(WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0) == 1);
	REQUIRE(wellboreCompletion->hasConnectionHistoryStatus(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0));
	REQUIRE(wellboreCompletion->getConnectionHistoryStatus(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0) == gsoap_eml2_3::witsml21__PhysicalStatus::open);
	REQUIRE(wellboreCompletion->hasConnectionHistoryStartDate(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0));
	REQUIRE(wellboreCompletion->getConnectionHistoryStartDate(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0) == 407568645);
	REQUIRE(wellboreCompletion->hasConnectionHistoryEndDate(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0));
	REQUIRE(wellboreCompletion->getConnectionHistoryEndDate(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0) == 1514764800);
	REQUIRE(wellboreCompletion->hasConnectionHistoryMdInterval(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0));
	REQUIRE(wellboreCompletion->getConnectionHistoryMdUnit(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0) == gsoap_eml2_3::eml23__LengthUom::m);
	REQUIRE(wellboreCompletion->getConnectionHistoryTopMd(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0) == 1970);
	REQUIRE(wellboreCompletion->getConnectionHistoryBaseMd(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0) == 1980);
	REQUIRE(wellboreCompletion->getConnectionHistoryComment(0, WITSML2_1_NS::WellboreCompletion::WellReservoirConnectionType::PERFORATION, 0) == "Comment");
}
