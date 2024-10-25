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
#include "StreamlinesFeature.h"

#include "../eml2/TimeSeries.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* StreamlinesFeature::XML_NS = "resqml22";

StreamlinesFeature::StreamlinesFeature(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title, uint64_t timeIndex, EML2_NS::TimeSeries* timeSeries)
{
	if (timeSeries == nullptr) {
		throw invalid_argument("The time series of a StreamlinesFeature is mandatory.");
	}

	gsoapProxy2_3 = soap_new_resqml22__StreamlinesFeature(repo->getGsoapContext());
	resqml22__StreamlinesFeature* sf = static_cast<resqml22__StreamlinesFeature*>(gsoapProxy2_3);
	sf->TimeIndex = soap_new_eml23__TimeIndex(repo->getGsoapContext());
	sf->TimeIndex->Index = timeIndex;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});

	// relationhsips
	sf->TimeIndex->TimeSeries = timeSeries->newEml23Reference();
	getRepository()->addRelationship(this, timeSeries);
}

COMMON_NS::DataObjectReference StreamlinesFeature::getTimeSeriesDor() const
{
	if (isPartial()) {
		throw std::logic_error("You cannot get the Time Series of a partial Streamlines feature.");
	}

	return COMMON_NS::DataObjectReference(static_cast<resqml22__StreamlinesFeature*>(gsoapProxy2_3)->TimeIndex->TimeSeries);
}

uint64_t StreamlinesFeature::getTimeIndex() const
{
	return static_cast<_resqml22__StreamlinesFeature*>(gsoapProxy2_3)->TimeIndex->Index;
}
