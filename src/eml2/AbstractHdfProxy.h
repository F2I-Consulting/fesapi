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

namespace EML2_NS
{
	/** @brief	An abstract proxy for reading and writing values into an HDF5 file.
	* It is possible to derive this class in a custom class in order for the FESAPI user
	* to get change the FESAPI reads from and writes to HDF5 file.
	* However, please note that the RESQML standard mandates so far a HDF5 1.8 backward compatibility.
	* In order to achieve this backward compatibility please use
	*	hid_t access_props = H5Pcreate (H5P_FILE_ACCESS);
	*	H5Pset_libver_bounds (access_props, H5F_LIBVER_V18, H5F_LIBVER_V18);
	* when you create an HDF5 file before to write into it.
	* See https://confluence.hdfgroup.org/display/HDF5/H5P_SET_LIBVER_BOUNDS for more details.
	*/
	class AbstractHdfProxy : public EpcExternalPartReference
	{
	public:

		/** Defines cumulative length ds name */
		static constexpr char const* CUMULATIVE_LENGTH_DS_NAME = "cumulativeLength";
		/** Defines elements ds name */
		static constexpr char const* ELEMENTS_DS_NAME = "elements";

		/** Destructor */
		DLL_IMPORT_OR_EXPORT virtual ~AbstractHdfProxy() = default;

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
		 * Gets the absolute path of the HDF5 file
		 *
		 * @returns	The absolute path of the HDF5 file.
		 */
		DLL_IMPORT_OR_EXPORT std::string getAbsolutePath() const {
			return (packageDirectoryAbsolutePath.empty() || packageDirectoryAbsolutePath.back() == '/' || packageDirectoryAbsolutePath.back() == '\\' ? packageDirectoryAbsolutePath : packageDirectoryAbsolutePath + '/')
				+ relativeFilePath;
		}

		/**
		 * Opens the HDF5 file for reading and writing. The read and write rights are determined by the EPC
		 * document configuration
		 */
		DLL_IMPORT_OR_EXPORT virtual void open() = 0;

		/**
		 * Checks if the HDF5 file is open or not
		 *
		 * @returns	True if opened, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isOpened() const = 0;

		/** Closes the HDF5 file */
		DLL_IMPORT_OR_EXPORT virtual void close() = 0;

		/**
		 * Gets the native datatype of a dataset
		 *
		 * @param 	datasetName	Name of the dataset.
		 *
		 * @returns	The native datatype identifier of the dataset if successful, otherwise returns unknown;
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::AbstractObject::numericalDatatypeEnum getNumericalDatatype(const std::string & datasetName) = 0;

		/**
		 * Gets the datatype class (@c H5T_INTEGER, @c H5T_FLOAT, @c H5T_STRING, etc.) of a dataset
		 *
		 * @param 	datasetName	Name of the dataset.
		 *
		 * @returns	The HDF5 datatype class identifier if successful, otherwise @c H5T_NO_CLASS (-1).
		 */
		DLL_IMPORT_OR_EXPORT virtual int getHdfDatatypeClassInDataset(const std::string & datasetName) = 0;

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
		 * @param 	elementsSize				Size of the elements array. It must be equal to
		 *										cumulativeLength[cumulativeLengthSize-1].
		 */
		DLL_IMPORT_OR_EXPORT virtual void writeItemizedListOfList(const std::string & groupName,
			const std::string & name,
			COMMON_NS::AbstractObject::numericalDatatypeEnum cumulativeLengthDatatype,
			const void * cumulativeLength,
			uint64_t cumulativeLengthSize,
			COMMON_NS::AbstractObject::numericalDatatypeEnum elementsDatatype,
			const void * elements,
			uint64_t elementsSize) = 0;

