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
#include "resqml2_0_1test/StratigraphicUnitInterpretationTest.h"

#include <stdexcept>

#include "catch.hpp"
#include "resqml2_0_1test/StratigraphicUnitTest.h"

#include "common/EpcDocument.h"
#include "resqml2_0_1/StratigraphicUnitFeature.h"
#include "resqml2_0_1/StratigraphicUnitInterpretation.h"
#include <stdexcept>

using namespace std;
using namespace resqml2_0_1test;
using namespace COMMON_NS;
using namespace RESQML2_0_1_NS;

const char* StratigraphicUnitInterpretationTest::defaultUuid = "65abde7d-d6ab-42b5-89c8-cc6ccec56dcc";
const char* StratigraphicUnitInterpretationTest::defaultTitle = "Strati Unit Interp";

StratigraphicUnitInterpretationTest::StratigraphicUnitInterpretationTest(const string & epcDocPath)
	: AbstractFeatureInterpretationTest(epcDocPath, defaultUuid, defaultTitle, StratigraphicUnitTest::defaultUuid, StratigraphicUnitTest::defaultTitle) {
}

StratigraphicUnitInterpretationTest::StratigraphicUnitInterpretationTest(const string & epcDocPath, const std::string & uuid, const std::string & title, const string & uuidFeature, const string & titleFeature)
	: AbstractFeatureInterpretationTest(epcDocPath, uuid, title, uuidFeature, titleFeature) {
}

StratigraphicUnitInterpretationTest::StratigraphicUnitInterpretationTest(EpcDocument* epcDoc, bool init)
	: AbstractFeatureInterpretationTest(epcDoc, defaultUuid, defaultTitle, StratigraphicUnitTest::defaultUuid, StratigraphicUnitTest::defaultTitle) {
	if (init)
			initEpcDoc();
		else
			readEpcDoc();
}

StratigraphicUnitInterpretationTest::StratigraphicUnitInterpretationTest(COMMON_NS::EpcDocument* epcDoc, const std::string & uuid, const std::string & title, const string & uuidFeature, const string & titleFeature, bool init)
	: AbstractFeatureInterpretationTest(epcDocPath, uuid, title, uuidFeature, titleFeature) {
}

void StratigraphicUnitInterpretationTest::initEpcDocHandler() {
	// creating dependencies
	StratigraphicUnitTest* stratiUnitTest = new StratigraphicUnitTest(epcDoc, true);

	StratigraphicUnitFeature* stratiUnit = static_cast<StratigraphicUnitFeature*>(this->epcDoc->getDataObjectByUuid(StratigraphicUnitTest::defaultTitle));

	// cleaning
	delete stratiUnitTest;

	StratigraphicUnitInterpretation* stratiUnitInterp = epcDoc->createStratigraphicUnitInterpretation(stratiUnit, uuid, title);
	REQUIRE(stratiUnitInterp != nullptr);
}

void StratigraphicUnitInterpretationTest::readEpcDocHandler() {
}

