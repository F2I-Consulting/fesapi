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

namespace WITSML2_0_NS
{
	/**
	* The class is the super class for all wellbore objects (all top level objects pointing to Wellbore)
	*/
	class WellboreObject : public WITSML2_0_NS::AbstractObject
	{
	protected:
		/**
		* Constructor for partial transfer
		*/
		WellboreObject(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WITSML2_0_NS::AbstractObject(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		*/
		WellboreObject():WITSML2_0_NS::AbstractObject() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreObject(gsoap_eml2_1::eml21__AbstractObject* fromGsoap):WITSML2_0_NS::AbstractObject(fromGsoap) {}

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~WellboreObject() {}

		DLL_IMPORT_OR_EXPORT virtual gsoap_eml2_1::eml21__DataObjectReference* getWellboreDor() const = 0;
		DLL_IMPORT_OR_EXPORT class Wellbore* getWellbore() const;
		DLL_IMPORT_OR_EXPORT virtual void setWellbore(class Wellbore* witsmlWellbore) = 0;

		DLL_IMPORT_OR_EXPORT virtual std::vector<epc::Relationship> getAllSourceRelationships() const;
		DLL_IMPORT_OR_EXPORT virtual std::vector<epc::Relationship> getAllTargetRelationships() const;
		DLL_IMPORT_OR_EXPORT virtual void resolveTargetRelationships(COMMON_NS::EpcDocument * epcDoc);
	};
}
