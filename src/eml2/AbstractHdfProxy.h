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

#include "EpcExternalPartReference.h"
#include "../common/HidtType.h"

/** A macro that defines cumulative length ds name */
#define CUMULATIVE_LENGTH_DS_NAME "cumulativeLength"
/** A macro that defines elements ds name */
#define ELEMENTS_DS_NAME "elements"

namespace EML2_NS
{
	/** @brief	An abstract proxy for reading and writing values into an HDF5 file. */
	class AbstractHdfProxy : public EpcExternalPartReference
	{
	public:  
		/** Destructor */
		virtual ~AbstractHdfProxy() {}

		/**
		 * Sets the path of the directory containing the EPC file associated to this HDF5 file
		 *
		 * @param 	rootPath	Path of the directory containing the EPC file.
		 */
		DLL_IMPORT_OR_EXPORT void setRootPath(const std::string& rootPath) { packageDirectoryAbsolutePath = rootPath; }

		/**
		 * Sets the relative path of the HDF5 file regarding the path of the directory containing the EPC
		 * file associated to this HDF5 file
		 *
		 * @param 	relPath	Relative path of the HDF5 file.
		 */
		DLL_IMPORT_OR_EXPORT void setRelativePath(const std::string& relPath) { relativeFilePath = relPath; }

		/**
		 * Sets the rights when opening the HDF5 file
		 *
		 * @param 	openingMode_	The opening mode of the HDF5 file.
		 */
		DLL_IMPORT_OR_EXPORT void setOpeningMode(COMMON_NS::DataObjectRepository::openingMode openingMode_) { openingMode = openingMode_; }

		/**
		 * Gets the relative path of the HDF5 file regarding the path of the directory containing the
		 * EPC file associated to this HDF5 file
		 *
		 * @returns	The relative path of the HDF5 file.
		 */
		DLL_IMPORT_OR_EXPORT const std::string& getRelativePath() const { return relativeFilePath; }

		/**
		 * Opens the HDF5 file for reading and writing. The read and write rights are determined by the EPC
		 * document configuration
		 */
		virtual void open() = 0;

		/**
		 * Checks if the HDF5 file is open or not
		 *
		 * @returns	True if opened, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isOpened() const = 0;

		/** Closes the HDF5 file */
		virtual void close() = 0;

		/**
		 * Gets the native datatype (@c H5T_NATIVE_INT, @c H5T_NATIVE_UINT,
		 * @c H5T_NATIVE_FLOAT, etc.) of a dataset
		 *
		 * @param 	datasetName	Name of the dataset.
		 *
		 * @returns	The native HDF5 datatype identifier of the dataset if successful, otherwise returns a
		 * 			negative value.
		 */
		virtual hdf5_hid_t getHdfDatatypeInDataset(const std::string & datasetName) = 0;

		/**
		 * Gets the datatype class (@c H5T_INTEGER, @c H5T_FLOAT, @c H5T_STRING, etc.) of a dataset
		 *
		 * @param 	datasetName	Name of the dataset.
		 *
		 * @returns	The HDF5 datatype class identifier if successful, otherwise @c H5T_NO_CLASS (-1).
		 */
		virtual int getHdfDatatypeClassInDataset(const std::string & datasetName) = 0;

