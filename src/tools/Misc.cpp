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

#include "tools/Misc.h"

#include <stdexcept>
#include "proxies/gsoap_resqml2_0_1H.h"

using namespace std;

string misc::getPartNameFromReference(gsoap_resqml2_0_1::eml20__DataObjectReference * reference)
{
	return reference->ContentType.substr(reference->ContentType.rfind('=')+1) + "_" + reference->UUID + ".xml";
}

string misc::getPartNameFromReference(gsoap_eml2_2::eml22__DataObjectReference * reference)
{
	return reference->ContentType.substr(reference->ContentType.rfind('=') + 1) + "_" + reference->Uuid + ".xml";
}

gsoap_resqml2_0_1::eml20__DataObjectReference* misc::eml22ToEml20Reference(gsoap_eml2_2::eml22__DataObjectReference* reference, soap* soapContext)
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* result = gsoap_resqml2_0_1::soap_new_eml20__DataObjectReference(soapContext);
	result->UUID = reference->Uuid;
	result->Title = reference->Title;
	result->ContentType = reference->ContentType;
	if (reference->ObjectVersion != nullptr) {
		result->VersionString = gsoap_resqml2_0_1::soap_new_std__string(soapContext);
		result->VersionString->assign(*reference->ObjectVersion);
	}

	return result;
}

