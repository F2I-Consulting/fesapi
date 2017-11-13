#include "DiscretePropertyUsingLocalKindOnWellFrameTest.h"

#include "catch.hpp"
#include "resqml2_0_1test/WellboreFrameRepresentationTest.h"
#include "resqml2_0_1test/PropertyKindTest.h"

#include "resqml2/PropertyKind.h"
#include "resqml2_0_1/DiscreteProperty.h"
#include "resqml2_0_1/WellboreFrameRepresentation.h"
#include "resqml2/AbstractHdfProxy.h"

using namespace std;
using namespace common;
using namespace resqml2;
using namespace resqml2_0_1test;

const char* DiscretePropertyUsingLocalKindOnWellFrameTest::defaultUuid = "5aa6a9d4-253e-43a8-bdf5-621e5df2d425";
const char* DiscretePropertyUsingLocalKindOnWellFrameTest::defaultTitle = "Discrete Property Using Local Kind On Well Frame Test";

DiscretePropertyUsingLocalKindOnWellFrameTest::DiscretePropertyUsingLocalKindOnWellFrameTest(const string & epcDocPath)
	: AbstractValuesPropertyTest(epcDocPath, defaultUuid, defaultTitle, WellboreFrameRepresentationTest::defaultUuid, WellboreFrameRepresentationTest::defaultTitle) {
}

DiscretePropertyUsingLocalKindOnWellFrameTest::DiscretePropertyUsingLocalKindOnWellFrameTest(EpcDocument * epcDoc, bool init)
	: AbstractValuesPropertyTest(epcDoc, defaultUuid, defaultTitle, WellboreFrameRepresentationTest::defaultUuid, WellboreFrameRepresentationTest::defaultTitle) {
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void DiscretePropertyUsingLocalKindOnWellFrameTest::initEpcDocHandler() {
	// creation
	WellboreFrameRepresentationTest * frameTest = new WellboreFrameRepresentationTest(this->epcDoc, true);
	resqml2_0_1::WellboreFrameRepresentation * frame = this->epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::WellboreFrameRepresentation>(WellboreFrameRepresentationTest::defaultUuid);

	PropertyKindTest * pkTest = new PropertyKindTest(this->epcDoc, true);
	PropertyKind * propertyKind = this->epcDoc->getResqmlAbstractObjectByUuid<PropertyKind>(PropertyKindTest::defaultUuid);

	// getting the hdf proxy
	AbstractHdfProxy* hdfProxy = this->epcDoc->getHdfProxySet()[0];

	// creating the DiscreteProperty
	resqml2_0_1::DiscreteProperty* discreteProperty = epcDoc->createDiscreteProperty(
		frame, this->uuid, this->title,
		1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__intervals,
		propertyKind);
	REQUIRE(discreteProperty != nullptr);
	int values[5] = { 0, 1, 2, 3 };
	discreteProperty->pushBackIntHdf5Array1dOfValues(values, 4, hdfProxy, -1);

	// cleaning
	delete frameTest;
}

void DiscretePropertyUsingLocalKindOnWellFrameTest::readEpcDocHandler() {
	// reading dependencies
	WellboreFrameRepresentationTest * frameTest = new WellboreFrameRepresentationTest(this->epcDoc, false);
	PropertyKindTest * pkTest = new PropertyKindTest(this->epcDoc, false);

	// getting the DiscreteProperty
	resqml2_0_1::DiscreteProperty* discreteProperty = this->epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::DiscreteProperty>(uuid);

	// ************************************
	// reading the DiscreteProperty

	// getElementCountPerValue
	REQUIRE(discreteProperty->getElementCountPerValue() == 1);

	// getAttachmentKind
	REQUIRE(discreteProperty->getAttachmentKind() == gsoap_resqml2_0_1::resqml2__IndexableElements__intervals);

	// getEnergisticsPropertyKind
	REQUIRE_FALSE(discreteProperty->isAssociatedToOneStandardEnergisticsPropertyKind());
	REQUIRE(discreteProperty->getLocalPropertyKindUuid() == PropertyKindTest::defaultUuid);
	REQUIRE(discreteProperty->getLocalPropertyKindTitle() == PropertyKindTest::defaultTitle);

	// getValuesCountOfPatch
	REQUIRE(discreteProperty->getValuesCountOfPatch(0) == 4);

	int* values = new int[4];
	discreteProperty->getIntValuesOfPatch(0, values);
	REQUIRE(values[0] == 0);
	REQUIRE(values[1] == 1);
	REQUIRE(values[2] == 2);
	REQUIRE(values[3] == 3);
	delete[] values;

	// cleaning
	delete frameTest;
}
