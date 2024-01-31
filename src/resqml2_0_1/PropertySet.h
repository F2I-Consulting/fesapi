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

namespace RESQML2_NS
{
	class AbstractProperty;
}

namespace RESQML2_0_1_NS
{
	/**
	 * @brief	Proxy class for a property set. A property set is a set of properties collected
	 * 			together for a specific purpose.
	 *
	 * 			For example, a property set can be used to collect all the properties corresponding
	 * 			to the simulation output at a single time, or all the values of a single property
	 * 			kind for all times.
	 */
	class PropertySet final : public COMMON_NS::AbstractObject
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT PropertySet(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>repo == nullptr</tt>.
		 * @exception	std::invalid_argument	If @p timeSetKind is single time series.
		 *
		 * @param [in]	repo				   	The DataObjectRepository where the instance must be
		 * 											created.
		 * @param 	  	guid				   	A guid for the instance to create. Empty guid lead to the
		 * 										creation of a random one.
		 * @param 	  	title				   	A title for the instance to create.
		 * @param 	  	hasMultipleRealizations	If true, indicates that the collection contains
		 * 										properties with defined realization indices.
		 * @param 	  	hasSinglePropertyKind  	If true, indicates that the collection contains only
		 * 										property values associated with a single property kind.
		 * @param 	  	timeSetKind			   	the time set kind of this property set.
		 */
		PropertySet(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title,
			bool hasMultipleRealizations, bool hasSinglePropertyKind, gsoap_resqml2_0_1::resqml20__TimeSetKind timeSetKind);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PropertySet(gsoap_resqml2_0_1::_resqml20__PropertySet* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~PropertySet() = default;

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
		COMMON_NS::DataObjectReference getParentDor() const;

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
		 * @returns	The children count.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getChildrenCount() const noexcept {
			return getChildren().size();
		}

		/**
		 * Gets a particular child property set of this property set.
		 *
		 * @exception	std::out_of_range	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the child property set we look for.
		 *
		 * @returns	The child property set at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT PropertySet* getChildren(uint64_t index) const;

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
		DLL_IMPORT_OR_EXPORT uint64_t getPropertyCount() const noexcept;

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
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractProperty* getProperty(uint64_t index) const;

		DLL_IMPORT_OR_EXPORT bool hasMultipleRealizations() const;

		DLL_IMPORT_OR_EXPORT bool hasSinglePropertyKind() const;

		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__TimeSetKind getTimeSetKind() const;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "resqml20";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

		/** The standard XML tag without XML namespace for serializing this data object */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "PropertySet";

		/**
		 * Gets the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

		/** Loads target relationships */
		void loadTargetRelationships() final;

		/** A fake property is needed when we want to create a property set which does not contain any property (but one or more property sets). */
		static constexpr char const* FAKE_PROP_UUID = "6b6656bb-32c4-4c4a-84ec-f66cf50bd4dd";

	private:

		/**
		 * Sets XML parent
		 *
		 * @param [in,out]	parent	If non-null, the parent.
		 */
		void setXmlParent(PropertySet * parent);

		/**
		 * Pushes a back XML property
		 *
		 * @param [in,out]	prop	If non-null, the property.
		 */
		void pushBackXmlProperty(RESQML2_NS::AbstractProperty * prop);

		std::vector<COMMON_NS::DataObjectReference> getAllPropertiesDors() const;
	};
}
