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
#include "resqml2_0_1test/DiscreteProperty.h"

#include "catch.hpp"
#include "resqml2_0_1test/LgrOnRightHanded4x3x2ExplicitIjkGrid.h"
#include "resqml2_0_1test/PropertyKindTest.h"
#include "resqml2_0_1test/WellboreFrameRepresentationTest.h"

#include "resqml2_0_1/PropertyKind.h"
#include "resqml2_0_1/DiscreteProperty.h"
#include "resqml2_0_1/AbstractIjkGridRepresentation.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace COMMON_NS;
using namespace RESQML2_NS;
using namespace resqml2_0_1test;

const char* DiscreteProperty::defaultCharPropUuid = "5aa6a9d4-253e-43a8-bdf5-621e5df2d425";
const char* DiscreteProperty::defaultShortPropUuid = "61acbc7f-fb9b-4578-800e-f310e947b865";
const char* DiscreteProperty::defaultUShortPropUuid = "0eae558f-e57b-47b1-9772-a336e99fd714";
const char* DiscreteProperty::defaultIntPropUuid = "a0721fbe-fb09-4d0f-aab3-315eca8e416e";
const char* DiscreteProperty::defaultLongPropUuid = "eda57b20-4639-4541-87b9-c2b44b46c336";

DiscreteProperty::DiscreteProperty(const string & repoPath)
	: commontest::AbstractObjectTest(repoPath) {
}

DiscreteProperty::DiscreteProperty(DataObjectRepository * repo, bool init)
	: commontest::AbstractObjectTest(repo) {
	if (init)
		initRepo();
	else
		readRepo();
}

void DiscreteProperty::initRepoHandler() {
	RESQML2_0_1_NS::AbstractIjkGridRepresentation* ijkGrid = repo->createPartialIjkGridRepresentation("", "partial IJK Grid");
	RESQML2_0_1_NS::PropertyKind * propertyKind = repo->createPartial<RESQML2_0_1_NS::PropertyKind>("", "Partial prop kind");

	// getting the hdf proxy
	AbstractHdfProxy* hdfProxy = repo->getHdfProxySet()[0];

	// creating the char DiscreteProperty
	RESQML2_0_1_NS::DiscreteProperty* charDiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultCharPropUuid, "char prop",
		1,
		gsoap_resqml2_0_1::resqml20__IndexableElements__cells,
		propertyKind);
	char charValues[6] = { 0, 1, 2, 3, 4, 5 };
	charDiscreteProperty->pushBackCharHdf5Array3dOfValues(charValues, 1, 2, 3, hdfProxy, -1);

	// creating the short DiscreteProperty
	RESQML2_0_1_NS::DiscreteProperty* shortDiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultShortPropUuid, "short prop",
		1,
		gsoap_resqml2_0_1::resqml20__IndexableElements__cells,
		propertyKind);
	short shortValues[6] = { 0, 1, 2, 3, 4, 5 };
	shortDiscreteProperty->pushBackShortHdf5Array3dOfValues(shortValues, 1, 2, 3, hdfProxy, -1);

	// creating the ushort DiscreteProperty
	RESQML2_0_1_NS::DiscreteProperty* ushortDiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultUShortPropUuid, "ushort prop",
		1,
		gsoap_resqml2_0_1::resqml20__IndexableElements__cells,
		propertyKind);
	unsigned short ushortValues[6] = { 0, 1, 2, 3, 4, 5 };
	ushortDiscreteProperty->pushBackUShortHdf5Array3dOfValues(ushortValues, 1, 2, 3, hdfProxy, -1);

	// creating the int DiscreteProperty
	RESQML2_0_1_NS::DiscreteProperty* intDiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultIntPropUuid, "int prop",
		1,
		gsoap_resqml2_0_1::resqml20__IndexableElements__cells,
		propertyKind);
	int intValues[6] = { 0, 1, 2, 3, 4, 5 };
	intDiscreteProperty->pushBackIntHdf5Array3dOfValues(intValues, 1, 2, 3, hdfProxy, -1);

	// creating the long DiscreteProperty
	RESQML2_0_1_NS::DiscreteProperty* longDiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultLongPropUuid, "long prop",
		1,
		gsoap_resqml2_0_1::resqml20__IndexableElements__cells,
		propertyKind);
	LONG64 longValues[6] = { 0, 1, 2, 3, 4, 5 };
	longDiscreteProperty->pushBackLongHdf5Array3dOfValues(longValues, 1, 2, 3, hdfProxy, -1);
}

void DiscreteProperty::readRepoHandler() {
	// getting the DiscreteProperty
	RESQML2_0_1_NS::DiscreteProperty* charDiscreteProperty = repo->getDataObjectByUuid<RESQML2_0_1_NS::DiscreteProperty>(defaultCharPropUuid);
	REQUIRE(charDiscreteProperty->getValuesHdfDatatype() == AbstractValuesProperty::CHAR);
	RESQML2_0_1_NS::DiscreteProperty* shortDiscreteProperty = repo->getDataObjectByUuid<RESQML2_0_1_NS::DiscreteProperty>(defaultShortPropUuid);
	REQUIRE(shortDiscreteProperty->getValuesHdfDatatype() == AbstractValuesProperty::SHORT);
	RESQML2_0_1_NS::DiscreteProperty* ushortDiscreteProperty = repo->getDataObjectByUuid<RESQML2_0_1_NS::DiscreteProperty>(defaultUShortPropUuid);
	REQUIRE(ushortDiscreteProperty->getValuesHdfDatatype() == AbstractValuesProperty::USHORT);
	RESQML2_0_1_NS::DiscreteProperty* intDiscreteProperty = repo->getDataObjectByUuid<RESQML2_0_1_NS::DiscreteProperty>(defaultIntPropUuid);
	REQUIRE(intDiscreteProperty->getValuesHdfDatatype() == AbstractValuesProperty::INT);
	RESQML2_0_1_NS::DiscreteProperty* longDiscreteProperty = repo->getDataObjectByUuid<RESQML2_0_1_NS::DiscreteProperty>(defaultLongPropUuid);
	REQUIRE(longDiscreteProperty->getValuesHdfDatatype() == AbstractValuesProperty::LONG_64);
}
