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

#include "../resqml2/AbstractValuesProperty.h"

namespace RESQML2_NS
{
	class AbstractDiscreteOrCategoricalProperty : public RESQML2_NS::AbstractValuesProperty
	{
	protected:

		AbstractDiscreteOrCategoricalProperty() {}

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT AbstractDiscreteOrCategoricalProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractValuesProperty(partialObject) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractDiscreteOrCategoricalProperty(gsoap_resqml2_0_1::_resqml20__DiscreteProperty* fromGsoap): AbstractValuesProperty(fromGsoap) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractDiscreteOrCategoricalProperty(gsoap_resqml2_0_1::_resqml20__CategoricalProperty* fromGsoap) : AbstractValuesProperty(fromGsoap) {}

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractDiscreteOrCategoricalProperty() {}

		/**
		* Add a 1d array of explicit long values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCount				The number of values to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If not provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If not provided then the maximum value will be computed from the values.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array1dOfValues(const LONG64 * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy* proxy, LONG64 nullValue);
		DLL_IMPORT_OR_EXPORT void pushBackIntHdf5Array1dOfValues(const int * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy* proxy, int nullValue);
		DLL_IMPORT_OR_EXPORT void pushBackShortHdf5Array1dOfValues(const short * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy* proxy, short nullValue);
		DLL_IMPORT_OR_EXPORT void pushBackCharHdf5Array1dOfValues(const char * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy* proxy, char nullValue);

		/**
		* Add a 2d array of explicit long values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly J dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If not provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If not provided then the maximum value will be computed from the values.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array2dOfValues(const LONG64 * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, LONG64 nullValue);
		DLL_IMPORT_OR_EXPORT void pushBackIntHdf5Array2dOfValues(const int * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, int nullValue);
		DLL_IMPORT_OR_EXPORT void pushBackShortHdf5Array2dOfValues(const short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, short nullValue);
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5Array2dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, unsigned short nullValue);
		DLL_IMPORT_OR_EXPORT void pushBackCharHdf5Array2dOfValues(const char * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, char nullValue);

		/**
		* Add a 3d array of explicit long values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If not provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If not provided then the maximum value will be computed from the values.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array3dOfValues(const LONG64 * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, LONG64 nullValue);
		DLL_IMPORT_OR_EXPORT void pushBackIntHdf5Array3dOfValues(const int * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, int nullValue);
		DLL_IMPORT_OR_EXPORT void pushBackShortHdf5Array3dOfValues(const short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, short nullValue);
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5Array3dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, unsigned short nullValue);
		DLL_IMPORT_OR_EXPORT void pushBackCharHdf5Array3dOfValues(const char * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, char nullValue);

		/**
		* Add an array (potentially multi dimensions) of explicit values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param numDimensionsInArray	The number of dimensions in the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If not provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If not provided then the maximum value will be computed from the values.
		*/
		DLL_IMPORT_OR_EXPORT virtual void pushBackLongHdf5ArrayOfValues(const LONG64 * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, LONG64 nullValue);
		DLL_IMPORT_OR_EXPORT virtual void pushBackIntHdf5ArrayOfValues(const int * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, int nullValue);
		DLL_IMPORT_OR_EXPORT virtual void pushBackShortHdf5ArrayOfValues(const short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, short nullValue);
		DLL_IMPORT_OR_EXPORT virtual void pushBackUShortHdf5ArrayOfValues(const unsigned short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, unsigned short nullValue);
		DLL_IMPORT_OR_EXPORT virtual void pushBackCharHdf5ArrayOfValues(const char * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, char nullValue);

