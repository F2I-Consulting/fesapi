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
#include "resqml2_0_1test/MultirealPropertyTest.h"

#include "catch.hpp"
#include "resqml2_0_1test/IjkGridExplicitRepresentationTest.h"

#include "common/EpcDocument.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2_0_1/ContinuousProperty.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_0_1test;

const char* MultirealPropertyTest::defaultUuidReal0 = "97d4ab35-44b5-47ef-9382-38b215326a27";
const char* MultirealPropertyTest::defaultUuidReal1 = "10b8a552-5b0c-4829-a528-004309bb705d";
const char* MultirealPropertyTest::defaultUuidReal10 = "aef9556b-b5c1-44e1-ad95-fcab6ae09353";
const char* MultirealPropertyTest::defaultUuidReal15 = "0efeafbf-17f7-4517-9457-c54dcb59524a";

MultirealPropertyTest::MultirealPropertyTest(const string & repoPath)
	: commontest::AbstractObjectTest(repoPath) {
}

MultirealPropertyTest::MultirealPropertyTest(DataObjectRepository * repo, bool init)
	: commontest::AbstractObjectTest(repo) {
	if (init)
		initRepo();
	else
		readRepo();
}

void MultirealPropertyTest::initRepoHandler() {
	// creating an IJK grid
	IjkGridExplicitRepresentationTest ijkTest(repo, true);
	RESQML2_0_1_NS::IjkGridExplicitRepresentation * ijkGrid = repo->getDataObjectByUuid<RESQML2_0_1_NS::IjkGridExplicitRepresentation>(IjkGridExplicitRepresentationTest::defaultUuid);

	// getting the hdf proxy
	AbstractHdfProxy* hdfProxy = repo->getHdfProxySet()[0];

	// creating the ContinuousProperty real 0
	RESQML2_0_1_NS::ContinuousProperty* continuousPropertyReal0 = repo->createContinuousProperty(
		ijkGrid, defaultUuidReal0, "real0",
		1,
		gsoap_resqml2_0_1::resqml20__IndexableElements__cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom__m,
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind__length);
	REQUIRE(continuousPropertyReal0 != nullptr);
	double values[2] = { 0.0, 0.0 };
	continuousPropertyReal0->pushBackDoubleHdf5Array1dOfValues(values, 2, hdfProxy);
	continuousPropertyReal0->setRealizationIndex(0);

	// creating the ContinuousProperty real 1
	RESQML2_0_1_NS::ContinuousProperty* continuousPropertyReal1 = repo->createContinuousProperty(
		ijkGrid, defaultUuidReal1, "real1",
		1,
		gsoap_resqml2_0_1::resqml20__IndexableElements__cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom__m,
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind__length);
	REQUIRE(continuousPropertyReal1 != nullptr);
	values[0] = 1.0;
	values[1] = 1.0;
	continuousPropertyReal1->pushBackDoubleHdf5Array1dOfValues(values, 2, hdfProxy);
	continuousPropertyReal1->setRealizationIndex(1);

	// creating the ContinuousProperty real 10
	RESQML2_0_1_NS::ContinuousProperty* continuousPropertyReal10 = repo->createContinuousProperty(
		ijkGrid, defaultUuidReal10, "real10",
		1,
		gsoap_resqml2_0_1::resqml20__IndexableElements__cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom__m,
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind__length);
	REQUIRE(continuousPropertyReal10 != nullptr);
	values[0] = 10;
	values[1] = 10;
	continuousPropertyReal10->pushBackDoubleHdf5Array1dOfValues(values, 2, hdfProxy);
	continuousPropertyReal10->setRealizationIndex(0);

	// creating the ContinuousProperty real 15
	RESQML2_0_1_NS::ContinuousProperty* continuousPropertyReal15 = repo->createContinuousProperty(
		ijkGrid, defaultUuidReal15, "real15",
		1,
		gsoap_resqml2_0_1::resqml20__IndexableElements__cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom__m,
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind__length);
	REQUIRE(continuousPropertyReal0 != nullptr);
	values[0] = 15;
	values[1] = 15;
	continuousPropertyReal15->pushBackDoubleHdf5Array1dOfValues(values, 2, hdfProxy);
	continuousPropertyReal15->setRealizationIndex(0);
}

void MultirealPropertyTest::readRepoHandler() {
}
