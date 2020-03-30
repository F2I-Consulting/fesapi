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

/** . */
namespace RESQML2_NS
{
	class StratigraphicColumnRankInterpretation;
	class WellboreMarkerFrameRepresentation;

	/**
	* This class is a container for stratigraphic organizations described along a wellbore.
	*/
	class StratigraphicOccurrenceInterpretation : public RESQML2_NS::AbstractStratigraphicOrganizationInterpretation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~StratigraphicOccurrenceInterpretation() {}

		/**
		 * Sets stratigraphic column rank interpretation
		 *
		 * @param [in,out]	stratiColumnRankInterp	If non-null, the strati column rank interp.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setStratigraphicColumnRankInterpretation(StratigraphicColumnRankInterpretation * stratiColumnRankInterp) = 0;

		/** A stratigraphic column rank interpretation*. */
		DLL_IMPORT_OR_EXPORT StratigraphicColumnRankInterpretation * getStratigraphicColumnRankInterpretation() const;

		/**
		 * Get all the stratigraphic occurence interpretations associated with this
		 * StratigraphicColumnRankInterpretation.
		 *
		 * @returns	Null if it fails, else the wellbore marker frame representation set.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<WellboreMarkerFrameRepresentation *> getWellboreMarkerFrameRepresentationSet() const;

		/**
		 * Gets stratigraphic column rank interpretation uuid
		 *
		 * @returns	The stratigraphic column rank interpretation uuid.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getStratigraphicColumnRankInterpretationDor() const = 0;

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

	protected:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT StratigraphicOccurrenceInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractStratigraphicOrganizationInterpretation(partialObject) {}

		/**
		* Defautl constructor
		*/
		StratigraphicOccurrenceInterpretation() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		StratigraphicOccurrenceInterpretation(gsoap_resqml2_0_1::_resqml20__StratigraphicOccurrenceInterpretation* fromGsoap) : AbstractStratigraphicOrganizationInterpretation(fromGsoap) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		StratigraphicOccurrenceInterpretation(gsoap_eml2_3::_resqml22__StratigraphicOccurrenceInterpretation* fromGsoap) : AbstractStratigraphicOrganizationInterpretation(fromGsoap) {}

		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
