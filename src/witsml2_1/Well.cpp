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

#include <limits>
#include <stdexcept>
#include <sstream>

#include "Wellbore.h"
#include "WellCompletion.h"

#include "../resqml2_0_1/WellboreFeature.h"

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

	repo->addDataObject(this);
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

	repo->addDataObject(this);
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

void Well::setGroundElevation(double value, gsoap_eml2_3::eml23__LengthUom uom)
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
	datumElevation->Datum = soap_new_eml23__DataObjectReference(gsoapProxy2_3->soap); // TODO : allow to reference an existing vertical CRS
	datumElevation->Datum->Uuid.assign("00000000-0000-0000-0000-000000000000");
	datumElevation->Datum->QualifiedType.assign("eml23.VerticalCrs");
	datumElevation->Datum->Title.assign("Fake Vertical CRS");
	well->GroundElevation = datumElevation;
}

void Well::setTimeZone(bool direction, unsigned short hours, unsigned short minutes)
{
	if (hours > 23) { throw invalid_argument("You cannot set a time zone superior to 23 hours"); }
	if (minutes > 59) { throw invalid_argument("You cannot set a time zone superior to 59 minutes"); }
	witsml21__Well* well = static_cast<witsml21__Well*>(gsoapProxy2_3);
	if (well->TimeZone == nullptr) { well->TimeZone = soap_new_eml23__TimeZone(gsoapProxy2_3->soap); }

	if (hours == 00 && minutes == 0) {
		well->TimeZone->assign("Z");
		return;
	}

	std::ostringstream oss;
	if (direction) {
		oss << "+";
	}
	else {
		oss << "-";
	}

	if (hours < 10) {
		oss << "0";
	}
	oss << hours << ":";

	if (minutes < 10) {
		oss << "0";
	}
	oss << minutes;

	well->TimeZone->assign(oss.str());
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
	if (static_cast<witsml21__Well*>(gsoapProxy2_3)->TimeZone->size() != 6) { throw invalid_argument("The time zone does not looks to conform to the XSD standard."); }

	istringstream iss(static_cast<witsml21__Well*>(gsoapProxy2_3)->TimeZone->substr(4, 2));
	unsigned short result;
	iss >> result;
	return result;
}

double Well::getLocationProjectedX(unsigned int locationIndex)
{
	witsml21__Well* well = static_cast<witsml21__Well*>(gsoapProxy2_3);

	if (well->WellSurfaceLocation.size() <= locationIndex) {
		throw range_error("The well location index is out of range.");
	}
	if (well->WellSurfaceLocation[locationIndex]->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__Projected2dPosition){
		throw invalid_argument("The well location is not a projected one.");
	}

	return static_cast<eml23__Projected2dPosition*>(well->WellSurfaceLocation[locationIndex])->Coordinate1;
}

double Well::getLocationProjectedY(unsigned int locationIndex)
{
	witsml21__Well* well = static_cast<witsml21__Well*>(gsoapProxy2_3);

	if (well->WellSurfaceLocation.size() <= locationIndex) {
		throw range_error("The well location index is out of range.");
	}
	if (well->WellSurfaceLocation[locationIndex]->soap_type() != SOAP_TYPE_gsoap_eml2_3_eml23__Projected2dPosition){
		throw invalid_argument("The well location is not a projected one.");
	}

	return static_cast<eml23__Projected2dPosition*>(well->WellSurfaceLocation[locationIndex])->Coordinate2;
}

void Well::pushBackLocation(
	double projectedX,
	double projectedY)
{
	witsml21__Well* well = static_cast<witsml21__Well*>(gsoapProxy2_3);

	eml23__Projected2dPosition* location = soap_new_eml23__Projected2dPosition(gsoapProxy2_3->soap);
	location->Coordinate1 = projectedX;
	location->Coordinate2 = projectedY;
	location->ProjectedCrs = soap_new_eml23__DataObjectReference(gsoapProxy2_3->soap);
	location->ProjectedCrs->Uuid.assign("00000000-0000-0000-0000-000000000001");
	location->ProjectedCrs->QualifiedType.assign("eml23.ProjectedCrs");
	location->ProjectedCrs->Title.assign("Fake Projected CRS");

	well->WellSurfaceLocation.push_back(location);
}

unsigned int Well::geLocationCount() const {
	const size_t result = static_cast<witsml21__Well*>(gsoapProxy2_3)->WellSurfaceLocation.size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much locations");
	}

	return static_cast<unsigned int>(result);
}
