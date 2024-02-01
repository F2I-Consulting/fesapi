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
#include "TimeSeriesTest.h"

#include "eml2/TimeSeries.h"
#include "eml2/PropertyKind.h"

#include "resqml2/IjkGridExplicitRepresentation.h"
#include "resqml2/ContinuousProperty.h"

#include "resqml2_0_1/PropertyKind.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_test;
using namespace RESQML2_NS;
using namespace EML2_NS;

TimeSeriesTest::TimeSeriesTest(const string & epcDocPath)
	: commontest::AbstractTest(epcDocPath) {
}

void TimeSeriesTest::initRepo()
{
	TimeSeries* timeSeries = repo->createTimeSeries(timeSeriesUuid, "Time series");
	timeSeries->pushBackTimestamp(1378217895);
	timeSeries->pushBackTimestamp(1409753895);
	timeSeries->pushBackTimestamp(1441289895);
	timeSeries->pushBackTimestamp(170266171200); // Huge datetime 7365-07-09 06:40:00 UTC

	// Time series properties
	auto* partialGrid = repo->createPartialIjkGridRepresentation(partialGridUuid, "Partial grid");
	RESQML2_0_1_NS::PropertyKind* propertyKind = repo->createPartial<RESQML2_0_1_NS::PropertyKind>("4a305182-221e-4205-9e7c-a36b06fa5b3d", "length");
	ContinuousProperty* prop1 = repo->createContinuousProperty(
		partialGrid, prop1Uuid, "prop 1",
		gsoap_eml2_3::eml23__IndexableElement::cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom::Pa,
		propertyKind);
	float prop1Values[2] = { -1, 0 };
	prop1->pushBackFloatHdf5Array3dOfValues(prop1Values, 2, 1, 1);
	prop1->setTimeSeries(timeSeries);
	prop1->setSingleTimestamp(1378217895);

	ContinuousProperty* prop2 = repo->createContinuousProperty(
		partialGrid, prop2Uuid, "prop 2",
		gsoap_eml2_3::eml23__IndexableElement::cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom::Pa,
		propertyKind);
	float prop2Values[2] = { -10, 0 };
	prop2->pushBackFloatHdf5Array3dOfValues(prop2Values, 2, 1, 1);
	prop2->setTimeSeries(timeSeries);
	prop2->setSingleTimestamp(1409753895);

	ContinuousProperty* prop3 = repo->createContinuousProperty(
		partialGrid, prop3Uuid, "prop 3",
		gsoap_eml2_3::eml23__IndexableElement::cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom::Pa,
		propertyKind);
	float prop3Values[2] = { -100, 0 };
	prop3->pushBackFloatHdf5Array3dOfValues(prop3Values, 2, 1, 1);
	prop3->setTimeSeries(timeSeries);
	prop3->setSingleTimestamp(1441289895);

	ContinuousProperty* prop4 = repo->createContinuousProperty(
		partialGrid, prop4Uuid, "prop 4", 1,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom::m,
		propertyKind);
	float prop4Values[2] = { -1000, 0 };
	prop4->pushBackFloatHdf5Array3dOfValues(prop3Values, 2, 1, 1);
	prop4->setTimeSeries(timeSeries);
	prop4->setSingleTimestamp(170266171200);

	double nodes[72] = {
		0,0,0, 1,0,0, 2,0,0, 0,1,0, 1,1,0, 2,1,0,
		0,0,1, 1,0,1, 2,0,1, 0,1,1, 1,1,1, 2,1,1,
		0,0,2, 1,0,2, 2,0,2, 0,1,2, 1,1,2, 2,1,2,
		0,0,3, 1,0,3, 2,0,3, 0,1,3, 1,1,3, 2,1,3
	};
	// Time series rep
	auto* grid1 = repo->createIjkGridExplicitRepresentation(rep1Uuid, "grid1", 2, 1, 1);
	grid1->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape::vertical, gsoap_resqml2_0_1::resqml20__KDirection::down, false, nodes);
	grid1->setTimeIndex(0, timeSeries);

	auto* grid2 = repo->createIjkGridExplicitRepresentation(rep2Uuid, "grid2", 2, 1, 2);
	grid2->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape::vertical, gsoap_resqml2_0_1::resqml20__KDirection::down, false, nodes);
	grid2->setTimeIndex(1, timeSeries);

	auto* grid3 = repo->createIjkGridExplicitRepresentation(rep3Uuid, "grid2", 2, 1, 3);
	grid3->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape::vertical, gsoap_resqml2_0_1::resqml20__KDirection::down, false, nodes);
	grid3->setTimeIndex(2, timeSeries);
}

void TimeSeriesTest::readRepo() {
	vector<TimeSeries*> timeSeriesSet = repo->getTimeSeriesSet();
	REQUIRE(timeSeriesSet.size() == 1);

	// getting the TimeSeries
	TimeSeries* timeSeries = timeSeriesSet[0];

	// **********************
	// reading the TimeSeries

	// getTimestampCount
	REQUIRE(timeSeries->getTimestampCount() == 4);

	// getTimestampIndex
	REQUIRE(timeSeries->getTimestampIndex(1378217895) == 0);
	REQUIRE(timeSeries->getTimestampIndex(1409753895) == 1);
	REQUIRE(timeSeries->getTimestampIndex(1441289895) == 2);
	REQUIRE(timeSeries->getTimestampIndex(170266171200) == 3);


	// getTimestamp
	REQUIRE(timeSeries->getTimestamp(0) == 1378217895);
	REQUIRE(timeSeries->getTimestamp(1) == 1409753895);
	REQUIRE(timeSeries->getTimestamp(2) == 1441289895);

	// **********************
	// reading the properties

	AbstractRepresentation* partialGrid = repo->getDataObjectByUuid<AbstractRepresentation>(partialGridUuid);
	auto propSet = partialGrid->getValuesPropertySet();
	for (auto* prop : propSet) {
		REQUIRE(prop->getTimeSeries() == timeSeries);
		const auto uuid = prop->getUuid();
		if (uuid == prop1Uuid) {
			REQUIRE(prop->getSingleTimestamp() == 1378217895);
		}
		else if (uuid == prop2Uuid) {
			REQUIRE(prop->getSingleTimestamp() == 1409753895);
		}
		else if (uuid == prop3Uuid) {
			REQUIRE(prop->getSingleTimestamp() == 1441289895);
		}
		else if (uuid == prop4Uuid) {
			REQUIRE(prop->getSingleTimestamp() == 170266171200);
		}
	}

	// **********************
	// reading the representations

	auto ijkSet = repo->getIjkGridExplicitRepresentationSet();
	for (auto* rep : ijkSet) {
		const auto uuid = rep->getUuid();
		if (uuid == partialGridUuid) {
			REQUIRE(rep->getTimeSeries() == nullptr);
		}
		else {
			REQUIRE(rep->getTimeSeries() == timeSeries);
			if (uuid == rep1Uuid) {
				REQUIRE(rep->getKCellCount() == 1);
				REQUIRE(rep->getTimeIndex() == 0);
			}
			else if (uuid == rep2Uuid) {
				REQUIRE(rep->getKCellCount() == 2);
				REQUIRE(rep->getTimeIndex() == 1);
			}
			else if (uuid == rep3Uuid) {
				REQUIRE(rep->getKCellCount() == 3);
				REQUIRE(rep->getTimeIndex() == 2);
			}
		}
	}
}
