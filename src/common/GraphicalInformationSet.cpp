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
#include "common/GraphicalInformationSet.h"

#include "tools/Misc.h"
#include "resqml2/AbstractFeature.h"
#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2/AbstractRepresentation.h"
#include "resqml2_0_1/WellboreMarker.h"
#include "resqml2_2/AbstractColorMap.h"
#include "resqml2_2/DiscreteColorMap.h"
#include "resqml2_2/ContinuousColorMap.h"

#include <stdexcept>

using namespace std;
using namespace COMMON_NS;
using namespace gsoap_eml2_2;
using namespace epc;
using namespace RESQML2_NS;
using namespace RESQML2_0_1_NS;
using namespace RESQML2_2_NS;

const char* GraphicalInformationSet::XML_TAG = "GraphicalInformationSet";

GraphicalInformationSet::GraphicalInformationSet(soap* soapContext, const string & guid, const string & title)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_2 = soap_new_eml22__GraphicalInformationSet(soapContext, 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");
}

unsigned int GraphicalInformationSet::getGraphicalInformationSetCount() const
{
	_eml22__GraphicalInformationSet* gis = static_cast<_eml22__GraphicalInformationSet*>(gsoapProxy2_2);

	size_t count = gis->GraphicalInformation.size();
	
	if (count > (numeric_limits<unsigned int>::max)()) {
		throw range_error("The graphical information set count is out of range.");
	}

	return static_cast<unsigned int>(count);
}

eml22__DataObjectReference* GraphicalInformationSet::getTargetObjectDor(unsigned int index) const
{
	_eml22__GraphicalInformationSet* gis = static_cast<_eml22__GraphicalInformationSet*>(gsoapProxy2_2);

	if (index >= gis->GraphicalInformation.size()) {
		throw range_error("The index if out of range in GraphicalInformationSet");
	}

	return gis->GraphicalInformation[index]->TargetObject;
}

string GraphicalInformationSet::getTargetObjectUuid(unsigned int index) const
{
	return getTargetObjectDor(index)->Uuid;
}

AbstractObject* GraphicalInformationSet::getTargetObject(unsigned int index) const
{
	return epcDocument->getDataObjectByUuid(getTargetObjectUuid(index));
}

vector<Relationship> GraphicalInformationSet::getAllSourceRelationships() const
{
	vector<Relationship> result = AbstractObject::getAllSourceRelationships();
	return result;
}

vector<Relationship> GraphicalInformationSet::getAllTargetRelationships() const
{
	vector<Relationship> result;

	_eml22__GraphicalInformationSet* gis = static_cast<_eml22__GraphicalInformationSet*>(gsoapProxy2_2);

	for (size_t giIndex = 0; giIndex < gis->GraphicalInformation.size(); ++giIndex) {
		eml22__DataObjectReference* dor = getTargetObjectDor(giIndex);
		Relationship relFop(misc::getPartNameFromReference(dor), "", dor->Uuid);
		relFop.setDestinationObjectType();
		result.push_back(relFop);

		if (resqml2__ColorInformation* colorInformation = dynamic_cast<resqml2__ColorInformation*>(gis->GraphicalInformation[giIndex])) {
			if (colorInformation->DiscreteColorMap != nullptr) {
				Relationship relFop(misc::getPartNameFromReference(colorInformation->DiscreteColorMap), "", colorInformation->DiscreteColorMap->Uuid);
				relFop.setDestinationObjectType();
				result.push_back(relFop);
			}

			if (colorInformation->ContinuousColorMap != nullptr) {
				Relationship relFop(misc::getPartNameFromReference(colorInformation->ContinuousColorMap), "", colorInformation->ContinuousColorMap->Uuid);
				relFop.setDestinationObjectType();
				result.push_back(relFop);
			}
		}
	}

	return result;
}

