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

#include "AbstractProperty.h"

#include <algorithm>
#include <stdexcept>

#include "../common/NumberArrayStatistics.h"

namespace RESQML2_NS
{
	/** @brief	Proxy class for an abstract values property. */
	class AbstractValuesProperty : public AbstractProperty
	{
	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractValuesProperty() = default;

		/**
		 * Gets the number of patches in this values property. It should be the same count as the patch
		 * count of the associated representation.
		 *
		 * @exception	std::out_of_range	If the patch count is strictly greater than unsigned int max
		 * 									value.
		 *
		 * @returns	The patch count.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getPatchCount() const final;

		/**
		 * Get the values data type in the HDF dataset
		 *
		 * @returns	The data type of the values if successful, else @c UNKNOWN.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractObject::numericalDatatypeEnum getValuesHdfDatatype() const final;

		/**
		 * Get the number of values in each dimension into the underlying HDF5 dataset.
		 * uint32_t is returned instead of uint64_t cause of some SWIG usage. I cannot SWIG port std::vector<uint64_t>
		 * @param 	patchIndex	The index of the patch we want to count the values from.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<uint32_t> getValuesCountPerDimensionOfPatch(uint64_t patchIndex) const final;

		/**
		 * Pushes back a new facet to this instance. Facets are qualifiers for property values which
		 * allow users to semantically specialize a property without creating a new property kind.
		 *
		 * @param 	facet	  	The facet.
		 * @param 	facetValue	The facet value.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFacet(gsoap_eml2_3::eml23__FacetKind facet, const std::string & facetValue);

		/**
		 * Gets the count of facet of this instance
		 *
		 * @returns	The facet count.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getFacetCount() const;

		/**
		 * Gets the facet at a particular index of the facet collection of this instance.
		 *
		 * @exception	std::out_of_range	If @p index is strictly greater than facet count.
		 *
		 * @param 	index	Zero-based index of the facet we want to get.
		 *
		 * @returns	The facet at index @p index.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__FacetKind getFacetKind(uint64_t index) const;

		/**
		 * Gets the facet value at a particular index of the facet collection of this instance.
		 *
		 * @exception	std::out_of_range	If @p index is strictly greater than facet count.
		 *
		 * @param 	index	Zero-based index of the facet we want to get.
		 *
		 * @returns	The facet value at index @p index.
		 */
		DLL_IMPORT_OR_EXPORT std::string getFacetValue(uint64_t index) const;

		/**
		 * @brief	Adds a nd array of explicit values to the property values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values	  	All the property values to set ordered according to the topology
		 * 								of the representation it is based on.
		 * @param [in]		proxy	  	The HDF proxy where to write the property values. It must be
		 * 								already opened for writing and won't be closed in this method. If
		 * 								@c nullptr, then a default HDF proxy must be defined in the
		 * 								repository.
		 * @param 		  	nullValue			  		The integer null value. Ignored (fixed to NaN) if it is a floating point value.
		 */
		template<typename T> std::enable_if_t<std::is_arithmetic_v<T>, void>
		pushBackArrayOfValues(const T* values, const uint64_t* numValues, uint32_t numDimensionsInArray,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, T nullValue = (std::numeric_limits<T>::max)());

		template<typename T>
		void pushBackArrayOfValuesPlusStatistics(const T* values, const uint64_t* numValues, uint32_t numDimensionsInArray, const COMMON_NS::NumberArrayStatistics<T>& statistics,
			EML2_NS::AbstractHdfProxy* proxy = nullptr) {
			pushBackArrayOfValues(values, numValues, numDimensionsInArray, proxy, statistics.getNullValue());
			setStatistics(statistics, getPatchCount() - 1);
		}
		
		/**
		 * @brief	Adds a 1d array of explicit values to the property values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values	  	All the property values to set ordered according to the topology
		 * 								of the representation it is based on.
		 * @param 		  	valueCount	The number of values to write.
		 * @param [in]		proxy	  	The HDF proxy where to write the property values. It must be
		 * 								already opened for writing and won't be closed in this method. If
		 * 								@c nullptr, then a default HDF proxy must be defined in the
		 * 								repository.
		 * @param 		  	nullValue			  		The integer null value. Ignored (fixed to NaN) if it is a floating point value.
		 */
		template<typename T>
		void pushBackArray1dOfValues(const T* values, uint64_t valueCount,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, T nullValue = (std::numeric_limits<T>::max)()) {
			pushBackArrayOfValues(values, &valueCount, 1, proxy, nullValue);
		}
		template<typename T>
		void pushBackArray1dOfValuesPlusStatistics(const T* values, uint64_t valueCount, const COMMON_NS::NumberArrayStatistics<T>& statistics,
			EML2_NS::AbstractHdfProxy* proxy = nullptr) {
			pushBackArray1dOfValues(values, valueCount, proxy, statistics.getNullValue());
			setStatistics(statistics, getPatchCount() - 1);
		}

		/**
		 * @brief Adds a 2d array of explicit values to the property values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values				  	All the property values to set ordered according to
		 * 											the topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly J dimension).
		 * @param [in]		proxy				  	The HDF proxy where to write the property values. It
		 * 											must be already opened for writing and won't be
		 * 											closed in this method. If @c nullptr, then a default
		 * 											HDF proxy must be defined in the repository.
		 * @param 		  	nullValue			  		The integer null value. Ignored (fixed to NaN) if it is a floating point value.
		 */
		template<typename T>
		void pushBackArray2dOfValues(const T* values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, T nullValue = (std::numeric_limits<T>::max)()) {
			const uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
			pushBackArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
		}
		template<typename T>
		void pushBackArray2dOfValuesPlusStatistics(const T* values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, const COMMON_NS::NumberArrayStatistics<T>& statistics,
			EML2_NS::AbstractHdfProxy* proxy = nullptr) {
			pushBackArray2dOfValues(values, valueCountInFastestDim, valueCountInSlowestDim, proxy, statistics.getNullValue());
			setStatistics(statistics, getPatchCount() - 1);
		}

		/**
		 * @brief Adds a 3d array of explicit values to the property values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values				  	All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values to write in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param [in]		proxy				  	The HDF proxy where to write the property values. It
		 * 											must be already opened for writing and won't be
		 * 											closed in this method. If @c nullptr, then a default
		 * 											HDF proxy must be defined in the repository.
		 * @param 		  	nullValue			  	The integer null value. Ignored (fixed to NaN) if it is a floating point value.
		 */
		template<typename T>
		void pushBackArray3dOfValues(const T* values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, T nullValue = (std::numeric_limits<T>::max)()) {
			const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
			pushBackArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
		}
		template<typename T>
		void pushBackArray3dOfValuesPlusStatistics(const T* values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, const COMMON_NS::NumberArrayStatistics<T>& statistics,
			EML2_NS::AbstractHdfProxy* proxy = nullptr) {
			pushBackArray3dOfValues(values, valueCountInFastestDim, valueCountInMiddleDim, valueCountInSlowestDim, proxy, statistics.getNullValue());
			setStatistics(statistics, getPatchCount() - 1);
		}

