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
#include "FaultMultiPatchTriangulatedSetRepresentationTest.h"
#include "../catch.hpp"
#include "resqml2/TriangulatedSetRepresentation.h"
#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2/LocalDepth3dCrs.h"
#include "eml2/AbstractHdfProxy.h"
#include "resqml2_test/FaultInterpretationTest.h"
#include "resqml2_test/LocalDepth3dCrsTest.h"

using namespace std;
using namespace resqml2_test;
using namespace COMMON_NS;
using namespace RESQML2_NS;

const char* FaultMultiPatchTriangulatedSetRepresentationTest::defaultUuid = "4b8503e8-28e5-44c5-877d-b9eb3295b2b9";
const char* FaultMultiPatchTriangulatedSetRepresentationTest::defaultTitle = "FaultMultiPatchTriangulatedSetRepresentationTest";

FaultMultiPatchTriangulatedSetRepresentationTest::FaultMultiPatchTriangulatedSetRepresentationTest(const string & repoPath)
	: commontest::AbstractTest(repoPath)
{
}

void FaultMultiPatchTriangulatedSetRepresentationTest::initRepo()
{
	FaultInterpretation* interp = repo->createPartial<RESQML2_0_1_NS::FaultInterpretation>(FaultInterpretationTest::defaultUuid, "");

	TriangulatedSetRepresentation* rep = repo->createTriangulatedSetRepresentation(interp, defaultUuid, defaultTitle);
	REQUIRE( rep != nullptr );

	// Patch 0
	double explicitPointsFault1Patch0[18] = {150, 0, 200, 150, 100, 200, 150, 200, 200,
		250, 0, 300, 250, 100, 300, 250, 200, 300};
	unsigned int triangleNodeIndexFaultPatch0[12] = {0,4,3, 0,1,4, 1,2,4, 2,5,4};
	rep->pushBackTrianglePatch(6, explicitPointsFault1Patch0, 4, triangleNodeIndexFaultPatch0, repo->getHdfProxySet()[0]);
	// Patch 1
	double explicitPointsFault1Patch1[18] = {250, 0, 300, 250, 100, 300, 250, 200, 300,
		300, 0, 350, 300, 100, 350, 300, 200, 350};
	unsigned int triangleNodeIndexFaultPatch1[12] = {6,10,9, 6,7,10, 7,8,10, 8,11,10};
	rep->pushBackTrianglePatch(6, explicitPointsFault1Patch1, 4, triangleNodeIndexFaultPatch1, repo->getHdfProxySet()[0]);
	// Patch 2
	double explicitPointsFault1Patch2[18] = {300, 0, 350, 300, 100, 350, 300, 200, 350,
		450, 0, 500, 450, 100, 500, 450, 200, 500};
	unsigned int triangleNodeIndexFaultPatch2[12] = {12,16,15, 12,13,16, 13,14,16, 14,17,16};
	rep->pushBackTrianglePatch(6, explicitPointsFault1Patch2, 4, triangleNodeIndexFaultPatch2, repo->getHdfProxySet()[0]);
	// Patch 3
	double explicitPointsFault1Patch3[18] = {450, 0, 500, 450, 100, 500, 450, 200, 500,
		500, 0, 550, 500, 100, 550 ,500, 200, 550};
	unsigned int triangleNodeIndexFaultPatch3[12] = {18,22,21, 18,19,22, 19,20,22, 20,23,22};
	rep->pushBackTrianglePatch(6, explicitPointsFault1Patch3, 4, triangleNodeIndexFaultPatch3, repo->getHdfProxySet()[0]);
	// Patch 4
	double explicitPointsFault1Patch4[18] = {500, 0, 550, 500, 100, 550 ,500, 200, 550,
		600, 0, 650, 600, 100, 650, 600, 200, 650};
	unsigned int triangleNodeIndexFaultPatch4[12] = {24,28,27, 24,25,28, 25,26,28, 26,29,28};
	rep->pushBackTrianglePatch(6, explicitPointsFault1Patch4, 4, triangleNodeIndexFaultPatch4, repo->getHdfProxySet()[0]);
}

void FaultMultiPatchTriangulatedSetRepresentationTest::readRepo()
{
}
