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

#include "../witsml2/WellboreObject.h"

namespace WITSML2_1_NS
{
	class WellboreMarkerSet : public WITSML2_NS::WellboreObject
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT WellboreMarkerSet(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WITSML2_NS::WellboreObject(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		*/
		WellboreMarkerSet(WITSML2_NS::Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			double mdBaseSample,
			double mdTopSample,
			gsoap_eml2_3::eml23__LengthUom mdUom);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreMarkerSet(gsoap_eml2_3::witsml21__WellboreMarkerSet* fromGsoap) : WITSML2_NS::WellboreObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~WellboreMarkerSet() {}

		COMMON_NS::DataObjectReference getWellboreDor() const final;
		DLL_IMPORT_OR_EXPORT void setWellbore(WITSML2_NS::Wellbore* witsmlWellbore) final;

		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "WellboreMarkerSet";
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
