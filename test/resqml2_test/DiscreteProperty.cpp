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

#include "eml2/AbstractHdfProxy.h"

#include "eml2_3/PropertyKind.h"

#include "resqml2/AbstractIjkGridRepresentation.h"
#include "resqml2/DiscreteProperty.h"

#include "resqml2_0_1/PropertyKind.h"

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

	// creating the int8_t DiscreteProperty
	RESQML2_NS::DiscreteProperty* int8DiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultInt8PropUuid, "int8_t prop",
		1,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		propertyKind);
	int8_t int8Values[6] = { -2, -1, 0, 1, 2, 3 };
	int8DiscreteProperty->pushBackArray3dOfValues(int8Values, 1, 2, 3, hdfProxy, static_cast<int8_t>(-1));

	// creating the uint8_t DiscreteProperty
	RESQML2_NS::DiscreteProperty* uint8DiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultUInt8PropUuid, "uint8_t prop",
		1,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		propertyKind);
	uint8_t uint8Values[6] = { 0, 1, 2, 3, 4, 5 };
	uint8DiscreteProperty->pushBackArray3dOfValues(uint8Values, 1, 2, 3, hdfProxy);

	// creating the int16_t DiscreteProperty
	RESQML2_NS::DiscreteProperty* int16DiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultInt16PropUuid, "int16_t prop",
		1,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		propertyKind);
	int16_t int16Values[6] = { -2, -1, 0, 1, 2, 3 };
	int16DiscreteProperty->pushBackArray3dOfValues(int16Values, 1, 2, 3, hdfProxy, static_cast<int16_t>(-1));

	// creating the uint16_t DiscreteProperty
	RESQML2_NS::DiscreteProperty* uint16DiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultUInt16PropUuid, "uint16_t prop",
		1,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		propertyKind);
	uint16_t uint16Values[6] = { 0, 1, 2, 3, 4, 5 };
	uint16DiscreteProperty->pushBackArray3dOfValues(uint16Values, 1, 2, 3, hdfProxy);

	// creating the int32_t DiscreteProperty
	RESQML2_NS::DiscreteProperty* int32DiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultInt32PropUuid, "int32_t prop",
		1,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		propertyKind);
	int32_t int32Values[6] = { -2, -1, 0, 1, 2, 3 };
	int32DiscreteProperty->pushBackArray3dOfValues(int32Values, 1, 2, 3, hdfProxy, -1);

	// creating the uint32_t DiscreteProperty
	RESQML2_NS::DiscreteProperty* uint32DiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultUInt32PropUuid, "uint32_t prop",
		1,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		propertyKind);
	uint32_t uint32Values[6] = { 0, 1, 2, 3, 4, 5 };
	uint32DiscreteProperty->pushBackArray3dOfValues(uint32Values, 1, 2, 3, hdfProxy);

	// creating the int64_t DiscreteProperty
	RESQML2_NS::DiscreteProperty* int64DiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultInt64PropUuid, "int64_t prop",
		1,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		propertyKind);
	int64_t int64Values[6] = { -2, -1, 0, 1, 2, 3 };
	int64DiscreteProperty->pushBackArray3dOfValues(int64Values, 1, 2, 3, hdfProxy, static_cast<int64_t>(-1));

	// creating the uint64_t DiscreteProperty
	RESQML2_NS::DiscreteProperty* uint64DiscreteProperty = repo->createDiscreteProperty(
		ijkGrid, defaultUInt64PropUuid, "uint64_t prop",
		1,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		propertyKind);
	uint64_t uint64Values[6] = { 0, 1, 2, 3, 4, 5 };
	uint64DiscreteProperty->pushBackArray3dOfValues(uint64Values, 1, 2, 3, hdfProxy);

	// creating Constant Integer prop
	RESQML2_NS::DiscreteProperty* constantIntegerProperty = repo->createDiscreteProperty(
		ijkGrid, "d6896172-795c-46be-bdd1-f9f9ed42f1f0", "Constant Integer Property",
		1,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		propertyKind);
	constantIntegerProperty->pushBackIntegerConstantArrayOfValues(10, 3);
}

