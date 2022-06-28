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
#include "PointsProperty.h"

#include <hdf5.h>

#include "../eml2/AbstractHdfProxy.h"

#include "../resqml2/AbstractLocal3dCrs.h"

using namespace RESQML2_NS;
using namespace std;

const char* PointsProperty::XML_TAG = "PointsProperty";

uint64_t PointsProperty::getXyzPointCountOfAllPatches() const
{
	uint64_t result = 0;

	const unsigned int patchCount = getPatchCount();
	for (unsigned int patchIndex = 0; patchIndex < patchCount; ++patchIndex)
	{
		result += getXyzPointCountOfPatch(patchIndex);
	}

	return result;
}

void PointsProperty::getXyzPointsOfPatchInGlobalCrs(unsigned int patchIndex, double* xyzPoints) const
{
	getXyzPointsOfPatch(patchIndex, xyzPoints);

	auto localCrs = getLocalCrs();
	if (localCrs != nullptr) {
		localCrs->convertXyzPointsToGlobalCrs(xyzPoints, getXyzPointCountOfPatch(patchIndex));
	}
}

void PointsProperty::getXyzPointsOfAllPatches(double* xyzPoints) const
{
	const unsigned int patchCount = getPatchCount();
	getXyzPointsOfPatch(0, xyzPoints);
	for (unsigned int patchIndex = 1; patchIndex < patchCount; patchIndex++)
	{
		xyzPoints += getXyzPointCountOfPatch(patchIndex - 1) * 3;
		getXyzPointsOfPatch(patchIndex, xyzPoints);
	}
}

void PointsProperty::getXyzPointsOfAllPatchesInGlobalCrs(double* xyzPoints) const
{
	getXyzPointsOfAllPatches(xyzPoints);

	auto localCrs = getLocalCrs();
	if (localCrs != nullptr) {
		localCrs->convertXyzPointsToGlobalCrs(xyzPoints, getXyzPointCountOfAllPatches());
	}
}

void PointsProperty::getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const
{
	std::string datasetPath;
	EML2_NS::AbstractHdfProxy* hdfProxy = getValuesHdfProxyAndDatasetPathOfPatch(patchIndex, datasetPath);

	hdfProxy->readArrayNdOfDoubleValues(datasetPath, xyzPoints);
}

void PointsProperty::pushBackArray1dOfXyzPoints(const double * points, uint64_t pointCount, EML2_NS::AbstractHdfProxy * proxy)
{
	const hsize_t pointCountPerDimension = pointCount;
	pushBackArrayOfXyzPoints(points, &pointCountPerDimension, 1, proxy);
}

void PointsProperty::pushBackArray2dOfXyzPoints(const double * points, uint64_t pointCountInFastestDim, uint64_t pointCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy)
{
	const hsize_t pointCountPerDimension[2] = { pointCountInSlowestDim, pointCountInFastestDim };
	pushBackArrayOfXyzPoints(points, pointCountPerDimension, 2, proxy);
}

void PointsProperty::pushBackArray3dOfXyzPoints(const double * points, uint64_t pointCountInFastestDim, uint64_t pointCountInMiddleDim, uint64_t pointCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy)
{
	const hsize_t pointCountPerDimension[3] = { pointCountInSlowestDim, pointCountInMiddleDim, pointCountInFastestDim };
	pushBackArrayOfXyzPoints(points, pointCountPerDimension, 3, proxy);
}

void PointsProperty::pushBackArrayOfXyzPoints(double const * points, unsigned long long const * pointCountByDimension, unsigned int numArrayDimensions, EML2_NS::AbstractHdfProxy * proxy)
{
	const string datasetName = pushBackRefToExistingDataset(proxy, "");

	// HDF
	std::unique_ptr<unsigned long long[]> coordinateCountByDimension(new unsigned long long[numArrayDimensions + 1]);
	for (unsigned int i = 0; i < numArrayDimensions; ++i) {
		coordinateCountByDimension[i] = pointCountByDimension[i];
	}
	coordinateCountByDimension[numArrayDimensions] = 3; // For the XYZ triplet
	proxy->writeArrayNd(getHdfGroup(),
		datasetName,
		COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE,
		points,
		coordinateCountByDimension.get(), numArrayDimensions + 1);
}
