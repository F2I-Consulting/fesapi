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

/** . */
namespace RESQML2_0_1_NS
{
	/** A property kind. */
	class PropertyKind : public EML2_NS::PropertyKind
	{
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

	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
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
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & parentEnergisticsPropertyKind);

		/**
		 * Creates a local property type which uses a standard uom and which derives from another local
		 * property type.
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
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, EML2_NS::PropertyKind * parentPropType);

		/**
		 * Creates a local property type which uses a non standard uom and which derives from a standard
		 * Energistics property type.
		 *
		 * @param [in,out]	repo						 	The repo where the underlying gsoap proxy is
		 * 													going to be created.
		 * @param 		  	guid						 	The guid to set to the local 3d crs. If empty
		 * 													then a new guid will be generated.
		 * @param 		  	title						 	The title of the instance.
		 * @param 		  	namingSystem				 	The name of the dictionary within which the
		 * 													property is unique.
		 * 													@apram nonStandardUom					The non standard
		 * 													uom of the values.
		 * @param 		  	nonStandardUom				 	The non standard uom.
		 * @param 		  	parentEnergisticsPropertyKind	The name of the parent property type in the
		 * 													Energistics property dictionary.
		 */
		PropertyKind(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & parentEnergisticsPropertyKind);

		/**
		 * Creates a local property type which uses a non standard uom which derives from another local
		 * property type.
		 *
		 * @param 		  	guid		  	The guid to set to the local 3d crs. If empty then a new guid
		 * 									will be generated.
		 * @param 		  	title		  	The title of the instance.
		 * @param 		  	namingSystem  	The name of the dictionary within which the property is
		 * 									unique.
		 * 									@apram nonStandardUom					The non standard uom of the values.
		 * @param 		  	nonStandardUom	The non standard uom.
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
		DLL_IMPORT_OR_EXPORT bool isAbstract() const;

		/**
		 * Query if this object is parent partial
		 *
		 * @returns	True if parent partial, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isParentPartial() const;

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
	};
}
