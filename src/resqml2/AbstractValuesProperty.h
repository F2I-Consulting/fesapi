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

#include <limits>
#include "AbstractProperty.h"

/** . */
namespace RESQML2_NS
{
	/** Proxy class for an abstract values property. */
	class AbstractValuesProperty : public AbstractProperty
	{
	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
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

		/**
		 * Get the dataset which contains the property values of a particular patch.
		 *
		 * @param 		  	patchIndex	The corresponding patch index of the dataset to get.
		 * @param [in,out]	nullValue 	If possible, this function will set this parameter to the Resqml
		 * 								null value of the dataset. If not, it will return long.min.
		 *
		 * @returns	Null if it fails, else the dataset of patch.
		 */
		gsoap_resqml2_0_1::eml20__Hdf5Dataset const * getDatasetOfPatch(unsigned int patchIndex, LONG64 & nullValue) const;

		/**
		 * Push back a new patch of integer values for this property where the values have not to be
		 * written in the HDF5 file. The reason can be that the values already exist in an external file
		 * (only HDF5 for now) or that the writing of the values in the external file is differed in
		 * time.
		 *
		 * @param [in]	hdfProxy   	The HDF5 proxy where the values are already or will be stored. If
		 * 							null then a default HDF proxy must be defined in the data object
		 * 							repository.
		 * @param 	  	datasetName	(Optional) If not provided during the method call, the dataset will
		 * 							be named the same as the dataset naming convention of fesapi:
		 * 							<tt>"/RESQML/" + prop-&gt;uuid + "/values_patch" + patchIndex</tt>
		 * @param 	  	nullValue  	(Optional) Only relevant for integer hdf5 datasets. Indeed, RESQML
		 * 							(and fesapi) forces null value for floating point to be NaN value.
		 *
		 * @returns	The name of the HDF5 dataset.
		 */
		std::string pushBackRefToExistingIntegerDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName = "", LONG64 nullValue = (std::numeric_limits<LONG64>::max)());

		/** Loads target relationships */
		void loadTargetRelationships();

	public:

		/** Values that represent HDF data types */
		enum hdfDatatypeEnum { UNKNOWN = 0, DOUBLE = 1, FLOAT = 2, LONG_64 = 3, ULONG_64 = 4, INT = 5, UINT = 6, SHORT = 7, USHORT = 8, CHAR = 9, UCHAR = 10};

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~AbstractValuesProperty() {}

		/**
		 * Gets the number of patches in this values property. It should be the same count as the patch
		 * count of the associated representation.
		 *
		 * @exception	std::out_of_range	If the patch count is strictly greater than unsigned int max
		 * 									value.
		 *
		 * @returns	The patch count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const;

		/**
		 * Get the values data type in the HDF dataset
		 *
		 * @returns	The data type of the values if successful, else @c UNKNOWN.
		 */
		DLL_IMPORT_OR_EXPORT AbstractValuesProperty::hdfDatatypeEnum getValuesHdfDatatype() const;

		/**
		 * Pushes back a new patch of values for this property where the values have not to be written
		 * in the HDF5 file. The reason can be that the values already exist in an external file (only
		 * HDF5 for now) or that the writing of the values in the external file is differed in time.
		 *
		 * @param [in]	hdfProxy   	The HDF5 proxy where the values are already or will be stored. If
		 * 							null then a default HDF proxy must be defined in the data object
		 * 							repository.
		 * @param 	  	datasetName	(Optional) If not provided during the method call, the dataset will
		 * 							be named the same as the dataset naming convention of fesapi:
		 * 							<tt>"/RESQML/" + prop-&gt;uuid + "/values_patch" + patchIndex</tt>
		 * @param 	  	nullValue  	(Optional) Only relevant for integer hdf5 datasets. Indeed, RESQML
		 * 							(and fesapi) forces null value for floating point to be NaN value.
		 *
		 * @returns	The name of the HDF5 dataset.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName = "", LONG64 nullValue = (std::numeric_limits<LONG64>::max)()) = 0;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be long ones.
		 * Do not use this method for continuous property values.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values.
		 *
		 * @returns	The null value.
		 */
		DLL_IMPORT_OR_EXPORT LONG64 getLongValuesOfPatch(unsigned int patchIndex, LONG64 * values) const;

