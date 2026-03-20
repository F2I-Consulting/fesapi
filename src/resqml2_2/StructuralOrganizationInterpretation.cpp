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
	
	static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3)->AscendingOrderingCriteria = static_cast<resqml22__OrderingCriteria>(orderingCriteria);

    initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	orgFeat->getRepository()->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
	setInterpretedFeature(orgFeat);
}

void StructuralOrganizationInterpretation::pushBackFaultInterpretation(RESQML2_NS::FaultInterpretation * faultInterpretation)
{
	getRepository()->addRelationship(this, faultInterpretation);

	_resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);

	resqml22__BoundaryFeatureInterpretationPlusItsRank* tmp = soap_new_resqml22__BoundaryFeatureInterpretationPlusItsRank(gsoapProxy2_3->soap);
	tmp->BoundaryFeatureInterpretation = faultInterpretation->newEml23Reference();
	structuralOrganization->OrderedBoundaryFeatureInterpretation.push_back(tmp);
}

uint64_t StructuralOrganizationInterpretation::getFaultInterpretationCount() const
{
	_resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);

	uint64_t result = 0;
	for (auto const* boundary : structuralOrganization->OrderedBoundaryFeatureInterpretation) {
		if (boundary->BoundaryFeatureInterpretation != nullptr && boundary->BoundaryFeatureInterpretation->QualifiedType.find("FaultInterpretation") != std::string::npos) {
			++result;
		}
	}

	return result;
}

COMMON_NS::DataObjectReference StructuralOrganizationInterpretation::getFaultInterpretationDor(uint64_t index) const
{
	_resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);
	uint64_t currentIndex = 0;
	for (auto const* boundary : structuralOrganization->OrderedBoundaryFeatureInterpretation) {
		if (boundary->BoundaryFeatureInterpretation != nullptr && boundary->BoundaryFeatureInterpretation->QualifiedType.find("FaultInterpretation") != std::string::npos) {
			if (currentIndex == index) {
				return COMMON_NS::DataObjectReference(boundary->BoundaryFeatureInterpretation);
			}
			else {
				++currentIndex;
			}
		}
	}

	return COMMON_NS::DataObjectReference();
}

void StructuralOrganizationInterpretation::pushBackHorizonInterpretation(RESQML2_NS::HorizonInterpretation * horizonInterpretation, uint64_t stratigraphicRank)
{
	getRepository()->addRelationship(this, horizonInterpretation);

	_resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);

	resqml22__BoundaryFeatureInterpretationPlusItsRank* horizonInterpPlusItsRank = soap_new_resqml22__BoundaryFeatureInterpretationPlusItsRank(gsoapProxy2_3->soap);
	horizonInterpPlusItsRank->StratigraphicRank = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_3->soap, sizeof(ULONG64)));
	*(horizonInterpPlusItsRank->StratigraphicRank) = stratigraphicRank;
	horizonInterpPlusItsRank->BoundaryFeatureInterpretation = horizonInterpretation->newEml23Reference();
	structuralOrganization->OrderedBoundaryFeatureInterpretation.push_back(horizonInterpPlusItsRank);
}

uint64_t StructuralOrganizationInterpretation::getHorizonInterpretationCount() const
{
	_resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);

	uint64_t result = 0;
	for (auto const* boundary : structuralOrganization->OrderedBoundaryFeatureInterpretation) {
		if (boundary->BoundaryFeatureInterpretation != nullptr && boundary->BoundaryFeatureInterpretation->QualifiedType.find("HorizonInterpretation") != std::string::npos) {
			++result;
		}
	}

	return result;
}

COMMON_NS::DataObjectReference StructuralOrganizationInterpretation::getHorizonInterpretationDor(uint64_t index) const
{
	_resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);
	uint64_t currentIndex = 0;
	for (auto const* boundary : structuralOrganization->OrderedBoundaryFeatureInterpretation) {
		if (boundary->BoundaryFeatureInterpretation != nullptr && boundary->BoundaryFeatureInterpretation->QualifiedType.find("HorizonInterpretation") != std::string::npos) {
			if (currentIndex == index) {
				return COMMON_NS::DataObjectReference(boundary->BoundaryFeatureInterpretation);
			}
			else {
				++currentIndex;
			}
		}
	}

	return COMMON_NS::DataObjectReference();
}

void StructuralOrganizationInterpretation::pushBackTopFrontierInterpretation(AbstractFeatureInterpretation * topFrontierInterpretation)
{
	getRepository()->addRelationship(this, topFrontierInterpretation);

    _resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);
	structuralOrganization->TopFrontier.push_back(topFrontierInterpretation->newEml23Reference());
}

uint64_t StructuralOrganizationInterpretation::getTopFrontierInterpretationCount() const
{
	return static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3)->TopFrontier.size();
}

COMMON_NS::DataObjectReference StructuralOrganizationInterpretation::getTopFrontierInterpretationDor(uint64_t index) const
{
	_resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);

	return COMMON_NS::DataObjectReference(structuralOrganization->TopFrontier.at(index));
}

void StructuralOrganizationInterpretation::pushBackBottomFrontierInterpretation(AbstractFeatureInterpretation * bottomFrontierInterpretation)
{
	getRepository()->addRelationship(this, bottomFrontierInterpretation);

    _resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);
	structuralOrganization->BottomFrontier.push_back(bottomFrontierInterpretation->newEml23Reference());
}

uint64_t StructuralOrganizationInterpretation::getBottomFrontierInterpretationCount() const
{
	return static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3)->BottomFrontier.size();
}

COMMON_NS::DataObjectReference StructuralOrganizationInterpretation::getBottomFrontierInterpretationDor(uint64_t index) const
{
	_resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);
	return COMMON_NS::DataObjectReference(structuralOrganization->BottomFrontier.at(index));
}

void StructuralOrganizationInterpretation::pushBackSideFrontierInterpretation(AbstractFeatureInterpretation * sideFrontierInterpretation)
{
	getRepository()->addRelationship(this, sideFrontierInterpretation);

    _resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);
	structuralOrganization->Sides.push_back(sideFrontierInterpretation->newEml23Reference());
}

uint64_t StructuralOrganizationInterpretation::getSideFrontierInterpretationCount() const
{
	return static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3)->Sides.size();
}

COMMON_NS::DataObjectReference StructuralOrganizationInterpretation::getSideFrontierInterpretationDor(uint64_t index) const
{
	_resqml22__StructuralOrganizationInterpretation* structuralOrganization = static_cast<_resqml22__StructuralOrganizationInterpretation*>(gsoapProxy2_3);

	return COMMON_NS::DataObjectReference(structuralOrganization->Sides.at(index));
}
