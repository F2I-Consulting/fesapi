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

#include "../witsml2/Well.h"

namespace WITSML2_1_NS
{
	/**
	 * @brief	Contains all information that is the same for all wellbores (sidetracks).
	 */
	class Well : public WITSML2_NS::Well
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT Well(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WITSML2_NS::Well(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	repo 	The dataobject repo where the underlying gsoap proxy is going to be
		 * 							created.
		 * @param 		  	guid 	The guid to set to this instance. If empty then a new guid will be
		 * 							generated.
		 * @param 		  	title	The title.
		 * @param 	  	isActive	  	True if is active, false if not.
		 */
		Well(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid,
			const std::string & title,
			bool isActive);

		/**
		 * @brief	Constructor
		 *
		 * @exception	std::invalid_argument	If <tt>repo == nullptr</tt>.
		 *
		 * @param [in,out]	repo		 	If non-null, the repo.
		 * @param 		  	guid		 	Unique identifier.
		 * @param 		  	title		 	The title.
		 * @param 	  		isActive	  	True if is active, false if not.
		 * @param 		  	statusWell   	The status well.
		 * @param 		  	directionWell	The direction well.
		 */
		Well(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid,
			const std::string & title,
			bool isActive,
			gsoap_eml2_3::eml23__WellStatus statusWell,
			gsoap_eml2_3::witsml21__WellDirection directionWell
		);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		Well(gsoap_eml2_3::witsml21__Well* fromGsoap): WITSML2_NS::Well(fromGsoap)  {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~Well() = default;

		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NameLegal)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NumLicense)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NumGovt)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Field)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Country)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, State)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, County)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Region)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, District)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Block)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, OperatorDiv)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NumAPI)

		// Optional enum
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::eml23__WellStatus, StatusWell)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::witsml21__WellPurpose, PurposeWell)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::witsml21__WellFluid, FluidWell)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::witsml21__WellDirection, DirectionWell)

		FINAL_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(WaterDepth, gsoap_eml2_3::eml23__LengthUom)
		FINAL_GETTER_PRESENCE_ATTRIBUTE(GroundElevation)
		FINAL_GETTER_PRESENCE_ATTRIBUTE(WellheadElevation)

		FINAL_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(PcInterest, gsoap_eml2_3::eml23__DimensionlessUom)

		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimLicense)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimSpud)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimPa)

		/**
			* @brief	Sets the ground level elevation (land rigs)
			*
			* @exception	std::invalid_argument	If @p value is undefined.
			*
			* @param 	value		The elevation value.
			* @param 	uom  		The elevation unit of measure.
			* @param	verticalCrs	The vertical CRS which is used as the datum for the ground elevation
			*/
		DLL_IMPORT_OR_EXPORT void setGroundElevation(double value, gsoap_eml2_3::eml23__LengthUom uom, EML2_3_NS::VerticalCrs* verticalCrs) final;

		/**
		 * @brief	Gets the ground level elevation value
		 *
		 * @exception	std::invalid_argument	If the ground elevation does not exist.
		 *
		 * @returns	The ground level elevation value.
		 */
		DLL_IMPORT_OR_EXPORT double getGroundElevationValue() const final;

		/**
		 * @brief	Gets the ground level elevation unit of measure
		 *
		 * @exception	std::invalid_argument	If the ground elevation does not exist.
		 *
		 * @returns	The ground level elevation unit of measure.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__LengthUom getGroundElevationUom() const final;
		
		/**
		 * Gets the data object reference of the datum of this ground elevation.
		 *
		 * @returns	The data object reference of the datum of this ground elevation.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getGroundElevationDatumDor() const final;

		/**
		* @brief	Sets the well head elevation
		*
		* @exception	std::invalid_argument	If @p value is undefined.
		*
		* @param 	value		The elevation value.
		* @param 	uom  		The elevation unit of measure.
		* @param	verticalCrs	The vertical CRS which is used as the datum for the well head elevation
		*/
		DLL_IMPORT_OR_EXPORT virtual void setWellheadElevation(double value, gsoap_eml2_3::eml23__LengthUom uom, EML2_3_NS::VerticalCrs* verticalCrs) final;

		/**
		 * @brief	Gets the well head elevation value
		 *
		 * @exception	std::invalid_argument	If the well head elevation does not exist.
		 *
		 * @returns	The well head elevation value.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getWellheadElevationValue() const final;

		/**
		 * @brief	Gets the well head elevation unit of measure
		 *
		 * @exception	std::invalid_argument	If the well head elevation does not exist.
		 *
		 * @returns	The well head elevation unit of measure.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_eml2_3::eml23__LengthUom getWellheadElevationUom() const final;

		/**
		 * Gets the data object reference of the datum of this well head elevation.
		 *
		 * @returns	The data object reference of the datum of this well head elevation.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getWellheadElevationDatumDor() const final;

		/**
		* Set the time zone in which the well is located.It is the deviation in hours and minutes from
		* UTC.This should be the normal time zone at the well and not a seasonally-adjusted value,
		* such as daylight savings time
		*
		* @param 	direction	True means the time zone is a positive offset from UTC, false means the
		* 						time zone is a negative offset from UTC.
		* @param 	hours	 	The deviation hours from UTC.
		* @param 	minutes		The deviation minutes from UTC.
		*/
		DLL_IMPORT_OR_EXPORT void setTimeZone(bool direction, unsigned short hours, unsigned short minutes) final;
		FINAL_GETTER_PRESENCE_ATTRIBUTE(TimeZone)

		/**
		 * Get the time zone direction in which the well is located.
		 *
		 * @returns	True means the time zone is a positive offset from UTC, false means the time zone is
		 * 			a negative offset from UTC. If the time zone is Z then an arbitrary '+' is returned.
		 */
		DLL_IMPORT_OR_EXPORT bool getTimeZoneDirection() const final;

		/**
		 * Get the time zone hour(s) in which the well is located. Must be used with
		 * getTimeZoneDirection and getTimeZoneMinute() to have the complete time zone.
		 *
		 * @returns	the deviation hour(s) from UTC.
		 */
		DLL_IMPORT_OR_EXPORT unsigned short getTimeZoneHours() const final;

		/**
		 * Get the time zone minute(s) in which the well is located. Must be used with
		 * getTimeZoneDirection and getTimeZoneHour() to have the complete time zone.
		 *
		 * @returns	the deviation minute(s) from UTC.
		 */
		DLL_IMPORT_OR_EXPORT unsigned short getTimeZoneMinutes() const final;

		/**
		 * Gets location projected x coordinate
		 *
		 * @param 	locationIndex	Zero-based index of the location.
		 *
		 * @returns	The location projected x coordinate.
		 */
		DLL_IMPORT_OR_EXPORT double getLocationProjectedX(uint64_t locationIndex) final;

		/**
		 * Gets location projected y coordinate
		 *
		 * @param 	locationIndex	Zero-based index of the location.
		 *
		 * @returns	The location projected y coordinate.
		 */
		DLL_IMPORT_OR_EXPORT double getLocationProjectedY(uint64_t locationIndex) final;

		/**
		 * Pushes a back location
		 *
		 * @param 	projectedX		The projected x coordinate.
		 * @param 	projectedY		The projected y coordinate.
		 * @param 	crs				The CRS of the X and Y coordinates.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackLocation(double projectedX, double projectedY, EML2_3_NS::LocalEngineering2dCrs* crs) final;

		/**
		 * Ge location count
		 *
		 * @returns	An int.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t geLocationCount() const final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "witsml21";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
