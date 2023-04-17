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

#include "../witsml2/Wellbore.h"

namespace WITSML2_1_NS
{
	/**
	 * @brief	A wellbore represents the path from surface to a unique bottomhole location.
	 */
	class Wellbore : public WITSML2_NS::Wellbore
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT Wellbore(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WITSML2_NS::Wellbore(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWell == nullptr</tt>.
		 *
		 * @param [in]	witsmlWell	If non-null, the witsml well.
		 * @param 	  	guid	  	The guid to set to this instance. If empty then a new guid will be
		 * 							generated.
		 * @param 	  	title	  	The title.
		 * @param 	  	isActive	  	True if is active, false if not.
		 */
		Wellbore(WITSML2_NS::Well* witsmlWell,
			const std::string & guid,
			const std::string & title,
			bool isActive);

		/**
		 * @brief	Constructor
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWell == nullptr</tt>.
		 *
		 * @param [in]	witsmlWell	  	If non-null, the witsml well.
		 * @param 	  	guid		  	Unique identifier.
		 * @param 	  	title		  	The title.
		 * @param 	  	statusWellbore	The status wellbore.
		 * @param 	  	isActive	  	True if is active, false if not.
		 * @param 	  	achievedTD	  	True to achieved td.
		 */
		Wellbore(WITSML2_NS::Well* witsmlWell,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_3::eml23__WellStatus statusWellbore,
			bool isActive,
			bool achievedTD
		);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		Wellbore(gsoap_eml2_3::witsml21__Wellbore* fromGsoap) : WITSML2_NS::Wellbore(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~Wellbore() = default;

		/**
		 * @brief	Gets well dor
		 *
		 * @returns	The well dor.
		 */
		COMMON_NS::DataObjectReference getWellDor() const final;

		/**
		 * Sets a well
		 *
		 * @param [in,out]	witsmlWell	If non-null, the witsml well.
		 */
		DLL_IMPORT_OR_EXPORT void setWell(WITSML2_NS::Well* witsmlWell) final;

		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Number)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, SuffixAPI)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NumGovt)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::eml23__WellStatus, StatusWellbore)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::witsml21__WellPurpose, PurposeWellbore)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::witsml21__WellboreType, TypeWellbore)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::witsml21__WellboreShape, Shape)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::witsml21__WellFluid, FluidWellbore)
		FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, AchievedTD)
		FINAL_GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(Md, gsoap_eml2_3::eml23__LengthUom)
		FINAL_GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdBit, gsoap_eml2_3::eml23__LengthUom)
		FINAL_GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdKickoff, gsoap_eml2_3::eml23__LengthUom)
		FINAL_GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdPlanned, gsoap_eml2_3::eml23__LengthUom)
		FINAL_GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdSubSeaPlanned, gsoap_eml2_3::eml23__LengthUom)

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
