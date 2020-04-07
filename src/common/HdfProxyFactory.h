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
#pragma once

#include "../resqml2_0_1/HdfProxy.h"

namespace COMMON_NS
{
	class HdfProxyFactory
	{
	public:

		DLL_IMPORT_OR_EXPORT virtual ~HdfProxyFactory() {}

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT virtual AbstractHdfProxy* make(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) {
			return new RESQML2_0_1_NS::HdfProxy(partialObject);
		}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		DLL_IMPORT_OR_EXPORT virtual AbstractHdfProxy* make(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap) {
			return new RESQML2_0_1_NS::HdfProxy(fromGsoap);
		}
		
		/**
		* Creates an instance of this class for serialization purpose.
		*/
		DLL_IMPORT_OR_EXPORT virtual AbstractHdfProxy* make(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath, COMMON_NS::DataObjectRepository::openingMode hdfPermissionAccess = COMMON_NS::DataObjectRepository::openingMode::READ_ONLY) {
			return new RESQML2_0_1_NS::HdfProxy(repo, guid, title, packageDirAbsolutePath, externalFilePath, hdfPermissionAccess);
		}

	};
}
