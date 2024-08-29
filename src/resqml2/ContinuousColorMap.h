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

#include "AbstractColorMap.h"

namespace RESQML2_NS
{
	/** @brief	Map of continuous colors. This class cannot be inherited. */
	class ContinuousColorMap : public AbstractColorMap
	{
	public:
		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~ContinuousColorMap() = default;

		/**
		* https://en.wikipedia.org/wiki/HSV_color_space
		* @param colorCount		the size (number of colors) of the continuous color map
		* @param hsvColors		array (of size colorCount * 3) of HSV colors with hsvColors[3*i] is the hue, hsvColors[3*i + 1] is the saturation and hsvColors[3*i + 2] is the value of the ith color (hue is in range [0, 360] while saturation and value are in range [0, 1])
		* @param alphas			array (of size colorCount) of numeric values in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). If alphas == nullptr (default value), default alpha value is 1.
		* @param indices		array (of size colorCount) of color indices. If indices == nullptr (default value), indices are set from 0 to colorCount - 1
		* @param colorTitles	vector (of size colorCount) of color titles. Titles are not set if colorTitles is empty (default value)
		*/
		DLL_IMPORT_OR_EXPORT void setHsvColors(uint64_t colorCount,
			double const* hsvColors, double const* alphas = nullptr,
			double const* indices = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>()) final;

		DLL_IMPORT_OR_EXPORT uint64_t getColorCount() const final;

		/**
		 * @brief	Gets interpolation domain
		 *
		 * @returns	The interpolation domain.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::resqml22__InterpolationDomain getInterpolationDomain();

		/**
		 * @brief	Gets interpolation domain as string
		 *
		 * @returns	The interpolation domain as string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getInterpolationDomainAsString();

		/**
		 * @brief	Gets interpolation method
		 *
		 * @returns	The interpolation method.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::resqml22__InterpolationMethod getInterpolationMethod();

		/**
		 * @brief	Gets interpolation method as string
		 *
		 * @returns	The interpolation method as string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getInterpolationMethodAsString();

		/**
		 * @brief	Gets the location of a color of the color map
		 *
		 * @param 	colorIndex	Zero-based index of the color.
		 *
		 * @returns	The color location in the color map.
		 */
		DLL_IMPORT_OR_EXPORT double getColorLocationInColorMap(uint64_t colorIndex) const;

		/** @brief	The XML tag */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "ContinuousColorMap";

		/**
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const { return XML_TAG; }

	protected:
		/**
		 * @param colorIndex	index of a color in the color map
		 */
		gsoap_eml2_3::resqml22__HsvColor* getColor(uint64_t colorIndex) const final;

		/**
		 * Default constructor
		 */
		ContinuousColorMap() {}

		/**
		 * Only to be used in partial transfer context
		 */
		ContinuousColorMap(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractColorMap(partialObject) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		ContinuousColorMap(gsoap_eml2_3::resqml22__ContinuousColorMap* fromGsoap) :
			AbstractColorMap(fromGsoap) {}
	};
}