		/**
		 * Gets the number of dimensions in an HDF5 dataset of the proxy.
		 *
		 * @param 	datasetName	The absolute name (not relative to a group) of the dataset we want to get
		 * 						the number of dimensions.
		 *
		 * @returns	The number of dimensions of the dataset if successful, otherwise returns a negative
		 * 			value.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getDimensionCount(const std::string & datasetName) { return getElementCountPerDimension(datasetName).size(); }

		/**
		 * Get the number of elements in each dimension of an HDF5 dataset.
		 * uint32_t is returned instead of uint64_t cause of some SWIG usage. I cannot SWIG port std::vector<uint64_t>
		 * @param datasetName	The absolute name of the dataset which we want to get the number of elements from.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::vector<uint32_t> getElementCountPerDimension(const std::string & datasetName) = 0;

		/**
		 * Gets the number of elements in an HDF5 dataset of the proxy. The number of elements is got
		 * from all dimensions.
		 *
		 * @param 	datasetName	The absolute name (not relative to a group) of the dataset we want to get
		 * 						the number of elements.
		 *
		 * @returns	The number of elements of the dataset
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getElementCount(const std::string & datasetName);

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
		DLL_IMPORT_OR_EXPORT void writeArrayNdOfFloatValues(const std::string & groupName,
			const std::string & name,
			const float * values,
			const uint64_t * numValuesInEachDimension,
			unsigned int numDimensions) {
			writeArrayNd(groupName, name, COMMON_NS::AbstractObject::numericalDatatypeEnum::FLOAT, values, numValuesInEachDimension, numDimensions);
		}

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
		DLL_IMPORT_OR_EXPORT void writeArrayNdOfDoubleValues(const std::string & groupName,
		  const std::string & name,
		  const double * values,
		  const uint64_t * numValuesInEachDimension,
		  unsigned int numDimensions) {
			writeArrayNd(groupName, name, COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE, values, numValuesInEachDimension, numDimensions);
		}

		/**
		 * Writes an nd array of int 8 bits values into the HDF5 file by means of a single dataset
		 *
		 * @param 	groupName					The name of the group where to create the nd array of int
		 * 										values. This name must not contain '/' character and must be
		 * 										directly contained in RESQML group.
		 * @param 	name						The name of the nd array HDF5 dataset. It must not
		 * 										already exist.
		 * @param 	intValues					1d array of int 8 bits values ordered firstly by fastest
		 * 										direction.
		 * @param 	numValuesInEachDimension	Number of values in each dimension of the nd array to
		 * 										write. They are ordered from fastest index to slowest index.
		 * @param 	numDimensions				The number of the dimensions (n) of the nd array to write.
		 */
		DLL_IMPORT_OR_EXPORT void writeArrayNdOfInt8Values(const std::string & groupName,
			const std::string & name,
			const int8_t * values,
			const uint64_t * numValuesInEachDimension,
			unsigned int numDimensions) {
			writeArrayNd(groupName, name, COMMON_NS::AbstractObject::numericalDatatypeEnum::INT8, values, numValuesInEachDimension, numDimensions);
		}

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
		DLL_IMPORT_OR_EXPORT void writeArrayNdOfIntValues(const std::string & groupName,
		  const std::string & name,
		  const int * values,
		  const uint64_t * numValuesInEachDimension,
		  unsigned int numDimensions) {
			writeArrayNd(groupName, name, COMMON_NS::AbstractObject::numericalDatatypeEnum::INT32, values, numValuesInEachDimension, numDimensions);
		}

		/**
		 * Writes an nd array of integer 64 values into the HDF5 file by means of a single
		 * dataset
		 *
		 * @param 	groupName					The name of the group where to create the nd array of
		 * 										gSOAP unsigned long 64 values. This name must not contain '/'
		 * 										character and must be directly contained in RESQML group.
		 * @param 	name						The name of the nd array HDF5 dataset. It must not
		 * 										already exist.
		 * @param 	values						1d array of integer 64 values ordered firstly
		 * 										by fastest direction.
		 * @param 	numValuesInEachDimension	Number of values in each dimension of the nd array to
		 * 										write. They are ordered from fastest index to slowest index.
		 * @param 	numDimensions				The number of the dimensions (n) of the nd array to write.
		 */
		DLL_IMPORT_OR_EXPORT void writeArrayNdOfInt64Values(const std::string & groupName,
			const std::string & name,
			const int64_t * values,
			const uint64_t * numValuesInEachDimension,
			unsigned int numDimensions) {
			writeArrayNd(groupName, name, COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64, values, numValuesInEachDimension, numDimensions);
		}

