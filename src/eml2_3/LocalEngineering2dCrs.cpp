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
#include "LocalEngineering2dCrs.h"

#include <stdexcept>

#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace std;
using namespace EML2_3_NS;
using namespace gsoap_eml2_3;

void LocalEngineering2dCrs::init(eml23__LocalEngineering2dCrs* local2dCrs, const std::string& guid, const std::string& title,
	double originOrdinal1, double originOrdinal2, gsoap_eml2_3::eml23__LengthUom projectedUom,
	double azimuth, gsoap_eml2_3::eml23__PlaneAngleUom azimuthUom, eml23__NorthReferenceKind azimuthReference,
	eml23__AxisOrder2d axisOrder)
{
	local2dCrs->Azimuth = soap_new_eml23__PlaneAngleMeasureExt(gsoapProxy2_3->soap);
	local2dCrs->Azimuth->__item = azimuth;
	local2dCrs->Azimuth->uom = soap_eml23__PlaneAngleUom2s(gsoapProxy2_3->soap, azimuthUom);
	local2dCrs->AzimuthReference = azimuthReference;
	local2dCrs->OriginProjectedCoordinate1 = originOrdinal1;
	local2dCrs->OriginProjectedCoordinate2 = originOrdinal2;

	//Local Axes
	local2dCrs->HorizontalAxes = soap_new_eml23__HorizontalAxes(gsoapProxy2_3->soap);
	local2dCrs->HorizontalAxes->IsTime = false;
	local2dCrs->HorizontalAxes->Uom = soap_eml23__LengthUom2s(gsoapProxy2_3->soap, projectedUom);
	switch (axisOrder) {
	case eml23__AxisOrder2d::easting_x0020northing:
		local2dCrs->HorizontalAxes->Direction1 = eml23__AxisDirectionKind::east;
		local2dCrs->HorizontalAxes->Direction2 = eml23__AxisDirectionKind::north;
		break;
	case eml23__AxisOrder2d::easting_x0020southing:
		local2dCrs->HorizontalAxes->Direction1 = eml23__AxisDirectionKind::east;
		local2dCrs->HorizontalAxes->Direction2 = eml23__AxisDirectionKind::south;
		break;
	case eml23__AxisOrder2d::northing_x0020easting:
		local2dCrs->HorizontalAxes->Direction1 = eml23__AxisDirectionKind::north;
		local2dCrs->HorizontalAxes->Direction2 = eml23__AxisDirectionKind::east;
		break;
	case eml23__AxisOrder2d::northing_x0020westing:
		local2dCrs->HorizontalAxes->Direction1 = eml23__AxisDirectionKind::north;
		local2dCrs->HorizontalAxes->Direction2 = eml23__AxisDirectionKind::west;
		break;
	case eml23__AxisOrder2d::southing_x0020easting:
		local2dCrs->HorizontalAxes->Direction1 = eml23__AxisDirectionKind::south;
		local2dCrs->HorizontalAxes->Direction2 = eml23__AxisDirectionKind::east;
		break;
	case eml23__AxisOrder2d::southing_x0020westing:
		local2dCrs->HorizontalAxes->Direction1 = eml23__AxisDirectionKind::south;
		local2dCrs->HorizontalAxes->Direction2 = eml23__AxisDirectionKind::west;
		break;
	case eml23__AxisOrder2d::westing_x0020northing:
		local2dCrs->HorizontalAxes->Direction1 = eml23__AxisDirectionKind::west;
		local2dCrs->HorizontalAxes->Direction2 = eml23__AxisDirectionKind::north;
		break;
	case eml23__AxisOrder2d::westing_x0020southing:
		local2dCrs->HorizontalAxes->Direction1 = eml23__AxisDirectionKind::west;
		local2dCrs->HorizontalAxes->Direction2 = eml23__AxisDirectionKind::south;
		break;
	default: throw range_error("This axis order is not supported yet.");
	}

	// ProjectedCrs
	eml23__ProjectedCrs* projectedCrs = soap_new_eml23__ProjectedCrs(gsoapProxy2_3->soap);
	local2dCrs->OriginProjectedCrs = projectedCrs;
	projectedCrs->AxisOrder = axisOrder;
	projectedCrs->uom = soap_new_std__string(gsoapProxy2_3->soap);
	projectedCrs->uom->assign(soap_eml23__LengthUom2s(gsoapProxy2_3->soap, projectedUom));

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	projectedCrs->schemaVersion = getXmlNamespaceVersion();
	projectedCrs->uuid = boost::uuids::to_string(boost::uuids::nil_uuid());
	projectedCrs->Citation = gsoap_eml2_3::soap_new_eml23__Citation(gsoapProxy2_3->soap);
	projectedCrs->Citation->Title = getTitle() + " ProjectedCrs";
	projectedCrs->Citation->Originator = getOriginator();
	projectedCrs->Citation->Format = getFormat();
	projectedCrs->Citation->Creation = getCreationAsTimeStructure();
}

