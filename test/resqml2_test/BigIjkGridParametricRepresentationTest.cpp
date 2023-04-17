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
#include "resqml2_test/BigIjkGridParametricRepresentationTest.h"

#include "catch.hpp"
#include "resqml2_test/LocalDepth3dCrsTest.h"

#include "resqml2/LocalDepth3dCrs.h"
#include "resqml2/IjkGridParametricRepresentation.h"
#include "resqml2/DiscreteProperty.h"
#include "resqml2/ContinuousProperty.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_test;
using namespace RESQML2_NS;

BigIjkGridParametricRepresentationTest::BigIjkGridParametricRepresentationTest(
	const string & repoPath,
	unsigned int iCount, unsigned int jCount, unsigned int kCount,
	unsigned int faultCount,
	double xMin, double xMax, double yMin, double yMax, double zMin, double zMax,
	double faultThrow)
	: AbstractBigIjkGridRepresentationTest(repoPath, iCount, jCount, kCount, faultCount, xMin, xMax, yMin, yMax, zMin, zMax, faultThrow) {
}

void BigIjkGridParametricRepresentationTest::initParametersAndControlPoints(double * parameters, double * controlPoints)
{
	const uint64_t nodeCount = initNodesCountIjkGridRepresentation(iCount, jCount, kCount, faultCount);

	for (unsigned int index = 0; index < nodeCount; ++index)
	{
		parameters[index] = nodesIjkGridRepresentation[3 * index + 2];
	}

	for (unsigned int index = 0; index < (iCount + 1) * (jCount + 1) * 3; ++index)
	{
		controlPoints[index] = nodesIjkGridRepresentation[index];
	}
}

void BigIjkGridParametricRepresentationTest::initRepo() {
	// creating the ijk grid
	RESQML2_NS::IjkGridParametricRepresentation* ijkGrid = repo->createIjkGridParametricRepresentation(defaultUuid, defaultTitle, iCount, jCount, kCount);
	REQUIRE(ijkGrid != nullptr);
	std::unique_ptr<double[]> parameters(new double[initNodesCountIjkGridRepresentation(iCount, jCount, kCount, faultCount)]);
	std::unique_ptr<double[]> controlPoints(new double[(iCount + 1) * (jCount + 1) * 3]);
	std::unique_ptr<unsigned int[]> pillarOfCoordinateLine(new unsigned int[faultCount * (jCount + 1)]);
	std::unique_ptr<unsigned int[]> splitCoordinateLineColumnCumulativeCount(new unsigned int[faultCount * (jCount + 1)]);
	std::unique_ptr<unsigned int[]> splitCoordinateLineColumns(new unsigned int[(faultCount * (jCount + 1)) + (faultCount * (jCount - 1))]);
	initNodesIjkGridRepresentation(iCount, jCount, kCount, faultCount, xMin, xMax, yMin, yMax, zMin, zMax, faultThrow);
	initParametersAndControlPoints(parameters.get(), controlPoints.get());
	initSplitCoordinateLine(pillarOfCoordinateLine.get(), splitCoordinateLineColumnCumulativeCount.get(), splitCoordinateLineColumns.get());

	ijkGrid->setGeometryAsParametricSplittedPillarNodes(false, parameters.get(), controlPoints.get(), NULL, 1, 0, nullptr,
		faultCount * (jCount + 1), pillarOfCoordinateLine.get(), splitCoordinateLineColumnCumulativeCount.get(), splitCoordinateLineColumns.get());

	// adding a discrete property
	auto propertyKind = repo->createPropertyKind("5f78f66a-ed1b-4827-a868-beb989febb31", "code", gsoap_eml2_3::eml23__QuantityClassKind::not_x0020a_x0020measure);
	RESQML2_NS::DiscreteProperty* discreteProperty = repo->createDiscreteProperty(
		ijkGrid, discretePropertyUuid, discretePropertyTitle,
		1, 
		gsoap_eml2_3::eml23__IndexableElement::cells,
		propertyKind);
	std::unique_ptr<unsigned short[]> discretePropertyValues(new unsigned short[iCount * jCount * kCount]);
	initDiscreteProperty(discretePropertyValues.get());
	discreteProperty->pushBackUShortHdf5Array3dOfValues(discretePropertyValues.get(), iCount, jCount, kCount, nullptr, -1);

	// adding a continuous property
	propertyKind = repo->createPropertyKind("4a305182-221e-4205-9e7c-a36b06fa5b3d", "length", gsoap_eml2_3::eml23__QuantityClassKind::length);
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

void BigIjkGridParametricRepresentationTest::readRepo() {
}

