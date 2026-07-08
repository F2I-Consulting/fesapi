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
#include "RockFluidUnitInterpretation.h"

#include "../resqml2/RockVolumeFeature.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* RockFluidUnitInterpretation::XML_NS = "resqml20";

RockFluidUnitInterpretation::RockFluidUnitInterpretation(RESQML2_NS::RockVolumeFeature * feature, const string & guid, const string & title)
{
	if (feature == nullptr) {
		throw invalid_argument("The interpreted feature cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORERockFluidUnitInterpretation(feature->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setInterpretedFeature(feature);
}

bool RockFluidUnitInterpretation::hasPhase() const
{
	return static_cast<_resqml20__RockFluidUnitInterpretation*>(gsoapProxy2_0_1)->Phase != nullptr;
}

gsoap_eml2_3::resqml22__Phase RockFluidUnitInterpretation::getPhase() const
{
	if (!hasPhase()) {
		throw logic_error("The rock fluid unit interpretation has not any phase.");
	}

	return static_cast<gsoap_eml2_3::resqml22__Phase>(*static_cast<_resqml20__RockFluidUnitInterpretation*>(gsoapProxy2_0_1)->Phase);
}

void RockFluidUnitInterpretation::setPhase(gsoap_eml2_3::resqml22__Phase phase) const
{
	static_cast<_resqml20__RockFluidUnitInterpretation*>(gsoapProxy2_0_1)->Phase = soap_new_resqml20__Phase(getGsoapContext());
	if (phase == gsoap_eml2_3::resqml22__Phase::aquifer) {
		*static_cast<_resqml20__RockFluidUnitInterpretation*>(gsoapProxy2_0_1)->Phase = resqml20__Phase::aquifer;
	}
	else if (phase == gsoap_eml2_3::resqml22__Phase::gas_x0020cap) {
		*static_cast<_resqml20__RockFluidUnitInterpretation*>(gsoapProxy2_0_1)->Phase = resqml20__Phase::gas_x0020cap;
	}
	else if (phase == gsoap_eml2_3::resqml22__Phase::oil_x0020column) {
		*static_cast<_resqml20__RockFluidUnitInterpretation*>(gsoapProxy2_0_1)->Phase = resqml20__Phase::oil_x0020column;
	}
}
