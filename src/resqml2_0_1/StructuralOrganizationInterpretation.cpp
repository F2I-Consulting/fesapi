/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"

#include <stdexcept>

#include "resqml2_0_1/OrganizationFeature.h"
#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2_0_1/HorizonInterpretation.h"
#include "resqml2_0_1/EarthModelInterpretation.h"

#include "tools/Misc.h"

using namespace std;
using namespace epc;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

const char* StructuralOrganizationInterpretation::XML_TAG = "StructuralOrganizationInterpretation";

StructuralOrganizationInterpretation::StructuralOrganizationInterpretation(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title,
		const gsoap_resqml2_0_1::resqml2__OrderingCriteria & orderingCriteria)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREStructuralOrganizationInterpretation(orgFeat->getGsoapContext(), 1);
	
	static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1)->OrderingCriteria = orderingCriteria;
	static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1)->Domain = resqml2__Domain__mixed;

    initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

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

FaultInterpretation* StructuralOrganizationInterpretation::getFaultInterpretation(const unsigned int & index)
{
	_resqml2__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);
	if (index < structuralOrganization->Faults.size()) {
		return static_cast<FaultInterpretation*>(epcDocument->getResqmlAbstractObjectByUuid(structuralOrganization->Faults[index]->UUID));
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
		
void StructuralOrganizationInterpretation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractOrganizationInterpretation::importRelationshipSetFromEpc(epcDoc);

	updateXml = false;

	_resqml2__StructuralOrganizationInterpretation* interp = static_cast<_resqml2__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);

	common::AbstractObject* obj = nullptr;
	for (size_t i = 0; i < interp->Faults.size(); ++i)
	{
		obj = epcDoc->getResqmlAbstractObjectByUuid(interp->Faults[i]->UUID);
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
			obj = epcDoc->getResqmlAbstractObjectByUuid(interp->Horizons[i]->Horizon->UUID);
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
		obj = epcDoc->getResqmlAbstractObjectByUuid(interp->TopFrontier[i]->UUID);
		if (dynamic_cast<AbstractFeatureInterpretation*>(obj) != nullptr) {
			pushBackTopFrontierInterpretation(static_cast<AbstractFeatureInterpretation*>(obj));
		}
		else {
			throw logic_error("The referenced top frontier does not look to be an interpretation.");
		}
	}
	for (size_t i = 0; i < interp->BottomFrontier.size(); ++i)
	{
		obj = epcDoc->getResqmlAbstractObjectByUuid(interp->BottomFrontier[i]->UUID);
		if (dynamic_cast<AbstractFeatureInterpretation*>(obj) != nullptr) {
			pushBackBottomFrontierInterpretation(static_cast<AbstractFeatureInterpretation*>(obj));
		}
		else {
			throw logic_error("The referenced bottom frontier does not look to be an interpretation.");
		}
	}
	for (size_t i = 0; i < interp->Sides.size(); ++i)
	{
		obj = epcDoc->getResqmlAbstractObjectByUuid(interp->Sides[i]->UUID);
		if (dynamic_cast<AbstractFeatureInterpretation*>(obj) != nullptr) {
			pushBackSideFrontierInterpretation(static_cast<AbstractFeatureInterpretation*>(obj));
		}
		else {
			throw logic_error("The referenced side frontier does not look to be an interpretation.");
		}
	}

	updateXml = true;
}
