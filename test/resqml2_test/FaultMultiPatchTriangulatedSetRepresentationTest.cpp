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
#include "eml2/AbstractHdfProxy.h"
#include "resqml2_test/FaultInterpretationTest.h"

using namespace std;
using namespace resqml2_test;
using namespace COMMON_NS;
using namespace RESQML2_NS;

FaultMultiPatchTriangulatedSetRepresentationTest::FaultMultiPatchTriangulatedSetRepresentationTest(const string & repoPath)
	: commontest::AbstractTest(repoPath)
{
}

void FaultMultiPatchTriangulatedSetRepresentationTest::initRepo()
{
	FaultInterpretation* interp = repo->createPartial<RESQML2_0_1_NS::FaultInterpretation>(FaultInterpretationTest::defaultUuid, "");

	TriangulatedSetRepresentation* rep = repo->createTriangulatedSetRepresentation(interp, defaultUuid, defaultTitle);
	REQUIRE( rep != nullptr );

	rep->pushBackTrianglePatch(6, explicitPointsFault1Patch0, 4, triangleNodeIndexFaultPatch0, repo->getHdfProxySet()[0]);
	rep->pushBackTrianglePatch(6, explicitPointsFault1Patch1, 4, triangleNodeIndexFaultPatch1, repo->getHdfProxySet()[0]);
	rep->pushBackTrianglePatch(6, explicitPointsFault1Patch2, 4, triangleNodeIndexFaultPatch2, repo->getHdfProxySet()[0]);
	rep->pushBackTrianglePatch(6, explicitPointsFault1Patch3, 4, triangleNodeIndexFaultPatch3, repo->getHdfProxySet()[0]);
	rep->pushBackTrianglePatch(6, explicitPointsFault1Patch4, 4, triangleNodeIndexFaultPatch4, repo->getHdfProxySet()[0]);
}

void FaultMultiPatchTriangulatedSetRepresentationTest::readRepo()
{
	RESQML2_NS::TriangulatedSetRepresentation* rep = repo->getDataObjectByUuid<RESQML2_NS::TriangulatedSetRepresentation>(defaultUuid);
	REQUIRE(rep->getSeismicSupportOfPatch(0) == nullptr);
	REQUIRE(rep->getPatchCount() == 5);
	REQUIRE(rep->getRepresentationSetRepresentationCount() == 0);
	REQUIRE(rep->getPropertySet().empty());
	REQUIRE(rep->getPointsPropertyCount() == 0);
	REQUIRE(rep->getSubRepresentationCount() == 0);
	REQUIRE(rep->getValuesPropertyCount() == 0);
	REQUIRE(rep->getTimeSeries() == nullptr);
	REQUIRE(rep->getTitle() == defaultTitle);
	REQUIRE(rep->getUuid() == defaultUuid);
	for (size_t patchIdx = 0; patchIdx < 5; ++patchIdx) {
		REQUIRE(rep->getTriangleCountOfPatch(patchIdx) == 4);
		REQUIRE(rep->getXyzPointCountOfPatch(0) == 6);
	}
	REQUIRE(rep->getTriangleCountOfAllPatches() == 20);
	REQUIRE(rep->getXyzPointCountOfAllPatches() == 30);

	uint32_t triangleNodeIndexFaultPatch[12];
	rep->getTriangleNodeIndicesOfPatch(0, triangleNodeIndexFaultPatch);
	REQUIRE(std::equal(begin(triangleNodeIndexFaultPatch0), end(triangleNodeIndexFaultPatch0), begin(triangleNodeIndexFaultPatch)));
	rep->getTriangleNodeIndicesOfPatch(1, triangleNodeIndexFaultPatch);
	REQUIRE(std::equal(begin(triangleNodeIndexFaultPatch1), end(triangleNodeIndexFaultPatch1), begin(triangleNodeIndexFaultPatch)));
	rep->getTriangleNodeIndicesOfPatch(2, triangleNodeIndexFaultPatch);
	REQUIRE(std::equal(begin(triangleNodeIndexFaultPatch2), end(triangleNodeIndexFaultPatch2), begin(triangleNodeIndexFaultPatch)));
	rep->getTriangleNodeIndicesOfPatch(3, triangleNodeIndexFaultPatch);
	REQUIRE(std::equal(begin(triangleNodeIndexFaultPatch3), end(triangleNodeIndexFaultPatch3), begin(triangleNodeIndexFaultPatch)));
	rep->getTriangleNodeIndicesOfPatch(4, triangleNodeIndexFaultPatch);
	REQUIRE(std::equal(begin(triangleNodeIndexFaultPatch4), end(triangleNodeIndexFaultPatch4), begin(triangleNodeIndexFaultPatch)));

	double explicitPointsFault[18];
	rep->getXyzPointsOfPatch(0, explicitPointsFault);
	REQUIRE(std::equal(begin(explicitPointsFault1Patch0), end(explicitPointsFault1Patch0), begin(explicitPointsFault)));
	rep->getXyzPointsOfPatch(1, explicitPointsFault);
	REQUIRE(std::equal(begin(explicitPointsFault1Patch1), end(explicitPointsFault1Patch1), begin(explicitPointsFault)));
	rep->getXyzPointsOfPatch(2, explicitPointsFault);
	REQUIRE(std::equal(begin(explicitPointsFault1Patch2), end(explicitPointsFault1Patch2), begin(explicitPointsFault)));
	rep->getXyzPointsOfPatch(3, explicitPointsFault);
	REQUIRE(std::equal(begin(explicitPointsFault1Patch3), end(explicitPointsFault1Patch3), begin(explicitPointsFault)));
	rep->getXyzPointsOfPatch(4, explicitPointsFault);
	REQUIRE(std::equal(begin(explicitPointsFault1Patch4), end(explicitPointsFault1Patch4), begin(explicitPointsFault)));
}
