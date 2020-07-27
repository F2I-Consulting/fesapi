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
#include "resqml2_test/StratigraphicColumnTest.h"

#include <stdexcept>

#include "catch.hpp"

#include "common/EpcDocument.h"
#include "resqml2/StratigraphicColumn.h"

using namespace std;
using namespace resqml2_test;
using namespace COMMON_NS;
using namespace RESQML2_NS;

const char* StratigraphicColumnTest::defaultUuid = "b407ddc5-67a7-437a-aa24-baf096a76857";
const char* StratigraphicColumnTest::defaultTitle = "Strati Column";

StratigraphicColumnTest::StratigraphicColumnTest(const string & epcDocPath)
	: commontest::AbstractObjectTest(epcDocPath) {
}

StratigraphicColumnTest::StratigraphicColumnTest(DataObjectRepository* repo, bool init)
	: commontest::AbstractObjectTest(repo) {
	if (init)
		initRepo();
	else
		readRepo();
}

void StratigraphicColumnTest::initRepoHandler() {
	StratigraphicColumn* stratiColumn = repo->createStratigraphicColumn(defaultUuid, defaultTitle);
	REQUIRE(stratiColumn != nullptr);
}

void StratigraphicColumnTest::readRepoHandler() {
}
