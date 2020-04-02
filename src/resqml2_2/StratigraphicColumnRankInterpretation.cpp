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

#include <stdexcept>

#include "../resqml2/Model.h"
#include "../resqml2/StratigraphicUnitInterpretation.h"
#include "../resqml2/HorizonInterpretation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

StratigraphicColumnRankInterpretation::StratigraphicColumnRankInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title, unsigned long rank, gsoap_resqml2_0_1::resqml20__OrderingCriteria orderingCriteria)
{
	if (orgFeat == nullptr) {
		throw invalid_argument("The interpreted organization feature cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__StratigraphicColumnRankInterpretation(orgFeat->getGsoapContext());
	static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3)->RankInStratigraphicColumn = rank;
	static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3)->OrderingCriteria = static_cast<resqml22__OrderingCriteria>(orderingCriteria);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretedFeature(orgFeat);
}

void StratigraphicColumnRankInterpretation::pushBackStratiUnitInterpretation(RESQML2_NS::StratigraphicUnitInterpretation * stratiUnitInterpretation)
{
	getRepository()->addRelationship(this, stratiUnitInterpretation);

    _resqml22__StratigraphicColumnRankInterpretation* stratigraphicColumnRankInterpretation = static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3);
	stratigraphicColumnRankInterpretation->StratigraphicUnits.push_back(stratiUnitInterpretation->newEml23Reference());
}

bool StratigraphicColumnRankInterpretation::isAChronoStratiRank() const
{
	return static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3)->OrderingCriteria == resqml22__OrderingCriteria__age;
}

unsigned int StratigraphicColumnRankInterpretation::getContactCount() const
{
	return static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3)->ContactInterpretation.size();
}

gsoap_eml2_3::resqml22__ContactMode StratigraphicColumnRankInterpretation::getSubjectContactModeOfContact(unsigned int contactIndex) const
{
	if (static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3)->ContactInterpretation.size() <= contactIndex)
		throw out_of_range("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml22__BinaryContactInterpretationPart* contact = static_cast<resqml22__BinaryContactInterpretationPart*>(static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3)->ContactInterpretation[contactIndex]);
	if (contact->Subject->SecondaryQualifier != nullptr)
		return *contact->Subject->SecondaryQualifier;
	else
		return gsoap_eml2_3::resqml22__ContactMode__conformable;
}

RESQML2_NS::StratigraphicUnitInterpretation* StratigraphicColumnRankInterpretation::getSubjectOfContact(unsigned int contactIndex) const
{
	if (static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3)->ContactInterpretation.size() <= contactIndex)
		throw out_of_range("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml22__BinaryContactInterpretationPart* contact = static_cast<resqml22__BinaryContactInterpretationPart*>(static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3)->ContactInterpretation[contactIndex]);
	if (contact->Subject)
		return repository->getDataObjectByUuid<RESQML2_NS::StratigraphicUnitInterpretation>(contact->Subject->Uuid);
	else
		return nullptr;
}

gsoap_eml2_3::resqml22__ContactMode StratigraphicColumnRankInterpretation::getDirectObjectContactModeOfContact(unsigned int contactIndex) const
{
	if (static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3)->ContactInterpretation.size() <= contactIndex)
		throw out_of_range("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml22__BinaryContactInterpretationPart* contact = static_cast<resqml22__BinaryContactInterpretationPart*>(static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3)->ContactInterpretation[contactIndex]);
	if (contact->DirectObject->SecondaryQualifier)
		return *contact->DirectObject->SecondaryQualifier;
	else
		return gsoap_eml2_3::resqml22__ContactMode__conformable;
}

RESQML2_NS::StratigraphicUnitInterpretation* StratigraphicColumnRankInterpretation::getDirectObjectOfContact(unsigned int contactIndex) const
{
	if (static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3)->ContactInterpretation.size() <= contactIndex)
		throw out_of_range("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml22__BinaryContactInterpretationPart* contact = static_cast<resqml22__BinaryContactInterpretationPart*>(static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3)->ContactInterpretation[contactIndex]);
	if (contact->DirectObject)
		return repository->getDataObjectByUuid<RESQML2_NS::StratigraphicUnitInterpretation>(contact->DirectObject->Uuid);
	else
		return nullptr;
}

