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

#include "../common/HdfProxyFactory.h"

#include "DataArrayBlockingSession.h"

namespace ETP_NS
{
	class DLL_IMPORT_OR_EXPORT EtpHdfProxy : public EML2_NS::AbstractHdfProxy
	{
	private:
		std::shared_ptr<DataArrayBlockingSession> session;
		unsigned int compressionLevel;

		std::string getUri() const;

	public:

		/**
		* Serialization context
		*/

		EtpHdfProxy(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath, COMMON_NS::DataObjectRepository::openingMode hdfPermissionAccess) :
			EML2_NS::AbstractHdfProxy(packageDirAbsolutePath, externalFilePath, hdfPermissionAccess) {
			initGsoapProxy(repo, guid, title, 20);
		}

		/**
		* Deserialization context
		*/
		EtpHdfProxy(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap) :
			EML2_NS::AbstractHdfProxy(fromGsoap), session(nullptr), compressionLevel(0) {}

		EtpHdfProxy(gsoap_eml2_1::_eml21__EpcExternalPartReference* fromGsoap) :
			EML2_NS::AbstractHdfProxy(fromGsoap), session(nullptr), compressionLevel(0) {}

		/**
		* Only for partial transfer
		*/
		EtpHdfProxy(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			EML2_NS::AbstractHdfProxy(partialObject), session(nullptr), compressionLevel(0) {}

		EtpHdfProxy(const COMMON_NS::DataObjectReference& dor) :
			EML2_NS::AbstractHdfProxy(dor), session(nullptr), compressionLevel(0) {}


		/**
		* Destructor.
		* Close the hdf file.
		*/
		~EtpHdfProxy() = default;

		std::shared_ptr<DataArrayBlockingSession> getSession() { return session; }
		void setSession(boost::asio::io_context& ioc, const std::string & host, const std::string & port, const std::string & target);

		/**
		* Open the file for reading and writing.
		* Does never overwrite an existing file but append to it if it already exists.
		*/
		void open();

		/**
		* It is opened if the ETP session is opened
		*/
		bool isOpened() const { return session != nullptr && !session->isWebSocketSessionClosed();  }

		/**
		* Close the file
		*/
		void close() { session->close(); }

		/*
		* Get the used (native) datatype in a dataset
		*/
		COMMON_NS::AbstractObject::hdfDatatypeEnum getHdfDatatypeInDataset(const std::string & groupName);

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
		 * Get the number of elements in each dimension in an HDF dataset of the proxy.
		 * @param datasetName	The absolute name of the dataset we want to get the number of elements.
		 */
		std::vector<unsigned long long> getElementCountPerDimension(const std::string & datasetName);

		/**
		* Get the number of elements in an HDF dataset of the proxy. The number of elements is get from all dimensions.
		* @param datasetName	The absolute name of the dataset we want to get the number of elements.
		*/
		signed long long getElementCount(const std::string & datasetName);

		/**
		* Set the new compression level which will be used for all data to be written
		* @param compressionLevel				Lower compression levels are faster but result in less compression. Range [0..9] is allowed.
		*/
		void setCompressionLevel(unsigned int newCompressionLevel) { if (newCompressionLevel > 9) compressionLevel = 9; else compressionLevel = newCompressionLevel; }

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

		void writeArrayNdOfInt64Values(const std::string & groupName,
			const std::string & name,
			const int64_t * values,
			const unsigned long long * numValuesInEachDimension,
			unsigned int numDimensions);

		/**
		* Write an array (potentially with multi dimensions) of gSoap unsigned long 64 values into the HDF file by means of a single dataset.
		* @param groupName						The name of the group where to create the array of int values.
		*										This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name							The name of the array of gSoap unsigned long 64 values hdf dataset. It must not already exist.
		* @param uint64_tValues					1d array of gSoap unsigned long 64 values ordered firstly by fastest direction.
		* @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param numDimensions					The number of the dimensions of the array to write
		*/
		void writeArrayNdOfUInt64Values(const std::string & groupName,
			const std::string & name,
			const uint64_t * values,
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

		int64_t readLongAttribute(const std::string & obj_name,
			const std::string & attr_name) const;

		/**
		* Read an array Nd of double values stored in a specific dataset
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated.
		*/
		void readArrayNdOfDoubleValues(const std::string & datasetName, double* values);

		/**
		 * Find the array associated with @p datasetName and read from it.
		 * @param datasetName                    The name of the array (potentially with multi dimensions).
		 * @param values                         1d array output of double values ordered firstly by fastest direction.
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
		*/
		void readArrayNdOfDoubleValues(
			hdf5_hid_t dataset,
			hdf5_hid_t filespace,
			void* values,
			unsigned long long slabSize);

		/**
		* Read an array Nd of float values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated.
		*/
		void readArrayNdOfFloatValues(const std::string & datasetName, float* values);

		/**
		* Find the array associated with @p datasetName and read from it.
		* @param datasetName                    The name of the array (potentially with multi dimensions).
		* @param values                         1d array output of float values ordered firstly by fastest direction.
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
		* @param values 		The values must be pre-allocated.
		*/
		void readArrayNdOfInt64Values(const std::string & datasetName, int64_t* values);

		/**
		* Find the array associated with datasetName and read from it.
		* @param datasetName                    The name of the array (potentially with multi dimensions).
		* @param values                         1d array output of long values ordered firstly by fastest direction.
		* @param numValuesInEachDimension       Number of values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param offsetValuesInEachDimension    Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param numDimensions                  The number of the dimensions of the array to read.
		*/
		void readArrayNdOfInt64Values(
			const std::string & datasetName,
			int64_t* values,
			unsigned long long const * numValuesInEachDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned int numDimensions
		);

		/**
		* Read an array Nd of unsigned long values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated.
		*/
		void readArrayNdOfUInt64Values(const std::string & datasetName, uint64_t* values);

		/**
		* Read an array Nd of int values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated.
		*/
		void readArrayNdOfIntValues(const std::string & datasetName, int* values);

		/**
		* Find the array associated with datasetName and read from it.
		* @param datasetName                    The name of the array (potentially with multi dimensions).
		* @param values                         1d array output of int values ordered firstly by fastest direction.
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
		* Don"t forget to delete the allocated pointer when no more necessary.
		* @param datasetName	The absolute dataset name where to read the values
		*/
		void readArrayNdOfUIntValues(const std::string & datasetName, unsigned int* values);

		/**
		* Read an array Nd of short values stored in a specific dataset
		* Don"t forget to delete the allocated pointer when no more necessary.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated.
		*/
		void readArrayNdOfShortValues(const std::string & datasetName, short* values);

		/**
		* Read an array Nd of unsigned short values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated.
		*/
		void readArrayNdOfUShortValues(const std::string & datasetName, unsigned short* values);

		/**
		* Read an array Nd of char values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		* @param values 		The values must be pre-allocated.
		*/
		void readArrayNdOfCharValues(const std::string & datasetName, char* values);

		/**
		* Read an array Nd of unsigned char values stored in a specific dataset.
		* @param datasetName	The absolute dataset name where to read the values
		*/
		void readArrayNdOfUCharValues(const std::string & datasetName, unsigned char* values);

		/**
		* Read the dimensions of an array stored in a specific dataset
		* @param datasetName	The absolute dataset name where to read the array dimensions
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

		/**
		* The standard XML namespace for serializing this data object.
		*/
		static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		std::string getXmlNamespace() const { return XML_NS; }
	};

	class DLL_IMPORT_OR_EXPORT EtpHdfProxyFactory : public COMMON_NS::HdfProxyFactory
	{
	public:
		/**
		* Only to be used in partial transfer context
		*/
		EML2_NS::AbstractHdfProxy* make(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) {
			return new EtpHdfProxy(partialObject);
		}
		EML2_NS::AbstractHdfProxy* make(const COMMON_NS::DataObjectReference& dor) {
			return new EtpHdfProxy(dor);
		}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		EML2_NS::AbstractHdfProxy* make(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap) {
			return new EtpHdfProxy(fromGsoap);
		}

		EML2_NS::AbstractHdfProxy* make(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			const std::string & packageDirAbsolutePath, const std::string & externalFilePath,
			COMMON_NS::DataObjectRepository::openingMode hdfPermissionAccess = COMMON_NS::DataObjectRepository::openingMode::READ_ONLY) {
			return new EtpHdfProxy(repo, guid, title, packageDirAbsolutePath, externalFilePath, hdfPermissionAccess);
		}
	};
}
