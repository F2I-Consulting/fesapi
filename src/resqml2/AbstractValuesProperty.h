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

namespace RESQML2_NS
{
	class AbstractValuesProperty : public AbstractProperty
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT AbstractValuesProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractProperty(partialObject) {}

		/**
		* Default constructor
		* Set the relationship with an AbstractRepresentation and a local property type.
		*/
		AbstractValuesProperty() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractValuesProperty(gsoap_resqml2_0_1::resqml20__AbstractValuesProperty* fromGsoap) : RESQML2_NS::AbstractProperty(fromGsoap) {}

		/**
		* Get the dataset which contains the property values of a particular patch.
		* @param patchIndex	The corresponding patch index of the dataset to get.
		* @param nullValue	If possible, this function will set this parameter to the Resqml null value of the dataset. If not, it will return long.min
		*/
		gsoap_resqml2_0_1::eml20__Hdf5Dataset const * getDatasetOfPatch(unsigned int patchIndex, LONG64 & nullValue) const;

		/**
		* Push back a new patch of integer values for this property where the values have not to be written in the HDF file.
		* The reason can be that the values already exist in an external file (only HDF5 for now) or that the writing of the values in the external file is defered in time.
		* @param	hdfProxy			The HDF5 proxy where the values are already or will be stored.
		* @param	datasetName			If not provided during the method call, the dataset will be named the same as the dataset naming convention of the fesapi :"/RESQML/" + prop->uuid + "/values_patch" + patchIndex;
		* @param	nullValue			Only relevant for integer hdf5 datasets. Indeed, Resqml (and fesapi) forces null value for floating point ot be NaN value.
		* @return	The name of the hdf5 dataset.
		*/
		std::string pushBackRefToExistingIntegerDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName = "", LONG64 nullValue = (std::numeric_limits<LONG64>::max)());

		void loadTargetRelationships();

	public:

		enum hdfDatatypeEnum { UNKNOWN = 0, DOUBLE = 1, FLOAT = 2, LONG_64 = 3, ULONG_64 = 4, INT = 5, UINT = 6, SHORT = 7, USHORT = 8, CHAR = 9, UCHAR = 10};

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractValuesProperty() {}

		/**
		* Get the number of patches in this values property. It should be the same count as the patch count of the associated representation.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const;

		/**
		* Get the values datatype in the HDF dataset
		*/
		DLL_IMPORT_OR_EXPORT AbstractValuesProperty::hdfDatatypeEnum getValuesHdfDatatype() const;

		/**
		* Push back a new patch of values for this property where the values have not to be written in the HDF file.
		* The reason can be that the values already exist in an external file (only HDF5 for now) or that the writing of the values in the external file is defered in time.
		* @param	hdfProxy			The HDF5 proxy where the values are already or will be stored.
		* @param	datasetName			If not provided during the method call, the dataset will be named the same as the dataset naming convention of the fesapi :"/RESQML/" + prop->uuid + "/values_patch" + patchIndex;
		* @param	nullValue			Only relevant for integer hdf5 datasets. Indeed, Resqml (and fesapi) forces null value for floating point to be NaN value.
		* @return	The name of the hdf5 dataset.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName = "", LONG64 nullValue = (std::numeric_limits<LONG64>::max)()) = 0;

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

		/**
		* Get the count of all values contained into the underlying HDF5 dataset of this property for a particular patch.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getValuesCountOfPatch (unsigned int patchIndex) const;

		/**
		* Get the count of values on a specific dimension of the underlying HDF5 dataset of this property.
		* @param dimIndex	The index of the dimension we want to know the values count in this property.
		* @param patchIndex	The index of the patch we want to know the values count in this property.
		* @return			The number of values, 0 otherwise.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getValuesCountOfDimensionOfPatch(unsigned int dimIndex, unsigned int patchIndex) const;

		/**
		* Get the count of dimension of the underlying HDF5 dataset of this property.
		* @param patchIndex	The index of the patch we want to know the dimensions in this property.
		* @return			The number of values, 0 otherwise.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getDimensionsCountOfPatch(unsigned int patchIndex) const;

		/**
		* Pushes back a new facet to this intance
		*/
		DLL_IMPORT_OR_EXPORT void pushBackFacet(const gsoap_resqml2_0_1::resqml20__Facet & facet, const std::string & facetValue);

		/**
		* Get the count of facet of this instance
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getFacetCount() const;

		/**
		* Get the facet at a particular index of the facet collection of this instance
		*/
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__Facet getFacet(unsigned int index) const;

		/**
		* Get the facet value at a particular index of the facet collection of this instance.
		*/
		DLL_IMPORT_OR_EXPORT std::string getFacetValue(unsigned int index) const;

		//***************************
		//*** For hyperslabbing *****
		//***************************

		/**
		* Create an array (potentially multi dimensions) of explicit long values to the property values. No values are written to this array yet.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		DLL_IMPORT_OR_EXPORT void createLongHdf5ArrayOfValues(
			unsigned long long* numValues, 
			unsigned int numArrayDimensions, 
			COMMON_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		* Create a 3d array of explicit Long values to the property values.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		DLL_IMPORT_OR_EXPORT void createLongHdf5Array3dOfValues(
			unsigned int valueCountInFastestDim, 
			unsigned int valueCountInMiddleDim, 
			unsigned int valueCountInSlowestDim, 
			COMMON_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		* Add a 3d array of explicit Long values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param offsetInFastestDim		The offset to write in the fastest dimension (mainly I dimension).
		* @param offsetInMiddleDim		The offset value to write in the middle dimension (mainly J dimension).
		* @param offsetInSlowestDim		The offset value to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
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
		* Add an array (potentially multi dimensions) of explicit long values to the property values.
		* This method is to be used along with createLongHdf5ArrayOfValues.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param offsetValues			The offset values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5SlabArrayOfValues(
			LONG64* values,
			unsigned long long const * numValues,
			unsigned long long const * offsetValues,
			unsigned int numArrayDimensions, 
			COMMON_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		* Get all the values of the instance which are supposed to be long ones.
		* @param patchIndex	Patch index.
		* @param values					The array (pointer) of values which must be preallocated.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param offsetValues			The offset values ordered by dimension of the array to write.
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
		* Get all the values of the instance which are supposed to be long ones.
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
			unsigned int valueCountInFastestDim, 
			unsigned int valueCountInMiddleDim, 
			unsigned int valueCountInSlowestDim, 
			unsigned int offsetInFastestDim, 
			unsigned int offsetInMiddleDim, 
			unsigned int offsetInSlowestDim
		) const;
	};
}
