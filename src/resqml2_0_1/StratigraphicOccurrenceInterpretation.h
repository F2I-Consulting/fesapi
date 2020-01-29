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

#include "AbstractStratigraphicOrganizationInterpretation.h"
#include "EarthModelInterpretation.h"
#include "WellboreMarkerFrameRepresentation.h"

/** . */
namespace RESQML2_0_1_NS
{
	/** This class is a container for other organizations that are consistent to each others. */
	class StratigraphicOccurrenceInterpretation : public AbstractStratigraphicOrganizationInterpretation
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT StratigraphicOccurrenceInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractStratigraphicOrganizationInterpretation(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	orgFeat				The feature the instance interprets. It must be a
		 * 										stratigraphic organization feature.
		 * @param 		  	guid				The guid to set to the interpretation. If empty then a
		 * 										new guid will be generated.
		 * @param 		  	title				A title for the instance to create.
		 * @param 		  	orderingCriteria	The ordering criteria.
		 */
		StratigraphicOccurrenceInterpretation(class OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml20__OrderingCriteria & orderingCriteria);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		StratigraphicOccurrenceInterpretation(gsoap_resqml2_0_1::_resqml20__StratigraphicOccurrenceInterpretation* fromGsoap) : AbstractStratigraphicOrganizationInterpretation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~StratigraphicOccurrenceInterpretation() {}

		/**
		 * Sets stratigraphic column rank interpretation
		 *
		 * @param [in,out]	stratiColumnRankInterp	If non-null, the strati column rank interp.
		 */
		DLL_IMPORT_OR_EXPORT void setStratigraphicColumnRankInterpretation(class StratigraphicColumnRankInterpretation * stratiColumnRankInterp);

		/** A stratigraphic column rank interpretation*. */
		DLL_IMPORT_OR_EXPORT class StratigraphicColumnRankInterpretation * getStratigraphicColumnRankInterpretation() const;

		/**
		 * Get all the stratigraphic occurence interpretations associated with this
		 * StratigraphicColumnRankInterpretation.
		 *
		 * @returns	Null if it fails, else the wellbore marker frame representation set.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<class WellboreMarkerFrameRepresentation *> getWellboreMarkerFrameRepresentationSet() const;

		/**
		 * Gets stratigraphic column rank interpretation uuid
		 *
		 * @returns	The stratigraphic column rank interpretation uuid.
		 */
		DLL_IMPORT_OR_EXPORT std::string getStratigraphicColumnRankInterpretationUuid() const;

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

	private:
		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