		/**
		* Push back a new patch of integer values for this property where the values have not to be written in the HDF file.
		* The reason can be that the values already exist in an external file (only HDF5 for now) or that the writing of the values in the external file is defered in time.
		* @param	hdfProxy			The HDF5 proxy where the values are already or will be stored.
		* @param	datasetName			If not provided during the method call, the dataset will be named the same as the dataset naming convention of the fesapi :getHdfGroup() + "/values_patch" + patchIndex;
		* @param	nullValue			Only relevant for integer hdf5 datasets. Indeed, Resqml (and fesapi) forces null value for floating point ot be NaN value.
		* @return	The name of the hdf5 dataset.
		*/
		DLL_IMPORT_OR_EXPORT std::string pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & dataset = "", LONG64 nullValue = (std::numeric_limits<LONG64>::max)());

		/**
		* Get all the values of the instance which are supposed to be long ones.
		* Not for continuous property values.
		* @return the null value
		*/
		DLL_IMPORT_OR_EXPORT LONG64 getLongValuesOfPatch(unsigned int patchIndex, LONG64 * values) const;

		/**
		* Get the null value of the instance which are supposed to be integer ones.
		* Not for continuous property values.
		* @return the null value
		*/
		DLL_IMPORT_OR_EXPORT LONG64 getNullValueOfPatch(unsigned int patchIndex) const;

		/**
		* Get all the values of the instance which are supposed to be unsigned long ones.
		* Not for continuous property values.
		* @return the null value
		*/
		DLL_IMPORT_OR_EXPORT ULONG64 getULongValuesOfPatch(unsigned int patchIndex, ULONG64 * values) const;

		/**
		* Get all the values of the instance which are supposed to be int ones.
		* Not for continuous property values.
		* @return the null value
		*/
		DLL_IMPORT_OR_EXPORT int getIntValuesOfPatch(unsigned int patchIndex, int * values) const;

		/**
		* Get all the values of the instance which are supposed to be unsigned int ones.
		* Not for continuous property values.
		* @return the null value
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getUIntValuesOfPatch(unsigned int patchIndex, unsigned int * values) const;

		/**
		* Get all the values of the instance which are supposed to be short ones.
		* Not for continuous property values.
		* @return the null value
		*/
		DLL_IMPORT_OR_EXPORT short getShortValuesOfPatch(unsigned int patchIndex, short * values) const;

		/**
		* Get all the values of the instance which are supposed to be unsigned short ones.
		* Not for continuous property values.
		* @return the null value
		*/
		DLL_IMPORT_OR_EXPORT unsigned short getUShortValuesOfPatch(unsigned int patchIndex, unsigned short * values) const;

		/**
		* Get all the values of the instance which are supposed to be char ones.
		* Not for continuous property values.
		* @return the null value
		*/
		DLL_IMPORT_OR_EXPORT char getCharValuesOfPatch(unsigned int patchIndex, char * values) const;

		/**
		* Get all the values of the instance which are supposed to be unsigned char ones.
		* Not for continuous property values.
		* @return the null value
		*/
		DLL_IMPORT_OR_EXPORT unsigned char getUCharValuesOfPatch(unsigned int patchIndex, unsigned char * values) const;
		
		//***************************
		//*** For hyperslabbing *****
		//***************************

