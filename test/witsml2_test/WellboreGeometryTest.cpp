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
#include "../catch.hpp"
#include "witsml2_0/Well.h"
#include "witsml2_0/Wellbore.h"
#include "witsml2_0/WellboreGeometry.h"
#include <stdexcept>

using namespace std;
using namespace witsml2_test;
using namespace COMMON_NS;

const char* WellboreGeometryTest::defaultUuid = "1e6c55f2-5250-4d1b-aceb-d2a707da8620";
const char* WellboreGeometryTest::defaultTitle = "WITSML Wellbore Geometry Test";

WellboreGeometryTest::WellboreGeometryTest(const string & epcDocPath)
	: AbstractTest(epcDocPath) {
}

void WellboreGeometryTest::initRepo() {
	WITSML2_0_NS::Wellbore* wellbore = repo->createPartial<WITSML2_0_NS::Wellbore>("", "");
	WITSML2_0_NS::WellboreGeometry* witsmlWbGeom = repo->createWellboreGeometry(wellbore, defaultUuid, "WellboreGeometry TEST", gsoap_eml2_1::witsml20__ChannelStatus__closed);

	witsmlWbGeom->setMdBase(0, gsoap_eml2_1::eml21__LengthUom__m, "d3ac5401-d3e7-4474-b846-070673b210ae");
	witsmlWbGeom->pushBackSection();
	witsmlWbGeom->setWellboreGeometrySectionTypeHoleCasing(0, gsoap_eml2_1::witsml20__HoleCasingType__casing);
	witsmlWbGeom->setWellboreGeometrySectionOdSection(0, 30, gsoap_eml2_1::eml21__LengthUom__in);
	witsmlWbGeom->setWellboreGeometrySectionMdInterval(0, 0, 250, "d3ac5401-d3e7-4474-b846-070673b210ae", gsoap_eml2_1::eml21__LengthUom__m);
	witsmlWbGeom->setWellboreGeometrySectionTvdInterval(0, 0, 250, "d3ac5401-d3e7-4474-b846-070673b210ae", gsoap_eml2_1::eml21__LengthUom__m);
	witsmlWbGeom->pushBackSection();
	witsmlWbGeom->setWellboreGeometrySectionTypeHoleCasing(1, gsoap_eml2_1::witsml20__HoleCasingType__casing);
	witsmlWbGeom->setWellboreGeometrySectionCurveConductor(1, false);
	witsmlWbGeom->setWellboreGeometrySectionDiaDrift(1, 17.5, gsoap_eml2_1::eml21__LengthUom__in);
	witsmlWbGeom->setWellboreGeometrySectionFactFric(1, 0.25);
	witsmlWbGeom->setWellboreGeometrySectionGrade(1, "L80");
	witsmlWbGeom->setWellboreGeometrySectionIdSection(1, 18, gsoap_eml2_1::eml21__LengthUom__in);
	witsmlWbGeom->setWellboreGeometrySectionOdSection(1, 20, gsoap_eml2_1::eml21__LengthUom__in);
	witsmlWbGeom->setWellboreGeometrySectionWtPerLen(1, 123, gsoap_eml2_1::eml21__MassPerLengthUom__lbm_x002fft);
	witsmlWbGeom->setWellboreGeometrySectionTvdInterval(1, 0, 990, "d3ac5401-d3e7-4474-b846-070673b210ae", gsoap_eml2_1::eml21__LengthUom__m);
}

