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
#include "resqml2_test/HorizonOnSeismicLine.h"
#include "../catch.hpp"

#include "resqml2/AbstractLocal3dCrs.h"
#include "resqml2_0_1/PolylineRepresentation.h"
#include "resqml2_0_1/HorizonInterpretation.h"
#include "resqml2/LocalDepth3dCrs.h"
#include "eml2/AbstractHdfProxy.h"
#include "resqml2_test/HorizonInterpretationTest.h"
#include "resqml2_test/SeismicLineRepresentationTest.h"
#include "LocalDepth3dCrsTest.h"

using namespace std;
using namespace resqml2_test;
using namespace COMMON_NS;
using namespace RESQML2_NS;

const char* HorizonOnSeismicLine::defaultUuid = "c9bea300-6231-4acb-8b7c-77e4099224d4";
const char* HorizonOnSeismicLine::defaultTitle = "Horizon on seismic line";
double HorizonOnSeismicLine::defaultXyzPoints[12] = { 0, 100, 300, 150, 110, 300, 450, 130, 350, 600, 140, 350 };

HorizonOnSeismicLine::HorizonOnSeismicLine(const string & repoPath)
	: commontest::AbstractTest(repoPath)
{
}

void HorizonOnSeismicLine::initRepo()
{
	EML2_NS::AbstractHdfProxy* hdfProxy = repo->getHdfProxy(0);

	HorizonInterpretation* horizonInterp = repo->getDataObjectByUuid<HorizonInterpretation>(HorizonInterpretationTest::defaultUuid);
	if (horizonInterp == nullptr) {
		horizonInterp = repo->createPartial<RESQML2_0_1_NS::HorizonInterpretation>(HorizonInterpretationTest::defaultUuid, "");
	}
	
	PolylineRepresentation* seismicLineRep = repo->getDataObjectByUuid<PolylineRepresentation>(SeismicLineRepresentationTest::defaultUuid);
	if (seismicLineRep == nullptr) {
		seismicLineRep = repo->createPartial<RESQML2_0_1_NS::PolylineRepresentation>(SeismicLineRepresentationTest::defaultUuid, "");
	}

	PolylineRepresentation* h1i1SinglePolylineRep = repo->createPolylineRepresentation(horizonInterp, defaultUuid, defaultTitle);
	h1i1SinglePolylineRep->setGeometry(defaultXyzPoints, 4, hdfProxy);
	double seismicLineAbscissa[4] = { 0.0, 1.0, 3.0, 4.0 };
	h1i1SinglePolylineRep->addSeismic2dCoordinatesToPatch(0, seismicLineAbscissa, seismicLineRep, hdfProxy);
}

void HorizonOnSeismicLine::readRepo()
{
	PolylineRepresentation* h1i1SinglePolylineRep = repo->getDataObjectByUuid<PolylineRepresentation>(defaultUuid);
	REQUIRE(h1i1SinglePolylineRep->getSeismicSupportOfPatch(0) != nullptr);

	double seismicLineAbscissa[4] = { -1.0, -1.0, -1.0, -1.0 };
	h1i1SinglePolylineRep->getSeismicLineAbscissaOfPointsOfPatch(0, seismicLineAbscissa);
	REQUIRE(seismicLineAbscissa[0] == 0.0);
	REQUIRE(seismicLineAbscissa[1] == 1.0);
	REQUIRE(seismicLineAbscissa[2] == 3.0);
	REQUIRE(seismicLineAbscissa[3] == 4.0);
}
