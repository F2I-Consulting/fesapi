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
#include "../config.h" 
#include "resqml2_0_1/TriangulatedSetRepresentation.h"
#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "common/HdfProxy.h"
#include "FaultInterpretationTest.h"
#include "LocalDepth3dCrsTest.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace COMMON_NS;
using namespace RESQML2_0_1_NS;

FaultSinglePatchTriangulatedSetRepresentationTest::FaultSinglePatchTriangulatedSetRepresentationTest(const string & epcDocPath)
	: TriangulatedSetRepresentationTest(epcDocPath, uuidFaultSinglePatchTriangulatedSetRepresentation, titleFaultSinglePatchTriangulatedSetRepresentation, nodesCountFaultSinglePatchTriangulatedSetRepresentation, nodesFaultSinglePatchTriangulatedSetRepresentation)
{
}

FaultSinglePatchTriangulatedSetRepresentationTest::FaultSinglePatchTriangulatedSetRepresentationTest(EpcDocument * epcDocument, bool init)
	: TriangulatedSetRepresentationTest(epcDocument, uuidFaultSinglePatchTriangulatedSetRepresentation, titleFaultSinglePatchTriangulatedSetRepresentation, nodesCountFaultSinglePatchTriangulatedSetRepresentation, nodesFaultSinglePatchTriangulatedSetRepresentation)
{
	if (init)
		initEpcDoc();
	else
		readEpcDoc();
}

void FaultSinglePatchTriangulatedSetRepresentationTest::initEpcDocHandler()
{
	FaultInterpretation * interp = epcDoc->getDataObjectByUuid<FaultInterpretation>(uuidFaultInterpretation);
	if (interp == nullptr) {
		FaultInterpretationTest interpTest(epcDoc, true);
		interp = epcDoc->getDataObjectByUuid<FaultInterpretation>(uuidFaultInterpretation);
	}

	LocalDepth3dCrs * crs = epcDoc->getDataObjectByUuid<LocalDepth3dCrs>(LocalDepth3dCrsTest::defaultUuid);
	if (crs == nullptr) {
		LocalDepth3dCrsTest crsTest(epcDoc, true);
		crs = epcDoc->getDataObjectByUuid<LocalDepth3dCrs>(LocalDepth3dCrsTest::defaultUuid);
	}

	TriangulatedSetRepresentation* rep = epcDoc->createTriangulatedSetRepresentation(interp, crs, uuid, title);
	REQUIRE( rep != nullptr );

	unsigned int triangleNodeIndexFault[60] = {0,4,3, 0,1,4, 1,2,4, 2,5,4,
		3,7,6, 3,4,7, 4,5,7, 5,8,7,
		6,10,9, 6,7,10, 7,8,10, 8,11,10,
		9,13,12, 9,10,13, 10,11,13, 11,14,13,
		12,16,15, 12,13,16, 13,14,16, 14,17,16 };
	rep->pushBackTrianglePatch(18, xyzPointsOfAllPatchesInLocalCrs, 20, triangleNodeIndexFault, epcDoc->getHdfProxySet()[0]);
}

void FaultSinglePatchTriangulatedSetRepresentationTest::readEpcDocHandler()
{
	// reading dependencies
	FaultInterpretationTest * interpTest = new FaultInterpretationTest(epcDoc, false);
	LocalDepth3dCrsTest * crsTest = new LocalDepth3dCrsTest(epcDoc, false);

	// cleaning
	delete interpTest;
	delete crsTest;
}
