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
#include "FaultSinglePatchTriangulatedSetRepresentationTest.h"
#include "../catch.hpp"
#include "resqml2/TriangulatedSetRepresentation.h"
#include "resqml2_0_1/FaultInterpretation.h"
#include "eml2/AbstractHdfProxy.h"
#include "FaultInterpretationTest.h"

using namespace std;
using namespace resqml2_test;
using namespace COMMON_NS;
using namespace RESQML2_NS;

FaultSinglePatchTriangulatedSetRepresentationTest::FaultSinglePatchTriangulatedSetRepresentationTest(const string & repoPath)
	: commontest::AbstractTest(repoPath)
{
}

void FaultSinglePatchTriangulatedSetRepresentationTest::initRepo()
{
	FaultInterpretation* interp = repo->getDataObjectByUuid<FaultInterpretation>(FaultInterpretationTest::defaultUuid);
	if (interp == nullptr) {
		interp = repo->createPartial<RESQML2_0_1_NS::FaultInterpretation>(FaultInterpretationTest::defaultUuid, "");
	}

	TriangulatedSetRepresentation* rep = repo->createTriangulatedSetRepresentation(interp, defaultUuid, defaultTitle);
	REQUIRE( rep != nullptr );

	rep->pushBackTrianglePatch(18, nodesFaultSinglePatchTriangulatedSetRepresentation, 20, triangleNodeIndexFault, repo->getHdfProxySet()[0]);
}

void FaultSinglePatchTriangulatedSetRepresentationTest::readRepo()
{
	RESQML2_NS::TriangulatedSetRepresentation* rep = repo->getDataObjectByUuid<RESQML2_NS::TriangulatedSetRepresentation>(defaultUuid);
	REQUIRE(rep->getSeismicSupportOfPatch(0) == nullptr);
	REQUIRE(rep->getPatchCount() == 1);
	REQUIRE(rep->getRepresentationSetRepresentationCount() == 0);
	REQUIRE(rep->getPropertySet().empty());
	REQUIRE(rep->getPointsPropertyCount() == 0);
	REQUIRE(rep->getSubRepresentationCount() == 0);
	REQUIRE(rep->getValuesPropertyCount() == 0);
	REQUIRE(rep->getTimeSeries() == nullptr);
	REQUIRE(rep->getTitle() == defaultTitle);
	REQUIRE(rep->getUuid() == defaultUuid);
	REQUIRE(rep->getTriangleCountOfPatch(0) == 20);
	REQUIRE_THROWS(rep->getTriangleCountOfPatch(1) == 20);
	REQUIRE(rep->getTriangleCountOfAllPatches() == 20);
	REQUIRE(rep->getXyzPointCountOfPatch(0) == 18);
	REQUIRE_THROWS(rep->getXyzPointCountOfPatch(1) == 18);
	REQUIRE(rep->getXyzPointCountOfAllPatches() == 18);

	uint32_t triangleNodeIndexFault2[60];
	rep->getTriangleNodeIndicesOfPatch(0, triangleNodeIndexFault2);
	REQUIRE(std::equal(begin(triangleNodeIndexFault), end(triangleNodeIndexFault), begin(triangleNodeIndexFault2)));

	double nodesFaultSinglePatchTriangulatedSetRepresentation2[54];
	rep->getXyzPointsOfPatch(0, nodesFaultSinglePatchTriangulatedSetRepresentation2);
	REQUIRE(std::equal(begin(nodesFaultSinglePatchTriangulatedSetRepresentation), end(nodesFaultSinglePatchTriangulatedSetRepresentation), begin(nodesFaultSinglePatchTriangulatedSetRepresentation2)));
}
