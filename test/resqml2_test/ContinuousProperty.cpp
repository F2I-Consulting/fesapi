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

#include "eml2/AbstractHdfProxy.h"

#include "resqml2/ContinuousProperty.h"

#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2_0_1/PropertyKind.h"

using namespace std;
using namespace COMMON_NS;
using namespace EML2_NS;
using namespace resqml2_test;

ContinuousProperty::ContinuousProperty(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void ContinuousProperty::initRepo() {
	// creating an IJK grid
	RESQML2_NS::AbstractIjkGridRepresentation * rep = repo->createPartialIjkGridRepresentation("", "");

	// creating Float prop without min max
	RESQML2_0_1_NS::PropertyKind* propertyKind = repo->createPartial<RESQML2_0_1_NS::PropertyKind>("4a305182-221e-4205-9e7c-a36b06fa5b3d", "length");
	RESQML2_NS::ContinuousProperty* noMinMaxFltProperty = repo->createContinuousProperty(
		rep, defaultUuid, "Float prop without min max",
		1,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom::Pa,
		propertyKind);
	float fltValues[24] = { 1, 0, 1, 2, 3, 4, -1, 0, 1, 2, 3, 4,
		-1, 0, 1, 2, 3, 4, -1, 0, 1, 2, 3, 5 };
	noMinMaxFltProperty->pushBackArray3dOfValues(fltValues, 2, 3, 4);

	// creating Double prop without min max
	RESQML2_NS::ContinuousProperty* noMinMaxDblProperty = repo->createContinuousProperty(
		rep, "f2c1c3de-0986-485a-9d09-d0edeadf0d1e", "Double prop without min max",
		1,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom::Pa,
		propertyKind);
	double dblValues[24] = { 1, std::numeric_limits<double>::quiet_NaN(), 1, std::numeric_limits<double>::quiet_NaN(), 3, 4, -1, 0, 1, 2, 3, 4,
		-1, 0, 1, 2, 3, 4, -1, 0, 1, 2, 3, 5 };
	noMinMaxDblProperty->pushBackArray3dOfValues(dblValues, 2, 3, 4);

	// creating Float prop with min max computation
	RESQML2_NS::ContinuousProperty* computedMinMaxFltProperty = repo->createContinuousProperty(
		rep, "3d31a87a-2715-4d23-b455-ff9980a08819", "Float prop with min max computation",
		1,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom::Pa,
		propertyKind);
	COMMON_NS::NumberArrayStatistics<float> floatStats(fltValues, 24);
	computedMinMaxFltProperty->pushBackArray3dOfValuesPlusStatistics(fltValues, 2, 3, 4, floatStats);

	// creating Float prop with min max computation
	RESQML2_NS::ContinuousProperty* computedMinMaxDblProperty = repo->createContinuousProperty(
		rep, "1398c2f8-3d95-4d29-87a8-8bb5fc334db0", "Double prop with min max computation",
		1,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom::Pa,
		propertyKind);
	COMMON_NS::NumberArrayStatistics<double> doubleStats(dblValues, 24);
	computedMinMaxDblProperty->pushBackArray3dOfValuesPlusStatistics(dblValues, 2, 3, 4, doubleStats);

	// creating Float prop with min max forcing
	RESQML2_NS::ContinuousProperty* forcingMinMaxFltProperty = repo->createContinuousProperty(
		rep, "f46f8407-1bfb-43b8-b822-863ba656cfe7", "Float prop with min max forcing",
		1,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom::Pa,
		propertyKind);
	COMMON_NS::NumberArrayStatistics<float> floatForcedStats;
	floatForcedStats.setMinimum(-5.5, 0);
	floatForcedStats.setMaximum(2.0, 0);
	forcingMinMaxFltProperty->pushBackArray3dOfValuesPlusStatistics(fltValues, 2, 3, 4, floatForcedStats);

	// creating Float prop with min max forcing
	RESQML2_NS::ContinuousProperty* forcingMinMaxDblProperty = repo->createContinuousProperty(
		rep, "ad589326-dfc7-4af2-a6ed-08c81657b72b", "Double prop with min max forcing",
		1,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom::Pa,
		propertyKind);
	COMMON_NS::NumberArrayStatistics<double> doubleForcedStats;
	doubleForcedStats.setMinimum(-5.5, 0);
	doubleForcedStats.setMaximum(2.0, 0);
	forcingMinMaxDblProperty->pushBackArray3dOfValuesPlusStatistics(dblValues, 2, 3, 4, doubleForcedStats);

	// creating Constant Floating point prop
	RESQML2_NS::ContinuousProperty* constantDblProperty = repo->createContinuousProperty(
		rep, "3ce662a6-c94b-4d19-b9df-b241693dba41", "Constant FloatingPoint Property",
		1,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom::Pa,
		propertyKind);
	constantDblProperty->pushBackFloatingPointConstantArrayOfValues(3.33, 3);
}

void ContinuousProperty::readRepo() {
	RESQML2_NS::ContinuousProperty* noMinMaxFltProperty = repo->getDataObjectByUuid<RESQML2_NS::ContinuousProperty>(defaultUuid);
	REQUIRE(noMinMaxFltProperty->getElementCountPerValue() == 1);
	REQUIRE(noMinMaxFltProperty->getAttachmentKind() == gsoap_eml2_3::eml23__IndexableElement::cells);
	REQUIRE(noMinMaxFltProperty->getUom() == gsoap_resqml2_0_1::resqml20__ResqmlUom::Pa);
	auto valuesCount = noMinMaxFltProperty->getValuesCountPerDimensionOfPatch(0);
	REQUIRE(std::equal(std::begin(valuesCount), std::end(valuesCount), std::begin({ 4, 3, 2 })));
	REQUIRE(noMinMaxFltProperty->getValuesCountOfPatch(0) == 24);
	float fltValues[24];
	const auto floatStats = noMinMaxFltProperty->getArrayOfValuesOfPatch(0, fltValues);
	REQUIRE(fltValues[0] == 1);
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
	REQUIRE(std::isnan(floatStats.getNullValue()));
	REQUIRE(floatStats.getMaximumSize() == 0);
	REQUIRE(floatStats.getMinimumSize() == 0);
	REQUIRE(floatStats.getValidValueCountSize() == 0);
	REQUIRE(floatStats.getModeSize() == 0);

	RESQML2_NS::ContinuousProperty* noMinMaxDblProperty = repo->getDataObjectByUuid<RESQML2_NS::ContinuousProperty>("f2c1c3de-0986-485a-9d09-d0edeadf0d1e");
	REQUIRE(noMinMaxDblProperty->getValuesCountOfPatch(0) == 24);
	double dblValues[24];
	const auto doubleStats = noMinMaxDblProperty->getArrayOfValuesOfPatch(0, dblValues, true);
	REQUIRE(dblValues[0] == 1);
	REQUIRE(std::isnan(dblValues[1]));
	REQUIRE(dblValues[2] == 1);
	REQUIRE(std::isnan(dblValues[3]));
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
	REQUIRE(std::isnan(doubleStats.getNullValue()));
	REQUIRE(doubleStats.getMaximumSize() == 1);
	REQUIRE(doubleStats.getMaximum() == 5);
	REQUIRE(doubleStats.getMinimumSize() == 1);
	REQUIRE(doubleStats.getMinimum(0) == -1);
	REQUIRE(doubleStats.getValidValueCountSize() == 1);
	REQUIRE(doubleStats.getValidValueCount(0) == 22);
	REQUIRE(doubleStats.getModeSize() == 1);
	REQUIRE(doubleStats.getMode(0) == 1);
	REQUIRE(doubleStats.getModePercentageSize() == 1);
	REQUIRE(doubleStats.getModePercentage(0) < 0.2273);
	REQUIRE(doubleStats.getModePercentage(0) > 0.2272);
	REQUIRE(doubleStats.getMeanSize() == 1);
	REQUIRE(doubleStats.getMean(0) > 1.68);
	REQUIRE(doubleStats.getMean(0) < 1.69);
	REQUIRE(doubleStats.getMedianSize() == 1);
	REQUIRE(doubleStats.getMedian() == 1.5);
	REQUIRE(doubleStats.getStandardDeviationSize() == 1);
	REQUIRE(doubleStats.getStandardDeviation() > 1.74);
	REQUIRE(doubleStats.getStandardDeviation() < 1.75);

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
	REQUIRE(!forcingMinMaxDblProperty->hasConstantValues(0));

	RESQML2_NS::ContinuousProperty* constantFloatingPointProperty = repo->getDataObjectByUuid<RESQML2_NS::ContinuousProperty>("3ce662a6-c94b-4d19-b9df-b241693dba41");
	valuesCount = constantFloatingPointProperty->getValuesCountPerDimensionOfPatch(0);
	REQUIRE(std::equal(std::begin(valuesCount), std::end(valuesCount), std::begin({ 3 })));
	REQUIRE(constantFloatingPointProperty->getValuesCountOfPatch(0) == 3);
	double constantFloatingPointValues[3];
	constantFloatingPointProperty->getArrayOfValuesOfPatch(0, constantFloatingPointValues);
	REQUIRE(constantFloatingPointValues[0] == 3.33);
	REQUIRE(constantFloatingPointValues[1] == 3.33);
	REQUIRE(constantFloatingPointValues[2] == 3.33);
	REQUIRE(constantFloatingPointProperty->hasConstantValues(0));
	REQUIRE_THROWS(constantFloatingPointProperty->getInt64ConstantValuesOfPatch(0));
	REQUIRE(constantFloatingPointProperty->getDoubleConstantValuesOfPatch(0) == 3.33);
}
