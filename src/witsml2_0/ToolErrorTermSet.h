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

#include "witsml2_0/ToolErrorModel.h"

namespace WITSML2_0_NS
{
	class DLL_IMPORT_OR_EXPORT ToolErrorTermSet : public WITSML2_0_NS::AbstractObject
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		*/
		ToolErrorTermSet(soap* soapContext,
			const std::string & guid,
			const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		ToolErrorTermSet(gsoap_eml2_1::witsml2__ToolErrorModel* fromGsoap) :AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~ToolErrorTermSet() {}

		void pushBackTerm(const std::string & name, const std::string & label,
			const std::string & weightingFunction, const std::string & weightingFunctionSource, const std::string & weightingFunctionComment,
			const gsoap_eml2_1::witsml2__ErrorTermSource & type,
			const std::string & depthFormula, const std::string & inclinationFormula, const std::string & azimuthFormula,
			const std::string & singularityNorthFormula, const std::string & singularityEastFormula, const std::string & singularityVerticalFormula);

		/**
		* Resolve all relationships of the object in an epc document.
		*/
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc) {};

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		std::vector<epc::Relationship> getAllEpcRelationships() const;

		// XML backwards relationship
		std::vector<WITSML2_0_NS::ToolErrorModel*> toolErrorModelSet;

		friend void WITSML2_0_NS::ToolErrorModel::setToolErrorTermSet(ToolErrorTermSet* tets);
	};
}

