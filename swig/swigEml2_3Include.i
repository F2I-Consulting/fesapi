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
#include "../src/eml2_3/Activity.h"
#include "../src/eml2_3/ActivityTemplate.h"
#include "../src/eml2_3/GraphicalInformationSet.h"
#include "../src/eml2_3/HdfProxy.h"
#include "../src/eml2_3/PropertyKind.h"
#include "../src/eml2_3/TimeSeries.h"
%}

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace EML2_3_NS::Activity;
	%nspace EML2_3_NS::ActivityTemplate;
	%nspace EML2_3_NS::GraphicalInformationSet;
	%nspace EML2_3_NS::HdfProxy;
	%nspace EML2_3_NS::PropertyKind;
	%nspace EML2_3_NS::TimeSeries;
#endif

namespace EML2_3_NS
{
	%nodefaultctor; // Disable creation of default constructors

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Activity_eml23) Activity;
#endif
	class Activity : public EML2_NS::Activity
	{
	public:
	};	
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(ActivityTemplate_eml23) ActivityTemplate;
#endif
	class ActivityTemplate : public EML2_NS::ActivityTemplate
	{
	public:
	};

#if defined(SWIGPYTHON)
	%rename(GraphicalInformationSet_eml23) GraphicalInformationSet;
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
		RESQML2_2_NS::DiscreteColorMap* getDiscreteColorMap(COMMON_NS::AbstractObject const* targetObject) const;
		void setDiscreteColorMap(COMMON_NS::AbstractObject * targetObject, RESQML2_2_NS::DiscreteColorMap* discreteColorMap,
			bool useReverseMapping = false, bool useLogarithmicMapping = false);

		bool hasContinuousColorMap(COMMON_NS::AbstractObject const* targetObject) const;
		std::string getContinuousColorMapUuid(COMMON_NS::AbstractObject const* targetObject) const;
		RESQML2_2_NS::ContinuousColorMap* getContinuousColorMap(COMMON_NS::AbstractObject const* targetObject) const;
		void setContinuousColorMap(COMMON_NS::AbstractObject * targetObject, RESQML2_2_NS::ContinuousColorMap* continuousColorMap,
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

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(HdfProxy_eml23) HdfProxy;
#endif
	class HdfProxy : public EML2_NS::HdfProxy
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(PropertyKind_eml23) PropertyKind;
#endif
	class PropertyKind : public EML2_NS::PropertyKind
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(TimeSeries_eml23) TimeSeries;
#endif
	class TimeSeries : public EML2_NS::TimeSeries
	{
	public:
	};
	
}
