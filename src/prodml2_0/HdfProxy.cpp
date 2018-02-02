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
/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
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

