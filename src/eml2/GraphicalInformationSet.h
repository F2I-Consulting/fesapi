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

namespace EML2_NS
{
	/** @brief	Proxy class for handling the graphical information of data objects. */
	class GraphicalInformationSet : public COMMON_NS::AbstractObject
	{
	public:
		/**
		 * Destructor does nothing since the memory is managed by the gsoap context.
		 */
		virtual ~GraphicalInformationSet() = default;

		/**
		 * Gets the size of this graphical information set
		 *
		 * @exception	std::range_error	If the size is strictly greater than unsigned int max.
		 *
		 * @returns	The size of this graphical information set.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getGraphicalInformationSetCount() const;

		/**
		 * Gets the data object reference of the object which receives some graphical information at a
		 * particular index of the graphical information set
		 *
		 * @exception	std::range_error	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the data object we look for.
		 *
		 * @returns	The data object reference of the object which receives some graphical information at
		 * 			@p index.
		 */
		COMMON_NS::DataObjectReference getTargetObjectDor(uint64_t index) const;

		/**
		 * Gets the UUID of the object which receives some graphical information at a particular index
		 * of the graphical information set
		 *
		 * @exception	std::range_error	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the data object we look for.
		 *
		 * @returns	The UUUID of the object which receives some graphical information at @p index.
		 */
		DLL_IMPORT_OR_EXPORT std::string getTargetObjectUuid(uint64_t index) const;

		/**
		 * Gets the data object which receives some graphical information at a particular index of the
		 * graphical information set
		 *
		 * @param 	index	Zero-based index of the data object we look for.
		 *
		 * @returns	The data object which receives some graphical information at @p index.
		 */
		DLL_IMPORT_OR_EXPORT AbstractObject* getTargetObject(uint64_t index) const;