		/**
		 * Writes an itemized list of lists into the HDF5 file by means of a single group containing two
		 * datasets: one for the elements and one for the cumulative lengths of the lists of elements.
		 *
		 * @param 	groupName					The name of the group where to create the itemized list
		 * 										of lists. This name must not contain '/' character and must
		 * 										be directly contained in the RESQML group.
		 * @param 	name						The name of the itemized list of lists HDF5 group.
		 * @param 	cumulativeLengthDatatype	The datatype of the cumulative lengths dataset to write.
		 * @param 	cumulativeLength			1d array of positive integers containing for each list
		 * 										the sum of all the previous lists lengths including the
		 * 										current one.
		 * @param 	cumulativeLengthSize		Size of the cumulative lengths array.
		 * @param 	elementsDatatype			The datatype of the elements to write.
		 * @param 	elements					1d array of elements containing the aggregation of
		 * 										individual lists contents.
		 * @param 	elementsSize				Size of the elements array.
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
		 * Gets the number of dimensions in an HDF5 dataset of the proxy.
		 *
		 * @param 	datasetName	The absolute name (not relative to a group) of the dataset we want to get
		 * 						the number of dimensions.
		 *
		 * @returns	The number of dimensions of the dataset if successful, otherwise returns a negative
		 * 			value.
		 */
		virtual unsigned int getDimensionCount(const std::string & datasetName) = 0;

		/**
		 * Gets the number of elements in an HDF5 dataset of the proxy. The number of elements is got
		 * from all dimensions.
		 *
		 * @param 	datasetName	The absolute name (not relative to a group) of the dataset we want to get
		 * 						the number of elements.
		 *
		 * @returns	The number of elements of the dataset if successful, otherwise returns a negative
		 * 			value.
		 */
		virtual signed long long getElementCount(const std::string & datasetName) = 0;

		/**
		 * Sets the new compression level which will be used for all data to be written
		 *
		 * @param 	newCompressionLevel	The new compression level in range [0..9]. Lower compression
		 * 								levels are faster but result in less compression.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setCompressionLevel(unsigned int newCompressionLevel) = 0;

		/**
		 * Writes an nd array of float values into the HDF5 file by means of a single dataset
		 *
		 * @param 	groupName					The name of the group where to create the nd array of
		 * 										float values. This name must not contain '/' character and
		 * 										must be directly contained in RESQML group.
		 * @param 	name						The name of the nd array HDF5 dataset. It must not
		 * 										already exist.
		 * @param 	floatValues					1d array of float values ordered firstly by fastest
		 * 										direction.
		 * @param 	numValuesInEachDimension	Number of values in each dimension of the nd array to
		 * 										write. They are ordered from fastest index to slowest index.
		 * @param 	numDimensions				The number of dimensions (n) of the nd array to write.
		 */
		virtual void writeArrayNdOfFloatValues(const std::string & groupName,
		  const std::string & name,
		  const float * floatValues,
		  const unsigned long long * numValuesInEachDimension,
		  unsigned int numDimensions) = 0;

		/**
		 * Writes an nd array of double values into the HDF5 file by means of a single dataset
		 *
		 * @param 	groupName					The name of the group where to create the nd array of
		 * 										double values. This name must not contain '/' character and
		 * 										must be directly contained in RESQML group.
		 * @param 	name						The name of the nd array HDF5 dataset. It must not
		 * 										already exist.
		 * @param 	dblValues					1d array of double values ordered firstly by fastest
		 * 										direction.
		 * @param 	numValuesInEachDimension	Number of values in each dimension of the nd array to
		 * 										write. They are ordered from fastest index to slowest index.
		 * @param 	numDimensions				The number of dimensions (n) of the nd array to write.
		 */
		virtual void writeArrayNdOfDoubleValues(const std::string & groupName,
		  const std::string & name,
		  const double * dblValues,
		  const unsigned long long * numValuesInEachDimension,
		  unsigned int numDimensions) = 0;

		/**
		 * Writes an nd array of char values into the HDF5 file by means of a single dataset
		 *
		 * @param 	groupName					The name of the group where to create the nd array of int
		 * 										values. This name must not contain '/' character and must be
		 * 										directly contained in RESQML group.
		 * @param 	name						The name of the nd array HDF5 dataset. It must not
		 * 										already exist.
		 * @param 	intValues					1d array of char values ordered firstly by fastest
		 * 										direction.
		 * @param 	numValuesInEachDimension	Number of values in each dimension of the nd array to
		 * 										write. They are ordered from fastest index to slowest index.
		 * @param 	numDimensions				The number of the dimensions (n) of the nd array to write.
		 */
		virtual void writeArrayNdOfCharValues(const std::string & groupName,
			const std::string & name,
			const char * intValues,
			const unsigned long long * numValuesInEachDimension,
			unsigned int numDimensions) = 0;

