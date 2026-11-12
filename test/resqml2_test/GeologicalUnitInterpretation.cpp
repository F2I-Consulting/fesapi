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
#include "resqml2_test/GeologicalUnitInterpretation.h"

#include <stdexcept>

#include "../catch.hpp"

#include "resqml2/GeologicUnitInterpretation.h"

#include "resqml2_0_1/GeologicUnitFeature.h"

namespace {
	const std::string featureUuid = "92fb784e-b38f-42eb-b76c-730655ff79d2";
	const std::string interpUuid = "d6606159-1795-4fa9-be55-cf32e587bc8c";
}

using namespace std;
using namespace resqml2_test;
using namespace COMMON_NS;
using namespace RESQML2_NS;

GeologicalUnitInterpretation::GeologicalUnitInterpretation(const string & repoPath)
	: AbstractTest(repoPath)
{
}

void GeologicalUnitInterpretation::initRepo()
{
	RESQML2_0_1_NS::GeologicUnitFeature* geologicalUnitFeature = repo->createGeologicUnitFeature(featureUuid, "GeologicalUnitFeature");
	RESQML2_NS::GeologicUnitInterpretation* geologicalUnitInterp = repo->createGeologicUnitInterpretation(geologicalUnitFeature, interpUuid, "GeologicalUnitInterpretation");
}

void GeologicalUnitInterpretation::readRepo() {
	RESQML2_0_1_NS::GeologicUnitFeature* geologicalUnitFeature = repo->getDataObjectByUuid<RESQML2_0_1_NS::GeologicUnitFeature>(featureUuid);
	REQUIRE(geologicalUnitFeature != nullptr);
	RESQML2_NS::GeologicUnitInterpretation* geologicalUnitInterp = repo->getDataObjectByUuid<RESQML2_NS::GeologicUnitInterpretation>(interpUuid);
	REQUIRE(geologicalUnitInterp != nullptr);
	REQUIRE(geologicalUnitInterp->getInterpretedFeature() == geologicalUnitFeature);
}
