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
%{
#include "../src/eml2/Activity.h"
#include "../src/eml2/ActivityTemplate.h"
#include "../src/eml2/GraphicalInformationSet.h"
#include "../src/eml2/PropertyKind.h"
#include "../src/eml2/TimeSeries.h"
%}

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace EML2_NS::AbstractHdfProxy;
	%nspace EML2_NS::Activity;
	%nspace EML2_NS::ActivityTemplate;
	%nspace EML2_NS::EpcExternalPartReference;
	%nspace EML2_NS::GraphicalInformationSet;
	%nspace EML2_NS::PropertyKind;
	%nspace EML2_NS::TimeSeries;
#endif

%module(directors="1") fesapi
%feature("director") EML2_NS::AbstractHdfProxy;

namespace EML2_NS
{
	%nodefaultctor; // Disable creation of default constructors
	
	/************ HDF *******************/
	class EpcExternalPartReference : public COMMON_NS::AbstractObject {
	public:
	};
	
	/*
	No wrappers will be generated for fesapi AbstractHdfProxy specializations.
	Wrapping AbstractHdfProxy suffices when no specialized HDF proxy is required 
	in the target language. Example of specialized HDF proxy in C# and how it should 
	be used is provided in the C# example (see HdfProxyFactoryExample.cs and
	HdfProxyExample.cs).
	*/
#if defined(SWIGPYTHON)
	%rename(Eml2_AbstractHdfProxy) AbstractHdfProxy;
#endif
	class AbstractHdfProxy : public EpcExternalPartReference
	{
	public:
		virtual ~AbstractHdfProxy();

		/**
		 * Sets the path of the directory containing the EPC file associated to this HDF5 file
		 *
		 * @param 	rootPath	Path of the directory containing the EPC file.
		 */
		void setRootPath(const std::string& rootPath);

		/**
		 * Sets the relative path of the HDF5 file regarding the path of the directory containing the EPC
		 * file associated to this HDF5 file
		 *
		 * @param 	relPath	Relative path of the HDF5 file.
		 */
		void setRelativePath(const std::string& relPath);

		/**
		 * Sets the rights when opening the HDF5 file
		 *
		 * @param 	openingMode_	The opening mode of the HDF5 file.
		 */
		void setOpeningMode(COMMON_NS::DataObjectRepository::openingMode openingMode_);

		/**
		 * Gets the relative path of the HDF5 file regarding the path of the directory containing the
		 * EPC file associated to this HDF5 file
		 *
		 * @returns	The relative path of the HDF5 file.
		 */
		std::string getRelativePath();

		virtual void open() = 0;

		/**
		 * Checks if the HDF5 file is open or not
		 *
		 * @returns	True if opened, false if not.
		 */
		virtual bool isOpened() const = 0;

		/** Closes the HDF5 file */
		virtual void close() = 0;

