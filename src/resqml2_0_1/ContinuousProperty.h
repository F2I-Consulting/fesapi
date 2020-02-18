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
#include "../common/AbstractHdfProxy.h"

#include <stdexcept>
#include <sstream>

namespace RESQML2_0_1_NS
{
	/**
	* Most common type of property used for storing rock or fluid attributes; all are represented as floating point values. 
	* So that the value range can be known before accessing all values, the min and max values of the range are also optionally stored. 
	* BUSINESS RULE: It also contains a unit of measure, which can be different from the unit of measure of its property type, but it must be convertible into this unit.
	*/
	class ContinuousProperty : public RESQML2_NS::AbstractValuesProperty
	{
	protected:

		/**
		* Default constructor
		*/
		ContinuousProperty() {}

	private:

		/**
		* Creates an instance of this class in a gsoap context.
		* @param rep						The representation which supports these property values.
		* @param guid						The guid to set to the fault. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param dimension					The dimension of each value (scalar properties == 1).
		* @param attachmentKind				The topological orbit which supports each value.
		*/
		void init(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind);

	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT ContinuousProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractValuesProperty(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context based on a standard kind and a standard uom.
		* @param rep						The representation which supports these property values.
		* @param guid						The guid to set to the fault. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param dimension					The dimension of each value (scalar properties == 1).
		* @param attachmentKind				The topological orbit which supports each value.
		* @param uom						The uom of the values. Please check EpcDocument::getEnergisticsUnitOfMeasure(const std::string & energisticsUomName) in order to minimize the use of non standard uom.
		* @param energisticsPropertyKind	The property kind of these property values which must be defined in the standard energistics property type dictionary.
		*/
		ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		/**
		* Creates an instance of this class in a gsoap context based on a local kind and a standard uom.
		* @param rep						The representation which supports these property values.
		* @param guid						The guid to set to the fault. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param dimension					The dimension of each value (scalar properties == 1).
		* @param attachmentKind				The topological orbit which supports each value.
		* @param uom						The uom of the values. Please check EpcDocument::getEnergisticsUnitOfMeasure(const std::string & energisticsUomName) in order to minimize the use of non standard uom.
		* @param localPropType				The property kind of these property values which must be defined in the EPC document as a local property kind.
		*/
		ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, COMMON_NS::PropertyKind * localPropKind);

