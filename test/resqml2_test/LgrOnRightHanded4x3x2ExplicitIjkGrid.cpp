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
#include "resqml2_test/LgrOnRightHanded4x3x2ExplicitIjkGrid.h"

#include <stdexcept>

#include "resqml2_test/RightHanded4x3x2ExplicitIjkGrid.h"
#include "resqml2_test/LocalDepth3dCrsTest.h"

#include "catch.hpp"
#include "common/EpcDocument.h"
#include "resqml2/LocalDepth3dCrs.h"
#include "resqml2/IjkGridExplicitRepresentation.h"
#include "resqml2/DiscreteProperty.h"
#include "resqml2/ContinuousProperty.h"
#include "resqml2/RepresentationSetRepresentation.h"

using namespace std;
using namespace resqml2_test;
using namespace COMMON_NS;
using namespace RESQML2_NS;

const char* LgrOnRightHanded4x3x2ExplicitIjkGrid::defaultUuid = "11852778-139e-4fa3-bb34-70c4014553f7";
const char* LgrOnRightHanded4x3x2ExplicitIjkGrid::defaultTitle = "LGR";
const unsigned long long LgrOnRightHanded4x3x2ExplicitIjkGrid::nodesCountIjkGridRepresentation = 40;
double LgrOnRightHanded4x3x2ExplicitIjkGrid::nodesIjkGridRepresentation[] = {
	0, 50, 300, 50, 50, 300, 100, 50, 300, 150, 50, 300, //IJ0K0
	0,  0, 300, 50,  0, 300, 100,  0, 300, 150,  0, 300, //IJ1K0
	0, 50, 350, 50, 50, 350, 100, 50, 350, 150, 50, 350, //IJ0K1
	0,  0, 350, 50,  0, 350, 100,  0, 350, 150,  0, 350, //IJ1K1
	0, 50, 400, 50, 50, 400, 100, 50, 400, 150, 50, 400, //IJ0K2
	0,  0, 400, 50,  0, 400, 100,  0, 400, 150,  0, 400, //IJ1K2
	0, 50, 450, 50, 50, 450, 100, 50, 450, 150, 50, 450, //IJ0K3
	0,  0, 450, 50,  0, 450, 100,  0, 450, 150,  0, 450, //IJ1K3
	0, 50, 500, 50, 50, 500, 100, 50, 500, 150, 50, 500, //IJ0K4
	0,  0, 500, 50,  0, 500, 100,  0, 500, 150,  0, 500  //IJ1K4
};

LgrOnRightHanded4x3x2ExplicitIjkGrid::LgrOnRightHanded4x3x2ExplicitIjkGrid(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void LgrOnRightHanded4x3x2ExplicitIjkGrid::initRepo() {
	auto* parentGrid = repo->createPartialIjkGridRepresentation(RightHanded4x3x2ExplicitIjkGrid::defaultUuid, "");

	// creating the child ijk grid
	RESQML2_NS::IjkGridExplicitRepresentation* childGrid = repo->createIjkGridExplicitRepresentation(defaultUuid, defaultTitle, 3, 1, 4);
	childGrid->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape__vertical, gsoap_resqml2_0_1::resqml20__KDirection__down, false, nodesIjkGridRepresentation, nullptr);
	childGrid->setParentWindow(
		0, 3, 1, 1,
		0, 1, 1, 1,
		0, 2, 1, 2,
		parentGrid);

	// creating the same child ijk grid using HDF5 datasets
	RESQML2_NS::IjkGridExplicitRepresentation* childGridHdf5 = repo->createIjkGridExplicitRepresentation("38930b30-1325-424e-a1e9-666fa50bfa4f", "Child grid HDF5", 3, 1, 4);
	childGridHdf5->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape__vertical, gsoap_resqml2_0_1::resqml20__KDirection__down, false, nodesIjkGridRepresentation, nullptr);
	unsigned int one = 1;
	unsigned int three = 3;
	unsigned int twotwo[2] = { 2,2 };
	unsigned int oneone[2] = { 1,1 };
	childGridHdf5->setParentWindow(
		0, &three, &one, one,
		0, &one, &one, one,
		0, twotwo, oneone, 2,
		parentGrid);

	// creating a non constant cell count per interval child ijk grid without geometry
	RESQML2_NS::IjkGridExplicitRepresentation* childGridNonConstant = repo->createIjkGridExplicitRepresentation("eaf36330-4c0b-40f8-bf07-b2818f09a229", "Child grid irregular refinement", 4, 1, 4);
	unsigned int onetwo[2] = { 1,2 };
	unsigned int twothree[2] = { 1,2 };
	childGridNonConstant->setParentWindow(
		0, onetwo, oneone, 2,
		0, &one, &one, one,
		0, twothree, oneone, 2,
		parentGrid);

	// Put all LGRs in a single representation set representation for other testing
	auto rsr = repo->createRepresentationSetRepresentation("4526345b-3900-4b1a-a68d-7ea9fd824827", "RSR");
	childGrid->pushBackIntoRepresentationSet(rsr);
	childGridHdf5->pushBackIntoRepresentationSet(rsr);
	childGridNonConstant->pushBackIntoRepresentationSet(rsr);
	REQUIRE(childGrid->getRepresentationSetRepresentation(0)->getRepresentationCount() == 3);
}