		/**
		 * Query if a given data object has some direct graphical information, that is to say if there exists
		 * a direct association between this data object and a graphical information
		 *
		 * @exception	std::invalid_argument	If the target object is null.
		 *
		 * @param 	targetObject	The data object we want to test for having some graphical information.
		 *
		 * @returns	True if @p targetObject has some graphical information, else false.
		 */
		bool hasDirectGraphicalInformation(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Query if a given data object has some graphical information. If it has no direct graphical
		 * information (see {@link hasDirectGraphicalInformation}) and it is a property, we also check
		 * that its property kind has some
		 *
		 * @exception	std::invalid_argument	If the target object is null.
		 *
		 * @param 	targetObject	The data object we want to test for having some graphical information.
		 *
		 * @returns	True if @p targetObject (or its property kind) has some graphical information, else false.
		 */
		DLL_IMPORT_OR_EXPORT bool hasGraphicalInformation(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Query if a given data object has a default color. It only looks at direct color association (see
		 * {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If the target object is null.
		 *
		 * @param 	targetObject	The data object we want to test for having a default color.
		 *
		 * @returns	True @p targetObject has one default color, else false.
		 */
		DLL_IMPORT_OR_EXPORT bool hasDefaultColor(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the default hue of a given data object. It only looks at direct color association (see
		 * {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If @p targetObject has no default color.
		 *
		 * @param 	targetObject	The data object for which we look for the default hue.
		 *
		 * @returns	The default hue of @p targetObject in the range [0, 360].
		 */
		DLL_IMPORT_OR_EXPORT double getDefaultHue(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the default saturation of a given data object. It only looks at direct color association
		 * (see {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If @p targetObject has no default color.
		 *
		 * @param 	targetObject	The data object for which we look for the default saturation.
		 *
		 * @returns	The default saturation of @p targetObject in the range [0, 1].
		 */
		DLL_IMPORT_OR_EXPORT double getDefaultSaturation(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the default color value of a given data object. It only looks at direct color
		 * association (see {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If @p targetObject has no default color.
		 *
		 * @param 	targetObject	The data object for which we look for the default color value.
		 *
		 * @returns	The default color value of @p targetObject in the range [0, 1].
		 */
		DLL_IMPORT_OR_EXPORT double getDefaultValue(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the default alpha value of a given data object. It only looks at direct color
		 * association (see {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If @p targetObject has no default color.
		 *
		 * @param 	targetObject	The data object for which we look for the default alpha value.
		 *
		 * @returns	The default alpha value in the range [0, 1] (0 means transparent and 1 means opaque).
		 */
		DLL_IMPORT_OR_EXPORT double getDefaultAlpha(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the default RGB color (https://en.wikipedia.org/wiki/RGB_color_space) of a given data
		 * object. It only looks at direct color association (see {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If @p targetObject has no default color.
		 *
		 * @param 	   	targetObject	The data object for which we look for the default RGB color.
		 * @param [out]	red				Red value in the range [0, 1].
		 * @param [out]	green			Green value in the range [0, 1].
		 * @param [out]	blue			Blue value in the range [0, 1].
		 */
		DLL_IMPORT_OR_EXPORT void getDefaultRgbColor(COMMON_NS::AbstractObject const* targetObject, double& red, double& green, double& blue) const;

		/**
		 * Gets the default RGB color (https://en.wikipedia.org/wiki/RGB_color_space) of a given data
		 * object. It only looks at direct color association (see {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If @p targetObject has no default color.
		 *
		 * @param 	   	targetObject	The data object for which we look for the default RGB color.
		 * @param [out]	red				Red value in the range [0, 255].
		 * @param [out]	green			Green value in the range [0, 255].
		 * @param [out]	blue			Blue value in the range [0, 255].
		 */
		DLL_IMPORT_OR_EXPORT void getDefaultRgbColor(COMMON_NS::AbstractObject const* targetObject, unsigned int& red, unsigned int& green, unsigned int& blue) const;

		/**
		 * Query if a given data object has a default color title. It only looks at direct color
		 * association (see {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If @p targetObject has no default color.
		 *
		 * @param 	targetObject	The data object for which we look for a default color title.
		 *
		 * @returns	True if @p targetObject has a default color title, else false.
		 */
		DLL_IMPORT_OR_EXPORT bool hasDefaultColorTitle(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the default color title of a given data object. It only looks at direct color
		 * association (see {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If @p targetObject has no default color or if its default
		 * 										color has no title.
		 *
		 * @param 	targetObject	The data object for which we look for the default color title.
		 *
		 * @returns	The default title.
		 */
		DLL_IMPORT_OR_EXPORT std::string getDefaultColorTitle(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Sets the default HSV color (https://en.wikipedia.org/wiki/HSV_color_space) of a given data
		 * object
		 *
		 * @exception	std::invalid_argument	If @p targetObject is null or if it is not a feature,
		 * 										interpretation, representation or wellbore marker.
		 * @exception	std::invalid_argument	If @p hue is out of range [0, 360].
		 * @exception	std::invalid_argument	If @p saturation, @p value or @p alpha is out of range [0,
		 * 										1].
		 *
		 * @param [in]	targetObject	The data object which receives the color.
		 * @param 	  	hue				The hue angle in degrees in range [0, 360].
		 * @param 	  	saturation  	The saturation value in range [0, 1].
		 * @param 	  	value			The color value in range [0, 1].
		 * @param 	  	alpha			(Optional) The alpha value in range [0, 1] for transparency
		 * 								channel (0 means transparent and 1 means opaque). Default value is 1.
		 * @param 	  	colorTitle  	(Optional) The title of the given HSV color. It is not set if
		 * 								title is empty (default).
		 */
		DLL_IMPORT_OR_EXPORT void setDefaultHsvColor(COMMON_NS::AbstractObject* targetObject, double hue, double saturation, double value, double alpha = 1.0, std::string const& colorTitle = "");

		/**
		 * Sets the default RGB color https://en.wikipedia.org/wiki/RGB_color_space of a given data
		 * object
		 *
		 * @exception	std::invalid_argument	If @p targetObject is null or if it is not a feature,
		 * 										interpretation, representation or wellbore marker.
		 * @exception	std::invalid_argument	If @p red, @p green, @p blue or @p alpha is out of range
		 * 										[0,
		 * 										1].
		 *
		 * @param [in]	targetObject	The data object which receives the color.
		 * @param 	  	red				Red value in range [0, 1].
		 * @param 	  	green			Green value in range [0, 1].
		 * @param 	  	blue			Blue value in range [0, 1].
		 * @param 	  	alpha			(Optional) The alpha value in range [0, 1] for transparency
		 * 								channel (0 means transparent and 1 means opaque). Default value is 1.
		 * @param 	  	colorTitle  	(Optional) The title of the given HSV color. It is not set if
		 * 								title is empty (default).
		 */
		DLL_IMPORT_OR_EXPORT void setDefaultRgbColor(COMMON_NS::AbstractObject* targetObject, double red, double green, double blue, double alpha = 1.0, std::string const& colorTitle = "");

		/**
		 * Sets the default RGB color https://en.wikipedia.org/wiki/RGB_color_space of a given data
		 * object
		 *
		 * @exception	std::invalid_argument	If @p targetObject is null or if it is not a feature,
		 * 										interpretation, representation or wellbore marker.
		 * @exception	std::invalid_argument	If @p red, @p green, @p blue or @p alpha is out of range
		 * 										[0,
		 * 										255].
		 * @exception	std::invalid_argument	If @p alpha is out of range [0,1].
		 *
		 * @param [in]	targetObject	The data object which receives the color.
		 * @param 	  	red				Red value in range [0, 255].
		 * @param 	  	green			Green value in range [0, 255].
		 * @param 	  	blue			Blue value in range [0, 255].
		 * @param 	  	alpha			(Optional) The alpha value in range [0, 1] for transparency
		 * 								channel (0 means transparent and 1 means opaque). Default value is 1.
		 * @param 	  	colorTitle  	(Optional) The title of the given HSV color. It is not set if
		 * 								title is empty (default).
		 */
		DLL_IMPORT_OR_EXPORT void setDefaultRgbColor(COMMON_NS::AbstractObject* targetObject, unsigned int red, unsigned int green, unsigned int blue, double alpha = 1.0, std::string const& colorTitle = "");

		/**
		 * Query if a given data object has a discrete color map. If it has not and it is a property, we
		 * also look for its property kind discrete color map
		 *
		 * @exception	std::invalid_argument	If @p targetObject is null.
		 *
		 * @param 	targetObject	The data object for which we look for a discrete color map.
		 *
		 * @returns	True if @p targetObject (or its property kind) has a discrete color map, else false.
		 */
		DLL_IMPORT_OR_EXPORT bool hasDiscreteColorMap(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the discrete color map data object reference of a given data object. If the data object
		 * has no discrete color map and if it is a property, we also look for its property kind
		 * discrete color map
		 *
		 * @exception	std::invalid_argument	If @p targetObject is null or if it has no discrete color
		 * 										map.
		 *
		 * @param 	targetObject	The data object for which we look for a discrete color map.
		 *
		 * @returns	A data object reference on the discrete color map of @p targetObject (or of its
		 * 			property kind).
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__DataObjectReference* getDiscreteColorMapDor(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the discrete color map data UUID of a given data object. If the data object has no
		 * discrete color map and if it is a property, we also look for its property kind discrete color
		 * map
		 *
		 * @exception	std::invalid_argument	If @p targetObject is null or if it has no discrete color
		 * 										map.
		 *
		 * @param 	targetObject	The data object for which we look for a discrete color map.
		 *
		 * @returns	The UUID of the discrete color map of @p targetObject (or of its property kind).
		 */
		DLL_IMPORT_OR_EXPORT std::string getDiscreteColorMapUuid(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the discrete color map of a given data object. If the data object has no discrete color
		 * map and if it is a property, we also look for its property kind discrete color map
		 *
		 * @exception	std::invalid_argument	If @p targetObject is null or if it has no discrete color
		 * 										map.
		 *
		 * @param 	targetObject	The data object for which we look for a discrete color map.
		 *
		 * @returns	The discrete color map of @p targetObject (or of its property kind).
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::DiscreteColorMap* getDiscreteColorMap(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Sets a discrete color map on a given data object
		 *
		 * @exception	std::invalid_argument	If @p targetObject or @p discreteColorMap is null.
		 * @exception	std::invalid_argument	If @p targetObject is neither a property nor a property
		 * 										kind.
		 *
		 * @param [in]	targetObject		 	The data object on which we want to set a discrete color
		 * 										map.
		 * @param [in]	discreteColorMap	 	The discrete color map we want to set on the data object.
		 * @param 	  	useReverseMapping	 	(Optional) It true, it indicates that the minimum value
		 * 										of the property corresponds to the maximum index of the
		 * 										color map and that the maximum value of the property
		 * 										corresponds to the minimum index of the color map.
		 * 										Default value is false.
		 * @param 	  	useLogarithmicMapping	(Optional) If true, it indicates that the log of the
		 * 										property values are taken into account when mapped with
		 * 										the index of the color map. Default value is false.
		 */
		DLL_IMPORT_OR_EXPORT void setDiscreteColorMap(COMMON_NS::AbstractObject* targetObject, RESQML2_NS::DiscreteColorMap* discreteColorMap,
			bool useReverseMapping = false, bool useLogarithmicMapping = false);

		/**
		 * Query if a given data object has a continuous color map. If it has not and it is a property,
		 * we also look for its property kind continuous color map
		 *
		 * @exception	std::invalid_argument	If @p targetObject is null.
		 *
		 * @param 	targetObject	The data object for which we look for a continuous color map.
		 *
		 * @returns	True if @p targetObject (or its property kind) has a continuous color map, else false.
		 */
		DLL_IMPORT_OR_EXPORT bool hasContinuousColorMap(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the continuous color map data object reference of a given data object. If the data
		 * object has no continuous color map and if it is a property, we also look for its property kind
		 * continuous color map
		 *
		 * @exception	std::invalid_argument	If @p targetObject is null or if it has no continuous
		 * 										color map.
		 *
		 * @param 	targetObject	The data object for which we look for a continuous color map.
		 *
		 * @returns	A data object reference on the continuous color map of @p targetObject (or of its
		 * 			property kind).
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__DataObjectReference* getContinuousColorMapDor(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the continuous color map data UUID of a given data object. If the data object has no
		 * continuous color map and if it is a property, we also look for its property kind continuous
		 * color map
		 *
		 * @exception	std::invalid_argument	If @p targetObject is null or if it has no continuous
		 * 										color map.
		 *
		 * @param 	targetObject	The data object for which we look for a continuous color map.
		 *
		 * @returns	The UUID of the continuous color map of @p targetObject (or of its property kind).
		 */
		DLL_IMPORT_OR_EXPORT std::string getContinuousColorMapUuid(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the continuous color map of a given data object. If the data object has no continuous
		 * color map and if it is a property, we also look for its property kind continuous color map
		 *
		 * @exception	std::invalid_argument	If @p targetObject is null or if it has no continuous
		 * 										color map.
		 *
		 * @param 	targetObject	The data object for which we look for a continuous color map.
		 *
		 * @returns	The continuous color map of @p targetObject (or of its property kind).
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::ContinuousColorMap* getContinuousColorMap(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Sets a continuous color map on a given data object
		 *
		 * @exception	std::invalid_argument	If @p targetObject or @p continuous is null.
		 * @exception	std::invalid_argument	If @p targetObject is neither a property nor a property
		 * 										kind.
		 *
		 * @param [in]	targetObject		 	The data object on which we want to set a continuous
		 * 										color map.
		 * @param [in]	continuousColorMap   	The continuous color map we want to set on the data
		 * 										object.
		 * @param 	  	useReverseMapping	 	(Optional) It true, it indicates that the minimum value
		 * 										of the property corresponds to the maximum index of the
		 * 										color map and that the maximum value of the property
		 * 										corresponds to the minimum index of the color map.
		 * 										Default value is false.
		 * @param 	  	useLogarithmicMapping	(Optional) If true, it indicates that the log of the
		 * 										property values are taken into account when mapped with
		 * 										the index of the color map. Default value is false.
		 */
		DLL_IMPORT_OR_EXPORT void setContinuousColorMap(COMMON_NS::AbstractObject* targetObject, RESQML2_NS::ContinuousColorMap* continuousColorMap,
			bool useReverseMapping = false, bool useLogarithmicMapping = false);

		/**
		 * Query if a given data object has minimum and maximum values to map with a color map. It only
		 * looks at direct color association (see {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If @p targetObject is null or if it has no color
		 * 										information.
		 *
		 * @param 	targetObject	The data object for which we look for the minimum and maximum values.
		 *
		 * @returns	True if minimum and maximum values exist, else false.
		 */
		DLL_IMPORT_OR_EXPORT bool hasColorMapMinMax(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the minimum value to map with a color map for a given data object. It only looks at
		 * direct color association (see {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If the color information associated @p targetObject has
		 * 										no minimum value.
		 *
		 * @param 	targetObject	The data object for which we look for the minimum value.
		 *
		 * @returns	The minimum value.
		 */
		DLL_IMPORT_OR_EXPORT double getColorMapMin(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Gets the maximum value to map with a color map for a given data object. It only looks at
		 * direct color association (see {@link hasDirectGraphicalInformation})
		 *
		 * @exception	std::invalid_argument	If the color information associated @p targetObject has
		 * 										no maximum value.
		 *
		 * @param 	targetObject	The data object for which we look for the maximum value.
		 *
		 * @returns	The maximum value.
		 */
		DLL_IMPORT_OR_EXPORT double getColorMapMax(COMMON_NS::AbstractObject const* targetObject) const;

		/**
		 * Sets the minimum and maximum values to map with a color map for a given data object
		 *
		 * @exception	std::invalid_argument	If @p targetObject has no color information.
		 *
		 * @param 	targetObject	The data object for which we want to set the minimum and maximum
		 * 							values to map with a color map.
		 * @param 	min				The minimum value.
		 * @param 	max				The maximum value.
		 */
		DLL_IMPORT_OR_EXPORT void setColorMapMinMax(COMMON_NS::AbstractObject const* targetObject, double min, double max) const;

		/**
		 * Query if a given data object indicates which value vector index to look when mapping with a
		 * color map. It is especially useful for vectorial property and for geometry
		 *
		 * @exception	std::invalid_argument	If @p targetObject is null or if it has no color
		 * 										information.
		 *
		 * @param 	targetObject	The data object for which we look for a value vector index to look
		 * 							when mapping with a color map.
		 *
		 * @returns	True if a value vector index exists, else false.
		 */
		DLL_IMPORT_OR_EXPORT bool hasValueVectorIndex(COMMON_NS::AbstractObject const* targetObject);

		/**
		 * Gets the value vector index to look when mapping with a color map. It is especially useful
		 * for vectorial property and for geometry
		 *
		 * @exception	std::invalid_argument	If the color information associated to @p targetObject
		 * 										has no value vector index.
		 *
		 * @param 	targetObject	The data object for which we look for a value vector index to look
		 * 							when mapping with a color map.
		 *
		 * @returns	The value vector index.
		 */
		DLL_IMPORT_OR_EXPORT int64_t getValueVectorIndex(COMMON_NS::AbstractObject const* targetObject);

		/**
		 * Sets the value vector index to look when mapping with a color map. It is especially useful
		 * for vectorial property and for geometry
		 *
		 * @exception	std::invalid_argument	If @p targetObject has no color information.
		 *
		 * @param 	targetObject		The data object for which we want to set the value vector index
		 * 								to look when mapping with a color map.
		 * @param 	valueVectorIndex	The value vector index to set.
		 */
		DLL_IMPORT_OR_EXPORT void setValueVectorIndex(COMMON_NS::AbstractObject const* targetObject, int64_t valueVectorIndex);

		/**
		 * Converts RGB to HSV color (using https://en.wikipedia.org/wiki/HSL_and_HSV#From_RGB
		 * algorithm). No range check is done on parameters
		 *
		 * @param 	   	red		  	Numeric value in the range [0, 1].
		 * @param 	   	green	  	Numeric value in the range [0, 1].
		 * @param 	   	blue	  	Numeric value in the range [0, 1].
		 * @param [out]	hue		  	Angle in degrees in the range [0, 360].
		 * @param [out]	saturation	Numeric value in the range [0, 1].
		 * @param [out]	value	  	Numeric value in the range [0, 1].
		 */
		DLL_IMPORT_OR_EXPORT static void rgbToHsv(double red, double green, double blue, double& hue, double& saturation, double& value);

		/**
		 * Converts RGB to HSV color (using https://en.wikipedia.org/wiki/HSL_and_HSV#From_RGB
		 * algorithm). No range check is done on parameters
		 *
		 * @param 	   	red		  	Numeric value in the range [0, 255].
		 * @param 	   	green	  	Numeric value in the range [0, 255].
		 * @param 	   	blue	  	Numeric value in the range [0, 255].
		 * @param [out]	hue		  	Angle in degrees in the range [0, 360].
		 * @param [out]	saturation	Numeric value in the range [0, 1].
		 * @param [out]	value	  	Numeric value in the range [0, 1].
		 */
		DLL_IMPORT_OR_EXPORT static void rgbToHsv(unsigned int red, unsigned int green, unsigned int blue, double& hue, double& saturation, double& value);

		/**
		 * Converts HSV to RGB color (using https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB
		 * algorithm). No range check is done on parameters
		 *
		 * @param 	   	hue		  	Angle in degrees in the range [0, 360].
		 * @param 	   	saturation	Numeric value in the range [0, 1].
		 * @param 	   	value	  	Numeric value in the range [0, 1].
		 * @param [out]	red		  	Numeric value in the range.
		 * @param [out]	green	  	Numeric value in the range.
		 * @param [out]	blue	  	Numeric value in the range.
		 */
		DLL_IMPORT_OR_EXPORT static void hsvToRgb(double hue, double saturation, double value, double& red, double& green, double& blue);

		/**
		 * Converts HSV to RGB color (using
		 * https://stackoverflow.com/questions/1914115/converting-color-value-from-float-0-1-to-byte-0-255
		 * algorithm). No range check is done on parameters
		 *
		 * @param 	   	hue		  	Angle in degrees in the range [0, 360].
		 * @param 	   	saturation	Numeric value in the range [0, 1].
		 * @param 	   	value	  	Numeric value in the range [0, 1].
		 * @param [out]	red		  	Numeric value in the range.
		 * @param [out]	green	  	Numeric value in the range.
		 * @param [out]	blue	  	Numeric value in the range.
		 */
		DLL_IMPORT_OR_EXPORT static void hsvToRgb(double hue, double saturation, double value, unsigned int& red, unsigned int& green, unsigned int& blue);

		/** The standard XML tag without XML namespace for serializing this data object */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "GraphicalInformationSet";

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const { return XML_TAG; }

		/**
		 * Gets the XML namespace for the tags for the XML serialization of this instance
		 *
		 * @returns	The XML namespace of this instance.
		 */
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const {
			return "eml23";
		}

		/**
		 * Reads the forward relationships of this data object and update the <tt>.rels</tt> of the
		 * associated data repository.
		 */
		void loadTargetRelationships() final;
	
	protected:

		/**
		* Default constructor
		*/
		GraphicalInformationSet() {}
	
		/**
		 * Constructor. Only to be used in partial transfer context
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		GraphicalInformationSet(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject): COMMON_NS::AbstractObject(partialObject) {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		GraphicalInformationSet(gsoap_eml2_3::_eml23__GraphicalInformationSet* fromGsoap) :
			COMMON_NS::AbstractObject(fromGsoap) {}
	
	private:
		gsoap_eml2_3::resqml22__DefaultGraphicalInformation* getDefaultGraphicalInformationForAllIndexableElements(COMMON_NS::AbstractObject const* targetObject) const;
		gsoap_eml2_3::resqml22__GraphicalInformationForWholeObject* getDefaultGraphicalInformation(COMMON_NS::AbstractObject const* targetObject) const;
		gsoap_eml2_3::resqml22__HsvColor* getDefaultColor(COMMON_NS::AbstractObject const* targetObject) const;
		gsoap_eml2_3::resqml22__ColorInformation* getColorInformation(COMMON_NS::AbstractObject const* targetObject) const;
	};
}
