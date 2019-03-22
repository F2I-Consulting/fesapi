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
#include "resqml2_0_1test/WellboreInterpretationTest.h"

#include "catch.hpp"
#include "resqml2_0_1test/WellboreTest.h"

#include "resqml2_0_1/WellboreFeature.h"
#include "resqml2_0_1/WellboreInterpretation.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace COMMON_NS;
using namespace RESQML2_0_1_NS;

const char* WellboreInterpretationTest::defaultUuid = "efc2e5d6-8a4a-4482-9561-cf3538c89ba4";
const char* WellboreInterpretationTest::defaultTitle = "Wellbore Interpretation Test";

WellboreInterpretationTest::WellboreInterpretationTest(const string & epcDocPath)
	: AbstractFeatureInterpretationTest(epcDocPath, defaultUuid, defaultTitle, WellboreTest::defaultUuid, WellboreTest::defaultTitle)
{
}

WellboreInterpretationTest::WellboreInterpretationTest(EpcDocument * epcDoc, bool init)
	: AbstractFeatureInterpretationTest(epcDoc, defaultUuid, defaultTitle, WellboreTest::defaultUuid, WellboreTest::defaultTitle)
{
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void WellboreInterpretationTest::initEpcDocHandler()
{
	// creating dependencies
	WellboreTest* wellboreTest = new WellboreTest(this->epcDoc, true);

	WellboreFeature* wellbore = static_cast<WellboreFeature*>(this->epcDoc->getDataObjectByUuid(WellboreTest::defaultUuid));

	// cleaning
	delete wellboreTest;

	WellboreInterpretation* WellboreInterp = this->epcDoc->createWellboreInterpretation(wellbore, uuid, title, true);
	REQUIRE( WellboreInterp != nullptr );
}

void WellboreInterpretationTest::readEpcDocHandler()
{
	// reading dependencies
	WellboreTest* wellboreTest = new WellboreTest(this->epcDoc, false);

	// cleaning
	delete wellboreTest;
}

