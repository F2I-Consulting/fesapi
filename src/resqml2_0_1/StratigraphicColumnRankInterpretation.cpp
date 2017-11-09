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
#include "resqml2_0_1/StratigraphicColumnRankInterpretation.h"

#include <stdexcept>

#include "resqml2_0_1/OrganizationFeature.h"
#include "resqml2_0_1/StratigraphicUnitInterpretation.h"
#include "resqml2_0_1/HorizonInterpretation.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* StratigraphicColumnRankInterpretation::XML_TAG = "StratigraphicColumnRankInterpretation";

StratigraphicColumnRankInterpretation::StratigraphicColumnRankInterpretation(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank, const gsoap_resqml2_0_1::resqml2__OrderingCriteria & orderingCriteria)
{
	if (!orgFeat)
		throw invalid_argument("The interpreted organization feature cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREStratigraphicColumnRankInterpretation(orgFeat->getGsoapContext(), 1);
	static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->Domain = resqml2__Domain__mixed;
	static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->Index = rank;
	static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->OrderingCriteria = orderingCriteria;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	setInterpretedFeature(orgFeat);
}

void StratigraphicColumnRankInterpretation::pushBackStratiUnitInterpretation(StratigraphicUnitInterpretation * stratiUnitInterpretation)
{
	// EPC
	stratigraphicUnitSet.push_back(stratiUnitInterpretation);
	stratiUnitInterpretation->stratigraphicColumnRankSet.push_back(this);

    // XML
	if (updateXml)
	{
        _resqml2__StratigraphicColumnRankInterpretation* stratigraphicColumnRankInterpretation = static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1); 
		resqml2__StratigraphicUnitInterpretationIndex* stratiUnitInterpRef = soap_new_resqml2__StratigraphicUnitInterpretationIndex(gsoapProxy2_0_1->soap, 1);
		stratiUnitInterpRef->Index = stratigraphicColumnRankInterpretation->StratigraphicUnits.size();
		stratiUnitInterpRef->Unit = stratiUnitInterpretation->newResqmlReference();
		stratigraphicColumnRankInterpretation->StratigraphicUnits.push_back(stratiUnitInterpRef);
	}
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
		return static_cast<StratigraphicUnitInterpretation*>(epcDocument->getResqmlAbstractObjectByUuid(contact->Subject->UUID));
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
		return static_cast<StratigraphicUnitInterpretation*>(epcDocument->getResqmlAbstractObjectByUuid(contact->DirectObject->UUID));
	else
		return nullptr;
}

HorizonInterpretation* StratigraphicColumnRankInterpretation::getHorizonInterpretationOfContact(const unsigned int & contactIndex) const
{
	if (static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation.size() <= contactIndex)
		throw range_error("The contact index is out of range in the context of the StratigraphicColumnRankInterpretation");

	resqml2__BinaryContactInterpretationPart* contact = static_cast<resqml2__BinaryContactInterpretationPart*>(static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1)->ContactInterpretation[contactIndex]);
	if (contact->PartOf)
		return static_cast<HorizonInterpretation*>(epcDocument->getResqmlAbstractObjectByUuid(contact->PartOf->UUID));
	else
		return nullptr;
}

void StratigraphicColumnRankInterpretation::setHorizonOfLastContact(HorizonInterpretation * partOf)
{
	// EPC
	horizonInterpretationSet.push_back(partOf);
	partOf->stratigraphicColumnRankInterpretationSet.push_back(this);

    // XML
	if (updateXml)
	{
		resqml2__AbstractOrganizationInterpretation* org = static_cast<resqml2__AbstractOrganizationInterpretation*>(gsoapProxy2_0_1);
        resqml2__BinaryContactInterpretationPart* contact = static_cast<resqml2__BinaryContactInterpretationPart*>(org->ContactInterpretation[org->ContactInterpretation.size() - 1]);
		contact->PartOf = partOf->newResqmlReference();
	}
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

	if (partOf)
	{
		setHorizonOfLastContact(partOf);
	}
}
		
void StratigraphicColumnRankInterpretation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractStratigraphicOrganizationInterpretation::importRelationshipSetFromEpc(epcDoc);

	updateXml = false;

	_resqml2__StratigraphicColumnRankInterpretation* interp = static_cast<_resqml2__StratigraphicColumnRankInterpretation*>(gsoapProxy2_0_1); 

	for (unsigned int i = 0; i < interp->StratigraphicUnits.size(); i++)
	{
		if (interp->StratigraphicUnits[i]->Unit)
			pushBackStratiUnitInterpretation(static_cast<StratigraphicUnitInterpretation*>(epcDoc->getResqmlAbstractObjectByUuid(interp->StratigraphicUnits[i]->Unit->UUID)));
		else
			throw logic_error("Not yet implemented");
	}

	for (unsigned int i = 0; i < interp->ContactInterpretation.size(); i++)
	{
		if (interp->ContactInterpretation[i]->PartOf) {
			HorizonInterpretation* horizonInterp = epcDoc->getResqmlAbstractObjectByUuid<HorizonInterpretation>(interp->ContactInterpretation[i]->PartOf->UUID);

			if (horizonInterp == nullptr) {
				getEpcDocument()->addWarning("The referenced horizon interp \"" + interp->ContactInterpretation[i]->PartOf->Title + "\" (" + interp->ContactInterpretation[i]->PartOf->UUID + ") is missing.");
				horizonInterp = epcDoc->createPartialHorizonInterpretation(interp->ContactInterpretation[i]->PartOf->UUID, interp->ContactInterpretation[i]->PartOf->Title);
			}

			setHorizonOfLastContact(horizonInterp);
		}
		else
			throw logic_error("Not yet implemented");
	}

	updateXml = true;
}

vector<Relationship> StratigraphicColumnRankInterpretation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractStratigraphicOrganizationInterpretation::getAllEpcRelationships();

	// forward relationships
	for (unsigned int i = 0; i < stratigraphicUnitSet.size(); i++)
	{
		Relationship rel(stratigraphicUnitSet[i]->getPartNameInEpcDocument(), "", stratigraphicUnitSet[i]->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}

	for (unsigned int i = 0; i < horizonInterpretationSet.size(); i++)
	{
		Relationship rel(horizonInterpretationSet[i]->getPartNameInEpcDocument(), "", horizonInterpretationSet[i]->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}

	// Backward relationships
	for (unsigned int i = 0; i < stratigraphicColumnSet.size(); i++)
	{
		Relationship rel(stratigraphicColumnSet[i]->getPartNameInEpcDocument(), "", stratigraphicColumnSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	for (unsigned int i = 0; i < stratigraphicOccurrenceInterpretationSet.size(); i++)
	{
		Relationship rel(stratigraphicOccurrenceInterpretationSet[i]->getPartNameInEpcDocument(), "", stratigraphicOccurrenceInterpretationSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}
        
    return result;
}

const std::vector<class StratigraphicUnitInterpretation*> & StratigraphicColumnRankInterpretation::getStratigraphicUnitInterpretationSet() const
{
	return stratigraphicUnitSet;
}

const std::vector<class StratigraphicOccurrenceInterpretation*> & StratigraphicColumnRankInterpretation::getStratigraphicOccurrenceInterpretationSet() const
{
	return stratigraphicOccurrenceInterpretationSet;
}

const std::vector<class HorizonInterpretation*> & StratigraphicColumnRankInterpretation::getHorizonInterpretationSet() const
{
	return horizonInterpretationSet;
}

const std::vector<StratigraphicColumn*> & StratigraphicColumnRankInterpretation::getStratigraphicColumnSet() const
{
	return stratigraphicColumnSet;
}
