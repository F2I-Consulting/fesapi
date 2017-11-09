#include "resqml2_0_1test/StratigraphicColumnTest.h"

#include <stdexcept>

#include "catch.hpp"

#include "EpcDocument.h"
#include "resqml2_0_1/StratigraphicColumn.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

const char* StratigraphicColumnTest::defaultUuid = "b407ddc5-67a7-437a-aa24-baf096a76857";
const char* StratigraphicColumnTest::defaultTitle = "Strati Column";

StratigraphicColumnTest::StratigraphicColumnTest(const string & epcDocPath)
	: AbstractResqmlDataObjectTest(epcDocPath, defaultUuid, defaultTitle) {
}

StratigraphicColumnTest::StratigraphicColumnTest(EpcDocument* epcDoc, bool init)
	: AbstractResqmlDataObjectTest(epcDoc, defaultUuid, defaultTitle) {
	if (init)
			this->initEpcDoc();
		else
			this->readEpcDoc();
}

void StratigraphicColumnTest::initEpcDocHandler() {
	StratigraphicColumn* stratiColumn = this->epcDoc->createStratigraphicColumn(uuid, title);
	REQUIRE(stratiColumn != nullptr);
}

void StratigraphicColumnTest::readEpcDocHandler() {
}