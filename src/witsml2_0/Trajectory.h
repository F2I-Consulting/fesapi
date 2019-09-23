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
#pragma once

#include "witsml2_0/WellboreObject.h"

namespace WITSML2_0_NS
{
	class Trajectory : public WellboreObject
	{
	public:
		/**
		* Constructor for partial transfer
		*/
		Trajectory(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WellboreObject(partialObject) {}

		Trajectory(class Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::witsml20__ChannelStatus channelStatus);
	
		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		Trajectory(gsoap_eml2_1::witsml20__Trajectory* fromGsoap) :WellboreObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~Trajectory() {}

		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__DataObjectReference* getWellboreDor() const;
		DLL_IMPORT_OR_EXPORT void setWellbore(class Wellbore* witsmlWellbore);

		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(gsoap_eml2_1::witsml20__ChannelStatus, GrowingStatus)

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimTrajStart)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimTrajEnd)

		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdMn, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdMx, gsoap_eml2_1::eml21__LengthUom)

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, ServiceCompany)

		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(MagDeclUsed, gsoap_eml2_1::eml21__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(GridConUsed, gsoap_eml2_1::eml21__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(AziVertSect, gsoap_eml2_1::eml21__PlaneAngleUom)

		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(DispNsVertSectOrig, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(DispEwVertSectOrig, gsoap_eml2_1::eml21__LengthUom)

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, Definitive)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, Memory)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, FinalTraj)

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml20__AziRef, AziRef)

		//***************************************
		// ******* TRAJECTORY STATIONS **********
		//***************************************

		// Mandatory
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, uid)
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(gsoap_eml2_1::witsml20__TrajStationType, TrajectoryStation, TypeTrajStation)
		GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Md, gsoap_eml2_1::eml21__LengthUom)

		// Optional bool
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, ManuallyEntered)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, GravAccelCorUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, MagXAxialCorUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, SagCorUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, MagDrlstrCorUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, InfieldRefCorUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, InterpolatedInfieldRefCorUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, InHoleRefCorUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, AxialMagInterferenceCorUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, CosagCorUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, MSACorUsed)

		// Optional string
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, Target)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, MagModelUsed)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, MagModelValid)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, GeoModelUsed)

		// Optional timestamp
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(time_t, TrajectoryStation, DTimStn)

		// Optional enum
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_1::witsml20__TypeSurveyTool, TrajectoryStation, TypeSurveyTool)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_1::witsml20__TrajStnCalcAlgorithm, TrajectoryStation, CalcAlgorithm)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_1::witsml20__TrajStationStatus, TrajectoryStation, StatusTrajStation)

		// Optional Length Measure
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Tvd, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, DispNs, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, DispEw, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, VertSect, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, MdDelta, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, TvdDelta, gsoap_eml2_1::eml21__LengthUom)

		// Optional Plane Angle Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Incl, gsoap_eml2_1::eml21__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Azi, gsoap_eml2_1::eml21__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Mtf, gsoap_eml2_1::eml21__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Gtf, gsoap_eml2_1::eml21__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, DipAngleUncert, gsoap_eml2_1::eml21__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, MagDipAngleReference, gsoap_eml2_1::eml21__PlaneAngleUom)

		// Optional Angle per Length Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Dls, gsoap_eml2_1::eml21__AnglePerLengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, RateTurn, gsoap_eml2_1::eml21__AnglePerLengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, RateBuild, gsoap_eml2_1::eml21__AnglePerLengthUom)

		// Optional Linear Acceleration Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, GravTotalUncert, gsoap_eml2_1::eml21__LinearAccelerationUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, GravTotalFieldReference, gsoap_eml2_1::eml21__LinearAccelerationUom)

		// Optional Magnetic Flux Density Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, MagTotalUncert, gsoap_eml2_1::eml21__MagneticFluxDensityUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, MagTotalFieldReference, gsoap_eml2_1::eml21__MagneticFluxDensityUom)

		/**
		* Push back a minimal trajectory station into the trajectory.
		*
		* @param kind		The kind of trajectory station
		* @param mdValue	The Measured Depth value of the trajectory station
		* @param mdValue	The Measured Depth uom of the trajectory station
		* @param datum		The datum of the trajectory station. Energistics does not well define if it should be the title or the uid of the referenced datum. 
		* @param uid		The uid of the trajectory station. Automatically set to its index if empty.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackTrajectoryStation(gsoap_eml2_1::witsml20__TrajStationType kind, double mdValue, gsoap_eml2_1::eml21__LengthUom uom, const std::string & datum, const std::string & uid = "");

		/**
		* Get the count of trajectory stations in this trajectory
		*
		* @return the count of trajectory stations in this trajectory
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getTrajectoryStationCount() const;

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }
	};
}
