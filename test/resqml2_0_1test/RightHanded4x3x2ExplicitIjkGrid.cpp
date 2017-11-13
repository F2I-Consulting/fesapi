#include "resqml2_0_1test/RightHanded4x3x2ExplicitIjkGrid.h"

#include "catch.hpp"
#include "resqml2_0_1test/LocalDepth3dCrsTest.h"

#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2/GridConnectionSetRepresentation.h"
#include "resqml2_0_1/DiscreteProperty.h"
#include "resqml2_0_1/ContinuousProperty.h"

using namespace std;
using namespace common;
using namespace resqml2_0_1test;
using namespace resqml2;

const char* RightHanded4x3x2ExplicitIjkGrid::defaultUuid = "f274d3d8-80ff-4860-90fb-609716303887";
const char* RightHanded4x3x2ExplicitIjkGrid::defaultTitle = "Right Handed 4x3x2 Explicit Ijk Grid";
const ULONG64 RightHanded4x3x2ExplicitIjkGrid::nodesCountIjkGridRepresentation = 72;
double RightHanded4x3x2ExplicitIjkGrid::nodesIjkGridRepresentation[] = {
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

RightHanded4x3x2ExplicitIjkGrid::RightHanded4x3x2ExplicitIjkGrid(const string & epcDocPath)
	: AbstractIjkGridRepresentationTest(epcDocPath, defaultUuid, defaultTitle, nodesCountIjkGridRepresentation, nodesIjkGridRepresentation) {
}

RightHanded4x3x2ExplicitIjkGrid::RightHanded4x3x2ExplicitIjkGrid(EpcDocument * epcDoc, bool init)
	: AbstractIjkGridRepresentationTest(epcDoc, defaultUuid, defaultTitle, nodesCountIjkGridRepresentation, nodesIjkGridRepresentation) {
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void RightHanded4x3x2ExplicitIjkGrid::initEpcDocHandler() {
	// getting the local depth 3d crs
	LocalDepth3dCrsTest* crsTest = new LocalDepth3dCrsTest(this->epcDoc, true);
	resqml2_0_1::LocalDepth3dCrs* crs = epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::LocalDepth3dCrs>(LocalDepth3dCrsTest::defaultUuid);

	// getting the hdf proxy
	AbstractHdfProxy* hdfProxy = this->epcDoc->getHdfProxySet()[0];

	// creating the ijk grid
	resqml2_0_1::IjkGridExplicitRepresentation* ijkGrid = this->epcDoc->createIjkGridExplicitRepresentation(crs, uuid, title, 4, 3, 2);
	REQUIRE(ijkGrid != nullptr);
	unsigned int pillarOfCoordinateLine[4] = { 17, 12, 7, 2 };
	unsigned int splitCoordinateLineColumnCumulativeCount[4] = { 1, 3, 5, 6 };
	unsigned int splitCoordinateLineColumns[6] = { 10, 10, 6, 6, 2, 2 };
	ijkGrid->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml2__PillarShape__vertical, gsoap_resqml2_0_1::resqml2__KDirection__down, false, this->xyzPointsOfAllPatchesInGlobalCrs, hdfProxy,
		4, pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);

	// Enabling cell
	unsigned char enabledCells[24] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0
	};
	ijkGrid->setEnabledCells(enabledCells);

	// Grid connection set representation
	resqml2::GridConnectionSetRepresentation * gridConnSet432 = epcDoc->createGridConnectionSetRepresentation("a3d1462a-04e3-4374-921b-a4a1e9ba3ea3", "GridConnectionSetRepresentation");
	gridConnSet432->pushBackSupportingGridRepresentation(ijkGrid);
	ULONG64 cellConn432[30] = {
		1, 9999, 5, 9999, 9, 9999,
		1, 2, 5, 6, 9, 10,
		13, 2, 17, 6, 21, 10,
		13, 14, 17, 18, 21, 22,
		9999, 14, 9999, 18, 9999, 22
	};
	gridConnSet432->setCellIndexPairs(15, cellConn432, 9999, hdfProxy);
	int localFacePerCellIndexPairs432[30] = {
		3, 9999, 3, 9999, 3, 9999,
		3, 5, 3, 5, 3, 5,
		3, 5, 3, 5, 3, 5,
		3, 5, 3, 5, 3, 5,
		9999, 5, 9999, 5, 9999, 5
	};
	gridConnSet432->setLocalFacePerCellIndexPairs(15, localFacePerCellIndexPairs432, hdfProxy);

	// Discrete property
	resqml2_0_1::DiscreteProperty* discreteProp = epcDoc->createDiscreteProperty(ijkGrid, "0a8fb2aa-d1e1-4914-931c-e9e6bf2aabe5", "Cell index", 1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__cells, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__index);
	long discretePropValues[24] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
		12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23
	};
	discreteProp->pushBackLongHdf5Array3dOfValues(discretePropValues, 4, 3, 2, hdfProxy, -1);

	// Continuous property
	resqml2_0_1::ContinuousProperty* continuousProp = epcDoc->createContinuousProperty(ijkGrid, "de5a71cc-879d-4cda-8fb3-146c70539cf9", "Amplitude", 1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__cells, gsoap_resqml2_0_1::resqml2__ResqmlUom__Euc, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__amplitude);
	double continuousPropValues[24] = {
		0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
		1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.5, 1.4, 1.3, 1.2, 1.1, 1.0
	};
	continuousProp->pushBackDoubleHdf5Array3dOfValues(continuousPropValues, 4, 3, 2, hdfProxy);

	// cleaning
	delete crsTest;
}

void RightHanded4x3x2ExplicitIjkGrid::readEpcDocHandler() {
	// getting the subrep
	resqml2_0_1::IjkGridExplicitRepresentation* ijkGrid = epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::IjkGridExplicitRepresentation>(this->uuid);

	REQUIRE(ijkGrid->getCellCount() == 24);
	REQUIRE(ijkGrid->getPillarCount() == 20);
	REQUIRE(ijkGrid->getGridConnectionSetRepresentationCount() == 1);
	REQUIRE(ijkGrid->getGridConnectionSetRepresentation(0)->getUuid() == "a3d1462a-04e3-4374-921b-a4a1e9ba3ea3");
	REQUIRE(ijkGrid->getGridConnectionSetRepresentation(0)->getCellIndexPairCount() == 15);
	REQUIRE(ijkGrid->getGridConnectionSetRepresentation(0)->getSupportingGridRepresentation(0) == ijkGrid);
}