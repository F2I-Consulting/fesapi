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
#include "GraphicalInformationSet.h"

#include "../eml2/PropertyKind.h"

#include "../resqml2/AbstractFeature.h"
#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../resqml2/AbstractRepresentation.h"
#include "../resqml2/AbstractValuesProperty.h"
#include "../resqml2/WellboreMarker.h"
#include "../resqml2/DiscreteColorMap.h"
#include "../resqml2/ContinuousColorMap.h"

using namespace std;
using namespace EML2_NS;
using namespace gsoap_eml2_3;
using namespace COMMON_NS;
using namespace RESQML2_NS;

uint64_t GraphicalInformationSet::getGraphicalInformationSetCount() const
{
	return static_cast<_eml23__GraphicalInformationSet*>(gsoapProxy2_3)->GraphicalInformation.size();
}

uint64_t GraphicalInformationSet::getTargetObjectCount(uint64_t graphicalInformationIndex) const
{
	_eml23__GraphicalInformationSet const * gis = static_cast<_eml23__GraphicalInformationSet*>(gsoapProxy2_3);

	if (graphicalInformationIndex >= gis->GraphicalInformation.size()) {
		throw range_error("The graphicalInformationIndex is out of range.");
	}

	return gis->GraphicalInformation[graphicalInformationIndex]->TargetObject.size();
}

eml23__DataObjectReference* GraphicalInformationSet::getTargetObjectDor(uint64_t graphicalInformationIndex, uint64_t targetIndex) const
{
	_eml23__GraphicalInformationSet const * gis = static_cast<_eml23__GraphicalInformationSet*>(gsoapProxy2_3);

	if (graphicalInformationIndex >= gis->GraphicalInformation.size()) {
		throw range_error("The graphicalInformationIndex is out of range.");
	}
	if (targetIndex >= gis->GraphicalInformation[graphicalInformationIndex]->TargetObject.size()) {
		throw range_error("The targetIndex is out of range.");
	}

	return gis->GraphicalInformation[graphicalInformationIndex]->TargetObject[targetIndex];
}

string GraphicalInformationSet::getTargetObjectUuid(uint64_t graphicalInformationIndex, uint64_t targetIndex) const
{
	return getTargetObjectDor(graphicalInformationIndex, targetIndex)->Uuid;
}

AbstractObject* GraphicalInformationSet::getTargetObject(uint64_t graphicalInformationIndex, uint64_t targetIndex) const
{
	return getRepository()->getDataObjectByUuid(getTargetObjectUuid(graphicalInformationIndex, targetIndex));
}

resqml22__DefaultGraphicalInformation* GraphicalInformationSet::getDefaultGraphicalInformationForAllIndexableElements(AbstractObject const* targetObject) const
{
	_eml23__GraphicalInformationSet* gis = static_cast<_eml23__GraphicalInformationSet*>(gsoapProxy2_3);

	const string targetUuid = targetObject->getUuid();
	for (size_t giIndex = 0; giIndex < gis->GraphicalInformation.size(); ++giIndex) {
		for (size_t targetIndex = 0; targetIndex < gis->GraphicalInformation[giIndex]->TargetObject.size(); ++targetIndex) {
			const string uuid = getTargetObjectUuid(giIndex, targetIndex);
			if (uuid == targetUuid &&
				gis->GraphicalInformation[giIndex]->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__DefaultGraphicalInformation) {
				return static_cast<resqml22__DefaultGraphicalInformation*>(gis->GraphicalInformation[giIndex]);
			}
		}
	}

	return nullptr;
}

resqml22__GraphicalInformationForWholeObject* GraphicalInformationSet::getDefaultGraphicalInformation(AbstractObject const* targetObject) const
{
	resqml22__DefaultGraphicalInformation* defaultGraphicalInformationForAllIndexableElements = getDefaultGraphicalInformationForAllIndexableElements(targetObject);

	if (defaultGraphicalInformationForAllIndexableElements != nullptr) {
		for (size_t indexableElementIndex = 0; indexableElementIndex < defaultGraphicalInformationForAllIndexableElements->IndexableElementInfo.size(); ++indexableElementIndex) {
			if (defaultGraphicalInformationForAllIndexableElements->IndexableElementInfo[indexableElementIndex]->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__GraphicalInformationForWholeObject) {
				return static_cast<resqml22__GraphicalInformationForWholeObject*>(defaultGraphicalInformationForAllIndexableElements->IndexableElementInfo[indexableElementIndex]);
			}
		}
	}

	return nullptr;
}