void WellboreGeometryTest::readRepo() {
	WITSML2_0_NS::WellboreGeometry* wbGeom = repo->getDataObjectByUuid<WITSML2_0_NS::WellboreGeometry>(defaultUuid);
	REQUIRE (wbGeom != nullptr);

	REQUIRE(!wbGeom->hasDepthWaterMean());
	REQUIRE(!wbGeom->hasGapAir());
	REQUIRE(wbGeom->hasMdBase());
	REQUIRE(wbGeom->getMdBaseValue() == .0);
	REQUIRE(wbGeom->getMdBaseUom() == gsoap_eml2_1::eml21__LengthUom__m);
	REQUIRE(wbGeom->getMdBaseDatum() == "d3ac5401-d3e7-4474-b846-070673b210ae");
	REQUIRE(wbGeom->getSectionCount() == 2);

	REQUIRE(wbGeom->getWellboreGeometrySectionTypeHoleCasing(0) == gsoap_eml2_1::witsml20__HoleCasingType__casing);
	REQUIRE(wbGeom->getWellboreGeometrySectionOdSectionValue(0) == 30);
	REQUIRE(wbGeom->getWellboreGeometrySectionOdSectionUom(0) == gsoap_eml2_1::eml21__LengthUom__in);
	REQUIRE(wbGeom->getWellboreGeometrySectionMdIntervalBase(0) == 250);
	REQUIRE(wbGeom->getWellboreGeometrySectionMdIntervalBaseUom(0) == gsoap_eml2_1::eml21__LengthUom__m);
	REQUIRE(wbGeom->getWellboreGeometrySectionMdIntervalTop(0) == 0);
	REQUIRE(wbGeom->getWellboreGeometrySectionMdIntervalTopUom(0) == gsoap_eml2_1::eml21__LengthUom__m);
	REQUIRE(wbGeom->getWellboreGeometrySectionMdIntervaldatum(0) == "d3ac5401-d3e7-4474-b846-070673b210ae");
	REQUIRE(wbGeom->getWellboreGeometrySectionTvdIntervalBase(0) == 250);
	REQUIRE(wbGeom->getWellboreGeometrySectionTvdIntervalBaseUom(0) == gsoap_eml2_1::eml21__LengthUom__m);
	REQUIRE(wbGeom->getWellboreGeometrySectionTvdIntervalTop(0) == 0);
	REQUIRE(wbGeom->getWellboreGeometrySectionTvdIntervalTopUom(0) == gsoap_eml2_1::eml21__LengthUom__m);
	REQUIRE(wbGeom->getWellboreGeometrySectionTvdIntervaldatum(0) == "d3ac5401-d3e7-4474-b846-070673b210ae");

	REQUIRE(wbGeom->getWellboreGeometrySectionTypeHoleCasing(1) == gsoap_eml2_1::witsml20__HoleCasingType__casing);
	REQUIRE(!wbGeom->getWellboreGeometrySectionCurveConductor(1));
	REQUIRE(wbGeom->getWellboreGeometrySectionDiaDriftValue(1) == 17.5);
	REQUIRE(wbGeom->getWellboreGeometrySectionDiaDriftUom(1) == gsoap_eml2_1::eml21__LengthUom__in);
	REQUIRE(wbGeom->getWellboreGeometrySectionFactFric(1) == 0.25);
	REQUIRE(wbGeom->getWellboreGeometrySectionGrade(1) == "L80");
	REQUIRE(wbGeom->getWellboreGeometrySectionIdSectionValue(1) == 18);
	REQUIRE(wbGeom->getWellboreGeometrySectionIdSectionUom(1) == gsoap_eml2_1::eml21__LengthUom__in);
	REQUIRE(wbGeom->getWellboreGeometrySectionOdSectionValue(1) == 20);
	REQUIRE(wbGeom->getWellboreGeometrySectionOdSectionUom(1) == gsoap_eml2_1::eml21__LengthUom__in);
	REQUIRE(wbGeom->getWellboreGeometrySectionTvdIntervalBase(1) == 990);
	REQUIRE(wbGeom->getWellboreGeometrySectionTvdIntervalBaseUom(1) == gsoap_eml2_1::eml21__LengthUom__m);
	REQUIRE(wbGeom->getWellboreGeometrySectionTvdIntervalTop(1) == 0);
	REQUIRE(wbGeom->getWellboreGeometrySectionTvdIntervalTopUom(1) == gsoap_eml2_1::eml21__LengthUom__m);
	REQUIRE(wbGeom->getWellboreGeometrySectionTvdIntervaldatum(1) == "d3ac5401-d3e7-4474-b846-070673b210ae");
	REQUIRE(wbGeom->getWellboreGeometrySectionWtPerLenValue(1) == 123);
	REQUIRE(wbGeom->getWellboreGeometrySectionWtPerLenUom(1) == gsoap_eml2_1::eml21__MassPerLengthUom__lbm_x002fft);
}
