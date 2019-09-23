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

#include <sstream>
#include <stdexcept>

#include "witsml2_0/Wellbore.h"

#include "tools/TimeTools.h"

using namespace std;
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;

const char* Trajectory::XML_TAG = "Trajectory";

Trajectory::Trajectory(Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title,
	gsoap_eml2_1::witsml20__ChannelStatus channelStatus)
{
	if (witsmlWellbore == nullptr) throw invalid_argument("A wellbore must be associated to a wellbore trajectory.");

	gsoapProxy2_1 = soap_new_witsml20__Trajectory(witsmlWellbore->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setWellbore(witsmlWellbore);

	static_cast<witsml20__Trajectory*>(gsoapProxy2_1)->GrowingStatus = channelStatus;
}

gsoap_eml2_1::eml21__DataObjectReference* Trajectory::getWellboreDor() const
{
	return static_cast<witsml20__Trajectory*>(gsoapProxy2_1)->Wellbore;
}

void Trajectory::setWellbore(Wellbore* witsmlWellbore)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("Cannot set a null witsml wellbore to a witsml trajectory");
	}
	if (getRepository() == nullptr) {
		witsmlWellbore->getRepository()->addOrReplaceDataObject(this);
	}

	getRepository()->addRelationship(this, witsmlWellbore);

	static_cast<witsml20__Trajectory*>(gsoapProxy2_1)->Wellbore = witsmlWellbore->newEmlReference();
}

GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IMPL(gsoap_eml2_1::witsml20__ChannelStatus, Trajectory, GrowingStatus)

GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IMPL(Trajectory, DTimTrajStart)
GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IMPL(Trajectory, DTimTrajEnd)

GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(Trajectory, MdMn, eml21__LengthUom, gsoap_eml2_1::soap_new_witsml20__MeasuredDepthCoord)
GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(Trajectory, MdMx, eml21__LengthUom, gsoap_eml2_1::soap_new_witsml20__MeasuredDepthCoord)

GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(std::string, Trajectory, ServiceCompany, gsoap_eml2_1::soap_new_std__string)

GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(Trajectory, MagDeclUsed, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_eml2_1::soap_new_eml21__PlaneAngleMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(Trajectory, GridConUsed, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_eml2_1::soap_new_eml21__PlaneAngleMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(Trajectory, AziVertSect, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_eml2_1::soap_new_eml21__PlaneAngleMeasure)

GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(Trajectory, DispNsVertSectOrig, eml21__LengthUom, gsoap_eml2_1::soap_new_eml21__LengthMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(Trajectory, DispEwVertSectOrig, eml21__LengthUom, gsoap_eml2_1::soap_new_eml21__LengthMeasure)

GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(bool, Trajectory, Definitive, gsoap_eml2_1::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(bool, Trajectory, Memory, gsoap_eml2_1::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(bool, Trajectory, FinalTraj, gsoap_eml2_1::soap_new_bool)

GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(gsoap_eml2_1::witsml20__AziRef, Trajectory, AziRef, gsoap_eml2_1::soap_new_witsml20__AziRef)

//***************************************
// ******* TRAJECTORY STATIONS **********
//***************************************

// Mandatory
GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR_IMPL(std::string, Trajectory, TrajectoryStation, uid)
GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR_IMPL(gsoap_eml2_1::witsml20__TrajStationType, Trajectory, TrajectoryStation, TypeTrajStation)
GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, Md, gsoap_eml2_1::eml21__LengthUom, gsoap_eml2_1::soap_new_witsml20__MeasuredDepthCoord)

// Optional bool
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, ManuallyEntered, gsoap_eml2_1::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, GravAccelCorUsed, gsoap_eml2_1::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, MagXAxialCorUsed, gsoap_eml2_1::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, SagCorUsed, gsoap_eml2_1::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, MagDrlstrCorUsed, gsoap_eml2_1::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, InfieldRefCorUsed, gsoap_eml2_1::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, InterpolatedInfieldRefCorUsed, gsoap_eml2_1::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, InHoleRefCorUsed, gsoap_eml2_1::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, AxialMagInterferenceCorUsed, gsoap_eml2_1::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, CosagCorUsed, gsoap_eml2_1::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, MSACorUsed, gsoap_eml2_1::soap_new_bool)

// Optional string
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(std::string, Trajectory, TrajectoryStation, Target, gsoap_eml2_1::soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(std::string, Trajectory, TrajectoryStation, MagModelUsed, gsoap_eml2_1::soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(std::string, Trajectory, TrajectoryStation, MagModelValid, gsoap_eml2_1::soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(std::string, Trajectory, TrajectoryStation, GeoModelUsed, gsoap_eml2_1::soap_new_std__string)

// Optional timestamp
GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, DTimStn)

// Optional enum
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(gsoap_eml2_1::witsml20__TypeSurveyTool, Trajectory, TrajectoryStation, TypeSurveyTool, gsoap_eml2_1::soap_new_witsml20__TypeSurveyTool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(gsoap_eml2_1::witsml20__TrajStnCalcAlgorithm, Trajectory, TrajectoryStation, CalcAlgorithm, gsoap_eml2_1::soap_new_witsml20__TrajStnCalcAlgorithm)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(gsoap_eml2_1::witsml20__TrajStationStatus, Trajectory, TrajectoryStation, StatusTrajStation, gsoap_eml2_1::soap_new_witsml20__TrajStationStatus)

// Optional Length Measure
GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, Tvd, gsoap_eml2_1::eml21__LengthUom, gsoap_eml2_1::soap_new_witsml20__WellVerticalDepthCoord)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, DispNs, gsoap_eml2_1::eml21__LengthUom, gsoap_eml2_1::soap_new_eml21__LengthMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, DispEw, gsoap_eml2_1::eml21__LengthUom, gsoap_eml2_1::soap_new_eml21__LengthMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, VertSect, gsoap_eml2_1::eml21__LengthUom, gsoap_eml2_1::soap_new_eml21__LengthMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, MdDelta, gsoap_eml2_1::eml21__LengthUom, gsoap_eml2_1::soap_new_eml21__LengthMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, TvdDelta, gsoap_eml2_1::eml21__LengthUom, gsoap_eml2_1::soap_new_eml21__LengthMeasure)

// Optional Plane AngleMeasure
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, Incl, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_eml2_1::soap_new_eml21__PlaneAngleMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, Azi, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_eml2_1::soap_new_eml21__PlaneAngleMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, Mtf, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_eml2_1::soap_new_eml21__PlaneAngleMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, Gtf, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_eml2_1::soap_new_eml21__PlaneAngleMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, DipAngleUncert, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_eml2_1::soap_new_eml21__PlaneAngleMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, MagDipAngleReference, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_eml2_1::soap_new_eml21__PlaneAngleMeasure)

// Optional Plane AngleMeasure
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, Dls, gsoap_eml2_1::eml21__AnglePerLengthUom, gsoap_eml2_1::soap_new_eml21__AnglePerLengthMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, RateTurn, gsoap_eml2_1::eml21__AnglePerLengthUom, gsoap_eml2_1::soap_new_eml21__AnglePerLengthMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, RateBuild, gsoap_eml2_1::eml21__AnglePerLengthUom, gsoap_eml2_1::soap_new_eml21__AnglePerLengthMeasure)

// Optional Linear Acceleration Measure
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, GravTotalUncert, gsoap_eml2_1::eml21__LinearAccelerationUom, gsoap_eml2_1::soap_new_eml21__LinearAccelerationMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, GravTotalFieldReference, gsoap_eml2_1::eml21__LinearAccelerationUom, gsoap_eml2_1::soap_new_eml21__LinearAccelerationMeasure)

// Optional Magnetic Flux Density Measure
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, MagTotalUncert, gsoap_eml2_1::eml21__MagneticFluxDensityUom, gsoap_eml2_1::soap_new_eml21__MagneticFluxDensityMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, MagTotalFieldReference, gsoap_eml2_1::eml21__MagneticFluxDensityUom, gsoap_eml2_1::soap_new_eml21__MagneticFluxDensityMeasure)

void Trajectory::pushBackTrajectoryStation(gsoap_eml2_1::witsml20__TrajStationType kind, double mdValue, gsoap_eml2_1::eml21__LengthUom uom, const std::string & datum, const std::string & uid)
{
	static_cast<witsml20__Trajectory*>(gsoapProxy2_1)->TrajectoryStation.push_back(gsoap_eml2_1::soap_new_witsml20__TrajectoryStation(gsoapProxy2_1->soap, 1));
	unsigned int index = getTrajectoryStationCount() - 1;
	if (uid.empty()) {
		std::ostringstream oss;
		oss << index;
		setTrajectoryStationuid(index, oss.str());
	}
	else {
		setTrajectoryStationuid(index, uid);
	}

	setTrajectoryStationTypeTrajStation(index, kind);
	setTrajectoryStationMd(index, mdValue, uom, datum);
}

unsigned int Trajectory::getTrajectoryStationCount() const
{
	const size_t count = static_cast<witsml20__Trajectory*>(gsoapProxy2_1)->TrajectoryStation.size();
	if (count >= (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("Too much trajectory stations");
	}

	return static_cast<unsigned int>(count);
}
