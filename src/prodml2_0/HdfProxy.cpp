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
#include "prodml2_0/HdfProxy.h"

#include <stdexcept>

using namespace std;
using namespace prodml2_0;


HdfProxy::HdfProxy(soap* soapContext, const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath) :
	common::HdfProxy(packageDirAbsolutePath, externalFilePath)
{
	initGsoapProxy(soapContext, guid, title, TWO_DOT_ONE);
}

HdfProxy::HdfProxy(soap* soapContext, const std::string & packageDirAbsolutePath, const std::string & externalFilePath) :
	common::HdfProxy(packageDirAbsolutePath, externalFilePath)
{
	gsoapProxy2_1 = gsoap_eml2_1::soap_new_eml21__EpcExternalPartReference(soapContext, 1);
	static_cast<gsoap_eml2_1::_eml21__EpcExternalPartReference* const>(gsoapProxy2_1)->MimeType = gsoap_eml2_1::soap_new_std__string(soapContext, 1);
	static_cast<gsoap_eml2_1::_eml21__EpcExternalPartReference* const>(gsoapProxy2_1)->MimeType->assign("application/x-hdf5");

	initMandatoryMetadata();
	open();
	setMetadata(readStringAttribute(".", "uuid"), "Fake/Virtual Hdf Proxy", "", -1, "", "", -1, "", "");
}

std::string HdfProxy::getXmlNamespace() const
{
	return "eml21";
}

