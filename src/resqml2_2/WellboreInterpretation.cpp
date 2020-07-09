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
#include "WellboreInterpretation.h"

#include "../resqml2/WellboreFeature.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* WellboreInterpretation::XML_NS = "resqml22";

WellboreInterpretation::WellboreInterpretation(RESQML2_NS::WellboreFeature * wellboreFeature, const string & guid, const string & title, bool isDrilled)
{
	if (wellboreFeature == nullptr) {
		throw invalid_argument("The interpreted wellbore cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__WellboreInterpretation(wellboreFeature->getGsoapContext());
	_resqml22__WellboreInterpretation* wbInterp = static_cast<_resqml22__WellboreInterpretation*>(gsoapProxy2_3);

	wbInterp->IsDrilled = isDrilled;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setInterpretedFeature(wellboreFeature);
}

bool WellboreInterpretation::isDrilled() const
{
	return static_cast<_resqml22__WellboreInterpretation*>(gsoapProxy2_3)->IsDrilled;
}
