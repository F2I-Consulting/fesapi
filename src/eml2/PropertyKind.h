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

namespace EML2_NS
{
	/**
	 * @brief	Property kinds carry the semantics of property values. They are used to identify if
	 * 			the values are, for example, representing porosity, length, stress tensor, etc.
	 * 			Energistics provides a list of standard property kind that represent the basis for
	 * 			the commonly used properties in the E&amp;P subsurface workflow.
	 */
	class PropertyKind : public COMMON_NS::AbstractObject
	{
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
		DLL_IMPORT_OR_EXPORT std::string getNamingSystem() const;

		/**
		 * Get the title of the parent property kind
		 *
		 * @returns	The title of the parent property kind.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getParentAsString() const = 0;

		/**
		 * Gets a data object reference on the parent local property kind
		 *
		 * @exception	std::invalid_argument	If the parent property kind is not a local one (it is an
		 * 										Energistics standard one).
		 *
		 * @returns	The data object reference of the associated parent local property kind.
		 */
		virtual COMMON_NS::DataObjectReference getParentPropertyKindDor() const = 0;

		/**
		 * Gets the parent local property kind
		 *
		 * @exception	std::invalid_argument	If the parent property kind is not a local one (it is an
		 * 										Energistics standard one).
		 *
		 * @returns	The parent local property kind.
		 */
		DLL_IMPORT_OR_EXPORT PropertyKind* getParentPropertyKind() const;

		/**
		 * Sets the parent property kind of this property kind
		 *
		 * @exception	std::invalid_argument	If @c parentPropertyKind is null.
		 *
		 * @param [in]	parentPropertyKind	The parent property kind to set to this property kind.
		 */
		DLL_IMPORT_OR_EXPORT void setParentPropertyKind(PropertyKind* parentPropertyKind);

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

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

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

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PropertyKind(gsoap_eml2_2::eml22__PropertyKind* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PropertyKind(gsoap_eml2_3::eml23__PropertyKind* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		 * Sets XML parent property kind
		 *
		 * @param [in,out]	parentPropertyKind	If non-null, the parent property kind.
		 */
		virtual void setXmlParentPropertyKind(PropertyKind* parentPropertyKind) = 0;
	};
}
