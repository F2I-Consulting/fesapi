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
#include "LocalEngineeringCompoundCrs.h"

#include <stdexcept>

#include <boost/version.hpp>
#if BOOST_VERSION < 106600
#include <boost/uuid/name_generator.hpp>
#else
#include <boost/uuid/name_generator_sha1.hpp>
#endif
#include <boost/uuid/uuid_io.hpp>

#include "LocalEngineering2dCrs.h"
#include "VerticalCrs.h"

using namespace std;
using namespace EML2_3_NS;
using namespace gsoap_eml2_3;

void LocalEngineeringCompoundCrs::init(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
	uint64_t projectedEpsgCode, std::string projectedDefinition,
	double originOrdinal1, double originOrdinal2, gsoap_resqml2_0_1::eml20__LengthUom projectedUom,
	double azimuth, gsoap_eml2_3::eml23__PlaneAngleUom azimuthUom, gsoap_eml2_3::eml23__NorthReferenceKind azimuthReference,
	gsoap_eml2_3::eml23__AxisOrder2d axisOrder,
	uint64_t verticalEpsgCode, std::string verticalDefinition,
	double originOrdinal3, gsoap_resqml2_0_1::eml20__LengthUom verticalUom,
	bool isUpOriented)
{
	if (repo == nullptr) {
		throw invalid_argument("The soap context where the local CRS will be instantiated must exist.");
	}
	if (projectedDefinition.empty() && projectedEpsgCode == 0) {
		throw invalid_argument("The projected CRS must either have a non null EPSG code or a reason why it is unkown.");
	}
	if (verticalDefinition.empty() && verticalEpsgCode == 0) {
		throw invalid_argument("The vertical CRS must either have a non null EPSG code or a reason why it is unkown.");
	}

	gsoapProxy2_3 = soap_new_eml23__LocalEngineeringCompoundCrs(repo->getGsoapContext());
	eml23__LocalEngineeringCompoundCrs* local3dCrs = static_cast<eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3);

	// Uuid creation
#if BOOST_VERSION < 106600
	// According to https://datatracker.ietf.org/doc/html/rfc4122#appendix-C the DNS uuid is 6ba7b810-9dad-11d1-80b4-00c04fd430c8
	boost::uuids::uuid dnsUuid = { {
		0x6b, 0xa7, 0xb8, 0x10, 0x9d, 0xad, 0x11, 0xd1 ,
		0x80, 0xb4, 0x00, 0xc0, 0x4f, 0xd4, 0x30, 0xc8
	}};
	boost::uuids::name_generator gen(dnsUuid);
	boost::uuids::name_generator finalGen(gen("f2i-consulting.com"));
#else
	boost::uuids::name_generator_sha1 gen(boost::uuids::ns::dns());
	boost::uuids::name_generator_sha1 finalGen(gen("f2i-consulting.com"));