LocalEngineering2dCrs::LocalEngineering2dCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
	uint64_t projectedEpsgCode,
	double originOrdinal1, double originOrdinal2, gsoap_eml2_3::eml23__LengthUom projectedUom,
	double azimuth, gsoap_eml2_3::eml23__PlaneAngleUom azimuthUom, eml23__NorthReferenceKind azimuthReference,
	eml23__AxisOrder2d axisOrder)
{
	if (repo == nullptr) {
		throw invalid_argument("The soap context where the local 2d CRS will be instantiated must exist.");
	}
	if (projectedEpsgCode == 0) {
		throw invalid_argument("The EPSG code must be positive");
	}

	gsoapProxy2_3 = soap_new_eml23__LocalEngineering2dCrs(repo->getGsoapContext());
	eml23__LocalEngineering2dCrs* local2dCrs = static_cast<eml23__LocalEngineering2dCrs*>(gsoapProxy2_3);
	init(local2dCrs, guid, title,
		originOrdinal1, originOrdinal2, projectedUom,
		azimuth, azimuthUom, azimuthReference,
		axisOrder);

	auto* epsgCrs = soap_new_eml23__ProjectedEpsgCrs(gsoapProxy2_3->soap);
	epsgCrs->EpsgCode = projectedEpsgCode;
	local2dCrs->OriginProjectedCrs->AbstractProjectedCrs = epsgCrs;

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
}

LocalEngineering2dCrs::LocalEngineering2dCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
	std::string projectedDefinition,
	double originOrdinal1, double originOrdinal2, gsoap_eml2_3::eml23__LengthUom projectedUom,
	double azimuth, gsoap_eml2_3::eml23__PlaneAngleUom azimuthUom, eml23__NorthReferenceKind azimuthReference,
	eml23__AxisOrder2d axisOrder)
{
	if (repo == nullptr) {
		throw invalid_argument("The soap context where the local 2d CRS will be instantiated must exist.");
	}

	gsoapProxy2_3 = soap_new_eml23__LocalEngineering2dCrs(repo->getGsoapContext());
	eml23__LocalEngineering2dCrs* local2dCrs = static_cast<eml23__LocalEngineering2dCrs*>(gsoapProxy2_3);
	init(local2dCrs, guid, title,
		originOrdinal1, originOrdinal2, projectedUom,
		azimuth, azimuthUom, azimuthReference,
		axisOrder);

	if (projectedDefinition.size() < 5 || projectedDefinition.substr(0, 5) != "PROJC") { // Either PROJCRS or alias PROJCS
		auto* unknownCrs = soap_new_eml23__ProjectedUnknownCrs(gsoapProxy2_3->soap);
		unknownCrs->Unknown = projectedDefinition;
		local2dCrs->OriginProjectedCrs->AbstractProjectedCrs = unknownCrs;
	}
	else {
		auto* wktCrs = soap_new_eml23__ProjectedWktCrs(gsoapProxy2_3->soap);
		wktCrs->WellKnownText = projectedDefinition;
		local2dCrs->OriginProjectedCrs->AbstractProjectedCrs = wktCrs;
	}

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
}