		/**
		 * Writes an nd array of int values into the HDF5 file by means of a single dataset
		 *
		 * @param 	groupName					The name of the group where to create the nd array of int
		 * 										values. This name must not contain '/' character and must be
		 * 										directly contained in RESQML group.
		 * @param 	name						The name of the nd array HDF5 dataset. It must not
		 * 										already exist.
		 * @param 	intValues					1d array of int values ordered firstly by fastest
		 * 										direction.
		 * @param 	numValuesInEachDimension	Number of values in each dimension of the nd array to
		 * 										write. They are ordered from fastest index to slowest index.
		 * @param 	numDimensions				The number of the dimensions (n) of the nd array to write.
		 */
		virtual void writeArrayNdOfIntValues(const std::string & groupName,
		  const std::string & name,
		  const int * intValues,
		  const unsigned long long * numValuesInEachDimension,
		  unsigned int numDimensions) = 0;

 		/**
 		 * Writes an nd array of gSOAP unsigned long 64 values into the HDF5 file by means of a single
 		 * dataset
 		 *
 		 * @param 	groupName					The name of the group where to create the nd array of
 		 * 										gSOAP unsigned long 64 values. This name must not contain '/'
 		 * 										character and must be directly contained in RESQML group.
 		 * @param 	name						The name of the nd array HDF5 dataset. It must not
 		 * 										already exist.
 		 * @param 	ulong64Values				1d array of gSOAP unsigned long 64 values ordered firstly
 		 * 										by fastest direction.
 		 * @param 	numValuesInEachDimension	Number of values in each dimension of the nd array to
 		 * 										write. They are ordered from fastest index to slowest index.
 		 * @param 	numDimensions				The number of the dimensions (n) of the nd array to write.
 		 */
 		virtual void writeArrayNdOfGSoapULong64Values(const std::string & groupName,
			const std::string & name,
			const ULONG64 * ulong64Values,
			const unsigned long long * numValuesInEachDimension,
			unsigned int numDimensions) = 0;

		/**
		 * Writes an nd array of a specific datatype into the HDF5 file by means of a single dataset
		 *
		 * @param 	groupName					The name of the group where to create the nd array of
		 * 										specific datatype values. This name must not contain '/'
		 * 										character and must be directly contained in RESQML group.
		 * @param 	name						The name of the nd array HDF5 dataset. It must not
		 * 										already exist.
		 * @param 	datatype					The specific datatype of the values to write.
		 * @param 	values						1d array of specific datatype values ordered firstly by
		 * 										fastest direction.
		 * @param 	numValuesInEachDimension	Number of values in each dimension of the nd array to
		 * 										write. They are ordered from fastest index to slowest index.
		 * @param 	numDimensions				The number of the dimensions (n) of the nd array to write.
		 */
		virtual void writeArrayNd(const std::string & groupName,
		  const std::string & name,
		  hdf5_hid_t datatype,
		  const void * values,
		  const unsigned long long * numValuesInEachDimension,
		  unsigned int numDimensions) = 0;

		/**
		 * Creates an nd array of a specific datatype into the HDF5 file by means of a single dataset.
		 * Values are not yet written to this array
		 *
		 * @param 	groupName					The name of the group where to create the nd array of
		 * 										specific datatype values. This name must not contain '/'
		 * 										character and must be directly contained in RESQML group.
		 * @param 	name						The name of the nd array HDF5 dataset. It must not exist.
		 * @param 	datatype					The specific datatype of the nd array values.
		 * @param 	numValuesInEachDimension	Number of values in each dimension of the nd array. They
		 * 										are ordered from fastest index to slowest index.
		 * @param 	numDimensions				The number of the dimensions (n) of the nd array to
		 * 										create.
		 */
		virtual void createArrayNd(
		  const std::string& groupName,
		  const std::string& name,
		  hdf5_hid_t datatype,
		  const unsigned long long* numValuesInEachDimension,
		  unsigned int numDimensions
		  ) = 0;

