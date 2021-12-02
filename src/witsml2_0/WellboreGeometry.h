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

#include "../witsml2/WellboreObject.h"

#include "../MacroDefinitions.h"

namespace WITSML2_0_NS
{
	/**
	 * Captures information about the configuration of the permanently installed components in a
	 * wellbore. It does not define the transient drilling strings (see the Tubular object) or the
	 * hanging production components (see the Completion object).
	 */
	class WellboreGeometry : public WITSML2_NS::WellboreObject
	{
	public:

		/**
		 * Constructor for partial transfer
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT WellboreGeometry(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WITSML2_NS::WellboreObject(partialObject) {}

		/**
		 * @brief	Constructor
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWellbore == nullptr</tt>.
		 *
		 * @param [in]	witsmlWellbore	If non-null, the witsml wellbore.
		 * @param 	  	guid		  	Unique identifier.
		 * @param 	  	title		  	The title.
		 * @param 	  	channelStatus 	The channel status.
		 */
		WellboreGeometry(WITSML2_NS::Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::witsml20__ChannelStatus channelStatus);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		WellboreGeometry(gsoap_eml2_1::witsml20__WellboreGeometry* fromGsoap) : WITSML2_NS::WellboreObject(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~WellboreGeometry() = default;

		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getWellboreDor() const final;
		DLL_IMPORT_OR_EXPORT void setWellbore(WITSML2_NS::Wellbore* witsmlWellbore) final;

		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdBase, gsoap_eml2_1::eml21__LengthUom)

		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(GapAir, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(DepthWaterMean, gsoap_eml2_1::eml21__LengthUom)

		//***************************************
		//************** SECTION ****************
		//***************************************

		// Mandatory
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(std::string, WellboreGeometrySection, uid)

		// Optional bool
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, WellboreGeometrySection, CurveConductor)

		// Optional double
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(double, WellboreGeometrySection, FactFric)

		// Optional string
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, WellboreGeometrySection, Grade)

		// Optional enum
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_1::witsml20__HoleCasingType, WellboreGeometrySection, TypeHoleCasing)

		// Optional Length Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, IdSection, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, OdSection, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, DiaDrift, gsoap_eml2_1::eml21__LengthUom)

		// Optional Mass per Length Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, WtPerLen, gsoap_eml2_1::eml21__MassPerLengthUom)

		/**
		 * Sets wellbore geometry section md interval
		 *
		 * @param 	index	Zero-based index of the.
		 * @param 	top  	The top.
		 * @param 	base 	The base.
		 * @param 	datum	The datum.
		 * @param 	uom  	The uom.
		 */
		DLL_IMPORT_OR_EXPORT void setWellboreGeometrySectionMdInterval(uint64_t index, double top, double base, const std::string & datum, gsoap_eml2_1::eml21__LengthUom uom);

		/**
		 * Gets wellbore geometry section md interval top
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The wellbore geometry section md interval top.
		 */
		DLL_IMPORT_OR_EXPORT double getWellboreGeometrySectionMdIntervalTop(uint64_t index) const;

		/**
		 * Gets wellbore geometry section md interval top uom
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The wellbore geometry section md interval top uom.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__LengthUom getWellboreGeometrySectionMdIntervalTopUom(uint64_t index) const;

		/**
		 * Gets wellbore geometry section md interval base
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The wellbore geometry section md interval base.
		 */
		DLL_IMPORT_OR_EXPORT double getWellboreGeometrySectionMdIntervalBase(uint64_t index) const;

		/**
		 * Gets wellbore geometry section md interval base uom
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The wellbore geometry section md interval base uom.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__LengthUom getWellboreGeometrySectionMdIntervalBaseUom(uint64_t index) const;

		/**
		 * Gets wellbore geometry section md intervaldatum
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The wellbore geometry section md intervaldatum.
		 */
		DLL_IMPORT_OR_EXPORT std::string getWellboreGeometrySectionMdIntervaldatum(uint64_t index) const;

		/**
		 * Query if 'index' has wellbore geometry section md interval
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if wellbore geometry section md interval, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasWellboreGeometrySectionMdInterval(uint64_t index) const;

		/**
		 * Sets wellbore geometry section tvd interval
		 *
		 * @param 	index	Zero-based index of the.
		 * @param 	top  	The top.
		 * @param 	base 	The base.
		 * @param 	datum	The datum.
		 * @param 	uom  	The uom.
		 */
		DLL_IMPORT_OR_EXPORT void setWellboreGeometrySectionTvdInterval(uint64_t index, double top, double base, const std::string & datum, gsoap_eml2_1::eml21__LengthUom uom);

		/**
		 * Gets wellbore geometry section tvd interval top
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The wellbore geometry section tvd interval top.
		 */
		DLL_IMPORT_OR_EXPORT double getWellboreGeometrySectionTvdIntervalTop(uint64_t index) const;

		/**
		 * Gets wellbore geometry section tvd interval top uom
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The wellbore geometry section tvd interval top uom.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__LengthUom getWellboreGeometrySectionTvdIntervalTopUom(uint64_t index) const;

		/**
		 * Gets wellbore geometry section tvd interval base
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The wellbore geometry section tvd interval base.
		 */
		DLL_IMPORT_OR_EXPORT double getWellboreGeometrySectionTvdIntervalBase(uint64_t index) const;

		/**
		 * Gets wellbore geometry section tvd interval base uom
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The wellbore geometry section tvd interval base uom.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__LengthUom getWellboreGeometrySectionTvdIntervalBaseUom(uint64_t index) const;

		/**
		 * Gets wellbore geometry section tvd intervaldatum
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The wellbore geometry section tvd intervaldatum.
		 */
		DLL_IMPORT_OR_EXPORT std::string getWellboreGeometrySectionTvdIntervaldatum(uint64_t index) const;

		/**
		 * Query if 'index' has wellbore geometry section tvd interval
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if wellbore geometry section tvd interval, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasWellboreGeometrySectionTvdInterval(uint64_t index) const;

		/**
		 * Push back an empty section into the isntance.
		 *
		 * @param 	uid	(Optional) The UID.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackSection(const std::string & uid = "");

		/**
		 * Get the count of sections in this instance
		 *
		 * @returns	the count of sections in this instance.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getSectionCount() const;

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "WellboreGeometry";

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "witsml20";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
