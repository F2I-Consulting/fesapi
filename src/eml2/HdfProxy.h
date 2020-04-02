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
	/** A proxy for reading and writing values into an HDF5 file. */
	class HdfProxy : public AbstractHdfProxy
	{
	public:

		/**
		 * Constructor. Only to be used in partial transfer context
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		HdfProxy(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractHdfProxy(partialObject), hdfFile(-1), compressionLevel(0) {}

		/** Destructor. Closes the hdf file. */
		virtual ~HdfProxy() { close(); }

		/**
		 * Creates or opens the HDF5 file according to the chosen opening mode.
		 */
		void open() override;

		/**
		 * Checks if the HDF5 file is open or not
		 *
		 * @returns	True if opened, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isOpened() const final { return hdfFile != -1; }

		/** Closes the HDF5 file */
		void close() final;

		/**
		 * Gets the native datatype (@c H5T_NATIVE_INT, @c H5T_NATIVE_UINT,
		 * @c H5T_NATIVE_FLOAT, etc.) of a dataset
		 *
		 * @param 	groupName	Name of the dataset.
		 *
		 * @returns	The native HDF5 datatype identifier of the dataset if successful, otherwise returns a
		 * 			negative value.
		 */
		hdf5_hid_t getHdfDatatypeInDataset(const std::string& groupName) final;

		/**
		 * Gets the datatype class (@c H5T_INTEGER, @c H5T_FLOAT, @c H5T_STRING, etc.) of a dataset
		 *
		 * @param 	datasetName	Name of the dataset.
		 *
		 * @returns	The HDF5 datatype class identifier if successful, otherwise @c H5T_NO_CLASS (-1).
		 */
		int getHdfDatatypeClassInDataset(const std::string& datasetName) final;

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
		void writeItemizedListOfList(const std::string& groupName,
			const std::string& name,
			hdf5_hid_t cumulativeLengthDatatype,
			const void* cumulativeLength,
			unsigned long long cumulativeLengthSize,
			hdf5_hid_t elementsDatatype,
			const void* elements,
			unsigned long long elementsSize) final;

		/**
		 * Gets the number of dimensions in an HDF5 dataset of the proxy.
		 *
		 * @param 	datasetName	The absolute name (not relative to a group) of the dataset we want to get
		 * 						the number of dimensions.
		 *
		 * @returns	The number of dimensions of the dataset if successful, otherwise returns a negative
		 * 			value.
		 */
		unsigned int getDimensionCount(const std::string& datasetName) final;

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
		signed long long getElementCount(const std::string& datasetName) final;

		/**
		 * Sets the new compression level which will be used for all data to be written
		 *
		 * @param 	newCompressionLevel	The new compression level in range [0..9]. Lower compression
		 * 								levels are faster but result in less compression.
		 */
		DLL_IMPORT_OR_EXPORT void setCompressionLevel(unsigned int newCompressionLevel) final {
			compressionLevel = newCompressionLevel > 9 ? 9 : newCompressionLevel;
		}

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
		void writeArrayNdOfFloatValues(const std::string& groupName,
			const std::string& name,
			const float* floatValues,
			const unsigned long long* numValuesInEachDimension,
			unsigned int numDimensions) final;

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
		void writeArrayNdOfDoubleValues(const std::string& groupName,
			const std::string& name,
			const double* dblValues,
			const unsigned long long* numValuesInEachDimension,
			unsigned int numDimensions) final;

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
		void writeArrayNdOfCharValues(const std::string& groupName,
			const std::string& name,
			const char* intValues,
			const unsigned long long* numValuesInEachDimension,
			unsigned int numDimensions) final;

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
		void writeArrayNdOfIntValues(const std::string& groupName,
			const std::string& name,
			const int* intValues,
			const unsigned long long* numValuesInEachDimension,
			unsigned int numDimensions) final;

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
		void writeArrayNdOfGSoapULong64Values(const std::string& groupName,
			const std::string& name,
			const ULONG64* ulong64Values,
			const unsigned long long* numValuesInEachDimension,
			unsigned int numDimensions) final;

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
		void writeArrayNd(const std::string& groupName,
			const std::string& name,
			hdf5_hid_t datatype,
			const void* values,
			const unsigned long long* numValuesInEachDimension,
			unsigned int numDimensions) final;

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
		void createArrayNd(
			const std::string& groupName,
			const std::string& name,
			hdf5_hid_t datatype,
			const unsigned long long* numValuesInEachDimension,
			unsigned int numDimensions
		) final;

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
		void writeArrayNdSlab(
			const std::string& groupName,
			const std::string& name,
			hdf5_hid_t datatype,
			const void* values,
			const unsigned long long* numValuesInEachDimension,
			const unsigned long long* offsetValuesInEachDimension,
			unsigned int numDimensions
		) final;

		/**
		 * Writes some string attributes into a group
		 *
		 * @exception	std::invalid_argument	Attributes names and string values vector do not have the
		 * 										same size.
		 *
		 * @param 	groupName	  	Name of the group.
		 * @param 	attributeNames	Vector of attributes names.
		 * @param 	values		  	Vector of string values.
		 */
		void writeGroupAttributes(const std::string& groupName,
			const std::vector<std::string>& attributeNames,
			const std::vector<std::string>& values) final;

		/**
		 * Writes a single attribute into a group which contains an array of string values
		 *
		 * @param 	groupName	 	Name of the group.
		 * @param 	attributeName	Name of the attribute.
		 * @param 	values		 	Vector of string values.
		 */
		void writeGroupAttribute(const std::string& groupName,
			const std::string& attributeName,
			const std::vector<std::string>& values) final;

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
		void writeGroupAttributes(const std::string& groupName,
			const std::vector<std::string>& attributeNames,
			const std::vector<double>& values) final;

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
		void writeGroupAttributes(const std::string& groupName,
			const std::vector<std::string>& attributeNames,
			const std::vector<int>& values) final;

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
		void writeDatasetAttributes(const std::string& datasetName,
			const std::vector<std::string>& attributeNames,
			const std::vector<std::string>& values) final;

		/**
		 * Writes a single attribute into a dataset which contain an array of strings values
		 *
		 * @param 	datasetName  	Name of the dataset.
		 * @param 	attributeName	Name of the attribute.
		 * @param 	values		 	Vector of string values.
		 */
		void writeDatasetAttribute(const std::string& datasetName,
			const std::string& attributeName,
			const std::vector<std::string>& values) final;

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
		void writeDatasetAttributes(const std::string& datasetName,
			const std::vector<std::string>& attributeNames,
			const std::vector<double>& values) final;

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
		void writeDatasetAttributes(const std::string& datasetName,
			const std::vector<std::string>& attributeNames,
			const std::vector<int>& values) final;

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
		std::string readStringAttribute(const std::string& obj_name,
			const std::string& attr_name) const final;

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
		std::vector<std::string> readStringArrayAttribute(const std::string& obj_name,
			const std::string& attr_name) const final;

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
		double readDoubleAttribute(const std::string& obj_name,
			const std::string& attr_name) const final;

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
		LONG64 readLongAttribute(const std::string& obj_name,
			const std::string& attr_name) const final;

		/**
		 * Reads an nd array of double values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of double values ordered firstly by fastest direction. The
		 * 							values must be pre-allocated and won't be freed by this method.
		 */
		void readArrayNdOfDoubleValues(const std::string& datasetName, double* values) final;

		/**
		 * Finds the nd array of double values associated with @p datasetName and reads from it
		 *
		 * @exception	invalid_argument	Thrown when an invalid argument error condition occurs.
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
		void readArrayNdOfDoubleValues(
			const std::string& datasetName,
			double* values,
			unsigned long long const* numValuesInEachDimension,
			unsigned long long const* offsetInEachDimension,
			unsigned int numDimensions
		) final;

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
		void readArrayNdOfDoubleValues(
			const std::string& datasetName, double* values,
			unsigned long long const* blockCountPerDimension,
			unsigned long long const* offsetInEachDimension,
			unsigned long long const* strideInEachDimension,
			unsigned long long const* blockSizeInEachDimension,
			unsigned int numDimensions) final;

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
		void readArrayNdOfDoubleValues(
			hdf5_hid_t dataset,
			hdf5_hid_t filespace,
			void* values,
			unsigned long long slabSize) final;

		/**
		 * Reads an nd array of float values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of float values ordered firstly by fastest direction. The
		 * 							values must be pre-allocated and won't be freed by this method.
		 */
		void readArrayNdOfFloatValues(const std::string& datasetName, float* values) final;

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
		void readArrayNdOfFloatValues(
			const std::string& datasetName,
			float* values,
			unsigned long long const* numValuesInEachDimension,
			unsigned long long const* offsetInEachDimension,
			unsigned int numDimensions
		) final;

		/**
		 * Reads an nd array of long values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of long values ordered firstly by fastest direction. The
		 * 							values must be pre-allocated and won't be freed by this method.
		 */
		void readArrayNdOfLongValues(const std::string& datasetName, LONG64* values) final;

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
		void readArrayNdOfLongValues(
			const std::string& datasetName,
			LONG64* values,
			unsigned long long const* numValuesInEachDimension,
			unsigned long long const* offsetInEachDimension,
			unsigned int numDimensions) final;

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
		void readArrayNdOfULongValues(const std::string& datasetName, ULONG64* values) final;

		/**
		 * Reads an nd array of int values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of int values ordered firstly by fastest direction. The
		 * 							values must be pre-allocated and won't be freed by this method.
		 */
		void readArrayNdOfIntValues(const std::string& datasetName, int* values) final;

		/**
		 * Finds the nd array of int values associated with @p datasetName and reads from it
		 *
		 * @exception	invalid_argument	Thrown when an invalid argument error condition occurs.
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
		void readArrayNdOfIntValues(
			const std::string& datasetName,
			int* values,
			unsigned long long const* numValuesInEachDimension,
			unsigned long long const* offsetInEachDimension,
			unsigned int numDimensions
		) final;

		/**
		 * Reads an nd array of unsigned int values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of unsigned int values ordered firstly by fastest direction.
		 * 							The values must be pre-allocated and won't be freed by this method.
		 */
		void readArrayNdOfUIntValues(const std::string& datasetName, unsigned int* values) final;

		/**
		 * Reads an nd array of short values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of short values ordered firstly by fastest direction. The
		 * 							values must be pre-allocated and won't be freed by this method.
		 */
		void readArrayNdOfShortValues(const std::string& datasetName, short* values) final;

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
		void readArrayNdOfUShortValues(const std::string& datasetName, unsigned short* values) final;

		/**
		 * Reads an nd array of char values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of char values ordered firstly by fastest direction. The
		 * 							values must be pre-allocated and won't be freed by this method.
		 */
		void readArrayNdOfCharValues(const std::string& datasetName, char* values) final;

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
		void readArrayNdOfUCharValues(const std::string& datasetName, unsigned char* values) final;

		/**
		 * Reads the dimensions size of an nd array stored in a specific dataset
		 *
		 * @param 	datasetName	The absolute name of the nd array dataset.
		 *
		 * @returns	A vector of dimensions size.
		 */
		std::vector<unsigned long long> readArrayDimensions(const std::string& datasetName) final;

		/**
		 * Checks whether an absolute path exists in the HDF5 file
		 *
		 * @param 	absolutePathInHdfFile	An absolute path in the HDF5 file.
		 *
		 * @returns	True if the absolute path exists, else false.
		 */
		bool exist(const std::string& absolutePathInHdfFile) const final;

		/**
		 * Checks whether a dataset is compressed or not
		 *
		 * @exception	invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @param 	datasetName	Name of the dataset.
		 *
		 * @returns	True if compressed, false if not.
		 */
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
		 * Read an nd array of float values stored in a specific dataset.
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
		 * Considering a given dataset, this method selects an hyperslab region to add to an existing
		 * selected region or to add to a new selected region. The dataset is not closed within this
		 * method.
		 *
		 * @param 		  	datasetName					The name of the array (potentially with multi
		 * 												dimensions).
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
		 * @param 		  	numDimensions				The number of the dimensions of the array to
		 * 												select.
		 * @param 		  	newSelection				true if creating a new selected region else false.
		 * @param [in,out]	dataset						Input dataset ID if adding a new hyperslab region
		 * 												to an existing selected region, output dataset ID if
		 * 												creating a new selected region.
		 * @param [in,out]	filespace					Input selected region ID if adding a new
		 * 												hyperslab region to an existing selected region,
		 * 												output selected region ID if creating a new selected
		 * 												region.
		 */
		void selectArrayNdOfValues(
			const std::string& datasetName,
			unsigned long long const* blockCountPerDimension,
			unsigned long long const* offsetInEachDimension,
			unsigned long long const* strideInEachDimension,
			unsigned long long const* blockSizeInEachDimension,
			unsigned int numDimensions,
			bool newSelection,
			hdf5_hid_t& dataset,
			hdf5_hid_t& filespace);

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
