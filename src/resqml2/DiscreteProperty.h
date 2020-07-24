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

#include "AbstractDiscreteOrCategoricalProperty.h"

#include <limits>

namespace RESQML2_NS
{
	/**
	 * @brief	Proxy class for a discrete  property. Such property contains discrete integer values;
	 * 			typically used to store any type of index. So that the value range can be known
	 * 			before accessing all values, it also optionally stores the minimum and maximum value
	 * 			in the range.
	 */
	class DiscreteProperty : public RESQML2_NS::AbstractDiscreteOrCategoricalProperty
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~DiscreteProperty() {}

		/**
		 * @brief Adds a 1d array of explicit long values to the property values.
		 *
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	values			All the property values to set ordered according to the
		 * 									topology of the representation it is based on.
		 * @param 		  	valueCount  	The number of values to write.
		 * @param [in,out]	proxy			The HDF proxy where to write the property values. It must be
		 * 									already opened for writing and won't be closed in this method. If
		 * 									@c nullptr, then a default HDF proxy must be defined in the
		 * 									repository.
		 * @param 		  	nullValue   	The null value.
		 * @param 		  	minimumValue	The minimum value of the values to add.
		 * @param 		  	maximumValue	The maximum value of the values to add.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array1dOfValues(const LONG64 * values, ULONG64 valueCount, EML2_NS::AbstractHdfProxy* proxy, LONG64 nullValue, LONG64 minimumValue, LONG64 maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackLongHdf5Array1dOfValues;
		
		/**
		 * Adds a 1d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array1dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackIntHdf5Array1dOfValues(const int * values, ULONG64 valueCount, EML2_NS::AbstractHdfProxy* proxy, int nullValue, int minimumValue, int maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackIntHdf5Array1dOfValues;
		
		/**
		 * Adds a 1d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array1dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackShortHdf5Array1dOfValues(const short * values, ULONG64 valueCount, EML2_NS::AbstractHdfProxy* proxy, short nullValue, short minimumValue, short maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackShortHdf5Array1dOfValues;
		
		/**
		 * Adds a 1d array of explicit char values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array1dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackCharHdf5Array1dOfValues(const char * values, ULONG64 valueCount, EML2_NS::AbstractHdfProxy* proxy, char nullValue, char minimumValue, char maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackCharHdf5Array1dOfValues;

		/**
		 * @brief Adds a 2d array of explicit long values to the property values.
		 *
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
		 * @param 		  	minimumValue		  	The minimum value of the values to add.
		 * @param 		  	maximumValue		  	The maximum value of the values to add.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array2dOfValues(const LONG64 * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, LONG64 nullValue, LONG64 minimumValue, LONG64 maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackLongHdf5Array2dOfValues;
		
		/**
		 * Adds a 2d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array2dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackIntHdf5Array2dOfValues(const int * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int nullValue, int minimumValue, int maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackIntHdf5Array2dOfValues;
		
		/**
		 * Adds a 2d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array2dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackShortHdf5Array2dOfValues(const short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, short nullValue, short minimumValue, short maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackShortHdf5Array2dOfValues;
		
		/**
		 * Adds a 2d array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array2dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5Array2dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackUShortHdf5Array2dOfValues;
		
		/**
		 * Adds a 2d array of explicit char values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array2dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackCharHdf5Array2dOfValues(const char * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, char nullValue, char minimumValue, char maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackCharHdf5Array2dOfValues;

		/**
		 * @brief Adds a 3d array of explicit long values to the property values.
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
		 * @param [in,out]	proxy				  	The HDF proxy where to write the property values. It
		 * 											must be already opened for writing and won't be
		 * 											closed in this method. If @c nullptr, then a default
		 * 											HDF proxy must be defined in the repository.
		 * @param 		  	nullValue			  	The null value.
		 * @param 		  	minimumValue		  	The minimum value of the values to add.
		 * @param 		  	maximumValue		  	The maximum value of the values to add.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array3dOfValues(const LONG64 * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, LONG64 nullValue, LONG64 minimumValue, LONG64 maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackLongHdf5Array3dOfValues;
		
		/**
		 * Adds a 3d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array3dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackIntHdf5Array3dOfValues(const int * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, int nullValue, int minimumValue, int maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackIntHdf5Array3dOfValues;
		
		/**
		 * Adds a 3d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array3dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackShortHdf5Array3dOfValues(const short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, short nullValue, short minimumValue, short maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackShortHdf5Array3dOfValues;
		
		/**
		 * Adds a 3d array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array3dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5Array3dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackUShortHdf5Array3dOfValues;
		
		/**
		 * Adds a 3d array of explicit char values to the property values.
		 *
		 * @copydetails pushBackLongHdf5Array3dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackCharHdf5Array3dOfValues(const char * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy, char nullValue, char minimumValue, char maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackCharHdf5Array3dOfValues;

		/**
		 * @brief Adds an nd array of explicit long values to the property values.
		 *
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
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5ArrayOfValues(const LONG64 * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, LONG64 nullValue) final;
		
		/**
		 * Adds an nd array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackLongHdf5ArrayOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackIntHdf5ArrayOfValues(const int * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int nullValue) final;
		
		/**
		 * Adds an nd array of explicit short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5ArrayOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackShortHdf5ArrayOfValues(const short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, short nullValue) final;
		
		/**
		 * Adds an nd array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5ArrayOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5ArrayOfValues(const unsigned short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue) final;
		
		/**
		 * Adds an nd array of explicit char values to the property values.
		 *
		 * @copydetails pushBackLongHdf5ArrayOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackCharHdf5ArrayOfValues(const char * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, char nullValue) final;

		/**
		 * @brief Adds an nd array of explicit long values to the property values.
		 *
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
		 * @param 		  	minimumValue			The minimum value of the values to add. If not
		 * 											provided then the minimum value will be computed from the
		 * 											values.
		 * @param 		  	maximumValue			The maximum value of the values to add. If not
		 * 											provided then the maximum value will be computed from the
		 * 											values.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5ArrayOfValues(const LONG64 * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, LONG64 nullValue, LONG64 minimumValue, LONG64 maximumValue);
		
		/**
		 * Adds an nd array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackLongHdf5ArrayOfValues(const LONG64 *,unsigned long long *,unsigned int,eml2::AbstractHdfProxy*,LONG64,LONG64,LONG64)
		 */
		DLL_IMPORT_OR_EXPORT void pushBackIntHdf5ArrayOfValues(const int * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int nullValue, int minimumValue, int maximumValue);
		
