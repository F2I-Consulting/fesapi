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
#include "WellTest.h"
#include "../catch.hpp"
#include "common/EpcDocument.h"
#include "witsml2_0/Well.h"
#include <stdexcept>

using namespace std;
using namespace witsml2_test;
using namespace COMMON_NS;
using namespace WITSML2_0_NS;

const char* WellTest::defaultUuid = "4b4ef814-a891-46f5-bf10-3cc30be396a5";
const char* WellTest::defaultTitle = "Witsml Well Test";
const time_t WellTest::defaultTimestamp = 1553268493; // 2019-03-22T15:28:13+00:00

WellTest::WellTest(const string & epcDocPath)
	: AbstractTest(epcDocPath) {
}

void WellTest::initRepo() {
	Well* well = repo->createWell(defaultUuid, defaultTitle);
	REQUIRE(well != nullptr);
	well->setBlock("my Block");
	// No county
	well->setDTimLicense(defaultTimestamp);
	well->setGroundElevation(10, gsoap_eml2_1::eml21__LengthUom__m, "MSL");
	REQUIRE_THROWS(well->setTimeZone(true, 24));
	REQUIRE_THROWS(well->setTimeZone(true, 22, 65));
	well->setTimeZone(true, 0); // time zone == 'Z'
	well->setStatusWell(gsoap_eml2_1::eml21__WellStatus__active);
}

void WellTest::readRepo() {
	Well* well = repo->getDataObjectByUuid<Well>(defaultUuid);
	REQUIRE(well != nullptr);
	REQUIRE(well->hasBlock());
	REQUIRE(well->getBlock() == "my Block");
	REQUIRE_FALSE(well->hasCounty());
	REQUIRE(well->getDTimLicense() == defaultTimestamp);
	REQUIRE(well->getGroundElevationValue() == 10);
	REQUIRE(well->getGroundElevationUom() == gsoap_eml2_1::eml21__LengthUom__m);
	REQUIRE(well->getGroundElevationDatum() == "MSL");
	REQUIRE(well->getTimeZoneDirection() == true);
	REQUIRE(well->getTimeZoneHours() == 0);
	REQUIRE(well->getTimeZoneMinutes() == 0);
	REQUIRE(well->getStatusWell() == gsoap_eml2_1::eml21__WellStatus__active);
}