resqml22__HsvColor* GraphicalInformationSet::getDefaultColor(AbstractObject const* targetObject) const
{
	if (targetObject == nullptr) {
		throw invalid_argument("The target object cannot be null");
	}

	resqml22__GraphicalInformationForWholeObject const* result = getDefaultGraphicalInformation(targetObject);

	return result != nullptr && result->ConstantColor != nullptr ? result->ConstantColor : nullptr;
}

resqml22__ColorInformation* GraphicalInformationSet::getColorInformation(AbstractObject const* targetObject) const
{
	if (targetObject == nullptr) {
		throw invalid_argument("The target object cannot be null");
	}

	_eml23__GraphicalInformationSet const* gis = static_cast<_eml23__GraphicalInformationSet*>(gsoapProxy2_3);

	for (size_t giIndex = 0; giIndex < gis->GraphicalInformation.size(); ++giIndex) {
		for (size_t targetIndex = 0; targetIndex < gis->GraphicalInformation[giIndex]->TargetObject.size(); ++targetIndex) {
			if (getTargetObjectUuid(giIndex, targetIndex) == targetObject->getUuid() &&
				gis->GraphicalInformation[giIndex]->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__ColorInformation) {
				return static_cast<resqml22__ColorInformation*>(gis->GraphicalInformation[giIndex]);
			}
		}
	}

	return nullptr;
}

bool GraphicalInformationSet::hasDirectGraphicalInformation(AbstractObject const* targetObject) const
{
	if (targetObject == nullptr) {
		throw invalid_argument("The target object cannot be null");
	}

	_eml23__GraphicalInformationSet* gis = static_cast<_eml23__GraphicalInformationSet*>(gsoapProxy2_3);

	const std::string targetUuid = targetObject->getUuid();
	for (size_t giIndex = 0; giIndex < gis->GraphicalInformation.size(); ++giIndex) {
		for (size_t targetIndex = 0; targetIndex < gis->GraphicalInformation[giIndex]->TargetObject.size(); ++targetIndex) {
			if (getTargetObjectUuid(giIndex, targetIndex).compare(targetUuid) == 0) {
				return true;
			}
		}
	}

	return false;
}

bool GraphicalInformationSet::hasGraphicalInformation(AbstractObject const* targetObject) const
{
	if (targetObject == nullptr) {
		throw invalid_argument("The target object cannot be null");
	}

	if (hasDirectGraphicalInformation(targetObject)) {
		return true;
	}
	else if (dynamic_cast<AbstractValuesProperty const*>(targetObject) != nullptr) {
		AbstractValuesProperty const* property = static_cast<AbstractValuesProperty const*>(targetObject);
		if (!property->isAssociatedToOneStandardEnergisticsPropertyKind()) {
			return hasDirectGraphicalInformation(property->getPropertyKind());
		}
	}

	return false;
}

bool GraphicalInformationSet::hasDefaultColor(AbstractObject const* targetObject) const
{
	if (targetObject == nullptr) {
		throw invalid_argument("The target object cannot be null");
	}

	return getDefaultColor(targetObject) != nullptr;
}

double GraphicalInformationSet::getDefaultHue(AbstractObject const* targetObject) const
{
	resqml22__HsvColor* color = getDefaultColor(targetObject);
	if (color == nullptr) {
		throw invalid_argument("This object has no default color");
	}

	return color->Hue;
}

double GraphicalInformationSet::getDefaultSaturation(AbstractObject const* targetObject) const
{
	resqml22__HsvColor* color = getDefaultColor(targetObject);
	if (color == nullptr) {
		throw invalid_argument("This object has no default color");
	}

	return color->Saturation;
}

double GraphicalInformationSet::getDefaultValue(AbstractObject const* targetObject) const
{
	resqml22__HsvColor* color = getDefaultColor(targetObject);
	if (color == nullptr) {
		throw invalid_argument("This object has no default color");
	}

	return color->Value;
}

double GraphicalInformationSet::getDefaultAlpha(AbstractObject const* targetObject) const
{
	resqml22__HsvColor* color = getDefaultColor(targetObject);
	if (color == nullptr) {
		throw invalid_argument("This object has no default color");
	}

	return color->Alpha;
}

