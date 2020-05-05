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
#include "../src/resqml2_2/AbstractColorMap.h"
#include "../src/resqml2_2/DiscreteColorMap.h"
#include "../src/resqml2_2/ContinuousColorMap.h"
#include "../src/resqml2_2/WellboreFrameRepresentation.h"
#include "../src/resqml2_2/SeismicWellboreFrameRepresentation.h"
%}

#ifdef SWIGPYTHON
namespace RESQML2_2_NS
{
	%typemap(out) WellboreFrameRepresentation* {
		// Check potential downcasting
		swig_type_info * const outtype = SWIG_TypeQuery(("resqml2_2::" + result->getXmlTag() + " *").c_str());
		resultobj = SWIG_NewPointerObj(SWIG_as_voidptr(result), outtype, 0);
	}
}
#endif
#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace RESQML2_2_NS::AbstractColorMap;
	%nspace RESQML2_2_NS::DiscreteColorMap;
	%nspace RESQML2_2_NS::ContinuousColorMap;
	%nspace RESQML2_2_NS::WellboreFrameRepresentation;
	%nspace RESQML2_2_NS::SeismicWellboreFrameRepresentation;
#endif

namespace gsoap_eml2_3
{
	enum resqml22__InterpolationDomain {
		resqml22__InterpolationDomain__hsv = 0,
		resqml22__InterpolationDomain__rgb = 1
	};
	
	enum resqml22__InterpolationMethod {
		resqml22__InterpolationMethod__linear = 0,
		resqml22__InterpolationMethod__logarithmic = 1
	};
}

namespace RESQML2_2_NS
{
	%nodefaultctor; // Disable creation of default constructors

#ifdef SWIGPYTHON
	%rename(Resqml2_2AbstractColorMap) AbstractColorMap;
#endif
	class AbstractColorMap : public COMMON_NS::AbstractObject
	{
	public:
		void setRgbColors(unsigned int colorCount,
			double const* rgbColors, double const* alphas = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>(),
			double const* indices = nullptr);
		void setRgbColors(unsigned int colorCount,
			unsigned int const* rgbColors, double const* alphas = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>(),
			double const* indices = nullptr);

		double getHue(double colorIndex) const;
		double getSaturation(double colorIndex) const;
		double getValue(double colorIndex) const;
		double getAlpha(double colorIndex) const;
		
		void getRgbColor(double colorIndex, double& red, double& green, double& blue) const;
		void getRgbColor(double colorIndex, unsigned int& red, unsigned int& green, unsigned int& blue) const;

		bool hasColorTitle(double colorIndex) const;
		std::string getColorTitle(double colorIndex) const;
	};
	
	class DiscreteColorMap : public AbstractColorMap
	{
	public:
		void setHsvColors(unsigned int colorCount, 
			double const * hsvColors, double const * alphas = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>(),
			double const * indices = nullptr);

		unsigned int getColorCount() const;
	};
	
	class ContinuousColorMap : public AbstractColorMap 
	{
	public:
		void setHsvColors(unsigned int colorCount,
			double const* hsvColors, double const* alphas = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>(),
			double const* indices = nullptr);

		unsigned int getColorCount() const;

		gsoap_eml2_3::resqml22__InterpolationDomain getInterpolationDomain();
		std::string getInterpolationDomainAsString();

		gsoap_eml2_3::resqml22__InterpolationMethod getInterpolationMethod();
		std::string getInterpolationMethodAsString();

		void setNanHsvColor(double hue, double saturation, double value, double alpha = 1, std::string const& colorTitle = "");
		void setNanRgbColor(double red, double green, double blue, double alpha = 1, std::string const& colorTitle = "");
		void setNanRgbColor(unsigned int red, unsigned int green, unsigned int blue, double alpha = 1, std::string const& colorTitle = "");
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_2_WellboreFrameRepresentation) WellboreFrameRepresentation;
#endif
	class WellboreFrameRepresentation : public RESQML2_NS::WellboreFrameRepresentation
	{
	};
	
#ifdef SWIGPYTHON
	%rename(Resqml2_2_SeismicWellboreFrameRepresentation) SeismicWellboreFrameRepresentation;
#endif
	class SeismicWellboreFrameRepresentation : public WellboreFrameRepresentation
	{
	public:
		void setTimeValues(double const * timeValues, unsigned int timeValueCount, COMMON_NS::AbstractHdfProxy* proxy = nullptr);
		void setTimeValues(double firstTimeValue, double incrementTimeValue, unsigned int timeValueCount);

		bool areTimeValuesRegularlySpaced() const;
		double getTimeConstantIncrementValue() const;
		double getTimeFirstValue() const;
		unsigned int getTimeValuesCount() const;
		RESQML2_NS::AbstractValuesProperty::hdfDatatypeEnum getTimeHdfDatatype() const;
		void getTimeAsDoubleValues(double* values) const;
		void getTimeAsFloatValues(float* values) const;
		double getSeismicReferenceDatum() const;
		double getWeatheringVelocity() const;
	};
}

