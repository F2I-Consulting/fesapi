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
#include "WellboreGeometryTest.h"

#include <stdexcept>

#include "../catch.hpp"

#include "witsml2_1/Wellbore.h"
#include "witsml2_1/WellboreGeometry.h"

using namespace std;
using namespace witsml2_test;
using namespace COMMON_NS;

const char* WellboreGeometryTest::defaultUuid = "1e6c55f2-5250-4d1b-aceb-d2a707da8620";
const char* WellboreGeometryTest::defaultTitle = "WITSML Wellbore Geometry Test";

WellboreGeometryTest::WellboreGeometryTest(const string & epcDocPath)
	: AbstractTest(epcDocPath) {
}

void WellboreGeometryTest::initRepo() {
	WITSML2_NS::Wellbore* wellbore = repo->createPartial<WITSML2_1_NS::Wellbore>("", "");
	WITSML2_1_NS::WellboreGeometry* witsmlWbGeom = repo->createWellboreGeometry(wellbore, defaultUuid, "WellboreGeometry TEST", false);

	witsmlWbGeom->pushBackSection(0, 250, gsoap_eml2_3::eml23__LengthUom::m);
	witsmlWbGeom->setWellboreGeometrySectionTypeHoleCasing(0, gsoap_eml2_3::witsml21__HoleCasingType::casing);
	witsmlWbGeom->setWellboreGeometrySectionOdSection(0, 30, gsoap_eml2_3::eml23__LengthUom::in);
	witsmlWbGeom->setWellboreGeometrySectionTvdInterval(0, 0, 250, gsoap_eml2_3::eml23__LengthUom::m);
	witsmlWbGeom->pushBackSection(0, 990, gsoap_eml2_3::eml23__LengthUom::m);
	witsmlWbGeom->setWellboreGeometrySectionTypeHoleCasing(1, gsoap_eml2_3::witsml21__HoleCasingType::casing);
	witsmlWbGeom->setWellboreGeometrySectionCurveConductor(1, false);
	witsmlWbGeom->setWellboreGeometrySectionDiaDrift(1, 17.5, gsoap_eml2_3::eml23__LengthUom::in);
	witsmlWbGeom->setWellboreGeometrySectionFactFric(1, 0.25);
	witsmlWbGeom->setWellboreGeometrySectionGrade(1, "L80");
	witsmlWbGeom->setWellboreGeometrySectionIdSection(1, 18, gsoap_eml2_3::eml23__LengthUom::in);
	witsmlWbGeom->setWellboreGeometrySectionOdSection(1, 20, gsoap_eml2_3::eml23__LengthUom::in);
	witsmlWbGeom->setWellboreGeometrySectionWtPerLen(1, 123, gsoap_eml2_3::eml23__MassPerLengthUom::lbm_x002fft);
	witsmlWbGeom->setWellboreGeometrySectionTvdInterval(1, 0, 990, gsoap_eml2_3::eml23__LengthUom::m);
}

void WellboreGeometryTest::readRepo() {
	WITSML2_1_NS::WellboreGeometry* wbGeom = repo->getDataObjectByUuid<WITSML2_1_NS::WellboreGeometry>(defaultUuid);
	REQUIRE (wbGeom != nullptr);

	REQUIRE(wbGeom->getSectionCount() == 2);

	REQUIRE(wbGeom->getWellboreGeometrySectionTypeHoleCasing(0) == gsoap_eml2_3::witsml21__HoleCasingType::casing);
	REQUIRE(wbGeom->getWellboreGeometrySectionOdSectionValue(0) == 30);
	REQUIRE(wbGeom->getWellboreGeometrySectionOdSectionUom(0) == gsoap_eml2_3::eml23__LengthUom::in);
	REQUIRE(wbGeom->getWellboreGeometrySectionMdIntervalBase(0) == 250);
	REQUIRE(wbGeom->getWellboreGeometrySectionMdIntervalUom(0) == gsoap_eml2_3::eml23__LengthUom::m);
	REQUIRE(wbGeom->getWellboreGeometrySectionMdIntervalTop(0) == 0);
	REQUIRE(wbGeom->getWellboreGeometrySectionTvdIntervalBase(0) == 250);
	REQUIRE(wbGeom->getWellboreGeometrySectionTvdIntervalTop(0) == 0);
	REQUIRE(wbGeom->getWellboreGeometrySectionTvdIntervalUom(0) == gsoap_eml2_3::eml23__LengthUom::m);

	REQUIRE(wbGeom->getWellboreGeometrySectionTypeHoleCasing(1) == gsoap_eml2_3::witsml21__HoleCasingType::casing);
	REQUIRE(!wbGeom->getWellboreGeometrySectionCurveConductor(1));
	REQUIRE(wbGeom->getWellboreGeometrySectionDiaDriftValue(1) == 17.5);
	REQUIRE(wbGeom->getWellboreGeometrySectionDiaDriftUom(1) == gsoap_eml2_3::eml23__LengthUom::in);
	REQUIRE(wbGeom->getWellboreGeometrySectionFactFric(1) == 0.25);
	REQUIRE(wbGeom->getWellboreGeometrySectionGrade(1) == "L80");
	REQUIRE(wbGeom->getWellboreGeometrySectionIdSectionValue(1) == 18);
	REQUIRE(wbGeom->getWellboreGeometrySectionIdSectionUom(1) == gsoap_eml2_3::eml23__LengthUom::in);
	REQUIRE(wbGeom->getWellboreGeometrySectionOdSectionValue(1) == 20);
	REQUIRE(wbGeom->getWellboreGeometrySectionOdSectionUom(1) == gsoap_eml2_3::eml23__LengthUom::in);
	REQUIRE(wbGeom->getWellboreGeometrySectionTvdIntervalBase(1) == 990);
	REQUIRE(wbGeom->getWellboreGeometrySectionTvdIntervalUom(1) == gsoap_eml2_3::eml23__LengthUom::m);
	REQUIRE(wbGeom->getWellboreGeometrySectionTvdIntervalTop(1) == 0);
	REQUIRE(wbGeom->getWellboreGeometrySectionWtPerLenValue(1) == 123);
	REQUIRE(wbGeom->getWellboreGeometrySectionWtPerLenUom(1) == gsoap_eml2_3::eml23__MassPerLengthUom::lbm_x002fft);
}
