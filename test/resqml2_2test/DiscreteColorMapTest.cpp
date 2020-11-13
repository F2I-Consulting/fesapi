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
#include "DiscreteColorMapTest.h"
#include "catch.hpp"
#include "eml2/AbstractHdfProxy.h"
#include "eml2/GraphicalInformationSet.h"
#include "eml2/PropertyKind.h"
#include "resqml2/IjkGridExplicitRepresentation.h"
#include "resqml2/Model.h"
#include "resqml2/EarthModelInterpretation.h"
#include "resqml2/LocalDepth3dCrs.h"
#include "resqml2/DiscreteProperty.h"
#include "resqml2_2/DiscreteColorMap.h"

using namespace std;
using namespace COMMON_NS;
using namespace RESQML2_NS;
using namespace EML2_NS;
using namespace resqml2_2test;
using namespace gsoap_resqml2_0_1;

char const* DiscreteColorMapTest::defaultUuid = "62075ce2-1b89-4f80-963e-2770bfc39baf";
char const* DiscreteColorMapTest::defaultTitle = "Discrete Color Map";
char const* DiscreteColorMapTest::uuidPropertyKind = "478278a5-827b-4a67-b5d8-d3dc18ef4525";
char const* DiscreteColorMapTest::titlePropertyKind = "Property Kind";
char const* DiscreteColorMapTest::uuidOrganizationFeature = "ceefeac1-21b1-4a31-b74b-ab1e64eacf80";
char const* DiscreteColorMapTest::titleOrganizationFeature = "Organization Feature";
char const* DiscreteColorMapTest::uuidEarthModelInterpretation = "8f6afd90-71e1-4a1e-891f-9c628feeb980";
char const* DiscreteColorMapTest::titleEarthModelInterpretation = "Earth Model Interpretation";
char const* DiscreteColorMapTest::uuidLocalDepth3dCrs = "69aa7e50-1538-4818-93a4-11fcfdc2292e";
char const* DiscreteColorMapTest::titleLocalDepth3dCrs = "Loacl Depth 3d Crs";
char const* DiscreteColorMapTest::uuidIjkGridExplicitRepresentation = "fd0e5b96-ca00-4f8e-bf7a-a5609b511044";
char const* DiscreteColorMapTest::titleIjkGridExplicitRepresentation = "Ijk Grid Explicit Representation";
char const* DiscreteColorMapTest::uuidDiscreteProperty = "7594850b-ab54-4c95-af9c-06f6a1175ad6";
char const* DiscreteColorMapTest::titleDiscreteProperty = "Discrete Property";
char const* DiscreteColorMapTest::uuidGraphicalInformationSet = "fb32a2a3-8ee6-4526-80dc-d247f13fcecc";
char const* DiscreteColorMapTest::titleGraphicalInformationSet = "Graphical Information Set";
char const* DiscreteColorMapTest::uuidPropertyKindDiscreteColorMap = "ab67d54c-4924-4c24-9be8-2924df6c5072";
char const* DiscreteColorMapTest::titlePropertyKindDiscreteColorMap = "Property Kind Discrete Color Map";


DiscreteColorMapTest::DiscreteColorMapTest(const string & repoPath)
	: AbstractTest(repoPath) {
}

