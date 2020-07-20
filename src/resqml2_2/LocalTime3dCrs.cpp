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
#include "LocalTime3dCrs.h"

#include <stdexcept>

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* LocalTime3dCrs::XML_NS = "resqml22";

void LocalTime3dCrs::init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
	double originOrdinal1, double originOrdinal2, double originOrdinal3,
	double arealRotation,
	gsoap_resqml2_0_1::eml20__LengthUom projectedUom,
	gsoap_resqml2_0_1::eml20__TimeUom timeUom,
	gsoap_resqml2_0_1::eml20__LengthUom verticalUom, bool isUpOriented)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__LocalTime3dCrs(repo->getGsoapContext());
	_resqml22__LocalTime3dCrs* local3dCrs = static_cast<_resqml22__LocalTime3dCrs*>(gsoapProxy2_3);
	local3dCrs->ArealRotation = soap_new_eml23__PlaneAngleMeasure(gsoapProxy2_3->soap);
	local3dCrs->ArealRotation->__item = arealRotation;
	local3dCrs->ArealRotation->uom = eml23__PlaneAngleUom__rad;
	local3dCrs->ProjectedAxisOrder = eml23__AxisOrder2d__easting_x0020northing;
	local3dCrs->XOffset = originOrdinal1;
	local3dCrs->YOffset = originOrdinal2;
	local3dCrs->ZOffset = originOrdinal3;
	local3dCrs->ZIncreasingDownward = !isUpOriented;
	local3dCrs->ProjectedUom = gsoap_resqml2_0_1::soap_eml20__LengthUom2s(gsoapProxy2_3->soap, projectedUom);
	local3dCrs->VerticalUom = gsoap_resqml2_0_1::soap_eml20__LengthUom2s(gsoapProxy2_3->soap, verticalUom);
	local3dCrs->TimeUom = gsoap_resqml2_0_1::soap_eml20__TimeUom2s(gsoapProxy2_3->soap, timeUom);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(this);
}

LocalTime3dCrs::LocalTime3dCrs(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
	double originOrdinal1, double originOrdinal2, double originOrdinal3,
	double arealRotation,
	gsoap_resqml2_0_1::eml20__LengthUom projectedUom, unsigned long projectedEpsgCode,
	gsoap_resqml2_0_1::eml20__TimeUom timeUom,
	gsoap_resqml2_0_1::eml20__LengthUom verticalUom, unsigned int verticalEpsgCode, bool isUpOriented)
{
	if (projectedEpsgCode == 0 || verticalEpsgCode == 0) {
		throw invalid_argument("An EPSG code cannot be set to 0.");
	}
	init(repo, guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation, projectedUom, timeUom, verticalUom, isUpOriented);
	_resqml22__LocalTime3dCrs* local3dCrs = static_cast<_resqml22__LocalTime3dCrs*>(gsoapProxy2_3);

	// Projected CRS
	eml23__ProjectedEpsgCrs* projCrs = soap_new_eml23__ProjectedEpsgCrs(gsoapProxy2_3->soap);
	local3dCrs->ProjectedCrs = projCrs;
	projCrs->EpsgCode = projectedEpsgCode;

	// Vertical CRS
	eml23__VerticalEpsgCrs* vertCrs = soap_new_eml23__VerticalEpsgCrs(gsoapProxy2_3->soap);
	local3dCrs->VerticalCrs = vertCrs;
	vertCrs->EpsgCode = verticalEpsgCode;
}

