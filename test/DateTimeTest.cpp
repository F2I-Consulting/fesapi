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
#include "DateTimeTest.h"

#include "catch.hpp"

#include "common/DataObjectRepository.h"

#include "eml2/AbstractLocal3dCrs.h"

#include "resqml2/BoundaryFeature.h"

using namespace std;
using namespace COMMON_NS;
using namespace commontest;

DateTimeTest::DateTimeTest(const string & epcDocPath)
	: AbstractTest(epcDocPath) {
}

void DateTimeTest::initRepo()
{
	AbstractObject* fault = repo->createFault("606df008-78dc-4949-993d-c70d8c7e766d", "testingFault");
	fault->setCreation(36003); // ten hours and 3 seconds after 1970-01-01T00:00:00Z
	REQUIRE_THROWS(fault->setLastUpdate(3602));

	std::tm tmDate;
	tmDate.tm_year = 70;
	tmDate.tm_mon = 0;
	tmDate.tm_mday = 1;
	tmDate.tm_hour = 10;
	tmDate.tm_min = 1;
	tmDate.tm_sec = 33;
	tmDate.tm_isdst = -1; // Information not available
	fault->setLastUpdate(tmDate);
}

void DateTimeTest::readRepo()
{
	auto* localCrs = repo->getDefaultCrs();
	time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	REQUIRE(localCrs->getCreation() > now - 5);
	REQUIRE(localCrs->getCreation() < now + 5);

	REQUIRE(localCrs->getLastUpdate() < 0);
	REQUIRE(localCrs->getLastUpdateAsTimeStructure().tm_year == 0);

	auto const* fault = repo->getDataObjectByUuid("606df008-78dc-4949-993d-c70d8c7e766d");
	REQUIRE(fault->getCreation() == 36003);
	std::tm tmDate = fault->getCreationAsTimeStructure();
	REQUIRE(tmDate.tm_year == 70);
	REQUIRE(tmDate.tm_mon == 0);
	REQUIRE(tmDate.tm_mday == 1);
	REQUIRE(tmDate.tm_hour == 10);
	REQUIRE(tmDate.tm_min == 0);
	REQUIRE(tmDate.tm_sec == 3);

	REQUIRE(fault->getLastUpdate() == 36093);
	tmDate = fault->getLastUpdateAsTimeStructure();
	REQUIRE(tmDate.tm_year == 70);
	REQUIRE(tmDate.tm_mon == 0);
	REQUIRE(tmDate.tm_mday == 1);
	REQUIRE(tmDate.tm_hour == 10);
	REQUIRE(tmDate.tm_min == 1);
	REQUIRE(tmDate.tm_sec == 33);
}
