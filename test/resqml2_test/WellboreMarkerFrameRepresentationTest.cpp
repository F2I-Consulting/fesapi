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
#include "resqml2_test/WellboreMarkerFrameRepresentationTest.h"

#include "catch.hpp"

#include "resqml2_test/WellboreTrajectoryRepresentationTest.h"

#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"

#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"

#include "resqml2_2/WellboreMarkerFrameRepresentation.h"
#include "resqml2_2/WellboreMarker.h"

#include "witsml2_0/WellboreMarker.h"

using namespace std;
using namespace COMMON_NS;
using namespace RESQML2_NS;
using namespace resqml2_test;

const char* WellboreMarkerFrameRepresentationTest::defaultUuid = "8f1c7e38-afc7-4cb8-86bb-a116e9135de4";
const char* WellboreMarkerFrameRepresentationTest::defaultTitle = "Wellbore Marker Frame Representation";

WellboreMarkerFrameRepresentationTest::WellboreMarkerFrameRepresentationTest(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void WellboreMarkerFrameRepresentationTest::initRepo() {
	WellboreInterpretation* interp = repo->createPartial<RESQML2_0_1_NS::WellboreInterpretation>("", "");
	MdDatum* mdDatum = repo->createMdDatum("", "", nullptr, gsoap_eml2_3::eml23__WellboreDatumReference__mean_x0020sea_x0020level, 275, 75, 0);

	// creating the WellboreTrajectoryRepresentation in m and ft and depth
	WellboreTrajectoryRepresentation* traj = repo->createWellboreTrajectoryRepresentation(interp, "", "", mdDatum);
	double controlPoints[12] = { 275, 75, 0, 275, 75, 325, 275, 75, 500, 275, 75, 1000 };
	double trajectoryTangentVectors[12] = { 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 3.2808 };
	double trajectoryMds[4] = { 0, 325, 500, 1000 };
	traj->setGeometry(controlPoints, trajectoryTangentVectors, trajectoryMds, 4, 0, repo->getHdfProxySet()[0]);

	// WellboreFeature marker frame
	WellboreMarkerFrameRepresentation* wmf = repo->createWellboreMarkerFrameRepresentation(interp, defaultUuid, defaultTitle, traj);
	double markerMdValues[2] = { 350, 550 };
	wmf->setMdValues(markerMdValues, 2, repo->getHdfProxySet()[0]);
	auto resqmlMarker = repo->createWellboreMarker(wmf, "dfc5292d-88cd-4c20-977f-e808f5a1d56e", "", gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind__horizon);
	repo->createWellboreMarker(wmf, "0f35ddef-d13e-4921-ab5b-3ee68b24a714", "testing Fault", gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind__fault);

	// WITSML link for dip and azimuth
	WITSML2_0_NS::WellboreMarker* witsmlMarker = repo->createWellboreMarker("c08339bc-acf7-49e7-90c8-cf4e275705bd", "WITSML marker", 350, gsoap_eml2_1::eml21__LengthUom__m, "my datum");
	witsmlMarker->setDipAngle(5, gsoap_eml2_1::eml21__PlaneAngleUom__dega);
	witsmlMarker->setDipDirection(10, gsoap_eml2_1::eml21__PlaneAngleUom__dega);
	resqmlMarker->setWitsmlWellboreMarker(witsmlMarker);
}

void WellboreMarkerFrameRepresentationTest::readRepo() {
	WellboreMarkerFrameRepresentation* wmf = repo->getDataObjectByUuid<WellboreMarkerFrameRepresentation>(defaultUuid);
	REQUIRE(wmf != nullptr);
	const auto mdCount = wmf->getWellboreMarkerCount();
	REQUIRE(mdCount == 2);
	
	auto resqmlMarker = wmf->getWellboreMarkerSet()[0];
	REQUIRE(resqmlMarker->getWellboreMarkerFrameRepresentation() == wmf);
	REQUIRE(resqmlMarker->getGeologicBoundaryKind() == gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind__horizon);
	REQUIRE(resqmlMarker->getWitsmlWellboreMarker() != nullptr);
	REQUIRE(resqmlMarker->hasDipAngle());
	REQUIRE(resqmlMarker->getDipAngleValue() == 5);
	REQUIRE(resqmlMarker->getDipAngleUom() == gsoap_eml2_1::eml21__PlaneAngleUom__dega);
	REQUIRE(resqmlMarker->getDipAngleUomAsString() == "dega");
	REQUIRE(resqmlMarker->hasDipDirection());
	REQUIRE(resqmlMarker->getDipDirectionValue() == 10);
	REQUIRE(resqmlMarker->getDipDirectionUom() == gsoap_eml2_1::eml21__PlaneAngleUom__dega);
	REQUIRE(resqmlMarker->getDipDirectionUomAsString() == "dega");

	resqmlMarker = wmf->getWellboreMarkerSet()[1];
	REQUIRE(resqmlMarker->getWellboreMarkerFrameRepresentation() == wmf);
	REQUIRE(resqmlMarker->getGeologicBoundaryKind() == gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind__fault);
	REQUIRE(resqmlMarker->getWitsmlWellboreMarker() == nullptr);
	REQUIRE(!resqmlMarker->hasDipAngle());
	REQUIRE_THROWS(resqmlMarker->getDipAngleValue() == 5);
	REQUIRE_THROWS(resqmlMarker->getDipAngleUom() == gsoap_eml2_1::eml21__PlaneAngleUom__dega);
	REQUIRE_THROWS(resqmlMarker->getDipAngleUomAsString() == "dega");
	REQUIRE(!resqmlMarker->hasDipDirection());
	REQUIRE_THROWS(resqmlMarker->getDipDirectionValue() == 10);
	REQUIRE_THROWS(resqmlMarker->getDipDirectionUom() == gsoap_eml2_1::eml21__PlaneAngleUom__dega);
	REQUIRE_THROWS(resqmlMarker->getDipDirectionUomAsString() == "dega");

	std::unique_ptr<double[]> xyzPoints(new double[mdCount*3]);
	wmf->getXyzPointsOfPatch(0, xyzPoints.get());
	REQUIRE(xyzPoints[0] == 275.0);
	REQUIRE(xyzPoints[1] == 75.0);
	REQUIRE(xyzPoints[2] == 350.0);
	REQUIRE(xyzPoints[3] == 275.0);
	REQUIRE(xyzPoints[4] == 75.0);
	REQUIRE(xyzPoints[5] == 550.0);
}
