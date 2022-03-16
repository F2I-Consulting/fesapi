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
#include "../eml2/AbstractLocal3dCrs.h"

using namespace RESQML2_NS;
using namespace std;

uint64_t PointsProperty::getXyzPointCountOfAllPatches() const
{
	uint64_t result = 0;

	const uint64_t patchCount = getPatchCount();
	for (uint64_t patchIndex = 0; patchIndex < patchCount; ++patchIndex) {
		result += getXyzPointCountOfPatch(patchIndex);
	}

	return result;
}

void PointsProperty::getXyzPointsOfPatchInGlobalCrs(uint64_t patchIndex, double* xyzPoints) const
{
	getXyzPointsOfPatch(patchIndex, xyzPoints);

	auto localCrs = getLocalCrs();
	if (localCrs != nullptr) {
		localCrs->convertXyzPointsToGlobalCrs(xyzPoints, getXyzPointCountOfPatch(patchIndex));
	}
}

void PointsProperty::getXyzPointsOfAllPatches(double* xyzPoints) const
{
	const uint64_t patchCount = getPatchCount();
	getXyzPointsOfPatch(0, xyzPoints);
	for (uint64_t patchIndex = 1; patchIndex < patchCount; patchIndex++) {
		xyzPoints += getXyzPointCountOfPatch(patchIndex - 1) * 3;
		getXyzPointsOfPatch(patchIndex, xyzPoints);
	}
}

void PointsProperty::getXyzPointsOfAllPatchesInGlobalCrs(double* xyzPoints) const
{
	getXyzPointsOfAllPatches(xyzPoints);

	auto const* localCrs = getLocalCrs();
	if (localCrs != nullptr) {
		localCrs->convertXyzPointsToGlobalCrs(xyzPoints, getXyzPointCountOfAllPatches());
	}
}

void PointsProperty::getXyzPointsOfPatch(uint64_t patchIndex, double * xyzPoints) const
{
	std::string datasetPath;
	EML2_NS::AbstractHdfProxy* hdfProxy = getValuesHdfProxyAndDatasetPathOfPatch(patchIndex, datasetPath);

	hdfProxy->readArrayNdOfDoubleValues(datasetPath, xyzPoints);
}

void PointsProperty::pushBackArray1dOfXyzPoints(const double * points, uint64_t pointCount, EML2_NS::AbstractHdfProxy * proxy)
{
	pushBackArrayOfXyzPoints(points, &pointCount, 1, proxy);
}

void PointsProperty::pushBackArray2dOfXyzPoints(const double * points, uint64_t pointCountInFastestDim, uint64_t pointCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy)
{
	const uint64_t pointCountPerDimension[2] = { pointCountInSlowestDim, pointCountInFastestDim };
	pushBackArrayOfXyzPoints(points, pointCountPerDimension, 2, proxy);
}

void PointsProperty::pushBackArray3dOfXyzPoints(const double * points, uint64_t pointCountInFastestDim, uint64_t pointCountInMiddleDim, uint64_t pointCountInSlowestDim, EML2_NS::AbstractHdfProxy * proxy)
{
	const uint64_t pointCountPerDimension[3] = { pointCountInSlowestDim, pointCountInMiddleDim, pointCountInFastestDim };
	pushBackArrayOfXyzPoints(points, pointCountPerDimension, 3, proxy);
}

void PointsProperty::pushBackArrayOfXyzPoints(double const * points, uint64_t const * pointCountByDimension, unsigned int numArrayDimensions, EML2_NS::AbstractHdfProxy * proxy)
{
	const string datasetName = "points_patch" + std::to_string(getPatchCount());

	// HDF
	std::unique_ptr<unsigned long long[]> coordinateCountByDimension(new unsigned long long[numArrayDimensions + 1]);
	for (unsigned int i = 0; i < numArrayDimensions; ++i) {
		coordinateCountByDimension[i] = pointCountByDimension[i];
	}
	coordinateCountByDimension[numArrayDimensions] = 3; // For the XYZ triplet
	proxy->writeArrayNd(getHdfGroup(),
		datasetName,
		H5T_NATIVE_DOUBLE,
		points,
		coordinateCountByDimension.get(), numArrayDimensions + 1);

	pushBackRefToExistingDataset(proxy, getHdfGroup() + "/" + datasetName);
}