resqml2__DefaultGraphicalInformation* GraphicalInformationSet::getDefaultGraphicalInformationForAllIndexableElements(AbstractObject* targetObject) const
{
	_eml22__GraphicalInformationSet* gis = static_cast<_eml22__GraphicalInformationSet*>(gsoapProxy2_2);

	string targetUuid = targetObject->getUuid();
	for (size_t giIndex = 0; giIndex < gis->GraphicalInformation.size(); ++giIndex) {
		string uuid = getTargetObjectUuid(giIndex);
		if (uuid.compare(targetUuid) == 0 &&
			gis->GraphicalInformation[giIndex]->soap_type() == SOAP_TYPE_gsoap_eml2_2_resqml2__DefaultGraphicalInformation) {
			return static_cast<resqml2__DefaultGraphicalInformation*>(gis->GraphicalInformation[giIndex]);
		}
	}

	return nullptr;
}

resqml2__GraphicalInformationForWholeObject* GraphicalInformationSet::getDefaultGraphicalInformation(AbstractObject* targetObject) const
{
	resqml2__DefaultGraphicalInformation* defaultGraphicalInformationForAllIndexableElements = getDefaultGraphicalInformationForAllIndexableElements(targetObject);

	if (defaultGraphicalInformationForAllIndexableElements != nullptr) {
		for (size_t indexableElementIndex = 0; indexableElementIndex < defaultGraphicalInformationForAllIndexableElements->IndexableElementInfo.size(); ++indexableElementIndex) {
			if (defaultGraphicalInformationForAllIndexableElements->IndexableElementInfo[indexableElementIndex]->soap_type() == SOAP_TYPE_gsoap_eml2_2_resqml2__GraphicalInformationForWholeObject) {
				return static_cast<resqml2__GraphicalInformationForWholeObject*>(defaultGraphicalInformationForAllIndexableElements->IndexableElementInfo[indexableElementIndex]);
			}
		}
	}

	return nullptr;
}

resqml2__HsvColor* GraphicalInformationSet::getDefaultColor(AbstractObject* targetObject) const
{
	resqml2__GraphicalInformationForWholeObject* result = getDefaultGraphicalInformation(targetObject);
	return result != nullptr && result->ConstantColor != nullptr ? result->ConstantColor : nullptr;
}

resqml2__ColorInformation* GraphicalInformationSet::getColorInformation(AbstractObject* targetObject) const
{
	_eml22__GraphicalInformationSet* gis = static_cast<_eml22__GraphicalInformationSet*>(gsoapProxy2_2);

	string targetUuid = targetObject->getUuid();
	for (size_t giIndex = 0; giIndex < gis->GraphicalInformation.size(); ++giIndex) {
		string uuid = getTargetObjectUuid(giIndex);
		if (uuid.compare(targetUuid) == 0 &&
			gis->GraphicalInformation[giIndex]->soap_type() == SOAP_TYPE_gsoap_eml2_2_resqml2__ColorInformation) {
			return static_cast<resqml2__ColorInformation*>(gis->GraphicalInformation[giIndex]);
		}
	}

	return nullptr;
}

bool GraphicalInformationSet::hasGraphicalInformation(const AbstractObject* targetObject) const
{
	_eml22__GraphicalInformationSet* gis = static_cast<_eml22__GraphicalInformationSet*>(gsoapProxy2_2);

	string targetUuid = targetObject->getUuid();
	for (size_t giIndex = 0; giIndex < gis->GraphicalInformation.size(); ++giIndex) {
		string uuid = getTargetObjectUuid(giIndex);
		if (uuid.compare(targetUuid) == 0) {
			return true;
		}
	}

	return nullptr;
}

bool GraphicalInformationSet::hasDefaultColor(AbstractObject* targetObject) const
{
	return getDefaultColor(targetObject) != nullptr;
}

double GraphicalInformationSet::getDefaultHue(AbstractObject* targetObject) const
{
	resqml2__HsvColor* color = getDefaultColor(targetObject);
	if (color == nullptr) {
		throw invalid_argument("This object has no default color");
	}

	return color->Hue;
}

double GraphicalInformationSet::getDefaultSaturation(AbstractObject* targetObject) const
{
	resqml2__HsvColor* color = getDefaultColor(targetObject);
	if (color == nullptr) {
		throw invalid_argument("This object has no default color");
	}

	return color->Saturation;
}

double GraphicalInformationSet::getDefaultValue(AbstractObject* targetObject) const
{
	resqml2__HsvColor* color = getDefaultColor(targetObject);
	if (color == nullptr) {
		throw invalid_argument("This object has no default color");
	}

	return color->Value;
}

