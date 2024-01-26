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

#include "../common/AbstractObject.h"

#include "../MacroDefinitions.h"

namespace RESQML2_NS
{
	class WellboreFeature;
}

namespace WITSML2_1_NS
{
	class WellCompletion;
}

namespace EML2_3_NS
{
	class LocalEngineering2dCrs;
	class VerticalCrs;
}

namespace WITSML2_NS
{
	class Wellbore;

	/** 
	 * @brief	Contains all information that is the same for all wellbores (sidetracks). 
	 */
	class Well : public COMMON_NS::AbstractObject
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT Well(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~Well() = default;

		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NameLegal)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NumLicense)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NumGovt)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Field)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Country)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, State)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, County)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Region)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, District)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Block)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, OperatorDiv)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NumAPI)

		// Optional enum
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::eml23__WellStatus, StatusWell)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::witsml21__WellPurpose, PurposeWell)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::witsml21__WellFluid, FluidWell)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::witsml21__WellDirection, DirectionWell)

		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(WaterDepth, gsoap_eml2_3::eml23__LengthUom)
		ABSTRACT_GETTER_PRESENCE_ATTRIBUTE(GroundElevation)
		ABSTRACT_GETTER_PRESENCE_ATTRIBUTE(WellheadElevation)

		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(PcInterest, gsoap_eml2_3::eml23__DimensionlessUom)

		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimLicense)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimSpud)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimPa)

		/**
		* @brief	Sets the ground level elevation (land rigs)
		*
		* @exception	std::invalid_argument	If @p value is undefined.
		*
		* @param 	value		The elevation value.
		* @param 	uom  		The elevation unit of measure.
		* @param	verticalCrs	The vertical CRS which is used as the datum for the ground elevation
		*/
		DLL_IMPORT_OR_EXPORT virtual void setGroundElevation(double value, gsoap_eml2_3::eml23__LengthUom uom, EML2_3_NS::VerticalCrs* verticalCrs) = 0;

		/**
		 * @brief	Gets the ground level elevation value
		 *
		 * @exception	std::invalid_argument	If the ground elevation does not exist.
		 *
		 * @returns	The ground level elevation value.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getGroundElevationValue() const = 0;

		/**
		 * @brief	Gets the ground level elevation unit of measure
		 *
		 * @exception	std::invalid_argument	If the ground elevation does not exist.
		 *
		 * @returns	The ground level elevation unit of measure.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_eml2_3::eml23__LengthUom getGroundElevationUom() const = 0;

		/**
		 * Gets the data object reference of the datum of this ground elevation.
		 *
		 * @returns	The data object reference of the datum of this ground elevation.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getGroundElevationDatumDor() const = 0;

		/**
		 * Gets the vertical CRS which acts as the datum of this ground elevation.
		 *
		 * @returns	The vertical CRS which acts as the datum of this ground elevation..
		 */
		DLL_IMPORT_OR_EXPORT EML2_3_NS::VerticalCrs* getGroundElevationDatum() const;

		/**
		* @brief	Sets the well head elevation
		*
		* @exception	std::invalid_argument	If @p value is undefined.
		*
		* @param 	value		The elevation value.
		* @param 	uom  		The elevation unit of measure.
		* @param	verticalCrs	The vertical CRS which is used as the datum for the well head elevation
		*/
		DLL_IMPORT_OR_EXPORT virtual void setWellheadElevation(double value, gsoap_eml2_3::eml23__LengthUom uom, EML2_3_NS::VerticalCrs* verticalCrs) = 0;

		/**
		 * @brief	Gets the well head elevation value
		 *
		 * @exception	std::invalid_argument	If the well head elevation does not exist.
		 *
		 * @returns	The well head elevation value.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getWellheadElevationValue() const = 0;

		/**
		 * @brief	Gets the well head elevation unit of measure
		 *
		 * @exception	std::invalid_argument	If the well head elevation does not exist.
		 *
		 * @returns	The well head elevation unit of measure.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_eml2_3::eml23__LengthUom getWellheadElevationUom() const = 0;

		/**
		 * Gets the data object reference of the datum of this well head elevation.
		 *
		 * @returns	The data object reference of the datum of this well head elevation.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getWellheadElevationDatumDor() const = 0;

		/**
		 * Gets the vertical CRS which acts as the datum of this well head elevation.
		 *
		 * @returns	The vertical CRS which acts as the datum of this well head elevation..
		 */
		DLL_IMPORT_OR_EXPORT EML2_3_NS::VerticalCrs* getWellheadElevationDatum() const;

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
		DLL_IMPORT_OR_EXPORT virtual void setTimeZone(bool direction, unsigned short hours, unsigned short minutes) = 0;
		ABSTRACT_GETTER_PRESENCE_ATTRIBUTE(TimeZone)

		/**
			* Get the time zone direction in which the well is located.
			*
			* @returns	True means the time zone is a positive offset from UTC, false means the time zone is
			* 			a negative offset from UTC. If the time zone is Z then an arbitrary '+' is returned.
			*/
		DLL_IMPORT_OR_EXPORT virtual bool getTimeZoneDirection() const = 0;

		/**
		 * Get the time zone hour(s) in which the well is located. Must be used with
		 * getTimeZoneDirection and getTimeZoneMinute() to have the complete time zone.
		 *
		 * @returns	the deviation hour(s) from UTC.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned short getTimeZoneHours() const = 0;

		/**
		 * Get the time zone minute(s) in which the well is located. Must be used with
		 * getTimeZoneDirection and getTimeZoneHour() to have the complete time zone.
		 *
		 * @returns	the deviation minute(s) from UTC.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned short getTimeZoneMinutes() const = 0;

		/**
			* Gets location projected x coordinate
			*
			* @param 	locationIndex	Zero-based index of the location.
			*
			* @returns	The location projected x coordinate.
			*/
		DLL_IMPORT_OR_EXPORT virtual double getLocationProjectedX(uint64_t locationIndex) = 0;

		/**
		 * Gets location projected y coordinate
		 *
		 * @param 	locationIndex	Zero-based index of the location.
		 *
		 * @returns	The location projected y coordinate.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getLocationProjectedY(uint64_t locationIndex) = 0;

		/**
		 * Pushes a back location
		 *
		 * @param 	projectedX		The projected x coordinate.
		 * @param 	projectedY		The projected y coordinate.
		 * @param 	crs				The CRS of the X and Y coordinates.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackLocation(double projectedX, double projectedY, EML2_3_NS::LocalEngineering2dCrs* crs) = 0;

		/**
		 * Get location count
		 *
		 * @returns	An int.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t geLocationCount() const = 0;

		GETTER_DATAOBJECTS(RESQML2_NS::WellboreFeature, ResqmlWellboreFeature)
		GETTER_DATAOBJECTS(WITSML2_NS::Wellbore, Wellbore)
		GETTER_DATAOBJECTS(WITSML2_1_NS::WellCompletion, Wellcompletion)

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "Well";

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/** Default constructor does nothing */
		Well() = default;

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		Well(gsoap_eml2_3::witsml21__Well* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
