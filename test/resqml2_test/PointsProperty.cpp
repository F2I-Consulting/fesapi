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
#include "resqml2_test/PointsProperty.h"

#include "catch.hpp"

#include "eml2/AbstractHdfProxy.h"

#include "resqml2/AbstractIjkGridRepresentation.h"
#include "resqml2/AbstractValuesProperty.h"

#include "resqml2_0_1/PointsProperty.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_test;

const char* PointsProperty::defaultUuid = "402ecb32-8c03-418f-98be-fe1bca069fb9";

PointsProperty::PointsProperty(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void PointsProperty::initRepo() {
	RESQML2_NS::AbstractIjkGridRepresentation* ijkGrid = repo->createPartialIjkGridRepresentation("", "partial IJK Grid");

	// getting the hdf proxy
	EML2_NS::AbstractHdfProxy* hdfProxy = repo->getHdfProxySet()[0];

	// creating the PointsProperty
	RESQML2_NS::PointsProperty* pointsProperty = repo->createPointsProperty(
		ijkGrid, defaultUuid, "points prop",
		1,
		gsoap_eml2_3::resqml22__IndexableElement__cells,
		repo->getDefaultCrs());
	double coordValues[6] = { .0, .1, .2, .3, .4, .5 };
	pointsProperty->pushBackArray3dOfXyzPoints(coordValues, 2, 1, 1, hdfProxy);
}

void PointsProperty::readRepo() {
	// getting the PointsProperty
	RESQML2_NS::PointsProperty* pointsProperty = repo->getDataObjectByUuid<RESQML2_NS::PointsProperty>(defaultUuid);
	REQUIRE(pointsProperty->getValuesHdfDatatype() == RESQML2_NS::AbstractValuesProperty::DOUBLE);
	REQUIRE(pointsProperty->getXyzPointCountOfPatch(0) == 2);
	std::unique_ptr<double[]> coords(new double[6]);
	pointsProperty->getXyzPointsOfPatch(0, coords.get());
	REQUIRE(coords[0] == .0);
	REQUIRE(coords[1] == .1);
	REQUIRE(coords[2] == .2);
	REQUIRE(coords[3] == .3);
	REQUIRE(coords[4] == .4);
	REQUIRE(coords[5] == .5);;
}