		/**
		* Creates an instance of this class in a gsoap context based on a standard kind and a local uom.
		* @param rep						The representation which supports these property values.
		* @param guid						The guid to set to the fault. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param dimension					The dimension of each value (scalar properties == 1).
		* @param attachmentKind				The topological orbit which supports each value.
		* @param nonStandardUom				The non standard uom of the values. Please check EpcDocument::getEnergisticsUnitOfMeasure(const std::string & energisticsUomName) in order to minimize the use of non standard uom.
		* @param energisticsPropertyKind	The property kind of these property values which must be defined in the standard energistics property type dictionary.
		*/
		ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind, const std::string & nonStandardUom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		/**
		* Creates an instance of this class in a gsoap context based on a local kind and a local uom.
		* @param rep						The representation which supports these property values.
		* @param guid						The guid to set to the fault. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param dimension					The dimension of each value (scalar properties == 1).
		* @param attachmentKind				The topological orbit which supports each value.
		* @param nonStandardUom				The non standard uom of the values. Please check EpcDocument::getEnergisticsUnitOfMeasure(const std::string & energisticsUomName) in order to minimize the use of non standard uom.
		* @param localPropType				The property kind of these property values which must be defined in the EPC document as a local property kind.
		*/
		ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind, const std::string & nonStandardUom, COMMON_NS::PropertyKind * localPropKind);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		ContinuousProperty(gsoap_resqml2_0_1::_resqml20__ContinuousProperty* fromGsoap): AbstractValuesProperty(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~ContinuousProperty() {}

		/**
		* Get the unit of measure of the values of this property.
		* If 'Euc'  is returned, you should check if an extrametadata called "Uom" also exists. If so, it would mean that the property uses a non standard uom. This is an official workaround for a known issue of Resqml 2.0.1.
		*/
		DLL_IMPORT_OR_EXPORT const gsoap_resqml2_0_1::resqml20__ResqmlUom & getUom() const;

		/**
		* Get the unit of measure of the values of this property as a string.
		* If 'Euc'  is returned, you should check if an extrametadata called "Uom" also exists. If so, it would mean that the property uses a non standard uom. This is an official workaround for a known issue of Resqml 2.0.1.
		*/
		DLL_IMPORT_OR_EXPORT std::string getUomAsString() const;

		/**
		* Add a 1d array of explicit double values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCount				The number of values to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If NAN is provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If NAN is provided then the maximum value will be computed from the values.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackDoubleHdf5Array1dOfValues(const double * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy* proxy = nullptr,
			double minimumValue = std::numeric_limits<double>::quiet_NaN(), double maximumValue = std::numeric_limits<double>::quiet_NaN());

		/**
		* Add a 2d array of explicit double values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly J dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If NAN is provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If NAN is provided then the maximum value will be computed from the values.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackDoubleHdf5Array2dOfValues(const double * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy = nullptr,
			double minimumValue = std::numeric_limits<double>::quiet_NaN(), double maximumValue = std::numeric_limits<double>::quiet_NaN());

		/**
		* Add a 3d array of explicit double values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If NAN is provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If NAN is provided then the maximum value will be computed from the values.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackDoubleHdf5Array3dOfValues(const double * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy = nullptr,
			double minimumValue = std::numeric_limits<double>::quiet_NaN(), double maximumValue = std::numeric_limits<double>::quiet_NaN());

		/**
		* Add an array (potentially multi dimensions) of explicit double values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value (or value vector) of the values to add. If nullptr is provided and the dimension of value is 1 then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value (or value vector) of the values to add. If nullptr is provided and the dimension of value is 1 then the maximum value will be computed from the values.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackDoubleHdf5ArrayOfValues(double const * values, unsigned long long const * numValues, unsigned int numArrayDimensions, COMMON_NS::AbstractHdfProxy* proxy = nullptr,
			double * minimumValue = nullptr, double * maximumValue = nullptr);

		/**
		* Add a 1d array of explicit float values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCount				The number of values to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If NAN is provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If NAN is provided then the maximum value will be computed from the values.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5Array1dOfValues(const float * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy* proxy = nullptr,
			float minimumValue = std::numeric_limits<float>::quiet_NaN(), float maximumValue = std::numeric_limits<float>::quiet_NaN());

		/**
		* Add a 2d array of explicit float values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the slowest dimension (mainly I dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly J dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If NAN is provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If NAN is provided then the maximum value will be computed from the values.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5Array2dOfValues(const float * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy = nullptr,
			float minimumValue = std::numeric_limits<float>::quiet_NaN(), float maximumValue = std::numeric_limits<float>::quiet_NaN());

		/**
		* Add a 3d array of explicit float values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the slowest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the slowest dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If NAN is provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If NAN is provided then the maximum value will be computed from the values.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5Array3dOfValues(const float * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy* proxy = nullptr,
			float minimumValue = std::numeric_limits<float>::quiet_NaN(), float maximumValue = std::numeric_limits<float>::quiet_NaN());

		/**
		* Add an array (potentially multi dimensions) of explicit float values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value (or value vector) of the values to add. If nullptr is provided and the dimension of value is 1 then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value (or value vector) of the values to add. If nullptr is provided and the dimension of value is 1 then the maximum value will be computed from the values.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5ArrayOfValues(float const * values, unsigned long long const * numValues, unsigned int numArrayDimensions, COMMON_NS::AbstractHdfProxy* proxy = nullptr,
			float * minimumValue = nullptr, float * maximumValue = nullptr);

		/**
		* Push back a new patch of values for this property where the values have not to be written in the HDF file.
		* The reason can be that the values already exist in an external file (only HDF5 for now) or that the writing of the values in the external file is defered in time.
		* @param	proxy				The HDF5 proxy where the values are already or will be stored.
		* @param	datasetName			If not provided during the method call, the dataset will be named the same as the dataset naming convention of the fesapi :"/RESQML/" + prop->uuid + "/values_patch" + patchIndex;
		* @param	nullValue			Only relevant for integer hdf5 datasets. Indeed, RESQML (and fesapi) forces null value for floating point to be NaN value.
		* @return	The name of the hdf5 dataset.
		*/
		DLL_IMPORT_OR_EXPORT std::string pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* proxy, const std::string & datasetName = "");

		/**
		* Get all the values of a particular patch of the instance which are supposed to be double ones.
		* @param patchIndex	The index of the patch we want the values from.
		* @param values		The array (pointer) of values must be preallocated.
		*/
		DLL_IMPORT_OR_EXPORT void getDoubleValuesOfPatch(unsigned int patchIndex, double * values) const ;

		/**
		* Get all the values of a particular patch of the instance which are supposed to be float ones.
		* @param patchIndex	The index of the patch we want the values from.
		* @param values		The array (pointer) of values must be preallocated.
		*/
		DLL_IMPORT_OR_EXPORT void getFloatValuesOfPatch(unsigned int patchIndex, float * values) const;

