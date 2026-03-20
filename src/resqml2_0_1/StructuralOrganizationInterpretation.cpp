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
#include "StructuralOrganizationInterpretation.h"

#include <limits>
#include <stdexcept>

#include "OrganizationFeature.h"
#include "../resqml2/FaultInterpretation.h"
#include "../resqml2/HorizonInterpretation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* StructuralOrganizationInterpretation::XML_NS = "resqml20";

StructuralOrganizationInterpretation::StructuralOrganizationInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title,
	gsoap_resqml2_0_1::resqml20__OrderingCriteria orderingCriteria)
{
	if (orgFeat == nullptr) {
		throw invalid_argument("The interpreted organization feature cannot be null.");
	}
	if (!orgFeat->isPartial() && dynamic_cast<RESQML2_0_1_NS::OrganizationFeature*>(orgFeat) != nullptr
		&& static_cast<RESQML2_0_1_NS::OrganizationFeature*>(orgFeat)->getKind() != gsoap_resqml2_0_1::resqml20__OrganizationKind::structural) {
		throw invalid_argument("The kind of the v2.0.1 organization feature is not a structural organization.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREStructuralOrganizationInterpretation(orgFeat->getGsoapContext());
	
	static_cast<_resqml20__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1)->OrderingCriteria = orderingCriteria;
	static_cast<_resqml20__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1)->Domain = resqml20__Domain::mixed;

    initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	orgFeat->getRepository()->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
	setInterpretedFeature(orgFeat);
}

void StructuralOrganizationInterpretation::pushBackFaultInterpretation(RESQML2_NS::FaultInterpretation * faultInterpretation)
{
	getRepository()->addRelationship(this, faultInterpretation);

    eml20__DataObjectReference* faultInterpRef = faultInterpretation->newResqmlReference();
    _resqml20__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml20__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);
	structuralOrganization->Faults.push_back(faultInterpRef);
}

uint64_t StructuralOrganizationInterpretation::getFaultInterpretationCount() const
{
	return static_cast<_resqml20__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1)->Faults.size();
}

COMMON_NS::DataObjectReference StructuralOrganizationInterpretation::getFaultInterpretationDor(uint64_t index) const
{
	_resqml20__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml20__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);

	return COMMON_NS::DataObjectReference(structuralOrganization->Faults.at(index));
}

void StructuralOrganizationInterpretation::pushBackHorizonInterpretation(RESQML2_NS::HorizonInterpretation * horizonInterpretation, uint64_t stratigraphicRank)
{
	getRepository()->addRelationship(this, horizonInterpretation);

	_resqml20__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml20__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);

	resqml20__HorizonInterpretationIndex* horizonInterpListElement = soap_new_resqml20__HorizonInterpretationIndex(gsoapProxy2_0_1->soap);
	horizonInterpListElement->StratigraphicRank = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
	*(horizonInterpListElement->StratigraphicRank) = stratigraphicRank;
	horizonInterpListElement->Index = structuralOrganization->Horizons.size();
    eml20__DataObjectReference* horizonInterpRef = horizonInterpretation->newResqmlReference();
    horizonInterpListElement->Horizon = horizonInterpRef;
	structuralOrganization->Horizons.push_back(horizonInterpListElement);
}

uint64_t StructuralOrganizationInterpretation::getHorizonInterpretationCount() const
{
	return static_cast<_resqml20__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1)->Horizons.size();
}

COMMON_NS::DataObjectReference StructuralOrganizationInterpretation::getHorizonInterpretationDor(uint64_t index) const
{
	_resqml20__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml20__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);

	return COMMON_NS::DataObjectReference(structuralOrganization->Horizons.at(index)->Horizon);
}

void StructuralOrganizationInterpretation::pushBackTopFrontierInterpretation(AbstractFeatureInterpretation * topFrontierInterpretation)
{
	getRepository()->addRelationship(this, topFrontierInterpretation);

    eml20__DataObjectReference* interpRef = topFrontierInterpretation->newResqmlReference();
    _resqml20__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml20__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);
	structuralOrganization->TopFrontier.push_back(interpRef);
}

uint64_t StructuralOrganizationInterpretation::getTopFrontierInterpretationCount() const
{
	return static_cast<_resqml20__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1)->TopFrontier.size();
}

COMMON_NS::DataObjectReference StructuralOrganizationInterpretation::getTopFrontierInterpretationDor(uint64_t index) const
{
	_resqml20__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml20__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);

	return COMMON_NS::DataObjectReference(structuralOrganization->TopFrontier.at(index));
}

void StructuralOrganizationInterpretation::pushBackBottomFrontierInterpretation(AbstractFeatureInterpretation * bottomFrontierInterpretation)
{
	getRepository()->addRelationship(this, bottomFrontierInterpretation);

    eml20__DataObjectReference* interpRef = bottomFrontierInterpretation->newResqmlReference();
    _resqml20__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml20__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);
	structuralOrganization->BottomFrontier.push_back(interpRef);
}

uint64_t StructuralOrganizationInterpretation::getBottomFrontierInterpretationCount() const
{
	return static_cast<_resqml20__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1)->BottomFrontier.size();
}

COMMON_NS::DataObjectReference StructuralOrganizationInterpretation::getBottomFrontierInterpretationDor(uint64_t index) const
{
	_resqml20__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml20__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);

	return COMMON_NS::DataObjectReference(structuralOrganization->BottomFrontier.at(index));
}

void StructuralOrganizationInterpretation::pushBackSideFrontierInterpretation(AbstractFeatureInterpretation * sideFrontierInterpretation)
{
	getRepository()->addRelationship(this, sideFrontierInterpretation);

    eml20__DataObjectReference* interpRef = sideFrontierInterpretation->newResqmlReference();
    _resqml20__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml20__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);
	structuralOrganization->Sides.push_back(interpRef);
}

uint64_t StructuralOrganizationInterpretation::getSideFrontierInterpretationCount() const
{
	return static_cast<_resqml20__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1)->Sides.size();
}

COMMON_NS::DataObjectReference StructuralOrganizationInterpretation::getSideFrontierInterpretationDor(uint64_t index) const
{
	_resqml20__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml20__StructuralOrganizationInterpretation*>(gsoapProxy2_0_1);

	return COMMON_NS::DataObjectReference(structuralOrganization->Sides.at(index));
}
