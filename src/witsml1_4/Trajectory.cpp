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

#include "../witsml2/Well.h"
#include "../witsml2/Wellbore.h"

#include "../tools/TimeTools.h"

#include "MacroDefinitions_witsm14.h"

using namespace std;
using namespace WITSML1_4_NS;
using namespace gsoap_witsml1_4;

COMMON_NS::DataObjectReference Trajectory::getWellboreDor() const
{
	auto* dor = gsoap_resqml2_0_1::soap_new_eml20__DataObjectReference(gsoapProxyTraj1_4->soap);
	dor->ContentType = "application/x-witsml+xml;version=1.4;type=obj_trajectory";
	dor->UUID = static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->uidWellbore != nullptr
		? *static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->uidWellbore
		: static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->nameWellbore;
	dor->Title = static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->nameWellbore;
	return COMMON_NS::DataObjectReference(dor);
}

void Trajectory::setWellbore(WITSML2_NS::Wellbore* witsmlWellbore)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("Cannot set a null witsml wellbore to a witsml trajectory");
	}
	if (getRepository() == nullptr) {
		witsmlWellbore->getRepository()->addOrReplaceDataObject(this);
	}

	// Wellbore
	static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->uidWellbore = soap_new_std__string(gsoapProxyTraj1_4->soap);
	static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->uidWellbore->assign(witsmlWellbore->getUuid());
	static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->nameWellbore = witsmlWellbore->getTitle();

	// Well from Wellbore
	WITSML2_NS::Well* well = witsmlWellbore->getWell();
	static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->uidWell = soap_new_std__string(gsoapProxyTraj1_4->soap);
	static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->uidWell->assign(well->getUuid());
	static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->nameWell = well->getTitle();


	getRepository()->addRelationship(this, witsmlWellbore);
}

void Trajectory::setGrowingStatus(const gsoap_eml2_1::witsml20__ChannelStatus & value)
{
	if (static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence == nullptr) {
		static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence = soap_new___witsml14__obj_USCOREtrajectory_sequence(gsoapProxyTraj1_4->soap);
	}
	if (static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->objectGrowing == nullptr) {
		static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->objectGrowing = soap_new_bool(gsoapProxyTraj1_4->soap);
	}
	*static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->objectGrowing = (value == gsoap_eml2_1::witsml20__ChannelStatus::active);
}
gsoap_eml2_1::witsml20__ChannelStatus Trajectory::getGrowingStatus() const
{
	if (static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence == nullptr ||
		static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->objectGrowing == nullptr) {
		return gsoap_eml2_1::witsml20__ChannelStatus::inactive;
	}

	return *static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->objectGrowing
		? gsoap_eml2_1::witsml20__ChannelStatus::active
		: gsoap_eml2_1::witsml20__ChannelStatus::inactive;
}

GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IMPL_1_4(Trajectory, DTimTrajStart, dTimTrajStart)
GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IMPL_1_4(Trajectory, DTimTrajEnd, dTimTrajEnd)

GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IMPL_1_4(Trajectory, MdMn, mdMn, gsoap_eml2_1::eml21__LengthUom, gsoap_witsml1_4::soap_new_witsml14__measuredDepthCoord)
GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IMPL_1_4(Trajectory, MdMx, mdMx, gsoap_eml2_1::eml21__LengthUom, gsoap_witsml1_4::soap_new_witsml14__measuredDepthCoord)

GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL_1_4(std::string, Trajectory, ServiceCompany, serviceCompany, gsoap_witsml1_4::soap_new_std__string)

GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL_1_4(Trajectory, MagDeclUsed, magDeclUsed, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_witsml1_4::witsml14__PlaneAngleUom, gsoap_witsml1_4::soap_new_witsml14__planeAngleMeasure,
	gsoap_eml2_1::soap_eml21__PlaneAngleUom2s, gsoap_eml2_1::soap_s2eml21__PlaneAngleUom, gsoap_witsml1_4::soap_witsml14__PlaneAngleUom2s, gsoap_witsml1_4::soap_s2witsml14__PlaneAngleUom)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL_1_4(Trajectory, GridConUsed, gridConUsed, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_witsml1_4::witsml14__PlaneAngleUom, gsoap_witsml1_4::soap_new_witsml14__planeAngleMeasure,
	gsoap_eml2_1::soap_eml21__PlaneAngleUom2s, gsoap_eml2_1::soap_s2eml21__PlaneAngleUom, gsoap_witsml1_4::soap_witsml14__PlaneAngleUom2s, gsoap_witsml1_4::soap_s2witsml14__PlaneAngleUom)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL_1_4(Trajectory, AziVertSect, aziVertSect, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_witsml1_4::witsml14__PlaneAngleUom, gsoap_witsml1_4::soap_new_witsml14__planeAngleMeasure,
	gsoap_eml2_1::soap_eml21__PlaneAngleUom2s, gsoap_eml2_1::soap_s2eml21__PlaneAngleUom, gsoap_witsml1_4::soap_witsml14__PlaneAngleUom2s, gsoap_witsml1_4::soap_s2witsml14__PlaneAngleUom)

GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL_1_4(Trajectory, DispNsVertSectOrig, dispNsVertSectOrig, gsoap_eml2_1::eml21__LengthUom, gsoap_witsml1_4::witsml14__LengthUom, gsoap_witsml1_4::soap_new_witsml14__lengthMeasure,
	gsoap_eml2_1::soap_eml21__LengthUom2s, gsoap_eml2_1::soap_s2eml21__LengthUom, gsoap_witsml1_4::soap_witsml14__LengthUom2s, gsoap_witsml1_4::soap_s2witsml14__LengthUom)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL_1_4(Trajectory, DispEwVertSectOrig, dispEwVertSectOrig, gsoap_eml2_1::eml21__LengthUom, gsoap_witsml1_4::witsml14__LengthUom, gsoap_witsml1_4::soap_new_witsml14__lengthMeasure,
	gsoap_eml2_1::soap_eml21__LengthUom2s, gsoap_eml2_1::soap_s2eml21__LengthUom, gsoap_witsml1_4::soap_witsml14__LengthUom2s, gsoap_witsml1_4::soap_s2witsml14__LengthUom)

GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL_1_4(bool, Trajectory, Definitive, definitive, gsoap_witsml1_4::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL_1_4(bool, Trajectory, Memory, memory, gsoap_witsml1_4::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL_1_4(bool, Trajectory, FinalTraj, finalTraj, gsoap_witsml1_4::soap_new_bool)

GETTER_AND_SETTER_ENUM_OPTIONAL_ATTRIBUTE_IMPL_1_4(gsoap_eml2_1::witsml20__AziRef, gsoap_witsml1_4::witsml14__AziRef, Trajectory, AziRef, aziRef, gsoap_witsml1_4::soap_new_witsml14__AziRef,
	gsoap_eml2_1::soap_witsml20__AziRef2s, gsoap_eml2_1::soap_s2witsml20__AziRef, gsoap_witsml1_4::soap_witsml14__AziRef2s, gsoap_witsml1_4::soap_s2witsml14__AziRef)

//***************************************
// ******* TRAJECTORY STATIONS **********
//***************************************

void Trajectory::setTrajectoryStationuid(unsigned int index, const std::string & value)
{
	CHECK_RANGE_1_4(trajectoryStation, index)
	static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->uid = soap_new_std__string(gsoapProxyTraj1_4->soap);
	static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->uid->assign(value);
}
std::string Trajectory::getTrajectoryStationuid(unsigned int index) const {
	CHECK_RANGE_1_4(trajectoryStation, index)
		return static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->uid == nullptr
		? ""
		: *static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->uid;
}

// Mandatory
GETTER_AND_SETTER_ENUM_ATTRIBUTE_IN_VECTOR_IMPL_1_4(gsoap_eml2_1::witsml20__TrajStationType, gsoap_witsml1_4::witsml14__TrajStationType, Trajectory, TrajectoryStation, trajectoryStation, TypeTrajStation, typeTrajStation,
	gsoap_eml2_1::soap_witsml20__TrajStationType2s, gsoap_eml2_1::soap_s2witsml20__TrajStationType, gsoap_witsml1_4::soap_witsml14__TrajStationType2s, gsoap_witsml1_4::soap_s2witsml14__TrajStationType)
GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, Md, md, gsoap_eml2_1::eml21__LengthUom, gsoap_witsml1_4::soap_new_witsml14__measuredDepthCoord)

void Trajectory::setTrajectoryStationManuallyEntered(unsigned int index, const bool & value) {
	throw logic_error("WITSML1.4.1.1 has not this kinf of information");
}

bool Trajectory::hasTrajectoryStationManuallyEntered(unsigned int index) const { return false; }

bool Trajectory::getTrajectoryStationManuallyEntered(unsigned int index) const {
	throw logic_error("WITSML1.4.1.1 has not this kind of information");
}

// Optional bool
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(bool, Trajectory, TrajectoryStation, trajectoryStation, GravAccelCorUsed, gravAccelCorUsed, gsoap_witsml1_4::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(bool, Trajectory, TrajectoryStation, trajectoryStation, MagXAxialCorUsed, magXAxialCorUsed, gsoap_witsml1_4::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(bool, Trajectory, TrajectoryStation, trajectoryStation, SagCorUsed, sagCorUsed, gsoap_witsml1_4::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(bool, Trajectory, TrajectoryStation, trajectoryStation, MagDrlstrCorUsed, magDrlstrCorUsed, gsoap_witsml1_4::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(bool, Trajectory, TrajectoryStation, trajectoryStation, InfieldRefCorUsed, infieldRefCorUsed, gsoap_witsml1_4::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(bool, Trajectory, TrajectoryStation, trajectoryStation, InterpolatedInfieldRefCorUsed, interpolatedInfieldRefCorUsed, gsoap_witsml1_4::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(bool, Trajectory, TrajectoryStation, trajectoryStation, InHoleRefCorUsed, inHoleRefCorUsed, gsoap_witsml1_4::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(bool, Trajectory, TrajectoryStation, trajectoryStation, AxialMagInterferenceCorUsed, axialMagInterferenceCorUsed, gsoap_witsml1_4::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(bool, Trajectory, TrajectoryStation, trajectoryStation, CosagCorUsed, cosagCorUsed, gsoap_witsml1_4::soap_new_bool)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(bool, Trajectory, TrajectoryStation, trajectoryStation, MSACorUsed, MSACorUsed, gsoap_witsml1_4::soap_new_bool)

// Optional string
void Trajectory::setTrajectoryStationTarget(unsigned int index, const std::string & value) {
	CREATE_ATTRIBUTE_IN_VECTOR_IF_NOT_PRESENT_1_4(trajectoryStation, target, gsoap_witsml1_4::soap_new_witsml14__refNameString)
	static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->target->__item = value;
}
GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, Target, target)
std::string Trajectory::getTrajectoryStationTarget(unsigned int index) const {
	CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE_1_4(Trajectory, trajectoryStation, target)
	return static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->target->__item;
}
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(std::string, Trajectory, TrajectoryStation, trajectoryStation, MagModelUsed, magModelUsed, gsoap_witsml1_4::soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(std::string, Trajectory, TrajectoryStation, trajectoryStation, MagModelValid, magModelValid, gsoap_witsml1_4::soap_new_std__string)
GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(std::string, Trajectory, TrajectoryStation, trajectoryStation, GeoModelUsed, geoModelUsed, gsoap_witsml1_4::soap_new_std__string)

// Optional timestamp
void Trajectory::setTrajectoryStationDTimStn(unsigned int index, const time_t & attributeName) {
	CHECK_RANGE_1_4(trajectoryStation, index)
	if (static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->dTimStn == nullptr) {
		static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->dTimStn = (tm*)soap_malloc(gsoapProxyTraj1_4->soap, sizeof(tm));
	}
	std::tm tmConversion = timeTools::to_calendar_time(std::chrono::system_clock::from_time_t(attributeName));
	*static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->dTimStn = tmConversion;
}
GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, DTimStn, dTimStn)
time_t Trajectory::getTrajectoryStationDTimStn(unsigned int index) const {
	CHECK_RANGE_1_4(trajectoryStation, index)
	CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE_1_4(Trajectory, trajectoryStation, dTimStn)
	return timeTools::timegm(*static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->dTimStn);
}

// Optional enum
void Trajectory::setTrajectoryStationTypeSurveyTool(unsigned int index, const gsoap_eml2_1::witsml20__TypeSurveyTool & attributeName) {
	CREATE_ATTRIBUTE_IN_VECTOR_IF_NOT_PRESENT_1_4(trajectoryStation, typeSurveyTool, gsoap_witsml1_4::soap_new_std__string)
	std::string attStr = gsoap_eml2_1::soap_witsml20__TypeSurveyTool2s(gsoapProxyTraj1_4->soap, attributeName);
	*static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->typeSurveyTool = attStr;
}
GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, TypeSurveyTool, typeSurveyTool)
gsoap_eml2_1::witsml20__TypeSurveyTool Trajectory::getTrajectoryStationTypeSurveyTool(unsigned int index) const {
	CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE_1_4(Trajectory, trajectoryStation, typeSurveyTool)
	std::string attStr = *static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->typeSurveyTool;
	gsoap_eml2_1::witsml20__TypeSurveyTool att2_1;
	if (gsoap_eml2_1::soap_s2witsml20__TypeSurveyTool(gsoapProxyTraj1_4->soap, attStr.c_str(), &att2_1) == SOAP_OK) { return att2_1; }
	else { throw invalid_argument("The enum " + attStr + " is not recognized."); }
}

void Trajectory::setTrajectoryStationCalcAlgorithm(unsigned int index, const gsoap_eml2_1::witsml20__TrajStnCalcAlgorithm & attributeName) {
	CREATE_ATTRIBUTE_IN_VECTOR_IF_NOT_PRESENT_1_4(trajectoryStation, calcAlgorithm, gsoap_witsml1_4::soap_new_std__string)
		std::string attStr = gsoap_eml2_1::soap_witsml20__TrajStnCalcAlgorithm2s(gsoapProxyTraj1_4->soap, attributeName);
	*static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->calcAlgorithm = attStr;
}
GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, CalcAlgorithm, calcAlgorithm)
gsoap_eml2_1::witsml20__TrajStnCalcAlgorithm Trajectory::getTrajectoryStationCalcAlgorithm(unsigned int index) const {
	CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE_1_4(Trajectory, trajectoryStation, calcAlgorithm)
		std::string attStr = *static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->calcAlgorithm;
	gsoap_eml2_1::witsml20__TrajStnCalcAlgorithm att2_1;
	if (gsoap_eml2_1::soap_s2witsml20__TrajStnCalcAlgorithm(gsoapProxyTraj1_4->soap, attStr.c_str(), &att2_1) == SOAP_OK) { return att2_1; }
	else { throw invalid_argument("The enum " + attStr + " is not recognized."); }
}

GETTER_AND_SETTER_ENUM_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(gsoap_eml2_1::witsml20__TrajStationStatus, gsoap_witsml1_4::witsml14__TrajStationStatus, Trajectory, TrajectoryStation, trajectoryStation, StatusTrajStation, statusTrajStation, gsoap_witsml1_4::soap_new_witsml14__TrajStationStatus,
	gsoap_eml2_1::soap_witsml20__TrajStationStatus2s, gsoap_eml2_1::soap_s2witsml20__TrajStationStatus, gsoap_witsml1_4::soap_witsml14__TrajStationStatus2s, gsoap_witsml1_4::soap_s2witsml14__TrajStationStatus)

// Well vertical measure
void Trajectory::setTrajectoryStationTvd(unsigned int index, double value, gsoap_eml2_1::eml21__LengthUom uom, const std::string & datum) {
	if (value != value) { throw invalid_argument("You cannot set an undefined measured depth coord"); }
	CREATE_ATTRIBUTE_IN_VECTOR_IF_NOT_PRESENT_1_4(trajectoryStation, tvd, gsoap_witsml1_4::soap_new_witsml14__wellVerticalDepthCoord)
	static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->tvd->__item = value;
	std::string uomStr = gsoap_eml2_1::soap_eml21__LengthUom2s(gsoapProxyTraj1_4->soap, uom);
	witsml14__WellVerticalCoordinateUom uom1_4;
	if (soap_s2witsml14__WellVerticalCoordinateUom(gsoapProxyTraj1_4->soap, uomStr.c_str(), &uom1_4) == SOAP_OK) { static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->tvd->uom = uom1_4; }
	else { throw invalid_argument("The depth uom " + uomStr + " is not recognized."); }
	if (!datum.empty()) {
		static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->tvd->datum = soap_new_std__string(gsoapProxyTraj1_4->soap);
		static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->tvd->datum->assign(datum);
	}
}
GETTER_VALUE_OF_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, Tvd, tvd)
GETTER_UOM_OF_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, Tvd, tvd, gsoap_eml2_1::eml21__LengthUom, soap_witsml14__WellVerticalCoordinateUom2s, gsoap_eml2_1::soap_s2eml21__LengthUom)
std::string Trajectory::getTrajectoryStationTvdDatum(unsigned int index) const {
	CHECK_RANGE_1_4(trajectoryStation, index)
	if (static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->tvd->datum == nullptr) return "";
	return *static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation[index]->tvd->datum;
}
GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, Tvd, tvd)

// Optional Length Measure
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, DispNs, dispNs, gsoap_eml2_1::eml21__LengthUom, gsoap_witsml1_4::witsml14__LengthUom, gsoap_witsml1_4::soap_new_witsml14__lengthMeasure,
	gsoap_eml2_1::soap_eml21__LengthUom2s, gsoap_eml2_1::soap_s2eml21__LengthUom, gsoap_witsml1_4::soap_witsml14__LengthUom2s, gsoap_witsml1_4::soap_s2witsml14__LengthUom)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, DispEw, dispEw, gsoap_eml2_1::eml21__LengthUom, gsoap_witsml1_4::witsml14__LengthUom, gsoap_witsml1_4::soap_new_witsml14__lengthMeasure,
	gsoap_eml2_1::soap_eml21__LengthUom2s, gsoap_eml2_1::soap_s2eml21__LengthUom, gsoap_witsml1_4::soap_witsml14__LengthUom2s, gsoap_witsml1_4::soap_s2witsml14__LengthUom)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, VertSect, vertSect, gsoap_eml2_1::eml21__LengthUom, gsoap_witsml1_4::witsml14__LengthUom, gsoap_witsml1_4::soap_new_witsml14__lengthMeasure,
	gsoap_eml2_1::soap_eml21__LengthUom2s, gsoap_eml2_1::soap_s2eml21__LengthUom, gsoap_witsml1_4::soap_witsml14__LengthUom2s, gsoap_witsml1_4::soap_s2witsml14__LengthUom)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, MdDelta, mdDelta, gsoap_eml2_1::eml21__LengthUom, gsoap_witsml1_4::witsml14__LengthUom, gsoap_witsml1_4::soap_new_witsml14__lengthMeasure,
	gsoap_eml2_1::soap_eml21__LengthUom2s, gsoap_eml2_1::soap_s2eml21__LengthUom, gsoap_witsml1_4::soap_witsml14__LengthUom2s, gsoap_witsml1_4::soap_s2witsml14__LengthUom)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, TvdDelta, tvdDelta, gsoap_eml2_1::eml21__LengthUom, gsoap_witsml1_4::witsml14__LengthUom, gsoap_witsml1_4::soap_new_witsml14__lengthMeasure,
	gsoap_eml2_1::soap_eml21__LengthUom2s, gsoap_eml2_1::soap_s2eml21__LengthUom, gsoap_witsml1_4::soap_witsml14__LengthUom2s, gsoap_witsml1_4::soap_s2witsml14__LengthUom)

