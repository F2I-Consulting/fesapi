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

/** . */
namespace RESQML2_NS
{
	/** An abstract property. */
	class AbstractProperty;

	/**
	 * A set of properties collected together for a specific purpose. For example, a property set
	 * can be used to collect all the properties corresponding to the simulation output at a single
	 * time, or all the values of a single property kind for all times.
	 */
	class PropertySet : public COMMON_NS::AbstractObject
	{
	protected:

		/** Default constructor does nothing */
		PropertySet() : COMMON_NS::AbstractObject() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PropertySet(gsoap_resqml2_0_1::_resqml20__PropertySet* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}protected:

		/**
		 * Sets XML parent
		 *
		 * @param [in,out]	parent	If non-null, the parent.
		 */
		virtual void setXmlParent(PropertySet * parent) = 0;

		/**
		 * Pushes a back XML property
		 *
		 * @param [in,out]	prop	If non-null, the property.
		 */
		virtual void pushBackXmlProperty(RESQML2_NS::AbstractProperty * prop) = 0;

		/**
		 * Gets all properties dors
		 *
		 * @returns	Null if it fails, else all properties dors.
		 */
		virtual std::vector<gsoap_resqml2_0_1::eml20__DataObjectReference *> getAllPropertiesDors() const = 0;

	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT PropertySet(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~PropertySet() {}

		/**
		 * Set the parent property set of this instance.
		 *
		 * @param [in,out]	parent	If non-null, the parent.
		 */
		DLL_IMPORT_OR_EXPORT void setParent(PropertySet * parent);

		/**
		 * Gets the parent dor
		 *
		 * @returns	Null if it fails, else the parent dor.
		 */
		virtual gsoap_resqml2_0_1::eml20__DataObjectReference const * getParentDor() const = 0;

		/**
		 * Get the parent property set uuid of this instance
		 *
		 * @returns	the parent property set uuid or empty string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getParentUuid() const;

		/**
		 * Get the parent property set of this instance
		 *
		 * @returns	the parent property set or nullptr.
		 */
		DLL_IMPORT_OR_EXPORT PropertySet * getParent() const;

		/**
		 * Get the children property set of this instance
		 *
		 * @returns	the children property set or empty vector.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<PropertySet *> getChildren() const;

		/**
		 * Get the count of all properties directly contained in this property set.
		 *
		 * @returns	The children count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getChildrenCount() const;

		/**
		 * Get a particular property of this property set.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	Null if it fails, else the children.
		 */
		DLL_IMPORT_OR_EXPORT PropertySet* getChildren(unsigned int index) const;

		/**
		 * Push back a property into this property set.
		 *
		 * @param [in,out]	prop	If non-null, the property.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackProperty(RESQML2_NS::AbstractProperty * prop);

		/**
		 * Get all properties directly contained in this property set.
		 *
		 * @returns	Null if it fails, else the properties.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_NS::AbstractProperty *> getProperties() const;

		/**
		 * Get the count of all properties directly contained in this property set.
		 *
		 * @returns	The property count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPropertyCount() const;

		/**
		 * Get a particular property of this property set.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	Null if it fails, else the property.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractProperty* getProperty(unsigned int index) const;

		/**
		 * If true, indicates that the collection contains properties with defined realization indices.
		 *
		 * @returns	True if multiple realizations, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool hasMultipleRealizations() const = 0;

		/**
		 * If true, indicates that the collection contains only property values associated with a single
		 * property kind.
		 *
		 * @returns	True if single property kind, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool hasSinglePropertyKind() const = 0;

		/**
		 * Gets time set kind
		 *
		 * @returns	The time set kind of this property set.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::resqml20__TimeSetKind getTimeSetKind() const = 0;

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

		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
