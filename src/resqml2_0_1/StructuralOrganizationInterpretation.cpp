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
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"

#include <stdexcept>

#include "resqml2_0_1/OrganizationFeature.h"
#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2_0_1/HorizonInterpretation.h"
#include "resqml2_0_1/EarthModelInterpretation.h"
#include "resqml2/AbstractFeatureInterpretation.h"
#include "tools/Misc.h"

using namespace std;
using namespace epc;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* StructuralOrganizationInterpretation::XML_TAG = "StructuralOrganizationInterpretation";

StructuralOrganizationInterpretation::StructuralOrganizationInterpretation(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title,
		const gsoap_resqml2_0_1::resqml2__OrderingCriteria & orderingCriteria)
{
	if (orgFeat == nullptr) {
		throw invalid_argument("The interpreted organization feature cannot be null.");
	}
	if (!orgFeat->isPartial() && orgFeat->getKind() != gsoap_resqml2_0_1::resqml2__OrganizationKind__structural) {
		throw invalid_argument("The kind of the organization feature is not a structural organization.");
	}

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREStructuralOrganizationInterpretation(orgFeat->getGsoapContext(), 1);
	
	static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1)->OrderingCriteria = orderingCriteria;
	static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1)->Domain = resqml2__Domain__mixed;

    initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretedFeature(orgFeat);
}

void StructuralOrganizationInterpretation::pushBackFaultInterpretation(FaultInterpretation * faultInterpretation)
{
    // EPC
	faultInterpretation->structuralOrganizationInterpretationSet.push_back(this);

    // XML
	if (updateXml)
	{
        eml20__DataObjectReference* faultInterpRef = faultInterpretation->newResqmlReference();
        _resqml2__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);
		structuralOrganization->Faults.push_back(faultInterpRef);
	}
}

unsigned int StructuralOrganizationInterpretation::getFaultInterpretationCount() const
{
	return static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1)->Faults.size();
}

FaultInterpretation* StructuralOrganizationInterpretation::getFaultInterpretation(unsigned int index)
{
	_resqml2__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);
	if (index < structuralOrganization->Faults.size()) {
		return static_cast<FaultInterpretation*>(epcDocument->getDataObjectByUuid(structuralOrganization->Faults[index]->UUID));
	}
	else {
		throw std::out_of_range("The fault index is out of range.");
	}
}

void StructuralOrganizationInterpretation::pushBackHorizonInterpretation(HorizonInterpretation * horizonInterpretation, const int & stratigraphicRank)
{
	// EPC
	horizonInterpretation->structuralOrganizationInterpretationSet.push_back(this);

    // XML
	if (updateXml)
	{
		_resqml2__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);

		resqml2__HorizonInterpretationIndex* horizonInterpListElement = soap_new_resqml2__HorizonInterpretationIndex(gsoapProxy2_0_1->soap, 1);
		horizonInterpListElement->StratigraphicRank = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
		*(horizonInterpListElement->StratigraphicRank) = stratigraphicRank;
		horizonInterpListElement->Index = structuralOrganization->Horizons.size();
        eml20__DataObjectReference* horizonInterpRef = horizonInterpretation->newResqmlReference();
        horizonInterpListElement->Horizon = horizonInterpRef;
		structuralOrganization->Horizons.push_back(horizonInterpListElement);
	}
}

unsigned int StructuralOrganizationInterpretation::getHorizonInterpretationCount() const
{
	return static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1)->Horizons.size();
}

HorizonInterpretation* StructuralOrganizationInterpretation::getHorizonInterpretation(unsigned int index) const
{
	_resqml2__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);
	if (index < structuralOrganization->Horizons.size()) {
		return static_cast<HorizonInterpretation*>(epcDocument->getDataObjectByUuid(structuralOrganization->Horizons[index]->Horizon->UUID));
	}
	else {
		throw std::out_of_range("The fault index is out of range.");
	}
}

