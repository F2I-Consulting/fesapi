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
#include "eml2/PropertyKind.h"
#include <stdexcept>

using namespace std;
using namespace resqml2_test;
using namespace COMMON_NS;
using namespace RESQML2_NS;

const char* PropertyKindTest::defaultUuid = "f1effef1-6bc7-4e82-829b-797713b60cdc";
const char* PropertyKindTest::defaultTitle = "Property Kind Test";

PropertyKindTest::PropertyKindTest(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void PropertyKindTest::initRepo() {
	auto parentPropertyKind = repo->createPropertyKind("a48c9c25-1e3a-43c8-be6a-044224cc69cb", "property", gsoap_eml2_1::eml21__QuantityClassKind__unitless);
	auto propertyKind = repo->createPropertyKind(defaultUuid, defaultTitle, gsoap_eml2_1::eml21__QuantityClassKind__not_x0020a_x0020measure, false, parentPropertyKind);
	REQUIRE(propertyKind != nullptr);
}

void PropertyKindTest::readRepo() {
	// getting the PropertyKind
	EML2_NS::PropertyKind* propertyKind = repo->getDataObjectByUuid<EML2_NS::PropertyKind>(defaultUuid);

	REQUIRE(propertyKind->getParentPropertyKindDor().getUuid() == "a48c9c25-1e3a-43c8-be6a-044224cc69cb");
}
