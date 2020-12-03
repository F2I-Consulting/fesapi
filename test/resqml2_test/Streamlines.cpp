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
#include "Streamlines.h"

#include "../catch.hpp"
#include "resqml2_0_1/TimeSeries.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2/StreamlinesFeature.h"
#include "resqml2_2/StreamlinesRepresentation.h"
#include "resqml2/AbstractIjkGridRepresentation.h"
#include "resqml2/GenericFeatureInterpretation.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_test;
using namespace RESQML2_NS;

const char* Streamlines::defaultUuid = "f84c2c46-3afc-469e-9faf-799785e09c5d";
const char* Streamlines::defaultTitle = "Streamlines feature";

Streamlines::Streamlines(const string & epcDocPath)
	: commontest::AbstractTest(epcDocPath) {
}

void Streamlines::initRepo()
{
	EML2_NS::TimeSeries* partialTimeSeries = repo->createPartial<RESQML2_0_1_NS::TimeSeries>("", "TimeSeries for streamline");

	RESQML2_NS::WellboreTrajectoryRepresentation* partialInjectorTraj = repo->createPartial<RESQML2_0_1_NS::WellboreTrajectoryRepresentation>("", "Injector");
	RESQML2_NS::WellboreTrajectoryRepresentation* partialProducerTraj = repo->createPartial<RESQML2_0_1_NS::WellboreTrajectoryRepresentation>("", "Producer");
	std::vector<RESQML2_NS::WellboreTrajectoryRepresentation*> trajVector;
	trajVector.push_back(partialInjectorTraj);
	trajVector.push_back(partialProducerTraj);

	RESQML2_NS::AbstractIjkGridRepresentation* partialIjkGridRep = repo->createPartialIjkGridRepresentation("", "Grid for streamline");
	std::vector<RESQML2_NS::AbstractGridRepresentation*> gridVector;
	gridVector.push_back(partialIjkGridRep);

	RESQML2_NS::StreamlinesFeature* streamlinesFeature = repo->createStreamlinesFeature(defaultUuid, defaultTitle, 0, partialTimeSeries);
	RESQML2_NS::GenericFeatureInterpretation* interp = repo->createGenericFeatureInterpretation(streamlinesFeature, "", "Streamlines interp");
	RESQML2_NS::StreamlinesRepresentation* streamlinesRep = repo->createStreamlinesRepresentation(interp, "", "Streamlines rep", 2);

	// Well
	uint32_t injectorPerLine[2] = { 0, 0 };
	uint32_t producerPerLine[2] = { 1, 1 };
	streamlinesRep->setWellboreInformation(injectorPerLine, producerPerLine, trajVector);

	// Geom
	uint32_t nodeCountPerLine[2] = { 2, 3 };
	if (repo->getDefaultResqmlVersion() == COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_2) {
		double xyzPoints[15] = { .0, .0, .0, 1.0, 1.0, 1.0, 2.0, 2.0, 2.0, 3.0, 3.0, 3.0, 4.0, 4.0, 4.0 };
		streamlinesRep->setGeometry(nodeCountPerLine, xyzPoints);
	}
	else {
		streamlinesRep->setGeometry(nodeCountPerLine, nullptr);
	}

	// Grid
	uint16_t gridIndices[3] = { 0, 0, 0 };
	uint64_t cellIndices[3] = { 0, 1, 2 };
	uint8_t localfacePairs[6] = { 7, 7, 7, 5, 3, 7 };
	streamlinesRep->setIntervalGridCells(gridIndices, (std::numeric_limits<uint32_t>::max)(),
		cellIndices, (std::numeric_limits<uint64_t>::max)(),
		localfacePairs, 7,
		gridVector);
}

