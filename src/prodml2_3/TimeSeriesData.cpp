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
#include "TimeSeriesData.h"

#include <stdexcept>

#include "../tools/TimeTools.h"

using namespace std;
using namespace PRODML2_3_NS;
using namespace gsoap_eml2_3;

TimeSeriesData::TimeSeriesData(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid,
	const std::string & title)
{
	if (repo == nullptr) {
		throw invalid_argument("A repo must exist.");
	}

	gsoapProxy2_3 = soap_new_prodml23__TimeSeriesData(repo->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
}

void TimeSeriesData::pushBackKeywordValue(gsoap_eml2_3::prodml23__TimeSeriesKeyword keyword, const std::string & value)
{
	auto keyVal = soap_new_prodml23__KeywordValueStruct(getGsoapContext());
	keyVal->keyword = keyword;
	keyVal->__item = value;

	prodml23__TimeSeriesData* tsData = static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3);
	tsData->Key.push_back(keyVal);
}

void TimeSeriesData::setUom(gsoap_resqml2_0_1::resqml20__ResqmlUom uom)
{
	prodml23__TimeSeriesData* tsData = static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3);
	if (tsData->Uom == nullptr) {
		tsData->Uom = soap_new_std__string(getGsoapContext());
	}
	tsData->Uom->assign(gsoap_resqml2_0_1::soap_resqml20__ResqmlUom2s(gsoapProxy2_3->soap, uom));
}

void TimeSeriesData::setMeasureClass(gsoap_eml2_3::eml23__MeasureClass measureClass)
{
	prodml23__TimeSeriesData* tsData = static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3);
	if (tsData->MeasureClass == nullptr) {
		tsData->MeasureClass = (gsoap_eml2_3::eml23__MeasureClass*)soap_malloc(getGsoapContext(), sizeof(gsoap_eml2_3::eml23__MeasureClass));
	}
	*tsData->MeasureClass = measureClass;
}

void TimeSeriesData::pushBackDoubleValue(double value, time_t timestamp)
{
	auto dblVal = soap_new_prodml23__DoubleValue(getGsoapContext());
	dblVal->DoubleValue = soap_new_prodml23__TimeSeriesDoubleSample(getGsoapContext());
	dblVal->DoubleValue->__item = value;
	if (timestamp > -1) {
		dblVal->DoubleValue->dTim = (tm*)soap_malloc(getGsoapContext(), sizeof(tm));
		std::tm tmConversion = timeTools::to_calendar_time(timeTools::from_time_t(timestamp));
		*dblVal->DoubleValue->dTim = tmConversion;
	}

	prodml23__TimeSeriesData* tsData = static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3);
	tsData->DataValue.push_back(dblVal);
}

void TimeSeriesData::pushBackDoubleValue(double value, time_t timestamp, gsoap_eml2_3::prodml23__ValueStatus status)
{
	pushBackDoubleValue(value, timestamp);

	prodml23__TimeSeriesData* tsData = static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3);
	static_cast<prodml23__DoubleValue*>(tsData->DataValue[tsData->DataValue.size() - 1])->DoubleValue->status = soap_new_prodml23__ValueStatus(getGsoapContext());
	*static_cast<prodml23__DoubleValue*>(tsData->DataValue[tsData->DataValue.size() - 1])->DoubleValue->status = status;
}

void TimeSeriesData::pushBackStringValue(const std::string & value, time_t timestamp)
{
	auto strVal = soap_new_prodml23__StringValue(getGsoapContext());
	strVal->StringValue = soap_new_prodml23__TimeSeriesStringSample(getGsoapContext());
	strVal->StringValue->__item = value;
	if (timestamp > -1) {
		strVal->StringValue->dTim = (tm*)soap_malloc(getGsoapContext(), sizeof(tm));
		std::tm tmConversion = timeTools::to_calendar_time(timeTools::from_time_t(timestamp));
		*strVal->StringValue->dTim = tmConversion;
	}

	prodml23__TimeSeriesData* tsData = static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3);
	tsData->DataValue.push_back(strVal);
}

std::string TimeSeriesData::getUomAsString() const
{
	return static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3)->Uom == nullptr
		? ""
		: *static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3)->Uom;
}

