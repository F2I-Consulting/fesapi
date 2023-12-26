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
		 * @brief Adds a 1d array of explicit int 64 bits values to the property values.
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
		DLL_IMPORT_OR_EXPORT void pushBackInt64Hdf5Array1dOfValues(const int64_t * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue, int64_t minimumValue, int64_t maximumValue) {
			pushBackInt64Hdf5ArrayOfValues(values, &valueCount, 1, proxy, nullValue, minimumValue, maximumValue);
		}
		using AbstractValuesProperty::pushBackInt64Hdf5Array1dOfValues;
		
		/**
		 * Adds a 1d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array1dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInt32Hdf5Array1dOfValues(const int * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, int nullValue, int minimumValue, int maximumValue) {
			pushBackInt32Hdf5ArrayOfValues(values, &valueCount, 1, proxy, nullValue, minimumValue, maximumValue);
		}
		using AbstractValuesProperty::pushBackInt32Hdf5Array1dOfValues;
		
		/**
		 * Adds a 1d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array1dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInt16Hdf5Array1dOfValues(const short * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, short nullValue, short minimumValue, short maximumValue) {
			pushBackInt16Hdf5ArrayOfValues(values, &valueCount, 1, proxy, nullValue, minimumValue, maximumValue);
		}
		using AbstractValuesProperty::pushBackInt16Hdf5Array1dOfValues;
		
		/**
		 * Adds a 1d array of explicit int8_t values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array1dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInt8Hdf5Array1dOfValues(const int8_t * values, uint64_t valueCount, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue, int8_t minimumValue, int8_t maximumValue) {
			pushBackInt8Hdf5ArrayOfValues(values, &valueCount, 1, proxy, nullValue, minimumValue, maximumValue);
		}
		using AbstractValuesProperty::pushBackInt8Hdf5Array1dOfValues;

		/**
		 * @brief Adds a 2d array of explicit int 64 bits values to the property values.
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
		DLL_IMPORT_OR_EXPORT void pushBackInt64Hdf5Array2dOfValues(const int64_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy,
			int64_t nullValue, int64_t minimumValue, int64_t maximumValue);
		using AbstractValuesProperty::pushBackInt64Hdf5Array2dOfValues;
		
		/**
		 * Adds a 2d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array2dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInt32Hdf5Array2dOfValues(const int * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy,
			int nullValue, int minimumValue, int maximumValue);
		using AbstractValuesProperty::pushBackInt32Hdf5Array2dOfValues;
		
		/**
		 * Adds a 2d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array2dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInt16Hdf5Array2dOfValues(const short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy,
			short nullValue, short minimumValue, short maximumValue);
		using AbstractValuesProperty::pushBackInt16Hdf5Array2dOfValues;
		
		/**
		 * Adds a 2d array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array2dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackUInt16Hdf5Array2dOfValues(const unsigned short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy,
			unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue);
		using AbstractValuesProperty::pushBackUInt16Hdf5Array2dOfValues;
		
		/**
		 * Adds a 2d array of explicit int8_t values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array2dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInt8Hdf5Array2dOfValues(const int8_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy,
			int8_t nullValue, int8_t minimumValue, int8_t maximumValue);
		using AbstractValuesProperty::pushBackInt8Hdf5Array2dOfValues;

		/**
		 * @brief Adds a 3d array of explicit int 64 bits values to the property values.
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
		DLL_IMPORT_OR_EXPORT void pushBackInt64Hdf5Array3dOfValues(const int64_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy,
			int64_t nullValue, int64_t minimumValue, int64_t maximumValue);
		using AbstractValuesProperty::pushBackInt64Hdf5Array3dOfValues;
		
		/**
		 * Adds a 3d array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array3dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInt32Hdf5Array3dOfValues(const int * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy,
			int nullValue, int minimumValue, int maximumValue);
		using AbstractValuesProperty::pushBackInt32Hdf5Array3dOfValues;
		
		/**
		 * Adds a 3d array of explicit short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array3dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInt16Hdf5Array3dOfValues(const short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy,
			short nullValue, short minimumValue, short maximumValue);
		using AbstractValuesProperty::pushBackInt16Hdf5Array3dOfValues;
		
		/**
		 * Adds a 3d array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array3dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackUInt16Hdf5Array3dOfValues(const unsigned short * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy,
			unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue);
		using AbstractValuesProperty::pushBackUInt16Hdf5Array3dOfValues;
		
		/**
		 * Adds a 3d array of explicit int8_t values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5Array3dOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInt8Hdf5Array3dOfValues(const int8_t * values, uint64_t valueCountInFastestDim, uint64_t valueCountInMiddleDim, uint64_t valueCountInSlowestDim, EML2_NS::AbstractHdfProxy* proxy,
			int8_t nullValue, int8_t minimumValue, int8_t maximumValue);
		using AbstractValuesProperty::pushBackInt8Hdf5Array3dOfValues;

		/**
		 * @brief Adds an nd array of explicit int 64 bits values to the property values.
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
		DLL_IMPORT_OR_EXPORT void pushBackInt64Hdf5ArrayOfValues(const int64_t * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int64_t nullValue) final;
		
		/**
		 * Adds an nd array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInt32Hdf5ArrayOfValues(const int * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int nullValue) final;
		
		/**
		 * Adds an nd array of explicit short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInt16Hdf5ArrayOfValues(const short * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, short nullValue) final;
		
		/**
		 * Adds an nd array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackUInt16Hdf5ArrayOfValues(const unsigned short * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, unsigned short nullValue) final;
		
		/**
		 * Adds an nd array of explicit int8_t values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInt8Hdf5ArrayOfValues(const int8_t * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy, int8_t nullValue) final;

		/**
		 * @brief Adds an nd array of explicit int 64 bits values to the property values.
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
		DLL_IMPORT_OR_EXPORT void pushBackInt64Hdf5ArrayOfValues(const int64_t * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy,
			int64_t nullValue, int64_t minimumValue, int64_t maximumValue);
		
		/**
		 * Adds an nd array of explicit integer values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues(const int64_t *,uint64_t *,unsigned int,eml2::AbstractHdfProxy*,int64_t,int64_t,int64_t)
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInt32Hdf5ArrayOfValues(const int * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy,
			int nullValue, int minimumValue, int maximumValue);
		
		/**
		 * Adds an nd array of explicit short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues(const int64_t *,uint64_t *,unsigned int,eml2::AbstractHdfProxy*,int64_t,int64_t,int64_t)
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInt16Hdf5ArrayOfValues(const short * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy,
			short nullValue, short minimumValue, short maximumValue);
		
		/**
		 * Adds an nd array of explicit unsigned short values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues(const int64_t *,uint64_t *,unsigned int,eml2::AbstractHdfProxy*,int64_t,int64_t,int64_t)
		 */
		DLL_IMPORT_OR_EXPORT void pushBackUInt16Hdf5ArrayOfValues(const unsigned short * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy,
			unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue);
		
		/**
		 * Adds an nd array of explicit int8_t values to the property values.
		 *
		 * @copydetails pushBackInt64Hdf5ArrayOfValues(const int64_t *,uint64_t *,unsigned int,eml2::AbstractHdfProxy*,int64_t,int64_t,int64_t)
		 */
		DLL_IMPORT_OR_EXPORT void pushBackInt8Hdf5ArrayOfValues(const int8_t * values, const uint64_t * numValues, unsigned int numDimensionsInArray, EML2_NS::AbstractHdfProxy* proxy,
			int8_t nullValue, int8_t minimumValue, int8_t maximumValue);

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
		DLL_IMPORT_OR_EXPORT virtual std::string pushBackRefToExistingIntegerDataset(EML2_NS::AbstractHdfProxy* proxy, const std::string & datasetName, int64_t nullValue, int64_t minimumValue, int64_t maximumValue) = 0;
		using AbstractValuesProperty::pushBackRefToExistingIntegerDataset;

		//***************************
		//*** For hyperslabbing *****
		//***************************

		/**
		 * Creates an nd array of explicit int 64 bits values into the property values. No values are
		 * written to this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 			datatype			The datatype of the values 
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
		 * @param 		  	nullValue		  	(Optional) The null value. Default value is int 64 bits
		 * 										maximum value.
		 * @param [in,out]	proxy			  	(Optional) The HDF proxy where to write the property
		 * 										values. It must be already opened for writing and won't
		 * 										be closed in this method. If @c nullptr (default), a
		 * 										default HDF proxy must be defined into the data object
		 * 										repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackHdf5ArrayOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			const uint64_t* numValues,
			unsigned int numArrayDimensions,
			int64_t* minimumValue, int64_t* maximumValue,
			int64_t nullValue = (std::numeric_limits<int64_t>::max)(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr);
		using AbstractValuesProperty::pushBackHdf5ArrayOfValues;

		/**
		 * Creates a 1d array of values into the property values. No values are written
		 * to this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 			datatype			The datatype of the values 
		 * @param 		  	valueCount			The count of values.
		 * @param 		  	minimumValue		  	The minimum value of the values in the HDF5 dataset.
		 * @param 		  	maximumValue		  	The maximum value of the values in the HDF5 dataset.
		 * @param 		  	nullValue			  	(Optional) The null value. Default value is int 64
		 * 											bits maximum value.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @p nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackHdf5Array1dOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			uint64_t valueCount,
			int64_t minimumValue, int64_t maximumValue,
			int64_t nullValue = (std::numeric_limits<int64_t>::max)(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr);
		using AbstractValuesProperty::pushBackHdf5Array1dOfValues;

		/**
		 * Creates a 2d array of explicit int 64 values into the property values. No values are written
		 * to this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 			datatype			The datatype of the values 
		 * @param 		  	valueCountInFastestDim	The number of values in the fastest dimension (mainly
		 * 											I dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values in the slowest dimension (mainly
		 * 											K dimension).
		 * @param 		  	minimumValue		  	The minimum value of the values in the HDF5 dataset.
		 * @param 		  	maximumValue		  	The maximum value of the values in the HDF5 dataset.
		 * @param 		  	nullValue			  	(Optional) The null value. Default value is int 64
		 * 											bits maximum value.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @p nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackHdf5Array2dOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInSlowestDim,
			int64_t minimumValue, int64_t maximumValue,
			int64_t nullValue = (std::numeric_limits<int64_t>::max)(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr);
		using AbstractValuesProperty::pushBackHdf5Array2dOfValues;

		/**
		 * Creates a 3d array of explicit int 64 values into the property values. No values are written
		 * to this array yet then the HDF5 array contains uninitialized values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined into the data object repository.
		 *
		 * @param 			datatype			The datatype of the values 
		 * @param 		  	valueCountInFastestDim	The number of values in the fastest dimension (mainly
		 * 											I dimension).
		 * @param 		  	valueCountInMiddleDim 	The number of values in the middle dimension (mainly
		 * 											J dimension).
		 * @param 		  	valueCountInSlowestDim	The number of values in the slowest dimension (mainly
		 * 											K dimension).
		 * @param 		  	minimumValue		  	The minimum value of the values in the HDF5 dataset.
		 * @param 		  	maximumValue		  	The maximum value of the values in the HDF5 dataset.
		 * @param 		  	nullValue			  	(Optional) The null value. Default value is int 64
		 * 											bits maximum value.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy where to write the property
		 * 											values. It must be already opened for writing and
		 * 											won't be closed in this method. If @p nullptr
		 * 											(default), a default HDF proxy must be defined into
		 * 											the data object repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackHdf5Array3dOfValues(
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			int64_t minimumValue, int64_t maximumValue,
			int64_t nullValue = (std::numeric_limits<int64_t>::max)(),
			EML2_NS::AbstractHdfProxy* proxy = nullptr);
		using AbstractValuesProperty::pushBackHdf5Array3dOfValues;

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
		DLL_IMPORT_OR_EXPORT void setValuesOfInt64Hdf5Array3dOfValues(
			int64_t* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)());
		using AbstractValuesProperty::setValuesOfInt64Hdf5Array3dOfValues;
		DLL_IMPORT_OR_EXPORT void setValuesOfInt32Hdf5Array3dOfValues(
			int32_t* values,
			uint64_t valueCountInFastestDim,
			uint64_t valueCountInMiddleDim,
			uint64_t valueCountInSlowestDim,
			uint64_t offsetInFastestDim,
			uint64_t offsetInMiddleDim,
			uint64_t offsetInSlowestDim,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)());
		using AbstractValuesProperty::setValuesOfInt32Hdf5Array3dOfValues;

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
		DLL_IMPORT_OR_EXPORT void setValuesOfInt64Hdf5ArrayOfValues(
			int64_t* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)());
		using AbstractValuesProperty::setValuesOfInt64Hdf5ArrayOfValues;
		DLL_IMPORT_OR_EXPORT void setValuesOfInt32Hdf5ArrayOfValues(
			int32_t* values,
			uint64_t const * numValues,
			uint64_t const * offsetValues,
			unsigned int numArrayDimensions,
			bool computeMinMax,
			EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)());
		using AbstractValuesProperty::setValuesOfInt32Hdf5ArrayOfValues;

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

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "DiscreteProperty";

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		DiscreteProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractValuesProperty(partialObject) {}

		/** Default constructor */
		DiscreteProperty() {}

		/**
		* Creates an instance of this class by wrapping a gSOAP instance.
		*
		* @param [in]	fromGsoap	If non-null, the gSOAP instance.
		*/
		DiscreteProperty(gsoap_resqml2_0_1::_resqml20__DiscreteProperty* fromGsoap) : AbstractValuesProperty(fromGsoap) {}

		/**
		* Creates an instance of this class by wrapping a gSOAP instance.
		*
		* @param [in]	fromGsoap	If non-null, the gSOAP instance.
		*/
		DiscreteProperty(gsoap_eml2_3::_resqml22__DiscreteProperty* fromGsoap) : AbstractValuesProperty(fromGsoap) {}

		virtual size_t getMinimumValueSize() const = 0;
		virtual size_t getMaximumValueSize() const = 0;
	};
}