		/**
		 * Gets all the values of a given patch of this instance.
		 *
		 * @exception	std::logic_error 		If the underlying gSOAP instance is not a RESQML2.0, nor a RESQML2.2 instance.
		 * @exception	std::out_of_range		If @p patchIndex is out of range.
		 * @exception	std::invalid_argument	If @p values is NULL.
		 *
		 * @param 	   	patchIndex					The index of the patch we want the values from.
		 * @param [out]	values	  					Preallocated buffer for receiving the values. Size is
		 * 											<tt>getValuesCountOfPatch(patchIndex)</tt>.
		 * @param		forceStatisticsComputation	Indicates if FESAPI must force computation of the statistics or if it only reads the provided statistics.
		 *
		 * @returns	The statistics about the array including the null value.
		 */
		template<typename T>
		COMMON_NS::NumberArrayStatistics<T> getArrayOfValuesOfPatch(uint64_t patchIndex, T* values, bool forceStatisticsComputation = false) const {
			cannotBePartial();
			if (values == nullptr) {
				throw std::invalid_argument("The array of values cannot be null");
			}

			T nullValue;
			if (gsoapProxy2_0_1 != nullptr) {
				auto const* xmlValues = static_cast<gsoap_resqml2_0_1::resqml20__AbstractValuesProperty const*>(gsoapProxy2_0_1)->PatchOfValues[patchIndex]->Values;
				if constexpr (std::is_integral_v<T>) {
					nullValue = readArrayNdOfIntegerValues(xmlValues, values);
				}
				else {
					auto const* xmlArray = dynamic_cast<gsoap_resqml2_0_1::resqml20__AbstractDoubleArray const*>(xmlValues);
					if (xmlArray != nullptr) {
						if constexpr (std::is_same_v<T, float>) {
							nullValue = std::numeric_limits<float>::quiet_NaN();
							readArrayNdOfFloatValues(xmlArray, values);
						}
						else {
							nullValue = std::numeric_limits<double>::quiet_NaN();
							readArrayNdOfDoubleValues(xmlArray, values);
						}
					}
					else {
						throw std::logic_error("Reading floating point values from a non RESQML2.0.1 double array is not supported.");
					}
				}
			}
			else if (gsoapProxy2_3 != nullptr) {
				gsoap_eml2_3::eml23__AbstractValueArray const* xmlValues = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3)->ValuesForPatch.at(patchIndex);
				if constexpr (std::is_integral_v<T>) {
					auto const* xmlArray = dynamic_cast<gsoap_eml2_3::eml23__AbstractIntegerArray const*>(xmlValues);
					if (xmlArray != nullptr) {
						nullValue = readArrayNdOfIntegerValues(xmlArray, values);
					}
					else {
						throw std::logic_error("Reading integer values from a non integer array is not supported.");
					}
				}
				else {
					auto const* xmlArray = dynamic_cast<gsoap_eml2_3::eml23__AbstractFloatingPointArray const*>(xmlValues);
					if (xmlArray != nullptr) {
						if constexpr (std::is_same_v<T, float>) {
							nullValue = std::numeric_limits<float>::quiet_NaN();
							readArrayNdOfFloatValues(xmlArray, values);
						}
						else {
							nullValue = std::numeric_limits<double>::quiet_NaN();
							readArrayNdOfDoubleValues(xmlArray, values);
						}
					}
					else {
						throw std::logic_error("Reading floating point values from a non RESQML2.2 double array is not supported.");
					}
				}
			}
			else {
				throw std::logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
			}

			if (forceStatisticsComputation) {
				return COMMON_NS::NumberArrayStatistics<T>(values, getValuesCountOfPatch(patchIndex), getElementCountPerValue(), nullValue);
			}

			return getStatistics<T>(patchIndex);
		}

		template<typename T>  std::enable_if_t<std::is_arithmetic_v<T>, COMMON_NS::NumberArrayStatistics<T>>
		getStatistics(uint64_t patchIndex) const;

