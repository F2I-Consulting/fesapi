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

#include "resqml2_test/WellboreFrameRepresentationTest.h"
#include "resqml2_test/PropertyKindTest.h"

#include "eml2/AbstractHdfProxy.h"

#include "resqml2/DiscreteProperty.h"

#include "resqml2_0_1/WellboreFrameRepresentation.h"
#include "resqml2_0_1/PropertyKind.h"

using namespace std;
using namespace COMMON_NS;
using namespace RESQML2_NS;
using namespace resqml2_test;

DiscretePropertyUsingLocalKindOnWellFrameTest::DiscretePropertyUsingLocalKindOnWellFrameTest(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void DiscretePropertyUsingLocalKindOnWellFrameTest::initRepo()
{
	// creation
	RESQML2_NS::WellboreFrameRepresentation * frame = repo->createPartial<RESQML2_0_1_NS::WellboreFrameRepresentation>(WellboreFrameRepresentationTest::defaultUuid, "");

	RESQML2_0_1_NS::PropertyKind* propertyKind = repo->createPartial<RESQML2_0_1_NS::PropertyKind>("5f78f66a-ed1b-4827-a868-beb989febb31", "code");

	// getting the hdf proxy
	EML2_NS::AbstractHdfProxy* hdfProxy = repo->getHdfProxySet()[0];

	// creating the DiscreteProperty
	RESQML2_NS::DiscreteProperty* discreteProperty = repo->createDiscreteProperty(
		frame, defaultUuid, defaultTitle,
		gsoap_eml2_3::eml23__IndexableElement::intervals,
		propertyKind);
	REQUIRE(discreteProperty != nullptr);
	int values[4] = { 0, 1, 2, 3 };
	discreteProperty->pushBackInt32Hdf5Array1dOfValues(values, 4, hdfProxy, -1);
}

void DiscretePropertyUsingLocalKindOnWellFrameTest::readRepo()
{
	// getting the DiscreteProperty
	RESQML2_NS::DiscreteProperty* discreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultUuid);

	// ************************************
	// reading the DiscreteProperty

	// getElementCountPerValue
	REQUIRE(discreteProperty->getElementCountPerValue() == 1);

	// getAttachmentKind
	REQUIRE(discreteProperty->getAttachmentKind() == gsoap_eml2_3::eml23__IndexableElement::intervals);

	// getEnergisticsPropertyKind
	REQUIRE_FALSE(discreteProperty->isAssociatedToOneStandardEnergisticsPropertyKind());

	// getValuesCountOfPatch
	REQUIRE(discreteProperty->getValuesCountOfPatch(0) == 4);

	int values[4];
	discreteProperty->getInt32ValuesOfPatch(0, values);
	REQUIRE(values[0] == 0);
	REQUIRE(values[1] == 1);
	REQUIRE(values[2] == 2);
	REQUIRE(values[3] == 3);
}
