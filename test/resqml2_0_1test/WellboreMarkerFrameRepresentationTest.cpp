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
#include "resqml2_0_1test/WellboreMarkerFrameRepresentationTest.h"

#include "catch.hpp"

#include "resqml2_0_1test/WellboreInterpretationTest.h"
#include "resqml2_0_1test/WellboreTrajectoryRepresentationTest.h"

#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"
#include "resqml2_0_1/WellboreMarker.h"

using namespace std;
using namespace COMMON_NS;
using namespace RESQML2_0_1_NS;
using namespace resqml2_0_1test;

const char* WellboreMarkerFrameRepresentationTest::defaultUuid = "8f1c7e38-afc7-4cb8-86bb-a116e9135de4";
const char* WellboreMarkerFrameRepresentationTest::defaultTitle = "Wellbore Marker Frame Representation";

WellboreMarkerFrameRepresentationTest::WellboreMarkerFrameRepresentationTest(const string & repoPath)
	: commontest::AbstractObjectTest(repoPath) {
}

WellboreMarkerFrameRepresentationTest::WellboreMarkerFrameRepresentationTest(DataObjectRepository * repo)
	: commontest::AbstractObjectTest(repo) {
}

void WellboreMarkerFrameRepresentationTest::initRepoHandler() {
	// creating dependencies
	WellboreTrajectoryRepresentationTest trajTest(repo, true);

	WellboreInterpretation * interp = repo->getDataObjectByUuid<WellboreInterpretation>(WellboreInterpretationTest::defaultUuid);
	WellboreTrajectoryRepresentation * traj = repo->getDataObjectByUuid<WellboreTrajectoryRepresentation>(WellboreTrajectoryRepresentationTest::defaultUuid);

	// WellboreFeature marker frame
	WellboreMarkerFrameRepresentation* wmf = repo->createWellboreMarkerFrameRepresentation(interp, defaultUuid, defaultTitle, traj);
	double markerMdValues[2] = { 350, 550 };
	wmf->setMdValues(markerMdValues, 2, repo->getHdfProxySet()[0]);
	repo->createWellboreMarker(wmf, "", "", gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind__horizon);
	repo->createWellboreMarker(wmf, "", "testing Fault", gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind__fault);
}

void WellboreMarkerFrameRepresentationTest::readRepoHandler() {
	WellboreMarkerFrameRepresentation* wmf = repo->getDataObjectByUuid<WellboreMarkerFrameRepresentation>(defaultUuid);
	REQUIRE(wmf != nullptr);
	REQUIRE(wmf->getWellboreMarkerCount() == 2);
	REQUIRE((wmf->getWellboreMarkerSet()[0])->getGeologicBoundaryKind() == gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind__horizon);
	REQUIRE((wmf->getWellboreMarkerSet()[1])->getGeologicBoundaryKind() == gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind__fault);
}
