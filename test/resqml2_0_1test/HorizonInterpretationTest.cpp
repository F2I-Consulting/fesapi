#include "resqml2_0_1test/HorizonInterpretationTest.h"

#include "catch.hpp"

#include "AbstractObjectTest.h"
#include "resqml2_0_1test/HorizonTest.h"

#include "resqml2_0_1/Horizon.h"
#include "resqml2_0_1/HorizonInterpretation.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

const char* HorizonInterpretationTest::defaultUuid = "4b256b37-4013-47f9-b6c3-4460abc6e421";
const char* HorizonInterpretationTest::defaultTitle = "Horizon Interpretation Test";

HorizonInterpretationTest::HorizonInterpretationTest(const string & epcDocPath)
	: BoundaryFeatureInterpretationTest(epcDocPath, defaultUuid, defaultTitle, HorizonTest::defaultUuid, HorizonTest::defaultTitle)
{
}

HorizonInterpretationTest::HorizonInterpretationTest(const std::string & epcDocPath, const std::string & uuid, const std::string & title, const std::string & uuidFeature, const std::string & titleFeature)
	: BoundaryFeatureInterpretationTest(epcDocPath, uuid, title, uuidFeature, titleFeature)
{
}

HorizonInterpretationTest::HorizonInterpretationTest(EpcDocument * epcDoc, bool init, const std::string & uuid, const std::string & title, const std::string & uuidFeature, const std::string & titleFeature)
	: BoundaryFeatureInterpretationTest(epcDoc, uuid, title, uuidFeature, titleFeature)
{
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

HorizonInterpretationTest::HorizonInterpretationTest(EpcDocument * epcDoc, bool init)
	: HorizonInterpretationTest(epcDoc, init, defaultUuid, defaultTitle, HorizonTest::defaultUuid, HorizonTest::defaultTitle)
{
}


void HorizonInterpretationTest::initEpcDocHandler()
{
	// creating dependencies
	Horizon* horizon = epcDoc->getResqmlAbstractObjectByUuid<Horizon>(uuidFeature);
	if (horizon == nullptr) {
		HorizonTest* horizonTest = new HorizonTest(this->epcDoc, true, uuidFeature, titleFeature);
		horizon = epcDoc->getResqmlAbstractObjectByUuid<Horizon>(uuidFeature);
		delete horizonTest;
	}

	HorizonInterpretation* horizonInterp = epcDoc->getResqmlAbstractObjectByUuid<HorizonInterpretation>(uuid);
	if (horizonInterp == nullptr) {
		horizonInterp = this->epcDoc->createHorizonInterpretation(horizon, uuid, title);
	}
	REQUIRE( horizonInterp != nullptr );
}

void HorizonInterpretationTest::readEpcDocHandler()
{
	// reading dependencies
	HorizonTest* horizonTest = new HorizonTest(this->epcDoc, false, uuidFeature, titleFeature);

	// cleaning
	delete horizonTest;
}