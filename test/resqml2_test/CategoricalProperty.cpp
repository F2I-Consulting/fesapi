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
#include "resqml2_test/CategoricalProperty.h"

#include "resqml2_test/LgrOnRightHanded4x3x2ExplicitIjkGrid.h"
#include "resqml2_test/PropertyKindTest.h"
#include "resqml2_test/WellboreFrameRepresentationTest.h"

#include "eml2/AbstractHdfProxy.h"
#include "eml2/ColumnBasedTable.h"

#include "eml2_3/PropertyKind.h"

#include "resqml2/AbstractIjkGridRepresentation.h"
#include "resqml2/DiscreteProperty.h"

#include "resqml2_0_1/PropertyKind.h"
#include "resqml2_0_1/DoubleTableLookup.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_test;

const char* CategoricalProperty::defaultUuid = "5aa6a9d4-253e-43a8-bdf5-621e5df2d425";
const char* CategoricalProperty::defaultTitle = "Testing Categorical Prop";

CategoricalProperty::CategoricalProperty(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void CategoricalProperty::initRepo() {
	RESQML2_NS::AbstractIjkGridRepresentation* ijkGrid = repo->createPartialIjkGridRepresentation("", "partial IJK Grid");
	EML2_NS::PropertyKind * propertyKind = repo->createPartial<RESQML2_0_1_NS::PropertyKind>("", "Partial prop kind");

	// getting the hdf proxy
	EML2_NS::AbstractHdfProxy* hdfProxy = repo->getHdfProxySet()[0];

	// creating the String Table Lookup
	auto* stringTableLookup = repo->createFaciesTable("62245eb4-dbf4-4871-97de-de9e4f4597be", "My String Table Lookup");
	stringTableLookup->setInt64Values(0, { 0,1,2,3,4,5 });
	stringTableLookup->setStringValues(1, { "Item 0","Item 1","Item 2","Item 3","Item 4","Item 5" });
	
	// creating the char CategoricalProperty
	RESQML2_NS::DiscreteProperty* charCategoricalProperty = repo->createCategoricalProperty(
		ijkGrid, defaultUuid, defaultTitle,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		stringTableLookup,
		propertyKind);
	int8_t charValues[6] = { 0, 1, 2, 3, 4, 5 };
	charCategoricalProperty->pushBackInt8Hdf5Array3dOfValues(charValues, 1, 2, 3, hdfProxy, -1);

	// creating the Double Table Lookup
	RESQML2_0_1_NS::DoubleTableLookup* dblTableLookup = repo->createDoubleTableLookup("0df04180-8bb1-4ca2-90c2-c48bfd4b0958", "My Double Table Lookup");
	dblTableLookup->setDoubleValues(0, { .0, 1.25, 2.451, 3.9, 6.1 });
	dblTableLookup->setDoubleValues(1, { .0, 0.52, 0.625, 0.845662, .1 });

	// creating the char CategoricalProperty
	RESQML2_NS::DiscreteProperty* dblCategoricalProperty = repo->createCategoricalProperty(
		ijkGrid, "3de7a1d8-8b5b-45f3-b90c-6c14b2dcb43e", "Continuous Categorical Property",
		gsoap_eml2_3::eml23__IndexableElement::cells,
		dblTableLookup,
		propertyKind);
	double dblValues[6] = { .0, .1, .2, .3, .4, .5 };
	dblCategoricalProperty->pushBackDoubleHdf5Array3dOfValues(dblValues, 1, 2, 3, hdfProxy);
}

void CategoricalProperty::readRepo() {
	// getting the string CategoricalProperty
	RESQML2_NS::DiscreteProperty* categoricalProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>(defaultUuid);
	auto* strTableLookup = categoricalProperty->getLookup();
	REQUIRE(strTableLookup->getRowCount() == 6);
	REQUIRE(strTableLookup->getColumnCount() == 2);
	REQUIRE(strTableLookup->getDatatype(0) == COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64);
	REQUIRE(strTableLookup->getDatatype(1) == COMMON_NS::AbstractObject::numericalDatatypeEnum::STRING);
	REQUIRE(strTableLookup->getInt64Values(0)[0] == 0);
	REQUIRE(strTableLookup->getStringValues(1)[0] == "Item 0");
	REQUIRE(strTableLookup->getInt64Values(0)[1] == 1);
	REQUIRE(strTableLookup->getStringValues(1)[1] == "Item 1");
	REQUIRE(strTableLookup->getInt64Values(0)[2] == 2);
	REQUIRE(strTableLookup->getStringValues(1)[2] == "Item 2");
	REQUIRE(strTableLookup->getInt64Values(0)[3] == 3);
	REQUIRE(strTableLookup->getStringValues(1)[3] == "Item 3");
	REQUIRE(strTableLookup->getInt64Values(0)[4] == 4);
	REQUIRE(strTableLookup->getStringValues(1)[4] == "Item 4");
	REQUIRE(strTableLookup->getInt64Values(0)[5] == 5);
	REQUIRE(strTableLookup->getStringValues(1)[5] == "Item 5");

	// getting the continuous CategoricalProperty
	categoricalProperty = repo->getDataObjectByUuid<RESQML2_NS::DiscreteProperty>("3de7a1d8-8b5b-45f3-b90c-6c14b2dcb43e");
	auto* dblTableLookup = categoricalProperty->getLookup();
	REQUIRE(dblTableLookup->getRowCount() == 5);
	REQUIRE(dblTableLookup->getColumnCount() == 2);
	REQUIRE(dblTableLookup->getDatatype(0) == COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE);
	REQUIRE(dblTableLookup->getDatatype(1) == COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE);
	const auto keys = dblTableLookup->getDoubleValues(0);
	const auto values = dblTableLookup->getDoubleValues(1);
	REQUIRE(keys[0] == .0);
	REQUIRE(values[0] == .0);
	REQUIRE(keys[1] == 1.25);
	REQUIRE(values[1] == 0.52);
	REQUIRE(keys[2] == 2.451);
	REQUIRE(values[2] == 0.625);
	REQUIRE(keys[3] == 3.9);
	REQUIRE(values[3] == 0.845662);
	REQUIRE(keys[4] == 6.1);
	REQUIRE(values[4] == .1);
}
