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
#include "SeismicWellboreFrameRepresentation.h"

#include "../resqml2/LocalTime3dCrs.h"
#include "../resqml2/WellboreInterpretation.h"
#include "../resqml2/WellboreTrajectoryRepresentation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* SeismicWellboreFrameRepresentation::XML_NS = "resqml22";

SeismicWellboreFrameRepresentation::SeismicWellboreFrameRepresentation(
	RESQML2_NS::WellboreInterpretation* interp,
	const std::string& guid, const std::string& title,
	RESQML2_NS::WellboreTrajectoryRepresentation* traj,
	double seismicReferenceDatum,
	double weatheringVelocity,
	RESQML2_NS::LocalTime3dCrs* crs)
{
	if (interp == nullptr) {
		throw invalid_argument("The wellbore interpretation cannot be null.");
	}
	if (traj == nullptr) {
		throw invalid_argument("The trajectory cannot be null.");
	}
	if (crs == nullptr) {
		throw invalid_argument("The local time crs cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__SeismicWellboreFrameRepresentation(interp->getGsoapContext());
	_resqml22__SeismicWellboreFrameRepresentation* frame = static_cast<_resqml22__SeismicWellboreFrameRepresentation*>(gsoapProxy2_3);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretation(interp);

	frame->Trajectory = traj->newEml23Reference();
	getRepository()->addRelationship(this, traj);

	frame->SeismicReferenceDatum = seismicReferenceDatum;

	frame->WeatheringVelocity = weatheringVelocity;

	frame->LocalTime3dCrs = crs->newEml23Reference();
	getRepository()->addRelationship(this, crs);
}
