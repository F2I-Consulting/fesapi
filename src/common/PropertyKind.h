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

#include "AbstractObject.h"

namespace COMMON_NS
{
	/** Proxy class for property kinds. */
	class PropertyKind : public COMMON_NS::AbstractObject
	{
	protected:

		/** Default constructor does nothing */
		PropertyKind() {}

		/**
		 * Constructor. Only to be used in partial transfer context
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT PropertyKind(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PropertyKind(gsoap_resqml2_0_1::_resqml20__PropertyKind* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PropertyKind(gsoap_eml2_1::eml21__PropertyKind* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context */
		virtual ~PropertyKind() {}

		/**
		 * Gets (in read only mode) the naming system of this property type. It is the name of the
		 * dictionary within which the property is unique. This also defines the name of the controlling
		 * authority. It is an URN of the form <tt>urn:x-resqml:domainOrEmail:dictionaryName</tt>
		 *
		 * @returns	The naming system.
		 */
		DLL_IMPORT_OR_EXPORT const std::string & getNamingSystem() const;

		/**
		 * Gets the unit of measure of the values of this property kind
		 *
		 * @returns	The unit of measure.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlUom getUom() const;

		/**
		 * Gets the unit of measure of the values of this property kind as a string
		 *
		 * @returns	The unit of measure as a string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getUomAsString() const;

		/**
		 * Get the title of the parent property kind
		 *
		 * @returns	The title of the parent property kind.
		 */
		DLL_IMPORT_OR_EXPORT std::string getParentAsString() const;

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

		/**
		 * Gets a data object reference on the parent local property kind
		 *
		 * @exception	std::invalid_argument	If the parent property kind is not a local one (it is an
		 * 										Energistics standard one).
		 *
		 * @returns	The data object reference of the associated parent local property kind.
		 */
		gsoap_resqml2_0_1::eml20__DataObjectReference* getParentLocalPropertyKindDor() const;

		/**
		 * Gets the UUID of the parent local property kind
		 *
		 * @exception	std::invalid_argument	If the parent property kind is not a local one (it is an
		 * 										Energistics standard one).
		 *
		 * @returns	The UUID of the parent local property kind UUID.
		 */
		DLL_IMPORT_OR_EXPORT std::string getParentLocalPropertyKindUuid() const;

		/**
		 * Gets the title of the parent local property kind
		 *
		 * @exception	std::invalid_argument	If the parent property kind is not a local one (it is an
		 * 										Energistics standard one).
		 *
		 * @returns	The title of the parent local property kind.
		 */
		DLL_IMPORT_OR_EXPORT std::string getParentLocalPropertyKindTitle() const;

		/**
		 * Gets the parent local property kind
		 *
		 * @exception	std::invalid_argument	If the parent property kind is not a local one (it is an
		 * 										Energistics standard one).
		 *
		 * @returns	The parent local property kind.
		 */
		DLL_IMPORT_OR_EXPORT PropertyKind* getParentLocalPropertyKind() const;

		/**
		 * Sets the parent property kind of this property kind
		 *
		 * @exception	std::invalid_argument	If @c parentPropertyKind is null.
		 *
		 * @param [in]	parentPropertyKind	The parent property kind to set to this property kind.
		 */
		DLL_IMPORT_OR_EXPORT void setParentPropertyKind(PropertyKind* parentPropertyKind);

		/**
		 * Checks if this property kind is a child of a particular standard Energistics property kind
		 *
		 * @exception	std::invalid_argument	If this property kind is partial, so that we cannot
		 * 										consequently get its parents.
		 * @exception	std::invalid_argument	If a required property kind mapping files is not loaded.
		 *
		 * @param 	standardPropKind	A standard Energistics property kind.
		 *
		 * @returns	True if this property kind is a child of @c standardPropKind, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isChildOf(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind standardPropKind) const = 0;

		/**
		 * Checks if this property kind is abstract or not
		 *
		 * @returns	True if abstract, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAbstract() const = 0;

		/**
		 * Checks if this property kind is partial or if one of its parent is partial.
		 *
		 * @returns	True if this property kind or one of its parent is partial, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isParentPartial() const = 0;

		/** The standard XML tag without XML namespace for serializing this data object */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Gets the standard XML tag without XML namespace for serializing this data object
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

	protected:

		/**
		 * Sets XML parent property kind
		 *
		 * @param [in,out]	parentPropertyKind	If non-null, the parent property kind.
		 */
		virtual void setXmlParentPropertyKind(PropertyKind* parentPropertyKind) = 0;

		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
