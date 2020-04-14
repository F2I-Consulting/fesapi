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

#include <stdexcept>
#include <sstream>

#include <hdf5.h>

#include "../common/AbstractHdfProxy.h"
#include "../common/EnumStringMapper.h"

#include "../resqml2/AbstractRepresentation.h"
#include "PropertyKind.h"
#include "StringTableLookup.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* CategoricalProperty::XML_TAG = "CategoricalProperty";

CategoricalProperty::CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind,
	StringTableLookup* strLookup, resqml20__ResqmlPropertyKind energisticsPropertyKind)
{
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORECategoricalProperty(rep->getGsoapContext());	
	_resqml20__CategoricalProperty* prop = static_cast<_resqml20__CategoricalProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	resqml20__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml20__StandardPropertyKind(gsoapProxy2_0_1->soap);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setRepresentation(rep);

	prop->Lookup = strLookup->newResqmlReference();
	getRepository()->addRelationship(this, strLookup);
}

CategoricalProperty::CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind,
	StringTableLookup* strLookup, COMMON_NS::PropertyKind * localPropKind)
{
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORECategoricalProperty(rep->getGsoapContext());	
	_resqml20__CategoricalProperty* prop = static_cast<_resqml20__CategoricalProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setRepresentation(rep);

	setLocalPropertyKind(localPropKind);

	prop->Lookup = strLookup->newResqmlReference();
	getRepository()->addRelationship(this, strLookup);
}

void CategoricalProperty::loadTargetRelationships()
{
	AbstractValuesProperty::loadTargetRelationships();

	convertDorIntoRel<StringTableLookup>(static_cast<_resqml20__CategoricalProperty*>(gsoapProxy2_0_1)->Lookup);
}

std::string CategoricalProperty::getStringLookupUuid() const
{
	return static_cast<_resqml20__CategoricalProperty*>(gsoapProxy2_0_1)->Lookup->UUID;
}

bool CategoricalProperty::validatePropertyKindAssociation(COMMON_NS::PropertyKind* pk)
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
			if (!pk->isChildOf(resqml20__ResqmlPropertyKind__categorical)) {
				if (!pk->isChildOf(resqml20__ResqmlPropertyKind__discrete)) {
					repository->addWarning("The categorical property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which does not derive from the discrete or categorical standard property kind. This property will be assumed to be a partial one.");
					changeToPartialObject();
					return false;
				}
				else {
					repository->addWarning("The categorical property " + getUuid() + " is associated to a discrete local property kind " + pk->getUuid() + ".");
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
		if (!pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind__categorical)) {
			if (!pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind__discrete)) {
				repository->addWarning("The categorical property " + getUuid() + " cannot be associated to a resqml property kind \"" + pkName + "\" which does not derive from the discrete or categorical standard property kind. This property will be assumed to be a partial one.");
				changeToPartialObject();
				return false;
			}
			else {
				getRepository()->addWarning("The categorical property " + getUuid() + " is associated to a discrete resqml property kind \"" + pkName + "\".");
			}
		}
	}
	else {
		repository->addWarning("Cannot verify if the resqml property kind \"" + pkName + "\" of the categorical property " + getUuid() + " is right because no property kind mapping files have been loaded.");
	}

	return true;
}

StringTableLookup* CategoricalProperty::getStringLookup()
{
	return getRepository()->getDataObjectByUuid<StringTableLookup>(getStringLookupUuid());
}
