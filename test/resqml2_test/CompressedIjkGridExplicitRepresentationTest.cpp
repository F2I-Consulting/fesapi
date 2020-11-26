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
#include "resqml2_test/CompressedIjkGridExplicitRepresentationTest.h"

#include "catch.hpp"
#include "resqml2_test/LocalDepth3dCrsTest.h"

#include "eml2/AbstractHdfProxy.h"
#include "resqml2/LocalDepth3dCrs.h"
#include "resqml2/IjkGridExplicitRepresentation.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_test;
using namespace RESQML2_NS;

const char* CompressedIjkGridExplicitRepresentationTest::defaultUuid = "f889e5d2-249e-4827-8532-ce60a1d05b99";
const char* CompressedIjkGridExplicitRepresentationTest::defaultTitle = "Compressed Ijk Grid Representation";
const unsigned long long CompressedIjkGridExplicitRepresentationTest::nodesCountIjkGridRepresentation = 16;
double CompressedIjkGridExplicitRepresentationTest::nodesIjkGridRepresentation[] = { 0, 0, 300, 375, 0, 300, 700, 0, 350, 0, 150, 300, 375, 150, 300, 700, 150, 350, /* SPLIT*/ 375, 0, 350, 375, 150, 350, 0, 0, 500, 375, 0, 500, 700, 0, 550, 0, 150, 500, 375, 150, 500, 700, 150, 550, /* SPLIT*/ 375, 0, 550, 375, 150, 550 };

CompressedIjkGridExplicitRepresentationTest::CompressedIjkGridExplicitRepresentationTest(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void CompressedIjkGridExplicitRepresentationTest::initRepo() {
	// getting the hdf proxy
	EML2_NS::AbstractHdfProxy* hdfProxy = repo->getHdfProxySet()[0];
	hdfProxy->setCompressionLevel(6);

	// creating the ijk grid
	RESQML2_NS::IjkGridExplicitRepresentation* ijkGrid = repo->createIjkGridExplicitRepresentation(defaultUuid, defaultTitle, 2, 1, 1);
	REQUIRE( ijkGrid != nullptr );
	unsigned int pillarOfCoordinateLine[2] = {1,4};
	unsigned int splitCoordinateLineColumnCumulativeCount[2] = {1,2};
	unsigned int splitCoordinateLineColumns[2] = {1,1};
	ijkGrid->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape__vertical, gsoap_resqml2_0_1::resqml20__KDirection__down, false, nodesIjkGridRepresentation, hdfProxy,
		2, pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);
}

void CompressedIjkGridExplicitRepresentationTest::readRepo() {
	// checking number of points in the geometry
	RESQML2_NS::AbstractIjkGridRepresentation* representation = repo->getDataObjectByUuid<RESQML2_NS::AbstractIjkGridRepresentation>(defaultUuid);
	REQUIRE(representation->getXyzPointCountOfAllPatches() == nodesCountIjkGridRepresentation);
	REQUIRE(representation->isNodeGeometryCompressed());

	// checking values
	const uint64_t pointCount = 3 * nodesCountIjkGridRepresentation;
	double * xyzPoint = new double[pointCount];
	representation->getXyzPointsOfAllPatches(xyzPoint);
	for (uint64_t i = 0; i<pointCount; ++i) {
		REQUIRE(nodesIjkGridRepresentation[i] == xyzPoint[i]);
	}
	delete[] xyzPoint;
}
