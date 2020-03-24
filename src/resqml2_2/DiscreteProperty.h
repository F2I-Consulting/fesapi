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

#include "../resqml2/DiscreteProperty.h"

/** . */
namespace RESQML2_2_NS
{
	/**
	 * Proxy class for a discrete  property. Such property contains discrete integer values;
	 * typically used to store any type of index. So that the value range can be known before
	 * accessing all values, it also optionally stores the minimum and maximum value in the range.
	 */
	class DiscreteProperty : public RESQML2_NS::DiscreteProperty
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT DiscreteProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::DiscreteProperty(partialObject) {}


		/**
		 * Creates a discrete property which is of a local property kind.
		 *
		 * @exception	std::invalid_argument	If @p or @p localPropKind is null. If @p dimension is zero.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	dimension	  	The dimension of each value of this property. Dimension is 1 for
		 * 								a scalar property.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param [in]	propKind	 	The property kind of these property values. It cannot be null.
		 */
		DiscreteProperty(RESQML2_NS::AbstractRepresentation* rep, const std::string& guid, const std::string& title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, COMMON_NS::PropertyKind* propKind);

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		DiscreteProperty(gsoap_eml2_3::_resqml22__DiscreteProperty* fromGsoap): RESQML2_NS::DiscreteProperty(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~DiscreteProperty() {}

		/**
		 * Pushes back a reference to an existing (or a "to exist") HDF dataset in a particular HDF
		 * proxy. The reason can be that the index values already exist in an external file (only HDF5
		 * for now) or that the writing of the values in the external file is differed in time.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param [in]	proxy			The HDF5 proxy where the values are already or will be stored. If
		 * 								@c nullptr, then a default HDF proxy must be defined in the
		 * 								repository.
		 * @param 	  	datasetName 	The HDF5 dataset name where the values are stored. If empty, the
		 * 								dataset will be named the same as the dataset naming convention of
		 * 								fesapi :
		 * 								<tt>getHdfGroup() + "/values_patch" +
		 * 								patch-&gt;RepresentationPatchIndex</tt>
		 * @param 	  	nullValue   	The null value which has been chosen in the referenced HDF
		 * 								dataset.
		 * @param 	  	minimumValue	The minimum value of the values in the HDF5 dataset.
		 * @param 	  	maximumValue	The maximum value of the values in the HDF5 dataset.
		 *
		 * @returns	The name of the referenced HDF5 dataset.
		 */
		DLL_IMPORT_OR_EXPORT std::string pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* proxy, const std::string & datasetName, LONG64 nullValue, LONG64 minimumValue, LONG64 maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackRefToExistingDataset;

		/**
		 * Gets the null value in this discrete property.
		 *
		 * @returns	The null value of this discrete property if present otherwise the maximum int 64 bits value.
		 */
		DLL_IMPORT_OR_EXPORT LONG64 getNullValue(unsigned int patchIndex = (std::numeric_limits<unsigned int>::max)()) const;

		/**
		 * Checks if this discrete property has got a minimum value already computed (or set).
		 *
		 * @returns	True if there exists a minimum value, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasMinimumValue(unsigned int index = 0) const;

		/**
		 * Gets the (first by default) minimum value in this discrete properties. It reads it from
		 * file.
		 *
		 * @exception	std::logic_error	If this property has no minimum value.
		 *
		 * @returns	The minimum value if present in the file, else false.
		 */
		DLL_IMPORT_OR_EXPORT LONG64 getMinimumValue(unsigned int index = 0) const;

		/**
		 * Checks if this discrete property has got a maximum value already computed (or set).
		 *
		 * @returns	True if there exists a minimum value, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasMaximumValue(unsigned int index = 0) const;

		/**
		 * Gets the (first by default) maximum value in this discrete properties. It reads it from
		 * file.
		 *
		 * @exception	std::logic_error	If this property has no maximum value.
		 *
		 * @returns	The maximum value if present in the file, else false.
		 */
		DLL_IMPORT_OR_EXPORT LONG64 getMaximumValue(unsigned int index = 0) const;

		/**
		 * Set the minimum value in this discrete property.
		 */
		DLL_IMPORT_OR_EXPORT void setMinimumValue(LONG64 value, unsigned int index = 0) const;

		/**
		 * Set the maximum value in this discrete property.
		 */
		DLL_IMPORT_OR_EXPORT void setMaximumValue(LONG64 value, unsigned int index = 0) const;

		bool validatePropertyKindAssociation(COMMON_NS::PropertyKind* pk) override { return true; }

		bool validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind pk) override { return true; }

	private:

		size_t getMinimumValueSize() const;
		size_t getMaximumValueSize() const;
	};
}