		/**
		 * Finds the nd array associated with @p groupName and @p name and writes into it
		 *
		 * @param 	groupName				   	The name of the group associated with the nd array.
		 * @param 	name					   	The name of the nd array dataset.
		 * @param 	datatype				   	The datatype of the nd array values.
		 * @param 	values					   	1d array of datatype values ordered firstly by fastest
		 * 										direction.
		 * @param 	numValuesInEachDimension   	Number of values in each dimension of the nd array to
		 * 										write. They are ordered from fastest index to slowest
		 * 										index.
		 * @param 	offsetValuesInEachDimension	Offset values in each dimension of the nd array to write.
		 * 										They are ordered from fastest index to slowest index.
		 * @param 	numDimensions			   	The number of the dimensions (n) of the nd array to write.
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
		 * Writes some string attributes into a group
		 *
		 * @exception	std::invalid_argument	Attributes names and string values vector do not have the same
		 * 										size.
		 *
		 * @param 	groupName	  	Name of the group.
		 * @param 	attributeNames	Vector of attributes names.
		 * @param 	values		  	Vector of string values.
		 */
		virtual void writeGroupAttributes(const std::string & groupName,
			const std::vector<std::string> & attributeNames,
			const std::vector<std::string> & values) = 0;

		/**
		 * Writes a single attribute into a group which contains an array of string values
		 *
		 * @param 	groupName	 	Name of the group.
		 * @param 	attributeName	Name of the attribute.
		 * @param 	values		 	Vector of string values.
		 */
		virtual void writeGroupAttribute(const std::string & groupName,
			const std::string & attributeName,
			const std::vector<std::string> & values) = 0;

		/**
		 * Writes some double attributes into a group
		 *
		 * @exception	std::invalid_argument	Attributes names and double values vector do not have the
		 * 										same size.  
		 *
		 * @param 	groupName	  	Name of the group.
		 * @param 	attributeNames	Vector of attributes names.
		 * @param 	values		  	Vector of double values.
		 */
		virtual void writeGroupAttributes(const std::string & groupName,
			const std::vector<std::string> & attributeNames,
			const std::vector<double> & values) = 0;

		/**
		 * Writes some int attributes into a group
		 *
		 * @exception	std::invalid_argument	Attributes names and int values vector do not have the
		 * 										same size.  
		 *
		 * @param 	groupName	  	Name of the group.
		 * @param 	attributeNames	Vector of attributes names.
		 * @param 	values		  	Vector of int values.
		 */
		virtual void writeGroupAttributes(const std::string & groupName,
			const std::vector<std::string> & attributeNames,
			const std::vector<int> & values) = 0;

		/**
		 * Writes some string attributes into a dataset
		 *
		 * @exception	std::invalid_argument	Attributes names and string values vector do not have the
		 * 										same size.
		 *
		 * @param 	datasetName   	Name of the dataset.
		 * @param 	attributeNames	Vector of attributes names.
		 * @param 	values		  	Vector of string values.
		 */
		virtual void writeDatasetAttributes(const std::string & datasetName,
			const std::vector<std::string> & attributeNames,
			const std::vector<std::string> & values) = 0;

		/**
		 * Writes a single attribute into a dataset which contain an array of strings values
		 *
		 * @param 	datasetName  	Name of the dataset.
		 * @param 	attributeName	Name of the attribute.
		 * @param 	values		 	Vector of string values.
		 */
		virtual void writeDatasetAttribute(const std::string & datasetName,
			const std::string & attributeName,
			const std::vector<std::string> & values) = 0;

