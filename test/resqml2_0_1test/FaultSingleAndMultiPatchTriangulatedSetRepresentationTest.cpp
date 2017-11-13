#include "FaultSingleAndMultiPatchTriangulatedSetRepresentationTest.h"
#include "FaultSinglePatchTriangulatedSetRepresentationTest.h"
#include "FaultMultiPatchTriangulatedSetRepresentationTest.h"
#include "../catch.hpp"

using namespace std;
using namespace common;
using namespace commontest;
using namespace resqml2_0_1test;

FaultSingleAndMultiPatchTriangulatedSetRepresentationTest::FaultSingleAndMultiPatchTriangulatedSetRepresentationTest(const string & epcDocPath)
	: AbstractTest(epcDocPath)
{
}

FaultSingleAndMultiPatchTriangulatedSetRepresentationTest::FaultSingleAndMultiPatchTriangulatedSetRepresentationTest(EpcDocument * epcDocument, bool init)
	: AbstractTest(epcDocument)
{
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void FaultSingleAndMultiPatchTriangulatedSetRepresentationTest::initEpcDoc()
{
	// creating dependencies
	FaultSinglePatchTriangulatedSetRepresentationTest* faultSinglePatchRep = new FaultSinglePatchTriangulatedSetRepresentationTest(this->epcDoc, true);
	FaultMultiPatchTriangulatedSetRepresentationTest* faultMultiPatchRep = new FaultMultiPatchTriangulatedSetRepresentationTest(this->epcDoc, true);

	// cleaning
	delete faultSinglePatchRep;
	delete faultMultiPatchRep;
}

void FaultSingleAndMultiPatchTriangulatedSetRepresentationTest::readEpcDoc()
{
	// reading dependencies
	FaultSinglePatchTriangulatedSetRepresentationTest* faultSinglePatchRep = new FaultSinglePatchTriangulatedSetRepresentationTest(this->epcDoc, false);
	FaultMultiPatchTriangulatedSetRepresentationTest* faultMultiPatchRep = new FaultMultiPatchTriangulatedSetRepresentationTest(this->epcDoc, false);

	// cleaning
	delete faultSinglePatchRep;
	delete faultMultiPatchRep;
}

