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

using namespace std;
using namespace EML2_1_NS;
using namespace gsoap_eml2_1;

const char* PropertyKind::XML_NS = "eml21";

PropertyKind::PropertyKind(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
	gsoap_eml2_1::eml21__QuantityClassKind quantityClass, bool isAbstract, EML2_NS::PropertyKind* parentPropertyKind)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_1 = soap_new_eml21__PropertyKind(repo->getGsoapContext());
	static_cast<eml21__PropertyKind*>(gsoapProxy2_1)->QuantityClass = soap_eml21__QuantityClassKind2s(repo->getGsoapContext(), quantityClass);
	static_cast<eml21__PropertyKind*>(gsoapProxy2_1)->IsAbstract = isAbstract;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	if (parentPropertyKind == nullptr) {
		parentPropertyKind = repo->createPartial<EML2_1_NS::PropertyKind>("a48c9c25-1e3a-43c8-be6a-044224cc69cb", "property");
	}

	setParentPropertyKind(parentPropertyKind);
}

void PropertyKind::setXmlParentPropertyKind(EML2_NS::PropertyKind* parentPropertyKind)
{
	static_cast<eml21__PropertyKind*>(gsoapProxy2_1)->Parent = parentPropertyKind->newEmlReference();
}

bool PropertyKind::isAbstract() const
{
	return static_cast<eml21__PropertyKind*>(gsoapProxy2_1)->IsAbstract;
}

bool PropertyKind::isParentPartial() const
{
	if (isPartial()) { return true; }

	EML2_NS::PropertyKind* parentPk = getParentPropertyKind();
	while (parentPk != nullptr && !parentPk->isPartial()) {
		parentPk = static_cast<EML2_1_NS::PropertyKind*>(parentPk)->getParentPropertyKind();
	}

	return parentPk != nullptr;
}

std::string PropertyKind::getParentAsString() const
{
	return getParentPropertyKindDor().getTitle();
}

COMMON_NS::DataObjectReference PropertyKind::getParentPropertyKindDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<gsoap_eml2_1::_eml21__PropertyKind*>(gsoapProxy2_1)->Parent);
}

void PropertyKind::loadTargetRelationships()
{
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
