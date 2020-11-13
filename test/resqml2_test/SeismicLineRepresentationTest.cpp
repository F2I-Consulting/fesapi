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
#include "resqml2_test/SeismicLineRepresentationTest.h"
#include "../catch.hpp"
#include "resqml2_0_1/SeismicLineFeature.h"
#include "resqml2/GenericFeatureInterpretation.h"
#include "resqml2/PolylineRepresentation.h"
#include "resqml2/LocalDepth3dCrs.h"
#include "eml2/AbstractHdfProxy.h"
#include "resqml2_test/LocalDepth3dCrsTest.h"

using namespace std;
using namespace resqml2_test;
using namespace COMMON_NS;

const char* SeismicLineRepresentationTest::defaultUuidFeatureSet = "4b463e9b-0369-40e7-a3c0-0f0d4b228a21";
const char* SeismicLineRepresentationTest::defaultTitleFeatureSet = "Seismic Line Set Feature";
const char* SeismicLineRepresentationTest::defaultUuidFeature = "88cbfbc8-d20f-4342-b6a3-e0fdc655fb38";
const char* SeismicLineRepresentationTest::defaultTitleFeature = "Seismic Line Feature";
const char* SeismicLineRepresentationTest::defaultUuidInterp = "195e8333-a2bd-4948-8940-6da8c5773eff";
const char* SeismicLineRepresentationTest::defaultTitleInterp = "Seismic Line Interp";
const char* SeismicLineRepresentationTest::defaultUuid = "99bd4f3e-8f52-43ae-98fb-ab60371e838e";
const char* SeismicLineRepresentationTest::defaultTitle = "Seismic Line Representation";

SeismicLineRepresentationTest::SeismicLineRepresentationTest(const string & repoPath)
	: commontest::AbstractTest(repoPath)
{
}

void SeismicLineRepresentationTest::initRepo()
{
	RESQML2_NS::SeismicLineSetFeature* seismicLineSet = repo->createSeismicLineSet(defaultUuidFeatureSet, defaultTitleFeatureSet);

	// Seismic Line
	RESQML2_0_1_NS::SeismicLineFeature* seismicLine = repo->createSeismicLine(defaultUuidFeature, defaultTitleFeature, 1, 0, 5);
	seismicLine->setSeismicLineSet(seismicLineSet);
	RESQML2_NS::GenericFeatureInterpretation* seismicLineInterp = repo->createGenericFeatureInterpretation(seismicLine, defaultUuidInterp, defaultTitleInterp);
	RESQML2_NS::PolylineRepresentation* seismicLineRep = repo->createPolylineRepresentation(seismicLineInterp, defaultUuid, defaultTitle);
	double seismicLinePoints[15] = { 0, 100, 0, 150, 110, 0, 300, 120, 0, 450, 130, 0, 600, 140, 0 };
	seismicLineRep->setGeometry(seismicLinePoints, 5, nullptr);
}

void SeismicLineRepresentationTest::readRepo()
{
	// Feature
	RESQML2_0_1_NS::SeismicLineFeature* feature = repo->getDataObjectByUuid<RESQML2_0_1_NS::SeismicLineFeature>(defaultUuidFeature);
	REQUIRE(feature->getFirstTraceIndex() == 0);
	REQUIRE(feature->getTraceCount() == 5);
	REQUIRE(feature->getTraceIndexIncrement() == 1);

	// Grid 2D
	RESQML2_NS::PolylineRepresentation* rep = repo->getDataObjectByUuid<RESQML2_NS::PolylineRepresentation>(defaultUuid);
	REQUIRE(rep->getSeismicSupportOfPatch(0) == nullptr);
	REQUIRE(rep->getXyzPointCountOfAllPatches() == 5);
}
