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
#include "resqml2_test/Grid2dRepresentationTest.h"
#include "../catch.hpp"
#include "resqml2/BoundaryFeature.h"
#include "resqml2/HorizonInterpretation.h"
#include "resqml2_0_1/Grid2dRepresentation.h"
#include "resqml2/LocalDepth3dCrs.h"
#include "eml2/AbstractHdfProxy.h"
#include "resqml2_test/SeismicLatticeRepresentationTest.h"
#include "resqml2_test/LocalDepth3dCrsTest.h"
#include "resqml2/SeismicLatticeFeature.h"
#include "resqml2/GenericFeatureInterpretation.h"

using namespace std;
using namespace resqml2_test;
using namespace COMMON_NS;
using namespace RESQML2_NS;

const char* Grid2dRepresentationTest::defaultUuidFeature = "25ecaf5e-90f2-482f-a3cc-9707b772f62d";
const char* Grid2dRepresentationTest::defaultTitleFeature = "Horizon Feature";
const char* Grid2dRepresentationTest::defaultUuidInterp = "d058e544-2946-4bb4-a0e4-ed19e9cbc84e";
const char* Grid2dRepresentationTest::defaultTitleInterp = "Horizon Interp";
const char* Grid2dRepresentationTest::defaultUuid = "6cbfb84d-f5c8-4595-9e7f-b003d0fe81c2";
const char* Grid2dRepresentationTest::defaultTitle = "Grid 2d Representation";

Grid2dRepresentationTest::Grid2dRepresentationTest(const string & repoPath)
	: commontest::AbstractTest(repoPath)
{
}

void Grid2dRepresentationTest::initRepo()
{
	BoundaryFeature* feature = repo->createHorizon(defaultUuidFeature, defaultTitleFeature);
	HorizonInterpretation* interp = repo->createHorizonInterpretation(feature, defaultUuidInterp, defaultTitleInterp);
	Grid2dRepresentation* rep = repo->createGrid2dRepresentation(interp, defaultUuid, defaultTitle);

	// Supporting lattice
	SeismicLatticeFeature* seismicLattice = repo->createSeismicLattice("", "", 2, 2, 150, 152, 4, 2);
	GenericFeatureInterpretation* seismicLatticeInterp = repo->createGenericFeatureInterpretation(seismicLattice, "", "");
	Grid2dRepresentation* supportingRep = repo->createGrid2dRepresentation(seismicLatticeInterp, "", "");
	supportingRep->setGeometryAsArray2dOfLatticePoints3d(4, 2, 0, 0, 0, 1, 0, 0, 0, 1, 0, 250, 200);

	double zValues[8] = { 300, 300, 350, 350, 300, 300, 350, 350 };
	rep->setGeometryAsArray2dOfExplicitZ(zValues, 4, 2, repo->getHdfProxySet()[0], supportingRep);
}

void Grid2dRepresentationTest::readRepo()
{
	// Grid 2D
	RESQML2_NS::Grid2dRepresentation* rep = repo->getDataObjectByUuid<RESQML2_NS::Grid2dRepresentation>(defaultUuid);
	REQUIRE(rep->getSupportingRepresentation() != nullptr);
	REQUIRE(rep->getSeismicSupportOfPatch(0) == nullptr);
	REQUIRE((rep->isISpacingConstant() && rep->isJSpacingConstant()));
	REQUIRE(rep->getXOrigin() == .0);
	REQUIRE(rep->getXOriginInGlobalCrs() == 1000);
	REQUIRE(rep->getYOrigin() == .0);
	REQUIRE(rep->getYOriginInGlobalCrs() == 2000);
	REQUIRE(rep->getNodeCountAlongIAxis() == 4);
	REQUIRE(rep->getNodeCountAlongJAxis() == 2);
	REQUIRE(rep->getISpacing() == 250.0);
	REQUIRE(rep->getJSpacing() == 200.0);
	REQUIRE(rep->getIndexOriginOnSupportingRepresentation() == 0);
	REQUIRE(rep->getIndexOffsetOnSupportingRepresentation(0) == 1);
	REQUIRE(rep->getNodeCountOnSupportingRepresentation(1) == 4);

	double zValues[8];
	rep->getZValues(zValues);
	REQUIRE(zValues[0] == 300);
	REQUIRE(zValues[1] == 300);
	REQUIRE(zValues[2] == 350);
	REQUIRE(zValues[3] == 350);
	REQUIRE(zValues[4] == 300);
	REQUIRE(zValues[5] == 300);
	REQUIRE(zValues[6] == 350);
	REQUIRE(zValues[7] == 350);
	rep->getZValuesInGlobalCrs(zValues);
	REQUIRE(zValues[0] == 3300);
	REQUIRE(zValues[1] == 3300);
	REQUIRE(zValues[2] == 3350);
	REQUIRE(zValues[3] == 3350);
	REQUIRE(zValues[4] == 3300);
	REQUIRE(zValues[5] == 3300);
	REQUIRE(zValues[6] == 3350);
	REQUIRE(zValues[7] == 3350);
}