		/**
		* Create an array (potentially multi dimensions) of explicit long 64 bits values to the property values. No values are written to this array yet.
		* @param numValues				The number of property values ordered by dimension of the array to write. Ordered from slowest dimension to fastest dimension.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5ArrayOfValues(
			unsigned long long* numValues,
			unsigned int numArrayDimensions,
			LONG64 nullValue = (std::numeric_limits<LONG64>::max)(),
			COMMON_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		* Create a 3d array of explicit Long 64 bits values to the property values.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array3dOfValues(
			ULONG64 valueCountInFastestDim,
			ULONG64 valueCountInMiddleDim,
			ULONG64 valueCountInSlowestDim,
			LONG64 nullValue = (std::numeric_limits<LONG64>::max)(),
			COMMON_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		* Add a 3d array of explicit Long 64 bits values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param offsetInFastestDim		The offset to write in the fastest dimension (mainly I dimension).
		* @param offsetInMiddleDim		The offset value to write in the middle dimension (mainly J dimension).
		* @param offsetInSlowestDim		The offset value to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		DLL_IMPORT_OR_EXPORT void setValuesOfLongHdf5Array3dOfValues(
			LONG64* values,
			ULONG64 valueCountInFastestDim,
			ULONG64 valueCountInMiddleDim,
			ULONG64 valueCountInSlowestDim,
			ULONG64 offsetInFastestDim,
			ULONG64 offsetInMiddleDim,
			ULONG64 offsetInSlowestDim,
			COMMON_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned int patchIndex = (std::numeric_limits<unsigned int>::max)());

		/**
		* Add an array (potentially multi dimensions) of explicit long 64 bits values to the property values.
		* This method is to be used along with createLongHdf5ArrayOfValues.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write. Ordered from slowest dimension to fastest dimension.
		* @param offsetValues			The offset values ordered by dimension of the array to write. Ordered from slowest dimension to fastest dimension.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		DLL_IMPORT_OR_EXPORT void setValuesOfLongHdf5ArrayOfValues(
			LONG64* values,
			unsigned long long const * numValues,
			unsigned long long const * offsetValues,
			unsigned int numArrayDimensions,
			COMMON_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned int patchIndex = (std::numeric_limits<unsigned int>::max)());

		/**
		* Get a subselection of the values as long 64 bits ones.
		* @param patchIndex	Patch index.
		* @param values					The array (pointer) of values which must be preallocated.
		* @param numValues				The number of property values ordered by dimension of the array to write. Ordered from slowest dimension to fastest dimension.
		* @param offsetValues			The offset values ordered by dimension of the array to write. Ordered from slowest dimension to fastest dimension.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		*/
		DLL_IMPORT_OR_EXPORT void getLongValuesOfPatch(
			unsigned int patchIndex,
			LONG64* values,
			unsigned long long const * numValuesInEachDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned int numArrayDimensions
		) const;

		/**
		* Get all the values of the instance as long 64 bits ones.
		* @param patchIndex				Patch index.
		* @param values					The array (pointer) of values must be preallocated.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param offsetInFastestDim		The offset to write in the fastest dimension (mainly I dimension).
		* @param offsetInMiddleDim		The offset value to write in the middle dimension (mainly J dimension).
		* @param offsetInSlowestDim		The offset value to write in the slowest dimension (mainly K dimension).
		*/
		DLL_IMPORT_OR_EXPORT void getLongValuesOf3dPatch(
			unsigned int patchIndex,
			LONG64* values,
			ULONG64 valueCountInFastestDim,
			ULONG64 valueCountInMiddleDim,
			ULONG64 valueCountInSlowestDim,
			ULONG64 offsetInFastestDim,
			ULONG64 offsetInMiddleDim,
			ULONG64 offsetInSlowestDim
		) const;

		/**
		* Get some of the values of a particular patch of the instance which are supposed to be int ones. This method makes use of HDF5 hyperslabbing.
		* @param patchIndex					The index of the patch we want the values from.
		* @param values						The array (pointer) of values must be preallocated.
		* @param numValuesInEachDimension	The number of property values ordered by dimension of the array to write.
		* @param offsetInEachDimension		The offset values ordered by dimension of the array to write.
		* @param numArrayDimensions			The number of dimensions of the HDF5 array to read.
		* @return the null value
		*/
		DLL_IMPORT_OR_EXPORT int getIntValuesOfPatch(
			unsigned int patchIndex,
			int* values,
			unsigned long long* numValuesInEachDimension,
			unsigned long long* offsetInEachDimension,
			unsigned int numArrayDimensions
		) const;

		/**
		* Get all the values of the instance which are supposed to be int ones.
		* @param patchIndex				Patch index.
		* @param values					The array (pointer) of values must be preallocated.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param offsetInFastestDim		The offset to write in the fastest dimension (mainly I dimension).
		* @param offsetInMiddleDim		The offset value to write in the middle dimension (mainly J dimension).
		* @param offsetInSlowestDim		The offset value to write in the slowest dimension (mainly K dimension).
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
	};
}
