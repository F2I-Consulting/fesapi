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

#include "../resqml2/AbstractStratigraphicOrganizationInterpretation.h"

namespace RESQML2_NS
{
	class StratigraphicColumnRankInterpretation;
	class WellboreMarkerFrameRepresentation;

	/** @brief	This class is a container for stratigraphic organizations described along a wellbore. */
	class GeologicUnitOccurrenceInterpretation : public AbstractStratigraphicOrganizationInterpretation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~GeologicUnitOccurrenceInterpretation() = default;

		/**
		 * Sets the stratigraphic column rank interpretation this stratigraphic occurrence
		 * interpretation is an occurrence of.
		 *
		 * @exception	std::invalid_argument	If @p stratiColumnRankInterp is @c nullptr.
		 *
		 * @param [in]	stratiColumnRankInterp	The stratigraphic column rank interpretation this
		 * 										stratigraphic occurrence interpretation is an occurrence
		 * 										of.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setStratigraphicColumnRankInterpretation(StratigraphicColumnRankInterpretation * stratiColumnRankInterp) = 0;

		/**
		 * Gets the stratigraphic column rank interpretation this stratigraphic occurrence
		 * interpretation is an occurrence of.
		 *
		 * @returns	@c nullptr if no stratigraphic column rank interpretation is associated to this
		 * 			stratigraphic occurrence interpretation, else the associated stratigraphic column
		 * 			rank interpretation.
		 */
		DLL_IMPORT_OR_EXPORT StratigraphicColumnRankInterpretation * getStratigraphicColumnRankInterpretation() const;

		GETTER_DATAOBJECTS(WellboreMarkerFrameRepresentation, WellboreMarkerFrameRepresentation)

		/**
		 * Gets the data object reference of the stratigraphic column rank interpretation this
		 * stratigraphic occurrence interpretation is an occurrence of.
		 *
		 * @returns	Empty data object reference if no stratigraphic column rank interpretation is
		 * 			associated to this stratigraphic occurrence interpretation, else the data object
		 * 			reference of the associated stratigraphic column rank interpretation.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getStratigraphicColumnRankInterpretationDor() const = 0;

	protected:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT GeologicUnitOccurrenceInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractStratigraphicOrganizationInterpretation(partialObject) {}

		/**
		* Defautl constructor
		*/
		GeologicUnitOccurrenceInterpretation() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		GeologicUnitOccurrenceInterpretation(gsoap_resqml2_0_1::_resqml20__StratigraphicOccurrenceInterpretation* fromGsoap) : AbstractStratigraphicOrganizationInterpretation(fromGsoap) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		GeologicUnitOccurrenceInterpretation(gsoap_eml2_3::_resqml22__GeologicUnitOccurrenceInterpretation* fromGsoap) : AbstractStratigraphicOrganizationInterpretation(fromGsoap) {}

		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
