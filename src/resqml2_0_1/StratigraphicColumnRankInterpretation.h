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

#include "../resqml2/StratigraphicColumnRankInterpretation.h"

namespace RESQML2_0_1_NS
{
	/**
	* This class is a container for other organizations that are consistent to each others.
	*/
	class StratigraphicColumnRankInterpretation final : public RESQML2_NS::StratigraphicColumnRankInterpretation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT StratigraphicColumnRankInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::StratigraphicColumnRankInterpretation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param orgFeat			The feature the instance interprets. It must be a stratigraphic organization feature.
		* @param guid				The guid to set to the interpretation. If empty then a new guid will be generated.
		* @param title				A title for the instance to create.
		* @param rank				The rank index of this interpretation within a stratigraphic column
		* @param orderingCriteria	How the included horizons are ordered.
		*/
		StratigraphicColumnRankInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title, unsigned long rank, gsoap_resqml2_0_1::resqml20__OrderingCriteria orderingCriteria);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/

		StratigraphicColumnRankInterpretation(gsoap_resqml2_0_1::_resqml20__StratigraphicColumnRankInterpretation* fromGsoap) : RESQML2_NS::StratigraphicColumnRankInterpretation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~StratigraphicColumnRankInterpretation() {}

		/**
		 * Add a StratiUnitInterp to this StratigraphicColumnRankInterpretation. Does add the inverse
		 * relationship i.e. from the included StratiUnitInterp to this
		 * StratigraphicColumnRankInterpretation.
		 *
		 * @param [in,out]	stratiUnitInterpretation	If non-null, the strati unit interpretation.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackStratiUnitInterpretation(RESQML2_NS::StratigraphicUnitInterpretation * stratiUnitInterpretation) final;

		/**
		 * Sets horizon of last contact
		 *
		 * @param [in,out]	partOf	If non-null, the part of.
		 */
		DLL_IMPORT_OR_EXPORT void setHorizonOfLastContact(RESQML2_NS::HorizonInterpretation * partOf) final;

		/**
		 * Add a stratigraphic binary contact to the organization interpretation.
		 *
		 * @param [in,out]	subject			  	If non-null, the subject.
		 * @param 		  	subjectContactMode	The subject contact mode.
		 * @param [in,out]	directObject	  	If non-null, the direct object.
		 * @param 		  	directObjectMode  	The direct object mode.
		 * @param [in,out]	partOf			  	(Optional) If non-null, the part of.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackStratigraphicBinaryContact(RESQML2_NS::StratigraphicUnitInterpretation* subject, gsoap_eml2_3::resqml22__ContactMode subjectContactMode,
			RESQML2_NS::StratigraphicUnitInterpretation* directObject, gsoap_eml2_3::resqml22__ContactMode directObjectMode,
			RESQML2_NS::HorizonInterpretation * partOf = nullptr) final;

		/**
		 * Indicates if this strati column rank interp is wether a chrono one or not. One of the
		 * consequence is that in a chrono strati column rank interp, each strati unit interp have only
		 * one top and only one bottom.
		 *
		 * @returns	True if a chrono strati rank, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAChronoStratiRank() const final;

		/**
		 * Get the count of contacts in this strati column rank interp.
		 *
		 * @returns	The contact count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getContactCount() const final;

		/**
		 * Get the contact mode between the subject strati unit and the contact located at a particular
		 * index. Most of time the subject strati unit is the strati unit on top of the contact.
		 *
		 * @param 	contactIndex	Zero-based index of the contact.
		 *
		 * @returns	proportional contact mode by default or the contact mode of the subject.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::resqml22__ContactMode getSubjectContactModeOfContact(unsigned int contactIndex) const final;

		/** Get the strati unt interpretation which is the subject of a particular contact. */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::StratigraphicUnitInterpretation* getSubjectOfContact(unsigned int contactIndex) const final;

		/**
		 * Get the contact mode between the direct object strati unit and the contact located at a
		 * particular index. Most of time the subject strati unit is the strati unit below the contact.
		 *
		 * @param 	contactIndex	Zero-based index of the contact.
		 *
		 * @returns	proportional contact mode by default or the contact mode of the direct object.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::resqml22__ContactMode getDirectObjectContactModeOfContact(unsigned int contactIndex) const final;

		/** Get the strati unt interpretation which is the direct object of a particular contact. */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::StratigraphicUnitInterpretation* getDirectObjectOfContact(unsigned int contactIndex) const final;

		/** Get the horizon interpretation which is the contact between two strati units. */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::HorizonInterpretation* getHorizonInterpretationOfContact(unsigned int contactIndex) const final;

		/**
		 * Get the count of all the stratigraphic unit interpretations which are contained in this
		 * stratigraphic column rank.
		 *
		 * @returns	the count of all the stratigraphic unit interpretations which are contained in this stratigraphic column rank.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getStratigraphicUnitInterpretationCount() const final;

		/**
		 * Get a stratigraphic unit interpretations DOR at a particular index.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getStratigraphicUnitInterpretationDor(unsigned int index) const final;

		/**
		 * Get the count of all the Horizon interpretations which are contained in this
		 * stratigraphic column rank.
		 *
		 * @returns	the count of all the Horizon interpretations which are contained in this stratigraphic column rank.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getHorizonInterpretationCount() const final;

		/**
		 * Get a Horizon interpretations DOR at a particular index.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getHorizonInterpretationDor(unsigned int index) const final;
	};
}
