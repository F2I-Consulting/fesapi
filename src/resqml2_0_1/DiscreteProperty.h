/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#pragma once

#include "resqml2/AbstractValuesProperty.h"

namespace resqml2_0_1
{
	/**
	* This class is mainly useful for describing temporal properties on well objects.
	* The prefered approach to describe temporal properties on Reservoir grids is to use one instance of DiscreteProperty per time step.
	*/
	class DLL_IMPORT_OR_EXPORT DiscreteProperty : public resqml2::AbstractValuesProperty
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DiscreteProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : resqml2::AbstractValuesProperty(partialObject) {}

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
		DiscreteProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
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
		DiscreteProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, resqml2::PropertyKind * localPropKind);

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
		void pushBackLongHdf5Array1dOfValues(long * values, const ULONG64 & valueCount, common::AbstractHdfProxy* proxy, const long & nullValue, const long & minimumValue, const long & maximumValue);
		void pushBackLongHdf5Array1dOfValues(long * values, const ULONG64 & valueCount, common::AbstractHdfProxy* proxy, const long & nullValue);
		void pushBackIntHdf5Array1dOfValues(int * values, const ULONG64 & valueCount, common::AbstractHdfProxy* proxy, const int & nullValue, const int & minimumValue, const int & maximumValue);
		void pushBackIntHdf5Array1dOfValues(int * values, const ULONG64 & valueCount, common::AbstractHdfProxy* proxy, const int & nullValue);
		void pushBackShortHdf5Array1dOfValues(short * values, const ULONG64 & valueCount, common::AbstractHdfProxy* proxy, const short & nullValue, const short & minimumValue, const short & maximumValue);
		void pushBackShortHdf5Array1dOfValues(short * values, const ULONG64 & valueCount, common::AbstractHdfProxy* proxy, const short & nullValue);
		void pushBackCharHdf5Array1dOfValues(char * values, const ULONG64 & valueCount, common::AbstractHdfProxy* proxy, const char & nullValue, const char & minimumValue, const char & maximumValue);
		void pushBackCharHdf5Array1dOfValues(char * values, const ULONG64 & valueCount, common::AbstractHdfProxy* proxy, const char & nullValue);

		/**
		* Add a 2d array of explicit long values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly J dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If not provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If not provided then the maximum value will be computed from the values.
		*/
		void pushBackLongHdf5Array2dOfValues(long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const long & nullValue, const long & minimumValue, const long & maximumValue);
		void pushBackLongHdf5Array2dOfValues(long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const long & nullValue);
		void pushBackIntHdf5Array2dOfValues(int * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const int & nullValue, const int & minimumValue, const int & maximumValue);
		void pushBackIntHdf5Array2dOfValues(int * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const int & nullValue);
		void pushBackShortHdf5Array2dOfValues(short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const short & nullValue, const short & minimumValue, const short & maximumValue);
		void pushBackShortHdf5Array2dOfValues(short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const short & nullValue);
		void pushBackUShortHdf5Array2dOfValues(unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const unsigned short & nullValue, const unsigned short & minimumValue, const unsigned short & maximumValue);
		void pushBackUShortHdf5Array2dOfValues(unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const unsigned short & nullValue);
		void pushBackCharHdf5Array2dOfValues(char * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const char & nullValue, const char & minimumValue, const char & maximumValue);
		void pushBackCharHdf5Array2dOfValues(char * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const char & nullValue);

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
		void pushBackLongHdf5Array3dOfValues(long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const long & nullValue, const long & minimumValue, const long & maximumValue);
		void pushBackLongHdf5Array3dOfValues(long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const long & nullValue);
		void pushBackIntHdf5Array3dOfValues(int * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const int & nullValue, const int & minimumValue, const int & maximumValue);
		void pushBackIntHdf5Array3dOfValues(int * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const int & nullValue);
		void pushBackShortHdf5Array3dOfValues(short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const short & nullValue, const short & minimumValue, const short & maximumValue);
		void pushBackShortHdf5Array3dOfValues(short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const short & nullValue);
		void pushBackUShortHdf5Array3dOfValues(unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const unsigned short & nullValue, const unsigned short & minimumValue, const unsigned short & maximumValue);
		void pushBackUShortHdf5Array3dOfValues(unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const unsigned short & nullValue);
		void pushBackCharHdf5Array3dOfValues(char * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const char & nullValue, const char & minimumValue, const char & maximumValue);
		void pushBackCharHdf5Array3dOfValues(char * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy, const char & nullValue);

		/**
		* Add an array (potentially multi dimensions) of explicit values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param numDimensionsInArray	The number of dimensions in the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If not provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If not provided then the maximum value will be computed from the values.
		*/
		void pushBackLongHdf5ArrayOfValues(long * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const long & nullValue, const long & minimumValue, const long & maximumValue);
		void pushBackLongHdf5ArrayOfValues(long * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const long & nullValue);
		void pushBackIntHdf5ArrayOfValues(int * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const int & nullValue, const int & minimumValue, const int & maximumValue);
		void pushBackIntHdf5ArrayOfValues(int * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const int & nullValue);
		void pushBackShortHdf5ArrayOfValues(short * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const short & nullValue, const short & minimumValue, const short & maximumValue);
		void pushBackShortHdf5ArrayOfValues(short * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const short & nullValue);
		void pushBackUShortHdf5ArrayOfValues(unsigned short * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const unsigned short & nullValue, const unsigned short & minimumValue, const unsigned short & maximumValue);
		void pushBackUShortHdf5ArrayOfValues(unsigned short * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const unsigned short & nullValue);
		void pushBackCharHdf5ArrayOfValues(char * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const char & nullValue, const char & minimumValue, const char & maximumValue);
		void pushBackCharHdf5ArrayOfValues(char * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const char & nullValue);

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
		std::string pushBackRefToExistingDataset(common::AbstractHdfProxy* proxy, const std::string & datasetName, const long & nullValue, const long &  minimumValue, const long &  maximumValue);
		std::string pushBackRefToExistingDataset(common::AbstractHdfProxy* hdfProxy, const std::string & dataset = "", const long & nullValue = (std::numeric_limits<long>::max)());

		/**
		* Check if the associated local property kind is allowed for this property.
		*/
		bool validatePropertyKindAssociation(resqml2::PropertyKind* pk);

		/**
		* Check if the associated standard property kind is allowed for this property.
		*/
		bool validatePropertyKindAssociation(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & pk);
	};
}