// Optional Plane AngleMeasure
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, Incl, incl, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_witsml1_4::witsml14__PlaneAngleUom, gsoap_witsml1_4::soap_new_witsml14__planeAngleMeasure,
	gsoap_eml2_1::soap_eml21__PlaneAngleUom2s, gsoap_eml2_1::soap_s2eml21__PlaneAngleUom, gsoap_witsml1_4::soap_witsml14__PlaneAngleUom2s, gsoap_witsml1_4::soap_s2witsml14__PlaneAngleUom)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, Azi, azi, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_witsml1_4::witsml14__PlaneAngleUom, gsoap_witsml1_4::soap_new_witsml14__planeAngleMeasure,
	gsoap_eml2_1::soap_eml21__PlaneAngleUom2s, gsoap_eml2_1::soap_s2eml21__PlaneAngleUom, gsoap_witsml1_4::soap_witsml14__PlaneAngleUom2s, gsoap_witsml1_4::soap_s2witsml14__PlaneAngleUom)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, Mtf, mtf, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_witsml1_4::witsml14__PlaneAngleUom, gsoap_witsml1_4::soap_new_witsml14__planeAngleMeasure,
	gsoap_eml2_1::soap_eml21__PlaneAngleUom2s, gsoap_eml2_1::soap_s2eml21__PlaneAngleUom, gsoap_witsml1_4::soap_witsml14__PlaneAngleUom2s, gsoap_witsml1_4::soap_s2witsml14__PlaneAngleUom)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, Gtf, gtf, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_witsml1_4::witsml14__PlaneAngleUom, gsoap_witsml1_4::soap_new_witsml14__planeAngleMeasure,
	gsoap_eml2_1::soap_eml21__PlaneAngleUom2s, gsoap_eml2_1::soap_s2eml21__PlaneAngleUom, gsoap_witsml1_4::soap_witsml14__PlaneAngleUom2s, gsoap_witsml1_4::soap_s2witsml14__PlaneAngleUom)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, DipAngleUncert, dipAngleUncert, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_witsml1_4::witsml14__PlaneAngleUom, gsoap_witsml1_4::soap_new_witsml14__planeAngleMeasure,
	gsoap_eml2_1::soap_eml21__PlaneAngleUom2s, gsoap_eml2_1::soap_s2eml21__PlaneAngleUom, gsoap_witsml1_4::soap_witsml14__PlaneAngleUom2s, gsoap_witsml1_4::soap_s2witsml14__PlaneAngleUom)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, MagDipAngleReference, magDipAngleReference, gsoap_eml2_1::eml21__PlaneAngleUom, gsoap_witsml1_4::witsml14__PlaneAngleUom, gsoap_witsml1_4::soap_new_witsml14__planeAngleMeasure,
	gsoap_eml2_1::soap_eml21__PlaneAngleUom2s, gsoap_eml2_1::soap_s2eml21__PlaneAngleUom, gsoap_witsml1_4::soap_witsml14__PlaneAngleUom2s, gsoap_witsml1_4::soap_s2witsml14__PlaneAngleUom)

