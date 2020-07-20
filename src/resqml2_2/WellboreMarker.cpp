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
#include "../resqml2/BoundaryFeatureInterpretation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* WellboreMarker::XML_NS = "resqml22";

WellboreMarker::WellboreMarker(RESQML2_2_NS::WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title)
{
	if (wellboreMarkerFrame == nullptr) {
		throw invalid_argument("The wellbore marker frame representation cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__WellboreMarker(wellboreMarkerFrame->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	wellboreMarkerFrame->pushBackNewWellboreMarker(this);
}

WellboreMarker::WellboreMarker(RESQML2_2_NS::WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind geologicBoundaryKind)
{
	if (wellboreMarkerFrame == nullptr) {
		throw invalid_argument("The wellbore marker frame representation cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__WellboreMarker(wellboreMarkerFrame->getGsoapContext());	
	resqml22__WellboreMarker* marker = static_cast<resqml22__WellboreMarker*>(gsoapProxy2_3);

	marker->GeologicBoundaryKind = (resqml22__GeologicBoundaryKind*)soap_malloc(gsoapProxy2_3->soap, sizeof(resqml22__GeologicBoundaryKind));
	*(marker->GeologicBoundaryKind) = static_cast<resqml22__GeologicBoundaryKind>(geologicBoundaryKind);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	wellboreMarkerFrame->pushBackNewWellboreMarker(this);
}

bool WellboreMarker::hasAGeologicBoundaryKind() const
{
	return static_cast<resqml22__WellboreMarker*>(gsoapProxy2_3)->GeologicBoundaryKind != nullptr;
}

gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind WellboreMarker::getGeologicBoundaryKind() const
{
	if (!hasAGeologicBoundaryKind()) {
		throw invalid_argument("The marker has not a Geologic Boundary Kind.");
	}

	return static_cast<gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind>(*static_cast<resqml22__WellboreMarker*>(gsoapProxy2_3)->GeologicBoundaryKind);
}

COMMON_NS::DataObjectReference WellboreMarker::getBoundaryFeatureInterpretationDor() const
{
	if (static_cast<resqml22__WellboreMarker*>(gsoapProxy2_3)->Interpretation != nullptr)
		return COMMON_NS::DataObjectReference(static_cast<resqml22__WellboreMarker*>(gsoapProxy2_3)->Interpretation);

	return COMMON_NS::DataObjectReference();
}

void WellboreMarker::setBoundaryFeatureInterpretation(RESQML2_NS::BoundaryFeatureInterpretation* interp)
{
	getRepository()->addRelationship(this, interp);

    resqml22__WellboreMarker* marker = static_cast<resqml22__WellboreMarker*>(gsoapProxy2_3);
	marker->Interpretation = interp->newEml23Reference();
}
