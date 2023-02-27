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

#include "resqml2_0_1/PropertyKind.h"
#include "eml2_3/PropertyKind.h"
#include "resqml2/DiscreteProperty.h"
#include "resqml2/AbstractIjkGridRepresentation.h"
#include "eml2/AbstractHdfProxy.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_test;

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
		gsoap_eml2_3::eml23__IndexableElement::cells,
		propertyKind);
	int8_t charValues[6] = { 0, 1, 2, 3, 4, 5 };
	charDiscreteProperty->pushBackInt8Hdf5Array3dOfValues(charValues, 1, 2, 3, hdfProxy, -1);

	// creating the short DiscreteProperty
	RESQML2_NS::DiscreteProperty* shortDiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultShortPropUuid, "short prop",
		gsoap_eml2_3::eml23__IndexableElement::cells,
		propertyKind);
	short shortValues[6] = { 0, 1, 2, 3, 4, 5 };
	shortDiscreteProperty->pushBackShortHdf5Array3dOfValues(shortValues, 1, 2, 3, hdfProxy, -1);

	// creating the ushort DiscreteProperty
	RESQML2_NS::DiscreteProperty* ushortDiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultUShortPropUuid, "ushort prop",
		gsoap_eml2_3::eml23__IndexableElement::cells,
		propertyKind);
	unsigned short ushortValues[6] = { 0, 1, 2, 3, 4, 5 };
	ushortDiscreteProperty->pushBackUShortHdf5Array3dOfValues(ushortValues, 1, 2, 3, hdfProxy, -1);

	// creating the int DiscreteProperty
	RESQML2_NS::DiscreteProperty* intDiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultIntPropUuid, "int prop",
		gsoap_eml2_3::eml23__IndexableElement::cells,
		propertyKind);
	int intValues[6] = { 0, 1, 2, 3, 4, 5 };
	intDiscreteProperty->pushBackIntHdf5Array3dOfValues(intValues, 1, 2, 3, hdfProxy, -1);

	// creating the Int64 DiscreteProperty
	RESQML2_NS::DiscreteProperty* int64DiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultInt64PropUuid, "Int64 prop",
		gsoap_eml2_3::eml23__IndexableElement::cells,
		propertyKind);
	int64_t int64Values[6] = { 0, 1, 2, 3, 4, 5 };
	int64DiscreteProperty->pushBackInt64Hdf5Array3dOfValues(int64Values, 1, 2, 3, hdfProxy, -1);

	// creating Constant Integer prop
	RESQML2_NS::DiscreteProperty* constantIntegerProperty = repo->createDiscreteProperty(
		ijkGrid, "d6896172-795c-46be-bdd1-f9f9ed42f1f0", "Constant Integer Property",
		gsoap_eml2_3::eml23__IndexableElement::cells,
		propertyKind);
	constantIntegerProperty->pushBackIntegerConstantArrayOfValues(10, 3);
}

void DiscreteProperty::readRepo() {
	// getting the DiscreteProperty
	RESQML2_NS::DiscreteProperty* charDiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultCharPropUuid);
	REQUIRE(charDiscreteProperty->getValuesHdfDatatype() == COMMON_NS::AbstractObject::numericalDatatypeEnum::INT8);
	RESQML2_NS::DiscreteProperty* shortDiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultShortPropUuid);
	REQUIRE(shortDiscreteProperty->getValuesHdfDatatype() == COMMON_NS::AbstractObject::numericalDatatypeEnum::INT16);
	RESQML2_NS::DiscreteProperty* ushortDiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultUShortPropUuid);
	REQUIRE(ushortDiscreteProperty->getValuesHdfDatatype() == COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT16);
	RESQML2_NS::DiscreteProperty* intDiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultIntPropUuid);
	REQUIRE(intDiscreteProperty->getValuesHdfDatatype() == COMMON_NS::AbstractObject::numericalDatatypeEnum::INT32);
	RESQML2_NS::DiscreteProperty* int64DiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultInt64PropUuid);
	REQUIRE(int64DiscreteProperty->getValuesHdfDatatype() == COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64);
	REQUIRE(!int64DiscreteProperty->hasConstantValues(0));

	RESQML2_NS::DiscreteProperty* constantDiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>("d6896172-795c-46be-bdd1-f9f9ed42f1f0");
	REQUIRE(constantDiscreteProperty->getValuesHdfDatatype() == COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64);
	REQUIRE(constantDiscreteProperty->getValuesCountOfPatch(0) == 3);
	int64_t constantDiscreteValues[3];
	constantDiscreteProperty->getInt64ValuesOfPatch(0, constantDiscreteValues);
	REQUIRE(constantDiscreteValues[0] == 10);
	REQUIRE(constantDiscreteValues[1] == 10);
	REQUIRE(constantDiscreteValues[2] == 10);
	REQUIRE(constantDiscreteProperty->hasConstantValues(0));
	REQUIRE(constantDiscreteProperty->getInt64ConstantValuesOfPatch(0) == 10);
	REQUIRE_THROWS(constantDiscreteProperty->getDoubleConstantValuesOfPatch(0));
}
