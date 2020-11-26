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
#include "resqml2_test/RightHanded4x3x2ExplicitIjkGrid.h"

#include "catch.hpp"
#include "resqml2_test/LocalDepth3dCrsTest.h"

#include "resqml2/LocalDepth3dCrs.h"
#include "resqml2/IjkGridExplicitRepresentation.h"
#include "resqml2/GridConnectionSetRepresentation.h"
#include "resqml2/DiscreteProperty.h"
#include "resqml2/ContinuousProperty.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_test;
using namespace RESQML2_NS;

const char* RightHanded4x3x2ExplicitIjkGrid::defaultUuid = "f274d3d8-80ff-4860-90fb-609716303887";
const char* RightHanded4x3x2ExplicitIjkGrid::defaultTitle = "Right Handed 4x3x2 Explicit Ijk Grid";
const unsigned long long RightHanded4x3x2ExplicitIjkGrid::nodesCountIjkGridRepresentation = 72;
double RightHanded4x3x2ExplicitIjkGrid::nodesIjkGridRepresentation[216] = {
	0, 150, 300, 150, 150, 300, 375, 150, 300, 550, 150, 350, 700, 150, 350, //IJ0K0
	0, 100, 300, 150, 100, 300, 375, 100, 300, 550, 100, 350, 700, 100, 350, //IJ1K0
	0, 50, 300, 150, 50, 300, 375, 50, 300, 550, 50, 350, 700, 50, 350, //IJ2K0
	0, 0, 300, 150, 0, 300, 375, 0, 300, 550, 0, 350, 700, 0, 350, //IJ3K0
	375, 0, 350, 375, 50, 350, 375, 100, 350, 375, 150, 350, // SPLIT K0
	0, 150, 400, 150, 150, 400, 375, 150, 400, 550, 150, 450, 700, 150, 450, //IJ0K1
	0, 100, 400, 150, 100, 400, 375, 100, 400, 550, 100, 450, 700, 100, 450, //IJ1K1
	0, 50, 400, 150, 50, 400, 375, 50, 400, 550, 50, 450, 700, 50, 450, //IJ2K1
	0, 0, 400, 150, 0, 400, 375, 0, 400, 550, 0, 450, 700, 0, 450, //IJ3K1
	375, 0, 450, 375, 50, 450, 375, 100, 450, 375, 150, 450, // SPLIT K1
	0, 150, 500, 150, 150, 500, 375, 150, 500, 550, 150, 550, 700, 150, 550, //IJ0K2
	0, 100, 500, 150, 100, 500, 375, 100, 500, 550, 100, 550, 700, 100, 550, //IJ1K2
	0, 50, 500, 150, 50, 500, 375, 50, 500, 550, 50, 550, 700, 50, 550, //IJ2K2
	0, 0, 500, 150, 0, 500, 375, 0, 500, 550, 0, 550, 700, 0, 550, //IJ3K2
	375, 0, 550, 375, 50, 550, 375, 100, 550, 375, 150, 550 // SPLIT K2
};

