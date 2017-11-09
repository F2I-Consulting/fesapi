#include "FaultSinglePatchTriangulatedSetRepresentationTest.h"
#include "../catch.hpp"
#include "../config.h" 
#include "resqml2_0_1/TriangulatedSetRepresentation.h"
#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "resqml2/HdfProxy.h"
#include "FaultInterpretationTest.h"
#include "LocalDepth3dCrsTest.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

FaultSinglePatchTriangulatedSetRepresentationTest::FaultSinglePatchTriangulatedSetRepresentationTest(const string & epcDocPath)
	: TriangulatedSetRepresentationTest(epcDocPath, uuidFaultSinglePatchTriangulatedSetRepresentation, titleFaultSinglePatchTriangulatedSetRepresentation, nodesCountFaultSinglePatchTriangulatedSetRepresentation, nodesFaultSinglePatchTriangulatedSetRepresentation)
{
}

FaultSinglePatchTriangulatedSetRepresentationTest::FaultSinglePatchTriangulatedSetRepresentationTest(EpcDocument * epcDocument, bool init)
	: TriangulatedSetRepresentationTest(epcDocument, uuidFaultSinglePatchTriangulatedSetRepresentation, titleFaultSinglePatchTriangulatedSetRepresentation, nodesCountFaultSinglePatchTriangulatedSetRepresentation, nodesFaultSinglePatchTriangulatedSetRepresentation)
{
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void FaultSinglePatchTriangulatedSetRepresentationTest::initEpcDocHandler()
{
	FaultInterpretation * interp = static_cast<FaultInterpretation*>(this->epcDoc->getResqmlAbstractObjectByUuid(uuidFaultInterpretation));
	if (interp == nullptr) {
		FaultInterpretationTest * interpTest = new FaultInterpretationTest(this->epcDoc, true);
		interp = static_cast<FaultInterpretation*>(this->epcDoc->getResqmlAbstractObjectByUuid(uuidFaultInterpretation));
		delete interpTest;
	}

	LocalDepth3dCrs * crs = static_cast<LocalDepth3dCrs *>(this->epcDoc->getResqmlAbstractObjectByUuid(LocalDepth3dCrsTest::defaultUuid));
	if (crs == nullptr) {
		LocalDepth3dCrsTest * crsTest = new LocalDepth3dCrsTest(this->epcDoc, true);
		crs = static_cast<LocalDepth3dCrs *>(this->epcDoc->getResqmlAbstractObjectByUuid(LocalDepth3dCrsTest::defaultUuid));
		delete crsTest;
	}

	TriangulatedSetRepresentation* rep = this->epcDoc->createTriangulatedSetRepresentation(interp, crs, this->uuid, this->title);
	REQUIRE( rep != nullptr );

	unsigned int triangleNodeIndexFault[60] = {0,4,3, 0,1,4, 1,2,4, 2,5,4,
		3,7,6, 3,4,7, 4,5,7, 5,8,7,
		6,10,9, 6,7,10, 7,8,10, 8,11,10,
		9,13,12, 9,10,13, 10,11,13, 11,14,13,
		12,16,15, 12,13,16, 13,14,16, 14,17,16 };
	rep->pushBackTrianglePatch(18, this->xyzPointsOfAllPatchesInGlobalCrs, 20, triangleNodeIndexFault, this->epcDoc->getHdfProxySet()[0]);
}

void FaultSinglePatchTriangulatedSetRepresentationTest::readEpcDocHandler()
{
	// reading dependencies
	FaultInterpretationTest * interpTest = new FaultInterpretationTest(this->epcDoc, false);
	LocalDepth3dCrsTest * crsTest = new LocalDepth3dCrsTest(this->epcDoc, false);

	// cleaning
	delete interpTest;
	delete crsTest;
}