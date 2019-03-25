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
using namespace epc;

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

	return epcDocument->getDataObjectByUuid<StructuralOrganizationInterpretation>(static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->Structure->UUID);
}

void EarthModelInterpretation::setStructuralOrganizationInterpretation(StructuralOrganizationInterpretation * structOrganization)
{
    // epc
	structOrganization->earthModelSet.push_back(this);
        
    // XML
	if (updateXml) {
		static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->Structure = structOrganization->newResqmlReference();
	}
}

bool EarthModelInterpretation::hasStratiColumn() const
{
	return static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicColumn != nullptr;
}

void EarthModelInterpretation::setStratiColumn(StratigraphicColumn * stratiColumn)
{
    // epc
    stratiColumn->earthModel = this;
        
    // XML
	if (updateXml) {
		static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicColumn = stratiColumn->newResqmlReference();
	}
}

StratigraphicColumn* EarthModelInterpretation::getStratiColumn() const
{
	if (!hasStratiColumn()) {
		throw invalid_argument("There is no associated stratigraphic column");
	}

	return epcDocument->getDataObjectByUuid<StratigraphicColumn>(static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicColumn->UUID);
}

unsigned int EarthModelInterpretation::getStratiOccurenceCount() const
{
	return static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicOccurrences.size();
}

StratigraphicOccurrenceInterpretation* EarthModelInterpretation::getStratiOccurence(unsigned int index) const
{
	_resqml2__EarthModelInterpretation* earthModelInterpretation = static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1);
	if (index < earthModelInterpretation->StratigraphicOccurrences.size()) {
		return static_cast<StratigraphicOccurrenceInterpretation*>(epcDocument->getDataObjectByUuid(earthModelInterpretation->StratigraphicOccurrences[index]->UUID));
	}
	else {
		throw std::out_of_range("The strati occurence index is out of range.");
	}
}

void EarthModelInterpretation::pushBackStratiOccurence(StratigraphicOccurrenceInterpretation * stratiOccurence)
{
    // epc
    stratiOccurence->earthModelSet.push_back(this);
        
    // XML
	if (updateXml) {
		static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicOccurrences.push_back(stratiOccurence->newResqmlReference());
	}
}

bool EarthModelInterpretation::hasRockFluidOrganizationInterpretation() const
{
	return static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->Fluid != nullptr;
}

void EarthModelInterpretation::setRockFluidOrganizationInterpretation(class RockFluidOrganizationInterpretation* rockFluid)
{
	// epc
	rockFluid->earthModelSet.push_back(this);

	//XML
	if(updateXml) {
		static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->Fluid = rockFluid->newResqmlReference();
	}
}

RockFluidOrganizationInterpretation* EarthModelInterpretation::getRockFluidOrganizationInterpretation() const
{
	if (!hasRockFluidOrganizationInterpretation()) {
		throw invalid_argument("There is no rock fluid organization");
	}

	return epcDocument->getDataObjectByUuid<RockFluidOrganizationInterpretation>(static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->Fluid->UUID);
}

vector<Relationship> EarthModelInterpretation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractFeatureInterpretation::getAllEpcRelationships();

	_resqml2__EarthModelInterpretation* interp = static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1);

    if (interp->Structure != nullptr)
    {
        Relationship rel(misc::getPartNameFromReference(interp->Structure), "", interp->Structure->UUID);
		rel.setDestinationObjectType();
		result.push_back(rel);
    }

    if (interp->StratigraphicColumn != nullptr)
    {
        Relationship rel(misc::getPartNameFromReference(interp->StratigraphicColumn), "", interp->StratigraphicColumn->UUID);
		rel.setDestinationObjectType();
		result.push_back(rel);
    }

	for (size_t i = 0; i < interp->StratigraphicOccurrences.size(); ++i)
    {
		if (interp->StratigraphicOccurrences[i] != nullptr)
		{
			Relationship rel(misc::getPartNameFromReference(interp->StratigraphicOccurrences[i]), "", interp->StratigraphicOccurrences[i]->UUID);
			rel.setDestinationObjectType();
			result.push_back(rel);
		}
		else
			throw domain_error("The stratigraphic occurence associated to the earth model cannot be nullptr.");
    }

	if (hasRockFluidOrganizationInterpretation())
	{
		Relationship rel(misc::getPartNameFromReference(interp->Fluid), "", interp->Fluid->UUID);
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
        
    return result;
}
		
void EarthModelInterpretation::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	AbstractFeatureInterpretation::importRelationshipSetFromEpc(epcDoc);

	_resqml2__EarthModelInterpretation* interp = static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1);

	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = interp->Structure;
	if (dor != nullptr) {
		StructuralOrganizationInterpretation* interp = epcDoc->getDataObjectByUuid<StructuralOrganizationInterpretation>(dor->UUID);
		if (interp == nullptr) { // partial transfer
			getEpcDocument()->createPartial(dor);
			interp = getEpcDocument()->getDataObjectByUuid<StructuralOrganizationInterpretation>(dor->UUID);
		}
		if (interp == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		updateXml = false;
		setStructuralOrganizationInterpretation(interp);
		updateXml = true;
	}

	dor = interp->StratigraphicColumn;
	if (dor != nullptr) {
		StratigraphicColumn* interp = epcDoc->getDataObjectByUuid<StratigraphicColumn>(dor->UUID);
		if (interp == nullptr) { // partial transfer
			getEpcDocument()->createPartial(dor);
			interp = getEpcDocument()->getDataObjectByUuid<StratigraphicColumn>(dor->UUID);
		}
		if (interp == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		updateXml = false;
		setStratiColumn(interp);
		updateXml = true;
	}

	for (size_t i = 0; i < interp->StratigraphicOccurrences.size(); ++i)
	{
		dor = interp->StratigraphicOccurrences[i];
		if (dor != nullptr) {
			StratigraphicOccurrenceInterpretation* interp = epcDoc->getDataObjectByUuid<StratigraphicOccurrenceInterpretation>(dor->UUID);
			if (interp == nullptr) { // partial transfer
				getEpcDocument()->createPartial(dor);
				interp = getEpcDocument()->getDataObjectByUuid<StratigraphicOccurrenceInterpretation>(dor->UUID);
			}
			if (interp == nullptr) {
				throw invalid_argument("The DOR looks invalid.");
			}
			updateXml = false;
			pushBackStratiOccurence(interp);
			updateXml = true;
		}
	}

	dor = interp->Fluid;
	if (dor != nullptr) {
		RockFluidOrganizationInterpretation* interp = epcDoc->getDataObjectByUuid<RockFluidOrganizationInterpretation>(dor->UUID);
		if (interp == nullptr) { // partial transfer
			getEpcDocument()->createPartial(dor);
			interp = getEpcDocument()->getDataObjectByUuid<RockFluidOrganizationInterpretation>(dor->UUID);
		}
		if (interp == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		updateXml = false;
		setRockFluidOrganizationInterpretation(interp);
		updateXml = true;
	}
}
