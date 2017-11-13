#include "FaultInterpretationTest.h"
#include "FaultTest.h"
#include "resqml2_0_1/TectonicBoundaryFeature.h"
#include "resqml2_0_1/FaultInterpretation.h"
#include "../catch.hpp"
#include "../config.h"
#include "AbstractObjectTest.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

FaultInterpretationTest::FaultInterpretationTest(const string & epcDocPath)
	: BoundaryFeatureInterpretationTest(epcDocPath, uuidFaultInterpretation, titleFaultInterpretation, uuidFault, titleFault)
{
}

FaultInterpretationTest::FaultInterpretationTest(EpcDocument * epcDoc, bool init)
	: BoundaryFeatureInterpretationTest(epcDoc, uuidFaultInterpretation, titleFaultInterpretation, uuidFault, titleFault)
{
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void FaultInterpretationTest::initEpcDocHandler()
{
	// creating dependencies
	FaultTest* faultTest = new FaultTest(this->epcDoc, true);

	TectonicBoundaryFeature* fault = static_cast<TectonicBoundaryFeature*>(this->epcDoc->getResqmlAbstractObjectByUuid(uuidFault));
	FaultInterpretation* FaultInterp = this->epcDoc->createFaultInterpretation(fault, this->uuid, this->title);
	REQUIRE( FaultInterp != nullptr );

	// cleaning
	delete faultTest;
}

void FaultInterpretationTest::readEpcDocHandler()
{
	// reading dependencies
	FaultTest* faultTest = new FaultTest(this->epcDoc, false);

	// cleaning
	delete faultTest;
}