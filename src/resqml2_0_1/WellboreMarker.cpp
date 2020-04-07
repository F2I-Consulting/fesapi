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
#include "WellboreMarker.h"

#include <stdexcept>

#include "WellboreMarkerFrameRepresentation.h"
#include "BoundaryFeatureInterpretation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* WellboreMarker::XML_TAG = "WellboreMarker";

WellboreMarker::WellboreMarker(WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title)
{
	gsoapProxy2_0_1 = soap_new_resqml20__WellboreMarker(wellboreMarkerFrame->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	wellboreMarkerFrame->pushBackNewWellboreMarker(this);
}

WellboreMarker::WellboreMarker(WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind geologicBoundaryKind)
{
	gsoapProxy2_0_1 = soap_new_resqml20__WellboreMarker(wellboreMarkerFrame->getGsoapContext());	
	resqml20__WellboreMarker* marker = static_cast<resqml20__WellboreMarker*>(gsoapProxy2_0_1);

	marker->GeologicBoundaryKind = (resqml20__GeologicBoundaryKind*)soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml20__GeologicBoundaryKind));
	*(marker->GeologicBoundaryKind) = geologicBoundaryKind;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	wellboreMarkerFrame->pushBackNewWellboreMarker(this);
}

bool WellboreMarker::hasAGeologicBoundaryKind() const
{
	return static_cast<resqml20__WellboreMarker*>(gsoapProxy2_0_1)->GeologicBoundaryKind != nullptr;
}

resqml20__GeologicBoundaryKind WellboreMarker::getGeologicBoundaryKind() const
{
	if (!hasAGeologicBoundaryKind()) {
		throw invalid_argument("The marker has not a Geologic Boundary Kind.");
	}

	return *(static_cast<resqml20__WellboreMarker*>(gsoapProxy2_0_1)->GeologicBoundaryKind);
}

std::string WellboreMarker::getBoundaryFeatureInterpretationUuid() const
{
	if (static_cast<resqml20__WellboreMarker*>(gsoapProxy2_0_1)->Interpretation != nullptr)
		return static_cast<resqml20__WellboreMarker*>(gsoapProxy2_0_1)->Interpretation->UUID;

	return "";
}

BoundaryFeatureInterpretation* WellboreMarker::getBoundaryFeatureInterpretation() const
{
	return getWellMarkerFrameRepresentation()->getRepository()->getDataObjectByUuid<BoundaryFeatureInterpretation>(getBoundaryFeatureInterpretationUuid());
}

void WellboreMarker::setBoundaryFeatureInterpretation(BoundaryFeatureInterpretation* interp)
{
	getRepository()->addRelationship(this, interp);

    resqml20__WellboreMarker* marker = static_cast<resqml20__WellboreMarker*>(gsoapProxy2_0_1);
	marker->Interpretation = interp->newResqmlReference();
}

void WellboreMarker::loadTargetRelationships()
{}

WellboreMarkerFrameRepresentation const * WellboreMarker::getWellMarkerFrameRepresentation() const
{
	const vector<WellboreMarkerFrameRepresentation *> wmfr = getRepository()->getSourceObjects<WellboreMarkerFrameRepresentation>(this);
	return wmfr.size() == 1 ? wmfr[0] : nullptr;
}
