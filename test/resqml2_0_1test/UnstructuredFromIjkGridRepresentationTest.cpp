#include "resqml2_0_1test/UnstructuredFromIjkGridRepresentationTest.h"

#include "catch.hpp"
#include "resqml2_0_1test/LocalDepth3dCrsTest.h"
#include "resqml2_0_1test/IjkGridExplicitRepresentationTest.h"

#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "EpcDocument.h"
#include "resqml2/AbstractHdfProxy.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/IjkGridExplicitRepresentation.h"

using namespace std;
using namespace common;
using namespace resqml2_0_1test;
using namespace resqml2;

const char* UnstructuredFromIjkGridRepresentationTest::defaultUuid = "e1a17651-7db6-43cf-ba47-17a839e9571f";
const char* UnstructuredFromIjkGridRepresentationTest::defaultTitle = "Unstructured Grid from IJK Grid Representation";

UnstructuredFromIjkGridRepresentationTest::UnstructuredFromIjkGridRepresentationTest(const string & epcDocPath)
	: UnstructuredGridRepresentationTest(epcDocPath, defaultUuid, defaultTitle, IjkGridExplicitRepresentationTest::nodesCountIjkGridRepresentation, IjkGridExplicitRepresentationTest::nodesIjkGridRepresentation) {
}

UnstructuredFromIjkGridRepresentationTest::UnstructuredFromIjkGridRepresentationTest(EpcDocument * epcDoc, bool init)
	: UnstructuredGridRepresentationTest(epcDoc, defaultUuid, defaultTitle, IjkGridExplicitRepresentationTest::nodesCountIjkGridRepresentation, IjkGridExplicitRepresentationTest::nodesIjkGridRepresentation) {
	if (init)
			this->initEpcDoc();
		else
			this->readEpcDoc();
}

void UnstructuredFromIjkGridRepresentationTest::initEpcDocHandler() {
	// creating an IJK grid
	IjkGridExplicitRepresentationTest * ijkGridTest = new IjkGridExplicitRepresentationTest(this->epcDoc, true);
	resqml2_0_1::IjkGridExplicitRepresentation * ijkGrid = static_cast<resqml2_0_1::IjkGridExplicitRepresentation *>(this->epcDoc->getResqmlAbstractObjectByUuid(IjkGridExplicitRepresentationTest::defaultUuid));

	// cloning the ijk grid into an unstructured one
	//ijkGrid->cloneToUnstructuredGridRepresentation(this->uuid, this->title);

	// cleaning
	delete ijkGridTest;
}