void GraphicalInformationSet::getDefaultRgbColor(AbstractObject const* targetObject, double & red, double & green, double & blue) const
{
	hsvToRgb(getDefaultHue(targetObject), getDefaultSaturation(targetObject), getDefaultValue(targetObject), red, green, blue);
}

void GraphicalInformationSet::getDefaultRgbColor(AbstractObject const* targetObject, unsigned int & red, unsigned int & green, unsigned int & blue) const
{
	hsvToRgb(getDefaultHue(targetObject), getDefaultSaturation(targetObject), getDefaultValue(targetObject), red, green, blue);
}

bool GraphicalInformationSet::hasDefaultColorTitle(AbstractObject const* targetObject) const
{
	resqml22__HsvColor* color = getDefaultColor(targetObject);
	if (color == nullptr) {
		throw invalid_argument("This object has no default color");
	}

	return color->Title != nullptr;
}

std::string GraphicalInformationSet::getDefaultColorTitle(AbstractObject const* targetObject) const
{
	resqml22__HsvColor* color = getDefaultColor(targetObject);
	if (color == nullptr) {
		throw invalid_argument("This object has no default color");
	}

	if (!hasDefaultColorTitle(targetObject)) {
		throw invalid_argument("This default color has no title");
	}

	return *color->Title;
}

void GraphicalInformationSet::setDefaultHsvColor(AbstractObject * targetObject, double hue, double saturation, double value, double alpha, string const& colorTitle)
{
	if (targetObject == nullptr) {
		throw invalid_argument("The target object cannot be null");
	}

	if (hue < 0 || hue >= 360) {
		throw invalid_argument("hue must be in range [0, 360]");
	}

	if (saturation < 0 || saturation > 1) {
		throw invalid_argument("saturation must be in range [0, 1]");
	}

	if (value < 0 || value > 1) {
		throw invalid_argument("value must be in range [0, 1]");
	}

	if (alpha < 0 || alpha > 1) {
		throw invalid_argument("alpha must be in range [0, 1]");
	}

	if ((dynamic_cast<AbstractFeature *>(targetObject) == nullptr) &&
		(dynamic_cast<AbstractFeatureInterpretation *>(targetObject) == nullptr) &&
		(dynamic_cast<AbstractRepresentation *>(targetObject) == nullptr) &&
		(dynamic_cast<WellboreMarker *>(targetObject) == nullptr)) {
		throw invalid_argument("The object must be a feature, interpretation, representation or wellbore marker.");
	}

	resqml22__HsvColor* color = nullptr;
	resqml22__DefaultGraphicalInformation* defaultGraphicalInformationForAllIndexableElements = getDefaultGraphicalInformationForAllIndexableElements(targetObject);
	if (defaultGraphicalInformationForAllIndexableElements == nullptr) {
		_eml23__GraphicalInformationSet* gis = static_cast<_eml23__GraphicalInformationSet*>(gsoapProxy2_3);
		defaultGraphicalInformationForAllIndexableElements = soap_new_resqml22__DefaultGraphicalInformation(gsoapProxy2_3->soap);
		getRepository()->addRelationship(this, targetObject);
		defaultGraphicalInformationForAllIndexableElements->TargetObject.push_back(targetObject->newEml23Reference());
		defaultGraphicalInformationForAllIndexableElements->ViewerKind = soap_resqml22__ViewerKind2s(gsoapProxy2_3->soap, resqml22__ViewerKind::_3d);
		gis->GraphicalInformation.push_back(defaultGraphicalInformationForAllIndexableElements);
		resqml22__GraphicalInformationForWholeObject* giwo = soap_new_resqml22__GraphicalInformationForWholeObject(gsoapProxy2_3->soap);
		giwo->IsVisible = true;
		defaultGraphicalInformationForAllIndexableElements->IndexableElementInfo.push_back(giwo);
		color = soap_new_resqml22__HsvColor(gsoapProxy2_3->soap);
		giwo->ConstantColor = color;
	}
	else {
		resqml22__GraphicalInformationForWholeObject* giwo = getDefaultGraphicalInformation(targetObject);
		if (giwo == nullptr) {
			giwo = soap_new_resqml22__GraphicalInformationForWholeObject(gsoapProxy2_3->soap);
			giwo->IsVisible = true;
			defaultGraphicalInformationForAllIndexableElements->IndexableElementInfo.push_back(giwo);
			color = soap_new_resqml22__HsvColor(gsoapProxy2_3->soap);
			giwo->ConstantColor = color;
			return;
		}
		else {
			color = giwo->ConstantColor;
			if (color == nullptr) {
				color = soap_new_resqml22__HsvColor(gsoapProxy2_3->soap);
				giwo->ConstantColor = color;
			}
		}
	}

	color->Hue = hue;
	color->Saturation = saturation;
	color->Value = value;
	color->Alpha = alpha;

	if (!colorTitle.empty()) {
		color->Title = gsoap_eml2_3::soap_new_std__string(gsoapProxy2_3->soap);
		*color->Title = colorTitle;
	}
}

