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
#include "resqml2_2test/SeismicWellboreFrameRepresentationTest.h"

#include "catch.hpp"

#include "resqml2_test/WellboreTrajectoryRepresentationTest.h"
#include "resqml2_test/LocalTime3dCrs.h"

#include "resqml2_2/WellboreInterpretation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "eml2/AbstractHdfProxy.h"
#include "resqml2_2/SeismicWellboreFrameRepresentation.h"
#include "resqml2_0_1/LocalTime3dCrs.h"

using namespace std;
using namespace COMMON_NS;
using namespace RESQML2_NS;
using namespace EML2_NS;
using namespace resqml2_2test;

const char* SeismicWellboreFrameRepresentationTest::defaultUuid = "ff2997a8-fe34-4ea9-bc11-e1cedf2da42c";
const char* SeismicWellboreFrameRepresentationTest::defaultTitle = "SeismicWellbore Frame Representation";

SeismicWellboreFrameRepresentationTest::SeismicWellboreFrameRepresentationTest(const string & epcDocPath)
	: commontest::AbstractTest(epcDocPath) {
}

void SeismicWellboreFrameRepresentationTest::initRepo() {
	WellboreInterpretation* interp = repo->createPartial<RESQML2_2_NS::WellboreInterpretation>("", "");
	WellboreTrajectoryRepresentation * traj = repo->createPartial<RESQML2_0_1_NS::WellboreTrajectoryRepresentation>("", "");

	// getting the hdf proxy
	EML2_NS::AbstractHdfProxy* hdfProxy = repo->getHdfProxySet()[0];
	REQUIRE(hdfProxy != nullptr);

	// getting the local time crs
	RESQML2_NS::LocalTime3dCrs* crs = repo->getDataObjectByUuid<RESQML2_NS::LocalTime3dCrs>(resqml2_test::LocalTime3dCrs::defaultUuid);
	if (crs == nullptr) {
		crs = repo->createPartial<RESQML2_0_1_NS::LocalTime3dCrs>("", "");
	}

	// WellboreFeature frame
	RESQML2_NS::SeismicWellboreFrameRepresentation* w1i1SeismicFrameRep = repo->createSeismicWellboreFrameRepresentation(interp, defaultUuid, defaultTitle, traj, 0., 0., crs);
	double logMds[5] = { 0, 250, 500, 750, 1200 };
	w1i1SeismicFrameRep->setMdValues(logMds, 5, hdfProxy);
	double logTimes[5] = { 0., 10., 20., 25., 30. };
	w1i1SeismicFrameRep->setTimeValues(logTimes, 5, hdfProxy);
}

void SeismicWellboreFrameRepresentationTest::readRepo() {
	RESQML2_2_NS::SeismicWellboreFrameRepresentation* w1i1SeismicFrameRep = repo->getDataObjectByUuid<RESQML2_2_NS::SeismicWellboreFrameRepresentation>(defaultUuid);
	REQUIRE(w1i1SeismicFrameRep != nullptr);

	REQUIRE(w1i1SeismicFrameRep->areMdValuesRegularlySpaced() == false);
	REQUIRE(w1i1SeismicFrameRep->getMdValuesCount() == 5);

	std::unique_ptr<double[]> logMds(new double[w1i1SeismicFrameRep->getMdValuesCount()]);

	w1i1SeismicFrameRep->getMdAsDoubleValues(logMds.get());
	REQUIRE(logMds[0] == .0);
	REQUIRE(logMds[1] == 250);
	REQUIRE(logMds[2] == 500);
	REQUIRE(logMds[3] == 750);
	REQUIRE(logMds[4] == 1200);

	std::unique_ptr<double[]> logTimes(new double[w1i1SeismicFrameRep->getTimeValuesCount()]);

	w1i1SeismicFrameRep->getTimeAsDoubleValues(logTimes.get());
	REQUIRE(logTimes[0] == 0.);
	REQUIRE(logTimes[1] == 10.);
	REQUIRE(logTimes[2] == 20.);
	REQUIRE(logTimes[3] == 25.);
	REQUIRE(logTimes[4] == 30.);

	REQUIRE(w1i1SeismicFrameRep->getSeismicReferenceDatum() == 0.);
	REQUIRE(w1i1SeismicFrameRep->getWeatheringVelocity() == 0.);	
}
