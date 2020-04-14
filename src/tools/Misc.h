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

#include "../proxies/gsoap_resqml2_0_1Stub.h"
#include "../proxies/gsoap_eml2_3Stub.h"

namespace misc
{
	/**
	* Get the part name of an object in the epc document based on one of its reference.
	*/
	std::string getPartNameFromReference(gsoap_resqml2_0_1::eml20__DataObjectReference * reference);

	/**
	* Get the part name of an eml 2.2 object in the epc document based on one of its reference.
	*/
	std::string getPartNameFromReference(gsoap_eml2_3::eml23__DataObjectReference * reference);

	/**
	 * Convert an EML 2.2 data object reference to an EML 2.0 data object reference.
	 */
	gsoap_resqml2_0_1::eml20__DataObjectReference* eml23ToEml20Reference(gsoap_eml2_3::eml23__DataObjectReference* reference, soap* soapContext);
}

