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

#include "AbstractHdfProxy.h"

#include <unordered_map>

namespace EML2_NS
{
	/** @brief	A proxy for reading and writing values into an HDF5 file. */
	class HdfProxy : public AbstractHdfProxy
	{
	public:

		/**
		 * Constructor. Only to be used in partial transfer context
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		HdfProxy(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractHdfProxy(partialObject), hdfFile(-1), compressionLevel(0) {}

		/**
		 * @brief	Constructor
		 *
		 * @param 	dor	The dor.
		 */
		HdfProxy(const COMMON_NS::DataObjectReference& dor) : AbstractHdfProxy(dor), hdfFile(-1), compressionLevel(0) {}

		/** Destructor. Closes the hdf file. */
		virtual ~HdfProxy() { close(); }

		void open() override;

		DLL_IMPORT_OR_EXPORT bool isOpened() const final { return hdfFile != -1; }

		void close() final;

		hdf5_hid_t getHdfDatatypeInDataset(const std::string& groupName) final;

		int getHdfDatatypeClassInDataset(const std::string& datasetName) final;

		void writeItemizedListOfList(const std::string& groupName,
			const std::string& name,
			hdf5_hid_t cumulativeLengthDatatype,
			const void* cumulativeLength,
			unsigned long long cumulativeLengthSize,
			hdf5_hid_t elementsDatatype,
			const void* elements,
			unsigned long long elementsSize) final;

		unsigned int getDimensionCount(const std::string& datasetName) final;

		signed long long getElementCount(const std::string& datasetName) final;

		DLL_IMPORT_OR_EXPORT void setCompressionLevel(unsigned int newCompressionLevel) final {
			compressionLevel = newCompressionLevel > 9 ? 9 : newCompressionLevel;
		}

		void writeArrayNdOfFloatValues(const std::string& groupName,
			const std::string& name,
			const float* floatValues,
			const unsigned long long* numValuesInEachDimension,
			unsigned int numDimensions) final;

		void writeArrayNdOfDoubleValues(const std::string& groupName,
			const std::string& name,
			const double* dblValues,
			const unsigned long long* numValuesInEachDimension,
			unsigned int numDimensions) final;

		void writeArrayNdOfCharValues(const std::string& groupName,
			const std::string& name,
			const char* intValues,
			const unsigned long long* numValuesInEachDimension,
			unsigned int numDimensions) final;

		void writeArrayNdOfIntValues(const std::string& groupName,
			const std::string& name,
			const int* intValues,
			const unsigned long long* numValuesInEachDimension,
			unsigned int numDimensions) final;

		void writeArrayNdOfGSoapULong64Values(const std::string& groupName,
			const std::string& name,
			const ULONG64* ulong64Values,
			const unsigned long long* numValuesInEachDimension,
			unsigned int numDimensions) final;

		void writeArrayNd(const std::string& groupName,
			const std::string& name,
			hdf5_hid_t datatype,
			const void* values,
			const unsigned long long* numValuesInEachDimension,
			unsigned int numDimensions) final;

		void createArrayNd(
			const std::string& groupName,
			const std::string& name,
			hdf5_hid_t datatype,
			const unsigned long long* numValuesInEachDimension,
			unsigned int numDimensions
		) final;

		void writeArrayNdSlab(
			const std::string& groupName,
			const std::string& name,
			hdf5_hid_t datatype,
			const void* values,
			const unsigned long long* numValuesInEachDimension,
			const unsigned long long* offsetValuesInEachDimension,
			unsigned int numDimensions
		) final;

		void writeGroupAttributes(const std::string& groupName,
			const std::vector<std::string>& attributeNames,
			const std::vector<std::string>& values) final;

		void writeGroupAttribute(const std::string& groupName,
			const std::string& attributeName,
			const std::vector<std::string>& values) final;

		void writeGroupAttributes(const std::string& groupName,
			const std::vector<std::string>& attributeNames,
			const std::vector<double>& values) final;

		void writeGroupAttributes(const std::string& groupName,
			const std::vector<std::string>& attributeNames,
			const std::vector<int>& values) final;

		void writeDatasetAttributes(const std::string& datasetName,
			const std::vector<std::string>& attributeNames,
			const std::vector<std::string>& values) final;

		void writeDatasetAttribute(const std::string& datasetName,
			const std::string& attributeName,
			const std::vector<std::string>& values) final;

		void writeDatasetAttributes(const std::string& datasetName,
			const std::vector<std::string>& attributeNames,
			const std::vector<double>& values) final;

		void writeDatasetAttributes(const std::string& datasetName,
			const std::vector<std::string>& attributeNames,
			const std::vector<int>& values) final;

		std::string readStringAttribute(const std::string& obj_name,
			const std::string& attr_name) const final;

