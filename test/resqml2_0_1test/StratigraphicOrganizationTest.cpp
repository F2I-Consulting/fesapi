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
#include "resqml2_0_1test/StratigraphicOrganizationTest.h"

#include <stdexcept>

#include "catch.hpp"

#include "common/EpcDocument.h"
#include "resqml2_0_1/OrganizationFeature.h"
#include <stdexcept>

using namespace std;
using namespace resqml2_0_1test;
using namespace COMMON_NS;
using namespace RESQML2_0_1_NS;

const char* StratigraphicOrganizationTest::defaultUuid = "8567b4b5-3e03-4e8e-bf69-b77965bea29f";
const char* StratigraphicOrganizationTest::defaultTitle = "Strati Organization";

StratigraphicOrganizationTest::StratigraphicOrganizationTest(const string & epcDocPath)
	: AbstractFeatureTest(epcDocPath, defaultUuid, defaultTitle) {
}

StratigraphicOrganizationTest::StratigraphicOrganizationTest(EpcDocument* epcDoc, bool init)
	: AbstractFeatureTest(epcDoc, defaultUuid, defaultTitle) {
	if (init)
			initEpcDoc();
		else
			readEpcDoc();
}

void StratigraphicOrganizationTest::initEpcDocHandler() {
	OrganizationFeature* stratiOrg = epcDoc->createStratigraphicModel(uuid, title);
	REQUIRE(stratiOrg != nullptr);
}

void StratigraphicOrganizationTest::readEpcDocHandler() {
}

