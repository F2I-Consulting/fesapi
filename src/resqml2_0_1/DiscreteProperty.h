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

#include "resqml2/AbstractValuesProperty.h"

namespace RESQML2_0_1_NS
{
	/**
	* This class is mainly useful for describing temporal properties on well objects.
	* The prefered approach to describe temporal properties on Reservoir grids is to use one instance of DiscreteProperty per time step.
	*/
	class DLL_IMPORT_OR_EXPORT DiscreteProperty : public RESQML2_NS::AbstractValuesProperty
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DiscreteProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractValuesProperty(partialObject) {}

		DiscreteProperty() {}

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
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

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
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, RESQML2_NS::PropertyKind * localPropKind);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		DiscreteProperty(gsoap_resqml2_0_1::_resqml2__DiscreteProperty* fromGsoap): AbstractValuesProperty(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~DiscreteProperty() {}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* Add a 1d array of explicit long values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCount				The number of values to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If not provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If not provided then the maximum value will be computed from the values.
		*/
		void pushBackLongHdf5Array1dOfValues(const long * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy* proxy, const long & nullValue, const long & minimumValue, const long & maximumValue);
		void pushBackLongHdf5Array1dOfValues(const long * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy* proxy, const long & nullValue);
		void pushBackIntHdf5Array1dOfValues(const int * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy* proxy, const int & nullValue, const int & minimumValue, const int & maximumValue);
		void pushBackIntHdf5Array1dOfValues(const int * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy* proxy, const int & nullValue);
		void pushBackShortHdf5Array1dOfValues(const short * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy* proxy, const short & nullValue, const short & minimumValue, const short & maximumValue);
		void pushBackShortHdf5Array1dOfValues(const short * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy* proxy, const short & nullValue);
		void pushBackCharHdf5Array1dOfValues(const char * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy* proxy, const char & nullValue, const char & minimumValue, const char & maximumValue);
		void pushBackCharHdf5Array1dOfValues(const char * values, const ULONG64 & valueCount, COMMON_NS::AbstractHdfProxy* proxy, const char & nullValue);

		/**
		* Add a 2d array of explicit long values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly J dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If not provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If not provided then the maximum value will be computed from the values.
		*/
		void pushBackLongHdf5Array2dOfValues(const long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const long & nullValue, const long & minimumValue, const long & maximumValue);
		void pushBackLongHdf5Array2dOfValues(const long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const long & nullValue);
		void pushBackIntHdf5Array2dOfValues(const int * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const int & nullValue, const int & minimumValue, const int & maximumValue);
		void pushBackIntHdf5Array2dOfValues(const int * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const int & nullValue);
		void pushBackShortHdf5Array2dOfValues(const short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const short & nullValue, const short & minimumValue, const short & maximumValue);
		void pushBackShortHdf5Array2dOfValues(const short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const short & nullValue);
		void pushBackUShortHdf5Array2dOfValues(const unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const unsigned short & nullValue, const unsigned short & minimumValue, const unsigned short & maximumValue);
		void pushBackUShortHdf5Array2dOfValues(const unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const unsigned short & nullValue);
		void pushBackCharHdf5Array2dOfValues(const char * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const char & nullValue, const char & minimumValue, const char & maximumValue);
		void pushBackCharHdf5Array2dOfValues(const char * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const char & nullValue);

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
		void pushBackLongHdf5Array3dOfValues(const long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const long & nullValue, const long & minimumValue, const long & maximumValue);
		void pushBackLongHdf5Array3dOfValues(const long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const long & nullValue);
		void pushBackIntHdf5Array3dOfValues(const int * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const int & nullValue, const int & minimumValue, const int & maximumValue);
		void pushBackIntHdf5Array3dOfValues(const int * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const int & nullValue);
		void pushBackShortHdf5Array3dOfValues(const short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const short & nullValue, const short & minimumValue, const short & maximumValue);
		void pushBackShortHdf5Array3dOfValues(const short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const short & nullValue);
		void pushBackUShortHdf5Array3dOfValues(const unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const unsigned short & nullValue, const unsigned short & minimumValue, const unsigned short & maximumValue);
		void pushBackUShortHdf5Array3dOfValues(const unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const unsigned short & nullValue);
		void pushBackCharHdf5Array3dOfValues(const char * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const char & nullValue, const char & minimumValue, const char & maximumValue);
		void pushBackCharHdf5Array3dOfValues(const char * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy, const char & nullValue);

		/**
		* Add an array (potentially multi dimensions) of explicit values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param numDimensionsInArray	The number of dimensions in the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If not provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If not provided then the maximum value will be computed from the values.
		*/
		void pushBackLongHdf5ArrayOfValues(const long * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const long & nullValue, const long & minimumValue, const long & maximumValue);
		void pushBackLongHdf5ArrayOfValues(const long * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const long & nullValue);
		void pushBackIntHdf5ArrayOfValues(const int * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const int & nullValue, const int & minimumValue, const int & maximumValue);
		void pushBackIntHdf5ArrayOfValues(const int * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const int & nullValue);
		void pushBackShortHdf5ArrayOfValues(const short * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const short & nullValue, const short & minimumValue, const short & maximumValue);
		void pushBackShortHdf5ArrayOfValues(const short * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const short & nullValue);
		void pushBackUShortHdf5ArrayOfValues(const unsigned short * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const unsigned short & nullValue, const unsigned short & minimumValue, const unsigned short & maximumValue);
		void pushBackUShortHdf5ArrayOfValues(const unsigned short * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const unsigned short & nullValue);
		void pushBackCharHdf5ArrayOfValues(const char * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const char & nullValue, const char & minimumValue, const char & maximumValue);
		void pushBackCharHdf5ArrayOfValues(const char * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, const char & nullValue);

		/**
		* Push back a a reference to an existing (or a "to exist") HDF5 dataset in a particular hdf proxy.
		* The reason can be that the indice values already exist in an external file (only HDF5 for now) or that the writing of these indice values in the external file is defered in time.
		* @param	datasetName			The HDF5 dataset name where the values are stored. If empty, the dataset will be named the same as the dataset naming convention of the fesapi : "/RESQML/" + prop->uuid + "/values_patch" + patch->RepresentationPatchIndex;
		* @param	hdfProxy				The HDF5 proxy where the values are already or will be stored.
		* @param	nullValue				The null value which has been chosen in the referenced hdf dataset.
		* @param	minimumValue			The minimum value of the values in the HDF5 dataset.
		* @param	maximumValue			The maximum value of the values in the HDF5 dataset.
		* @return	The name of the referenced HDF5 dataset.
		*/
		std::string pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* proxy, const std::string & datasetName, const long & nullValue, const long &  minimumValue, const long &  maximumValue);
		std::string pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & dataset = "", const long & nullValue = (std::numeric_limits<long>::max)());

		/**
		* Check if the associated local property kind is allowed for this property.
		*/
		bool validatePropertyKindAssociation(RESQML2_NS::PropertyKind* pk);

		/**
		* Check if the associated standard property kind is allowed for this property.
		*/
		bool validatePropertyKindAssociation(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & pk);

		/*
		* Get the minimum value in this discrete properties. It reads it from file.
		* @return the minimum value if present in the file otherwise long.max.
		*/
		LONG64 getMinimumValue();

		/*
		* Get the maximum value in this discrete properties. It reads it from file.
		* @return the maximum value if present in the file otherwise long.min.
		*/
		LONG64 getMaximumValue();
	};
}

