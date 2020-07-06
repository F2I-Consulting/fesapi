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
#include "resqml2_0_1test/StratigraphicUnitTest.h"

#include <stdexcept>

#include "catch.hpp"

#include "common/EpcDocument.h"
#include "resqml2/RockVolumeFeature.h"
#include <stdexcept>

using namespace std;
using namespace resqml2_0_1test;
using namespace COMMON_NS;
using namespace RESQML2_NS;

const char* StratigraphicUnitTest::defaultUuid = "e9e8ce58-b53a-4425-84c7-667642027a4a";
const char* StratigraphicUnitTest::defaultTitle = "Strati Unit";

StratigraphicUnitTest::StratigraphicUnitTest(const string & epcDocPath)
	: commontest::AbstractObjectTest(epcDocPath) {
}

StratigraphicUnitTest::StratigraphicUnitTest(DataObjectRepository* repo, bool init)
	: commontest::AbstractObjectTest(repo) {
	if (init)
		initRepo();
	else
		readRepo();
}

void StratigraphicUnitTest::initRepoHandler() {
	RockVolumeFeature* stratiUnit = repo->createStratigraphicUnitFeature(defaultUuid, defaultTitle);
	REQUIRE(stratiUnit != nullptr);
}

void StratigraphicUnitTest::readRepoHandler() {
}
