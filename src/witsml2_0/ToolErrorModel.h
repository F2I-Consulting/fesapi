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

#include "witsml2_0/AbstractObject.h"

namespace WITSML2_0_NS
{
	class DLL_IMPORT_OR_EXPORT ToolErrorModel : public WITSML2_0_NS::AbstractObject
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		*/
		ToolErrorModel(soap* soapContext,
			const std::string & guid,
			const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		ToolErrorModel(gsoap_eml2_1::witsml2__ToolErrorModel* fromGsoap) :AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~ToolErrorModel() {}

		class ToolErrorTermSet* getToolErrorTermSet() const;
		void setToolErrorTermSet(class ToolErrorTermSet* tets);

		void setTypeSurveyTool(const gsoap_eml2_1::witsml2__TypeSurveyTool & typeSurveyTool);

		void setAuthorization(const std::string & authority, const gsoap_eml2_1::witsml2__AuthorizationStatus & status);
		void setAuthorizationVersion(const std::string & version);
		void setAuthorizationComment(const std::string & comment);
		void setAuthorizationSource(const std::string & source);

		void pushBackOperatingCondition(const std::string & parameter, const std::string & value);
		void pushBackOperatingCondition(const std::string & parameter,
			const double & min, const std::string & minUom,
			const double & max, const std::string & maxUom);

		void pushBackTermValue(const std::string & term, const gsoap_eml2_1::witsml2__ErrorPropagationMode & errorPropagationMode,
			const double & value, const std::string & uom,
			const std::string & p1 = "", const std::string & p2 = "", const std::string & p3 = "");

		/**
		* Resolve all relationships of the object in an epc document.
		*/
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		std::vector<epc::Relationship> getAllEpcRelationships() const;
	};
}

