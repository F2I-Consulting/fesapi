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

#include "../resqml2/Model.h"
#include "../resqml2/FaultInterpretation.h"
#include "../resqml2/HorizonInterpretation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* StructuralOrganizationInterpretation::XML_NS = "resqml22";

StructuralOrganizationInterpretation::StructuralOrganizationInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title,
	gsoap_resqml2_0_1::resqml20__OrderingCriteria orderingCriteria)
{
	if (orgFeat == nullptr) {
		throw invalid_argument("The interpreted organization feature cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__StructuralOrganizationInterpretation(orgFeat->getGsoapContext());
	
	static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3)->OrderingCriteria = static_cast<resqml22__OrderingCriteria>(orderingCriteria);

    initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	orgFeat->getRepository()->addDataObject(this);
	setInterpretedFeature(orgFeat);
}

void StructuralOrganizationInterpretation::pushBackFaultInterpretation(RESQML2_NS::FaultInterpretation * faultInterpretation)
{
	getRepository()->addRelationship(this, faultInterpretation);

	_resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);
	if (structuralOrganization->UnorderedFaultCollection == nullptr) {
		structuralOrganization->UnorderedFaultCollection = soap_new_resqml22__FeatureInterpretationSet(gsoapProxy2_3->soap);
		structuralOrganization->UnorderedFaultCollection->IsHomogeneous = true;
		structuralOrganization->UnorderedFaultCollection->Citation = soap_new_eml23__Citation(gsoapProxy2_3->soap);
		structuralOrganization->UnorderedFaultCollection->Citation->Title = getTitle() + " Fault collection";
		structuralOrganization->UnorderedFaultCollection->Citation->Originator = getOriginator();
		structuralOrganization->UnorderedFaultCollection->Citation->Creation = getCreationAsTimeStructure();
		structuralOrganization->UnorderedFaultCollection->Citation->Format = getFormat();
	}

	structuralOrganization->UnorderedFaultCollection->FeatureInterpretation.push_back(faultInterpretation->newEml23Reference());
}

unsigned int StructuralOrganizationInterpretation::getFaultInterpretationCount() const
{
	_resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);

	const size_t result = structuralOrganization->UnorderedFaultCollection == nullptr
		? 0
		: structuralOrganization->UnorderedFaultCollection->FeatureInterpretation.size();

	if (result > (numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too many associated fault interpretations.");
	}

	return static_cast<unsigned int>(result);
}

COMMON_NS::DataObjectReference StructuralOrganizationInterpretation::getFaultInterpretationDor(unsigned int index) const
{
	_resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);
	if (index >= getFaultInterpretationCount()) {
		throw std::out_of_range("The fault index is out of range.");
	}

	return COMMON_NS::DataObjectReference(structuralOrganization->UnorderedFaultCollection->FeatureInterpretation[index]);
}

void StructuralOrganizationInterpretation::pushBackHorizonInterpretation(RESQML2_NS::HorizonInterpretation * horizonInterpretation, int stratigraphicRank)
{
	getRepository()->addRelationship(this, horizonInterpretation);

	_resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);

	resqml22__BoundaryFeatureInterpretationPlusItsRank* horizonInterpPlusItsRank = soap_new_resqml22__BoundaryFeatureInterpretationPlusItsRank(gsoapProxy2_3->soap);
	horizonInterpPlusItsRank->StratigraphicRank = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_3->soap, sizeof(ULONG64)));
	*(horizonInterpPlusItsRank->StratigraphicRank) = stratigraphicRank;
	horizonInterpPlusItsRank->BoundaryFeatureInterpretation = horizonInterpretation->newEml23Reference();
	structuralOrganization->OrderedBoundaryFeatureInterpretation.push_back(horizonInterpPlusItsRank);
}

