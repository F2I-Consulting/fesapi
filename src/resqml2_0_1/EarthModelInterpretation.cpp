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

#include "tools/Misc.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* EarthModelInterpretation::XML_TAG = "EarthModelInterpretation";

EarthModelInterpretation::EarthModelInterpretation(OrganizationFeature * orgFeat, const std::string & guid, const string & title)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREEarthModelInterpretation(orgFeat->getGsoapContext(), 1);
	_resqml2__EarthModelInterpretation* interp = static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1);

	interp->Domain = resqml2__Domain__mixed;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretedFeature(orgFeat);
}

void EarthModelInterpretation::setStructuralOrganizationInterpretation(StructuralOrganizationInterpretation * structOrganization)
{
    // epc
	structOrganization->earthModelSet.push_back(this);
        
    // XML
	if (updateXml) {
		static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->Structure = structOrganization->newResqmlReference();
	}
}

void EarthModelInterpretation::setStratiColumn(StratigraphicColumn * stratiColumn)
{
    // epc
    stratiColumn->earthModel = this;
        
    // XML
	if (updateXml) {
		static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicColumn = stratiColumn->newResqmlReference();
	}
}

void EarthModelInterpretation::pushBackStratiOccurence(StratigraphicOccurrenceInterpretation * stratiOccurence)
{
    // epc
    stratiOccurence->earthModelSet.push_back(this);
        
    // XML
	if (updateXml) {
		static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicOccurrences.push_back(stratiOccurence->newResqmlReference());
	}
}

vector<Relationship> EarthModelInterpretation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractFeatureInterpretation::getAllEpcRelationships();

	_resqml2__EarthModelInterpretation* interp = static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1);

    if (interp->Structure != nullptr)
    {
        Relationship rel(misc::getPartNameFromReference(interp->Structure), "", interp->Structure->UUID);
		rel.setDestinationObjectType();
		result.push_back(rel);
    }

    if (interp->StratigraphicColumn != nullptr)
    {
        Relationship rel(misc::getPartNameFromReference(interp->StratigraphicColumn), "", interp->StratigraphicColumn->UUID);
		rel.setDestinationObjectType();
		result.push_back(rel);
    }

	for (size_t i = 0; i < interp->StratigraphicOccurrences.size(); ++i)
    {
		if (interp->StratigraphicOccurrences[i] != nullptr)
		{
			Relationship rel(misc::getPartNameFromReference(interp->StratigraphicOccurrences[i]), "", interp->StratigraphicOccurrences[i]->UUID);
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

	if (interp->Structure != nullptr)
	{
		StructuralOrganizationInterpretation* structuralOrganizationInterp = static_cast<StructuralOrganizationInterpretation*>(epcDoc->getDataObjectByUuid(interp->Structure->UUID));
		if (structuralOrganizationInterp != nullptr)
			setStructuralOrganizationInterpretation(structuralOrganizationInterp);
	}

	if (interp->StratigraphicColumn != nullptr)
	{
		StratigraphicColumn* stratCol = static_cast<StratigraphicColumn*>(epcDoc->getDataObjectByUuid(interp->StratigraphicColumn->UUID));
		if (stratCol != nullptr)
			setStratiColumn(stratCol);
	}

	for (size_t i = 0; i < interp->StratigraphicOccurrences.size(); ++i)
	{
		pushBackStratiOccurence(static_cast<StratigraphicOccurrenceInterpretation*>(epcDoc->getDataObjectByUuid(interp->StratigraphicOccurrences[i]->UUID)));
	}

	updateXml = true;
}

bool EarthModelInterpretation::hasStratiColumn() const
{
	return static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicColumn != nullptr;
}

StratigraphicColumn* EarthModelInterpretation::getStratiColumn() const
{
	if (!hasStratiColumn()) {
		throw invalid_argument("There is no associated stratigraphic column");
	}

	return epcDocument->getDataObjectByUuid<StratigraphicColumn>(static_cast<_resqml2__EarthModelInterpretation*>(gsoapProxy2_0_1)->StratigraphicColumn->UUID);
}
