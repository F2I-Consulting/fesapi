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
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

RockFluidUnitInterpretation::RockFluidUnitInterpretation(RESQML2_NS::RockVolumeFeature * feature, const string & guid, const string & title)
{
	if (feature == nullptr) {
		throw invalid_argument("The interpreted feature cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__RockFluidUnitInterpretation(feature->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setInterpretedFeature(feature);
}

bool RockFluidUnitInterpretation::hasPhase() const
{
	return static_cast<_resqml22__RockFluidUnitInterpretation*>(gsoapProxy2_3)->Phase != nullptr;
}

gsoap_eml2_3::resqml22__Phase RockFluidUnitInterpretation::getPhase() const
{
	if (!hasPhase()) {
		throw logic_error("The rock fluid unit interpretation has not any phase.");
	}

	return *static_cast<_resqml22__RockFluidUnitInterpretation*>(gsoapProxy2_3)->Phase;
}