		/**
		 * Adds an nd array of explicit short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5ArrayOfValues(const LONG64 *,unsigned long long *,unsigned int,eml2::AbstractHdfProxy*,LONG64,LONG64,LONG64)
		 */
		DLL_IMPORT_OR_EXPORT void pushBackShortHdf5ArrayOfValues(const short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, short nullValue, short minimumValue, short maximumValue);
		
		/**
		 * Adds an nd array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackLongHdf5ArrayOfValues(const LONG64 *,unsigned long long *,unsigned int,eml2::AbstractHdfProxy*,LONG64,LONG64,LONG64)
		 */
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5ArrayOfValues(const unsigned short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue);
		
		/**
		 * Adds an nd array of explicit char values to the property values.
		 *
		 * @copydetails pushBackLongHdf5ArrayOfValues(const LONG64 *,unsigned long long *,unsigned int,eml2::AbstractHdfProxy*,LONG64,LONG64,LONG64)
		 */
		DLL_IMPORT_OR_EXPORT void pushBackCharHdf5ArrayOfValues(const char * values, unsigned long long * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, char nullValue, char minimumValue, char maximumValue);

		/**
		 * Pushes back a reference to an existing (or a "to exist") HDF dataset in a particular HDF
		 * proxy. The reason can be that the index values already exist in an external file (only HDF5
		 * for now) or that the writing of the values in the external file is differed in time.
		 *
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
		DLL_IMPORT_OR_EXPORT virtual std::string pushBackRefToExistingDataset(EML2_NS::AbstractHdfProxy* proxy, const std::string & datasetName, LONG64 nullValue, LONG64 minimumValue, LONG64 maximumValue) = 0;
		using AbstractDiscreteOrCategoricalProperty::pushBackRefToExistingDataset;

		//***************************
		//*** For hyperslabbing *****
		//***************************

		/**
		 * Creates an nd array of explicit long 64 bits values into the property values. No values are
		 * written to this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param [in]	  	numValues		  	The number of property values ordered by dimension of the
		 * 										array to write. It is ordered from slowest dimension to
		 * 										fastest dimension.
		 * @param 		  	numArrayDimensions	The number of dimensions of the array to write.
		 * @param [in]	  	minimumValue	  	If non-nullptr, a pointer to the minimum values. If non-
		 * 										nullptr, the count of minimum values is this property
		 * 										count.
		 * @param [in]	  	maximumValue	  	If non-nullptr, a pointer to the maximum values. If non-
		 * 										nullptr, the count of maximum values is this property
		 * 										count.
		 * @param 		  	nullValue		  	(Optional) The null value. Default value is long 64 bits
		 * 										maximum value.
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If @c nullptr (default), a
		 * 										default HDF proxy must be defined into the data object
		 * 										repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5ArrayOfValues(
			unsigned long long* numValues,
			unsigned int numArrayDimensions,
			LONG64* minimumValue, LONG64* maximumValue,
			LONG64 nullValue = (std::numeric_limits<LONG64>::max)(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr);
		using AbstractDiscreteOrCategoricalProperty::pushBackLongHdf5ArrayOfValues;

		/**
		 * Creates a 3d array of explicit long 64 values into the property values. No values are written
		 * to this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 		  	valueCountInFastestDim	The number of values in the fastest dimension (mainly
		 * 											I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values in the middle dimension (mainly
		 * 											J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values in the slowest dimension (mainly
		 * 											K dimension).
		 * @param 		  	minimumValue		  	The minimum value of the values in the HDF5 dataset.
		 * @param 		  	maximumValue		  	The maximum value of the values in the HDF5 dataset.
		 * @param 		  	nullValue			  	(Optional) The null value. Default value is long 64
		 * 											bits maximum value.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @p nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array3dOfValues(
			ULONG64 valueCountInFastestDim,
			ULONG64 valueCountInMiddleDim,
			ULONG64 valueCountInSlowestDim,
			LONG64 minimumValue, LONG64 maximumValue,
			LONG64 nullValue = (std::numeric_limits<LONG64>::max)(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Adds a 3d array of explicit long 64 bits values into the property values. Since this methods
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
		 * @param 		  	computeMinMax		  	True if FESAPI needs to compute the min and  max from
		 * 											the given @p values in order to set them.
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
		DLL_IMPORT_OR_EXPORT void setValuesOfLongHdf5Array3dOfValues(
			LONG64* values,
			ULONG64 valueCountInFastestDim,
			ULONG64 valueCountInMiddleDim,
			ULONG64 valueCountInSlowestDim,
			ULONG64 offsetInFastestDim,
			ULONG64 offsetInMiddleDim,
			ULONG64 offsetInSlowestDim,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned int patchIndex = (std::numeric_limits<unsigned int>::max)());
		using AbstractDiscreteOrCategoricalProperty::setValuesOfLongHdf5Array3dOfValues;

		/**
		 * Adds an nd array of explicit long 64 bits values into to the property values. Since this
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
		 * @param 		  	computeMinMax	  	True to compute and to set minimum and maximum values.
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
		DLL_IMPORT_OR_EXPORT void setValuesOfLongHdf5ArrayOfValues(
			LONG64* values,
			unsigned long long const * numValues,
			unsigned long long const * offsetValues,
			unsigned int numArrayDimensions,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned int patchIndex = (std::numeric_limits<unsigned int>::max)());

		/**
		 * @brief	Gets the null value in this discrete property.
		 *
		 * @param 	patchIndex	(Optional) Zero-based index of the patch for which we want to get the null value.
		 *
		 * @returns	The null value of this discrete property if present otherwise the maximum int 64 bits
		 * 			value.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getNullValue(unsigned int patchIndex = (std::numeric_limits<unsigned int>::max)()) const = 0;

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
		DLL_IMPORT_OR_EXPORT virtual bool hasMinimumValue(unsigned int index = 0) const = 0;

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
		DLL_IMPORT_OR_EXPORT virtual LONG64 getMinimumValue(unsigned int index = 0) const = 0;

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
		DLL_IMPORT_OR_EXPORT virtual bool hasMaximumValue(unsigned int index = 0) const = 0;

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
		DLL_IMPORT_OR_EXPORT virtual LONG64 getMaximumValue(unsigned int index = 0) const = 0;

		/**
		 * @brief	Sets the minimum value of a non vector property or the minimum value of one given
		 * 			value of a vector property.
		 *
		 * @param 	value	The minimum value to set.
		 * @param 	index	(Optional)  @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we want to set the
		 * 					minimum value (vector property case).
		 */
		DLL_IMPORT_OR_EXPORT virtual void setMinimumValue(LONG64 value, unsigned int index = 0) const = 0;

