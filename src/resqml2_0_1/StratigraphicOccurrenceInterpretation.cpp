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
#include "../resqml2/StratigraphicColumnRankInterpretation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* StratigraphicOccurrenceInterpretation::XML_NS = "resqml20";

StratigraphicOccurrenceInterpretation::StratigraphicOccurrenceInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__OrderingCriteria orderingCriteria)
{
	if (orgFeat == nullptr) {
		throw invalid_argument("The interpreted organization feature cannot be null.");
	}
	if (!orgFeat->isPartial() && dynamic_cast<RESQML2_0_1_NS::OrganizationFeature*>(orgFeat) != nullptr
		&& static_cast<RESQML2_0_1_NS::OrganizationFeature*>(orgFeat)->getKind() != gsoap_resqml2_0_1::resqml20__OrganizationKind::stratigraphic) {
		throw invalid_argument("The kind of an organization feature linked to a stratigraphic occurrence interpretation must be a stratigraphic one.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREStratigraphicOccurrenceInterpretation(orgFeat->getGsoapContext());
	static_cast<_resqml20__StratigraphicOccurrenceInterpretation*>(gsoapProxy2_0_1)->Domain = resqml20__Domain::mixed;
	static_cast<_resqml20__StratigraphicOccurrenceInterpretation*>(gsoapProxy2_0_1)->OrderingCriteria = orderingCriteria;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	orgFeat->getRepository()->addDataObject(this);
	setInterpretedFeature(orgFeat);
}

void StratigraphicOccurrenceInterpretation::setStratigraphicColumnRankInterpretation(RESQML2_NS::StratigraphicColumnRankInterpretation * stratiColumnRankInterp)
{
	getRepository()->addRelationship(this, stratiColumnRankInterp);

	_resqml20__StratigraphicOccurrenceInterpretation* interp = static_cast<_resqml20__StratigraphicOccurrenceInterpretation*>(gsoapProxy2_0_1);
	interp->IsOccurrenceOf = stratiColumnRankInterp->newResqmlReference();
}

COMMON_NS::DataObjectReference StratigraphicOccurrenceInterpretation::getStratigraphicColumnRankInterpretationDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<_resqml20__StratigraphicOccurrenceInterpretation*>(gsoapProxy2_0_1)->IsOccurrenceOf);
}