#endif

	// uom conversion
	std::string str = gsoap_resqml2_0_1::soap_eml20__LengthUom2s(gsoapProxy2_3->soap, projectedUom);
	gsoap_eml2_3::eml23__LengthUom projectedLengthUom;
	if (gsoap_eml2_3::soap_s2eml23__LengthUom(gsoapProxy2_3->soap, str.c_str(), &projectedLengthUom) != SOAP_OK) {
		throw invalid_argument("Cannot recognize the uom \"" + str + "\"");
	}
	std::string verticalUomStr = gsoap_resqml2_0_1::soap_eml20__LengthUom2s(gsoapProxy2_3->soap, verticalUom);
	gsoap_eml2_3::eml23__LengthUom verticalLengthUom;
	if (gsoap_eml2_3::soap_s2eml23__LengthUom(gsoapProxy2_3->soap, verticalUomStr.c_str(), &verticalLengthUom) != SOAP_OK) {
		throw invalid_argument("Cannot recognize the uom \"" + verticalUomStr + "\"");
	}

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	// 2d crs
	LocalEngineering2dCrs* local2dCrs = !projectedDefinition.empty()
		? new LocalEngineering2dCrs(repo, boost::uuids::to_string(finalGen(gsoapProxy2_3->uuid + "_ProjectedStringRepresentedCrs")), title + " LocalEngineering2dCrs",
			projectedDefinition,
			originOrdinal1, originOrdinal2, projectedLengthUom,
			azimuth, azimuthUom, azimuthReference,
			axisOrder)
		: new LocalEngineering2dCrs(repo, boost::uuids::to_string(finalGen(gsoapProxy2_3->uuid + "_ProjectedEpsgCrs")), title + " LocalEngineering2dCrs",
			projectedEpsgCode,
			originOrdinal1, originOrdinal2, projectedLengthUom,
			azimuth, azimuthUom, azimuthReference,
			axisOrder);
	local3dCrs->LocalEngineering2dCrs = local2dCrs->newEml23Reference();
	repo->addRelationship(this, local2dCrs);

	// Vertical CRS
	VerticalCrs* verticalCrs = !verticalDefinition.empty()
		? new VerticalCrs(repo, boost::uuids::to_string(finalGen(gsoapProxy2_3->uuid + "_VerticalStringRepresentedCrs")), title + " VerticalCrs",
			verticalDefinition,
			verticalLengthUom,
			isUpOriented)
		: new VerticalCrs(repo, boost::uuids::to_string(finalGen(gsoapProxy2_3->uuid + "_VerticalEpsgCrs")), title + " VerticalCrs",
			verticalEpsgCode,
			verticalLengthUom,
			isUpOriented);
	local3dCrs->VerticalCrs = verticalCrs->newEml23Reference();
	repo->addRelationship(this, verticalCrs);
	local3dCrs->OriginVerticalCoordinate = originOrdinal3;
	local3dCrs->VerticalAxis = soap_new_eml23__VerticalAxis(repo->getGsoapContext());
	local3dCrs->VerticalAxis->IsTime = false;
	local3dCrs->VerticalAxis->Uom = verticalUomStr;
	local3dCrs->VerticalAxis->Direction = isUpOriented ? eml23__VerticalDirection::up : eml23__VerticalDirection::down;

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
}

void LocalEngineeringCompoundCrs::init(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
	uint64_t projectedEpsgCode, std::string projectedDefinition,
	double originOrdinal1, double originOrdinal2, gsoap_resqml2_0_1::eml20__LengthUom projectedUom,
	double azimuth, gsoap_eml2_3::eml23__PlaneAngleUom azimuthUom, gsoap_eml2_3::eml23__NorthReferenceKind azimuthReference,
	gsoap_eml2_3::eml23__AxisOrder2d axisOrder,
	uint64_t verticalEpsgCode, std::string verticalDefinition,
	double originOrdinal3, gsoap_resqml2_0_1::eml20__LengthUom verticalUom,
	gsoap_resqml2_0_1::eml20__TimeUom timeUom,
	bool isUpOriented)
{
	init(repo, guid, title,
		projectedEpsgCode, projectedDefinition,
		originOrdinal1, originOrdinal2, projectedUom,
		azimuth, azimuthUom, azimuthReference,
		axisOrder,
		verticalEpsgCode, verticalDefinition,
		originOrdinal3, verticalUom,
		isUpOriented);
	static_cast<eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->VerticalAxis->IsTime = true;
	static_cast<eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->VerticalAxis->Uom = gsoap_resqml2_0_1::soap_eml20__TimeUom2s(gsoapProxy2_3->soap, timeUom);
}

LocalEngineeringCompoundCrs::LocalEngineeringCompoundCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
	double originOrdinal1, double originOrdinal2, double originOrdinal3,
	double arealRotation,
	gsoap_resqml2_0_1::eml20__LengthUom projectedUom, uint64_t projectedEpsgCode,
	gsoap_resqml2_0_1::eml20__LengthUom verticalUom, uint64_t verticalEpsgCode, bool isUpOriented)
{
	init(repo, guid, title,
		projectedEpsgCode, "",
		originOrdinal1, originOrdinal2, projectedUom,
		arealRotation, gsoap_eml2_3::eml23__PlaneAngleUom::rad, gsoap_eml2_3::eml23__NorthReferenceKind::grid_x0020north,
		gsoap_eml2_3::eml23__AxisOrder2d::easting_x0020northing,
		verticalEpsgCode, "",
		originOrdinal3, verticalUom,
		isUpOriented);
}

