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

#include "common/EpcExternalPartReference.h"
#include "common/HidtType.h"

#define CUMULATIVE_LENGTH_DS_NAME "cumulativeLength"
#define ELEMENTS_DS_NAME "elements"

namespace COMMON_NS
{
	class AbstractHdfProxy : public EpcExternalPartReference
	{
	protected:

		std::string packageDirectoryAbsolutePath;												/// The directory where the EPC document is stored.
		std::string relativeFilePath;															/// Must be relative to the location of the package
		DataObjectRepository::openingMode openingMode;

		/**
		* @param soapContext	The soap context where the underlying gsoap proxy is going to be created.
		*/
		DLL_IMPORT_OR_EXPORT AbstractHdfProxy(const std::string & packageDirAbsolutePath, const std::string & externalFilePath, DataObjectRepository::openingMode hdfPermissionAccess = DataObjectRepository::READ_ONLY);

		DLL_IMPORT_OR_EXPORT AbstractHdfProxy(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap) :
			EpcExternalPartReference(fromGsoap), openingMode(DataObjectRepository::READ_ONLY) {}

		DLL_IMPORT_OR_EXPORT AbstractHdfProxy(gsoap_eml2_1::_eml21__EpcExternalPartReference* fromGsoap) :
			EpcExternalPartReference(fromGsoap), openingMode(DataObjectRepository::READ_ONLY) {}

		/**
		* Instantiate and initialize the gsoap proxy v2.0.1.
		* This method is defined in order to be used in derived class without having to link to generated gsoap files.
		*/
		DLL_IMPORT_OR_EXPORT void initGsoapProxy(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, EmlVersion emlVersion);

	public:  
		virtual ~AbstractHdfProxy() {}

		/**
		* Set the root of the path where to resolve relativeFilePath.
		* It must be the folder path containing the EPC file if this HDF5 file is associated to an EPC file.
		*/
		DLL_IMPORT_OR_EXPORT void setRootPath(const std::string& rootPath) { packageDirectoryAbsolutePath = rootPath; }

		/**
		* Set the relative path regarding packageDirectoryAbsolutePath where the HDF5 file is located.
		*/
		DLL_IMPORT_OR_EXPORT void setRelativePath(const std::string& relPath) { relativeFilePath = relPath; }

		/**
		* Set the rights when opening the HDF5 file.
		*/
		DLL_IMPORT_OR_EXPORT void setOpeningMode(DataObjectRepository::openingMode openingMode_) { openingMode = openingMode_; }

		/**
		* Get the relative path regarding packageDirectoryAbsolutePath where the HDF5 file is located.
		*/
		DLL_IMPORT_OR_EXPORT const std::string& getRelativePath() const { return relativeFilePath; }

		/**
		* Open the file for reading and writing.
		* The read/write access are determined by the EPC document configuration.
		*/
		virtual void open() = 0;

		/**
		 * Check if the Hdf file is open or not
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isOpened() const = 0;

		/**
		 * Close the file
		 */
		virtual void close() = 0;

		/**
		 * Get the used (native) datatype in a dataset
		* To compare with H5T_NATIVE_INT, H5T_NATIVE_UINT, H5T_NATIVE_FLOAT, etc...
		 */
		virtual hdf5_hid_t getHdfDatatypeInDataset(const std::string & datasetName) = 0;

		/**
		* Get the used datatype class in a dataset
		* To compare with H5T_INTEGER, H5T_FLOAT , H5T_STRING , etc...
		*/
		virtual int getHdfDatatypeClassInDataset(const std::string & datasetName) = 0;

		/**
		* Write an itemized list of list into the HDF file by means of a single group containing 2 datasets.
		* @param groupName					The name of the group where to create the itemized list of list.
		*									This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name						The name of the itemized list of list hdf group.
		* @param cumulativeLengthDatatype	The datatype of the cumulative length to write.
		* @param cumulativeLength			1d array of positive integers containing for each list the sum of all the previous list lengths including the current one
		* @param cumulativeLengthSize		Size of the cumulativeLength array.
		* @param elementsDatatype			The datatype of the elements to write.
		* @param elements					1d array of elements containing the aggregation of individual list content.
		* @param elementsSize				Size of the elements array.
		*/
		virtual void writeItemizedListOfList(const std::string & groupName,
			const std::string & name,
			hdf5_hid_t cumulativeLengthDatatype,
			const void * cumulativeLength,
			unsigned long long cumulativeLengthSize,
			hdf5_hid_t elementsDatatype,
			const void * elements,
			unsigned long long elementsSize) = 0;

