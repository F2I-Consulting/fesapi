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

namespace RESQML2_NS
{
	class HorizonInterpretation;
	class StratigraphicColumn;
	class StratigraphicOccurrenceInterpretation;
}

/** . */
namespace RESQML2_NS
{
	class StratigraphicUnitInterpretation;

	/**
	* A stratigraphic column rank interpretation is a global hierarchy containing an ordered list of stratigraphic unit interpretations.

	*/
	class StratigraphicColumnRankInterpretation : public AbstractStratigraphicOrganizationInterpretation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~StratigraphicColumnRankInterpretation() {}

		/**
		 * Adds a stratigraphic unit interpretation to this stratigraphic column rank interpretation.
		 * Does add the inverse relationship i.e. from the included stratigraphic unit interpretation to
		 * this stratigraphic column rank interpretation.
		 *
		 * @exception	std::invalid_argument	If @p stratiUnitInterpretation is @c nullptr.
		 *
		 * @param [in]	stratiUnitInterpretation	The stratigraphic unit interpretation to add.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackStratiUnitInterpretation(StratigraphicUnitInterpretation * stratiUnitInterpretation) = 0;

		/**
		 * Sets the horizon interpretation that contains the last (the one with the greater index)
		 * contact interpretation within the list of contact interpretation associated to this
		 * stratigraphic column rank interpretation.
		 *
		 * @exception	std::invalid_argument	If @p partOf is @c nullptr.
		 *
		 * @param [in]	partOf	The horizon interpretation that contains the last contact interpretation.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setHorizonOfLastContact(HorizonInterpretation * partOf) = 0;

		/**
		 * Adds a stratigraphic binary "stops" contact to this stratigraphic column rank interpretation.
		 *
		 * @exception	std::invalid_argument	If @p subject or @p directObject is @c nullptr.
		 *
		 * @param [in]	subject			  	The subject of the sentence that defines how the contact was
		 * 									constructed.
		 * @param 	  	subjectContactMode	The subject contact mode (baselap, erosion, extended or
		 * 									proportional).
		 * @param [in]	directObject	  	The direct object of the sentence that defines how the
		 * 									contact was constructed.
		 * @param 	  	directObjectMode  	The direct object contact mode (baselap, erosion, extended or
		 * 									proportional).
		 * @param [in]	partOf			  	(Optional) If non-null, the horizon interpretation that
		 * 									contains this new binary contact. Default value is @c nullptr.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackStratigraphicBinaryContact(StratigraphicUnitInterpretation* subject, gsoap_resqml2_0_1::resqml20__ContactMode subjectContactMode,
			StratigraphicUnitInterpretation* directObject, gsoap_resqml2_0_1::resqml20__ContactMode directObjectMode,
			HorizonInterpretation * partOf = nullptr) = 0;

		/**
		 * Indicates whether this stratigraphic column rank interpretation is a chrono one (it is
		 * ordered by ages) or not. One of the consequence is that in a chrono stratigraphic column rank
		 * interpretation, each stratigraphic unit interpretation have only one top and only one bottom.
		 *
		 * @returns	True if is a chrono stratigraphic column rank, false if it is not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isAChronoStratiRank() const = 0;

		/**
		 * Gets the count of contacts in this stratigraphic column rank interpretation.
		 *
		 * @returns	The contact count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getContactCount() const = 0;

		/**
		 * Gets the contact mode of the subject stratigraphic unit of a contact located at a particular
		 * index. Most of time the subject stratigraphic unit is the stratigraphic unit on top of the
		 * contact.
		 *
		 * @exception	std::out_of_range	If @p contactIndex is out of range.
		 *
		 * @param 	contactIndex	Zero-based index of the contact for which we look for the contact
		 * 							mode of the subject stratigraphic unit.
		 *
		 * @returns	Proportional contact mode by default (if no contact mode is associated to the subject
		 * 			stratigraphic unit) or the contact mode of the subject stratigraphic unit.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::resqml20__ContactMode getSubjectContactModeOfContact(unsigned int contactIndex) const = 0;

		/** Gets the stratigraphic unit interpretation which is the subject of a particular contact.
		 *
		 * @exception std::out_of_range	If @p contactIndex is out of range.
		 * 								
		 * @param 	contactIndex	Zero-based index of the contact for which we look for the subject 
		 * 							stratigraphic unit interpretation.
		 * 							
		 * @returns The subject stratigraphic unit interpretation of the contact at position @p contactIndex
		 * 			if it exists, else @c nullptr.
		 */
		DLL_IMPORT_OR_EXPORT virtual class StratigraphicUnitInterpretation* getSubjectOfContact(unsigned int contactIndex) const = 0;

