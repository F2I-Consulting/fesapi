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
#include "HdfProxy.h"

using namespace EML2_3_NS;

HdfProxy::HdfProxy(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath, COMMON_NS::DataObjectRepository::openingMode hdfPermissionAccess) :
	EML2_NS::HdfProxy(packageDirAbsolutePath, externalFilePath, hdfPermissionAccess)
{
	partialObject = gsoap_resqml2_0_1::soap_new_eml20__DataObjectReference(repo->getGsoapContext());
	partialObject->UUID = guid.empty() ? getRelativePath() : guid;
	partialObject->Title = title;
}
