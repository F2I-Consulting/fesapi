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
#include "Trajectory.h"

#include <limits>
#include <sstream>
#include <stdexcept>

#include "../witsml2/Wellbore.h"

#include "../tools/TimeTools.h"

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_3;

Trajectory::Trajectory(WITSML2_NS::Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title,
	bool isActive)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("A wellbore must be associated to a wellbore trajectory.");
	}

	gsoapProxy2_3 = soap_new_witsml21__Trajectory(witsmlWellbore->getGsoapContext());

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	static_cast<witsml21__Trajectory*>(gsoapProxy2_3)->ActiveStatus = isActive ? eml23__ActiveStatusKind::active : eml23__ActiveStatusKind::inactive;

	// Abstract MD Growing Object
	static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->Index = soap_new_eml23__GrowingObjectIndex(witsmlWellbore->getGsoapContext());
	static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->Index->IndexKind = eml23__DataIndexKind::measured_x0020depth;
	static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->Index->Direction = eml23__IndexDirection::increasing;
	static_cast<witsml21__WellboreGeometry*>(gsoapProxy2_3)->Index->Uom = "Euc"; //TODO

	witsmlWellbore->getRepository()->addDataObject(this);
	setWellbore(witsmlWellbore);
}

COMMON_NS::DataObjectReference Trajectory::getWellboreDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<witsml21__Trajectory*>(gsoapProxy2_3)->Wellbore);
}

void Trajectory::setWellbore(WITSML2_NS::Wellbore* witsmlWellbore)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("Cannot set a null witsml wellbore to a witsml trajectory");
	}

	static_cast<witsml21__Trajectory*>(gsoapProxy2_3)->Wellbore = witsmlWellbore->newEml23Reference();

	getRepository()->addRelationship(this, witsmlWellbore);
}

GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IMPL(Trajectory, DTimTrajStart)
GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IMPL(Trajectory, DTimTrajEnd)

GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(bool, Trajectory, Definitive, gsoap_eml2_3::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(bool, Trajectory, Memory, gsoap_eml2_3::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(bool, Trajectory, FinalTraj, gsoap_eml2_3::soap_new_bool)

void Trajectory::setAziRef(const gsoap_eml2_3::eml23__NorthReferenceKind & aziRef) {
	if (static_cast<witsml21__Trajectory*>(gsoapProxy2_3)->AziRef == nullptr) {
		static_cast<witsml21__Trajectory*>(gsoapProxy2_3)->AziRef = (gsoap_eml2_3::eml23__NorthReferenceKind*)soap_malloc(getGsoapContext(), sizeof(gsoap_eml2_3::eml23__NorthReferenceKind));
	}
	*static_cast<witsml21__Trajectory*>(gsoapProxy2_3)->AziRef = aziRef;
}
GETTER_PRESENCE_ATTRIBUTE_IMPL(Trajectory, AziRef)
gsoap_eml2_3::eml23__NorthReferenceKind Trajectory::getAziRef() const {
	CHECK_ATTRIBUTE_EXISTENCE(Trajectory, AziRef)
	return *static_cast<witsml21__Trajectory*>(gsoapProxy2_3)->AziRef;
}

//***************************************
// ******* TRAJECTORY STATIONS **********
//***************************************

// Mandatory
GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR_IMPL(std::string, Trajectory, TrajectoryStation, uid)
GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR_IMPL(gsoap_eml2_3::witsml21__TrajStationType, Trajectory, TrajectoryStation, TypeTrajStation)
GETTER_AND_SETTER_MEASURED_DEPTH_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, Md, gsoap_eml2_3::eml23__LengthUom, gsoap_eml2_3::soap_new_eml23__MeasuredDepth)
GETTER_AND_SETTER_TIME_T_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, Creation)
GETTER_AND_SETTER_TIME_T_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, LastUpdate)

