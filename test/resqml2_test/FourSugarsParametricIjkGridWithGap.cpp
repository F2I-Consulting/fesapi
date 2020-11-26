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
#include "resqml2_test/FourSugarsParametricIjkGridWithGap.h"

#include "catch.hpp"
#include "resqml2_test/LocalDepth3dCrsTest.h"

#include "resqml2/LocalDepth3dCrs.h"
#include "resqml2/IjkGridParametricRepresentation.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_test;
using namespace RESQML2_NS;

const char* FourSugarsParametricIjkGridWithGap::defaultUuid = "ecd52ad4-ca18-49d4-8394-2e8b9796b9d5";
const char* FourSugarsParametricIjkGridWithGap::defaultTitle = "Four faulted sugar cubes parametric with k gap";
double FourSugarsParametricIjkGridWithGap::parameters[32] = { 300, 300, 350, 300, 300, 350, /* SPLIT*/ 350, 350,
		400, 400, 450, 400, 400, 450, /* SPLIT*/ 450, 450,
		425, 425, 475, 425, 425, 475, /* SPLIT*/ 475, 475,
		500, 500, 550, 500, 500, 550, /* SPLIT*/ 550, 550 };

FourSugarsParametricIjkGridWithGap::FourSugarsParametricIjkGridWithGap(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void FourSugarsParametricIjkGridWithGap::initRepo() {
	// creating the ijk grid
	bool kgap[1] = { true };
	RESQML2_NS::IjkGridParametricRepresentation* ijkGrid = repo->createIjkGridParametricRepresentation(defaultUuid, defaultTitle, 2, 1, 2, kgap);
	unsigned int pillarOfCoordinateLine[2] = { 1, 4 };
	unsigned int splitCoordinateLineColumnCumulativeCount[2] = { 1, 2 };
	unsigned int splitCoordinateLineColumns[2] = { 1, 1 };

	double controlPointsParametricStraight[36] = { 0, 0, 300, 375, 0, 300, 700, 0, 350, 0, 150, 300, 375, 150, 300, 700, 150, 350,
		0, 0, 500, 375, 0, 500, 700, 0, 550, 0, 150, 500, 375, 150, 500, 700, 150, 550 };
	double controlPointsParameters[12] = { 300, 300, 350, 300, 300, 350,
		500, 500, 550, 500, 500, 550 };

	ijkGrid->setGeometryAsParametricSplittedPillarNodes(false, parameters, controlPointsParametricStraight, controlPointsParameters, 2, 1, nullptr,
		2, pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);
}

void FourSugarsParametricIjkGridWithGap::readRepo() {
	// getting the subrep
	RESQML2_NS::IjkGridParametricRepresentation* ijkGrid = repo->getDataObjectByUuid<RESQML2_NS::IjkGridParametricRepresentation>(defaultUuid);

	REQUIRE(ijkGrid->getCellCount() == 4);
	REQUIRE(ijkGrid->getPillarCount() == 6);

	// checking values
	const uint64_t pointCount = ijkGrid->getXyzPointCountOfAllPatches();
	REQUIRE(pointCount == 32);

	std::unique_ptr<double[]> xyzPoints(new double[pointCount * 3]);
	ijkGrid->getXyzPointsOfAllPatches(xyzPoints.get());
	for (uint64_t i = 0; i < pointCount; ++i) {
		REQUIRE(xyzPoints[i*3+2] == parameters[i]);
	}

	// read points by cell corner
	ijkGrid->loadSplitInformation();

	auto ptIndex = ijkGrid->getXyzPointIndexFromCellCorner(0, 0, 0, 1);
	REQUIRE(xyzPoints[ptIndex * 3] == 375);
	REQUIRE(xyzPoints[ptIndex * 3 + 1] == .0);
	REQUIRE(xyzPoints[ptIndex * 3 + 2] == 300);

	ptIndex = ijkGrid->getXyzPointIndexFromCellCorner(0, 0, 0, 5);
	REQUIRE(xyzPoints[ptIndex * 3] == 375);
	REQUIRE(xyzPoints[ptIndex * 3 + 1] == .0);
	REQUIRE(xyzPoints[ptIndex * 3 + 2] == 400);

	ptIndex = ijkGrid->getXyzPointIndexFromCellCorner(0, 0, 1, 1);
	REQUIRE(xyzPoints[ptIndex * 3] == 375);
	REQUIRE(xyzPoints[ptIndex * 3 + 1] == .0);
	REQUIRE(xyzPoints[ptIndex * 3 + 2] == 425);

	ptIndex = ijkGrid->getXyzPointIndexFromCellCorner(0, 0, 1, 5);
	REQUIRE(xyzPoints[ptIndex * 3] == 375);
	REQUIRE(xyzPoints[ptIndex * 3 + 1] == .0);
	REQUIRE(xyzPoints[ptIndex * 3 + 2] == 500);

	ijkGrid->unloadSplitInformation();

}