/**
* https://en.wikipedia.org/wiki/RGB_color_space
* @param targetObject	The object which receives the color
* @param red			numeric value in the range [0, 1]
* @param green			numeric value in the range [0, 1]
* @param blue			numeric value in the range [0, 1]
* @param alpha			numeric value in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). Default value is 1.
* @param colorTitle		title for the given HSV color
*/
void GraphicalInformationSet::setDefaultRgbColor(AbstractObject* targetObject, double red, double green, double blue, double alpha, std::string const& colorTitle)
{
	if (targetObject == nullptr) {
		throw invalid_argument("The target object cannot be null");
	}

	if (red < 0 || red > 1) {
		throw invalid_argument("red must be in range [0, 1]");
	}

	if (green < 0 || green > 1) {
		throw invalid_argument("green must be in range [0, 1]");
	}

	if (blue < 0 || blue > 1) {
		throw invalid_argument("blue must be in range [0, 1]");
	}

	double hue, saturation, value;
	rgbToHsv(red, green, blue, hue, saturation, value);
	setDefaultHsvColor(targetObject, hue, saturation, value, alpha, colorTitle);
}

/**
* https://en.wikipedia.org/wiki/RGB_color_space
* @param targetObject	The object which receives the color
* @param red			numeric value in the range [0, 255]
* @param green			numeric value in the range [0, 255]
* @param blue			numeric value in the range [0, 255]
* @param alpha			numeric value in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque). Default value is 1.
* @param colorTitle		title for the given HSV color
*/
void GraphicalInformationSet::setDefaultRgbColor(AbstractObject* targetObject, unsigned int red, unsigned int green, unsigned int blue, double alpha, std::string const& colorTitle)
{
	if (targetObject == nullptr) {
		throw invalid_argument("The target object cannot be null");
	}

	if (red > 255) {
		throw invalid_argument("red must be in range [0, 255]");
	}

	if (green > 255) {
		throw invalid_argument("green must be in range [0, 255]");
	}

	if (blue > 255) {
		throw invalid_argument("blue must be in range [0, 255]");
	}

	double hue, saturation, value;
	rgbToHsv(red, green, blue, hue, saturation, value);
	setDefaultHsvColor(targetObject, hue, saturation, value, alpha, colorTitle);
}

bool GraphicalInformationSet::hasDiscreteColorMap(AbstractObject const* targetObject) const
{
	if (targetObject == nullptr) {
		throw invalid_argument("The target object cannot be null");
	}

	resqml22__ColorInformation const* const colorInformation = getColorInformation(targetObject);

	if (colorInformation != nullptr && colorInformation->ColorMap->QualifiedType.find("DiscreteColorMap") != std::string::npos) {
		return true;
	}
	else if (dynamic_cast<AbstractValuesProperty const*>(targetObject) != nullptr) {
		AbstractValuesProperty const* property = static_cast<AbstractValuesProperty const*>(targetObject);
		if (!property->isAssociatedToOneStandardEnergisticsPropertyKind()) {
			return hasDiscreteColorMap(property->getPropertyKind());
		}
	}

	return false;
}

