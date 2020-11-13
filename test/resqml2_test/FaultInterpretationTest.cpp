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
#include "FaultInterpretationTest.h"
#include "resqml2/BoundaryFeature.h"
#include "resqml2/FaultInterpretation.h"
#include "../catch.hpp"
#include "AbstractTest.h"

using namespace std;
using namespace resqml2_test;
using namespace COMMON_NS;
using namespace RESQML2_NS;

const char* FaultInterpretationTest::faultUuid = "a2e84855-738e-462a-82c5-863abd058be1";
const char* FaultInterpretationTest::faultTitle = "Fault";
const char* FaultInterpretationTest::defaultUuid = "91f90343-2581-48c5-893f-667a2995088c";
const char* FaultInterpretationTest::defaultTitle = "FaultInterpretationTest";

FaultInterpretationTest::FaultInterpretationTest(const string & repoPath)
	: commontest::AbstractTest(repoPath)
{
}

void FaultInterpretationTest::initRepo()
{
	// creating dependencies
	BoundaryFeature* fault = repo->createFault(faultUuid, faultTitle);

	FaultInterpretation* faultInterp = repo->createFaultInterpretation(fault, defaultUuid, defaultTitle);
	REQUIRE(faultInterp != nullptr);
}

void FaultInterpretationTest::readRepo()
{
	// getting the fault interpretation
	FaultInterpretation* faultInterp = repo->getDataObjectByUuid<FaultInterpretation>(defaultUuid);
	REQUIRE(faultInterp != nullptr);
}
