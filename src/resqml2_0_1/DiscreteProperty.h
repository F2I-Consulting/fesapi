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

#include "../resqml2/AbstractDiscreteOrCategoricalProperty.h"

namespace RESQML2_0_1_NS
{
	/**
	* Contains discrete integer values; typically used to store any type of index.
	* So that the value range can be known before accessing all values, it also optionally stores the minimum and maximum value in the range.
	*/
	class DiscreteProperty : public RESQML2_NS::AbstractDiscreteOrCategoricalProperty
	{
	protected:

		DiscreteProperty() {}

	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT DiscreteProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractDiscreteOrCategoricalProperty(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param rep						The representation which supports these property values.
		* @param guid						The guid to set to the fault. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param dimension					The dimension of each value (scalar properties == 1).
		* @param attachmentKind				The topological orbit which support each value.
		* @param energisticsPropertyKind	The property kind of these property values which must be defined in the standard energistics property type dictionary.
		*/
		DiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param rep						The representation which supports these property values.
		* @param guid						The guid to set to the fault. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param dimension					The dimension of each value (scalar properties == 1).
		* @param attachmentKind				The topological orbit which support each value.
		* @param localPropType				The property kind of these property values which must be defined in the EPC document as a local property kind.
		*/
		DiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind, COMMON_NS::PropertyKind * localPropKind);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		DiscreteProperty(gsoap_resqml2_0_1::_resqml20__DiscreteProperty* fromGsoap): AbstractDiscreteOrCategoricalProperty(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~DiscreteProperty() {}

		/**
		* Add a 1d array of explicit long values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCount				The number of values to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If not provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If not provided then the maximum value will be computed from the values.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array1dOfValues(const LONG64 * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy* proxy, LONG64 nullValue, LONG64 minimumValue, LONG64 maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackLongHdf5Array1dOfValues;
		DLL_IMPORT_OR_EXPORT void pushBackIntHdf5Array1dOfValues(const int * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy* proxy, int nullValue, int minimumValue, int maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackIntHdf5Array1dOfValues;
		DLL_IMPORT_OR_EXPORT void pushBackShortHdf5Array1dOfValues(const short * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy* proxy, short nullValue, short minimumValue, short maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackShortHdf5Array1dOfValues;
		DLL_IMPORT_OR_EXPORT void pushBackCharHdf5Array1dOfValues(const char * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy* proxy, char nullValue, char minimumValue, char maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackCharHdf5Array1dOfValues;

		/**
		* Add a 2d array of explicit long values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly J dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If not provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If not provided then the maximum value will be computed from the values.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array2dOfValues(const LONG64 * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, LONG64 nullValue, LONG64 minimumValue, LONG64 maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackLongHdf5Array2dOfValues;
		DLL_IMPORT_OR_EXPORT void pushBackIntHdf5Array2dOfValues(const int * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, int nullValue, int minimumValue, int maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackIntHdf5Array2dOfValues;
		DLL_IMPORT_OR_EXPORT void pushBackShortHdf5Array2dOfValues(const short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, short nullValue, short minimumValue, short maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackShortHdf5Array2dOfValues;
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5Array2dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackUShortHdf5Array2dOfValues;
		DLL_IMPORT_OR_EXPORT void pushBackCharHdf5Array2dOfValues(const char * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, char nullValue, char minimumValue, char maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackCharHdf5Array2dOfValues;

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
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5Array3dOfValues(const LONG64 * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, LONG64 nullValue, LONG64 minimumValue, LONG64 maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackLongHdf5Array3dOfValues;
		DLL_IMPORT_OR_EXPORT void pushBackIntHdf5Array3dOfValues(const int * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, int nullValue, int minimumValue, int maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackIntHdf5Array3dOfValues;
		DLL_IMPORT_OR_EXPORT void pushBackShortHdf5Array3dOfValues(const short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, short nullValue, short minimumValue, short maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackShortHdf5Array3dOfValues;
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5Array3dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackUShortHdf5Array3dOfValues;
		DLL_IMPORT_OR_EXPORT void pushBackCharHdf5Array3dOfValues(const char * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, char nullValue, char minimumValue, char maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackCharHdf5Array3dOfValues;

		/**
		* Add an array (potentially multi dimensions) of explicit values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param numDimensionsInArray	The number of dimensions in the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If not provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If not provided then the maximum value will be computed from the values.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5ArrayOfValues(const LONG64 * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, LONG64 nullValue);
		DLL_IMPORT_OR_EXPORT void pushBackIntHdf5ArrayOfValues(const int * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, int nullValue);
		DLL_IMPORT_OR_EXPORT void pushBackShortHdf5ArrayOfValues(const short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, short nullValue);
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5ArrayOfValues(const unsigned short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, unsigned short nullValue);
		DLL_IMPORT_OR_EXPORT void pushBackCharHdf5ArrayOfValues(const char * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, char nullValue);
		DLL_IMPORT_OR_EXPORT void pushBackLongHdf5ArrayOfValues(const LONG64 * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, LONG64 nullValue, LONG64 minimumValue, LONG64 maximumValue);
		DLL_IMPORT_OR_EXPORT void pushBackIntHdf5ArrayOfValues(const int * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, int nullValue, int minimumValue, int maximumValue);
		DLL_IMPORT_OR_EXPORT void pushBackShortHdf5ArrayOfValues(const short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, short nullValue, short minimumValue, short maximumValue);
		DLL_IMPORT_OR_EXPORT void pushBackUShortHdf5ArrayOfValues(const unsigned short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, unsigned short nullValue, unsigned short minimumValue, unsigned short maximumValue);
		DLL_IMPORT_OR_EXPORT void pushBackCharHdf5ArrayOfValues(const char * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, char nullValue, char minimumValue, char maximumValue);

		/**
		* Push back a a reference to an existing (or a "to exist") HDF5 dataset in a particular hdf proxy.
		* The reason can be that the indice values already exist in an external file (only HDF5 for now) or that the writing of these indice values in the external file is defered in time.
		* @param	datasetName			The HDF5 dataset name where the values are stored. If empty, the dataset will be named the same as the dataset naming convention of the fesapi : getHdfGroup() + "/values_patch" + patch->RepresentationPatchIndex;
		* @param	hdfProxy				The HDF5 proxy where the values are already or will be stored.
		* @param	nullValue				The null value which has been chosen in the referenced hdf dataset.
		* @param	minimumValue			The minimum value of the values in the HDF5 dataset.
		* @param	maximumValue			The maximum value of the values in the HDF5 dataset.
		* @return	The name of the referenced HDF5 dataset.
		*/
		DLL_IMPORT_OR_EXPORT std::string pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* proxy, const std::string & datasetName, LONG64 nullValue, LONG64 minimumValue, LONG64 maximumValue);
		using AbstractDiscreteOrCategoricalProperty::pushBackRefToExistingDataset;

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
			LONG64* minimumValue, LONG64* maximumValue,
			LONG64 nullValue = (std::numeric_limits<LONG64>::max)(),
			COMMON_NS::AbstractHdfProxy* proxy = nullptr);
		using AbstractDiscreteOrCategoricalProperty::pushBackLongHdf5ArrayOfValues;

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
			LONG64 minimumValue, LONG64 maximumValue,
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
			bool computeMinMax,
			COMMON_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned int patchIndex = (std::numeric_limits<unsigned int>::max)());
		using AbstractDiscreteOrCategoricalProperty::setValuesOfLongHdf5Array3dOfValues;

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
			bool computeMinMax,
			COMMON_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned int patchIndex = (std::numeric_limits<unsigned int>::max)());

		/**
		* Check if the associated local property kind is allowed for this property.
		*/
		bool validatePropertyKindAssociation(COMMON_NS::PropertyKind* pk);

		/**
		* Check if the associated standard property kind is allowed for this property.
		*/
		bool validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind pk);

		/*
		* Check if this discrete property has got a minimum value already computed.
		*/
		DLL_IMPORT_OR_EXPORT bool hasMinimumValue() const;

		/*
		* Get the (first if non scalar) minimum value in this discrete properties. It reads it from file.
		* @return the minimum value if present in the file otherwise long.max.
		*/
		DLL_IMPORT_OR_EXPORT LONG64 getMinimumValue() const;

		/*
		* Check if this discrete property has got a minimum value already computed.
		*/
		DLL_IMPORT_OR_EXPORT bool hasMaximumValue() const;

		/*
		* Get the (first if non scalar) maximum value in this discrete properties. It reads it from file.
		* @return the maximum value if present in the file otherwise long.min.
		*/
		DLL_IMPORT_OR_EXPORT LONG64 getMaximumValue() const;

		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }
	};
}
