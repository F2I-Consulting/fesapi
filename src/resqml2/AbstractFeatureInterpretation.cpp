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

#include "resqml2/AbstractFeatureInterpretation.h"

#include <stdexcept>

#include "resqml2/AbstractFeature.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "resqml2/GridConnectionSetRepresentation.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"

using namespace RESQML2_NS;
using namespace std;
using namespace epc;


void AbstractFeatureInterpretation::setInterpretedFeatureInXml(RESQML2_NS::AbstractFeature* feature)
{
	if (gsoapProxy2_0_1 != nullptr) {
		static_cast<gsoap_resqml2_0_1::resqml2__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->InterpretedFeature = feature->newResqmlReference();
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractFeatureInterpretation::setInterpretedFeature(RESQML2_NS::AbstractFeature * feature)
{
	if (feature == nullptr)
		throw invalid_argument("The interpreted feature cannot be null.");

	// EPC
	feature->interpretationSet.push_back(this);

	// XMl
	if (updateXml)
	{
		setInterpretedFeatureInXml(feature);
	}
}

void AbstractFeatureInterpretation::resolveTargetRelationships(COMMON_NS::EpcDocument* epcDoc)
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getInterpretedFeatureDor();
	RESQML2_NS::AbstractFeature* interpretedFeature = epcDoc->getDataObjectByUuid<AbstractFeature>(dor->UUID);
	if (interpretedFeature == nullptr) { // partial transfer
		getEpcDocument()->createPartial(dor);
		interpretedFeature = getEpcDocument()->getDataObjectByUuid<AbstractFeature>(dor->UUID);
	}
	if (interpretedFeature == nullptr) {
		throw invalid_argument("The DOR looks invalid.");
	}
	updateXml = false;
	setInterpretedFeature(interpretedFeature);
	updateXml = true;
}

vector<Relationship> AbstractFeatureInterpretation::getAllTargetRelationships() const
{
	vector<Relationship> result;

	RESQML2_NS::AbstractFeature* interpretedFeature = getInterpretedFeature();
	Relationship rel(interpretedFeature->getPartNameInEpcDocument(), "", interpretedFeature->getUuid());
	rel.setDestinationObjectType();
	result.push_back(rel);

	return result;
}
	
vector<Relationship> AbstractFeatureInterpretation::getAllSourceRelationships() const
{
	vector<Relationship> result;

	for (size_t i = 0; i < representationSet.size(); ++i)
	{
		if (representationSet[i] != nullptr)
		{
			Relationship relRep(representationSet[i]->getPartNameInEpcDocument(), "", representationSet[i]->getUuid());
			relRep.setSourceObjectType();
			result.push_back(relRep);
		}
		else
			throw domain_error("The representation associated to the interpretation cannot be nullptr.");
	}

	for (size_t i = 0; i < gridConnectionSetRepresentationSet.size(); i++)
	{
		if (gridConnectionSetRepresentationSet[i] != nullptr)
		{
			Relationship relGsr(gridConnectionSetRepresentationSet[i]->getPartNameInEpcDocument(), "", gridConnectionSetRepresentationSet[i]->getUuid());
			relGsr.setSourceObjectType();
			result.push_back(relGsr);
		}
		else
			throw domain_error("The representation associated to the interpretation cannot be nullptr.");
	}

	for (size_t i = 0; i < isTopFrontierSet.size(); i++)
	{
		Relationship relOrgStack(isTopFrontierSet[i]->getPartNameInEpcDocument(), "", isTopFrontierSet[i]->getUuid());
		relOrgStack.setSourceObjectType();
		result.push_back(relOrgStack);
	}

	for (size_t i = 0; i < isBottomFrontierSet.size(); i++)
	{
		Relationship relOrgStack(isBottomFrontierSet[i]->getPartNameInEpcDocument(), "", isBottomFrontierSet[i]->getUuid());
		relOrgStack.setSourceObjectType();
		result.push_back(relOrgStack);
	}

	for (size_t i = 0; i < isSideFrontierSet.size(); i++)
	{
		Relationship relOrgStack(isSideFrontierSet[i]->getPartNameInEpcDocument(), "", isSideFrontierSet[i]->getUuid());
		relOrgStack.setSourceObjectType();
		result.push_back(relOrgStack);
	}

	return result;
}

gsoap_resqml2_0_1::eml20__DataObjectReference* AbstractFeatureInterpretation::getInterpretedFeatureDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->InterpretedFeature;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string AbstractFeatureInterpretation::getInterpretedFeatureUuid() const
{
	return getInterpretedFeatureDor()->UUID;
}

RESQML2_NS::AbstractFeature* AbstractFeatureInterpretation::getInterpretedFeature() const
{
	return static_cast<RESQML2_NS::AbstractFeature*>(epcDocument->getDataObjectByUuid(getInterpretedFeatureUuid()));
}

const gsoap_resqml2_0_1::resqml2__Domain & AbstractFeatureInterpretation::initDomain(const gsoap_resqml2_0_1::resqml2__Domain & defaultDomain) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		const unsigned int repCount = getRepresentationCount();
		bool isTimeDomain = false;
		bool isDepthDomain = false;
		for (unsigned int repIndex = 0; repIndex < repCount && (!isTimeDomain || !isDepthDomain); ++repIndex) {
			AbstractLocal3dCrs* local3dCrs = getRepresentation(repIndex)->getLocalCrs();
			if (local3dCrs != nullptr) {
				if (local3dCrs->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORELocalTime3dCrs) {
					isTimeDomain = true;
				}
				else if (local3dCrs->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORELocalDepth3dCrs) {
					isDepthDomain = true;
				}
			}
		}

		if (isTimeDomain && isDepthDomain) {
			static_cast<gsoap_resqml2_0_1::resqml2__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->Domain = gsoap_resqml2_0_1::resqml2__Domain__mixed;
		}
		else if (!isTimeDomain && !isDepthDomain) {
			static_cast<gsoap_resqml2_0_1::resqml2__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->Domain = defaultDomain;
		}
		else if (isTimeDomain) {
			static_cast<gsoap_resqml2_0_1::resqml2__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->Domain = gsoap_resqml2_0_1::resqml2__Domain__time;
		}
		else {
			static_cast<gsoap_resqml2_0_1::resqml2__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->Domain = gsoap_resqml2_0_1::resqml2__Domain__depth;
		}

		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->Domain;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::resqml2__Domain AbstractFeatureInterpretation::getDomain() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->Domain;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

vector<AbstractRepresentation*> AbstractFeatureInterpretation::getRepresentationSet() const
{
	return representationSet;
}

unsigned int AbstractFeatureInterpretation::getRepresentationCount() const
{
	return representationSet.size();
}

AbstractRepresentation*	AbstractFeatureInterpretation::getRepresentation(const unsigned int & index) const
{
	if (representationSet.size() > index)
		return representationSet[index];
	else
		throw range_error("The representation index you are requesting is out of range.");
}

vector<GridConnectionSetRepresentation *> AbstractFeatureInterpretation::getGridConnectionSetRepresentationSet()
{
	return gridConnectionSetRepresentationSet;
}

void AbstractFeatureInterpretation::setBottomFrontierOf(RESQML2_0_1_NS::StructuralOrganizationInterpretation* structOrg)
{
	isBottomFrontierSet.push_back(structOrg);
}

void AbstractFeatureInterpretation::setTopFrontierOf(RESQML2_0_1_NS::StructuralOrganizationInterpretation* structOrg)
{
	isTopFrontierSet.push_back(structOrg);
}

void AbstractFeatureInterpretation::setSideFrontierOf(RESQML2_0_1_NS::StructuralOrganizationInterpretation* structOrg)
{
	isSideFrontierSet.push_back(structOrg);
}


