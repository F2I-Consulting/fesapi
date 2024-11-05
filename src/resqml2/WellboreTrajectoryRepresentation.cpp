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
#include "WellboreTrajectoryRepresentation.h"

#include <array>
#include <math.h>

#include "../eml2/AbstractLocal3dCrs.h"

#include "MdDatum.h"
#include "WellboreFrameRepresentation.h"

using namespace std;
using namespace RESQML2_NS;
using namespace gsoap_eml2_3;
using namespace COMMON_NS;

void WellboreTrajectoryRepresentation::setGeometry(double const* controlPoints,
	double const* inclinations, double const* azimuths, double const* controlPointParameters, uint64_t controlPointCount, int lineKind,
	EML2_NS::AbstractHdfProxy* proxy, EML2_NS::AbstractLocal3dCrs* localCrs)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}
	if (localCrs->getAxisOrder() != gsoap_eml2_3::eml23__AxisOrder2d::easting_x0020northing) {
		throw std::invalid_argument("Cannot compute inclinations and azimuths if the local CRS is not an easting northing one.");
	}

	std::unique_ptr<double[]> tangentVectors(new double[controlPointCount *3]);

	size_t j = 0;
	for (size_t i = 0; i < controlPointCount; ++i) {
		const auto sinIncl = sin(inclinations[i]);
		tangentVectors[j++] = sin(azimuths[i]) * sinIncl;
		tangentVectors[j++] = cos(azimuths[i]) * sinIncl;
		tangentVectors[j++] = localCrs->isDepthOriented() ? cos(inclinations[i]) : -cos(inclinations[i]);
	}

	// Tangent vectors are computed in the same uom and must be converted in the local CRS uses some different uoms.
	auto projectedUom = localCrs->getProjectedCrsUnit();
	auto verticalUom = localCrs->getVerticalCrsUnit();
	if (projectedUom != verticalUom) {
		if (projectedUom == gsoap_resqml2_0_1::eml20__LengthUom::m &&
			verticalUom == gsoap_resqml2_0_1::eml20__LengthUom::ft) {
			for (size_t i = 0; i < controlPointCount; ++i) {
				tangentVectors[i * 3 + 2] *= 3.2808;
			}
		}
		else if (projectedUom == gsoap_resqml2_0_1::eml20__LengthUom::ft &&
			verticalUom == gsoap_resqml2_0_1::eml20__LengthUom::m) {
			for (size_t i = 0; i < controlPointCount; ++i) {
				tangentVectors[i * 3 + 2] /= 3.2808;
			}
		}
		else {
			throw logic_error("Cannot compute inclinations and azimuths if the aeral and vertical CRS have not the same unit of measure adn are different than m and ft.");
		}
	}

	setGeometry(controlPoints, tangentVectors.get(), controlPointParameters, controlPointCount, lineKind, proxy, localCrs);
}

void WellboreTrajectoryRepresentation::getInclinationsAndAzimuths(double * inclinations, double * azimuths)
{
	auto* localCrs = getLocalCrs(0);
	if (localCrs->getAxisOrder() != gsoap_eml2_3::eml23__AxisOrder2d::easting_x0020northing) {
		throw std::invalid_argument("Cannot compute inclinations and azimuths if the local CRS is not an easting northing one.");
	}

	std::unique_ptr<double[]> tangentVectors(new double[getXyzPointCountOfAllPatches() * 3]);
	getTangentVectors(tangentVectors.get());

	// We also need to locate our tangent vectors in a same unit of measure coordinate system.
	uint64_t controlPointCount = getXyzPointCountOfAllPatches();
	auto projectedUom = localCrs->getProjectedCrsUnit();
	auto verticalUom = localCrs->getVerticalCrsUnit();
	if (projectedUom != verticalUom) {
		if (projectedUom == gsoap_resqml2_0_1::eml20__LengthUom::m &&
			verticalUom == gsoap_resqml2_0_1::eml20__LengthUom::ft) {
			for (size_t i = 0; i < controlPointCount; ++i) {
				tangentVectors[i * 3 + 2] /= 3.2808;
			}
		}
		else if (projectedUom == gsoap_resqml2_0_1::eml20__LengthUom::ft &&
			verticalUom == gsoap_resqml2_0_1::eml20__LengthUom::m) {
			for (size_t i = 0; i < controlPointCount; ++i) {
				tangentVectors[i * 3 + 2] *= 3.2808;
			}
		}
		else {
			throw logic_error("Cannot compute inclinations and azimuths if the aeral and vertical CRS have not the same unit of measure adn are different than m and ft.");
		}
	}

	for (size_t i = 0; i < controlPointCount; ++i) {
		size_t vectorIndex = i * 3;

		// Norm of the tangent vector
		double norm = sqrt(
			tangentVectors[vectorIndex] * tangentVectors[vectorIndex] +
			tangentVectors[vectorIndex + 1] * tangentVectors[vectorIndex + 1] +
			tangentVectors[vectorIndex + 2] * tangentVectors[vectorIndex + 2]);
		inclinations[i] = acos((localCrs->isDepthOriented() ? tangentVectors[vectorIndex + 2] : -tangentVectors[vectorIndex + 2]) / norm);

		// Norm of the tangent vector projected on XY plan
		norm = sqrt(
			tangentVectors[vectorIndex] * tangentVectors[vectorIndex] +
			tangentVectors[vectorIndex + 1] * tangentVectors[vectorIndex + 1]);
		azimuths[i] = norm > 0 ? acos(tangentVectors[vectorIndex + 1] / norm) : .0;
		if (tangentVectors[vectorIndex] < 0) {
			azimuths[i] *= -1;
		}
	}
}

