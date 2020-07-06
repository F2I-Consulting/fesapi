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

#include "../MacroDefinitions.h"

namespace WITSML2_0_NS
{
	/** An abstract object. */
	class AbstractObject : public COMMON_NS::AbstractObject
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~AbstractObject() {}

		/**
		 * Get the XML namespace for the tags for the XML serialization of this instance
		 *
		 * @returns	The XML namespace.
		 */
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const;

		/**
		 * Get the content type of the instance according to EPC recommendation
		 *
		 * @returns	The content type.
		 */
		DLL_IMPORT_OR_EXPORT std::string getContentType() const;

		/**
		 * Get part name of this XML top level instance in the EPC document
		 *
		 * @returns	The part name in epc document.
		 */
		DLL_IMPORT_OR_EXPORT std::string getPartNameInEpcDocument() const;

	protected:

		/**
		 * Constructor for partial transfer
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT AbstractObject(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/** Default constructor */
		AbstractObject() {}

		/**
		 * Constructor when importing EML 2.1 dataobjects
		 *
		 * @param [in,out]	proxy	If non-null, the proxy.
		 */
		AbstractObject(gsoap_eml2_1::eml21__AbstractObject* proxy) : COMMON_NS::AbstractObject(proxy) {}
	};
}
