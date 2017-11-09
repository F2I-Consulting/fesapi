#include "resqml2_0_1test/StratigraphicUnitInterpretationTest.h"

#include <stdexcept>

#include "catch.hpp"
#include "resqml2_0_1test/StratigraphicUnitTest.h"

#include "EpcDocument.h"
#include "resqml2_0_1/StratigraphicUnitFeature.h"
#include "resqml2_0_1/StratigraphicUnitInterpretation.h"
#include <stdexcept>

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

const char* StratigraphicUnitInterpretationTest::defaultUuid = "65abde7d-d6ab-42b5-89c8-cc6ccec56dcc";
const char* StratigraphicUnitInterpretationTest::defaultTitle = "Strati Unit Interp";

StratigraphicUnitInterpretationTest::StratigraphicUnitInterpretationTest(const string & epcDocPath)
	: AbstractFeatureInterpretationTest(epcDocPath, defaultUuid, defaultTitle, StratigraphicUnitTest::defaultUuid, StratigraphicUnitTest::defaultTitle) {
}

StratigraphicUnitInterpretationTest::StratigraphicUnitInterpretationTest(const string & epcDocPath, const std::string & uuid, const std::string & title, const string & uuidFeature, const string & titleFeature)
	: AbstractFeatureInterpretationTest(epcDocPath, uuid, title, uuidFeature, titleFeature) {
}

StratigraphicUnitInterpretationTest::StratigraphicUnitInterpretationTest(EpcDocument* epcDoc, bool init)
	: AbstractFeatureInterpretationTest(epcDoc, defaultUuid, defaultTitle, StratigraphicUnitTest::defaultUuid, StratigraphicUnitTest::defaultTitle) {
	if (init)
			initEpcDoc();
		else
			readEpcDoc();
}

StratigraphicUnitInterpretationTest::StratigraphicUnitInterpretationTest(common::EpcDocument* epcDoc, const std::string & uuid, const std::string & title, const string & uuidFeature, const string & titleFeature, bool init)
	: AbstractFeatureInterpretationTest(epcDocPath, uuid, title, uuidFeature, titleFeature) {
}

void StratigraphicUnitInterpretationTest::initEpcDocHandler() {
	// creating dependencies
	StratigraphicUnitTest* stratiUnitTest = new StratigraphicUnitTest(epcDoc, true);

	StratigraphicUnitFeature* stratiUnit = static_cast<StratigraphicUnitFeature*>(this->epcDoc->getResqmlAbstractObjectByUuid(StratigraphicUnitTest::defaultTitle));

	// cleaning
	delete stratiUnitTest;

	StratigraphicUnitInterpretation* stratiUnitInterp = epcDoc->createStratigraphicUnitInterpretation(stratiUnit, uuid, title);
	REQUIRE(stratiUnitInterp != nullptr);
}

void StratigraphicUnitInterpretationTest::readEpcDocHandler() {
}
