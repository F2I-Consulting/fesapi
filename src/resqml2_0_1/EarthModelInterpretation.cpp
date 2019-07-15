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
#include "resqml2_0_1/EarthModelInterpretation.h"

#include <stdexcept>

#include "resqml2_0_1/OrganizationFeature.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"
#include "resqml2_0_1/StratigraphicColumn.h"
#include "resqml2_0_1/StratigraphicOccurrenceInterpretation.h"
#include "resqml2_0_1/RockFluidOrganizationInterpretation.h"
#include "tools/Misc.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* EarthModelInterpretation::XML_TAG = "EarthModelInterpretation";

EarthModelInterpretation::EarthModelInterpretation(OrganizationFeature * orgFeat, const std::string & guid, const string & title)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREEarthModelInterpretation(orgFeat->getGsoapContext(), 1);
	_resqml2__EarthModelInterpretation* interp = static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1);

	interp->Domain = resqml2__Domain__mixed;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretedFeature(orgFeat);
}

bool EarthModelInterpretation::hasStructuralOrganizationInterpretation() const
{
	return static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->Structure != nullptr;
}

StructuralOrganizationInterpretation* EarthModelInterpretation::getStructuralOrganizationInterpertation() const
{
	if (!hasStructuralOrganizationInterpretation()) {
		throw invalid_argument("There is no associated structural organization");
	}

	return repository->getDataObjectByUuid<StructuralOrganizationInterpretation>(static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->Structure->UUID);
}

void EarthModelInterpretation::setStructuralOrganizationInterpretation(StructuralOrganizationInterpretation * structOrganization)
{
	getRepository()->addRelationship(this, structOrganization);
        
	static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->Structure = structOrganization->newResqmlReference();
}

bool EarthModelInterpretation::hasStratiColumn() const
{
	return static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicColumn != nullptr;
}

void EarthModelInterpretation::setStratiColumn(StratigraphicColumn * stratiColumn)
{
	getRepository()->addRelationship(this, stratiColumn);

	static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicColumn = stratiColumn->newResqmlReference();
}

StratigraphicColumn* EarthModelInterpretation::getStratiColumn() const
{
	if (!hasStratiColumn()) {
		throw invalid_argument("There is no associated stratigraphic column");
	}

	return repository->getDataObjectByUuid<StratigraphicColumn>(static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicColumn->UUID);
}

unsigned int EarthModelInterpretation::getStratiOccurenceCount() const
{
	return static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicOccurrences.size();
}

StratigraphicOccurrenceInterpretation* EarthModelInterpretation::getStratiOccurence(unsigned int index) const
{
	_resqml2__EarthModelInterpretation* earthModelInterpretation = static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1);
	if (index < earthModelInterpretation->StratigraphicOccurrences.size()) {
		return static_cast<StratigraphicOccurrenceInterpretation*>(repository->getDataObjectByUuid(earthModelInterpretation->StratigraphicOccurrences[index]->UUID));
	}
	else {
		throw std::out_of_range("The strati occurence index is out of range.");
	}
}

void EarthModelInterpretation::pushBackStratiOccurence(StratigraphicOccurrenceInterpretation * stratiOccurence)
{
	getRepository()->addRelationship(this, stratiOccurence);
		
	static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicOccurrences.push_back(stratiOccurence->newResqmlReference());
}

bool EarthModelInterpretation::hasRockFluidOrganizationInterpretation() const
{
	return static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->Fluid != nullptr;
}

void EarthModelInterpretation::setRockFluidOrganizationInterpretation(class RockFluidOrganizationInterpretation* rockFluid)
{
	getRepository()->addRelationship(this, rockFluid);

	static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->Fluid = rockFluid->newResqmlReference();
}

RockFluidOrganizationInterpretation* EarthModelInterpretation::getRockFluidOrganizationInterpretation() const
{
	if (!hasRockFluidOrganizationInterpretation()) {
		throw invalid_argument("There is no rock fluid organization");
	}

	return repository->getDataObjectByUuid<RockFluidOrganizationInterpretation>(static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->Fluid->UUID);
}
		
void EarthModelInterpretation::loadTargetRelationships() const
{
	AbstractFeatureInterpretation::loadTargetRelationships();

	_resqml2__EarthModelInterpretation* interp = static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1);

	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = interp->Structure;
	if (dor != nullptr) {
		convertDorIntoRel<StructuralOrganizationInterpretation>(dor);
	}

	dor = interp->StratigraphicColumn;
	if (dor != nullptr) {
		convertDorIntoRel<StratigraphicColumn>(dor);
	}

	for (size_t i = 0; i < interp->StratigraphicOccurrences.size(); ++i)
	{
		dor = interp->StratigraphicOccurrences[i];
		if (dor != nullptr) {
			convertDorIntoRel<StratigraphicOccurrenceInterpretation>(dor);
		}
	}

	dor = interp->Fluid;
	if (dor != nullptr) {
		convertDorIntoRel<RockFluidOrganizationInterpretation>(dor);
	}
}
