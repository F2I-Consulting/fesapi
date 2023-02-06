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
		 * Gets the count of values on a specific dimension of the underlying HDF5 dataset of a given
		 * patch of this property.
		 *
		 * @exception	std::out_of_range	If @p dimIndex is strictly greater than dimension count.
		 * @exception	std::range_error 	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	dimIndex  	The index of the dimension we want to count the values from.
		 * @param 	patchIndex	The index of the patch we want to count the values from.
		 *
		 * @returns	The count of values in the @p dimIndex dimension of @p patchIndex patch.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getValuesCountOfDimensionOfPatch(uint64_t dimIndex, uint64_t patchIndex) const final;

		/**
		 * Gets the count of dimensions of the underlying HDF5 dataset of a given patch of this property.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	patchIndex	The index of the patch we want to count the dimensions from.
		 *
		 * @returns	The number of values, 0 otherwise.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getDimensionsCountOfPatch(uint64_t patchIndex) const final;

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

		//****************************
		//****** INTEGER *************
		//****************************

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
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array1dOfValues(const int64_t * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue);

		/**
		 * Adds a 1d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array1dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackIntHdf5Array1dOfValues(const int * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, int nullValue);

		/**
		 * Adds a 1d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array1dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackShortHdf5Array1dOfValues(const short * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, short nullValue);

		/**
		 * Adds a 1d array of explicit int8_t values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array1dOfValues
		 */
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
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array2dOfValues(const int64_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue);

		/**
		 * Adds a 2d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array2dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackIntHdf5Array2dOfValues(const int * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int nullValue);

		/**
		 * Adds a 2d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array2dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackShortHdf5Array2dOfValues(const short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, short nullValue);

		/**
		 * Adds a 2d array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array2dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5Array2dOfValues(const unsigned short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue);

		/**
		 * Adds a 2d array of explicit int8_t values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array2dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInt8Hdf5Array2dOfValues(const int8_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue);

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
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array3dOfValues(const int64_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue);

		/**
		 * Adds a 3d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array3dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackIntHdf5Array3dOfValues(const int * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int nullValue);

		/**
		 * Adds a 3d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array3dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackShortHdf5Array3dOfValues(const short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, short nullValue);

		/**
		 * Adds a 3d array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array3dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5Array3dOfValues(const unsigned short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue);

		/**
		 * Adds a 3d array of explicit int8_t values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array3dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInt8Hdf5Array3dOfValues(const int8_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue);

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
		DLL_IMPORT_OR_EXPORT virtual void pushBackLongHdf5ArrayOfValues(const int64_t * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue);

		/**
		 * Adds an nd array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackLongHdf5ArrayOfValues
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackIntHdf5ArrayOfValues(const int * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int nullValue);

		/**
		 * Adds an nd array of explicit short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5ArrayOfValues
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackShortHdf5ArrayOfValues(const short * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, short nullValue);

		/**
		 * Adds an nd array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5ArrayOfValues
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackUShortHdf5ArrayOfValues(const unsigned short * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue);

		/**
		 * Adds an nd array of explicit int8_t values to the property values.
		 *
		 * @copydetails pushBackLongHdf5ArrayOfValues
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackInt8Hdf5ArrayOfValues(const int8_t * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue);

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
		 * Gets all the values of a given patch of this instance. Values are supposed to be int ones.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>.
		 *
		 * @returns	The null value.
		 */
		DLL_IMPORT_OR_EXPORT int64_t getLongValuesOfPatch(uint64_t patchIndex, int64_t * values) const;

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

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be integer ones.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>
		 *
		 * @returns	The null value.
		 */
		DLL_IMPORT_OR_EXPORT int32_t getIntValuesOfPatch(uint64_t patchIndex, int32_t* values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be unsigned
		 * integer ones.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>
		 *
		 * @returns	The null value.
		 */
		DLL_IMPORT_OR_EXPORT uint32_t getUIntValuesOfPatch(uint64_t patchIndex, uint32_t* values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be short ones.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>
		 *
		 * @returns	The null value.
		 */
		DLL_IMPORT_OR_EXPORT int16_t getShortValuesOfPatch(uint64_t patchIndex, int16_t* values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be unsigned
		 * short ones.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>
		 *
		 * @returns	The null value.
		 */
		DLL_IMPORT_OR_EXPORT uint16_t getUShortValuesOfPatch(uint64_t patchIndex, uint16_t* values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be int8 ones.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>
		 *
		 * @returns	The null value.
		 */
		DLL_IMPORT_OR_EXPORT int8_t getInt8ValuesOfPatch(uint64_t patchIndex, int8_t* values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be uint8 ones
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values. Size is
		 * 							<tt>getValuesCountOfPatch(patchIndex)</tt>
		 *
		 * @returns	The null value.
		 */
		DLL_IMPORT_OR_EXPORT uint8_t getUInt8ValuesOfPatch(uint64_t patchIndex, uint8_t* values) const;

		//***********************************
		//*** For hyperslabbing *****
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
		 * @param 			nullvalue			The integer null value in case we create an integer array.
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
		 * @param 			nullvalue			The integer null value in case we create an integer array.
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
		 * @param 			nullvalue				The integer null value in case we create an integer array.
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
			uint64_t valueCountInMiddleDim,
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
		 * @param 			nullvalue			The integer null value in case we create an integer array.
		 * 										It is ignored if the @p datatype is a floating point one.
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
		 * pushBackLongHdf5ArrayOfValues().
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
		 * pushBackLongHdf5Array3dOfValues().
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
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)());
		DLL_IMPORT_OR_EXPORT void setValuesOfInt32Hdf5Array1dOfValues(
			int32_t const* values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)());
		DLL_IMPORT_OR_EXPORT void setValuesOfDoubleHdf5Array1dOfValues(
			double const * values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)());
		DLL_IMPORT_OR_EXPORT void setValuesOfFloatHdf5Array1dOfValues(
			float const * values,
			uint64_t valueCount,
			uint64_t offset,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)());

		/**
		 * Adds a 2d array of explicit values into the property values. Since this methods
		 * only pushes back values into an existing array, it is to be used along with
		 * pushBackLongHdf5Array2dOfValues().
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
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)());
		DLL_IMPORT_OR_EXPORT void setValuesOfInt32Hdf5Array2dOfValues(
			int32_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)());
		DLL_IMPORT_OR_EXPORT void setValuesOfDoubleHdf5Array2dOfValues(
			double const * values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)());
		DLL_IMPORT_OR_EXPORT void setValuesOfFloatHdf5Array2dOfValues(
			float const * values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)());

		/**
		 * Adds a 3d array of explicit int 64 bits values into the property values. Since this methods
		 * only pushes back values into an existing array, it is to be used along with
		 * pushBackLongHdf5Array3dOfValues().
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
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)());
		DLL_IMPORT_OR_EXPORT void setValuesOfInt32Hdf5Array3dOfValues(
			int32_t const* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)());
		DLL_IMPORT_OR_EXPORT void setValuesOfDoubleHdf5Array3dOfValues(
			double const * values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)());
		DLL_IMPORT_OR_EXPORT void setValuesOfFloatHdf5Array3dOfValues(
			float const * values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)());

		//***********************************
		//*** INTEGER For hyperslabbing *****
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
		DLL_IMPORT_OR_EXPORT void getLongValuesOfPatch(
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
		DLL_IMPORT_OR_EXPORT void getLongValuesOf3dPatch(
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
		DLL_IMPORT_OR_EXPORT void pushBackDoubleHdf5ArrayOfValues(double const * values, uint64_t const * numValues, unsigned int numArrayDimensions, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds a 1d array of explicit float values to the property values.
		 *
		 * @copydetails pushBackDoubleHdf5Array1dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5Array1dOfValues(const float * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds a 2d array of explicit float values to the property values.
		 *
		 * @copydetails pushBackDoubleHdf5Array2dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5Array2dOfValues(const float * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds a 3d array of explicit float values to the property values.
		 *
		 * @copydetails pushBackDoubleHdf5Array3dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5Array3dOfValues(const float * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds an nd array of explicit float values to the property values.
		 *
		 * @copydetails	pushBackDoubleHdf5ArrayOfValues
		 */
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
		DLL_IMPORT_OR_EXPORT void getDoubleValuesOfPatch(uint64_t patchIndex, double * values) const;

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
		DLL_IMPORT_OR_EXPORT void getFloatValuesOfPatch(uint64_t patchIndex, float * values) const;

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
		 * pushBackLongHdf5ArrayOfValues().
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
	};
}
