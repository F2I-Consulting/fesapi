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
#include "OrganizationFeature.h"

#include <stdexcept>

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* OrganizationFeature::XML_TAG = "OrganizationFeature";
const char* OrganizationFeature::XML_NS = "resqml20";

OrganizationFeature::OrganizationFeature(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const string & title, resqml20__OrganizationKind orgType)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREOrganizationFeature(repo->getGsoapContext());
	static_cast<_resqml20__OrganizationFeature*>(gsoapProxy2_0_1)->OrganizationKind = orgType;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	repo->addOrReplaceDataObject(this);
}

gsoap_resqml2_0_1::resqml20__OrganizationKind OrganizationFeature::getKind() const {
	return static_cast<_resqml20__OrganizationFeature*>(gsoapProxy2_0_1)->OrganizationKind;
}