double LocalEngineering2dCrs::getOriginOrdinal1() const
{
	return static_cast<gsoap_eml2_3::eml23__LocalEngineering2dCrs*>(gsoapProxy2_3)->OriginProjectedCoordinate1;
}

double LocalEngineering2dCrs::getOriginOrdinal2() const
{
	return static_cast<gsoap_eml2_3::eml23__LocalEngineering2dCrs*>(gsoapProxy2_3)->OriginProjectedCoordinate2;
}

double LocalEngineering2dCrs::getAzimuth() const
{
	return static_cast<gsoap_eml2_3::eml23__LocalEngineering2dCrs*>(gsoapProxy2_3)->Azimuth->__item;
}

std::string LocalEngineering2dCrs::getAzimuthUomAsString() const
{
	return static_cast<gsoap_eml2_3::eml23__LocalEngineering2dCrs*>(gsoapProxy2_3)->Azimuth->uom;
}

bool LocalEngineering2dCrs::isProjectedCrsDefinedWithEpsg() const
{
	return static_cast<gsoap_eml2_3::eml23__LocalEngineering2dCrs*>(gsoapProxy2_3)->OriginProjectedCrs->AbstractProjectedCrs->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__ProjectedEpsgCrs;
}

bool LocalEngineering2dCrs::isProjectedCrsDefinedWithWkt() const
{
	return static_cast<gsoap_eml2_3::eml23__LocalEngineering2dCrs*>(gsoapProxy2_3)->OriginProjectedCrs->AbstractProjectedCrs->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__ProjectedWktCrs;
}

bool LocalEngineering2dCrs::isProjectedCrsUnknown() const
{
	return static_cast<gsoap_eml2_3::eml23__LocalEngineering2dCrs*>(gsoapProxy2_3)->OriginProjectedCrs->AbstractProjectedCrs->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__ProjectedUnknownCrs;
}

std::string LocalEngineering2dCrs::getProjectedCrsUnknownReason() const
{
	return static_cast<gsoap_eml2_3::eml23__ProjectedUnknownCrs*>(static_cast<gsoap_eml2_3::eml23__LocalEngineering2dCrs*>(gsoapProxy2_3)->OriginProjectedCrs->AbstractProjectedCrs)->Unknown;
}

std::string LocalEngineering2dCrs::getProjectedCrsWkt() const
{
	return static_cast<gsoap_eml2_3::eml23__ProjectedWktCrs*>(static_cast<gsoap_eml2_3::eml23__LocalEngineering2dCrs*>(gsoapProxy2_3)->OriginProjectedCrs->AbstractProjectedCrs)->WellKnownText;
}

int64_t LocalEngineering2dCrs::getProjectedCrsEpsgCode() const
{
	return static_cast<gsoap_eml2_3::eml23__ProjectedEpsgCrs*>(static_cast<gsoap_eml2_3::eml23__LocalEngineering2dCrs*>(gsoapProxy2_3)->OriginProjectedCrs->AbstractProjectedCrs)->EpsgCode;
}

std::string LocalEngineering2dCrs::getProjectedCrsUnitAsString() const
{
	return static_cast<gsoap_eml2_3::eml23__LocalEngineering2dCrs*>(gsoapProxy2_3)->HorizontalAxes->Uom;
}

gsoap_eml2_3::eml23__AxisOrder2d LocalEngineering2dCrs::getAxisOrder() const
{
	return static_cast<gsoap_eml2_3::eml23__LocalEngineering2dCrs*>(gsoapProxy2_3)->OriginProjectedCrs->AxisOrder;
}

void LocalEngineering2dCrs::setAxisOrder(gsoap_eml2_3::eml23__AxisOrder2d axisOrder) const
{
	static_cast<gsoap_eml2_3::eml23__LocalEngineering2dCrs*>(gsoapProxy2_3)->OriginProjectedCrs->AxisOrder = axisOrder;
}
