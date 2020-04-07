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

#include <stdexcept>

#include <hdf5.h>

using namespace std;
using namespace RESQML2_0_1_NS;

const char* HdfProxy::RESQML_ROOT_GROUP = "/RESQML";

HdfProxy::HdfProxy(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath, COMMON_NS::DataObjectRepository::openingMode hdfPermissionAccess) :
	COMMON_NS::HdfProxy(packageDirAbsolutePath, externalFilePath, hdfPermissionAccess)
{
	initGsoapProxy(repo, guid, title, COMMON_NS::AbstractObject::EmlVersion::TWO_DOT_ZERO);
}

std::string HdfProxy::getXmlNamespace() const
{
	return "eml20";
}

hid_t HdfProxy::openOrCreateRootGroup()
{
	if (!isOpened()) {
		open();
	}
	
	if (openedGroups.find(RESQML_ROOT_GROUP) != openedGroups.end()) {
		return openedGroups.at(RESQML_ROOT_GROUP);
	}
	
	H5O_info_t info;
	herr_t status = H5Oget_info_by_name(hdfFile, RESQML_ROOT_GROUP, &info, H5P_DEFAULT);
	
	hid_t result =  status >= 0 ? H5Gopen(hdfFile, RESQML_ROOT_GROUP, H5P_DEFAULT) : H5Gcreate(hdfFile, RESQML_ROOT_GROUP, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	openedGroups[RESQML_ROOT_GROUP] = result;
	return result;
	
}
