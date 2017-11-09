#include "resqml2_0_1test/StratigraphicColumnRankInterpretationTest.h"

#include <stdexcept>

#include "catch.hpp"
#include "resqml2_0_1test/StratigraphicOrganizationTest.h"
#include "resqml2_0_1test/StratigraphicUnitInterpretationTest.h"

#include "EpcDocument.h"
#include "resqml2_0_1/OrganizationFeature.h"
#include "resqml2_0_1/StratigraphicColumnRankInterpretation.h"
#include "resqml2_0_1/StratigraphicUnitInterpretation.h"
#include <stdexcept>

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

const char* StratigraphicColumnRankInterpretationTest::defaultUuid = "51f39ab2-3b1f-4da3-8541-324632357dd7";
const char* StratigraphicColumnRankInterpretationTest::defaultTitle = "Strati Column Rank";

const char* StratigraphicColumnRankInterpretationTest::defaultOverburdenUuid = "91622a20-e2a0-4123-a8b5-6540a1ff4f8f";
const char* StratigraphicColumnRankInterpretationTest::defaultOverburdenTitle = "Overburden";
const char* StratigraphicColumnRankInterpretationTest::defaultOverburdenInterpUuid = "80ba46c8-86e7-42ef-ab30-4718958f3707";
const char* StratigraphicColumnRankInterpretationTest::defaultOverburdenInterpTitle = "Overburden Interp";

const char* StratigraphicColumnRankInterpretationTest::defaultUnderburdenUuid = "88575500-4f85-4bea-9245-530e71867945";
const char* StratigraphicColumnRankInterpretationTest::defaultUnderburdenTitle = "Underburden";
const char* StratigraphicColumnRankInterpretationTest::defaultUnderburdenInterpUuid = "1914478a-e50b-4808-ad62-11201992024d";
const char* StratigraphicColumnRankInterpretationTest::defaultUnderburdenInterpTitle = "Underburden Interp";

StratigraphicColumnRankInterpretationTest::StratigraphicColumnRankInterpretationTest(const string & epcDocPath)
	: AbstractFeatureInterpretationTest(epcDocPath, defaultUuid, defaultTitle, StratigraphicOrganizationTest::defaultUuid, StratigraphicOrganizationTest::defaultTitle) {
}

StratigraphicColumnRankInterpretationTest::StratigraphicColumnRankInterpretationTest(const string & epcDocPath, const std::string & uuid, const std::string & title, const string & uuidFeature, const string & titleFeature)
	: AbstractFeatureInterpretationTest(epcDocPath, uuid, title, uuidFeature, titleFeature) {
}

StratigraphicColumnRankInterpretationTest::StratigraphicColumnRankInterpretationTest(EpcDocument* epcDoc, bool init)
	: AbstractFeatureInterpretationTest(epcDoc, defaultUuid, defaultTitle, StratigraphicOrganizationTest::defaultUuid, StratigraphicOrganizationTest::defaultTitle) {
	if (init)
			initEpcDoc();
		else
			readEpcDoc();
}

StratigraphicColumnRankInterpretationTest::StratigraphicColumnRankInterpretationTest(common::EpcDocument* epcDoc, const std::string & uuid, const std::string & title, const string & uuidFeature, const string & titleFeature, bool init)
	: AbstractFeatureInterpretationTest(epcDocPath, uuid, title, uuidFeature, titleFeature) {
}

void StratigraphicColumnRankInterpretationTest::initEpcDocHandler() {
	// creating dependencies
	StratigraphicOrganizationTest* stratiOrgtTest = new StratigraphicOrganizationTest(epcDoc, true);
	StratigraphicUnitInterpretationTest* overburdenInterpTest = new StratigraphicUnitInterpretationTest(epcDoc, defaultOverburdenInterpUuid, defaultOverburdenInterpTitle, defaultOverburdenUuid, defaultOverburdenTitle, true);
	StratigraphicUnitInterpretationTest* stratiLayerInterpTest = new StratigraphicUnitInterpretationTest(epcDoc, true);
	StratigraphicUnitInterpretationTest* underburdenInterpTest = new StratigraphicUnitInterpretationTest(epcDoc, defaultUnderburdenInterpUuid, defaultUnderburdenInterpTitle, defaultUnderburdenUuid, defaultUnderburdenTitle, true);

	OrganizationFeature* stratiOrg = epcDoc->getResqmlAbstractObjectByUuid<OrganizationFeature>(StratigraphicOrganizationTest::defaultUuid);
	StratigraphicUnitInterpretation* overburdenInterp = epcDoc->getResqmlAbstractObjectByUuid<StratigraphicUnitInterpretation>(defaultOverburdenInterpUuid);
	StratigraphicUnitInterpretation* stratiLayerInterp = epcDoc->getResqmlAbstractObjectByUuid<StratigraphicUnitInterpretation>(StratigraphicUnitInterpretationTest::defaultUuid);
	StratigraphicUnitInterpretation* underburdenInterp = epcDoc->getResqmlAbstractObjectByUuid<StratigraphicUnitInterpretation>(defaultUnderburdenInterpUuid);

	// cleaning
	delete stratiOrgtTest;
	delete overburdenInterpTest;
	delete stratiLayerInterpTest;
	delete underburdenInterpTest;

	StratigraphicColumnRankInterpretation* stratiColumnRank = epcDoc->createStratigraphicColumnRankInterpretationInApparentDepth(stratiOrg, uuid, title, 0);
	REQUIRE(stratiColumnRank != nullptr);
	stratiColumnRank->pushBackStratiUnitInterpretation(overburdenInterp);
	stratiColumnRank->pushBackStratiUnitInterpretation(stratiLayerInterp);
	stratiColumnRank->pushBackStratiUnitInterpretation(underburdenInterp);
}

void StratigraphicColumnRankInterpretationTest::readEpcDocHandler()
{
	StratigraphicColumnRankInterpretation* stratiColumnRank = epcDoc->getResqmlAbstractObjectByUuid<StratigraphicColumnRankInterpretation>(uuid);
	REQUIRE(stratiColumnRank != nullptr);
	REQUIRE(stratiColumnRank->getStratigraphicUnitInterpretationSet().size() == 3);
}