// Optional bool
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, ManuallyEntered, gsoap_eml2_3::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, GravAccelCorUsed, gsoap_eml2_3::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, MagXAxialCorUsed, gsoap_eml2_3::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, SagCorUsed, gsoap_eml2_3::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, MagDrlstrCorUsed, gsoap_eml2_3::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, InfieldRefCorUsed, gsoap_eml2_3::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, InterpolatedInfieldRefCorUsed, gsoap_eml2_3::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, InHoleRefCorUsed, gsoap_eml2_3::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, AxialMagInterferenceCorUsed, gsoap_eml2_3::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, CosagCorUsed, gsoap_eml2_3::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(bool, Trajectory, TrajectoryStation, MSACorUsed, gsoap_eml2_3::soap_new_bool)

// Optional string
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(std::string, Trajectory, TrajectoryStation, MagModelUsed, gsoap_eml2_3::soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(std::string, Trajectory, TrajectoryStation, MagModelValid, gsoap_eml2_3::soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(std::string, Trajectory, TrajectoryStation, GeoModelUsed, gsoap_eml2_3::soap_new_std__string)

// Optional timestamp
GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, DTimStn)

// Optional enum
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(gsoap_eml2_3::witsml21__TypeSurveyTool, Trajectory, TrajectoryStation, TypeSurveyTool, gsoap_eml2_3::soap_new_witsml21__TypeSurveyTool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(gsoap_eml2_3::witsml21__TrajStnCalcAlgorithm, Trajectory, TrajectoryStation, CalcAlgorithm, gsoap_eml2_3::soap_new_witsml21__TrajStnCalcAlgorithm)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(gsoap_eml2_3::witsml21__TrajStationStatus, Trajectory, TrajectoryStation, StatusTrajStation, gsoap_eml2_3::soap_new_witsml21__TrajStationStatus)

// Optional Length Measure
void Trajectory::setTrajectoryStationTvd(uint64_t index, double value, gsoap_eml2_3::eml23__LengthUom uom) {
	if (value != value) { throw invalid_argument("You cannot set an undefined measured depth coord"); }
	CREATE_ATTRIBUTE_IN_VECTOR_IF_NOT_PRESENT(Trajectory, TrajectoryStation, Tvd, gsoap_eml2_3::soap_new_eml23__DatumVerticalDepth)
		if (static_cast<witsml21__Trajectory*>(gsoapProxy2_3)->TrajectoryStation[index]->Tvd->VerticalDepth == nullptr) {
			static_cast<witsml21__Trajectory*>(gsoapProxy2_3)->TrajectoryStation[index]->Tvd->VerticalDepth = gsoap_eml2_3::soap_new_eml23__LengthMeasureExt(gsoapProxy2_3->soap);
		}
	static_cast<witsml21__Trajectory*>(gsoapProxy2_3)->TrajectoryStation[index]->Tvd->VerticalDepth->__item = value; \
		static_cast<witsml21__Trajectory*>(gsoapProxy2_3)->TrajectoryStation[index]->Tvd->VerticalDepth->uom = gsoap_eml2_3::soap_eml23__LengthUom2s(gsoapProxy2_3->soap, uom); \
}
double Trajectory::getTrajectoryStationTvdValue(uint64_t index) const {
	CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE(Trajectory, TrajectoryStation, Tvd)
		return static_cast<witsml21__Trajectory*>(gsoapProxy2_3)->TrajectoryStation[index]->Tvd->VerticalDepth->__item;
}
eml23__LengthUom Trajectory::getTrajectoryStationTvdUom(uint64_t index) const {
	CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE(Trajectory, TrajectoryStation, Tvd)
		eml23__LengthUom result;
	gsoap_eml2_3::soap_s2eml23__LengthUom(gsoapProxy2_3->soap, static_cast<witsml21__Trajectory*>(gsoapProxy2_3)->TrajectoryStation[index]->Tvd->VerticalDepth->uom.c_str(), &result);
	return result;
}
GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, Tvd)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, DispNs, gsoap_eml2_3::eml23__LengthUom, gsoap_eml2_3::soap_new_eml23__LengthMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, DispEw, gsoap_eml2_3::eml23__LengthUom, gsoap_eml2_3::soap_new_eml23__LengthMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, VertSect, gsoap_eml2_3::eml23__LengthUom, gsoap_eml2_3::soap_new_eml23__LengthMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, MdDelta, gsoap_eml2_3::eml23__LengthUom, gsoap_eml2_3::soap_new_eml23__LengthMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, TvdDelta, gsoap_eml2_3::eml23__LengthUom, gsoap_eml2_3::soap_new_eml23__LengthMeasure)

