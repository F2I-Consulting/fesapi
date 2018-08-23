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
#include "resqml2/AbstractProperty.h"

namespace RESQML2_NS
{
	class DLL_IMPORT_OR_EXPORT AbstractValuesProperty : public AbstractProperty
	{
	protected:
		/**
		* Get the path in the hdf file of the dataset which contains the property values of a particular patch.
		* @param patchIndex	The corresponding patch index of the dataset to get.
		* @param  nullValue	If possible, this function will set this parameter to the Resqml null value of the dataset. If not, it will return long.min
		*/
		std::string getPathInHdfFileOfPatch(const unsigned int & patchIndex, LONG64 & nullValue) const;

		/**
		* Push back a new patch of integer values for this property where the values have not to be written in the HDF file.
		* The reason can be that the values already exist in an external file (only HDF5 for now) or that the writing of the values in the external file is defered in time.
		* @param	hdfProxy			The HDF5 proxy where the values are already or will be stored.
		* @param	datasetName			If not provided during the method call, the dataset will be named the same as the dataset naming convention of the fesapi :"/RESQML/" + prop->uuid + "/values_patch" + patchIndex;
		* @param	nullValue			Only relevant for integer hdf5 datasets. Indeed, Resqml (and fesapi) forces null value for floating point ot be NaN value.
		* @return	The name of the hdf5 dataset.
		*/
		std::string pushBackRefToExistingIntegerDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName = "", const long & nullValue = (std::numeric_limits<long>::max)());

	public:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractValuesProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractProperty(partialObject) {}

		/**
		* Default constructor
		* Set the relationship with an AbstractRepresentation and a local property type.
		*/
		AbstractValuesProperty() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractValuesProperty(gsoap_resqml2_0_1::resqml2__AbstractValuesProperty* fromGsoap) : RESQML2_NS::AbstractProperty(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractValuesProperty() {}

		/**
		* Get the number of patches in this values property. It should be the same count as the patch count of the associated representation.
		*/
		unsigned int getPatchCount() const;

		/**
		* Get the values datatype in the HDF dataset
		*/
		COMMON_NS::AbstractObject::hdfDatatypeEnum getValuesHdfDatatype() const;

		/**
		* Push back a new patch of values for this property where the values have not to be written in the HDF file.
		* The reason can be that the values already exist in an external file (only HDF5 for now) or that the writing of the values in the external file is defered in time.
		* @param	hdfProxy			The HDF5 proxy where the values are already or will be stored.
		* @param	datasetName			If not provided during the method call, the dataset will be named the same as the dataset naming convention of the fesapi :"/RESQML/" + prop->uuid + "/values_patch" + patchIndex;
		* @param	nullValue			Only relevant for integer hdf5 datasets. Indeed, Resqml (and fesapi) forces null value for floating point to be NaN value.
		* @return	The name of the hdf5 dataset.
		*/
		virtual std::string pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName = "", const long & nullValue = (std::numeric_limits<long>::max)()) = 0;

		/**
		* Get all the values of the instance which are supposed to be long ones.
		* Not for continuous property values.
		* @return the null value
		*/
		long getLongValuesOfPatch(const unsigned int & patchIndex, long * values);

		/**
		* Get the null value of the instance which are supposed to be integer ones.
		* Not for continuous property values.
		* @return the null value
		*/
		long getNullValueOfPatch(const unsigned int & patchIndex);

		/**
		* Get all the values of the instance which are supposed to be unsigned long ones.
		* Not for continuous property values.
		* @return the null value
		*/
		unsigned long getULongValuesOfPatch(const unsigned int & patchIndex, unsigned long * values);

		/**
		* Get all the values of the instance which are supposed to be int ones.
		* Not for continuous property values.
		* @return the null value
		*/
		int getIntValuesOfPatch(const unsigned int & patchIndex, int * values);

		/**
		* Get some of the values of a particular patch of the instance which are supposed to be int ones. This method makes use of HDF5 hyperslabbing.
		* @param patchIndex					The index of the patch we want the values from.
		* @param values						The array (pointer) of values must be preallocated.
		* @param numValuesInEachDimension	The number of property values ordered by dimension of the array to write.
		* @param offsetInEachDimension		The offset values ordered by dimension of the array to write.
		* @param numArrayDimensions			The number of dimensions of the HDF5 array to read.
		* @return the null value
		*/
		int getIntValuesOfPatch(
			const unsigned int& patchIndex,
			int* values,
			unsigned long long* numValuesInEachDimension,
			unsigned long long* offsetInEachDimension,
			const unsigned int& numArrayDimensions
		);

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
		void getIntValuesOf3dPatch(
			const unsigned int& patchIndex,
			int* values,
			const unsigned int& valueCountInFastestDim,
			const unsigned int& valueCountInMiddleDim,
			const unsigned int& valueCountInSlowestDim,
			const unsigned int& offsetInFastestDim,
			const unsigned int& offsetInMiddleDim,
			const unsigned int& offsetInSlowestDim
		);

