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

#include <algorithm>

#include "../eml2_3/LocalEngineering2dCrs.h"
#include "../eml2_3/VerticalCrs.h"
#include "../tools/Trigonometry.h"

using namespace std;
using namespace EML2_NS;

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
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->XOffset;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getRepository()->getDataObjectByUuid<EML2_3_NS::LocalEngineering2dCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->LocalEngineering2dCrs->Uuid)->getOriginOrdinal1();
	}

	throw logic_error("Not implemented yet.");
}

double AbstractLocal3dCrs::getOriginOrdinal2() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->YOffset;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getRepository()->getDataObjectByUuid<EML2_3_NS::LocalEngineering2dCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->LocalEngineering2dCrs->Uuid)->getOriginOrdinal2();
	}

	throw logic_error("Not implemented yet.");
}

double AbstractLocal3dCrs::getOriginDepthOrElevation() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ZOffset;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->OriginVerticalCoordinate;
	}

	throw logic_error("Not implemented yet.");
}

double AbstractLocal3dCrs::getArealRotation() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ArealRotation->__item;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getRepository()->getDataObjectByUuid<EML2_3_NS::LocalEngineering2dCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->LocalEngineering2dCrs->Uuid)->getAzimuth();
	}

	throw logic_error("Not implemented yet.");
}

gsoap_resqml2_0_1::eml20__PlaneAngleUom AbstractLocal3dCrs::getArealRotationUom() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ArealRotation->uom;
	}
	else if (gsoapProxy2_3 != nullptr) {
		const std::string uom = getRepository()->getDataObjectByUuid<EML2_3_NS::LocalEngineering2dCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->LocalEngineering2dCrs->Uuid)->getAzimuthUomAsString();
		gsoap_resqml2_0_1::eml20__PlaneAngleUom result;
		if (gsoap_resqml2_0_1::soap_s2eml20__PlaneAngleUom(gsoapProxy2_3->soap, uom.c_str(), &result) != SOAP_OK) {
			throw logic_error("The CRS uom " + uom + " is not supported by FESAPI yet.");
		}
		return result;
	}

	throw logic_error("Not implemented yet.");
}

bool AbstractLocal3dCrs::isDepthOriented() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ZIncreasingDownward;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->VerticalAxis->Direction == gsoap_eml2_3::eml23__VerticalDirection::down;
	}

	throw logic_error("Not implemented yet.");
}

bool AbstractLocal3dCrs::isProjectedCrsDefinedWithEpsg() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedCrs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_eml20__ProjectedCrsEpsgCode;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getRepository()->getDataObjectByUuid<EML2_3_NS::LocalEngineering2dCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->LocalEngineering2dCrs->Uuid)->isProjectedCrsDefinedWithEpsg();
	}

	throw logic_error("Not implemented yet.");
}

bool AbstractLocal3dCrs::isProjectedCrsDefinedWithWkt() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		if (static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedCrs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_eml20__ProjectedUnknownCrs &&
			static_cast<gsoap_resqml2_0_1::eml20__ProjectedUnknownCrs*>(static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedCrs)->Unknown == "WKT") {
			for (gsoap_resqml2_0_1::resqml20__NameValuePair const* em : static_cast<gsoap_resqml2_0_1::resqml20__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata) {
				if (em->Name.find("projectedCrsWkt") != std::string::npos) {
					return true;
				}
			}
		}
		return false;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getRepository()->getDataObjectByUuid<EML2_3_NS::LocalEngineering2dCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->LocalEngineering2dCrs->Uuid)->isProjectedCrsDefinedWithWkt();
	}

	throw logic_error("Not implemented yet.");
}

bool AbstractLocal3dCrs::isProjectedCrsUnknown() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedCrs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_eml20__ProjectedUnknownCrs &&
			!isProjectedCrsDefinedWithWkt();
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getRepository()->getDataObjectByUuid<EML2_3_NS::LocalEngineering2dCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->LocalEngineering2dCrs->Uuid)->isProjectedCrsUnknown();
	}

	throw logic_error("Not implemented yet.");
}

std::string AbstractLocal3dCrs::getProjectedCrsUnknownReason() const
{
	cannotBePartial();

	if (!isProjectedCrsUnknown())
		throw invalid_argument("The associated projected CRS is not unknown.");

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::eml20__ProjectedUnknownCrs*>(static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedCrs)->Unknown;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getRepository()->getDataObjectByUuid<EML2_3_NS::LocalEngineering2dCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->LocalEngineering2dCrs->Uuid)->getProjectedCrsUnknownReason();
	}

	throw logic_error("Not implemented yet.");
}

