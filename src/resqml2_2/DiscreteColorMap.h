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
	class DiscreteColorMap : public AbstractColorMap
	{
	private:
		/**
		 * @param colorIndex	index of a color in the color map. It is cast to unsigned int in the case of a discrete color map
		 */
		gsoap_eml2_2::resqml2__HsvColor* getColor(double colorIndex) const;
	public:
		/**
		 * Only to be used in partial transfer context
		 */
		DiscreteColorMap(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractColorMap(partialObject) {}

		/**
		* @param soapContext	The soap context where the underlying gsoap proxy is going to be created.
		* @param guid			The guid to set to graphical information set.
		* @param title			A title for graphical information set.
		*/
		DiscreteColorMap(COMMON_NS::DataObjectRepository* repo, std::string const& guid, std::string const& title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		DiscreteColorMap(gsoap_eml2_2::resqml2__DiscreteColorMap* fromGsoap) :
			AbstractColorMap(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~DiscreteColorMap() {}

		/**
		* https://en.wikipedia.org/wiki/HSV_color_space
		* @param colorCount		the size (number of colors) of the discrete color map
		* @param hsvColors		array (of size colorCount * 3) of HSV colors with hsvColors[3*i] is the hue, hsvColors[3*i + 1] is the saturation and hsvColors[3*i + 2] is the value of the ith color (hue is in range [0, 360] while saturation and value are in range [0, 1]) 
		* @param alpha			array (of size colorCount) of numeric values in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). If alphas == nullptr (default value), default alpha value is 1.
		* @param colorTitle		vector (of size colorCount) of color titles. Titles are not set if colorTitles == nullptr (default value)
		* @param indices		array (of size solorCount) of color indices.  These indices are cast to unsigned int in the case of a discrete color map. If indices == nullptr (default value), indices are set from 0 to colorCount - 1
		*/
		DLL_IMPORT_OR_EXPORT void setHsvColors(unsigned int colorCount, 
			double const * hsvColors, double const * alphas = nullptr, std::vector<std::string> const& colorTitles = std::vector<std::string>(),
			double const * indices = nullptr);

		DLL_IMPORT_OR_EXPORT unsigned int getColorCount() const;

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const { return XML_TAG; }
	};
}
