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

namespace RESQML2_NS
{
	/** @brief	Map of abstract colors. */
	class AbstractColorMap : public COMMON_NS::AbstractObject
	{
	public:
		virtual ~AbstractColorMap() = default;

		/**
		* https://en.wikipedia.org/wiki/HSV_color_space
		* @param colorCount		the size (number of colors) of the color map
		* @param hsvColors		array (of size colorCount * 3) of HSV colors with hsvColors[3*i] is the hue, hsvColors[3*i + 1] is the saturation and hsvColors[3*i + 2] is the value of the ith color (hue is in range [0, 360] while saturation and value are in range [0, 1])
		* @param alphas			array (of size colorCount) of numeric values in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). If alphas == nullptr (default value), default alpha value is 1.
		* @param indices		array (of size colorCount) of color indices. These indices are cast to unsigned int in the case of a discrete color map. If indices 
		* @param colorTitles	vector (of size colorCount) of color titles. Titles are not set if colorTitles is empty (default value)= nullptr (default value), indices are set from 0 to colorCount - 1
		*/
		virtual DLL_IMPORT_OR_EXPORT void setHsvColors(uint64_t colorCount,
			double const* hsvColors, double const* alphas = nullptr, double const* indices = nullptr,
			std::vector<std::string> const& colorTitles = std::vector<std::string>()) = 0;

		/**
		* https://en.wikipedia.org/wiki/HSV_color_space
		* @param colorCount		the size (number of colors) of the color map
		* @param rgbColors		array (of size colorCount * 3) of RGB colors with rgbColors[3*i] is red component, rgbColors[3*i + 1] is green component and rgbColors[3*i + 2] is blue component of the ith color (red, green and blue are in range [0, 1])
		* @param alphas			array (of size colorCount) of numeric values in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). If alphas == nullptr (default value), default alpha value is 1.
		* @param indices		array (of size colorCount) of color indices. These indices are cast to unsigned int in the case of a discrete color map. If indices == nullptr (default value), indices are set from 0 to colorCount - 1
		* @param colorTitles	vector (of size colorCount) of color titles. Titles are not set if colorTitles is empty (default value)
		*/
		DLL_IMPORT_OR_EXPORT void setRgbColors(uint64_t colorCount,
			double const* rgbColors, double const* alphas = nullptr,
			double const* indices = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>());

		/**
		* https://en.wikipedia.org/wiki/HSV_color_space
		* @param colorCount		the size (number of colors) of the color map
		* @param rgbColors		array (of size colorCount * 3) of RGB colors with hsvColors[3*i] is red component, hsvColors[3*i + 1] is green component and hsvColors[3*i + 2] is blue component of the ith color (red, green and blue are in range [0, 255])
		* @param alphas			array (of size colorCount) of numeric values in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). If alphas == nullptr (default value), default alpha value is 1.
		* @param indices		array (of size colorCount) of color indices. These indices are cast to unsigned int in the case of a discrete color map. If indices == nullptr (default value), indices are set from 0 to colorCount - 1
		* @param colorTitles	vector (of size colorCount) of color titles. Titles are not set if colorTitles is empty (default value)
		*/
		DLL_IMPORT_OR_EXPORT void setRgbColors(uint64_t colorCount,
			uint8_t const* rgbColors, double const* alphas = nullptr,
			double const* indices = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>());

		/**
		 * @brief	Gets color count
		 *
		 * @returns	The color count.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getColorCount() const = 0;

		/**
		 * @param colorIndex	index of a color in the color map.
		 * @return				hue in the range [0, 360]
		 */
		DLL_IMPORT_OR_EXPORT double getHue(uint64_t colorIndex) const;

		/**
		 * @param colorIndex	index of a color in the color map.
		 * @return				saturation in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT double getSaturation(uint64_t colorIndex) const;

		/**
		 * @param colorIndex	index of a color in the color map.
		 * @return				value in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT double getValue(uint64_t colorIndex) const;

		/**
		 * @param colorIndex	index of a color in the color map.
		 * @return				alpha in the range [0, 1] (0 means transparent and 1 means opaque)
		 */
		DLL_IMPORT_OR_EXPORT double getAlpha(uint64_t colorIndex) const;

		/**
		 * @param colorIndex	index of a color in the color map.
		 * @param red			(output parameter) red value in the range [0, 1]
		 * @param green			(output parameter) green value in the range [0, 1]
		 * @param blue			(output parameter) blue value in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT void getRgbColor(uint64_t colorIndex, double& red, double& green, double& blue) const;

		/**
		 * @param colorIndex	index of a color in the color map.
		 * @param red			(output parameter) red value in the range [0, 255]
		 * @param green			(output parameter) green value in the range [0, 255]
		 * @param blue			(output parameter) blue value in the range [0, 255]
		 */
		DLL_IMPORT_OR_EXPORT void getRgbColor(uint64_t colorIndex, uint8_t& red, uint8_t& green, uint8_t& blue) const;

