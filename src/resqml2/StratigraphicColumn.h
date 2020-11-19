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

#include "../common/AbstractObject.h"

namespace RESQML2_NS
{
	class StratigraphicColumnRankInterpretation;

	/**
	 * @brief	A global interpretation of the stratigraphy, which can be made up of several ranks of
	 * 			stratigraphic unit interpretations.
	 * 			
	 * 			BUSINESS RULE: All stratigraphic column rank interpretations that make up a
	 * 			stratigraphic column must be ordered by age.
	 */
	class StratigraphicColumn : public COMMON_NS::AbstractObject
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~StratigraphicColumn() = default;

		/**
		 * Pushes a back a stratigraphic column rank interpretation into this stratigraphic column.
		 *
		 * @exception	std::invalid_argument	If <tt>stratiColumnRank == nullptr</tt>
		 *
		 * @param [in]	stratiColumnRank	A stratigraphic column rank interpretation.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackStratiColumnRank(StratigraphicColumnRankInterpretation * stratiColumnRank) = 0;

		/**
		 * Gets the count of all the stratigraphic column rank interpretations which are contained in
		 * this stratigraphic column.
		 *
		 * @returns	The count of all the stratigraphic column rank interpretations which are contained in
		 * 			this stratigraphic column.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getStratigraphicColumnRankInterpretationCount() const = 0;

		/**
		 * Gets the DOR of a stratigraphic column rank interpretations at a particular index.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=
		 * 									getStratigraphicColumnRankInterpretationCount()</tt>.
		 *
		 * @param 	index	Zero-based index of the stratigraphic column rank interpretations.
		 *
		 * @returns	The DOR of the stratigraphic column rank interpretation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getStratigraphicColumnRankInterpretationDor(unsigned int index) const = 0;

		/**
		 * Gets the stratigraphic column rank interpretations at a particular index.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=
		 * 									getStratigraphicColumnRankInterpretationCount()</tt>.
		 *
		 * @param 	index	Zero-based index of the stratigraphic column rank interpretations.
		 *
		 * @returns	The stratigraphic column rank interpretation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT StratigraphicColumnRankInterpretation* getStratigraphicColumnRankInterpretation(unsigned int index) const;

		/**
		 * Gets all the stratigraphic column rank interpretations which are contained in this
		 * stratigraphic column.
		 *
		 * @returns	A vector of pointers to all the stratigraphic column rank interpretations which are
		 * 			contained in this stratigraphic column.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<StratigraphicColumnRankInterpretation *> getStratigraphicColumnRankInterpretationSet() const;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

    protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT StratigraphicColumn(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		 * Default constructor
		 */
		StratigraphicColumn() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		StratigraphicColumn(gsoap_resqml2_0_1::_resqml20__StratigraphicColumn* fromGsoap) : AbstractObject(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		StratigraphicColumn(gsoap_eml2_3::_resqml22__StratigraphicColumn* fromGsoap) : AbstractObject(fromGsoap) {}

		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
