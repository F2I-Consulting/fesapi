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
#include "resqml2_0_1/PropertyKind.h"

#include <stdexcept>

#include "resqml2/AbstractValuesProperty.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

void PropertyKind::init(soap* soapContext, const std::string & guid, const std::string & title, const std::string & namingSystem)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREPropertyKind(soapContext, 1);
	_resqml2__PropertyKind* propType = getSpecializedGsoapProxy();

	propType->NamingSystem = namingSystem;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

PropertyKind::PropertyKind(soap* soapContext, const string & guid, const string & title,
	const string & namingSystem, const resqml2__ResqmlUom & uom, const resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind)
{
	init(soapContext, guid, title, namingSystem);
	static_cast<_resqml2__PropertyKind*>(gsoapProxy2_0_1)->RepresentativeUom = uom;

	resqml2__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml2__StandardPropertyKind(gsoapProxy2_0_1->soap, 1);
	xmlStandardPropKind->Kind = parentEnergisticsPropertyKind;
	static_cast<_resqml2__PropertyKind*>(gsoapProxy2_0_1)->ParentPropertyKind = xmlStandardPropKind;
}

PropertyKind::PropertyKind(soap* soapContext, const string & guid, const string & title,
	const string & namingSystem, const resqml2__ResqmlUom & uom, RESQML2_NS::PropertyKind * parentPropType)
{
	init(soapContext, guid, title, namingSystem);
	static_cast<_resqml2__PropertyKind*>(gsoapProxy2_0_1)->RepresentativeUom = uom;

	setParentPropertyKind(parentPropType);
}

PropertyKind::PropertyKind(soap* soapContext, const string & guid, const string & title,
	const string & namingSystem, const std::string & nonStandardUom, const resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind)
{
	init(soapContext, guid, title, namingSystem);
	static_cast<_resqml2__PropertyKind*>(gsoapProxy2_0_1)->RepresentativeUom = gsoap_resqml2_0_1::resqml2__ResqmlUom__Euc;
	pushBackExtraMetadata("Uom", nonStandardUom);

	resqml2__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml2__StandardPropertyKind(gsoapProxy2_0_1->soap, 1);
	xmlStandardPropKind->Kind = parentEnergisticsPropertyKind;
	static_cast<_resqml2__PropertyKind*>(gsoapProxy2_0_1)->ParentPropertyKind = xmlStandardPropKind;
}

PropertyKind::PropertyKind(soap* soapContext, const string & guid, const string & title,
	const string & namingSystem, const std::string & nonStandardUom, RESQML2_NS::PropertyKind * parentPropType)
{
	init(soapContext, guid, title, namingSystem);
	static_cast<_resqml2__PropertyKind*>(gsoapProxy2_0_1)->RepresentativeUom = gsoap_resqml2_0_1::resqml2__ResqmlUom__Euc;
	pushBackExtraMetadata("Uom", nonStandardUom);

	setParentPropertyKind(parentPropType);
}

_resqml2__PropertyKind* PropertyKind::getSpecializedGsoapProxy() const
{
	if (isPartial()) {
		throw logic_error("Partial object");
	}

	return static_cast<_resqml2__PropertyKind*>(gsoapProxy2_0_1);
}

void PropertyKind::setXmlParentPropertyKind(RESQML2_NS::PropertyKind* parentPropertyKind)
{
	_resqml2__PropertyKind* propType = getSpecializedGsoapProxy();

	resqml2__LocalPropertyKind* xmlLocalPropKind = soap_new_resqml2__LocalPropertyKind(gsoapProxy2_0_1->soap, 1);
	xmlLocalPropKind->LocalPropertyKind = parentPropertyKind->newResqmlReference();
	propType->ParentPropertyKind = xmlLocalPropKind;
}

bool PropertyKind::isChildOf(gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind standardPropKind) const
{
	if (!isParentAnEnergisticsPropertyKind()) {
		return getParentLocalPropertyKind()->isChildOf(standardPropKind);
	}
	else{
		if (getParentEnergisticsPropertyKind() == standardPropKind) {
			return true;
		}
		else if (epcDocument->getPropertyKindMapper() != nullptr) {
			return epcDocument->getPropertyKindMapper()->isChildOf(getParentEnergisticsPropertyKind(), standardPropKind);
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