		/**
		 * Gets the null value of a given patch of this instance. Values are supposed to be integer
		 * ones. Do not use this method for continuous property values.
		 *
		 * @exception	std::range_error	 	If @p patchIndex is strictly greater than patch count.
		 * @exception	std::invalid_argument	If the @p patchIndex patch does not contain integer
		 * 										values.
		 *
		 * @param 	patchIndex	The index of the patch we want the values from.
		 *
		 * @returns	the null value.
		 */
		DLL_IMPORT_OR_EXPORT LONG64 getNullValueOfPatch(unsigned int patchIndex) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be unsigned
		 * long ones. Do not use this method for continuous property values.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values.
		 *
		 * @returns	The null value.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getULongValuesOfPatch(unsigned int patchIndex, ULONG64 * values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be int ones. Do
		 * not use this method for continuous property values.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values.
		 *
		 * @returns	The null value.
		 */
		DLL_IMPORT_OR_EXPORT int getIntValuesOfPatch(unsigned int patchIndex, int * values) const;

		/**
		 * Gets some of the values of a given patch of this instance. Values are supposed to be int
		 * ones. This method makes use of HDF5 hyperslabbing.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex					The index of the patch we want the values from.
		 * @param [out]	values						Preallocated buffer for receiving the values.
		 * @param [in] 	numValuesInEachDimension	The number of property values ordered by dimension of
		 * 											the array to read.
		 * @param [in] 	offsetInEachDimension   	The offset values ordered by dimension of the array
		 * 											to read.
		 * @param 	   	numArrayDimensions			The number of dimensions of the HDF5 array to read.
		 *
		 * @returns	the null value.
		 */
		DLL_IMPORT_OR_EXPORT int getIntValuesOfPatch(
			unsigned int patchIndex,
			int* values,
			unsigned long long* numValuesInEachDimension,
			unsigned long long* offsetInEachDimension,
			unsigned int numArrayDimensions
		) const;

		/**
		 * Gets some of the values of a given patch of this instance. Values are supposed to be int
		 * ones.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex			  	The index of the patch we want the values from.
		 * @param [out]	values				  	Preallocated buffer for receiving the values.
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
			unsigned int patchIndex,
			int* values,
			unsigned int valueCountInFastestDim,
			unsigned int valueCountInMiddleDim,
			unsigned int valueCountInSlowestDim,
			unsigned int offsetInFastestDim,
			unsigned int offsetInMiddleDim,
			unsigned int offsetInSlowestDim
		) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be unsigned int
		 * ones. Do not use this method for continuous property values.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values.
		 *
		 * @returns	The null value.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getUIntValuesOfPatch(unsigned int patchIndex, unsigned int * values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be short ones.
		 * Do not use this method for continuous property values.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values.
		 *
		 * @returns	The null value.
		 */
		DLL_IMPORT_OR_EXPORT short getShortValuesOfPatch(unsigned int patchIndex, short * values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be unsigned
		 * short ones. Do not use this method for continuous property values.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values.
		 *
		 * @returns	The null value.
		 */
		DLL_IMPORT_OR_EXPORT unsigned short getUShortValuesOfPatch(unsigned int patchIndex, unsigned short * values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be char ones.
		 * Do not use this method for continuous property values.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values.
		 *
		 * @returns	The null value.
		 */
		DLL_IMPORT_OR_EXPORT char getCharValuesOfPatch(unsigned int patchIndex, char * values) const;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be unsigned
		 * char ones. Do not use this method for continuous property values.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex	The index of the patch we want the values from.
		 * @param [out]	values	  	Preallocated buffer for receiving the values.
		 *
		 * @returns	The null value.
		 */
		DLL_IMPORT_OR_EXPORT unsigned char getUCharValuesOfPatch(unsigned int patchIndex, unsigned char * values) const;

		/**
		 * Gets the count of all values contained into the underlying HDF5 dataset of a given patch of
		 * this property.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	patchIndex	The index of the patch we want to count the values from.
		 *
		 * @returns	The count of values of the @p patchIndex patch.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getValuesCountOfPatch (unsigned int patchIndex) const;

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
		DLL_IMPORT_OR_EXPORT unsigned int getValuesCountOfDimensionOfPatch(unsigned int dimIndex, unsigned int patchIndex) const;

		/**
		 * Gets the count of dimensions of the underlying HDF5 dataset of a given patch of this property.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	patchIndex	The index of the patch we want to count the dimensions from.
		 *
		 * @returns	The number of values, 0 otherwise.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getDimensionsCountOfPatch(unsigned int patchIndex) const;

		/**
		 * Pushes back a new facet to this instance. Facets are qualifiers for property values which
		 * allow users to semantically specialize a property without creating a new property kind.
		 *
		 * @param 	facet	  	The facet.
		 * @param 	facetValue	The facet value.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackFacet(const gsoap_resqml2_0_1::resqml20__Facet & facet, const std::string & facetValue);

		/**
		 * Gets the count of facet of this instance
		 *
		 * @returns	The facet count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getFacetCount() const;

		/**
		 * Gets the facet at a particular index of the facet collection of this instance.
		 *
		 * @exception	std::out_of_range	If @p index is strictly greater than facet count.
		 *
		 * @param 	index	Zero-based index of the facet we want to get.
		 *
		 * @returns	The facet at index @p index.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__Facet getFacet(unsigned int index) const;

		/**
		 * Gets the facet value at a particular index of the facet collection of this instance.
		 *
		 * @exception	std::out_of_range	If @p index is strictly greater than facet count.
		 *
		 * @param 	index	Zero-based index of the facet we want to get.
		 *
		 * @returns	The facet value at index @p index.
		 */
		DLL_IMPORT_OR_EXPORT std::string getFacetValue(unsigned int index) const;

		//***************************
		//*** For hyperslabbing *****
		//***************************

		/**
		 * Creates an nd array of explicit long values into the property values. No values are written
		 * to this array yet.
		 *
		 * @exception	std::invalid_argument	If @p proxy is null and no default HDF proxy is defined
		 * 										into the data object repository.
		 *
		 * @param [in]	numValues		  	The number of property values ordered by dimension of the
		 * 									array to write.
		 * @param 	  	numArrayDimensions	The number of dimensions of the array to write.
		 * @param [in]	proxy			  	(Optional) The HDF proxy where to write the property values.
		 * 									It must be already opened for writing and won't be closed in
		 * 									this method. If null (default value), a default HDF proxy
		 * 									must be defined into the data object repository.
		 */
		DLL_IMPORT_OR_EXPORT void createLongHdf5ArrayOfValues(
			unsigned long long* numValues, 
			unsigned int numArrayDimensions, 
			COMMON_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Creates a 3d array of explicit long values into the property values. No values are written to
		 * this array yet.
		 *
		 * @exception	std::invalid_argument	If @p proxy is null and no default HDF proxy is defined
		 * 										into the data object repository.
		 *
		 * @param 	  	valueCountInFastestDim	The number of values in the fastest dimension (mainly I
		 * 										dimension).
		 * @param 	  	valueCountInMiddleDim 	The number of values in the middle dimension (mainly J
		 * 										dimension).
		 * @param 	  	valueCountInSlowestDim	The number of values in the slowest dimension (mainly K
		 * 										dimension).
		 * @param [in]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If null (default value), a
		 * 										default HDF proxy must be defined into the data object
		 * 										repository.
		 */
		DLL_IMPORT_OR_EXPORT void createLongHdf5Array3dOfValues(
			unsigned int valueCountInFastestDim, 
			unsigned int valueCountInMiddleDim, 
			unsigned int valueCountInSlowestDim, 
			COMMON_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds a 3d array of explicit long values into the property values. Since this methods only
		 * pushes back values into an existing array, it is to be used along with {@link
		 * createLongHdf5Array3dOfValues}.
		 *
		 * @exception	std::invalid_argument	If @p proxy is null and no default HDF proxy is defined
		 * 										into the data object repository.
		 *
		 * @param [in]	values				  	All the property values to set ordered according to the
		 * 											topology of the representation it is based on.
		 * @param 	  	valueCountInFastestDim	The number of values to write in the fastest dimension
		 * 										(mainly I dimension).
		 * @param 	  	valueCountInMiddleDim 	The number of values to write in the middle dimension
		 * 										(mainly J dimension).
		 * @param 	  	valueCountInSlowestDim	The number of values to write in the slowest dimension
		 * 										(mainly K dimension).
		 * @param 	  	offsetInFastestDim	  	The offset value for writing in the fastest dimension
		 * 										(mainly I dimension).
		 * @param 	  	offsetInMiddleDim	  	The offset value for writing in the middle dimension
		 * 										(mainly J dimension).
		 * @param 	  	offsetInSlowestDim	  	The offset value for writing in the slowest dimension
		 * 										(mainly K dimension).
		 * @param [in]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If null (default value), a
		 * 										default HDF proxy must be defined into the data object
		 * 										repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5SlabArray3dOfValues(
			LONG64* values, 
			unsigned int valueCountInFastestDim, 
			unsigned int valueCountInMiddleDim, 
			unsigned int valueCountInSlowestDim, 
			unsigned int offsetInFastestDim, 
			unsigned int offsetInMiddleDim, 
			unsigned int offsetInSlowestDim, 
			COMMON_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds an nd array of explicit long values into to the property values. Since this methods
		 * only pushes back values into an existing array, it is to be used along with {@link
		 * createLongHdf5ArrayOfValues}.
		 *
		 * @exception	std::invalid_argument	If @p proxy is null and no default HDF proxy is defined
		 * 										into the data object repository.
		 *
		 * @param [in]	values			  	All the property values to set ordered according to the
		 * 									topology of the representation it is based on.
		 * @param 	  	numValues		  	The number of property values ordered by dimension of the
		 * 									array to write.
		 * @param 	  	offsetValues	  	The offset values ordered by dimension of the array to write.
		 * @param 	  	numArrayDimensions	The number of dimensions of the array to write.
		 * @param [in]	proxy			  	(Optional) The HDF proxy where to write the property values.
		 * 									It must be already opened for writing and won't be closed in
		 * 									this method. If null (default value), a default HDF proxy
		 * 									must be defined into the data object repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5SlabArrayOfValues(
			LONG64* values,
			unsigned long long const * numValues,
			unsigned long long const * offsetValues,
			unsigned int numArrayDimensions, 
			COMMON_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Gets some of the values of a given patch of this instance. Values are supposed to be long ones.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex					The index of the patch we want the values from.
		 * @param [out]	values						Preallocated buffer for receiving the values.
		 * @param 	   	numValuesInEachDimension	The number of property values ordered by dimension of
		 * 											the array to read.
		 * @param 	   	offsetInEachDimension   	The offset values ordered by dimension of the array
		 * 											to read.
		 * @param 	   	numArrayDimensions			The number of dimensions of the array to write.
		 */
		DLL_IMPORT_OR_EXPORT void getLongValuesOfPatch(
			unsigned int patchIndex, 
			LONG64* values,
			unsigned long long const * numValuesInEachDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned int numArrayDimensions
		) const;

		/**
		 * Gets some of the values of a given patch of this instance. Values are supposed to be long ones.
		 *
		 * @exception	std::range_error	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	   	patchIndex			  	The index of the patch we want the values from.
		 * @param [out]	values				  	Preallocated buffer for receiving the values.
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
			unsigned int patchIndex, 
			LONG64* values,
			unsigned int valueCountInFastestDim, 
			unsigned int valueCountInMiddleDim, 
			unsigned int valueCountInSlowestDim, 
			unsigned int offsetInFastestDim, 
			unsigned int offsetInMiddleDim, 
			unsigned int offsetInSlowestDim
		) const;
	};
}
