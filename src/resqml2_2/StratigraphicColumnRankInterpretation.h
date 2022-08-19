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

namespace RESQML2_2_NS
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
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt>.
		 *
		 * @param [in]	orgFeat				The feature the instance interprets. It must be a
		 * 									stratigraphic organization feature.
		 * @param 	  	guid				The guid to set to the interpretation. If empty then a new
		 * 									guid will be generated.
		 * @param 	  	title				A title for the instance to create.
		 * @param 	  	rank				The rank index of this interpretation within a stratigraphic
		 * 									column.
		 * @param 	  	orderingCriteria	How the included horizons are ordered.
		 */
		StratigraphicColumnRankInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title, unsigned long rank, gsoap_resqml2_0_1::resqml20__OrderingCriteria orderingCriteria);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/

		StratigraphicColumnRankInterpretation(gsoap_eml2_3::_resqml22__StratigraphicColumnRankInterpretation* fromGsoap) : RESQML2_NS::StratigraphicColumnRankInterpretation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~StratigraphicColumnRankInterpretation() = default;

		DLL_IMPORT_OR_EXPORT void pushBackStratiUnitInterpretation(RESQML2_NS::StratigraphicUnitInterpretation * stratiUnitInterpretation) final;

		DLL_IMPORT_OR_EXPORT void setHorizonOfLastContact(RESQML2_NS::HorizonInterpretation * partOf) final;

		DLL_IMPORT_OR_EXPORT void pushBackStratigraphicBinaryContact(RESQML2_NS::StratigraphicUnitInterpretation* subject, gsoap_eml2_3::resqml22__ContactMode subjectContactMode,
			RESQML2_NS::StratigraphicUnitInterpretation* directObject, gsoap_eml2_3::resqml22__ContactMode directObjectMode,
			RESQML2_NS::HorizonInterpretation * partOf = nullptr) final;

		DLL_IMPORT_OR_EXPORT bool isAChronoStratiRank() const final;

		DLL_IMPORT_OR_EXPORT uint64_t getContactCount() const final;

		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::resqml22__ContactMode getSubjectContactModeOfContact(uint64_t contactIndex) const final;

		DLL_IMPORT_OR_EXPORT RESQML2_NS::StratigraphicUnitInterpretation* getSubjectOfContact(uint64_t contactIndex) const final;

		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::resqml22__ContactMode getDirectObjectContactModeOfContact(uint64_t contactIndex) const final;

		DLL_IMPORT_OR_EXPORT RESQML2_NS::StratigraphicUnitInterpretation* getDirectObjectOfContact(uint64_t contactIndex) const final;

		DLL_IMPORT_OR_EXPORT RESQML2_NS::HorizonInterpretation* getHorizonInterpretationOfContact(uint64_t contactIndex) const final;

		DLL_IMPORT_OR_EXPORT uint64_t getStratigraphicUnitInterpretationCount() const final;

		COMMON_NS::DataObjectReference getStratigraphicUnitInterpretationDor(uint64_t index) const final;

		DLL_IMPORT_OR_EXPORT uint64_t getHorizonInterpretationCount() const final;

		COMMON_NS::DataObjectReference getHorizonInterpretationDor(uint64_t index) const final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "resqml22";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
