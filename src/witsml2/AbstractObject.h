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

#include "../common/AbstractObject.h"

namespace WITSML2_NS
{
	class AbstractObject : public COMMON_NS::AbstractObject
	{
	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractObject() {}

		/**
		* Get part name of this XML top level instance in the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::string getPartNameInEpcDocument() const;

	protected:

		/**
		* Constructor for partial transfer
		*/
		AbstractObject(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		* Default constructor
		*/
		AbstractObject() {}

		AbstractObject(gsoap_eml2_1::eml21__AbstractObject* proxy) : COMMON_NS::AbstractObject(proxy) {}

		//AbstractObject(gsoap_eml2_2::eml22__AbstractObject* proxy) : COMMON_NS::AbstractObject(proxy) {}
	};
}
