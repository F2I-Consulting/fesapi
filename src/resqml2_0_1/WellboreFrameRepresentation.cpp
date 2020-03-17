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
#include "WellboreFrameRepresentation.h"

#include "WellboreInterpretation.h"
#include "WellboreTrajectoryRepresentation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* WellboreFrameRepresentation::XML_TAG = "WellboreFrameRepresentation";

WellboreFrameRepresentation::WellboreFrameRepresentation(WellboreInterpretation* interp, const string& guid, const std::string& title, WellboreTrajectoryRepresentation* traj)
{
	if (interp == nullptr) {
		throw invalid_argument("The wellbore interpretation this wellbore frame represents cannot be null.");
	}
	if (traj == nullptr) {
		throw invalid_argument("The wellbore trajectory representation cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREWellboreFrameRepresentation(interp->getGsoapContext());
	_resqml20__WellboreFrameRepresentation* frame = static_cast<_resqml20__WellboreFrameRepresentation*>(gsoapProxy2_0_1);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretation(interp);

	frame->Trajectory = traj->newResqmlReference();
	getRepository()->addRelationship(this, traj);
}
