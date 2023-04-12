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
#include "ContinuousProperty.h"

#include <limits>

#include "../common/EnumStringMapper.h"

#include "../eml2/AbstractHdfProxy.h"

#include "../resqml2/AbstractRepresentation.h"

#include "PropertyKind.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* ContinuousProperty::XML_NS = "resqml20";

void ContinuousProperty::init(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	unsigned int dimension, gsoap_eml2_3::eml23__IndexableElement attachmentKind)
{
	if (rep == nullptr) {
		throw invalid_argument("The representation of this property values cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREContinuousProperty(rep->getGsoapContext());
	_resqml20__ContinuousProperty* prop = static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = mapIndexableElement(attachmentKind);
	prop->Count = dimension;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	rep->getRepository()->addDataObject(this);
	setRepresentation(rep);
}

ContinuousProperty::ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_3::eml23__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, resqml20__ResqmlPropertyKind energisticsPropertyKind)
{
	init(rep, guid, title, dimension, attachmentKind);

	static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1)->UOM = uom;

	resqml20__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml20__StandardPropertyKind(gsoapProxy2_0_1->soap);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1)->PropertyKind = xmlStandardPropKind;
}

ContinuousProperty::ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_3::eml23__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, EML2_NS::PropertyKind * localPropKind)
{
	init(rep, guid, title, dimension, attachmentKind);

	static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1)->UOM = uom;

	setPropertyKind(localPropKind);
}

ContinuousProperty::ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_3::eml23__IndexableElement attachmentKind, const std::string & nonStandardUom, resqml20__ResqmlPropertyKind energisticsPropertyKind)
{
	init(rep, guid, title, dimension, attachmentKind);

	static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1)->UOM = gsoap_resqml2_0_1::resqml20__ResqmlUom::Euc;
	pushBackExtraMetadata("Uom", nonStandardUom);

	resqml20__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml20__StandardPropertyKind(gsoapProxy2_0_1->soap);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1)->PropertyKind = xmlStandardPropKind;
}

ContinuousProperty::ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_3::eml23__IndexableElement attachmentKind, const std::string & nonStandardUom, EML2_NS::PropertyKind * localPropKind)
{
	init(rep, guid, title, dimension, attachmentKind);

	static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1)->UOM = gsoap_resqml2_0_1::resqml20__ResqmlUom::Euc;
	pushBackExtraMetadata("Uom", nonStandardUom);

	setPropertyKind(localPropKind);
}

gsoap_resqml2_0_1::resqml20__ResqmlUom ContinuousProperty::getUom() const
{
	return static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1)->UOM;
}

std::string ContinuousProperty::getUomAsString() const
{
	gsoap_resqml2_0_1::resqml20__ResqmlUom uom = getUom();

	if (uom == gsoap_resqml2_0_1::resqml20__ResqmlUom::Euc) {
		unsigned int emCount = getExtraMetadataCount();
		for (unsigned int i = 0; i < emCount; ++i) {
			if (getExtraMetadataKeyAtIndex(i) == "Uom") {
				return getExtraMetadataStringValueAtIndex(i);
			}
		}
	}

	return gsoap_resqml2_0_1::soap_resqml20__ResqmlUom2s(gsoapProxy2_0_1->soap, uom);
}

EML2_NS::AbstractHdfProxy* ContinuousProperty::getValuesHdfProxyAndDatasetPathOfPatch(unsigned int patchIndex, std::string & datasetPath) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	_resqml20__ContinuousProperty const * prop = static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1);
	eml20__Hdf5Dataset const * dataset = static_cast<resqml20__DoubleHdf5Array*>(prop->PatchOfValues[patchIndex]->Values)->Values;
	datasetPath = dataset->PathInHdfFile;
	return getHdfProxyFromDataset(dataset);
}

double ContinuousProperty::getMinimumValue(unsigned int index) const
{
	_resqml20__ContinuousProperty* prop = static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1);

	return prop->MinimumValue.size() <= index ? std::numeric_limits<double>::quiet_NaN() : prop->MinimumValue[index];
}

double ContinuousProperty::getMaximumValue(unsigned int index) const
{
	_resqml20__ContinuousProperty* prop = static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1);

	return prop->MaximumValue.size() <= index ? std::numeric_limits<double>::quiet_NaN() : prop->MaximumValue[index];
}

void ContinuousProperty::setMinimumValue(double value, unsigned int index) const
{
	_resqml20__ContinuousProperty* prop = static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1);

	while (prop->MinimumValue.size() <= index) {
		prop->MinimumValue.push_back(std::numeric_limits<double>::quiet_NaN());
	}

	prop->MinimumValue[index] = value;
}

void ContinuousProperty::setMaximumValue(double value, unsigned int index) const
{
	_resqml20__ContinuousProperty* prop = static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1);

	while (prop->MaximumValue.size() <= index) {
		prop->MaximumValue.push_back(std::numeric_limits<double>::quiet_NaN());
	}

	prop->MaximumValue[index] = value;
}

size_t ContinuousProperty::getMinimumValueSize() const
{
	return static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1)->MinimumValue.size();
}

size_t ContinuousProperty::getMaximumValueSize() const
{
	return static_cast<_resqml20__ContinuousProperty*>(gsoapProxy2_0_1)->MaximumValue.size();
}

bool ContinuousProperty::validatePropertyKindAssociation(EML2_NS::PropertyKind* pk)
{
	if (pk == nullptr) {
		throw invalid_argument("The property kind to validate cannot be null.");
	}

	if (!pk->isPartial()) {
		if (pk->isAbstract()) {
			repository->addWarning("The continuous property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (repository->getPropertyKindMapper() != nullptr) {
			if (pk->isParentPartial()) {
				repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the continuous property " + getUuid() + " is right because one if its parent property kind is abstract.");
				return true;
			}
			auto pk201 = dynamic_cast<RESQML2_0_1_NS::PropertyKind*>(pk);
			if (pk201 != nullptr) {
				if (!pk201->isChildOf(resqml20__ResqmlPropertyKind::continuous)) {
					repository->addWarning("The continuous property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which does not derive from the continuous standard property kind. This property will be assumed to be a partial one.");
					changeToPartialObject();
					return false;
				}
			}
		}
		else {
			repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the continuous property " + getUuid() + " is right because no property kind mapping files have been loaded.");
		}
	}
	else {
		repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the continuous property " + getUuid() + " is right because it is abstract.");
	}

	return true;
}

bool ContinuousProperty::validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind pk)
{
	COMMON_NS::EnumStringMapper tmp;
	std::string pkName = tmp.getEnergisticsPropertyKindName(pk);

	PropertyKindMapper* pkMapper = repository->getPropertyKindMapper();
	if (pkMapper != nullptr) {
		if (pkMapper->isAbstract(pk)) {
			repository->addWarning("The continuous property " + getUuid() + " cannot be associated to a resqml property kind \"" + pkName + "\" which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (!pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind::continuous)) {
			repository->addWarning("The continuous property " + getUuid() + " cannot be associated to a resqml property kind \"" + pkName + "\" which does not derive from the continuous standard property kind. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
	}
	else {
		repository->addWarning("Cannot verify if the resqml property kind \"" + pkName + "\" of the continuous property " + getUuid() + " is right because no property kind mapping files have been loaded.");
	}

	return true;
}

gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind ContinuousProperty::getEnergisticsPropertyKind() const
{
	return getEnergisticsPropertyKind201();
}
