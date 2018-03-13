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
#include "resqml2_0_1/EarthModelInterpretation.h"

#include <stdexcept>

#include "resqml2_0_1/OrganizationFeature.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"
#include "resqml2_0_1/StratigraphicColumn.h"
#include "resqml2_0_1/StratigraphicOccurrenceInterpretation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* EarthModelInterpretation::XML_TAG = "EarthModelInterpretation";

EarthModelInterpretation::EarthModelInterpretation(OrganizationFeature * orgFeat, const std::string & guid, const string & title):
	structuralOrganization(nullptr), stratigraphicColumn(nullptr)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREEarthModelInterpretation(orgFeat->getGsoapContext(), 1);
	_resqml2__EarthModelInterpretation* interp = static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1);

	interp->Domain = resqml2__Domain__mixed;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	setInterpretedFeature(orgFeat);
}

void EarthModelInterpretation::setStructuralOrganizationInterpretation(StructuralOrganizationInterpretation * structOrganization)
{
    // epc
    this->structuralOrganization = structOrganization;
	structuralOrganization->earthModelSet.push_back(this);
        
    // XML
	if (updateXml)
		static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->Structure = structOrganization->newResqmlReference();
}

void EarthModelInterpretation::setStratiColumn(StratigraphicColumn * stratiColumn)
{
    // epc
    this->stratigraphicColumn = stratiColumn;
    stratiColumn->earthModel = this;
        
    // XML
	if (updateXml)
		static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicColumn = stratiColumn->newResqmlReference();
}

void EarthModelInterpretation::pushBackStratiOccurence(StratigraphicOccurrenceInterpretation * stratiOccurence)
{
    // epc
	this->stratigraphicOccurenceSet.push_back(stratiOccurence);
    stratiOccurence->earthModelSet.push_back(this);
        
    // XML
	if (updateXml)
		static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicOccurrences.push_back(stratiOccurence->newResqmlReference());
}

vector<Relationship> EarthModelInterpretation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractFeatureInterpretation::getAllEpcRelationships();
        
    if (structuralOrganization)
    {
        Relationship rel(structuralOrganization->getPartNameInEpcDocument(), "", structuralOrganization->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
    }

    if (stratigraphicColumn)
    {
        Relationship rel(stratigraphicColumn->getPartNameInEpcDocument(), "", stratigraphicColumn->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
    }

	for (unsigned int i = 0; i< stratigraphicOccurenceSet.size();i++)
    {
		if (stratigraphicOccurenceSet[i])
		{
			Relationship rel(stratigraphicOccurenceSet[i]->getPartNameInEpcDocument(), "", stratigraphicOccurenceSet[i]->getUuid());
			rel.setDestinationObjectType();
			result.push_back(rel);
		}
		else
			throw domain_error("The stratigraphic occurence associated to the earth model cannot be nullptr.");
    }
        
    return result;
}
		
void EarthModelInterpretation::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	AbstractFeatureInterpretation::importRelationshipSetFromEpc(epcDoc);

	updateXml = false;

	_resqml2__EarthModelInterpretation* interp = static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1);

	if (interp->Structure)
	{
		StructuralOrganizationInterpretation* structuralOrganizationInterp = static_cast<StructuralOrganizationInterpretation*>(epcDoc->getResqmlAbstractObjectByUuid(interp->Structure->UUID));
		if (structuralOrganizationInterp)
			setStructuralOrganizationInterpretation(structuralOrganizationInterp);
	}

	if (interp->StratigraphicColumn)
	{
		StratigraphicColumn* stratCol = static_cast<StratigraphicColumn*>(epcDoc->getResqmlAbstractObjectByUuid(interp->StratigraphicColumn->UUID));
		if (stratCol)
			setStratiColumn(stratCol);
	}

	for (unsigned int i = 0; i < interp->StratigraphicOccurrences.size(); i++)
	{
		pushBackStratiOccurence(static_cast<StratigraphicOccurrenceInterpretation*>(epcDoc->getResqmlAbstractObjectByUuid(interp->StratigraphicOccurrences[i]->UUID)));
	}

	updateXml = true;
}

