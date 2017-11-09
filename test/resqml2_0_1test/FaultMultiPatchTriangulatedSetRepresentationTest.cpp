#include "FaultMultiPatchTriangulatedSetRepresentationTest.h"
#include "../catch.hpp"
#include "../config.h" 
#include "resqml2_0_1/TriangulatedSetRepresentation.h"
#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "resqml2_0_1/HdfProxy.h"
#include "FaultInterpretationTest.h"
#include "LocalDepth3dCrsTest.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

FaultMultiPatchTriangulatedSetRepresentationTest::FaultMultiPatchTriangulatedSetRepresentationTest(const string & epcDocPath)
	: TriangulatedSetRepresentationTest(epcDocPath, uuidFaultMultiPatchTriangulatedSetRepresentation, titleFaultMultiPatchTriangulatedSetRepresentation)
{
}

FaultMultiPatchTriangulatedSetRepresentationTest::FaultMultiPatchTriangulatedSetRepresentationTest(EpcDocument * epcDocument, bool init)
	: TriangulatedSetRepresentationTest(epcDocument, uuidFaultMultiPatchTriangulatedSetRepresentation, titleFaultMultiPatchTriangulatedSetRepresentation)
{
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void FaultMultiPatchTriangulatedSetRepresentationTest::initEpcDocHandler()
{
	FaultInterpretationTest * interpTest = new FaultInterpretationTest(this->epcDoc, true);

	LocalDepth3dCrsTest * crsTest = new LocalDepth3dCrsTest(this->epcDoc, true);

	FaultInterpretation * interp = static_cast<FaultInterpretation*>(this->epcDoc->getResqmlAbstractObjectByUuid(uuidFaultInterpretation));
	LocalDepth3dCrs * crs = static_cast<LocalDepth3dCrs *>(this->epcDoc->getResqmlAbstractObjectByUuid(LocalDepth3dCrsTest::defaultUuid));
	HdfProxy* hdfProxy = static_cast<HdfProxy *>(this->epcDoc->getResqmlAbstractObjectByUuid(uuidHdfProxy));

	TriangulatedSetRepresentation* rep = this->epcDoc->createTriangulatedSetRepresentation(interp, crs, this->uuid, this->title);
	REQUIRE( rep != nullptr );

	// Patch 0
	double explicitPointsFault1Patch0[18] = {150, 0, 200, 150, 100, 200, 150, 200, 200,
		250, 0, 300, 250, 100, 300, 250, 200, 300};
	unsigned int triangleNodeIndexFaultPatch0[12] = {0,4,3, 0,1,4, 1,2,4, 2,5,4};
	rep->pushBackTrianglePatch(6, explicitPointsFault1Patch0, 4, triangleNodeIndexFaultPatch0, this->epcDoc->getHdfProxySet()[0]);
	// Patch 1
	double explicitPointsFault1Patch1[18] = {250, 0, 300, 250, 100, 300, 250, 200, 300,
		300, 0, 350, 300, 100, 350, 300, 200, 350};
	unsigned int triangleNodeIndexFaultPatch1[12] = {6,10,9, 6,7,10, 7,8,10, 8,11,10};
	rep->pushBackTrianglePatch(6, explicitPointsFault1Patch1, 4, triangleNodeIndexFaultPatch1, this->epcDoc->getHdfProxySet()[0]);
	// Patch 2
	double explicitPointsFault1Patch2[18] = {300, 0, 350, 300, 100, 350, 300, 200, 350,
		450, 0, 500, 450, 100, 500, 450, 200, 500};
	unsigned int triangleNodeIndexFaultPatch2[12] = {12,16,15, 12,13,16, 13,14,16, 14,17,16};
	rep->pushBackTrianglePatch(6, explicitPointsFault1Patch2, 4, triangleNodeIndexFaultPatch2, this->epcDoc->getHdfProxySet()[0]);
	// Patch 3
	double explicitPointsFault1Patch3[18] = {450, 0, 500, 450, 100, 500, 450, 200, 500,
		500, 0, 550, 500, 100, 550 ,500, 200, 550};
	unsigned int triangleNodeIndexFaultPatch3[12] = {18,22,21, 18,19,22, 19,20,22, 20,23,22};
	rep->pushBackTrianglePatch(6, explicitPointsFault1Patch3, 4, triangleNodeIndexFaultPatch3, this->epcDoc->getHdfProxySet()[0]);
	// Patch 4
	double explicitPointsFault1Patch4[18] = {500, 0, 550, 500, 100, 550 ,500, 200, 550,
		600, 0, 650, 600, 100, 650, 600, 200, 650};
	unsigned int triangleNodeIndexFaultPatch4[12] = {24,28,27, 24,25,28, 25,26,28, 26,29,28};
	rep->pushBackTrianglePatch(6, explicitPointsFault1Patch4, 4, triangleNodeIndexFaultPatch4, this->epcDoc->getHdfProxySet()[0]);

	// cleaning
	delete interpTest;
	delete crsTest;
}

void FaultMultiPatchTriangulatedSetRepresentationTest::readEpcDocHandler()
{
	// reading dependencies
	FaultInterpretationTest * interpTest = new FaultInterpretationTest(this->epcDoc, false);
	LocalDepth3dCrsTest * crsTest = new LocalDepth3dCrsTest(this->epcDoc, false);

	// cleaning
	delete interpTest;
	delete crsTest;
}