void StructuralOrganizationInterpretation::pushBackTopFrontierInterpretation(AbstractFeatureInterpretation * topFrontierInterpretation)
{
    // EPC
	topFrontierInterpretation->setTopFrontierOf(this);

    // XML
	if (updateXml)
	{
        eml20__DataObjectReference* interpRef = topFrontierInterpretation->newResqmlReference();
        _resqml2__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);
		structuralOrganization->TopFrontier.push_back(interpRef);
	}
}

unsigned int StructuralOrganizationInterpretation::getTopFrontierInterpretationCount() const
{
	return static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1)->TopFrontier.size();
}

RESQML2_NS::AbstractFeatureInterpretation* StructuralOrganizationInterpretation::getTopFrontierInterpretation(unsigned int index) const
{
	_resqml2__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);
	if (index < structuralOrganization->TopFrontier.size()) {
		return static_cast<RESQML2_NS::AbstractFeatureInterpretation*>(epcDocument->getDataObjectByUuid(structuralOrganization->TopFrontier[index]->UUID));
	}
	else {
		throw std::out_of_range("The top frontier index is out of range.");
	}
}

void StructuralOrganizationInterpretation::pushBackBottomFrontierInterpretation(AbstractFeatureInterpretation * bottomFrontierInterpretation)
{
    // EPC
	bottomFrontierInterpretation->setBottomFrontierOf(this);

    // XML
	if (updateXml)
	{
        eml20__DataObjectReference* interpRef = bottomFrontierInterpretation->newResqmlReference();
        _resqml2__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);
		structuralOrganization->BottomFrontier.push_back(interpRef);
	}
}

unsigned int StructuralOrganizationInterpretation::getBottomFrontierInterpretationCount() const
{
	return static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1)->BottomFrontier.size();
}

RESQML2_NS::AbstractFeatureInterpretation* StructuralOrganizationInterpretation::getBottomFrontierInterpretation(unsigned int index) const
{
	_resqml2__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);
	if (index < structuralOrganization->BottomFrontier.size()) {
		return static_cast<RESQML2_NS::AbstractFeatureInterpretation*>(epcDocument->getDataObjectByUuid(structuralOrganization->BottomFrontier[index]->UUID));
	}
	else {
		throw std::out_of_range("The bottom frontier index is out of range.");
	}
}

void StructuralOrganizationInterpretation::pushBackSideFrontierInterpretation(AbstractFeatureInterpretation * sideFrontierInterpretation)
{
    // EPC
	sideFrontierInterpretation->setSideFrontierOf(this);

    // XML
	if (updateXml)
	{
        eml20__DataObjectReference* interpRef = sideFrontierInterpretation->newResqmlReference();
        _resqml2__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);
		structuralOrganization->Sides.push_back(interpRef);
	}
}

unsigned int StructuralOrganizationInterpretation::getSideFrontierInterpretationCount() const
{
	return static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1)->Sides.size();
}

RESQML2_NS::AbstractFeatureInterpretation* StructuralOrganizationInterpretation::getSideFrontierInterpretation(unsigned int index) const
{
	_resqml2__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);
	if (index < structuralOrganization->Sides.size()) {
		return static_cast<RESQML2_NS::AbstractFeatureInterpretation*>(epcDocument->getDataObjectByUuid(structuralOrganization->Sides[index]->UUID));
	}
	else {
		throw std::out_of_range("The bottom frontier index is out of range.");
	}
}