std::string TimeSeriesData::getMeasureClassAsString() const
{
	return static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3)->MeasureClass == nullptr
		? ""
		: gsoap_eml2_3::soap_eml23__MeasureClass2s(gsoapProxy2_3->soap, *static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3)->MeasureClass);
}

unsigned int TimeSeriesData::getValueCount() const
{
	const size_t result = static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3)->DataValue.size();
	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much values.");
	}

	return static_cast<unsigned int>(result);
}

bool TimeSeriesData::isDoubleValue(unsigned int index) const
{
	prodml23__TimeSeriesData* tsData = static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3);
	if (index >= tsData->DataValue.size()) {
		throw std::out_of_range("The index is out of range.");
	}

	return tsData->DataValue[index]->soap_type() == SOAP_TYPE_gsoap_eml2_3_prodml23__DoubleValue;
}

bool TimeSeriesData::isStringValue(unsigned int index) const
{
	prodml23__TimeSeriesData* tsData = static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3);
	if (index >= tsData->DataValue.size()) {
		throw std::out_of_range("The index is out of range.");
	}

	return tsData->DataValue[index]->soap_type() == SOAP_TYPE_gsoap_eml2_3_prodml23__StringValue;
}

double TimeSeriesData::getDoubleValue(unsigned int index) const
{
	if (!isDoubleValue(index)) {
		throw std::logic_error("This value is not a double one");
	}

	prodml23__TimeSeriesData* tsData = static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3);
	return static_cast<prodml23__DoubleValue*>(tsData->DataValue[index])->DoubleValue->__item;
}

std::string TimeSeriesData::getStringValue(unsigned int index) const
{
	if (!isStringValue(index)) {
		throw std::logic_error("This value is not a string one");
	}

	prodml23__TimeSeriesData* tsData = static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3);
	return static_cast<prodml23__StringValue*>(tsData->DataValue[index])->StringValue->__item;
}

time_t TimeSeriesData::getValueTimestamp(unsigned int index) const
{
	prodml23__TimeSeriesData* tsData = static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3);
	tm* result = nullptr;
	if (isDoubleValue(index)) {
		result = static_cast<prodml23__DoubleValue*>(tsData->DataValue[index])->DoubleValue->dTim;
	}
	else if (isStringValue(index)) {
		result = static_cast<prodml23__StringValue*>(tsData->DataValue[index])->StringValue->dTim;
	}
	else {
		throw std::logic_error("This value is not a string one neither a double one");
	}

	return result == nullptr
		? -1
		: timeTools::timegm(*result);
}

bool TimeSeriesData::hasValueStatus(unsigned int index) const
{
	if (!isDoubleValue(index)) {
		return false;
	}

	prodml23__TimeSeriesData* tsData = static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3);
	return static_cast<prodml23__DoubleValue*>(tsData->DataValue[index])->DoubleValue->status != nullptr;
}

gsoap_eml2_3::prodml23__ValueStatus TimeSeriesData::getValueStatus(unsigned int index) const
{
	if (!hasValueStatus(index)) {
		throw std::logic_error("This value has no status");
	}

	prodml23__TimeSeriesData* tsData = static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3);
	return *static_cast<prodml23__DoubleValue*>(tsData->DataValue[index])->DoubleValue->status;
}

unsigned int TimeSeriesData::getKeywordCount() const
{
	const size_t result = static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3)->Key.size();
	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much keywords.");
	}

	return static_cast<unsigned int>(result);
}

gsoap_eml2_3::prodml23__TimeSeriesKeyword TimeSeriesData::getKeyword(unsigned int index) const
{
	prodml23__TimeSeriesData* tsData = static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3);
	if (index >= tsData->Key.size()) {
		throw std::out_of_range("The index is out of range.");
	}

	return tsData->Key[index]->keyword;
}

std::string TimeSeriesData::getKeywordValue(unsigned int index) const
{
	prodml23__TimeSeriesData* tsData = static_cast<prodml23__TimeSeriesData*>(gsoapProxy2_3);
	if (index >= tsData->Key.size()) {
		throw std::out_of_range("The index is out of range.");
	}

	return tsData->Key[index]->__item;
}
