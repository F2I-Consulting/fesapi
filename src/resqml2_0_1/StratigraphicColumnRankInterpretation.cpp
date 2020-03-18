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

#include "OrganizationFeature.h"
#include "StratigraphicUnitInterpretation.h"
#include "HorizonInterpretation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* StratigraphicColumnRankInterpretation::XML_TAG = "StratigraphicColumnRankInterpretation";

StratigraphicColumnRankInterpretation::StratigraphicColumnRankInterpretation(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, unsigned long rank, gsoap_resqml2_0_1::resqml20__OrderingCriteria orderingCriteria)
{
	if (orgFeat == nullptr) {
		throw invalid_argument("The interpreted organization feature cannot be null.");
	}
	if (!orgFeat->isPartial() && orgFeat->getKind() != gsoap_resqml2_0_1::resqml20__OrganizationKind__stratigraphic) {
		throw invalid_argument("The kind of an organization feature linked to a stratigraphic column rank interpretation must be a stratigraphic one.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREStratigraphicColumnRankInterpretation(orgFeat->getGsoapContext());
	static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->Domain = resqml20__Domain__mixed;
	static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->Index = rank;
	static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->OrderingCriteria = orderingCriteria;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretedFeature(orgFeat);
}

void StratigraphicColumnRankInterpretation::pushBackStratiUnitInterpretation(StratigraphicUnitInterpretation * stratiUnitInterpretation)
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
	return static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->OrderingCriteria == resqml20__OrderingCriteria__age;
}

unsigned int StratigraphicColumnRankInterpretation::getContactCount() const
{
	return static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size();
}

resqml20__ContactMode StratigraphicColumnRankInterpretation::getSubjectContactModeOfContact(const unsigned int & contactIndex) const
{
	if (static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size() <= contactIndex)
		throw range_error("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml20__BinaryContactInterpretationPart* contact = static_cast<resqml20__BinaryContactInterpretationPart*>(static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation[contactIndex]);
	if (contact->Subject->SecondaryQualifier)
		return *contact->Subject->SecondaryQualifier;
	else
		return resqml20__ContactMode__proportional;
}

StratigraphicUnitInterpretation* StratigraphicColumnRankInterpretation::getSubjectOfContact(const unsigned int & contactIndex) const
{
	if (static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size() <= contactIndex)
		throw range_error("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml20__BinaryContactInterpretationPart* contact = static_cast<resqml20__BinaryContactInterpretationPart*>(static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation[contactIndex]);
	if (contact->Subject)
		return static_cast<StratigraphicUnitInterpretation*>(repository->getDataObjectByUuid(contact->Subject->UUID));
	else
		return nullptr;
}

resqml20__ContactMode StratigraphicColumnRankInterpretation::getDirectObjectContactModeOfContact(const unsigned int & contactIndex) const
{
	if (static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size() <= contactIndex)
		throw range_error("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml20__BinaryContactInterpretationPart* contact = static_cast<resqml20__BinaryContactInterpretationPart*>(static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation[contactIndex]);
	if (contact->DirectObject->SecondaryQualifier)
		return *contact->DirectObject->SecondaryQualifier;
	else
		return resqml20__ContactMode__proportional;
}

StratigraphicUnitInterpretation* StratigraphicColumnRankInterpretation::getDirectObjectOfContact(const unsigned int & contactIndex) const
{
	if (static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size() <= contactIndex)
		throw range_error("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml20__BinaryContactInterpretationPart* contact = static_cast<resqml20__BinaryContactInterpretationPart*>(static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation[contactIndex]);
	if (contact->DirectObject)
		return static_cast<StratigraphicUnitInterpretation*>(repository->getDataObjectByUuid(contact->DirectObject->UUID));
	else
		return nullptr;
}

HorizonInterpretation* StratigraphicColumnRankInterpretation::getHorizonInterpretationOfContact(const unsigned int & contactIndex) const
{
	if (static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size() <= contactIndex)
		throw range_error("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml20__BinaryContactInterpretationPart* contact = static_cast<resqml20__BinaryContactInterpretationPart*>(static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation[contactIndex]);
	if (contact->PartOf)
		return static_cast<HorizonInterpretation*>(repository->getDataObjectByUuid(contact->PartOf->UUID));
	else
		return nullptr;
}

void StratigraphicColumnRankInterpretation::setHorizonOfLastContact(HorizonInterpretation * partOf)
{
	getRepository()->addRelationship(this, partOf);

	resqml20__AbstractOrganizationInterpretation* org = static_cast<resqml20__AbstractOrganizationInterpretation*>(gsoapProxy2_0_1);
    resqml20__BinaryContactInterpretationPart* contact = static_cast<resqml20__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
	contact->PartOf = partOf->newResqmlReference();
}

void StratigraphicColumnRankInterpretation::pushBackStratigraphicBinaryContact(StratigraphicUnitInterpretation* subject, const gsoap_resqml2_0_1::resqml20__ContactMode & subjectContactMode,
			StratigraphicUnitInterpretation* directObject, gsoap_resqml2_0_1::resqml20__ContactMode directObjectMode,
			HorizonInterpretation * partOf)
{
	resqml20__AbstractOrganizationInterpretation* org = static_cast<resqml20__AbstractOrganizationInterpretation*>(gsoapProxy2_0_1);

	pushBackBinaryContact(subject, gsoap_eml2_2::resqml22__ContactVerb__stops, directObject);
    resqml20__BinaryContactInterpretationPart* contact = static_cast<resqml20__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
    contact->DirectObject->SecondaryQualifier = static_cast<resqml20__ContactMode*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml20__ContactMode)));
    *(contact->DirectObject->SecondaryQualifier) = directObjectMode;
    contact->Subject->SecondaryQualifier = static_cast<resqml20__ContactMode*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml20__ContactMode)));
    *(contact->Subject->SecondaryQualifier) = subjectContactMode;

	if (partOf != nullptr) {
		setHorizonOfLastContact(partOf);
	}
}
		
