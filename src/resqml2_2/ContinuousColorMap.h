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

#include "common/GraphicalInformationSet.h"
#include "resqml2_2/AbstractColorMap.h"

namespace RESQML2_2_NS
{
	class ContinuousColorMap : public AbstractColorMap
	{
	private:
		/**
		 * @param colorIndex	index of a color in the color map
		 */
		gsoap_eml2_2::resqml22__HsvColor* getColor(double colorIndex) const;
	public:
		/**
		 * Only to be used in partial transfer context
		 */
		ContinuousColorMap(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractColorMap(partialObject) {}

		/**
		* @param soapContext	The soap context where the underlying gsoap proxy is going to be created.
		* @param guid			The guid to set to graphical information set.
		* @param title			A title for graphical information set.
		*/
		ContinuousColorMap(COMMON_NS::DataObjectRepository *repo, std::string const& guid, std::string const& title,
			gsoap_eml2_2::resqml22__InterpolationDomain interpolationDomain, gsoap_eml2_2::resqml22__InterpolationMethod interpolationMethod);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		ContinuousColorMap(gsoap_eml2_2::resqml22__ContinuousColorMap* fromGsoap) :
			AbstractColorMap(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~ContinuousColorMap() {}

		/**
		* https://en.wikipedia.org/wiki/HSV_color_space
		* @param colorCount		the size (number of colors) of the continuous color map
		* @param hsvColors		array (of size colorCount * 3) of HSV colors with hsvColors[3*i] is the hue, hsvColors[3*i + 1] is the saturation and hsvColors[3*i + 2] is the value of the ith color (hue is in range [0, 360] while saturation and value are in range [0, 1])
		* @param alpha			array (of size colorCount) of numeric values in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). If alphas == nullptr (default value), default alpha value is 1.
		* @param colorTitle		vector (of size colorCount) of color titles. Titles are not set if colorTitles == nullptr (default value)
		* @param indices		array (of size solorCount) of color indices. If indices == nullptr (default value), indices are set from 0 to colorCount - 1
		*/
		DLL_IMPORT_OR_EXPORT void setHsvColors(unsigned int colorCount,
			double const* hsvColors, double const* alphas = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>(),
			double const* indices = nullptr);

		DLL_IMPORT_OR_EXPORT unsigned int getColorCount() const;

		DLL_IMPORT_OR_EXPORT gsoap_eml2_2::resqml22__InterpolationDomain getInterpolationDomain();
		DLL_IMPORT_OR_EXPORT std::string getInterpolationDomainAsString();

		DLL_IMPORT_OR_EXPORT gsoap_eml2_2::resqml22__InterpolationMethod getInterpolationMethod();
		DLL_IMPORT_OR_EXPORT std::string getInterpolationMethodAsString();

		/**
		 * Sets the NanColor value of a continuous color map
		 * @param hue			hue in the range [0, 360]
		 * @param saturation	saturation in the range [0, 1]
		 * @param value			value in the range [0, 1]
		 * @param alpha			alpha in the range [0, 1] (0 means transparent and 1 means opaque). Default alpha value is 1
		 * @param title			color title. It is not set if empty string (default value)
		 */
		DLL_IMPORT_OR_EXPORT void setNanHsvColor(double hue, double saturation, double value, double alpha = 1, std::string const& colorTitle = "");

		/**
		 * Sets the NanColor value of a continuous color map
		 * @param red		red value in the range [0, 1]
		 * @param green		green value in the range [0, 1]
		 * @param blue		blue value in the range [0, 1]
		 * @param alpha		alpha in the range [0, 1] (0 means transparent and 1 means opaque). Default alpha value is 1
		 * @param title		color title. It is not set if empty string (default value)
		 */
		DLL_IMPORT_OR_EXPORT void setNanRgbColor(double red, double green, double blue, double alpha = 1, std::string const& colorTitle = "");

		/**
		 * Sets the NanColor value of a continuous color map
		 * @param red		red value in the range [0, 255]
		 * @param green		green value in the range [0, 255]
		 * @param blue		blue value in the range [0, 255]
		 * @param alpha		alpha in the range [0, 1] (0 means transparent and 1 means opaque). Default alpha value is 1
		 * @param title		color title. It is not set if empty string (default value)
		 */
		DLL_IMPORT_OR_EXPORT void setNanRgbColor(unsigned int red, unsigned int green, unsigned int blue, double alpha = 1, std::string const& colorTitle = "");

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const { return XML_TAG; }
	};
}
