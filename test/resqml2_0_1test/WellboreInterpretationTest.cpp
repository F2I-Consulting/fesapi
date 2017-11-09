#include "resqml2_0_1test/WellboreInterpretationTest.h"

#include "catch.hpp"
#include "resqml2_0_1test/WellboreTest.h"

#include "resqml2_0_1/WellboreFeature.h"
#include "resqml2_0_1/WellboreInterpretation.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

const char* WellboreInterpretationTest::defaultUuid = "efc2e5d6-8a4a-4482-9561-cf3538c89ba4";
const char* WellboreInterpretationTest::defaultTitle = "Wellbore Interpretation Test";

WellboreInterpretationTest::WellboreInterpretationTest(const string & epcDocPath)
	: AbstractFeatureInterpretationTest(epcDocPath, defaultUuid, defaultTitle, WellboreTest::defaultUuid, WellboreTest::defaultTitle)
{
}

WellboreInterpretationTest::WellboreInterpretationTest(EpcDocument * epcDoc, bool init)
	: AbstractFeatureInterpretationTest(epcDoc, defaultUuid, defaultTitle, WellboreTest::defaultUuid, WellboreTest::defaultTitle)
{
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void WellboreInterpretationTest::initEpcDocHandler()
{
	// creating dependencies
	WellboreTest* wellboreTest = new WellboreTest(this->epcDoc, true);

	WellboreFeature* wellbore = static_cast<WellboreFeature*>(this->epcDoc->getResqmlAbstractObjectByUuid(WellboreTest::defaultUuid));

	// cleaning
	delete wellboreTest;

	WellboreInterpretation* WellboreInterp = this->epcDoc->createWellboreInterpretation(wellbore, uuid, title, true);
	REQUIRE( WellboreInterp != nullptr );
}

void WellboreInterpretationTest::readEpcDocHandler()
{
	// reading dependencies
	WellboreTest* wellboreTest = new WellboreTest(this->epcDoc, false);

	// cleaning
	delete wellboreTest;
}