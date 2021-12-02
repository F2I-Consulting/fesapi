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
#include "../eml2/AbstractHdfProxy.h"

#include <stdexcept>

namespace RESQML2_NS
{
	/**
	 * @brief	Proxy class for a continuous property. Most common type of property used for storing
	 * 			rock or fluid attributes; all are represented as floating point values. So that the
	 * 			value range can be known before accessing all values, the min and max values of the
	 * 			range are also optionally stored.
	 * 			
	 * 			BUSINESS RULE: It also contains a unit of measure, which can be different from the
	 * 			unit of measure of its property type, but it must be convertible into this unit.
	 */
	class ContinuousProperty : public AbstractValuesProperty
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~ContinuousProperty() = default;

		/**
		* Please use std::string pushBackRefToExistingDataset(EML2_NS::AbstractHdfProxy* proxy, const std::string & datasetName = "") instead. Notice the lack of null value parameter.
		*/
		std::string pushBackRefToExistingIntegerDataset(EML2_NS::AbstractHdfProxy*, const std::string&, int64_t) final {
			throw std::logic_error("You cannot push back integer values in a Continuous Property.");
		}

		/**
		 * Gets the unit of measure of the values of this property. If <tt>
		 * resqml20__ResqmlUom::resqml20__ResqmlUom::Euc </tt> is returned, you should check if
		 * getUomAsString() gives you another result: it would be that the writer would have used a non
		 * standard unit of measure.
		 *
		 * @returns	The unit of measure of the values of this property.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::resqml20__ResqmlUom getUom() const = 0;

		/**
		 * Gets the unit of measure of the values of this property as a string.
		 *
		 * @returns	The unit of measure of the values of this property as a string.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getUomAsString() const = 0;

		/**
		 * @brief Adds a 1d array of explicit double values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values			All the property values to set ordered according the topology
		 * 									of the representation it is based on.
		 * @param 		  	valueCount  	The number of values to write.
		 * @param 		  	minimumValue	The minimum value of the values to add. If @c NaN is
		 * 									provided then both minimum and maximum values will be computed
		 * 									from the values.
		 * @param 		  	maximumValue	The maximum value of the values to add. If @c NaN is
		 * 									provided then both maximum and minimum values will be computed
		 * 									from the values.
		 * @param [in,out]	proxy			(Optional) The HDF proxy where to write the property values.
		 * 									It must be already opened for writing and won't be closed in this
		 * 									method. If @c nullptr (default value), then a default HDF proxy
		 * 									must be defined in the repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackDoubleHdf5Array1dOfValues(const double * values, uint64_t valueCount,
			double minimumValue, double maximumValue, EML2_NS::AbstractHdfProxy* proxy = nullptr);
		using AbstractValuesProperty::pushBackDoubleHdf5Array1dOfValues;

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
		 * @param 		  	minimumValue		  	The minimum value of the values to add. If
		 * 											@c NaN is provided then both minimum and maximum
		 * 											values will be computed from the values.
		 * @param 		  	maximumValue		  	The maximum value of the values to add. If
		 * 											@c NaN is provided then both maximum and minimum
		 * 											values will be computed from the values.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default value), then a default HDF proxy must be
		 * 											defined in the repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackDoubleHdf5Array2dOfValues(const double * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim,
			double minimumValue, double maximumValue, EML2_NS::AbstractHdfProxy* proxy = nullptr);
		using AbstractValuesProperty::pushBackDoubleHdf5Array2dOfValues;

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
		 * @param 		  	minimumValue		  	The minimum value of the values to add. If
		 * 											@c NaN is provided then both minimum and maximum
		 * 											values will be computed from the values.
		 * @param 		  	maximumValue		  	The maximum value of the values to add. If
		 * 											@c NaN is provided then both maximum and minimum
		 * 											values will be computed from the values.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default value), then a default HDF proxy must be
		 * 											defined in the repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackDoubleHdf5Array3dOfValues(const double * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim,
			double minimumValue, double maximumValue, EML2_NS::AbstractHdfProxy* proxy = nullptr);
		using AbstractValuesProperty::pushBackDoubleHdf5Array3dOfValues;

		/**
		 * @brief Adds an nd array of explicit double values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception std::invalid_argument		If <tt> minimumValue == nullptr </tt> and <tt> maximumValue != nullptr </tt>.
		 * @exception std::invalid_argument		If <tt> minimumValue != nullptr </tt> and <tt> maximumValue == nullptr </tt>.
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
		 * @param [in]	  	minimumValue	  	The minimum value (or value vector) of the
		 * 										values to add. If @c nullptr is provided for both @p
		 * 										minimumValue and @p maximumValue then both minimum and
		 *										maximum values will be computed from the values.
		 * @param [in]	  	maximumValue	  	The maximum value (or value vector) of the
		 * 										values to add. If @ nullptr is provided for both @p
		 * 										maximumValue and @p minimumValue then both minimum and
		 *										maximum values will be computed from the values.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackDoubleHdf5ArrayOfValues(double const * values, unsigned long long const * numValues, unsigned int numArrayDimensions,
			double * minimumValue, double * maximumValue, EML2_NS::AbstractHdfProxy* proxy = nullptr);
		using AbstractValuesProperty::pushBackDoubleHdf5ArrayOfValues;

		/**
		 * Adds a 1d array of explicit float values to the property values.
		 *
		 * @copydetails pushBackDoubleHdf5Array1dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5Array1dOfValues(const float * values, uint64_t valueCount,
			float minimumValue, float maximumValue, EML2_NS::AbstractHdfProxy* proxy = nullptr);
		using AbstractValuesProperty::pushBackFloatHdf5Array1dOfValues;

		/**
		 * Adds a 2d array of explicit float values to the property values.
		 *
		 * @copydetails pushBackDoubleHdf5Array2dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5Array2dOfValues(const float * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim,
			float minimumValue, float maximumValue, EML2_NS::AbstractHdfProxy* proxy = nullptr);
		using AbstractValuesProperty::pushBackFloatHdf5Array2dOfValues;

		/**
		 * Adds a 3d array of explicit float values to the property values.
		 *
		 * @copydetails pushBackDoubleHdf5Array3dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5Array3dOfValues(const float * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim,
			float minimumValue, float maximumValue, EML2_NS::AbstractHdfProxy* proxy = nullptr);
		using AbstractValuesProperty::pushBackFloatHdf5Array3dOfValues;

		/**
		 * Adds an nd array of explicit float values to the property values.
		 * 
		 * @exception std::invalid_argument If <tt> minimumValue == nullptr </tt> and <tt> maximumValue != nullptr </tt>.
		 * @exception std::invalid_argument	If <tt> minimumValue != nullptr </tt> and <tt> maximumValue == nullptr </tt>.
		 * 									
		 * @copydetails	pushBackDoubleHdf5ArrayOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5ArrayOfValues(float const * values, uint64_t const * numValues, unsigned int numArrayDimensions,
			float * minimumValue, float * maximumValue, EML2_NS::AbstractHdfProxy* proxy = nullptr);
		using AbstractValuesProperty::pushBackFloatHdf5ArrayOfValues;

		/**
		 * @brief	Gets the minimum value of a property. This minimum value is read (it is not computed).
		 *
		 * @param 	index	(Optional) @c 0 (default value, corresponding to the non vector property case) or
		 * 					zero-based index of the vector value for which we look for the minimum value
		 * 					(vector property case).
		 *
		 * @returns	The minimum value of the non vector property or the minimum value at position @p
		 * 			index of the vector value or @c NaN if @p index is out of range of if no minimum is present.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getMinimumValue(uint64_t index = 0) const = 0;

		/**
		 * @brief	Gets the maximum value of a property. This maximum value is read (it is not computed).
		 *
		 * @param 	index	(Optional) @c 0 (default value, corresponding to the non vector property case) or
		 * 					zero-based index of the vector value for which we look for the maximum value
		 * 					(vector property case).
		 *
		 * @returns	The maximum value of the non vector property or the maximum value at position @p
		 * 			index of the vector value or @c NaN if @p index is out of range of if no maximum is present.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getMaximumValue(uint64_t index = 0) const = 0;

		/**
		 * @brief	Sets the minimum value of a non vector property or the minimum value of one given
		 * 			value of a vector property.
		 *
		 * @param 	value	The minimum value to set.
		 * @param 	index	(Optional)  @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we want to set the
		 * 					minimum value (vector property case).
		 */
		DLL_IMPORT_OR_EXPORT virtual void setMinimumValue(double value, uint64_t index = 0) const = 0;