void WellboreTrajectoryRepresentation::loadTargetRelationships()
{
	AbstractRepresentation::loadTargetRelationships();

	COMMON_NS::DataObjectReference dor = getMdDatumDor();
	convertDorIntoRel<MdDatum>(dor);

	dor = getParentTrajectoryDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<WellboreTrajectoryRepresentation>(dor);
	}
}

RESQML2_NS::MdDatum * WellboreTrajectoryRepresentation::getMdDatum() const
{
	return getRepository()->getDataObjectByUuid<RESQML2_NS::MdDatum>(getMdDatumDor().getUuid());
}

void WellboreTrajectoryRepresentation::convertMdValuesToXyzValues(double* mdValues, uint64_t mdCount, double* xyzPoints) const
{
	auto const* mdDatum = getMdDatum();
	if (mdDatum == nullptr || mdDatum->isPartial()) {
		throw logic_error("Cannot compute the XYZ points of the frame without the MD datum.");
	}

	// We add 1 trajectory station for MDDatum support.
	uint64_t trajStationCount = getXyzPointCountOfPatch(0) + 1;
	if (trajStationCount < 2) {
		throw logic_error("Cannot compute the XYZ points of the frame with a trajectory which does not contain any trajectory station.");
	}
	std::unique_ptr<double[]> mdTrajValues(new double[trajStationCount]);
	mdTrajValues[0] = .0; // MD Datum
	getMdValues(mdTrajValues.get() + 1);

	std::unique_ptr<double[]> xyzTrajValues(new double[trajStationCount * 3]);
	xyzTrajValues[0] = mdDatum->getX();
	xyzTrajValues[1] = mdDatum->getY();
	xyzTrajValues[2] = mdDatum->getZ();
	getXyzPointsOfPatch(0, xyzTrajValues.get() + 3);

	size_t nextTrajStationIndex = 1;
	for (uint64_t i = 0; i < mdCount; ++i) {
		while (nextTrajStationIndex < trajStationCount &&
			mdTrajValues[nextTrajStationIndex] <= mdValues[i]) {
			++nextTrajStationIndex;
		}
		if (nextTrajStationIndex == trajStationCount) {
			if (mdTrajValues[nextTrajStationIndex - 1] != mdValues[i]) {
				throw range_error("Cannot compute the frame MD " + std::to_string(mdValues[i]) + " because it is out of the trajectory range");
			}
			nextTrajStationIndex = nextTrajStationIndex - 1;
		}

		const size_t previousTrajStationIndex = nextTrajStationIndex - 1;
		const double mdDistance = mdTrajValues[nextTrajStationIndex] - mdTrajValues[previousTrajStationIndex];
		const double ratioFromPreviousControlPoint = mdDistance != .0
			? (mdValues[i] - mdTrajValues[previousTrajStationIndex]) / mdDistance
			: .0;

		xyzPoints[i * 3] = xyzTrajValues[previousTrajStationIndex * 3] + ratioFromPreviousControlPoint * (xyzTrajValues[nextTrajStationIndex * 3] - xyzTrajValues[previousTrajStationIndex * 3]);
		xyzPoints[i * 3 + 1] = xyzTrajValues[previousTrajStationIndex * 3 + 1] + ratioFromPreviousControlPoint * (xyzTrajValues[nextTrajStationIndex * 3 + 1] - xyzTrajValues[previousTrajStationIndex * 3 + 1]);
		xyzPoints[i * 3 + 2] = xyzTrajValues[previousTrajStationIndex * 3 + 2] + ratioFromPreviousControlPoint * (xyzTrajValues[nextTrajStationIndex * 3 + 2] - xyzTrajValues[previousTrajStationIndex * 3 + 2]);
	}
}

WellboreTrajectoryRepresentation* WellboreTrajectoryRepresentation::getParentTrajectory() const
{
	return getRepository()->getDataObjectByUuid<WellboreTrajectoryRepresentation>(getParentTrajectoryDor().getUuid());
}

std::vector<WellboreTrajectoryRepresentation *> WellboreTrajectoryRepresentation::getChildrenTrajectorySet() const
{
	return getRepository()->getSourceObjects<WellboreTrajectoryRepresentation>(this);
}

std::vector<RESQML2_NS::WellboreFrameRepresentation *> WellboreTrajectoryRepresentation::getWellboreFrameRepresentationSet() const
{
	return getRepository()->getSourceObjects<RESQML2_NS::WellboreFrameRepresentation>(this);
}

uint64_t WellboreTrajectoryRepresentation::getWellboreFrameRepresentationCount() const
{
	return getWellboreFrameRepresentationSet().size();
}

RESQML2_NS::WellboreFrameRepresentation* WellboreTrajectoryRepresentation::getWellboreFrameRepresentation(uint64_t index) const
{
	return getWellboreFrameRepresentationSet().at(index);
}
