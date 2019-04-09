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
#include "common/EpcExternalPartReference.h"

#include <stdexcept>

#include "tools/GuidTools.h"

#include "resqml2/AbstractRepresentation.h"
#include "resqml2/AbstractProperty.h"

using namespace std;
using namespace COMMON_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* EpcExternalPartReference::XML_TAG = "EpcExternalPartReference";

EpcExternalPartReference::EpcExternalPartReference(const string & packageDirAbsolutePath, const string & externalFilePath) :
		packageDirectoryAbsolutePath(packageDirAbsolutePath), relativeFilePath(externalFilePath) {
}

string EpcExternalPartReference::getXmlTag() const
{
	return XML_TAG;
}

std::vector<epc::Relationship> EpcExternalPartReference::getAllSourceRelationships() const
{
	vector<Relationship> result;

	for (size_t i = 0; i < representationSourceObject.size(); ++i) {
		if (representationSourceObject[i] != nullptr) {
			Relationship rel(representationSourceObject[i]->getPartNameInEpcDocument(), "", representationSourceObject[i]->getUuid());
			rel.setExternalPartProxyToMlType();
			result.push_back(rel);
		}
		else {
			throw domain_error("The representation associated to the external EPC reference cannot be nullptr.");
		}
	}

	for (size_t i = 0; i < propertySourceObject.size(); ++i) {
		if (propertySourceObject[i] != nullptr) {
			Relationship rel(propertySourceObject[i]->getPartNameInEpcDocument(), "", propertySourceObject[i]->getUuid());
			rel.setExternalPartProxyToMlType();
			result.push_back(rel);
		}
		else {
			throw domain_error("The property associated to the external EPC reference cannot be nullptr.");
		}
	}

	return result;
}

std::vector<epc::Relationship> EpcExternalPartReference::getAllTargetRelationships() const
{
	vector<Relationship> result;

	Relationship relExt(relativeFilePath, "", "Hdf5File", false);
	relExt.setExternalResourceType();
	result.push_back(relExt);

	return result;
}

void EpcExternalPartReference::resolveTargetRelationships(COMMON_NS::EpcDocument*)
{}