namespace {
	void checkSignedProperty(RESQML2_NS::DiscreteProperty* unsignedProp) {
		int64_t values[6];
		unsignedProp->getArrayOfValuesOfPatch(0, values);
		REQUIRE(values[0] == -2);
		REQUIRE(values[1] == -1);
		REQUIRE(values[2] == 0);
		REQUIRE(values[3] == 1);
		REQUIRE(values[4] == 2);
		REQUIRE(values[5] == 3);
	}
	void checkUnsignedProperty(RESQML2_NS::DiscreteProperty * signedProp) {
		uint64_t values[6];
		signedProp->getArrayOfValuesOfPatch(0, values);
		REQUIRE(values[0] == 0);
		REQUIRE(values[1] == 1);
		REQUIRE(values[2] == 2);
		REQUIRE(values[3] == 3);
		REQUIRE(values[4] == 4);
		REQUIRE(values[5] == 5);
	}
}

void DiscreteProperty::readRepo() {
	// getting the DiscreteProperty
	RESQML2_NS::DiscreteProperty* int8DiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultInt8PropUuid);
	REQUIRE(int8DiscreteProperty->getValuesHdfDatatype() == COMMON_NS::AbstractObject::numericalDatatypeEnum::INT8);
	checkSignedProperty(int8DiscreteProperty);
	RESQML2_NS::DiscreteProperty* uint8DiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultUInt8PropUuid);
	REQUIRE(uint8DiscreteProperty->getValuesHdfDatatype() == COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT8);
	checkUnsignedProperty(uint8DiscreteProperty);
	RESQML2_NS::DiscreteProperty* int16DiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultInt16PropUuid);
	REQUIRE(int16DiscreteProperty->getValuesHdfDatatype() == COMMON_NS::AbstractObject::numericalDatatypeEnum::INT16);
	checkSignedProperty(int16DiscreteProperty);
	RESQML2_NS::DiscreteProperty* uint16DiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultUInt16PropUuid);
	REQUIRE(uint16DiscreteProperty->getValuesHdfDatatype() == COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT16);
	checkUnsignedProperty(uint16DiscreteProperty);
	RESQML2_NS::DiscreteProperty* int32DiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultInt32PropUuid);
	REQUIRE(int32DiscreteProperty->getValuesHdfDatatype() == COMMON_NS::AbstractObject::numericalDatatypeEnum::INT32);
	checkSignedProperty(int32DiscreteProperty);
	RESQML2_NS::DiscreteProperty* uint32DiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultUInt32PropUuid);
	REQUIRE(uint32DiscreteProperty->getValuesHdfDatatype() == COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT32);
	checkUnsignedProperty(uint32DiscreteProperty);
	RESQML2_NS::DiscreteProperty* int64DiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultInt64PropUuid);
	REQUIRE(int64DiscreteProperty->getValuesHdfDatatype() == COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64);
	checkSignedProperty(int64DiscreteProperty);
	RESQML2_NS::DiscreteProperty* uint64DiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultUInt64PropUuid);
	REQUIRE(uint64DiscreteProperty->getValuesHdfDatatype() == COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT64);
	checkUnsignedProperty(uint64DiscreteProperty);
	REQUIRE(!int64DiscreteProperty->hasConstantValues(0));

	RESQML2_NS::DiscreteProperty* constantDiscreteProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>("d6896172-795c-46be-bdd1-f9f9ed42f1f0");
	REQUIRE(constantDiscreteProperty->getValuesHdfDatatype() == COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64);
	REQUIRE(constantDiscreteProperty->getValuesCountOfPatch(0) == 3);
	int64_t constantDiscreteValues[3];
	constantDiscreteProperty->getArrayOfValuesOfPatch(0, constantDiscreteValues);
	REQUIRE(constantDiscreteValues[0] == 10);
	REQUIRE(constantDiscreteValues[1] == 10);
	REQUIRE(constantDiscreteValues[2] == 10);
	REQUIRE(constantDiscreteProperty->hasConstantValues(0));
	REQUIRE(constantDiscreteProperty->getInt64ConstantValuesOfPatch(0) == 10);
	REQUIRE_THROWS(constantDiscreteProperty->getDoubleConstantValuesOfPatch(0));
}
