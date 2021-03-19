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

#include "WellboreObject.h"

#include "../MacroDefinitions.h"

namespace WITSML2_NS
{
	/** 
	 * @brief	It contains many trajectory stations to capture the information about individual survey points.
	 */
	class Trajectory : public WellboreObject
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT Trajectory(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WellboreObject(partialObject) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~Trajectory() = default;

		ABSTRACT_GETTER_AND_SETTER_GENERIC_ATTRIBUTE(gsoap_eml2_1::witsml20__ChannelStatus, GrowingStatus)

		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimTrajStart)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimTrajEnd)

		ABSTRACT_GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdMn, gsoap_eml2_1::eml21__LengthUom)
		ABSTRACT_GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdMx, gsoap_eml2_1::eml21__LengthUom)

		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, ServiceCompany)

		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(MagDeclUsed, gsoap_eml2_1::eml21__PlaneAngleUom)
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(GridConUsed, gsoap_eml2_1::eml21__PlaneAngleUom)
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(AziVertSect, gsoap_eml2_1::eml21__PlaneAngleUom)

		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(DispNsVertSectOrig, gsoap_eml2_1::eml21__LengthUom)
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(DispEwVertSectOrig, gsoap_eml2_1::eml21__LengthUom)

		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, Definitive)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, Memory)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, FinalTraj)

		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml20__AziRef, AziRef)

		//***************************************
		// ******* TRAJECTORY STATIONS **********
		//***************************************

		// Mandatory
		ABSTRACT_GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, uid)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(gsoap_eml2_1::witsml20__TrajStationType, TrajectoryStation, TypeTrajStation)
		ABSTRACT_GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Md, gsoap_eml2_1::eml21__LengthUom)

		// Optional bool
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, ManuallyEntered)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, GravAccelCorUsed)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, MagXAxialCorUsed)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, SagCorUsed)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, MagDrlstrCorUsed)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, InfieldRefCorUsed)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, InterpolatedInfieldRefCorUsed)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, InHoleRefCorUsed)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, AxialMagInterferenceCorUsed)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, CosagCorUsed)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, TrajectoryStation, MSACorUsed)

		// Optional string
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, Target)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, MagModelUsed)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, MagModelValid)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, TrajectoryStation, GeoModelUsed)

		// Optional timestamp
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(time_t, TrajectoryStation, DTimStn)

		// Optional enum
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_1::witsml20__TypeSurveyTool, TrajectoryStation, TypeSurveyTool)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_1::witsml20__TrajStnCalcAlgorithm, TrajectoryStation, CalcAlgorithm)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_1::witsml20__TrajStationStatus, TrajectoryStation, StatusTrajStation)

		// Optional Length Measure
		ABSTRACT_GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Tvd, gsoap_eml2_1::eml21__LengthUom)
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, DispNs, gsoap_eml2_1::eml21__LengthUom)
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, DispEw, gsoap_eml2_1::eml21__LengthUom)
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, VertSect, gsoap_eml2_1::eml21__LengthUom)
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, MdDelta, gsoap_eml2_1::eml21__LengthUom)
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, TvdDelta, gsoap_eml2_1::eml21__LengthUom)

		// Optional Plane Angle Measure
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Incl, gsoap_eml2_1::eml21__PlaneAngleUom)
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Azi, gsoap_eml2_1::eml21__PlaneAngleUom)
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Mtf, gsoap_eml2_1::eml21__PlaneAngleUom)
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Gtf, gsoap_eml2_1::eml21__PlaneAngleUom)
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, DipAngleUncert, gsoap_eml2_1::eml21__PlaneAngleUom)
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, MagDipAngleReference, gsoap_eml2_1::eml21__PlaneAngleUom)

		// Optional Angle per Length Measure
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, Dls, gsoap_eml2_1::eml21__AnglePerLengthUom)
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, RateTurn, gsoap_eml2_1::eml21__AnglePerLengthUom)
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, RateBuild, gsoap_eml2_1::eml21__AnglePerLengthUom)

		// Optional Linear Acceleration Measure
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, GravTotalUncert, gsoap_eml2_1::eml21__LinearAccelerationUom)
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, GravTotalFieldReference, gsoap_eml2_1::eml21__LinearAccelerationUom)

		// Optional Magnetic Flux Density Measure
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, MagTotalUncert, gsoap_eml2_1::eml21__MagneticFluxDensityUom)
		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(TrajectoryStation, MagTotalFieldReference, gsoap_eml2_1::eml21__MagneticFluxDensityUom)

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static constexpr char XML_TAG[] = "Trajectory";

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

		/**
		 * Push back a minimal trajectory station into the trajectory.
		 *
		 * @param 	kind   	The kind of trajectory station.
		 * @param 	mdValue	The Measured Depth value of the trajectory station.
		 * @param 	uom	   	The Measured Depth uom of the trajectory station.
		 * @param 	datum  	The datum of the trajectory station. Energistics does not well define if it
		 * 					should be the title or the uid of the referenced datum.
		 * @param 	uid	   	(Optional) The uid of the trajectory station. Automatically set to its index
		 * 					if empty.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackTrajectoryStation(gsoap_eml2_1::witsml20__TrajStationType kind, double mdValue, gsoap_eml2_1::eml21__LengthUom uom, const std::string & datum, const std::string & uid = "") = 0;

		/**
		 * Get the count of trajectory stations in this trajectory
		 *
		 * @returns	the count of trajectory stations in this trajectory.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getTrajectoryStationCount() const = 0;

	protected:

		/** Default constructor does nothing */
		Trajectory() = default;

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		Trajectory(gsoap_eml2_1::witsml20__Trajectory* fromGsoap) : WellboreObject(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		Trajectory(gsoap_witsml1_4::witsml14__obj_USCOREtrajectory* fromGsoap) : WellboreObject(fromGsoap) {}
	};
}
