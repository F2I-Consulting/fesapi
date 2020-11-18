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
#include "resqml2_test/WellboreRegularFrameRepresentationTest.h"

#include "catch.hpp"

#include "resqml2_test/WellboreTrajectoryRepresentationTest.h"

#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2/WellboreMarkerFrameRepresentation.h"
#include "eml2/AbstractHdfProxy.h"

using namespace std;
using namespace COMMON_NS;
using namespace RESQML2_NS;
using namespace resqml2_test;

const char* WellboreRegularFrameRepresentationTest::defaultUuid = "bbcacfa6-b117-467f-8514-02660df62270";
const char* WellboreRegularFrameRepresentationTest::defaultTitle = "Wellbore Regular Frame Representation";

WellboreRegularFrameRepresentationTest::WellboreRegularFrameRepresentationTest(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void WellboreRegularFrameRepresentationTest::initRepo() {
	WellboreInterpretation* interp = repo->createPartial<RESQML2_0_1_NS::WellboreInterpretation>("", "");
	WellboreTrajectoryRepresentation * traj = repo->createPartial<RESQML2_0_1_NS::WellboreTrajectoryRepresentation>(WellboreTrajectoryRepresentationTest::defaultUuid, "");

	// getting the hdf proxy
	EML2_NS::AbstractHdfProxy* hdfProxy = repo->getHdfProxySet()[0];
	REQUIRE(hdfProxy != nullptr);

	// WellboreFeature frame
#if WITH_EXPERIMENTAL
	RESQML2_NS::WellboreFrameRepresentation* w1i1FrameRep = repo->createWellboreFrameRepresentation(interp, defaultUuid, defaultTitle, traj, true);
#else
	RESQML2_NS::WellboreFrameRepresentation* w1i1FrameRep = repo->createWellboreFrameRepresentation(interp, defaultUuid, defaultTitle, traj);
#endif
	w1i1FrameRep->setMdValues(0, 200, 6);
}

void WellboreRegularFrameRepresentationTest::readRepo() {
	WellboreFrameRepresentation* w1i1FrameRep = repo->getDataObjectByUuid<WellboreFrameRepresentation>(defaultUuid);
	REQUIRE(w1i1FrameRep != nullptr);

	REQUIRE(w1i1FrameRep->areMdValuesRegularlySpaced());
	REQUIRE(w1i1FrameRep->getMdValuesCount() == 6);

	REQUIRE(w1i1FrameRep->getMdFirstValue() == .0);
	REQUIRE(w1i1FrameRep->getMdConstantIncrementValue() == 200);
}
