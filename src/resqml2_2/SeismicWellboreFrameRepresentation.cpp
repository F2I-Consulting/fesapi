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
#include "resqml2_2/SeismicWellboreFrameRepresentation.h"

#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_2;

const char* SeismicWellboreFrameRepresentation::XML_TAG = "SeismicWellboreFrameRepresentation";

SeismicWellboreFrameRepresentation::SeismicWellboreFrameRepresentation(RESQML2_0_1_NS::WellboreInterpretation* interp, const string& guid, const std::string& title, RESQML2_0_1_NS::WellboreTrajectoryRepresentation* traj)
{
	gsoapProxy2_2 = soap_new_resqml22__SeismicWellboreFrameRepresentation(interp->getGsoapContext());
	_resqml22__SeismicWellboreFrameRepresentation* frame = static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_2);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretation(interp);

	frame->Trajectory = traj->newEml22Reference();
	getRepository()->addRelationship(this, traj);
}