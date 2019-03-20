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
#include "witsml2_0/Trajectory.h"

#include "witsml2_0/Wellbore.h"

#include "tools/TimeTools.h"

using namespace std;
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;

const char* Trajectory::XML_TAG = "Trajectory";

Trajectory::Trajectory(Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title,
	gsoap_eml2_1::witsml2__ChannelStatus channelStatus)
{
	if (witsmlWellbore == nullptr) throw invalid_argument("A wellbore must be associated to a wellbore trajectory.");

	gsoapProxy2_1 = soap_new_witsml2__Trajectory(witsmlWellbore->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setWellbore(witsmlWellbore);

	static_cast<witsml2__Trajectory*>(gsoapProxy2_1)->GrowingStatus = channelStatus;
}

gsoap_eml2_1::eml21__DataObjectReference* Trajectory::getWellboreDor() const
{
	return static_cast<witsml2__Trajectory*>(gsoapProxy2_1)->Wellbore;
}

void Trajectory::setWellbore(Wellbore* witsmlWellbore)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("Cannot set a null witsml wellbore to a witsml trajectory");
	}

	// EPC
	witsmlWellbore->trajectorySet.push_back(this);

	// XML
	if (updateXml) {
		static_cast<witsml2__Trajectory*>(gsoapProxy2_1)->Wellbore = witsmlWellbore->newEmlReference();
	}
}

GETTER_AND_SETTER_TIME_T_ATTRIBUTE_IMPL(Trajectory, DTimTrajStart)
GETTER_AND_SETTER_TIME_T_ATTRIBUTE_IMPL(Trajectory, DTimTrajEnd)

GETTER_AND_SETTER_MEASURED_DEPTH_COORD_ATTRIBUTE_IMPL(Trajectory, MdMn)
GETTER_AND_SETTER_MEASURED_DEPTH_COORD_ATTRIBUTE_IMPL(Trajectory, MdMx)

GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Trajectory, ServiceCompany, soap_new_std__string)

GETTER_AND_SETTER_PLANE_ANGLE_MEASURE_ATTRIBUTE_IMPL(Trajectory, MagDeclUsed)
GETTER_AND_SETTER_PLANE_ANGLE_MEASURE_ATTRIBUTE_IMPL(Trajectory, GridConUsed)
GETTER_AND_SETTER_PLANE_ANGLE_MEASURE_ATTRIBUTE_IMPL(Trajectory, AziVertSect)

GETTER_AND_SETTER_LENGTH_MEASURE_ATTRIBUTE_IMPL(Trajectory, DispNsVertSectOrig)
GETTER_AND_SETTER_LENGTH_MEASURE_ATTRIBUTE_IMPL(Trajectory, DispEwVertSectOrig)

GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(bool, Trajectory, Definitive, gsoap_eml2_1::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(bool, Trajectory, Memory, gsoap_eml2_1::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(bool, Trajectory, FinalTraj, gsoap_eml2_1::soap_new_bool)

GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(gsoap_eml2_1::witsml2__AziRef, Trajectory, AziRef, gsoap_eml2_1::soap_new_witsml2__AziRef)
