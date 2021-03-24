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
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* LocalTime3dCrs::XML_NS = "resqml20";

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

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORELocalTime3dCrs(repo->getGsoapContext());
	_resqml20__LocalTime3dCrs* local3dCrs = static_cast<_resqml20__LocalTime3dCrs*>(gsoapProxy2_0_1);
	local3dCrs->ArealRotation = soap_new_eml20__PlaneAngleMeasure(gsoapProxy2_0_1->soap);
	local3dCrs->ArealRotation->__item = arealRotation;
	local3dCrs->ArealRotation->uom = eml20__PlaneAngleUom::rad;
	local3dCrs->ProjectedAxisOrder = eml20__AxisOrder2d::easting_x0020northing;
	local3dCrs->XOffset = originOrdinal1;
	local3dCrs->YOffset = originOrdinal2;
	local3dCrs->ZOffset = originOrdinal3;
	local3dCrs->ZIncreasingDownward = !isUpOriented;
	local3dCrs->ProjectedUom = projectedUom;
	local3dCrs->VerticalUom = verticalUom;
	local3dCrs->TimeUom = timeUom;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

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
	_resqml20__LocalTime3dCrs* local3dCrs = static_cast<_resqml20__LocalTime3dCrs*>(gsoapProxy2_0_1);

	// Projected CRS
	eml20__ProjectedCrsEpsgCode* projCrs = soap_new_eml20__ProjectedCrsEpsgCode(gsoapProxy2_0_1->soap);
	local3dCrs->ProjectedCrs = projCrs;
	projCrs->EpsgCode = projectedEpsgCode;

	// Vertical CRS
	eml20__VerticalCrsEpsgCode* vertCrs = soap_new_eml20__VerticalCrsEpsgCode(gsoapProxy2_0_1->soap);
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
	_resqml20__LocalTime3dCrs* local3dCrs = static_cast<_resqml20__LocalTime3dCrs*>(gsoapProxy2_0_1);

	// Projected CRS
	eml20__ProjectedUnknownCrs* projCrs = soap_new_eml20__ProjectedUnknownCrs(gsoapProxy2_0_1->soap);
	local3dCrs->ProjectedCrs = projCrs;
	projCrs->Unknown = projectedUnknownReason;

	// Vertical CRS
	eml20__VerticalUnknownCrs* vertCrs = soap_new_eml20__VerticalUnknownCrs(gsoapProxy2_0_1->soap);
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
	_resqml20__LocalTime3dCrs* local3dCrs = static_cast<_resqml20__LocalTime3dCrs*>(gsoapProxy2_0_1);

	// Projected CRS
	eml20__ProjectedCrsEpsgCode* projCrs = soap_new_eml20__ProjectedCrsEpsgCode(gsoapProxy2_0_1->soap);
	local3dCrs->ProjectedCrs = projCrs;
	projCrs->EpsgCode = projectedEpsgCode;

	// Vertical CRS
	eml20__VerticalUnknownCrs* vertCrs = soap_new_eml20__VerticalUnknownCrs(gsoapProxy2_0_1->soap);
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
	_resqml20__LocalTime3dCrs* local3dCrs = static_cast<_resqml20__LocalTime3dCrs*>(gsoapProxy2_0_1);

	// Projected CRS
	eml20__ProjectedUnknownCrs* projCrs = soap_new_eml20__ProjectedUnknownCrs(gsoapProxy2_0_1->soap);
	local3dCrs->ProjectedCrs = projCrs;
	projCrs->Unknown = projectedUnknownReason;

	// Vertical CRS
	eml20__VerticalCrsEpsgCode* vertCrs = soap_new_eml20__VerticalCrsEpsgCode(gsoapProxy2_0_1->soap);
	local3dCrs->VerticalCrs = vertCrs;
	vertCrs->EpsgCode = verticalEpsgCode;
}

gsoap_resqml2_0_1::eml20__TimeUom LocalTime3dCrs::getUnit() const
{
	return static_cast<_resqml20__LocalTime3dCrs*>(gsoapProxy2_0_1)->TimeUom;
}

std::string LocalTime3dCrs::getUnitAsString() const
{
	return gsoap_resqml2_0_1::soap_eml20__TimeUom2s(gsoapProxy2_0_1->soap, static_cast<_resqml20__LocalTime3dCrs*>(gsoapProxy2_0_1)->TimeUom);
}

