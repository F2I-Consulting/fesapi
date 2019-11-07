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

#include "WellboreFeature.h"
#include "WellboreTrajectoryRepresentation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* WellboreInterpretation::XML_TAG = "WellboreInterpretation";

const char* WellboreInterpretation::XML_NS = "resqml20";

WellboreInterpretation::WellboreInterpretation(WellboreFeature * WellboreFeature, const string & guid, const string & title, bool isDrilled)
{
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREWellboreInterpretation(WellboreFeature->getGsoapContext());
	_resqml20__WellboreInterpretation* wbInterp = static_cast<_resqml20__WellboreInterpretation*>(gsoapProxy2_0_1);
	wbInterp->Domain = resqml20__Domain__mixed;

	wbInterp->IsDrilled = isDrilled;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setInterpretedFeature(WellboreFeature);
}

bool WellboreInterpretation::isDrilled() const
{
	return static_cast<_resqml20__WellboreInterpretation*>(gsoapProxy2_0_1)->IsDrilled;
}

std::vector<WellboreTrajectoryRepresentation*> WellboreInterpretation::getWellboreTrajectoryRepresentationSet() const
{
	return getRepository()->getSourceObjects<WellboreTrajectoryRepresentation>(this);
}