gsoap_eml2_3::eml23__DataObjectReference* GraphicalInformationSet::getDiscreteColorMapDor(AbstractObject const* targetObject) const
{
	if (targetObject == nullptr) {
		throw invalid_argument("The target object cannot be null");
	}

	if (!hasDiscreteColorMap(targetObject)) {
		throw invalid_argument("This object has no discrete color map");
	}

	resqml22__ColorInformation const* const colorInformation = getColorInformation(targetObject);

	if (colorInformation != nullptr && colorInformation->ColorMap != nullptr) {
		return colorInformation->ColorMap;
	}
	else {
		AbstractValuesProperty const* property = static_cast<AbstractValuesProperty const*>(targetObject);
		if (!property->isAssociatedToOneStandardEnergisticsPropertyKind()) {
			return getDiscreteColorMapDor(property->getPropertyKind());
		}
	}

	throw invalid_argument("This object has no discrete color map");
}

std::string GraphicalInformationSet::getDiscreteColorMapUuid(AbstractObject const* targetObject) const
{
	return getDiscreteColorMapDor(targetObject)->Uuid;
}

RESQML2_NS::DiscreteColorMap* GraphicalInformationSet::getDiscreteColorMap(AbstractObject const* targetObject) const
{
	return getRepository()->getDataObjectByUuid<RESQML2_NS::DiscreteColorMap>(getDiscreteColorMapUuid(targetObject));
}

void GraphicalInformationSet::setDiscreteColorMap(AbstractObject* targetObject, RESQML2_NS::DiscreteColorMap* discreteColorMap,
	bool useReverseMapping, bool useLogarithmicMapping)
{
	if (targetObject == nullptr) {
		throw invalid_argument("The target object cannot be null");
	}

	if (discreteColorMap == nullptr) {
		throw invalid_argument("The discrete color map cannot be null");
	}

	if ((dynamic_cast<AbstractValuesProperty*>(targetObject) == nullptr) &&
		(dynamic_cast<EML2_NS::PropertyKind*>(targetObject) == nullptr)) {
		throw invalid_argument("The object must be a property or property kind.");
	}

	_eml23__GraphicalInformationSet* gis = static_cast<_eml23__GraphicalInformationSet*>(gsoapProxy2_3);

	resqml22__ColorInformation* colorInformation = getColorInformation(targetObject);
	if (colorInformation == nullptr) {
		colorInformation = soap_new_resqml22__ColorInformation(gsoapProxy2_3->soap);
		getRepository()->addRelationship(this, targetObject);
		colorInformation->TargetObject.push_back(targetObject->newEml23Reference());
		gis->GraphicalInformation.push_back(colorInformation);
	}

	colorInformation->UseReverseMapping = useReverseMapping;
	colorInformation->UseLogarithmicMapping = useLogarithmicMapping;

	getRepository()->addRelationship(this, discreteColorMap);
	colorInformation->ColorMap = discreteColorMap->newEml23Reference();
}

bool GraphicalInformationSet::hasContinuousColorMap(AbstractObject const* targetObject) const
{
	if (targetObject == nullptr) {
		throw invalid_argument("The target object cannot be null");
	}

	resqml22__ColorInformation const * const colorInformation = getColorInformation(targetObject);

	if (colorInformation != nullptr && colorInformation->ColorMap->QualifiedType.find("ContinuousColorMap") != std::string::npos) {
		return true;
	}
	else if (dynamic_cast<AbstractValuesProperty const*>(targetObject) != nullptr) {
		AbstractValuesProperty const* property = static_cast<AbstractValuesProperty const*>(targetObject);
		if (!property->isAssociatedToOneStandardEnergisticsPropertyKind()) {
			return hasContinuousColorMap(property->getPropertyKind());
		}
	}

	return false;
}

gsoap_eml2_3::eml23__DataObjectReference* GraphicalInformationSet::getContinuousColorMapDor(AbstractObject const* targetObject) const
{
	if (targetObject == nullptr) {
		throw invalid_argument("The target object cannot be null");
	}

	if (!hasContinuousColorMap(targetObject)) {
		throw invalid_argument("This object has no continuous color map");
	}

	resqml22__ColorInformation const* const colorInformation = getColorInformation(targetObject);

	if (colorInformation != nullptr && colorInformation->ColorMap != nullptr) {
		return colorInformation->ColorMap;
	}
	else {
		AbstractValuesProperty const* property = static_cast<AbstractValuesProperty const*>(targetObject);
		if (!property->isAssociatedToOneStandardEnergisticsPropertyKind()) {
			return getContinuousColorMapDor(property->getPropertyKind());
		}
	}

	throw invalid_argument("This object has no continuous color map");
}

