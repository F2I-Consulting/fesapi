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
#include "resqml2_0_1test/PropertyBySlab.h"

#include <array>

#include "catch.hpp"

#include "resqml2_0_1/PropertyKind.h"
#include "resqml2_0_1/ContinuousProperty.h"
#include "resqml2_0_1/DiscreteProperty.h"
#include "resqml2_0_1/AbstractIjkGridRepresentation.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace COMMON_NS;
using namespace RESQML2_NS;
using namespace resqml2_0_1test;

const char* PropertyBySlab::defaultContinuousPropComputeUuid = "9d0a717f-2cd3-4d43-9cbf-3484105ed384";
const char* PropertyBySlab::defaultDiscretePropComputeUuid = "50935c31-93ec-4084-8891-6e9f130c49c3";
const char* PropertyBySlab::defaultPropNoComputeUuid = "459ab2a0-5f76-4c1e-ba70-7b7da67c82cf";
const char* PropertyBySlab::defaultDiscretePropNoComputeUuid = "f66f0142-d4a1-48f6-9762-39ac00a4fcab";

PropertyBySlab::PropertyBySlab(const string & repoPath)
	: commontest::AbstractObjectTest(repoPath) {
}

PropertyBySlab::PropertyBySlab(DataObjectRepository * repo, bool init)
	: commontest::AbstractObjectTest(repo) {
	if (init)
		initRepo();
	else
		readRepo();
}

