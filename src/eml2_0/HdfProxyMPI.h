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

#include <mpi.h>

#include "HdfProxy.h"

namespace EML2_0_NS
{
    /** This class allows to open an HDF5 file using Parallel HDF5 (MPI) for writing with multiple processes */
    class HdfProxyMPI final : public EML2_NS::HdfProxy
    {
    public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT HdfProxyMPI(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : EML2_NS::HdfProxy(partialObject) {}

		/**
		 * @brief	Constructor
		 *
		 * @param 	dor	The dor.
		 */
		DLL_IMPORT_OR_EXPORT HdfProxyMPI(const COMMON_NS::DataObjectReference& dor) : EML2_NS::HdfProxy(dor) {}

       /**
		 * Creates an instance of this class in a gsoap context for writing.
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
		HdfProxyMPI(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			const std::string & packageDirAbsolutePath, const std::string & externalFilePath,
			COMMON_NS::DataObjectRepository::openingMode hdfPermissionAccess = COMMON_NS::DataObjectRepository::openingMode::READ_ONLY) :
			EML2_NS::HdfProxy(packageDirAbsolutePath, externalFilePath, hdfPermissionAccess)
		{
			initGsoapProxy(repo, guid, title, 20);
		}

		/**
		 * Hdf proxy
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT HdfProxyMPI(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap) :
			EML2_NS::HdfProxy(fromGsoap) {}

		/** Destructor */
		~HdfProxyMPI() = default;

        /** Open the file for reading. */
		void open() final;

		/**
		 * Set the MPI communicator to use
		*/
		void setMPICommunicator(MPI_Comm communicator) { mpi_comm = communicator; }

		/**
		 * @brief Set IO to collective
		 * @details necessary to write with compression enabled
		 */
		void setCollectiveIO();

		/**
		 * @brief Set IO to independent (default)
		 */
		void setIndependentIO();

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "eml20";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
		
	private:
        /** An MPI communicator where each rank in the communicator will be accessing the target file. */
        MPI_Comm mpi_comm = MPI_COMM_WORLD;
    };
}