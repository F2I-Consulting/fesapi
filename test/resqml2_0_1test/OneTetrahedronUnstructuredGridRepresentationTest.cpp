#include "OneTetrahedronUnstructuredGridRepresentationTest.h"
#include "../config.h"
#include "../catch.hpp"
#include "LocalDepth3dCrsTest.h"
#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "EpcDocument.h"
#include "resqml2/AbstractHdfProxy.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"

using namespace std;
using namespace common;
using namespace resqml2_0_1test;
using namespace resqml2;

OneTetrahedronUnstructuredGridRepresentationTest::OneTetrahedronUnstructuredGridRepresentationTest(const string & epcDocPath)
	: UnstructuredGridRepresentationTest(epcDocPath, uuidOneTetrahedronUnstructuredGridRepresentation, titleOneTetrahedronUnstructuredGridRepresentation, nodesCountOneTetrahedronUnstructuredGridRepresentation, nodesOneTetrahedronUnstructuredGridRepresentation) {
}

OneTetrahedronUnstructuredGridRepresentationTest::OneTetrahedronUnstructuredGridRepresentationTest(EpcDocument * epcDoc, bool init)
	: UnstructuredGridRepresentationTest(epcDoc, uuidOneTetrahedronUnstructuredGridRepresentation, titleOneTetrahedronUnstructuredGridRepresentation, nodesCountOneTetrahedronUnstructuredGridRepresentation, nodesOneTetrahedronUnstructuredGridRepresentation) {
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void OneTetrahedronUnstructuredGridRepresentationTest::initEpcDocHandler() {
	// getting the local depth 3d crs
	LocalDepth3dCrsTest* crsTest = new LocalDepth3dCrsTest(this->epcDoc, true);
	resqml2_0_1::LocalDepth3dCrs* crs = static_cast<resqml2_0_1::LocalDepth3dCrs*>(this->epcDoc->getResqmlAbstractObjectByUuid(LocalDepth3dCrsTest::defaultUuid));

	// getting the hdf proxy
	AbstractHdfProxy* hdfProxy = this->epcDoc->getHdfProxySet()[0];

	// creating the unstructured grid
	resqml2_0_1::UnstructuredGridRepresentation* tetraGrid = this->epcDoc->createUnstructuredGridRepresentation(crs, this->uuid, this->title, 1);
	REQUIRE(tetraGrid != nullptr);
	unsigned char faceRightHandness[4] = { 0, 0, 1, 1 };
	ULONG64 faceIndicesPerCell[4] = { 0, 1, 2, 3 };
	ULONG64 nodeIndicesPerCell[12] = { 0, 1, 2, 1, 2, 3, 0, 1, 3, 0, 2, 3 };
	tetraGrid->setTetrahedraOnlyGeometry(faceRightHandness, this->xyzPointsOfAllPatchesInGlobalCrs, 4, 4, hdfProxy, faceIndicesPerCell, nodeIndicesPerCell);

	// cleaning
	delete crsTest;
}

void OneTetrahedronUnstructuredGridRepresentationTest::readEpcDocHandler() {
	// reading the local depth 3d crs
	LocalDepth3dCrsTest* crsTest = new LocalDepth3dCrsTest(this->epcDoc, false);

	// getting the unstructured grid
	resqml2_0_1::UnstructuredGridRepresentation * unstructuredGrid = static_cast<resqml2_0_1::UnstructuredGridRepresentation*>(this->epcDoc->getResqmlAbstractObjectByUuid(uuidOneTetrahedronUnstructuredGridRepresentation));
	
	// getHdfProxyUuid
	REQUIRE( unstructuredGrid->getHdfProxyUuid() == uuidHdfProxy);

	// getXyzPointCountOfPatch
	REQUIRE_THROWS( unstructuredGrid->getXyzPointCountOfPatch(1));
	REQUIRE( unstructuredGrid->getXyzPointCountOfPatch(0) == 4);
	
	// getFaceIndicesOfCells
	ULONG64 faceIndicesPerCell[4];
	unstructuredGrid->getFaceIndicesOfCells(faceIndicesPerCell);
	REQUIRE( faceIndicesPerCell[0] == 0 );
	REQUIRE( faceIndicesPerCell[1] == 1 );
	REQUIRE( faceIndicesPerCell[2] == 2 );
	REQUIRE( faceIndicesPerCell[3] == 3 );

	// getCumulativeFaceCountPerCell
	ULONG64 cumulativeFaceCountPerCell[1];
	unstructuredGrid->getCumulativeFaceCountPerCell(cumulativeFaceCountPerCell);
	REQUIRE( cumulativeFaceCountPerCell[0] == 4 );

	// getFaceCountPerCell
	ULONG64 faceCountPerCell[1];
	unstructuredGrid->getFaceCountPerCell(faceCountPerCell);
	REQUIRE( faceCountPerCell[0] == 4 );

	// isFaceCountOfCellsConstant
	REQUIRE( unstructuredGrid->isFaceCountOfCellsConstant() );

	// getConstantFaceCountOfCells
	REQUIRE( unstructuredGrid->getConstantFaceCountOfCells() == 4);

	// getNodeIndicesOfFaces
	ULONG64 nodeIndicesPerCell[12];
	unstructuredGrid->getNodeIndicesOfFaces(nodeIndicesPerCell);
	REQUIRE( nodeIndicesPerCell[0] == 0 );
	REQUIRE( nodeIndicesPerCell[1] == 1 );
	REQUIRE( nodeIndicesPerCell[2] == 2 );
	REQUIRE( nodeIndicesPerCell[3] == 1 );
	REQUIRE( nodeIndicesPerCell[4] == 2 );
	REQUIRE( nodeIndicesPerCell[5] == 3 );
	REQUIRE( nodeIndicesPerCell[6] == 0 );
	REQUIRE( nodeIndicesPerCell[7] == 1 );
	REQUIRE( nodeIndicesPerCell[8] == 3 );
	REQUIRE( nodeIndicesPerCell[9] == 0 );
	REQUIRE( nodeIndicesPerCell[10] == 2 );
	REQUIRE( nodeIndicesPerCell[11] == 3 );

	// getCumulativeNodeCountPerFace
	ULONG64 cumulativeNodeCountPerFace[4];
	unstructuredGrid->getCumulativeNodeCountPerFace(cumulativeNodeCountPerFace);
	REQUIRE( cumulativeNodeCountPerFace[0] == 3 );
	REQUIRE( cumulativeNodeCountPerFace[1] == 6 );
	REQUIRE( cumulativeNodeCountPerFace[2] == 9 );
	REQUIRE( cumulativeNodeCountPerFace[3] == 12 );

	// getNodeCountPerFace
	ULONG64 nodeCountPerFace[4];
	unstructuredGrid->getNodeCountPerFace(nodeCountPerFace);
	REQUIRE( nodeCountPerFace[0] == 3 );
	REQUIRE( nodeCountPerFace[1] == 3 );
	REQUIRE( nodeCountPerFace[2] == 3 );
	REQUIRE( nodeCountPerFace[3] == 3 );

	// isNodeCountOfFacesContant
	REQUIRE( unstructuredGrid->isNodeCountOfFacesConstant() );

	// getConstantNodeCountOfFaces
	REQUIRE( unstructuredGrid->getConstantNodeCountOfFaces() == 3 );

	// getFaceCountOfCell should raises en exception since geometry is not loaded
	REQUIRE_THROWS_AS( unstructuredGrid->getFaceCountOfCell(0), invalid_argument );

	// loading geometry into memory (required for subsequent testing)
	unstructuredGrid->loadGeometry();

	// getFaceCountOfCell
	REQUIRE_THROWS_AS( unstructuredGrid->getFaceCountOfCell(1), range_error );
	REQUIRE( unstructuredGrid->getFaceCountOfCell(0) == 4 );

	// getNodeCountOfFaceOfCell
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(0, 0) == 3 );
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(0, 1) == 3 );
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(0, 2) == 3 );
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(0, 3) == 3 );

	// getNodeIndicesOfFaceOfCell
	ULONG64* nodeIndicesOfFirstFace = unstructuredGrid->getNodeIndicesOfFaceOfCell(0, 0);
	REQUIRE( nodeIndicesOfFirstFace[0] == 0 );
	REQUIRE( nodeIndicesOfFirstFace[1] == 1 );
	REQUIRE( nodeIndicesOfFirstFace[2] == 2 );
	ULONG64* nodeIndicesOfSecondFace = unstructuredGrid->getNodeIndicesOfFaceOfCell(0, 1);
	REQUIRE( nodeIndicesOfSecondFace[0] == 1 );
	REQUIRE( nodeIndicesOfSecondFace[1] == 2 );
	REQUIRE( nodeIndicesOfSecondFace[2] == 3 );
	ULONG64* nodeIndicesOfThirdFace = unstructuredGrid->getNodeIndicesOfFaceOfCell(0, 2);
	REQUIRE( nodeIndicesOfThirdFace[0] == 0 );
	REQUIRE( nodeIndicesOfThirdFace[1] == 1 );
	REQUIRE( nodeIndicesOfThirdFace[2] == 3 );
	ULONG64* nodeIndicesOfFourthFace = unstructuredGrid->getNodeIndicesOfFaceOfCell(0, 3);
	REQUIRE( nodeIndicesOfFourthFace[0] == 0 );
	REQUIRE( nodeIndicesOfFourthFace[1] == 2 );
	REQUIRE( nodeIndicesOfFourthFace[2] == 3 );

	// getCellCount
	REQUIRE( unstructuredGrid->getCellCount() == 1);

	// getFaceCount
	REQUIRE( unstructuredGrid->getFaceCount() == 4);

	// getNodeCount
	REQUIRE( unstructuredGrid->getNodeCount() == 4);

	// TODO: not able to test since method is not yet implemented
	//unstructuredGrid->getCellFaceIsRightHanded(cellFaceIsRightHanded);

	// unloading geometry
	unstructuredGrid->unloadGeometry();

	// getPatchCount
	REQUIRE( unstructuredGrid->getPatchCount() == 1);

	// cleaning
	delete crsTest;
}