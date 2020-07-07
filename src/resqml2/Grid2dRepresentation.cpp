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
#include "Grid2dRepresentation.h"

#include <stdexcept>

#include "AbstractLocal3dCrs.h"

using namespace std;
using namespace RESQML2_NS;

const char* Grid2dRepresentation::XML_TAG = "Grid2dRepresentation";

ULONG64 Grid2dRepresentation::getXyzPointCountOfPatch(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index patch is not in the allowed range of patch.");
	}

	return getNodeCountAlongIAxis() * getNodeCountAlongJAxis();
}

void Grid2dRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double *) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index patch is not in the allowed range of patch.");
	}

	throw logic_error("Please compute X and Y values with the lattice information.");
}

void Grid2dRepresentation::getZValuesInGlobalCrs(double * values) const
{
	getZValues(values);

	RESQML2_NS::AbstractLocal3dCrs* localCrs = !getSupportingRepresentationDor().isEmpty()
		? getSupportingRepresentation()->getLocalCrs(0)
		: getLocalCrs(0);

	if (localCrs != nullptr) {
		const ULONG64 nodeCount = getXyzPointCountOfPatch(0);
		const double zOffset = localCrs->getOriginDepthOrElevation();
		if (zOffset != .0) {
			for (size_t index = 0; index < nodeCount; ++index)
				values[index] += zOffset;
		}
	}
}

double Grid2dRepresentation::getComponentInGlobalCrs(double x, double y, double z, size_t componentIndex, bool withoutTranslation) const
{
	double result[3] = { x, y, z };
	if (result[componentIndex] != result[componentIndex]) {
		return result[componentIndex];
	}

	// there can be only one patch in a 2d grid repesentation
	RESQML2_NS::AbstractLocal3dCrs* localCrs = componentIndex != 2 && !getSupportingRepresentationDor().isEmpty()
		? getSupportingRepresentation()->getLocalCrs(0)
		: getLocalCrs(0);

	localCrs->convertXyzPointsToGlobalCrs(result, 1, withoutTranslation);

	return result[componentIndex];
}

double Grid2dRepresentation::getXOriginInGlobalCrs() const
{
	return getComponentInGlobalCrs(getXOrigin(), getYOrigin(), getZOrigin(), 0);
}

double Grid2dRepresentation::getYOriginInGlobalCrs() const
{
	return getComponentInGlobalCrs(getXOrigin(), getYOrigin(), getZOrigin(), 1);
}

double Grid2dRepresentation::getZOriginInGlobalCrs() const
{
	return getComponentInGlobalCrs(getXOrigin(), getYOrigin(), getZOrigin(), 2);
}

double Grid2dRepresentation::getXJOffsetInGlobalCrs() const
{
	return getComponentInGlobalCrs(getXJOffset(), getYJOffset(), getZJOffset(), 0, true);
}

double Grid2dRepresentation::getYJOffsetInGlobalCrs() const
{
	return getComponentInGlobalCrs(getXJOffset(), getYJOffset(), getZJOffset(), 1, true);
}

double Grid2dRepresentation::getZJOffsetInGlobalCrs() const
{
	return getComponentInGlobalCrs(getXJOffset(), getYJOffset(), getZJOffset(), 2, true);
}

double Grid2dRepresentation::getXIOffsetInGlobalCrs() const
{
	return getComponentInGlobalCrs(getXIOffset(), getYIOffset(), getZIOffset(), 0, true);
}

double Grid2dRepresentation::getYIOffsetInGlobalCrs() const
{
	return getComponentInGlobalCrs(getXIOffset(), getYIOffset(), getZIOffset(), 1, true);
}

double Grid2dRepresentation::getZIOffsetInGlobalCrs() const
{
	return getComponentInGlobalCrs(getXIOffset(), getYIOffset(), getZIOffset(), 2, true);
}

Grid2dRepresentation* Grid2dRepresentation::getSupportingRepresentation() const
{
	return getRepository()->getDataObjectByUuid<Grid2dRepresentation>(getSupportingRepresentationDor().getUuid());
}

void Grid2dRepresentation::loadTargetRelationships()
{
	AbstractSurfaceRepresentation::loadTargetRelationships();

	// Base representation
	COMMON_NS::DataObjectReference dor = getSupportingRepresentationDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<Grid2dRepresentation>(dor);
	}
}