		/**
		 * @brief	Queries if 'colorIndex' has color title
		 *
		 * @param 	colorIndex	Zero-based index of the color.
		 *
		 * @returns	True if color title, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasColorTitle(uint64_t colorIndex) const;

		/**
		 * @brief	Gets color title
		 *
		 * @param 	colorIndex	Zero-based index of the color.
		 *
		 * @returns	The color title.
		 */
		DLL_IMPORT_OR_EXPORT std::string getColorTitle(uint64_t colorIndex) const;

		/**
		 * @brief	Sets the NullColor value of a continuous color map
		 *
		 * @param 	hue		  	hue in the range [0, 360].
		 * @param 	saturation	saturation in the range [0, 1].
		 * @param 	value	  	value in the range [0, 1].
		 * @param 	alpha	  	(Optional) alpha in the range [0, 1] (0 means transparent and 1 means
		 * 						opaque). Default alpha value is 1.
		 * @param 	colorTitle	(Optional) color title. It is not set if empty string (default value)
		 */
		DLL_IMPORT_OR_EXPORT void setNullHsvColor(double hue, double saturation, double value, double alpha = 1, std::string const& colorTitle = "");

		/**
		 * @brief	Sets the NullColor value of a continuous color map
		 *
		 * @param 	red		  	red value in the range [0, 1].
		 * @param 	green	  	green value in the range [0, 1].
		 * @param 	blue	  	blue value in the range [0, 1].
		 * @param 	alpha	  	(Optional) alpha in the range [0, 1] (0 means transparent and 1 means
		 * 						opaque). Default alpha value is 1.
		 * @param 	colorTitle	(Optional) color title. It is not set if empty string (default value)
		 */
		DLL_IMPORT_OR_EXPORT void setNullRgbColor(double red, double green, double blue, double alpha = 1, std::string const& colorTitle = "");

		/**
		 * @brief	Sets the NullColor value of a continuous color map
		 *
		 * @param 	red		  	red value in the range [0, 255].
		 * @param 	green	  	green value in the range [0, 255].
		 * @param 	blue	  	blue value in the range [0, 255].
		 * @param 	alpha	  	(Optional) alpha in the range [0, 1] (0 means transparent and 1 means
		 * 						opaque). Default alpha value is 1.
		 * @param 	colorTitle	(Optional) color title. It is not set if empty string (default value)
		 */
		DLL_IMPORT_OR_EXPORT void setNullRgbColor(uint8_t red, uint8_t green, uint8_t blue, double alpha = 1, std::string const& colorTitle = "");

		/**
		 * @brief	checks if the color map has a definition for the color of Null values.
		 */
		DLL_IMPORT_OR_EXPORT bool hasNullColor() const { return static_cast<gsoap_eml2_3::resqml22__ContinuousColorMap const*>(gsoapProxy2_3)->NullColor != nullptr; }

		/**
		 * @return				hue in the range [0, 360]
		 */
		DLL_IMPORT_OR_EXPORT double getNullHue() const;

		/**
		 * @return				saturation in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT double getNullSaturation() const;

		/**
		 * @return				value in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT double getNullValue() const;

		/**
		 * @return				alpha in the range [0, 1] (0 means transparent and 1 means opaque)
		 */
		DLL_IMPORT_OR_EXPORT double getNullAlpha() const;

		/**
		 * @param red			(output parameter) red value in the range [0, 1]
		 * @param green			(output parameter) green value in the range [0, 1]
		 * @param blue			(output parameter) blue value in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT void getNullRgbColor(double& red, double& green, double& blue) const;

		/**
		 * @param red			(output parameter) red value in the range [0, 255]
		 * @param green			(output parameter) green value in the range [0, 255]
		 * @param blue			(output parameter) blue value in the range [0, 255]
		 */
		DLL_IMPORT_OR_EXPORT void getNullRgbColor(uint8_t& red, uint8_t& green, uint8_t& blue) const;

		void loadTargetRelationships() {};

	protected:
		/**
		 * Only to be used in partial transfer context
		 */
		DLL_IMPORT_OR_EXPORT AbstractColorMap(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractColorMap(gsoap_eml2_3::resqml22__AbstractColorMap* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		* Default constructor
		* Set the gsoap proxy to nullptr from superclass constructor
		*/
		AbstractColorMap() {}

	private:
		/**
		 * @param colorIndex	index of a color in the color map.
		 */
		virtual gsoap_eml2_3::resqml22__HsvColor* getColor(uint64_t colorIndex) const = 0;
	};
}