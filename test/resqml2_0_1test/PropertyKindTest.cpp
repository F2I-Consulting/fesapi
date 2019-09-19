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
#include "PropertyKindTest.h"
#include "../catch.hpp"
#include "common/EpcDocument.h"
#include "resqml2/PropertyKind.h"
#include <stdexcept>

using namespace std;
using namespace resqml2_0_1test;
using namespace COMMON_NS;
using namespace RESQML2_NS;

const char* PropertyKindTest::defaultUuid = "f1effef1-6bc7-4e82-829b-797713b60cdc";
const char* PropertyKindTest::defaultTitle = "Property Kind Test";

PropertyKindTest::PropertyKindTest(const string & repoPath)
	: commontest::AbstractObjectTest(repoPath) {
}

PropertyKindTest::PropertyKindTest(DataObjectRepository* repo, bool init)
	: commontest::AbstractObjectTest(repo) {
	if (init)
		initRepo();
	else
		readRepo();
}

void PropertyKindTest::initRepoHandler() {
	PropertyKind* propertyKind = repo->createPropertyKind(defaultUuid, defaultTitle, "F2I", gsoap_resqml2_0_1::resqml20__ResqmlUom__Euc, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind__index);
	REQUIRE(propertyKind != nullptr);
}

void PropertyKindTest::readRepoHandler() {
	// getting the PropertyKind
	PropertyKind* propertyKind = repo->getDataObjectByUuid<PropertyKind>(defaultUuid);

	REQUIRE(propertyKind->getNamingSystem().compare("F2I") == 0);
	REQUIRE(propertyKind->getUom() == gsoap_resqml2_0_1::resqml20__ResqmlUom__Euc);
	REQUIRE(propertyKind->isParentAnEnergisticsPropertyKind());
	REQUIRE(propertyKind->getParentEnergisticsPropertyKind() == gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind__index);
	REQUIRE_THROWS(propertyKind->getParentLocalPropertyKind());
	REQUIRE_THROWS(propertyKind->getParentLocalPropertyKindTitle());
	REQUIRE_THROWS(propertyKind->getParentLocalPropertyKindUuid());
}