unsigned int StructuralOrganizationInterpretation::getHorizonInterpretationCount() const
{
	size_t result = 0;
	for (auto const* boundary : static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3)->OrderedBoundaryFeatureInterpretation) {
		if (boundary->BoundaryFeatureInterpretation != nullptr) {
			++result;
		}
	}

	if (result > (numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too many associated horizon interpretations.");
	}

	return static_cast<unsigned int>(result);
}

COMMON_NS::DataObjectReference StructuralOrganizationInterpretation::getHorizonInterpretationDor(unsigned int index) const
{
	_resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);
	if (index >= structuralOrganization->OrderedBoundaryFeatureInterpretation.size()) {
		throw std::out_of_range("The horizon index is out of range.");
	}

	size_t tmpIndex = 0;
	while (tmpIndex < index) {
		if (structuralOrganization->OrderedBoundaryFeatureInterpretation[tmpIndex]->BoundaryFeatureInterpretation != nullptr) {
			++tmpIndex;
		}
	}

	return COMMON_NS::DataObjectReference(structuralOrganization->OrderedBoundaryFeatureInterpretation[tmpIndex]->BoundaryFeatureInterpretation);
}

void StructuralOrganizationInterpretation::pushBackTopFrontierInterpretation(AbstractFeatureInterpretation * topFrontierInterpretation)
{
	getRepository()->addRelationship(this, topFrontierInterpretation);

    _resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);
	structuralOrganization->TopFrontier.push_back(topFrontierInterpretation->newEml23Reference());
}

unsigned int StructuralOrganizationInterpretation::getTopFrontierInterpretationCount() const
{
	const size_t result = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3)->TopFrontier.size();

	if (result > (numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too many associated top frontier interpretations.");
	}

	return static_cast<unsigned int>(result);
}

COMMON_NS::DataObjectReference StructuralOrganizationInterpretation::getTopFrontierInterpretationDor(unsigned int index) const
{
	_resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);
	if (index >= structuralOrganization->TopFrontier.size()) {
		throw std::out_of_range("The top frontier index is out of range.");
	}

	return COMMON_NS::DataObjectReference(structuralOrganization->TopFrontier[index]);
}

void StructuralOrganizationInterpretation::pushBackBottomFrontierInterpretation(AbstractFeatureInterpretation * bottomFrontierInterpretation)
{
	getRepository()->addRelationship(this, bottomFrontierInterpretation);

    _resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);
	structuralOrganization->BottomFrontier.push_back(bottomFrontierInterpretation->newEml23Reference());
}

unsigned int StructuralOrganizationInterpretation::getBottomFrontierInterpretationCount() const
{
	const size_t result = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3)->BottomFrontier.size();

	if (result > (numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too many associated bottom frontier interpretations.");
	}

	return static_cast<unsigned int>(result);
}

COMMON_NS::DataObjectReference StructuralOrganizationInterpretation::getBottomFrontierInterpretationDor(unsigned int index) const
{
	_resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);
	if (index >= structuralOrganization->BottomFrontier.size()) {
		throw std::out_of_range("The bottom frontier index is out of range.");
	}

	return COMMON_NS::DataObjectReference(structuralOrganization->BottomFrontier[index]);
}

void StructuralOrganizationInterpretation::pushBackSideFrontierInterpretation(AbstractFeatureInterpretation * sideFrontierInterpretation)
{
	getRepository()->addRelationship(this, sideFrontierInterpretation);

    _resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);
	structuralOrganization->Sides.push_back(sideFrontierInterpretation->newEml23Reference());
}

unsigned int StructuralOrganizationInterpretation::getSideFrontierInterpretationCount() const
{
	const size_t result = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3)->Sides.size();

	if (result > (numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too many associated side frontier interpretations.");
	}

	return static_cast<unsigned int>(result);
}

COMMON_NS::DataObjectReference StructuralOrganizationInterpretation::getSideFrontierInterpretationDor(unsigned int index) const
{
	_resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);
	if (index >= structuralOrganization->Sides.size()) {
		throw std::out_of_range("The side frontier index is out of range.");
	}

	return COMMON_NS::DataObjectReference(structuralOrganization->Sides[index]);
}
