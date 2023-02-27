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
#include "StratigraphicColumnRankInterpretation.h"

#include "OrganizationFeature.h"
#include "../resqml2/StratigraphicUnitInterpretation.h"
#include "../resqml2/HorizonInterpretation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

StratigraphicColumnRankInterpretation::StratigraphicColumnRankInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title, uint64_t rank, gsoap_resqml2_0_1::resqml20__OrderingCriteria orderingCriteria)
{
	if (orgFeat == nullptr) {
		throw invalid_argument("The interpreted organization feature cannot be null.");
	}
	if (!orgFeat->isPartial() && dynamic_cast<RESQML2_0_1_NS::OrganizationFeature*>(orgFeat) != nullptr
		&& static_cast<RESQML2_0_1_NS::OrganizationFeature*>(orgFeat)->getKind() != gsoap_resqml2_0_1::resqml20__OrganizationKind::stratigraphic) {
		throw invalid_argument("The kind of an organization feature linked to a stratigraphic column rank interpretation must be a stratigraphic one.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREStratigraphicColumnRankInterpretation(orgFeat->getGsoapContext());
	static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->Domain = resqml20__Domain::mixed;
	static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->Index = rank;
	static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->OrderingCriteria = orderingCriteria;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	orgFeat->getRepository()->addDataObject(this);
	setInterpretedFeature(orgFeat);
}

void StratigraphicColumnRankInterpretation::pushBackStratiUnitInterpretation(RESQML2_NS::StratigraphicUnitInterpretation * stratiUnitInterpretation)
{
	getRepository()->addRelationship(this, stratiUnitInterpretation);

    _resqml20__StratigraphicColumnRankInterpretation* stratigraphicColumnRankInterpretation = static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1); 
	resqml20__StratigraphicUnitInterpretationIndex* stratiUnitInterpRef = soap_new_resqml20__StratigraphicUnitInterpretationIndex(gsoapProxy2_0_1->soap);
	stratiUnitInterpRef->Index = stratigraphicColumnRankInterpretation->StratigraphicUnits.size();
	stratiUnitInterpRef->Unit = stratiUnitInterpretation->newResqmlReference();
	stratigraphicColumnRankInterpretation->StratigraphicUnits.push_back(stratiUnitInterpRef);
}

bool StratigraphicColumnRankInterpretation::isAChronoStratiRank() const
{
	return static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->OrderingCriteria == resqml20__OrderingCriteria::age;
}

uint64_t StratigraphicColumnRankInterpretation::getContactCount() const
{
	return static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size();
}

gsoap_eml2_3::resqml22__ContactMode StratigraphicColumnRankInterpretation::getSubjectContactModeOfContact(uint64_t contactIndex) const
{
	if (static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size() <= contactIndex)
		throw out_of_range("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml20__BinaryContactInterpretationPart* contact = static_cast<resqml20__BinaryContactInterpretationPart*>(static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation[contactIndex]);
	if (contact->Subject->SecondaryQualifier != nullptr) {
		switch (*contact->Subject->SecondaryQualifier) {
		case gsoap_resqml2_0_1::resqml20__ContactMode::baselap:
		case gsoap_resqml2_0_1::resqml20__ContactMode::erosion: return gsoap_eml2_3::resqml22__ContactMode::unconformable;
		case gsoap_resqml2_0_1::resqml20__ContactMode::extended: return gsoap_eml2_3::resqml22__ContactMode::extended;
		case gsoap_resqml2_0_1::resqml20__ContactMode::proportional: return gsoap_eml2_3::resqml22__ContactMode::conformable;
		default: throw std::out_of_range("Not a supported enumerated value for contact mode.");
		}
	}

	return gsoap_eml2_3::resqml22__ContactMode::conformable;
}

RESQML2_NS::StratigraphicUnitInterpretation* StratigraphicColumnRankInterpretation::getSubjectOfContact(uint64_t contactIndex) const
{
	if (static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size() <= contactIndex)
		throw out_of_range("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml20__BinaryContactInterpretationPart* contact = static_cast<resqml20__BinaryContactInterpretationPart*>(static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation[contactIndex]);
	if (contact->Subject)
		return repository->getDataObjectByUuid<RESQML2_NS::StratigraphicUnitInterpretation>(contact->Subject->UUID);
	else
		return nullptr;
}

gsoap_eml2_3::resqml22__ContactMode StratigraphicColumnRankInterpretation::getDirectObjectContactModeOfContact(uint64_t contactIndex) const
{
	if (static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size() <= contactIndex)
		throw out_of_range("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml20__BinaryContactInterpretationPart* contact = static_cast<resqml20__BinaryContactInterpretationPart*>(static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation[contactIndex]);
	if (contact->DirectObject->SecondaryQualifier != nullptr) {
		switch (*contact->DirectObject->SecondaryQualifier) {
		case gsoap_resqml2_0_1::resqml20__ContactMode::baselap:
		case gsoap_resqml2_0_1::resqml20__ContactMode::erosion: return gsoap_eml2_3::resqml22__ContactMode::unconformable;
		case gsoap_resqml2_0_1::resqml20__ContactMode::extended: return gsoap_eml2_3::resqml22__ContactMode::extended;
		case gsoap_resqml2_0_1::resqml20__ContactMode::proportional: return gsoap_eml2_3::resqml22__ContactMode::conformable;
		default: throw std::out_of_range("Not a supported enumerated value for contact mode.");
		}
	}

	return gsoap_eml2_3::resqml22__ContactMode::conformable;
}

RESQML2_NS::StratigraphicUnitInterpretation* StratigraphicColumnRankInterpretation::getDirectObjectOfContact(uint64_t contactIndex) const
{
	if (static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size() <= contactIndex)
		throw out_of_range("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml20__BinaryContactInterpretationPart* contact = static_cast<resqml20__BinaryContactInterpretationPart*>(static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation[contactIndex]);
	if (contact->DirectObject)
		return repository->getDataObjectByUuid<RESQML2_NS::StratigraphicUnitInterpretation>(contact->DirectObject->UUID);
	else
		return nullptr;
}

RESQML2_NS::HorizonInterpretation* StratigraphicColumnRankInterpretation::getHorizonInterpretationOfContact(uint64_t contactIndex) const
{
	if (static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size() <= contactIndex)
		throw out_of_range("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml20__BinaryContactInterpretationPart* contact = static_cast<resqml20__BinaryContactInterpretationPart*>(static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation[contactIndex]);
	if (contact->PartOf)
		return repository->getDataObjectByUuid<RESQML2_NS::HorizonInterpretation>(contact->PartOf->UUID);
	else
		return nullptr;
}

void StratigraphicColumnRankInterpretation::setHorizonOfLastContact(RESQML2_NS::HorizonInterpretation * partOf)
{
	getRepository()->addRelationship(this, partOf);

	resqml20__AbstractOrganizationInterpretation* org = static_cast<resqml20__AbstractOrganizationInterpretation*>(gsoapProxy2_0_1);
    resqml20__BinaryContactInterpretationPart* contact = static_cast<resqml20__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
	contact->PartOf = partOf->newResqmlReference();
}

void StratigraphicColumnRankInterpretation::pushBackStratigraphicBinaryContact(RESQML2_NS::StratigraphicUnitInterpretation* subject, gsoap_eml2_3::resqml22__ContactMode subjectContactMode,
	RESQML2_NS::StratigraphicUnitInterpretation* directObject, gsoap_eml2_3::resqml22__ContactMode directObjectMode,
	RESQML2_NS::HorizonInterpretation * partOf)
{
	resqml20__AbstractOrganizationInterpretation* org = static_cast<resqml20__AbstractOrganizationInterpretation*>(gsoapProxy2_0_1);

	pushBackBinaryContact(subject, gsoap_eml2_3::resqml22__ContactVerb::stops, directObject);
    resqml20__BinaryContactInterpretationPart* contact = static_cast<resqml20__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
    contact->DirectObject->SecondaryQualifier = static_cast<resqml20__ContactMode*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml20__ContactMode)));
	switch (directObjectMode) {
	case gsoap_eml2_3::resqml22__ContactMode::conformable: *(contact->DirectObject->SecondaryQualifier) = gsoap_resqml2_0_1::resqml20__ContactMode::proportional; break;
	case gsoap_eml2_3::resqml22__ContactMode::extended: *(contact->DirectObject->SecondaryQualifier) = gsoap_resqml2_0_1::resqml20__ContactMode::extended; break;
	case gsoap_eml2_3::resqml22__ContactMode::unconformable: *(contact->DirectObject->SecondaryQualifier) = gsoap_resqml2_0_1::resqml20__ContactMode::erosion; break;
	default: throw std::out_of_range("Not a supported enumerated value for contact mode.");
	}
    contact->Subject->SecondaryQualifier = static_cast<resqml20__ContactMode*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml20__ContactMode)));
	switch (subjectContactMode) {
	case gsoap_eml2_3::resqml22__ContactMode::conformable: *(contact->Subject->SecondaryQualifier) = gsoap_resqml2_0_1::resqml20__ContactMode::proportional; break;
	case gsoap_eml2_3::resqml22__ContactMode::extended: *(contact->Subject->SecondaryQualifier) = gsoap_resqml2_0_1::resqml20__ContactMode::extended; break;
	case gsoap_eml2_3::resqml22__ContactMode::unconformable: *(contact->Subject->SecondaryQualifier) = gsoap_resqml2_0_1::resqml20__ContactMode::baselap; break;
	default : throw std::out_of_range("Not a supported enumerated value for contact mode.");
	}

	if (partOf != nullptr) {
		setHorizonOfLastContact(partOf);
	}
}

