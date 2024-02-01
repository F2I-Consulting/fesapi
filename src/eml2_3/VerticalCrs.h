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

namespace EML2_3_NS
{
	/** A vertical crs. */
	class VerticalCrs final : public COMMON_NS::AbstractObject
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT VerticalCrs(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		 * Construct a VerticalCrs deriving from an EPSG vertical CRS
		 *
		 * @param [in,out]	repo		  		If non-null, the repo.
		 * @param 		  	guid		  		Unique identifier.
		 * @param 		  	title		  		The title.
		 * @param 		  	verticalEpsgCode	The EPSG code of the vertical CRS
		 * @param 		  	verticalUom  		The vertical axis uom.
		 * @param 		  	isUpOriented		Defines if the vertical CRS axis is up oreinted or not.
		 */
		VerticalCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
			uint64_t verticalEpsgCode,
			gsoap_eml2_3::eml23__LengthUom verticalUom,
			bool isUpOriented);

		/**
		 * Construct a VerticalCrs deriving from an unknown vertical CRS
		 *
		 * @param [in,out]	repo		  		If non-null, the repo.
		 * @param 		  	guid		  		Unique identifier.
		 * @param 		  	title		  		The title.
		 * @param 		  	unknownReason		The reason why this CRS is unknown.
		 * @param 		  	verticalUom  		The projected uom.
		 * @param 		  	isUpOriented		Defines if the vertical CRS axis is up oreinted or not.
		 */
		VerticalCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
			std::string unknownReason,
			gsoap_eml2_3::eml23__LengthUom verticalUom,
			bool isUpOriented);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		VerticalCrs(gsoap_eml2_3::_eml23__VerticalCrs* fromGsoap): COMMON_NS::AbstractObject(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~VerticalCrs() = default;

		/**
		 * Indicates either the associated vertical CRS is identified by means of EPSG or not.
		 *
		 * @returns	True if the vertical CRS is defined with an EPSG code, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isVerticalCrsDefinedWithEpsg() const;

		/**
		 * Indicates either the associated vertical CRS is unknown or not.
		 *
		 * @returns	True if vertical CRS is unknown, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isVerticalCrsUnknown() const;

		/**
		 * Gets the reason why the vertical CRS is unknown.
		 *
		 * @exception	std::invalid_argument	If the associated vertical CRS is not unknown.
		 *
		 * @returns	The vertical CRS unknown reason.
		 */
		DLL_IMPORT_OR_EXPORT std::string getVerticalCrsUnknownReason() const;

		/**
		 * Gets the EPSG code of the vertical CRS
		 *
		 * @exception	std::invalid_argument	If the associated projected CRS is not an EPSG one.
		 *
		 * @returns	The vertical CRS EPSG code.
		 */
		DLL_IMPORT_OR_EXPORT int64_t getVerticalCrsEpsgCode() const;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "eml23";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "VerticalCrs";

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

		void loadTargetRelationships() final {}

	private:

		void init(gsoap_eml2_3::eml23__VerticalCrs* verticalCrs, const std::string& guid, const std::string& title,
			gsoap_eml2_3::eml23__LengthUom verticalUom,
			bool isUpOriented);
	};
}
