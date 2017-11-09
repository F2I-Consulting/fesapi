/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#pragma once

#include "resqml2_0_1/AbstractStratigraphicOrganizationInterpretation.h"
#include "resqml2_0_1/StratigraphicColumn.h"
#include "resqml2_0_1/StratigraphicOccurrenceInterpretation.h"

namespace resqml2_0_1
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
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

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
