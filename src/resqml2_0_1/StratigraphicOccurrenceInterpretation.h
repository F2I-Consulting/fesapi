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

#include "resqml2_0_1/AbstractStratigraphicOrganizationInterpretation.h"
#include "resqml2_0_1/EarthModelInterpretation.h"
#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"

namespace RESQML2_0_1_NS
{
	/**
	* This class is a container for other organizations that are consistent to each others.
	*/
	class DLL_IMPORT_OR_EXPORT StratigraphicOccurrenceInterpretation : public AbstractStratigraphicOrganizationInterpretation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		StratigraphicOccurrenceInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			AbstractStratigraphicOrganizationInterpretation(partialObject),
			stratigraphicColumnRankInterpretation(nullptr) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param orgFeat	The feature the instance interprets. It must be a stratigraphic organization feature.
		* @param guid		The guid to set to the interpretation. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		*/
		StratigraphicOccurrenceInterpretation(class OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__OrderingCriteria & orderingCriteria);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		StratigraphicOccurrenceInterpretation(gsoap_resqml2_0_1::_resqml2__StratigraphicOccurrenceInterpretation* fromGsoap) : AbstractStratigraphicOrganizationInterpretation(fromGsoap), stratigraphicColumnRankInterpretation(nullptr) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~StratigraphicOccurrenceInterpretation() {}

		void setStratigraphicColumnRankInterpretation(class StratigraphicColumnRankInterpretation * stratiColumnRankInterp);

		class StratigraphicColumnRankInterpretation * getStratigraphicColumnRankInterpretation() const {return stratigraphicColumnRankInterpretation;}

		/**
		* Get all the stratigraphic occurence interpretations associated with this StratigraphicColumnRankInterpretation.
		*/
		std::vector<class WellboreMarkerFrameRepresentation*> getWellboreMarkerFrameRepresentationSet() const { return wellboreMarkerFrameRepresentationSet; }

		std::string getStratigraphicColumnRankInterpretationUuid() const;
                
		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

        std::vector<epc::Relationship> getAllSourceRelationships() const;
        std::vector<epc::Relationship> getAllTargetRelationships() const;
	private:
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);

		// Forward relationship
		class StratigraphicColumnRankInterpretation * stratigraphicColumnRankInterpretation;

		// Backward relationship
		std::vector<EarthModelInterpretation *> earthModelSet;
		std::vector<WellboreMarkerFrameRepresentation *> wellboreMarkerFrameRepresentationSet;

		friend void EarthModelInterpretation::pushBackStratiOccurence(StratigraphicOccurrenceInterpretation * stratiOccurence);
		friend void WellboreMarkerFrameRepresentation::setStratigraphicOccurrenceInterpretation(StratigraphicOccurrenceInterpretation * stratiOccurenceInterp);
	};
}

