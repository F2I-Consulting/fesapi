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

#include "witsml2_1/ErrorTermDictionary.h"
#include "witsml2_1/ToolErrorModel.h"

namespace WITSML2_1_NS
{
	class ErrorTerm : public WITSML2_1_NS::AbstractObject
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		ErrorTerm(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			WITSML2_1_NS::AbstractObject(partialObject),
			errorTermDictionary(nullptr) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		*/
		ErrorTerm(soap* soapContext,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_2::witsml2__ErrorPropagationMode propagationMode,
			class WeightingFunction* weightingFunction);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		ErrorTerm(gsoap_eml2_2::witsml2__ErrorTerm* fromGsoap) :AbstractObject(fromGsoap),
			errorTermDictionary(nullptr) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~ErrorTerm() {}

		DLL_IMPORT_OR_EXPORT bool isTopLevelElement() const;

		DLL_IMPORT_OR_EXPORT std::string getWeightingFunctionUuid() const;
		DLL_IMPORT_OR_EXPORT class WeightingFunction* getWeightingFunction() const;
		DLL_IMPORT_OR_EXPORT void setWeightingFunction(class WeightingFunction* weightingFunction);

		DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> getAllSourceRelationships() const;
		DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> getAllTargetRelationships() const;
		DLL_IMPORT_OR_EXPORT void resolveTargetRelationships(COMMON_NS::EpcDocument * epcDoc);

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const {return XML_TAG;}

	protected:
		// XML backwards relationship
		ErrorTermDictionary* errorTermDictionary;
		std::vector<WITSML2_1_NS::ToolErrorModel*> toolErrorModelSet;

		friend void WITSML2_1_NS::ToolErrorModel::pushBackErrorTerm(class ErrorTerm* errorTerm, double magnitude, gsoap_eml2_2::eml22__UomEnum uom);
		friend void WITSML2_1_NS::ErrorTermDictionary::pushBackErrorTerm(ErrorTerm* et);
	};
}

