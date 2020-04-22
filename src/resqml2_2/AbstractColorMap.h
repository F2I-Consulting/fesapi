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

#include "../common/AbstractObject.h"

namespace RESQML2_2_NS
{
	/** @brief	Map of abstract colors. */
	class AbstractColorMap : public COMMON_NS::AbstractObject
	{
	public:
		virtual ~AbstractColorMap() {}

		/**
		* https://en.wikipedia.org/wiki/HSV_color_space
		* @param colorCount		the size (number of colors) of the color map
		* @param hsvColors		array (of size colorCount * 3) of HSV colors with hsvColors[3*i] is the hue, hsvColors[3*i + 1] is the saturation and hsvColors[3*i + 2] is the value of the ith color (hue is in range [0, 360] while saturation and value are in range [0, 1])
		* @param alpha			array (of size colorCount) of numeric values in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). If alphas == nullptr (default value), default alpha value is 1.
		* @param colorTitle		vector (of size colorCount) of color titles. Titles are not set if colorTitles == nullptr (default value)
		* @param indices		array (of size solorCount) of color indices. These indices are cast to unsigned int in the case of a discrete color map. If indices == nullptr (default value), indices are set from 0 to colorCount - 1
		*/
		virtual DLL_IMPORT_OR_EXPORT void setHsvColors(unsigned int colorCount,
			double const* hsvColors, double const* alphas = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>(),
			double const* indices = nullptr) = 0;

		/**
		* https://en.wikipedia.org/wiki/HSV_color_space
		* @param colorCount		the size (number of colors) of the color map
		* @param rgbColors		array (of size colorCount * 3) of RGB colors with hsvColors[3*i] is red componant, hsvColors[3*i + 1] is green component and hsvColors[3*i + 2] is blue component of the ith color (red, green and blue are in range [0, 1])
		* @param alpha			array (of size colorCount) of numeric values in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). If alphas == nullptr (default value), default alpha value is 1.
		* @param colorTitle		vector (of size colorCount) of color titles. Titles are not set if colorTitles == nullptr (default value)
		* @param indices		array (of size solorCount) of color indices. These indices are cast to unsigned int in the case of a discrete color map. If indices == nullptr (default value), indices are set from 0 to colorCount - 1
		*/
		DLL_IMPORT_OR_EXPORT void setRgbColors(unsigned int colorCount,
			double const* rgbColors, double const* alphas = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>(),
			double const* indices = nullptr);

		/**
		* https://en.wikipedia.org/wiki/HSV_color_space
		* @param colorCount		the size (number of colors) of the color map
		* @param rgbColors		array (of size colorCount * 3) of RGB colors with hsvColors[3*i] is red componant, hsvColors[3*i + 1] is green component and hsvColors[3*i + 2] is blue component of the ith color (red, green and blue are in range [0, 255])
		* @param alpha			array (of size colorCount) of numeric values in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). If alphas == nullptr (default value), default alpha value is 1.
		* @param colorTitle		vector (of size colorCount) of color titles. Titles are not set if colorTitles == nullptr (default value)
		* @param indices		array (of size solorCount) of color indices. These indices are cast to unsigned int in the case of a discrete color map. If indices == nullptr (default value), indices are set from 0 to colorCount - 1
		*/
		DLL_IMPORT_OR_EXPORT void setRgbColors(unsigned int colorCount,
			unsigned int const* rgbColors, double const* alphas = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>(),
			double const* indices = nullptr);

		virtual DLL_IMPORT_OR_EXPORT unsigned int getColorCount() const = 0;

		/**
		 * @param colorIndex	index of a color in the color map. It is cast to unsigned int in the case of a discrete color map
		 * @return				hue in the range [0, 360]
		 */
		DLL_IMPORT_OR_EXPORT double getHue(double colorIndex) const;

		/**
		 * @param colorIndex	index of a color in the color map. It is cast to unsigned int in the case of a discrete color map
		 * @return				saturation in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT double getSaturation(double colorIndex) const;

		/**
		 * @param colorIndex	index of a color in the color map. It is cast to unsigned int in the case of a discrete color map
		 * @return				value in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT double getValue(double colorIndex) const;

		/**
		 * @param colorIndex	index of a color in the color map. It is cast to unsigned int in the case of a discrete color map
		 * @return				alpha in the range [0, 1] (0 means transparent and 1 means opaque)
		 */
		DLL_IMPORT_OR_EXPORT double getAlpha(double colorIndex) const;

		/**
		 * @param colorIndex	index of a color in the color map. It is cast to unsigned int in the case of a discrete color map
		 * @param red			(output parameter) red value in the range [0, 1]
		 * @param green			(output parameter) green value in the range [0, 1]
		 * @param blue			(output parameter) blue value in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT void getRgbColor(double colorIndex, double& red, double& green, double& blue) const;

		/**
		 * @param colorIndex	index of a color in the color map. It is cast to unsigned int in the case of a discrete color map
		 * @param red			(output parameter) red value in the range [0, 1]
		 * @param green			(output parameter) green value in the range [0, 1]
		 * @param blue			(output parameter) blue value in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT void getRgbColor(double colorIndex, unsigned int& red, unsigned int& green, unsigned int& blue) const;

		DLL_IMPORT_OR_EXPORT bool hasColorTitle(double colorIndex) const;
		DLL_IMPORT_OR_EXPORT std::string getColorTitle(double colorIndex) const;

		void loadTargetRelationships() {};

		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final {
			return "resqml22";
		}

	private:
		/**
		 * @param colorIndex	index of a color in the color map. It is cast to unsigned int in the case of a discrete color map
		 */
		virtual gsoap_eml2_3::resqml22__HsvColor* getColor(double colorIndex) const = 0;

	protected:
		/**
		 * Only to be used in partial transfer context
		 */
		DLL_IMPORT_OR_EXPORT AbstractColorMap(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractColorMap(gsoap_eml2_3::resqml22__DiscreteColorMap* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}
		AbstractColorMap(gsoap_eml2_3::resqml22__ContinuousColorMap* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		* Default constructor
		* Set the gsoap proxy to nullptr from superclass constructor
		*/
		AbstractColorMap() {}
	};
}