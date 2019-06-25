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

#include "common/AbstractObject.h"
#include "common/GraphicalInformationSet.h"

namespace RESQML2_2_NS
{
	class DiscreteColorMap : public COMMON_NS::AbstractObject
	{
	private:
		gsoap_eml2_2::resqml2__HsvColor* getColor(unsigned int colorIndex) const;
	public:
		/**
		* @param soapContext	The soap context where the underlying gsoap proxy is going to be created.
		* @param guid			The guid to set to graphical information set.
		* @param title			A title for graphical information set.
		*/
		DiscreteColorMap(soap* soapContext, const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		DiscreteColorMap(gsoap_eml2_2::resqml2__DiscreteColorMap* fromGsoap) :
			COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~DiscreteColorMap() {}

		/**
		* https://en.wikipedia.org/wiki/HSV_color_space
		* @param colorCount		the size (number of colors) of the discrete color map
		* @param hsvColors		array (of size colorCount * 3) of HSV colors with hsvColors[3*i] is the hue, hsvColors[3*i + 1] is the saturation and hsvColors[3*i + 2] is the value of the ith color (hue is in range [0, 360] while saturation and value are in range [0, 1]) 
		* @param alpha			array (of size colorCount) of numeric values in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). If alphas == nullptr (default value), default alpha value is 1.
		* @param colorTitle		array (of size colorCount) of color titles. Titles are not set if colorTitles == nullptr (default value)
		* @param indices		array (of size solorCount) of color indices. If indices == nullptr (default value), indices are set from 0 to colorCount - 1
		*/
		DLL_IMPORT_OR_EXPORT void setHsvColors(unsigned int colorCount, 
			double const * hsvColors, double const * alphas = nullptr, std::string const * colorTitles = nullptr,
			double const * indices = nullptr);

		/**
		* https://en.wikipedia.org/wiki/HSV_color_space
		* @param colorCount		the size (number of colors) of the discrete color map
		* @param rgbColors		array (of size colorCount * 3) of RGB colors with hsvColors[3*i] is red componant, hsvColors[3*i + 1] is green component and hsvColors[3*i + 2] is blue component of the ith color (red, green and blue are in range [0, 1])
		* @param alpha			array (of size colorCount) of numeric values in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). If alphas == nullptr (default value), default alpha value is 1.
		* @param colorTitle		array (of size colorCount) of color titles. Titles are not set if colorTitles == nullptr (default value)
		* @param indices		array (of size solorCount) of color indices. If indices == nullptr (default value), indices are set from 0 to colorCount - 1
		*/
		DLL_IMPORT_OR_EXPORT void setRgbColors(unsigned int colorCount,
			double const * rgbColors, double const * alphas = nullptr, std::string const * colorTitles = nullptr,
			double const * indices = nullptr);

		/**
		* https://en.wikipedia.org/wiki/HSV_color_space
		* @param colorCount		the size (number of colors) of the discrete color map
		* @param rgbColors		array (of size colorCount * 3) of RGB colors with hsvColors[3*i] is red componant, hsvColors[3*i + 1] is green component and hsvColors[3*i + 2] is blue component of the ith color (red, green and blue are in range [0, 255])
		* @param alpha			array (of size colorCount) of numeric values in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). If alphas == nullptr (default value), default alpha value is 1.
		* @param colorTitle		array (of size colorCount) of color titles. Titles are not set if colorTitles == nullptr (default value)
		* @param indices		array (of size solorCount) of color indices. If indices == nullptr (default value), indices are set from 0 to colorCount - 1
		*/
		DLL_IMPORT_OR_EXPORT void setRgbColors(unsigned int colorCount,
			unsigned int const * rgbColors, double const * alphas = nullptr, std::string const * colorTitles = nullptr,
			double const * indices = nullptr);

		DLL_IMPORT_OR_EXPORT unsigned int getColorCount() const;

		/**
		 * @param colorIndex	index of a color in the discrete color map
		 * @return				hue in the range [0, 360]
		 */
		DLL_IMPORT_OR_EXPORT double getHue(unsigned int colorIndex) const;
		
		/**
		 * @param colorIndex	index of a color in the discrete color map
		 * @return				saturation in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT double getSaturation(unsigned int colorIndex) const;
		
		/**
		 * @param colorIndex	index of a color in the discrete color map
		 * @return				value in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT double getValue(unsigned int colorIndex) const;
		
		/**
		 * @param colorIndex	index of a color in the discrete color map
		 * @return				alpha in the range [0, 1] (0 means transparent and 1 means opaque)
		 */
		DLL_IMPORT_OR_EXPORT double getAlpha(unsigned int colorIndex) const;

		/**
		 * @param colorIndex	index of a color in the discrete color map
		 * @param red			(output parameter) red value in the range [0, 1]
		 * @param green			(output parameter) green value in the range [0, 1]
		 * @param blue			(output parameter) blue value in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT void getRgbColor(unsigned int colorIndex, double & red, double & green, double & blue) const;

		/**
		 * @param colorIndex	index of a color in the discrete color map
		 * @param red			(output parameter) red value in the range [0, 1]
		 * @param green			(output parameter) green value in the range [0, 1]
		 * @param blue			(output parameter) blue value in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT void getRgbColor(unsigned int colorIndex, unsigned int & red, unsigned int & green, unsigned int & blue) const;

		DLL_IMPORT_OR_EXPORT bool hasColorTitle(unsigned int colorIndex) const;
		DLL_IMPORT_OR_EXPORT std::string getColorTitle(unsigned int colorIndex) const;

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const { return XML_TAG; }
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const {
			return "resqml22";
		}

		void computeMinMax(LONG64& min, LONG64& max) const;

	protected:
		std::vector<COMMON_NS::GraphicalInformationSet*> graphicalInformationSetSet; 

		void resolveTargetRelationships(COMMON_NS::EpcDocument* epcDoc) {}

		DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> getAllSourceRelationships() const;
		DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> getAllTargetRelationships() const;

		friend void COMMON_NS::GraphicalInformationSet::setDiscreteColorMap(COMMON_NS::AbstractObject* targetObject, DiscreteColorMap* discreteColorMap, bool useReverseMapping);
	};
}