		std::vector<std::string> readStringArrayAttribute(const std::string& obj_name,
			const std::string& attr_name) const final;

		double readDoubleAttribute(const std::string& obj_name,
			const std::string& attr_name) const final;

		LONG64 readLongAttribute(const std::string& obj_name,
			const std::string& attr_name) const final;

		void readArrayNdOfDoubleValues(const std::string& datasetName, double* values) final;

		void readArrayNdOfDoubleValues(
			const std::string& datasetName,
			double* values,
			unsigned long long const* numValuesInEachDimension,
			unsigned long long const* offsetInEachDimension,
			unsigned int numDimensions
		) final;

		void readArrayNdOfDoubleValues(
			const std::string& datasetName, double* values,
			unsigned long long const* blockCountPerDimension,
			unsigned long long const* offsetInEachDimension,
			unsigned long long const* strideInEachDimension,
			unsigned long long const* blockSizeInEachDimension,
			unsigned int numDimensions) final;

		void selectArrayNdOfValues(
			const std::string& datasetName,
			unsigned long long const* blockCountPerDimension,
			unsigned long long const* offsetInEachDimension,
			unsigned long long const* strideInEachDimension,
			unsigned long long const* blockSizeInEachDimension,
			unsigned int numDimensions,
			bool newSelection,
			hdf5_hid_t& dataset,
			hdf5_hid_t& filespace) final;

		void readArrayNdOfDoubleValues(
			hdf5_hid_t dataset,
			hdf5_hid_t filespace,
			void* values,
			unsigned long long slabSize) final;

		void readArrayNdOfFloatValues(const std::string& datasetName, float* values) final;

		void readArrayNdOfFloatValues(
			const std::string& datasetName,
			float* values,
			unsigned long long const* numValuesInEachDimension,
			unsigned long long const* offsetInEachDimension,
			unsigned int numDimensions
		) final;

		void readArrayNdOfLongValues(const std::string& datasetName, LONG64* values) final;

		void readArrayNdOfLongValues(
			const std::string& datasetName,
			LONG64* values,
			unsigned long long const* numValuesInEachDimension,
			unsigned long long const* offsetInEachDimension,
			unsigned int numDimensions) final;

		void readArrayNdOfULongValues(const std::string& datasetName, ULONG64* values) final;

		void readArrayNdOfIntValues(const std::string& datasetName, int* values) final;

		void readArrayNdOfIntValues(
			const std::string& datasetName,
			int* values,
			unsigned long long const* numValuesInEachDimension,
			unsigned long long const* offsetInEachDimension,
			unsigned int numDimensions
		) final;

		void readArrayNdOfUIntValues(const std::string& datasetName, unsigned int* values) final;

		void readArrayNdOfShortValues(const std::string& datasetName, short* values) final;

		void readArrayNdOfUShortValues(const std::string& datasetName, unsigned short* values) final;

		void readArrayNdOfCharValues(const std::string& datasetName, char* values) final;

		void readArrayNdOfUCharValues(const std::string& datasetName, unsigned char* values) final;

		std::vector<unsigned long long> readArrayDimensions(const std::string& datasetName) final;

		bool exist(const std::string& absolutePathInHdfFile) const final;

		bool isCompressed(const std::string& datasetName) final;

