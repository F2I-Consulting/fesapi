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
#include "../witsml2_1/WellboreMarker.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* WellboreMarker::XML_NS = "resqml20";

WellboreMarker::WellboreMarker(RESQML2_0_1_NS::WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title)
{
	if (wellboreMarkerFrame == nullptr) {
		throw invalid_argument("The wellbore marker frame representation cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__WellboreMarker(wellboreMarkerFrame->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	wellboreMarkerFrame->pushBackNewWellboreMarker(std::unique_ptr<RESQML2_0_1_NS::WellboreMarker>{this});
}

WellboreMarker::WellboreMarker(RESQML2_0_1_NS::WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind geologicBoundaryKind)
{
	if (wellboreMarkerFrame == nullptr) {
		throw invalid_argument("The wellbore marker frame representation cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__WellboreMarker(wellboreMarkerFrame->getGsoapContext());	
	resqml20__WellboreMarker* marker = static_cast<resqml20__WellboreMarker*>(gsoapProxy2_0_1);

	marker->GeologicBoundaryKind = (resqml20__GeologicBoundaryKind*)soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml20__GeologicBoundaryKind));
	*(marker->GeologicBoundaryKind) = geologicBoundaryKind;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	wellboreMarkerFrame->pushBackNewWellboreMarker(std::unique_ptr<RESQML2_0_1_NS::WellboreMarker>{this});
}

bool WellboreMarker::hasAGeologicBoundaryKind() const
{
	cannotBePartial();
	return static_cast<resqml20__WellboreMarker*>(gsoapProxy2_0_1)->GeologicBoundaryKind != nullptr;
}

resqml20__GeologicBoundaryKind WellboreMarker::getGeologicBoundaryKind() const
{
	if (!hasAGeologicBoundaryKind()) {
		throw invalid_argument("The marker has not a Geologic Boundary Kind.");
	}

	return *(static_cast<resqml20__WellboreMarker*>(gsoapProxy2_0_1)->GeologicBoundaryKind);
}

COMMON_NS::DataObjectReference WellboreMarker::getBoundaryFeatureInterpretationDor() const
{
	cannotBePartial();

	return static_cast<resqml20__WellboreMarker*>(gsoapProxy2_0_1)->Interpretation != nullptr
		? COMMON_NS::DataObjectReference(static_cast<resqml20__WellboreMarker*>(gsoapProxy2_0_1)->Interpretation)
		: COMMON_NS::DataObjectReference();
}

void WellboreMarker::setBoundaryFeatureInterpretation(RESQML2_NS::BoundaryFeatureInterpretation* interp)
{
	cannotBePartial();
	getRepository()->addRelationship(this, interp);

    resqml20__WellboreMarker* marker = static_cast<resqml20__WellboreMarker*>(gsoapProxy2_0_1);
	marker->Interpretation = interp->newResqmlReference();
}

COMMON_NS::DataObjectReference WellboreMarker::getWitsmlWellboreMarkerDor() const
{
	cannotBePartial();

	return static_cast<resqml20__WellboreMarker*>(gsoapProxy2_0_1)->WitsmlFormationMarker != nullptr
		? COMMON_NS::DataObjectReference(static_cast<resqml20__WellboreMarker*>(gsoapProxy2_0_1)->WitsmlFormationMarker)
		: COMMON_NS::DataObjectReference();
}

void WellboreMarker::setWitsmlWellboreMarker(WITSML2_1_NS::WellboreMarker * wellboreMarker)
{
	cannotBePartial();
	getRepository()->addRelationship(this, wellboreMarker);
	static_cast<resqml20__WellboreMarker*>(gsoapProxy2_0_1)->WitsmlFormationMarker = wellboreMarker->newResqmlReference();
}
