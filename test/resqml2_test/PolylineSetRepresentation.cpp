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
#include "resqml2_test/PolylineSetRepresentation.h"

#include <stdexcept>

#include "../catch.hpp"

#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2_0_1/LocalTime3dCrs.h"
#include "resqml2/PolylineSetRepresentation.h"
#include "resqml2_test/FaultInterpretationTest.h"
#include "resqml2_test/LocalTime3dCrs.h"

using namespace std;
using namespace resqml2_test;
using namespace COMMON_NS;

namespace {
	constexpr const char* FAULT_STICKS_UUID = "60b04722-8608-4e92-8f1d-596372dd309e";
	constexpr const char* defaultTitle = "Fault sticks";
	constexpr uint32_t numNodesPerPolylinePerPatch[] = { 3, 2 };
	double polylinePoints[] = { 150, 0, 200, 300, 0, 350, 450, 0, 500, 150, 200, 200, 450, 200, 500 };

	constexpr const char* ALL_OPENED_TITLE = "all opened";
	constexpr const char* ALL_OPENED_UUID = "0a893d34-940d-4134-8008-ddc44dcab0e0";
	constexpr const char* ALL_CLOSED_TITLE = "all closed";
	constexpr const char* ALL_CLOSED_UUID = "8dae13f4-a51b-4394-ac73-14d30ca7c065";
	constexpr const char* OPENED_CLOSED_TITLE = "opened and closed";
	constexpr const char* OPENED_CLOSED_UUID = "3bc25a0e-7efe-40dc-950f-8204f8855120";
	constexpr uint32_t openedClosedNodeCountPerPolyline[] = { 3, 3, 3 };
	constexpr double openedClosedPolylinePoints[] = { 0, 0, 0, 0, 1, 0, 1, 1, 0,
		0, 0, 1, 0, 1, 1, 1, 1, 1,
		0, 0, 2, 0, 1, 2, 1, 1, 2 };
}


PolylineSetRepresentation::PolylineSetRepresentation(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void PolylineSetRepresentation::initRepo() {
	RESQML2_NS::FaultInterpretation* interp = repo->createPartial<RESQML2_0_1_NS::FaultInterpretation>("", "");
	RESQML2_NS::PolylineSetRepresentation* rep = repo->createPolylineSetRepresentation(interp, FAULT_STICKS_UUID, defaultTitle);
	rep->pushBackGeometryPatch(numNodesPerPolylinePerPatch, polylinePoints, 2, false);

	RESQML2_NS::PolylineSetRepresentation* allOpenedRep = repo->createPolylineSetRepresentation(ALL_OPENED_UUID, ALL_OPENED_TITLE);
	allOpenedRep->pushBackGeometryPatch(openedClosedNodeCountPerPolyline, openedClosedPolylinePoints, 3, false);

	RESQML2_NS::PolylineSetRepresentation* allClosedRep = repo->createPolylineSetRepresentation(ALL_CLOSED_UUID, ALL_CLOSED_TITLE);
	allClosedRep->pushBackGeometryPatch(openedClosedNodeCountPerPolyline, openedClosedPolylinePoints, 3, true);

	bool openedOrClosed[] = { true, false, true };
	RESQML2_NS::PolylineSetRepresentation* openedClosedRep = repo->createPolylineSetRepresentation(OPENED_CLOSED_UUID, OPENED_CLOSED_TITLE);
	openedClosedRep->pushBackGeometryPatch(openedClosedNodeCountPerPolyline, openedClosedPolylinePoints, 3, openedOrClosed);
}

void PolylineSetRepresentation::readRepo()
{
	RESQML2_NS::PolylineSetRepresentation* faultSticksRep = repo->getDataObjectByUuid<RESQML2_NS::PolylineSetRepresentation>(FAULT_STICKS_UUID);
	REQUIRE(faultSticksRep->getPolylineCountOfAllPatches() == 2);
	REQUIRE(!faultSticksRep->areAllPolylinesClosedOfAllPatches());

	RESQML2_NS::PolylineSetRepresentation* allOpenedRep = repo->getDataObjectByUuid<RESQML2_NS::PolylineSetRepresentation>(ALL_OPENED_UUID);
	REQUIRE(allOpenedRep->getPolylineCountOfAllPatches() == 3);
	REQUIRE(!allOpenedRep->areAllPolylinesClosedOfAllPatches());

	RESQML2_NS::PolylineSetRepresentation* allClosedRep = repo->getDataObjectByUuid<RESQML2_NS::PolylineSetRepresentation>(ALL_CLOSED_UUID);
	REQUIRE(allClosedRep->getPolylineCountOfAllPatches() == 3);
	REQUIRE(allClosedRep->areAllPolylinesClosedOfAllPatches());

	RESQML2_NS::PolylineSetRepresentation* openedClosedRep = repo->getDataObjectByUuid<RESQML2_NS::PolylineSetRepresentation>(OPENED_CLOSED_UUID);
	REQUIRE(openedClosedRep->getPolylineCountOfAllPatches() == 3);
	REQUIRE(!openedClosedRep->areAllPolylinesClosedOfAllPatches());
}
