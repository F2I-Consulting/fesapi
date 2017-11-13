#include "resqml2_0_1test/HorizonTest.h"

#include <stdexcept>

#include "catch.hpp"

#include "EpcDocument.h"
#include "resqml2_0_1/Horizon.h"
#include <stdexcept>

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

const char* HorizonTest::defaultUuid = "dce10adc-dbd1-4b19-87ad-92457d7e9031";
const char* HorizonTest::defaultTitle = "Horizon";

HorizonTest::HorizonTest(const string & epcDocPath)
	: AbstractFeatureTest(epcDocPath, defaultUuid, defaultTitle) {
}

HorizonTest::HorizonTest(const string & epcDocPath, const std::string & uuid, const std::string & title)
	: AbstractFeatureTest(epcDocPath, uuid, title) {
}

HorizonTest::HorizonTest(EpcDocument* epcDoc, bool init)
	: HorizonTest(epcDoc, init, defaultUuid, defaultTitle)
{
}

HorizonTest::HorizonTest(EpcDocument* epcDoc, bool init, const std::string & uuid, const std::string & title)
	: AbstractFeatureTest(epcDoc, uuid, title) {
	if (init)
		initEpcDoc();
	else
		readEpcDoc();
}

void HorizonTest::initEpcDocHandler() {
	Horizon* horizon = epcDoc->createHorizon(uuid, title);
	REQUIRE( horizon != nullptr );
}

void HorizonTest::readEpcDocHandler() {
}