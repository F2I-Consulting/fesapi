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

/** @brief */
namespace RESQML2_0_1_NS
{
	class WellboreMarkerFrameRepresentation;

	/**
	 * Proxy class for a wellbore marker. This class is one of the only one to be a RESQML data
	 * object which is not exported into a single file i.e. it is not a top level element.
	 * Consequently its behaviour is slightly different than other class. Especially there is no
	 * integration of the instances into an EPC document.
	 */
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

		/**
		 * Indicates if the marker is associated to a particular geologic boundary kind.
		 *
		 * @returns	True if the marker is associated to a particular geologic boundary kind, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasAGeologicBoundaryKind() const final;

		/**
		 * Gets the type of the intersected feature of the marker.
		 *
		 * @exception	std::invalid_argument	If the marker has no geologic boundary kind (see method
		 * 										hasAGeologicBoundaryKind()).
		 *
		 * @returns	The geologic boundary kind associated to this marker.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind getGeologicBoundaryKind() const final;

		/**
		 * Gets the UUID of the boundary feature interpretation linked to this well marker. Especially
		 * useful in partial transfer mode.
		 *
		 * @returns	The boundary feature interpretation UUID, or empty string if it fails.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getBoundaryFeatureInterpretationDor() const final;

		/**
		 * Sets the boundary feature interpretation linked to this well marker.
		 *
		 * @exception	std::invalid_argument	If @p interp is @c nullptr.
		 *
		 * @param [in]	interp	The boundary feature interpretation to link to this well marker. It
		 * 						cannot be null.
		 */
		DLL_IMPORT_OR_EXPORT void setBoundaryFeatureInterpretation(RESQML2_NS::BoundaryFeatureInterpretation* interp) final;
	};
}
