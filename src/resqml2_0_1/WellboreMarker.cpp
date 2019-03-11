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
#include "resqml2_0_1/WellboreMarker.h"

#include <stdexcept>

#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"
#include "resqml2_0_1/BoundaryFeatureInterpretation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* WellboreMarker::XML_TAG = "WellboreMarker";

WellboreMarker::WellboreMarker(WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title):
	boundaryFeatureInterpretation(nullptr), wellboreMarkerFrameRepresentation(wellboreMarkerFrame)
{
	gsoapProxy2_0_1 = soap_new_resqml2__WellboreMarker(wellboreMarkerFrame->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());
}

WellboreMarker::WellboreMarker(WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind & geologicBoundaryKind):
	boundaryFeatureInterpretation(nullptr), wellboreMarkerFrameRepresentation(wellboreMarkerFrame)
{
	gsoapProxy2_0_1 = soap_new_resqml2__WellboreMarker(wellboreMarkerFrame->getGsoapContext(), 1);	
	resqml2__WellboreMarker* marker = static_cast<resqml2__WellboreMarker*>(gsoapProxy2_0_1);

	marker->GeologicBoundaryKind = (resqml2__GeologicBoundaryKind*)soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml2__GeologicBoundaryKind));
	*(marker->GeologicBoundaryKind) = geologicBoundaryKind;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());
}

bool WellboreMarker::hasAGeologicBoundaryKind()
{
	return static_cast<resqml2__WellboreMarker*>(gsoapProxy2_0_1)->GeologicBoundaryKind != nullptr;
}

resqml2__GeologicBoundaryKind WellboreMarker::getGeologicBoundaryKind()
{
	if (!hasAGeologicBoundaryKind())
		throw invalid_argument("The marker has not a Geologic Boundary Kind.");

	return *(static_cast<resqml2__WellboreMarker*>(gsoapProxy2_0_1)->GeologicBoundaryKind);
}

std::string WellboreMarker::getBoundaryFeatureInterpretationUuid() const
{
	if (static_cast<resqml2__WellboreMarker*>(gsoapProxy2_0_1)->Interpretation != nullptr)
		return static_cast<resqml2__WellboreMarker*>(gsoapProxy2_0_1)->Interpretation->UUID;

	return "";
}

void WellboreMarker::setBoundaryFeatureInterpretation(BoundaryFeatureInterpretation* interp)
{
	// EPC
	boundaryFeatureInterpretation = interp;
	interp->wellboreMarkerSet.push_back(this);

    // XML
	if (updateXml)
	{
        resqml2__WellboreMarker* marker = static_cast<resqml2__WellboreMarker*>(gsoapProxy2_0_1);
		marker->Interpretation = interp->newResqmlReference();
	}
}

void WellboreMarker::importRelationshipSetFromEpc(COMMON_NS::EpcDocument*)
{}
