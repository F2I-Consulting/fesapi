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

#include "../eml2_0/HdfProxy.h"
#include "../eml2_3/HdfProxy.h"

namespace COMMON_NS
{
	/** An HDF5 file proxy factory. */
	class HdfProxyFactory
	{
	public:

		/** Destructor */
		DLL_IMPORT_OR_EXPORT virtual ~HdfProxyFactory() {}

		/**
		 * Creates an instance of HDF5 file proxy. Only to be used in partial transfer context
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A pointer to an instantiated HDF5 file proxy.
		 */
		DLL_IMPORT_OR_EXPORT virtual EML2_NS::AbstractHdfProxy* make(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) {
			return new EML2_0_NS::HdfProxy(partialObject);
		}

		/**
		 * Creates an instance of HDF5 file proxy by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 *
		 * @returns	A pointer to an instantiated HDF5 file proxy.
		 */
		DLL_IMPORT_OR_EXPORT virtual EML2_NS::AbstractHdfProxy* make(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap) {
			return new EML2_0_NS::HdfProxy(fromGsoap);
		}

		/**
		 * Creates an instance of HDF5 file proxy by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 *
		 * @returns	A pointer to an instantiated HDF5 file proxy.
		 */
		DLL_IMPORT_OR_EXPORT virtual EML2_NS::AbstractHdfProxy* make(gsoap_eml2_3::_eml23__EpcExternalPartReference* fromGsoap) {
			return new EML2_3_NS::HdfProxy(fromGsoap);
		}

		/**
		 * Creates an instance of HDF5 file proxy for serialization purpose.
		 *
		 * @param [in]	repo				  	A non-null data object repository.
		 * @param 	  	guid				  	A unique identifier for the HDF5 file proxy.
		 * @param 	  	title				  	The title of the HDF5 file proxy.
		 * @param 	  	packageDirAbsolutePath	Path of the directory containing the EPC file.
		 * @param 	  	externalFilePath	  	Path of the HDF5 file relative to the directory where
		 * 										the EPC document is stored.
		 * @param 	  	hdfPermissionAccess   	(Optional) The HDF5 file permission access. It is read
		 * 										only by default.
		 *
		 * @returns	A pointer to an instantiated HDF5 file proxy.
		 */
		DLL_IMPORT_OR_EXPORT virtual EML2_NS::AbstractHdfProxy* make(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			const std::string & packageDirAbsolutePath, const std::string & externalFilePath,
			COMMON_NS::DataObjectRepository::openingMode hdfPermissionAccess = COMMON_NS::DataObjectRepository::openingMode::READ_ONLY) {
			switch (repo->getDefaultEmlVersion()) {
			case COMMON_NS::DataObjectRepository::EnergisticsStandard::EML2_0:
				return new EML2_0_NS::HdfProxy(repo, guid, title, packageDirAbsolutePath, externalFilePath, hdfPermissionAccess);
			case COMMON_NS::DataObjectRepository::EnergisticsStandard::EML2_3:
				return new EML2_3_NS::HdfProxy(repo, guid, title, packageDirAbsolutePath, externalFilePath, hdfPermissionAccess);
			default:
				throw std::invalid_argument("Unrecognized Energistics standard.");
			}
		}

	};
}
