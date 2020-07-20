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
#include "PropertyKind.h"

#include <stdexcept>

#include "../common/EnumStringMapper.h"

#include "../resqml2/AbstractValuesProperty.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* PropertyKind::XML_NS = "resqml20";

void PropertyKind::init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, const std::string & namingSystem)
{
	if (repo == nullptr)
		throw invalid_argument("The repo cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREPropertyKind(repo->getGsoapContext());
	_resqml20__PropertyKind* propType = getSpecializedGsoapProxy();

	propType->NamingSystem = namingSystem;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addOrReplaceDataObject(this);
}

PropertyKind::PropertyKind(COMMON_NS::DataObjectRepository * repo, const string & guid, const string & title,
	const string & namingSystem, resqml20__ResqmlUom uom, resqml20__ResqmlPropertyKind parentEnergisticsPropertyKind)
{
	init(repo, guid, title, namingSystem);
	static_cast<_resqml20__PropertyKind*>(gsoapProxy2_0_1)->RepresentativeUom = uom;

	resqml20__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml20__StandardPropertyKind(gsoapProxy2_0_1->soap);
	xmlStandardPropKind->Kind = parentEnergisticsPropertyKind;
	static_cast<_resqml20__PropertyKind*>(gsoapProxy2_0_1)->ParentPropertyKind = xmlStandardPropKind;
}

PropertyKind::PropertyKind(const string & guid, const string & title,
	const string & namingSystem, resqml20__ResqmlUom uom, EML2_NS::PropertyKind * parentPropType)
{
	if (parentPropType == nullptr) {
		throw invalid_argument("The parent property kind cannot be null.");
	}

	init(parentPropType->getRepository(), guid, title, namingSystem);
	static_cast<_resqml20__PropertyKind*>(gsoapProxy2_0_1)->RepresentativeUom = uom;

	setParentPropertyKind(parentPropType);
}

PropertyKind::PropertyKind(COMMON_NS::DataObjectRepository * repo, const string & guid, const string & title,
	const string & namingSystem, const std::string & nonStandardUom, resqml20__ResqmlPropertyKind parentEnergisticsPropertyKind)
{
	init(repo, guid, title, namingSystem);
	static_cast<_resqml20__PropertyKind*>(gsoapProxy2_0_1)->RepresentativeUom = gsoap_resqml2_0_1::resqml20__ResqmlUom__Euc;
	pushBackExtraMetadata("Uom", nonStandardUom);

	resqml20__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml20__StandardPropertyKind(gsoapProxy2_0_1->soap);
	xmlStandardPropKind->Kind = parentEnergisticsPropertyKind;
	static_cast<_resqml20__PropertyKind*>(gsoapProxy2_0_1)->ParentPropertyKind = xmlStandardPropKind;
}

PropertyKind::PropertyKind(const string & guid, const string & title,
	const string & namingSystem, const std::string & nonStandardUom, EML2_NS::PropertyKind * parentPropType)
{
	init(parentPropType->getRepository(), guid, title, namingSystem);
	static_cast<_resqml20__PropertyKind*>(gsoapProxy2_0_1)->RepresentativeUom = gsoap_resqml2_0_1::resqml20__ResqmlUom__Euc;
	pushBackExtraMetadata("Uom", nonStandardUom);

	setParentPropertyKind(parentPropType);
}

_resqml20__PropertyKind* PropertyKind::getSpecializedGsoapProxy() const
{
	if (isPartial()) {
		throw logic_error("Partial object");
	}

	return static_cast<_resqml20__PropertyKind*>(gsoapProxy2_0_1);
}

void PropertyKind::setXmlParentPropertyKind(EML2_NS::PropertyKind* parentPropertyKind)
{
	_resqml20__PropertyKind* propType = getSpecializedGsoapProxy();

	resqml20__LocalPropertyKind* xmlLocalPropKind = soap_new_resqml20__LocalPropertyKind(gsoapProxy2_0_1->soap);
	xmlLocalPropKind->LocalPropertyKind = parentPropertyKind->newResqmlReference();
	propType->ParentPropertyKind = xmlLocalPropKind;
}

bool PropertyKind::isChildOf(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind standardPropKind) const
{
	if (isPartial()) {
		throw std::invalid_argument("The property kind " + getUuid() + " is partial, we cannot consequently get its parents.");
	}

	if (!isParentAnEnergisticsPropertyKind()) {
		auto parentPk201 = dynamic_cast<RESQML2_0_1_NS::PropertyKind*>(getParentPropertyKind());
		return parentPk201 != nullptr ? parentPk201->isChildOf(standardPropKind) : false;
	}
	else {
		if (getParentEnergisticsPropertyKind() == standardPropKind) {
			return true;
		}
		else if (repository->getPropertyKindMapper() != nullptr) {
			return repository->getPropertyKindMapper()->isChildOf(getParentEnergisticsPropertyKind(), standardPropKind);
		}
		else {
			throw std::invalid_argument("You must load the property kind mapping files if you want to get the standard parent property kind.");
		}
	}
}

bool PropertyKind::isAbstract() const
{
	return getSpecializedGsoapProxy()->IsAbstract;
}

bool PropertyKind::isParentPartial() const
{
	if (isPartial()) { return true; }

	if (isParentAnEnergisticsPropertyKind()) {
		return false;
	}

	EML2_NS::PropertyKind* parentPk = getParentPropertyKind();
	while (!parentPk->isPartial()) {
		parentPk = parentPk->getParentPropertyKind();
		auto parentPk201 = dynamic_cast<RESQML2_0_1_NS::PropertyKind*>(parentPk);
		if (parentPk201->isParentAnEnergisticsPropertyKind()) {
			break;
		}
	}

	return parentPk->isPartial();
}

std::string PropertyKind::getParentAsString() const
{
	if (!isParentAnEnergisticsPropertyKind()) {
		return getParentPropertyKindDor().getTitle();
	}
	else
	{
		gsoap_resqml2_0_1::_resqml20__PropertyKind* propType = static_cast<gsoap_resqml2_0_1::_resqml20__PropertyKind*>(gsoapProxy2_0_1);
		COMMON_NS::EnumStringMapper tmp;
		return tmp.getEnergisticsPropertyKindName(static_cast<gsoap_resqml2_0_1::resqml20__StandardPropertyKind*>(propType->ParentPropertyKind)->Kind);
	}
}

COMMON_NS::DataObjectReference PropertyKind::getParentPropertyKindDor() const
{
	if (isParentAnEnergisticsPropertyKind()) {
		throw invalid_argument("The property kind parent of this property kind is not a local one.");
	}

	gsoap_resqml2_0_1::_resqml20__PropertyKind* propKind = static_cast<gsoap_resqml2_0_1::_resqml20__PropertyKind*>(gsoapProxy2_0_1);
	return static_cast<gsoap_resqml2_0_1::resqml20__LocalPropertyKind*>(propKind->ParentPropertyKind)->LocalPropertyKind;
}

bool PropertyKind::isParentAnEnergisticsPropertyKind() const
{
	return static_cast<gsoap_resqml2_0_1::_resqml20__PropertyKind*>(gsoapProxy2_0_1)->ParentPropertyKind->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StandardPropertyKind;
}

gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind PropertyKind::getParentEnergisticsPropertyKind() const
{
	if (isParentAnEnergisticsPropertyKind())
	{
		if (gsoapProxy2_0_1 != nullptr) {
			gsoap_resqml2_0_1::_resqml20__PropertyKind* propKind = static_cast<gsoap_resqml2_0_1::_resqml20__PropertyKind*>(gsoapProxy2_0_1);
			return static_cast<gsoap_resqml2_0_1::resqml20__StandardPropertyKind*>(propKind->ParentPropertyKind)->Kind;
		}
		else {
			throw logic_error("Not implemented yet");
		}
	}

	throw invalid_argument("The property kind parent of this property kind is not an Energistics one.");
}

void PropertyKind::loadTargetRelationships()
{
	if (isParentAnEnergisticsPropertyKind()) {
		return;
	}

	COMMON_NS::DataObjectReference dor = getParentPropertyKindDor();
	EML2_NS::PropertyKind* parentPk = getRepository()->getDataObjectByUuid<EML2_NS::PropertyKind>(dor.getUuid());
	if (parentPk == nullptr) {
		getRepository()->createPartial(dor);
		parentPk = getRepository()->getDataObjectByUuid<EML2_NS::PropertyKind>(dor.getUuid());
		if (parentPk == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
	}
	getRepository()->addRelationship(this, parentPk);
}