		/**
		 * Gets the native datatype of a dataset
		 *
		 * @param 	datasetName	Name of the dataset.
		 *
		 * @returns	The native datatype identifier of the dataset if successful, otherwise returns unknown.
		 */
		virtual COMMON_NS::AbstractObject::numericalDatatypeEnum getNumericalDatatype(const std::string & datasetName) = 0;

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
		 * @param 	elementsSize				Size of the elements array. It must be equal to
		 *										cumulativeLength[cumulativeLengthSize-1].
		 */
		virtual void writeItemizedListOfList(const std::string & groupName,
			const std::string & name,
			COMMON_NS::AbstractObject::numericalDatatypeEnum cumulativeLengthDatatype,
			const void * cumulativeLength,
			unsigned long long cumulativeLengthSize,
			COMMON_NS::AbstractObject::numericalDatatypeEnum elementsDatatype,
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
		uint64_t getDimensionCount(const std::string & datasetName);

		/**
		 * Get the number of elements in each dimension of an HDF5 dataset.
		 * @param datasetName	The absolute name of the dataset which we want to get the number of elements from.
		 */
		virtual std::vector<unsigned long long> getElementCountPerDimension(const std::string & datasetName) = 0;

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
		signed long long getElementCount(const std::string & datasetName);

		/**
		 * Sets the new compression level which will be used for all data to be written
		 *
		 * @param 	newCompressionLevel	The new compression level in range [0..9]. Lower compression
		 * 								levels are faster but result in less compression.
		 */
		virtual void setCompressionLevel(unsigned int newCompressionLevel) = 0;

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
		void writeArrayNdOfFloatValues(const std::string & groupName,
		  const std::string & name,
		  const float * floatValues,
		  const unsigned long long * numValuesInEachDimension,
		  unsigned int numDimensions);

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
		void writeArrayNdOfDoubleValues(const std::string & groupName,
		  const std::string & name,
		  const double * dblValues,
		  const unsigned long long * numValuesInEachDimension,
		  unsigned int numDimensions);

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
		void writeArrayNdOfCharValues(const std::string & groupName,
			const std::string & name,
			const char * intValues,
			const unsigned long long * numValuesInEachDimension,
			unsigned int numDimensions);

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
		void writeArrayNdOfIntValues(const std::string & groupName,
		  const std::string & name,
		  const int * intValues,
		  const unsigned long long * numValuesInEachDimension,
		  unsigned int numDimensions);

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
 		void writeArrayNdOfInt64Values(const std::string & groupName,
			const std::string & name,
			const int64_t * values,
			const unsigned long long * numValuesInEachDimension,
			unsigned int numDimensions);

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
 		void writeArrayNdOfUInt64Values(const std::string & groupName,
			const std::string & name,
			const uint64_t * values,
			const unsigned long long * numValuesInEachDimension,
			unsigned int numDimensions);

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
		  COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
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
		  COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
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
		  COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
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
		virtual void writeGroupAttribute(const std::string & groupName,
			const std::string & attributeName,
			const std::vector<std::string> & values) = 0;
		virtual void writeGroupAttributes(const std::string & groupName,
			const std::vector<std::string> & attributeNames,
			const std::vector<double> & values) = 0;
		virtual void writeGroupAttributes(const std::string & groupName,
			const std::vector<std::string> & attributeNames,
			const std::vector<int> & values) = 0;
		virtual void writeDatasetAttributes(const std::string & datasetName,
			const std::vector<std::string> & attributeNames,
			const std::vector<std::string> & values) = 0;
		virtual void writeDatasetAttribute(const std::string & datasetName,
			const std::string & attributeName,
			const std::vector<std::string> & values) = 0;
		virtual void writeDatasetAttributes(const std::string & datasetName,
			const std::vector<std::string> & attributeNames,
			const std::vector<double> & values) = 0;
		virtual void writeDatasetAttributes(const std::string & datasetName,
			const std::vector<std::string> & attributeNames,
			const std::vector<int> & values) = 0;

		virtual std::string readStringAttribute(const std::string & obj_name,
			const std::string & attr_name) const = 0;
		virtual std::vector<std::string> readStringArrayAttribute(const std::string & obj_name,
			const std::string & attr_name) const = 0;
		virtual double readDoubleAttribute(const std::string & obj_name,
			const std::string & attr_name) const = 0;
		virtual int64_t readLongAttribute(const std::string & obj_name,
			const std::string & attr_name) const = 0;
		virtual void readArrayNdOfDoubleValues(const std::string & datasetName, double* values) = 0;
		virtual void readArrayNdOfDoubleValues(
		  const std::string & datasetName,
		  double* values,
		  unsigned long long const * numValuesInEachDimension,
		  unsigned long long const * offsetInEachDimension,
		  unsigned int numDimensions
		  ) = 0;
		virtual void readArrayNdOfDoubleValues(
			const std::string & datasetName, 
			double* values,
			unsigned long long const * blockCountPerDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned long long const * strideInEachDimension,
			unsigned long long const * blockSizeInEachDimension,
			unsigned int numDimensions) = 0;
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
		virtual void readArrayNdOfDoubleValues(
			hdf5_hid_t dataset,
			hdf5_hid_t filespace,
			void* values,
			unsigned long long slabSize) = 0;
		virtual void readArrayNdOfFloatValues(const std::string & datasetName, float* values) = 0;
		virtual void readArrayNdOfFloatValues(
		  const std::string & datasetName,
		  float* values,
		  unsigned long long const * numValuesInEachDimension,
		  unsigned long long const * offsetInEachDimension,
		  unsigned int numDimensions
		  ) = 0;
		virtual void readArrayNdOfInt64Values(const std::string & datasetName, int64_t* values) = 0;
		virtual void readArrayNdOfInt64Values(
			const std::string & datasetName,
			int64_t* values,
			unsigned long long const * numValuesInEachDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned int numDimensions) = 0;
		virtual void readArrayNdOfUInt64Values(const std::string & datasetName, uint64_t* values) = 0;
		virtual void readArrayNdOfIntValues(const std::string & datasetName, int* values) = 0;
		virtual void readArrayNdOfIntValues(
			const std::string & datasetName,
			int* values,
			unsigned long long const * numValuesInEachDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned int numDimensions
		) = 0;
		virtual void readArrayNdOfUIntValues(const std::string & datasetName, unsigned int* values) = 0;
		virtual void readArrayNdOfShortValues(const std::string & datasetName, short* values) = 0;
		virtual void readArrayNdOfUShortValues(const std::string & datasetName, unsigned short* values) = 0;
		virtual void readArrayNdOfCharValues(const std::string & datasetName, char* values) = 0;
		virtual void readArrayNdOfUCharValues(const std::string & datasetName, unsigned char* values) = 0;
		
		virtual bool exist(const std::string & absolutePathInHdfFile) const = 0;
		
		virtual bool isCompressed(const std::string & datasetName) = 0;
		
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
		void setMaxChunkSize(unsigned int newMaxChunkSize);
		
		/**
		 * Get the number of elements in each chunk dimension of an HDF5 dataset.
		 * If the dataset is not compressed, then it returns an empty vector.
		 * @param datasetName	The absolute name of the dataset which we want to get the number of elements from.
		 */
		virtual std::vector<unsigned long long> getElementCountPerChunkDimension(const std::string & datasetName) = 0;

		void initGsoapProxy(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, unsigned int emlVersion);
				
	protected:
	
		AbstractHdfProxy(const std::string & packageDirAbsolutePath, const std::string & externalFilePath, COMMON_NS::DataObjectRepository::openingMode hdfPermissionAccess = COMMON_NS::DataObjectRepository::openingMode::READ_ONLY);
		AbstractHdfProxy(const COMMON_NS::DataObjectReference& dor);
		
	};
	
