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

#include "common/HdfProxyFactory.h"

#include "HdfProxyExample.h"

class HdfProxyFactoryExample : public COMMON_NS::HdfProxyFactory
{
public:
	HdfProxyFactoryExample() {}
	~HdfProxyFactoryExample() = default;

	/**
	* Only to be used in partial transfer context
	*/
	EML2_NS::AbstractHdfProxy* make(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) {
		return new HdfProxyExample(partialObject);
	}

	/**
	* Creates an instance of this class by wrapping a gsoap instance.
	*/
	EML2_NS::AbstractHdfProxy* make(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap) {
		return new HdfProxyExample(fromGsoap);
	}

	/**
	* Creates an instance of this class for serialization purpose.
	*/
	EML2_NS::AbstractHdfProxy* make(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
		const std::string & packageDirAbsolutePath, const std::string & externalFilePath, COMMON_NS::DataObjectRepository::openingMode hdfPermissionAccess = COMMON_NS::DataObjectRepository::openingMode::READ_ONLY) {
		return new HdfProxyExample(repo, guid, title, packageDirAbsolutePath, externalFilePath, hdfPermissionAccess);
	}
};