vector<Relationship> StructuralOrganizationInterpretation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractOrganizationInterpretation::getAllEpcRelationships();

	_resqml2__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);
	for (size_t i = 0; i < structuralOrganization->Faults.size(); i++)
	{
		Relationship rel(misc::getPartNameFromReference(structuralOrganization->Faults[i]), "", structuralOrganization->Faults[i]->UUID);
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
        
	for (size_t i = 0; i < structuralOrganization->Horizons.size(); i++)
	{
		Relationship rel(misc::getPartNameFromReference(structuralOrganization->Horizons[i]->Horizon), "", structuralOrganization->Horizons[i]->Horizon->UUID);
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
        
	for (size_t i = 0; i < structuralOrganization->BottomFrontier.size(); i++)
	{
		Relationship rel(misc::getPartNameFromReference(structuralOrganization->BottomFrontier[i]), "", structuralOrganization->BottomFrontier[i]->UUID);
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
        
	for (size_t i = 0; i < structuralOrganization->TopFrontier.size(); i++)
	{
		Relationship rel(misc::getPartNameFromReference(structuralOrganization->TopFrontier[i]), "", structuralOrganization->TopFrontier[i]->UUID);
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
        
	for (size_t i = 0; i < structuralOrganization->Sides.size(); i++)
	{
		Relationship rel(misc::getPartNameFromReference(structuralOrganization->Sides[i]), "", structuralOrganization->Sides[i]->UUID);
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
        
	for (size_t i = 0; i < earthModelSet.size(); i++)
    {
        Relationship rel(earthModelSet[i]->getPartNameInEpcDocument(), "", earthModelSet[i]->getUuid());
		rel.setSourceObjectType();
        result.push_back(rel);
    }
    
	return result;
}
		
void StructuralOrganizationInterpretation::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	AbstractOrganizationInterpretation::importRelationshipSetFromEpc(epcDoc);

	updateXml = false;

	_resqml2__StructuralOrganizationInterpretation* interp = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);

	COMMON_NS::AbstractObject* obj = nullptr;
	for (size_t i = 0; i < interp->Faults.size(); ++i)
	{
		obj = epcDoc->getDataObjectByUuid(interp->Faults[i]->UUID);
		if (dynamic_cast<FaultInterpretation*>(obj) != nullptr) {
			pushBackFaultInterpretation(static_cast<FaultInterpretation*>(obj));
		}
		else {
			throw logic_error("The referenced fault interpretation does not look to be a fault interpretation.");
		}
	}
	for (size_t i = 0; i < interp->Horizons.size(); ++i)
	{
		if (interp->Horizons[i]->StratigraphicRank != nullptr) {
			obj = epcDoc->getDataObjectByUuid(interp->Horizons[i]->Horizon->UUID);
			if (dynamic_cast<HorizonInterpretation*>(obj) != nullptr) {
				pushBackHorizonInterpretation(static_cast<HorizonInterpretation*>(obj), *(interp->Horizons[i]->StratigraphicRank));
			}
			else {
				throw logic_error("The referenced horizon interpretation does not look to be a horizon interpretation.");
			}
		}
		else {
			throw logic_error("Not yet implemented");
		}
	}

	for (size_t i = 0; i < interp->TopFrontier.size(); ++i)
	{
		obj = epcDoc->getDataObjectByUuid(interp->TopFrontier[i]->UUID);
		if (dynamic_cast<AbstractFeatureInterpretation*>(obj) != nullptr) {
			pushBackTopFrontierInterpretation(static_cast<AbstractFeatureInterpretation*>(obj));
		}
		else {
			throw logic_error("The referenced top frontier does not look to be an interpretation.");
		}
	}
	for (size_t i = 0; i < interp->BottomFrontier.size(); ++i)
	{
		obj = epcDoc->getDataObjectByUuid(interp->BottomFrontier[i]->UUID);
		if (dynamic_cast<AbstractFeatureInterpretation*>(obj) != nullptr) {
			pushBackBottomFrontierInterpretation(static_cast<AbstractFeatureInterpretation*>(obj));
		}
		else {
			throw logic_error("The referenced bottom frontier does not look to be an interpretation.");
		}
	}
	for (size_t i = 0; i < interp->Sides.size(); ++i)
	{
		obj = epcDoc->getDataObjectByUuid(interp->Sides[i]->UUID);
		if (dynamic_cast<AbstractFeatureInterpretation*>(obj) != nullptr) {
			pushBackSideFrontierInterpretation(static_cast<AbstractFeatureInterpretation*>(obj));
		}
		else {
			throw logic_error("The referenced side frontier does not look to be an interpretation.");
		}
	}

	updateXml = true;
}

