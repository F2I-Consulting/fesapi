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

#include "../eml2/PropertyKind.h"

namespace EML2_3_NS
{
	/** A property kind. */
	class PropertyKind final : public EML2_NS::PropertyKind
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT PropertyKind(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : EML2_NS::PropertyKind(partialObject) {}

		/**
		 * Creates a local property type which uses a standard uom and which derives from a standard
		 * Energistics property type.
		 *
		 * @param [in,out]	repo			  	The repo where the underlying gsoap proxy is going to be
		 * 										created.
		 * @param 		  	guid			  	The guid to set to the local 3d crs. If empty then a new
		 * 										guid will be generated.
		 * @param 		  	title			  	The title of the instance.
		 * @param 		  	quantityClass	  	The quantity class of this property kind. It wil
		 * 										constrain its allowed uom collection. The enum comes from
		 * 										Energistics Unit Of Measure.
		 * @param 		  	isAbstract		  	(Optional) Inidcates if this property kind can be used
		 * 										directly by a property or not.
		 * @param [in,out]	parentPropertyKind	(Optional) The parent property kind if this property
		 * 										kind. By default, it is the Energistics root property
		 * 										kind called "property".
		 */
		PropertyKind(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			gsoap_eml2_1::eml21__QuantityClassKind quantityClass, bool isAbstract = false, EML2_NS::PropertyKind* parentPropertyKind = nullptr);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PropertyKind(gsoap_eml2_3::eml23__PropertyKind* fromGsoap) :EML2_NS::PropertyKind(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~PropertyKind() = default;

		/**
		 * Query if this object is abstract
		 *
		 * @returns	True if abstract, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAbstract() const;

		/**
		 * Query if this object is parent partial
		 *
		 * @returns	True if parent partial, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isParentPartial() const;
		
		/**
		* Please do not use: not implemented yet.
		*/
		DLL_IMPORT_OR_EXPORT std::string getBaseUomAsString() const final;

		/**
		 * Get the title of the parent property kind
		 *
		 * @returns	The title of the parent property kind.
		 */
		DLL_IMPORT_OR_EXPORT std::string getParentAsString() const final;

		/**
		 * Gets a data object reference on the parent local property kind
		 *
		 * @exception	std::invalid_argument	If the parent property kind is not a local one (it is an
		 * 										Energistics standard one).
		 *
		 * @returns	The data object reference of the associated parent local property kind.
		 */
		COMMON_NS::DataObjectReference getParentPropertyKindDor() const final;

		/** Loads target relationships */
		void loadTargetRelationships() final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

	private:

		/**
		 * Sets XML parent property kind
		 *
		 * @param [in,out]	parentPropertyKind	If non-null, the parent property kind.
		 */
		void setXmlParentPropertyKind(EML2_NS::PropertyKind* parentPropertyKind);
	};
}
