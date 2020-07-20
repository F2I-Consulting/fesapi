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
	class ToolErrorModelDictionary : public WITSML2_1_NS::AbstractObject
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		*/
		ToolErrorModelDictionary(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid,
			const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		ToolErrorModelDictionary(gsoap_eml2_2::witsml2__ToolErrorModelDictionary* fromGsoap) :AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~ToolErrorModelDictionary() {}

		DLL_IMPORT_OR_EXPORT std::string getToolErrorModelUuid(unsigned long index) const;
		DLL_IMPORT_OR_EXPORT class ToolErrorModel* getToolErrorModel(unsigned long index) const;
		DLL_IMPORT_OR_EXPORT std::vector<class ToolErrorModel*> getToolErrorModels() const;
		DLL_IMPORT_OR_EXPORT void pushBackToolErrorModel(class ToolErrorModel* tem);

		/**
		* Resolve all relationships of the object in an epc document.
		*/
		void loadTargetRelationships();

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const {return XML_TAG;}
	};
}