std::string AbstractLocal3dCrs::getProjectedCrsWkt() const
{
	cannotBePartial();

	if (!isProjectedCrsDefinedWithWkt())
		throw invalid_argument("The associated projected CRS is not a WKT one.");

	if (gsoapProxy2_0_1 != nullptr) {
		for (gsoap_resqml2_0_1::resqml20__NameValuePair const* em : static_cast<gsoap_resqml2_0_1::resqml20__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata) {
			if (em->Name.find("projectedCrsWkt") != std::string::npos) {
				return em->Value;
			}
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getRepository()->getDataObjectByUuid<EML2_3_NS::LocalEngineering2dCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->LocalEngineering2dCrs->Uuid)->getProjectedCrsWkt();
	}

	throw logic_error("Not implemented yet.");
}

uint64_t AbstractLocal3dCrs::getProjectedCrsEpsgCode() const
{
	cannotBePartial();

	if (isProjectedCrsDefinedWithEpsg() == false)
		throw invalid_argument("The associated projected Crs is not an EPSG one.");

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::eml20__ProjectedCrsEpsgCode*>(static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedCrs)->EpsgCode;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getRepository()->getDataObjectByUuid<EML2_3_NS::LocalEngineering2dCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->LocalEngineering2dCrs->Uuid)->getProjectedCrsEpsgCode();
	}

	throw logic_error("Not implemented yet.");
}

bool AbstractLocal3dCrs::isVerticalCrsDefinedWithEpsg() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalCrs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_eml20__VerticalCrsEpsgCode;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getRepository()->getDataObjectByUuid<EML2_3_NS::VerticalCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->VerticalCrs->Uuid)->isVerticalCrsDefinedWithEpsg();
	}

	throw logic_error("Not implemented yet.");
}

bool AbstractLocal3dCrs::isVerticalCrsDefinedWithWkt() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		if (static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalCrs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_eml20__VerticalUnknownCrs &&
			getVerticalCrsUnknownReason() == "WKT") {
			for (gsoap_resqml2_0_1::resqml20__NameValuePair const* em : static_cast<gsoap_resqml2_0_1::resqml20__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata) {
				if (em->Name.find("verticalCrsWkt") != std::string::npos) {
					return true;
				}
			}
		}
		return false;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getRepository()->getDataObjectByUuid<EML2_3_NS::LocalEngineering2dCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->LocalEngineering2dCrs->Uuid)->isProjectedCrsDefinedWithWkt();
	}

	throw logic_error("Not implemented yet.");
}

bool AbstractLocal3dCrs::isVerticalCrsUnknown() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalCrs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_eml20__VerticalUnknownCrs;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getRepository()->getDataObjectByUuid<EML2_3_NS::VerticalCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->VerticalCrs->Uuid)->isVerticalCrsUnknown();
	}

	throw logic_error("Not implemented yet.");
}

std::string AbstractLocal3dCrs::getVerticalCrsUnknownReason() const
{
	cannotBePartial();

	if (!isVerticalCrsUnknown()) {
		throw invalid_argument("The associated vertical Crs is not unknown.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::eml20__VerticalUnknownCrs*>(static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalCrs)->Unknown;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getRepository()->getDataObjectByUuid<EML2_3_NS::VerticalCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->VerticalCrs->Uuid)->getVerticalCrsUnknownReason();
	}

	throw logic_error("Not implemented yet.");
}

std::string AbstractLocal3dCrs::getVerticalCrsWkt() const
{
	cannotBePartial();

	if (!isVerticalCrsDefinedWithWkt())
		throw invalid_argument("The associated vertical CRS is not a WKT one.");

	if (gsoapProxy2_0_1 != nullptr) {
		for (gsoap_resqml2_0_1::resqml20__NameValuePair const* em : static_cast<gsoap_resqml2_0_1::resqml20__AbstractResqmlDataObject*>(gsoapProxy2_0_1)->ExtraMetadata) {
			if (em->Name.find("verticalCrsWkt") != std::string::npos) {
				return em->Value;
			}
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getRepository()->getDataObjectByUuid<EML2_3_NS::VerticalCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->VerticalCrs->Uuid)->getVerticalCrsWkt();
	}

	throw logic_error("Not implemented yet.");
}

uint64_t AbstractLocal3dCrs::getVerticalCrsEpsgCode() const
{
	cannotBePartial();

	if (!isVerticalCrsDefinedWithEpsg()) {
		throw invalid_argument("The associated vertical Crs is not an EPSG one.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::eml20__VerticalCrsEpsgCode*>(static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalCrs)->EpsgCode;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getRepository()->getDataObjectByUuid<EML2_3_NS::VerticalCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->VerticalCrs->Uuid)->getVerticalCrsEpsgCode();
	}

	throw logic_error("Not implemented yet.");
}

gsoap_resqml2_0_1::eml20__LengthUom AbstractLocal3dCrs::getProjectedCrsUnit() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedUom;
	}
	else if (gsoapProxy2_3 != nullptr) {
		const std::string uom = getProjectedCrsUnitAsString();
		gsoap_resqml2_0_1::eml20__LengthUom result;
		if (gsoap_resqml2_0_1::soap_s2eml20__LengthUom(gsoapProxy2_3->soap, uom.c_str(), &result) != SOAP_OK) {
			throw logic_error("The CRS uom \"" + uom + "\" is not supported by FESAPI yet.");
		}
		return result;
	}

	throw logic_error("Not implemented yet.");
}

