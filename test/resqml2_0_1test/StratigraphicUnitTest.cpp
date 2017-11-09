#include "resqml2_0_1test/StratigraphicUnitTest.h"

#include <stdexcept>

#include "catch.hpp"

#include "EpcDocument.h"
#include "resqml2_0_1/StratigraphicUnitFeature.h"
#include <stdexcept>

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

const char* StratigraphicUnitTest::defaultUuid = "e9e8ce58-b53a-4425-84c7-667642027a4a";
const char* StratigraphicUnitTest::defaultTitle = "Strati Unit";

StratigraphicUnitTest::StratigraphicUnitTest(const string & epcDocPath)
	: AbstractFeatureTest(epcDocPath, defaultUuid, defaultTitle) {
}

StratigraphicUnitTest::StratigraphicUnitTest(const string & epcDocPath, const std::string & uuid, const std::string & title)
	: AbstractFeatureTest(epcDocPath, uuid, title) {
}

StratigraphicUnitTest::StratigraphicUnitTest(EpcDocument* epcDoc, bool init)
	: AbstractFeatureTest(epcDoc, defaultUuid, defaultTitle) {
	if (init)
			this->initEpcDoc();
		else
			this->readEpcDoc();
}

StratigraphicUnitTest::StratigraphicUnitTest(EpcDocument* epcDoc, const std::string & uuid, const std::string & title, bool init)
	: AbstractFeatureTest(epcDoc, uuid, title) {
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void StratigraphicUnitTest::initEpcDocHandler() {
	StratigraphicUnitFeature* stratiUnit = this->epcDoc->createStratigraphicUnit(uuid, title);
	REQUIRE(stratiUnit != nullptr);
}

void StratigraphicUnitTest::readEpcDocHandler() {
}