 		/**
 		 * Writes an nd array of unsigned integer 64 values into the HDF5 file by means of a single
 		 * dataset
 		 *
 		 * @param 	groupName					The name of the group where to create the nd array of
 		 * 										gSOAP unsigned long 64 values. This name must not contain '/'
 		 * 										character and must be directly contained in RESQML group.
 		 * @param 	name						The name of the nd array HDF5 dataset. It must not
 		 * 										already exist.
 		 * @param 	values						1d array of unsigned integer 64 values ordered firstly
 		 * 										by fastest direction.
 		 * @param 	numValuesInEachDimension	Number of values in each dimension of the nd array to
 		 * 										write. They are ordered from fastest index to slowest index.
 		 * @param 	numDimensions				The number of the dimensions (n) of the nd array to write.
 		 */
		DLL_IMPORT_OR_EXPORT void writeArrayNdOfUInt64Values(const std::string & groupName,
			const std::string & name,
			const uint64_t * values,
			const uint64_t * numValuesInEachDimension,
			unsigned int numDimensions) {
			writeArrayNd(groupName, name, COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT64, values, numValuesInEachDimension, numDimensions);
		}

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
		DLL_IMPORT_OR_EXPORT virtual void writeArrayNd(const std::string & groupName,
		  const std::string & name,
		  COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
		  const void * values,
		  const uint64_t * numValuesInEachDimension,
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
		DLL_IMPORT_OR_EXPORT virtual void createArrayNd(
		  const std::string& groupName,
		  const std::string& name,
		  COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
		  const uint64_t* numValuesInEachDimension,
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
		DLL_IMPORT_OR_EXPORT virtual void writeArrayNdSlab(
		  const std::string& groupName,
		  const std::string& name,
		  COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
		  const void* values,
		  const uint64_t* numValuesInEachDimension,
		  const uint64_t* offsetValuesInEachDimension,
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
		DLL_IMPORT_OR_EXPORT virtual void writeGroupAttributes(const std::string & groupName,
			const std::vector<std::string> & attributeNames,
			const std::vector<std::string> & values) = 0;

		/**
		 * Writes a single attribute into a group which contains an array of string values
		 *
		 * @param 	groupName	 	Name of the group.
		 * @param 	attributeName	Name of the attribute.
		 * @param 	values		 	Vector of string values.
		 */
		DLL_IMPORT_OR_EXPORT virtual void writeGroupAttribute(const std::string & groupName,
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
		DLL_IMPORT_OR_EXPORT virtual void writeGroupAttributes(const std::string & groupName,
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
		DLL_IMPORT_OR_EXPORT virtual void writeGroupAttributes(const std::string & groupName,
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
		DLL_IMPORT_OR_EXPORT virtual void writeDatasetAttributes(const std::string & datasetName,
			const std::vector<std::string> & attributeNames,
			const std::vector<std::string> & values) = 0;

		/**
		 * Writes a single attribute into a dataset which contain an array of strings values
		 *
		 * @param 	datasetName  	Name of the dataset.
		 * @param 	attributeName	Name of the attribute.
		 * @param 	values		 	Vector of string values.
		 */
		DLL_IMPORT_OR_EXPORT virtual void writeDatasetAttribute(const std::string & datasetName,
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
		DLL_IMPORT_OR_EXPORT virtual void writeDatasetAttributes(const std::string & datasetName,
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
		DLL_IMPORT_OR_EXPORT virtual void writeDatasetAttributes(const std::string & datasetName,
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
		DLL_IMPORT_OR_EXPORT virtual std::string readStringAttribute(const std::string & obj_name,
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
		DLL_IMPORT_OR_EXPORT virtual std::vector<std::string> readStringArrayAttribute(const std::string & obj_name,
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
		DLL_IMPORT_OR_EXPORT virtual double readDoubleAttribute(const std::string & obj_name,
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
		DLL_IMPORT_OR_EXPORT virtual int64_t readInt64Attribute(const std::string & obj_name,
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
		DLL_IMPORT_OR_EXPORT virtual void readArrayNdOfDoubleValues(const std::string & datasetName, double* values) = 0;

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
		DLL_IMPORT_OR_EXPORT virtual void readArrayNdOfDoubleValues(
		  const std::string & datasetName,
		  double* values,
		  uint64_t const * numValuesInEachDimension,
		  uint64_t const * offsetInEachDimension,
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
		DLL_IMPORT_OR_EXPORT virtual void readArrayNdOfDoubleValues(
			const std::string & datasetName, 
			double* values,
			uint64_t const * blockCountPerDimension,
			uint64_t const * offsetInEachDimension,
			uint64_t const * strideInEachDimension,
			uint64_t const * blockSizeInEachDimension,
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
		DLL_IMPORT_OR_EXPORT virtual void selectArrayNdOfValues(
			const std::string & datasetName,
			uint64_t const* blockCountPerDimension,
			uint64_t const* offsetInEachDimension,
			uint64_t const* strideInEachDimension,
			uint64_t const* blockSizeInEachDimension,
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
		DLL_IMPORT_OR_EXPORT virtual void readArrayNdOfDoubleValues(
			hdf5_hid_t dataset,
			hdf5_hid_t filespace,
			void* values,
			uint64_t slabSize) = 0;

		/**
		 * Reads an nd array of float values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of float values ordered firstly by fastest direction. The
		 * 							values must be pre-allocated and won't be freed by this method.
		 */
		DLL_IMPORT_OR_EXPORT virtual void readArrayNdOfFloatValues(const std::string & datasetName, float* values) = 0;

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
		DLL_IMPORT_OR_EXPORT virtual void readArrayNdOfFloatValues(
		  const std::string & datasetName,
		  float* values,
		  uint64_t const * numValuesInEachDimension,
		  uint64_t const * offsetInEachDimension,
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
		DLL_IMPORT_OR_EXPORT virtual void readArrayNdOfInt64Values(const std::string & datasetName, int64_t* values) = 0;

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
		DLL_IMPORT_OR_EXPORT virtual void readArrayNdOfInt64Values(
			const std::string & datasetName,
			int64_t* values,
			uint64_t const * numValuesInEachDimension,
			uint64_t const * offsetInEachDimension,
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
		DLL_IMPORT_OR_EXPORT virtual void readArrayNdOfUInt64Values(const std::string & datasetName, uint64_t* values) = 0;

		/**
		 * Reads an nd array of int values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of int values ordered firstly by fastest direction. The
		 * 							values must be pre-allocated and won't be freed by this method.
		 */
		DLL_IMPORT_OR_EXPORT virtual void readArrayNdOfIntValues(const std::string & datasetName, int* values) = 0;

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
		DLL_IMPORT_OR_EXPORT virtual void readArrayNdOfIntValues(
			const std::string & datasetName,
			int* values,
			uint64_t const * numValuesInEachDimension,
			uint64_t const * offsetInEachDimension,
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
		DLL_IMPORT_OR_EXPORT virtual void readArrayNdOfUIntValues(const std::string & datasetName, unsigned int* values) = 0;

		/**
		 * Reads an nd array of short values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of short values ordered firstly by fastest direction. The
		 * 							values must be pre-allocated and won't be freed by this method.
		 */
		DLL_IMPORT_OR_EXPORT virtual void readArrayNdOfShortValues(const std::string & datasetName, short* values) = 0;

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
		DLL_IMPORT_OR_EXPORT virtual void readArrayNdOfUShortValues(const std::string & datasetName, unsigned short* values) = 0;

		/**
		 * Reads an nd array of int 8 bits values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of int 8 bits values ordered firstly by fastest direction. The
		 * 							values must be pre-allocated and won't be freed by this method.
		 */
		DLL_IMPORT_OR_EXPORT virtual void readArrayNdOfInt8Values(const std::string & datasetName, int8_t* values) = 0;

		/**
		 * Reads an nd array of unsigned int 8 bits values stored in a specific dataset
		 *
		 * @exception	std::invalid_argument	If the nd array dataset cannot be opened or read.
		 *
		 * @param 	   	datasetName	The absolute name of the nd array dataset.
		 * @param [out]	values	   	1d array of unsigned int 8 bits values ordered firstly by fastest
		 * 							direction. The values must be pre-allocated and won't be freed by
		 * 							this method.
		 */
		DLL_IMPORT_OR_EXPORT virtual void readArrayNdOfUInt8Values(const std::string & datasetName, uint8_t* values) = 0;

		/**
		 * Checks whether an absolute path exists in the HDF5 file
		 *
		 * @param 	absolutePathInHdfFile	An absolute path in the HDF5 file.
		 *
		 * @returns	True if the absolute path exists, else false.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool exist(const std::string & absolutePathInHdfFile) const = 0;

		/**
		 * Checks whether a dataset is compressed or not
		 *
		 * @exception	invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @param 	datasetName	Name of the dataset.
		 *
		 * @returns	True if compressed, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isCompressed(const std::string & datasetName) = 0;
		
		/**
		* Set the maximum size for a chunk of a dataset only in case the HDF5 file is compressed.
		* Chunk dimensions, and consequently actual size, will be computed from this maximum chunk memory size.
		* Chunks dimensions are computed by reducing dataset dimensions from slowest to fastest until the max chunk size is honored.
		*
		* Example : Let's take a 3d property 4x3x2 (fastest from slowest) of double with a max chunk size of 100 bytes
		* The total size of this property is 4*3*2*8 = 192 bytes which is greater than 100 bytes, the max chunk size.
		* The computed chunk dimension will consequently be 4*3*1 = 96 which is lower than (not equal to) 100 bytes, the max chunk size.
		* If we would have set a max chunk size of 20 bytes, the chunk dimension would have been computed as 2*1*1 (16 bytes), etc...
		*
		* @param newMaxChunkSize The maximum chunk size to set in bytes.
		*/
		DLL_IMPORT_OR_EXPORT void setMaxChunkSize(unsigned int newMaxChunkSize) { maxChunkSize = newMaxChunkSize; }

		/**
		 * Get the number of elements in each chunk dimension of an HDF5 dataset.
		 * If the dataset is not compressed, then it returns an empty vector.
		 * uint32_t is returned instead of uint64_t cause of some SWIG usage. I cannot SWIG port std::vector<uint64_t>
		 * @param datasetName	The absolute name of the dataset which we want to get the number of elements from.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::vector<uint32_t> getElementCountPerChunkDimension(const std::string & datasetName) = 0;

		/**
		 * Instantiate and initialize the gsoap proxy.
		 * This method is defined in order to be used in derived class without having to link to generated gsoap files.
		 * It is public in order for the user to be able to call it in other languages (C#, Java, etc.) thanks to Swig.
		 *
		 * @param [in,out]	repo		The repository where the underlying gsoap proxy is going to be initialized.
		 * @param 		  	guid		The guid of the underlying gsoap proxy to be initialized.
		 * @param 		  	title		The title of the underlying gsoap proxy to be initialized.
		 * @param 			emlVersion	Desired eml Version such as 20 (for v2.0) or 23 (for v2.3) etc...
		*/
		DLL_IMPORT_OR_EXPORT void initGsoapProxy(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title, unsigned int emlVersion);

		static constexpr char const* MIME_TYPE = "application/x-hdf5";

	protected:
		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		AbstractHdfProxy(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : EpcExternalPartReference(partialObject) {}
		AbstractHdfProxy(const COMMON_NS::DataObjectReference& dor) : EpcExternalPartReference(dor) {}

		/**
		 * Constructor for serialization purpose
		 *
		 * @param 	packageDirAbsolutePath	The soap context where the underlying gSOAP proxy is going to
		 * 									be created.
		 * @param 	externalFilePath	  	Full pathname of the external file.
		 * @param 	hdfPermissionAccess   	(Optional) The hdf permission access.
		 */
		DLL_IMPORT_OR_EXPORT AbstractHdfProxy(const std::string & packageDirAbsolutePath, const std::string & externalFilePath, COMMON_NS::DataObjectRepository::openingMode hdfPermissionAccess = COMMON_NS::DataObjectRepository::openingMode::READ_ONLY) :
			packageDirectoryAbsolutePath(packageDirAbsolutePath), relativeFilePath(externalFilePath), openingMode(hdfPermissionAccess) {}

		/**
		 * Constructor for deserialization purpose
		 *
		 * @param 	fromGsoap	The deserialized EpcExternalPartReference into a gSoap proxy.
		 */
		AbstractHdfProxy(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap) :
			EpcExternalPartReference(fromGsoap) {}

		/** / The directory where the EPC document is stored. */
		std::string packageDirectoryAbsolutePath;
		/** / Must be relative to the location of the package */
		std::string relativeFilePath;
		/** The opening mode */
		COMMON_NS::DataObjectRepository::openingMode openingMode = COMMON_NS::DataObjectRepository::openingMode::READ_ONLY;
		/** The maximum size of an HDF5 to be written
		About 1e6 See https://support.hdfgroup.org/HDF5/doc/RM/RM_H5P.html#Property-SetChunkCache
		especially "In the absence of any cache settings, H5Dopen will by default create a 1 MB chunk cache for the opened dataset."*/
		unsigned int maxChunkSize = 1000000;
	};
}
