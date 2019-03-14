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
#include "resqml2_0_1/RockFluidOrganizationInterpretation.h"
#include <algorithm>

#include "tools/Misc.h"

using namespace std;
using namespace epc;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* RockFluidOrganizationInterpretation::XML_TAG = "RockFluidOrganizationInterpretation";

RockFluidOrganizationInterpretation::RockFluidOrganizationInterpretation(class OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	if (orgFeat != nullptr)
		throw invalid_argument("The interpreted organization feature cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORERockFluidOrganizationInterpretation(orgFeat->getGsoapContext(), 1);
	static_cast<_resqml2__RockFluidOrganizationInterpretation*>(gsoapProxy2_0_1)->RockFluidUnitIndex->Index = 0;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretedFeature(orgFeat);
}

ULONG64 RockFluidOrganizationInterpretation::getRockFluidUnitInterpretationIndex() const
{
	return static_cast<_resqml2__RockFluidOrganizationInterpretation*>(gsoapProxy2_0_1)->RockFluidUnitIndex->Index;
}

unsigned int RockFluidOrganizationInterpretation::getGridRepresentationCount() const
{
	return gridRepresentationSet.size();
}

RESQML2_NS::AbstractGridRepresentation* RockFluidOrganizationInterpretation::getGridRepresentation(unsigned int index) const
{
	if (index >= getGridRepresentationCount()) {
		throw range_error("The index of the grid representation to get is out of range.");
	}

	return gridRepresentationSet[index];
}

bool RockFluidOrganizationInterpretation::isAssociatedToGridRepresentation(RESQML2_NS::AbstractGridRepresentation* gridRep) const
{
	return find(gridRepresentationSet.begin(), gridRepresentationSet.end(), gridRep) != gridRepresentationSet.end();
}

vector<Relationship> RockFluidOrganizationInterpretation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractOrganizationInterpretation::getAllEpcRelationships();

	for (size_t i = 0; i < gridRepresentationSet.size(); ++i) {
		Relationship rel(gridRepresentationSet[i]->getPartNameInEpcDocument(), "", gridRepresentationSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	for (size_t i = 0; i < earthModelSet.size(); ++i)
	{
		Relationship rel(earthModelSet[i]->getPartNameInEpcDocument(), "", earthModelSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

void RockFluidOrganizationInterpretation::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	AbstractOrganizationInterpretation::importRelationshipSetFromEpc(epcDoc);
}