void DiscreteColorMapTest::initRepo() {
	// creating an ijk grid
	AbstractHdfProxy* hdfProxy =  repo->getHdfProxySet()[0];
	Model* organizationFeature =  repo->createEarthModel(uuidOrganizationFeature, titleOrganizationFeature);
	EarthModelInterpretation* earthModelInterp = repo->createEarthModelInterpretation(organizationFeature, uuidEarthModelInterpretation, titleEarthModelInterpretation);
	IjkGridExplicitRepresentation* ijkgrid = repo->createIjkGridExplicitRepresentation(earthModelInterp, uuidIjkGridExplicitRepresentation, titleIjkGridExplicitRepresentation, 2, 1, 1);
	double nodes[48] = { 0, 0, 300, 375, 0, 300, 700, 0, 350, 0, 150, 300, 375, 150, 300, 700, 150, 350, /* SPLIT*/ 375, 0, 350, 375, 150, 350,
		0, 0, 500, 375, 0, 500, 700, 0, 550, 0, 150, 500, 375, 150, 500, 700, 150, 550, /* SPLIT*/ 375, 0, 550, 375, 150, 550 };
	unsigned int pillarOfCoordinateLine[2] = { 1, 4 };
	unsigned int splitCoordinateLineColumnCumulativeCount[2] = { 1, 2 };
	unsigned int splitCoordinateLineColumns[2] = { 1, 1 };
	ijkgrid->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape__vertical, gsoap_resqml2_0_1::resqml20__KDirection__down, false, nodes, hdfProxy,
		2, pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);

	// assotiating a discrete property to the ijk grid
	auto propertyKind = repo->createPropertyKind("5f78f66a-ed1b-4827-a868-beb989febb31", "code", gsoap_eml2_1::eml21__QuantityClassKind__not_x0020a_x0020measure);
	DiscreteProperty* discreteProperty = repo->createDiscreteProperty(ijkgrid, uuidDiscreteProperty, titleDiscreteProperty, 1,
		gsoap_eml2_3::resqml22__IndexableElement__cells, propertyKind);
	unsigned short prop1Values[2] = { 0, 1 };
	discreteProperty->pushBackUShortHdf5Array3dOfValues(prop1Values, 2, 1, 1, hdfProxy, -1);

	// associating a discrete color map to the discrete property kind
	RESQML2_NS::DiscreteColorMap* discreteColorMap1 = repo->createDiscreteColorMap(uuidPropertyKindDiscreteColorMap, titlePropertyKindDiscreteColorMap);
	REQUIRE(discreteColorMap1 != nullptr);
	unsigned int rgbColors1[6] = { 0, 0, 256, 255, 0, 0 };
	double alphas1[2] = { 1., 1. };
	vector<string> titles1 = { "blue", "red" };
	REQUIRE_THROWS(discreteColorMap1->setRgbColors(2, rgbColors1, alphas1, titles1));
	rgbColors1[2] = 255;
	discreteColorMap1->setRgbColors(2, rgbColors1, alphas1, titles1);
	GraphicalInformationSet* graphicalInformationSet = repo->createGraphicalInformationSet(uuidGraphicalInformationSet, titleGraphicalInformationSet);
	graphicalInformationSet->setDiscreteColorMap(propertyKind, discreteColorMap1);
	REQUIRE(graphicalInformationSet->hasDiscreteColorMap(discreteProperty) == true);
	REQUIRE(graphicalInformationSet->getDiscreteColorMapUuid(discreteProperty) == discreteColorMap1->getUuid());

	// associating the discrete color map to the discrete property
	RESQML2_NS::DiscreteColorMap* discreteColorMap2 = repo->createDiscreteColorMap(defaultUuid, defaultTitle);
	REQUIRE(discreteColorMap2 != nullptr);
	unsigned int rgbColors2[6] = { 255, 0, 0, 0, 0, 255 };
	double alphas2[2] = { 1., 1. };
	vector<string> titles2 = { "red", "blue" };
	discreteColorMap2->setRgbColors(2, rgbColors2, alphas2, titles2);
	graphicalInformationSet->setDiscreteColorMap(discreteProperty, discreteColorMap2);
	REQUIRE(graphicalInformationSet->hasDiscreteColorMap(discreteProperty) == true);
	REQUIRE(graphicalInformationSet->getDiscreteColorMapUuid(discreteProperty) == discreteColorMap2->getUuid());
}

void DiscreteColorMapTest::readRepo() {
	GraphicalInformationSet * graphicalInformationSet = repo->getDataObjects<GraphicalInformationSet>()[0];
	DiscreteProperty* discreteProperty = repo->getDataObjectByUuid<DiscreteProperty>(uuidDiscreteProperty);
	REQUIRE(graphicalInformationSet->hasDiscreteColorMap(discreteProperty));
	RESQML2_NS::DiscreteColorMap* discreteColorMap = graphicalInformationSet->getDiscreteColorMap(discreteProperty);
	REQUIRE(discreteColorMap->getUuid() == defaultUuid);
	double r, g, b;
	discreteColorMap->getRgbColor(0, r, g, b);
	REQUIRE(r == 1.); // 255 is converted to 1. since we ask for double red value
	REQUIRE(g == 0.);
	REQUIRE(b == 0.);
	discreteColorMap->getRgbColor(1, r, g, b);
	REQUIRE(r == 0.);
	REQUIRE(g == 0.);
	REQUIRE(b == 1.); // 255 is converted to 1. since we ask for double blue value
}