	/************ GraphicalInformationSet **************/
	
#if defined(SWIGPYTHON)
	%rename(Eml2_GraphicalInformationSet) GraphicalInformationSet;
#endif
	class GraphicalInformationSet : public COMMON_NS::AbstractObject
	{
	public:
		unsigned int getGraphicalInformationSetCount() const;
		std::string getTargetObjectUuid(uint64_t index) const;
		COMMON_NS::AbstractObject* getTargetObject(uint64_t index) const;
		bool hasGraphicalInformation(COMMON_NS::AbstractObject const* targetObject) const;
		
		bool hasDefaultColor(COMMON_NS::AbstractObject const* targetObject) const;
		double getDefaultHue(COMMON_NS::AbstractObject const* targetObject) const;
		double getDefaultSaturation(COMMON_NS::AbstractObject const* targetObject) const;
		double getDefaultValue(COMMON_NS::AbstractObject const* targetObject) const;
		double getDefaultAlpha(COMMON_NS::AbstractObject const* targetObject) const;
		void getDefaultRgbColor(COMMON_NS::AbstractObject const* targetObject, double& red, double& green, double& blue) const;
		void getDefaultRgbColor(COMMON_NS::AbstractObject const* targetObject, unsigned int& red, unsigned int& green, unsigned int& blue) const;
		bool hasDefaultColorTitle(COMMON_NS::AbstractObject const* targetObject) const;
		std::string getDefaultColorTitle(COMMON_NS::AbstractObject const* targetObject) const;
		void setDefaultHsvColor(COMMON_NS::AbstractObject * targetObject, double hue, double saturation, double value, double alpha = 1.0, std::string const& colorTitle = "");
		void setDefaultRgbColor(COMMON_NS::AbstractObject * targetObject, double red, double green, double blue, double alpha = 1.0, std::string const& colorTitle = "");
		void setDefaultRgbColor(COMMON_NS::AbstractObject * targetObject, unsigned int red, unsigned int green, unsigned int blue, double alpha = 1.0, std::string const& colorTitle = "");

		bool hasDiscreteColorMap(COMMON_NS::AbstractObject const* targetObject) const;
		std::string getDiscreteColorMapUuid(COMMON_NS::AbstractObject const* targetObject) const;
		RESQML2_NS::DiscreteColorMap* getDiscreteColorMap(COMMON_NS::AbstractObject const* targetObject) const;
		void setDiscreteColorMap(COMMON_NS::AbstractObject * targetObject, RESQML2_NS::DiscreteColorMap* discreteColorMap,
			bool useReverseMapping = false, bool useLogarithmicMapping = false);

		bool hasContinuousColorMap(COMMON_NS::AbstractObject const* targetObject) const;
		std::string getContinuousColorMapUuid(COMMON_NS::AbstractObject const* targetObject) const;
		RESQML2_NS::ContinuousColorMap* getContinuousColorMap(COMMON_NS::AbstractObject const* targetObject) const;
		void setContinuousColorMap(COMMON_NS::AbstractObject * targetObject, RESQML2_NS::ContinuousColorMap* continuousColorMap,
			bool useReverseMapping = false, bool useLogarithmicMapping = false);

		bool hasColorMapMinMax(COMMON_NS::AbstractObject const* targetObject) const;
		double getColorMapMin(COMMON_NS::AbstractObject const* targetObject) const;
		double getColorMapMax(COMMON_NS::AbstractObject const* targetObject) const;
		void setColorMapMinMax(COMMON_NS::AbstractObject const* targetObject, double min, double max) const;