// Optional Plane AngleMeasure
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, Incl, gsoap_eml2_3::eml23__PlaneAngleUom, gsoap_eml2_3::soap_new_eml23__PlaneAngleMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, Azi, gsoap_eml2_3::eml23__PlaneAngleUom, gsoap_eml2_3::soap_new_eml23__PlaneAngleMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, Mtf, gsoap_eml2_3::eml23__PlaneAngleUom, gsoap_eml2_3::soap_new_eml23__PlaneAngleMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, Gtf, gsoap_eml2_3::eml23__PlaneAngleUom, gsoap_eml2_3::soap_new_eml23__PlaneAngleMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, DipAngleUncert, gsoap_eml2_3::eml23__PlaneAngleUom, gsoap_eml2_3::soap_new_eml23__PlaneAngleMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, MagDipAngleReference, gsoap_eml2_3::eml23__PlaneAngleUom, gsoap_eml2_3::soap_new_eml23__PlaneAngleMeasure)

// Optional Plane AngleMeasure
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, Dls, gsoap_eml2_3::eml23__AnglePerLengthUom, gsoap_eml2_3::soap_new_eml23__AnglePerLengthMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, RateTurn, gsoap_eml2_3::eml23__AnglePerLengthUom, gsoap_eml2_3::soap_new_eml23__AnglePerLengthMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, RateBuild, gsoap_eml2_3::eml23__AnglePerLengthUom, gsoap_eml2_3::soap_new_eml23__AnglePerLengthMeasure)

// Optional Linear Acceleration Measure
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, GravTotalUncert, gsoap_eml2_3::eml23__LinearAccelerationUom, gsoap_eml2_3::soap_new_eml23__LinearAccelerationMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, GravTotalFieldReference, gsoap_eml2_3::eml23__LinearAccelerationUom, gsoap_eml2_3::soap_new_eml23__LinearAccelerationMeasure)

// Optional Magnetic Flux Density Measure
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, MagTotalUncert, gsoap_eml2_3::eml23__MagneticFluxDensityUom, gsoap_eml2_3::soap_new_eml23__MagneticFluxDensityMeasure)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(Trajectory, TrajectoryStation, MagTotalFieldReference, gsoap_eml2_3::eml23__MagneticFluxDensityUom, gsoap_eml2_3::soap_new_eml23__MagneticFluxDensityMeasure)

void Trajectory::pushBackTrajectoryStation(gsoap_eml2_3::witsml21__TrajStationType kind, double mdValue, gsoap_eml2_3::eml23__LengthUom uom, const std::string & uid)
{
	static_cast<witsml21__Trajectory*>(gsoapProxy2_3)->TrajectoryStation.push_back(gsoap_eml2_3::soap_new_witsml21__TrajectoryStation(gsoapProxy2_3->soap));
	uint64_t index = getTrajectoryStationCount() - 1;
	setTrajectoryStationuid(index, uid.empty() ? std::to_string(index) : uid);

	setTrajectoryStationTypeTrajStation(index, kind);
	setTrajectoryStationMd(index, mdValue, uom);
	setTrajectoryStationCreation(index, 0);
	setTrajectoryStationLastUpdate(index, 0);
}

uint64_t Trajectory::getTrajectoryStationCount() const noexcept
{
	return static_cast<witsml21__Trajectory*>(gsoapProxy2_3)->TrajectoryStation.size();
}
