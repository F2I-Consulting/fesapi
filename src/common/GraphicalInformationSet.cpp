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

#include <stdexcept>

using namespace std;
using namespace common;
using namespace gsoap_eml2_2;
using namespace resqml2;
using namespace resqml2_0_1;

const char* GraphicalInformationSet::XML_TAG = "GraphicalInformationSet";

GraphicalInformationSet::GraphicalInformationSet(COMMON_NS::DataObjectRepository* repo, const string & guid, const string & title)
{
	if (repo == nullptr)
		throw invalid_argument("The repo cannot be null.");

	gsoapProxy2_2 = gsoap_eml2_2::soap_new_eml22__GraphicalInformationSet(repo->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(this);
}

unsigned int GraphicalInformationSet::getGraphicalInformationSetCount() const
{
	_eml22__GraphicalInformationSet* gis = static_cast<_eml22__GraphicalInformationSet*>(gsoapProxy2_2);

	size_t count = gis->GraphicalInformation.size();
	
	if (count > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("The graphical information set count is out of range.");
	}

	return static_cast<unsigned int>(count);
}

gsoap_eml2_2::eml22__DataObjectReference* GraphicalInformationSet::getTargetObjectDor(unsigned int index) const
{
	_eml22__GraphicalInformationSet* gis = static_cast<_eml22__GraphicalInformationSet*>(gsoapProxy2_2);

	if (index >= gis->GraphicalInformation.size()) {
		throw range_error("The index if out of range in GraphicalInformationSet");
	}

	return gis->GraphicalInformation[index]->TargetObject;
}

std::string GraphicalInformationSet::getTargetObjectUuid(unsigned int index) const
{
	return getTargetObjectDor(index)->Uuid;
}

common::AbstractObject* GraphicalInformationSet::getTargetObject(unsigned int index) const
{
	return getRepository()->getDataObjectByUuid(getTargetObjectUuid(index));
}

gsoap_eml2_2::resqml2__DefaultGraphicalInformation* GraphicalInformationSet::getDefaultGraphicalInformationForAllIndexableElements(common::AbstractObject* targetObject) const
{
	_eml22__GraphicalInformationSet* gis = static_cast<_eml22__GraphicalInformationSet*>(gsoapProxy2_2);

	std::string targetUuid = targetObject->getUuid();
	for (size_t giIndex = 0; giIndex < gis->GraphicalInformation.size(); ++giIndex) {
		std::string uuid = getTargetObjectUuid(giIndex);
		if (uuid.compare(targetUuid) == 0 &&
			gis->GraphicalInformation[giIndex]->soap_type() == SOAP_TYPE_gsoap_eml2_2_resqml2__DefaultGraphicalInformation) {
			return static_cast<resqml2__DefaultGraphicalInformation*>(gis->GraphicalInformation[giIndex]);
		}
	}

	return nullptr;
}

gsoap_eml2_2::resqml2__GraphicalInformationForWholeObject* GraphicalInformationSet::getDefaultGraphicalInformation(common::AbstractObject* targetObject) const
{
	gsoap_eml2_2::resqml2__DefaultGraphicalInformation* defaultGraphicalInformationForAllIndexableElements = getDefaultGraphicalInformationForAllIndexableElements(targetObject);

	if (defaultGraphicalInformationForAllIndexableElements != nullptr) {
		for (size_t indexableElementIndex = 0; indexableElementIndex < defaultGraphicalInformationForAllIndexableElements->IndexableElementInfo.size(); ++indexableElementIndex) {
			if (defaultGraphicalInformationForAllIndexableElements->IndexableElementInfo[indexableElementIndex]->soap_type() == SOAP_TYPE_gsoap_eml2_2_resqml2__GraphicalInformationForWholeObject) {
				return static_cast<resqml2__GraphicalInformationForWholeObject*>(defaultGraphicalInformationForAllIndexableElements->IndexableElementInfo[indexableElementIndex]);
			}
		}
	}

	return nullptr;
}

gsoap_eml2_2::resqml2__HsvColor* GraphicalInformationSet::getDefaultColor(common::AbstractObject* targetObject) const
{
	gsoap_eml2_2::resqml2__GraphicalInformationForWholeObject* result = getDefaultGraphicalInformation(targetObject);
	return result != nullptr && result->ConstantColor != nullptr ? result->ConstantColor : nullptr;
}

bool GraphicalInformationSet::hasGraphicalInformation(const common::AbstractObject* targetObject) const
{
	_eml22__GraphicalInformationSet* gis = static_cast<_eml22__GraphicalInformationSet*>(gsoapProxy2_2);

	std::string targetUuid = targetObject->getUuid();
	for (size_t giIndex = 0; giIndex < gis->GraphicalInformation.size(); ++giIndex) {
		if (getTargetObjectUuid(giIndex).compare(targetUuid) == 0) {
			return true;
		}
	}

	return false;
}

bool GraphicalInformationSet::hasDefaultColor(common::AbstractObject* targetObject) const
{
	return getDefaultColor(targetObject) != nullptr;
}

double GraphicalInformationSet::getDefaultHue(common::AbstractObject* targetObject) const
{
	gsoap_eml2_2::resqml2__HsvColor* color = getDefaultColor(targetObject);
	if (color == nullptr) {
		throw std::invalid_argument("This object has no color information");
	}

	return color->Hue;
}

double GraphicalInformationSet::getDefaultSaturation(common::AbstractObject* targetObject) const
{
	gsoap_eml2_2::resqml2__HsvColor* color = getDefaultColor(targetObject);
	if (color == nullptr) {
		throw std::invalid_argument("This object has no color information");
	}

	return color->Saturation;
}

double GraphicalInformationSet::getDefaultValue(common::AbstractObject* targetObject) const
{
	gsoap_eml2_2::resqml2__HsvColor* color = getDefaultColor(targetObject);
	if (color == nullptr) {
		throw std::invalid_argument("This object has no color information");
	}

	return color->Value;
}

double GraphicalInformationSet::getDefaultAlpha(common::AbstractObject* targetObject) const
{
	gsoap_eml2_2::resqml2__HsvColor* color = getDefaultColor(targetObject);
	if (color == nullptr) {
		throw std::invalid_argument("This object has no color information");
	}

	return color->Alpha;
}

void GraphicalInformationSet::setDefaultHsvColor(common::AbstractObject* targetObject, double hue, double saturation, double value, double alpha)
{
	if (hue < 0 || hue > 360) {
		throw std::invalid_argument("hue must be in range [0, 360]");
	}

	if (saturation < 0 || saturation > 1) {
		throw std::invalid_argument("saturation must be in range [0, 1]");
	}

	if (value < 0 || value > 1) {
		throw std::invalid_argument("value must be in range [0, 1]");
	}

	if (alpha < 0 || alpha > 1) {
		throw std::invalid_argument("alpha must be in range [0, 1]");
	}

	if ((dynamic_cast<AbstractFeature*>(targetObject) == nullptr) &&
		(dynamic_cast<AbstractFeatureInterpretation*>(targetObject) == nullptr) &&
		(dynamic_cast<AbstractRepresentation*>(targetObject) == nullptr) &&
		(dynamic_cast<WellboreMarker*>(targetObject) == nullptr)) {
		throw std::invalid_argument("The object must be a feature, interpretation, representation or wellbore marker.");
	}

	gsoap_eml2_2::resqml2__HsvColor* color = nullptr;
	resqml2__DefaultGraphicalInformation* defaultGraphicalInformationForAllIndexableElements = getDefaultGraphicalInformationForAllIndexableElements(targetObject);
	if (defaultGraphicalInformationForAllIndexableElements == nullptr) {
		_eml22__GraphicalInformationSet* gis = static_cast<_eml22__GraphicalInformationSet*>(gsoapProxy2_2);
		defaultGraphicalInformationForAllIndexableElements = gsoap_eml2_2::soap_new_resqml2__DefaultGraphicalInformation(gsoapProxy2_2->soap, 1);
		defaultGraphicalInformationForAllIndexableElements->TargetObject = targetObject->newEml22Reference();
		defaultGraphicalInformationForAllIndexableElements->ViewerKind = gsoap_eml2_2::soap_resqml2__ViewerKind2s(gsoapProxy2_2->soap, resqml2__ViewerKind__3d);
		gis->GraphicalInformation.push_back(defaultGraphicalInformationForAllIndexableElements);
		gsoap_eml2_2::resqml2__GraphicalInformationForWholeObject* giwo = gsoap_eml2_2::soap_new_resqml2__GraphicalInformationForWholeObject(gsoapProxy2_2->soap, 1);
		giwo->IsVisible = true;
		defaultGraphicalInformationForAllIndexableElements->IndexableElementInfo.push_back(giwo);
		color = gsoap_eml2_2::soap_new_resqml2__HsvColor(gsoapProxy2_2->soap, 1);
		giwo->ConstantColor = color;
	}
	else {
		gsoap_eml2_2::resqml2__GraphicalInformationForWholeObject* giwo = getDefaultGraphicalInformation(targetObject);
		if (giwo == nullptr) {
			giwo = gsoap_eml2_2::soap_new_resqml2__GraphicalInformationForWholeObject(gsoapProxy2_2->soap, 1);
			giwo->IsVisible = true;
			defaultGraphicalInformationForAllIndexableElements->IndexableElementInfo.push_back(giwo);
			color = gsoap_eml2_2::soap_new_resqml2__HsvColor(gsoapProxy2_2->soap, 1);
			giwo->ConstantColor = color;
			return;
		}
		else {
			color = giwo->ConstantColor;
			if (color == nullptr) {
				color = gsoap_eml2_2::soap_new_resqml2__HsvColor(gsoapProxy2_2->soap, 1);
				giwo->ConstantColor = color;
			}
		}
	}
	
	color->Hue = hue;
	color->Saturation = saturation;
	color->Value = value;
	color->Alpha = alpha;
}

void GraphicalInformationSet::loadTargetRelationships() const
{
	const unsigned int count = getGraphicalInformationSetCount();
	for (unsigned int index = 0; index < count; ++index) {
		convertDorIntoRel(getTargetObjectDor(index));
	}
}
