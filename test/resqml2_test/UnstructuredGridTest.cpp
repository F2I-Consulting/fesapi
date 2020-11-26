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
#include "UnstructuredGridTest.h"

#include "../catch.hpp"
#include "resqml2/UnstructuredGridRepresentation.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_test;

const char* UnstructuredGridTest::defaultUuid = "6f1d493d-3da5-43ab-8f57-a508f9590eb8";
const char* UnstructuredGridTest::defaultTitle = "One tetrahedron plus prism grid";
double UnstructuredGridTest::nodes[] = { 0, 0, 300, 375, 0, 300, 0, 150, 300, // points for shared face between tetra and wedge
		0, 0, 500, // point for tetra
		0, 0, 0, 375, 0, 0, 0, 150, 0 }; // points for wedge

UnstructuredGridTest::UnstructuredGridTest(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void UnstructuredGridTest::initRepo() {
	// creating the unstructured grid
	RESQML2_NS::UnstructuredGridRepresentation* unstructuredGrid = repo->createUnstructuredGridRepresentation(defaultUuid, defaultTitle, 2);
	REQUIRE(unstructuredGrid != nullptr);
	
	// The point indices of each face.
	uint64_t nodeIndicesPerFace[27] = { 0, 1, 2, // shared face
		1, 2, 3, 0, 1, 3, 0, 2, 3, // faces for tetra
		0, 2, 6, 4, 2, 1, 5, 6, 0, 1, 5, 4, 4, 5, 6 //  faces for wedge
	};
	// The cumulative count of points per face i.e. first face contains 3 points, second face contains 6-3=3 points, third face contains 9-6=3 points etc...
	uint64_t nodeIndicesCumulativeCountPerFace[8] = { 3, // shared face
		6, 9, 12, // faces for tetra
		16, 20, 24, 27 //  faces for wedge
	};
	// The face indices of each cell. 
	uint64_t faceIndicesPerCell[9] = { 0, 1, 2, 3, // tetra
		0, 4, 5, 6, 7 }; //wedge
	uint64_t faceIndicesCumulativeCountPerCell[2] = { 4, 9 };
	// Exporting the right handness of each face of each cell is mandatory. However, it is often ignored by the readers. Dummy values
	unsigned char faceRightHandness[9] = { 0, 0, 1, 1, 1, 0, 1, 0, 0 };

	unstructuredGrid->setGeometry(faceRightHandness, nodes, 7, nullptr, faceIndicesPerCell, faceIndicesCumulativeCountPerCell, 8, nodeIndicesPerFace, nodeIndicesCumulativeCountPerFace,
		gsoap_resqml2_0_1::resqml20__CellShape__prism);
}

void UnstructuredGridTest::readRepo() {
	// getting the unstructured grid
	RESQML2_NS::UnstructuredGridRepresentation * unstructuredGrid = repo->getDataObjectByUuid<RESQML2_NS::UnstructuredGridRepresentation>(defaultUuid);

	// getXyzPointCountOfPatch
	REQUIRE_THROWS(unstructuredGrid->getXyzPointCountOfPatch(1));
	REQUIRE(unstructuredGrid->getXyzPointCountOfPatch(0) == 7);

	// getFaceIndicesOfCells
	uint64_t faceIndicesPerCell[9];
	unstructuredGrid->getFaceIndicesOfCells(faceIndicesPerCell);
	REQUIRE(faceIndicesPerCell[0] == 0);
	REQUIRE(faceIndicesPerCell[1] == 1);
	REQUIRE(faceIndicesPerCell[2] == 2);
	REQUIRE(faceIndicesPerCell[3] == 3);
	REQUIRE(faceIndicesPerCell[4] == 0);
	REQUIRE(faceIndicesPerCell[5] == 4);
	REQUIRE(faceIndicesPerCell[6] == 5);
	REQUIRE(faceIndicesPerCell[7] == 6);
	REQUIRE(faceIndicesPerCell[8] == 7);

	// getCumulativeFaceCountPerCell
	uint64_t cumulativeFaceCountPerCell[2];
	unstructuredGrid->getCumulativeFaceCountPerCell(cumulativeFaceCountPerCell);
	REQUIRE(cumulativeFaceCountPerCell[0] == 4);
	REQUIRE(cumulativeFaceCountPerCell[1] == 9);

	// getFaceCountPerCell
	uint64_t faceCountPerCell[2];
	unstructuredGrid->getFaceCountPerCell(faceCountPerCell);
	REQUIRE(faceCountPerCell[0] == 4);
	REQUIRE(faceCountPerCell[1] == 5);

	// isFaceCountOfCellsConstant
	REQUIRE(!unstructuredGrid->isFaceCountOfCellsConstant());

	// getConstantFaceCountOfCells
	REQUIRE_THROWS(unstructuredGrid->getConstantFaceCountOfCells() == 4);

	// getNodeIndicesOfFaces
	uint64_t nodeIndicesPerFace[27];
	unstructuredGrid->getNodeIndicesOfFaces(nodeIndicesPerFace);
	REQUIRE(nodeIndicesPerFace[0] == 0);
	REQUIRE(nodeIndicesPerFace[1] == 1);
	REQUIRE(nodeIndicesPerFace[2] == 2);
	REQUIRE(nodeIndicesPerFace[3] == 1);
	REQUIRE(nodeIndicesPerFace[4] == 2);
	REQUIRE(nodeIndicesPerFace[5] == 3);
	REQUIRE(nodeIndicesPerFace[6] == 0);
	REQUIRE(nodeIndicesPerFace[7] == 1);
	REQUIRE(nodeIndicesPerFace[8] == 3);
	REQUIRE(nodeIndicesPerFace[9] == 0);
	REQUIRE(nodeIndicesPerFace[10] == 2);
	REQUIRE(nodeIndicesPerFace[11] == 3);
	REQUIRE(nodeIndicesPerFace[12] == 0);
	REQUIRE(nodeIndicesPerFace[13] == 2);
	REQUIRE(nodeIndicesPerFace[14] == 6);
	REQUIRE(nodeIndicesPerFace[15] == 4);
	REQUIRE(nodeIndicesPerFace[16] == 2);
	REQUIRE(nodeIndicesPerFace[17] == 1);
	REQUIRE(nodeIndicesPerFace[18] == 5);
	REQUIRE(nodeIndicesPerFace[19] == 6);
	REQUIRE(nodeIndicesPerFace[20] == 0);
	REQUIRE(nodeIndicesPerFace[21] == 1);
	REQUIRE(nodeIndicesPerFace[22] == 5);
	REQUIRE(nodeIndicesPerFace[23] == 4);
	REQUIRE(nodeIndicesPerFace[24] == 4);
	REQUIRE(nodeIndicesPerFace[25] == 5);
	REQUIRE(nodeIndicesPerFace[26] == 6);

	// getCumulativeNodeCountPerFace
	uint64_t cumulativeNodeCountPerFace[8];
	unstructuredGrid->getCumulativeNodeCountPerFace(cumulativeNodeCountPerFace);
	REQUIRE(cumulativeNodeCountPerFace[0] == 3);
	REQUIRE(cumulativeNodeCountPerFace[1] == 6);
	REQUIRE(cumulativeNodeCountPerFace[2] == 9);
	REQUIRE(cumulativeNodeCountPerFace[3] == 12);
	REQUIRE(cumulativeNodeCountPerFace[4] == 16);
	REQUIRE(cumulativeNodeCountPerFace[5] == 20);
	REQUIRE(cumulativeNodeCountPerFace[6] == 24);
	REQUIRE(cumulativeNodeCountPerFace[7] == 27);

	// getNodeCountPerFace
	uint64_t nodeCountPerFace[8];
	unstructuredGrid->getNodeCountPerFace(nodeCountPerFace);
	REQUIRE(nodeCountPerFace[0] == 3);
	REQUIRE(nodeCountPerFace[1] == 3);
	REQUIRE(nodeCountPerFace[2] == 3);
	REQUIRE(nodeCountPerFace[3] == 3);
	REQUIRE(nodeCountPerFace[4] == 4);
	REQUIRE(nodeCountPerFace[5] == 4);
	REQUIRE(nodeCountPerFace[6] == 4);
	REQUIRE(nodeCountPerFace[7] == 3);

	// isNodeCountOfFacesContant
	REQUIRE(!unstructuredGrid->isNodeCountOfFacesConstant());

	// getConstantNodeCountOfFaces
	REQUIRE_THROWS(unstructuredGrid->getConstantNodeCountOfFaces() == 3);

	// getFaceCountOfCell should raises en exception since geometry is not loaded
	REQUIRE_THROWS_AS(unstructuredGrid->getFaceCountOfCell(0), logic_error);

	// loading geometry into memory (required for subsequent testing)
	unstructuredGrid->loadGeometry();

	// getFaceCountOfCell
	REQUIRE_THROWS_AS(unstructuredGrid->getFaceCountOfCell(2), out_of_range);
	REQUIRE(unstructuredGrid->getFaceCountOfCell(0) == 4);
	REQUIRE(unstructuredGrid->getFaceCountOfCell(1) == 5);

	// getNodeCountOfFaceOfCell
	REQUIRE(unstructuredGrid->getNodeCountOfFaceOfCell(0, 0) == 3);
	REQUIRE(unstructuredGrid->getNodeCountOfFaceOfCell(0, 1) == 3);
	REQUIRE(unstructuredGrid->getNodeCountOfFaceOfCell(0, 2) == 3);
	REQUIRE(unstructuredGrid->getNodeCountOfFaceOfCell(0, 3) == 3);
	REQUIRE(unstructuredGrid->getNodeCountOfFaceOfCell(1, 0) == 3);
	REQUIRE(unstructuredGrid->getNodeCountOfFaceOfCell(1, 1) == 4);
	REQUIRE(unstructuredGrid->getNodeCountOfFaceOfCell(1, 2) == 4);
	REQUIRE(unstructuredGrid->getNodeCountOfFaceOfCell(1, 3) == 4);
	REQUIRE(unstructuredGrid->getNodeCountOfFaceOfCell(1, 4) == 3);

	// getNodeIndicesOfFaceOfCell
	uint64_t const* nodeIndicesOfFirstFace = unstructuredGrid->getNodeIndicesOfFaceOfCell(0, 0);
	REQUIRE(nodeIndicesOfFirstFace[0] == 0);
	REQUIRE(nodeIndicesOfFirstFace[1] == 1);
	REQUIRE(nodeIndicesOfFirstFace[2] == 2);
	uint64_t const* nodeIndicesOfSecondFace = unstructuredGrid->getNodeIndicesOfFaceOfCell(0, 1);
	REQUIRE(nodeIndicesOfSecondFace[0] == 1);
	REQUIRE(nodeIndicesOfSecondFace[1] == 2);
	REQUIRE(nodeIndicesOfSecondFace[2] == 3);
	uint64_t const* nodeIndicesOfThirdFace = unstructuredGrid->getNodeIndicesOfFaceOfCell(0, 2);
	REQUIRE(nodeIndicesOfThirdFace[0] == 0);
	REQUIRE(nodeIndicesOfThirdFace[1] == 1);
	REQUIRE(nodeIndicesOfThirdFace[2] == 3);
	uint64_t const* nodeIndicesOfFourthFace = unstructuredGrid->getNodeIndicesOfFaceOfCell(0, 3);
	REQUIRE(nodeIndicesOfFourthFace[0] == 0);
	REQUIRE(nodeIndicesOfFourthFace[1] == 2);
	REQUIRE(nodeIndicesOfFourthFace[2] == 3);
	nodeIndicesOfFirstFace = unstructuredGrid->getNodeIndicesOfFaceOfCell(1, 0);
	REQUIRE(nodeIndicesOfFirstFace[0] == 0);
	REQUIRE(nodeIndicesOfFirstFace[1] == 1);
	REQUIRE(nodeIndicesOfFirstFace[2] == 2);
	nodeIndicesOfSecondFace = unstructuredGrid->getNodeIndicesOfFaceOfCell(1, 1);
	REQUIRE(nodeIndicesOfSecondFace[0] == 0);
	REQUIRE(nodeIndicesOfSecondFace[1] == 2);
	REQUIRE(nodeIndicesOfSecondFace[2] == 6);
	REQUIRE(nodeIndicesOfSecondFace[3] == 4);
	nodeIndicesOfThirdFace = unstructuredGrid->getNodeIndicesOfFaceOfCell(1, 2);
	REQUIRE(nodeIndicesOfThirdFace[0] == 2);
	REQUIRE(nodeIndicesOfThirdFace[1] == 1);
	REQUIRE(nodeIndicesOfThirdFace[2] == 5);
	REQUIRE(nodeIndicesOfThirdFace[3] == 6);
	nodeIndicesOfFourthFace = unstructuredGrid->getNodeIndicesOfFaceOfCell(1, 3);
	REQUIRE(nodeIndicesOfFourthFace[0] == 0);
	REQUIRE(nodeIndicesOfFourthFace[1] == 1);
	REQUIRE(nodeIndicesOfFourthFace[2] == 5);
	REQUIRE(nodeIndicesOfFourthFace[3] == 4);
	uint64_t const* nodeIndicesOfFifthFace = unstructuredGrid->getNodeIndicesOfFaceOfCell(1, 4);
	REQUIRE(nodeIndicesOfFifthFace[0] == 4);
	REQUIRE(nodeIndicesOfFifthFace[1] == 5);
	REQUIRE(nodeIndicesOfFifthFace[2] == 6);

	// getCellCount
	REQUIRE(unstructuredGrid->getCellCount() == 2);

	// getFaceCount
	REQUIRE(unstructuredGrid->getFaceCount() == 8);

	// getNodeCount
	REQUIRE(unstructuredGrid->getNodeCount() == 7);

	// TODO: not able to test since method is not implemented yet
	unsigned char faceRightHandness[9];
	unstructuredGrid->getCellFaceIsRightHanded(faceRightHandness);
	REQUIRE(faceRightHandness[0] == 0);
	REQUIRE(faceRightHandness[1] == 0);
	REQUIRE(faceRightHandness[2] == 1);
	REQUIRE(faceRightHandness[3] == 1);
	REQUIRE(faceRightHandness[4] == 1);
	REQUIRE(faceRightHandness[5] == 0);
	REQUIRE(faceRightHandness[6] == 1);
	REQUIRE(faceRightHandness[7] == 0);
	REQUIRE(faceRightHandness[8] == 0);

	// unloading geometry
	unstructuredGrid->unloadGeometry();

	// getPatchCount
	REQUIRE( unstructuredGrid->getPatchCount() == 1);
}
