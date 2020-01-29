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

#include "../common/HdfProxy.h"

/** . */
namespace RESQML2_0_1_NS
{
	/** A hdf proxy. */
	class HdfProxy : public COMMON_NS::HdfProxy
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT HdfProxy(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::HdfProxy(partialObject) {}

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
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT HdfProxy(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap) :
			COMMON_NS::HdfProxy(fromGsoap) {}

		/** Destructor */
		DLL_IMPORT_OR_EXPORT ~HdfProxy() {}

		/**
		 * Get the XML namespace for the tags for the XML serialization of this instance
		 *
		 * @returns	The XML namespace.
		 */
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const;

	private:
		/** Group the resqml root belongs to */
		static const char * RESQML_ROOT_GROUP;

		/**
		 * Check if a hdf group named "RESQML" exists as a child of the root of the HDF file. If it
		 * exists, it returns the latter. If not, it creates this group and then returns it. Please
		 * close the group after having called and used this group.
		 *
		 * @returns	A hdf5_hid_t.
		 */
		hdf5_hid_t openOrCreateRootGroup();

	};
}
