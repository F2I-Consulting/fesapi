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
#include "StratigraphicOccurrenceInterpretation.h"

#include <stdexcept>

#include "OrganizationFeature.h"
#include "StratigraphicColumnRankInterpretation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* StratigraphicOccurrenceInterpretation::XML_TAG = "StratigraphicOccurrenceInterpretation";

StratigraphicOccurrenceInterpretation::StratigraphicOccurrenceInterpretation(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml20__OrderingCriteria & orderingCriteria)
{
	if (orgFeat == nullptr) {
		throw invalid_argument("The interpreted organization feature cannot be null.");
	}
	if (!orgFeat->isPartial() && orgFeat->getKind() != gsoap_resqml2_0_1::resqml20__OrganizationKind__stratigraphic) {
		throw invalid_argument("The kind of an organization feature linked to a stratigraphic occurrence interpretation must be a stratigraphic one.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREStratigraphicOccurrenceInterpretation(orgFeat->getGsoapContext());
	static_cast<_resqml20__StratigraphicOccurrenceInterpretation*>(gsoapProxy2_0_1)->Domain = resqml20__Domain__mixed;
	static_cast<_resqml20__StratigraphicOccurrenceInterpretation*>(gsoapProxy2_0_1)->OrderingCriteria = orderingCriteria;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setInterpretedFeature(orgFeat);
}

void StratigraphicOccurrenceInterpretation::setStratigraphicColumnRankInterpretation(StratigraphicColumnRankInterpretation * stratiColumnRankInterp)
{
	getRepository()->addRelationship(this, stratiColumnRankInterp);

	_resqml20__StratigraphicOccurrenceInterpretation* interp = static_cast<_resqml20__StratigraphicOccurrenceInterpretation*>(gsoapProxy2_0_1);
	interp->IsOccurrenceOf = stratiColumnRankInterp->newResqmlReference();
}

StratigraphicColumnRankInterpretation * StratigraphicOccurrenceInterpretation::getStratigraphicColumnRankInterpretation() const
{
	return getRepository()->getDataObjectByUuid<StratigraphicColumnRankInterpretation>(getStratigraphicColumnRankInterpretationUuid());
}

std::string StratigraphicOccurrenceInterpretation::getStratigraphicColumnRankInterpretationUuid() const
{
	return static_cast<_resqml20__StratigraphicOccurrenceInterpretation*>(gsoapProxy2_0_1)->IsOccurrenceOf->UUID;
}

std::vector<class WellboreMarkerFrameRepresentation *> StratigraphicOccurrenceInterpretation::getWellboreMarkerFrameRepresentationSet() const
{
	return getRepository()->getSourceObjects<WellboreMarkerFrameRepresentation>(this);
}
	
void StratigraphicOccurrenceInterpretation::loadTargetRelationships()
{
	AbstractStratigraphicOrganizationInterpretation::loadTargetRelationships();

	_resqml20__StratigraphicOccurrenceInterpretation* interp = static_cast<_resqml20__StratigraphicOccurrenceInterpretation*>(gsoapProxy2_0_1); 

	if (interp->IsOccurrenceOf != nullptr)
	{
		convertDorIntoRel<StratigraphicColumnRankInterpretation>(interp->IsOccurrenceOf);
	}
}
