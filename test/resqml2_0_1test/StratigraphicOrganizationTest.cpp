#include "resqml2_0_1test/StratigraphicOrganizationTest.h"

#include <stdexcept>

#include "catch.hpp"

#include "EpcDocument.h"
#include "resqml2_0_1/OrganizationFeature.h"
#include <stdexcept>

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

const char* StratigraphicOrganizationTest::defaultUuid = "8567b4b5-3e03-4e8e-bf69-b77965bea29f";
const char* StratigraphicOrganizationTest::defaultTitle = "Strati Organization";

StratigraphicOrganizationTest::StratigraphicOrganizationTest(const string & epcDocPath)
	: AbstractFeatureTest(epcDocPath, defaultUuid, defaultTitle) {
}

StratigraphicOrganizationTest::StratigraphicOrganizationTest(EpcDocument* epcDoc, bool init)
	: AbstractFeatureTest(epcDoc, defaultUuid, defaultTitle) {
	if (init)
			initEpcDoc();
		else
			readEpcDoc();
}

void StratigraphicOrganizationTest::initEpcDocHandler() {
	OrganizationFeature* stratiOrg = epcDoc->createStratigraphicModel(uuid, title);
	REQUIRE(stratiOrg != nullptr);
}

void StratigraphicOrganizationTest::readEpcDocHandler() {
}