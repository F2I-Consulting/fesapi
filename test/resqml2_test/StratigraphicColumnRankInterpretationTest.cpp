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
#include "resqml2_test/StratigraphicColumnRankInterpretationTest.h"

#include <stdexcept>

#include "catch.hpp"
#include "resqml2_test/StratigraphicOrganizationTest.h"
#include "resqml2_test/StratigraphicUnitInterpretationTest.h"

#include "common/EpcDocument.h"
#include "resqml2/Model.h"
#include "resqml2/StratigraphicColumnRankInterpretation.h"
#include "resqml2/StratigraphicUnitInterpretation.h"
#include <stdexcept>

using namespace std;
using namespace resqml2_test;
using namespace COMMON_NS;
using namespace RESQML2_NS;

const char* StratigraphicColumnRankInterpretationTest::defaultUuid = "51f39ab2-3b1f-4da3-8541-324632357dd7";
const char* StratigraphicColumnRankInterpretationTest::defaultTitle = "Strati Column Rank";

const char* StratigraphicColumnRankInterpretationTest::defaultOverburdenUuid = "91622a20-e2a0-4123-a8b5-6540a1ff4f8f";
const char* StratigraphicColumnRankInterpretationTest::defaultOverburdenTitle = "Overburden";
const char* StratigraphicColumnRankInterpretationTest::defaultOverburdenInterpUuid = "80ba46c8-86e7-42ef-ab30-4718958f3707";
const char* StratigraphicColumnRankInterpretationTest::defaultOverburdenInterpTitle = "Overburden Interp";

const char* StratigraphicColumnRankInterpretationTest::defaultUnderburdenUuid = "88575500-4f85-4bea-9245-530e71867945";
const char* StratigraphicColumnRankInterpretationTest::defaultUnderburdenTitle = "Underburden";
const char* StratigraphicColumnRankInterpretationTest::defaultUnderburdenInterpUuid = "1914478a-e50b-4808-ad62-11201992024d";
const char* StratigraphicColumnRankInterpretationTest::defaultUnderburdenInterpTitle = "Underburden Interp";

StratigraphicColumnRankInterpretationTest::StratigraphicColumnRankInterpretationTest(const string & repoPath)
	: commontest::AbstractObjectTest(repoPath) {
}

StratigraphicColumnRankInterpretationTest::StratigraphicColumnRankInterpretationTest(DataObjectRepository* repo, bool init)
	: commontest::AbstractObjectTest(repo) {
	if (init)
		initRepo();
	else
		readRepo();
}

void StratigraphicColumnRankInterpretationTest::initRepoHandler() {
	// creating dependencies
	StratigraphicOrganizationTest stratiOrgtTest(repo, true);
	StratigraphicUnitInterpretationTest overburdenInterpTest(repo, true);
	StratigraphicUnitInterpretationTest stratiLayerInterpTest(repo, true);
	StratigraphicUnitInterpretationTest underburdenInterpTest(repo, true);

	Model* stratiOrg = repo->getDataObjectByUuid<Model>(StratigraphicOrganizationTest::defaultUuid);
	StratigraphicUnitInterpretation* overburdenInterp = repo->getDataObjectByUuid<StratigraphicUnitInterpretation>(defaultOverburdenInterpUuid);
	StratigraphicUnitInterpretation* stratiLayerInterp = repo->getDataObjectByUuid<StratigraphicUnitInterpretation>(StratigraphicUnitInterpretationTest::defaultUuid);
	StratigraphicUnitInterpretation* underburdenInterp = repo->getDataObjectByUuid<StratigraphicUnitInterpretation>(defaultUnderburdenInterpUuid);

	StratigraphicColumnRankInterpretation* stratiColumnRank = repo->createStratigraphicColumnRankInterpretationInApparentDepth(stratiOrg, defaultUuid, defaultTitle, 0);
	REQUIRE(stratiColumnRank != nullptr);
	stratiColumnRank->pushBackStratiUnitInterpretation(overburdenInterp);
	stratiColumnRank->pushBackStratiUnitInterpretation(stratiLayerInterp);
	stratiColumnRank->pushBackStratiUnitInterpretation(underburdenInterp);
}

void StratigraphicColumnRankInterpretationTest::readRepoHandler()
{
	StratigraphicColumnRankInterpretation* stratiColumnRank = repo->getDataObjectByUuid<StratigraphicColumnRankInterpretation>(defaultUuid);
	REQUIRE(stratiColumnRank != nullptr);
	REQUIRE(stratiColumnRank->getStratigraphicUnitInterpretationSet().size() == 3);
}
