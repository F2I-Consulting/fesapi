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

#include <algorithm>

#include "OrganizationFeature.h"
#include "RockFluidUnitInterpretation.h"
#include "../resqml2/AbstractGridRepresentation.h"

#include "../tools/Misc.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* RockFluidOrganizationInterpretation::XML_TAG = "RockFluidOrganizationInterpretation";

RockFluidOrganizationInterpretation::RockFluidOrganizationInterpretation(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, RockFluidUnitInterpretation * rockFluidUnitInterp)
{
	if (orgFeat == nullptr) {
		throw invalid_argument("The interpreted organization feature cannot be null.");
	}
	if (!orgFeat->isPartial() && orgFeat->getKind() != gsoap_resqml2_0_1::resqml20__OrganizationKind__fluid) {
		throw invalid_argument("The kind of the organization feature is not a fluid organization.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORERockFluidOrganizationInterpretation(orgFeat->getGsoapContext());
	_resqml20__RockFluidOrganizationInterpretation* rfoi = static_cast<_resqml20__RockFluidOrganizationInterpretation*>(gsoapProxy2_0_1);
	rfoi->RockFluidUnitIndex = soap_new_resqml20__RockFluidUnitInterpretationIndex(orgFeat->getGsoapContext());
	// No need to initialize index since it is a bug : http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-500-106-0-R-sv2010.html
	pushBackRockFluidUnitInterpretation(rockFluidUnitInterp);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretedFeature(orgFeat);
}

std::vector<RESQML2_NS::AbstractGridRepresentation *> RockFluidOrganizationInterpretation::getGridRepresentationSet() const
{
	return getRepository()->getSourceObjects<RESQML2_NS::AbstractGridRepresentation>(this);
}

unsigned int RockFluidOrganizationInterpretation::getGridRepresentationCount() const
{
	const size_t count = getGridRepresentationSet().size();
	if (count > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("Too much grid representations.");
	}

	return static_cast<unsigned int>(count);
}

RESQML2_NS::AbstractGridRepresentation * RockFluidOrganizationInterpretation::getGridRepresentation(unsigned int index) const
{
	const std::vector<RESQML2_NS::AbstractGridRepresentation *>& gridRepresentationSet = getGridRepresentationSet();

	if (index >= gridRepresentationSet.size()) {
		throw range_error("The index of the grid representation to get is out of range.");
	}

	return gridRepresentationSet[index];
}

bool RockFluidOrganizationInterpretation::isAssociatedToGridRepresentation(RESQML2_NS::AbstractGridRepresentation* gridRep) const
{
	const std::vector<RESQML2_NS::AbstractGridRepresentation *>& gridRepresentationSet = getGridRepresentationSet();
	return find(gridRepresentationSet.begin(), gridRepresentationSet.end(), gridRep) != gridRepresentationSet.end();
}

void RockFluidOrganizationInterpretation::pushBackRockFluidUnitInterpretation(RockFluidUnitInterpretation * rockFluidUnitInterpretation)
{
	if (static_cast<_resqml20__RockFluidOrganizationInterpretation*>(gsoapProxy2_0_1)->RockFluidUnitIndex->RockFluidUnit != nullptr) {
		throw logic_error("Fesapi for now only supports one unit in a Rock fluid organization");
	}

	static_cast<_resqml20__RockFluidOrganizationInterpretation*>(gsoapProxy2_0_1)->RockFluidUnitIndex->RockFluidUnit = rockFluidUnitInterpretation->newResqmlReference();
}

// For now cannot really count cause of the bug http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-500-106-0-R-sv2010.html
unsigned int RockFluidOrganizationInterpretation::getRockFluidUnitInterpCount() const
{
	return static_cast<_resqml20__RockFluidOrganizationInterpretation*>(gsoapProxy2_0_1)->RockFluidUnitIndex->RockFluidUnit != nullptr ? 1 : 0;
}

RockFluidUnitInterpretation* RockFluidOrganizationInterpretation::getRockFluidUnitInterpretation(unsigned int index) const
{
	if (index >= getRockFluidUnitInterpCount()) {
		throw range_error("The index is out of range");
	}

	return repository->getDataObjectByUuid<RockFluidUnitInterpretation>(static_cast<_resqml20__RockFluidOrganizationInterpretation*>(gsoapProxy2_0_1)->RockFluidUnitIndex->RockFluidUnit->UUID);
}

void RockFluidOrganizationInterpretation::loadTargetRelationships()
{
	AbstractOrganizationInterpretation::loadTargetRelationships();

	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = static_cast<_resqml20__RockFluidOrganizationInterpretation*>(gsoapProxy2_0_1)->RockFluidUnitIndex->RockFluidUnit;
	if (dor != nullptr) {
		convertDorIntoRel<RockFluidUnitInterpretation>(dor);
	}
}
