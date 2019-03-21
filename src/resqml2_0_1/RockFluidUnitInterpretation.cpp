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
#include "resqml2_0_1/RockFluidUnitInterpretation.h"
#include "resqml2_0_1/RockFluidUnitFeature.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* RockFluidUnitInterpretation::XML_TAG = "RockFluidUnitInterpretation";

RockFluidUnitInterpretation::RockFluidUnitInterpretation(RockFluidUnitFeature * feature, const string & guid, const string & title)
{
	if (feature == nullptr)
		throw invalid_argument("The interpreted feature cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORERockFluidUnitInterpretation(feature->getGsoapContext(), 1);
	//static_cast<_resqml2__RockFluidUnitInterpretation*>(gsoapProxy2_0_1)->Phase = ??;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretedFeature(feature);
}

vector<Relationship> RockFluidUnitInterpretation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractFeatureInterpretation::getAllEpcRelationships();

	for (size_t i = 0; i < rockFluidOrganizationInterpSet.size(); ++i)
	{
		if (rockFluidOrganizationInterpSet[i] != nullptr)
		{
			Relationship rel(rockFluidOrganizationInterpSet[i]->getPartNameInEpcDocument(), "", rockFluidOrganizationInterpSet[i]->getUuid());
			rel.setSourceObjectType();
			result.push_back(rel);
		}
		else
			throw domain_error("The rockFluidOrganization Interpretation associated to this interpretation cannot be nullptr.");
	}

	return result;
}

bool RockFluidUnitInterpretation::hasPhase() const
{
	return static_cast<_resqml2__RockFluidUnitInterpretation*>(gsoapProxy2_0_1)->Phase != nullptr;
}

gsoap_resqml2_0_1::resqml2__Phase RockFluidUnitInterpretation::getPhase() const
{
	if (hasPhase() == false)
		throw invalid_argument("The rock fluid unit interpretation has not any phase.");

	return *static_cast<_resqml2__RockFluidUnitInterpretation*>(gsoapProxy2_0_1)->Phase;
}

