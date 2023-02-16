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
#include <stdexcept>
#include <limits>
#include <math.h>

#include "AbstractLocal3dCrs.h"
#include "DeviationSurveyRepresentation.h"
#include "MdDatum.h"
#include "WellboreFrameRepresentation.h"

using namespace std;
using namespace RESQML2_NS;
using namespace gsoap_eml2_3;
using namespace COMMON_NS;

void WellboreTrajectoryRepresentation::setGeometry(double const* controlPoints,
	double const* inclinations, double const* azimuths, double const* controlPointParameters, uint64_t controlPointCount, int lineKind,
	EML2_NS::AbstractHdfProxy* proxy, AbstractLocal3dCrs* localCrs)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}
	if (localCrs->getAxisOrder() != gsoap_resqml2_0_1::eml20__AxisOrder2d::easting_x0020northing) {
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
	if (localCrs->getAxisOrder() != gsoap_resqml2_0_1::eml20__AxisOrder2d::easting_x0020northing) {
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

	dor = getDeviationSurveyDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<DeviationSurveyRepresentation>(dor);
	}

	dor = getParentTrajectoryDor();
	if (!dor.isEmpty()) {
		convertDorIntoRel<WellboreTrajectoryRepresentation>(dor);
	}
}

RESQML2_NS::MdDatum * WellboreTrajectoryRepresentation::getMdDatum() const
{
	return getRepository()->getDataObjectByUuid<RESQML2_NS::MdDatum>(getMdDatumDor().getUuid());
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

unsigned int WellboreTrajectoryRepresentation::getWellboreFrameRepresentationCount() const
{
	const size_t result = getWellboreFrameRepresentationSet().size();
	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too much associated WellboreFrameRepresentation.");
	}

	return static_cast<unsigned int>(result);
}

RESQML2_NS::WellboreFrameRepresentation * WellboreTrajectoryRepresentation::getWellboreFrameRepresentation(unsigned int index) const
{
	const std::vector<RESQML2_NS::WellboreFrameRepresentation *>& wfrs = getWellboreFrameRepresentationSet();

	if (index >= wfrs.size()) {
		throw out_of_range("The index if out of range");
	}

	return wfrs[index];
}

DeviationSurveyRepresentation* WellboreTrajectoryRepresentation::getDeviationSurvey() const
{
	return getRepository()->getDataObjectByUuid<DeviationSurveyRepresentation>(getDeviationSurveyDor().getUuid());
}