		/**
		 * Gets the contact mode of the direct object stratigraphic unit of a contact located at a
		 * particular index. Most of time the direct object stratigraphic unit is the stratigraphic unit
		 * below the contact.
		 *
		 * @param 	contactIndex	Zero-based index of the contact for which we look for the contact
		 * 							mode of the direct object stratigraphic unit.
		 *
		 * @returns	Proportional contact mode by default (if no contact mode is associated to the direct
		 * 			object stratigraphic unit) or the contact mode of the direct object stratigraphic
		 * 			unit.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::resqml20__ContactMode getDirectObjectContactModeOfContact(unsigned int contactIndex) const = 0;

		/** Gets the stratigraphic unit interpretation which is the direct object of a particular contact.
		 *
		 * @exception std::out_of_range	If @p contactIndex is out of range.
		 *
		 * @param 	contactIndex	Zero-based index of the contact for which we look for the direct
		 * 							object stratigraphic unit interpretation.
		 *
		 * @returns The direct object stratigraphic unit interpretation of the contact at position 
		 * 			@p contactIndex if it exists, else @c nullptr.
		 */
		DLL_IMPORT_OR_EXPORT virtual StratigraphicUnitInterpretation* getDirectObjectOfContact(unsigned int contactIndex) const = 0;

		/**
		 * Gets the horizon interpretation which is the contact between two stratigraphic units.
		 *
		 * @exception	std::out_of_range	If @p contactIndex is out of range.
		 *
		 * @param 	contactIndex	Zero-based index of the contact for which we want to get the
		 * 							corresponding horizon interpretation.
		 *
		 * @returns	@c nullptr if the horizon corresponding to the contact at position @p contactIndex is
		 * 			unknown, else the corresponding horizon interpretation.
		 */
		DLL_IMPORT_OR_EXPORT virtual HorizonInterpretation* getHorizonInterpretationOfContact(unsigned int contactIndex) const = 0;

		/**
		 * Gets the count of all the stratigraphic unit interpretations which are contained in this
		 * stratigraphic column rank.
		 *
		 * @returns	The count of all the stratigraphic unit interpretations which are contained in this
		 * 			stratigraphic column rank.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getStratigraphicUnitInterpretationCount() const = 0;

		/**
		 * Gets the data object reference of the stratigraphic unit interpretations at a particular
		 * index.
		 *
		 * @exception	std::out_of_range	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the stratigraphic unit interpretation we look for the
		 * 					data object reference.
		 *
		 * @returns	The data object reference of the stratigraphic unit interpretation at position @p
		 * 			index.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getStratigraphicUnitInterpretationDor(unsigned int index) const = 0;

		/**
		 * Gets all the stratigraphic unit interpretations contained in this stratigraphic column rank
		 * interpretation.
		 *
		 * @returns	A vector of pointers to all the stratigraphic unit interpretations contained in this
		 * 			stratigraphic column rank interpretation.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<StratigraphicUnitInterpretation *> getStratigraphicUnitInterpretationSet() const;

		/**
		 * Gets all the stratigraphic occurrence interpretations associated with this stratigraphic
		 * column rank interpretation.
		 *
		 * @returns	A vector of pointers to all the stratigraphic occurrence interpretations associated
		 * 			with this stratigraphic column rank interpretation.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<StratigraphicOccurrenceInterpretation *> getStratigraphicOccurrenceInterpretationSet() const;

		/**
		 * Gets the count of all the contact horizon interpretations which are contained in this
		 * stratigraphic column rank.
		 *
		 * @returns	The count of all the contact horizon interpretations which are contained in this
		 * 			stratigraphic column rank.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getHorizonInterpretationCount() const = 0;

		/**
		 * Gets the data object reference of a contact horizon interpretation at a particular index.
		 *
		 * @exception	std::out_of_range	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the contact horizon interpretation we look for the data
		 * 					object reference.
		 *
		 * @returns	The data object reference of the contact horizon interpretation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getHorizonInterpretationDor(unsigned int index) const = 0;

		/**
		 * Gets all the horizon interpretations contained in this stratigraphic column rank
		 * interpretation.
		 *
		 * @returns	A vector of pointers to all the horizon interpretations contained in this
		 * 			stratigraphic column rank interpretation.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<HorizonInterpretation *> getHorizonInterpretationSet() const;

		/**
		 * Gets all the stratigraphic columns this stratigraphic column rank belongs to.
		 *
		 * @returns	A vector of pointers to all the stratigraphic columns this stratigraphic column rank
		 * 			belongs to.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<StratigraphicColumn *> getStratigraphicColumnSet() const;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const override { return XML_TAG; }

	protected :

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT StratigraphicColumnRankInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractStratigraphicOrganizationInterpretation(partialObject) {}

		/**
		* Default constructor
		*/
		StratigraphicColumnRankInterpretation() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		StratigraphicColumnRankInterpretation(gsoap_resqml2_0_1::_resqml20__StratigraphicColumnRankInterpretation* fromGsoap) : AbstractStratigraphicOrganizationInterpretation(fromGsoap) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		StratigraphicColumnRankInterpretation(gsoap_eml2_3::_resqml22__StratigraphicColumnRankInterpretation* fromGsoap) : AbstractStratigraphicOrganizationInterpretation(fromGsoap) {}

		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
