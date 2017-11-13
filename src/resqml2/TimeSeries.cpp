/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#include "resqml2/TimeSeries.h"

#include <stdexcept>

#include "resqml2/AbstractValuesProperty.h"

using namespace std;
using namespace resqml2;
using namespace epc;

const char* TimeSeries::XML_TAG = "TimeSeries";

void TimeSeries::pushBackTimestamp(const time_t & timestamp)
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
			if (timeSeries->Time[result]->DateTime == timestamp) {
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
