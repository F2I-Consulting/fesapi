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
#include "TimeSeries.h"

#include <stdexcept>

#include "../tools/TimeTools.h"

using namespace std;
using namespace EML2_3_NS;
using namespace gsoap_eml2_3;

TimeSeries::TimeSeries(COMMON_NS::DataObjectRepository* repo, const string & guid, const string & title)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_3 = soap_new_eml23__TimeSeries(repo->getGsoapContext());
	
	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(this);
}

void TimeSeries::pushBackTimestamp(const tm & timestamp, LONG64 yearOffset)
{
	gsoap_eml2_3::eml23__GeologicTime* ts = gsoap_eml2_3::soap_new_eml23__GeologicTime(gsoapProxy2_3->soap);
	ts->DateTime = timestamp;
	if (yearOffset != 0) {
		ts->AgeOffsetAttribute = (LONG64*)soap_malloc(gsoapProxy2_3->soap, sizeof(LONG64));
		*ts->AgeOffsetAttribute = yearOffset;
	}
	static_cast<gsoap_eml2_3::_eml23__TimeSeries*>(gsoapProxy2_3)->Time.push_back(ts);
}

uint64_t TimeSeries::getTimestampIndex(time_t timestamp, LONG64 yearOffset) const
{
	gsoap_eml2_3::_eml23__TimeSeries* timeSeries = static_cast<gsoap_eml2_3::_eml23__TimeSeries*>(gsoapProxy2_3);

	for (size_t result = 0; result < timeSeries->Time.size(); ++result) {
		if (timeTools::timegm(timeSeries->Time[result]->DateTime) == timestamp &&
			((yearOffset == 0 && timeSeries->Time[result]->AgeOffsetAttribute == nullptr) || (timeSeries->Time[result]->AgeOffsetAttribute != nullptr && *timeSeries->Time[result]->AgeOffsetAttribute == yearOffset))) {
			return result;
		}
	}

	throw out_of_range("The timestamp has not been found in the allowed range.");
}

uint64_t TimeSeries::getTimestampIndex(const tm & timestamp, LONG64 yearOffset) const
{
	gsoap_eml2_3::_eml23__TimeSeries* timeSeries = static_cast<gsoap_eml2_3::_eml23__TimeSeries*>(gsoapProxy2_3);

	for (size_t result = 0; result < timeSeries->Time.size(); ++result) {
		// Very basic equality check between two tm
		if ((timeSeries->Time[result]->DateTime.tm_year == timestamp.tm_year &&
			timeSeries->Time[result]->DateTime.tm_mon == timestamp.tm_mon &&
			timeSeries->Time[result]->DateTime.tm_mday == timestamp.tm_mday &&
			timeSeries->Time[result]->DateTime.tm_hour == timestamp.tm_hour &&
			timeSeries->Time[result]->DateTime.tm_min == timestamp.tm_min &&
			timeSeries->Time[result]->DateTime.tm_sec == timestamp.tm_sec) &&
			((yearOffset == 0 && timeSeries->Time[result]->AgeOffsetAttribute == nullptr) || (timeSeries->Time[result]->AgeOffsetAttribute != nullptr && *timeSeries->Time[result]->AgeOffsetAttribute == yearOffset))) {
			return result;
		}
	}

	throw out_of_range("The timestamp has not been found in the allowed range.");
}

uint64_t TimeSeries::getTimestampCount() const
{
	return static_cast<gsoap_eml2_3::_eml23__TimeSeries*>(gsoapProxy2_3)->Time.size();
}

tm TimeSeries::getTimestampAsTimeStructure(uint64_t index) const
{
	gsoap_eml2_3::_eml23__TimeSeries* timeSeries = static_cast<gsoap_eml2_3::_eml23__TimeSeries*>(gsoapProxy2_3);

	if (timeSeries->Time.size() > index) {
		return timeSeries->Time[index]->DateTime;
	}

	throw out_of_range("The index is out of range");
}
