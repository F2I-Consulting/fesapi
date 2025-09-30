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

namespace RESQML2_2_NS
{
	/**
	 * Proxy class for a discrete  property. Such property contains discrete integer values;
	 * typically used to store any type of index. So that the value range can be known before
	 * accessing all values, it also optionally stores the minimum and maximum value in the range.
	 */
	class DiscreteProperty final : public RESQML2_NS::DiscreteProperty
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
			unsigned int dimension, gsoap_eml2_3::eml23__IndexableElement attachmentKind, EML2_NS::PropertyKind* propKind);

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		DiscreteProperty(gsoap_eml2_3::_resqml22__DiscreteProperty* fromGsoap): RESQML2_NS::DiscreteProperty(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~DiscreteProperty() = default;

		DLL_IMPORT_OR_EXPORT std::string pushBackRefToExistingIntegerDataset(EML2_NS::AbstractHdfProxy* proxy, const std::string & datasetName, int64_t nullValue, int64_t minimumValue, int64_t maximumValue) final;
		using AbstractValuesProperty::pushBackRefToExistingIntegerDataset;

		DLL_IMPORT_OR_EXPORT int64_t getNullValue(uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) const final;

		DLL_IMPORT_OR_EXPORT bool hasMinimumValue(uint64_t index = 0) const final;

		DLL_IMPORT_OR_EXPORT int64_t getMinimumValue(uint64_t index = 0) const final;

		DLL_IMPORT_OR_EXPORT bool hasMaximumValue(uint64_t index = 0) const final;

		DLL_IMPORT_OR_EXPORT int64_t getMaximumValue(uint64_t index = 0) const final;

		DLL_IMPORT_OR_EXPORT void setMinimumValue(int64_t value, uint64_t index = 0) const final;

		DLL_IMPORT_OR_EXPORT void setMaximumValue(int64_t value, uint64_t index = 0) const final;

		bool validatePropertyKindAssociation(EML2_NS::PropertyKind*) final { return true; }

		bool validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind) final { return true; }

		DLL_IMPORT_OR_EXPORT COMMON_NS::NumberArrayStatistics<int8_t> getInt8Statistics(uint64_t patchIndex) const final { return getStats<int8_t>(patchIndex); }
		DLL_IMPORT_OR_EXPORT COMMON_NS::NumberArrayStatistics<uint8_t> getUInt8Statistics(uint64_t patchIndex) const final { return getStats<uint8_t>(patchIndex); }
		DLL_IMPORT_OR_EXPORT COMMON_NS::NumberArrayStatistics<int16_t> getInt16Statistics(uint64_t patchIndex) const final { return getStats<int16_t>(patchIndex); }
		DLL_IMPORT_OR_EXPORT COMMON_NS::NumberArrayStatistics<uint16_t> getUInt16Statistics(uint64_t patchIndex) const final { return getStats<uint16_t>(patchIndex); }
		DLL_IMPORT_OR_EXPORT COMMON_NS::NumberArrayStatistics<int32_t> getInt32Statistics(uint64_t patchIndex) const final { return getStats<int32_t>(patchIndex); }
		DLL_IMPORT_OR_EXPORT COMMON_NS::NumberArrayStatistics<uint32_t> getUInt32Statistics(uint64_t patchIndex) const final { return getStats<uint32_t>(patchIndex); }
		DLL_IMPORT_OR_EXPORT COMMON_NS::NumberArrayStatistics<int64_t> getInt64Statistics(uint64_t patchIndex) const final { return getStats<int64_t>(patchIndex); }
		DLL_IMPORT_OR_EXPORT COMMON_NS::NumberArrayStatistics<uint64_t> getUInt64Statistics(uint64_t patchIndex) const final { return getStats<uint64_t>(patchIndex); }

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

	private:

		size_t getMinimumValueSize() const;
		size_t getMaximumValueSize() const;

		template<typename T>
		COMMON_NS::NumberArrayStatistics<T> getStats(uint64_t patchIndex) const {
			auto nullValue = getNullValueOfPatch(patchIndex);
			if constexpr (std::is_signed_v<T>) {
				if (nullValue > (std::numeric_limits<T>::max)() || nullValue < (std::numeric_limits<T>::min)()) {
					nullValue = (std::numeric_limits<T>::max)();
				}
			}
			else {
				if (nullValue > 0 || static_cast<uint64_t>(nullValue) < (std::numeric_limits<T>::min)()) {
					nullValue = (std::numeric_limits<T>::max)();
				}
			}
			COMMON_NS::NumberArrayStatistics<T> result;
			result.setNullValue(static_cast<T>(nullValue));

			const auto* valuesforPatch = static_cast<gsoap_eml2_3::_resqml22__DiscreteProperty*>(gsoapProxy2_3)->ValuesForPatch.at(patchIndex);
			auto const* intArray = dynamic_cast<gsoap_eml2_3::eml23__AbstractIntegerArray const*>(valuesforPatch);
			if (intArray == nullptr) return result;

			for (size_t i = 0; i < intArray->Statistics.size(); ++i) {
				auto const* stats = intArray->Statistics[i];
				if (stats->MaximumValue) {
					if constexpr (std::is_signed_v<T>) {
						if (*stats->MaximumValue > (std::numeric_limits<T>::min)() &&
							*stats->MaximumValue < (std::numeric_limits<T>::max)()) {
							result.setMaximum(static_cast<T>(*stats->MaximumValue), i);
						}
					}
					else {
						if (*stats->MaximumValue > 0 &&
							static_cast<uint64_t>(*stats->MaximumValue) < (std::numeric_limits<T>::max)()) {
							result.setMaximum(static_cast<T>(*stats->MaximumValue), i);
						}
					}
				}
				if (stats->MinimumValue) {
					if constexpr (std::is_signed_v<T>) {
						if (*stats->MinimumValue > (std::numeric_limits<T>::min)() &&
							*stats->MinimumValue < (std::numeric_limits<T>::max)()) {
							result.setMinimum(static_cast<T>(*stats->MinimumValue), i);
						}
					}
					else {
						if (*stats->MinimumValue > 0 &&
							static_cast<uint64_t>(*stats->MinimumValue) < (std::numeric_limits<T>::max)()) {
							result.setMinimum(static_cast<T>(*stats->MinimumValue), i);
						}
					}
				}
				if (stats->ModePercentage) {
					result.setModePercentage(*stats->ModePercentage, i);
				}
				if (stats->ValidValueCount) {
					result.setValidValueCount(*stats->ValidValueCount, i);
				}
				if (stats->ValuesMedian) {
					result.setMedian(*stats->ValuesMedian, i);
				}
				if (stats->ValuesMode) {
					if constexpr (std::is_signed_v<T>) {
						if (*stats->ValuesMode > (std::numeric_limits<T>::min)() &&
							*stats->ValuesMode < (std::numeric_limits<T>::max)()) {
							result.setMode(static_cast<T>(*stats->ValuesMode), i);
						}
					}
					else {
						if (*stats->ValuesMode > 0 &&
							static_cast<uint64_t>(*stats->ValuesMode) < (std::numeric_limits<T>::max)()) {
							result.setMode(static_cast<T>(*stats->ValuesMode), i);
						}
					}
				}
			}

			return result;
		}
	};
}