		/**
		 * Writes some double attributes into a dataset
		 *
		 * @exception	std::invalid_argument	Attributes names and double values vector do not have the
		 * 										same size.
		 *
		 * @param 	datasetName   	Name of the dataset.
		 * @param 	attributeNames	Vector of attributes names.
		 * @param 	values		  	Vector of double values.
		 */
		virtual void writeDatasetAttributes(const std::string & datasetName,
			const std::vector<std::string> & attributeNames,
			const std::vector<double> & values) = 0;

		/**
		 * Writes some int attributes into a dataset
		 *
		 * @exception	std::invalid_argument	Attributes names and int values vector do not have the
		 * 										same size.
		 *
		 * @param 	datasetName   	Name of the dataset.
		 * @param 	attributeNames	Vector of attributes names.
		 * @param 	values		  	Vector of int values.
		 */
		virtual void writeDatasetAttributes(const std::string & datasetName,
			const std::vector<std::string> & attributeNames,
			const std::vector<int> & values) = 0;

		/**
		 * Reads a string which is stored as an HDF5 attribute in a file, group or dataset
		 *
		 * @exception	std::invalid_argument	If the HDF5 file is not opened or if the attribute cannot
		 * 										be read.
		 *
		 * @param 	obj_name 	Use "." if the attribute to read is on the HDF5 file otherwise the full
		 * 						path of the group or dataset.
		 * @param 	attr_name	Name of the attribute.
		 *
		 * @returns	The attribute value.
		 */
		virtual std::string readStringAttribute(const std::string & obj_name,
			const std::string & attr_name) const = 0;

		/**
		 * Reads string values which are stored as an HDF5 attribute in a file, group or dataset
		 *
		 * @exception	std::invalid_argument	If the HDF5 file is not opened or if the attribute cannot
		 * 										be read.
		 *
		 * @param 	obj_name 	Use "." if the attribute to read is on the HDF5 file otherwise the full
		 * 						path of the group or dataset.
		 * @param 	attr_name	Name of the attribute.
		 *
		 * @returns	The vector of attribute values.
		 */
		virtual std::vector<std::string> readStringArrayAttribute(const std::string & obj_name,
			const std::string & attr_name) const = 0;

		/**
		 * Reads a double which is stored as an HDF5 attribute in a file, group or dataset
		 *
		 * @exception	std::invalid_argument	If the HDF5 file is not opened or if the attribute cannot
		 * 										be read.
		 *
		 * @param 	obj_name 	use "." if the attribute to read is on the file otherwise the full path
		 * 						of the group or dataset.
		 * @param 	attr_name	Name of the attribute.
		 *
		 * @returns	The attribute value.
		 */
		virtual double readDoubleAttribute(const std::string & obj_name,
			const std::string & attr_name) const = 0;

		/**
		 * Reads a long which is stored as an HDF5 attribute in a file, group or dataset
		 *
		 * @exception	std::invalid_argument	If the HDF5 file is not opened or if the attribute cannot
		 * 										be read.
		 *
		 * @param 	obj_name 	use '.' if the attribute to read is on the file otherwise the full path
		 * 						of the group or dataset.
		 * @param 	attr_name	Name of the attribute.
		 *
		 * @returns	The attribute value.
		 */
		virtual LONG64 readLongAttribute(const std::string & obj_name,
			const std::string & attr_name) const = 0;

		/**
		 * Reads an nd array of double values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of double values ordered firstly by fastest direction. The
		 * 							values must be pre-allocated and won't be freed by this method.
		 */
		virtual void readArrayNdOfDoubleValues(const std::string & datasetName, double* values) = 0;

