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
#include "AbstractHdfProxy.h"

using namespace COMMON_NS;

void AbstractHdfProxy::initGsoapProxy(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, AbstractObject::EmlVersion emlVersion)
{
	if (emlVersion == AbstractObject::EmlVersion::TWO_DOT_ZERO) {
		gsoapProxy2_0_1 = gsoap_resqml2_0_1::soap_new_eml20__obj_USCOREEpcExternalPartReference(repo->getGsoapContext());
		static_cast<gsoap_resqml2_0_1::_eml20__EpcExternalPartReference*>(gsoapProxy2_0_1)->MimeType = "application/x-hdf5";
	}
	else {
		gsoapProxy2_1 = gsoap_eml2_1::soap_new_eml21__EpcExternalPartReference(repo->getGsoapContext());
		static_cast<gsoap_eml2_1::_eml21__EpcExternalPartReference*>(gsoapProxy2_1)->MimeType = gsoap_eml2_1::soap_new_std__string(repo->getGsoapContext());
		static_cast<gsoap_eml2_1::_eml21__EpcExternalPartReference*>(gsoapProxy2_1)->MimeType->assign("application/x-hdf5");
	}

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(this);
}
