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
#include "resqml2_0_1/StratigraphicColumnRankInterpretation.h"

#include <stdexcept>

#include "resqml2_0_1/OrganizationFeature.h"
#include "resqml2_0_1/StratigraphicUnitInterpretation.h"
#include "resqml2_0_1/HorizonInterpretation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* StratigraphicColumnRankInterpretation::XML_TAG = "StratigraphicColumnRankInterpretation";

StratigraphicColumnRankInterpretation::StratigraphicColumnRankInterpretation(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank, const gsoap_resqml2_0_1::resqml2__OrderingCriteria & orderingCriteria)
{
	if (orgFeat == nullptr) {
		throw invalid_argument("The interpreted organization feature cannot be null.");
	}
	if (!orgFeat->isPartial() && orgFeat->getKind() != gsoap_resqml2_0_1::resqml2__OrganizationKind__stratigraphic) {
		throw invalid_argument("The kind of an organization feature linked to a stratigraphic column rank interpretation must be a stratigraphic one.");
	}

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREStratigraphicColumnRankInterpretation(orgFeat->getGsoapContext(), 1);
	static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->Domain = resqml2__Domain__mixed;
	static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->Index = rank;
	static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->OrderingCriteria = orderingCriteria;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretedFeature(orgFeat);
}

void StratigraphicColumnRankInterpretation::pushBackStratiUnitInterpretation(StratigraphicUnitInterpretation * stratiUnitInterpretation)
{
	getRepository()->addRelationship(this, stratiUnitInterpretation);

    _resqml2__StratigraphicColumnRankInterpretation* stratigraphicColumnRankInterpretation = static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1); 
	resqml2__StratigraphicUnitInterpretationIndex* stratiUnitInterpRef = soap_new_resqml2__StratigraphicUnitInterpretationIndex(gsoapProxy2_0_1->soap, 1);
	stratiUnitInterpRef->Index = stratigraphicColumnRankInterpretation->StratigraphicUnits.size();
	stratiUnitInterpRef->Unit = stratiUnitInterpretation->newResqmlReference();
	stratigraphicColumnRankInterpretation->StratigraphicUnits.push_back(stratiUnitInterpRef);
}

bool StratigraphicColumnRankInterpretation::isAChronoStratiRank() const
{
	return static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->OrderingCriteria == resqml2__OrderingCriteria__age;
}

unsigned int StratigraphicColumnRankInterpretation::getContactCount() const
{
	return static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size();
}