		/*
		* Get the minimum value in this continuous properties. It reads it from file.
		* @return the minimum value if present in the file otherwise NaN.
		*/
		DLL_IMPORT_OR_EXPORT double getMinimumValue() const;

		/*
		* Get the maximum value in this discrete properties. It reads it from file.
		* @return the maximum value if present in the file otherwise NaN.
		*/
		DLL_IMPORT_OR_EXPORT double getMaximumValue() const;

		/**
		* Check if the associated local property kind is allowed for this property.
		*/
		bool validatePropertyKindAssociation(COMMON_NS::PropertyKind* pk);

		/**
		* Check if the associated standard property kind is allowed for this property.
		*/
		bool validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind pk);

		//***************************
		//*** For hyperslabbing *****
		//***************************

		/**
		* Create an array (potentially multi dimensions) of explicit float values to the property values. No values are written to this array yet then the HDF5 array contains uninitialized values.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value (or value vector) of the values to add. If nullptr is provided then no minimum value will be set. It cannot be nullptr if maximumValue is not NaN.
		* @param maximumValue			The maximum value (or value vector) of the values to add. If nullptr is provided then no maximum value will be set. It cannot be nullptr if minimumValue is not NaN.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5ArrayOfValues(
			unsigned long long const * numValues,
			unsigned int numArrayDimensions,
			COMMON_NS::AbstractHdfProxy* proxy = nullptr,
			float * minimumValue = nullptr, float * maximumValue = nullptr
		);

		/**
		* Create a 3d array of explicit float values to the property values. No values are written to this array yet then the HDF5 array contains uninitialized values.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If NAN is provided then no minimum value will be set. It cannot be NaN if maximumValue is not NaN.
		* @param maximumValue			The maximum value of the values to add. If NAN is provided then no maximum value will be set. It cannot be NaN if minimumValue is not NaN.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackFloatHdf5Array3dOfValues(
			ULONG64 valueCountInFastestDim,
			ULONG64 valueCountInMiddleDim,
			ULONG64 valueCountInSlowestDim,
			COMMON_NS::AbstractHdfProxy* proxy = nullptr,
			float minimumValue = std::numeric_limits<float>::quiet_NaN(), float maximumValue = std::numeric_limits<float>::quiet_NaN()
		);

		/**
		* Set some values of an existing 3d array of explicit float values of a particular patch. This method makes use of HDF5 hyperslabbing.
		* This method is to be used along with one of the pushBackFloatHdf5ArrayOfValues methods which do not write any value.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param offsetInFastestDim		The offset to write in the fastest dimension (mainly I dimension).
		* @param offsetInMiddleDim		The offset value to write in the middle dimension (mainly J dimension).
		* @param offsetInSlowestDim		The offset value to write in the slowest dimension (mainly K dimension).
		* @param computeMinMax			Indicates if FESAPI needs to compute the min and  max from the given \p values in order to set them.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param patchIndex				The index of the patch we want to set some values. If not present, the last patch is arbitrarily taken into account.
		*/
		DLL_IMPORT_OR_EXPORT void setValuesOfFloatHdf5Array3dOfValues(
			float const * values,
			ULONG64 valueCountInFastestDim,
			ULONG64 valueCountInMiddleDim,
			ULONG64 valueCountInSlowestDim,
			ULONG64 offsetInFastestDim,
			ULONG64 offsetInMiddleDim,
			ULONG64 offsetInSlowestDim,
			bool computeMinMax = true,
			COMMON_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned int patchIndex = (std::numeric_limits<unsigned int>::max)()
		);

		/**
		* Set some values of an existing 3d array of explicit float values of a particular patch.  This method makes use of HDF5 hyperslabbing.
		* This method is to be used along with one of the pushBackFloatHdf5ArrayOfValues methods which do not write any value.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write. From slowest to fastest.
		* @param offsetValues			The offset values ordered by dimension of the array to write. From slowest to fastest.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param patchIndex				The index of the patch we want to set some values.  If not present, the last patch is arbitrarily taken into account.
		*/
		DLL_IMPORT_OR_EXPORT void setValuesOfFloatHdf5ArrayOfValues(
			float const * values,
			unsigned long long const * numValues,
			unsigned long long const * offsetValues,
			unsigned int numArrayDimensions,
			bool computeMinMax = true,
			COMMON_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned int patchIndex = (std::numeric_limits<unsigned int>::max)()
		);

		/**
		* Get some of the values of a particular patch of the instance as float ones. This method makes use of HDF5 hyperslabbing.
		* @param patchIndex					The index of the patch we want the values from.
		* @param values						The array (pointer) of values must be preallocated.
		* @param numValuesInEachDimension	The number of property values ordered by dimension of the array to write.
		* @param offsetInEachDimension		The offset values ordered by dimension of the array to write.
		* @param numArrayDimensions			The number of dimensions of the HDF5 array to read.
		*/
		DLL_IMPORT_OR_EXPORT void getFloatValuesOfPatch(
			unsigned int patchIndex,
			float* values,
			unsigned long long const * numValuesInEachDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned int numArrayDimensions
		) const;

		/**
		* Get some of the values of a particular patch of the instance as float ones. This method makes use of HDF5 hyperslabbing.
		* @param patchIndex				The index of the patch we want the values from.
		* @param values					The array (pointer) of values must be preallocated.
		* @param valueCountInFastestDim	The number of values to read in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to read in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to read in the slowest dimension (mainly K dimension).
		* @param offsetInFastestDim		The offset value to read in the fastest dimension (mainly I dimension).
		* @param offsetInMiddleDim		The offset value to read in the middle dimension (mainly J dimension).
		* @param offsetInSlowestDim		The offset value to read in the slowest dimension (mainly K dimension).
		*/
		DLL_IMPORT_OR_EXPORT void getFloatValuesOf3dPatch(
			unsigned int patchIndex,
			float* values,
			ULONG64 valueCountInFastestDim,
			ULONG64 valueCountInMiddleDim,
			ULONG64 valueCountInSlowestDim,
			ULONG64 offsetInFastestDim,
			ULONG64 offsetInMiddleDim,
			ULONG64 offsetInSlowestDim
		) const;

		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlNamespace() const { return XML_NS; }

	private:

		/**
		* Compute and set the minimum and maximum value in \p values. 
		* @param values				The array of values.
		* @param numValues			The number of property values in each dimension.
		* @param numArrayDimensions	The number of dimensions of the array.
		* @param minimumValue		If this value and \p maximumValue are defined then the method does not compute the min but forces it to this value.
		* @param maximumValue		If this value and \p minimumValue are defined then the method does not compute the max but forces it to this value.
		*/
		template <class T>
		void setPropertyMinMax(
			T const * values, 
			unsigned long long const * numValuesInEachDimension,
			unsigned int numArrayDimensions,
			T * minimumValue = nullptr, T * maximumValue = nullptr)
		{
			gsoap_resqml2_0_1::_resqml20__ContinuousProperty* prop = static_cast<gsoap_resqml2_0_1::_resqml20__ContinuousProperty*>(gsoapProxy2_0_1);

			// Some minimum and maximum values are given : No need to compute them.
			if (minimumValue != nullptr) {
				for (size_t propIndex = 0; propIndex < prop->Count; ++propIndex) {
					if (prop->MinimumValue.size() > propIndex) {
						prop->MinimumValue[propIndex] = fmin(prop->MinimumValue[propIndex], minimumValue[propIndex]);
					}
					else {
						prop->MinimumValue.push_back(minimumValue[propIndex]);
					}
				}
			}
			if (maximumValue != nullptr) {
				for (size_t propIndex = 0; propIndex < prop->Count; ++propIndex) {
					if (prop->MaximumValue.size() > propIndex) {
						prop->MaximumValue[propIndex] = fmax(prop->MaximumValue[propIndex], maximumValue[propIndex]);
					}
					else {
						prop->MaximumValue.push_back(maximumValue[propIndex]);
					}
				}
			}
			if (minimumValue != nullptr && maximumValue != nullptr) return; // No need to compute max or min value

			ULONG64 nValues = numValuesInEachDimension[0];
			//If count > 1, the last (fastest) dimension has the number of properties per indexable element of the representation.
			for (unsigned int dim = 1; dim < (prop->Count == 1 ? numArrayDimensions : numArrayDimensions - 1); ++dim) { 
				nValues *= numValuesInEachDimension[dim];
			}

			// Minimum or maximum values are not given : Need to compute them.
			std::unique_ptr<T[]> allComputedMin(new T[prop->Count]);
			std::unique_ptr<T[]> allComputedMax(new T[prop->Count]);
			for (size_t propIndex = 0; propIndex < prop->Count; ++propIndex) {
				allComputedMin[propIndex] = std::numeric_limits<T>::quiet_NaN();
				allComputedMax[propIndex] = std::numeric_limits<T>::quiet_NaN();
				for (size_t i = 0; i < nValues; i += prop->Count) {
					allComputedMin[propIndex] = fmin(allComputedMin[propIndex], values[i]);
					allComputedMax[propIndex] = fmax(allComputedMax[propIndex], values[i]);
				}
			}
			setPropertyMinMax(values, numValuesInEachDimension, numArrayDimensions, allComputedMin.get(), allComputedMax.get());
		}
	};
}
