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

/** @brief */
namespace RESQML2_NS
{
	class AbstractProperty;

	/**
	 * Proxy class for a property set. A property set is a set of properties collected together for
	 * a specific purpose. For example, a property set can be used to collect all the properties
	 * corresponding to the simulation output at a single time, or all the values of a single
	 * property kind for all times.
	 */
	class PropertySet : public COMMON_NS::AbstractObject
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT PropertySet(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~PropertySet() {}

		/**
		 * Sets the parent property set of this instance.
		 *
		 * @exception	std::invalid_argument	If @p parent is nullptr.
		 *
		 * @param [in]	parent	The parent to set to this instance.
		 */
		DLL_IMPORT_OR_EXPORT void setParent(PropertySet * parent);

		/**
		 * Gets the data object reference of the parent property set of this instance.
		 *
		 * @returns	Empty data object reference if no parent property set is defined, else the data
		 * 			object reference of the parent property set.
		 */
		virtual COMMON_NS::DataObjectReference getParentDor() const = 0;

		/**
		 * Gets the parent property set of this instance.
		 *
		 * @returns	A pointer to the parent property set or nullptr if no parent property set is defined.
		 */
		DLL_IMPORT_OR_EXPORT PropertySet * getParent() const;

		/**
		 * Gets the children property set of this instance.
		 *
		 * @returns	A vector of pointer to the children property set or empty vector if this instance has
		 * 			no child property set.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<PropertySet *> getChildren() const;

		/**
		 * Gets the count of all children property set of this instance.
		 *
		 * @exception	std::range_error	If the count of children property set is strictly greater
		 * 									than unsigned int max.
		 *
		 * @returns	The children count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getChildrenCount() const;

		/**
		 * Gets a particular child property set of this property set.
		 *
		 * @exception	std::out_of_range	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the child property set we look for.
		 *
		 * @returns	The child property set at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT PropertySet* getChildren(unsigned int index) const;

		/**
		 * Pushes back a property into this property set.
		 *
		 * @exception	std::invalid_argument	If @p prop is nullptr.
		 *
		 * @param [in]	prop	The property to push into this property set.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackProperty(RESQML2_NS::AbstractProperty * prop);

		/**
		 * Gets all properties directly contained in this property set. "Directly contained" means that
		 * this method does not collect properties contained in the children property set.
		 *
		 * @returns	The vector of pointer to all the contained properties.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_NS::AbstractProperty *> getProperties() const;

		/**
		 * Gets the count of all properties directly contained in this property set. "Directly
		 * contained" means that this method does not count properties contained in the children
		 * property set.
		 *
		 * @returns	The count of contained properties.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPropertyCount() const;

		/**
		 * Gets a particular property among the properties directly contained in this property set.
		 * "Directly contained" means that this method does not look at properties contained in the
		 * children property set.
		 *
		 * @exception	std::out_of_range	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the property we look for.
		 *
		 * @returns	The contained property at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractProperty* getProperty(unsigned int index) const;

		/**
		 * Checks whether this property set contains at least one property with multiple realization
		 * indices. This method just read the @c HasMultipleRealizations attribute value. The value of
		 * this attribute only concerns properties directly contained in this property set and thus does
		 * not inform about properties contained in the children property set.
		 *
		 * @returns	True if this property set contains properties with multiple realization indices,
		 * 			false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool hasMultipleRealizations() const = 0;

		/**
		 * Checks whether this property set contains only property values associated with a single
		 * property kind. This method just read the @c HasSinglePropertyKind attribute value. The value
		 * of this attribute only concerns properties directly contained in this property set and thus
		 * does not inform about properties contained in the children property set.
		 *
		 * @returns	True if this property set contains only property values associated with a single
		 * 			property kind.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool hasSinglePropertyKind() const = 0;

		/**
		 * Gets the time set kind that applies on all properties directly contained in this property
		 * set. "Directly contained" means that the time set kind does not apply on properties contained
		 * in the children property set.
		 *
		 * @returns	The time set kind associated to this this property set.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_eml2_3::resqml22__TimeSetKind getTimeSetKind() const = 0;

		/** The standard XML tag without XML namespace for serializing this data object */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Gets the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

		/** Loads target relationships */
		void loadTargetRelationships() final;

	protected:

		/** Default constructor does nothing */
		PropertySet() : COMMON_NS::AbstractObject() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PropertySet(gsoap_resqml2_0_1::_resqml20__PropertySet* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PropertySet(gsoap_eml2_3::_resqml22__PropertySet* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

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

		virtual std::vector<COMMON_NS::DataObjectReference> getAllPropertiesDors() const = 0;
	};
}