double GraphicalInformationSet::getDefaultAlpha(AbstractObject* targetObject) const
{
	resqml2__HsvColor* color = getDefaultColor(targetObject);
	if (color == nullptr) {
		throw invalid_argument("This object has no default color");
	}

	return color->Alpha;
}

void GraphicalInformationSet::getDefaultRgbColor(AbstractObject* targetObject, double & red, double & green, double & blue) const
{
	hsvToRgb(getDefaultHue(targetObject), getDefaultSaturation(targetObject), getDefaultValue(targetObject), red, green, blue);
}

void GraphicalInformationSet::getDefaultRgbColor(AbstractObject* targetObject, unsigned int & red, unsigned int & green, unsigned int & blue) const
{
	hsvToRgb(getDefaultHue(targetObject), getDefaultSaturation(targetObject), getDefaultValue(targetObject), red, green, blue);
}

bool GraphicalInformationSet::hasDefaultColorTitle(AbstractObject* targetObject) const
{
	resqml2__HsvColor* color = getDefaultColor(targetObject);
	if (color == nullptr) {
		throw invalid_argument("This object has no default color");
	}

	return color->Title != nullptr;
}

std::string GraphicalInformationSet::getDefaultColorTitle(AbstractObject* targetObject) const
{
	resqml2__HsvColor* color = getDefaultColor(targetObject);
	if (color == nullptr) {
		throw invalid_argument("This object has no default color");
	}

	if (!hasDefaultColorTitle(targetObject)) {
		throw invalid_argument("This default color has no title");
	}

	return *color->Title;
}

