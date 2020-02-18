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

#include "HdfProxy.h"

namespace RESQML2_0_1_NS
{
	/**
	* This class allows to open an HDF5 file for reading only which is located on an AWS S3 bucket.
	*/
	class HdfProxyROS3 : public RESQML2_0_1_NS::HdfProxy
	{
		// aws_region is assumed to be managed by means of inherited setRootPath method
		std::string secretId_;
		std::string secretKey_;

	public:

		/**
		* Only to be used in partial transfer context
		*/
		HdfProxyROS3(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject, const std::string & secretId = "", const std::string & secretKey_ = "") :
			RESQML2_0_1_NS::HdfProxy(partialObject),
			secretId_(secretId), secretKey_(secretKey_)
		{}

		HdfProxyROS3(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap, const std::string & secretId = "", const std::string & secretKey_ = "") :
			RESQML2_0_1_NS::HdfProxy(fromGsoap),
			secretId_(secretId), secretKey_(secretKey_)
		{}

		~HdfProxyROS3() {}

		/**
		* Open the file for reading.
		*/
		void open();
	};
}
