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
	class EpcExternalPartReference : public COMMON_NS::AbstractObject {};
	
	/*
	No wrappers will be generated for fesapi AbstractHdfProxy specializations.
	Wrapping AbstractHdfProxy suffices when no specialized HDF proxy is required 
	in the target language. Example of specialized HDF proxy in C# and how it should 
	be used is provided in the C# example (see HdfProxyFactoryExample.cs and
	HdfProxyExample.cs).
	*/
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
 		virtual void writeArrayNdOfLong64Values(const std::string & groupName,
			const std::string & name,
			const ULONG64 * long64Values,
			const unsigned long long * numValuesInEachDimension,
			unsigned int numDimensions) = 0;
 		virtual void writeArrayNdOfULong64Values(const std::string & groupName,
			const std::string & name,
			const ULONG64 * ulong64Values,
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
		virtual LONG64 readLongAttribute(const std::string & obj_name,
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
		virtual void readArrayNdOfLongValues(const std::string & datasetName, LONG64* values) = 0;
		virtual void readArrayNdOfLongValues(
			const std::string & datasetName,
			LONG64* values,
			unsigned long long const * numValuesInEachDimension,
			unsigned long long const * offsetInEachDimension,
			unsigned int numDimensions) = 0;
		virtual void readArrayNdOfULongValues(const std::string & datasetName, ULONG64* values) = 0;
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

		void initGsoapProxy(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, unsigned int emlVersion);
				
	protected:
	
		AbstractHdfProxy(const std::string & packageDirAbsolutePath, const std::string & externalFilePath, COMMON_NS::DataObjectRepository::openingMode hdfPermissionAccess = COMMON_NS::DataObjectRepository::openingMode::READ_ONLY);
		
	};
	
	/************ GraphicalInformationSet **************/
	
#if defined(SWIGPYTHON)
	%rename(GraphicalInformationSet_eml2) GraphicalInformationSet;
#endif
	class GraphicalInformationSet : public COMMON_NS::AbstractObject
	{
	public:
		unsigned int getGraphicalInformationSetCount() const;
		std::string getTargetObjectUuid(unsigned int index) const;
		COMMON_NS::AbstractObject* getTargetObject(unsigned int index) const;
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
		LONG64 getValueVectorIndex(COMMON_NS::AbstractObject const* targetObject);
		void setValueVectorIndex(COMMON_NS::AbstractObject const* targetObject, LONG64 valueVectorIndex);

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
		LONG64 getParameterMinOccurences(unsigned int index) const;
		LONG64 getParameterMinOccurences(const std::string & paramTitle) const;
		LONG64 getParameterMaxOccurences(unsigned int index) const;
		LONG64 getParameterMaxOccurences(const std::string & paramTitle) const;
	};

	class Activity : public COMMON_NS::AbstractObject
	{
	public:
		void pushBackParameter(const std::string title, const std::string & value);
		void pushBackParameter(const std::string title, LONG64 value);
		void pushBackParameter(const std::string title, COMMON_NS::AbstractObject* resqmlObject);
		
		unsigned int getParameterCount() const;
		unsigned int getParameterCount(const std::string & paramTitle) const;

		const std::string & getParameterTitle(unsigned int index) const;

		bool isAFloatingPointQuantityParameter(const std::string & paramTitle) const;
		bool isAFloatingPointQuantityParameter(unsigned int index) const;
		double getFloatingPointQuantityParameterValue(unsigned int index) const;

		bool isAnIntegerQuantityParameter(const std::string & paramTitle) const;
		bool isAnIntegerQuantityParameter(unsigned int index) const;
		LONG64 getIntegerQuantityParameterValue(unsigned int index) const;

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
