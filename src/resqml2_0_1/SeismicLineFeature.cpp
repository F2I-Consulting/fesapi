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
#include "SeismicLineFeature.h"

#include "../resqml2/SeismicLineSetFeature.h"

using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

SeismicLineFeature::SeismicLineFeature(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title,
	int64_t traceIndexIncrement, int64_t firstTraceIndex, uint64_t traceCount)
{
	if (repo == nullptr) {
		throw std::invalid_argument("The soap context cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORESeismicLineFeature(repo->getGsoapContext());
	_resqml20__SeismicLineFeature* seismicLine = static_cast<_resqml20__SeismicLineFeature*>(gsoapProxy2_0_1);

	seismicLine->TraceIndexIncrement = traceIndexIncrement;
	seismicLine->FirstTraceIndex = firstTraceIndex;
	seismicLine->TraceCount = traceCount;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(this);
}