		/**
		 * Get the number of dimensions in an HDF dataset of the proxy.
		 * @param datasetName	The absolute name of the dataset we want to get the number of dimensions.
		 */
		virtual unsigned int getDimensionCount(const std::string & datasetName) = 0;

		/**
		 * Get the number of elements in an HDF dataset of the proxy. The number of elements is get from all dimensions.
		 * @param datasetName	The absolute name of the dataset we want to get the number of elements.
		 */
		virtual signed long long getElementCount(const std::string & datasetName) = 0;

		/**
		 * Set the new compression level which will be used for all data to be written
		 * @param compressionLevel				Lower compression levels are faster but result in less compression. Range [0..9] is allowed.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setCompressionLevel(unsigned int newCompressionLevel) = 0;

		virtual void writeArrayNdOfFloatValues(const std::string & groupName,
		  const std::string & name,
		  const float * floatValues,
		  const unsigned long long * numValuesInEachDimension,
		  unsigned int numDimensions) = 0;

		/**
		 * Write an array (potentially with multi dimensions) of double values into the HDF file by means of a single dataset.
		 * @param groupName						The name of the group where to create the array of double values.
		 *										This name must not contain '/' character and must be directly contained in RESQML group.
		 * @param name							The name of the array of double values hdf dataset. It must not already exist.
		 * @param dblValues						1d array of double values ordered firstly by fastest direction.
		 * @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		 * @param numDimensions					The number of the dimensions of the array to write
		 */
		virtual void writeArrayNdOfDoubleValues(const std::string & groupName,
		  const std::string & name,
		  const double * dblValues,
		  const unsigned long long * numValuesInEachDimension,
		  unsigned int numDimensions) = 0;

		/**
		* Write an array (potentially with multi dimensions) of char values into the HDF file by means of a single dataset.
		* @param groupName						The name of the group where to create the array of int values.
		*										This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name							The name of the array of int values hdf dataset. It must not already exist.
		* @param intValues						1d array of char values ordered firstly by fastest direction.
		* @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param numDimensions					The number of the dimensions of the array to write
		*/
		virtual void writeArrayNdOfCharValues(const std::string & groupName,
			const std::string & name,
			const char * intValues,
			const unsigned long long * numValuesInEachDimension,
			unsigned int numDimensions) = 0;

		/**
		 * Write an array (potentially with multi dimensions) of int values into the HDF file by means of a single dataset.
		 * @param groupName						The name of the group where to create the array of int values.
		 *										This name must not contain '/' character and must be directly contained in RESQML group.
		 * @param name							The name of the array of int values hdf dataset. It must not already exist.
		 * @param intValues						1d array of int values ordered firstly by fastest direction.
		 * @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		 * @param numDimensions					The number of the dimensions of the array to write
		 */
		virtual void writeArrayNdOfIntValues(const std::string & groupName,
		  const std::string & name,
		  const int * intValues,
		  const unsigned long long * numValuesInEachDimension,
		  unsigned int numDimensions) = 0;

		/**
		* Write an array (potentially with multi dimensions) of gSoap unsigned long 64 values into the HDF file by means of a single dataset.
		* @param groupName						The name of the group where to create the array of int values.
		*										This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name							The name of the array of gSoap unsigned long 64 values hdf dataset. It must not already exist.
		* @param ulong64Values					1d array of gSoap unsigned long 64 values ordered firstly by fastest direction.
		* @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param numDimensions					The number of the dimensions of the array to write
		*/
 		virtual void writeArrayNdOfGSoapULong64Values(const std::string & groupName,
			const std::string & name,
			const ULONG64 * ulong64Values,
			const unsigned long long * numValuesInEachDimension,
			unsigned int numDimensions) = 0;

		/**
		 * Write an array (potentially with multi dimensions) of a specific datatype into the HDF file by means of a single dataset.
		 * @param groupName						The name of the group where to create the array of values.
		 *										This name must not contain '/' character and must be directly contained in RESQML group.
		 * @param name							The name of the array (potentially with multi dimensions) of a specific datatype hdf dataset. It must not already exist.
		 * @param datatype						The specific datatype of the valeus to write.
		 * @param values							1d array of specific datatype ordered firstly by fastest direction.
		 * @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		 * @param numDimensions					The number of the dimensions of the array to write
		 */
		virtual void writeArrayNd(const std::string & groupName,
		  const std::string & name,
		  hdf5_hid_t datatype,
		  const void * values,
		  const unsigned long long * numValuesInEachDimension,
		  unsigned int numDimensions) = 0;

