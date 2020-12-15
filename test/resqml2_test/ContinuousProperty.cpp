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
#include "resqml2_test/ContinuousProperty.h"

#include "catch.hpp"

#include "resqml2/ContinuousProperty.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "eml2/AbstractHdfProxy.h"

using namespace std;
using namespace COMMON_NS;
using namespace EML2_NS;
using namespace resqml2_test;

const char* ContinuousProperty::defaultUuid = "13f40533-96fc-4f4a-940e-cac96228782a";
const char* ContinuousProperty::defaultTitle = "Testing continuous property";

ContinuousProperty::ContinuousProperty(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void ContinuousProperty::initRepo() {
	// creating an IJK grid
	RESQML2_NS::AbstractIjkGridRepresentation * rep = repo->createPartialIjkGridRepresentation("", "");

	// creating Float prop without min max
	auto propertyKind = repo->createPropertyKind("", "Fake prop kind", gsoap_eml2_1::eml21__QuantityClassKind__pressure);
	RESQML2_NS::ContinuousProperty* noMinMaxFltProperty = repo->createContinuousProperty(
		rep, defaultUuid, "Float prop without min max",
		1,
		gsoap_eml2_3::resqml22__IndexableElement__cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom__Pa,
		propertyKind);
	float fltValues[24] = { -1, 0, 1, 2, 3, 4, -1, 0, 1, 2, 3, 4,
		-1, 0, 1, 2, 3, 4, -1, 0, 1, 2, 3, 5 };
	noMinMaxFltProperty->pushBackFloatHdf5Array3dOfValues(fltValues, 2, 3, 4);

	// creating Float prop without min max
	RESQML2_NS::ContinuousProperty* noMinMaxDblProperty = repo->createContinuousProperty(
		rep, "f2c1c3de-0986-485a-9d09-d0edeadf0d1e", "Double prop without min max",
		1,
		gsoap_eml2_3::resqml22__IndexableElement__cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom__Pa,
		propertyKind);
	double dblValues[24] = { -1, 0, 1, 2, 3, 4, -1, 0, 1, 2, 3, 4,
		-1, 0, 1, 2, 3, 4, -1, 0, 1, 2, 3, 5 };
	noMinMaxDblProperty->pushBackDoubleHdf5Array3dOfValues(dblValues, 2, 3, 4);

	// creating Float prop with min max computation
	RESQML2_NS::ContinuousProperty* computedMinMaxFltProperty = repo->createContinuousProperty(
		rep, "3d31a87a-2715-4d23-b455-ff9980a08819", "Float prop with min max computation",
		1,
		gsoap_eml2_3::resqml22__IndexableElement__cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom__Pa,
		propertyKind);
	computedMinMaxFltProperty->pushBackFloatHdf5Array3dOfValues(fltValues, 2, 3, 4, std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN());

	// creating Float prop with min max computation
	RESQML2_NS::ContinuousProperty* computedMinMaxDblProperty = repo->createContinuousProperty(
		rep, "1398c2f8-3d95-4d29-87a8-8bb5fc334db0", "Double prop with min max computation",
		1,
		gsoap_eml2_3::resqml22__IndexableElement__cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom__Pa,
		propertyKind);
	computedMinMaxDblProperty->pushBackDoubleHdf5Array3dOfValues(dblValues, 2, 3, 4, std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN());

	// creating Float prop with min max forcing
	RESQML2_NS::ContinuousProperty* forcingMinMaxFltProperty = repo->createContinuousProperty(
		rep, "f46f8407-1bfb-43b8-b822-863ba656cfe7", "Float prop with min max forcing",
		1,
		gsoap_eml2_3::resqml22__IndexableElement__cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom__Pa,
		propertyKind);
	forcingMinMaxFltProperty->pushBackFloatHdf5Array3dOfValues(fltValues, 2, 3, 4, -5.5, 2.0);

	// creating Float prop with min max forcing
	RESQML2_NS::ContinuousProperty* forcingMinMaxDblProperty = repo->createContinuousProperty(
		rep, "ad589326-dfc7-4af2-a6ed-08c81657b72b", "Double prop with min max forcing",
		1,
		gsoap_eml2_3::resqml22__IndexableElement__cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom__Pa,
		propertyKind);
	forcingMinMaxDblProperty->pushBackDoubleHdf5Array3dOfValues(dblValues, 2, 3, 4, -5.5, 2.0);
}

void ContinuousProperty::readRepo() {
	RESQML2_NS::ContinuousProperty* noMinMaxFltProperty = repo->getDataObjectByUuid<RESQML2_NS::ContinuousProperty>(defaultUuid);
	REQUIRE(noMinMaxFltProperty->getElementCountPerValue() == 1);
	REQUIRE(noMinMaxFltProperty->getAttachmentKind() == gsoap_eml2_3::resqml22__IndexableElement__cells);
	REQUIRE(noMinMaxFltProperty->getUom() == gsoap_resqml2_0_1::resqml20__ResqmlUom__Pa);
	REQUIRE(noMinMaxFltProperty->getValuesCountOfPatch(0) == 24);
	float fltValues[24];
	noMinMaxFltProperty->getFloatValuesOfPatch(0, fltValues);
	REQUIRE(fltValues[0] == -1);
	REQUIRE(fltValues[1] == 0);
	REQUIRE(fltValues[2] == 1);
	REQUIRE(fltValues[3] == 2);
	REQUIRE(fltValues[4] == 3);
	REQUIRE(fltValues[5] == 4);
	REQUIRE(fltValues[6] == -1);
	REQUIRE(fltValues[7] == 0);
	REQUIRE(fltValues[8] == 1);
	REQUIRE(fltValues[9] == 2);
	REQUIRE(fltValues[10] == 3);
	REQUIRE(fltValues[11] == 4);
	REQUIRE(fltValues[12] == -1);
	REQUIRE(fltValues[13] == 0);
	REQUIRE(fltValues[14] == 1);
	REQUIRE(fltValues[15] == 2);
	REQUIRE(fltValues[16] == 3);
	REQUIRE(fltValues[17] == 4);
	REQUIRE(fltValues[18] == -1);
	REQUIRE(fltValues[19] == 0);
	REQUIRE(fltValues[20] == 1);
	REQUIRE(fltValues[21] == 2);
	REQUIRE(fltValues[22] == 3);
	REQUIRE(fltValues[23] == 5);
	REQUIRE(std::isnan(noMinMaxFltProperty->getMinimumValue()));
	REQUIRE(std::isnan(noMinMaxFltProperty->getMaximumValue()));

	RESQML2_NS::ContinuousProperty* noMinMaxDblProperty = repo->getDataObjectByUuid<RESQML2_NS::ContinuousProperty>("f2c1c3de-0986-485a-9d09-d0edeadf0d1e");
	REQUIRE(noMinMaxDblProperty->getValuesCountOfPatch(0) == 24);
	double dblValues[24];
	noMinMaxDblProperty->getDoubleValuesOfPatch(0, dblValues);
	REQUIRE(dblValues[0] == -1);
	REQUIRE(dblValues[1] == 0);
	REQUIRE(dblValues[2] == 1);
	REQUIRE(dblValues[3] == 2);
	REQUIRE(dblValues[4] == 3);
	REQUIRE(dblValues[5] == 4);
	REQUIRE(dblValues[6] == -1);
	REQUIRE(dblValues[7] == 0);
	REQUIRE(dblValues[8] == 1);
	REQUIRE(dblValues[9] == 2);
	REQUIRE(dblValues[10] == 3);
	REQUIRE(dblValues[11] == 4);
	REQUIRE(dblValues[12] == -1);
	REQUIRE(dblValues[13] == 0);
	REQUIRE(dblValues[14] == 1);
	REQUIRE(dblValues[15] == 2);
	REQUIRE(dblValues[16] == 3);
	REQUIRE(dblValues[17] == 4);
	REQUIRE(dblValues[18] == -1);
	REQUIRE(dblValues[19] == 0);
	REQUIRE(dblValues[20] == 1);
	REQUIRE(dblValues[21] == 2);
	REQUIRE(dblValues[22] == 3);
	REQUIRE(dblValues[23] == 5);
	REQUIRE(std::isnan(noMinMaxDblProperty->getMinimumValue()));
	REQUIRE(std::isnan(noMinMaxDblProperty->getMaximumValue()));

	RESQML2_NS::ContinuousProperty* computedMinMaxFltProperty = repo->getDataObjectByUuid<RESQML2_NS::ContinuousProperty>("3d31a87a-2715-4d23-b455-ff9980a08819");
	REQUIRE(computedMinMaxFltProperty->getMinimumValue() == -1);
	REQUIRE(computedMinMaxFltProperty->getMaximumValue() == 5);

	RESQML2_NS::ContinuousProperty* computedMinMaxDblProperty = repo->getDataObjectByUuid<RESQML2_NS::ContinuousProperty>("1398c2f8-3d95-4d29-87a8-8bb5fc334db0");
	REQUIRE(computedMinMaxDblProperty->getMinimumValue() == -1);
	REQUIRE(computedMinMaxDblProperty->getMaximumValue() == 5);

	RESQML2_NS::ContinuousProperty* forcingMinMaxFltProperty = repo->getDataObjectByUuid<RESQML2_NS::ContinuousProperty>("f46f8407-1bfb-43b8-b822-863ba656cfe7");
	REQUIRE(forcingMinMaxFltProperty->getMinimumValue() == -5.5);
	REQUIRE(forcingMinMaxFltProperty->getMaximumValue() == 2.0);

	RESQML2_NS::ContinuousProperty* forcingMinMaxDblProperty = repo->getDataObjectByUuid<RESQML2_NS::ContinuousProperty>("ad589326-dfc7-4af2-a6ed-08c81657b72b");
	REQUIRE(forcingMinMaxDblProperty->getMinimumValue() == -5.5);
	REQUIRE(forcingMinMaxDblProperty->getMaximumValue() == 2.0);

}