uint64_t StratigraphicColumnRankInterpretation::getStratigraphicUnitInterpretationCount() const
{
	return static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->StratigraphicUnits.size();
}

COMMON_NS::DataObjectReference StratigraphicColumnRankInterpretation::getStratigraphicUnitInterpretationDor(uint64_t index) const
{
	return COMMON_NS::DataObjectReference(static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->StratigraphicUnits.at(index)->Unit);
}

uint64_t StratigraphicColumnRankInterpretation::getHorizonInterpretationCount() const
{
	_resqml20__StratigraphicColumnRankInterpretation* cr = static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1);
	uint64_t result = 0;
	for (size_t i = 0; i < cr->ContactInterpretation.size(); ++i) {
		if (cr->ContactInterpretation[i]->PartOf != nullptr &&
			cr->ContactInterpretation[i]->PartOf->ContentType.find("HorizonInterpretation") != std::string::npos) {
			++result;
		}
	}

	return result;
}

COMMON_NS::DataObjectReference StratigraphicColumnRankInterpretation::getHorizonInterpretationDor(uint64_t index) const
{
	if (index >= getHorizonInterpretationCount()) {
		throw std::out_of_range("the index is out of range");
	}

	_resqml20__StratigraphicColumnRankInterpretation* cr = static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1);
	unsigned int result = 0;
	for (size_t i = 0; i < cr->ContactInterpretation.size(); ++i) {
		if (cr->ContactInterpretation[i]->PartOf != nullptr &&
			cr->ContactInterpretation[i]->PartOf->ContentType.find(RESQML2_NS::HorizonInterpretation::XML_TAG) != std::string::npos) {
			++result;
		}
		if (result > 0 && index == result - 1) {
			return COMMON_NS::DataObjectReference(cr->ContactInterpretation[i]->PartOf);
		}
	}

	return COMMON_NS::DataObjectReference();
}
