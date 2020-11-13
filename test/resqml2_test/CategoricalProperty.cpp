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

#include "catch.hpp"
#include "resqml2_test/LgrOnRightHanded4x3x2ExplicitIjkGrid.h"
#include "resqml2_test/PropertyKindTest.h"
#include "resqml2_test/WellboreFrameRepresentationTest.h"

#include "resqml2_0_1/PropertyKind.h"
#include "eml2_3/PropertyKind.h"
#include "resqml2/CategoricalProperty.h"
#include "resqml2/DoubleTableLookup.h"
#include "resqml2/StringTableLookup.h"
#include "resqml2/AbstractIjkGridRepresentation.h"
#include "eml2/AbstractHdfProxy.h"

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
	RESQML2_NS::StringTableLookup* stringTableLookup = repo->createStringTableLookup("62245eb4-dbf4-4871-97de-de9e4f4597be", "My String Table Lookup");
	stringTableLookup->addValue("Item 0", 0);
	stringTableLookup->addValue("Item 1", 1);
	stringTableLookup->addValue("Item 2", 2);
	stringTableLookup->addValue("Item 3", 3);
	stringTableLookup->addValue("Item 4", 4);
	stringTableLookup->addValue("Item 5", 5);
	
	// creating the char CategoricalProperty
	RESQML2_NS::CategoricalProperty* charCategoricalProperty = repo->createCategoricalProperty(
		ijkGrid, defaultUuid, defaultTitle,
		1,
		gsoap_eml2_3::resqml22__IndexableElement__cells,
		stringTableLookup,
		propertyKind);
	char charValues[6] = { 0, 1, 2, 3, 4, 5 };
	charCategoricalProperty->pushBackCharHdf5Array3dOfValues(charValues, 1, 2, 3, hdfProxy, -1);

	// creating the Double Table Lookup
	RESQML2_NS::DoubleTableLookup* dblTableLookup = repo->createDoubleTableLookup("0df04180-8bb1-4ca2-90c2-c48bfd4b0958", "My Double Table Lookup");
	dblTableLookup->addValue(.0, .0);
	dblTableLookup->addValue(1.25, 0.52);
	dblTableLookup->addValue(2.451, 0.625);
	dblTableLookup->addValue(3.9, 0.845662);
	dblTableLookup->addValue(6.1, .1);

	// creating the char CategoricalProperty
	RESQML2_NS::CategoricalProperty* dblCategoricalProperty = repo->createCategoricalProperty(
		ijkGrid, "3de7a1d8-8b5b-45f3-b90c-6c14b2dcb43e", "Continuous Categorical Property",
		1,
		gsoap_eml2_3::resqml22__IndexableElement__cells,
		dblTableLookup,
		propertyKind);
	double dblValues[6] = { .0, .1, .2, .3, .4, .5 };
	dblCategoricalProperty->pushBackDoubleHdf5Array3dOfValues(dblValues, 1, 2, 3, hdfProxy);
}

void CategoricalProperty::readRepo() {
	// getting the string CategoricalProperty
	RESQML2_NS::CategoricalProperty* categoricalProperty = repo->getDataObjectByUuid<RESQML2_NS::CategoricalProperty>(defaultUuid);
	auto strTableLookup = categoricalProperty->getStringLookup();
	REQUIRE(strTableLookup->getItemCount() == 6);
	REQUIRE(strTableLookup->getStringValue(0) == "Item 0");
	REQUIRE(strTableLookup->getStringValueAtIndex(1) == "Item 1");
	REQUIRE(strTableLookup->getKeyAtIndex(2) == 2);
	REQUIRE(strTableLookup->getStringValue(3) == "Item 3");
	REQUIRE(strTableLookup->getStringValue(4) == "Item 4");
	REQUIRE(strTableLookup->getStringValue(5) == "Item 5");

	// getting the continuous CategoricalProperty
	categoricalProperty = repo->getDataObjectByUuid<RESQML2_NS::CategoricalProperty>("3de7a1d8-8b5b-45f3-b90c-6c14b2dcb43e");
	auto dblTableLookup = categoricalProperty->getDoubleLookup();
	REQUIRE(dblTableLookup->getItemCount() == 5);
	REQUIRE(dblTableLookup->getValueAtIndex(0) == .0);
	REQUIRE(dblTableLookup->getValueAtKey(1.25) == 0.52);
	REQUIRE(dblTableLookup->getKeyAtIndex(2) == 2.451);
}
