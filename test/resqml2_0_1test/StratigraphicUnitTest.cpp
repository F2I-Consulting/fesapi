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
#include "resqml2_0_1/StratigraphicUnitFeature.h"
#include <stdexcept>

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

const char* StratigraphicUnitTest::defaultUuid = "e9e8ce58-b53a-4425-84c7-667642027a4a";
const char* StratigraphicUnitTest::defaultTitle = "Strati Unit";

StratigraphicUnitTest::StratigraphicUnitTest(const string & epcDocPath)
	: AbstractFeatureTest(epcDocPath, defaultUuid, defaultTitle) {
}

StratigraphicUnitTest::StratigraphicUnitTest(const string & epcDocPath, const std::string & uuid, const std::string & title)
	: AbstractFeatureTest(epcDocPath, uuid, title) {
}

StratigraphicUnitTest::StratigraphicUnitTest(EpcDocument* epcDoc, bool init)
	: AbstractFeatureTest(epcDoc, defaultUuid, defaultTitle) {
	if (init)
			this->initEpcDoc();
		else
			this->readEpcDoc();
}

StratigraphicUnitTest::StratigraphicUnitTest(EpcDocument* epcDoc, const std::string & uuid, const std::string & title, bool init)
	: AbstractFeatureTest(epcDoc, uuid, title) {
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void StratigraphicUnitTest::initEpcDocHandler() {
	StratigraphicUnitFeature* stratiUnit = this->epcDoc->createStratigraphicUnit(uuid, title);
	REQUIRE(stratiUnit != nullptr);
}

void StratigraphicUnitTest::readEpcDocHandler() {
}

