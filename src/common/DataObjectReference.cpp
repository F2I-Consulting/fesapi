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
#include "DataObjectReference.h"

#include "AbstractObject.h"

using namespace COMMON_NS;

DataObjectReference::DataObjectReference(AbstractObject const * dataObj)
	: dor20(nullptr), dor23(nullptr)
{
	std::string ns = dataObj->getXmlNamespace();
	if (ns == "resqml20" || ns == "eml20") {
		dor20 = dataObj->newResqmlReference();
	}
	else if (ns == "witsml21" || ns == "prodml22" || ns == "resqml22" || ns == "eml23") {
		dor23 = dataObj->newEml23Reference();
	}
}

gsoap_resqml2_0_1::eml20__DataObjectReference* DataObjectReference::toDor20() const {
	if (dor20 != nullptr) {
		return dor20;
	}

	gsoap_resqml2_0_1::eml20__DataObjectReference* result = nullptr;
	if (dor23 != nullptr) {
		result = gsoap_resqml2_0_1::soap_new_eml20__DataObjectReference(dor23->soap);
	}
	else {
		throw std::logic_error("The instance is in an inconsistent state.");
	}

	result->ContentType = getContentType();
	result->Title = getTitle();
	result->UUID = getUuid();
	const std::string version = getVersion();
	if (!version.empty()) {
		result->VersionString = gsoap_resqml2_0_1::soap_new_std__string(result->soap);
		result->VersionString->assign(version);
	}

	return result;
}
