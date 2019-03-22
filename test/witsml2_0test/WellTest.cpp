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
#include "WellTest.h"
#include "../catch.hpp"
#include "common/EpcDocument.h"
#include "witsml2_0/Well.h"
#include <stdexcept>
#include "../config.h"

using namespace std;
using namespace witsml2_0test;
using namespace COMMON_NS;
using namespace WITSML2_0_NS;

WellTest::WellTest(const string & epcDocPath)
	: AbstractObjectTest(epcDocPath, uuidWell, titleWell) {
}

WellTest::WellTest(EpcDocument* epcDoc, bool init)
	: AbstractObjectTest(epcDoc, uuidWell, titleWell) {
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void WellTest::initEpcDocHandler() {
	Well* well = this->epcDoc->createWell(this->uuid, this->title);
	REQUIRE(well != nullptr);
}

void WellTest::readEpcDocHandler() {
}

