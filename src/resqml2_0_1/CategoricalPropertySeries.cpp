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
#include "resqml2_0_1/CategoricalPropertySeries.h"

#include <stdexcept>

#include "resqml2_0_1/TimeSeries.h"
#include "resqml2/AbstractRepresentation.h"
#include "resqml2_0_1/PropertyKind.h"
#include "resqml2_0_1/StringTableLookup.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* CategoricalPropertySeries::XML_TAG = "CategoricalPropertySeries";

CategoricalPropertySeries::CategoricalPropertySeries(resqml2::AbstractRepresentation * rep, const string & guid, const string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
	StringTableLookup* strLookup, const resqml2__ResqmlPropertyKind & energisticsPropertyKind,
	resqml2::TimeSeries * ts, const bool & useInterval)
	: CategoricalProperty(strLookup)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORECategoricalPropertySeries(rep->getGsoapContext(), 1);	
	_resqml2__CategoricalPropertySeries* prop = static_cast<_resqml2__CategoricalPropertySeries*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	resqml2__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml2__StandardPropertyKind(gsoapProxy2_0_1->soap, 1);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	stringLookup->addCategoricalPropertyValues(this);
	prop->Lookup = stringLookup->newResqmlReference();

	setRepresentation(rep);

	prop->SeriesTimeIndices = soap_new_resqml2__TimeIndices(gsoapProxy2_0_1->soap, 1);
	prop->SeriesTimeIndices->TimeIndexCount = ts->getTimestampCount();
	prop->SeriesTimeIndices->UseInterval = useInterval;
	setTimeSeries(ts);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

CategoricalPropertySeries::CategoricalPropertySeries(resqml2::AbstractRepresentation * rep, const string & guid, const string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
	StringTableLookup* strLookup, resqml2::PropertyKind * localPropKind,
	resqml2::TimeSeries * ts, const bool & useInterval)
	:CategoricalProperty(strLookup)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORECategoricalPropertySeries(rep->getGsoapContext(), 1);	
	_resqml2__CategoricalPropertySeries* prop = static_cast<_resqml2__CategoricalPropertySeries*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	stringLookup->addCategoricalPropertyValues(this);
	prop->Lookup = stringLookup->newResqmlReference();

	setRepresentation(rep);

	prop->SeriesTimeIndices = soap_new_resqml2__TimeIndices(gsoapProxy2_0_1->soap, 1);
	prop->SeriesTimeIndices->TimeIndexCount = ts->getTimestampCount();
	prop->SeriesTimeIndices->UseInterval = useInterval;
	setTimeSeries(ts);

	setLocalPropertyKind(localPropKind);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