		/**
		 * Finds the nd array of double values associated with @p datasetName and reads from it
		 *
		 * @exception	std::invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @param 	   	datasetName					The name of the nd array dataset.
		 * @param [out]	values						1d array of double values ordered firstly by fastest
		 * 											direction. The values must be pre-allocated and won't be
		 * 											freed by this method.
		 * @param 	   	numValuesInEachDimension	Number of values in each dimension of the nd array to
		 * 											read. They are ordered from fastest index to slowest
		 * 											index.
		 * @param 	   	offsetInEachDimension   	Offset values in each dimension of the nd array to
		 * 											read. They are ordered from fastest index to slowest
		 * 											index.
		 * @param 	   	numDimensions				The number of the dimensions (n) of the nd array to
		 * 											read.
		 */
		virtual void readArrayNdOfDoubleValues(
		  const std::string & datasetName,
		  double* values,
		  unsigned long long const * numValuesInEachDimension,
		  unsigned long long const * offsetInEachDimension,
		  unsigned int numDimensions
		  ) = 0;

		/**
		 * Finds the nd array of double values associated with @p datasetName and reads from it
		 *
		 * @exception	invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @param 	   	datasetName					The name of the nd array dataset.
		 * @param [out]	values						1d array of double values ordered firstly by fastest
		 * 											direction. The values must be pre-allocated and won't be
		 * 											freed by this method.
		 * @param 	   	blockCountPerDimension  	Number of blocks to select from the dataspace, in
		 * 											each dimension. They are ordered from fastest index to
		 * 											slowest index.
		 * @param 	   	offsetInEachDimension   	Offset values in each dimension of the nd array to
		 * 											read. They are ordered from fastest index to slowest
		 * 											index.
		 * @param 	   	strideInEachDimension   	Number of elements to move from one block to another
		 * 											in each dimension. They are ordered from fastest index to
		 * 											slowest index.
		 * @param 	   	blockSizeInEachDimension	Size of selected blocks in each dimension. They are
		 * 											ordered from fastest index to slowest index.
		 * @param 	   	numDimensions				The number of the dimensions (n) of the nd array to
		 * 											read.
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
		 * Considering a given nd array dataset, this method selects an hyperslab region to add to an
		 * existing selected region or to add to a new selected region. The dataset is not closed within
		 * this method.
		 *
		 * @exception	invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @param 		  	datasetName					The name of the nd array dataset.
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
		 * @param 		  	numDimensions				The number of the dimensions (n) of the nd array
		 * 												to read.
		 * @param 		  	newSelection				true if creating a new selected region else false.
		 * @param [in,out]	dataset						Input dataset ID if adding a new hyperslab region
		 * 												to an existing selected region, output dataset ID if
		 * 												creating a new selected region.
		 * @param [in,out]	filespace					Input selected region ID if adding a new
		 * 												hyperslab region to an existing selected region,
		 * 												output selected region ID if creating a new selected
		 * 												region.
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
		 * Considering a given nd array dataset, reads the double values corresponding to an existing
		 * selected region.
		 *
		 * @exception	invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @param 	   	dataset  	ID of the dataset to read from.
		 * @param 	   	filespace	ID of the selected region.
		 * @param [out]	values   	1d array of double values ordered firstly by fastest direction. The
		 * 							values must be pre-allocated and won't be freed by this method.
		 * @param 	   	slabSize 	Number of values to read.
		 */
		virtual void readArrayNdOfDoubleValues(
			hdf5_hid_t dataset,
			hdf5_hid_t filespace,
			void* values,
			unsigned long long slabSize) = 0;

		/**
		 * Reads an nd array of float values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of float values ordered firstly by fastest direction. The
		 * 							values must be pre-allocated and won't be freed by this method.
		 */
		virtual void readArrayNdOfFloatValues(const std::string & datasetName, float* values) = 0;

