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
#include "ContinuousPropertyOnWellFrameTest.h"

#include "catch.hpp"
#include "resqml2_0_1test/WellboreFrameRepresentationTest.h"

#include "resqml2/ContinuousProperty.h"
#include "resqml2/WellboreFrameRepresentation.h"
#include "eml2/AbstractHdfProxy.h"

using namespace std;
using namespace COMMON_NS;
using namespace RESQML2_NS;
using namespace resqml2_0_1test;

const char* ContinuousPropertyOnWellFrameTest::defaultUuid = "6e4ca2c9-6780-44bd-b4c2-6bb3ef4682d4";
const char* ContinuousPropertyOnWellFrameTest::defaultTitle = "Continuous Property on well frame Test";
const char* ContinuousPropertyOnWellFrameTest::exoticUuid = "8535b08f-739f-470c-b940-36c1bd5209a4";
const char* ContinuousPropertyOnWellFrameTest::exoticTitle = "Continuous Property exotic uom on well frame Test";

ContinuousPropertyOnWellFrameTest::ContinuousPropertyOnWellFrameTest(const string & repoPath)
	: commontest::AbstractObjectTest(repoPath) {
}

ContinuousPropertyOnWellFrameTest::ContinuousPropertyOnWellFrameTest(DataObjectRepository * repo, bool init)
	: commontest::AbstractObjectTest(repo) {
	if (init)
		initRepo();
	else
		readRepo();
}

void ContinuousPropertyOnWellFrameTest::initRepoHandler() {
	// creating a wellbore frame
	WellboreFrameRepresentationTest * frameTest = new WellboreFrameRepresentationTest(repo, true);
	RESQML2_NS::WellboreFrameRepresentation * frame = static_cast<RESQML2_NS::WellboreFrameRepresentation *>(repo->getDataObjectByUuid(WellboreFrameRepresentationTest::defaultUuid));

	// getting the hdf proxy
	EML2_NS::AbstractHdfProxy* hdfProxy = repo->getHdfProxySet()[0];

	// creating the ContinuousProperty
	auto propertyKind = repo->createPropertyKind("4a305182-221e-4205-9e7c-a36b06fa5b3d", "length", gsoap_eml2_1::eml21__QuantityClassKind__length);
	RESQML2_NS::ContinuousProperty* continuousProperty = repo->createContinuousProperty(
		frame, defaultUuid, defaultTitle,
		1,
		gsoap_eml2_3::resqml22__IndexableElement__nodes,
		gsoap_resqml2_0_1::resqml20__ResqmlUom__m,
		propertyKind);
	REQUIRE(continuousProperty != nullptr);
	double values[5] = { 0.1, 1.2, 2.3, 3.4, 4.5 };
	continuousProperty->pushBackDoubleHdf5Array1dOfValues(values, 5, hdfProxy);
	
	// creating the exotic ContinuousProperty
	RESQML2_NS::ContinuousProperty* exoticContinuousProperty = repo->createContinuousProperty(
		frame, exoticUuid, exoticTitle,
		1,
		gsoap_eml2_3::resqml22__IndexableElement__nodes,
		"My exotic Uom",
		propertyKind);
	REQUIRE(exoticContinuousProperty != nullptr);
	exoticContinuousProperty->pushBackDoubleHdf5Array1dOfValues(values, 5, hdfProxy);

	// cleaning
	delete frameTest;
}

void ContinuousPropertyOnWellFrameTest::readRepoHandler() {
	// reading dependencies
	WellboreFrameRepresentationTest * frameTest = new WellboreFrameRepresentationTest(repo, false);

	// getting the ContinuousPropertySeries
	RESQML2_NS::ContinuousProperty* continuousProperty = repo->getDataObjectByUuid<RESQML2_NS::ContinuousProperty>(defaultUuid);
	RESQML2_NS::ContinuousProperty* exoticContinuousProperty = repo->getDataObjectByUuid<RESQML2_NS::ContinuousProperty>(exoticUuid);

	// ************************************
	// reading the ContinuousProperty

	// getElementCountPerValue
	REQUIRE(continuousProperty->getElementCountPerValue() == 1);

	// getAttachmentKind
	REQUIRE(continuousProperty->getAttachmentKind() == gsoap_eml2_3::resqml22__IndexableElement__nodes);

	// getUom
	REQUIRE(continuousProperty->getUom() == gsoap_resqml2_0_1::resqml20__ResqmlUom__m);
	REQUIRE(exoticContinuousProperty->getUom() == gsoap_resqml2_0_1::resqml20__ResqmlUom__Euc);
	REQUIRE(exoticContinuousProperty->getUomAsString() == "My exotic Uom");

	// getEnergisticsPropertyKind
	//REQUIRE(continuousProperty->isAssociatedToOneStandardEnergisticsPropertyKind());
	REQUIRE(continuousProperty->getPropertyKindAsString() == "length");

	// getValuesCountOfPatch
	REQUIRE(continuousProperty->getValuesCountOfPatch(0) == 5);

	double values[5];
	continuousProperty->getDoubleValuesOfPatch(0, values);
	REQUIRE(values[0] == 0.1);
	REQUIRE(values[1] == 1.2);
	REQUIRE(values[2] == 2.3);
	REQUIRE(values[3] == 3.4);
	REQUIRE(values[4] == 4.5);

	// cleaning
	delete frameTest;
}