		/**
		 * @brief	Sets the maximum value of a non vector property or the maximum value of one given
		 * 			value of a vector property.
		 *
		 * @param 	value	The maximum value to set.
		 * @param 	index	(Optional)  @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we want to set the
		 * 					maximum value (vector property case).
		 */
		DLL_IMPORT_OR_EXPORT virtual void setMaximumValue(double value, uint64_t index = 0) const = 0;

		//***************************
		//*** For hyperslabbing *****
		//***************************

		/**
		 * Create an nd array of explicit float values to the property values. No values are written to
		 * this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 		  	numValues		  	The number of property values ordered by dimension of the
		 * 										array to write.  It is ordered from slowest dimension to
		 * 										fastest dimension.
		 * @param 		  	numArrayDimensions	The number of dimensions of the array to write.
		 * @param [in]	  	minimumValue	  	The minimum value (or value vector) of the
		 * 										values to add. If @c nullptr (default) is provided then
		 * 										neither minimum nor maximum value will be set.
		 * @param [in]	  	maximumValue	  	The maximum value (or value vector) of the
		 * 										values to add. If @c nullptr (default) is provided then
		 * 										neither maximum nor minimum value will be set.
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If @c nullptr (default), a
		 * 										default HDF proxy must be defined into the data object
		 * 										repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5ArrayOfValues(
			unsigned long long const * numValues,
			unsigned int numArrayDimensions,
			float * minimumValue, float * maximumValue,
			EML2_NS::AbstractHdfProxy* proxy = nullptr
		);

		/**
		 * Creates a 3d array of explicit float values to the property values. No values are written to
		 * this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 		  	valueCountInFastestDim	The number of values to write in the fastest
		 * 											dimension (mainly I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values to write in the middle dimension
		 * 											(mainly J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values to write in the slowest
		 * 											dimension (mainly K dimension).
		 * @param 		  	minimumValue		  	The minimum value of the values to add. If
		 * 											@c NaN is provided (default) then neither minimum nor
		 * 											maximum value will be set.
		 * @param 		  	maximumValue		  	The maximum value of the values to add. If
		 * 											@c NaN is provided (default) then neither maximum nor
		 * 											minimum value will be set.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5Array3dOfValues(
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			float minimumValue, float maximumValue,
			EML2_NS::AbstractHdfProxy* proxy = nullptr
		);

		/**
		 * Sets some values of an existing 3d array of explicit float values of a particular patch. This
		 * method makes use of HDF5 hyperslabbing. Since this methods only pushes back values into an
		 * existing array, it is to be used along with pushBackFloatHdf5Array3dOfValues().
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 * @exception	std::out_of_range	 	If @p patchIndex is strictly greater than patch count and
		 * 										different from unsigned int maximum value.
		 *
		 * @param 		  	values				  	All the property values to set ordered according to
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
		 * @param 		  	computeMinMax		  	True if FESAPI needs to compute
		 * 											the min and  max from the given @p values in order to
		 * 											set them.
		 * @param [in,out]	proxy				  	The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @p nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 * @param 		  	patchIndex			  	(Optional) Zero-based index of the patch where to
		 * 											write the property values. If not provided, its
		 * 											default value is by convention set to unsigned int
		 * 											maximum value and the property values will be written
		 * 											in the last property values patch (the one with the
		 * 											greatest index).
		 */
		DLL_IMPORT_OR_EXPORT void setValuesOfFloatHdf5Array3dOfValues(
			float const * values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()
		);
		using AbstractValuesProperty::setValuesOfFloatHdf5Array3dOfValues;