		/**
		 * Finds the nd array of float values associated with @p datasetName and reads from it
		 *
		 * @exception	invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @param 	   	datasetName					The name of the nd array dataset.
		 * @param [out]	values						1d array of float values ordered firstly by fastest
		 * 											direction. The values must be pre-allocated and won't be
		 * 											freed by this method.
		 * @param 	   	numValuesInEachDimension	Number of values in each dimension of the nd array to
		 * 											read. They are ordered from fastest index to slowest
		 * 											index.
		 * @param 	   	offsetInEachDimension   	Offset values in each dimension of the nd array to
		 * 											read. They are ordered from fastest index to slowest
		 * 											index.
		 * @param 	   	numDimensions				The number of the dimensions (n) of the nd array to
		 * 											read.
		 */
		virtual void readArrayNdOfFloatValues(
		  const std::string & datasetName,
		  float* values,
		  unsigned long long const * numValuesInEachDimension,
		  unsigned long long const * offsetInEachDimension,
		  unsigned int numDimensions
		  ) = 0;

		/**
		 * Reads an nd array of long values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of long values ordered firstly by fastest direction. The
		 * 							values must be pre-allocated and won't be freed by this method.
		 */
		virtual void readArrayNdOfLongValues(const std::string & datasetName, LONG64* values) = 0;

		/**
		 * Finds the nd array of long values associated with @p datasetName and reads from it
		 *
		 * @exception	invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @param 	   	datasetName					The name of the nd array dataset.
		 * @param [out]	values						1d array of long values ordered firstly by fastest
		 * 											direction. The values must be pre-allocated and won't be
		 * 											freed by this method.
		 * @param 	   	numValuesInEachDimension	Number of values in each dimension of the nd array to
		 * 											read. They are ordered from fastest index to slowest
		 * 											index.
		 * @param 	   	offsetInEachDimension   	Offset values in each dimension of the nd array to
		 * 											read. They are ordered from fastest index to slowest
		 * 											index.
		 * @param 	   	numDimensions				The number of the dimensions (n) of the nd array to
		 * 											read.
		 */
		virtual void readArrayNdOfLongValues(
			const std::string & datasetName,
			LONG64* values,
			unsigned long long const * numValuesInEachDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned int numDimensions) = 0;

		/**
		 * Reads an nd array of unsigned long values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of unsigned long values ordered firstly by fastest
		 * 							direction. The values must be pre-allocated and won't be freed by
		 * 							this method.
		 */
		virtual void readArrayNdOfULongValues(const std::string & datasetName, ULONG64* values) = 0;

		/**
		 * Reads an nd array of int values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of int values ordered firstly by fastest direction. The
		 * 							values must be pre-allocated and won't be freed by this method.
		 */
		virtual void readArrayNdOfIntValues(const std::string & datasetName, int* values) = 0;

		/**
		 * Finds the nd array of int values associated with @p datasetName and reads from it
		 *
		 * @exception	std::invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @param 	   	datasetName					The name of the nd array dataset.
		 * @param [out]	values						1d array of int values ordered firstly by fastest
		 * 											direction. The values must be pre-allocated and won't be
		 * 											freed by this method.
		 * @param 	   	numValuesInEachDimension	Number of values in each dimension of the nd array to
		 * 											read. They are ordered from fastest index to slowest
		 * 											index.
		 * @param 	   	offsetInEachDimension   	Offset values in each dimension of the nd array to
		 * 											read. They are ordered from fastest index to slowest
		 * 											index.
		 * @param 	   	numDimensions				The number of the dimensions (n) of the nd array to
		 * 											read.
		 */
		virtual void readArrayNdOfIntValues(
			const std::string & datasetName,
			int* values,
			unsigned long long const * numValuesInEachDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned int numDimensions
		) = 0;

		/**
		 * Reads an nd array of unsigned int values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of unsigned int values ordered firstly by fastest direction.
		 * 							The values must be pre-allocated and won't be freed by this method.
		 */
		virtual void readArrayNdOfUIntValues(const std::string & datasetName, unsigned int* values) = 0;

		/**
		 * Reads an nd array of short values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of short values ordered firstly by fastest direction. The
		 * 							values must be pre-allocated and won't be freed by this method.
		 */
		virtual void readArrayNdOfShortValues(const std::string & datasetName, short* values) = 0;