void StratigraphicColumnRankInterpretation::loadTargetRelationships()
{
	AbstractStratigraphicOrganizationInterpretation::loadTargetRelationships();

	_resqml20__StratigraphicColumnRankInterpretation* interp = static_cast<_resqml20__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1); 

	for (size_t i = 0; i < interp->StratigraphicUnits.size(); ++i)
	{
		if (interp->StratigraphicUnits[i]->Unit != nullptr) {
			convertDorIntoRel<StratigraphicUnitInterpretation>(interp->StratigraphicUnits[i]->Unit);
		}
	}

	for (size_t i = 0; i < interp->ContactInterpretation.size(); ++i)
	{
		if (interp->ContactInterpretation[i]->PartOf != nullptr) {
			convertDorIntoRel<HorizonInterpretation>(interp->ContactInterpretation[i]->PartOf);
		}
	}
}

std::vector<StratigraphicUnitInterpretation *> StratigraphicColumnRankInterpretation::getStratigraphicUnitInterpretationSet() const
{
	return getRepository()->getTargetObjects<StratigraphicUnitInterpretation>(this);
}

std::vector<StratigraphicOccurrenceInterpretation *> StratigraphicColumnRankInterpretation::getStratigraphicOccurrenceInterpretationSet() const
{
	return getRepository()->getSourceObjects<StratigraphicOccurrenceInterpretation>(this);
}

std::vector<HorizonInterpretation *> StratigraphicColumnRankInterpretation::getHorizonInterpretationSet() const
{
	return getRepository()->getTargetObjects<HorizonInterpretation>(this);
}

std::vector<StratigraphicColumn *> StratigraphicColumnRankInterpretation::getStratigraphicColumnSet() const
{
	return getRepository()->getSourceObjects<StratigraphicColumn>(this);
}
