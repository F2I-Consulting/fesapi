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
#include "resqml2_0_1/StratigraphicColumn.h"
#include "resqml2_0_1/StratigraphicOccurrenceInterpretation.h"

namespace RESQML2_0_1_NS
{
	/**
	* This class is a container for other organizations that are consistent to each others.
	*/
	class DLL_IMPORT_OR_EXPORT StratigraphicColumnRankInterpretation : public AbstractStratigraphicOrganizationInterpretation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		StratigraphicColumnRankInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractStratigraphicOrganizationInterpretation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param orgFeat			The feature the instance interprets. It must be a stratigraphic organization feature.
		* @param guid				The guid to set to the interpretation. If empty then a new guid will be generated.
		* @param title				A title for the instance to create.
		* @param rank				The rank index of this interpretation within a stratigraphic column
		* @param orderingCriteria	How the included horizons are ordered.
		*/
		StratigraphicColumnRankInterpretation(class OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank, const gsoap_resqml2_0_1::resqml2__OrderingCriteria & orderingCriteria);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/

		StratigraphicColumnRankInterpretation(gsoap_resqml2_0_1::_resqml2__StratigraphicColumnRankInterpretation* fromGsoap) : AbstractStratigraphicOrganizationInterpretation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~StratigraphicColumnRankInterpretation() {}

		/**
        * Add a StratiUnitInterp to this StratigraphicColumnRankInterpretation.
        * Does add the inverse relationship i.e. from the included StratiUnitInterp to this StratigraphicColumnRankInterpretation.
        */
        void pushBackStratiUnitInterpretation(class StratigraphicUnitInterpretation * stratiUnitInterpretation);
		
		void setHorizonOfLastContact(class HorizonInterpretation * partOf);

		/**
		 * Add a stratigraphic binary contact to the organization interpretation.
		 */
		void pushBackStratigraphicBinaryContact(StratigraphicUnitInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactMode & subjectContactMode,
			StratigraphicUnitInterpretation* directObject, const gsoap_resqml2_0_1::resqml2__ContactMode & directObjectMode,
			class HorizonInterpretation * partOf = nullptr);

		/**
		* Indicates if this strati column rank interp is wether a chrono one or not.
		* One of the consequence is that in a chrono strati column rank interp, each strati unit interp have only one top and only one bottom.
		*/
		bool isAChronoStratiRank() const;

		/**
		* Get the count of contacts in this strati column rank interp.
		*/
		unsigned int getContactCount() const;

		/**
		* Get the contact mode between the subject strati unit and the contact located at a particular index.
		* Most of time the subject strati unit is the strati unit on top of the contact.
		* @return	proportional contact mode by default or the contact mode of the subject.
		*/
		gsoap_resqml2_0_1::resqml2__ContactMode getSubjectContactModeOfContact(const unsigned int & contactIndex) const;

		/**
		* Get the strati unt interpretation which is the subject of a particular contact.
		*/
		class StratigraphicUnitInterpretation* getSubjectOfContact(const unsigned int & contactIndex) const;

		/**
		* Get the contact mode between the direct object strati unit and the contact located at a particular index.
		* Most of time the subject strati unit is the strati unit below the contact.
		* @return	proportional contact mode by default or the contact mode of the direct object.
		*/
		gsoap_resqml2_0_1::resqml2__ContactMode getDirectObjectContactModeOfContact(const unsigned int & contactIndex) const;

		/**
		* Get the strati unt interpretation which is the direct object of a particular contact.
		*/
		class StratigraphicUnitInterpretation* getDirectObjectOfContact(const unsigned int & contactIndex) const;

		/**
		* Get the horizon interpretation which is the contact between two strati units.
		*/
		class HorizonInterpretation* getHorizonInterpretationOfContact(const unsigned int & contactIndex) const;

		/**
		* Get all the stratigraphic unit interpretations contained in this StratigraphicColumnRankInterpretation.
		*/
		const std::vector<class StratigraphicUnitInterpretation*> & getStratigraphicUnitInterpretationSet() const;

		/**
		* Get all the stratigraphic occurence interpretations associated with this StratigraphicColumnRankInterpretation.
		*/
		const std::vector<class StratigraphicOccurrenceInterpretation*> & getStratigraphicOccurrenceInterpretationSet() const;

		/**
		* Get all the horizon interpretations contained in this StratigraphicColumnRankInterpretation.
		*/
		const std::vector<class HorizonInterpretation*> & getHorizonInterpretationSet() const;

		/**
		* Get all the stratigraphic column this strati column rank belongs to.
		*/
		const std::vector<StratigraphicColumn*> & getStratigraphicColumnSet() const;

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	private:

        std::vector<epc::Relationship> getAllEpcRelationships() const;	
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);

        // forward relationships
        std::vector<class StratigraphicUnitInterpretation*> stratigraphicUnitSet;
        std::vector<class HorizonInterpretation*> horizonInterpretationSet;

		// Backward relationship
		std::vector<StratigraphicColumn *> stratigraphicColumnSet;
		std::vector<StratigraphicOccurrenceInterpretation *> stratigraphicOccurrenceInterpretationSet;

		friend void StratigraphicColumn::pushBackStratiColumnRank(StratigraphicColumnRankInterpretation * stratiColumnRank);
		friend void StratigraphicOccurrenceInterpretation::setStratigraphicColumnRankInterpretation(StratigraphicColumnRankInterpretation * stratiColumnRankInterp);
	};
}