		/**
		* Get all the values of the instance which are supposed to be unsigned int ones.
		* Not for continuous property values.
		* @return the null value
		*/
		unsigned int getUIntValuesOfPatch(const unsigned int & patchIndex, unsigned int * values);
		
		/**
		* Get all the values of the instance which are supposed to be short ones.
		* Not for continuous property values.
		* @return the null value
		*/
		short getShortValuesOfPatch(const unsigned int & patchIndex, short * values);

		/**
		* Get all the values of the instance which are supposed to be unsigned short ones.
		* Not for continuous property values.
		* @return the null value
		*/
		unsigned short getUShortValuesOfPatch(const unsigned int & patchIndex, unsigned short * values);

		/**
		* Get all the values of the instance which are supposed to be char ones.
		* Not for continuous property values.
		* @return the null value
		*/
		char getCharValuesOfPatch(const unsigned int & patchIndex, char * values);

		/**
		* Get all the values of the instance which are supposed to be unsigned char ones.
		* Not for continuous property values.
		* @return the null value
		*/
		unsigned char getUCharValuesOfPatch(const unsigned int & patchIndex, unsigned char * values);

		/**
		* Get the count of all values contained into the underlying HDF5 dataset of this property for a particular patch.
		*/
		unsigned int getValuesCountOfPatch (const unsigned int & patchIndex);

		/**
		* Get the count of values on a specific dimension of the underlying HDF5 dataset of this property.
		* @param dimIndex	The index of the dimension we want to know the values count in this property.
		* @param patchIndex	The index of the patch we want to know the values count in this property.
		* @return			The number of values, 0 otherwise.
		*/
		unsigned int getValuesCountOfDimensionOfPatch(const unsigned int & dimIndex, const unsigned int & patchIndex);

		/**
		* Get the count of dimension of the underlying HDF5 dataset of this property.
		* @param patchIndex	The index of the patch we want to know the dimensions in this property.
		* @return			The number of values, 0 otherwise.
		*/
		unsigned int getDimensionsCountOfPatch(const unsigned int & patchIndex);

		/**
		* Pushes back a new facet to this intance
		*/
		void pushBackFacet(const gsoap_resqml2_0_1::resqml2__Facet & facet, const std::string & facetValue);

		/**
		* Get the count of facet of this instance
		*/
		unsigned int getFacetCount() const;

		/**
		* Get the facet at a particular index of the facet collection of this instance
		*/
		gsoap_resqml2_0_1::resqml2__Facet getFacet(const unsigned int & index) const;

		/**
		* Get the facet value at a particular index of the facet collection of this instance.
		*/
		std::string getFacetValue(const unsigned int & index) const;

		//***************************
		//*** For hyperslabbing *****
		//***************************

		/**
		* Create an array (potentially multi dimensions) of explicit long values to the property values. No values are written to this array yet.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		void createLongHdf5ArrayOfValues(
			unsigned long long* numValues, 
			const unsigned int& numArrayDimensions, 
			COMMON_NS::AbstractHdfProxy* proxy
		);

		/**
		* Create a 3d array of explicit Long values to the property values.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		void createLongHdf5Array3dOfValues(
			const unsigned int& valueCountInFastestDim, 
			const unsigned int& valueCountInMiddleDim, 
			const unsigned int& valueCountInSlowestDim, 
			COMMON_NS::AbstractHdfProxy* proxy
		);

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
		void pushBackLongHdf5SlabArray3dOfValues(
			long* values, 
			const unsigned int& valueCountInFastestDim, 
			const unsigned int& valueCountInMiddleDim, 
			const unsigned int& valueCountInSlowestDim, 
			const unsigned int& offsetInFastestDim, 
			const unsigned int& offsetInMiddleDim, 
			const unsigned int& offsetInSlowestDim, 
			COMMON_NS::AbstractHdfProxy* proxy
		);

		/**
		* Add an array (potentially multi dimensions) of explicit long values to the property values.
		* This method is to be used along with createLongHdf5ArrayOfValues.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param offsetValues			The offset values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		void pushBackLongHdf5SlabArrayOfValues(
			long * values, 
			unsigned long long * numValues,
			unsigned long long * offsetValues,
			const unsigned int & numArrayDimensions, 
			COMMON_NS::AbstractHdfProxy* proxy
		);

		/**
		* Get all the values of the instance which are supposed to be long ones.
		* @param patchIndex	Patch index.
		* @param values					The array (pointer) of values which must be preallocated.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param offsetValues			The offset values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		*/
		void getLongValuesOfPatch(
			const unsigned int& patchIndex, 
			long* values, 
			unsigned long long* numValuesInEachDimension,
			unsigned long long* offsetInEachDimension,
			const unsigned int& numArrayDimensions
		);

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
		void getLongValuesOf3dPatch(
			const unsigned int& patchIndex, 
			long* values, 
			const unsigned int& valueCountInFastestDim, 
			const unsigned int& valueCountInMiddleDim, 
			const unsigned int& valueCountInSlowestDim, 
			const unsigned int& offsetInFastestDim, 
			const unsigned int& offsetInMiddleDim, 
			const unsigned int& offsetInSlowestDim
		);

	};
}

