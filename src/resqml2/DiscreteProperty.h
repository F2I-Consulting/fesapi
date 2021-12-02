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

#include "AbstractValuesProperty.h"

#include <limits>

namespace EML2_NS
{
	class ColumnBasedTable;
}

namespace RESQML2_NS
{
	/**
	 * @brief	Proxy class for a discrete  property. Such property contains discrete integer values;
	 * 			typically used to store any type of index. So that the value range can be known
	 * 			before accessing all values, it also optionally stores the minimum and maximum value
	 * 			in the range.
	 */
	class DiscreteProperty : public RESQML2_NS::AbstractValuesProperty
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~DiscreteProperty() = default;

		/**
		 * @brief	Gets the null value in this discrete property.
		 *
		 * @param 	patchIndex	(Optional) Zero-based index of the patch for which we want to get the null value.
		 *
		 * @returns	The null value of this discrete property if present otherwise the maximum int 64 bits
		 * 			value.
		 */
		DLL_IMPORT_OR_EXPORT virtual int64_t getNullValue(uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) const = 0;

		/**
		 * @brief	Checks if a non vector property or a given value of a vector property has got a
		 * 			minimum value already computed (or set).
		 *
		 * @param 	index	(Optional) @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we want to know if a
		 * 					minimum value exists (vector property case).
		 *
		 * @returns	True if there exists a minimum value, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool hasMinimumValue(uint64_t index = 0) const = 0;

		/**
		 * @brief	Gets the minimum value of a non vector property or the minimum value of one given
		 * 			value of a vector property. This minimum value is read (it is not computed).
		 *
		 * @exception	std::logic_error	If this property has no minimum value.
		 *
		 * @param 	index	(Optional) @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we look for the
		 * 					minimum value (vector property case).
		 *
		 * @returns	The minimum value of the non vector property or the minimum value at position @p
		 * 			index of the vector value or @c NaN if @p index is out of range (strictly greater
		 * 			than @p 0 for a non vector property or greater than the vector size for a vector
		 * 			property).
		 */
		DLL_IMPORT_OR_EXPORT virtual int64_t getMinimumValue(uint64_t index = 0) const = 0;

		/**
		 * @brief	Checks if a non vector property or a given value of a vector property has got a
		 * 			maximum value already computed (or set).
		 *
		 * @param 	index	(Optional) @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we want to know if a
		 * 					maximum value exists (vector property case).
		 *
		 * @returns	True if there exists a maximum value, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool hasMaximumValue(uint64_t index = 0) const = 0;

		/**
		 * @brief	Gets the maximum value of a non vector property or the maximum value of one given
		 * 			value of a vector property. This maximum value is read (it is not computed).
		 *
		 * @exception	std::logic_error	If this property has no maximum value.
		 *
		 * @param 	index	(Optional) @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we look for the
		 * 					maximum value (vector property case).
		 *
		 * @returns	The maximum value of the non vector property or the maximum value at position @p
		 * 			index of the vector value or @c NaN if @p index is out of range (strictly greater
		 * 			than @p 0 for a non vector property or greater than the vector size for a vector
		 * 			property).
		 */
		DLL_IMPORT_OR_EXPORT virtual int64_t getMaximumValue(uint64_t index = 0) const = 0;

		/**
		 * @brief	Sets the minimum value of a non vector property or the minimum value of one given
		 * 			value of a vector property.
		 *
		 * @param 	value	The minimum value to set.
		 * @param 	index	(Optional)  @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we want to set the
		 * 					minimum value (vector property case).
		 */
		DLL_IMPORT_OR_EXPORT virtual void setMinimumValue(int64_t value, uint64_t index = 0) const = 0;

		/**
		 * @brief	Sets the maximum value of a non vector property or the maximum value of one given
		 * 			value of a vector property.
		 *
		 * @param 	value	The maximum value to set.
		 * @param 	index	(Optional)  @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we want to set the
		 * 					maximum value (vector property case).
		 */
		DLL_IMPORT_OR_EXPORT virtual void setMaximumValue(int64_t value, uint64_t index = 0) const = 0;

		/**
		 * Gets the DOR of the lookup which is associated to this categorical property values.
		 *
		 * @returns	The DOR of the lookup which is associated to this categorical property.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getLookupDor() const = 0;

		/**
		 * @brief	Gets the lookup table which is associated to this categorical property values.
		 *
		 * @returns	A pointer to the lookup table which is associated to this categorical property
		 * 			 values.
		 */
		DLL_IMPORT_OR_EXPORT EML2_NS::ColumnBasedTable* getLookup() const;

	protected:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		DiscreteProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractValuesProperty(partialObject) {}

		/** Default constructor */
		DiscreteProperty() = default;

		/**
		* Creates an instance of this class by wrapping a gSOAP instance.
		*
		* @param [in]	fromGsoap	If non-null, the gSOAP instance.
		*/
		DiscreteProperty(gsoap_resqml2_0_1::_resqml20__DiscreteProperty* fromGsoap) : AbstractValuesProperty(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP RESQML2.0.1 instance
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		DiscreteProperty(gsoap_resqml2_0_1::_resqml20__CategoricalProperty* fromGsoap) : AbstractValuesProperty(fromGsoap) {}

		/**
		* Creates an instance of this class by wrapping a gSOAP instance.
		*
		* @param [in]	fromGsoap	If non-null, the gSOAP instance.
		*/
		DiscreteProperty(gsoap_eml2_3::_resqml22__DiscreteProperty* fromGsoap) : AbstractValuesProperty(fromGsoap) {}

		/** Loads target relationships */
		void loadTargetRelationships() final;
	};
}
