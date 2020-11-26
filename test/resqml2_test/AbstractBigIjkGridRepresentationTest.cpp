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
#include "resqml2_test/AbstractBigIjkGridRepresentationTest.h"

#include "catch.hpp"
#include "resqml2_test/LocalDepth3dCrsTest.h"

#include "resqml2/LocalDepth3dCrs.h"
#include "resqml2/IjkGridExplicitRepresentation.h"
#include "resqml2/DiscreteProperty.h"
#include "resqml2/ContinuousProperty.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_test;
using namespace RESQML2_NS;

AbstractBigIjkGridRepresentationTest::AbstractBigIjkGridRepresentationTest(
	const string & repoPath,
	unsigned int iCount, unsigned int jCount, unsigned int kCount,
	unsigned int faultCount,
	double xMin, double xMax, double yMin, double yMax, double zMin, double zMax,
	double faultThrow) :
	commontest::AbstractTest(repoPath),
	iCount(iCount), jCount(jCount), kCount(kCount), faultCount(faultCount),
	xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax), zMin(zMin), zMax(zMax), faultThrow(faultThrow)
{
	if ((iCount < 1) || (jCount < 1) || (kCount < 1))
	{
		throw invalid_argument("iCount, jCount and kCount must be >= 1.");
	}

	if (faultCount > (iCount - 1))
	{
		throw invalid_argument("faultCount must be strictly less than iCount.");
	}

	if ((xMin == xMax) || (yMin == yMax) || (zMin == zMax))
	{
		throw invalid_argument("In each dimension, grid length cannot be 0.");
	}
}

unsigned long long AbstractBigIjkGridRepresentationTest::initNodesCountIjkGridRepresentation(unsigned int iCount, unsigned int jCount, unsigned int kCount,
	unsigned int faultCount)
{
	return ((iCount + 1) * (jCount + 1) * (kCount + 1)) + (faultCount * (jCount + 1) * (kCount + 1));
}

double * AbstractBigIjkGridRepresentationTest::initNodesIjkGridRepresentation(unsigned int iCount, unsigned int jCount, unsigned int kCount,
	unsigned int faultCount,
	double xMin, double xMax, double yMin, double yMax, double zMin, double zMax,
	double faultThrow)
{
	uint64_t nodeCount = initNodesCountIjkGridRepresentation(iCount, jCount, kCount, faultCount);
	
	nodesIjkGridRepresentation = new double[nodeCount * 3];
	
	double xIncr = (xMax - xMin) / iCount;
	double yIncr = (yMax - yMin) / jCount;
	double zIncr = (zMax - zMin) / kCount;

	for (unsigned int k = 0; k < kCount + 1; ++k)
		for (unsigned int j = 0; j < jCount + 1; ++j)
		{
			double cumulativeFaultThrow = 0.;

			for (unsigned int i = 0; i < iCount + 1; ++i)
			{
				unsigned int currentIndex = k * ((iCount + 1) * (jCount + 1) + faultCount * (jCount + 1)) + j * (iCount + 1) + i;

				nodesIjkGridRepresentation[3 * currentIndex] = i * xIncr;
				nodesIjkGridRepresentation[3 * currentIndex + 1] = j * yIncr;
				nodesIjkGridRepresentation[3 * currentIndex + 2] = k * zIncr + cumulativeFaultThrow;

				if (i <= faultCount)
				{
					cumulativeFaultThrow = i*faultThrow;
				}
			}
		}

	for (unsigned int k = 0; k < kCount + 1; ++k)
		for (unsigned int j = 0; j < jCount + 1; ++j)
			for (unsigned int i = 1; i < faultCount + 1; ++i)
			{
				unsigned int currentIndex = k * ((iCount + 1) * (jCount + 1) + faultCount * (jCount + 1)) + (iCount + 1) * (jCount + 1) + j * faultCount + i - 1;

				nodesIjkGridRepresentation[3 * currentIndex] = i * xIncr;
				nodesIjkGridRepresentation[3 * currentIndex + 1] = j * yIncr;
				nodesIjkGridRepresentation[3 * currentIndex + 2] = k * zIncr + i * faultThrow;
			}

	return nodesIjkGridRepresentation;
}

