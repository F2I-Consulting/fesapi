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
using namespace EML2_NS;

const char* PropertyKind::XML_TAG = "PropertyKind";

std::string PropertyKind::getNamingSystem() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::_resqml20__PropertyKind*>(gsoapProxy2_0_1)->NamingSystem;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getOriginator();
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

PropertyKind* PropertyKind::getParentPropertyKind() const
{
	return static_cast<PropertyKind*>(repository->getDataObjectByUuid(getParentPropertyKindDor().getUuid()));
}

void PropertyKind::setParentPropertyKind(PropertyKind* parentPropertyKind)
{
	if (parentPropertyKind == nullptr) {
		throw invalid_argument("The parent property kind cannot be null");
	}

	setXmlParentPropertyKind(parentPropertyKind);

	parentPropertyKind->getRepository()->addRelationship(this, parentPropertyKind);
	if (getRepository() == nullptr) {
		parentPropertyKind->getRepository()->addOrReplaceDataObject(this);
	}
}
