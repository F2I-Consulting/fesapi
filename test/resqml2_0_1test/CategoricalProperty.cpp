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
#include "resqml2_0_1test/CategoricalProperty.h"

#include "catch.hpp"
#include "resqml2_0_1test/LgrOnRightHanded4x3x2ExplicitIjkGrid.h"
#include "resqml2_0_1test/PropertyKindTest.h"
#include "resqml2_0_1test/WellboreFrameRepresentationTest.h"

#include "eml2_3/PropertyKind.h"
#include "resqml2/CategoricalProperty.h"
#include "resqml2/StringTableLookup.h"
#include "resqml2/AbstractIjkGridRepresentation.h"
#include "eml2/AbstractHdfProxy.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_0_1test;

const char* CategoricalProperty::defaultUuid = "5aa6a9d4-253e-43a8-bdf5-621e5df2d425";
const char* CategoricalProperty::defaultTitle = "Testing Categorical Prop";

CategoricalProperty::CategoricalProperty(const string & repoPath)
	: commontest::AbstractObjectTest(repoPath) {
}

CategoricalProperty::CategoricalProperty(DataObjectRepository * repo, bool init)
	: commontest::AbstractObjectTest(repo) {
	if (init)
		initRepo();
	else
		readRepo();
}

void CategoricalProperty::initRepoHandler() {
	RESQML2_NS::AbstractIjkGridRepresentation* ijkGrid = repo->createPartialIjkGridRepresentation("", "partial IJK Grid");
	EML2_NS::PropertyKind * propertyKind = repo->createPartial<EML2_3_NS::PropertyKind>("", "Partial prop kind");

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
}

void CategoricalProperty::readRepoHandler() {
	// getting the CategoricalProperty
	RESQML2_NS::CategoricalProperty* categoricalProperty = repo->getDataObjectByUuid<RESQML2_NS::CategoricalProperty>(defaultUuid);
	auto strTableLookup = categoricalProperty->getStringLookup();
	REQUIRE(strTableLookup->getItemCount() == 6);
	REQUIRE(strTableLookup->getStringValue(0) == "Item 0");
	REQUIRE(strTableLookup->getStringValue(1) == "Item 1");
	REQUIRE(strTableLookup->getStringValue(2) == "Item 2");
	REQUIRE(strTableLookup->getStringValue(3) == "Item 3");
	REQUIRE(strTableLookup->getStringValue(4) == "Item 4");
	REQUIRE(strTableLookup->getStringValue(5) == "Item 5");
}
