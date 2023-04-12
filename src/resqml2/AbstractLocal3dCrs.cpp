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
#include "AbstractLocal3dCrs.h"

#include <stdexcept>
#include <algorithm>

#include "../tools/Trigonometry.h"

using namespace std;
using namespace RESQML2_NS;

void AbstractLocal3dCrs::loadTargetRelationships() {
}

void AbstractLocal3dCrs::convertXyzPointsToGlobalCrs(double * xyzPoints, uint64_t xyzPointCount, bool withoutTranslation) const
{
	uint64_t coordinateCount = xyzPointCount * 3;

	if (getArealRotation() != .0)
	{
		pair<double, double> xRotatedUnitVector = trigonometry::rotateXY(1.0, .0, -getArealRotation(), getArealRotationUom());
		pair<double, double> yRotatedUnitVector = trigonometry::rotateXY(.0, 1.0, -getArealRotation(), getArealRotationUom());
		for (uint64_t i = 0; i < coordinateCount; i += 3)
		{
			xyzPoints[i] = xRotatedUnitVector.first * xyzPoints[i] + yRotatedUnitVector.first * xyzPoints[i];
			xyzPoints[i + 1] = xRotatedUnitVector.second * xyzPoints[i + 1] + yRotatedUnitVector.second * xyzPoints[i + 1];
		}
	}

	if (!withoutTranslation)
	{
		const double originOrdinal1 = getOriginOrdinal1();
		const double originOrdinal2 = getOriginOrdinal2();
		const double originOrdinal3 = getZOffset();
		if (originOrdinal1 == .0 && originOrdinal2 == .0 && originOrdinal3 == .0)
			return;

		for (uint64_t i = 0; i < coordinateCount; i += 3)
		{
			xyzPoints[i] += originOrdinal1;
			xyzPoints[i + 1] += originOrdinal2;
			xyzPoints[i + 2] += originOrdinal3;
		}
	}
}

double AbstractLocal3dCrs::getOriginOrdinal1() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->XOffset;
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
}

double AbstractLocal3dCrs::getOriginOrdinal2() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->YOffset;
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
}

double AbstractLocal3dCrs::getOriginDepthOrElevation() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ZOffset;
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
}

double AbstractLocal3dCrs::getArealRotation() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ArealRotation->__item;
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
}

gsoap_resqml2_0_1::eml20__PlaneAngleUom AbstractLocal3dCrs::getArealRotationUom() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ArealRotation->uom;
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
}

bool AbstractLocal3dCrs::isDepthOriented() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ZIncreasingDownward;
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found.It is probably a partial one.");
}

bool AbstractLocal3dCrs::isProjectedCrsDefinedWithEpsg() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedCrs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_eml20__ProjectedCrsEpsgCode;
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
}

bool AbstractLocal3dCrs::isProjectedCrsUnknown() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedCrs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_eml20__ProjectedUnknownCrs;
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
}

const std::string & AbstractLocal3dCrs::getProjectedCrsUnknownReason() const
{
	if (isProjectedCrsUnknown() == false)
		throw invalid_argument("The associated projected Crs is not unknown.");

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::eml20__ProjectedUnknownCrs*>(static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedCrs)->Unknown;
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
}

uint64_t AbstractLocal3dCrs::getProjectedCrsEpsgCode() const
{
	if (isProjectedCrsDefinedWithEpsg() == false)
		throw invalid_argument("The associated projected Crs is not an EPSG one.");

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::eml20__ProjectedCrsEpsgCode*>(static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedCrs)->EpsgCode;
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
}

bool AbstractLocal3dCrs::isVerticalCrsDefinedWithEpsg() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalCrs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_eml20__VerticalCrsEpsgCode;
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
}

bool AbstractLocal3dCrs::isVerticalCrsUnknown() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalCrs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_eml20__VerticalUnknownCrs;
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
}

const std::string & AbstractLocal3dCrs::getVerticalCrsUnknownReason() const
{
	if (isVerticalCrsUnknown() == false)
		throw invalid_argument("The associated vertical Crs is not unknown.");

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::eml20__VerticalUnknownCrs*>(static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalCrs)->Unknown;
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
}

uint64_t AbstractLocal3dCrs::getVerticalCrsEpsgCode() const
{
	if (isVerticalCrsDefinedWithEpsg() == false)
		throw invalid_argument("The associated vertical Crs is not an EPSG one.");

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::eml20__VerticalCrsEpsgCode*>(static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalCrs)->EpsgCode;
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
}

gsoap_resqml2_0_1::eml20__LengthUom AbstractLocal3dCrs::getProjectedCrsUnit() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedUom;
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
}

string AbstractLocal3dCrs::getProjectedCrsUnitAsString() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return gsoap_resqml2_0_1::soap_eml20__LengthUom2s(gsoapProxy2_0_1->soap, static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedUom);
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
}

gsoap_resqml2_0_1::eml20__LengthUom AbstractLocal3dCrs::getVerticalCrsUnit() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalUom;
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
}

string AbstractLocal3dCrs::getVerticalCrsUnitAsString() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return gsoap_resqml2_0_1::soap_eml20__LengthUom2s(gsoapProxy2_0_1->soap, static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalUom);
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
}

gsoap_resqml2_0_1::eml20__AxisOrder2d AbstractLocal3dCrs::getAxisOrder() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedAxisOrder;
	}

	throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
}

void AbstractLocal3dCrs::setAxisOrder(gsoap_resqml2_0_1::eml20__AxisOrder2d axisOrder) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedAxisOrder = axisOrder;
	}
	else {
		throw logic_error("The local CRS UUID " + getUuid() + " cannot be found. It is probably a partial one.");
	}
}
