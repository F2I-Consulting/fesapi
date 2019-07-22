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

#include "witsml2_0/AbstractObject.h"
#include "witsml2_0/Wellbore.h"
#include "witsml2_0/WellCompletion.h"

namespace WITSML2_0_NS
{
	class Well : public WITSML2_0_NS::AbstractObject
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		Well(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WITSML2_0_NS::AbstractObject(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param repo	The dataobject repo where the underlying gsoap proxy is going to be created.
		* @param guid	The guid to set to this instance. If empty then a new guid will be generated.
		*/
		Well(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid,
			const std::string & title);

		Well(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid,
			const std::string & title,
			const std::string & operator_,
			gsoap_eml2_1::eml21__WellStatus statusWell,
			gsoap_eml2_1::witsml2__WellDirection directionWell
		);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		Well(gsoap_eml2_1::witsml2__Well* fromGsoap):AbstractObject(fromGsoap)  {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~Well() {}

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NameLegal)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NumLicense)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NumGovt)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Field)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Country)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, State)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, County)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Region)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, District)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Block)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Operator)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, OperatorDiv)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, OriginalOperator)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NumAPI)

		// Optional enum
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::eml21__WellStatus, StatusWell)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml2__WellPurpose, PurposeWell)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml2__WellFluid, FluidWell)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml2__WellDirection, DirectionWell)

		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(WaterDepth, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(GroundElevation, gsoap_eml2_1::eml21__LengthUom)

		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(PcInterest, gsoap_eml2_1::eml21__DimensionlessUom)

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimLicense)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimSpud)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(time_t, DTimPa)

		/**
		* Set the time zone in which the well is located. It is the deviation in hours and minutes from UTC. This should be the normal time zone at the well and not a seasonally-adjusted value, such as daylight savings time
		*
		* @param direction	True means the time zone is a positive offset from UTC, false means the time zone is a negative offset from UTC
		* @param hours		the deviation hours from UTC
		* @param minutes	the deviation minutes from UTC
		*/
		DLL_IMPORT_OR_EXPORT void setTimeZone(bool direction, unsigned short hours, unsigned short minutes = 0);
		GETTER_PRESENCE_ATTRIBUTE(TimeZone)
		/**
		* Get the time zone direction in which the well is located.
		*
		* @return True means the time zone is a positive offset from UTC, false means the time zone is a negative offset from UTC. If the time zone is Z then an arbitrary '+' is returned.
		*/
		DLL_IMPORT_OR_EXPORT bool getTimeZoneDirection() const;
		/**
		* Get the time zone hour(s) in which the well is located.
		* Must be used with getTimeZoneDirection and getTimeZoneMinute() to have the complete time zone.
		*
		* @return the deviation hour(s) from UTC
		*/
		DLL_IMPORT_OR_EXPORT unsigned short getTimeZoneHours() const;
		/**
		* Get the time zone minute(s) in which the well is located.
		* Must be used with getTimeZoneDirection and getTimeZoneHour() to have the complete time zone.
		*
		* @return the deviation minute(s) from UTC
		*/
		DLL_IMPORT_OR_EXPORT unsigned short getTimeZoneMinutes() const;

		DLL_IMPORT_OR_EXPORT double getLocationProjectedX(unsigned int locationIndex);
		DLL_IMPORT_OR_EXPORT double getLocationProjectedY(unsigned int locationIndex);

		DLL_IMPORT_OR_EXPORT void pushBackLocation(
			const std::string & guid,
			double projectedX,
			double projectedY,
			unsigned int projectedCrsEpsgCode);

		DLL_IMPORT_OR_EXPORT unsigned int geLocationCount() const;
		
		DLL_IMPORT_OR_EXPORT void pushBackDatum(
			const std::string & guid, 
			const std::string & title,
			gsoap_eml2_1::eml21__WellboreDatumReference code,
			const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom elevationUnit,
			double elevation,
			unsigned int verticalCrsEpsgCode);

		DLL_IMPORT_OR_EXPORT unsigned int getDatumCount() const;

		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::WellboreFeature *> getResqmlWellboreFeatures() const;

		DLL_IMPORT_OR_EXPORT std::vector<Wellbore *> getWellbores() const;

		DLL_IMPORT_OR_EXPORT std::vector<WellCompletion *> getWellcompletions() const;

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		void loadTargetRelationships();
	};
}
