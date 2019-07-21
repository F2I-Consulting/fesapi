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

namespace COMMON_NS
{
	class GraphicalInformationSet : public AbstractObject
	{
	private:
		gsoap_eml2_2::resqml2__DefaultGraphicalInformation* getDefaultGraphicalInformationForAllIndexableElements(AbstractObject const* targetObject) const;
		gsoap_eml2_2::resqml2__GraphicalInformationForWholeObject* getDefaultGraphicalInformation(AbstractObject const* targetObject) const;
		gsoap_eml2_2::resqml2__HsvColor* getDefaultColor(AbstractObject const* targetObject) const;
		gsoap_eml2_2::resqml2__ColorInformation* getColorInformation(AbstractObject const* targetObject) const;

	public:
		/**
		* Only to be used in partial transfer context
		*/
		GraphicalInformationSet(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject): AbstractObject(partialObject) {}

		/**
		* @param repo		The repository where the underlying gsoap proxy is going to be created.
		* @param guid		The guid to set to graphical information set.
		* @param title		A title for graphical information set.
		*/
		GraphicalInformationSet(COMMON_NS::DataObjectRepository* repo, std::string const& guid, std::string const& title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 */
		GraphicalInformationSet(gsoap_eml2_2::_eml22__GraphicalInformationSet* fromGsoap) :
			AbstractObject(fromGsoap) {}

		/**
		 * Destructor does nothing since the memory is managed by the gsoap context.
		 */
		~GraphicalInformationSet() {}

		/**
		 * @return	the size of the GraphicalInformationSet.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getGraphicalInformationSetCount() const;

		/**
		 * @return	the data objet reference of the object which receives some graphical information at a particular index of the GraphicalInformationSet.
		 */
		gsoap_eml2_2::eml22__DataObjectReference* getTargetObjectDor(unsigned int index) const;

		/**
		 * @return	the Uuid of the object which receives some graphical information at a particular index of the GraphicalInformationSet.
		 */
		DLL_IMPORT_OR_EXPORT std::string getTargetObjectUuid(unsigned int index) const;

		/**
		 * @return	the object which receives some graphical information at a particular index of the GraphicalInformationSet
		 */
		DLL_IMPORT_OR_EXPORT AbstractObject* getTargetObject(unsigned int index) const;

		/**
		 * @param targetObject	the object we want to test for having some graphical informations
		 * @return				true if the target object has some graphical informations
		 */
		bool hasDirectGraphicalInformation(AbstractObject const* targetObject) const;

		/**
		 * @param targetObject	the object we want to test for having some graphical informations. If it has not and it is a property,
								we also check that its property kind has some
		 * @return				true if the target object (or its property kind) has some graphical informations
		 */
		DLL_IMPORT_OR_EXPORT bool hasGraphicalInformation(AbstractObject const* targetObject) const;

		/**
		 * @param targetObject	the object we want to test for having a default color
		 * @return				true if the target object has one
		 */
		DLL_IMPORT_OR_EXPORT bool hasDefaultColor(AbstractObject const* targetObject) const;

		/**
		 * @param targetObject	the object for which we look for the default hue
		 * @return				hue in the range [0, 360]
		 */
		DLL_IMPORT_OR_EXPORT double getDefaultHue(AbstractObject const* targetObject) const;

		/**
		 * @param targetObject	the object for which we look for the default saturation
		 * @return				saturation in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT double getDefaultSaturation(AbstractObject const* targetObject) const;

		/**
		 * @param targetObject	the object for which we look for the default color value
		 * @return				value in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT double getDefaultValue(AbstractObject const* targetObject) const;

		/**
		 * @param targetObject	the object for which we look for the default alpha
		 * @return				alpha in the range [0, 1] (0 means transparent and 1 means opaque)
		 */
		DLL_IMPORT_OR_EXPORT double getDefaultAlpha(AbstractObject const* targetObject) const;

		/**
		 * @param targetObject	the object for which we look for the default rgb color
		 * @param red			(output parameter) red value in the range [0, 1]
		 * @param green			(output parameter) green value in the range [0, 1]
		 * @param blue			(output parameter) blue value in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT void getDefaultRgbColor(AbstractObject const* targetObject, double& red, double& green, double& blue) const;

		/**
		 * @param targetObject	the object for which we look for the default rgb color
		 * @param red			(output parameter) red value in the range [0, 255]
		 * @param green			(output parameter) green value in the range [0, 255]
		 * @param blue			(output parameter) blue value in the range [0, 255]
		 */
		DLL_IMPORT_OR_EXPORT void getDefaultRgbColor(AbstractObject const* targetObject, unsigned int& red, unsigned int& green, unsigned int& blue) const;

		/**
		 * @param targetObject	the object for which we look for a default title
		 * @return				true if the target object has a default title
		 */
		DLL_IMPORT_OR_EXPORT bool hasDefaultColorTitle(AbstractObject const* targetObject) const;

		/**
		 * @param targetObject	the object for which we look for a default title
		 * @return				the default title
		 */
		DLL_IMPORT_OR_EXPORT std::string getDefaultColorTitle(AbstractObject const* targetObject) const;

		/**
		* https://en.wikipedia.org/wiki/HSV_color_space
		* @param targetObject	the object which receives the color
		* @param hue			angle in degrees in the range [0, 360]
		* @param saturation		numeric value in the range [0, 1]
		* @param value			numeric value in the range [0, 1]
		* @param alpha			numeric value in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). Default value is 1.
		* @param colorTitle		title for the given color. It is not set if title is empty
		*/
		DLL_IMPORT_OR_EXPORT void setDefaultHsvColor(AbstractObject* targetObject, double hue, double saturation, double value, double alpha = 1.0, std::string const& colorTitle = "");

		/**
		* https://en.wikipedia.org/wiki/RGB_color_space
		* @param targetObject	The object which receives the color
		* @param red			numeric value in the range [0, 1]
		* @param green			numeric value in the range [0, 1]
		* @param blue			numeric value in the range [0, 1]
		* @param alpha			numeric value in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). Default value is 1.
		* @param colorTitle		title for the given color. It is not set if title is empty
		*/
		DLL_IMPORT_OR_EXPORT void setDefaultRgbColor(AbstractObject* targetObject, double red, double green, double blue, double alpha = 1.0, std::string const& colorTitle = "");

		/**
		* https://en.wikipedia.org/wiki/RGB_color_space
		* @param targetObject	The object which receives the color
		* @param red			numeric value in the range [0, 255]
		* @param green			numeric value in the range [0, 255]
		* @param blue			numeric value in the range [0, 255]
		* @param alpha			numeric value in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). Default value is 1.
		* @param colorTitle		title for the given color. It is not set if title is empty
		*/
		DLL_IMPORT_OR_EXPORT void setDefaultRgbColor(AbstractObject* targetObject, unsigned int red, unsigned int green, unsigned int blue, double alpha = 1.0, std::string const& colorTitle = "");

		/**
		 * @param targetObject	the object for wich we look for a discrete color map. If it has not and it is a property,
		 *						we also look for its property kind discrete color map
		 * @return				true if the target object (or its property kind) has a discrete color map
		 */
		DLL_IMPORT_OR_EXPORT bool hasDiscreteColorMap(AbstractObject const* targetObject) const;
		
		/**
		 * @param targetObject	the object for wich we look for a discrete color map. If it has not and it is a property,
		 *						we also look for its property kind discrete color map
		 * @return				the discrete color map data object reference
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_2::eml22__DataObjectReference* getDiscreteColorMapDor(AbstractObject const* targetObject) const;

		/**
		 * @param targetObject	the object for wich we look for a discrete color map. If it has not and it is a property,
		 *						we also look for its property kind discrete color map
		 * @return				the discrete color map uuid
		 */
		DLL_IMPORT_OR_EXPORT std::string getDiscreteColorMapUuid(AbstractObject const* targetObject) const;

		/**
		 * @param targetObject	the object for wich we look for a discrete color map. If it has not and it is a property,
		 *						we also look for its property kind discrete color map
		 * @return				the discrete color map
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_2_NS::DiscreteColorMap* getDiscreteColorMap(AbstractObject const* targetObject) const;

		DLL_IMPORT_OR_EXPORT void setDiscreteColorMap(AbstractObject* targetObject, RESQML2_2_NS::DiscreteColorMap* discreteColorMap,
			LONG64 valueVectorIndex = 0, bool useReverseMapping = false, bool useLogarithmicMapping = false);

		/**
		 * @param targetObject	the object for wich we look for a continuous color map. If it has not and it is a property,
		 *						we also look for its property kind continuous color map
		 * @return				true if the target object (or its property kind) has a continuous color map
		 */
		DLL_IMPORT_OR_EXPORT bool hasContinuousColorMap(AbstractObject const* targetObject) const;
		
		/**
		 * @param targetObject	the object for wich we look for a continuous color map. If it has not and it is a property,
		 *						we also look for its property kind continuous color map
		 * @return				the continuous color map data object reference
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_2::eml22__DataObjectReference* getContinuousColorMapDor(AbstractObject const* targetObject) const;
		
		/**
		 * @param targetObject	the object for wich we look for a continuous color map. If it has not and it is a property,
		 *						we also look for its property kind continuous color map
		 * @return				the continuous color map uuid
		 */
		DLL_IMPORT_OR_EXPORT std::string getContinuousColorMapUuid(AbstractObject const* targetObject) const;

		/**
		 * @param targetObject	the object for wich we look for a continuous color map. If it has not and it is a property,
		 *						we also look for its property kind continuous color map
		 * @return				the continuous color map
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_2_NS::ContinuousColorMap* getContinuousColorMap(AbstractObject const* targetObject) const;

		DLL_IMPORT_OR_EXPORT void setContinuousColorMap(AbstractObject* targetObject, RESQML2_2_NS::ContinuousColorMap* continuousColorMap,
			LONG64 valueVectorIndex = 0, bool useReverseMapping = false, bool useLogarithmicMapping = false);

		DLL_IMPORT_OR_EXPORT double getColorMapMinIndex(AbstractObject const* targetObject) const;
		DLL_IMPORT_OR_EXPORT double getColorMapMaxIndex(AbstractObject const* targetObject) const;

		/**
		 * https://en.wikipedia.org/wiki/HSL_and_HSV#From_RGB
		 * note: no range check is done on parameters
		 * @param red			numeric value in the range [0, 1]
		 * @param green			numeric value in the range [0, 1]
		 * @param blue			numeric value in the range [0, 1]
		 * @param hue			(output parameter) angle in degrees in the range [0, 360]
		 * @param saturation	(output parameter) numeric value in the range [0, 1]
		 * @param value			(output parameter) numeric value in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT static void rgbToHsv(double red, double green, double blue, double& hue, double& saturation, double& value);

		/**
		 * note: no range check is done on parameters
		 * @param red			numeric value in the range [0, 255]
		 * @param green			numeric value in the range [0, 255]
		 * @param blue			numeric value in the range [0, 255]
		 * @param hue			(output parameter) angle in degrees in the range [0, 360]
		 * @param saturation	(output parameter) numeric value in the range [0, 1]
		 * @param value			(output parameter) numeric value in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT static void rgbToHsv(unsigned int red, unsigned int green, unsigned int blue, double& hue, double& saturation, double& value);

		/**
		 * https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB
		 * note: no range check is done on parameters
		 * @param hue			angle in degrees in the range [0, 360]
		 * @param saturation	numeric value in the range [0, 1]
		 * @param value			numeric value in the range [0, 1]
		 * @param red			(output parameter) numeric value in the range [0, 1]
		 * @param green			(output parameter) numeric value in the range [0, 1]
		 * @param blue			(output parameter) numeric value in the range [0, 1]
		 */
		DLL_IMPORT_OR_EXPORT static void hsvToRgb(double hue, double saturation, double value, double& red, double& green, double& blue);

		/**
		 * https://stackoverflow.com/questions/1914115/converting-color-value-from-float-0-1-to-byte-0-255
		 * note: no range check is done on parameters
		 * @param hue			angle in degrees in the range [0, 360]
		 * @param saturation	numeric value in the range [0, 1]
		 * @param value			numeric value in the range [0, 1]
		 * @param red			(output parameter) numeric value in the range [0, 255]
		 * @param green			(output parameter) numeric value in the range [0, 255]
		 * @param blue			(output parameter) numeric value in the range [0, 255]
		 */
		DLL_IMPORT_OR_EXPORT static void hsvToRgb(double hue, double saturation, double value, unsigned int& red, unsigned int& green, unsigned int& blue);

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const { return XML_TAG; }
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const {
			return "eml22";
		}

		void loadTargetRelationships();
	};
}