// Optional Plane AngleMeasure
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, Dls, dls, gsoap_eml2_1::eml21__AnglePerLengthUom, gsoap_witsml1_4::witsml14__AnglePerLengthUom, gsoap_witsml1_4::soap_new_witsml14__anglePerLengthMeasure,
	gsoap_eml2_1::soap_eml21__AnglePerLengthUom2s, gsoap_eml2_1::soap_s2eml21__AnglePerLengthUom, gsoap_witsml1_4::soap_witsml14__AnglePerLengthUom2s, gsoap_witsml1_4::soap_s2witsml14__AnglePerLengthUom)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, RateTurn, rateTurn, gsoap_eml2_1::eml21__AnglePerLengthUom, gsoap_witsml1_4::witsml14__AnglePerLengthUom, gsoap_witsml1_4::soap_new_witsml14__anglePerLengthMeasure,
	gsoap_eml2_1::soap_eml21__AnglePerLengthUom2s, gsoap_eml2_1::soap_s2eml21__AnglePerLengthUom, gsoap_witsml1_4::soap_witsml14__AnglePerLengthUom2s, gsoap_witsml1_4::soap_s2witsml14__AnglePerLengthUom)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, RateBuild, rateBuild, gsoap_eml2_1::eml21__AnglePerLengthUom, gsoap_witsml1_4::witsml14__AnglePerLengthUom, gsoap_witsml1_4::soap_new_witsml14__anglePerLengthMeasure,
	gsoap_eml2_1::soap_eml21__AnglePerLengthUom2s, gsoap_eml2_1::soap_s2eml21__AnglePerLengthUom, gsoap_witsml1_4::soap_witsml14__AnglePerLengthUom2s, gsoap_witsml1_4::soap_s2witsml14__AnglePerLengthUom)

