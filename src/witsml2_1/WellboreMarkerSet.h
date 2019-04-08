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

#include "witsml2_1/AbstractObject.h"

#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"

namespace WITSML2_1_NS
{
	class DLL_IMPORT_OR_EXPORT WellboreMarkerSet : public WITSML2_1_NS::AbstractObject
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		*/
		WellboreMarkerSet(class Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			const std::string & mdDatum,
			const double & mdBaseSample,
			const double & mdTopSample);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreMarkerSet(gsoap_eml2_2::witsml2__WellboreMarkerSet* fromGsoap) :AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~WellboreMarkerSet() {}

		gsoap_eml2_2::eml22__DataObjectReference* getWellboreDor() const;
		class Wellbore* getWellbore() const;
		void setWellbore(class Wellbore* witsmlWellbore);

		std::vector<epc::Relationship> getAllEpcRelationships() const;

		/**
		* Resolve all relationships of the object in an epc document.
		*/
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}
	};
}