		/**
		 * Create an array (potentially with multi dimensions) of a specific datatype into the HDF file. Values are not yet written to this array.
		 * @param groupName                      The name of the group where to create the array of double values.
		 *                                       This name must not contain '/' character and must be directly contained in RESQML group.
		 * @param name                           The name of the array (potentially with multi dimensions) of a specific datatype hdf dataset. It must not exist.
		 * @param datatype                       The specific datatype of the values to write.
		 * @param numValuesInEachDimension       Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		 * @param numDimensions                  The number of the dimensions of the array to write.
		 */
		virtual void createArrayNd(
		  const std::string& groupName,
		  const std::string& name,
		  hdf5_hid_t datatype,
		  const unsigned long long* numValuesInEachDimension,
		  unsigned int numDimensions
		  ) = 0;

		/**
		 * Find the array associated with @p groupName and @p name and write to it.
		 * @param groupName                      The name of the group associated with the array.
		 * @param name                           The name of the array (potentially with multi dimensions).
		 * @param values                         1d array of specific datatype ordered firstly by fastest direction.
		 * @param numValuesInEachDimension       Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		 * @param offsetValuesInEachDimension    Offset values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		 * @param numDimensions                  The number of the dimensions of the array to write.
		 */
		virtual void writeArrayNdSlab(
		  const std::string& groupName,
		  const std::string& name,
		  hdf5_hid_t datatype,
		  const void* values,
		  const unsigned long long* numValuesInEachDimension,
		  const unsigned long long* offsetValuesInEachDimension,
		  unsigned int numDimensions
		  ) = 0;

		/**
		* Write some string attributes into a group
		*/
		virtual void writeGroupAttributes(const std::string & groupName,
			const std::vector<std::string> & attributeNames,
			const std::vector<std::string> & values) = 0;

		/**
		* Write a single attribute which contain an array of strings
		*/
		virtual void writeGroupAttribute(const std::string & groupName,
			const std::string & attributeName,
			const std::vector<std::string> & values) = 0;

		/**
		* Write some double attributes into a group
		*/
		virtual void writeGroupAttributes(const std::string & groupName,
			const std::vector<std::string> & attributeNames,
			const std::vector<double> & values) = 0;

		/**
		* Write some int attributes into a group
		*/
		virtual void writeGroupAttributes(const std::string & groupName,
			const std::vector<std::string> & attributeNames,
			const std::vector<int> & values) = 0;

		/**
		* Write some string attributes into a dataset
		*/
		virtual void writeDatasetAttributes(const std::string & datasetName,
			const std::vector<std::string> & attributeNames,
			const std::vector<std::string> & values) = 0;

		/**
		* Write a single attribute which contain an array of strings
		*/
		virtual void writeDatasetAttribute(const std::string & datasetName,
			const std::string & attributeName,
			const std::vector<std::string> & values) = 0;

		/**
		* Write some double attributes into a dataset
		*/
		virtual void writeDatasetAttributes(const std::string & datasetName,
			const std::vector<std::string> & attributeNames,
			const std::vector<double> & values) = 0;

		/**
		* Write some int attributes into a dataset
		*/
		virtual void writeDatasetAttributes(const std::string & datasetName,
			const std::vector<std::string> & attributeNames,
			const std::vector<int> & values) = 0;

		/**
		* Read a string which is stored as an HDF attribute in a file, group or dataset
		* @param obj_name use '.' if the attribute to read is on the file otherwise the full path
		*/
		virtual std::string readStringAttribute(const std::string & obj_name,
			const std::string & attr_name) const = 0;

		virtual std::vector<std::string> readStringArrayAttribute(const std::string & obj_name,
			const std::string & attr_name) const = 0;

		/**
		* Read a double which is stored as an HDF attribute in a file, group or dataset
		* @param obj_name use '.' if the attribute to read is on the file otherwise the full path
		*/
		virtual double readDoubleAttribute(const std::string & obj_name,
			const std::string & attr_name) const = 0;

		/**
		* Read a long which is stored as an HDF attribute in a file, group or dataset
		* @param obj_name use '.' if the attribute to read is on the file otherwise the full path
		*/
		virtual LONG64 readLongAttribute(const std::string & obj_name,
			const std::string & attr_name) const = 0;

		/**
		 * Read an array Nd of double values stored in a specific dataset
		 * @param datasetName	The absolute dataset name where to read the values
		 * @param values 		The values must be pre-allocated and won't be freed by this method.
		 */
		virtual void readArrayNdOfDoubleValues(const std::string & datasetName, double* values) = 0;