string AbstractLocal3dCrs::getProjectedCrsUnitAsString() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		return gsoap_resqml2_0_1::soap_eml20__LengthUom2s(gsoapProxy2_0_1->soap, static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedUom);
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getRepository()->getDataObjectByUuid<EML2_3_NS::LocalEngineering2dCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->LocalEngineering2dCrs->Uuid)->getProjectedCrsUnitAsString();
	}

	throw logic_error("Not implemented yet.");
}

gsoap_resqml2_0_1::eml20__LengthUom AbstractLocal3dCrs::getVerticalCrsUnit() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalUom;
	}
	else if (gsoapProxy2_3 != nullptr) {
		const std::string uom = static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->VerticalAxis->Uom;
		gsoap_resqml2_0_1::eml20__LengthUom result;
		if (gsoap_resqml2_0_1::soap_s2eml20__LengthUom(gsoapProxy2_3->soap, uom.c_str(), &result) != SOAP_OK) {
			throw logic_error("The CRS uom " + uom + " is not supported by FESAPI yet.");
		}
		return result;
	}

	throw logic_error("Not implemented yet.");
}

string AbstractLocal3dCrs::getVerticalCrsUnitAsString() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		return gsoap_resqml2_0_1::soap_eml20__LengthUom2s(gsoapProxy2_0_1->soap, static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalUom);
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->VerticalAxis->Uom;
	}

	throw logic_error("Not implemented yet.");
}

std::string AbstractLocal3dCrs::getTimeUomAsString() const
{
	return gsoap_resqml2_0_1::soap_eml20__TimeUom2s(getGsoapContext(), getTimeUom());
}

gsoap_eml2_3::eml23__AxisOrder2d AbstractLocal3dCrs::getAxisOrder() const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		auto axisOrder = static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedAxisOrder;
		const std::string axisOrderStr = gsoap_resqml2_0_1::soap_eml20__AxisOrder2d2s(gsoapProxy2_0_1->soap, axisOrder);

		gsoap_eml2_3::eml23__AxisOrder2d result;
		if (gsoap_eml2_3::soap_s2eml23__AxisOrder2d(gsoapProxy2_0_1->soap, axisOrderStr.c_str(), &result) != SOAP_OK) {
			throw logic_error("The axis order \"" + axisOrderStr + "\" is not supported by FESAPI yet.");
		}
		return result;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getRepository()->getDataObjectByUuid<EML2_3_NS::LocalEngineering2dCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->LocalEngineering2dCrs->Uuid)->getAxisOrder();
	}

	throw logic_error("Not implemented yet.");
}

void AbstractLocal3dCrs::setAxisOrder(gsoap_eml2_3::eml23__AxisOrder2d axisOrder) const
{
	cannotBePartial();

	if (gsoapProxy2_0_1 != nullptr) {
		const std::string axisOrderStr = gsoap_eml2_3::soap_eml23__AxisOrder2d2s(gsoapProxy2_0_1->soap, axisOrder);
		gsoap_resqml2_0_1::eml20__AxisOrder2d result;
		if (gsoap_resqml2_0_1::soap_s2eml20__AxisOrder2d(gsoapProxy2_3->soap, axisOrderStr.c_str(), &result) != SOAP_OK) {
			throw logic_error("The axis order \"" + axisOrderStr + "\" is not supported by FESAPI yet.");
		}
		
		static_cast<gsoap_resqml2_0_1::resqml20__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedAxisOrder = result;
	}
	else if (gsoapProxy2_3 != nullptr) {
		getRepository()->getDataObjectByUuid<EML2_3_NS::LocalEngineering2dCrs>(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->LocalEngineering2dCrs->Uuid)->setAxisOrder(axisOrder);
	}

	throw logic_error("Not implemented yet.");
}