		/**
		 * Reads an nd array of unsigned short values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of unsigned short values ordered firstly by fastest
		 * 							direction. The values must be pre-allocated and won't be freed by
		 * 							this method.
		 */
		virtual void readArrayNdOfUShortValues(const std::string & datasetName, unsigned short* values) = 0;

		/**
		 * Reads an nd array of char values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of char values ordered firstly by fastest direction. The
		 * 							values must be pre-allocated and won't be freed by this method.
		 */
		virtual void readArrayNdOfCharValues(const std::string & datasetName, char* values) = 0;

		/**
		 * Reads an nd array of unsigned char values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of unsigned char values ordered firstly by fastest
		 * 							direction. The values must be pre-allocated and won't be freed by
		 * 							this method.
		 */
		virtual void readArrayNdOfUCharValues(const std::string & datasetName, unsigned char* values) = 0;

		/**
		 * Reads the dimensions size of an nd array stored in a specific dataset
		 *
		 * @param 	datasetName	The absolute name of the nd array dataset.
		 *
		 * @returns	A vector of dimensions size.
		 */
		virtual std::vector<unsigned long long> readArrayDimensions(const std::string & datasetName) = 0;

		/**
		 * Checks whether an absolute path exists in the HDF5 file
		 *
		 * @param 	absolutePathInHdfFile	An absolute path in the HDF5 file.
		 *
		 * @returns	True if the absolute path exists, else false.
		 */
		virtual bool exist(const std::string & absolutePathInHdfFile) const = 0;

		/**
		 * Checks whether a dataset is compressed or not
		 *
		 * @exception	invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @param 	datasetName	Name of the dataset.
		 *
		 * @returns	True if compressed, false if not.
		 */
		virtual bool isCompressed(const std::string & datasetName) = 0;

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		AbstractHdfProxy(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : EpcExternalPartReference(partialObject) {}

		/** / The directory where the EPC document is stored. */
		std::string packageDirectoryAbsolutePath;
		/** / Must be relative to the location of the package */
		std::string relativeFilePath;
		/** The opening mode */
		COMMON_NS::DataObjectRepository::openingMode openingMode;

		/**
		 * Abstract hdf proxy
		 *
		 * @param 	packageDirAbsolutePath	The soap context where the underlying gSOAP proxy is going to
		 * 									be created.
		 * @param 	externalFilePath	  	Full pathname of the external file.
		 * @param 	hdfPermissionAccess   	(Optional) The hdf permission access.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		AbstractHdfProxy(const std::string & packageDirAbsolutePath, const std::string & externalFilePath, COMMON_NS::DataObjectRepository::openingMode hdfPermissionAccess = COMMON_NS::DataObjectRepository::openingMode::READ_ONLY) :
			packageDirectoryAbsolutePath(packageDirAbsolutePath), relativeFilePath(externalFilePath), openingMode(hdfPermissionAccess) {}

		AbstractHdfProxy(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap) :
			EpcExternalPartReference(fromGsoap), openingMode(COMMON_NS::DataObjectRepository::openingMode::READ_ONLY) {}

		AbstractHdfProxy(gsoap_eml2_1::_eml21__EpcExternalPartReference* fromGsoap) :
			EpcExternalPartReference(fromGsoap), openingMode(COMMON_NS::DataObjectRepository::openingMode::READ_ONLY) {}

		AbstractHdfProxy(gsoap_eml2_3::_eml23__EpcExternalPartReference* fromGsoap) :
			EpcExternalPartReference(fromGsoap), openingMode(COMMON_NS::DataObjectRepository::openingMode::READ_ONLY) {}

		/**
		 * Instantiate and initialize the gsoap proxy.
		 * This method is defined in order to be used in derived class without having to link to generated gsoap files.
		 *
		 * @param 	emlVersion	  	Desired eml Version such as 20 (for v2.0) or 23 (for v2.3) etc...
		*/
		DLL_IMPORT_OR_EXPORT void initGsoapProxy(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, unsigned int emlVersion);
	};
}
