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

		void setRootPath(const std::string& rootPath);
		void setRelativePath(const std::string& relPath);
		void setOpeningMode(COMMON_NS::DataObjectRepository::openingMode openingMode_);
	
		std::string getRelativePath();

		virtual void open() = 0;
		virtual bool isOpened() const = 0;
		virtual void close() = 0;

		virtual COMMON_NS::AbstractObject::hdfDatatypeEnum getHdfDatatypeInDataset(const std::string & datasetName) = 0;
		virtual int getHdfDatatypeClassInDataset(const std::string & datasetName) = 0;

		virtual void writeItemizedListOfList(const std::string & groupName,
			const std::string & name,
			hdf5_hid_t cumulativeLengthDatatype,
			const void * cumulativeLength,
			unsigned long long cumulativeLengthSize,
			hdf5_hid_t elementsDatatype,
			const void * elements,
			unsigned long long elementsSize) = 0;
		
		virtual unsigned int getDimensionCount(const std::string & datasetName) = 0;
		virtual std::vector<unsigned long long> getElementCountPerDimension(const std::string & datasetName) = 0;
		virtual signed long long getElementCount(const std::string & datasetName) = 0;

		virtual void setCompressionLevel(unsigned int newCompressionLevel) = 0;

		virtual void writeArrayNdOfFloatValues(const std::string & groupName,
		  const std::string & name,
		  const float * floatValues,
		  const unsigned long long * numValuesInEachDimension,
		  unsigned int numDimensions) = 0;
		virtual void writeArrayNdOfDoubleValues(const std::string & groupName,
		  const std::string & name,
		  const double * dblValues,
		  const unsigned long long * numValuesInEachDimension,
		  unsigned int numDimensions) = 0;
		virtual void writeArrayNdOfCharValues(const std::string & groupName,
			const std::string & name,
			const char * intValues,
			const unsigned long long * numValuesInEachDimension,
			unsigned int numDimensions) = 0;
		virtual void writeArrayNdOfIntValues(const std::string & groupName,
		  const std::string & name,
		  const int * intValues,
		  const unsigned long long * numValuesInEachDimension,
		  unsigned int numDimensions) = 0;
 		virtual void writeArrayNdOfInt64Values(const std::string & groupName,
			const std::string & name,
			const int64_t * values,
			const unsigned long long * numValuesInEachDimension,
			unsigned int numDimensions) = 0;
 		virtual void writeArrayNdOfUInt64Values(const std::string & groupName,
			const std::string & name,
			const uint64_t * values,
			const unsigned long long * numValuesInEachDimension,
			unsigned int numDimensions) = 0;
		virtual void writeArrayNd(const std::string & groupName,
		  const std::string & name,
		  hdf5_hid_t datatype,
		  const void * values,
		  const unsigned long long * numValuesInEachDimension,
		  unsigned int numDimensions) = 0;
		virtual void createArrayNd(
		  const std::string& groupName,
		  const std::string& name,
		  hdf5_hid_t datatype,
		  const unsigned long long* numValuesInEachDimension,
		  unsigned int numDimensions
		  ) = 0;
		virtual void writeArrayNdSlab(
		  const std::string& groupName,
		  const std::string& name,
		  hdf5_hid_t datatype,
		  const void* values,
		  const unsigned long long* numValuesInEachDimension,
		  const unsigned long long* offsetValuesInEachDimension,
		  unsigned int numDimensions
		  ) = 0;
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
		virtual std::vector<unsigned long long> readArrayDimensions(const std::string & datasetName) = 0;
		
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
		/**
		 * Gets the size of this graphical information set
		 *
		 * @exception	std::range_error	If the size is strictly greater than unsigned int max.
		 *
		 * @returns	The size of this graphical information set.
		 */
		unsigned int getGraphicalInformationSetCount() const;
		
		/**
		 * Gets the UUID of the object which receives some graphical information at a particular index
		 * of the graphical information set and at a particular target index.
		 *
		 * @exception	std::range_error	If @p index is out of range.
		 *
		 * @param 	graphicalInformationIndex	Zero-based index of the graphical information in the GraphicalInformationSet
		 * @param	targetIndex					Zero-based index of the data object reference in the graphical information
		 *
		 * @returns	The UUUID of the object which receives some graphical information at @p graphicalInformationIndex and target @p targetIndex.
		 */
		std::string getTargetObjectUuid(unsigned int graphicalInformationIndex, unsigned int targetIndex) const;

		/**
		 * Gets the data object which receives some graphical information at a particular index of the
		 * graphical information set and at a particular target index.
		 *
		 * @param 	graphicalInformationIndex	Zero-based index of the graphical information in the GraphicalInformationSet
		 * @param	targetIndex					Zero-based index of the data object reference in the graphical information
		 *
		 * @returns	The data object which receives some graphical information at @p graphicalInformationIndex and target @p targetIndex.
		 */
		COMMON_NS::AbstractObject* getTargetObject(unsigned int graphicalInformationIndex, unsigned int targetIndex) const;

		/**
		 * Query if a given data object has some graphical information. If it has no direct graphical
		 * information (see {@link hasDirectGraphicalInformation}) and it is a property, we also check
		 * that its property kind has some
		 *
		 * @exception	std::invalid_argument	If the target object is null.
		 *
		 * @param 	targetObject	The data object we want to test for having some graphical information.
		 *
		 * @returns	True if @p targetObject (or its property kind) has some graphical information, else false.
		 */
		bool hasGraphicalInformation(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Query if a given data object has a default color. It only looks at direct color association (see
		 * {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If the target object is null.
		 *
		 * @param 	targetObject	The data object we want to test for having a default color.
		 *
		 * @returns	True @p targetObject has one default color, else false.
		 */
		bool hasDefaultColor(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the default hue of a given data object. It only looks at direct color association (see
		 * {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If @p targetObject has no default color.
		 *
		 * @param 	targetObject	The data object for which we look for the default hue.
		 *
		 * @returns	The default hue of @p targetObject in the range [0, 360].
		 */
		double getDefaultHue(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the default saturation of a given data object. It only looks at direct color association
		 * (see {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If @p targetObject has no default color.
		 *
		 * @param 	targetObject	The data object for which we look for the default saturation.
		 *
		 * @returns	The default saturation of @p targetObject in the range [0, 1].
		 */
		double getDefaultSaturation(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the default color value of a given data object. It only looks at direct color
		 * association (see {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If @p targetObject has no default color.
		 *
		 * @param 	targetObject	The data object for which we look for the default color value.
		 *
		 * @returns	The default color value of @p targetObject in the range [0, 1].
		 */
		double getDefaultValue(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the default alpha value of a given data object. It only looks at direct color
		 * association (see {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If @p targetObject has no default color.
		 *
		 * @param 	targetObject	The data object for which we look for the default alpha value.
		 *
		 * @returns	The default alpha value in the range [0, 1] (0 means transparent and 1 means opaque).
		 */
		double getDefaultAlpha(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the default RGB color (https://en.wikipedia.org/wiki/RGB_color_space) of a given data
		 * object. It only looks at direct color association (see {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If @p targetObject has no default color.
		 *
		 * @param 	   	targetObject	The data object for which we look for the default RGB color.
		 * @param [out]	red				Red value in the range [0, 1].
		 * @param [out]	green			Green value in the range [0, 1].
		 * @param [out]	blue			Blue value in the range [0, 1].
		 */
		void getDefaultRgbColor(COMMON_NS::AbstractObject const* targetObject, double& red, double& green, double& blue) const;

		/**
		 * Gets the default RGB color (https://en.wikipedia.org/wiki/RGB_color_space) of a given data
		 * object. It only looks at direct color association (see {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If @p targetObject has no default color.
		 *
		 * @param 	   	targetObject	The data object for which we look for the default RGB color.
		 * @param [out]	red				Red value in the range [0, 255].
		 * @param [out]	green			Green value in the range [0, 255].
		 * @param [out]	blue			Blue value in the range [0, 255].
		 */
		void getDefaultRgbColor(COMMON_NS::AbstractObject const* targetObject, unsigned int& red, unsigned int& green, unsigned int& blue) const;

		/**
		 * Query if a given data object has a default color title. It only looks at direct color
		 * association (see {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If @p targetObject has no default color.
		 *
		 * @param 	targetObject	The data object for which we look for a default color title.
		 *
		 * @returns	True if @p targetObject has a default color title, else false.
		 */
		bool hasDefaultColorTitle(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the default color title of a given data object. It only looks at direct color
		 * association (see {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If @p targetObject has no default color or if its default
		 * 										color has no title.
		 *
		 * @param 	targetObject	The data object for which we look for the default color title.
		 *
		 * @returns	The default title.
		 */
		std::string getDefaultColorTitle(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Sets the default HSV color (https://en.wikipedia.org/wiki/HSV_color_space) of a given data
		 * object
		 *
		 * @exception	std::invalid_argument	If @p targetObject is null or if it is not a feature,
		 * 										interpretation, representation or wellbore marker.
		 * @exception	std::invalid_argument	If @p hue is out of range [0, 360].
		 * @exception	std::invalid_argument	If @p saturation, @p value or @p alpha is out of range [0,
		 * 										1].
		 *
		 * @param [in]	targetObject	The data object which receives the color.
		 * @param 	  	hue				The hue angle in degrees in range [0, 360].
		 * @param 	  	saturation  	The saturation value in range [0, 1].
		 * @param 	  	value			The color value in range [0, 1].
		 * @param 	  	alpha			(Optional) The alpha value in range [0, 1] for transparency
		 * 								channel (0 means transparent and 1 means opaque). Default value is 1.
		 * @param 	  	colorTitle  	(Optional) The title of the given HSV color. It is not set if
		 * 								title is empty (default).
		 */
		void setDefaultHsvColor(COMMON_NS::AbstractObject* targetObject, double hue, double saturation, double value, double alpha = 1.0, std::string const& colorTitle = "");

		/**
		 * Sets the default RGB color https://en.wikipedia.org/wiki/RGB_color_space of a given data
		 * object
		 *
		 * @exception	std::invalid_argument	If @p targetObject is null or if it is not a feature,
		 * 										interpretation, representation or wellbore marker.
		 * @exception	std::invalid_argument	If @p red, @p green, @p blue or @p alpha is out of range
		 * 										[0,
		 * 										1].
		 *
		 * @param [in]	targetObject	The data object which receives the color.
		 * @param 	  	red				Red value in range [0, 1].
		 * @param 	  	green			Green value in range [0, 1].
		 * @param 	  	blue			Blue value in range [0, 1].
		 * @param 	  	alpha			(Optional) The alpha value in range [0, 1] for transparency
		 * 								channel (0 means transparent and 1 means opaque). Default value is 1.
		 * @param 	  	colorTitle  	(Optional) The title of the given HSV color. It is not set if
		 * 								title is empty (default).
		 */
		void setDefaultRgbColor(COMMON_NS::AbstractObject* targetObject, double red, double green, double blue, double alpha = 1.0, std::string const& colorTitle = "");

		/**
		 * Sets the default RGB color https://en.wikipedia.org/wiki/RGB_color_space of a given data
		 * object
		 *
		 * @exception	std::invalid_argument	If @p targetObject is null or if it is not a feature,
		 * 										interpretation, representation or wellbore marker.
		 * @exception	std::invalid_argument	If @p red, @p green, @p blue or @p alpha is out of range
		 * 										[0,
		 * 										255].
		 * @exception	std::invalid_argument	If @p alpha is out of range [0,1].
		 *
		 * @param [in]	targetObject	The data object which receives the color.
		 * @param 	  	red				Red value in range [0, 255].
		 * @param 	  	green			Green value in range [0, 255].
		 * @param 	  	blue			Blue value in range [0, 255].
		 * @param 	  	alpha			(Optional) The alpha value in range [0, 1] for transparency
		 * 								channel (0 means transparent and 1 means opaque). Default value is 1.
		 * @param 	  	colorTitle  	(Optional) The title of the given HSV color. It is not set if
		 * 								title is empty (default).
		 */
		void setDefaultRgbColor(COMMON_NS::AbstractObject* targetObject, unsigned int red, unsigned int green, unsigned int blue, double alpha = 1.0, std::string const& colorTitle = "");

		/**
		 * Query if a given data object has a discrete color map. If it has not and it is a property, we
		 * also look for its property kind discrete color map
		 *
		 * @exception	std::invalid_argument	If @p targetObject is null.
		 *
		 * @param 	targetObject	The data object for which we look for a discrete color map.
		 *
		 * @returns	True if @p targetObject (or its property kind) has a discrete color map, else false.
		 */
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
		void pushBackTimestamp(time_t timestamp);
		unsigned int getTimestampIndex(time_t timestamp) const;
		unsigned int getTimestampCount() const;
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
		void pushBackParameter(const std::string title, const std::string & value);
		void pushBackParameter(const std::string title, int64_t value);
		void pushBackParameter(const std::string title, COMMON_NS::AbstractObject* resqmlObject);
		
		unsigned int getParameterCount() const;
		unsigned int getParameterCount(const std::string & paramTitle) const;

		const std::string & getParameterTitle(unsigned int index) const;

		bool isAFloatingPointQuantityParameter(const std::string & paramTitle) const;
		bool isAFloatingPointQuantityParameter(unsigned int index) const;
		double getFloatingPointQuantityParameterValue(unsigned int index) const;

		bool isAnIntegerQuantityParameter(const std::string & paramTitle) const;
		bool isAnIntegerQuantityParameter(unsigned int index) const;
		int64_t getIntegerQuantityParameterValue(unsigned int index) const;

		bool isAStringParameter(const std::string & paramTitle) const;
		bool isAStringParameter(unsigned int index) const;
		const std::string & getStringParameterValue(unsigned int index) const;

		bool isAResqmlObjectParameter(const std::string & paramTitle) const;
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
