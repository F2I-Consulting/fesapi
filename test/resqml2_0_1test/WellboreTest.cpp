#include "resqml2_0_1test/WellboreTest.h"

#include <stdexcept>

#include "catch.hpp"
#include "EpcDocument.h"
#include "resqml2_0_1/WellboreFeature.h"
#include "config.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

const char* WellboreTest::defaultUuid = "9058a950-35c7-44e6-9671-0f1ba13118cf";
const char* WellboreTest::defaultTitle = "Wellbore Test";

WellboreTest::WellboreTest(const string & epcDocPath)
	: AbstractFeatureTest(epcDocPath, defaultUuid, defaultTitle) {
}

WellboreTest::WellboreTest(EpcDocument* epcDoc, bool init)
	: AbstractFeatureTest(epcDoc, defaultUuid, defaultTitle) {
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void WellboreTest::initEpcDocHandler() {
	WellboreFeature* wellbore = this->epcDoc->createWellboreFeature(this->uuid, this->title);
	REQUIRE(wellbore != nullptr);
}

void WellboreTest::readEpcDocHandler() {
}