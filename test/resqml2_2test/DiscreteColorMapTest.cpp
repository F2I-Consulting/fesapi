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
#include "../config.h"
#include "common/AbstractHdfProxy.h"
#include "common/GraphicalInformationSet.h"
#include "resqml2/PropertyKind.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2_0_1/OrganizationFeature.h"
#include "resqml2_0_1/EarthModelInterpretation.h"
#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "resqml2_0_1/DiscreteProperty.h"
#include "resqml2_2/DiscreteColorMap.h"

using namespace std;
using namespace COMMON_NS;
using namespace RESQML2_NS;
using namespace RESQML2_2_NS;
using namespace RESQML2_0_1_NS;
using namespace resqml2_2test;
using namespace gsoap_resqml2_0_1;

// PropertyKind
const char* DiscreteColorMapTest::uuidPropertyKind = "478278a5-827b-4a67-b5d8-d3dc18ef4525";
const char* DiscreteColorMapTest::titlePropertyKind = "Property Kind";
const char* DiscreteColorMapTest::uuidOrganizationFeature = "ceefeac1-21b1-4a31-b74b-ab1e64eacf80";
const char* DiscreteColorMapTest::titleOrganizationFeature = "Organization Feature";
const char* DiscreteColorMapTest::uuidEarthModelInterpretation = "8f6afd90-71e1-4a1e-891f-9c628feeb980";
const char* DiscreteColorMapTest::titleEarthModelInterpretation = "Earth Model Interpretation";
const char* DiscreteColorMapTest::uuidLocalDepth3dCrs = "69aa7e50-1538-4818-93a4-11fcfdc2292e";
const char* DiscreteColorMapTest::titleLocalDepth3dCrs = "Loacl Depth 3d Crs";
const char* DiscreteColorMapTest::uuidIjkGridExplicitRepresentation = "fd0e5b96-ca00-4f8e-bf7a-a5609b511044";
const char* DiscreteColorMapTest::titleIjkGridExplicitRepresentation = "Ijk Grid Explicit Representation";
const char* DiscreteColorMapTest::uuidDiscreteProperty = "7594850b-ab54-4c95-af9c-06f6a1175ad6";
const char* DiscreteColorMapTest::titleDiscreteProperty = "Discrete Property";
const char* DiscreteColorMapTest::uuidGraphicalInformationSet = "fb32a2a3-8ee6-4526-80dc-d247f13fcecc";
const char* DiscreteColorMapTest::titleGraphicalInformationSet = "Graphical Information Set";

DiscreteColorMapTest::DiscreteColorMapTest(const string & epcDocPath)
	: AbstractObjectTest(epcDocPath, uuidDiscreteColorMap, titleDiscreteColorMap) {
}

DiscreteColorMapTest::DiscreteColorMapTest(EpcDocument * epcDoc, bool init)
	: AbstractObjectTest(epcDoc, uuidDiscreteColorMap, uuidDiscreteColorMap) {
	if (init)
		initEpcDoc();
	else
		readEpcDoc();
}

void DiscreteColorMapTest::initEpcDocHandler() {
	// creating an ijk grid
	AbstractHdfProxy* hdfProxy = this->epcDoc->getHdfProxySet()[0];
	OrganizationFeature* organizationFeature = epcDoc->createEarthModel(uuidOrganizationFeature, titleOrganizationFeature);
	EarthModelInterpretation* earthModelInterp = epcDoc->createEarthModelInterpretation(organizationFeature, uuidEarthModelInterpretation, titleEarthModelInterpretation);
	LocalDepth3dCrs* local3dCrs = epcDoc->createLocalDepth3dCrs(uuidLocalDepth3dCrs, titleLocalDepth3dCrs, 
		.0, .0, .0, .0, eml20__LengthUom__m, 23031, eml20__LengthUom__m, "Unknown", false);
	IjkGridExplicitRepresentation* ijkgrid = epcDoc->createIjkGridExplicitRepresentation(earthModelInterp, local3dCrs, uuidIjkGridExplicitRepresentation, titleIjkGridExplicitRepresentation, 2, 1, 1);
	double nodes[48] = { 0, 0, 300, 375, 0, 300, 700, 0, 350, 0, 150, 300, 375, 150, 300, 700, 150, 350, /* SPLIT*/ 375, 0, 350, 375, 150, 350,
		0, 0, 500, 375, 0, 500, 700, 0, 550, 0, 150, 500, 375, 150, 500, 700, 150, 550, /* SPLIT*/ 375, 0, 550, 375, 150, 550 };
	unsigned int pillarOfCoordinateLine[2] = { 1, 4 };
	unsigned int splitCoordinateLineColumnCumulativeCount[2] = { 1, 2 };
	unsigned int splitCoordinateLineColumns[2] = { 1, 1 };
	ijkgrid->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml2__PillarShape__vertical, gsoap_resqml2_0_1::resqml2__KDirection__down, false, nodes, hdfProxy,
		2, pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);

	// assotiating a discrete property to the ijk grid
	PropertyKind* propertyKind = epcDoc->createPropertyKind(uuidPropertyKind, titlePropertyKind, "urn:resqml:f2i-consulting.com", 
		resqml2__ResqmlUom__Euc, resqml2__ResqmlPropertyKind__discrete);
	DiscreteProperty* discreteProperty = epcDoc->createDiscreteProperty(ijkgrid, uuidDiscreteProperty, titleDiscreteProperty, 1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__cells, propertyKind);
	unsigned short prop1Values[2] = { 0, 1 };
	discreteProperty->pushBackUShortHdf5Array3dOfValues(prop1Values, 2, 1, 1, hdfProxy, -1);

	// creating the discrete color map
	DiscreteColorMap* discreteColorMap = epcDoc->createDiscreteColorMap(uuid, title);
	REQUIRE(discreteColorMap != nullptr);
	unsigned int rgbColors[6] = { 256, 0, 0, 0, 0, 255 };
	double alphas[2] = { 1., 1. };
	std::string titles[2] = { "red", "blue" };
	REQUIRE_THROWS(discreteColorMap->setRgbColors(2, rgbColors, alphas, titles));
	rgbColors[0] = 255;
	discreteColorMap->setRgbColors(2, rgbColors, alphas, titles);

	// associating the discrete color map to the discrete property
	GraphicalInformationSet* graphicalInformationSet = epcDoc->createGraphicalInformationSet(uuidGraphicalInformationSet, titleGraphicalInformationSet);
	graphicalInformationSet->setDiscreteColorMap(discreteProperty, discreteColorMap);
}

void DiscreteColorMapTest::readEpcDocHandler() {
	GraphicalInformationSet * graphicalInformationSet = epcDoc->getDataObjects<GraphicalInformationSet>()[0];
	DiscreteProperty* discreteProperty = epcDoc->getDataObjectByUuid<DiscreteProperty>(uuidDiscreteProperty);
	REQUIRE(graphicalInformationSet->hasDiscreteColorMap(discreteProperty));
	DiscreteColorMap* discreteColorMap = graphicalInformationSet->getDiscreteColorMap(discreteProperty);
	REQUIRE(discreteColorMap->getUuid() == uuidDiscreteColorMap);
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

