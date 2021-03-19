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
	/** A WellboreMarker. */
	class WellboreMarker : public WITSML2_NS::WellboreObject
	{
	public:

		/**
		 * Constructor for partial transfer
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT WellboreMarker(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WITSML2_NS::WellboreObject(partialObject) {}

		/**
		 * @brief	Constructor
		 *
		 * @exception	std::invalid_argument	If <tt>repo == nullptr</tt>.
		 *
		 * @param	[in,out]	repo 	The repo where the underlying gsoap proxy is going to be created.
		 * @param 	  			guid	Unique identifier.
		 * @param 	  			title	The title.
		 * @param 	  			md		The Measured Depth to set to this marker.
		 * @param 	  			mdUom	The underlying unit of measure of the MD value.
		 * @param 				mdDatum	A free string to unformally indicate the datum of the MD (i.e. where MD==0).
		 */
		WellboreMarker(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid,
			const std::string & title,
			double md, gsoap_eml2_1::eml21__LengthUom mdUom, const std::string & mdDatum);

		/**
		 * @brief	Constructor
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWellbore == nullptr</tt>.
		 *
		 * @param [in]	witsmlWellbore	If non-null, the witsml wellbore.
		 * @param 	  	guid		  	Unique identifier.
		 * @param 	  	title		  	The title.
		 * @param 	  	md		  		The Measured Depth to set to this marker.
		 * @param 	  	mdUom			The underlying unit of measure of the MD value.
		 * @param 	  	mdDatum		  	A free string to unformally indicate the datum of the MD (i.e. where MD==0).
		 */
		WellboreMarker(WITSML2_NS::Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			double md, gsoap_eml2_1::eml21__LengthUom mdUom, const std::string & mdDatum);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		WellboreMarker(gsoap_eml2_1::witsml20__WellboreMarker* fromGsoap) : WITSML2_NS::WellboreObject(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~WellboreMarker() = default;

		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getWellboreDor() const final;
		DLL_IMPORT_OR_EXPORT void setWellbore(WITSML2_NS::Wellbore* witsmlWellbore) final;

		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(Md, gsoap_eml2_1::eml21__LengthUom)

		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(DipAngle, gsoap_eml2_1::eml21__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(DipDirection, gsoap_eml2_1::eml21__PlaneAngleUom)

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char XML_NS[] = "witsml20";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
