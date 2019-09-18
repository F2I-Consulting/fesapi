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
#include "resqml2/PropertyKind.h"

#include <stdexcept>

#include "common/EnumStringMapper.h"

#include "resqml2/AbstractValuesProperty.h"

using namespace std;
using namespace RESQML2_NS;

const char* PropertyKind::XML_TAG = "PropertyKind";

const std::string & PropertyKind::getNamingSystem() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::_resqml20__PropertyKind*>(gsoapProxy2_0_1)->NamingSystem;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

const gsoap_resqml2_0_1::resqml20__ResqmlUom & PropertyKind::getUom() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::_resqml20__PropertyKind*>(gsoapProxy2_0_1)->RepresentativeUom;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string PropertyKind::getUomAsString() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return gsoap_resqml2_0_1::soap_resqml20__ResqmlUom2s(gsoapProxy2_0_1->soap, getUom());
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string PropertyKind::getParentAsString() const
{
	if (!isParentAnEnergisticsPropertyKind()) {
		return getParentLocalPropertyKindTitle();
	}
	else
	{
		gsoap_resqml2_0_1::_resqml20__PropertyKind* propType = static_cast<gsoap_resqml2_0_1::_resqml20__PropertyKind*>(gsoapProxy2_0_1);
		COMMON_NS::EnumStringMapper tmp;
		return tmp.getEnergisticsPropertyKindName(static_cast<gsoap_resqml2_0_1::resqml20__StandardPropertyKind*>(propType->ParentPropertyKind)->Kind);
	}
}

bool PropertyKind::isParentAnEnergisticsPropertyKind() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::_resqml20__PropertyKind*>(gsoapProxy2_0_1)->ParentPropertyKind->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__StandardPropertyKind;
	}
	else {
		throw logic_error("Not implemented yet");
	}
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

PropertyKind* PropertyKind::getParentLocalPropertyKind() const
{
	return static_cast<PropertyKind*>(repository->getDataObjectByUuid(getParentLocalPropertyKindUuid()));
}

gsoap_resqml2_0_1::eml20__DataObjectReference* PropertyKind::getParentLocalPropertyKindDor() const
{
	if (isParentAnEnergisticsPropertyKind()) {
		throw invalid_argument("The property kind parent of this property kind is not a local one.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::_resqml20__PropertyKind* propKind = static_cast<gsoap_resqml2_0_1::_resqml20__PropertyKind*>(gsoapProxy2_0_1);
		return static_cast<gsoap_resqml2_0_1::resqml20__LocalPropertyKind*>(propKind->ParentPropertyKind)->LocalPropertyKind;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string PropertyKind::getParentLocalPropertyKindUuid() const
{
	return getParentLocalPropertyKindDor()->UUID;
}

std::string PropertyKind::getParentLocalPropertyKindTitle() const
{
	return getParentLocalPropertyKindDor()->Title;
}

void PropertyKind::setParentPropertyKind(PropertyKind* parentPropertyKind)
{
	if (parentPropertyKind == nullptr) {
		throw invalid_argument("The parent property kind cannot be null");
	}
	if (getRepository() == nullptr) {
		parentPropertyKind->getRepository()->addOrReplaceDataObject(this);
	}
	getRepository()->addRelationship(this, parentPropertyKind);

	setXmlParentPropertyKind(parentPropertyKind);
}

void PropertyKind::loadTargetRelationships()
{
	if (isParentAnEnergisticsPropertyKind()) {
		return;
	}

	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getParentLocalPropertyKindDor();
	RESQML2_NS::PropertyKind* parentPk = getRepository()->getDataObjectByUuid<PropertyKind>(dor->UUID);
	if (parentPk == nullptr) {
		getRepository()->createPartial(dor);
		parentPk = getRepository()->getDataObjectByUuid<PropertyKind>(dor->UUID);
		if (parentPk == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
	}
	getRepository()->addRelationship(this, parentPk);
}
