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
#include "resqml2_0_1/StratigraphicOccurrenceInterpretation.h"

#include <stdexcept>

#include "resqml2_0_1/OrganizationFeature.h"
#include "resqml2_0_1/StratigraphicColumnRankInterpretation.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* StratigraphicOccurrenceInterpretation::XML_TAG = "StratigraphicOccurrenceInterpretation";

StratigraphicOccurrenceInterpretation::StratigraphicOccurrenceInterpretation(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__OrderingCriteria & orderingCriteria):
	stratigraphicColumnRankInterpretation(nullptr)
{
	if (!orgFeat)
		throw invalid_argument("The interpreted organization feature cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREStratigraphicOccurrenceInterpretation(orgFeat->getGsoapContext(), 1);
	static_cast<_resqml2__StratigraphicOccurrenceInterpretation*>(gsoapProxy2_0_1)->Domain = resqml2__Domain__mixed;
	static_cast<_resqml2__StratigraphicOccurrenceInterpretation*>(gsoapProxy2_0_1)->OrderingCriteria = orderingCriteria;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	setInterpretedFeature(orgFeat);
}

void StratigraphicOccurrenceInterpretation::setStratigraphicColumnRankInterpretation(StratigraphicColumnRankInterpretation * stratiColumnRankInterp)
{
	// EPC
	stratigraphicColumnRankInterpretation = stratiColumnRankInterp;
	stratiColumnRankInterp->stratigraphicOccurrenceInterpretationSet.push_back(this);

    // XML
	if (updateXml)
	{
		_resqml2__StratigraphicOccurrenceInterpretation* interp = static_cast<_resqml2__StratigraphicOccurrenceInterpretation*>(gsoapProxy2_0_1);
		interp->IsOccurrenceOf = stratiColumnRankInterp->newResqmlReference();
	}
}

std::string StratigraphicOccurrenceInterpretation::getStratigraphicColumnRankInterpretationUuid() const
{
	return static_cast<_resqml2__StratigraphicOccurrenceInterpretation*>(gsoapProxy2_0_1)->IsOccurrenceOf->UUID;
}

vector<Relationship> StratigraphicOccurrenceInterpretation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractStratigraphicOrganizationInterpretation::getAllEpcRelationships();

	if (stratigraphicColumnRankInterpretation)
	{
		Relationship relStratiRank(stratigraphicColumnRankInterpretation->getPartNameInEpcDocument(), "", stratigraphicColumnRankInterpretation->getUuid());
		relStratiRank.setDestinationObjectType();
		result.push_back(relStratiRank);
	}

	for (unsigned int i = 0; i < earthModelSet.size(); i++)
	{
		Relationship rel(earthModelSet[i]->getPartNameInEpcDocument(), "", earthModelSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	for (unsigned int i = 0; i < wellboreMarkerFrameRepresentationSet.size(); i++)
	{
		Relationship rel(wellboreMarkerFrameRepresentationSet[i]->getPartNameInEpcDocument(), "", wellboreMarkerFrameRepresentationSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}
        
    return result;
}
	
void StratigraphicOccurrenceInterpretation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractStratigraphicOrganizationInterpretation::importRelationshipSetFromEpc(epcDoc);

	updateXml = false;

	_resqml2__StratigraphicOccurrenceInterpretation* interp = static_cast<_resqml2__StratigraphicOccurrenceInterpretation*>(gsoapProxy2_0_1); 

	if (interp->IsOccurrenceOf)
	{
		setStratigraphicColumnRankInterpretation(static_cast<StratigraphicColumnRankInterpretation*>(epcDoc->getResqmlAbstractObjectByUuid(interp->IsOccurrenceOf->UUID)));
	}

	updateXml = true;
}
