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
#include "resqml2_0_1/OrganizationFeature.h"

#include <stdexcept>

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

const char* OrganizationFeature::XML_TAG = "OrganizationFeature";

OrganizationFeature::OrganizationFeature(soap* soapContext, const std::string & guid, const string & title, const resqml2__OrganizationKind & orgType)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREOrganizationFeature(soapContext, 1);
	_resqml2__OrganizationFeature* orgFeat = static_cast<_resqml2__OrganizationFeature*>(gsoapProxy2_0_1);
	orgFeat->OrganizationKind = orgType;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}


