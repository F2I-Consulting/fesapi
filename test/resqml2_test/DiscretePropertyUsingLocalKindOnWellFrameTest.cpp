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
#include "resqml2_test/WellboreFrameRepresentationTest.h"
#include "resqml2_test/PropertyKindTest.h"

#include "eml2/PropertyKind.h"
#include "resqml2/DiscreteProperty.h"
#include "resqml2/WellboreFrameRepresentation.h"
#include "eml2/AbstractHdfProxy.h"

using namespace std;
using namespace COMMON_NS;
using namespace RESQML2_NS;
using namespace resqml2_test;

const char* DiscretePropertyUsingLocalKindOnWellFrameTest::defaultUuid = "5aa6a9d4-253e-43a8-bdf5-621e5df2d425";
const char* DiscretePropertyUsingLocalKindOnWellFrameTest::defaultTitle = "Discrete Property Using Local Kind On Well Frame Test";

DiscretePropertyUsingLocalKindOnWellFrameTest::DiscretePropertyUsingLocalKindOnWellFrameTest(const string & repoPath)
	: commontest::AbstractObjectTest(repoPath) {
}

DiscretePropertyUsingLocalKindOnWellFrameTest::DiscretePropertyUsingLocalKindOnWellFrameTest(DataObjectRepository * repo, bool init)
	: commontest::AbstractObjectTest(repo) {
	if (init)
		initRepo();
	else
		readRepo();
}

void DiscretePropertyUsingLocalKindOnWellFrameTest::initRepoHandler() {
	// creation
	WellboreFrameRepresentationTest * frameTest = new WellboreFrameRepresentationTest(repo, true);
	RESQML2_NS::WellboreFrameRepresentation * frame = repo->getDataObjectByUuid<RESQML2_NS::WellboreFrameRepresentation>(WellboreFrameRepresentationTest::defaultUuid);

	PropertyKindTest * pkTest = new PropertyKindTest(repo, true);
	EML2_NS::PropertyKind * propertyKind = repo->getDataObjectByUuid<EML2_NS::PropertyKind>(PropertyKindTest::defaultUuid);

	// getting the hdf proxy
	EML2_NS::AbstractHdfProxy* hdfProxy = repo->getHdfProxySet()[0];

	// creating the DiscreteProperty
	RESQML2_NS::DiscreteProperty* discreteProperty = repo->createDiscreteProperty(
		frame, defaultUuid, defaultTitle,
		1,
		gsoap_eml2_3::resqml22__IndexableElement__intervals,
		propertyKind);
	REQUIRE(discreteProperty != nullptr);
	int values[5] = { 0, 1, 2, 3 };
	discreteProperty->pushBackIntHdf5Array1dOfValues(values, 4, hdfProxy, -1);

	// cleaning
	delete frameTest;
	delete pkTest;
}

void DiscretePropertyUsingLocalKindOnWellFrameTest::readRepoHandler() {
	// reading dependencies
	WellboreFrameRepresentationTest * frameTest = new WellboreFrameRepresentationTest(repo, false);
	PropertyKindTest * pkTest = new PropertyKindTest(repo, false);

	// getting the DiscreteProperty
	RESQML2_NS::DiscreteProperty* discreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultUuid);

	// ************************************
	// reading the DiscreteProperty

	// getElementCountPerValue
	REQUIRE(discreteProperty->getElementCountPerValue() == 1);

	// getAttachmentKind
	REQUIRE(discreteProperty->getAttachmentKind() == gsoap_eml2_3::resqml22__IndexableElement__intervals);

	// getEnergisticsPropertyKind
	REQUIRE_FALSE(discreteProperty->isAssociatedToOneStandardEnergisticsPropertyKind());

	// getValuesCountOfPatch
	REQUIRE(discreteProperty->getValuesCountOfPatch(0) == 4);

	int values[4];
	discreteProperty->getIntValuesOfPatch(0, values);
	REQUIRE(values[0] == 0);
	REQUIRE(values[1] == 1);
	REQUIRE(values[2] == 2);
	REQUIRE(values[3] == 3);

	// cleaning
	delete frameTest;
	delete pkTest;
}
