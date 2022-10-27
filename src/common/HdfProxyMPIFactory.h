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

#include "HdfProxyFactory.h"

#ifdef WITH_PARALLEL
#include "../eml2_0/HdfProxyMPI.h"
#endif

namespace COMMON_NS
{
#ifdef WITH_PARALLEL
	/**
	 * @brief	A proxy factory for an HDF5 file located on an Amazon S3 cloud. Here, HDF5 file
	 * 			access is read only.
	 */
	class HdfProxyMPIFactory : public HdfProxyFactory
	{
	public:

		/** Default constructor */
		HdfProxyMPIFactory() {}

		/** Destructor */
		~HdfProxyMPIFactory() = default;

		/**
		 * Creates an instance of a proxy for an HDF5 file with MPI access. Only to be
		 * used in partial transfer context
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A pointer to an instantiated proxy for an HDF5 file with MPI access.
		 */
		virtual EML2_NS::AbstractHdfProxy* make(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject, MPI_Comm comm) {
			return new EML2_0_NS::HdfProxyMPI(partialObject, comm);
		}

		/**
		 * Creates an instance of a proxy for an HDF5 file file with MPI access by wrapping a
		 * gSOAP instance
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 *
		 * @returns	A pointer to an instantiated proxy for an HDF5 file with MPI access.
		 */
		virtual EML2_NS::AbstractHdfProxy* make(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap, MPI_Comm comm) {
			return new EML2_0_NS::HdfProxyMPI(fromGsoap, comm);
		}
	};
#endif
}
