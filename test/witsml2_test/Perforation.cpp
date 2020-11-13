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
#include "witsml2_0/Well.h"
#include "witsml2_0/Wellbore.h"
#include "witsml2_0/WellCompletion.h"
#include "witsml2_0/WellboreCompletion.h"
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
	WITSML2_0_NS::Well* well = repo->createPartial<WITSML2_0_NS::Well>("", "");
	WITSML2_0_NS::Wellbore* wellbore = repo->createPartial<WITSML2_0_NS::Wellbore>("", "");
	WITSML2_0_NS::WellCompletion* wellCompletion = repo->createWellCompletion(well, "6593d580-2f44-4b18-97ce-8a9cf42a0414", "WellCompletion1");
	WITSML2_0_NS::WellboreCompletion* wellboreCompletion = repo->createWellboreCompletion(wellbore, wellCompletion, "7bda8ecf-2037-4dc7-8c59-db6ca09f2008", "WellboreCompletion1", "wellCompletionName");

	wellboreCompletion->pushBackPerforation("Mean Sea Level", gsoap_eml2_1::eml21__LengthUom__m, 1970, 1980, "myId");
	wellboreCompletion->pushBackPerforation("Mean Sea Level", gsoap_eml2_1::eml21__LengthUom__m, 1990, 2000);
	wellboreCompletion->pushBackPerforationHistory(0);
	wellboreCompletion->setPerforationHistoryStatus(0, 0, gsoap_eml2_1::witsml20__PerforationStatus__open);
	wellboreCompletion->setPerforationHistoryTopMd(0, 0, "Mean Sea Level", gsoap_eml2_1::eml21__LengthUom__m, 1970);
	wellboreCompletion->setPerforationHistoryBaseMd(0, 0, "Mean Sea Level", gsoap_eml2_1::eml21__LengthUom__m, 1980);
	wellboreCompletion->setPerforationHistoryStartDate(0, 0, 407568645);
	wellboreCompletion->setPerforationHistoryEndDate(0, 0, 1514764800);
	wellboreCompletion->setPerforationHistoryComment(0, 0, "Comment");
}

void Perforation::readRepo() {
	WITSML2_0_NS::WellboreCompletion* wellboreCompletion = repo->getDataObjectByUuid<WITSML2_0_NS::WellboreCompletion>("7bda8ecf-2037-4dc7-8c59-db6ca09f2008");
	REQUIRE (wellboreCompletion != nullptr);

	REQUIRE(wellboreCompletion->getPerforationCount() == 2);
	REQUIRE(wellboreCompletion->getPerforationUid(0) == "myId");
	REQUIRE(wellboreCompletion->hasPerforationMdDatum(0));
	REQUIRE(wellboreCompletion->getPerforationMdDatum(0) == "Mean Sea Level");
	REQUIRE(wellboreCompletion->hasPerforationMdUnit(0));
	REQUIRE(wellboreCompletion->getPerforationMdUnit(0) == gsoap_eml2_1::eml21__LengthUom__m);
	REQUIRE(wellboreCompletion->hasPerforationTopMd(0));
	REQUIRE(wellboreCompletion->getPerforationTopMd(0) == 1970);
	REQUIRE(wellboreCompletion->hasPerforationBaseMd(0));
	REQUIRE(wellboreCompletion->getPerforationBaseMd(0) == 1980);
	REQUIRE(wellboreCompletion->getPerforationHistoryCount(0) == 1);
	REQUIRE(wellboreCompletion->hasPerforationHistoryStatus(0, 0));
	REQUIRE(wellboreCompletion->getPerforationHistoryStatus(0, 0) == gsoap_eml2_1::witsml20__PerforationStatus__open);
	REQUIRE(wellboreCompletion->hasPerforationHistoryStartDate(0, 0));
	REQUIRE(wellboreCompletion->getPerforationHistoryStartDate(0, 0) == 407568645);
	REQUIRE(wellboreCompletion->hasPerforationHistoryEndDate(0, 0));
	REQUIRE(wellboreCompletion->getPerforationHistoryEndDate(0, 0) == 1514764800);
	REQUIRE(wellboreCompletion->hasPerforationHistoryMdDatum(0, 0));
	REQUIRE(wellboreCompletion->getPerforationHistoryMdDatum(0, 0) == "Mean Sea Level");
	REQUIRE(wellboreCompletion->hasPerforationHistoryMdUnit(0, 0));
	REQUIRE(wellboreCompletion->getPerforationHistoryMdUnit(0, 0) == gsoap_eml2_1::eml21__LengthUom__m);
	REQUIRE(wellboreCompletion->hasPerforationHistoryTopMd(0, 0));
	REQUIRE(wellboreCompletion->getPerforationHistoryTopMd(0, 0) == 1970);
	REQUIRE(wellboreCompletion->hasPerforationHistoryBaseMd(0, 0));
	REQUIRE(wellboreCompletion->getPerforationHistoryBaseMd(0, 0) == 1980);
	REQUIRE(wellboreCompletion->getPerforationHistoryComment(0, 0) == "Comment");
}