RESQML2_NS::HorizonInterpretation* StratigraphicColumnRankInterpretation::getHorizonInterpretationOfContact(unsigned int contactIndex) const
{
	if (static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3)->ContactInterpretation.size() <= contactIndex)
		throw out_of_range("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml22__BinaryContactInterpretationPart* contact = static_cast<resqml22__BinaryContactInterpretationPart*>(static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3)->ContactInterpretation[contactIndex]);
	if (contact->PartOf)
		return repository->getDataObjectByUuid<RESQML2_NS::HorizonInterpretation>(contact->PartOf->Uuid);
	else
		return nullptr;
}

void StratigraphicColumnRankInterpretation::setHorizonOfLastContact(RESQML2_NS::HorizonInterpretation * partOf)
{
	getRepository()->addRelationship(this, partOf);

	resqml22__AbstractOrganizationInterpretation* org = static_cast<resqml22__AbstractOrganizationInterpretation*>(gsoapProxy2_3);
    resqml22__BinaryContactInterpretationPart* contact = static_cast<resqml22__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
	contact->PartOf = partOf->newEml23Reference();
}

void StratigraphicColumnRankInterpretation::pushBackStratigraphicBinaryContact(RESQML2_NS::StratigraphicUnitInterpretation* subject, gsoap_eml2_3::resqml22__ContactMode subjectContactMode,
	RESQML2_NS::StratigraphicUnitInterpretation* directObject, gsoap_eml2_3::resqml22__ContactMode directObjectMode,
	RESQML2_NS::HorizonInterpretation * partOf)
{
	resqml22__AbstractOrganizationInterpretation* org = static_cast<resqml22__AbstractOrganizationInterpretation*>(gsoapProxy2_3);

	pushBackBinaryContact(subject, gsoap_eml2_3::resqml22__ContactVerb__stops, directObject);
    resqml22__BinaryContactInterpretationPart* contact = static_cast<resqml22__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
    contact->DirectObject->SecondaryQualifier = static_cast<resqml22__ContactMode*>(soap_malloc(gsoapProxy2_3->soap, sizeof(resqml22__ContactMode)));
    *(contact->DirectObject->SecondaryQualifier) = directObjectMode;
    contact->Subject->SecondaryQualifier = static_cast<resqml22__ContactMode*>(soap_malloc(gsoapProxy2_3->soap, sizeof(resqml22__ContactMode)));
    *(contact->Subject->SecondaryQualifier) = subjectContactMode;

	if (partOf != nullptr) {
		setHorizonOfLastContact(partOf);
	}
}

unsigned int StratigraphicColumnRankInterpretation::getStratigraphicUnitInterpretationCount() const
{
	return static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3)->StratigraphicUnits.size();
}

COMMON_NS::DataObjectReference StratigraphicColumnRankInterpretation::getStratigraphicUnitInterpretationDor(unsigned int index) const
{
	if (index >= getStratigraphicUnitInterpretationCount()) {
		throw std::out_of_range("the index is out of range");
	}

	return COMMON_NS::DataObjectReference(static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3)->StratigraphicUnits[index]);
}

unsigned int StratigraphicColumnRankInterpretation::getHorizonInterpretationCount() const
{
	_resqml22__StratigraphicColumnRankInterpretation* cr = static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3);
	unsigned int result = 0;
	for (size_t i = 0; i < cr->ContactInterpretation.size(); ++i) {
		if (cr->ContactInterpretation[i]->PartOf != nullptr &&
			cr->ContactInterpretation[i]->PartOf->ContentType.find("HorizonInterpretation") != std::string::npos) {
			++result;
		}
	}

	return result;
}

COMMON_NS::DataObjectReference StratigraphicColumnRankInterpretation::getHorizonInterpretationDor(unsigned int index) const
{
	if (index >= getHorizonInterpretationCount()) {
		throw std::out_of_range("the index is out of range");
	}

	_resqml22__StratigraphicColumnRankInterpretation* cr = static_cast<_resqml22__StratigraphicColumnRankInterpretation*>(gsoapProxy2_3);
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