		/**
		 * Find the array associated with @p datasetName and read from it.
		 * @param datasetName                    The name of the array (potentially with multi dimensions).
		 * @param values                         1d array output of double values ordered firstly by fastest direction. The values must be pre-allocated and won't be freed by this method.
		 * @param numValuesInEachDimension       Number of values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		 * @param offsetValuesInEachDimension    Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		 * @param numDimensions                  The number of the dimensions of the array to read.
		 */
		virtual void readArrayNdOfDoubleValues(
		  const std::string & datasetName,
		  double* values,
		  unsigned long long const * numValuesInEachDimension,
		  unsigned long long const * offsetInEachDimension,
		  unsigned int numDimensions
		  ) = 0;

		/**
		 * Find the array associated with @p datasetName and read from it.
		 * @param datasetName					The name of the array (potentially with multi dimensions).
		 * @param values						1d array output of double values ordered firstly by fastest direction. The values must be pre-allocated and won't be freed by this method.
		 * @param blockCountPerDimension		Number of blocks to select from the dataspace, in each dimension. They are ordered from fastest index to slowest index.
		 * @param offsetInEachDimension			Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		 * @param strideInEachDimension			Number of elements to move from one block to another in each dimension. They are ordered from fastest index to slowest index.
		 * @param blockSizeInEachDimension		Size of selected blocks in each dimension. They are ordered from fastest index to slowest index.
		 * @param numDimensions					The number of the dimensions of the array to read.
		 */
		virtual void readArrayNdOfDoubleValues(
			const std::string & datasetName, 
			double* values,
			unsigned long long const * blockCountPerDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned long long const * strideInEachDimension,
			unsigned long long const * blockSizeInEachDimension,
			unsigned int numDimensions) = 0;

		/**
		 * Considering a given dataset, this method selects an hyperslab region to add to an existing selected region or to add to a new selected region.
		 * The dataset is not closed within this method.
		 * @param datasetName					The name of the array (potentially with multi dimensions).
		 * @param blockCountPerDimension		Number of blocks to select from the dataspace, in each dimension. They are ordered from fastest index to slowest index.
		 * @param offsetInEachDimension			Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		 * @param strideInEachDimension			Number of elements to move from one block to another in each dimension. They are ordered from fastest index to slowest index.
		 * @param blockSizeInEachDimension		Size of selected blocks in each dimension. They are ordered from fastest index to slowest index.
		 * @param numDimensions					The number of the dimensions of the array to read.
		 * @param newSelection					true if creating a new selected region else false.
		 * @param dataset						Input dataset ID if adding a new hyperslab region to an existing selected region, output dataset ID if creating a new selected region.
		 * @param filespace						Input selected region ID if adding a new hyperslab region to an existing selected region, output selected region ID if creating a new selected region.
		 */
		virtual void selectArrayNdOfValues(
			const std::string & datasetName,
			unsigned long long const* blockCountPerDimension,
			unsigned long long const* offsetInEachDimension,
			unsigned long long const* strideInEachDimension,
			unsigned long long const* blockSizeInEachDimension,
			unsigned int numDimensions,
			bool newSelection,
			hdf5_hid_t & dataset,
			hdf5_hid_t & filespace) = 0;

		/**
		 * Considering a given dataset, read the double values corresponding to an existing selected region. 
		 * @param dataset		ID of the dataset to read from.
		 * @param filespace		ID of the selected region.
		 * @param values		1d array output of double values ordered firstly by fastest direction. The values must be pre-allocated and won't be freed by this method.
		 * @param slabSize		Number of values to read.
		 */
		virtual void readArrayNdOfDoubleValues(
			hdf5_hid_t dataset,
			hdf5_hid_t filespace,
			void* values,
			unsigned long long slabSize) = 0;

		/**
		 * Read an array Nd of float values stored in a specific dataset.
		 * @param datasetName	The absolute dataset name where to read the values
		 * @param values 		The values must be pre-allocated.
		 */
		virtual void readArrayNdOfFloatValues(const std::string & datasetName, float* values) = 0;

		/**
		 * Find the array associated with @p datasetName and read from it.
		 * @param datasetName                    The name of the array (potentially with multi dimensions).
		 * @param values                         1d array output of float values ordered firstly by fastest direction. The values must be pre-allocated and won't be freed by this method.
		 * @param numValuesInEachDimension       Number of values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		 * @param offsetValuesInEachDimension    Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		 * @param numDimensions                  The number of the dimensions of the array to read.
		 */
		virtual void readArrayNdOfFloatValues(
		  const std::string & datasetName,
		  float* values,
		  unsigned long long const * numValuesInEachDimension,
		  unsigned long long const * offsetInEachDimension,
		  unsigned int numDimensions
		  ) = 0;

