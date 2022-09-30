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
#include "BlockedWellbore.h"

#include "resqml2/BlockedWellboreRepresentation.h"
#include "resqml2/AbstractIjkGridRepresentation.h"

#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_test;
using namespace RESQML2_NS;

const char* BlockedWellbore::defaultUuid = "442b1bed-c997-42ce-8b99-8e89a23edc0d";
const char* BlockedWellbore::defaultTitle = "BlockedWellbore representation with null value";
const char* BlockedWellbore::defaultUuidNoNullValue = "02318f5e-399e-43a0-9e7c-340b5954eaf2";
const char* BlockedWellbore::defaultTitleNoNullValue = "BlockedWellbore representation without null value";
const char* BlockedWellbore::defaultGridUuid = "0987a24d-24c0-49ea-bae3-f6c9d91a8d46";

BlockedWellbore::BlockedWellbore(const string & epcDocPath)
	: commontest::AbstractTest(epcDocPath) {
}

void BlockedWellbore::initRepo()
{
	RESQML2_NS::WellboreTrajectoryRepresentation* partialTraj = repo->createPartial<RESQML2_0_1_NS::WellboreTrajectoryRepresentation>("", "Partial Well traj");

	RESQML2_NS::AbstractIjkGridRepresentation* partialIjkGridRep = repo->createPartialIjkGridRepresentation(defaultGridUuid, "Grid for blocked well");

	RESQML2_NS::BlockedWellboreRepresentation* bwRep = repo->createBlockedWellboreRepresentation(nullptr, defaultUuid, defaultTitle, partialTraj);
	bwRep->pushBackSupportingGridRepresentation(partialIjkGridRep);

	double mdValues[6] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.7 };
	bwRep->setMdValues(mdValues, 6);

	int8_t gridIndices[5] = { 0, 0, 0, -1, 0 };
	int64_t cellIndices[5] = { 0, 10, 20, -1, 40 };
	int8_t localFacePairPerCellIndices[10] = { 0, 1, 1, 2, 2, 3, -1, -1, 5, 6};
	bwRep->setIntervalGridCells(gridIndices, -1, cellIndices, localFacePairPerCellIndices, -1);

	RESQML2_NS::BlockedWellboreRepresentation* bwRepNoNullValue = repo->createBlockedWellboreRepresentation(nullptr, defaultUuidNoNullValue, defaultTitleNoNullValue, partialTraj);
	bwRepNoNullValue->pushBackSupportingGridRepresentation(partialIjkGridRep);

	bwRepNoNullValue->setMdValues(mdValues, 6);
	gridIndices[3] = 0;
	cellIndices[3] = 30;
	localFacePairPerCellIndices[6] = 0;
	localFacePairPerCellIndices[7] = 0;
	bwRepNoNullValue->setIntervalGridCells(gridIndices, -1, cellIndices, localFacePairPerCellIndices, -1);
}

void BlockedWellbore::readRepo()
{
	RESQML2_NS::BlockedWellboreRepresentation* bwRep = repo->getDataObjectByUuid<RESQML2_NS::BlockedWellboreRepresentation>(defaultUuid);
	RESQML2_NS::BlockedWellboreRepresentation* bwRepNoNullValue = repo->getDataObjectByUuid<RESQML2_NS::BlockedWellboreRepresentation>(defaultUuidNoNullValue);
	REQUIRE(bwRep != nullptr);
	REQUIRE(bwRepNoNullValue != nullptr);
	REQUIRE(bwRep->getMdValuesCount() == 6);
	REQUIRE(bwRep->getCellCount() == 4);
	REQUIRE(bwRepNoNullValue->getCellCount() == 5);
	
	// Grid indices
	int8_t gridIndices[5];
	int8_t gridIndiceNullValue = bwRep->getGridIndices(gridIndices);
	REQUIRE(gridIndices[0] == 0);
	REQUIRE(gridIndices[1] == 0);
	REQUIRE(gridIndices[2] == 0);
	REQUIRE(gridIndices[3] == gridIndiceNullValue);
	REQUIRE(gridIndices[4] == 0);
	REQUIRE(bwRep->getSupportingGridRepresentationCount() == 1);
	REQUIRE(bwRep->getSupportingGridRepresentation(0) == repo->getDataObjectByUuid<RESQML2_NS::AbstractIjkGridRepresentation>(defaultGridUuid));
	bwRepNoNullValue->getGridIndices(gridIndices);
	REQUIRE(gridIndices[0] == 0);
	REQUIRE(gridIndices[1] == 0);
	REQUIRE(gridIndices[2] == 0);
	REQUIRE(gridIndices[3] == 0);
	REQUIRE(gridIndices[4] == 0);

	// Cell indices
	int64_t cellIndices[5];
	int64_t cellIndiceNullValue = bwRep->getCellIndices(cellIndices);
	REQUIRE(cellIndices[0] == 0);
	REQUIRE(cellIndices[1] == 10);
	REQUIRE(cellIndices[2] == 20);
	REQUIRE(cellIndices[3] == cellIndiceNullValue);
	REQUIRE(cellIndices[4] == 40);
	bwRepNoNullValue->getCellIndices(cellIndices);
	REQUIRE(cellIndices[0] == 0);
	REQUIRE(cellIndices[1] == 10);
	REQUIRE(cellIndices[2] == 20);
	REQUIRE(cellIndices[3] == 30);
	REQUIRE(cellIndices[4] == 40);

	// Local Face Pair Per Cell Indices
	int8_t localFacePairPerCellIndices[10];
	int8_t localFacePairPerCellIndicesNullValue = bwRep->getLocalFacePairPerCellIndices(localFacePairPerCellIndices);
	REQUIRE(localFacePairPerCellIndices[0] == 0);
	REQUIRE(localFacePairPerCellIndices[1] == 1);
	REQUIRE(localFacePairPerCellIndices[2] == 1);
	REQUIRE(localFacePairPerCellIndices[3] == 2);
	REQUIRE(localFacePairPerCellIndices[4] == 2);
	REQUIRE(localFacePairPerCellIndices[5] == 3);
	REQUIRE(localFacePairPerCellIndices[6] == localFacePairPerCellIndicesNullValue);
	REQUIRE(localFacePairPerCellIndices[7] == localFacePairPerCellIndicesNullValue);
	REQUIRE(localFacePairPerCellIndices[8] == 5);
	REQUIRE(localFacePairPerCellIndices[9] == 6);
	bwRepNoNullValue->getLocalFacePairPerCellIndices(localFacePairPerCellIndices);
	REQUIRE(localFacePairPerCellIndices[0] == 0);
	REQUIRE(localFacePairPerCellIndices[1] == 1);
	REQUIRE(localFacePairPerCellIndices[2] == 1);
	REQUIRE(localFacePairPerCellIndices[3] == 2);
	REQUIRE(localFacePairPerCellIndices[4] == 2);
	REQUIRE(localFacePairPerCellIndices[5] == 3);
	REQUIRE(localFacePairPerCellIndices[6] == 0);
	REQUIRE(localFacePairPerCellIndices[7] == 0);
	REQUIRE(localFacePairPerCellIndices[8] == 5);
	REQUIRE(localFacePairPerCellIndices[9] == 6);
}
