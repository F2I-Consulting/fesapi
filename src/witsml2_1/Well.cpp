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
#include "Well.h"

#include <stdexcept>

#include "../eml2_3/LocalEngineering2dCrs.h"
#include "../eml2_3/VerticalCrs.h"

#include "../tools/TimeTools.h"

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_3;
using namespace COMMON_NS;

Well::Well(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid,
	const std::string & title,
	bool isActive)
{
	if (repo == nullptr) {
		throw invalid_argument("A repo must exist.");
	}

	gsoapProxy2_3 = soap_new_witsml21__Well(repo->getGsoapContext());

	static_cast<witsml21__Well*>(gsoapProxy2_3)->ActiveStatus = isActive ? eml23__ActiveStatusKind::active : eml23__ActiveStatusKind::inactive;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
}

Well::Well(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid,
	const std::string & title,
	bool isActive,
	eml23__WellStatus statusWell,
	witsml21__WellDirection directionWell)
{
	if (repo == nullptr) {
		throw invalid_argument("A repo must exist.");
	}

	gsoapProxy2_3 = soap_new_witsml21__Well(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	witsml21__Well* well = static_cast<witsml21__Well*>(gsoapProxy2_3);

	static_cast<witsml21__Well*>(gsoapProxy2_3)->ActiveStatus = isActive ? eml23__ActiveStatusKind::active : eml23__ActiveStatusKind::inactive;

	well->StatusWell = (eml23__WellStatus *)soap_malloc(gsoapProxy2_3->soap, sizeof(eml23__WellStatus));
	*well->StatusWell = statusWell;

	well->DirectionWell = (witsml21__WellDirection *)soap_malloc(gsoapProxy2_3->soap, sizeof(witsml21__WellDirection));
	*well->DirectionWell = directionWell;

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
}

GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Well, NameLegal, soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Well, NumLicense, soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Well, NumGovt, soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Well, Field, soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Well, Country, soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Well, State, soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Well, County, soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Well, Region, soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Well, District, soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Well, Block, soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Well, OperatorDiv, soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Well, NumAPI, soap_new_std__string)

// Optional enum
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(gsoap_eml2_3::eml23__WellStatus, Well, StatusWell, gsoap_eml2_3::soap_new_eml23__WellStatus)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(gsoap_eml2_3::witsml21__WellPurpose, Well, PurposeWell, gsoap_eml2_3::soap_new_witsml21__WellPurpose)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(gsoap_eml2_3::witsml21__WellFluid, Well, FluidWell, gsoap_eml2_3::soap_new_witsml21__WellFluid)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(gsoap_eml2_3::witsml21__WellDirection, Well, DirectionWell, gsoap_eml2_3::soap_new_witsml21__WellDirection)

GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(Well, WaterDepth, gsoap_eml2_3::eml23__LengthUom, gsoap_eml2_3::soap_eml23__LengthUom2s, gsoap_eml2_3::soap_new_eml23__LengthMeasure)
GETTER_PRESENCE_ATTRIBUTE_IMPL(Well, GroundElevation)
GETTER_PRESENCE_ATTRIBUTE_IMPL(Well, WellheadElevation)

GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(Well, PcInterest, gsoap_eml2_3::eml23__DimensionlessUom, gsoap_eml2_3::soap_eml23__DimensionlessUom2s, gsoap_eml2_3::soap_new_eml23__DimensionlessMeasure)

GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IMPL(Well, DTimLicense)
GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IMPL(Well, DTimSpud)
GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IMPL(Well, DTimPa)

double Well::getGroundElevationValue() const {
	if (!hasGroundElevation()) { throw invalid_argument("The ground elevation does not exist."); }
	return static_cast<witsml21__Well*>(gsoapProxy2_3)->GroundElevation->Elevation->__item;
}

gsoap_eml2_3::eml23__LengthUom Well::getGroundElevationUom() const {
	if (!hasGroundElevation()) { throw invalid_argument("The ground elevation does not exist."); }
	gsoap_eml2_3::eml23__LengthUom result;
	gsoap_eml2_3::soap_s2eml23__LengthUom(gsoapProxy2_3->soap, static_cast<witsml21__Well*>(gsoapProxy2_3)->GroundElevation->Elevation->uom.c_str(), &result);
	return result;
}

