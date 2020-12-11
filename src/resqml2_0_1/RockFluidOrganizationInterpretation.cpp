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
#include "RockFluidOrganizationInterpretation.h"

#include "OrganizationFeature.h"
#include "../resqml2/RockFluidUnitInterpretation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* RockFluidOrganizationInterpretation::XML_TAG = "StratigraphicOccurrenceInterpretation";
const char* RockFluidOrganizationInterpretation::XML_NS = "resqml20";

RockFluidOrganizationInterpretation::RockFluidOrganizationInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title)
{
	if (orgFeat == nullptr) {
		throw invalid_argument("The interpreted organization feature cannot be null.");
	}
	if (!orgFeat->isPartial() && dynamic_cast<RESQML2_0_1_NS::OrganizationFeature*>(orgFeat) != nullptr
		&& static_cast<RESQML2_0_1_NS::OrganizationFeature*>(orgFeat)->getKind() != gsoap_resqml2_0_1::resqml20__OrganizationKind__fluid) {
		throw invalid_argument("The kind of the v2.0.1 organization feature is not a fluid organization.");
	}

	// it is not a bug to create a strati occurence instead of a reock fluid org : http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-500-106-0-R-sv2010.html
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREStratigraphicOccurrenceInterpretation(orgFeat->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setInterpretedFeature(orgFeat);
}

void RockFluidOrganizationInterpretation::pushBackRockFluidUnitInterpretation(RESQML2_NS::RockFluidUnitInterpretation * rockFluidUnitInterpretation)
{
	if (rockFluidUnitInterpretation == nullptr) {
		throw invalid_argument("The rock fluid unit interpretation cannot be null.");
	}

	auto* unitIndex = soap_new_resqml20__GeologicUnitInterpretationIndex(getGsoapContext());
	unitIndex->Index = static_cast<_resqml20__StratigraphicOccurrenceInterpretation*>(gsoapProxy2_0_1)->GeologicUnitIndex.size();
	unitIndex->Unit = rockFluidUnitInterpretation->newResqmlReference();

	static_cast<_resqml20__StratigraphicOccurrenceInterpretation*>(gsoapProxy2_0_1)->GeologicUnitIndex.push_back(unitIndex);
}

unsigned int RockFluidOrganizationInterpretation::getRockFluidUnitInterpCount() const
{
	return static_cast<_resqml20__StratigraphicOccurrenceInterpretation*>(gsoapProxy2_0_1)->GeologicUnitIndex.size();
}

COMMON_NS::DataObjectReference RockFluidOrganizationInterpretation::getRockFluidUnitInterpretationDor(unsigned int index) const
{
	if (index >= getRockFluidUnitInterpCount()) {
		throw out_of_range("The index is out of range");
	}

	return COMMON_NS::DataObjectReference(static_cast<_resqml20__StratigraphicOccurrenceInterpretation*>(gsoapProxy2_0_1)->GeologicUnitIndex[index]->Unit);
}
