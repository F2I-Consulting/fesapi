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
#include "resqml2_test/BigIjkGridExplicitRepresentationTest.h"

#include "catch.hpp"

#include "resqml2/IjkGridExplicitRepresentation.h"
#include "resqml2/DiscreteProperty.h"
#include "resqml2/ContinuousProperty.h"

#include "resqml2_0_1/PropertyKind.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_test;
using namespace RESQML2_NS;

BigIjkGridExplicitRepresentationTest::BigIjkGridExplicitRepresentationTest(
	const string & repoPath,
	unsigned int iCount, unsigned int jCount, unsigned int kCount,
	unsigned int faultCount,
	double xMin, double xMax, double yMin, double yMax, double zMin, double zMax,
	double faultThrow)
	: AbstractBigIjkGridRepresentationTest(repoPath, iCount, jCount, kCount, faultCount, xMin, xMax, yMin, yMax, zMin, zMax, faultThrow) {
}

void BigIjkGridExplicitRepresentationTest::initRepo() {
	// creating the ijk grid
	RESQML2_NS::IjkGridExplicitRepresentation* ijkGrid = repo->createIjkGridExplicitRepresentation(defaultUuid, defaultTitle, iCount, jCount, kCount);
	REQUIRE(ijkGrid != nullptr);
	std::unique_ptr<unsigned int[]> pillarOfCoordinateLine(new unsigned int[faultCount * (jCount + 1)]);
	std::unique_ptr<unsigned int[]> splitCoordinateLineColumnCumulativeCount(new unsigned int[faultCount * (jCount + 1)]);
	std::unique_ptr<unsigned int[]> splitCoordinateLineColumns(new unsigned int[(faultCount * (jCount + 1)) + (faultCount * (jCount - 1))]);
	initSplitCoordinateLine(pillarOfCoordinateLine.get(), splitCoordinateLineColumnCumulativeCount.get(), splitCoordinateLineColumns.get());
	initNodesIjkGridRepresentation(iCount, jCount, kCount, faultCount, xMin, xMax, yMin, yMax, zMin, zMax, faultThrow);
	ijkGrid->setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape::vertical, gsoap_resqml2_0_1::resqml20__KDirection::down, false, nodesIjkGridRepresentation, nullptr,
		faultCount * (jCount + 1), pillarOfCoordinateLine.get(), splitCoordinateLineColumnCumulativeCount.get(), splitCoordinateLineColumns.get());

	// adding a discrete property
	RESQML2_0_1_NS::PropertyKind* propertyKind = repo->createPartial<RESQML2_0_1_NS::PropertyKind>("5f78f66a-ed1b-4827-a868-beb989febb31", "code");
	RESQML2_NS::DiscreteProperty* discreteProperty = repo->createDiscreteProperty(
		ijkGrid, discretePropertyUuid, discretePropertyTitle,
		1, 
		gsoap_eml2_3::eml23__IndexableElement::cells,
		propertyKind);
	std::unique_ptr<uint16_t[]> discretePropertyValues(new unsigned short[iCount * jCount * kCount]);
	initDiscreteProperty(discretePropertyValues.get());
	discreteProperty->pushBackIntegerArray3dOfValues(discretePropertyValues.get(), iCount, jCount, kCount, nullptr, (std::numeric_limits<uint16_t>::max)());

	// adding a continuous property
	propertyKind = repo->createPartial<RESQML2_0_1_NS::PropertyKind>("4a305182-221e-4205-9e7c-a36b06fa5b3d", "length");
	RESQML2_NS::ContinuousProperty* continuousProperty = repo->createContinuousProperty(
		ijkGrid, continuousPropertyUuid, continuousPropertyTitle,
		1,
		gsoap_eml2_3::eml23__IndexableElement::cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom::m,
		propertyKind);
	std::unique_ptr<double[]> continuousPropertyValues(new double[iCount * jCount * kCount]);
	initContinuousProperty(continuousPropertyValues.get());
	continuousProperty->pushBackDoubleHdf5Array1dOfValues(continuousPropertyValues.get(), iCount * jCount * kCount, nullptr);
}

void BigIjkGridExplicitRepresentationTest::readRepo() {
}
