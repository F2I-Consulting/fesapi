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
#include "../config.h"
#include "common/EpcDocument.h"
#include "../catch.hpp"

using namespace resqml2_0_1test;
using namespace COMMON_NS;
using namespace std;

const char* LocalDepth3dCrsTest::defaultUuid = "a8effb2c-c94f-4d88-ae76-581ff14a4b96";
const char* LocalDepth3dCrsTest::defaultTitle = "Local Depth 3d Crs Test";

LocalDepth3dCrsTest::LocalDepth3dCrsTest(const string & epcDocPath)
	: AbstractLocal3dCrsTest(epcDocPath, defaultUuid, defaultTitle)
{
}

LocalDepth3dCrsTest::LocalDepth3dCrsTest(EpcDocument* epcDoc, bool init)
	: AbstractLocal3dCrsTest(epcDoc, defaultUuid, defaultTitle)
{
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void LocalDepth3dCrsTest::initEpcDocHandler()
{
	this->epcDoc->createLocalDepth3dCrs(uuid, title, .0, .0, .0, .0, gsoap_resqml2_0_1::eml20__LengthUom__m, 23031, gsoap_resqml2_0_1::eml20__LengthUom__m, "Unknown", false);
}

void LocalDepth3dCrsTest::readEpcDocHandler()
{
	REQUIRE( epcDoc->getLocalDepth3dCrsSet().size() == 1 );
}