// Optional Linear Acceleration Measure
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, GravTotalUncert, gravTotalUncert, gsoap_eml2_1::eml21__LinearAccelerationUom, gsoap_witsml1_4::witsml14__AccelerationLinearUom, gsoap_witsml1_4::soap_new_witsml14__accelerationLinearMeasure,
	gsoap_eml2_1::soap_eml21__LinearAccelerationUom2s, gsoap_eml2_1::soap_s2eml21__LinearAccelerationUom, gsoap_witsml1_4::soap_witsml14__AccelerationLinearUom2s, gsoap_witsml1_4::soap_s2witsml14__AccelerationLinearUom)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, GravTotalFieldReference, gravTotalFieldReference, gsoap_eml2_1::eml21__LinearAccelerationUom, gsoap_witsml1_4::witsml14__AccelerationLinearUom, gsoap_witsml1_4::soap_new_witsml14__accelerationLinearMeasure,
	gsoap_eml2_1::soap_eml21__LinearAccelerationUom2s, gsoap_eml2_1::soap_s2eml21__LinearAccelerationUom, gsoap_witsml1_4::soap_witsml14__AccelerationLinearUom2s, gsoap_witsml1_4::soap_s2witsml14__AccelerationLinearUom)

// Optional Magnetic Flux Density Measure
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, MagTotalUncert, magTotalUncert, gsoap_eml2_1::eml21__MagneticFluxDensityUom, gsoap_witsml1_4::witsml14__MagneticInductionUom, gsoap_witsml1_4::soap_new_witsml14__magneticInductionMeasure,
	gsoap_eml2_1::soap_eml21__MagneticFluxDensityUom2s, gsoap_eml2_1::soap_s2eml21__MagneticFluxDensityUom, gsoap_witsml1_4::soap_witsml14__MagneticInductionUom2s, gsoap_witsml1_4::soap_s2witsml14__MagneticInductionUom)
GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(Trajectory, TrajectoryStation, trajectoryStation, MagTotalFieldReference, magTotalFieldReference, gsoap_eml2_1::eml21__MagneticFluxDensityUom, gsoap_witsml1_4::witsml14__MagneticInductionUom, gsoap_witsml1_4::soap_new_witsml14__magneticInductionMeasure,
	gsoap_eml2_1::soap_eml21__MagneticFluxDensityUom2s, gsoap_eml2_1::soap_s2eml21__MagneticFluxDensityUom, gsoap_witsml1_4::soap_witsml14__MagneticInductionUom2s, gsoap_witsml1_4::soap_s2witsml14__MagneticInductionUom)

void Trajectory::pushBackTrajectoryStation(gsoap_eml2_1::witsml20__TrajStationType kind, double mdValue, gsoap_eml2_1::eml21__LengthUom uom, const std::string & datum, const std::string & uid)
{
	if (static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence == nullptr) {
		static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence = soap_new___witsml14__obj_USCOREtrajectory_sequence(gsoapProxyTraj1_4->soap);
	}

	static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation.push_back(soap_new_witsml14__cs_USCOREtrajectoryStation(gsoapProxyTraj1_4->soap));
	unsigned int index = getTrajectoryStationCount() - 1;
	setTrajectoryStationTypeTrajStation(index, kind);
	setTrajectoryStationMd(index, mdValue, uom, datum);
}

unsigned int Trajectory::getTrajectoryStationCount() const
{
	const size_t count = static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence != nullptr
		? static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->trajectoryStation.size()
		: 0;
	if (count >= (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("Too much trajectory stations");
	}

	return static_cast<unsigned int>(count);
}
