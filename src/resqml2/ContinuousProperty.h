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
		virtual ~ContinuousProperty() {}

		/**
		 * Gets the unit of measure of the values of this property. If <tt>
		 * resqml20__ResqmlUom::resqml20__ResqmlUom__Euc </tt> is returned, you should check if
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
		 * @param [in,out]	proxy			(Optional) The HDF proxy where to write the property values.
		 * 									It must be already opened for writing and won't be closed in this
		 * 									method. If @c nullptr (default value), then a default HDF proxy
		 * 									must be defined in the repository.
		 * @param 		  	minimumValue	(Optional) The minimum value of the values to add. If @c NaN is
		 * 									provided then both minimum and maximum values will be computed
		 * 									from the values.
		 * @param 		  	maximumValue	(Optional) The maximum value of the values to add. If @c NaN is
		 * 									provided then both maximum and minimum values will be computed
		 * 									from the values.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackDoubleHdf5Array1dOfValues(const double * values, ULONG64 valueCount, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			double minimumValue = std::numeric_limits<double>::quiet_NaN(), double maximumValue = std::numeric_limits<double>::quiet_NaN());

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
		 * @param 		  	minimumValue		  	(Optional) The minimum value of the values to add. If
		 * 											@c NaN is provided then both minimum and maximum
		 * 											values will be computed from the values.
		 * @param 		  	maximumValue		  	(Optional) The maximum value of the values to add. If
		 * 											@c NaN is provided then both maximum and minimum
		 * 											values will be computed from the values.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackDoubleHdf5Array2dOfValues(const double * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			double minimumValue = std::numeric_limits<double>::quiet_NaN(), double maximumValue = std::numeric_limits<double>::quiet_NaN());

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
		 * @param 		  	minimumValue		  	(Optional) The minimum value of the values to add. If
		 * 											@c NaN is provided then both minimum and maximum
		 * 											values will be computed from the values.
		 * @param 		  	maximumValue		  	(Optional) The maximum value of the values to add. If
		 * 											@c NaN is provided then both maximum and minimum
		 * 											values will be computed from the values.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackDoubleHdf5Array3dOfValues(const double * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			double minimumValue = std::numeric_limits<double>::quiet_NaN(), double maximumValue = std::numeric_limits<double>::quiet_NaN());

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
		 * @param [in]	  	minimumValue	  	(Optional) The minimum value (or value vector) of the
		 * 										values to add. If @c nullptr is provided for both @p
		 * 										minimumValue and @p maximumValue and if the dimension of
		 * 										value is 1 then both minimum and maximum values will be
		 * 										computed from the values.
		 * @param [in]	  	maximumValue	  	(Optional) The maximum value (or value vector) of the
		 * 										values to add. If @ nullptr is provided for both @p
		 * 										maximumValue and @p minimumValue and if the dimension of
		 * 										value is 1 then both maximum and minimum values will be
		 * 										computed from the values.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackDoubleHdf5ArrayOfValues(double const * values, unsigned long long const * numValues, unsigned int numArrayDimensions, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			double * minimumValue = nullptr, double * maximumValue = nullptr);

		/**
		 * Adds a 1d array of explicit float values to the property values.
		 *
		 * @copydetails pushBackDoubleHdf5Array1dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5Array1dOfValues(const float * values, ULONG64 valueCount, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			float minimumValue = std::numeric_limits<float>::quiet_NaN(), float maximumValue = std::numeric_limits<float>::quiet_NaN());

		/**
		 * Adds a 2d array of explicit float values to the property values.
		 *
		 * @copydetails pushBackDoubleHdf5Array2dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5Array2dOfValues(const float * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			float minimumValue = std::numeric_limits<float>::quiet_NaN(), float maximumValue = std::numeric_limits<float>::quiet_NaN());

		/**
		 * Adds a 3d array of explicit float values to the property values.
		 *
		 * @copydetails pushBackDoubleHdf5Array3dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5Array3dOfValues(const float * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			float minimumValue = std::numeric_limits<float>::quiet_NaN(), float maximumValue = std::numeric_limits<float>::quiet_NaN());

		/**
		 * Adds an nd array of explicit float values to the property values.
		 * 
		 * @exception std::invalid_argument If <tt> minimumValue == nullptr </tt> and <tt> maximumValue != nullptr </tt>.
		 * @exception std::invalid_argument	If <tt> minimumValue != nullptr </tt> and <tt> maximumValue == nullptr </tt>.
		 * 									
		 * @copydetails	pushBackDoubleHdf5ArrayOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5ArrayOfValues(float const * values, unsigned long long const * numValues, unsigned int numArrayDimensions, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			float * minimumValue = nullptr, float * maximumValue = nullptr);

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
		DLL_IMPORT_OR_EXPORT virtual std::string pushBackRefToExistingDataset(EML2_NS::AbstractHdfProxy* proxy, const std::string & datasetName = "") = 0;

		/**
		 * Gets all the values of a particular patch of this instance which are supposed to be double
		 * ones.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>.
		 */
		DLL_IMPORT_OR_EXPORT void getDoubleValuesOfPatch(unsigned int patchIndex, double * values) const ;

		/**
		 * Gets all the values of a particular patch of this instance which are supposed to be float
		 * ones.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>.
		 */
		DLL_IMPORT_OR_EXPORT void getFloatValuesOfPatch(unsigned int patchIndex, float * values) const;

		/**
		 * @brief	Gets the minimum value of a non vector property or the minimum value of one given
		 * 			value of a vector property. This minimum value is read (it is not computed).
		 *
		 * @param 	index	(Optional) @c 0 (default value, corresponding to the non vector property case) or
		 * 					zero-based index of the vector value for which we look for the minimum value
		 * 					(vector property case).
		 *
		 * @returns	The minimum value of the non vector property or the minimum value at position @p
		 * 			index of the vector value or @c NaN if @p index is out of range (strictly
		 * 			greater than @p 0 for a non vector property or greater than the vector size for a
		 * 			vector property).
		 */
		DLL_IMPORT_OR_EXPORT virtual double getMinimumValue(unsigned int index = 0) const = 0;

		/**
		 * @brief	Gets the maximum value of a non vector property or the maximum value of one given
		 * 			value of a vector property. This maximum value is read (it is not computed).
		 *
		 * @param 	index	(Optional) @c 0 (default value, corresponding to the non vector property case) or
		 * 					zero-based index of the vector value for which we look for the maximum value
		 * 					(vector property case).
		 *
		 * @returns	The maximum value of the non vector property or the maximum value at position @p
		 * 			index of the vector value or @c NaN if @p index is out of range (strictly
		 * 			greater than @p 0 for a non vector property or greater than the vector size for a
		 * 			vector property).
		 */
		DLL_IMPORT_OR_EXPORT virtual double getMaximumValue(unsigned int index = 0) const = 0;

		/**
		 * @brief	Sets the minimum value of a non vector property or the minimum value of one given
		 * 			value of a vector property.
		 *
		 * @param 	value	The minimum value to set.
		 * @param 	index	(Optional)  @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we want to set the
		 * 					minimum value (vector property case).
		 */
		DLL_IMPORT_OR_EXPORT virtual void setMinimumValue(double value, unsigned int index = 0) const = 0;

		/**
		 * @brief	Sets the maximum value of a non vector property or the maximum value of one given
		 * 			value of a vector property.
		 *
		 * @param 	value	The maximum value to set.
		 * @param 	index	(Optional)  @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we want to set the
		 * 					maximum value (vector property case).
		 */
		DLL_IMPORT_OR_EXPORT virtual void setMaximumValue(double value, unsigned int index = 0) const = 0;

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
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If @c nullptr (default), a
		 * 										default HDF proxy must be defined into the data object
		 * 										repository.
		 * @param [in]	  	minimumValue	  	(Optional) The minimum value (or value vector) of the
		 * 										values to add. If @c nullptr (default) is provided then
		 * 										neither minimum nor maximum value will be set.
		 * @param [in]	  	maximumValue	  	(Optional) The maximum value (or value vector) of the
		 * 										values to add. If @c nullptr (default) is provided then
		 * 										neither maximum nor minimum value will be set.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5ArrayOfValues(
			unsigned long long const * numValues,
			unsigned int numArrayDimensions,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			float * minimumValue = nullptr, float * maximumValue = nullptr
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
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @c nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 * @param 		  	minimumValue		  	(Optional) The minimum value of the values to add. If
		 * 											@c NaN is provided (default) then neither minimum nor
		 * 											maximum value will be set.
		 * @param 		  	maximumValue		  	(Optional) The maximum value of the values to add. If
		 * 											@c NaN is provided (default) then neither maximum nor
		 * 											minimum value will be set.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5Array3dOfValues(
			ULONG64 valueCountInFastestDim,
			ULONG64 valueCountInMiddleDim,
			ULONG64 valueCountInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			float minimumValue = std::numeric_limits<float>::quiet_NaN(), float maximumValue = std::numeric_limits<float>::quiet_NaN()
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
		 * @param 		  	computeMinMax		  	(Optional) True (default) if FESAPI needs to compute
		 * 											the min and  max from the given @p values in order to
		 * 											set them.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
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
			ULONG64 valueCountInFastestDim,
			ULONG64 valueCountInMiddleDim,
			ULONG64 valueCountInSlowestDim,
			ULONG64 offsetInFastestDim,
			ULONG64 offsetInMiddleDim,
			ULONG64 offsetInSlowestDim,
			bool computeMinMax = true,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned int patchIndex = (std::numeric_limits<unsigned int>::max)()
		);

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
		 * @param 		  	computeMinMax	  	(Optional) True (default) if FESAPI needs to compute the
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
			bool computeMinMax = true,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned int patchIndex = (std::numeric_limits<unsigned int>::max)()
		);

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
			unsigned int patchIndex,
			float* values,
			unsigned long long const * numValuesInEachDimension,
			unsigned long long const * offsetInEachDimension,
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
			unsigned int patchIndex,
			float* values,
			ULONG64 valueCountInFastestDim,
			ULONG64 valueCountInMiddleDim,
			ULONG64 valueCountInSlowestDim,
			ULONG64 offsetInFastestDim,
			ULONG64 offsetInMiddleDim,
			ULONG64 offsetInSlowestDim
		) const;

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

		virtual EML2_NS::AbstractHdfProxy* getValuesHdfProxyAndDatasetPathOfPatch(unsigned int patchIndex, std::string & datasetPath) const = 0;

		virtual size_t getMinimumValueSize() const = 0;
		virtual size_t getMaximumValueSize() const = 0;

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
			const unsigned int elementCount = getElementCountPerValue();

			// Some minimum and maximum values are given : No need to compute them.
			if (minimumValue != nullptr) {
				for (size_t propIndex = 0; propIndex < elementCount; ++propIndex) {
					setMinimumValue(getMinimumValueSize() > propIndex ? fmin(getMinimumValue(propIndex), minimumValue[propIndex]) : minimumValue[propIndex], propIndex);
				}
			}
			if (maximumValue != nullptr) {
				for (size_t propIndex = 0; propIndex < elementCount; ++propIndex) {
					setMaximumValue(getMaximumValueSize() > propIndex ? fmax(getMaximumValue(propIndex), maximumValue[propIndex]) : maximumValue[propIndex], propIndex);
				}
			}
			if (minimumValue != nullptr && maximumValue != nullptr) return; // No need to compute max or min value

			ULONG64 nValues = numValuesInEachDimension[0];
			//If count > 1, the last (fastest) dimension has the number of properties per indexable element of the representation.
			for (unsigned int dim = 1; dim < (elementCount == 1 ? numArrayDimensions : numArrayDimensions - 1); ++dim) {
				nValues *= numValuesInEachDimension[dim];
			}

			// Minimum or maximum values are not given : Need to compute them.
			std::unique_ptr<T[]> allComputedMin(new T[elementCount]);
			std::unique_ptr<T[]> allComputedMax(new T[elementCount]);
			for (size_t propIndex = 0; propIndex < elementCount; ++propIndex) {
				allComputedMin[propIndex] = std::numeric_limits<T>::quiet_NaN();
				allComputedMax[propIndex] = std::numeric_limits<T>::quiet_NaN();
				for (size_t i = 0; i < nValues; i += elementCount) {
					allComputedMin[propIndex] = fmin(allComputedMin[propIndex], values[i]);
					allComputedMax[propIndex] = fmax(allComputedMax[propIndex], values[i]);
				}
			}
			setPropertyMinMax(values, numValuesInEachDimension, numArrayDimensions, allComputedMin.get(), allComputedMax.get());
		}
	};
}
