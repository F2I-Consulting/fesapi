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

#include "../eml2/HdfProxy.h"

namespace EML2_3_NS
{
	/** A hdf proxy. */
	class HdfProxy final : public EML2_NS::HdfProxy
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT HdfProxy(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : EML2_NS::HdfProxy(partialObject) {}

		/**
		 * @brief	Constructor
		 *
		 * @param 	dor	The dor.
		 */
		DLL_IMPORT_OR_EXPORT HdfProxy(const COMMON_NS::DataObjectReference& dor) : EML2_NS::HdfProxy(dor) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	repo				  	The repo where the underlying gsoap proxy is going to
		 * 											be created.
		 * @param 		  	guid				  	The guid of the underlying gsoap proxy to be created.
		 * @param 		  	title				  	The title of the underlying gsoap proxy to be created.
		 * @param			packageDirAbsolutePath	The directory where the EPC
		 * 											document is stored. Must end with a slash or back-
		 * 											slash.
		 * @param			externalFilePath		The relative file path of the associated HDF file. It
		 * 											is relative to the location of the package.
		 * @param 		  	hdfPermissionAccess   	(Optional) The hdf permission access.
		 */
		DLL_IMPORT_OR_EXPORT HdfProxy(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath, COMMON_NS::DataObjectRepository::openingMode hdfPermissionAccess = COMMON_NS::DataObjectRepository::openingMode::READ_ONLY);

		/**
		 * Hdf proxy
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT HdfProxy(gsoap_eml2_3::_eml23__EpcExternalPartReference* fromGsoap) :
			EML2_NS::HdfProxy(fromGsoap) {}

		/** Destructor */
		DLL_IMPORT_OR_EXPORT ~HdfProxy() {}

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
