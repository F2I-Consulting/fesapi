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

#include "../eml2_0/HdfProxyROS3.h"

namespace COMMON_NS
{
	/**
	 * @brief	A proxy factory for an HDF5 file located on an Amazon S3 cloud. Here, HDF5 file
	 * 			access is read only.
	 */
	class HdfProxyROS3Factory : public HdfProxyFactory
	{
	public:

		/** Identifier for an Amazon S3 secret access key */
		std::string secret_id;
		/** An Amazon S3 secret access key */
		std::string secret_key;

		/** Default constructor */
		HdfProxyROS3Factory() {}

		/** Destructor */
		~HdfProxyROS3Factory() {}

		/**
		 * Creates an instance of a proxy for an HDF5 file located on an Amazon S3 cloud. Only to be
		 * used in partial transfer context
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A pointer to an instantiated proxy for an HDF5 file located on an Amazon S3 cloud.
		 */
		virtual EML2_NS::AbstractHdfProxy* make(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) {
			return new EML2_0_NS::HdfProxyROS3(partialObject, secret_id, secret_key);
		}

		/**
		 * Creates an instance of a proxy for an HDF5 file located on an Amazon S3 cloud by wrapping a
		 * gSOAP instance
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 *
		 * @returns	A pointer to an instantiated proxy for an HDF5 file located on an Amazon S3 cloud.
		 */
		virtual EML2_NS::AbstractHdfProxy* make(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap) {
			return new EML2_0_NS::HdfProxyROS3(fromGsoap, secret_id, secret_key);
		}
	};
}
