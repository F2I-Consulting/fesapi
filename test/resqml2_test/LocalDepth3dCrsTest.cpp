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
#include "LocalDepth3dCrsTest.h"
#include "resqml2/LocalDepth3dCrs.h"
#include "../catch.hpp"

#include "resqml2/LocalDepth3dCrs.h"

using namespace resqml2_test;
using namespace COMMON_NS;
using namespace std;
using namespace RESQML2_NS;

const char* LocalDepth3dCrsTest::defaultUuid = "a8effb2c-c94f-4d88-ae76-581ff14a4b96";
const char* LocalDepth3dCrsTest::defaultTitle = "Local Depth 3d Crs Test";

LocalDepth3dCrsTest::LocalDepth3dCrsTest(const string & repoPath)
	: commontest::AbstractTest(repoPath)
{
}

void LocalDepth3dCrsTest::initRepo()
{
	repo->createLocalDepth3dCrs(defaultUuid, defaultTitle, 1000, 2000, 3000, .0, gsoap_resqml2_0_1::eml20__LengthUom__m, 23031, gsoap_resqml2_0_1::eml20__LengthUom__ft, "Unknown", false);
}

void LocalDepth3dCrsTest::readRepo()
{
	REQUIRE( repo->getLocalDepth3dCrsSet().size() == 2 );
	LocalDepth3dCrs* crs = repo->getDataObjectByUuid<LocalDepth3dCrs>(defaultUuid);
	REQUIRE(crs->getOriginOrdinal1() == 1000);
	REQUIRE(crs->getOriginOrdinal2() == 2000);
	REQUIRE(crs->getOriginDepthOrElevation() == 3000);
	REQUIRE(crs->getProjectedCrsEpsgCode() == 23031);
	REQUIRE(crs->isVerticalCrsUnknown());
	REQUIRE(crs->getProjectedCrsUnit() == gsoap_resqml2_0_1::eml20__LengthUom__m);
	REQUIRE(crs->getVerticalCrsUnit() == gsoap_resqml2_0_1::eml20__LengthUom__ft);
	REQUIRE(crs->isDepthOriented());
}
