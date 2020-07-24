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
#include "resqml2_test/StratigraphicUnitInterpretationTest.h"

#include <stdexcept>

#include "catch.hpp"
#include "resqml2_test/StratigraphicUnitTest.h"

#include "common/EpcDocument.h"
#include "resqml2/RockVolumeFeature.h"
#include "resqml2/StratigraphicUnitInterpretation.h"
#include <stdexcept>

using namespace std;
using namespace resqml2_test;
using namespace COMMON_NS;
using namespace RESQML2_NS;

const char* StratigraphicUnitInterpretationTest::defaultUuid = "65abde7d-d6ab-42b5-89c8-cc6ccec56dcc";
const char* StratigraphicUnitInterpretationTest::defaultTitle = "Strati Unit Interp";

StratigraphicUnitInterpretationTest::StratigraphicUnitInterpretationTest(const string & epcDocPath)
	: commontest::AbstractObjectTest(epcDocPath) {
}

StratigraphicUnitInterpretationTest::StratigraphicUnitInterpretationTest(DataObjectRepository* repo, bool init)
	: commontest::AbstractObjectTest(repo) {
	if (init)
		initRepo();
	else
		readRepo();
}

void StratigraphicUnitInterpretationTest::initRepoHandler() {
	// creating dependencies
	StratigraphicUnitTest* stratiUnitTest = new StratigraphicUnitTest(repo, true);

	RockVolumeFeature* stratiUnit = this->repo->getDataObjectByUuid<RockVolumeFeature>(StratigraphicUnitTest::defaultTitle);

	// cleaning
	delete stratiUnitTest;

	StratigraphicUnitInterpretation* stratiUnitInterp = repo->createStratigraphicUnitInterpretation(stratiUnit, defaultUuid, defaultTitle);
	REQUIRE(stratiUnitInterp != nullptr);
}

void StratigraphicUnitInterpretationTest::readRepoHandler() {
}