std::string GraphicalInformationSet::getContinuousColorMapUuid(AbstractObject const* targetObject) const
{
	return getContinuousColorMapDor(targetObject)->Uuid;
}

RESQML2_NS::ContinuousColorMap* GraphicalInformationSet::getContinuousColorMap(AbstractObject const* targetObject) const
{
	return getRepository()->getDataObjectByUuid<RESQML2_NS::ContinuousColorMap>(getContinuousColorMapUuid(targetObject));
}

void GraphicalInformationSet::setContinuousColorMap(AbstractObject* targetObject, RESQML2_NS::ContinuousColorMap* continuousColorMap,
	bool useReverseMapping, bool useLogarithmicMapping)
{
	if (targetObject == nullptr) {
		throw invalid_argument("The target object cannot be null");
	}

	if (continuousColorMap == nullptr) {
		throw invalid_argument("The continuous color map cannot be null");
	}

	if ((dynamic_cast<AbstractValuesProperty const*>(targetObject) == nullptr) &&
		(dynamic_cast<EML2_NS::PropertyKind const*>(targetObject) == nullptr)) {
		throw invalid_argument("The object must be a property or property kind.");
	}

	_eml23__GraphicalInformationSet* gis = static_cast<_eml23__GraphicalInformationSet*>(gsoapProxy2_3);

	resqml22__ColorInformation* colorInformation = getColorInformation(targetObject);
	if (colorInformation == nullptr) {
		colorInformation = soap_new_resqml22__ColorInformation(gsoapProxy2_3->soap);
		getRepository()->addRelationship(this, targetObject);
		colorInformation->TargetObject.push_back(targetObject->newEml23Reference());
		gis->GraphicalInformation.push_back(colorInformation);
	}

	colorInformation->UseReverseMapping = useReverseMapping;
	colorInformation->UseLogarithmicMapping = useLogarithmicMapping;

	getRepository()->addRelationship(this, continuousColorMap);
	colorInformation->ColorMap = continuousColorMap->newEml23Reference();
}

bool GraphicalInformationSet::hasColorMapMinMax(AbstractObject const* targetObject) const
{
	resqml22__ColorInformation* colorInformation = getColorInformation(targetObject);

	if (colorInformation == nullptr) {
		throw invalid_argument("This object has no color information");
	}

	return colorInformation->MinMax != nullptr;
}

double GraphicalInformationSet::getColorMapMin(AbstractObject const* targetObject) const
{
	if (!hasColorMapMinMax(targetObject)) {
		throw invalid_argument("The color information associated to the target object have no minimum value");
	}

	resqml22__ColorInformation* colorInformation = getColorInformation(targetObject);

	return colorInformation->MinMax->Minimum;
}

double GraphicalInformationSet::getColorMapMax(AbstractObject const* targetObject) const
{
	if (!hasColorMapMinMax(targetObject)) {
		throw invalid_argument("The color information associated to the target object have no maximum value");
	}

	resqml22__ColorInformation* colorInformation = getColorInformation(targetObject);

	return colorInformation->MinMax->Maximum;
}

void GraphicalInformationSet::setColorMapMinMax(AbstractObject const* targetObject, double min, double max) const
{
	resqml22__ColorInformation* colorInformation = getColorInformation(targetObject);

	if (colorInformation == nullptr) {
		throw invalid_argument("This object has no color information");
	}

	if (colorInformation->MinMax == nullptr) {
		colorInformation->MinMax = soap_new_resqml22__MinMax(gsoapProxy2_3->soap);
	}
	colorInformation->MinMax->Minimum = min;
	colorInformation->MinMax->Maximum = max;
}

bool GraphicalInformationSet::hasValueVectorIndex(AbstractObject const* targetObject)
{
	if (targetObject == nullptr) {
		throw invalid_argument("The target object cannot be null");
	}

	resqml22__ColorInformation const* const colorInformation = getColorInformation(targetObject);

	if (colorInformation == nullptr) {
		throw invalid_argument("The target object have no color information (it is not related to any continuous or discrete color map)");
	}

	return colorInformation->ValueVectorIndex != nullptr;
}

int64_t GraphicalInformationSet::getValueVectorIndex(AbstractObject const* targetObject) {
	if (!hasValueVectorIndex(targetObject)) {
		throw invalid_argument("The color information associated to the target object has no value vector index");
	}

	resqml22__ColorInformation const* const colorInformation = getColorInformation(targetObject);
	return *colorInformation->ValueVectorIndex;
}

