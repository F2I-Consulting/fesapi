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
	* A rank of a stratigraphic column corresponds to a level of detail of the stratigraphic column.
	* First indexed ranks are coarser than last indexed ranks.
	*/
	class StratigraphicColumnRankInterpretation final : public RESQML2_NS::StratigraphicColumnRankInterpretation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT StratigraphicColumnRankInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::StratigraphicColumnRankInterpretation(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt> or if @p orgFeat is not a
		 * 										stratigraphic organization.
		 *
		 * @param [in]	orgFeat				The feature the instance interprets. It must be a
		 * 										stratigraphic organization feature.
		 * @param 	  	guid				The guid to set to the interpretation. If empty then a new
		 * 									guid will be generated.
		 * @param 	  	title				A title for the instance to create.
		 * @param 	  	rank				The rank index of this interpretation within a stratigraphic
		 * 									column.
		 * @param 	  	orderingCriteria	How the included horizons are ordered.
		 */
		StratigraphicColumnRankInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title,
			uint64_t rank, gsoap_resqml2_0_1::resqml20__OrderingCriteria ascendingOrderingCriteria);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/

		StratigraphicColumnRankInterpretation(gsoap_resqml2_0_1::_resqml20__StratigraphicColumnRankInterpretation* fromGsoap) : RESQML2_NS::StratigraphicColumnRankInterpretation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~StratigraphicColumnRankInterpretation() = default;

		/**
		 * Pushes back a stratigraphic unit interpretation to this stratigraphic column rank interpretation.
		 * The stratigraphic unit interpretation must be pushed back according to the ordering criteria of the stratigraphic column rank interpretation:
		 *  - If the (ascending) ordering criteria is age then units must be pushed back from the youngest to oldest.
		 *	- If the (ascending) ordering criteria is apparent depth then units must be pushed back from the shallowest one to the deepest one.
		 *	- If the (ascending) ordering criteria is measured depth then units must be pushed back
		 *		from the first drilled trajectory stations to the latest drilled trajectory stations of the wellbore.
		 * Remark : RESQML2.0.1 does not explicitely states that the ordering criteria is ascending but RESQML 2.2 does.
		 *
		 * @exception	std::invalid_argument	If @p stratiUnitInterpretation is @c nullptr.
		 *
		 * @param [in]	stratiUnitInterpretation	The stratigraphic unit interpretation to add.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackStratiUnitInterpretation(RESQML2_NS::StratigraphicUnitInterpretation * stratiUnitInterpretation) final;

		DLL_IMPORT_OR_EXPORT void setHorizonOfLastContact(RESQML2_NS::HorizonInterpretation * partOf) final;

		DLL_IMPORT_OR_EXPORT void pushBackStratigraphicBinaryContact(RESQML2_NS::StratigraphicUnitInterpretation* subject, gsoap_eml2_3::resqml22__ContactMode subjectContactMode,
			RESQML2_NS::StratigraphicUnitInterpretation* directObject, gsoap_eml2_3::resqml22__ContactMode directObjectMode,
			RESQML2_NS::HorizonInterpretation * partOf = nullptr) final;

		DLL_IMPORT_OR_EXPORT bool isAChronoStratiRank() const final;

		DLL_IMPORT_OR_EXPORT unsigned int getContactCount() const final;

		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::resqml22__ContactMode getSubjectContactModeOfContact(unsigned int contactIndex) const final;

		DLL_IMPORT_OR_EXPORT RESQML2_NS::StratigraphicUnitInterpretation* getSubjectOfContact(unsigned int contactIndex) const final;

		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::resqml22__ContactMode getDirectObjectContactModeOfContact(unsigned int contactIndex) const final;

		DLL_IMPORT_OR_EXPORT RESQML2_NS::StratigraphicUnitInterpretation* getDirectObjectOfContact(unsigned int contactIndex) const final;

		DLL_IMPORT_OR_EXPORT RESQML2_NS::HorizonInterpretation* getHorizonInterpretationOfContact(unsigned int contactIndex) const final;

		DLL_IMPORT_OR_EXPORT unsigned int getStratigraphicUnitInterpretationCount() const final;

		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getStratigraphicUnitInterpretationDor(unsigned int index) const final;

		DLL_IMPORT_OR_EXPORT unsigned int getHorizonInterpretationCount() const final;

		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getHorizonInterpretationDor(unsigned int index) const final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
