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

namespace WITSML2_0_NS
{
	class WellCompletion;
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
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Operator)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, OperatorDiv)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, OriginalOperator)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NumAPI)

		// Optional enum
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::eml21__WellStatus, StatusWell)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml20__WellPurpose, PurposeWell)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml20__WellFluid, FluidWell)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml20__WellDirection, DirectionWell)

		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(WaterDepth, gsoap_eml2_1::eml21__LengthUom)
		ABSTRACT_GETTER_PRESENCE_ATTRIBUTE(GroundElevation)

		ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(PcInterest, gsoap_eml2_1::eml21__DimensionlessUom)

		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimLicense)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimSpud)
		ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimPa)

		/**
			* @brief	Sets the ground level elevation (land rigs)
			*
			* @exception	std::invalid_argument	If @p value is undefined.
			*
			* @param 	value	The elevation value.
			* @param 	uom  	The elevation unit of measure.
			* @param 	datum	The elevation datum.
			*/
		DLL_IMPORT_OR_EXPORT virtual void setGroundElevation(double value, gsoap_eml2_1::eml21__LengthUom uom, const std::string& datum) = 0;

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
		DLL_IMPORT_OR_EXPORT virtual gsoap_eml2_1::eml21__LengthUom getGroundElevationUom() const = 0;

		/**
		 * @brief	Gets the ground level elevation datum
		 *
		 * @exception	std::invalid_argument	If the ground elevation does not exist.
		 *
		 * @returns	The ground level elevation datum.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getGroundElevationDatum() const = 0;

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
		DLL_IMPORT_OR_EXPORT virtual double getLocationProjectedX(unsigned int locationIndex) = 0;

		/**
		 * Gets location projected y coordinate
		 *
		 * @param 	locationIndex	Zero-based index of the location.
		 *
		 * @returns	The location projected y coordinate.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getLocationProjectedY(unsigned int locationIndex) = 0;

		/**
		 * Pushes a back location
		 *
		 * @param 	guid					Unique identifier.
		 * @param 	projectedX				The projected x coordinate.
		 * @param 	projectedY				The projected y coordinate.
		 * @param 	projectedCrsEpsgCode	The projected crs epsg code.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackLocation(
			const std::string & guid,
			double projectedX,
			double projectedY,
			unsigned int projectedCrsEpsgCode) = 0;

		/**
		 * Ge location count
		 *
		 * @returns	An int.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int geLocationCount() const = 0;

		/**
		 * Pushes a back datum
		 *
		 * @param 	guid			   	Unique identifier.
		 * @param 	title			   	The title.
		 * @param 	code			   	The code.
		 * @param 	datum			   	The datum.
		 * @param 	elevationUnit	   	The elevation unit.
		 * @param 	elevation		   	The elevation.
		 * @param 	verticalCrsEpsgCode	The vertical crs epsg code.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackDatum(
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::eml21__WellboreDatumReference code,
			const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom elevationUnit,
			double elevation,
			unsigned int verticalCrsEpsgCode) = 0;

		/**
		 * Gets datum count
		 *
		 * @returns	The datum count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getDatumCount() const = 0;

		/**
		 * Gets resqml wellbore features
		 *
		 * @returns	Null if it fails, else the RESQML wellbore features.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_NS::WellboreFeature *> getResqmlWellboreFeatures() const;

		GETTER_DATAOBJECTS(WITSML2_NS::Wellbore, Wellbore)
		GETTER_DATAOBJECTS(WITSML2_0_NS::WellCompletion, Wellcompletion)

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static constexpr char XML_TAG[] = "Well";

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

		/** A WITSML well points towards no other dataobject */
		void loadTargetRelationships() {}

	protected:

		/** Default constructor does nothing */
		Well() = default;

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		Well(gsoap_eml2_1::witsml20__Well* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		//Well(gsoap_eml2_3::_resqml22__Well* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}
	};
}
