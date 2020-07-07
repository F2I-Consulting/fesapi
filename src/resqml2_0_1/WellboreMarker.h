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

#include "../resqml2/WellboreMarker.h"

namespace RESQML2_0_1_NS
{
	class WellboreMarkerFrameRepresentation;

	class WellboreMarker final : public RESQML2_NS::WellboreMarker
	{
	public:

		/**
		 * Creates an instance of this class in a gSOAP context.
		 *
		 * @exception	std::invalid_argument	If @p wellboreMarkerFrame is @c nullptr.
		 *
		 * @param [in,out]	wellboreMarkerFrame	The wellbore marker frame representation which contains
		 * 										the wellbore marker to contruct. It cannot be null.
		 * @param 		  	guid			   	The guid to set to this wellbore marker. If empty then a
		 * 										new guid will be generated.
		 * @param 		  	title			   	The title to set to this wellbore marker. If empty then
		 * 										\"unknown\" title will be set.
		 */
		DLL_IMPORT_OR_EXPORT WellboreMarker(RESQML2_0_1_NS::WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class in a gSOAP context.
		 *
		 * @exception	std::invalid_argument	If @p wellboreMarkerFrame is @c nullptr.
		 *
		 * @param [in,out]	wellboreMarkerFrame 	The wellbore marker frame representation which
		 * 											contains the wellbore marker to contruct. It cannot be
		 * 											null.
		 * @param 		  	guid					The guid to set to this wellbore marker. If empty
		 * 											then a new guid will be generated.
		 * @param 		  	title					The title to set to this wellbore marker. If empty
		 * 											then \"unknown\" title will be set.
		 * @param 		  	geologicBoundaryKind	The type of the feature the marker intersects.
		 */
		DLL_IMPORT_OR_EXPORT WellboreMarker(RESQML2_0_1_NS::WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind geologicBoundaryKind);

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		WellboreMarker(gsoap_resqml2_0_1::resqml20__WellboreMarker* fromGsoap) : RESQML2_NS::WellboreMarker(fromGsoap)  {}

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		~WellboreMarker() {}

		DLL_IMPORT_OR_EXPORT bool hasAGeologicBoundaryKind() const final;

		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind getGeologicBoundaryKind() const final;

		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getBoundaryFeatureInterpretationDor() const final;

		DLL_IMPORT_OR_EXPORT void setBoundaryFeatureInterpretation(RESQML2_NS::BoundaryFeatureInterpretation* interp) final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlNamespace() const { return XML_NS; }
	};
}
