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

#include "../resqml2/WellboreMarkerFrameRepresentation.h"

#include "WellboreMarker.h"

/** . */
namespace RESQML2_0_1_NS
{
	/** Proxy class for a wellbore marker frame representation. */
	class WellboreMarkerFrameRepresentation final : public RESQML2_NS::WellboreMarkerFrameRepresentation
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT WellboreMarkerFrameRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			RESQML2_NS::WellboreMarkerFrameRepresentation(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If @p interp of @p traj is @c nullptr.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the wellbore marker frame representation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title 	The title to set to the wellbore marker frame representation. If empty
		 * 						then \"unknown\" title will be set.
		 * @param [in]	traj  	The wellbore trajectory that refers this wellbore marker frame. It cannot
		 * 						be null.
		 */
		WellboreMarkerFrameRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, RESQML2_NS::WellboreTrajectoryRepresentation* traj);

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		WellboreMarkerFrameRepresentation(gsoap_resqml2_0_1::_resqml20__WellboreMarkerFrameRepresentation* fromGsoap) : RESQML2_NS::WellboreMarkerFrameRepresentation(fromGsoap) {}

		/** Cleans the owned markers. */
		~WellboreMarkerFrameRepresentation() {}

		/**
		 * Gets the number of wellbore marker of this wellbore marker frame representation.
		 *
		 * @returns	The wellbore marker count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getWellboreMarkerCount() final;

		/**
		 * Sets stratigraphic occurrence interpretation associated to this wellbore marker frame
		 * representation.
		 *
		 * @exception	std::invalid_argument	If @p stratiOccurenceInterp is @c nullptr.
		 *
		 * @param [in]	stratiOccurenceInterp	The stratigraphic occurrence interpretation to set.
		 */
		DLL_IMPORT_OR_EXPORT void setStratigraphicOccurrenceInterpretation(RESQML2_NS::StratigraphicOccurrenceInterpretation * stratiOccurenceInterp) final;

		/**
		 * Sets the correspondence between the intervals of this wellbore marker frame representation
		 * and the units of a stratigraphic column rank interpretation of a stratigraphic occurrence
		 * interpretation.
		 *
		 * @exception	std::invalid_argument	If @p stratiUnitIndices, @p stratiOccurenceInterp or @p
		 * 										proxy is @c nullptr.
		 *
		 * @param [in]	  	stratiUnitIndices	 	The index of the stratigraphic unit per interval, of
		 * 											a given stratigraphic column. The count must be equal
		 * 											to the count of wellbore marker intervals
		 * 											(getWellboreMarkerCount() <tt> - 1
		 * 											</tt>).
		 * @param 		  	nullValue			 	The value which is used to tell that there is no
		 * 											correspondence between stratigraphic units and a
		 * 											particular interval (e.g., within salt, use this null
		 * 											value).
		 * @param [in]	  	stratiOccurenceInterp	The stratigraphic occurrence interpretation to
		 * 											associate to this wellbore marker frame
		 * 											representation.
		 * @param [in,out]	proxy				 	The HDF proxy where the numerical values (indices)
		 * 											are stored.
		 */
		DLL_IMPORT_OR_EXPORT void setIntervalStratigraphicUnits(unsigned int const* stratiUnitIndices, unsigned int nullValue, RESQML2_NS::StratigraphicOccurrenceInterpretation* stratiOccurenceInterp, EML2_NS::AbstractHdfProxy* proxy) final;

		/** A stratigraphic occurrence interpretation*. */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getStratigraphicOccurrenceInterpretationDor() const final;

	private:

		void loadTargetRelationships() final;

		/**
		 * Pushes back a new WellboreFeature marker to this WellboreFeature marker frame. One
		 * WellboreFeature marker must be added per MD of the WellboreFeature marker frame.
		 *
		 * @param [in,out]	marker	If non-null, the marker.
		 */
		void pushBackNewWellboreMarker(RESQML2_0_1_NS::WellboreMarker * marker);

		/**
		 * Wellbore marker
		 *
		 * @param [in,out]	wellboreMarkerFrame	If non-null, the wellbore marker frame.
		 * @param 		  	guid			   	Unique identifier.
		 * @param 		  	title			   	The title.
		 *
		 * @returns	A friend.
		 */
		friend WellboreMarker::WellboreMarker(RESQML2_0_1_NS::WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title);

		/**
		 * Wellbore marker
		 *
		 * @param [in,out]	wellboreMarkerFrame 	If non-null, the wellbore marker frame.
		 * @param 		  	guid					Unique identifier.
		 * @param 		  	title					The title.
		 * @param 		  	geologicBoundaryKind	The geologic boundary kind.
		 *
		 * @returns	A friend.
		 */
		friend WellboreMarker::WellboreMarker(RESQML2_0_1_NS::WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind geologicBoundaryKind);
	};
}
