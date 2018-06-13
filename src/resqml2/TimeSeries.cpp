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
#include "resqml2/TimeSeries.h"

#include <stdexcept>

#include "resqml2/AbstractValuesProperty.h"

using namespace std;
using namespace RESQML2_NS;
using namespace epc;

const char* TimeSeries::XML_TAG = "TimeSeries";

void TimeSeries::pushBackTimestamp(const time_t & timestamp)
{
	pushBackTimestamp(*gmtime(&timestamp));
}

void TimeSeries::pushBackTimestamp(const tm & timestamp)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__Timestamp* ts = gsoap_resqml2_0_1::soap_new_resqml2__Timestamp(gsoapProxy2_0_1->soap, 1);
		ts->DateTime = timestamp;
		static_cast<gsoap_resqml2_0_1::_resqml2__TimeSeries*>(gsoapProxy2_0_1)->Time.push_back(ts);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

unsigned int TimeSeries::getTimestampIndex(const time_t & timestamp) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::_resqml2__TimeSeries* timeSeries = static_cast<gsoap_resqml2_0_1::_resqml2__TimeSeries*>(gsoapProxy2_0_1);

		for (size_t result = 0; result < timeSeries->Time.size(); ++result) {
			if (mktime(&timeSeries->Time[result]->DateTime) == timestamp) {
				return result;
			}
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}

	throw out_of_range("The timestamp has not been found in the allowed range.");
}

unsigned int TimeSeries::getTimestampIndex(const tm & timestamp) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::_resqml2__TimeSeries* timeSeries = static_cast<gsoap_resqml2_0_1::_resqml2__TimeSeries*>(gsoapProxy2_0_1);

		for (size_t result = 0; result < timeSeries->Time.size(); ++result) {
			// Very basic equaility check between two tm
			if (timeSeries->Time[result]->DateTime.tm_year == timestamp.tm_year &&
				timeSeries->Time[result]->DateTime.tm_mon == timestamp.tm_mon &&
				timeSeries->Time[result]->DateTime.tm_mday == timestamp.tm_mday &&
				timeSeries->Time[result]->DateTime.tm_hour == timestamp.tm_hour &&
				timeSeries->Time[result]->DateTime.tm_min == timestamp.tm_min &&
				timeSeries->Time[result]->DateTime.tm_sec == timestamp.tm_sec) {
				return result;
			}
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}

	throw out_of_range("The timestamp has not been found in the allowed range.");
}

unsigned int TimeSeries::getTimestampCount() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::_resqml2__TimeSeries*>(gsoapProxy2_0_1)->Time.size();
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

time_t TimeSeries::getTimestamp(const unsigned int & index) const
{
	tm temp = getTimestampAsTimeStructure(index);
	return mktime(&temp);
}

tm TimeSeries::getTimestampAsTimeStructure(const unsigned int & index) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::_resqml2__TimeSeries* timeSeries = static_cast<gsoap_resqml2_0_1::_resqml2__TimeSeries*>(gsoapProxy2_0_1);

		if (timeSeries->Time.size() > index) {
			return timeSeries->Time[index]->DateTime;
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}

	throw out_of_range("The index is out of range");
}

vector<Relationship> TimeSeries::getAllEpcRelationships() const
{
	vector<Relationship> result;

	// backward relationships
	for (size_t i = 0; i < propertySet.size(); i++)
	{
		Relationship rel(propertySet[i]->getPartNameInEpcDocument(), "", propertySet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

