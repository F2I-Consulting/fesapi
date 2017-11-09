#include "FaultTest.h"
#include "../catch.hpp"
#include "EpcDocument.h"
#include "resqml2_0_1/TectonicBoundaryFeature.h"
#include <stdexcept>
#include "../config.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

FaultTest::FaultTest(const string & epcDocPath)
	: AbstractFeatureTest(epcDocPath, uuidFault, titleFault) {
}

FaultTest::FaultTest(EpcDocument* epcDoc, bool init)
	: AbstractFeatureTest(epcDoc, uuidFault, titleFault) {
		if (init)
			this->initEpcDoc();
		else
			this->readEpcDoc();
}

void FaultTest::initEpcDocHandler() {
	TectonicBoundaryFeature* fault = this->epcDoc->createFault(this->uuid, this->title);
	REQUIRE( fault != nullptr );
}

void FaultTest::readEpcDocHandler() {
}