LocalEngineeringCompoundCrs::LocalEngineeringCompoundCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
	double originOrdinal1, double originOrdinal2, double originOrdinal3,
	double arealRotation,
	gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string& projectedDefinition,
	gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string& verticalDefinition, bool isUpOriented)
{
	init(repo, guid, title,
		0, projectedDefinition,
		originOrdinal1, originOrdinal2, projectedUom,
		arealRotation, gsoap_eml2_3::eml23__PlaneAngleUom::rad, gsoap_eml2_3::eml23__NorthReferenceKind::grid_x0020north,
		gsoap_eml2_3::eml23__AxisOrder2d::easting_x0020northing,
		0, verticalDefinition,
		originOrdinal3, verticalUom,
		isUpOriented);
}

LocalEngineeringCompoundCrs::LocalEngineeringCompoundCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
	double originOrdinal1, double originOrdinal2, double originOrdinal3,
	double arealRotation,
	gsoap_resqml2_0_1::eml20__LengthUom projectedUom, uint64_t projectedEpsgCode,
	gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string& verticalDefinition, bool isUpOriented)
{
	init(repo, guid, title,
		projectedEpsgCode, "",
		originOrdinal1, originOrdinal2, projectedUom,
		arealRotation, gsoap_eml2_3::eml23__PlaneAngleUom::rad, gsoap_eml2_3::eml23__NorthReferenceKind::grid_x0020north,
		gsoap_eml2_3::eml23__AxisOrder2d::easting_x0020northing,
		0, verticalDefinition,
		originOrdinal3, verticalUom,
		isUpOriented);
}

LocalEngineeringCompoundCrs::LocalEngineeringCompoundCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
	double originOrdinal1, double originOrdinal2, double originOrdinal3,
	double arealRotation,
	gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string& projectedDefinition,
	gsoap_resqml2_0_1::eml20__LengthUom verticalUom, uint64_t verticalEpsgCode, bool isUpOriented)
{
	init(repo, guid, title,
		0, projectedDefinition,
		originOrdinal1, originOrdinal2, projectedUom,
		arealRotation, gsoap_eml2_3::eml23__PlaneAngleUom::rad, gsoap_eml2_3::eml23__NorthReferenceKind::grid_x0020north,
		gsoap_eml2_3::eml23__AxisOrder2d::easting_x0020northing,
		verticalEpsgCode, "",
		originOrdinal3, verticalUom,
		isUpOriented);
}

LocalEngineeringCompoundCrs::LocalEngineeringCompoundCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
	double originOrdinal1, double originOrdinal2, double originOrdinal3,
	double arealRotation,
	gsoap_resqml2_0_1::eml20__LengthUom projectedUom, uint64_t projectedEpsgCode,
	gsoap_resqml2_0_1::eml20__TimeUom timeUom,
	gsoap_resqml2_0_1::eml20__LengthUom verticalUom, uint64_t verticalEpsgCode, bool isUpOriented)
{
	init(repo, guid, title,
		projectedEpsgCode, "",
		originOrdinal1, originOrdinal2, projectedUom,
		arealRotation, gsoap_eml2_3::eml23__PlaneAngleUom::rad, gsoap_eml2_3::eml23__NorthReferenceKind::grid_x0020north,
		gsoap_eml2_3::eml23__AxisOrder2d::easting_x0020northing,
		verticalEpsgCode, "",
		originOrdinal3, verticalUom, timeUom,
		isUpOriented);
}

