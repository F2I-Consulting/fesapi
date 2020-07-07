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
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* TimeSeries::XML_NS = "resqml20";

TimeSeries::TimeSeries(COMMON_NS::DataObjectRepository* repo, const string & guid, const string & title)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORETimeSeries(repo->getGsoapContext());
	
	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addOrReplaceDataObject(this);
}

void TimeSeries::pushBackTimestamp(const tm & timestamp)
{
	gsoap_resqml2_0_1::resqml20__Timestamp* ts = gsoap_resqml2_0_1::soap_new_resqml20__Timestamp(gsoapProxy2_0_1->soap);
	ts->DateTime = timestamp;
	static_cast<gsoap_resqml2_0_1::_resqml20__TimeSeries*>(gsoapProxy2_0_1)->Time.push_back(ts);
}

unsigned int TimeSeries::getTimestampIndex(time_t timestamp) const
{
	gsoap_resqml2_0_1::_resqml20__TimeSeries* timeSeries = static_cast<gsoap_resqml2_0_1::_resqml20__TimeSeries*>(gsoapProxy2_0_1);

	for (size_t result = 0; result < timeSeries->Time.size(); ++result) {
		if (timeTools::timegm(&timeSeries->Time[result]->DateTime) == timestamp) {
			return result;
		}
	}

	throw out_of_range("The timestamp has not been found in the allowed range.");
}

unsigned int TimeSeries::getTimestampIndex(const tm & timestamp) const
{
	gsoap_resqml2_0_1::_resqml20__TimeSeries* timeSeries = static_cast<gsoap_resqml2_0_1::_resqml20__TimeSeries*>(gsoapProxy2_0_1);

	for (size_t result = 0; result < timeSeries->Time.size(); ++result) {
		// Very basic equality check between two tm
		if (timeSeries->Time[result]->DateTime.tm_year == timestamp.tm_year &&
			timeSeries->Time[result]->DateTime.tm_mon == timestamp.tm_mon &&
			timeSeries->Time[result]->DateTime.tm_mday == timestamp.tm_mday &&
			timeSeries->Time[result]->DateTime.tm_hour == timestamp.tm_hour &&
			timeSeries->Time[result]->DateTime.tm_min == timestamp.tm_min &&
			timeSeries->Time[result]->DateTime.tm_sec == timestamp.tm_sec) {
			return result;
		}
	}

	throw out_of_range("The timestamp has not been found in the allowed range.");
}

unsigned int TimeSeries::getTimestampCount() const
{
	return static_cast<gsoap_resqml2_0_1::_resqml20__TimeSeries*>(gsoapProxy2_0_1)->Time.size();
}

tm TimeSeries::getTimestampAsTimeStructure(unsigned int index) const
{
	gsoap_resqml2_0_1::_resqml20__TimeSeries* timeSeries = static_cast<gsoap_resqml2_0_1::_resqml20__TimeSeries*>(gsoapProxy2_0_1);

	if (timeSeries->Time.size() > index) {
		return timeSeries->Time[index]->DateTime;
	}

	throw out_of_range("The index is out of range");
}
