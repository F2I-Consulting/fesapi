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
#include "resqml2_test/DiscreteProperty.h"

#include "catch.hpp"

#include "resqml2_0_1/PropertyKind.h"
#include "eml2_3/PropertyKind.h"
#include "resqml2/DiscreteProperty.h"
#include "resqml2/AbstractIjkGridRepresentation.h"
#include "eml2/AbstractHdfProxy.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_test;

const char* DiscreteProperty::defaultCharPropUuid = "5aa6a9d4-253e-43a8-bdf5-621e5df2d425";
const char* DiscreteProperty::defaultShortPropUuid = "61acbc7f-fb9b-4578-800e-f310e947b865";
const char* DiscreteProperty::defaultUShortPropUuid = "0eae558f-e57b-47b1-9772-a336e99fd714";
const char* DiscreteProperty::defaultIntPropUuid = "a0721fbe-fb09-4d0f-aab3-315eca8e416e";
const char* DiscreteProperty::defaultLongPropUuid = "eda57b20-4639-4541-87b9-c2b44b46c336";

DiscreteProperty::DiscreteProperty(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void DiscreteProperty::initRepo() {
	RESQML2_NS::AbstractIjkGridRepresentation* ijkGrid = repo->createPartialIjkGridRepresentation("", "partial IJK Grid");
	EML2_NS::PropertyKind * propertyKind = repo->createPartial<RESQML2_0_1_NS::PropertyKind>("", "Partial prop kind");

	// getting the hdf proxy
	EML2_NS::AbstractHdfProxy* hdfProxy = repo->getHdfProxySet()[0];

	// creating the char DiscreteProperty
	RESQML2_NS::DiscreteProperty* charDiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultCharPropUuid, "char prop",
		1,
		gsoap_eml2_3::resqml22__IndexableElement__cells,
		propertyKind);
	char charValues[6] = { 0, 1, 2, 3, 4, 5 };
	charDiscreteProperty->pushBackCharHdf5Array3dOfValues(charValues, 1, 2, 3, hdfProxy, -1);

	// creating the short DiscreteProperty
	RESQML2_NS::DiscreteProperty* shortDiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultShortPropUuid, "short prop",
		1,
		gsoap_eml2_3::resqml22__IndexableElement__cells,
		propertyKind);
	short shortValues[6] = { 0, 1, 2, 3, 4, 5 };
	shortDiscreteProperty->pushBackShortHdf5Array3dOfValues(shortValues, 1, 2, 3, hdfProxy, -1);

	// creating the ushort DiscreteProperty
	RESQML2_NS::DiscreteProperty* ushortDiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultUShortPropUuid, "ushort prop",
		1,
		gsoap_eml2_3::resqml22__IndexableElement__cells,
		propertyKind);
	unsigned short ushortValues[6] = { 0, 1, 2, 3, 4, 5 };
	ushortDiscreteProperty->pushBackUShortHdf5Array3dOfValues(ushortValues, 1, 2, 3, hdfProxy, -1);

	// creating the int DiscreteProperty
	RESQML2_NS::DiscreteProperty* intDiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultIntPropUuid, "int prop",
		1,
		gsoap_eml2_3::resqml22__IndexableElement__cells,
		propertyKind);
	int intValues[6] = { 0, 1, 2, 3, 4, 5 };
	intDiscreteProperty->pushBackIntHdf5Array3dOfValues(intValues, 1, 2, 3, hdfProxy, -1);

	// creating the long DiscreteProperty
	RESQML2_NS::DiscreteProperty* longDiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultLongPropUuid, "long prop",
		1,
		gsoap_eml2_3::resqml22__IndexableElement__cells,
		propertyKind);
	int64_t longValues[6] = { 0, 1, 2, 3, 4, 5 };
	longDiscreteProperty->pushBackLongHdf5Array3dOfValues(longValues, 1, 2, 3, hdfProxy, -1);
}

void DiscreteProperty::readRepo() {
	// getting the DiscreteProperty
	RESQML2_NS::DiscreteProperty* charDiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultCharPropUuid);
	REQUIRE(charDiscreteProperty->getValuesHdfDatatype() == RESQML2_NS::AbstractValuesProperty::CHAR);
	RESQML2_NS::DiscreteProperty* shortDiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultShortPropUuid);
	REQUIRE(shortDiscreteProperty->getValuesHdfDatatype() == RESQML2_NS::AbstractValuesProperty::SHORT);
	RESQML2_NS::DiscreteProperty* ushortDiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultUShortPropUuid);
	REQUIRE(ushortDiscreteProperty->getValuesHdfDatatype() == RESQML2_NS::AbstractValuesProperty::USHORT);
	RESQML2_NS::DiscreteProperty* intDiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultIntPropUuid);
	REQUIRE(intDiscreteProperty->getValuesHdfDatatype() == RESQML2_NS::AbstractValuesProperty::INT);
	RESQML2_NS::DiscreteProperty* longDiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultLongPropUuid);
	REQUIRE(longDiscreteProperty->getValuesHdfDatatype() == RESQML2_NS::AbstractValuesProperty::LONG_64);
}
