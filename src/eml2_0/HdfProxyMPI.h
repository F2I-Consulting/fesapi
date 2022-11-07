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


#include <H5pubconf.h>
#include <hdf5.h>

#include "HdfProxy.h"

namespace EML2_0_NS
{
#ifdef H5_HAVE_PARALLEL
    /** This class allows to open an HDF5 file using MPI for reading / writing with multiple processes */
    class HdfProxyMPI final : public EML2_0_NS::HdfProxy
    {
        /** Whether to open the same file in parallel, or open a file per process */
        // bool mpio_file_parallel;

        /** An MPI communicator where each rank in the communicator will be accessing the target file. */
        MPI_Comm mpi_comm;

        /** The hdf file access properties list id */
        hid_t fapl_id;

    public:

        /**
		 * @brief	Only to be used in partial transfer context
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
         */
        HdfProxyMPI(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject, MPI_Comm comm):
            EML2_0_NS::HdfProxy(partialObject),
            mpi_comm(comm)
        {}

		/**
		 * @brief	Constructor
		 *
		 * @param [in]	fromGsoap 	If non-nullptr, from gsoap.
		 * @param 	  	secretId  	(Optional) Identifier for the secret.
		 * @param 	  	secretKey_	(Optional) The secret key.
		 */
		HdfProxyMPI(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap, MPI_Comm comm) :
			EML2_0_NS::HdfProxy(fromGsoap),
            mpi_comm(comm)
		{}

		/** Destructor */
		~HdfProxyMPI() = default;

        /** Open the file for reading. */
		void open() override;

        /** Close the file */
        void close() override;
    };
#endif
}