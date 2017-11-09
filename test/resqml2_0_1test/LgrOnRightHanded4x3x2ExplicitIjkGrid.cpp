#include "resqml2_0_1test/LgrOnRightHanded4x3x2ExplicitIjkGrid.h"

#include <stdexcept>

#include "resqml2_0_1test/AbstractIjkGridRepresentationTest.h"
#include "resqml2_0_1test/RightHanded4x3x2ExplicitIjkGrid.h"
#include "resqml2_0_1test/LocalDepth3dCrsTest.h"

#include "catch.hpp"
#include "EpcDocument.h"
#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2_0_1/DiscreteProperty.h"
#include "resqml2_0_1/ContinuousProperty.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2;

const char* LgrOnRightHanded4x3x2ExplicitIjkGrid::defaultUuid = "11852778-139e-4fa3-bb34-70c4014553f7";
const char* LgrOnRightHanded4x3x2ExplicitIjkGrid::defaultTitle = "LGR";
const ULONG64 LgrOnRightHanded4x3x2ExplicitIjkGrid::nodesCountIjkGridRepresentation = 40;
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

LgrOnRightHanded4x3x2ExplicitIjkGrid::LgrOnRightHanded4x3x2ExplicitIjkGrid(const string & epcDocPath)
	: AbstractIjkGridRepresentationTest(epcDocPath, defaultUuid, defaultTitle, nodesCountIjkGridRepresentation, nodesIjkGridRepresentation) {
}

LgrOnRightHanded4x3x2ExplicitIjkGrid::LgrOnRightHanded4x3x2ExplicitIjkGrid(EpcDocument* epcDoc, bool init)
	: AbstractIjkGridRepresentationTest(epcDoc, defaultUuid, defaultTitle, nodesCountIjkGridRepresentation, nodesIjkGridRepresentation) {
	if (init) {
		this->initEpcDoc();
	}
	else {
		this->readEpcDoc();
	}
}

void LgrOnRightHanded4x3x2ExplicitIjkGrid::initEpcDocHandler() {
	// getting the parent grid
	RightHanded4x3x2ExplicitIjkGrid* parentGridTest = new RightHanded4x3x2ExplicitIjkGrid(this->epcDoc, true);

	resqml2_0_1::IjkGridExplicitRepresentation* parentGrid = epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::IjkGridExplicitRepresentation>(RightHanded4x3x2ExplicitIjkGrid::defaultUuid);
	resqml2_0_1::LocalDepth3dCrs* crs = epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::LocalDepth3dCrs>(LocalDepth3dCrsTest::defaultUuid);

	// cleaning
	delete parentGridTest;

	// getting the hdf proxy
	AbstractHdfProxy* hdfProxy = this->epcDoc->getHdfProxySet()[0];

	// creating the child ijk grid
	resqml2_0_1::IjkGridExplicitRepresentation* childGrid = epcDoc->createIjkGridExplicitRepresentation(crs, uuid, title, 3, 1, 4);
	childGrid->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml2__PillarShape__vertical, gsoap_resqml2_0_1::resqml2__KDirection__down, false, xyzPointsOfAllPatchesInGlobalCrs, hdfProxy);
	childGrid->setParentWindow(
		0, 3, 1, 1,
		0, 1, 1, 1,
		0, 2, 1, 2,
		parentGrid);

	// Discrete Property
	resqml2_0_1::DiscreteProperty* discreteProp = epcDoc->createDiscreteProperty(childGrid, "65169116-4330-4a88-b698-f127454a7106", "Cell index", 1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__cells, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__index);
	long discretePropValues[12] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
	};
	discreteProp->pushBackLongHdf5Array3dOfValues(discretePropValues, 3, 1, 4, hdfProxy, -1);

	// Continuous property
	resqml2_0_1::ContinuousProperty* continuousProp = epcDoc->createContinuousProperty(childGrid, "a8e1720e-2b58-4329-9317-534bf8abca29", "Amplitude", 1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__cells, gsoap_resqml2_0_1::resqml2__ResqmlUom__Euc, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__amplitude);
	double continuousPropValues[12] = {
		0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0
	};
	continuousProp->pushBackDoubleHdf5Array3dOfValues(continuousPropValues, 3, 1, 4, hdfProxy);
}

void LgrOnRightHanded4x3x2ExplicitIjkGrid::readEpcDocHandler() {
	RightHanded4x3x2ExplicitIjkGrid* parentGridTest = new RightHanded4x3x2ExplicitIjkGrid(this->epcDoc, false);

	// getting the childGrid
	resqml2_0_1::IjkGridExplicitRepresentation* childGrid = epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::IjkGridExplicitRepresentation>(uuid);
	resqml2_0_1::IjkGridExplicitRepresentation* parentGrid = epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::IjkGridExplicitRepresentation>(RightHanded4x3x2ExplicitIjkGrid::defaultUuid);

	REQUIRE(childGrid->getCellCount() == 12);
	REQUIRE(childGrid->getPillarCount() == 8);
	REQUIRE(parentGrid->getChildGridCount() == 1);
	REQUIRE(childGrid->getParentGrid() == parentGrid);
	// Child
	REQUIRE(childGrid->isRegridCellCountPerIntervalConstant('i', true));
	REQUIRE(childGrid->isRegridCellCountPerIntervalConstant('j', true));
	REQUIRE(childGrid->isRegridCellCountPerIntervalConstant('k', true));
	// Parent
	REQUIRE(childGrid->isRegridCellCountPerIntervalConstant('i', false));
	REQUIRE(childGrid->isRegridCellCountPerIntervalConstant('j', false));
	REQUIRE(childGrid->isRegridCellCountPerIntervalConstant('k', false));
	// Child
	REQUIRE(childGrid->getRegridConstantCellCountPerInterval('i', true) == 3);
	REQUIRE(childGrid->getRegridConstantCellCountPerInterval('j', true) == 1);
	REQUIRE(childGrid->getRegridConstantCellCountPerInterval('k', true) == 2);
	// Parent
	REQUIRE(childGrid->getRegridConstantCellCountPerInterval('i', false) == 1);
	REQUIRE(childGrid->getRegridConstantCellCountPerInterval('j', false) == 1);
	REQUIRE(childGrid->getRegridConstantCellCountPerInterval('k', false) == 1);
}