// remark: the deserialization of the origin ijk grid is not handled
void UnstructuredFromIjkGridRepresentationTest::readEpcDocHandler() {
	// reading the IJK grid
	IjkGridExplicitRepresentationTest * ijkGridTest = new IjkGridExplicitRepresentationTest(this->epcDoc, false);

	// getting the unstructured grid
	resqml2_0_1::UnstructuredGridRepresentation * unstructuredGrid = static_cast<resqml2_0_1::UnstructuredGridRepresentation*>(this->epcDoc->getResqmlAbstractObjectByUuid(uuid));

	// checking that unstructured and ijk grid refer the same interpretation
	resqml2_0_1::IjkGridExplicitRepresentation* ijkGrid = static_cast<resqml2_0_1::IjkGridExplicitRepresentation*>(epcDoc->getResqmlAbstractObjectByUuid(IjkGridExplicitRepresentationTest::defaultUuid));
	REQUIRE( unstructuredGrid->getInterpretation() == ijkGrid->getInterpretation() );

	// getXyzPointCountOfPatch
	REQUIRE_THROWS( unstructuredGrid->getXyzPointCountOfPatch(1) );
	REQUIRE( unstructuredGrid->getXyzPointCountOfPatch(0) == 16);

	// getFaceIndicesOfCells
	ULONG64 faceIndicesPerCell[12];
	unstructuredGrid->getFaceIndicesOfCells(faceIndicesPerCell);
	REQUIRE( faceIndicesPerCell[0] == 0 );
	REQUIRE( faceIndicesPerCell[1] == 1 );
	REQUIRE( faceIndicesPerCell[2] == 2 );
	REQUIRE( faceIndicesPerCell[3] == 3 );
	REQUIRE( faceIndicesPerCell[4] == 4 );
	REQUIRE( faceIndicesPerCell[5] == 5 );
	REQUIRE( faceIndicesPerCell[6] == 6 );
	REQUIRE( faceIndicesPerCell[7] == 7 );
	REQUIRE( faceIndicesPerCell[8] == 8 );
	REQUIRE( faceIndicesPerCell[9] == 9 );
	REQUIRE( faceIndicesPerCell[10] == 10 );
	REQUIRE( faceIndicesPerCell[11] == 11 );

	// getCumulativeFaceCountPerCell
	ULONG64 cumulativeFaceCountPerCell[2];
	unstructuredGrid->getCumulativeFaceCountPerCell(cumulativeFaceCountPerCell);
	REQUIRE( cumulativeFaceCountPerCell[0] == 6 );
	REQUIRE( cumulativeFaceCountPerCell[1] == 12 );

	// getFaceCountPerCell
	ULONG64 faceCountPerCell[2];
	unstructuredGrid->getFaceCountPerCell(faceCountPerCell);
	REQUIRE( faceCountPerCell[0] == 6 );
	REQUIRE( faceCountPerCell[1] == 6 );

	// isFaceCountOfCellsConstant
	REQUIRE( unstructuredGrid->isFaceCountOfCellsConstant() );

	// getConstantFaceCountOfCells
	REQUIRE( unstructuredGrid->getConstantFaceCountOfCells() == 6);

	// getNodeIndicesOfFaces
	ULONG64 nodeIndicesPerCell[48];
	unstructuredGrid->getNodeIndicesOfFaces(nodeIndicesPerCell);
	REQUIRE( nodeIndicesPerCell[0] == 8 );
	REQUIRE( nodeIndicesPerCell[1] == 9 );
	REQUIRE( nodeIndicesPerCell[2] == 12 );
	REQUIRE( nodeIndicesPerCell[3] == 11 );
	REQUIRE( nodeIndicesPerCell[4] == 0 );
	REQUIRE( nodeIndicesPerCell[5] == 1 );
	REQUIRE( nodeIndicesPerCell[6] == 4 );
	REQUIRE( nodeIndicesPerCell[7] == 3 );
	REQUIRE( nodeIndicesPerCell[8] == 0 );
	REQUIRE( nodeIndicesPerCell[9] == 8 );
	REQUIRE( nodeIndicesPerCell[10] == 9 );
	REQUIRE( nodeIndicesPerCell[11] == 1 );
	REQUIRE( nodeIndicesPerCell[12] == 1 );
	REQUIRE( nodeIndicesPerCell[13] == 4 );
	REQUIRE( nodeIndicesPerCell[14] == 12 );
	REQUIRE( nodeIndicesPerCell[15] == 9 );
	REQUIRE( nodeIndicesPerCell[16] == 3 );
	REQUIRE( nodeIndicesPerCell[17] == 11 );
	REQUIRE( nodeIndicesPerCell[18] == 12 );
	REQUIRE( nodeIndicesPerCell[19] == 4 );
	REQUIRE( nodeIndicesPerCell[20] == 0 );
	REQUIRE( nodeIndicesPerCell[21] == 3 );
	REQUIRE( nodeIndicesPerCell[22] == 11 );
	REQUIRE( nodeIndicesPerCell[23] == 8 );
	REQUIRE( nodeIndicesPerCell[24] == 14 );
	REQUIRE( nodeIndicesPerCell[25] == 10 );
	REQUIRE( nodeIndicesPerCell[26] == 13 );
	REQUIRE( nodeIndicesPerCell[27] == 15 );
	REQUIRE( nodeIndicesPerCell[28] == 6 );
	REQUIRE( nodeIndicesPerCell[29] == 2 );
	REQUIRE( nodeIndicesPerCell[30] == 5 );
	REQUIRE( nodeIndicesPerCell[31] == 7 );
	REQUIRE( nodeIndicesPerCell[32] == 6 );
	REQUIRE( nodeIndicesPerCell[33] == 14 );
	REQUIRE( nodeIndicesPerCell[34] == 10 );
	REQUIRE( nodeIndicesPerCell[35] == 2 );
	REQUIRE( nodeIndicesPerCell[36] == 2 );
	REQUIRE( nodeIndicesPerCell[37] == 5 );
	REQUIRE( nodeIndicesPerCell[38] == 13 );
	REQUIRE( nodeIndicesPerCell[39] == 10 );
	REQUIRE( nodeIndicesPerCell[40] == 7 );
	REQUIRE( nodeIndicesPerCell[41] == 15 );
	REQUIRE( nodeIndicesPerCell[42] == 13 );
	REQUIRE( nodeIndicesPerCell[43] == 5 );
	REQUIRE( nodeIndicesPerCell[44] == 6 );
	REQUIRE( nodeIndicesPerCell[45] == 7 );
	REQUIRE( nodeIndicesPerCell[46] == 15 );
	REQUIRE( nodeIndicesPerCell[47] == 14 );

	// getCumulativeNodeCountPerFace
	ULONG64 cumulativeNodeCountPerFace[12];
	unstructuredGrid->getCumulativeNodeCountPerFace(cumulativeNodeCountPerFace);
	REQUIRE( cumulativeNodeCountPerFace[0] == 4 );
	REQUIRE( cumulativeNodeCountPerFace[1] == 8 );
	REQUIRE( cumulativeNodeCountPerFace[2] == 12 );
	REQUIRE( cumulativeNodeCountPerFace[3] == 16 );
	REQUIRE( cumulativeNodeCountPerFace[4] == 20 );
	REQUIRE( cumulativeNodeCountPerFace[5] == 24 );
	REQUIRE( cumulativeNodeCountPerFace[6] == 28 );
	REQUIRE( cumulativeNodeCountPerFace[7] == 32 );
	REQUIRE( cumulativeNodeCountPerFace[8] == 36 );
	REQUIRE( cumulativeNodeCountPerFace[9] == 40 );
	REQUIRE( cumulativeNodeCountPerFace[10] == 44 );
	REQUIRE( cumulativeNodeCountPerFace[11] == 48 );

	// getNodeCountPerFace
	ULONG64 nodeCountPerFace[12];
	unstructuredGrid->getNodeCountPerFace(nodeCountPerFace);
	REQUIRE( nodeCountPerFace[0] == 4 );
	REQUIRE( nodeCountPerFace[1] == 4 );
	REQUIRE( nodeCountPerFace[2] == 4 );
	REQUIRE( nodeCountPerFace[3] == 4 );
	REQUIRE( nodeCountPerFace[4] == 4 );
	REQUIRE( nodeCountPerFace[5] == 4 );
	REQUIRE( nodeCountPerFace[6] == 4 );
	REQUIRE( nodeCountPerFace[7] == 4 );
	REQUIRE( nodeCountPerFace[8] == 4 );
	REQUIRE( nodeCountPerFace[9] == 4 );
	REQUIRE( nodeCountPerFace[10] == 4 );
	REQUIRE( nodeCountPerFace[11] == 4 );

	// isNodeCountOfFacesContant
	REQUIRE( unstructuredGrid->isNodeCountOfFacesConstant() );

	// getConstantNodeCountOfFaces
	REQUIRE( unstructuredGrid->getConstantNodeCountOfFaces() == 4 );

	// getFaceCountOfCell should raises en exception since geometry is not loaded
	REQUIRE_THROWS_AS( unstructuredGrid->getFaceCountOfCell(0), invalid_argument );

	// loading geometry into memory (required for subsequent testing)
	unstructuredGrid->loadGeometry();

	// getFaceCountOfCell
	REQUIRE_THROWS_AS( unstructuredGrid->getFaceCountOfCell(2), range_error );
	REQUIRE( unstructuredGrid->getFaceCountOfCell(0) == 6 );
	REQUIRE( unstructuredGrid->getFaceCountOfCell(1) == 6 );

	// getNodeCountOfFaceOfCell
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(0, 0) == 4 );
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(0, 1) == 4 );
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(0, 2) == 4 );
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(0, 3) == 4 );
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(0, 4) == 4 );
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(0, 5) == 4 );
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(1, 0) == 4 );
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(1, 1) == 4 );
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(1, 2) == 4 );
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(1, 3) == 4 );
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(1, 4) == 4 );
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(1, 5) == 4 );

	// getNodeIndicesOfFaceOfCell
	ULONG64* nodeIndicesOfFace0_0 = unstructuredGrid->getNodeIndicesOfFaceOfCell(0, 0);
	REQUIRE( nodeIndicesOfFace0_0[0] == 8 );
	REQUIRE( nodeIndicesOfFace0_0[1] == 9 );
	REQUIRE( nodeIndicesOfFace0_0[2] == 12 );
	REQUIRE( nodeIndicesOfFace0_0[3] == 11 );
	ULONG64* nodeIndicesOfFace0_1 = unstructuredGrid->getNodeIndicesOfFaceOfCell(0, 1);
	REQUIRE( nodeIndicesOfFace0_1[0] == 0 );
	REQUIRE( nodeIndicesOfFace0_1[1] == 1 );
	REQUIRE( nodeIndicesOfFace0_1[2] == 4 );
	REQUIRE( nodeIndicesOfFace0_1[3] == 3 );
	ULONG64* nodeIndicesOfFace0_2 = unstructuredGrid->getNodeIndicesOfFaceOfCell(0, 2);
	REQUIRE( nodeIndicesOfFace0_2[0] == 0 );
	REQUIRE( nodeIndicesOfFace0_2[1] == 8 );
	REQUIRE( nodeIndicesOfFace0_2[2] == 9 );
	REQUIRE( nodeIndicesOfFace0_2[3] == 1 );
	ULONG64* nodeIndicesOfFace0_3 = unstructuredGrid->getNodeIndicesOfFaceOfCell(0, 3);
	REQUIRE( nodeIndicesOfFace0_3[0] == 1 );
	REQUIRE( nodeIndicesOfFace0_3[1] == 4 );
	REQUIRE( nodeIndicesOfFace0_3[2] == 12 );
	REQUIRE( nodeIndicesOfFace0_3[3] == 9 );
	ULONG64* nodeIndicesOfFace0_4 = unstructuredGrid->getNodeIndicesOfFaceOfCell(0, 4);
	REQUIRE( nodeIndicesOfFace0_4[0] == 3 );
	REQUIRE( nodeIndicesOfFace0_4[1] == 11 );
	REQUIRE( nodeIndicesOfFace0_4[2] == 12 );
	REQUIRE( nodeIndicesOfFace0_4[3] == 4 );
	ULONG64* nodeIndicesOfFace0_5 = unstructuredGrid->getNodeIndicesOfFaceOfCell(0, 5);
	REQUIRE( nodeIndicesOfFace0_5[0] == 0 );
	REQUIRE( nodeIndicesOfFace0_5[1] == 3 );
	REQUIRE( nodeIndicesOfFace0_5[2] == 11 );
	REQUIRE( nodeIndicesOfFace0_5[3] == 8 );
	ULONG64* nodeIndicesOfFace1_0 = unstructuredGrid->getNodeIndicesOfFaceOfCell(1, 0);
	REQUIRE( nodeIndicesOfFace1_0[0] == 14 );
	REQUIRE( nodeIndicesOfFace1_0[1] == 10 );
	REQUIRE( nodeIndicesOfFace1_0[2] == 13 );
	REQUIRE( nodeIndicesOfFace1_0[3] == 15 );
	ULONG64* nodeIndicesOfFace1_1 = unstructuredGrid->getNodeIndicesOfFaceOfCell(1, 1);
	REQUIRE( nodeIndicesOfFace1_1[0] == 6 );
	REQUIRE( nodeIndicesOfFace1_1[1] == 2 );
	REQUIRE( nodeIndicesOfFace1_1[2] == 5 );
	REQUIRE( nodeIndicesOfFace1_1[3] == 7 );
	ULONG64* nodeIndicesOfFace1_2 = unstructuredGrid->getNodeIndicesOfFaceOfCell(1, 2);
	REQUIRE( nodeIndicesOfFace1_2[0] == 6 );
	REQUIRE( nodeIndicesOfFace1_2[1] == 14 );
	REQUIRE( nodeIndicesOfFace1_2[2] == 10 );
	REQUIRE( nodeIndicesOfFace1_2[3] == 2 );
	ULONG64* nodeIndicesOfFace1_3 = unstructuredGrid->getNodeIndicesOfFaceOfCell(1, 3);
	REQUIRE( nodeIndicesOfFace1_3[0] == 2 );
	REQUIRE( nodeIndicesOfFace1_3[1] == 5 );
	REQUIRE( nodeIndicesOfFace1_3[2] == 13 );
	REQUIRE( nodeIndicesOfFace1_3[3] == 10 );
	ULONG64* nodeIndicesOfFace1_4 = unstructuredGrid->getNodeIndicesOfFaceOfCell(1, 4);
	REQUIRE( nodeIndicesOfFace1_4[0] == 7 );
	REQUIRE( nodeIndicesOfFace1_4[1] == 15 );
	REQUIRE( nodeIndicesOfFace1_4[2] == 13 );
	REQUIRE( nodeIndicesOfFace1_4[3] == 5 );
	ULONG64* nodeIndicesOfFace1_5 = unstructuredGrid->getNodeIndicesOfFaceOfCell(1, 5);
	REQUIRE( nodeIndicesOfFace1_5[0] == 6 );
	REQUIRE( nodeIndicesOfFace1_5[1] == 7 );
	REQUIRE( nodeIndicesOfFace1_5[2] == 15 );
	REQUIRE( nodeIndicesOfFace1_5[3] == 14 );
	
	// getCellCount
	REQUIRE( unstructuredGrid->getCellCount() == 2);

	// getFaceCount
	REQUIRE( unstructuredGrid->getFaceCount() == 12);

	// getNodeCount
	REQUIRE( unstructuredGrid->getNodeCount() == 16);

	// getCellFaceIsRightHanded
	// TODO: getCellFaceIsRightHanded does not seem to be implemented, always false?
	/*char cellfaceisrighthanded[2];
	unstructuredgrid->getcellfaceisrighthanded(cellfaceisrighthanded);*/

	// unloading geometry
	unstructuredGrid->unloadGeometry();

	// getPatchCount
	REQUIRE( unstructuredGrid->getPatchCount() == 1);

	// cleaning
	delete ijkGridTest;
}