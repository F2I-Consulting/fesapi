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
#include "GraphicalInformationSetTest.h"
#include "catch.hpp"
#include "config.h"
#include "common/GraphicalInformationSet.h"
#include "resqml2_0_1/Horizon.h"
#include "resqml2_0_1/LocalTime3dCrs.h"

using namespace std;
using namespace COMMON_NS;
using namespace RESQML2_0_1_NS;
using namespace commontest;
using namespace resqml2_0_1test;

GraphicalInformationSetTest::GraphicalInformationSetTest(const string & epcDocPath)
	: AbstractObjectTest(epcDocPath, uuidGraphicalInformationSet, titleGraphicalInformationSet) {
}

GraphicalInformationSetTest::GraphicalInformationSetTest(EpcDocument * epcDoc, bool init)
	: AbstractObjectTest(epcDoc, uuidGraphicalInformationSet, titleGraphicalInformationSet) {
	if (init)
		initEpcDoc();
	else
		readEpcDoc();
}

void GraphicalInformationSetTest::initEpcDocHandler() {
	Horizon* feature = epcDoc->createHorizon(uuidHorizon0, titleHorizon0);

	GraphicalInformationSet* graphicalInformationSet = epcDoc->createGraphicalInformationSet(uuid, title);
	REQUIRE(graphicalInformationSet != nullptr);
	
	REQUIRE(graphicalInformationSet->hasGraphicalInformation(feature) == false);
	REQUIRE(graphicalInformationSet->hasDefaultColor(feature) == false);
	REQUIRE_THROWS(graphicalInformationSet->setDefaultHsvColor(feature, 361, 0., 0.));
	REQUIRE_THROWS(graphicalInformationSet->setDefaultHsvColor(feature, 0., 1.1, 0.));
	REQUIRE_THROWS(graphicalInformationSet->setDefaultHsvColor(feature, 0., 0., -1.));

	graphicalInformationSet->setDefaultHsvColor(feature, 0., 1., 0.5, 1., "blue");
}

void GraphicalInformationSetTest::readEpcDocHandler() {
	REQUIRE(epcDoc->getDataObjects<GraphicalInformationSet>().size() == 1);
	GraphicalInformationSet * graphicalInformationSet = epcDoc->getDataObjects<GraphicalInformationSet>()[0];
	REQUIRE(graphicalInformationSet->getUuid() == uuid);
	
	REQUIRE(graphicalInformationSet->getGraphicalInformationSetCount() == 1);
	Horizon* feature = static_cast<Horizon *>(graphicalInformationSet->getTargetObject(0));
	REQUIRE(feature->getUuid() == uuidHorizon0);
	REQUIRE(graphicalInformationSet->hasGraphicalInformation(feature) == true);
	REQUIRE(graphicalInformationSet->hasDefaultColor(feature) == true);
	REQUIRE(graphicalInformationSet->getDefaultHue(feature) == 0.);
	REQUIRE(graphicalInformationSet->getDefaultSaturation(feature) == 1.);
	REQUIRE(graphicalInformationSet->getDefaultValue(feature) == 0.5);
	REQUIRE(graphicalInformationSet->getDefaultAlpha(feature) == 1.);
	REQUIRE(graphicalInformationSet->hasDefaultColorTitle(feature) == true);
	REQUIRE(graphicalInformationSet->getDefaultColorTitle(feature) == "blue");

	double hue, saturation, value;
	GraphicalInformationSet::rgbToHsv(1., 0., 0., hue, saturation, value); // red
	REQUIRE(hue == 0.);
	REQUIRE(saturation == 1.);
	REQUIRE(value == 1.);
	GraphicalInformationSet::rgbToHsv(0., 1., 0., hue, saturation, value); // green
	REQUIRE(hue == 120.);
	REQUIRE(saturation == 1.);
	REQUIRE(value == 1.);
	GraphicalInformationSet::rgbToHsv(0., 0., 1., hue, saturation, value); // blue
	REQUIRE(hue == 240.);
	REQUIRE(saturation == 1.);
	REQUIRE(value == 1.);

	GraphicalInformationSet::rgbToHsv((unsigned int) 255, (unsigned int) 0, (unsigned int) 0, hue, saturation, value); // red
	REQUIRE(hue == 0.);
	REQUIRE(saturation == 1.);
	REQUIRE(value == 1.);
	GraphicalInformationSet::rgbToHsv((unsigned int) 0, (unsigned int) 255, (unsigned int) 0, hue, saturation, value); // green
	REQUIRE(hue == 120.);
	REQUIRE(saturation == 1.);
	REQUIRE(value == 1.);
	GraphicalInformationSet::rgbToHsv((unsigned int)  0, (unsigned int)  0, (unsigned int)  255, hue, saturation, value); // blue
	REQUIRE(hue == 240.);
	REQUIRE(saturation == 1.);
	REQUIRE(value == 1.);

	double red, green, blue;
	GraphicalInformationSet::hsvToRgb(0., 1., 1., red, green, blue); // red
	REQUIRE(red == 1.);
	REQUIRE(green == 0.);
	REQUIRE(blue == 0.);
	GraphicalInformationSet::hsvToRgb(120., 1., 1., red, green, blue); // green
	REQUIRE(red == 0.);
	REQUIRE(green == 1.);
	REQUIRE(blue == 0.);
	GraphicalInformationSet::hsvToRgb(240., 1., 1., red, green, blue); // blue
	REQUIRE(red == 0.);
	REQUIRE(green == 0.);
	REQUIRE(blue == 1.);

	unsigned int r, g, b;
	GraphicalInformationSet::hsvToRgb(0., 1., 1., r, g, b); // red
	REQUIRE(r == 255);
	REQUIRE(g == 0);
	REQUIRE(b == 0);
	GraphicalInformationSet::hsvToRgb(360., 1., 1., r, g, b); // red
	REQUIRE(r == 255);
	REQUIRE(g == 0);
	REQUIRE(b == 0);
	GraphicalInformationSet::hsvToRgb(120., 1., 1., r, g, b); // green
	REQUIRE(r == 0);
	REQUIRE(g == 255);
	REQUIRE(b == 0);
	GraphicalInformationSet::hsvToRgb(240., 1., 1., r, g, b); // blue
	REQUIRE(r == 0);
	REQUIRE(g == 0);
	REQUIRE(b == 255);
}

