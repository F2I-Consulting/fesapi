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

namespace COMMON_NS
{
	class HdfProxy : public AbstractHdfProxy
	{
	protected:

		HdfProxy(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap) :
			COMMON_NS::AbstractHdfProxy(fromGsoap), hdfFile(-1), compressionLevel(0), openedGroups() {}

		HdfProxy(gsoap_eml2_1::_eml21__EpcExternalPartReference* fromGsoap) :
			COMMON_NS::AbstractHdfProxy(fromGsoap), hdfFile(-1), compressionLevel(0), openedGroups() {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @packageDirAbsolutePath	The directory where the EPC document is stored. Must end with a slash or back-slash
		* @relativeFilePath			The relative file path of the associated HDF file. It is relative to the location of the package
		*/
		HdfProxy(const std::string & packageDirAbsolutePath, const std::string & externalFilePath, DataObjectRepository::openingMode hdfPermissionAccess = DataObjectRepository::READ_ONLY);

		/**
		* Read an array Nd of float values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated.
		* @param datatype 		The hdf datatype of the values to read.
		* 						If the values are not stored in this particular datatype, then hdf library will try to do a conversion.
		*/
		void readArrayNdOfValues(const std::string & datasetName, void* values, hdf5_hid_t datatype);

		/**
		* Find the array associated with @p datasetName and read a portion of it.
		* @param datasetName                    The name of the array (potentially with multi dimensions).
		* @param values                         1d array output of double values ordered firstly by fastest direction.
		* @param numValuesInEachDimension       Number of values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param offsetValuesInEachDimension    Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param numDimensions                  The number of the dimensions of the array to read.
		* @param datatype 		The hdf datatype of the values to read.
		* 						If the values are not stored in this particular datatype, then hdf library will try to do a conversion.
		*/
		void readArrayNdOfValues(
			const std::string & datasetName,
			void* values,
			unsigned long long const * numValuesInEachDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned int numDimensions,
			hdf5_hid_t datatype);

		/**
		* Find the array associated with @p datasetName and read from it.
		* @param datasetName					The name of the array (potentially with multi dimensions).
		* @param values							1d array output of values ordered firstly by fastest direction.
		* @param blockCountPerDimension			Number of blocks to select from the dataspace, in each dimension. They are ordered from fastest index to slowest index.
		* @param offsetInEachDimension			Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param strideInEachDimension			Number of elements to move from one block to another in each dimension. They are ordered from fastest index to slowest index.
		* @param blockSizeInEachDimension		Size of selected blocks in each dimension. They are ordered from fastest index to slowest index.
		* @param numDimensions					The number of the dimensions of the array to read.
		* @param datatype 						The hdf datatype of the values to read.
		* 										If the values are not stored in this particular datatype, then hdf library will try to do a conversion.
		*/
		void readArrayNdOfValues(
			const std::string & datasetName,
			void* values,
			unsigned long long const * blockCountPerDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned long long const * strideInEachDimension,
			unsigned long long const * blockSizeInEachDimension,
			unsigned int numDimensions,
			hdf5_hid_t datatype);

		/**
		* Considering a given dataset, this method selects an hyperslab region to add to an existing selected region or to add to a new selected region.
		* The dataset is not closed within this method.
		* @param datasetName					The name of the array (potentially with multi dimensions).
		* @param blockCountPerDimension			Number of blocks to select from the dataspace, in each dimension. They are ordered from fastest index to slowest index.
		* @param offsetInEachDimension			Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param strideInEachDimension			Number of elements to move from one block to another in each dimension. They are ordered from fastest index to slowest index.
		* @param blockSizeInEachDimension		Size of selected blocks in each dimension. They are ordered from fastest index to slowest index.
		* @param numDimensions					The number of the dimensions of the array to select.
		* @param newSelection					true if creating a new selected region else false.
		* @param dataset						Input dataset ID if adding a new hyperslab region to an existing selected region, output dataset ID if creating a new selected region.
		* @param filespace						Input selected region ID if adding a new hyperslab region to an existing selected region, output selected region ID if creating a new selected region.
		*/
		void selectArrayNdOfValues(
			const std::string & datasetName,
			unsigned long long const * blockCountPerDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned long long const * strideInEachDimension,
			unsigned long long const * blockSizeInEachDimension,
			unsigned int numDimensions,
			bool newSelection,
			hdf5_hid_t & dataset,
			hdf5_hid_t & filespace);

		/**
		* Considering a given dataset, read the double values corresponding to an existing selected region.
		* @param dataset		ID of the dataset to read from.
		* @param filespace		ID of the selected region.
		* @param values			1d array output of double values ordered firstly by fastest direction.
		* @param slabSize		Number of values to read.
		* @param datatype 		The hdf datatype of the values to read.
		* 						If the values are not stored in this particular datatype, then hdf library will try to do a conversion.
		*/
		void readArrayNdOfValues(
			hdf5_hid_t dataset,
			hdf5_hid_t filespace,
			void* values, 
			unsigned long long slabSize, 
			hdf5_hid_t datatype);

	public:

		/**
		* Only to be used in partial transfer context
		*/
		HdfProxy(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractHdfProxy(partialObject), hdfFile(-1), compressionLevel(0) {}

		/**
		* Destructor.
		* Close the hdf file.
		*/
		virtual ~HdfProxy() {close();}

		/**
		* Open the file for reading and writing.
		* Does never overwrite an existing file but append to it if it already exists.
		*/
		void open();

		/**
		* Check if the Hdf file is open or not
		*/
		DLL_IMPORT_OR_EXPORT bool isOpened() const {return hdfFile != -1;}

		/**
		* Close the file
		*/
		void close();

		/*
		* Get the used (native) datatype in a dataset
		* To compare with H5T_NATIVE_INT, H5T_NATIVE_UINT, H5T_NATIVE_FLOAT, etc...
		*/
		hdf5_hid_t getHdfDatatypeInDataset(const std::string & groupName);

		/**
		* Get the used datatype class in a dataset
		* To compare with H5T_INTEGER, H5T_FLOAT , H5T_STRING , etc...
		*/
		int getHdfDatatypeClassInDataset(const std::string & datasetName);
		
		/**
		* Write an itemized list of list into the HDF file by means of a single group containing 2 datasets.
		* @param groupName				The name of the group where to create the itemized list of list.
		*								This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name					The name of the itemized list of list hdf group.
		* @param cumulativeLengthDatatype	The datatype of the cumulative length to write.
		* @param cumulativeLength			1d array of positive integers containing for each list the sum of all the previous list lengths including the current one
		* @param cumulativeLengthSize		Size of the cumulativeLength array.
		* @param elementsDatatype			The datatype of the elements to write.
		* @param elements					1d array of elements containing the aggregation of individual list content.
		* @param elementsSize				Size of the elements array.
		*/
		void writeItemizedListOfList(const std::string & groupName,
			const std::string & name,
			hdf5_hid_t cumulativeLengthDatatype,
			const void * cumulativeLength,
			unsigned long long cumulativeLengthSize,
			hdf5_hid_t elementsDatatype,
			const void * elements,
			unsigned long long elementsSize);

		/**
		* Get the number of dimensions in an HDF dataset of the proxy.
		* @param datasetName	The absolute name of the dataset we want to get the number of dimensions.
		*/
		unsigned int getDimensionCount(const std::string & datasetName);

		/**
		* Get the number of elements in an HDF dataset of the proxy. The number of elements is get from all dimensions.
		* @param datasetName	The absolute name of the dataset we want to get the number of elements.
		*/
		signed long long getElementCount(const std::string & datasetName);

		/**
		* Set the new compression level which will be used for all data to be written
		* @param compressionLevel				Lower compression levels are faster but result in less compression. Range [0..9] is allowed.
		*/
		DLL_IMPORT_OR_EXPORT void setCompressionLevel(unsigned int newCompressionLevel) {
			compressionLevel = newCompressionLevel > 9 ? 9 : newCompressionLevel;
		}

		void writeArrayNdOfFloatValues(const std::string & groupName,
			const std::string & name,
			const float * floatValues,
			const unsigned long long * numValuesInEachDimension,
			unsigned int numDimensions);

		/**
		* Write an array (potentially with multi dimensions) of double values into the HDF file by means of a single dataset.
		* @param groupName						The name of the group where to create the array of double values.
		*										This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name							The name of the array of double values hdf dataset. It must not already exist.
		* @param dblValues						1d array of double values ordered firstly by fastest direction.
		* @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param numDimensions					The number of the dimensions of the array to write
		*/
		void writeArrayNdOfDoubleValues(const std::string & groupName,
			const std::string & name,
			const double * dblValues,
			const unsigned long long * numValuesInEachDimension,
			unsigned int numDimensions);

		/**
		* Write an array (potentially with multi dimensions) of char values into the HDF file by means of a single dataset.
		* @param groupName						The name of the group where to create the array of int values.
		*										This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name							The name of the array of int values hdf dataset. It must not already exist.
		* @param intValues						1d array of char values ordered firstly by fastest direction.
		* @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param numDimensions					The number of the dimensions of the array to write
		*/
		void writeArrayNdOfCharValues(const std::string & groupName,
			const std::string & name,
			const char * intValues,
			const unsigned long long * numValuesInEachDimension,
			unsigned int numDimensions);

		/**
		* Write an array (potentially with multi dimensions) of int values into the HDF file by means of a single dataset.
		* @param groupName						The name of the group where to create the array of int values.
		*										This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name							The name of the array of int values hdf dataset. It must not already exist.
		* @param intValues						1d array of int values ordered firstly by fastest direction.
		* @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param numDimensions					The number of the dimensions of the array to write
		*/
		void writeArrayNdOfIntValues(const std::string & groupName,
			const std::string & name,
			const int * intValues,
			const unsigned long long * numValuesInEachDimension,
			unsigned int numDimensions);

		/**
		* Write an array (potentially with multi dimensions) of gSoap unsigned long 64 values into the HDF file by means of a single dataset.
		* @param groupName						The name of the group where to create the array of int values.
		*										This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name							The name of the array of gSoap unsigned long 64 values hdf dataset. It must not already exist.
		* @param ulong64Values					1d array of gSoap unsigned long 64 values ordered firstly by fastest direction.
		* @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param numDimensions					The number of the dimensions of the array to write
		*/
		void writeArrayNdOfGSoapULong64Values(const std::string & groupName,
			const std::string & name,
			const ULONG64 * ulong64Values,
			const unsigned long long * numValuesInEachDimension,
			unsigned int numDimensions);

		/**
		* Write an array (potentially with multi dimensions) of a specific datatype into the HDF file by means of a single dataset.
		* @param groupName						The name of the group where to create the array of values.
		*										This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name							The name of the array (potentially with multi dimensions) of a specific datatype hdf dataset. It must not already exist.
		* @param datatype						The specific datatype of the values to write.
		* @param values							1d array of specific datatype ordered firstly by fastest direction.
		* @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param numDimensions					The number of the dimensions of the array to write
		*/
		void writeArrayNd(const std::string & groupName,
			const std::string & name,
			hdf5_hid_t datatype,
			const void * values,
			const unsigned long long * numValuesInEachDimension,
			unsigned int numDimensions);

		/**
		* Create an array (potentially with multi dimensions) of a specific datatype into the HDF file. Values are not yet written to this array.
		* @param groupName                      The name of the group where to create the array of double values.
		*                                       This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name                           The name of the array (potentially with multi dimensions) of a specific datatype hdf dataset. It must not exist.
		* @param datatype                       The specific datatype of the values to write.
		* @param numValuesInEachDimension       Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param numDimensions                  The number of the dimensions of the array to write.
		*/
		void createArrayNd(
			const std::string& groupName,
			const std::string& name,
			hdf5_hid_t datatype,
			const unsigned long long* numValuesInEachDimension,
			unsigned int numDimensions
		);

		/**
		* Find the array associated with @p groupName and @p name and write to it.
		* @param groupName                      The name of the group associated with the array.
		* @param name                           The name of the array (potentially with multi dimensions).
		* @param datatype						The specific datatype of the values to write.
		* @param values                         1d array of specific datatype ordered firstly by fastest direction.
		* @param numValuesInEachDimension       Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param offsetValuesInEachDimension    Offset values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param numDimensions                  The number of the dimensions of the array to write.
		*/
		void writeArrayNdSlab(
			const std::string& groupName,
			const std::string& name,
			hdf5_hid_t datatype,
			const void* values,
			const unsigned long long* numValuesInEachDimension,
			const unsigned long long* offsetValuesInEachDimension,
			unsigned int numDimensions
		);

		/**
		* Write some string attributes into a group
		*/
		void writeGroupAttributes(const std::string & groupName,
			const std::vector<std::string> & attributeNames,
			const std::vector<std::string> & values);

		/**
		* Write a single attribute which contain an array of strings
		*/
		void writeGroupAttribute(const std::string & groupName,
			const std::string & attributeName,
			const std::vector<std::string> & values);

		/**
		* Write some double attributes into a group
		*/
		void writeGroupAttributes(const std::string & groupName,
			const std::vector<std::string> & attributeNames,
			const std::vector<double> & values);

		/**
		* Write some int attributes into a group
		*/
		void writeGroupAttributes(const std::string & groupName,
			const std::vector<std::string> & attributeNames,
			const std::vector<int> & values);

		/**
		* Write some string attributes into a dataset
		*/
		void writeDatasetAttributes(const std::string & datasetName,
			const std::vector<std::string> & attributeNames,
			const std::vector<std::string> & values);

		/**
		* Write a single attribute which contain an array of strings
		*/
		void writeDatasetAttribute(const std::string & datasetName,
			const std::string & attributeName,
			const std::vector<std::string> & values);

		/**
		* Write some double attributes into a dataset
		*/
		void writeDatasetAttributes(const std::string & datasetName,
			const std::vector<std::string> & attributeNames,
			const std::vector<double> & values);

		/**
		* Write some int attributes into a dataset
		*/
		void writeDatasetAttributes(const std::string & datasetName,
			const std::vector<std::string> & attributeNames,
			const std::vector<int> & values);

		std::string readStringAttribute(const std::string & obj_name,
			const std::string & attr_name) const;

		std::vector<std::string> readStringArrayAttribute(const std::string & obj_name,
			const std::string & attr_name) const;

		double readDoubleAttribute(const std::string & obj_name,
			const std::string & attr_name) const;

		LONG64 readLongAttribute(const std::string & obj_name,
			const std::string & attr_name) const;

		/**
		* Read an array Nd of double values stored in a specific dataset
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated and won't be freed by this method.
		*/
		void readArrayNdOfDoubleValues(const std::string & datasetName, double* values);

		/**
		 * Find the array associated with @p datasetName and read from it.
		 * @param datasetName                    The name of the array (potentially with multi dimensions).
		 * @param values                         1d array output of double values ordered firstly by fastest direction. The values must be pre-allocated and won't be freed by this method.
		 * @param numValuesInEachDimension       Number of values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		 * @param offsetValuesInEachDimension    Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		 * @param numDimensions                  The number of the dimensions of the array to read.
		 */
		void readArrayNdOfDoubleValues(
		  const std::string & datasetName,
		  double* values,
		  unsigned long long const * numValuesInEachDimension,
		  unsigned long long const * offsetInEachDimension,
		  unsigned int numDimensions
		  );

		/**
		* Find the array associated with @p datasetName and read from it.
		* @param datasetName					The name of the array (potentially with multi dimensions).
		* @param values							1d array output of double values ordered firstly by fastest direction.
		* @param blockCountPerDimension			Number of blocks to select from the dataspace, in each dimension. They are ordered from fastest index to slowest index.
		* @param offsetInEachDimension			Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param strideInEachDimension			Number of elements to move from one block to another in each dimension. They are ordered from fastest index to slowest index.
		* @param blockSizeInEachDimension		Size of selected blocks in each dimension. They are ordered from fastest index to slowest index.
		* @param numDimensions					The number of the dimensions of the array to read.
		*/
		void readArrayNdOfDoubleValues(
			const std::string & datasetName, double* values,
			unsigned long long const * blockCountPerDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned long long const * strideInEachDimension,
			unsigned long long const * blockSizeInEachDimension,
			unsigned int numDimensions);

		/**
		* Considering a given dataset, read the double values corresponding to an existing selected region.
		* @param dataset		ID of the dataset to read from.
		* @param filespace		ID of the selected region.
		* @param values			1d array output of double values ordered firstly by fastest direction. The values must be pre-allocated and won't be freed by this method.
		* @param slabSize		Number of values to read.
		*/
		void readArrayNdOfDoubleValues(
			hdf5_hid_t dataset,
			hdf5_hid_t filespace,
			void* values,
			unsigned long long slabSize);

		/**
		* Read an array Nd of float values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated and won't be freed by this method.
		*/
		void readArrayNdOfFloatValues(const std::string & datasetName, float* values);

		/**
		* Find the array associated with @p datasetName and read from it.
		* @param datasetName                    The name of the array (potentially with multi dimensions).
		* @param values                         1d array output of float values ordered firstly by fastest direction. The values must be pre-allocated and won't be freed by this method.
		* @param numValuesInEachDimension       Number of values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param offsetValuesInEachDimension    Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param numDimensions                  The number of the dimensions of the array to read.
		*/
		void readArrayNdOfFloatValues(
			const std::string & datasetName, 
			float* values, 
			unsigned long long const * numValuesInEachDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned int numDimensions
		);

		/**
		* Read an array Nd of long values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated and won't be freed by this method.
		*/
		virtual void readArrayNdOfLongValues(const std::string & datasetName, LONG64* values);

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
			unsigned int numDimensions);

		/**
		* Read an array Nd of unsigned long values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated and won't be freed by this method.
		*/
		virtual void readArrayNdOfULongValues(const std::string & datasetName, ULONG64* values);

		/**
		* Read an array Nd of int values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated and won't be freed by this method.
		*/
		void readArrayNdOfIntValues(const std::string & datasetName, int* values);

		/**
		* Find the array associated with datasetName and read from it.
		* @param datasetName                    The name of the array (potentially with multi dimensions).
		* @param values                         1d array output of int values ordered firstly by fastest direction. The values must be pre-allocated and won't be freed by this method.
		* @param numValuesInEachDimension       Number of values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param offsetValuesInEachDimension    Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param numDimensions                  The number of the dimensions of the array to read.
		*/
		void readArrayNdOfIntValues(
			const std::string & datasetName,
			int* values,
			unsigned long long const * numValuesInEachDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned int numDimensions
		);

		/**
		* Read an array Nd of unsigned int values stored in a specific dataset
		* Don't forget to delete the allocated pointer when no more necessary.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated and won't be freed by this method.
		*/
		void readArrayNdOfUIntValues(const std::string & datasetName, unsigned int* values);

		/**
		* Read an array Nd of short values stored in a specific dataset
		* Don't forget to delete the allocated pointer when no more necessary.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated and won't be freed by this method.
		*/
		void readArrayNdOfShortValues(const std::string & datasetName, short* values);

		/**
		* Read an array Nd of unsigned short values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated and won't be freed by this method.
		*/
		void readArrayNdOfUShortValues(const std::string & datasetName, unsigned short* values);

		/**
		* Read an array Nd of char values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated and won't be freed by this method.
		*/
		void readArrayNdOfCharValues(const std::string & datasetName, char* values);

		/**
		* Read an array Nd of unsigned char values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated and won't be freed by this method.
		*/
		void readArrayNdOfUCharValues(const std::string & datasetName, unsigned char* values);

		/**
		* Read the dimensions of an array stored in a specific dataset
		* @param datasetName	The absolute dataset name where to read the array dimensions
		* @param values 		The values must be pre-allocated and won't be freed by this method.
		*/
		std::vector<unsigned long long> readArrayDimensions(const std::string & datasetName);

		/**
		* Check wether an absolute path exists in the hdf file or not.
		*/
		bool exist(const std::string & absolutePathInHdfFile) const;

		/**
		* Check wether a dataset is compressed or not.
		*/
		bool isCompressed(const std::string & datasetName);

	protected:
		
		/**
		* Allow to force a root group for all newly created groups in inherited hdf proxies.
		*/
		virtual hdf5_hid_t openOrCreateRootGroup();

		/**
		* Check if an hdf group named as groupName exists in the root group.
		* If it exists, it returns the latter. If not, it creates this group and then returns it.
		* Do not close opened or created HDF5 group. They are automatically managed by fesapi.
		*/
		hdf5_hid_t openOrCreateGroupInRootGroup(const std::string & groupName);

	    hdf5_hid_t hdfFile;

		unsigned int compressionLevel;

		std::unordered_map< std::string, hdf5_hid_t > openedGroups;
	};
}
