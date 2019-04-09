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
#include "resqml2_0_1/RockFluidOrganizationInterpretation.h"
#include "resqml2_0_1/RockFluidUnitInterpretation.h"
#include <algorithm>

#include "tools/Misc.h"

using namespace std;
using namespace epc;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* RockFluidOrganizationInterpretation::XML_TAG = "RockFluidOrganizationInterpretation";

RockFluidOrganizationInterpretation::RockFluidOrganizationInterpretation(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, RockFluidUnitInterpretation * rockFluidUnitInterp)
{
	if (orgFeat == nullptr) {
		throw invalid_argument("The interpreted organization feature cannot be null.");
	}
	if (!orgFeat->isPartial() && orgFeat->getKind() != gsoap_resqml2_0_1::resqml2__OrganizationKind__fluid) {
		throw invalid_argument("The kind of the organization feature is not a fluid organization.");
	}

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORERockFluidOrganizationInterpretation(orgFeat->getGsoapContext(), 1);
	_resqml2__RockFluidOrganizationInterpretation* rfoi = static_cast<_resqml2__RockFluidOrganizationInterpretation*>(gsoapProxy2_0_1);
	rfoi->RockFluidUnitIndex = soap_new_resqml2__RockFluidUnitInterpretationIndex(orgFeat->getGsoapContext(), 1);
	// No need to initialize index since it is a bug : http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-500-106-0-R-sv2010.html
	pushBackRockFluidUnitInterpretation(rockFluidUnitInterp);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretedFeature(orgFeat);
}

unsigned int RockFluidOrganizationInterpretation::getGridRepresentationCount() const
{
	const size_t count = gridRepresentationSet.size();
	if (count > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("Too much grid representations.");
	}

	return static_cast<unsigned int>(count);
}

RESQML2_NS::AbstractGridRepresentation* RockFluidOrganizationInterpretation::getGridRepresentation(unsigned int index) const
{
	if (index >= getGridRepresentationCount()) {
		throw range_error("The index of the grid representation to get is out of range.");
	}

	return gridRepresentationSet[index];
}

bool RockFluidOrganizationInterpretation::isAssociatedToGridRepresentation(RESQML2_NS::AbstractGridRepresentation* gridRep) const
{
	return find(gridRepresentationSet.begin(), gridRepresentationSet.end(), gridRep) != gridRepresentationSet.end();
}

void RockFluidOrganizationInterpretation::pushBackRockFluidUnitInterpretation(RockFluidUnitInterpretation * rockFluidUnitInterpretation)
{
	if (updateXml && static_cast<_resqml2__RockFluidOrganizationInterpretation*>(gsoapProxy2_0_1)->RockFluidUnitIndex->RockFluidUnit != nullptr) {
		throw logic_error("Fesapi for now only supports one unit in a Rock fluid organization");
	}

	// EPC
	rockFluidUnitInterpretation->rockFluidOrganizationInterpSet.push_back(this);

	// XML
	// For now cannot really push back but only set cause of the bug http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-500-106-0-R-sv2010.html
	if (updateXml)
	{
		static_cast<_resqml2__RockFluidOrganizationInterpretation*>(gsoapProxy2_0_1)->RockFluidUnitIndex->RockFluidUnit = rockFluidUnitInterpretation->newResqmlReference();
	}
}

// For now cannot really count cause of the bug http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-500-106-0-R-sv2010.html
unsigned int RockFluidOrganizationInterpretation::getRockFluidUnitInterpCount() const
{
	return static_cast<_resqml2__RockFluidOrganizationInterpretation*>(gsoapProxy2_0_1)->RockFluidUnitIndex->RockFluidUnit != nullptr ? 1 : 0;
}

RockFluidUnitInterpretation* RockFluidOrganizationInterpretation::getRockFluidUnitInterpretation(unsigned int index) const
{
	if (index >= getRockFluidUnitInterpCount()) {
		throw range_error("The index is out of range");
	}

	return epcDocument->getDataObjectByUuid<RockFluidUnitInterpretation>(static_cast<_resqml2__RockFluidOrganizationInterpretation*>(gsoapProxy2_0_1)->RockFluidUnitIndex->RockFluidUnit->UUID);
}

std::vector<epc::Relationship> RockFluidOrganizationInterpretation::getAllSourceRelationships() const
{
	vector<Relationship> result = AbstractOrganizationInterpretation::getAllSourceRelationships();

	for (size_t i = 0; i < gridRepresentationSet.size(); ++i) {
		Relationship rel(gridRepresentationSet[i]->getPartNameInEpcDocument(), "", gridRepresentationSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	for (size_t i = 0; i < earthModelSet.size(); ++i)
	{
		Relationship rel(earthModelSet[i]->getPartNameInEpcDocument(), "", earthModelSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

std::vector<epc::Relationship> RockFluidOrganizationInterpretation::getAllTargetRelationships() const
{
	vector<Relationship> result = AbstractOrganizationInterpretation::getAllTargetRelationships();

	// Only one unit for now : http://docs.energistics.org/#RESQML/RESQML_TOPICS/RESQML-500-106-0-R-sv2010.html
	gsoap_resqml2_0_1::eml20__DataObjectReference * dor = static_cast<_resqml2__RockFluidOrganizationInterpretation*>(gsoapProxy2_0_1)->RockFluidUnitIndex->RockFluidUnit;
	Relationship relUnit(misc::getPartNameFromReference(dor), "", dor->UUID);
	relUnit.setDestinationObjectType();
	result.push_back(relUnit);

	return result;
}

void RockFluidOrganizationInterpretation::resolveTargetRelationships(COMMON_NS::EpcDocument * epcDoc)
{
	AbstractOrganizationInterpretation::resolveTargetRelationships(epcDoc);

	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = static_cast<_resqml2__RockFluidOrganizationInterpretation*>(gsoapProxy2_0_1)->RockFluidUnitIndex->RockFluidUnit;
	if (dor != nullptr) {
		RockFluidUnitInterpretation* interp = epcDoc->getDataObjectByUuid<RockFluidUnitInterpretation>(dor->UUID);
		if (interp == nullptr) { // partial transfer
			getEpcDocument()->createPartial(dor);
			interp = getEpcDocument()->getDataObjectByUuid<RockFluidUnitInterpretation>(dor->UUID);
		}
		if (interp == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		updateXml = false;
		pushBackRockFluidUnitInterpretation(interp);
		updateXml = true;
	}
}
