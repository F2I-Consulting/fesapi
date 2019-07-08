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
#include "resqml2_0_1test/BigIjkGridParametricRepresentationTest.h"

#include "catch.hpp"
#include "resqml2_0_1test/LocalDepth3dCrsTest.h"

#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "resqml2_0_1/IjkGridParametricRepresentation.h"
#include "resqml2_0_1/DiscreteProperty.h"
#include "resqml2_0_1/ContinuousProperty.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_0_1test;
using namespace RESQML2_NS;

const char* BigIjkGridParametricRepresentationTest::defaultUuid = "d94033f1-188b-465b-9594-c88403f7767e";
const char* BigIjkGridParametricRepresentationTest::defaultTitle = "Ijk Grid Param Representation";
const char* BigIjkGridParametricRepresentationTest::discretePropertyUuid = "e3a36173-1d46-4db3-87d0-84e51efce7ed";
const char* BigIjkGridParametricRepresentationTest::discretePropertyTitle = "Parametric IJK Grid K Index";
const char* BigIjkGridParametricRepresentationTest::continuousPropertyUuid = "78fa1c70-f0d6-4ce1-8cc6-401f812cd713";
const char* BigIjkGridParametricRepresentationTest::continuousPropertyTitle = "Parametric IJK Grid Continuous Property";

BigIjkGridParametricRepresentationTest::BigIjkGridParametricRepresentationTest(
	const string & repoPath,
	const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount,
	const unsigned int & faultCount,
	const double & xMin, const double & xMax, const double & yMin, const double & yMax, const double & zMin, const double & zMax,
	const double & faultThrow)
	: AbstractBigIjkGridRepresentationTest(repoPath, iCount, jCount, kCount, faultCount, xMin, xMax, yMin, yMax, zMin, zMax, faultThrow) {
}

BigIjkGridParametricRepresentationTest::BigIjkGridParametricRepresentationTest(DataObjectRepository * repo, bool init,
	const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount,
	const unsigned int & faultCount,
	const double & xMin, const double & xMax, const double & yMin, const double & yMax, const double & zMin, const double & zMax,
	const double & faultThrow)
	: AbstractBigIjkGridRepresentationTest(repo, init, iCount, jCount, kCount, faultCount, xMin, xMax, yMin, yMax, zMin, zMax, faultThrow) {
}

void BigIjkGridParametricRepresentationTest::initParametersAndControlPoints(double * parameters, double * controlPoints)
{
	const ULONG64 nodeCount = initNodesCountIjkGridRepresentation(iCount, jCount, kCount, faultCount);

	for (unsigned int index = 0; index < nodeCount; ++index)
	{
		parameters[index] = nodesIjkGridRepresentation[3 * index + 2];
	}

	for (unsigned int index = 0; index < (iCount + 1) * (jCount + 1) * 3; ++index)
	{
		controlPoints[index] = nodesIjkGridRepresentation[index];
	}
}

void BigIjkGridParametricRepresentationTest::initRepoHandler() {
	// creating the ijk grid
	RESQML2_0_1_NS::IjkGridParametricRepresentation* ijkGrid = repo->createIjkGridParametricRepresentation(defaultUuid, defaultTitle, iCount, jCount, kCount);
	REQUIRE(ijkGrid != nullptr);
	double * parameters = new double[initNodesCountIjkGridRepresentation(iCount, jCount, kCount, faultCount)]; 
	double * controlPoints = new double[(iCount + 1) * (jCount + 1) * 3];
	unsigned int * pillarOfCoordinateLine = new unsigned int[faultCount * (jCount + 1)];
	unsigned int * splitCoordinateLineColumnCumulativeCount = new unsigned int[faultCount * (jCount + 1)];
	unsigned int * splitCoordinateLineColumns = new unsigned int[(faultCount * (jCount + 1)) + (faultCount * (jCount - 1))];
	initNodesIjkGridRepresentation(iCount, jCount, kCount, faultCount, xMin, xMax, yMin, yMax, zMin, zMax, faultThrow);
	initParametersAndControlPoints(parameters, controlPoints);
	initSplitCoordinateLine(pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);

	ijkGrid->setGeometryAsParametricSplittedPillarNodes(false, parameters, controlPoints, NULL, 1, 0, nullptr,
		faultCount * (jCount + 1), pillarOfCoordinateLine, splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns);

	// adding a discrete property
	RESQML2_0_1_NS::DiscreteProperty* discreteProperty = repo->createDiscreteProperty(
		ijkGrid, discretePropertyUuid, discretePropertyTitle,
		1, 
		gsoap_resqml2_0_1::resqml2__IndexableElements__cells, 
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__index);
	unsigned short * discretePropertyValues = new unsigned short[iCount * jCount * kCount];
	initDiscreteProperty(discretePropertyValues);
	discreteProperty->pushBackUShortHdf5Array3dOfValues(discretePropertyValues, iCount, jCount, kCount, nullptr, -1);

	// adding a continuous property
	RESQML2_0_1_NS::ContinuousProperty* continuousProperty = repo->createContinuousProperty(
		ijkGrid, continuousPropertyUuid, continuousPropertyTitle,
		1,
		gsoap_resqml2_0_1::resqml2__IndexableElements__cells,
		gsoap_resqml2_0_1::resqml2__ResqmlUom__m,
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__length);
	double * continuousPropertyValues = new double[iCount * jCount * kCount];
	initContinuousProperty(continuousPropertyValues);
	continuousProperty->pushBackDoubleHdf5Array1dOfValues(continuousPropertyValues, iCount * jCount * kCount, nullptr);

	// cleaning
	delete[] parameters;
	delete[] controlPoints;
	delete[] pillarOfCoordinateLine;
	delete[] splitCoordinateLineColumnCumulativeCount;
	delete[] splitCoordinateLineColumns;
	delete[] discretePropertyValues;
	delete[] continuousPropertyValues;
}

void BigIjkGridParametricRepresentationTest::readRepoHandler() {
}