void GraphicalInformationSet::setValueVectorIndex(AbstractObject const* targetObject, int64_t valueVectorIndex) {
	resqml22__ColorInformation* colorInformation = getColorInformation(targetObject);

	if (colorInformation == nullptr) {
		throw invalid_argument("This object has no color information");
	}

	if (colorInformation->ValueVectorIndex == nullptr) {
		colorInformation->ValueVectorIndex = soap_new_LONG64(gsoapProxy2_3->soap);
	}
	*colorInformation->ValueVectorIndex = valueVectorIndex;
}

void GraphicalInformationSet::rgbToHsv(double red, double green, double blue, double & hue, double & saturation, double & value)
{
	double max = red > green ? red : green;
	max = max > blue ? max : blue;

	double min = red < green ? red : green;
	min = min < blue ? min : blue;

	// computing hue

	if (max == min)
		hue = 0;
	else if (max == red)
		hue = 60. * (green - blue) / (max - min);
	else if (max == green)
		hue = 60. * (2. + (blue - red) / (max - min));
	else // max == b
		hue = 60. * (4. + (red - green) / (max - min));

	if (hue < 0.)
		hue = hue + 360.;

	// computing saturation

	if (max == 0.)
		saturation = 0.;
	else
		saturation = (max - min) / max;

	// computing value

	value = max;
}

void GraphicalInformationSet::rgbToHsv(unsigned int red, unsigned int green, unsigned int blue, double & hue, double & saturation, double & value)
{
	rgbToHsv(red / 255., green / 255., blue / 255., hue, saturation, value);
}

void GraphicalInformationSet::hsvToRgb(double hue, double saturation, double value, double & red, double & green, double & blue)
{
	double c = value * saturation;
	double hprim = hue / 60.;
	double x = c * (1. - fabs(fmod(hprim, 2) - 1.));
	double m = value - c;

	if (0. <= hprim && hprim <= 1.) {
		red = c;
		green = x;
		blue = 0.;
	}
	else if (1. <= hprim && hprim <= 2.) {
		red = x;
		green = c;
		blue = 0.;
	}
	else if (2. <= hprim && hprim <= 3.) {
		red = 0.;
		green = c;
		blue = x;
	}
	else if (3. <= hprim && hprim <= 4.) {
		red = 0.;
		green = x;
		blue = c;
	}
	else if (4. <= hprim && hprim <= 5.) {
		red = x;
		green = 0.;
		blue = c;
	}
	else { // (5. <= hprim << hprim <= 6.)
		red = c;
		green = 0.;
		blue = x;
	}

	red = red + m;
	green = green + m;
	blue = blue + m;
}

void GraphicalInformationSet::hsvToRgb(double hue, double saturation, double value, unsigned int & red, unsigned int & green, unsigned int & blue)
{
	double r, g, b;
	hsvToRgb(hue, saturation, value, r, g, b);

	r = max(0.0, min(1.0, r));
	red = floor(r == 1.0 ? 255 : r * 256.0);

	g = max(0.0, min(1.0, g));
	green = floor(g == 1.0 ? 255 : g * 256.0);

	b = max(0.0, min(1.0, b));
	blue = floor(b == 1.0 ? 255 : b * 256.0);
}

void GraphicalInformationSet::loadTargetRelationships()
{
	_eml23__GraphicalInformationSet const* gis = static_cast<_eml23__GraphicalInformationSet*>(gsoapProxy2_3);

	for (size_t giIndex = 0; giIndex < gis->GraphicalInformation.size(); ++giIndex) {
		for (size_t targetIndex = 0; targetIndex < gis->GraphicalInformation[giIndex]->TargetObject.size(); ++targetIndex) {
			convertDorIntoRel(getTargetObjectDor(giIndex, targetIndex));
			if (gis->GraphicalInformation[giIndex]->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__ColorInformation) {
				resqml22__ColorInformation const* colorInformation = static_cast<resqml22__ColorInformation*>(gis->GraphicalInformation[giIndex]);
				if (colorInformation->ColorMap != nullptr) {
					convertDorIntoRel(colorInformation->ColorMap);
				}
			}
		}
	}
}
