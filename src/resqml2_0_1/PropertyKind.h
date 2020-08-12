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
#include "PropertyKindMapper.h"

namespace RESQML2_0_1_NS
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
		 * @param [in,out]	repo						 	The repo where the underlying gsoap proxy is
		 * 													going to be created.
		 * @param 		  	guid						 	The guid to set to the local 3d crs. If empty
		 * 													then a new guid will be generated.
		 * @param 		  	title						 	The title of the instance.
		 * @param 		  	namingSystem				 	The name of the dictionary within which the
		 * 													property is unique.
		 * @param 		  	uom							 	The unit of measure of the property type.
		 * @param 		  	parentEnergisticsPropertyKind	The name of the parent property type in the
		 * 													Energistics property dictionary.
		 */
		PropertyKind(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			const std::string & namingSystem, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind parentEnergisticsPropertyKind);

		/**
		 * @brief	Creates a local property type which uses a standard uom and which derives from
		 * 			another local property type.
		 *
		 * @exception	std::invalid_argument	If <tt>parentPropType == nullptr</tt>.
		 *
		 * @param 		  	guid		  	The guid to set to the local 3d crs. If empty then a new guid
		 * 									will be generated.
		 * @param 		  	title		  	The title of the instance.
		 * @param 		  	namingSystem  	The name of the dictionary within which the property is
		 * 									unique.
		 * @param 		  	uom			  	The unit of measure of the property type.
		 * @param [in,out]	parentPropType	The local parent property type in the EPC document.
		 */
		PropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, EML2_NS::PropertyKind * parentPropType);

		/**
		 * @brief	Creates a local property type which uses a non standard uom and which derives from a
		 * 			standard Energistics property type.
		 *
		 * @param [in,out]	repo						 	The repo where the underlying gsoap proxy is
		 * 													going to be created.
		 * @param 		  	guid						 	The guid to set to the local 3d crs. If empty
		 * 													then a new guid will be generated.
		 * @param 		  	title						 	The title of the instance.
		 * @param 		  	namingSystem				 	The name of the dictionary within which the
		 * 													property is unique.
		 * @param 		  	nonStandardUom				 	The non standard uom of the values.
		 * @param 		  	parentEnergisticsPropertyKind	The name of the parent property type in the
		 * 													Energistics property dictionary.
		 */
		PropertyKind(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind parentEnergisticsPropertyKind);

		/**
		 * @brief	Creates a local property type which uses a non standard uom which derives from
		 * 			another local property type.
		 *
		 * @param 		  	guid		  	The guid to set to the local 3d crs. If empty then a new guid
		 * 									will be generated.
		 * @param 		  	title		  	The title of the instance.
		 * @param 		  	namingSystem  	The name of the dictionary within which the property is
		 * 									unique.
		 * @param 		  	nonStandardUom	The non standard uom of the values.
		 * @param [in,out]	parentPropType	The local parent property type in the EPC document.
		 */
		PropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, EML2_NS::PropertyKind * parentPropType);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PropertyKind(gsoap_resqml2_0_1::_resqml20__PropertyKind* fromGsoap) :EML2_NS::PropertyKind(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~PropertyKind() {}

		/**
		 * Is child of the given standard property kind
		 *
		 * @param 	standardPropKind	The standard property kind.
		 *
		 * @returns	True if child of, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isChildOf(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind standardPropKind) const;

		/**
		 * Query if this object is abstract
		 *
		 * @returns	True if abstract, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAbstract() const final;

		/**
		 * Query if this object is parent partial
		 *
		 * @returns	True if parent partial, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isParentPartial() const final;

		/**
		* Get the base unit of measure for conversion of the values of this property kind as a string.
		*
		* @returns The unit or measure of the values of this property kind as a string.
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

		/**
		 * Indicates if the parent property kind is either from the standard catalog of Energistics or
		 * from another local property kind
		 *
		 * @returns	True if the parent is a standard Energistics property kind, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isParentAnEnergisticsPropertyKind() const;

		/**
		 * Gets the standard Energistics parent property kind
		 *
		 * @exception	std::invalid_argument	If the parent property kind is not an Energistics one.
		 *
		 * @returns	The standard Energistics parent property kind.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getParentEnergisticsPropertyKind() const;

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

	protected:

		/**
		 * Sets XML parent property kind
		 *
		 * @param [in,out]	parentPropertyKind	If non-null, the parent property kind.
		 */
		void setXmlParentPropertyKind(EML2_NS::PropertyKind* parentPropertyKind);

		/**
		 * Gets specialized gsoap proxy
		 *
		 * @returns	Null if it fails, else the specialized gsoap proxy.
		 */
		gsoap_resqml2_0_1::_resqml20__PropertyKind* getSpecializedGsoapProxy() const;

		/**
		 * Adds a resqml local property kind to epc document from application property kind name to
		 * 'application'
		 *
		 * @param 	applicationPropertyKindName	Name of the application property kind.
		 * @param 	application				   	The application.
		 *
		 * @returns	Null if it fails, else a pointer to a RESQML2_0_1_NS::PropertyKind.
		 */
		friend RESQML2_0_1_NS::PropertyKind* PropertyKindMapper::addResqmlLocalPropertyKindToEpcDocumentFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application);

	private:

		/**
		 * Initializes this object
		 *
		 * @param [in,out]	repo			If non-null, the repo.
		 * @param 		  	guid			Unique identifier.
		 * @param 		  	title			The title.
		 * @param 		  	namingSystem	The naming system.
		 */
		void init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, const std::string & namingSystem);
	};
}
