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
#include "resqml2_2test/WellboreFrameRepresentationTest.h"

#include "catch.hpp"

#include "resqml2_test/WellboreTrajectoryRepresentationTest.h"

#include "resqml2_2/WellboreInterpretation.h"
#include "resqml2_2/WellboreTrajectoryRepresentation.h"
#include "resqml2/WellboreFrameRepresentation.h"
#include "eml2/AbstractHdfProxy.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_2test;

const char* WellboreFrameRepresentationTest::defaultUuid = "0047500b-cf08-47c0-89e0-84f330c7e132";
const char* WellboreFrameRepresentationTest::defaultTitle = "Wellbore Frame Representation";

WellboreFrameRepresentationTest::WellboreFrameRepresentationTest(const string & epcDocPath)
	: commontest::AbstractTest(epcDocPath) {
}

void WellboreFrameRepresentationTest::initRepo() {
	RESQML2_NS::WellboreInterpretation* interp = repo->createPartial<RESQML2_2_NS::WellboreInterpretation>("", "");
	RESQML2_NS::WellboreTrajectoryRepresentation * traj = repo->createPartial<RESQML2_2_NS::WellboreTrajectoryRepresentation>(resqml2_test::WellboreTrajectoryRepresentationTest::defaultUuid, "");

	// getting the hdf proxy
	EML2_NS::AbstractHdfProxy* hdfProxy = repo->getHdfProxySet()[0];
	REQUIRE(hdfProxy != nullptr);

	// WellboreFeature frame
	RESQML2_NS::WellboreFrameRepresentation* w1i1FrameRep = repo->createWellboreFrameRepresentation(interp, defaultUuid, defaultTitle, traj);
	double logMds[5] = { 0, 250, 500, 750, 1200 };
	w1i1FrameRep->setMdValues(logMds, 5, hdfProxy);
}

void WellboreFrameRepresentationTest::readRepo() {
	RESQML2_NS::WellboreFrameRepresentation* w1i1FrameRep = repo->getDataObjectByUuid<RESQML2_NS::WellboreFrameRepresentation>(defaultUuid);
	REQUIRE(w1i1FrameRep != nullptr);

	RESQML2_NS::WellboreTrajectoryRepresentation* traj = repo->getDataObjectByUuid<RESQML2_NS::WellboreTrajectoryRepresentation>(resqml2_test::WellboreTrajectoryRepresentationTest::defaultUuid);
	RESQML2_NS::WellboreFrameRepresentation* w1i1FrameRepFromTraj = traj->getWellboreFrameRepresentation(0);	
	REQUIRE(w1i1FrameRep->getUuid() == w1i1FrameRepFromTraj->getUuid());

	REQUIRE(w1i1FrameRep->areMdValuesRegularlySpaced() == false);
	REQUIRE(w1i1FrameRep->getMdValuesCount() == 5);

	std::unique_ptr<double[]> logMds(new double[w1i1FrameRep->getMdValuesCount()]);

	w1i1FrameRep->getMdAsDoubleValues(logMds.get());
	REQUIRE(logMds[0] == .0);
	REQUIRE(logMds[1] == 250);
	REQUIRE(logMds[2] == 500);
	REQUIRE(logMds[3] == 750);
	REQUIRE(logMds[4] == 1200);
}
