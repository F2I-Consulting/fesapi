#include "resqml2_0_1test/MdDatumTest.h"

#include <stdexcept>

#include "catch.hpp"
#include "resqml2_0_1test/LocalDepth3dCrsTest.h"

#include "EpcDocument.h"
#include "resqml2_0_1/WellboreFeature.h"
#include "resqml2_0_1/LocalDepth3dCrs.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2;

const char* MdDatumTest::defaultUuid = "aa4da18f-5cc8-4bbb-841a-30e4031376fa";
const char* MdDatumTest::defaultTitle = "Md Datum";

MdDatumTest::MdDatumTest(const string & epcDocPath)
	: AbstractResqmlDataObjectTest(epcDocPath, defaultUuid, defaultTitle) {
}

MdDatumTest::MdDatumTest(EpcDocument* epcDoc, bool init)
	: AbstractResqmlDataObjectTest(epcDoc, defaultUuid, defaultTitle) {
	if (init)
			this->initEpcDoc();
		else
			this->readEpcDoc();
}

void MdDatumTest::initEpcDocHandler() {
	LocalDepth3dCrsTest * crsTest = new LocalDepth3dCrsTest(this->epcDoc, true);
	resqml2_0_1::LocalDepth3dCrs * crs = static_cast<resqml2_0_1::LocalDepth3dCrs *>(this->epcDoc->getResqmlAbstractObjectByUuid(LocalDepth3dCrsTest::defaultUuid));

	// cleaning
	delete crsTest;

	MdDatum* mdDatum = epcDoc->createMdDatum(uuid, title, crs, gsoap_resqml2_0_1::resqml2__MdReference__mean_x0020sea_x0020level, 275, 75, 0);
	REQUIRE(mdDatum != nullptr);
}

void MdDatumTest::readEpcDocHandler() {
}