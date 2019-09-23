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

const char* SeismicLineFeature::XML_TAG = "SeismicLineFeature";

SeismicLineFeature::SeismicLineFeature(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title,
	int traceIndexIncrement, int firstTraceIndex, unsigned int traceCount)
{
	if (repo == nullptr) {
		throw invalid_argument("The soap context cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORESeismicLineFeature(repo->getGsoapContext(), 1);
	_resqml20__SeismicLineFeature* seismicLine = static_cast<_resqml20__SeismicLineFeature*>(gsoapProxy2_0_1);

	seismicLine->TraceIndexIncrement = traceIndexIncrement;
	seismicLine->FirstTraceIndex = firstTraceIndex;
	seismicLine->TraceCount = traceCount;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addOrReplaceDataObject(this);
}

int SeismicLineFeature::getTraceIndexIncrement() const
{
	return static_cast<_resqml20__SeismicLineFeature*>(gsoapProxy2_0_1)->TraceIndexIncrement;
}
		
int SeismicLineFeature::getFirstTraceIndex() const
{
	return static_cast<_resqml20__SeismicLineFeature*>(gsoapProxy2_0_1)->FirstTraceIndex;
}
		
unsigned int SeismicLineFeature::getTraceCount() const
{
	return static_cast<_resqml20__SeismicLineFeature*>(gsoapProxy2_0_1)->TraceCount;
}

void SeismicLineFeature::setSeismicLineSet(SeismicLineSetFeature * seisLineSet)
{
	getRepository()->addRelationship(this, seisLineSet);

	static_cast<_resqml20__SeismicLineFeature*>(gsoapProxy2_0_1)->IsPartOf = seisLineSet->newResqmlReference();
}

SeismicLineSetFeature* SeismicLineFeature::getSeismicLineSet() const
{
	_resqml20__SeismicLineFeature* seismicLine = static_cast<_resqml20__SeismicLineFeature*>(gsoapProxy2_0_1);

	return seismicLine->IsPartOf == nullptr ? nullptr : getRepository()->getDataObjectByUuid<SeismicLineSetFeature>(seismicLine->IsPartOf->UUID);
}

void SeismicLineFeature::loadTargetRelationships()
{
	_resqml20__SeismicLineFeature* seismicLine = static_cast<_resqml20__SeismicLineFeature*>(gsoapProxy2_0_1);

	if (seismicLine->IsPartOf != nullptr) {
		convertDorIntoRel<SeismicLineSetFeature>(seismicLine->IsPartOf);
	}
}
