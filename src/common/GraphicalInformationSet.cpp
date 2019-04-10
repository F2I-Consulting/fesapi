/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#include "common/GraphicalInformationSet.h"

#include "tools/Misc.h"

#include <stdexcept>

using namespace std;
using namespace common;
using namespace gsoap_eml2_2;
using namespace epc;

const char* GraphicalInformationSet::XML_TAG = "GraphicalInformationSet";

GraphicalInformationSet::GraphicalInformationSet(soap* soapContext, const string & guid, const string & title)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_2 = gsoap_eml2_2::soap_new_eml22__GraphicalInformationSet(soapContext, 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");
}

gsoap_eml2_2::eml22__DataObjectReference* GraphicalInformationSet::getTargetObjectDor(const unsigned int & index) const
{
	_eml22__GraphicalInformationSet* gis = static_cast<_eml22__GraphicalInformationSet*>(gsoapProxy2_2);

	if (index >= gis->GraphicalInformation.size()) {
		throw range_error("The index if out of range in GraphicalInformationSet");
	}

	return gis->GraphicalInformation[index]->TargetObject;
}

std::string GraphicalInformationSet::getTargetObjectUuid(const unsigned int & index) const
{
	return getTargetObjectDor(index)->Uuid;
}

common::AbstractObject* GraphicalInformationSet::getTargetObject(const unsigned int & index) const
{
	return epcDocument->getDataObjectByUuid(getTargetObjectUuid(index));
}

vector<Relationship> GraphicalInformationSet::getAllEpcRelationships() const
{
	vector<Relationship> result;

	_eml22__GraphicalInformationSet* gis = static_cast<_eml22__GraphicalInformationSet*>(gsoapProxy2_2);

	for (size_t giIndex = 0; giIndex < gis->GraphicalInformation.size(); ++giIndex) {
		gsoap_eml2_2::eml22__DataObjectReference* dor = getTargetObjectDor(giIndex);
		Relationship relFop(misc::getPartNameFromReference(dor), "", dor->Uuid);
		relFop.setDestinationObjectType();
		result.push_back(relFop);
	}

	return result;
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
		std::string uuid = getTargetObjectUuid(giIndex);
		if (uuid.compare(targetUuid) == 0) {
			return true;
		}
	}

	return nullptr;
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

void GraphicalInformationSet::setDefaultHsvColor(common::AbstractObject* targetObject, const double & hue, const double & saturation, const double & value, const double & alpha)
{
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