		/**
		 * Read an array Nd of long values stored in a specific dataset.
		 * @param datasetName	The absolute dataset name where to read the values
		 * @param values 		The values must be pre-allocated and won't be freed by this method.
		 */
		virtual void readArrayNdOfLongValues(const std::string & datasetName, LONG64* values) = 0;

		/**
		 * Find the array associated with datasetName and read from it.
		 * @param datasetName                    The name of the array (potentially with multi dimensions).
		 * @param values                         1d array output of long values ordered firstly by fastest direction. The values must be pre-allocated and won't be freed by this method.
		 * @param numValuesInEachDimension       Number of values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		 * @param offsetValuesInEachDimension    Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		 * @param numDimensions                  The number of the dimensions of the array to read.
		 */
		virtual void readArrayNdOfLongValues(
			const std::string & datasetName,
			LONG64* values,
			unsigned long long const * numValuesInEachDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned int numDimensions) = 0;

		/**
		 * Read an array Nd of unsigned long values stored in a specific dataset.
		 * @param datasetName	The absolute dataset name where to read the values
		 * @param values 		The values must be pre-allocated and won't be freed by this method.
		 */
		virtual void readArrayNdOfULongValues(const std::string & datasetName, ULONG64* values) = 0;

		/**
		 * Read an array Nd of int values stored in a specific dataset.
		 * @param datasetName	The absolute dataset name where to read the values
		 * @param values 		The values must be pre-allocated and won't be freed by this method.
		 */
		virtual void readArrayNdOfIntValues(const std::string & datasetName, int* values) = 0;

		/**
		* Find the array associated with datasetName and read from it.
		* @param datasetName                    The name of the array (potentially with multi dimensions).
		* @param values                         1d array output of int values ordered firstly by fastest direction. The values must be pre-allocated and won't be freed by this method.
		* @param numValuesInEachDimension       Number of values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param offsetValuesInEachDimension    Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param numDimensions                  The number of the dimensions of the array to read.
		*/
		virtual void readArrayNdOfIntValues(
			const std::string & datasetName,
			int* values,
			unsigned long long const * numValuesInEachDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned int numDimensions
		) = 0;

		/**
		 * Read an array Nd of unsigned int values stored in a specific dataset
		 * Don't forget to delete the allocated pointer when no more necessary.
		 * @param datasetName	The absolute dataset name where to read the values
		 * @param values 		The values must be pre-allocated and won't be freed by this method.
		 */
		virtual void readArrayNdOfUIntValues(const std::string & datasetName, unsigned int* values) = 0;

		/**
		 * Read an array Nd of short values stored in a specific dataset
		 * Don't forget to delete the allocated pointer when no more necessary.
		 * @param datasetName	The absolute dataset name where to read the values
		 * @param values 		The values must be pre-allocated and won't be freed by this method.
		 */
		virtual void readArrayNdOfShortValues(const std::string & datasetName, short* values) = 0;

		/**
		 * Read an array Nd of unsigned short values stored in a specific dataset.
		 * @param datasetName	The absolute dataset name where to read the values
		 * @param values 		The values must be pre-allocated and won't be freed by this method.
		 */
		virtual void readArrayNdOfUShortValues(const std::string & datasetName, unsigned short* values) = 0;

		/**
		 * Read an array Nd of char values stored in a specific dataset.
		 * @param datasetName	The absolute dataset name where to read the values
		 * @param values 		The values must be pre-allocated and won't be freed by this method.
		 */
		virtual void readArrayNdOfCharValues(const std::string & datasetName, char* values) = 0;

		/**
		 * Read an array Nd of unsigned char values stored in a specific dataset.
		 * @param datasetName	The absolute dataset name where to read the values
		 * @param values 		The values must be pre-allocated and won't be freed by this method.
		 */
		virtual void readArrayNdOfUCharValues(const std::string & datasetName, unsigned char* values) = 0;

		/**
		 * Read the dimensions of an array stored in a specific dataset
		 * @param datasetName	The absolute dataset name where to read the array dimensions
		 */
		virtual std::vector<unsigned long long> readArrayDimensions(const std::string & datasetName) = 0;

		/**
		* Check wether an absolute path exists in the hdf file or not.
		*/
		virtual bool exist(const std::string & absolutePathInHdfFile) const = 0;

		/**
		* Check wether a dataset is compressed or not.
		*/
		virtual bool isCompressed(const std::string & datasetName) = 0;
	};
}
