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
#include "resqml2_0_1/SeismicLineFeature.h"

#include "resqml2_0_1/SeismicLineSetFeature.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* SeismicLineFeature::XML_TAG = "SeismicLineFeature";

SeismicLineFeature::SeismicLineFeature(soap* soapContext, const std::string & guid, const std::string & title,
			const int & traceIndexIncrement, const int & firstTraceIndex, const unsigned int & traceCount):
	seismicLineSet(nullptr)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORESeismicLineFeature(soapContext, 1);
	_resqml2__SeismicLineFeature* seismicLine = static_cast<_resqml2__SeismicLineFeature*>(gsoapProxy2_0_1);

	seismicLine->TraceIndexIncrement = traceIndexIncrement;
	seismicLine->FirstTraceIndex = firstTraceIndex;
	seismicLine->TraceCount = traceCount;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

int SeismicLineFeature::getTraceIndexIncrement() const
{
	return static_cast<_resqml2__SeismicLineFeature*>(gsoapProxy2_0_1)->TraceIndexIncrement;
}
		
int SeismicLineFeature::getFirstTraceIndex() const
{
	return static_cast<_resqml2__SeismicLineFeature*>(gsoapProxy2_0_1)->FirstTraceIndex;
}
		
unsigned int SeismicLineFeature::getTraceCount() const
{
	return static_cast<_resqml2__SeismicLineFeature*>(gsoapProxy2_0_1)->TraceCount;
}

void SeismicLineFeature::setSeismicLineSet(SeismicLineSetFeature * seisLineSet)
{
	// EPC
	seismicLineSet = seisLineSet;
	seisLineSet->seismicLineSet.push_back(this);

	// XML
	if (updateXml)
	{
		static_cast<_resqml2__SeismicLineFeature*>(gsoapProxy2_0_1)->IsPartOf = seisLineSet->newResqmlReference();
	}
}

std::vector<epc::Relationship> SeismicLineFeature::getAllEpcRelationships() const
{
	std::vector<epc::Relationship> result;

	if (seismicLineSet)
	{
		Relationship rel(seismicLineSet->getPartNameInEpcDocument(), "", seismicLineSet->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}

	return result;
}

void SeismicLineFeature::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	updateXml = false;

	_resqml2__SeismicLineFeature* seismicLine = static_cast<_resqml2__SeismicLineFeature*>(gsoapProxy2_0_1);

	if (seismicLine->IsPartOf)
	{
		SeismicLineSetFeature* seisLineSet = static_cast<SeismicLineSetFeature*>(epcDoc->getResqmlAbstractObjectByUuid(seismicLine->IsPartOf->UUID));
		if (seisLineSet)
			setSeismicLineSet(seisLineSet);
	}

	updateXml = true;
}

