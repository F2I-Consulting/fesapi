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

