/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2016)

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
#include "resqml2/AbstractFeatureInterpretation.h"

#include <stdexcept>

#include "resqml2/AbstractFeature.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "resqml2/GridConnectionSetRepresentation.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"

using namespace resqml2;
using namespace std;
using namespace epc;


void AbstractFeatureInterpretation::setInterpretedFeatureInXml(resqml2::AbstractFeature* feature)
{
	if (gsoapProxy2_0_1 != nullptr) {
		static_cast<gsoap_resqml2_0_1::resqml2__AbstractFeatureInterpretation*>(gsoapProxy2_0_1)->InterpretedFeature = feature->newResqmlReference();
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractFeatureInterpretation::setInterpretedFeature(resqml2::AbstractFeature * feature)
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

void AbstractFeatureInterpretation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getInterpretedFeatureDor();
	resqml2::AbstractFeature* interpretedFeature = epcDoc->getResqmlAbstractObjectByUuid<AbstractFeature>(dor->UUID);
	if (interpretedFeature == nullptr) { // partial transfer
		getEpcDocument()->createPartial(dor);
		interpretedFeature = getEpcDocument()->getResqmlAbstractObjectByUuid<AbstractFeature>(dor->UUID);
	}
	if (interpretedFeature == nullptr) {
		throw invalid_argument("The DOR looks invalid.");
	}
	updateXml = false;
	setInterpretedFeature(interpretedFeature);
	updateXml = true;
}

vector<Relationship> AbstractFeatureInterpretation::getAllEpcRelationships() const
{
	vector<Relationship> result;

	resqml2::AbstractFeature* interpretedFeature = getInterpretedFeature();
	Relationship rel(interpretedFeature->getPartNameInEpcDocument(), "", interpretedFeature->getUuid());
	rel.setDestinationObjectType();
	result.push_back(rel);
	
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

resqml2::AbstractFeature* AbstractFeatureInterpretation::getInterpretedFeature() const
{
	return static_cast<resqml2::AbstractFeature*>(epcDocument->getResqmlAbstractObjectByUuid(getInterpretedFeatureUuid()));
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

void AbstractFeatureInterpretation::setBottomFrontierOf(resqml2_0_1::StructuralOrganizationInterpretation* structOrg)
{
	isBottomFrontierSet.push_back(structOrg);
}

void AbstractFeatureInterpretation::setTopFrontierOf(resqml2_0_1::StructuralOrganizationInterpretation* structOrg)
{
	isTopFrontierSet.push_back(structOrg);
}

void AbstractFeatureInterpretation::setSideFrontierOf(resqml2_0_1::StructuralOrganizationInterpretation* structOrg)
{
	isSideFrontierSet.push_back(structOrg);
}

