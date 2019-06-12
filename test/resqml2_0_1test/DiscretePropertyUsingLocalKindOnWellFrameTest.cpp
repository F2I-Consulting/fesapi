/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/
#include "DiscretePropertyUsingLocalKindOnWellFrameTest.h"

#include "catch.hpp"
#include "resqml2_0_1test/WellboreFrameRepresentationTest.h"
#include "resqml2_0_1test/PropertyKindTest.h"

#include "resqml2/PropertyKind.h"
#include "resqml2_0_1/DiscreteProperty.h"
#include "resqml2_0_1/WellboreFrameRepresentation.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace COMMON_NS;
using namespace RESQML2_NS;
using namespace resqml2_0_1test;

const char* DiscretePropertyUsingLocalKindOnWellFrameTest::defaultUuid = "5aa6a9d4-253e-43a8-bdf5-621e5df2d425";
const char* DiscretePropertyUsingLocalKindOnWellFrameTest::defaultTitle = "Discrete Property Using Local Kind On Well Frame Test";

DiscretePropertyUsingLocalKindOnWellFrameTest::DiscretePropertyUsingLocalKindOnWellFrameTest(const string & epcDocPath)
	: commontest::AbstractObjectTest(epcDocPath) {
}

DiscretePropertyUsingLocalKindOnWellFrameTest::DiscretePropertyUsingLocalKindOnWellFrameTest(EpcDocument * epcDoc, bool init)
	: commontest::AbstractObjectTest(epcDoc) {
	if (init)
		initEpcDoc();
	else
		readEpcDoc();
}

void DiscretePropertyUsingLocalKindOnWellFrameTest::initEpcDocHandler() {
	// creation
	WellboreFrameRepresentationTest * frameTest = new WellboreFrameRepresentationTest(epcDoc, true);
	RESQML2_0_1_NS::WellboreFrameRepresentation * frame = epcDoc->getDataObjectByUuid<RESQML2_0_1_NS::WellboreFrameRepresentation>(WellboreFrameRepresentationTest::defaultUuid);

	PropertyKindTest * pkTest = new PropertyKindTest(epcDoc, true);
	PropertyKind * propertyKind = epcDoc->getDataObjectByUuid<PropertyKind>(PropertyKindTest::defaultUuid);

	// getting the hdf proxy
	AbstractHdfProxy* hdfProxy = epcDoc->getHdfProxySet()[0];

	// creating the DiscreteProperty
	RESQML2_0_1_NS::DiscreteProperty* discreteProperty = epcDoc->createDiscreteProperty(
		frame, defaultUuid, defaultTitle,
		1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__intervals,
		propertyKind);
	REQUIRE(discreteProperty != nullptr);
	int values[5] = { 0, 1, 2, 3 };
	discreteProperty->pushBackIntHdf5Array1dOfValues(values, 4, hdfProxy, -1);

	// cleaning
	delete frameTest;
	delete pkTest;
}

void DiscretePropertyUsingLocalKindOnWellFrameTest::readEpcDocHandler() {
	// reading dependencies
	WellboreFrameRepresentationTest * frameTest = new WellboreFrameRepresentationTest(epcDoc, false);
	PropertyKindTest * pkTest = new PropertyKindTest(epcDoc, false);

	// getting the DiscreteProperty
	RESQML2_0_1_NS::DiscreteProperty* discreteProperty = epcDoc->getDataObjectByUuid<RESQML2_0_1_NS::DiscreteProperty>(defaultUuid);

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
	delete pkTest;
}
