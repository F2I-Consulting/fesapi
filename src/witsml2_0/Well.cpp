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
#include "witsml2_0/Well.h"

#include <stdexcept>
#include <sstream>

#include "tools/TimeTools.h"

using namespace std;
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;
using namespace epc;
using namespace COMMON_NS;

const char* Well::XML_TAG = "Well";

Well::Well(soap* soapContext,
			const std::string & guid,
			const std::string & title):resqmlWellboreFeature(nullptr)
{
	if (soapContext == nullptr) {
		throw invalid_argument("A soap context must exist.");
	}

	gsoapProxy2_1 = soap_new_witsml2__Well(soapContext, 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");
}

Well::Well(soap* soapContext,
		const std::string & guid,
		const std::string & title,
		const std::string & operator_,
		eml21__WellStatus statusWell,
		witsml2__WellDirection directionWell
	):resqmlWellboreFeature(nullptr)
{
	if (soapContext == nullptr) {
		throw invalid_argument("A soap context must exist.");
	}

	gsoapProxy2_1 = soap_new_witsml2__Well(soapContext, 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setOperator(operator_);

	witsml2__Well* well = static_cast<witsml2__Well*>(gsoapProxy2_1);

	well->StatusWell = (eml21__WellStatus *)soap_malloc(soapContext, sizeof(eml21__WellStatus));
	*well->StatusWell = statusWell;

	well->DirectionWell = (witsml2__WellDirection *)soap_malloc(soapContext, sizeof(witsml2__WellDirection));
	*well->DirectionWell = directionWell;
}

void Well::setString(std::string* & strToBeSet, const std::string & strToSet) {
	if (strToSet.empty()) {
		throw invalid_argument("The value to set cannot be empty.");
	}

	if (strToBeSet == nullptr) {
		strToBeSet = soap_new_std__string(gsoapProxy2_1->soap, 1);
	}
	strToBeSet->assign(strToSet);
}

#define GETTER_PRESENCE_ATTRIBUTE_IMPL(attributeName) bool Well::has##attributeName() const { return static_cast<witsml2__Well*>(gsoapProxy2_1)->attributeName != nullptr; }

#define GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE_IMPL(attributeName)\
	void Well::set##attributeName(const std::string & attributeName) { setString(static_cast<witsml2__Well*>(gsoapProxy2_1)->attributeName, attributeName); }\
	GETTER_PRESENCE_ATTRIBUTE_IMPL(attributeName)\
	std::string Well::get##attributeName() const {\
		if (!has##attributeName()) { throw invalid_argument("The string attribute to get does not exist."); }\
		return *static_cast<witsml2__Well*>(gsoapProxy2_1)->attributeName;\
	}

GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE_IMPL(NameLegal)
GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE_IMPL(NumLicense)
GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE_IMPL(NumGovt)
GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE_IMPL(Field)
GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE_IMPL(Country)
GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE_IMPL(State)
GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE_IMPL(County)
GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE_IMPL(Region)
GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE_IMPL(District)
GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE_IMPL(Block)
GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE_IMPL(Operator)
GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE_IMPL(OperatorDiv)
GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE_IMPL(OriginalOperator)
GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE_IMPL(NumAPI)

#define GETTER_AND_SETTER_WELL_LENGTH_MEASURE_ATTRIBUTE_IMPL(attributeName, constructor)\
	void Well::set##attributeName(double value, gsoap_eml2_1::eml21__LengthUom uom) {\
		if (value != value) { throw invalid_argument("You cannot set an undefined water depth"); }\
		witsml2__Well* well = static_cast<witsml2__Well*>(gsoapProxy2_1);\
		if (well->attributeName == nullptr) { well->attributeName = constructor; }\
		well->attributeName->__item = value;\
		well->attributeName->uom = uom;\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IMPL(attributeName)\
	double Well::get##attributeName##Value() const {\
		if (!has##attributeName()) { throw invalid_argument("The length measure attribute to get does not exist."); }\
		return static_cast<witsml2__Well*>(gsoapProxy2_1)->attributeName->__item;\
	}\
	gsoap_eml2_1::eml21__LengthUom Well::get##attributeName##Uom() const {\
		if (!has##attributeName()) { throw invalid_argument("The length measure attribute to get does not exist."); }\
		return static_cast<witsml2__Well*>(gsoapProxy2_1)->attributeName->uom;\
	}\

GETTER_AND_SETTER_WELL_LENGTH_MEASURE_ATTRIBUTE_IMPL(WaterDepth, soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap, 1))
GETTER_AND_SETTER_WELL_LENGTH_MEASURE_ATTRIBUTE_IMPL(GroundElevation, soap_new_witsml2__WellElevationCoord(gsoapProxy2_1->soap, 1))

#define GETTER_AND_SETTER_WELL_TIMESTAMP_ATTRIBUTE_IMPL(attributeName)\
	void Well::set##attributeName(unsigned int attributeName) { setString(static_cast<witsml2__Well*>(gsoapProxy2_1)->attributeName, timeTools::convertUnixTimestampToIso(attributeName)); }\
	GETTER_PRESENCE_ATTRIBUTE_IMPL(attributeName)\
	unsigned int Well::get##attributeName() const {\
		if (!has##attributeName()) { throw invalid_argument("The string attribute to get does not exist."); }\
		return timeTools::convertIsoToUnixTimestamp(*static_cast<witsml2__Well*>(gsoapProxy2_1)->attributeName);\
	}

GETTER_AND_SETTER_WELL_TIMESTAMP_ATTRIBUTE_IMPL(DTimLicense)
GETTER_AND_SETTER_WELL_TIMESTAMP_ATTRIBUTE_IMPL(DTimSpud)
GETTER_AND_SETTER_WELL_TIMESTAMP_ATTRIBUTE_IMPL(DTimPa)

void Well::setTimeZone(bool direction, unsigned short hours, unsigned short minutes)
{
	if (hours > 23) { throw invalid_argument("You cannot set a time zone superior to 23 hours"); }
	if (minutes > 59) { throw invalid_argument("You cannot set a time zone superior to 59 minutes"); }
	witsml2__Well* well = static_cast<witsml2__Well*>(gsoapProxy2_1);
	if (well->TimeZone == nullptr) { well->TimeZone = soap_new_eml21__TimeZone(gsoapProxy2_1->soap, 1); }

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
GETTER_PRESENCE_ATTRIBUTE_IMPL(TimeZone)
bool Well::getTimeZoneDirection() const {
	if (!hasTimeZone()) { throw invalid_argument("The  attribute to get does not exist."); }
	return static_cast<witsml2__Well*>(gsoapProxy2_1)->TimeZone->at(0) != '-';
}
unsigned short Well::getTimeZoneHours() const {
	if (!hasTimeZone()) { throw invalid_argument("The  attribute to get does not exist."); }
	if (static_cast<witsml2__Well*>(gsoapProxy2_1)->TimeZone->size() == 1) { return 0; }
	if (static_cast<witsml2__Well*>(gsoapProxy2_1)->TimeZone->size() != 6) { throw invalid_argument("The time zone does not looks to conform to the XSD standard."); }

	istringstream iss(static_cast<witsml2__Well*>(gsoapProxy2_1)->TimeZone->substr(1,2));
	unsigned short result;
	iss >> result;
	return result;
}
unsigned short Well::getTimeZoneMinutes() const {
	if (!hasTimeZone()) { throw invalid_argument("The  attribute to get does not exist."); }
	if (static_cast<witsml2__Well*>(gsoapProxy2_1)->TimeZone->size() == 1) { return 0; }
	if (static_cast<witsml2__Well*>(gsoapProxy2_1)->TimeZone->size() != 6) { throw invalid_argument("The time zone does not looks to conform to the XSD standard."); }

	istringstream iss(static_cast<witsml2__Well*>(gsoapProxy2_1)->TimeZone->substr(4, 2));
	unsigned short result;
	iss >> result;
	return result;
}

double Well::getLocationProjectedX(unsigned int locationIndex)
{
	witsml2__Well* well = static_cast<witsml2__Well*>(gsoapProxy2_1);

	if (well->WellLocation.size() <= locationIndex) {
		throw range_error("The well location index is out of range.");
	}
	if (well->WellLocation[locationIndex]->soap_type() != SOAP_TYPE_gsoap_eml2_1_witsml2__ProjectedWellLocation){
		throw invalid_argument("The well location is not a projected one.");
	}

	return static_cast<witsml2__ProjectedWellLocation*>(well->WellLocation[locationIndex])->Coordinate1;
}

double Well::getLocationProjectedY(unsigned int locationIndex)
{
	witsml2__Well* well = static_cast<witsml2__Well*>(gsoapProxy2_1);

	if (well->WellLocation.size() <= locationIndex) {
		throw range_error("The well location index is out of range.");
	}
	if (well->WellLocation[locationIndex]->soap_type() != SOAP_TYPE_gsoap_eml2_1_witsml2__ProjectedWellLocation){
		throw invalid_argument("The well location is not a projected one.");
	}

	return static_cast<witsml2__ProjectedWellLocation*>(well->WellLocation[locationIndex])->Coordinate2;
}

void Well::pushBackLocation(
	const std::string & guid,
	double projectedX,
	double projectedY,
	unsigned int projectedCrsEpsgCode)
{
	witsml2__Well* well = static_cast<witsml2__Well*>(gsoapProxy2_1);

	witsml2__ProjectedWellLocation* location = soap_new_witsml2__ProjectedWellLocation(gsoapProxy2_1->soap, 1);
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
	location->Crs = soap_new_eml21__ProjectedEpsgCrs(gsoapProxy2_1->soap, 1);
	static_cast<eml21__ProjectedEpsgCrs*>(location->Crs)->EpsgCode = projectedCrsEpsgCode;

	well->WellLocation.push_back(location);
}

unsigned int Well::geLocationCount() const {
	return static_cast<witsml2__Well*>(gsoapProxy2_1)->WellLocation.size();
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
	witsml2__Well* well = static_cast<witsml2__Well*>(gsoapProxy2_1);

	witsml2__WellDatum* wellDatum = soap_new_witsml2__WellDatum(gsoapProxy2_1->soap, 1);
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

	wellDatum->Crs = soap_new_eml21__VerticalEpsgCrs(gsoapProxy2_1->soap, 1);
	static_cast<eml21__VerticalEpsgCrs*>(wellDatum->Crs)->EpsgCode = verticalCrsEpsgCode;

	wellDatum->Elevation = soap_new_witsml2__WellElevationCoord(gsoapProxy2_1->soap, 1);
	wellDatum->Elevation->datum = datum;
	wellDatum->Elevation->uom = elevationUnit;
	wellDatum->Elevation->__item = elevation;

	well->WellDatum.push_back(wellDatum);
}

unsigned int Well::getDatumCount() const
{
	return static_cast<witsml2__Well*>(gsoapProxy2_1)->WellDatum.size();
}

std::vector<epc::Relationship> Well::getAllSourceRelationships() const
{
	vector<Relationship> result;

	// XML backward relationship
	if (resqmlWellboreFeature != nullptr)
	{
		Relationship rel(resqmlWellboreFeature->getPartNameInEpcDocument(), "", resqmlWellboreFeature->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	for (size_t i = 0; i < wellboreSet.size(); ++i)
	{
		Relationship relWellbore(wellboreSet[i]->getPartNameInEpcDocument(), "", wellboreSet[i]->getUuid());
		relWellbore.setSourceObjectType();
		result.push_back(relWellbore);
	}

	for (size_t i = 0; i < wellCompletionSet.size(); ++i)
	{
		Relationship relWellCompletion(wellCompletionSet[i]->getPartNameInEpcDocument(), "", wellCompletionSet[i]->getUuid());
		relWellCompletion.setSourceObjectType();
		result.push_back(relWellCompletion);
	}

	return result;
}

std::vector<epc::Relationship> Well::getAllTargetRelationships() const {
	vector<Relationship> result;
	return result;
}

void Well::resolveTargetRelationships(COMMON_NS::EpcDocument * epcDoc) {}

RESQML2_0_1_NS::WellboreFeature* Well::getResqmlWellboreFeature() const
{
	return resqmlWellboreFeature;
}

const std::vector<Wellbore*>& Well::getWellbores() const
{
	return wellboreSet;
}

const std::vector<WellCompletion*>& Well::getWellcompletions() const
{
	return wellCompletionSet;
}