void GraphicalInformationSet::setDefaultHsvColor(AbstractObject* targetObject, double hue, double saturation, double value, double alpha, string colorTitle)
{
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

	if ((dynamic_cast<AbstractFeature*>(targetObject) == nullptr) &&
		(dynamic_cast<AbstractFeatureInterpretation*>(targetObject) == nullptr) &&
		(dynamic_cast<AbstractRepresentation*>(targetObject) == nullptr) &&
		(dynamic_cast<WellboreMarker*>(targetObject) == nullptr)) {
		throw invalid_argument("The object must be a feature, interpretation, representation or wellbore marker.");
	}

	resqml2__HsvColor* color = nullptr;
	resqml2__DefaultGraphicalInformation* defaultGraphicalInformationForAllIndexableElements = getDefaultGraphicalInformationForAllIndexableElements(targetObject);
	if (defaultGraphicalInformationForAllIndexableElements == nullptr) {
		_eml22__GraphicalInformationSet* gis = static_cast<_eml22__GraphicalInformationSet*>(gsoapProxy2_2);
		defaultGraphicalInformationForAllIndexableElements = soap_new_resqml2__DefaultGraphicalInformation(gsoapProxy2_2->soap, 1);
		defaultGraphicalInformationForAllIndexableElements->TargetObject = targetObject->newEml22Reference();
		defaultGraphicalInformationForAllIndexableElements->ViewerKind = soap_resqml2__ViewerKind2s(gsoapProxy2_2->soap, resqml2__ViewerKind__3d);
		gis->GraphicalInformation.push_back(defaultGraphicalInformationForAllIndexableElements);
		resqml2__GraphicalInformationForWholeObject* giwo = soap_new_resqml2__GraphicalInformationForWholeObject(gsoapProxy2_2->soap, 1);
		giwo->IsVisible = true;
		defaultGraphicalInformationForAllIndexableElements->IndexableElementInfo.push_back(giwo);
		color = soap_new_resqml2__HsvColor(gsoapProxy2_2->soap, 1);
		giwo->ConstantColor = color;
	}
	else {
		resqml2__GraphicalInformationForWholeObject* giwo = getDefaultGraphicalInformation(targetObject);
		if (giwo == nullptr) {
			giwo = soap_new_resqml2__GraphicalInformationForWholeObject(gsoapProxy2_2->soap, 1);
			giwo->IsVisible = true;
			defaultGraphicalInformationForAllIndexableElements->IndexableElementInfo.push_back(giwo);
			color = soap_new_resqml2__HsvColor(gsoapProxy2_2->soap, 1);
			giwo->ConstantColor = color;
			return;
		}
		else {
			color = giwo->ConstantColor;
			if (color == nullptr) {
				color = soap_new_resqml2__HsvColor(gsoapProxy2_2->soap, 1);
				giwo->ConstantColor = color;
			}
		}
	}
	
	color->Hue = hue;
	color->Saturation = saturation;
	color->Value = value;
	color->Alpha = alpha;

	if (colorTitle != "") {
		color->Title = gsoap_eml2_2::soap_new_std__string(gsoapProxy2_2->soap, 1);
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
void GraphicalInformationSet::setDefaultRgbColor(AbstractObject* targetObject, double red, double green, double blue, double alpha, std::string colorTitle)
{
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
void GraphicalInformationSet::setDefaultRgbColor(AbstractObject* targetObject, unsigned int red, unsigned int green, unsigned int blue, double alpha, std::string colorTitle)
{
	if (red < 0 || red > 255) {
		throw invalid_argument("red must be in range [0, 255]");
	}

	if (green < 0 || green > 255) {
		throw invalid_argument("green must be in range [0, 255]");
	}

	if (blue < 0 || blue > 255) {
		throw invalid_argument("blue must be in range [0, 255]");
	}

	double hue, saturation, value;
	rgbToHsv(red, green, blue, hue, saturation, value);
	setDefaultHsvColor(targetObject, hue, saturation, value, alpha, colorTitle);
}

bool GraphicalInformationSet::hasDiscreteColorMap(AbstractObject* targetObject) const
{
	resqml2__ColorInformation const * const colorInformation = getColorInformation(targetObject);
	return colorInformation != nullptr && colorInformation->DiscreteColorMap != nullptr;
}

gsoap_eml2_2::eml22__DataObjectReference* GraphicalInformationSet::getDiscreteColorMapDor(AbstractObject* targetObject) const
{
	resqml2__ColorInformation const * const colorInformation = getColorInformation(targetObject);

	if (colorInformation == nullptr || colorInformation->DiscreteColorMap == nullptr) {
		throw invalid_argument("This object has no discrete color map");
	}

	return colorInformation->DiscreteColorMap;
}

std::string GraphicalInformationSet::getDiscreteColorMapUuid(AbstractObject* targetObject) const
{
	return getDiscreteColorMapDor(targetObject)->Uuid;
}

DiscreteColorMap* GraphicalInformationSet::getDiscreteColorMap(AbstractObject* targetObject) const
{
	return epcDocument->getDataObjectByUuid<DiscreteColorMap>(getDiscreteColorMapUuid(targetObject));
}

// TODO do not test that ContinuousColorMap exists, make the assumption that
// a same ColorInformation can connect to both DiscreteColorMap and ContinuousColorMap
// TODO can I reset a relation to a DiscreteColorMap?
void GraphicalInformationSet::setDiscreteColorMap(AbstractObject* targetObject, DiscreteColorMap* discreteColorMap, 
	const LONG64& valueVectorIndex, bool useReverseMapping, bool useLogarithmicMapping)
{
	if (discreteColorMap == nullptr) {
		throw invalid_argument("The discrete color map cannot be null");
	}

	_eml22__GraphicalInformationSet* gis = static_cast<_eml22__GraphicalInformationSet*>(gsoapProxy2_2);

	resqml2__ColorInformation* colorInformation = getColorInformation(targetObject);
	if (colorInformation == nullptr) {
		colorInformation = soap_new_resqml2__ColorInformation(gsoapProxy2_2->soap, 1);
		colorInformation->TargetObject = targetObject->newEml22Reference();
		gis->GraphicalInformation.push_back(colorInformation);
	}

	LONG64 min, max;
	discreteColorMap->computeMinMax(min, max);
	if (colorInformation->MinMax == nullptr) {
		colorInformation->MinMax = soap_new_resqml2__MinMax(gsoapProxy2_2->soap, 1);
	}
	colorInformation->MinMax->Minimum = min;
	colorInformation->MinMax->Maximum = max;

	colorInformation->UseReverseMapping = useReverseMapping;
	colorInformation->UseLogarithmicMapping = useLogarithmicMapping;
	colorInformation->ValueVectorIndex = valueVectorIndex;

	discreteColorMap->graphicalInformationSetSet.push_back(this);
	colorInformation->DiscreteColorMap = discreteColorMap->newEml22Reference();
}

bool GraphicalInformationSet::hasContinuousColorMap(AbstractObject* targetObject) const
{
	resqml2__ColorInformation const * const colorInformation = getColorInformation(targetObject);
	return colorInformation != nullptr && colorInformation->ContinuousColorMap != nullptr;
}

gsoap_eml2_2::eml22__DataObjectReference* GraphicalInformationSet::getContinuousColorMapDor(AbstractObject* targetObject) const
{
	resqml2__ColorInformation const* const colorInformation = getColorInformation(targetObject);

	if (colorInformation == nullptr || colorInformation->ContinuousColorMap == nullptr) {
		throw invalid_argument("This object has no continuous color map");
	}

	return colorInformation->ContinuousColorMap;
}

std::string GraphicalInformationSet::getContinuousColorMapUuid(AbstractObject* targetObject) const
{
	return getContinuousColorMapDor(targetObject)->Uuid;
}

ContinuousColorMap* GraphicalInformationSet::getContinuousColorMap(AbstractObject* targetObject) const
{
	return epcDocument->getDataObjectByUuid<ContinuousColorMap>(getContinuousColorMapUuid(targetObject));
}

// TODO do not test that ContinuousColorMap exists, make the assumption that
// a same ColorInformation can connect to both DiscreteColorMap and ContinuousColorMap
// TODO can I reset a relation to a DiscreteColorMap?
void GraphicalInformationSet::setContinuousColorMap(AbstractObject* targetObject, ContinuousColorMap* continuousColorMap, 
	const LONG64& valueVectorIndex, bool useReverseMapping, bool useLogarithmicMapping)
{
	if (continuousColorMap == nullptr) {
		throw invalid_argument("The continuous color map cannot be null");
	}

	_eml22__GraphicalInformationSet* gis = static_cast<_eml22__GraphicalInformationSet*>(gsoapProxy2_2);

	resqml2__ColorInformation* colorInformation = getColorInformation(targetObject);
	if (colorInformation == nullptr) {
		colorInformation = soap_new_resqml2__ColorInformation(gsoapProxy2_2->soap, 1);
		colorInformation->TargetObject = targetObject->newEml22Reference();
		gis->GraphicalInformation.push_back(colorInformation);
	}

	LONG64 min, max;
	continuousColorMap->computeMinMax(min, max);
	if (colorInformation->MinMax == nullptr) {
		colorInformation->MinMax = soap_new_resqml2__MinMax(gsoapProxy2_2->soap, 1);
	}
	colorInformation->MinMax->Minimum = min;
	colorInformation->MinMax->Maximum = max;

	colorInformation->UseReverseMapping = useReverseMapping;
	colorInformation->UseLogarithmicMapping = useLogarithmicMapping;
	colorInformation->ValueVectorIndex = valueVectorIndex;

	continuousColorMap->graphicalInformationSetSet.push_back(this);
	colorInformation->ContinuousColorMap = continuousColorMap->newEml22Reference();
}

double GraphicalInformationSet::getColorMapMinIndex(AbstractObject* targetObject) const
{
	resqml2__ColorInformation* colorInformation = getColorInformation(targetObject);

	if (colorInformation == nullptr) {
		throw invalid_argument("This object has no color information");
	}

	if (colorInformation->MinMax == nullptr) {
		throw invalid_argument("No min index is defined");
	}

	return colorInformation->MinMax->Minimum;
}

double GraphicalInformationSet::getColorMapMaxIndex(AbstractObject* targetObject) const
{
	resqml2__ColorInformation* colorInformation = getColorInformation(targetObject);

	if (colorInformation == nullptr)
	{
		throw invalid_argument("This object has no color information");
	}

	if (colorInformation->MinMax == nullptr)
	{
		throw invalid_argument("No max index is defined");
	}

	return colorInformation->MinMax->Maximum;
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
	double x = c * (1. - abs(fmod(hprim,2) - 1.));
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


