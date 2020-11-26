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
#include "OneTetrahedronUnstructuredGridRepresentationTest.h"
#include "../catch.hpp"
#include "LocalDepth3dCrsTest.h"
#include "resqml2/LocalDepth3dCrs.h"
#include "common/EpcDocument.h"
#include "eml2/AbstractHdfProxy.h"
#include "resqml2/UnstructuredGridRepresentation.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_test;
using namespace RESQML2_NS;

const char* OneTetrahedronUnstructuredGridRepresentationTest::defaultUuid = "6f1d493d-3da5-43ab-8f57-a508f9590eb8";
const char* OneTetrahedronUnstructuredGridRepresentationTest::defaultTitle = "One Tetrahedron Unstructured Grid Representation Test";
double OneTetrahedronUnstructuredGridRepresentationTest::nodes[] = { 0,0,300, 700,0,350, 0,150,300, 0,0,500 };

OneTetrahedronUnstructuredGridRepresentationTest::OneTetrahedronUnstructuredGridRepresentationTest(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void OneTetrahedronUnstructuredGridRepresentationTest::initRepo() {
	// creating the unstructured grid
	RESQML2_NS::UnstructuredGridRepresentation* tetraGrid = repo->createUnstructuredGridRepresentation(defaultUuid, defaultTitle, 1);
	REQUIRE(tetraGrid != nullptr);
	unsigned char faceRightHandness[4] = { 0, 0, 1, 1 };
	uint64_t faceIndicesPerCell[4] = { 0, 1, 2, 3 };
	uint64_t nodeIndicesPerCell[12] = { 0, 1, 2, 1, 2, 3, 0, 1, 3, 0, 2, 3 };
	tetraGrid->setTetrahedraOnlyGeometry(faceRightHandness, nodes, 4, 4, nullptr, faceIndicesPerCell, nodeIndicesPerCell);
}

void OneTetrahedronUnstructuredGridRepresentationTest::readRepo() {
	// getting the unstructured grid
	RESQML2_NS::UnstructuredGridRepresentation * unstructuredGrid = repo->getDataObjectByUuid<RESQML2_NS::UnstructuredGridRepresentation>(defaultUuid);

	// getXyzPointCountOfPatch
	REQUIRE_THROWS( unstructuredGrid->getXyzPointCountOfPatch(1));
	REQUIRE( unstructuredGrid->getXyzPointCountOfPatch(0) == 4);
	
	// getFaceIndicesOfCells
	uint64_t faceIndicesPerCell[4];
	unstructuredGrid->getFaceIndicesOfCells(faceIndicesPerCell);
	REQUIRE( faceIndicesPerCell[0] == 0 );
	REQUIRE( faceIndicesPerCell[1] == 1 );
	REQUIRE( faceIndicesPerCell[2] == 2 );
	REQUIRE( faceIndicesPerCell[3] == 3 );

	// getCumulativeFaceCountPerCell
	uint64_t cumulativeFaceCountPerCell[1];
	unstructuredGrid->getCumulativeFaceCountPerCell(cumulativeFaceCountPerCell);
	REQUIRE( cumulativeFaceCountPerCell[0] == 4 );

	// getFaceCountPerCell
	uint64_t faceCountPerCell[1];
	unstructuredGrid->getFaceCountPerCell(faceCountPerCell);
	REQUIRE( faceCountPerCell[0] == 4 );

	// isFaceCountOfCellsConstant
	REQUIRE( unstructuredGrid->isFaceCountOfCellsConstant() );

	// getConstantFaceCountOfCells
	REQUIRE( unstructuredGrid->getConstantFaceCountOfCells() == 4);

	// getNodeIndicesOfFaces
	uint64_t nodeIndicesPerCell[12];
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
	uint64_t cumulativeNodeCountPerFace[4];
	unstructuredGrid->getCumulativeNodeCountPerFace(cumulativeNodeCountPerFace);
	REQUIRE( cumulativeNodeCountPerFace[0] == 3 );
	REQUIRE( cumulativeNodeCountPerFace[1] == 6 );
	REQUIRE( cumulativeNodeCountPerFace[2] == 9 );
	REQUIRE( cumulativeNodeCountPerFace[3] == 12 );

	// getNodeCountPerFace
	uint64_t nodeCountPerFace[4];
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
	REQUIRE_THROWS_AS( unstructuredGrid->getFaceCountOfCell(0), logic_error);

	// loading geometry into memory (required for subsequent testing)
	unstructuredGrid->loadGeometry();

	// getFaceCountOfCell
	REQUIRE_THROWS_AS( unstructuredGrid->getFaceCountOfCell(1), out_of_range);
	REQUIRE( unstructuredGrid->getFaceCountOfCell(0) == 4 );

	// getNodeCountOfFaceOfCell
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(0, 0) == 3 );
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(0, 1) == 3 );
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(0, 2) == 3 );
	REQUIRE( unstructuredGrid->getNodeCountOfFaceOfCell(0, 3) == 3 );

	// getNodeIndicesOfFaceOfCell
	uint64_t const * nodeIndicesOfFirstFace = unstructuredGrid->getNodeIndicesOfFaceOfCell(0, 0);
	REQUIRE( nodeIndicesOfFirstFace[0] == 0 );
	REQUIRE( nodeIndicesOfFirstFace[1] == 1 );
	REQUIRE( nodeIndicesOfFirstFace[2] == 2 );
	uint64_t const* nodeIndicesOfSecondFace = unstructuredGrid->getNodeIndicesOfFaceOfCell(0, 1);
	REQUIRE( nodeIndicesOfSecondFace[0] == 1 );
	REQUIRE( nodeIndicesOfSecondFace[1] == 2 );
	REQUIRE( nodeIndicesOfSecondFace[2] == 3 );
	uint64_t const* nodeIndicesOfThirdFace = unstructuredGrid->getNodeIndicesOfFaceOfCell(0, 2);
	REQUIRE( nodeIndicesOfThirdFace[0] == 0 );
	REQUIRE( nodeIndicesOfThirdFace[1] == 1 );
	REQUIRE( nodeIndicesOfThirdFace[2] == 3 );
	uint64_t const* nodeIndicesOfFourthFace = unstructuredGrid->getNodeIndicesOfFaceOfCell(0, 3);
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
}