		/**
		 * Set some values of an existing 3d array of explicit float values of a particular patch.  This
		 * method makes use of HDF5 hyperslabbing. This method is to be used along with one of the
		 * pushBackFloatHdf5ArrayOfValues() methods which do not write any value.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 * @exception	std::out_of_range	 	If @p patchIndex is strictly greater than patch count and
		 * 										different from unsigned int maximum value.
		 *
		 * @param 		  	values			  	All the property values to set ordered according to the
		 * 										topology of the representation it is based on.
		 * @param 		  	numValues		  	The number of property values ordered by dimension of the
		 * 										array to write. It is ordered from slowest dimension to
		 * 										fastest dimension.
		 * @param 		  	offsetValues	  	The offset values ordered by dimension of the array to
		 * 										write. It is ordered from slowest dimension to fastest
		 * 										dimension.
		 * @param 		  	numArrayDimensions	The number of dimensions of the array to write.
		 * @param 		  	computeMinMax	  	True if FESAPI needs to compute the
		 * 										min and  max from the given @p values in order to set
		 * 										them.
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If @p nullptr (default), a
		 * 										default HDF proxy must be defined into the data object
		 * 										repository.
		 * @param 		  	patchIndex		  	(Optional) Zero-based index of the patch where to write
		 * 										the property values. If not provided, its default value
		 * 										is by convention set to unsigned int maximum value and
		 * 										the property values will be written in the last property
		 * 										values patch (the one with the greatest index).
		 */
		DLL_IMPORT_OR_EXPORT void setValuesOfFloatHdf5ArrayOfValues(
			float const * values,
			unsigned long long const * numValues,
			unsigned long long const * offsetValues,
			unsigned int numArrayDimensions,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()
		);
		using AbstractValuesProperty::setValuesOfFloatHdf5ArrayOfValues;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT ContinuousProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractValuesProperty(partialObject) {}