LocalTime3dCrs::LocalTime3dCrs(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
	double originOrdinal1, double originOrdinal2, double originOrdinal3,
	double arealRotation,
	gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string & projectedUnknownReason,
	gsoap_resqml2_0_1::eml20__TimeUom timeUom,
	gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string & verticalUnknownReason, bool isUpOriented)
{
	init(repo, guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation, projectedUom, timeUom, verticalUom, isUpOriented);
	_resqml22__LocalTime3dCrs* local3dCrs = static_cast<_resqml22__LocalTime3dCrs*>(gsoapProxy2_3);

	// Projected CRS
	eml23__ProjectedUnknownCrs* projCrs = soap_new_eml23__ProjectedUnknownCrs(gsoapProxy2_3->soap);
	local3dCrs->ProjectedCrs = projCrs;
	projCrs->Unknown = projectedUnknownReason;

	// Vertical CRS
	eml23__VerticalUnknownCrs* vertCrs = soap_new_eml23__VerticalUnknownCrs(gsoapProxy2_3->soap);
	local3dCrs->VerticalCrs = vertCrs;
	vertCrs->Unknown = verticalUnknownReason;
}

LocalTime3dCrs::LocalTime3dCrs(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
	double originOrdinal1, double originOrdinal2, double originOrdinal3,
	double arealRotation,
	gsoap_resqml2_0_1::eml20__LengthUom projectedUom, unsigned long projectedEpsgCode,
	gsoap_resqml2_0_1::eml20__TimeUom timeUom,
	gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string & verticalUnknownReason, bool isUpOriented)
{
	if (projectedEpsgCode == 0) {
		throw invalid_argument("An EPSG code cannot be set to 0.");
	}
	init(repo, guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation, projectedUom, timeUom, verticalUom, isUpOriented);
	_resqml22__LocalTime3dCrs* local3dCrs = static_cast<_resqml22__LocalTime3dCrs*>(gsoapProxy2_3);

	// Projected CRS
	eml23__ProjectedEpsgCrs* projCrs = soap_new_eml23__ProjectedEpsgCrs(gsoapProxy2_3->soap);
	local3dCrs->ProjectedCrs = projCrs;
	projCrs->EpsgCode = projectedEpsgCode;

	// Vertical CRS
	eml23__VerticalUnknownCrs* vertCrs = soap_new_eml23__VerticalUnknownCrs(gsoapProxy2_3->soap);
	local3dCrs->VerticalCrs = vertCrs;
	vertCrs->Unknown = verticalUnknownReason;
}

LocalTime3dCrs::LocalTime3dCrs(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
	double originOrdinal1, double originOrdinal2, double originOrdinal3,
	double arealRotation,
	gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string & projectedUnknownReason,
	gsoap_resqml2_0_1::eml20__TimeUom timeUom,
	gsoap_resqml2_0_1::eml20__LengthUom verticalUom, unsigned int verticalEpsgCode, bool isUpOriented)
{
	if (verticalEpsgCode == 0) {
		throw invalid_argument("An EPSG code cannot be set to 0.");
	}
	init(repo, guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation, projectedUom, timeUom, verticalUom, isUpOriented);
	_resqml22__LocalTime3dCrs* local3dCrs = static_cast<_resqml22__LocalTime3dCrs*>(gsoapProxy2_3);

	// Projected CRS
	eml23__ProjectedUnknownCrs* projCrs = soap_new_eml23__ProjectedUnknownCrs(gsoapProxy2_3->soap);
	local3dCrs->ProjectedCrs = projCrs;
	projCrs->Unknown = projectedUnknownReason;

	// Vertical CRS
	eml23__VerticalEpsgCrs* vertCrs = soap_new_eml23__VerticalEpsgCrs(gsoapProxy2_3->soap);
	local3dCrs->VerticalCrs = vertCrs;
	vertCrs->EpsgCode = verticalEpsgCode;
}

gsoap_resqml2_0_1::eml20__TimeUom LocalTime3dCrs::getUnit() const
{
	gsoap_resqml2_0_1::eml20__TimeUom result;
	gsoap_resqml2_0_1::soap_s2eml20__TimeUom(gsoapProxy2_3->soap, static_cast<_resqml22__LocalTime3dCrs*>(gsoapProxy2_3)->TimeUom.c_str(), &result);
	return result;
}

std::string LocalTime3dCrs::getUnitAsString() const
{
	return static_cast<_resqml22__LocalTime3dCrs*>(gsoapProxy2_3)->TimeUom;
}