	protected:

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		HdfProxy(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap) :
			AbstractHdfProxy(fromGsoap), hdfFile(-1), compressionLevel(0), openedGroups() {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		HdfProxy(gsoap_eml2_1::_eml21__EpcExternalPartReference* fromGsoap) :
			AbstractHdfProxy(fromGsoap), hdfFile(-1), compressionLevel(0), openedGroups() {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		HdfProxy(gsoap_eml2_3::_eml23__EpcExternalPartReference* fromGsoap) :
			AbstractHdfProxy(fromGsoap), hdfFile(-1), compressionLevel(0), openedGroups() {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 * @packageDirAbsolutePath	The directory where the EPC document is stored. Must end with a slash
		 * or back-slash
		 * @relativeFilePath			The relative file path of the associated HDF file. It is relative to the
		 * location of the package
		 *
		 * @param 	packageDirAbsolutePath	Full pathname of the package dir absolute file.
		 * @param 	externalFilePath	  	Full pathname of the external file.
		 * @param 	hdfPermissionAccess   	(Optional) The hdf permission access.
		 */
		HdfProxy(const std::string & packageDirAbsolutePath, const std::string & externalFilePath, COMMON_NS::DataObjectRepository::openingMode hdfPermissionAccess = COMMON_NS::DataObjectRepository::openingMode::READ_ONLY);

		/**
		 * Read an nd array of values stored in a specific dataset.
		 *
		 * @param 		  	datasetName	The absolute dataset name where to read the values.
		 * @param [in,out]	values	   	The values must be pre-allocated.
		 * @param 		  	datatype   	The hdf datatype of the values to read. If the values are not
		 * 								stored in this particular datatype, then hdf library will try to
		 * 								do a conversion.
		 */
		void readArrayNdOfValues(const std::string& datasetName, void* values, hdf5_hid_t datatype);

		/**
		 * Find the array associated with @p datasetName and read a portion of it.
		 *
		 * @param 		  	datasetName					The name of the array (potentially with multi
		 * 												dimensions).
		 * @param [in,out]	values						1d array output of double values ordered firstly
		 * 												by fastest direction.
		 * @param 		  	numValuesInEachDimension	Number of values in each dimension of the array
		 * 												to read. They are ordered from fastest index to
		 * 												slowest index.
		 * @param 		  	offsetInEachDimension   	Offset values in each dimension of the array to
		 * 												read. They are ordered from fastest index to slowest
		 * 												index.
		 * @param 		  	numDimensions				The number of the dimensions of the array to read.
		 * @param 		  	datatype					The hdf datatype of the values to read. If the
		 * 												values are not stored in this particular datatype,
		 * 												then hdf library will try to do a conversion.
		 */
		void readArrayNdOfValues(
			const std::string& datasetName,
			void* values,
			unsigned long long const* numValuesInEachDimension,
			unsigned long long const* offsetInEachDimension,
			unsigned int numDimensions,
			hdf5_hid_t datatype);

		/**
		 * Find the array associated with @p datasetName and read from it.
		 *
		 * @param 		  	datasetName					The name of the array (potentially with multi
		 * 												dimensions).
		 * @param [in,out]	values						1d array output of values ordered firstly by
		 * 												fastest direction.
		 * @param 		  	blockCountPerDimension  	Number of blocks to select from the dataspace, in
		 * 												each dimension. They are ordered from fastest index
		 * 												to slowest index.
		 * @param 		  	offsetInEachDimension   	Offset values in each dimension of the array to
		 * 												read. They are ordered from fastest index to slowest
		 * 												index.
		 * @param 		  	strideInEachDimension   	Number of elements to move from one block to
		 * 												another in each dimension. They are ordered from
		 * 												fastest index to slowest index.
		 * @param 		  	blockSizeInEachDimension	Size of selected blocks in each dimension. They
		 * 												are ordered from fastest index to slowest index.
		 * @param 		  	numDimensions				The number of the dimensions of the array to read.
		 * @param 		  	datatype					The hdf datatype of the values to read. If the
		 * 												values are not stored in this particular datatype,
		 * 												then hdf library will try to do a conversion.
		 */
		void readArrayNdOfValues(
			const std::string& datasetName,
			void* values,
			unsigned long long const* blockCountPerDimension,
			unsigned long long const* offsetInEachDimension,
			unsigned long long const* strideInEachDimension,
			unsigned long long const* blockSizeInEachDimension,
			unsigned int numDimensions,
			hdf5_hid_t datatype);

		/**
		 * Considering a given dataset, read the double values corresponding to an existing selected
		 * region.
		 *
		 * @param 		  	dataset  	ID of the dataset to read from.
		 * @param 		  	filespace	ID of the selected region.
		 * @param [in,out]	values   	1d array output of double values ordered firstly by fastest
		 * 								direction.
		 * @param 		  	slabSize 	Number of values to read.
		 * @param 		  	datatype 	The hdf datatype of the values to read. If the values are not
		 * 								stored in this particular datatype, then hdf library will try to
		 * 								do a conversion.
		 */
		void readArrayNdOfValues(
			hdf5_hid_t dataset,
			hdf5_hid_t filespace,
			void* values,
			unsigned long long slabSize,
			hdf5_hid_t datatype);

		/**
		* Write the uuid of the XML EpcExternalPartReference as a string attribute of the HDF5 file.
		*/
		void writeUuidAttribute();

		/**
		 * Allows to force a root group for all newly created groups in inherited HDF proxies.
		 *
		 * @param 	rootGroup	Group the root belongs to.
		 *
		 * @returns	A hdf5_hid_t.
		 */
		virtual hdf5_hid_t openOrCreateRootGroup(const std::string& rootGroup);

		/**
		 * Checks if an HDF group named as groupName exists in the root group. If it exists, it returns
		 * the latter. If not, it creates this group and then returns it. Do not close opened or created
		 * HDF5 group. They are automatically managed by fesapi.
		 *
		 * @param 	rootSlashGroup	Name of the group.
		 *
		 * @returns	A hdf5_hid_t.
		 */
		hdf5_hid_t openOrCreateGroupInRootGroup(const std::string& rootSlashGroup);

		/** The hdf file */
		hdf5_hid_t hdfFile;

		/** The compression level */
		unsigned int compressionLevel;

		/** Groups the opened belongs to */
		std::unordered_map< std::string, hdf5_hid_t > openedGroups;
	};
}
