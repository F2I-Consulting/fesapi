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
#include "resqml2_0_1/WellboreFeature.h"
#include "witsml2_0/WellboreCompletion.h"
#include "witsml2_0/Trajectory.h"

namespace WITSML2_0_NS
{
	class Wellbore : public WITSML2_0_NS::AbstractObject
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		Wellbore(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WITSML2_0_NS::AbstractObject(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		*/
		Wellbore(class Well* witsmlWell,
			const std::string & guid,
			const std::string & title);

		Wellbore(class Well* witsmlWell,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::eml21__WellStatus statusWellbore,
			bool isActive,
			bool achievedTD
		);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		Wellbore(gsoap_eml2_1::witsml2__Wellbore* fromGsoap):AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~Wellbore() {}

		gsoap_eml2_1::eml21__DataObjectReference* getWellDor() const;
		DLL_IMPORT_OR_EXPORT class Well* getWell() const;

		DLL_IMPORT_OR_EXPORT void setWell(class Well* witsmlWell);

		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::WellboreFeature *> getResqmlWellboreFeature() const;

		DLL_IMPORT_OR_EXPORT std::vector<WellboreCompletion *> getWellboreCompletions() const;
		DLL_IMPORT_OR_EXPORT std::vector<Trajectory *> getTrajectories() const;

		DLL_IMPORT_OR_EXPORT void setShape(gsoap_eml2_1::witsml2__WellboreShape shape);

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		/**
		* Resolve all relationships of the object in the repository.
		*/
		void loadTargetRelationships();
	};
}
