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

#include "../resqml2/StratigraphicOccurrenceInterpretation.h"

/** . */
namespace RESQML2_0_1_NS
{
	/**
	* This class is a container for other organizations that are consistent to each others.
	*/
	class StratigraphicOccurrenceInterpretation final : public RESQML2_NS::StratigraphicOccurrenceInterpretation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT StratigraphicOccurrenceInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::StratigraphicOccurrenceInterpretation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param orgFeat	The feature the instance interprets. It must be a stratigraphic organization feature.
		* @param guid		The guid to set to the interpretation. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		*/
		StratigraphicOccurrenceInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__OrderingCriteria orderingCriteria);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		StratigraphicOccurrenceInterpretation(gsoap_resqml2_0_1::_resqml20__StratigraphicOccurrenceInterpretation* fromGsoap) : RESQML2_NS::StratigraphicOccurrenceInterpretation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~StratigraphicOccurrenceInterpretation() {}

		/**
		 * Sets stratigraphic column rank interpretation
		 *
		 * @param [in,out]	stratiColumnRankInterp	If non-null, the strati column rank interp.
		 */
		DLL_IMPORT_OR_EXPORT void setStratigraphicColumnRankInterpretation(RESQML2_NS::StratigraphicColumnRankInterpretation * stratiColumnRankInterp) final;

		/** A stratigraphic column rank interpretation*. */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getStratigraphicColumnRankInterpretationDor() const final;
	};
}
