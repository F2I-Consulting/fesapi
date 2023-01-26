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
#include "CategoricalProperty.h"

#include "../common/EnumStringMapper.h"

#include "../eml2/ColumnBasedTable.h"

#include "../resqml2/AbstractRepresentation.h"

#include "PropertyKind.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

CategoricalProperty::CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	gsoap_eml2_3::eml23__IndexableElement attachmentKind,
	EML2_NS::ColumnBasedTable* strLookup, resqml20__ResqmlPropertyKind energisticsPropertyKind,
	std::vector<int> dimensions)
{
	if (rep == nullptr) {
		throw invalid_argument("The representation of this property values cannot be null.");
	}
	if (strLookup == nullptr) {
		throw invalid_argument("The string lookup table cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORECategoricalProperty(rep->getGsoapContext());	
	_resqml20__CategoricalProperty* prop = static_cast<_resqml20__CategoricalProperty*>(gsoapProxy2_0_1);
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

	prop->Lookup = strLookup->newResqmlReference();
	getRepository()->addRelationship(this, strLookup);
}

CategoricalProperty::CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	gsoap_eml2_3::eml23__IndexableElement attachmentKind,
	EML2_NS::ColumnBasedTable* strLookup, EML2_NS::PropertyKind * localPropKind,
	std::vector<int> dimensions)
{
	if (rep == nullptr) {
		throw invalid_argument("The representation of this property values cannot be null.");
	}
	if (strLookup == nullptr) {
		throw invalid_argument("The string lookup table cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORECategoricalProperty(rep->getGsoapContext());	
	_resqml20__CategoricalProperty* prop = static_cast<_resqml20__CategoricalProperty*>(gsoapProxy2_0_1);
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

	prop->Lookup = strLookup->newResqmlReference();
	getRepository()->addRelationship(this, strLookup);
}

COMMON_NS::DataObjectReference CategoricalProperty::getLookupDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<_resqml20__CategoricalProperty*>(gsoapProxy2_0_1)->Lookup);
}

bool CategoricalProperty::validatePropertyKindAssociation(EML2_NS::PropertyKind* pk)
{
	if (pk == nullptr) {
		throw invalid_argument("The property kind to validate cannot be null.");
	}

	if (!pk->isPartial()) {
		if (pk->isAbstract()) {
			repository->addWarning("The categorical property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (repository->getPropertyKindMapper() != nullptr) {
			if (pk->isParentPartial()) {
				repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the categorical property " + getUuid() + " is right because one if its parent property kind is abstract.");
				return true;
			}
			auto pk201 = dynamic_cast<RESQML2_0_1_NS::PropertyKind*>(pk);
			if (pk201 != nullptr) {
				if (!pk201->isChildOf(resqml20__ResqmlPropertyKind::categorical) &&
					!pk201->isChildOf(resqml20__ResqmlPropertyKind::discrete)) {
					repository->addWarning("The categorical property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which does not derive from the discrete or categorical standard property kind. This property will be assumed to be a partial one.");
					changeToPartialObject();
					return false;
				}
			}
		}
		else {
			repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the categorical property " + getUuid() + " is right because no property kind mapping files have been loaded.");
		}
	}
	else {
		repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the categorical property " + getUuid() + " is right because it is abstract.");
	}

	return true;
}

bool CategoricalProperty::validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind pk)
{
	COMMON_NS::EnumStringMapper tmp;
	std::string pkName = tmp.getEnergisticsPropertyKindName(pk);

	PropertyKindMapper* pkMapper = repository->getPropertyKindMapper();
	if (pkMapper != nullptr) {
		if (pkMapper->isAbstract(pk)) {
			repository->addWarning("The categorical property " + getUuid() + " cannot be associated to a resqml property kind \"" + pkName + "\" which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (!pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind::categorical) &&
			!pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind::discrete)) {
			repository->addWarning("The categorical property " + getUuid() + " cannot be associated to a resqml property kind \"" + pkName + "\" which does not derive from the discrete or categorical standard property kind. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
}
	else {
		repository->addWarning("Cannot verify if the resqml property kind \"" + pkName + "\" of the categorical property " + getUuid() + " is right because no property kind mapping files have been loaded.");
	}

	return true;
}

gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind CategoricalProperty::getEnergisticsPropertyKind() const
{
	return getEnergisticsPropertyKind201();
}