void LgrOnRightHanded4x3x2ExplicitIjkGrid::readRepo() {
	// getting the childGrid
	RESQML2_NS::AbstractIjkGridRepresentation* childGrid = repo->getDataObjectByUuid<RESQML2_NS::AbstractIjkGridRepresentation>(defaultUuid);
	RESQML2_NS::AbstractIjkGridRepresentation* childGridHdf5 = repo->getDataObjectByUuid<RESQML2_NS::AbstractIjkGridRepresentation>("38930b30-1325-424e-a1e9-666fa50bfa4f");
	RESQML2_NS::AbstractIjkGridRepresentation* childGridNonConstant = repo->getDataObjectByUuid<RESQML2_NS::AbstractIjkGridRepresentation>("eaf36330-4c0b-40f8-bf07-b2818f09a229");
	RESQML2_NS::AbstractIjkGridRepresentation* parentGrid = repo->getDataObjectByUuid<RESQML2_NS::AbstractIjkGridRepresentation>(RightHanded4x3x2ExplicitIjkGrid::defaultUuid);

	REQUIRE(childGrid->getCellCount() == 12);
	REQUIRE(childGrid->getPillarCount() == 8);
	REQUIRE(childGrid->getParentGrid() == parentGrid);
	REQUIRE(childGridHdf5->getCellCount() == 12);
	REQUIRE(childGridHdf5->getPillarCount() == 8);
	REQUIRE(childGridHdf5->getParentGrid() == parentGrid);
	REQUIRE(childGridNonConstant->getCellCount() == 16);
	REQUIRE(childGridNonConstant->getPillarCount() == 10);
	REQUIRE(childGridNonConstant->getParentGrid() == parentGrid);
	REQUIRE(parentGrid->getChildGridCount() == 3);
	// Child
	REQUIRE(childGrid->isRegridCellCountPerIntervalConstant('i', true));
	REQUIRE(childGrid->isRegridCellCountPerIntervalConstant('j', true));
	REQUIRE(childGrid->isRegridCellCountPerIntervalConstant('k', true));
	REQUIRE(childGridHdf5->isRegridCellCountPerIntervalConstant('i', true));
	REQUIRE(childGridHdf5->isRegridCellCountPerIntervalConstant('j', true));
	REQUIRE(childGridHdf5->isRegridCellCountPerIntervalConstant('k', true));
	REQUIRE_FALSE(childGridNonConstant->isRegridCellCountPerIntervalConstant('i', true));
	REQUIRE(childGridNonConstant->isRegridCellCountPerIntervalConstant('j', true));
	REQUIRE_FALSE(childGridNonConstant->isRegridCellCountPerIntervalConstant('k', true));
	// Parent
	REQUIRE(childGrid->isRegridCellCountPerIntervalConstant('i', false));
	REQUIRE(childGrid->isRegridCellCountPerIntervalConstant('j', false));
	REQUIRE(childGrid->isRegridCellCountPerIntervalConstant('k', false));
	REQUIRE(childGridHdf5->isRegridCellCountPerIntervalConstant('i', false));
	REQUIRE(childGridHdf5->isRegridCellCountPerIntervalConstant('j', false));
	REQUIRE(childGridHdf5->isRegridCellCountPerIntervalConstant('k', false));
	REQUIRE(childGridNonConstant->isRegridCellCountPerIntervalConstant('i', false));
	REQUIRE(childGridNonConstant->isRegridCellCountPerIntervalConstant('j', false));
	REQUIRE(childGridNonConstant->isRegridCellCountPerIntervalConstant('k', false));
	// Child
	REQUIRE(childGrid->getRegridConstantCellCountPerInterval('i', true) == 3);
	REQUIRE(childGrid->getRegridConstantCellCountPerInterval('j', true) == 1);
	REQUIRE(childGrid->getRegridConstantCellCountPerInterval('k', true) == 2);
	REQUIRE(childGridHdf5->getRegridConstantCellCountPerInterval('i', true) == 3);
	REQUIRE(childGridHdf5->getRegridConstantCellCountPerInterval('j', true) == 1);
	REQUIRE(childGridHdf5->getRegridConstantCellCountPerInterval('k', true) == 2);
	REQUIRE(childGridNonConstant->getRegridConstantCellCountPerInterval('j', true) == 1);
	// Parent
	REQUIRE(childGrid->getRegridConstantCellCountPerInterval('i', false) == 1);
	REQUIRE(childGrid->getRegridConstantCellCountPerInterval('j', false) == 1);
	REQUIRE(childGrid->getRegridConstantCellCountPerInterval('k', false) == 1);
	REQUIRE(childGridHdf5->getRegridConstantCellCountPerInterval('i', false) == 1);
	REQUIRE(childGridHdf5->getRegridConstantCellCountPerInterval('j', false) == 1);
	REQUIRE(childGridHdf5->getRegridConstantCellCountPerInterval('k', false) == 1);
	REQUIRE(childGridNonConstant->getRegridConstantCellCountPerInterval('i', false) == 1);
	REQUIRE(childGridNonConstant->getRegridConstantCellCountPerInterval('j', false) == 1);
	REQUIRE(childGridNonConstant->getRegridConstantCellCountPerInterval('k', false) == 1);
	// Child
	REQUIRE_FALSE(childGrid->hasRegridChildCellWeights('i'));
	REQUIRE_FALSE(childGrid->hasRegridChildCellWeights('j'));
	REQUIRE_FALSE(childGrid->hasRegridChildCellWeights('k'));
	REQUIRE_FALSE(childGridHdf5->hasRegridChildCellWeights('i'));
	REQUIRE_FALSE(childGridHdf5->hasRegridChildCellWeights('j'));
	REQUIRE_FALSE(childGridHdf5->hasRegridChildCellWeights('k'));
	REQUIRE_FALSE(childGridNonConstant->hasRegridChildCellWeights('i'));
	REQUIRE_FALSE(childGridNonConstant->hasRegridChildCellWeights('j'));
	REQUIRE_FALSE(childGridNonConstant->hasRegridChildCellWeights('k'));

	// RSR
	REQUIRE(childGrid->getRepresentationSetRepresentationCount() == 1);
	REQUIRE(childGridHdf5->getRepresentationSetRepresentationCount() == 1);
	REQUIRE(childGridNonConstant->getRepresentationSetRepresentationCount() == 1);
	auto rsr = childGridHdf5->getRepresentationSetRepresentation(0);
	REQUIRE(childGrid->getRepresentationSetRepresentation(0) == rsr);
	REQUIRE(childGridNonConstant->getRepresentationSetRepresentation(0) == rsr);
	REQUIRE(rsr->isHomogeneous());
	REQUIRE(rsr->getRepresentationCount() == 3);
	REQUIRE(rsr->getRepresentation(0) == childGrid);
	REQUIRE(rsr->getRepresentation(1) == childGridHdf5);
	REQUIRE(rsr->getRepresentation(2) == childGridNonConstant);
}