RightHanded4x3x2ExplicitIjkGrid::RightHanded4x3x2ExplicitIjkGrid(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void RightHanded4x3x2ExplicitIjkGrid::initRepo() {
	// creating the ijk grid
	RESQML2_NS::IjkGridExplicitRepresentation* ijkGrid = repo->createIjkGridExplicitRepresentation(defaultUuid, defaultTitle, 4, 3, 2);
	REQUIRE(ijkGrid != nullptr);
	unsigned int pillarOfCoordinateLine[4] = { 17, 12, 7, 2 };
	unsigned int splitCoordinateLineColumnCumulativeCount[4] = { 1, 3, 5, 6 };
	unsigned int splitCoordinateLineColumns[6] = { 10, 10, 6, 6, 2, 2 };
	ijkGrid->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape__vertical, gsoap_resqml2_0_1::resqml20__KDirection__down, false, nodesIjkGridRepresentation, nullptr,
		4, pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);

	// Enabling cell
	unsigned char enabledCells[24] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0
	};
	ijkGrid->setEnabledCells(enabledCells);

	// Grid connection set representation
	RESQML2_NS::GridConnectionSetRepresentation * gridConnSet432 = repo->createGridConnectionSetRepresentation("a3d1462a-04e3-4374-921b-a4a1e9ba3ea3", "GridConnectionSetRepresentation");
	gridConnSet432->pushBackSupportingGridRepresentation(ijkGrid);
	uint64_t cellConn432[30] = {
		1, 9999, 5, 9999, 9, 9999,
		1, 2, 5, 6, 9, 10,
		13, 2, 17, 6, 21, 10,
		13, 14, 17, 18, 21, 22,
		9999, 14, 9999, 18, 9999, 22
	};
	gridConnSet432->setCellIndexPairs(15, cellConn432, 9999, nullptr);
	int localFacePerCellIndexPairs432[30] = {
		3, 9999, 3, 9999, 3, 9999,
		3, 5, 3, 5, 3, 5,
		3, 5, 3, 5, 3, 5,
		3, 5, 3, 5, 3, 5,
		9999, 5, 9999, 5, 9999, 5
	};
	gridConnSet432->setLocalFacePerCellIndexPairs(15, localFacePerCellIndexPairs432, -1, nullptr);

	// Discrete property
	auto propertyKind = repo->createPropertyKind("5f78f66a-ed1b-4827-a868-beb989febb31", "code", gsoap_eml2_1::eml21__QuantityClassKind__not_x0020a_x0020measure);
	RESQML2_NS::DiscreteProperty* discreteProp = repo->createDiscreteProperty(ijkGrid, "0a8fb2aa-d1e1-4914-931c-e9e6bf2aabe5", "Cell index", 1,
		gsoap_eml2_3::resqml22__IndexableElement__cells, propertyKind);
	int64_t discretePropValues[24] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
		12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23
	};
	discreteProp->pushBackLongHdf5Array3dOfValues(discretePropValues, 4, 3, 2, nullptr, -1);

	// Continuous property
	propertyKind = repo->createPropertyKind("4a305182-221e-4205-9e7c-a36b06fa5b3d", "length", gsoap_eml2_1::eml21__QuantityClassKind__length);
	RESQML2_NS::ContinuousProperty* continuousProp = repo->createContinuousProperty(ijkGrid, "de5a71cc-879d-4cda-8fb3-146c70539cf9", "Amplitude", 1,
		gsoap_eml2_3::resqml22__IndexableElement__cells, gsoap_resqml2_0_1::resqml20__ResqmlUom__Euc, propertyKind);
	double continuousPropValues[24] = {
		0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
		1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.5, 1.4, 1.3, 1.2, 1.1, 1.0
	};
	continuousProp->pushBackDoubleHdf5Array3dOfValues(continuousPropValues, 4, 3, 2, nullptr);
}

void RightHanded4x3x2ExplicitIjkGrid::readRepo() {
	// getting the subrep
	RESQML2_NS::IjkGridExplicitRepresentation* ijkGrid = repo->getDataObjectByUuid<RESQML2_NS::IjkGridExplicitRepresentation>(defaultUuid);

	REQUIRE(ijkGrid->getCellCount() == 24);
	REQUIRE(ijkGrid->getPillarCount() == 20);

	// checking values
	const uint64_t coordCount = 3 * nodesCountIjkGridRepresentation;
	std::unique_ptr<double[]> xyzPoints(new double[coordCount]);
	ijkGrid->getXyzPointsOfAllPatches(xyzPoints.get());
	for (uint64_t i = 0; i < coordCount; ++i) {
		REQUIRE(nodesIjkGridRepresentation[i] == xyzPoints[i]);
	}

	REQUIRE(ijkGrid->getGridConnectionSetRepresentationCount() == 1);
	REQUIRE(ijkGrid->getGridConnectionSetRepresentation(0)->getUuid() == "a3d1462a-04e3-4374-921b-a4a1e9ba3ea3");
	REQUIRE(ijkGrid->getGridConnectionSetRepresentation(0)->getCellIndexPairCount() == 15);
	REQUIRE(ijkGrid->getGridConnectionSetRepresentation(0)->getSupportingGridRepresentation(0) == ijkGrid);
}
