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
#include "common/AbstractHdfProxy.h"

#include <stdexcept>
#include <sstream>      // std::ostringstream

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT ContinuousProperty : public resqml2::AbstractValuesProperty
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
		void init(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind);

	public:

		/**
		* Only to be used in partial transfer context
		*/
		ContinuousProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : resqml2::AbstractValuesProperty(partialObject) {}

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
		ContinuousProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

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
		ContinuousProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2::PropertyKind * localPropKind);

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
		ContinuousProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const std::string & nonStandardUom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

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
		ContinuousProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const std::string & nonStandardUom, resqml2::PropertyKind * localPropKind);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		ContinuousProperty(gsoap_resqml2_0_1::_resqml2__ContinuousProperty* fromGsoap): AbstractValuesProperty(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~ContinuousProperty() {}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* Get the unit of measure of the values of this property.
		* If 'Euc'  is returned, you should check if an extrametadata called "Uom" also exists. If so, it would mean that the property uses a non standard uom. This is an official workaround for a known issue of Resqml 2.0.1.
		*/
		const gsoap_resqml2_0_1::resqml2__ResqmlUom & getUom() const;

		/**
		* Get the unit of measure of the values of this property as a string.
		* If 'Euc'  is returned, you should check if an extrametadata called "Uom" also exists. If so, it would mean that the property uses a non standard uom. This is an official workaround for a known issue of Resqml 2.0.1.
		*/
		std::string getUomAsString() const;

		/**
		* Add a 1d array of explicit double values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCount				The number of values to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If NAN is provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If NAN is provided then the maximum value will be computed from the values.
		*/
		void pushBackDoubleHdf5Array1dOfValues(double * values, const ULONG64 & valueCount, common::AbstractHdfProxy* proxy,
			const double & minimumValue = std::numeric_limits<double>::quiet_NaN(), const double & maximumValue = std::numeric_limits<double>::quiet_NaN());

		/**
		* Add a 2d array of explicit double values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly J dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If NAN is provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If NAN is provided then the maximum value will be computed from the values.
		*/
		void pushBackDoubleHdf5Array2dOfValues(double * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy,
			const double & minimumValue = std::numeric_limits<double>::quiet_NaN(), const double & maximumValue = std::numeric_limits<double>::quiet_NaN());

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
		void pushBackDoubleHdf5Array3dOfValues(double * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy,
			const double & minimumValue = std::numeric_limits<double>::quiet_NaN(), const double & maximumValue = std::numeric_limits<double>::quiet_NaN());

		/**
		* Add an array (potentially multi dimensions) of explicit double values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value (or value vector) of the values to add. If nullptr is provided and the dimension of value is 1 then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value (or value vector) of the values to add. If nullptr is provided and the dimension of value is 1 then the maximum value will be computed from the values.
		*/
		void pushBackDoubleHdf5ArrayOfValues(double * values, unsigned long long * numValues, const unsigned int & numArrayDimensions, common::AbstractHdfProxy* proxy,
			double * minimumValue = nullptr, double * maximumValue = nullptr);

		/**
		* Add a 1d array of explicit float values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCount				The number of values to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If NAN is provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If NAN is provided then the maximum value will be computed from the values.
		*/
		void pushBackFloatHdf5Array1dOfValues(float * values, const ULONG64 & valueCount, common::AbstractHdfProxy* proxy,
			const float & minimumValue = std::numeric_limits<float>::quiet_NaN(), const float & maximumValue = std::numeric_limits<float>::quiet_NaN());

		/**
		* Add a 2d array of explicit float values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the slowest dimension (mainly I dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly J dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value of the values to add. If NAN is provided then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value of the values to add. If NAN is provided then the maximum value will be computed from the values.
		*/
		void pushBackFloatHdf5Array2dOfValues(float * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy,
			const float & minimumValue = std::numeric_limits<float>::quiet_NaN(), const float & maximumValue = std::numeric_limits<float>::quiet_NaN());

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
		void pushBackFloatHdf5Array3dOfValues(float * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy* proxy,
			const float & minimumValue = std::numeric_limits<float>::quiet_NaN(), const float & maximumValue = std::numeric_limits<float>::quiet_NaN());

		/**
		* Add an array (potentially multi dimensions) of explicit float values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param minimumValue			The minimum value (or value vector) of the values to add. If nullptr is provided and the dimension of value is 1 then the minimum value will be computed from the values.
		* @param maximumValue			The maximum value (or value vector) of the values to add. If nullptr is provided and the dimension of value is 1 then the maximum value will be computed from the values.
		*/
		void pushBackFloatHdf5ArrayOfValues(float * values, unsigned long long * numValues, const unsigned int & numArrayDimensions, common::AbstractHdfProxy* proxy,
			float * minimumValue = nullptr, float * maximumValue = nullptr);

		/**
		* Create an array (potentially multi dimensions) of explicit float values to the property values. No values are written to this array yet then the HDF5 array contains uninitialized values.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		void pushBackFloatHdf5ArrayOfValues(
			unsigned long long* numValues,
			const unsigned int& numArrayDimensions, 
			common::AbstractHdfProxy* proxy
		);

		/**
		* Create a 3d array of explicit float values to the property values. No values are written to this array yet then the HDF5 array contains uninitialized values.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		void pushBackFloatHdf5ArrayOfValues(
			const ULONG64& valueCountInFastestDim,
			const ULONG64& valueCountInMiddleDim,
			const ULONG64& valueCountInSlowestDim,
			common::AbstractHdfProxy* proxy
		);

		/**
		* Set some values of an existing 3d array of explicit float values of a particular patch. This method makes use of HDF5 hyperslabbing.
		* This method is to be used along with createFloatHdf5ArrayOfValues.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param valueCountInFastestDim	The number of values to write in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to write in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to write in the slowest dimension (mainly K dimension).
		* @param offsetInFastestDim		The offset to write in the fastest dimension (mainly I dimension).
		* @param offsetInMiddleDim		The offset value to write in the middle dimension (mainly J dimension).
		* @param offsetInSlowestDim		The offset value to write in the slowest dimension (mainly K dimension).
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param patchIndex				The index of the patch we want to set some values. If not present, the last patch is arbitrarily taken into account.
		*/
		void setValuesOfFloatHdf5ArrayOfValues(
			float* values, 
			const ULONG64& valueCountInFastestDim,
			const ULONG64& valueCountInMiddleDim,
			const ULONG64& valueCountInSlowestDim,
			const ULONG64& offsetInFastestDim,
			const ULONG64& offsetInMiddleDim,
			const ULONG64& offsetInSlowestDim,
			common::AbstractHdfProxy* proxy,
			unsigned int patchIndex = (std::numeric_limits<unsigned int>::max)()
		);

		/**
		* Set some values of an existing 3d array of explicit float values of a particular patch.  This method makes use of HDF5 hyperslabbing.
		* This method is to be used along with createFloatHdf5ArrayOfValues.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param numValues				The number of property values ordered by dimension of the array to write.
		* @param offsetValues			The offset values ordered by dimension of the array to write.
		* @param numArrayDimensions		The number of dimensions of the array to write.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		* @param patchIndex				The index of the patch we want to set some values.  If not present, the last patch is arbitrarily taken into account.
		*/
		void setValuesOfFloatHdf5ArrayOfValues(
			float * values, 
			unsigned long long * numValues,
			unsigned long long * offsetValues,
			const unsigned int & numArrayDimensions, 
			common::AbstractHdfProxy* proxy,
			unsigned int patchIndex = (std::numeric_limits<unsigned int>::max)()
		);

		/**
		* Push back a new patch of values for this property where the values have not to be written in the HDF file.
		* The reason can be that the values already exist in an external file (only HDF5 for now) or that the writing of the values in the external file is defered in time.
		* @param	hdfProxy			The HDF5 proxy where the values are already or will be stored.
		* @param	datasetName			If not provided during the method call, the dataset will be named the same as the dataset naming convention of the fesapi :"/RESQML/" + prop->uuid + "/values_patch" + patchIndex;
		* @param	nullValue			Only relevant for integer hdf5 datasets. Indeed, Resqml (and fesapi) forces null value for floating point ot be NaN value.
		* @return	The name of the hdf5 dataset.
		*/
		std::string pushBackRefToExistingDataset(common::AbstractHdfProxy* hdfProxy, const std::string & datasetName = "", const long & nullValue = (std::numeric_limits<long>::max)());

		/**
		* Get all the values of a particular patch of the instance which are supposed to be double ones.
		* @param patchIndex	The index of the patch we want the values from.
		* @param values		The array (pointer) of values must be preallocated.
		*/
		void getDoubleValuesOfPatch(const unsigned int & patchIndex, double * values);

		/**
		* Get all the values of a particular patch of the instance which are supposed to be float ones.
		* @param patchIndex	The index of the patch we want the values from.
		* @param values		The array (pointer) of values must be preallocated.
		*/
		void getFloatValuesOfPatch(const unsigned int & patchIndex, float * values);

		/**
		* Get some of the values of a particular patch of the instance which are supposed to be float ones. This method makes use of HDF5 hyperslabbing.
		* @param patchIndex					The index of the patch we want the values from.
		* @param values						The array (pointer) of values must be preallocated.
		* @param numValuesInEachDimension	The number of property values ordered by dimension of the array to write.
		* @param offsetInEachDimension		The offset values ordered by dimension of the array to write.
		* @param numArrayDimensions			The number of dimensions of the HDF5 array to read.
		*/
		void getFloatValuesOfPatch(
			const unsigned int& patchIndex, 
			float* values, 
			unsigned long long* numValuesInEachDimension,
			unsigned long long* offsetInEachDimension,
			const unsigned int& numArrayDimensions
		);

		/**
		* Get some of the values of a particular patch of the instance which are supposed to be float ones. This method makes use of HDF5 hyperslabbing.
		* @param patchIndex					The index of the patch we want the values from.
		* @param values						The array (pointer) of values must be preallocated.
		* @param valueCountInFastestDim	The number of values to read in the fastest dimension (mainly I dimension).
		* @param valueCountInMiddleDim	The number of values to read in the middle dimension (mainly J dimension).
		* @param valueCountInSlowestDim The number of values to read in the slowest dimension (mainly K dimension).
		* @param offsetInFastestDim		The offset value to read in the fastest dimension (mainly I dimension).
		* @param offsetInMiddleDim		The offset value to read in the middle dimension (mainly J dimension).
		* @param offsetInSlowestDim		The offset value to read in the slowest dimension (mainly K dimension).
		*/
		void getFloatValuesOf3dPatch(
			const unsigned int& patchIndex, 
			float* values, 
			const ULONG64& valueCountInFastestDim,
			const ULONG64& valueCountInMiddleDim,
			const ULONG64& valueCountInSlowestDim,
			const ULONG64& offsetInFastestDim,
			const ULONG64& offsetInMiddleDim,
			const ULONG64& offsetInSlowestDim
		);

		double getMinimumValue();
		double getMaximumValue();

		/**
		* Check if the associated local property kind is allowed for this property.
		*/
		bool validatePropertyKindAssociation(resqml2::PropertyKind* pk);

		/**
		* Check if the associated standard property kind is allowed for this property.
		*/
		bool validatePropertyKindAssociation(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & pk);

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
			T* values, 
			unsigned long long* numValuesInEachDimension,
			const unsigned int& numArrayDimensions,
			T * minimumValue = nullptr, T * maximumValue = nullptr)
		{
			gsoap_resqml2_0_1::_resqml2__ContinuousProperty* prop = static_cast<gsoap_resqml2_0_1::_resqml2__ContinuousProperty*>(gsoapProxy2_0_1);
			prop->MinimumValue.clear();
			prop->MaximumValue.clear();

			if (minimumValue != nullptr && maximumValue != nullptr) {
				for (unsigned int i = 0; i < prop->Count; ++i)
				{
					prop->MinimumValue.push_back(minimumValue[i]);
					prop->MaximumValue.push_back(maximumValue[i]);
				}
			}
			else {

				ULONG64 nValues = numValuesInEachDimension[0];
				if (prop->Count == 1) {
					for (unsigned int dim = 1; dim < numArrayDimensions; dim++) {
						nValues *= numValuesInEachDimension[dim];
					}
				}
				else if (prop->Count > 1) {
					//In this case, the last (fastest) dimension has the number of properties per indexable element of the representation.
					for (unsigned int dim = 1; dim < numArrayDimensions - 1; dim++) {
						nValues *= numValuesInEachDimension[dim];
					}
				}
				else {
					throw std::invalid_argument("Cannot compute and set min and max value on a property which has a Count set to zero or negative.");
				}

				for (unsigned int propIndex = 0; propIndex < prop->Count; ++propIndex) {
					size_t i = propIndex;
					T computedMin = std::numeric_limits<T>::quiet_NaN();
					T computedMax = std::numeric_limits<T>::quiet_NaN();
					while (i < nValues && values[i] != values[i]) i += prop->Count;
					if (i >= nValues) {
						throw std::invalid_argument("All values of a dimension of the vectorial property look to be only NaN values.");
					}
					computedMin = values[i];
					computedMax = values[i];

					for (; i < nValues; i += prop->Count) {
						T propVal = values[i];
						if (propVal < computedMin) {
							computedMin = propVal;
						}
						else if (propVal > computedMax) {
							computedMax = propVal;
						}
					}
					prop->MinimumValue.push_back(computedMin);
					prop->MaximumValue.push_back(computedMax);
				}
			}
		}
	};
}