		/** Default constructor */
		ContinuousProperty() {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		ContinuousProperty(gsoap_resqml2_0_1::_resqml20__ContinuousProperty* fromGsoap) : AbstractValuesProperty(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gSoap RESQML2.2 instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		ContinuousProperty(gsoap_eml2_3::_resqml22__ContinuousProperty* fromGsoap) : AbstractValuesProperty(fromGsoap) {}

	private:

		/**
		 * Compute and set the minimum and maximum value in \p values.
		 *
		 * @exception	std::invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @tparam	T	Generic type parameter.
		 * @param 		  	values						The array of values.
		 * @param 		  	numValuesInEachDimension	The number of property values in each dimension.
		 * @param 		  	numArrayDimensions			The number of dimensions of the array.
		 * @param [in,out]	minimumValue				(Optional) If this value and \p maximumValue are
		 * 												defined then the method does not compute the min but
		 * 												forces it to this value.
		 * @param [in,out]	maximumValue				(Optional) If this value and \p minimumValue are
		 * 												defined then the method does not compute the max but
		 * 												forces it to this value.
		 */
		template <class T>
		void setPropertyMinMax(
			T const * values, 
			unsigned long long const * numValuesInEachDimension,
			unsigned int numArrayDimensions,
			T * minimumValue = nullptr, T * maximumValue = nullptr)
		{
			if ((minimumValue == nullptr) != (maximumValue == nullptr)) {
				throw std::logic_error("You cannot set min without max and vice versa.");
			}

			const uint64_t elementCount = getElementCountPerValue();

			// Some minimum and maximum values are given : No need to compute them.
			if (minimumValue != nullptr) {
				for (uint64_t componentIndex = 0; componentIndex < elementCount; ++componentIndex) {
					const double currentMinimumValue = getMinimumValue(componentIndex);
					const double currentMaximumValue = getMaximumValue(componentIndex);
					setMinimumValue(fmin(currentMinimumValue, minimumValue[componentIndex]), componentIndex);
					setMaximumValue(fmax(currentMaximumValue, maximumValue[componentIndex]), componentIndex);
				}
				return; // No need to compute max or min value
			}

			uint64_t nValues = numValuesInEachDimension[0];
			//If count > 1, the last (fastest) dimension has the number of properties per indexable element of the representation.
			for (uint64_t dim = 1; dim < (elementCount == 1 ? numArrayDimensions : numArrayDimensions - 1); ++dim) {
				nValues *= numValuesInEachDimension[dim];
			}

			// Minimum or maximum values are not given : Need to compute them.
			std::unique_ptr<T[]> allComputedMin(new T[elementCount]);
			std::unique_ptr<T[]> allComputedMax(new T[elementCount]);
			for (uint64_t propIndex = 0; propIndex < elementCount; ++propIndex) {
				allComputedMin[propIndex] = std::numeric_limits<T>::quiet_NaN();
				allComputedMax[propIndex] = std::numeric_limits<T>::quiet_NaN();
				for (uint64_t i = 0; i < nValues; i += elementCount) {
					allComputedMin[propIndex] = fmin(allComputedMin[propIndex], values[i]);
					allComputedMax[propIndex] = fmax(allComputedMax[propIndex], values[i]);
				}
			}
			setPropertyMinMax(values, numValuesInEachDimension, numArrayDimensions, allComputedMin.get(), allComputedMax.get());
		}
	};
}