LocalEngineeringCompoundCrs::LocalEngineeringCompoundCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
	double originOrdinal1, double originOrdinal2, double originOrdinal3,
	double arealRotation,
	gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string& projectedDefinition,
	gsoap_resqml2_0_1::eml20__TimeUom timeUom,
	gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string& verticalDefinition, bool isUpOriented)
{
	init(repo, guid, title,
		0, projectedDefinition,
		originOrdinal1, originOrdinal2, projectedUom,
		arealRotation, gsoap_eml2_3::eml23__PlaneAngleUom::rad, gsoap_eml2_3::eml23__NorthReferenceKind::grid_x0020north,
		gsoap_eml2_3::eml23__AxisOrder2d::easting_x0020northing,
		0, verticalDefinition,
		originOrdinal3, verticalUom, timeUom,
		isUpOriented);
}

LocalEngineeringCompoundCrs::LocalEngineeringCompoundCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
	double originOrdinal1, double originOrdinal2, double originOrdinal3,
	double arealRotation,
	gsoap_resqml2_0_1::eml20__LengthUom projectedUom, uint64_t projectedEpsgCode,
	gsoap_resqml2_0_1::eml20__TimeUom timeUom,
	gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string& verticalDefinition, bool isUpOriented)
{
	init(repo, guid, title,
		projectedEpsgCode, "",
		originOrdinal1, originOrdinal2, projectedUom,
		arealRotation, gsoap_eml2_3::eml23__PlaneAngleUom::rad, gsoap_eml2_3::eml23__NorthReferenceKind::grid_x0020north,
		gsoap_eml2_3::eml23__AxisOrder2d::easting_x0020northing,
		0, verticalDefinition,
		originOrdinal3, verticalUom, timeUom,
		isUpOriented);
}

LocalEngineeringCompoundCrs::LocalEngineeringCompoundCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
	double originOrdinal1, double originOrdinal2, double originOrdinal3,
	double arealRotation,
	gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string& projectedDefinition,
	gsoap_resqml2_0_1::eml20__TimeUom timeUom,
	gsoap_resqml2_0_1::eml20__LengthUom verticalUom, uint64_t verticalEpsgCode, bool isUpOriented)
{
	init(repo, guid, title,
		0, projectedDefinition,
		originOrdinal1, originOrdinal2, projectedUom,
		arealRotation, gsoap_eml2_3::eml23__PlaneAngleUom::rad, gsoap_eml2_3::eml23__NorthReferenceKind::grid_x0020north,
		gsoap_eml2_3::eml23__AxisOrder2d::easting_x0020northing,
		verticalEpsgCode, "",
		originOrdinal3, verticalUom, timeUom,
		isUpOriented);
}

gsoap_resqml2_0_1::eml20__TimeUom LocalEngineeringCompoundCrs::getTimeUom() const
{
	if (!isATimeCrs()) {
		throw std::logic_error("You cannot get time uom from a depth/elevation CRS.");
	}

	gsoap_resqml2_0_1::eml20__TimeUom result;

	if (gsoap_resqml2_0_1::soap_s2eml20__TimeUom(getGsoapContext(), static_cast<eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->VerticalAxis->Uom.c_str(), &result) != SOAP_OK) {
		throw invalid_argument("The time uom \"" + static_cast<eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->VerticalAxis->Uom + "\" is not recognized by FESAPI.");
	}

	return result;
}

LocalEngineering2dCrs* LocalEngineeringCompoundCrs::getLocalEngineering2dCrs() const
{
	return getRepository()->getDataObjectByUuid<LocalEngineering2dCrs>
		(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->LocalEngineering2dCrs->Uuid);
}

VerticalCrs* LocalEngineeringCompoundCrs::getVerticalCrs() const
{
	return getRepository()->getDataObjectByUuid<VerticalCrs>
		(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->VerticalCrs->Uuid);
}

void LocalEngineeringCompoundCrs::loadTargetRelationships()
{
	COMMON_NS::DataObjectReference dorVerticalCrs(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->VerticalCrs);
	convertDorIntoRel<EML2_3_NS::VerticalCrs>(dorVerticalCrs);

	COMMON_NS::DataObjectReference dor2dCrs(static_cast<gsoap_eml2_3::eml23__LocalEngineeringCompoundCrs*>(gsoapProxy2_3)->LocalEngineering2dCrs);
	convertDorIntoRel<EML2_3_NS::LocalEngineering2dCrs>(dor2dCrs);
}