		/**
		 * @brief	Sets the maximum value of a non vector property or the maximum value of one given
		 * 			value of a vector property.
		 *
		 * @param 	value	The maximum value to set.
		 * @param 	index	(Optional)  @c 0 (default value, corresponding to the non vector property
		 * 					case) or zero-based index of the vector value for which we want to set the
		 * 					maximum value (vector property case).
		 */
		DLL_IMPORT_OR_EXPORT virtual void setMaximumValue(LONG64 value, unsigned int index = 0) const = 0;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		DiscreteProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractDiscreteOrCategoricalProperty(partialObject) {}

		/** Default constructor */
		DiscreteProperty() {}

		/**
		* Creates an instance of this class by wrapping a gSOAP instance.
		*
		* @param [in]	fromGsoap	If non-null, the gSOAP instance.
		*/
		DiscreteProperty(gsoap_resqml2_0_1::_resqml20__DiscreteProperty* fromGsoap) : AbstractDiscreteOrCategoricalProperty(fromGsoap) {}

		/**
		* Creates an instance of this class by wrapping a gSOAP instance.
		*
		* @param [in]	fromGsoap	If non-null, the gSOAP instance.
		*/
		DiscreteProperty(gsoap_eml2_3::_resqml22__DiscreteProperty* fromGsoap) : AbstractDiscreteOrCategoricalProperty(fromGsoap) {}

		virtual size_t getMinimumValueSize() const = 0;
		virtual size_t getMaximumValueSize() const = 0;
	};
}
