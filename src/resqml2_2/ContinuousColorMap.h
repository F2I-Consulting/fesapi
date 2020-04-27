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

#include "../common/GraphicalInformationSet.h"
#include "AbstractColorMap.h"

namespace RESQML2_2_NS
{
	/** @brief	Map of continuous colors. This class cannot be inherited. */
	class ContinuousColorMap final : public AbstractColorMap
	{
	private:
		/**
		 * @param colorIndex	index of a color in the color map
		 */
		gsoap_eml2_3::resqml22__HsvColor* getColor(double colorIndex) const;
	public:
		/**
		 * Only to be used in partial transfer context
		 */
		DLL_IMPORT_OR_EXPORT ContinuousColorMap(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractColorMap(partialObject) {}

		/**
		 * @brief	Constructor
		 *
		 * @param [in]		repo			   	If non-nullptr, the repo.
		 * @param 		  	guid			   	The guid to set to graphical information set.
		 * @param 		  	title			   	A title for graphical information set.
		 * @param 		  	interpolationDomain	The interpolation domain.
		 * @param 		  	interpolationMethod	The interpolation method.
		 */
		ContinuousColorMap(COMMON_NS::DataObjectRepository *repo, std::string const& guid, std::string const& title,
			gsoap_eml2_3::resqml22__InterpolationDomain interpolationDomain, gsoap_eml2_3::resqml22__InterpolationMethod interpolationMethod);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		ContinuousColorMap(gsoap_eml2_3::resqml22__ContinuousColorMap* fromGsoap) :
			AbstractColorMap(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~ContinuousColorMap() {}

		/**
		* https://en.wikipedia.org/wiki/HSV_color_space
		* @param colorCount		the size (number of colors) of the continuous color map
		* @param hsvColors		array (of size colorCount * 3) of HSV colors with hsvColors[3*i] is the hue, hsvColors[3*i + 1] is the saturation and hsvColors[3*i + 2] is the value of the ith color (hue is in range [0, 360] while saturation and value are in range [0, 1])
		* @param alphas			array (of size colorCount) of numeric values in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). If alphas == nullptr (default value), default alpha value is 1.
		* @param colorTitles	vector (of size colorCount) of color titles. Titles are not set if colorTitles == nullptr (default value)
		* @param indices		array (of size solorCount) of color indices. If indices == nullptr (default value), indices are set from 0 to colorCount - 1
		*/
		DLL_IMPORT_OR_EXPORT void setHsvColors(unsigned int colorCount,
			double const* hsvColors, double const* alphas = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>(),
			double const* indices = nullptr);

		DLL_IMPORT_OR_EXPORT unsigned int getColorCount() const;

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
		 * @brief	Sets the NanColor value of a continuous color map
		 *
		 * @param 	hue		  	hue in the range [0, 360].
		 * @param 	saturation	saturation in the range [0, 1].
		 * @param 	value	  	value in the range [0, 1].
		 * @param 	alpha	  	(Optional) alpha in the range [0, 1] (0 means transparent and 1 means
		 * 						opaque). Default alpha value is 1.
		 * @param 	colorTitle	(Optional) color title. It is not set if empty string (default value)
		 */
		DLL_IMPORT_OR_EXPORT void setNanHsvColor(double hue, double saturation, double value, double alpha = 1, std::string const& colorTitle = "");

		/**
		 * @brief	Sets the NanColor value of a continuous color map
		 *
		 * @param 	red		  	red value in the range [0, 1].
		 * @param 	green	  	green value in the range [0, 1].
		 * @param 	blue	  	blue value in the range [0, 1].
		 * @param 	alpha	  	(Optional) alpha in the range [0, 1] (0 means transparent and 1 means
		 * 						opaque). Default alpha value is 1.
		 * @param 	colorTitle	(Optional) color title. It is not set if empty string (default value)
		 */
		DLL_IMPORT_OR_EXPORT void setNanRgbColor(double red, double green, double blue, double alpha = 1, std::string const& colorTitle = "");

		/**
		 * @brief	Sets the NanColor value of a continuous color map
		 *
		 * @param 	red		  	red value in the range [0, 255].
		 * @param 	green	  	green value in the range [0, 255].
		 * @param 	blue	  	blue value in the range [0, 255].
		 * @param 	alpha	  	(Optional) alpha in the range [0, 1] (0 means transparent and 1 means
		 * 						opaque). Default alpha value is 1.
		 * @param 	colorTitle	(Optional) color title. It is not set if empty string (default value)
		 */
		DLL_IMPORT_OR_EXPORT void setNanRgbColor(unsigned int red, unsigned int green, unsigned int blue, double alpha = 1, std::string const& colorTitle = "");

		/** @brief	The XML tag */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * @brief	Gets XML tag
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const { return XML_TAG; }
	};
}
