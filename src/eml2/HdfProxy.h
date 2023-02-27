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
		HdfProxy(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractHdfProxy(partialObject) {}

		/**
		 * @brief	Constructor
		 *
		 * @param 	dor	The dor.
		 */
		HdfProxy(const COMMON_NS::DataObjectReference& dor) : AbstractHdfProxy(dor) {}

		/** Destructor. Closes the hdf file. */
		virtual ~HdfProxy() { close(); }

		void open() override;

		DLL_IMPORT_OR_EXPORT bool isOpened() const final { return hdfFile != -1; }

		void close() final;

		COMMON_NS::AbstractObject::numericalDatatypeEnum getNumericalDatatype(const std::string& groupName) final;

		int getHdfDatatypeClassInDataset(const std::string& datasetName) final;

		void writeItemizedListOfList(const std::string& groupName,
			const std::string& name,
			COMMON_NS::AbstractObject::numericalDatatypeEnum cumulativeLengthDatatype,
			const void* cumulativeLength,
			uint64_t cumulativeLengthSize,
			COMMON_NS::AbstractObject::numericalDatatypeEnum elementsDatatype,
			const void* elements,
			uint64_t elementsSize) final;

		/**
		 * Get the number of elements in each dimension in an HDF dataset of the proxy.
		 * uint32_t is returned instead of uint64_t cause of some SWIG usage. I cannot SWIG port std::vector<uint64_t>
		 * @param datasetName	The absolute name of the dataset we want to get the number of elements.
		 */
		std::vector<uint32_t> getElementCountPerDimension(const std::string & datasetName) final;

		DLL_IMPORT_OR_EXPORT void setCompressionLevel(unsigned int newCompressionLevel) final {
			compressionLevel = newCompressionLevel > 9 ? 9 : newCompressionLevel;
		}

		void writeArrayNd(const std::string& groupName,
			const std::string& name,
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			const void* values,
			const uint64_t* numValuesInEachDimension,
			unsigned int numDimensions) final;

		void createArrayNd(
			const std::string& groupName,
			const std::string& name,
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			const uint64_t* numValuesInEachDimension,
			unsigned int numDimensions
		) final;

		void writeArrayNdSlab(
			const std::string& groupName,
			const std::string& name,
			COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
			const void* values,
			const uint64_t* numValuesInEachDimension,
			const uint64_t* offsetValuesInEachDimension,
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

		int64_t readInt64Attribute(const std::string& obj_name,
			const std::string& attr_name) const final;

		void readArrayNdOfDoubleValues(const std::string& datasetName, double* values) final;

		void readArrayNdOfDoubleValues(
			const std::string& datasetName,
			double* values,
			uint64_t const* numValuesInEachDimension,
			uint64_t const* offsetInEachDimension,
			unsigned int numDimensions
		) final;

		void readArrayNdOfDoubleValues(
			const std::string& datasetName, double* values,
			uint64_t const* blockCountPerDimension,
			uint64_t const* offsetInEachDimension,
			uint64_t const* strideInEachDimension,
			uint64_t const* blockSizeInEachDimension,
			unsigned int numDimensions) final;

		void selectArrayNdOfValues(
			const std::string& datasetName,
			uint64_t const* blockCountPerDimension,
			uint64_t const* offsetInEachDimension,
			uint64_t const* strideInEachDimension,
			uint64_t const* blockSizeInEachDimension,
			unsigned int numDimensions,
			bool newSelection,
			hdf5_hid_t& dataset,
			hdf5_hid_t& filespace) final;

		void readArrayNdOfDoubleValues(
			hdf5_hid_t dataset,
			hdf5_hid_t filespace,
			void* values,
			uint64_t slabSize) final;

		void readArrayNdOfFloatValues(const std::string& datasetName, float* values) final;

		void readArrayNdOfFloatValues(
			const std::string& datasetName,
			float* values,
			uint64_t const* numValuesInEachDimension,
			uint64_t const* offsetInEachDimension,
			unsigned int numDimensions
		) final;

		void readArrayNdOfInt64Values(const std::string& datasetName, int64_t* values) final;

		void readArrayNdOfInt64Values(
			const std::string& datasetName,
			int64_t* values,
			uint64_t const* numValuesInEachDimension,
			uint64_t const* offsetInEachDimension,
			unsigned int numDimensions) final;

		void readArrayNdOfUInt64Values(const std::string& datasetName, uint64_t* values) final;

		void readArrayNdOfIntValues(const std::string& datasetName, int* values) final;

		void readArrayNdOfIntValues(
			const std::string& datasetName,
			int* values,
			uint64_t const* numValuesInEachDimension,
			uint64_t const* offsetInEachDimension,
			unsigned int numDimensions
		) final;

		void readArrayNdOfUIntValues(const std::string& datasetName, unsigned int* values) final;

		void readArrayNdOfShortValues(const std::string& datasetName, short* values) final;

		void readArrayNdOfUShortValues(const std::string& datasetName, unsigned short* values) final;

		void readArrayNdOfInt8Values(const std::string& datasetName, int8_t* values) final;

		void readArrayNdOfUInt8Values(const std::string& datasetName, uint8_t* values) final;

		bool exist(const std::string& absolutePathInHdfFile) const final;

		bool isCompressed(const std::string& datasetName) final;

		std::vector<uint32_t> getElementCountPerChunkDimension(const std::string & datasetName) final;

	protected:

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		HdfProxy(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap) :
			AbstractHdfProxy(fromGsoap) {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		HdfProxy(gsoap_eml2_1::_eml21__EpcExternalPartReference* fromGsoap) :
			AbstractHdfProxy(fromGsoap) {}

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
			uint64_t const* numValuesInEachDimension,
			uint64_t const* offsetInEachDimension,
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
			uint64_t const* blockCountPerDimension,
			uint64_t const* offsetInEachDimension,
			uint64_t const* strideInEachDimension,
			uint64_t const* blockSizeInEachDimension,
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
			uint64_t slabSize,
			hdf5_hid_t datatype);

		/**
		* Write the uuid of the XML EpcExternalPartReference as a string attribute of the HDF5 file.
		*/
		void writeUuidAttribute();

		/**
		 * Checks if an HDF group named as groupName exists in the HDF5 file. If it exists, it returns
		 * the latter. If not, it creates this group and then returns it. Do not close opened or created
		 * HDF5 group. They are automatically managed by FESAPI.
		 *
		 * @param 	groupName	Name of the group. It must start with a slash.
		 *
		 * @returns	A hdf5_hid_t.
		 */
		hdf5_hid_t openOrCreateGroup(const std::string& groupName);

		/** The hdf file identifier */
		hdf5_hid_t hdfFile = -1;

		/** The compression level used for writing data */
		unsigned int compressionLevel = 0;

		/** Groups which are currently opened where key is their path and value is their identifier */
		std::unordered_map< std::string, hdf5_hid_t > openedGroups;
	};
}
