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
#include "RockFluidOrganizationInterpretation.h"

#include "../resqml2/Model.h"
#include "../resqml2/RockFluidUnitInterpretation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* RockFluidOrganizationInterpretation::XML_TAG = "RockFluidOrganizationInterpretation";
const char* RockFluidOrganizationInterpretation::XML_NS = "resqml22";

RockFluidOrganizationInterpretation::RockFluidOrganizationInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title)
{
	if (orgFeat == nullptr) {
		throw invalid_argument("The interpreted organization feature cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__RockFluidOrganizationInterpretation(orgFeat->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	orgFeat->getRepository()->addDataObject(this);
	setInterpretedFeature(orgFeat);
}

void RockFluidOrganizationInterpretation::pushBackRockFluidUnitInterpretation(RESQML2_NS::RockFluidUnitInterpretation * rockFluidUnitInterpretation)
{
	if (rockFluidUnitInterpretation == nullptr) {
		throw invalid_argument("The rock fluid unit interpretation cannot be null.");
	}

	static_cast<_resqml22__RockFluidOrganizationInterpretation*>(gsoapProxy2_3)->RockFluidUnit.push_back(rockFluidUnitInterpretation->newEml23Reference());
}

unsigned int RockFluidOrganizationInterpretation::getRockFluidUnitInterpCount() const
{
	return static_cast<_resqml22__RockFluidOrganizationInterpretation*>(gsoapProxy2_3)->RockFluidUnit.size();
}

COMMON_NS::DataObjectReference RockFluidOrganizationInterpretation::getRockFluidUnitInterpretationDor(unsigned int index) const
{
	if (index >= getRockFluidUnitInterpCount()) {
		throw out_of_range("The index is out of range");
	}

	return COMMON_NS::DataObjectReference(static_cast<_resqml22__RockFluidOrganizationInterpretation*>(gsoapProxy2_3)->RockFluidUnit[index]);
}