void Streamlines::readRepo()
{
	RESQML2_NS::StreamlinesFeature* streamlinesFeature = repo->getDataObjectByUuid<RESQML2_NS::StreamlinesFeature>(defaultUuid);
	REQUIRE(streamlinesFeature->getTimeIndex() == 0);
	REQUIRE(streamlinesFeature->getTimeSeries()->getTitle() == "TimeSeries for streamline");
	REQUIRE(streamlinesFeature->getInterpretationCount() == 1);
	REQUIRE(streamlinesFeature->getInterpretation(0)->getRepresentationCount() == 1);
	RESQML2_NS::StreamlinesRepresentation* streamlinesRep = repo->getDataObjectByUuid<RESQML2_NS::StreamlinesRepresentation>(streamlinesFeature->getInterpretation(0)->getRepresentation(0)->getUuid());
	REQUIRE(streamlinesRep->getLineCount() == 2);

	// Well
	REQUIRE(streamlinesRep->getWellboreTrajectoryCount() == 2);
	uint32_t injectorPerLine[2];
	uint32_t producerPerLine[2];
	streamlinesRep->getInjectorPerLine(injectorPerLine);
	streamlinesRep->getProducerPerLine(producerPerLine);
	REQUIRE(injectorPerLine[0] == 0);
	REQUIRE(injectorPerLine[1] == 0);
	REQUIRE(producerPerLine[0] == 1);
	REQUIRE(producerPerLine[1] == 1);
	REQUIRE(streamlinesRep->getWellboreTrajectory(0)->getTitle() == "Injector");

	//Geom
	uint32_t nodeCountPerLine[2];
	streamlinesRep->getNodeCountPerLine(nodeCountPerLine);
	REQUIRE(nodeCountPerLine[0] == 2);
	REQUIRE(nodeCountPerLine[1] == 3);
	uint32_t intervalCountPerLine[2];
	streamlinesRep->getIntervalCountPerLine(intervalCountPerLine);
	REQUIRE(intervalCountPerLine[0] == 1);
	REQUIRE(intervalCountPerLine[1] == 2);
	REQUIRE(streamlinesRep->getIntervalCount() == 3);
	if (dynamic_cast<RESQML2_2_NS::StreamlinesRepresentation*>(streamlinesRep) != nullptr) {
		REQUIRE(streamlinesRep->getXyzPointCountOfAllPatches() == 5);
		double xyzPoints[15];
		streamlinesRep->getXyzPointsOfAllPatches(xyzPoints);
		REQUIRE(xyzPoints[0] == .0);
		REQUIRE(xyzPoints[1] == .0);
		REQUIRE(xyzPoints[2] == .0);
		REQUIRE(xyzPoints[3] == 1.0);
		REQUIRE(xyzPoints[14] == 4.0);
	}
	else {
		double xyzPoints[15];
		REQUIRE_THROWS(streamlinesRep->getXyzPointsOfAllPatches(xyzPoints));
	}

	// Grid
	REQUIRE(streamlinesRep->getGridRepresentationCount() == 1);
	REQUIRE(streamlinesRep->getGridRepresentation(0)->getTitle() == "Grid for streamline");
	uint64_t cellIndices[3];
	streamlinesRep->getCellIndices(cellIndices);
	REQUIRE(cellIndices[0] == 0);
	REQUIRE(cellIndices[1] == 1);
	REQUIRE(cellIndices[2] == 2);
	uint16_t gridIndices[3];
	streamlinesRep->getGridIndices(gridIndices);
	REQUIRE(gridIndices[0] == 0);
	REQUIRE(gridIndices[1] == 0);
	REQUIRE(gridIndices[2] == 0);
	uint8_t localfacePairs[6];
	uint8_t nullValue = streamlinesRep->getLocalFacePairPerCellIndices(localfacePairs);
	REQUIRE(localfacePairs[0] == nullValue);
	REQUIRE(localfacePairs[1] == nullValue);
	REQUIRE(localfacePairs[2] == nullValue);
	REQUIRE(localfacePairs[3] == 5);
	REQUIRE(localfacePairs[4] == 3);
	REQUIRE(localfacePairs[5] == nullValue);
}