void PropertyBySlab::initRepoHandler() {
	RESQML2_0_1_NS::AbstractIjkGridRepresentation* ijkGrid = repo->createPartialIjkGridRepresentation("", "partial IJK Grid");
	RESQML2_0_1_NS::PropertyKind * propertyKind = repo->createPartial<RESQML2_0_1_NS::PropertyKind>("", "Partial prop kind");

	// getting the hdf proxy
	AbstractHdfProxy* hdfProxy = repo->getHdfProxySet()[0];

	// creating the continuous Property with computing min max
	RESQML2_0_1_NS::ContinuousProperty* propertyCompute = repo->createContinuousProperty(
		ijkGrid, defaultContinuousPropComputeUuid, "slab prop compute min max",
		1,
		gsoap_resqml2_0_1::resqml20__IndexableElements__cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom__m,
		propertyKind);
	propertyCompute->pushBackFloatHdf5Array3dOfValues(2, 3, 4);

	ULONG64 valueCountInFastestDim = 2;
	ULONG64 valueCountInMiddleDim = 3;
	ULONG64 valueCountInSlowestDim = 1;
	ULONG64 offsetInFastestDim = 0;
	ULONG64 offsetInMiddleDim = 0;
	ULONG64 offsetInSlowestDim = 0;
	std::array<float, 6> k0LayerValues = { -123.0f, .01f, .02f, .03f, .04f, .05f };
	propertyCompute->setValuesOfFloatHdf5Array3dOfValues(k0LayerValues.data(), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim,
		offsetInFastestDim, offsetInMiddleDim, offsetInSlowestDim);
	std::array<float, 6> k1LayerValues = { .10f, .11f, .12f, .13f, .14f, .15f };
	++offsetInSlowestDim;
	propertyCompute->setValuesOfFloatHdf5Array3dOfValues(k1LayerValues.data(), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim,
		offsetInFastestDim, offsetInMiddleDim, offsetInSlowestDim);
	std::array<float, 6> k2LayerValues = { .20f, .21f, .22f, std::numeric_limits<float>::quiet_NaN(), .24f, .25f };
	++offsetInSlowestDim;
	propertyCompute->setValuesOfFloatHdf5Array3dOfValues(k2LayerValues.data(), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim,
		offsetInFastestDim, offsetInMiddleDim, offsetInSlowestDim);
	std::array<float, 6> k3LayerValues = { .30f, .31f, .32f, .33f, .34f, .35f};
	++offsetInSlowestDim;
	propertyCompute->setValuesOfFloatHdf5Array3dOfValues(k3LayerValues.data(), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim,
		offsetInFastestDim, offsetInMiddleDim, offsetInSlowestDim);

	// creating the continuous Property without computing min max
	RESQML2_0_1_NS::ContinuousProperty* propertyNoCompute = repo->createContinuousProperty(
		ijkGrid, defaultPropNoComputeUuid, "slab prop no compute min max",
		1,
		gsoap_resqml2_0_1::resqml20__IndexableElements__cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom__m,
		propertyKind);
	propertyNoCompute->pushBackFloatHdf5Array3dOfValues(2, 3, 4, nullptr, -500.0f, 0.1f);

	offsetInSlowestDim = 0;
	propertyNoCompute->setValuesOfFloatHdf5Array3dOfValues(k0LayerValues.data(), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim,
		offsetInFastestDim, offsetInMiddleDim, offsetInSlowestDim, false);
	++offsetInSlowestDim;
	propertyNoCompute->setValuesOfFloatHdf5Array3dOfValues(k1LayerValues.data(), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim,
		offsetInFastestDim, offsetInMiddleDim, offsetInSlowestDim, false);
	++offsetInSlowestDim;
	propertyNoCompute->setValuesOfFloatHdf5Array3dOfValues(k2LayerValues.data(), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim,
		offsetInFastestDim, offsetInMiddleDim, offsetInSlowestDim, false);
	++offsetInSlowestDim;
	propertyNoCompute->setValuesOfFloatHdf5Array3dOfValues(k3LayerValues.data(), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim,
		offsetInFastestDim, offsetInMiddleDim, offsetInSlowestDim, false);

	REQUIRE(propertyNoCompute->getMinimumValue() == -500.0f);
	REQUIRE(propertyNoCompute->getMaximumValue() == .1f);

	propertyNoCompute->pushBackFloatHdf5Array3dOfValues(2, 3, 4, nullptr, -300.0f, 100.0f);
	REQUIRE(propertyNoCompute->getMinimumValue() == -500.0f);
	REQUIRE(propertyNoCompute->getMaximumValue() == 100.0f);

	// Creating the Discrete property using slab
	RESQML2_0_1_NS::DiscreteProperty* discretePropertyCompute = repo->createDiscreteProperty(
		ijkGrid, defaultDiscretePropComputeUuid, "testing discrete prop",
		1,
		gsoap_resqml2_0_1::resqml20__IndexableElements__cells,
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind__index);
	discretePropertyCompute->pushBackLongHdf5Array3dOfValues(2, 3, 4, 9999);
	REQUIRE_THROWS(discretePropertyCompute->getMinimumValue() == -10);
	REQUIRE_THROWS(discretePropertyCompute->getMaximumValue() == 35);

	offsetInSlowestDim = 0;
	std::array<LONG64, 6> kLayerlongValues = { -10, 1, 2, 3, 4, 5 };
	discretePropertyCompute->setValuesOfLongHdf5Array3dOfValues(kLayerlongValues.data(), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim,
		offsetInFastestDim, offsetInMiddleDim, offsetInSlowestDim, true);
	kLayerlongValues[0] = 10;
	kLayerlongValues[1] = 11;
	kLayerlongValues[2] = 12;
	kLayerlongValues[3] = 13;
	kLayerlongValues[4] = 14;
	kLayerlongValues[5] = 15;
	++offsetInSlowestDim;
	discretePropertyCompute->setValuesOfLongHdf5Array3dOfValues(kLayerlongValues.data(), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim,
		offsetInFastestDim, offsetInMiddleDim, offsetInSlowestDim, true);
	kLayerlongValues[0] = 20;
	kLayerlongValues[1] = 21;
	kLayerlongValues[2] = 22;
	kLayerlongValues[3] = 9999;
	kLayerlongValues[4] = 24;
	kLayerlongValues[5] = 25;
	++offsetInSlowestDim;
	discretePropertyCompute->setValuesOfLongHdf5Array3dOfValues(kLayerlongValues.data(), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim,
		offsetInFastestDim, offsetInMiddleDim, offsetInSlowestDim, true);
	kLayerlongValues[0] = 30;
	kLayerlongValues[1] = 31;
	kLayerlongValues[2] = 32;
	kLayerlongValues[3] = 33;
	kLayerlongValues[4] = 34;
	kLayerlongValues[5] = 35;
	++offsetInSlowestDim;
	discretePropertyCompute->setValuesOfLongHdf5Array3dOfValues(kLayerlongValues.data(), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim,
		offsetInFastestDim, offsetInMiddleDim, offsetInSlowestDim, true);

	// creating the discrete Property without computing min max
	RESQML2_0_1_NS::DiscreteProperty* discretePropertyNoCompute = repo->createDiscreteProperty(
		ijkGrid, defaultDiscretePropNoComputeUuid, "testing discrete prop no min max",
		1,
		gsoap_resqml2_0_1::resqml20__IndexableElements__cells,
		propertyKind);
	discretePropertyNoCompute->pushBackLongHdf5Array3dOfValues(2, 3, 4, 9999);
	offsetInSlowestDim = 0;
	discretePropertyNoCompute->setValuesOfLongHdf5Array3dOfValues(kLayerlongValues.data(), valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim,
		offsetInFastestDim, offsetInMiddleDim, offsetInSlowestDim, false);
	REQUIRE_THROWS(discretePropertyNoCompute->getMinimumValue() == -10);
	REQUIRE_THROWS(discretePropertyNoCompute->getMaximumValue() == 35);


	discretePropertyNoCompute->pushBackLongHdf5Array3dOfValues(2, 3, 4, -25, 102, 9999);
	REQUIRE(discretePropertyNoCompute->getMinimumValue() == -25);
	REQUIRE(discretePropertyNoCompute->getMaximumValue() == 102);
}

void PropertyBySlab::readRepoHandler()
{
	RESQML2_0_1_NS::ContinuousProperty* propertyCompute = repo->getDataObjectByUuid<RESQML2_0_1_NS::ContinuousProperty>(defaultContinuousPropComputeUuid);
	REQUIRE(propertyCompute->getValuesHdfDatatype() == AbstractValuesProperty::FLOAT);
	REQUIRE(propertyCompute->getMinimumValue() == -123.0);
	REQUIRE(propertyCompute->getMaximumValue() == .35f);

	RESQML2_0_1_NS::ContinuousProperty* propertyNoCompute = repo->getDataObjectByUuid<RESQML2_0_1_NS::ContinuousProperty>(defaultPropNoComputeUuid);
	REQUIRE(propertyNoCompute->getMinimumValue() == -500.0f);
	REQUIRE(propertyNoCompute->getMaximumValue() == 100.0f);

	RESQML2_0_1_NS::DiscreteProperty* discretePropertyCompute = repo->getDataObjectByUuid<RESQML2_0_1_NS::DiscreteProperty>(defaultDiscretePropComputeUuid);
	REQUIRE(discretePropertyCompute->getMinimumValue() == -10);
	REQUIRE(discretePropertyCompute->getMaximumValue() == 35);
}
