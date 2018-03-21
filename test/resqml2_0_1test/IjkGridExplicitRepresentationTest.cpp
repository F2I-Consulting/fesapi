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
#include "resqml2_0_1test/IjkGridExplicitRepresentationTest.h"

#include "catch.hpp"
#include "resqml2_0_1test/LocalDepth3dCrsTest.h"

#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_0_1test;
using namespace RESQML2_NS;

const char* IjkGridExplicitRepresentationTest::defaultUuid = "f889e5d2-249e-4827-8532-ce60a1d05b99";
const char* IjkGridExplicitRepresentationTest::defaultTitle = "Ijk Grid Representation";
const ULONG64 IjkGridExplicitRepresentationTest::nodesCountIjkGridRepresentation = 16;
double IjkGridExplicitRepresentationTest::nodesIjkGridRepresentation[] = { 0, 0, 300, 375, 0, 300, 700, 0, 350, 0, 150, 300, 375, 150, 300, 700, 150, 350, /* SPLIT*/ 375, 0, 350, 375, 150, 350, 0, 0, 500, 375, 0, 500, 700, 0, 550, 0, 150, 500, 375, 150, 500, 700, 150, 550, /* SPLIT*/ 375, 0, 550, 375, 150, 550 };

IjkGridExplicitRepresentationTest::IjkGridExplicitRepresentationTest(const string & epcDocPath)
	: AbstractIjkGridRepresentationTest(epcDocPath, defaultUuid, defaultTitle, nodesCountIjkGridRepresentation, nodesIjkGridRepresentation) {
}

IjkGridExplicitRepresentationTest::IjkGridExplicitRepresentationTest(EpcDocument * epcDoc, bool init)
	: AbstractIjkGridRepresentationTest(epcDoc, defaultUuid, defaultTitle, nodesCountIjkGridRepresentation, nodesIjkGridRepresentation) {
	if (init)
			this->initEpcDoc();
		else
			this->readEpcDoc();
}

void IjkGridExplicitRepresentationTest::initEpcDocHandler() {
	// getting the local depth 3d crs
	LocalDepth3dCrsTest* crsTest = new LocalDepth3dCrsTest(this->epcDoc, true);
	RESQML2_0_1_NS::LocalDepth3dCrs* crs = epcDoc->getResqmlAbstractObjectByUuid<RESQML2_0_1_NS::LocalDepth3dCrs>(LocalDepth3dCrsTest::defaultUuid);

	// getting the hdf proxy
	AbstractHdfProxy* hdfProxy = this->epcDoc->getHdfProxySet()[0];

	// creating the ijk grid
	RESQML2_0_1_NS::IjkGridExplicitRepresentation* ijkGrid = this->epcDoc->createIjkGridExplicitRepresentation(crs, uuid, title, 2, 1, 1);
	REQUIRE( ijkGrid != nullptr );
	unsigned int pillarOfCoordinateLine[2] = {1,4};
	unsigned int splitCoordinateLineColumnCumulativeCount[2] = {1,2};
	unsigned int splitCoordinateLineColumns[2] = {1,1};
	ijkGrid->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml2__PillarShape__vertical, gsoap_resqml2_0_1::resqml2__KDirection__down, false, this->xyzPointsOfAllPatchesInGlobalCrs, hdfProxy,
		2, pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);

	// cleaning
	delete crsTest;
}

void IjkGridExplicitRepresentationTest::readEpcDocHandler() {
}