COMMON_NS::DataObjectReference Well::getGroundElevationDatumDor() const {
	if (!hasGroundElevation()) { return COMMON_NS::DataObjectReference(); }
	witsml21__Well* well = static_cast<witsml21__Well*>(gsoapProxy2_3);
	if (well->GroundElevation->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__DatumElevation) {
		return COMMON_NS::DataObjectReference(static_cast<eml23__DatumElevation*>(well->GroundElevation)->Datum);
	}
	else {
		return COMMON_NS::DataObjectReference(static_cast<eml23__ReferencePointElevation*>(well->GroundElevation)->ReferencePoint);
	}
}

void Well::setGroundElevation(double value, gsoap_eml2_3::eml23__LengthUom uom, EML2_3_NS::VerticalCrs* verticalCrs)
{
	if (value != value) { throw invalid_argument("You cannot set an undefined measure"); }
	witsml21__Well* well = static_cast<witsml21__Well*>(gsoapProxy2_3);
	eml23__DatumElevation* datumElevation = well->GroundElevation == nullptr
		? soap_new_eml23__DatumElevation(gsoapProxy2_3->soap)
		: dynamic_cast<eml23__DatumElevation*>(well->GroundElevation);
	eml23__LengthMeasureExt* lengthMeasure = datumElevation->Elevation == nullptr
		? soap_new_eml23__LengthMeasureExt(gsoapProxy2_3->soap)
		: datumElevation->Elevation;
	lengthMeasure->__item = value;
	lengthMeasure->uom = gsoap_eml2_3::soap_eml23__LengthUom2s(gsoapProxy2_3->soap, uom);
	datumElevation->Elevation = lengthMeasure;
	datumElevation->Datum = verticalCrs->newEml23Reference();
	well->GroundElevation = datumElevation;
}

double Well::getWellheadElevationValue() const {
	if (!hasWellheadElevation()) { throw invalid_argument("The Wellhead elevation does not exist."); }
	return static_cast<witsml21__Well*>(gsoapProxy2_3)->WellheadElevation->Elevation->__item;
}

gsoap_eml2_3::eml23__LengthUom Well::getWellheadElevationUom() const {
	if (!hasWellheadElevation()) { throw invalid_argument("The Wellhead elevation does not exist."); }
	gsoap_eml2_3::eml23__LengthUom result;
	gsoap_eml2_3::soap_s2eml23__LengthUom(gsoapProxy2_3->soap, static_cast<witsml21__Well*>(gsoapProxy2_3)->WellheadElevation->Elevation->uom.c_str(), &result);
	return result;
}

COMMON_NS::DataObjectReference Well::getWellheadElevationDatumDor() const {
	if (!hasWellheadElevation()) { return COMMON_NS::DataObjectReference(); }
	witsml21__Well* well = static_cast<witsml21__Well*>(gsoapProxy2_3);
	if (well->WellheadElevation->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__DatumElevation) {
		return COMMON_NS::DataObjectReference(static_cast<eml23__DatumElevation*>(well->WellheadElevation)->Datum);
	}
	else {
		return COMMON_NS::DataObjectReference(static_cast<eml23__ReferencePointElevation*>(well->WellheadElevation)->ReferencePoint);
	}
}

void Well::setWellheadElevation(double value, gsoap_eml2_3::eml23__LengthUom uom, EML2_3_NS::VerticalCrs* verticalCrs)
{
	if (value != value) { throw invalid_argument("You cannot set an undefined measure"); }
	witsml21__Well* well = static_cast<witsml21__Well*>(gsoapProxy2_3);
	eml23__DatumElevation* datumElevation = well->WellheadElevation == nullptr
		? soap_new_eml23__DatumElevation(gsoapProxy2_3->soap)
		: dynamic_cast<eml23__DatumElevation*>(well->WellheadElevation);
	eml23__LengthMeasureExt* lengthMeasure = datumElevation->Elevation == nullptr
		? soap_new_eml23__LengthMeasureExt(gsoapProxy2_3->soap)
		: datumElevation->Elevation;
	lengthMeasure->__item = value;
	lengthMeasure->uom = gsoap_eml2_3::soap_eml23__LengthUom2s(gsoapProxy2_3->soap, uom);
	datumElevation->Elevation = lengthMeasure;
	datumElevation->Datum = verticalCrs->newEml23Reference();
	well->WellheadElevation = datumElevation;
}

