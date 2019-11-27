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
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;

PropertyKind::PropertyKind(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
	gsoap_eml2_1::eml21__QuantityClassKind quantityClass, bool isAbstract, COMMON_NS::PropertyKind* parentPropertyKind)
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
		parentPropertyKind = repo->createPartial<WITSML2_0_NS::PropertyKind>("a48c9c25-1e3a-43c8-be6a-044224cc69cb", "property");
	}

	setParentPropertyKind(parentPropertyKind);
}

void PropertyKind::setXmlParentPropertyKind(COMMON_NS::PropertyKind* parentPropertyKind)
{
	static_cast<eml21__PropertyKind*>(gsoapProxy2_1)->Parent = parentPropertyKind->newEmlReference();
}

PropertyKind* PropertyKind::getParentPropertyKind() const
{
	if (static_cast<eml21__PropertyKind*>(gsoapProxy2_1)->Parent == nullptr) {
		return nullptr;
	}
	return getRepository()->getDataObjectByUuid<PropertyKind>(static_cast<eml21__PropertyKind*>(gsoapProxy2_1)->Parent->Uuid);
}

bool PropertyKind::isChildOf(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind) const
{
	return false;
}

bool PropertyKind::isAbstract() const
{
	return static_cast<eml21__PropertyKind*>(gsoapProxy2_1)->IsAbstract;
}

bool PropertyKind::isParentPartial() const
{
	if (isPartial()) { return true; }

	if (isParentAnEnergisticsPropertyKind()) {
		return false;
	}

	COMMON_NS::PropertyKind* parentPk = getParentPropertyKind();
	while (parentPk != nullptr && !parentPk->isPartial()) {
		parentPk = static_cast<WITSML2_0_NS::PropertyKind*>(parentPk)->getParentPropertyKind();
	}

	return parentPk != nullptr;
}
