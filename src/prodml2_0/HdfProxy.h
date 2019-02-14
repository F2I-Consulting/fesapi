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

#include "common/HdfProxy.h"

namespace PRODML2_0_NS
{
	class DLL_IMPORT_OR_EXPORT HdfProxy : public COMMON_NS::HdfProxy
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param soapContext		The soap context where the underlying gsoap proxy is going to be created.
		* @param guid				The guid of the underlying gsoap proxy to be created.
		* @param title				The title of the underlying gsoap proxy to be created.
		* @packageDirAbsolutePath	The directory where the EPC document is stored. Must end with a slash or back-slash
		* @relativeFilePath			The relative file path of the associated HDF file. It is relative to the location of the package
		*/
		HdfProxy(soap* soapContext, const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath);

		HdfProxy(soap* soapContext, const std::string & packageDirAbsolutePath, const std::string & externalFilePath);

		HdfProxy(gsoap_eml2_1::_eml21__EpcExternalPartReference* fromGsoap, const std::string & packageDirAbsolutePath, const std::string & externalFilePath) :
			COMMON_NS::HdfProxy(fromGsoap, packageDirAbsolutePath, externalFilePath) {}

		~HdfProxy() {}

		/**
		* Get the XML namespace for the tags for the XML serialization of this instance
		*/
		std::string getXmlNamespace() const;
	};
}

