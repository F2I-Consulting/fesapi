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
#include "FaultTest.h"
#include "../catch.hpp"
#include "common/EpcDocument.h"
#include "resqml2_0_1/TectonicBoundaryFeature.h"
#include <stdexcept>
#include "../config.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace COMMON_NS;
using namespace RESQML2_0_1_NS;

FaultTest::FaultTest(const string & epcDocPath)
	: AbstractFeatureTest(epcDocPath, uuidFault, titleFault) {
}

FaultTest::FaultTest(EpcDocument* epcDoc, bool init)
	: AbstractFeatureTest(epcDoc, uuidFault, titleFault) {
		if (init)
			this->initEpcDoc();
		else
			this->readEpcDoc();
}

void FaultTest::initEpcDocHandler() {
	TectonicBoundaryFeature* fault = this->epcDoc->createFault(this->uuid, this->title);
	REQUIRE( fault != nullptr );
}

void FaultTest::readEpcDocHandler() {
}

