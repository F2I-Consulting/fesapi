#include "ContinuousPropertyOnWellFrameTest.h"

#include "catch.hpp"
#include "resqml2_0_1test/WellboreFrameRepresentationTest.h"

#include "resqml2_0_1/ContinuousProperty.h"
#include "resqml2_0_1/WellboreFrameRepresentation.h"
#include "resqml2/AbstractHdfProxy.h"

using namespace std;
using namespace common;
using namespace resqml2;
using namespace resqml2_0_1test;

const char* ContinuousPropertyOnWellFrameTest::defaultUuid = "6e4ca2c9-6780-44bd-b4c2-6bb3ef4682d4";
const char* ContinuousPropertyOnWellFrameTest::defaultTitle = "Continuous Property on well frame Test";

ContinuousPropertyOnWellFrameTest::ContinuousPropertyOnWellFrameTest(const string & epcDocPath)
	: ContinuousPropertyTest(epcDocPath, defaultUuid, defaultTitle, WellboreFrameRepresentationTest::defaultUuid, WellboreFrameRepresentationTest::defaultTitle) {
}

ContinuousPropertyOnWellFrameTest::ContinuousPropertyOnWellFrameTest(EpcDocument * epcDoc, bool init)
	: ContinuousPropertyTest(epcDoc, defaultUuid, defaultTitle, WellboreFrameRepresentationTest::defaultUuid, WellboreFrameRepresentationTest::defaultTitle) {
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void ContinuousPropertyOnWellFrameTest::initEpcDocHandler() {
	// creating an IJK grid
	WellboreFrameRepresentationTest * frameTest = new WellboreFrameRepresentationTest(this->epcDoc, true);
	resqml2_0_1::WellboreFrameRepresentation * frame = static_cast<resqml2_0_1::WellboreFrameRepresentation *>(this->epcDoc->getResqmlAbstractObjectByUuid(WellboreFrameRepresentationTest::defaultUuid));

	// getting the hdf proxy
	AbstractHdfProxy* hdfProxy = this->epcDoc->getHdfProxySet()[0];

	// creating the ContinuousProperty
	resqml2_0_1::ContinuousProperty* continuousProperty = epcDoc->createContinuousProperty(
		frame, this->uuid, this->title,
		1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__nodes,
		gsoap_resqml2_0_1::resqml2__ResqmlUom__m,
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__length);
	REQUIRE(continuousProperty != nullptr);
	double values[5] = { 0.1, 1.2, 2.3, 3.4, 4.5 };
	continuousProperty->pushBackDoubleHdf5Array1dOfValues(values, 5, hdfProxy);

	// cleaning
	delete frameTest;
}

void ContinuousPropertyOnWellFrameTest::readEpcDocHandler() {
	// reading dependencies
	WellboreFrameRepresentationTest * frameTest = new WellboreFrameRepresentationTest(this->epcDoc, false);

	// getting the ContinuousPropertySeries
	resqml2_0_1::ContinuousProperty* continuousProperty = this->epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::ContinuousProperty>(uuid);

	// ************************************
	// reading the ContinuousProperty

	// getElementCountPerValue
	REQUIRE(continuousProperty->getElementCountPerValue() == 1);

	// getAttachmentKind
	REQUIRE(continuousProperty->getAttachmentKind() == gsoap_resqml2_0_1::resqml2__IndexableElements__nodes);

	// getUom
	REQUIRE(continuousProperty->getUom() == gsoap_resqml2_0_1::resqml2__ResqmlUom__m);

	// getEnergisticsPropertyKind
	REQUIRE(continuousProperty->isAssociatedToOneStandardEnergisticsPropertyKind());
	REQUIRE(continuousProperty->getEnergisticsPropertyKind() == gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__length);

	// getValuesCountOfPatch
	REQUIRE(continuousProperty->getValuesCountOfPatch(0) == 5);

	double* values = new double[5];
	continuousProperty->getDoubleValuesOfPatch(0, values);
	REQUIRE(values[0] == 0.1);
	REQUIRE(values[1] == 1.2);
	REQUIRE(values[2] == 2.3);
	REQUIRE(values[3] == 3.4);
	REQUIRE(values[4] == 4.5);
	delete[] values;

	// cleaning
	delete frameTest;
}
