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
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;
using namespace COMMON_NS;

const char* Well::XML_TAG = "Well";

Well::Well(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid,
			const std::string & title)
{
	if (repo == nullptr) {
		throw invalid_argument("A repo must exist.");
	}

	gsoapProxy2_1 = soap_new_witsml20__Well(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(this);
}

Well::Well(COMMON_NS::DataObjectRepository * repo,
		const std::string & guid,
		const std::string & title,
		const std::string & operator_,
		eml21__WellStatus statusWell,
		witsml20__WellDirection directionWell
	)
{
	if (repo == nullptr) {
		throw invalid_argument("A repo must exist.");
	}

	gsoapProxy2_1 = soap_new_witsml20__Well(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setOperator(operator_);

	witsml20__Well* well = static_cast<witsml20__Well*>(gsoapProxy2_1);

	well->StatusWell = (eml21__WellStatus *)soap_malloc(gsoapProxy2_1->soap, sizeof(eml21__WellStatus));
	*well->StatusWell = statusWell;

	well->DirectionWell = (witsml20__WellDirection *)soap_malloc(gsoapProxy2_1->soap, sizeof(witsml20__WellDirection));
	*well->DirectionWell = directionWell;

	repo->addOrReplaceDataObject(this);
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
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Well, Operator, soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Well, OperatorDiv, soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Well, OriginalOperator, soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Well, NumAPI, soap_new_std__string)

// Optional enum
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(gsoap_eml2_1::eml21__WellStatus, Well, StatusWell, gsoap_eml2_1::soap_new_eml21__WellStatus)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(gsoap_eml2_1::witsml20__WellPurpose, Well, PurposeWell, gsoap_eml2_1::soap_new_witsml20__WellPurpose)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(gsoap_eml2_1::witsml20__WellFluid, Well, FluidWell, gsoap_eml2_1::soap_new_witsml20__WellFluid)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(gsoap_eml2_1::witsml20__WellDirection, Well, DirectionWell, gsoap_eml2_1::soap_new_witsml20__WellDirection)

GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(Well, WaterDepth, gsoap_eml2_1::eml21__LengthUom, gsoap_eml2_1::soap_new_eml21__LengthMeasure)
GETTER_PRESENCE_ATTRIBUTE_IMPL(Well, GroundElevation)
GETTER_VALUE_OF_MEASURE_ATTRIBUTE_IMPL(Well, GroundElevation)
GETTER_UOM_OF_MEASURE_ATTRIBUTE_IMPL(Well, GroundElevation, gsoap_eml2_1::eml21__LengthUom)

GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(Well, PcInterest, gsoap_eml2_1::eml21__DimensionlessUom, gsoap_eml2_1::soap_new_eml21__DimensionlessMeasure)

GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IMPL(Well, DTimLicense)
GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IMPL(Well, DTimSpud)
GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IMPL(Well, DTimPa)

void Well::setGroundElevation(double value, gsoap_eml2_1::eml21__LengthUom uom, const std::string& datum)
{
	if (value != value) { throw invalid_argument("You cannot set an undefined measure"); }
	witsml20__Well* well = static_cast<witsml20__Well*>(gsoapProxy2_1);
	if (well->GroundElevation == nullptr) { well->GroundElevation = soap_new_witsml20__WellElevationCoord(gsoapProxy2_1->soap); }
	static_cast<witsml20__Well*>(gsoapProxy2_1)->GroundElevation->__item = value;
	static_cast<witsml20__Well*>(gsoapProxy2_1)->GroundElevation->uom = uom;
	static_cast<witsml20__Well*>(gsoapProxy2_1)->GroundElevation->datum = datum;
}

std::string Well::getGroundElevationDatum() const
{
	if (!hasGroundElevation()) { throw invalid_argument("The measure attribute to get does not exist."); }\
	return static_cast<witsml20__Well*>(gsoapProxy2_1)->GroundElevation->datum;
}

void Well::setTimeZone(bool direction, unsigned short hours, unsigned short minutes)
{
	if (hours > 23) { throw invalid_argument("You cannot set a time zone superior to 23 hours"); }
	if (minutes > 59) { throw invalid_argument("You cannot set a time zone superior to 59 minutes"); }
	witsml20__Well* well = static_cast<witsml20__Well*>(gsoapProxy2_1);
	if (well->TimeZone == nullptr) { well->TimeZone = soap_new_eml21__TimeZone(gsoapProxy2_1->soap); }

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
	return static_cast<witsml20__Well*>(gsoapProxy2_1)->TimeZone->at(0) != '-';
}
unsigned short Well::getTimeZoneHours() const {
	if (!hasTimeZone()) { throw invalid_argument("The attribute to get does not exist."); }
	if (static_cast<witsml20__Well*>(gsoapProxy2_1)->TimeZone->size() == 1) { return 0; }
	if (static_cast<witsml20__Well*>(gsoapProxy2_1)->TimeZone->size() != 6) { throw invalid_argument("The time zone does not looks to conform to the XSD standard."); }

	istringstream iss(static_cast<witsml20__Well*>(gsoapProxy2_1)->TimeZone->substr(1,2));
	unsigned short result;
	iss >> result;
	return result;
}
unsigned short Well::getTimeZoneMinutes() const {
	if (!hasTimeZone()) { throw invalid_argument("The attribute to get does not exist."); }
	if (static_cast<witsml20__Well*>(gsoapProxy2_1)->TimeZone->size() == 1) { return 0; }
	if (static_cast<witsml20__Well*>(gsoapProxy2_1)->TimeZone->size() != 6) { throw invalid_argument("The time zone does not looks to conform to the XSD standard."); }

	istringstream iss(static_cast<witsml20__Well*>(gsoapProxy2_1)->TimeZone->substr(4, 2));
	unsigned short result;
	iss >> result;
	return result;
}

double Well::getLocationProjectedX(unsigned int locationIndex)
{
	witsml20__Well* well = static_cast<witsml20__Well*>(gsoapProxy2_1);

	if (well->WellLocation.size() <= locationIndex) {
		throw range_error("The well location index is out of range.");
	}
	if (well->WellLocation[locationIndex]->soap_type() != SOAP_TYPE_gsoap_eml2_1_witsml20__ProjectedWellLocation){
		throw invalid_argument("The well location is not a projected one.");
	}

	return static_cast<witsml20__ProjectedWellLocation*>(well->WellLocation[locationIndex])->Coordinate1;
}

double Well::getLocationProjectedY(unsigned int locationIndex)
{
	witsml20__Well* well = static_cast<witsml20__Well*>(gsoapProxy2_1);

	if (well->WellLocation.size() <= locationIndex) {
		throw range_error("The well location index is out of range.");
	}
	if (well->WellLocation[locationIndex]->soap_type() != SOAP_TYPE_gsoap_eml2_1_witsml20__ProjectedWellLocation){
		throw invalid_argument("The well location is not a projected one.");
	}

	return static_cast<witsml20__ProjectedWellLocation*>(well->WellLocation[locationIndex])->Coordinate2;
}

void Well::pushBackLocation(
	const std::string & guid,
	double projectedX,
	double projectedY,
	unsigned int projectedCrsEpsgCode)
{
	witsml20__Well* well = static_cast<witsml20__Well*>(gsoapProxy2_1);

	witsml20__ProjectedWellLocation* location = soap_new_witsml20__ProjectedWellLocation(gsoapProxy2_1->soap);
	if (guid.size() == 0) {
		ostringstream oss;
		oss << well->WellLocation.size();
		location->uid = oss.str();
	}
	else {
		location->uid = guid;
	}
	location->Coordinate1 = projectedX;
	location->Coordinate2 = projectedY;
	location->Crs = soap_new_eml21__ProjectedEpsgCrs(gsoapProxy2_1->soap);
	static_cast<eml21__ProjectedEpsgCrs*>(location->Crs)->EpsgCode = projectedCrsEpsgCode;

	well->WellLocation.push_back(location);
}

unsigned int Well::geLocationCount() const {
	const size_t result = static_cast<witsml20__Well*>(gsoapProxy2_1)->WellLocation.size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much locations");
	}

	return static_cast<unsigned int>(result);
}

void Well::pushBackDatum(
	const std::string & guid,
	const std::string & title,
	eml21__WellboreDatumReference code,
	const std::string & datum,
	eml21__LengthUom elevationUnit,
	double elevation,
	unsigned int verticalCrsEpsgCode)
{
	witsml20__Well* well = static_cast<witsml20__Well*>(gsoapProxy2_1);

	witsml20__WellDatum* wellDatum = soap_new_witsml20__WellDatum(gsoapProxy2_1->soap);
	if (guid.empty()) {
		ostringstream oss;
		oss << well->WellDatum.size();
		wellDatum->uid = oss.str();
	}
	else {
		wellDatum->uid = guid;
	}
	wellDatum->Name = title.size() == 0 ? "unknown" : title;

	wellDatum->Code = (eml21__WellboreDatumReference *)soap_malloc(gsoapProxy2_1->soap, sizeof(eml21__WellboreDatumReference));
	*wellDatum->Code = code;

	wellDatum->Crs = soap_new_eml21__VerticalEpsgCrs(gsoapProxy2_1->soap);
	static_cast<eml21__VerticalEpsgCrs*>(wellDatum->Crs)->EpsgCode = verticalCrsEpsgCode;

	wellDatum->Elevation = soap_new_witsml20__WellElevationCoord(gsoapProxy2_1->soap);
	wellDatum->Elevation->datum = datum;
	wellDatum->Elevation->uom = elevationUnit;
	wellDatum->Elevation->__item = elevation;

	well->WellDatum.push_back(wellDatum);
}

unsigned int Well::getDatumCount() const
{
	const size_t result = static_cast<witsml20__Well*>(gsoapProxy2_1)->WellDatum.size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much datums");
	}

	return static_cast<unsigned int>(result);
}

void Well::loadTargetRelationships()
{}

std::vector<RESQML2_NS::WellboreFeature *> Well::getResqmlWellboreFeatures() const
{
	return getRepository()->getSourceObjects<RESQML2_NS::WellboreFeature>(this);
}

std::vector<Wellbore *> Well::getWellbores() const
{
	return getRepository()->getSourceObjects<Wellbore>(this);
}

std::vector<WellCompletion *> Well::getWellcompletions() const
{
	return getRepository()->getSourceObjects<WellCompletion>(this);
}