resqml2__ContactMode StratigraphicColumnRankInterpretation::getSubjectContactModeOfContact(const unsigned int & contactIndex) const
{
	if (static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size() <= contactIndex)
		throw range_error("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml2__BinaryContactInterpretationPart* contact = static_cast<resqml2__BinaryContactInterpretationPart*>(static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation[contactIndex]);
	if (contact->Subject->SecondaryQualifier)
		return *contact->Subject->SecondaryQualifier;
	else
		return resqml2__ContactMode__proportional;
}

StratigraphicUnitInterpretation* StratigraphicColumnRankInterpretation::getSubjectOfContact(const unsigned int & contactIndex) const
{
	if (static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size() <= contactIndex)
		throw range_error("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml2__BinaryContactInterpretationPart* contact = static_cast<resqml2__BinaryContactInterpretationPart*>(static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation[contactIndex]);
	if (contact->Subject)
		return static_cast<StratigraphicUnitInterpretation*>(repository->getDataObjectByUuid(contact->Subject->UUID));
	else
		return nullptr;
}

resqml2__ContactMode StratigraphicColumnRankInterpretation::getDirectObjectContactModeOfContact(const unsigned int & contactIndex) const
{
	if (static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size() <= contactIndex)
		throw range_error("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml2__BinaryContactInterpretationPart* contact = static_cast<resqml2__BinaryContactInterpretationPart*>(static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation[contactIndex]);
	if (contact->DirectObject->SecondaryQualifier)
		return *contact->DirectObject->SecondaryQualifier;
	else
		return resqml2__ContactMode__proportional;
}

StratigraphicUnitInterpretation* StratigraphicColumnRankInterpretation::getDirectObjectOfContact(const unsigned int & contactIndex) const
{
	if (static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size() <= contactIndex)
		throw range_error("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml2__BinaryContactInterpretationPart* contact = static_cast<resqml2__BinaryContactInterpretationPart*>(static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation[contactIndex]);
	if (contact->DirectObject)
		return static_cast<StratigraphicUnitInterpretation*>(repository->getDataObjectByUuid(contact->DirectObject->UUID));
	else
		return nullptr;
}

HorizonInterpretation* StratigraphicColumnRankInterpretation::getHorizonInterpretationOfContact(const unsigned int & contactIndex) const
{
	if (static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size() <= contactIndex)
		throw range_error("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml2__BinaryContactInterpretationPart* contact = static_cast<resqml2__BinaryContactInterpretationPart*>(static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation[contactIndex]);
	if (contact->PartOf)
		return static_cast<HorizonInterpretation*>(repository->getDataObjectByUuid(contact->PartOf->UUID));
	else
		return nullptr;
}

void StratigraphicColumnRankInterpretation::setHorizonOfLastContact(HorizonInterpretation * partOf)
{
	getRepository()->addRelationship(this, partOf);

	resqml2__AbstractOrganizationInterpretation* org = static_cast<resqml2__AbstractOrganizationInterpretation*>(gsoapProxy2_0_1);
    resqml2__BinaryContactInterpretationPart* contact = static_cast<resqml2__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
	contact->PartOf = partOf->newResqmlReference();
}

void StratigraphicColumnRankInterpretation::pushBackStratigraphicBinaryContact(StratigraphicUnitInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactMode & subjectContactMode,
			StratigraphicUnitInterpretation* directObject, const gsoap_resqml2_0_1::resqml2__ContactMode & directObjectMode,
			HorizonInterpretation * partOf)
{
	resqml2__AbstractOrganizationInterpretation* org = static_cast<resqml2__AbstractOrganizationInterpretation*>(gsoapProxy2_0_1);

	pushBackBinaryContact(resqml2__ContactRelationship__stratigraphic_x0020unit_x0020to_x0020stratigraphic_x0020unit, subject, resqml2__ContactVerb__stops_x0020at, directObject);
    resqml2__BinaryContactInterpretationPart* contact = static_cast<resqml2__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
    contact->DirectObject->SecondaryQualifier = static_cast<resqml2__ContactMode*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml2__ContactMode)));
    *(contact->DirectObject->SecondaryQualifier) = directObjectMode;
    contact->Subject->SecondaryQualifier = static_cast<resqml2__ContactMode*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(resqml2__ContactMode)));
    *(contact->Subject->SecondaryQualifier) = subjectContactMode;

	if (partOf != nullptr)
	{
		setHorizonOfLastContact(partOf);
	}
}
		
void StratigraphicColumnRankInterpretation::loadTargetRelationships() const
{
	AbstractStratigraphicOrganizationInterpretation::loadTargetRelationships();

	_resqml2__StratigraphicColumnRankInterpretation* interp = static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1); 

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

std::vector<StratigraphicUnitInterpretation const *> StratigraphicColumnRankInterpretation::getStratigraphicUnitInterpretationSet() const
{
	return getRepository()->getTargetObjects<StratigraphicUnitInterpretation>(this);
}

std::vector<StratigraphicOccurrenceInterpretation const *> StratigraphicColumnRankInterpretation::getStratigraphicOccurrenceInterpretationSet() const
{
	return getRepository()->getSourceObjects<StratigraphicOccurrenceInterpretation>(this);
}

std::vector<HorizonInterpretation const *> StratigraphicColumnRankInterpretation::getHorizonInterpretationSet() const
{
	return getRepository()->getTargetObjects<HorizonInterpretation>(this);
}

std::vector<StratigraphicColumn const *> StratigraphicColumnRankInterpretation::getStratigraphicColumnSet() const
{
	return getRepository()->getSourceObjects<StratigraphicColumn>(this);
}
