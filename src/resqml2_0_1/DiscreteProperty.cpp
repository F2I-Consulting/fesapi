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

#include <limits>
#include <sstream>
#include <stdexcept>

#include <hdf5.h>

#include "../tools/Statistics.h"

#include "../common/EnumStringMapper.h"

#include "../eml2/AbstractHdfProxy.h"

#include "../resqml2/AbstractRepresentation.h"

#include "PropertyKind.h"
#include "PropertyKindMapper.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* DiscreteProperty::XML_NS = "resqml20";

DiscreteProperty::DiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, resqml20__ResqmlPropertyKind energisticsPropertyKind)
{
	if (rep == nullptr) {
		throw invalid_argument("The representation of this property values cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREDiscreteProperty(rep->getGsoapContext());	
	_resqml20__DiscreteProperty* prop = static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = mapIndexableElement(attachmentKind);
	prop->Count = dimension;

	resqml20__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml20__StandardPropertyKind(gsoapProxy2_0_1->soap);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setRepresentation(rep);
}

DiscreteProperty::DiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, EML2_NS::PropertyKind * localPropKind)
{
	if (rep == nullptr) {
		throw invalid_argument("The representation of this property values cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREDiscreteProperty(rep->getGsoapContext());	
	_resqml20__DiscreteProperty* prop = static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = mapIndexableElement(attachmentKind);
	prop->Count = dimension;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setRepresentation(rep);

	setPropertyKind(localPropKind);
}

std::string DiscreteProperty::pushBackRefToExistingDataset(EML2_NS::AbstractHdfProxy* proxy, const std::string & datasetName, LONG64 nullValue, LONG64 minimumValue, LONG64 maximumValue)
{
	const string result = AbstractDiscreteOrCategoricalProperty::pushBackRefToExistingDataset(proxy, datasetName, nullValue);

	_resqml20__DiscreteProperty* prop = static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1);

	if (prop->Count == 1)
	{
		if (prop->MinimumValue.empty())
			prop->MinimumValue.push_back(minimumValue);
		else
			prop->MinimumValue[0] = minimumValue;

		if (prop->MaximumValue.empty())
			prop->MaximumValue.push_back(maximumValue);
		else
			prop->MaximumValue[0] = maximumValue;
	}

	return result;
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
				if (!pk201->isChildOf(resqml20__ResqmlPropertyKind__discrete)) {
					if (!pk201->isChildOf(resqml20__ResqmlPropertyKind__categorical)) {
						repository->addWarning("The discrete property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which does not derive from the discrete or categorical standard property kind. This property will be assumed to be a partial one.");
						changeToPartialObject();
						return false;
					}
					else {
						repository->addWarning("The discrete property " + getUuid() + " is associated to a categorical property kind " + pk->getUuid() + ".");
					}
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
		if (!pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind__discrete)) {
			if (!pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind__categorical)) {
				repository->addWarning("The discrete property " + getUuid() + " cannot be associated to a resqml property kind \"" + pkName + "\" which does not derive from the discrete or categorical standard property kind. This property will be assumed to be a partial one.");
				changeToPartialObject();
				return false;
			}
			else {
				getRepository()->addWarning("The discrete property " + getUuid() + " is associated to a categorical property kind.");
			}
		}
	}
	else {
		repository->addWarning("Cannot verify if the resqml property kind \"" + pkName + "\" of the discrete property " + getUuid() + " is right because no property kind mapping files have been loaded.");
	}

	return true;
}

LONG64 DiscreteProperty::getNullValue(unsigned int patchIndex) const
{
	gsoap_resqml2_0_1::_resqml20__DiscreteProperty* prop = static_cast<gsoap_resqml2_0_1::_resqml20__DiscreteProperty*>(gsoapProxy2_0_1);

	auto abstractIntArray = prop->PatchOfValues[patchIndex == (numeric_limits<unsigned int>::max)() ? prop->PatchOfValues.size() - 1 : patchIndex]->Values;
	if (abstractIntArray->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		return (std::numeric_limits<LONG64>::max)();
	}

	return static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(abstractIntArray)->NullValue;
}

bool DiscreteProperty::hasMinimumValue(unsigned int index) const
{
	return static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1)->MinimumValue.size() > index;
}

LONG64 DiscreteProperty::getMinimumValue(unsigned int index) const
{
	if (!hasMinimumValue(index)) {
		throw std::logic_error("This property has not minimum value at index " + std::to_string(index) );
	}

	return static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1)->MinimumValue[index];
}

bool DiscreteProperty::hasMaximumValue(unsigned int index) const
{
	return static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1)->MaximumValue.size() > index;
}

LONG64 DiscreteProperty::getMaximumValue(unsigned int index) const
{
	if (!hasMaximumValue(index)) {
		throw std::logic_error("This property has not maximum value at index " + std::to_string(index));
	}

	return static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1)->MaximumValue[index];
}

void DiscreteProperty::setMinimumValue(LONG64 value, unsigned int index) const
{
	_resqml20__DiscreteProperty* prop = static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1);

	while (prop->MinimumValue.size() <= index) {
		prop->MinimumValue.push_back((std::numeric_limits<LONG64>::max)());
	}

	prop->MinimumValue[index] = value;
}

void DiscreteProperty::setMaximumValue(LONG64 value, unsigned int index) const
{
	_resqml20__DiscreteProperty* prop = static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1);

	while (prop->MaximumValue.size() <= index) {
		prop->MaximumValue.push_back((std::numeric_limits<LONG64>::min)());
	}

	prop->MaximumValue[index] = value;
}

size_t DiscreteProperty::getMinimumValueSize() const
{
	return static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1)->MinimumValue.size();
}

size_t DiscreteProperty::getMaximumValueSize() const
{
	return static_cast<_resqml20__DiscreteProperty*>(gsoapProxy2_0_1)->MaximumValue.size();
}

gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind DiscreteProperty::getEnergisticsPropertyKind() const
{
	return getEnergisticsPropertyKind201();
}
