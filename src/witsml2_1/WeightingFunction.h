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

#include "WeightingFunctionDictionary.h"
#include "ErrorTerm.h"

namespace WITSML2_1_NS
{
	class WeightingFunction : public COMMON_NS::AbstractObject
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		WeightingFunction(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			COMMON_NS::AbstractObject(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		*/
		WeightingFunction(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid,
			const std::string & title,
			const std::string & depthFormula,
			const std::string & inclinationFormula,
			const std::string & azimuthFormula);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WeightingFunction(gsoap_eml2_3::witsml21__WeightingFunction* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~WeightingFunction() {}

		DLL_IMPORT_OR_EXPORT bool isTopLevelElement() const;

		DLL_IMPORT_OR_EXPORT void setKind(gsoap_eml2_3::witsml21__ErrorKind errorKind);
		DLL_IMPORT_OR_EXPORT void pushBackSource(const std::string & source);
		DLL_IMPORT_OR_EXPORT void setSingularityNorthFormula(const std::string & singularityNorthFormula);
		DLL_IMPORT_OR_EXPORT void setSingularityEastFormula(const std::string & singularityEastFormula);
		DLL_IMPORT_OR_EXPORT void setSingularityVerticalFormula(const std::string & singularityVerticalFormula);

		void loadTargetRelationships() {}

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "witsml21";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