		bool hasValueVectorIndex(COMMON_NS::AbstractObject const* targetObject);
		int64_t getValueVectorIndex(COMMON_NS::AbstractObject const* targetObject);
		void setValueVectorIndex(COMMON_NS::AbstractObject const* targetObject, int64_t valueVectorIndex);

		static void rgbToHsv(double red, double green, double blue, double& hue, double& saturation, double& value);
		static void rgbToHsv(unsigned int red, unsigned int green, unsigned int blue, double& hue, double& saturation, double& value);
		static void hsvToRgb(double hue, double saturation, double value, double& red, double& green, double& blue);
		static void hsvToRgb(double hue, double saturation, double value, unsigned int& red, unsigned int& green, unsigned int& blue);
	};
	
	/************ Property **************/
	
	class PropertyKind : public COMMON_NS::AbstractObject {
	public:
		std::string getBaseUomAsString() const;
	};
	
	class TimeSeries : public COMMON_NS::AbstractObject
	{
	public:

		/**
		 * Pushes back an timestamp into this time series.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @param 	timestamp	The timestamp to push back.
		 */
		void pushBackTimestamp(time_t timestamp);

		/**
		 * Gets the index of a given timestamp in this time series.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p timestamp has not been found in this time series.
		 *
		 * @param 	timestamp	The timestamp we look for.
		 * @param 	yearOffset	Indicates that the dateTime attribute must be translated according to this value.
		 *
		 * @returns	The index of @p timestamp in this time series.
		 */
		uint64_t getTimestampIndex(time_t timestamp, LONG64 yearOffset = 0) const;

		/**
		 * Gets a timestamp at a particular index of this time series.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the timestamp we look for.
		 *
		 * @returns	The timestamp at position @p index.
		 */
		time_t getTimestamp(unsigned int index) const;
	};
	
	/************ Activity **************/

	class ActivityTemplate : public COMMON_NS::AbstractObject
	{
	public:
		void pushBackParameter(const std::string & title,
			bool isInput, bool isOutput,
			unsigned int minOccurs, int maxOccurs);
		void pushBackParameter(const std::string & title,
			bool isInput, bool isOutput,
			unsigned int minOccurs, int maxOccurs,
			std::string resqmlObjectContentType);
		bool isAnExistingParameter(const std::string & paramTitle) const;
		const unsigned int getParameterCount() const;
		const std::string & getParameterTitle(unsigned int index) const;
		bool getParameterIsInput(unsigned int index) const;
		bool getParameterIsInput(const std::string & paramTitle) const;
		bool getParameterIsOutput(unsigned int index) const;
		bool getParameterIsOutput(const std::string & paramTitle) const;
		int64_t getParameterMinOccurences(unsigned int index) const;
		int64_t getParameterMinOccurences(const std::string & paramTitle) const;
		int64_t getParameterMaxOccurences(unsigned int index) const;
		int64_t getParameterMaxOccurences(const std::string & paramTitle) const;
	};

	class Activity : public COMMON_NS::AbstractObject
	{
	public:
		void pushBackParameter(const std::string& title, const std::string& value);
		void pushBackParameter(const std::string& title, int64_t value);
		void pushBackParameter(const std::string& title, COMMON_NS::AbstractObject* resqmlObject);
		
		unsigned int getParameterCount() const;
		unsigned int getParameterCount(const std::string& paramTitle) const;

		const std::string & getParameterTitle(unsigned int index) const;

		bool isAFloatingPointQuantityParameter(const std::string& paramTitle) const;
		bool isAFloatingPointQuantityParameter(unsigned int index) const;
		double getFloatingPointQuantityParameterValue(unsigned int index) const;

		bool isAnIntegerQuantityParameter(const std::string& paramTitle) const;
		bool isAnIntegerQuantityParameter(unsigned int index) const;
		int64_t getIntegerQuantityParameterValue(unsigned int index) const;

		bool isAStringParameter(const std::string& paramTitle) const;
		bool isAStringParameter(unsigned int index) const;
		const std::string & getStringParameterValue(unsigned int index) const;

		bool isAResqmlObjectParameter(const std::string& paramTitle) const;
		bool isAResqmlObjectParameter(unsigned int index) const;
		COMMON_NS::AbstractObject* getResqmlObjectParameterValue(unsigned int index) const;

		void setActivityTemplate(ActivityTemplate* activityTemplate);
		ActivityTemplate* getActivityTemplate() const;
	};
}

%include "swigEml2_1Include.i"
#ifdef WITH_RESQML2_2
%include "swigEml2_3Include.i"
#endif