		/**
		 * @brief	Adds an array constant integer values to the property values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 or 2.2 one.
		 *
		 * @param 		  	value	  	The constant value in the array.
		 * @param 		  	valueCount	The number of values to write.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackIntegerConstantArrayOfValues(int64_t value, uint64_t valueCount);

		/**
		 * @brief	Adds a 1d array of explicit int values to the property values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values	  	All the property values to set ordered according to the topology
		 * 								of the representation it is based on.
		 * @param 		  	valueCount	The number of values to write.
		 * @param [in,out]	proxy	  	The HDF proxy where to write the property values. It must be
		 * 								already opened for writing and won't be closed in this method. If
		 * 								@c nullptr, then a default HDF proxy must be defined in the
		 * 								repository.
		 * @param 		  	nullValue 	The null value.
		 */
		[[deprecated("Use pushBackArray1dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackInt64Hdf5Array1dOfValues(const int64_t* values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue);

		/**
		 * Adds a 1d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array1dOfValues
		 */
		[[deprecated("Use pushBackArray1dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackInt32Hdf5Array1dOfValues(const int* values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, int nullValue);

		/**
		 * Adds a 1d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array1dOfValues
		 */
		[[deprecated("Use pushBackArray1dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackInt16Hdf5Array1dOfValues(const short* values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, short nullValue);

		/**
		 * Adds a 1d array of explicit int8_t values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array1dOfValues
		 */
		[[deprecated("Use pushBackArray1dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackInt8Hdf5Array1dOfValues(const int8_t* values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue);

		/**
		 * @brief Adds a 2d array of explicit int values to the property values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values				  	All the property values to set ordered according to
		 * 											the topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly J dimension).
		 * @param [in,out]	proxy				  	The HDF proxy where to write the property values. It
		 * 											must be already opened for writing and won't be
		 * 											closed in this method. If @c nullptr, then a default
		 * 											HDF proxy must be defined in the repository.
		 * @param 		  	nullValue			  	The null value.
		 */
		[[deprecated("Use pushBackArray2dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackInt64Hdf5Array2dOfValues(const int64_t* values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue);

		/**
		 * Adds a 2d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array2dOfValues
		 */
		[[deprecated("Use pushBackArray2dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackInt32Hdf5Array2dOfValues(const int* values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int nullValue);

		/**
		 * Adds a 2d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array2dOfValues
		 */
		[[deprecated("Use pushBackArray2dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackInt16Hdf5Array2dOfValues(const short* values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, short nullValue);

		/**
		 * Adds a 2d array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array2dOfValues
		 */
		[[deprecated("Use pushBackArray2dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackUInt16Hdf5Array2dOfValues(const unsigned short* values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue);

		/**
		 * Adds a 2d array of explicit int8_t values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array2dOfValues
		 */
		[[deprecated("Use pushBackArray2dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackInt8Hdf5Array2dOfValues(const int8_t* values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue);

		/**
		 * @brief Adds a 3d array of explicit int values to the property values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values				  	All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values to write in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param [in,out]	proxy				  	The HDF proxy where to write the property values. It
		 * 											must be already opened for writing and won't be
		 * 											closed in this method. If @c nullptr, then a default
		 * 											HDF proxy must be defined in the repository.
		 * @param 		  	nullValue			  	The null value.
		 */
		[[deprecated("Use pushBackArray3dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackInt64Hdf5Array3dOfValues(const int64_t* values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue);

		/**
		 * Adds a 3d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array3dOfValues
		 */
		[[deprecated("Use pushBackArray3dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackInt32Hdf5Array3dOfValues(const int* values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int nullValue);

		/**
		 * Adds a 3d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array3dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInt16Hdf5Array3dOfValues(const short* values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, short nullValue);

		/**
		 * Adds a 3d array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array3dOfValues
		 */
		[[deprecated("Use pushBackArray3dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackUInt16Hdf5Array3dOfValues(const unsigned short* values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue);

		/**
		 * Adds a 3d array of explicit int8_t values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array3dOfValues
		 */
		[[deprecated("Use pushBackArray3dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackInt8Hdf5Array3dOfValues(const int8_t* values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue);

		/**
		 * @brief	Adds an nd array of explicit int values to the property values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values					All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param [in]	  	numValues				The number of property values ordered by dimension of
		 * 											the array to write.
		 * @param 		  	numDimensionsInArray	The number of dimensions in the array to write.
		 * @param [in,out]	proxy					The HDF proxy where to write the property values. It
		 * 											must be already opened for writing and won't be closed in
		 * 											this method. If @c nullptr, then a default HDF proxy must
		 * 											be defined in the repository.
		 * @param 		  	nullValue				The null value.
		 */
		[[deprecated("Use pushBackArrayOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT virtual void pushBackInt64Hdf5ArrayOfValues(const int64_t* values, const uint64_t* numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue);

		/**
		 * Adds an nd array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues
		 */
		[[deprecated("Use pushBackArrayOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT virtual void pushBackInt32Hdf5ArrayOfValues(const int* values, const uint64_t* numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int nullValue);

		/**
		 * Adds an nd array of explicit short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues
		 */
		[[deprecated("Use pushBackArrayOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT virtual void pushBackInt16Hdf5ArrayOfValues(const short* values, const uint64_t* numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, short nullValue);

		/**
		 * Adds an nd array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues
		 */
		[[deprecated("Use pushBackArrayOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT virtual void pushBackUInt16Hdf5ArrayOfValues(const unsigned short* values, const uint64_t* numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue);

		/**
		 * Adds an nd array of explicit int8_t values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues
		 */
		[[deprecated("Use pushBackArrayOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT virtual void pushBackInt8Hdf5ArrayOfValues(const int8_t* values, const uint64_t* numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue);

		/**
		 * Pushes back a new patch of values for this property where the values have not to be written
		 * in the HDF5 file.The reason can be that the values already exist in an external file (only
		 * HDF5 for now) or that the writing of the values in the external file is differed in time.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p hdfProxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param [in]	hdfProxy 	The HDF5 proxy where the values are already or will be stored. If @c
		 * 							nullptr, then a default HDF proxy must be defined in the repository.
		 * @param 	  	dataset  	(Optional) If not provided during the method call, the dataset will
		 * 							be named the same as the dataset naming convention of fesapi :
		 * 							<tt>getHdfGroup() + "/values_patch" + patchIndex</tt>
		 * @param 	  	nullValue	(Optional) Only relevant for integer HDF5 datasets. Indeed, RESQML
		 * 							(and fesapi) forces null value for floating point to be @c NaN value.
		 *
		 * @returns	The name of the HDF5 dataset.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string pushBackRefToExistingIntegerDataset(EML2_NS::AbstractHdfProxy* hdfProxy, const std::string & dataset = "", int64_t nullValue = (std::numeric_limits<int64_t>::max)());

		/**
		 * Check if this property has all its values set to a constant ones.
		 * This method does not check if all given values are the same constant ones.
		 * It only checks if the property has been written using the optimized constant array.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want to check the values from.
		 *
		 * @returns	True if the property has been written using the optimized constant array.
		 */
		DLL_IMPORT_OR_EXPORT bool hasConstantValues(uint64_t patchIndex) const;

		/**
		 * Get the constant value of all values of this property as an integer one.
		 * This method does not check if all given values are the same constant ones.
		 * It only checks if the property has been written using the optimized constant array.
		 *
		 * @exception	std::logic_error 		If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range		If @p patchIndex is strictly greater than patch count.
		 * @exception	std::invalid_argument	If the property does not have any integer constant value.
		 *
		 * @param 	   	patchIndex	The index of the patch we want to get the constant value from.
		 *
		 * @returns	The constant value of all values of this property as an integer one.
		 */
		DLL_IMPORT_OR_EXPORT int64_t getInt64ConstantValuesOfPatch(uint64_t patchIndex) const;

		/**
		 * Get the constant value of all values of this property as a double one.
		 * This method does not check if all given values are the same constant ones.
		 * It only checks if the property has been written using the optimized constant array.
		 *
		 * @exception	std::logic_error 		If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range		If @p patchIndex is strictly greater than patch count.
		 * @exception	std::invalid_argument	If the property does not have any double constant value.
		 *
		 * @param 	   	patchIndex	The index of the patch we want to get the constant value from.
		 *
		 * @returns	The constant value of all values of this property as a double one.
		 */
		DLL_IMPORT_OR_EXPORT double getDoubleConstantValuesOfPatch(uint64_t patchIndex) const;

		/**
		 * Gets the null value of a given patch of this instance. Values are supposed to be integer ones.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::range_error	 	If @p patchIndex is strictly greater than patch count.
		 * @exception	std::invalid_argument	If the @p patchIndex patch does not contain integer
		 * 										values.
		 *
		 * @param 	patchIndex	The index of the patch we want the values from.
		 *
		 * @returns	the null value.
		 */
		DLL_IMPORT_OR_EXPORT int64_t getNullValueOfPatch(uint64_t patchIndex) const;

		[[deprecated("Use getArrayOfValuesOfPatch instead.")]]
		DLL_IMPORT_OR_EXPORT int64_t getInt64ValuesOfPatch(uint64_t patchIndex, int64_t* values) const {
			return getArrayOfValuesOfPatch(patchIndex, values).getNullValue();
		}

		[[deprecated("Use getArrayOfValuesOfPatch instead.")]]
		DLL_IMPORT_OR_EXPORT uint64_t getUInt64ValuesOfPatch(uint64_t patchIndex, uint64_t* values) const {
			return getArrayOfValuesOfPatch(patchIndex, values).getNullValue();
		}

		[[deprecated("Use getArrayOfValuesOfPatch instead.")]]
		DLL_IMPORT_OR_EXPORT int32_t getInt32ValuesOfPatch(uint64_t patchIndex, int32_t* values) const {
			return getArrayOfValuesOfPatch(patchIndex, values).getNullValue();
		}

		[[deprecated("Use getArrayOfValuesOfPatch instead.")]]
		DLL_IMPORT_OR_EXPORT uint32_t getUInt32ValuesOfPatch(uint64_t patchIndex, uint32_t* values) const {
			return getArrayOfValuesOfPatch(patchIndex, values).getNullValue();
		}

		[[deprecated("Use getArrayOfValuesOfPatch instead.")]]
		DLL_IMPORT_OR_EXPORT int16_t getInt16ValuesOfPatch(uint64_t patchIndex, int16_t* values) const {
			return getArrayOfValuesOfPatch(patchIndex, values).getNullValue();
		}

		[[deprecated("Use getArrayOfValuesOfPatch instead.")]]
		DLL_IMPORT_OR_EXPORT uint16_t getUInt16ValuesOfPatch(uint64_t patchIndex, uint16_t* values) const {
			return getArrayOfValuesOfPatch(patchIndex, values).getNullValue();
		}

		DLL_IMPORT_OR_EXPORT int8_t getInt8ValuesOfPatch(uint64_t patchIndex, int8_t* values) const {
			return getArrayOfValuesOfPatch(patchIndex, values).getNullValue();
		}

		[[deprecated("Use getArrayOfValuesOfPatch instead.")]]
		DLL_IMPORT_OR_EXPORT uint8_t getUInt8ValuesOfPatch(uint64_t patchIndex, uint8_t* values) const {
			return getArrayOfValuesOfPatch(patchIndex, values).getNullValue();
		}

		//***********************************
		//*** Writing with hyperslabbing *****
		//***********************************

		/**
		 * Create an nd array of values to the property values. No values are written to
		 * this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 			datatype			The datatype of the values
		 * @param 		  	numValues		  	The number of property values ordered by dimension of the
		 * 										array to write.  It is ordered from slowest dimension to
		 * 										fastest dimension.
		 * @param 		  	numArrayDimensions	The number of dimensions of the array to write.
		 * @param 			nullValue			The integer null value in case we create an integer array.
		 * 										It is ignored if the @p datatype is a floating point one.
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If @c nullptr (default), a
		 * 										default HDF proxy must be defined into the data object
		 * 										repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackHdf5ArrayOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			uint64_t const * numValues,
			unsigned int numArrayDimensions,
			int64_t nullValue = (std::numeric_limits<int64_t>::max)(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr
		);

		/**
		 * Creates a 1d array of values to the property values. No values are written to
		 * this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 			datatype			The datatype of the values
		 * @param 		  	valueCount			The number of values to write).
		 * @param 			nullValue			The integer null value in case we create an integer array.
		 * 										It is ignored if the @p datatype is a floating point one.
		 * @param [in,out]	proxy				(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and
		 * 										won't be closed in this method. If @c nullptr
		 * 										(default), a default HDF proxy must be defined into
		 * 										the data object repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackHdf5Array1dOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			uint64_t valueCount,
			int64_t nullValue = (std::numeric_limits<int64_t>::max)(), EML2_NS::AbstractHdfProxy* proxy = nullptr
		);

		/**
		 * Creates a 2d array of values to the property values. No values are written to
		 * this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 			datatype				The datatype of the values
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param 			nullValue				The integer null value in case we create an integer array.
		 * 											It is ignored if the @p datatype is a floating point one.
		 * @param [in,out]	proxy					(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackHdf5Array2dOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			int64_t nullValue = (std::numeric_limits<int64_t>::max)(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr
		);

		/**
		 * Creates a 3d array of values to the property values. No values are written to
		 * this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 			datatype				The datatype of the values
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values to write in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param 			nullValue				The integer null value in case we create an integer array.
		 * 											It is ignored if the @p datatype is a floating point one.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackHdf5Array3dOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			int64_t nullValue = (std::numeric_limits<int64_t>::max)(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr
		);

		/**
		 * Adds an nd array of explicit int 64 bits values into to the property values. Since this
		 * methods only pushes back values into an existing array, it is to be used along with
		 * pushBackInt64Hdf5ArrayOfValues().
		 *
		 * @exception	std::invalid_argument	If @p proxy is null and no default HDF proxy is defined
		 * 										into the data object repository.
		 * @exception	std::out_of_range	 	If @p patchIndex is strictly greater than patch count and
		 * 										different from unsigned int maximum value.
		 *
		 * @param [in]	  	values			  	All the property values to set ordered according to the
		 * 										topology of the representation it is based on.
		 * @param 		  	numValues		  	The number of property values ordered by dimension of the
		 * 										array to write. It is ordered from slowest dimension to
		 * 										fastest dimension.
		 * @param 		  	offsetValues	  	The offset values ordered by dimension of the array to
		 * 										write. It is ordered from slowest dimension to fastest
		 * 										dimension.
		 * @param 		  	numArrayDimensions	The number of dimensions of the array to write.
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If null (default value), a
		 * 										default HDF proxy must be defined into the data object
		 * 										repository.
		 * @param 		  	patchIndex		  	(Optional) Zero-based index of the patch where to write
		 * 										the property values. If not provided, its default value
		 * 										is by convention set to unsigned int maximum value and
		 * 										the property values will be written in the last property
		 * 										values patch (the one with the greatest index).
		 */
		DLL_IMPORT_OR_EXPORT void setValuesOfInt64Hdf5ArrayOfValues(
			int64_t const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfHdf5ArrayOfValues(
				COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64, values, numValues,
				offsetValues, numArrayDimensions, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfUInt64Hdf5ArrayOfValues(
			uint64_t const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfHdf5ArrayOfValues(
				COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT64, values, numValues,
				offsetValues, numArrayDimensions, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfInt32Hdf5ArrayOfValues(
			int32_t const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfHdf5ArrayOfValues(
				COMMON_NS::AbstractObject::numericalDatatypeEnum::INT32, values, numValues,
				offsetValues, numArrayDimensions, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfUInt32Hdf5ArrayOfValues(
			uint32_t const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfHdf5ArrayOfValues(
				COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT32, values, numValues,
				offsetValues, numArrayDimensions, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfInt16Hdf5ArrayOfValues(
			int16_t const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfHdf5ArrayOfValues(
				COMMON_NS::AbstractObject::numericalDatatypeEnum::INT16, values, numValues,
				offsetValues, numArrayDimensions, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfUInt16Hdf5ArrayOfValues(
			uint16_t const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfHdf5ArrayOfValues(
				COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT16, values, numValues,
				offsetValues, numArrayDimensions, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfInt8Hdf5ArrayOfValues(
			int8_t const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfHdf5ArrayOfValues(
				COMMON_NS::AbstractObject::numericalDatatypeEnum::INT8, values, numValues,
				offsetValues, numArrayDimensions, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfUInt8Hdf5ArrayOfValues(
			uint8_t const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfHdf5ArrayOfValues(
				COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT8, values, numValues,
				offsetValues, numArrayDimensions, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfDoubleHdf5ArrayOfValues(
			double const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfHdf5ArrayOfValues(
				COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE, values, numValues,
				offsetValues, numArrayDimensions, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfFloatHdf5ArrayOfValues(
			float const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfHdf5ArrayOfValues(
				COMMON_NS::AbstractObject::numericalDatatypeEnum::FLOAT, values, numValues,
				offsetValues, numArrayDimensions, proxy, patchIndex);
		}

		/**
		 * Adds a 1d array of explicit int 64 bits values into the property values. Since this methods
		 * only pushes back values into an existing array, it is to be used along with
		 * pushBackInt64Hdf5Array3dOfValues().
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 * @exception	std::out_of_range	 	If @p patchIndex is strictly greater than patch count and
		 * 										different from unsigned int maximum value.
		 *
		 * @param [in]	  	values				  	All the property values to set ordered according to
		 * 											the topology of the representation it is based on.
		 * @param 		  	valueCount				The number of values to write.
		 * @param 		  	offset	  				The offset value.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @p nullptr
		 * 											(default value), a default HDF proxy must be defined
		 * 											into the data object repository.
		 * @param 		  	patchIndex			  	(Optional) Zero-based index of the patch where to
		 * 											write the property values. If not provided, its
		 * 											default value is by convention set to unsigned int
		 * 											maximum value and the property values will be written
		 * 											in the last property values patch (the one with the
		 * 											greatest index).
		 */
		DLL_IMPORT_OR_EXPORT void setValuesOfInt64Hdf5Array1dOfValues(
			int64_t const* values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfInt64Hdf5ArrayOfValues(values, &valueCount, &offset, 1, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfUInt64Hdf5Array1dOfValues(
			uint64_t const* values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfUInt64Hdf5ArrayOfValues(values, &valueCount, &offset, 1, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfInt32Hdf5Array1dOfValues(
			int32_t const* values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfInt32Hdf5ArrayOfValues(values, &valueCount, &offset, 1, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfUInt32Hdf5Array1dOfValues(
			uint32_t const* values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfUInt32Hdf5ArrayOfValues(values, &valueCount, &offset, 1, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfInt16Hdf5Array1dOfValues(
			int16_t const* values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfInt16Hdf5ArrayOfValues(values, &valueCount, &offset, 1, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfUInt16Hdf5Array1dOfValues(
			uint16_t const* values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfUInt16Hdf5ArrayOfValues(values, &valueCount, &offset, 1, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfInt8Hdf5Array1dOfValues(
			int8_t const* values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfInt8Hdf5ArrayOfValues(values, &valueCount, &offset, 1, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfUInt8Hdf5Array1dOfValues(
			uint8_t const* values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfUInt8Hdf5ArrayOfValues(values, &valueCount, &offset, 1, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfDoubleHdf5Array1dOfValues(
			double const * values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfDoubleHdf5ArrayOfValues(values, &valueCount, &offset, 1, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfFloatHdf5Array1dOfValues(
			float const * values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			setValuesOfFloatHdf5ArrayOfValues(values, &valueCount, &offset, 1, proxy, patchIndex);
		}

		/**
		 * Adds a 2d array of explicit values into the property values. Since this methods
		 * only pushes back values into an existing array, it is to be used along with
		 * pushBackInt64Hdf5Array2dOfValues().
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 * @exception	std::out_of_range	 	If @p patchIndex is strictly greater than patch count and
		 * 										different from unsigned int maximum value.
		 *
		 * @param [in]	  	values				  	All the property values to set ordered according to
		 * 											the topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param 		  	offsetInFastestDim	  	The offset value for writing in the fastest dimension
		 * 											(mainly I dimension).
		 * @param 		  	offsetInSlowestDim	  	The offset value for writing in the slowest dimension
		 * 											(mainly K dimension).
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @p nullptr
		 * 											(default value), a default HDF proxy must be defined
		 * 											into the data object repository.
		 * @param 		  	patchIndex			  	(Optional) Zero-based index of the patch where to
		 * 											write the property values. If not provided, its
		 * 											default value is by convention set to unsigned int
		 * 											maximum value and the property values will be written
		 * 											in the last property values patch (the one with the
		 * 											greatest index).
		 */
		DLL_IMPORT_OR_EXPORT void setValuesOfInt64Hdf5Array2dOfValues(
			int64_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[2] = { offsetInSlowestDim, offsetInFastestDim };
			setValuesOfInt64Hdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 2, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfUInt64Hdf5Array2dOfValues(
			uint64_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[2] = { offsetInSlowestDim, offsetInFastestDim };
			setValuesOfUInt64Hdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 2, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfInt32Hdf5Array2dOfValues(
			int32_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[2] = { offsetInSlowestDim, offsetInFastestDim };
			setValuesOfInt32Hdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 2, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfUInt32Hdf5Array2dOfValues(
			uint32_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[2] = { offsetInSlowestDim, offsetInFastestDim };
			setValuesOfUInt32Hdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 2, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfInt16Hdf5Array2dOfValues(
			int16_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[2] = { offsetInSlowestDim, offsetInFastestDim };
			setValuesOfInt16Hdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 2, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfUInt16Hdf5Array2dOfValues(
			uint16_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[2] = { offsetInSlowestDim, offsetInFastestDim };
			setValuesOfUInt16Hdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 2, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfInt8Hdf5Array2dOfValues(
			int8_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[2] = { offsetInSlowestDim, offsetInFastestDim };
			setValuesOfInt8Hdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 2, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfUInt8Hdf5Array2dOfValues(
			uint8_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[2] = { offsetInSlowestDim, offsetInFastestDim };
			setValuesOfUInt8Hdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 2, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfDoubleHdf5Array2dOfValues(
			double const * values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[2] = { offsetInSlowestDim, offsetInFastestDim };
			setValuesOfDoubleHdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 2, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfFloatHdf5Array2dOfValues(
			float const * values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[2] = { valueCountInSlowestDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[2] = { offsetInSlowestDim, offsetInFastestDim };
			setValuesOfFloatHdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 2, proxy, patchIndex);
		}

		/**
		 * Adds a 3d array of explicit int 64 bits values into the property values. Since this methods
		 * only pushes back values into an existing array, it is to be used along with
		 * pushBackInt64Hdf5Array3dOfValues().
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 * @exception	std::out_of_range	 	If @p patchIndex is strictly greater than patch count and
		 * 										different from unsigned int maximum value.
		 *
		 * @param [in]	  	values				  	All the property values to set ordered according to
		 * 											the topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values to write in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param 		  	offsetInFastestDim	  	The offset value for writing in the fastest dimension
		 * 											(mainly I dimension).
		 * @param 		  	offsetInMiddleDim	  	The offset value for writing in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	offsetInSlowestDim	  	The offset value for writing in the slowest dimension
		 * 											(mainly K dimension).
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @p nullptr
		 * 											(default value), a default HDF proxy must be defined
		 * 											into the data object repository.
		 * @param 		  	patchIndex			  	(Optional) Zero-based index of the patch where to
		 * 											write the property values. If not provided, its
		 * 											default value is by convention set to unsigned int
		 * 											maximum value and the property values will be written
		 * 											in the last property values patch (the one with the
		 * 											greatest index).
		 */
		DLL_IMPORT_OR_EXPORT void setValuesOfInt64Hdf5Array3dOfValues(
			int64_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };
			setValuesOfInt64Hdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 3, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfUInt64Hdf5Array3dOfValues(
			uint64_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };
			setValuesOfUInt64Hdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 3, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfInt32Hdf5Array3dOfValues(
			int32_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };
			setValuesOfInt32Hdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 3, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfUInt32Hdf5Array3dOfValues(
			uint32_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };
			setValuesOfUInt32Hdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 3, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfInt16Hdf5Array3dOfValues(
			int16_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };
			setValuesOfInt16Hdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 3, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfUInt16Hdf5Array3dOfValues(
			uint16_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };
			setValuesOfUInt16Hdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 3, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfInt8Hdf5Array3dOfValues(
			int8_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };
			setValuesOfInt8Hdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 3, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfUInt8Hdf5Array3dOfValues(
			uint8_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };
			setValuesOfUInt8Hdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 3, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfDoubleHdf5Array3dOfValues(
			double const * values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };
			setValuesOfDoubleHdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 3, proxy, patchIndex);
		}
		DLL_IMPORT_OR_EXPORT void setValuesOfFloatHdf5Array3dOfValues(
			float const * values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) {
			const uint64_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
			const uint64_t offsetPerDimension[3] = { offsetInSlowestDim, offsetInMiddleDim, offsetInFastestDim };
			setValuesOfFloatHdf5ArrayOfValues(values, valueCountPerDimension, offsetPerDimension, 3, proxy, patchIndex);
		}

		//***********************************
		//*** Reading with hyperslabbing *****
		//***********************************

		/**
		 * Gets some of the values of a given patch of this instance. Values are supposed to be int 64
		 * bits ones.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex					The index of the patch we want the values from.
		 * @param [out]	values						The array (pointer) of values which must be
		 * 											preallocated. Size is
		 * 											<tt>getValuesCountOfPatch(patchIndex)</tt>.
		 * @param 	   	numValuesInEachDimension	The number of property values ordered by dimension of
		 * 											the array to read. It is ordered from slowest dimension
		 * 											to fastest dimension.
		 * @param 	   	offsetInEachDimension   	The offset values ordered by dimension of the array
		 * 											to read. It is ordered from slowest dimension to fastest
		 * 											dimension.
		 * @param 	   	numArrayDimensions			The number of dimensions of the array to write.
		 */
		DLL_IMPORT_OR_EXPORT void getInt64ValuesOfPatch(
			uint64_t patchIndex,
			int64_t* values,
			uint64_t const * numValuesInEachDimension,
			uint64_t const * offsetInEachDimension,
			unsigned int numArrayDimensions
		) const;

		/**
		 * Gets some of the values of a given patch of this instance. Values are supposed to be int 64
		 * bits ones.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex			  	The index of the patch we want the values from.
		 * @param [out]	values				  	The array (pointer) of values must be preallocated. Size
		 * 										is <tt>getValuesCountOfPatch(patchIndex)</tt>.
		 * @param 	   	valueCountInFastestDim	The number of values to read in the fastest dimension
		 * 										(mainly I dimension).
		 * @param 	   	valueCountInMiddleDim 	The number of values to read in the middle dimension
		 * 										(mainly J dimension).
		 * @param 	   	valueCountInSlowestDim	The number of values to read in the slowest dimension
		 * 										(mainly K dimension).
		 * @param 	   	offsetInFastestDim	  	The offset value for reading in the fastest dimension
		 * 										(mainly I dimension).
		 * @param 	   	offsetInMiddleDim	  	The offset value for reading in the middle dimension
		 * 										(mainly J dimension).
		 * @param 	   	offsetInSlowestDim	  	The offset value for reading in the slowest dimension
		 * 										(mainly K dimension).
		 */
		DLL_IMPORT_OR_EXPORT void getInt64ValuesOf3dPatch(
			uint64_t patchIndex,
			int64_t* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim
		) const;

		/**
		 * Gets some of the values of a given patch of this instance. Values are supposed to be integer
		 * ones.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex					The index of the patch we want the values from.
		 * @param [out]	values						The array (pointer) of values which must be
		 * 											preallocated. Size is
		 * 											<tt>getValuesCountOfPatch(patchIndex)</tt>.
		 * @param [in] 	numValuesInEachDimension	The number of property values ordered by
		 * 											dimension of the array to read. It is ordered from
		 * 											slowest dimension to fastest dimension.
		 * @param [in] 	offsetInEachDimension   	The offset values ordered by dimension of the
		 * 											array to read. It is ordered from slowest dimension to
		 * 											fastest dimension.
		 * @param 	   	numArrayDimensions			The number of dimensions of the array to read.
		 *
		 * @returns	The null value.
		 */
		DLL_IMPORT_OR_EXPORT int32_t getIntValuesOfPatch(
			uint64_t patchIndex,
			int32_t* values,
			const uint64_t* numValuesInEachDimension,
			const uint64_t* offsetInEachDimension,
			unsigned int numArrayDimensions
		) const;

		/**
		 * Gets some of the values of a given patch of this instance. Values are supposed to be integer
		 * ones.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex			  	The index of the patch we want the values from.
		 * @param [out]	values				  	The array (pointer) of values must be preallocated. Size
		 * 										is <tt>getValuesCountOfPatch(patchIndex)</tt>.
		 * @param 	   	valueCountInFastestDim	The number of values to read in the fastest dimension
		 * 										(mainly I dimension).
		 * @param 	   	valueCountInMiddleDim 	The number of values to read in the middle dimension
		 * 										(mainly J dimension).
		 * @param 	   	valueCountInSlowestDim	The number of values to read in the slowest dimension
		 * 										(mainly K dimension).
		 * @param 	   	offsetInFastestDim	  	The offset value for reading in the fastest dimension
		 * 										(mainly I dimension).
		 * @param 	   	offsetInMiddleDim	  	The offset value for reading in the middle dimension
		 * 										(mainly J dimension).
		 * @param 	   	offsetInSlowestDim	  	The offset value for reading in the slowest dimension
		 * 										(mainly K dimension).
		 */
		DLL_IMPORT_OR_EXPORT void getIntValuesOf3dPatch(
			uint64_t patchIndex,
			int32_t* values,
			unsigned int valueCountInFastestDim,
			unsigned int valueCountInMiddleDim,
			unsigned int valueCountInSlowestDim,
			unsigned int offsetInFastestDim,
			unsigned int offsetInMiddleDim,
			unsigned int offsetInSlowestDim
		) const;

		//***********************************
		//****** FLOATING POINT *************
		//***********************************

		/**
		 * @brief	Adds an array constant flaoting point values to the property values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 or 2.2 one.
		 *
		 * @param 		  	value	  	The constant value in the array.
		 * @param 		  	valueCount	The number of values to write.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFloatingPointConstantArrayOfValues(double value, uint64_t valueCount);

		/**
		 * @brief Adds a 1d array of explicit double values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values			All the property values to set ordered according the topology
		 * 									of the representation it is based on.
		 * @param 		  	valueCount  	The number of values to write.
		 * @param [in,out]	proxy			(Optional) The HDF proxy where to write the property values.
		 * 									It must be already opened for writing and won't be closed in this
		 * 									method. If @c nullptr (default value), then a default HDF proxy
		 * 									must be defined in the repository.
		 */
		[[deprecated("Use pushBackArray1dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackDoubleHdf5Array1dOfValues(const double * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief Adds a 2d array of explicit double values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values				  	All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly J dimension).
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default value), then a default HDF proxy must be
		 * 											defined in the repository.
		 */
		[[deprecated("Use pushBackArray2dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackDoubleHdf5Array2dOfValues(const double * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief Adds a 3d array of explicit double values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values				  	All the property values to set ordered according the
		 * 											topology of the representation it is based on.
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values to write in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default value), then a default HDF proxy must be
		 * 											defined in the repository.
		 */
		[[deprecated("Use pushBackArray3dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackDoubleHdf5Array3dOfValues(const double * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief Adds an nd array of explicit double values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values			  	All the property values to set ordered according the
		 * 										topology of the representation it is based on.
		 * @param 		  	numValues		  	The number of property values ordered by dimension of the
		 * 										array to write.
		 * @param 		  	numArrayDimensions	The number of dimensions of the array to write.
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If @c nullptr (default value),
		 * 										then a default HDF proxy must be defined in the
		 * 										repository.
		 */
		[[deprecated("Use pushBackArrayOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackDoubleHdf5ArrayOfValues(double const * values, uint64_t const * numValues, unsigned int numArrayDimensions, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds a 1d array of explicit float values to the property values.
		 *
		 * @copydetails pushBackDoubleHdf5Array1dOfValues
		 */
		[[deprecated("Use pushBackArray1dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5Array1dOfValues(const float * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds a 2d array of explicit float values to the property values.
		 *
		 * @copydetails pushBackDoubleHdf5Array2dOfValues
		 */
		[[deprecated("Use pushBackArray2dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5Array2dOfValues(const float * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds a 3d array of explicit float values to the property values.
		 *
		 * @copydetails pushBackDoubleHdf5Array3dOfValues
		 */
		[[deprecated("Use pushBackArray3dOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5Array3dOfValues(const float * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds an nd array of explicit float values to the property values.
		 *
		 * @copydetails	pushBackDoubleHdf5ArrayOfValues
		 */
		[[deprecated("Use pushBackArrayOfValues instead.")]]
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5ArrayOfValues(float const * values, uint64_t const * numValues, unsigned int numArrayDimensions, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Pushes back a reference to an existing (or a "to exist") HDF dataset in a particular HDF
		 * proxy. The reason can be that the values already exist in an external file (only HDF5 for
		 * now) or that the writing of the values in the external file is differed in time.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param [in]	proxy	   	The HDF5 proxy where the values are already or will be stored. If
		 * 							@c nullptr, then a default HDF proxy must be defined in the
		 * 							repository.
		 * @param 	  	datasetName	(Optional) The HDF5 dataset name where the values are stored. If
		 * 							empty, the dataset will be named the same as the dataset naming
		 * 							convention of fesapi :
		 * 							<tt>getHdfGroup() + "/values_patch" + patchIndex</tt>
		 *
		 * @returns	The name of the referenced HDF5 dataset.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string pushBackRefToExistingFloatingPointDataset(EML2_NS::AbstractHdfProxy* proxy, const std::string & datasetName = "");

		[[deprecated("Use getArrayOfValuesOfPatch instead.")]]
		DLL_IMPORT_OR_EXPORT void getDoubleValuesOfPatch(uint64_t patchIndex, double * values) const {
			getArrayOfValuesOfPatch(patchIndex, values);
		}

		[[deprecated("Use getArrayOfValuesOfPatch instead.")]]
		DLL_IMPORT_OR_EXPORT void getFloatValuesOfPatch(uint64_t patchIndex, float * values) const {
			getArrayOfValuesOfPatch(patchIndex, values);
		}

		//******************************************
		//*** For FLOATING POINT hyperslabbing *****
		//******************************************

		/**
		 * Get some of the values of a particular patch of the instance as float ones. This method makes
		 * use of HDF5 hyperslabbing.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex					The index of the patch we want the values from.
		 * @param [out]	values						The array (pointer) of values must be
		 * 											preallocated. Size is
		 * 											<tt>getValuesCountOfPatch(patchIndex)</tt>.
		 * @param 	   	numValuesInEachDimension	The number of property values ordered by dimension of
		 * 											the array to read. It is ordered from slowest dimension
		 * 											to fastest dimension.
		 * @param 	   	offsetInEachDimension   	The offset values ordered by dimension of the array
		 * 											to read. It is ordered from slowest dimension to fastest
		 * 											dimension.
		 * @param 	   	numArrayDimensions			The number of dimensions of the HDF5 array to read.
		 */
		DLL_IMPORT_OR_EXPORT void getFloatValuesOfPatch(
			uint64_t patchIndex,
			float* values,
			uint64_t const * numValuesInEachDimension,
			uint64_t const * offsetInEachDimension,
			unsigned int numArrayDimensions
		) const;

		/**
		 * Get some of the values of a particular patch of the instance as float ones. This method makes
		 * use of HDF5 hyperslabbing.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 		  	patchIndex			  	The index of the patch we want the values from.
		 * @param [in,out]	values				  	The array (pointer) of values must be preallocated.
		 * 											Size is <tt>getValuesCountOfPatch(patchIndex)</tt>.
		 * @param 		  	valueCountInFastestDim	The number of values to read in the fastest dimension
		 * 											(mainly I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values to read in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to read in the slowest dimension
		 * 											(mainly K dimension).
		 * @param 		  	offsetInFastestDim	  	The offset value for reading in the fastest dimension
		 * 											(mainly I dimension).
		 * @param 		  	offsetInMiddleDim	  	The offset value for reading in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	offsetInSlowestDim	  	The offset value for reading in the slowest dimension
		 * 											(mainly K dimension).
		 */
		DLL_IMPORT_OR_EXPORT void getFloatValuesOf3dPatch(
			uint64_t patchIndex,
			float* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim
		) const;

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT AbstractValuesProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractProperty(partialObject) {}

		/**
		 * Default constructor Set the relationship with an AbstractRepresentation and a local property
		 * type.
		 */
		AbstractValuesProperty() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractValuesProperty(gsoap_resqml2_0_1::resqml20__AbstractValuesProperty* fromGsoap) : RESQML2_NS::AbstractProperty(fromGsoap) {}
		AbstractValuesProperty(gsoap_eml2_3::resqml22__AbstractValuesProperty* fromGsoap) : RESQML2_NS::AbstractProperty(fromGsoap) {}

		/**
		 * Get the HDF Proxy which contains the property values of a particular patch.
		 *
		 * @param 		  	patchIndex	The corresponding patch index of the dataset to get.
		 * @param [out]		nullValue 	If possible, this function will set this parameter to the RESQML
		 * 								null value of the dataset. If not, it will return int64_t.min.
		 * @param [out]		nullValue 	this function will set this parameter to the RESQML
		 * 								dataset path in the HDF file.
		 *
		 * @returns	Null if it fails, else the HDF Proxy of patch.
		 */
		EML2_NS::AbstractHdfProxy* getDatasetOfPatch(uint64_t patchIndex, int64_t & nullValue, std::string & dsPath) const final;

		/**
		 * Gets the data object reference of the HDF proxy which is associated to a particular
		 * property patch.
		 *
		 * @param 		  	patchIndex	The corresponding patch index of the HDF proxy to get.
		 * @returns	Empty data object reference if no HDF proxy is associated to this property patch.
		 * 			Otherwise returns the data object reference of the associated representation. Null
		 * 			should not occured since each property must be associated to a representation.
		 */
		COMMON_NS::DataObjectReference getHdfProxyDor(uint64_t patchIndex) const final;

		/**
		 * Adds an nd array of values into to the property values. Since this
		 * methods only pushes back values into an existing array, it is to be used along with
		 * pushBackInt64Hdf5ArrayOfValues().
		 *
		 * @exception	std::invalid_argument	If @p proxy is null and no default HDF proxy is defined
		 * 										into the data object repository.
		 * @exception	std::out_of_range	 	If @p patchIndex is strictly greater than patch count and
		 * 										different from unsigned int maximum value.
		 *
		 * @param 			datatype			The datatype of the values
		 * @param [in]	  	values			  	All the property values to set ordered according to the
		 * 										topology of the representation it is based on.
		 * @param 		  	numValues		  	The number of property values ordered by dimension of the
		 * 										array to write. It is ordered from slowest dimension to
		 * 										fastest dimension.
		 * @param 		  	offsetValues	  	The offset values ordered by dimension of the array to
		 * 										write. It is ordered from slowest dimension to fastest
		 * 										dimension.
		 * @param 		  	numArrayDimensions	The number of dimensions of the array to write.
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If null (default value), a
		 * 										default HDF proxy must be defined into the data object
		 * 										repository.
		 * @param 		  	patchIndex		  	(Optional) Zero-based index of the patch where to write
		 * 										the property values. If not provided, its default value
		 * 										is by convention set to unsigned int maximum value and
		 * 										the property values will be written in the last property
		 * 										values patch (the one with the greatest index).
		 */
		void setValuesOfHdf5ArrayOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			void const* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)());

		// Need to dll export because it is called in a template implementation
		DLL_IMPORT_OR_EXPORT void pushBackArrayOfValues(const void* values, COMMON_NS::AbstractObject::numericalDatatypeEnum numericalDatatype, const uint64_t* numValues, unsigned int numDimensionsInArray,
			EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue);

		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::NumberArrayStatistics<int8_t> getInt8Statistics(uint64_t patchIndex) const {
			auto nullValue = getNullValueOfPatch(patchIndex);
			if (nullValue > (std::numeric_limits<int8_t>::max)() || nullValue < (std::numeric_limits<int8_t>::min)()) {
				nullValue = (std::numeric_limits<int8_t>::max)();
			}
			COMMON_NS::NumberArrayStatistics<int8_t> result;
			result.setNullValue(static_cast<int8_t>(nullValue));
			return result;
		}
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::NumberArrayStatistics<uint8_t> getUInt8Statistics(uint64_t patchIndex) const {
			auto nullValue = getNullValueOfPatch(patchIndex);
			if (nullValue > (std::numeric_limits<uint8_t>::max)() || nullValue < 0) {
				nullValue = (std::numeric_limits<uint8_t>::max)();
			}
			COMMON_NS::NumberArrayStatistics<uint8_t> result;
			result.setNullValue(static_cast<uint8_t>(nullValue));
			return result;
		}
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::NumberArrayStatistics<int16_t> getInt16Statistics(uint64_t patchIndex) const {
			auto nullValue = getNullValueOfPatch(patchIndex);
			if (nullValue > (std::numeric_limits<int16_t>::max)() || nullValue < (std::numeric_limits<int16_t>::min)()) {
				nullValue = (std::numeric_limits<int16_t>::max)();
			}
			COMMON_NS::NumberArrayStatistics<int16_t> result;
			result.setNullValue(static_cast<int16_t>(nullValue));
			return result;
		}
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::NumberArrayStatistics<uint16_t> getUInt16Statistics(uint64_t patchIndex) const {
			auto nullValue = getNullValueOfPatch(patchIndex);
			if (nullValue > (std::numeric_limits<uint16_t>::max)() || nullValue < 0) {
				nullValue = (std::numeric_limits<uint16_t>::max)();
			}
			COMMON_NS::NumberArrayStatistics<uint16_t> result;
			result.setNullValue(static_cast<uint16_t>(nullValue));
			return result;
		}
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::NumberArrayStatistics<int32_t> getInt32Statistics(uint64_t patchIndex) const {
			auto nullValue = getNullValueOfPatch(patchIndex);
			if (nullValue > (std::numeric_limits<int32_t>::max)() || nullValue < (std::numeric_limits<int32_t>::min)()) {
				nullValue = (std::numeric_limits<int32_t>::max)();
			}
			COMMON_NS::NumberArrayStatistics<int32_t> result;
			result.setNullValue(static_cast<int32_t>(nullValue));
			return result;
		}
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::NumberArrayStatistics<uint32_t> getUInt32Statistics(uint64_t patchIndex) const {
			auto nullValue = getNullValueOfPatch(patchIndex);
			if (nullValue > (std::numeric_limits<uint32_t>::max)() || nullValue < 0) {
				nullValue = (std::numeric_limits<uint32_t>::max)();
			}
			COMMON_NS::NumberArrayStatistics<uint32_t> result;
			result.setNullValue(static_cast<uint32_t>(nullValue));
			return result;
		}
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::NumberArrayStatistics<int64_t> getInt64Statistics(uint64_t patchIndex) const {
			COMMON_NS::NumberArrayStatistics<int64_t> result;
			result.setNullValue(getNullValueOfPatch(patchIndex));
			return result;
		}
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::NumberArrayStatistics<uint64_t> getUInt64Statistics(uint64_t patchIndex) const {
			COMMON_NS::NumberArrayStatistics<uint64_t> result;
			result.setNullValue(getNullValueOfPatch(patchIndex));
			return result;
		}
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::NumberArrayStatistics<float> getFloatStatistics(uint64_t) const { return COMMON_NS::NumberArrayStatistics<float>(); }
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::NumberArrayStatistics<double> getDoubleStatistics(uint64_t) const { return COMMON_NS::NumberArrayStatistics<double>(); }

		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__IntegerArrayStatistics* createIntegerArrayStatisticsFrom(const COMMON_NS::NumberArrayStatistics<int8_t>& stats, size_t index);
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__IntegerArrayStatistics* createIntegerArrayStatisticsFrom(const COMMON_NS::NumberArrayStatistics<uint8_t>& stats, size_t index);
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__IntegerArrayStatistics* createIntegerArrayStatisticsFrom(const COMMON_NS::NumberArrayStatistics<int16_t>& stats, size_t index);
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__IntegerArrayStatistics* createIntegerArrayStatisticsFrom(const COMMON_NS::NumberArrayStatistics<uint16_t>& stats, size_t index);
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__IntegerArrayStatistics* createIntegerArrayStatisticsFrom(const COMMON_NS::NumberArrayStatistics<int32_t>& stats, size_t index);
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__IntegerArrayStatistics* createIntegerArrayStatisticsFrom(const COMMON_NS::NumberArrayStatistics<uint32_t>& stats, size_t index);
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__IntegerArrayStatistics* createIntegerArrayStatisticsFrom(const COMMON_NS::NumberArrayStatistics<int64_t>& stats, size_t index);
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__IntegerArrayStatistics* createIntegerArrayStatisticsFrom(const COMMON_NS::NumberArrayStatistics<uint64_t>& stats, size_t index);
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__FloatingPointArrayStatistics* createFloatingPointArrayStatisticsFrom(const COMMON_NS::NumberArrayStatistics<float>& stats, size_t index);
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__FloatingPointArrayStatistics* createFloatingPointArrayStatisticsFrom(const COMMON_NS::NumberArrayStatistics<double>& stats, size_t index);

		template<typename T>
		void setStatistics(const COMMON_NS::NumberArrayStatistics<T>& stats, size_t patchIndex) {
			cannotBePartial();

			if (gsoapProxy2_0_1 != nullptr) {
				if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCOREContinuousProperty) {
					gsoap_resqml2_0_1::_resqml20__ContinuousProperty* prop = static_cast<gsoap_resqml2_0_1::_resqml20__ContinuousProperty*>(gsoapProxy2_0_1);
					for (size_t i = 0; i < stats.getMinimumSize(); ++i) {
						const auto minStat = stats.getMinimum(i);
						if (prop->MinimumValue.size() > i) {
							if (minStat == minStat && prop->MinimumValue[i] > minStat) {
								prop->MinimumValue[i] = minStat;
							}
						}
						else {
							prop->MinimumValue.push_back(minStat);
						}
					}
					for (size_t i = 0; i < stats.getMaximumSize(); ++i) {
						const auto maxStat = stats.getMaximum(i);
						if (prop->MaximumValue.size() > i) {
							if (maxStat == maxStat && prop->MaximumValue[i] < maxStat) {
								prop->MaximumValue[i] = maxStat;
							}
						}
						else {
							prop->MaximumValue.push_back(maxStat);
						}
					}
				}
				else if (gsoapProxy2_0_1->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCOREDiscreteProperty) {
					gsoap_resqml2_0_1::_resqml20__DiscreteProperty* prop = static_cast<gsoap_resqml2_0_1::_resqml20__DiscreteProperty*>(gsoapProxy2_0_1);
					for (size_t i = 0; i < stats.getMinimumSize(); ++i) {
						const auto minStat = stats.getMinimum(i);
						if (prop->MinimumValue.size() > i) {
							if (minStat == minStat && prop->MinimumValue[i] > minStat) {
								prop->MinimumValue[i] = minStat;
							}
						}
						else {
							prop->MinimumValue.push_back(minStat);
						}
					}
					for (size_t i = 0; i < stats.getMaximumSize(); ++i) {
						const auto maxStat = stats.getMaximum(i);
						if (prop->MaximumValue.size() > i) {
							if (maxStat == maxStat && prop->MaximumValue[i] < maxStat) {
								prop->MaximumValue[i] = maxStat;
							}
						}
						else {
							prop->MaximumValue.push_back(maxStat);
						}
					}
				}
				else {
					throw std::invalid_argument("In RESQML 2.0.1, only continuous and discrete properties can transfer only minimum and maximum values");
				}
			}
			else if (gsoapProxy2_3 != nullptr) {
				const auto valuePerIndexableElement = getElementCountPerValue();
				gsoap_eml2_3::resqml22__AbstractValuesProperty* prop = static_cast<gsoap_eml2_3::resqml22__AbstractValuesProperty*>(gsoapProxy2_3);
				if (auto* integerArray = dynamic_cast<gsoap_eml2_3::eml23__AbstractIntegerArray*>(prop->ValuesForPatch.at(patchIndex))) {
					if constexpr (std::is_integral_v<T>) {
						integerArray->Statistics.clear();
						for (size_t i = 0; i < valuePerIndexableElement; ++i) {
							integerArray->Statistics.push_back(createIntegerArrayStatisticsFrom(stats, i));
						}
					}
				}
				else if (auto* floatingPointArray = dynamic_cast<gsoap_eml2_3::eml23__AbstractFloatingPointArray*>(prop->ValuesForPatch.at(patchIndex))) {
					if constexpr (std::is_floating_point_v<T>) {
						floatingPointArray->Statistics.clear();
						for (size_t i = 0; i < valuePerIndexableElement; ++i) {
							floatingPointArray->Statistics.push_back(createFloatingPointArrayStatisticsFrom(stats, i));
						}
					}
				}
				else {
					throw std::invalid_argument("In RESQML 2.2, only floating point and integer property array of values can haev statistics");
				}
			}
			else {
				throw std::logic_error("Only RESQML 2.2 and 2.0.1 are supported for now.");
			}
		}
	};

	template<> DLL_IMPORT_OR_EXPORT void AbstractValuesProperty::pushBackArrayOfValues<int8_t>(const int8_t* values, const uint64_t* numValues, unsigned int numDimensionsInArray,
		EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue);
	template<> DLL_IMPORT_OR_EXPORT void AbstractValuesProperty::pushBackArrayOfValues<uint8_t>(const uint8_t* values, const uint64_t* numValues, unsigned int numDimensionsInArray,
		EML2_NS::AbstractHdfProxy* proxy, uint8_t nullValue);
	template<> DLL_IMPORT_OR_EXPORT void AbstractValuesProperty::pushBackArrayOfValues<int16_t>(const int16_t* values, const uint64_t* numValues, unsigned int numDimensionsInArray,
		EML2_NS::AbstractHdfProxy* proxy, int16_t nullValue);
	template<> DLL_IMPORT_OR_EXPORT void AbstractValuesProperty::pushBackArrayOfValues<uint16_t>(const uint16_t* values, const uint64_t* numValues, unsigned int numDimensionsInArray,
		EML2_NS::AbstractHdfProxy* proxy, uint16_t nullValue);
	template<> DLL_IMPORT_OR_EXPORT void AbstractValuesProperty::pushBackArrayOfValues<int32_t>(const int32_t* values, const uint64_t* numValues, unsigned int numDimensionsInArray,
		EML2_NS::AbstractHdfProxy* proxy, int32_t nullValue);
	template<> DLL_IMPORT_OR_EXPORT void AbstractValuesProperty::pushBackArrayOfValues<uint32_t>(const uint32_t* values, const uint64_t* numValues, unsigned int numDimensionsInArray,
		EML2_NS::AbstractHdfProxy* proxy, uint32_t nullValue);
	template<> DLL_IMPORT_OR_EXPORT void AbstractValuesProperty::pushBackArrayOfValues<int64_t>(const int64_t* values, const uint64_t* numValues, unsigned int numDimensionsInArray,
		EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue);
	template<> DLL_IMPORT_OR_EXPORT void AbstractValuesProperty::pushBackArrayOfValues<uint64_t>(const uint64_t* values, const uint64_t* numValues, unsigned int numDimensionsInArray,
		EML2_NS::AbstractHdfProxy* proxy, uint64_t nullValue);
	template<> DLL_IMPORT_OR_EXPORT void AbstractValuesProperty::pushBackArrayOfValues<float>(const float* values, const uint64_t* numValues, unsigned int numDimensionsInArray,
		EML2_NS::AbstractHdfProxy* proxy, float nullValue);
	template<> DLL_IMPORT_OR_EXPORT void AbstractValuesProperty::pushBackArrayOfValues<double>(const double* values, const uint64_t* numValues, unsigned int numDimensionsInArray,
		EML2_NS::AbstractHdfProxy* proxy, double nullValue);

	template<> DLL_IMPORT_OR_EXPORT COMMON_NS::NumberArrayStatistics<int8_t> AbstractValuesProperty::getStatistics<int8_t>(uint64_t patchIndex) const;
	template<> DLL_IMPORT_OR_EXPORT COMMON_NS::NumberArrayStatistics<uint8_t> AbstractValuesProperty::getStatistics<uint8_t>(uint64_t patchIndex) const;
	template<> DLL_IMPORT_OR_EXPORT COMMON_NS::NumberArrayStatistics<int16_t> AbstractValuesProperty::getStatistics<int16_t>(uint64_t patchIndex) const;
	template<> DLL_IMPORT_OR_EXPORT COMMON_NS::NumberArrayStatistics<uint16_t> AbstractValuesProperty::getStatistics<uint16_t>(uint64_t patchIndex) const;
	template<> DLL_IMPORT_OR_EXPORT COMMON_NS::NumberArrayStatistics<int32_t> AbstractValuesProperty::getStatistics<int32_t>(uint64_t patchIndex) const;
	template<> DLL_IMPORT_OR_EXPORT COMMON_NS::NumberArrayStatistics<uint32_t> AbstractValuesProperty::getStatistics<uint32_t>(uint64_t patchIndex) const;
	template<> DLL_IMPORT_OR_EXPORT COMMON_NS::NumberArrayStatistics<int64_t> AbstractValuesProperty::getStatistics<int64_t>(uint64_t patchIndex) const;
	template<> DLL_IMPORT_OR_EXPORT COMMON_NS::NumberArrayStatistics<uint64_t> AbstractValuesProperty::getStatistics<uint64_t>(uint64_t patchIndex) const;
	template<> DLL_IMPORT_OR_EXPORT COMMON_NS::NumberArrayStatistics<float> AbstractValuesProperty::getStatistics<float>(uint64_t patchIndex) const;
	template<> DLL_IMPORT_OR_EXPORT COMMON_NS::NumberArrayStatistics<double> AbstractValuesProperty::getStatistics<double>(uint64_t patchIndex) const;
}