void Well::setTimeZone(bool direction, unsigned short hours, unsigned short minutes)
{
	if (hours > 23) { throw invalid_argument("You cannot set a time zone superior to 23 hours"); }
	if (minutes > 59) { throw invalid_argument("You cannot set a time zone superior to 59 minutes"); }
	witsml21__Well* well = static_cast<witsml21__Well*>(gsoapProxy2_3);
	if (well->TimeZone == nullptr) { well->TimeZone = soap_new_eml23__TimeZone(gsoapProxy2_3->soap); }

	if (hours == 00 && minutes == 0) {
		well->TimeZone->assign(1, 'Z');
		return;
	}

	std::string timeZone(1, direction ? '+' : '-');

	if (hours < 10) {
		timeZone += '0';
	}
	timeZone += std::to_string(hours) + ':';

	if (minutes < 10) {
		timeZone += '0';
	}
	timeZone += std::to_string(minutes);

	well->TimeZone->assign(timeZone);
}
GETTER_PRESENCE_ATTRIBUTE_IMPL(Well, TimeZone)
bool Well::getTimeZoneDirection() const {
	if (!hasTimeZone()) { throw invalid_argument("The attribute to get does not exist."); }
	return static_cast<witsml21__Well*>(gsoapProxy2_3)->TimeZone->at(0) != '-';
}
unsigned short Well::getTimeZoneHours() const {
	if (!hasTimeZone()) { throw invalid_argument("The attribute to get does not exist."); }
	if (static_cast<witsml21__Well*>(gsoapProxy2_3)->TimeZone->size() == 1) { return 0; }
	if (static_cast<witsml21__Well*>(gsoapProxy2_3)->TimeZone->size() != 6) { throw invalid_argument("The time zone does not looks to conform to the XSD standard."); }

	istringstream iss(static_cast<witsml21__Well*>(gsoapProxy2_3)->TimeZone->substr(1,2));
	unsigned short result;
	iss >> result;
	return result;
}
unsigned short Well::getTimeZoneMinutes() const {
	if (!hasTimeZone()) { throw invalid_argument("The attribute to get does not exist."); }
	if (static_cast<witsml21__Well*>(gsoapProxy2_3)->TimeZone->size() == 1) { return 0; }
	if (static_cast<witsml21__Well*>(gsoapProxy2_3)->TimeZone->size() != 6) { throw invalid_argument("The time zone does not look to conform to the XSD standard."); }

	istringstream iss(static_cast<witsml21__Well*>(gsoapProxy2_3)->TimeZone->substr(4, 2));
	unsigned short result;
	iss >> result;
	return result;
}

double Well::getLocationProjectedX(uint64_t locationIndex)
{
	auto* surfaceLocation = static_cast<witsml21__Well*>(gsoapProxy2_3)->WellSurfaceLocation.at(locationIndex);

	if (surfaceLocation->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__LocalEngineering2dPosition){
		throw invalid_argument("The well location is not a LocalEngineering2dPosition one.");
	}

	return static_cast<eml23__LocalEngineering2dPosition*>(surfaceLocation)->Coordinate1;
}

double Well::getLocationProjectedY(uint64_t locationIndex)
{
	auto* surfaceLocation = static_cast<witsml21__Well*>(gsoapProxy2_3)->WellSurfaceLocation.at(locationIndex);

	if (surfaceLocation->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__LocalEngineering2dPosition){
		throw invalid_argument("The well location is not a LocalEngineering2dPosition one.");
	}

	return static_cast<eml23__LocalEngineering2dPosition*>(surfaceLocation)->Coordinate2;
}

void Well::pushBackLocation(double projectedX, double projectedY, EML2_3_NS::LocalEngineering2dCrs* crs)
{
	witsml21__Well* well = static_cast<witsml21__Well*>(gsoapProxy2_3);

	eml23__LocalEngineering2dPosition* location = soap_new_eml23__LocalEngineering2dPosition(gsoapProxy2_3->soap);
	location->Coordinate1 = projectedX;
	location->Coordinate2 = projectedY;
	location->LocalEngineering2dCrs = crs->newEml23Reference();

	well->WellSurfaceLocation.push_back(location);
}

uint64_t Well::geLocationCount() const {
	return static_cast<witsml21__Well*>(gsoapProxy2_3)->WellSurfaceLocation.size();
}
