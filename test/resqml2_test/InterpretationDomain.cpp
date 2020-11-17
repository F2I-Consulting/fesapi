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
#include "resqml2_test/InterpretationDomain.h"

#include <stdexcept>

#include "../catch.hpp"

#include "resqml2_test/FaultInterpretationTest.h"
#include "resqml2_test/FaultSinglePatchTriangulatedSetRepresentationTest.h"
#include "resqml2_test/PolylineSetRepresentation.h"

#include "resqml2_0_1/TectonicBoundaryFeature.h"
#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2_0_1/LocalTime3dCrs.h"
#include "resqml2/TriangulatedSetRepresentation.h"
#include "resqml2/PolylineSetRepresentation.h"

using namespace std;
using namespace resqml2_test;
using namespace COMMON_NS;
using namespace RESQML2_NS;

InterpretationDomain::InterpretationDomain(const string & repoPath)
	: AbstractTest(repoPath)
{
}

void InterpretationDomain::initRepo()
{
	BoundaryFeature* fault = repo->createPartial<RESQML2_0_1_NS::TectonicBoundaryFeature>("", "");
	FaultInterpretation* faultInterp = repo->createFaultInterpretation(fault, FaultInterpretationTest::defaultUuid, "");

	REQUIRE(faultInterp->getDomain() == gsoap_resqml2_0_1::resqml20__Domain__mixed);
	faultInterp->initDomain(gsoap_resqml2_0_1::resqml20__Domain__time);
	REQUIRE(faultInterp->getDomain() == gsoap_resqml2_0_1::resqml20__Domain__time);

	if (dynamic_cast<RESQML2_0_1_NS::FaultInterpretation*>(faultInterp) != nullptr) {
		TriangulatedSetRepresentation* depthRep = repo->createTriangulatedSetRepresentation(faultInterp, "", "");
		double nodesFaultSinglePatchTriangulatedSetRepresentation[9] = { 0,0,0,1,1,1,2,2,2 };
		unsigned int triangleNodeIndexFault[3] = { 0,1,2, };
		depthRep->pushBackTrianglePatch(3, nodesFaultSinglePatchTriangulatedSetRepresentation, 1, triangleNodeIndexFault, repo->getHdfProxySet()[0]);
		REQUIRE(faultInterp->getDomain() == gsoap_resqml2_0_1::resqml20__Domain__depth);

		RESQML2_NS::LocalTime3dCrs * timeCrs = repo->getDataObjectByUuid<RESQML2_NS::LocalTime3dCrs>("");
		if (timeCrs == nullptr) {
			timeCrs = repo->createPartial<RESQML2_0_1_NS::LocalTime3dCrs>("", "");
		}
		RESQML2_NS::PolylineSetRepresentation* timeRep = repo->createPolylineSetRepresentation(faultInterp, "", "");
		unsigned int numNodesPerPolylinePerPatch[] = { 1 };
		double polylinePoints[3] = { 150, 0, 200 };
		timeRep->pushBackGeometryPatch(numNodesPerPolylinePerPatch, polylinePoints, 1, false, nullptr, timeCrs);
		REQUIRE(faultInterp->getDomain() == gsoap_resqml2_0_1::resqml20__Domain__mixed);
	}
}

void InterpretationDomain::readRepo() {

}
