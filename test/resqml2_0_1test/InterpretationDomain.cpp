#include "resqml2_0_1test/InterpretationDomain.h"

#include "../catch.hpp"

#include "resqml2_0_1test/FaultInterpretationTest.h"
#include "resqml2_0_1test/FaultSinglePatchTriangulatedSetRepresentationTest.h"
#include "resqml2_0_1test/PolylineSetRepresentation.h"

#include "resqml2_0_1/FaultInterpretation.h"
#include <stdexcept>
#include "../config.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

InterpretationDomain::InterpretationDomain(const string & epcDocPath)
	: AbstractTest(epcDocPath)
{
}

InterpretationDomain::InterpretationDomain(EpcDocument* epcDoc, bool init)
	: AbstractTest(epcDoc)
{
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void InterpretationDomain::initEpcDoc() {

	FaultInterpretation* faultInterp = epcDoc->getResqmlAbstractObjectByUuid<FaultInterpretation>(uuidFaultInterpretation);
	if (faultInterp == nullptr) {
		FaultInterpretationTest* faultInterpTest = new FaultInterpretationTest(this->epcDoc, true);
		faultInterp = epcDoc->getResqmlAbstractObjectByUuid<FaultInterpretation>(uuidFaultInterpretation);
		delete faultInterpTest;
	}

	REQUIRE(faultInterp->getDomain() == gsoap_resqml2_0_1::resqml2__Domain__mixed);
	faultInterp->initDomain(gsoap_resqml2_0_1::resqml2__Domain__time);
	REQUIRE(faultInterp->getDomain() == gsoap_resqml2_0_1::resqml2__Domain__time);

	FaultSinglePatchTriangulatedSetRepresentationTest* repTest = new FaultSinglePatchTriangulatedSetRepresentationTest(epcDoc, true);
	REQUIRE(faultInterp->getDomain() == gsoap_resqml2_0_1::resqml2__Domain__depth);
	resqml2_0_1test::PolylineSetRepresentation* polylineRepTest = new resqml2_0_1test::PolylineSetRepresentation(epcDoc, true);
	REQUIRE(faultInterp->getDomain() == gsoap_resqml2_0_1::resqml2__Domain__mixed);
}

void InterpretationDomain::readEpcDoc() {

}