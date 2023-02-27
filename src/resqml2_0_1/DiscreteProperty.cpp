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
#include "DiscreteProperty.h"

#include <sstream>

#include "../tools/Statistics.h"

#include "../common/EnumStringMapper.h"

#include "../eml2/AbstractHdfProxy.h"

#include "../resqml2/AbstractRepresentation.h"

#include "PropertyKind.h"
#include "PropertyKindMapper.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

DiscreteProperty::DiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	gsoap_eml2_3::eml23__IndexableElement attachmentKind, resqml20__ResqmlPropertyKind energisticsPropertyKind,
	std::vector<int> dimensions)
{
	if (rep == nullptr) {
		throw invalid_argument("The representation of this property values cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREDiscreteProperty(rep->getGsoapContext());	
	_resqml20__DiscreteProperty* prop = static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = mapIndexableElement(attachmentKind);
	LONG64 valueCountPerIndexableElement = 1;
	for (auto dim : dimensions) {
		valueCountPerIndexableElement *= dim;
	}
	prop->Count = valueCountPerIndexableElement;

	resqml20__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml20__StandardPropertyKind(gsoapProxy2_0_1->soap);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	rep->getRepository()->addDataObject(this);
	setRepresentation(rep);
}

DiscreteProperty::DiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	gsoap_eml2_3::eml23__IndexableElement attachmentKind, EML2_NS::PropertyKind * localPropKind,
	std::vector<int> dimensions)
{
	if (rep == nullptr) {
		throw invalid_argument("The representation of this property values cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREDiscreteProperty(rep->getGsoapContext());	
	_resqml20__DiscreteProperty* prop = static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = mapIndexableElement(attachmentKind);
	LONG64 valueCountPerIndexableElement = 1;
	for (auto dim : dimensions) {
		valueCountPerIndexableElement *= dim;
	}
	prop->Count = valueCountPerIndexableElement;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	rep->getRepository()->addDataObject(this);
	setRepresentation(rep);

	setPropertyKind(localPropKind);
}

bool DiscreteProperty::validatePropertyKindAssociation(EML2_NS::PropertyKind* pk)
{
	if (pk == nullptr) {
		throw invalid_argument("The property kind to validate cannot be null.");
	}

	if (!pk->isPartial()) {
		if (pk->isAbstract()) {
			repository->addWarning("The discrete property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (repository->getPropertyKindMapper() != nullptr) {
			if (pk->isParentPartial()) {
				repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the discrete property " + getUuid() + " is right because one if its parent property kind is abstract.");
				return true;
			}
			auto pk201 = dynamic_cast<RESQML2_0_1_NS::PropertyKind*>(pk);
			if (pk201 != nullptr) {
				if (!pk201->isChildOf(resqml20__ResqmlPropertyKind::discrete) &&
					!pk201->isChildOf(resqml20__ResqmlPropertyKind::categorical)) {
					repository->addWarning("The discrete property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which does not derive from the discrete or categorical standard property kind. This property will be assumed to be a partial one.");
					changeToPartialObject();
					return false;
				}
			}
		}
		else {
			repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the discrete property " + getUuid() + " is right because no property kind mapping files have been loaded.");
		}
	}
	else {
		repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the discrete property " + getUuid() + " is right because it is abstract.");
	}

	return true;
}

bool DiscreteProperty::validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind pk)
{
	COMMON_NS::EnumStringMapper tmp;
	std::string pkName = tmp.getEnergisticsPropertyKindName(pk);

	PropertyKindMapper* pkMapper = repository->getPropertyKindMapper();
	if (pkMapper != nullptr) {
		if (pkMapper->isAbstract(pk)) {
			repository->addWarning("The discrete property " + getUuid() + " cannot be associated to a resqml property kind \"" + pkName + "\" which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (!pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind::discrete) &&
			!pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind::categorical)) {
			repository->addWarning("The discrete property " + getUuid() + " cannot be associated to a resqml property kind \"" + pkName + "\" which does not derive from the discrete or categorical standard property kind. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
	}
	else {
		repository->addWarning("Cannot verify if the resqml property kind \"" + pkName + "\" of the discrete property " + getUuid() + " is right because no property kind mapping files have been loaded.");
	}

	return true;
}

bool DiscreteProperty::hasMinimumValue(uint64_t index) const
{
	return static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1)->MinimumValue.size() > index;
}

int64_t DiscreteProperty::getMinimumValue(uint64_t index) const
{
	if (!hasMinimumValue(index)) {
		throw std::logic_error("This property has not minimum value at index " + std::to_string(index) );
	}

	return static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1)->MinimumValue[index];
}

bool DiscreteProperty::hasMaximumValue(uint64_t index) const
{
	return static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1)->MaximumValue.size() > index;
}

int64_t DiscreteProperty::getMaximumValue(uint64_t index) const
{
	if (!hasMaximumValue(index)) {
		throw std::logic_error("This property has not maximum value at index " + std::to_string(index));
	}

	return static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1)->MaximumValue[index];
}

void DiscreteProperty::setMinimumValue(int64_t value, uint64_t index) const
{
	_resqml20__DiscreteProperty* prop = static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1);

	while (prop->MinimumValue.size() <= index) {
		prop->MinimumValue.push_back((std::numeric_limits<int64_t>::max)());
	}

	prop->MinimumValue[index] = value;
}

void DiscreteProperty::setMaximumValue(int64_t value, uint64_t index) const
{
	_resqml20__DiscreteProperty* prop = static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1);

	while (prop->MaximumValue.size() <= index) {
		prop->MaximumValue.push_back((std::numeric_limits<int64_t>::min)());
	}

	prop->MaximumValue[index] = value;
}

gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind DiscreteProperty::getEnergisticsPropertyKind() const
{
	return getEnergisticsPropertyKind201();
}
