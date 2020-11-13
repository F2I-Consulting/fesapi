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
#include "ContinuousColorMapTest.h"
#include "catch.hpp"
#include "eml2/AbstractHdfProxy.h"
#include "eml2/GraphicalInformationSet.h"
#include "eml2/PropertyKind.h"
#include "resqml2/BoundaryFeature.h"
#include "resqml2/HorizonInterpretation.h"
#include "resqml2/Grid2dRepresentation.h"
#include "resqml2/Model.h"
#include "resqml2/EarthModelInterpretation.h"
#include "resqml2/LocalDepth3dCrs.h"
#include "resqml2/ContinuousProperty.h"
#include "resqml2_2/ContinuousColorMap.h"

using namespace std;
using namespace COMMON_NS;
using namespace RESQML2_NS;
using namespace EML2_NS;
using namespace resqml2_2test;
using namespace gsoap_resqml2_0_1;

char const* ContinuousColorMapTest::defaultUuid = "8187ebb5-6d6d-4182-8d0e-8bcb9a5060e9";
char const* ContinuousColorMapTest::defaultTitle = "Continuous Color Map";
char const* ContinuousColorMapTest::uuidHorizon = "e860f1ac-2aa9-4721-b2b9-7e47c186c704";
char const* ContinuousColorMapTest::titleHorizon = "Horizon";
char const* ContinuousColorMapTest::uuidHorizonInterpretation = "d8a2ae13-eef9-497b-870c-e43f92b2f336";
char const* ContinuousColorMapTest::titleHorizonInterpretation = "Horizon Interpretation";
char const* ContinuousColorMapTest::uuidGrid2dRepresentation = "9c4be7fe-96ef-457d-8835-9a22c6d2f7be";
char const* ContinuousColorMapTest::titleGrid2dRepresentation = "Grid 2d Representation";
char const* ContinuousColorMapTest::uuidContinuousProperty = "90d93fd2-6976-40bc-aaa2-43c230426218";
char const* ContinuousColorMapTest::titleContinuousProperty = "Continuous Property";
char const* ContinuousColorMapTest::uuidOrganizationFeature = "ceefeac1-21b1-4a31-b74b-ab1e64eacf80";
char const* ContinuousColorMapTest::titleOrganizationFeature = "Organization Feature";
char const* ContinuousColorMapTest::uuidEarthModelInterpretation = "8f6afd90-71e1-4a1e-891f-9c628feeb980";
char const* ContinuousColorMapTest::titleEarthModelInterpretation = "Earth Model Interpretation";
char const* ContinuousColorMapTest::uuidLocalDepth3dCrs = "69aa7e50-1538-4818-93a4-11fcfdc2292e";
char const* ContinuousColorMapTest::titleLocalDepth3dCrs = "Loacl Depth 3d Crs";
char const* ContinuousColorMapTest::uuidGraphicalInformationSet = "3b5c1be9-d2a0-4bd3-806f-883d928d1a7d";
char const* ContinuousColorMapTest::titleGraphicalInformationSet = "Graphical Information Set";

ContinuousColorMapTest::ContinuousColorMapTest(const string & repoPath)
	: AbstractTest(repoPath) {
}

void ContinuousColorMapTest::initRepo() {
	// creating a grid 2d representation
	BoundaryFeature* horizon = repo->createHorizon(uuidHorizon,titleHorizonInterpretation);
	HorizonInterpretation* horizonInterpretation = repo->createHorizonInterpretation(horizon, uuidHorizonInterpretation, titleHorizonInterpretation);
	AbstractHdfProxy* hdfProxy = this->repo->getHdfProxySet()[0];
	Grid2dRepresentation* grid2dRepresentation = repo->createGrid2dRepresentation(horizonInterpretation, uuidGrid2dRepresentation, titleGrid2dRepresentation);
	const unsigned int numPointInFastestDirection = 2;
	const unsigned int numPointsInSlowestDirection = 1;
	grid2dRepresentation->setGeometryAsArray2dOfLatticePoints3d(numPointInFastestDirection, numPointsInSlowestDirection,
		0., 0., 0.,
		1., 0., 0.,
		0., 1., 0.,
		1., 1.);

	// assotiating a Continuous property to the grid 2d representation
	auto propertyKind = repo->createPropertyKind("5f78f66a-ed1b-4827-a868-beb989febb31", "code", gsoap_eml2_1::eml21__QuantityClassKind__not_x0020a_x0020measure);
	ContinuousProperty* continuousProperty = repo->createContinuousProperty(grid2dRepresentation, uuidContinuousProperty, titleContinuousProperty, 2,
		gsoap_eml2_3::resqml22__IndexableElement__nodes, "continuousColorMapIndex", propertyKind);
	double values[2] = { 0., 1. };
	continuousProperty->pushBackDoubleHdf5Array2dOfValues(values, numPointInFastestDirection, numPointsInSlowestDirection, hdfProxy);

	// creating the continuous color map
	RESQML2_NS::ContinuousColorMap* continuousColorMap = repo->createContinuousColorMap(defaultUuid, defaultTitle, gsoap_eml2_3::resqml22__InterpolationDomain__rgb, gsoap_eml2_3::resqml22__InterpolationMethod__linear);
	REQUIRE(continuousColorMap != nullptr);
	unsigned int rgbColors[6] = { 0, 256, 0, 255, 0, 0 };
	vector<string> titles = { "green", "red" };
	double alphas[2] = { 1., 1. };
	REQUIRE_THROWS(continuousColorMap->setRgbColors(2, rgbColors, alphas, titles));
	rgbColors[1] = 255;
	continuousColorMap->setRgbColors(2, rgbColors, alphas, titles);

	// associating the Continuous color map to the Continuous property
	GraphicalInformationSet* graphicalInformationSet = repo->createGraphicalInformationSet(uuidGraphicalInformationSet, titleGraphicalInformationSet);
	graphicalInformationSet->setContinuousColorMap(continuousProperty, continuousColorMap);
	graphicalInformationSet->setColorMapMinMax(continuousProperty, 0., 1.);
	graphicalInformationSet->setValueVectorIndex(continuousProperty, 1);
}

void ContinuousColorMapTest::readRepo() {
	GraphicalInformationSet * graphicalInformationSet = repo->getDataObjects<GraphicalInformationSet>()[0];
	ContinuousProperty* continuousProperty = repo->getDataObjectByUuid<ContinuousProperty>(uuidContinuousProperty);
	REQUIRE(graphicalInformationSet->hasContinuousColorMap(continuousProperty));
	RESQML2_NS::ContinuousColorMap* continuousColorMap = graphicalInformationSet->getContinuousColorMap(continuousProperty);
	REQUIRE(continuousColorMap->getUuid() == defaultUuid);
	double r, g, b;
	continuousColorMap->getRgbColor(0, r, g, b);
	REQUIRE(r == 0.); // 255 is converted to 1. since we ask for double red value
	REQUIRE(g == 1.);
	REQUIRE(b == 0.);
	continuousColorMap->getRgbColor(1, r, g, b);
	REQUIRE(r == 1.);
	REQUIRE(g == 0.);
	REQUIRE(b == 0.); // 255 is converted to 1. since we ask for double blue value
	REQUIRE(graphicalInformationSet->getColorMapMin(continuousProperty) == 0.);
	REQUIRE(graphicalInformationSet->getColorMapMax(continuousProperty) == 1.);
	REQUIRE(graphicalInformationSet->getValueVectorIndex(continuousProperty) == 1);
}

