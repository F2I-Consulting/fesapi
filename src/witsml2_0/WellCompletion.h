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

#include "witsml2_0/AbstractObject.h"
#include "witsml2_0/WellboreCompletion.h"

namespace WITSML2_0_NS
{
	class WellCompletion : public WITSML2_0_NS::AbstractObject
	{
	public:
		WellCompletion(class Well* witsmlWell,
			const std::string & guid,
			const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellCompletion(gsoap_eml2_1::witsml2__WellCompletion* fromGsoap) :AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~WellCompletion() {}

		gsoap_eml2_1::eml21__DataObjectReference* getWellDor() const;
		
		DLL_IMPORT_OR_EXPORT class Well* getWell() const;

		DLL_IMPORT_OR_EXPORT void setWell(class Well* witsmlWell);

		/**
		* Resolve all relationships of the object in an epc document.
		*/
		void resolveTargetRelationships(COMMON_NS::DataObjectRepository* epcDoc);

		std::vector<epc::Relationship> getAllEpcRelationships() const;

		DLL_IMPORT_OR_EXPORT const std::vector<WellboreCompletion*>& getWellboreCompletions() const { return wellboreCompletionSet; }

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

	protected:
		// backwards relationships
		std::vector<WellboreCompletion* > wellboreCompletionSet;

		friend void WellboreCompletion::setWellCompletion(WellCompletion * wellCompletion);
	};
}