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

#include <vector>
#include <string>

#include "witsml2_1/AbstractObject.h"

namespace WITSML2_1_NS
{
	class ErrorTermDictionary : public WITSML2_1_NS::AbstractObject
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		*/
		ErrorTermDictionary(soap* soapContext,
			const std::string & guid,
			const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		ErrorTermDictionary(gsoap_eml2_2::witsml2__ErrorTermDictionary* fromGsoap) :AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~ErrorTermDictionary() {}

		DLL_IMPORT_OR_EXPORT std::string getErrorTermUuid(unsigned long index) const;
		DLL_IMPORT_OR_EXPORT class ErrorTerm* getErrorTerm(unsigned long index) const;
		DLL_IMPORT_OR_EXPORT std::vector<class ErrorTerm*> getErrorTerms() const;
		DLL_IMPORT_OR_EXPORT void pushBackErrorTerm(class ErrorTerm* tem);

		DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> getAllSourceRelationships() const;
		DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> getAllTargetRelationships() const;
		DLL_IMPORT_OR_EXPORT void resolveTargetRelationships(COMMON_NS::EpcDocument * epcDoc);

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }
	};
}