void AbstractBigIjkGridRepresentationTest::initSplitCoordinateLine(unsigned int * pillarOfCoordinateLine,
	unsigned int * splitCoordinateLineColumnCumulativeCount,
	unsigned int * splitCoordinateLineColumns)
{
	//*************************************
	// initializing  pillarOfCoordinateLine
	
	unsigned int currentIndex = 0;
	for (unsigned int j = 0; j < jCount + 1; ++j)
		for (unsigned int i = 1; i < faultCount + 1; ++i)
		{
			pillarOfCoordinateLine[currentIndex] = j * (iCount + 1) + i;
			++currentIndex;
		}

	//******************************************************
	// initializing splitCoordinateLineColumnCumulativeCount

	unsigned int currentCumulativeCount = 0;
	for (unsigned int faultIndex = 0; faultIndex < faultCount; ++faultIndex)
	{
		++currentCumulativeCount;
		splitCoordinateLineColumnCumulativeCount[faultIndex] = currentCumulativeCount;
	}

	for (unsigned int jIndex = 1; jIndex < jCount; ++jIndex)
	{
		for (unsigned int faultIndex = 0; faultIndex < faultCount; ++faultIndex)
		{
			currentCumulativeCount += 2;
			splitCoordinateLineColumnCumulativeCount[jIndex * faultCount + faultIndex] = currentCumulativeCount;
		}
	}

	for (unsigned int faultIndex = 0; faultIndex < faultCount; ++faultIndex)
	{
		++currentCumulativeCount;
		splitCoordinateLineColumnCumulativeCount[jCount * faultCount + faultIndex] = currentCumulativeCount;
	}

	//****************************************
	// initializing splitCoordinateLineColumns

	currentIndex = 0;
	for (unsigned int faultIndex = 0; faultIndex < faultCount; ++faultIndex)
	{
		splitCoordinateLineColumns[currentIndex] = faultIndex + 1;
		++currentIndex;
	}

	for (unsigned int jIndex = 1; jIndex < jCount; ++jIndex)
		for (unsigned int faultIndex = 0; faultIndex < faultCount; ++faultIndex)
		{
			splitCoordinateLineColumns[currentIndex] = ((jIndex - 1) * iCount) + faultIndex + 1;
			splitCoordinateLineColumns[currentIndex + 1] = (jIndex * iCount) + faultIndex + 1;
			currentIndex += 2;
		}

	for (unsigned int faultIndex = 0; faultIndex < faultCount; ++faultIndex)
	{
		splitCoordinateLineColumns[currentIndex] = ((jCount - 1) * iCount) + faultIndex + 1;
		++currentIndex;
	}
}

void AbstractBigIjkGridRepresentationTest::initDiscreteProperty(unsigned short * discretePropertyValues)
{
	for (unsigned short k = 0; k < kCount; ++k)
		for (unsigned int j = 0; j < jCount; ++j)
			for (unsigned int i = 0; i < iCount; ++i)
			{
				discretePropertyValues[k * iCount * jCount + j * iCount + i] = k;
			}
}

void AbstractBigIjkGridRepresentationTest::initContinuousProperty(double * continuousPropertyValues)
{
	double valueIncr = (iCount - 1) != 0 ? 1. / (iCount - 1) : 0.;

	for (unsigned short k = 0; k < kCount; ++k)
		for (unsigned int j = 0; j < jCount; ++j)
			for (unsigned int i = 0; i < iCount; ++i)
			{
				continuousPropertyValues[k * iCount * jCount + j * iCount + i] = i * valueIncr;
			}
}
