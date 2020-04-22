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

#include "../resqml2/StratigraphicUnitInterpretation.h"

/** @brief */
namespace RESQML2_2_NS
{
	/** A stratigraphic unit interpretation. */
	class StratigraphicUnitInterpretation final : public RESQML2_NS::StratigraphicUnitInterpretation
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT StratigraphicUnitInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::StratigraphicUnitInterpretation(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	feature	The feature the instance interprets.
		 * @param 		  	guid   	The guid to set to the interpretation. If empty then a new guid will
		 * 							be generated.
		 * @param 		  	title  	A title for the instance to create.
		 */
		StratigraphicUnitInterpretation(RESQML2_NS::RockVolumeFeature * feature, const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		StratigraphicUnitInterpretation(gsoap_eml2_3::_resqml22__StratigraphicUnitInterpretation* fromGsoap) : RESQML2_NS::StratigraphicUnitInterpretation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~StratigraphicUnitInterpretation() {}

		/**
		 * Indicates if the instance has an information about its deposition mode.
		 *
		 * @returns	True if deposition mode, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasDepositionMode() const final;

		/**
		 * Get the deposition mode of the stratigraphic unit interpretation. You should verify its
		 * existency using hasDepositionMode() before to call this function.
		 *
		 * @returns	The deposition mode.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__DepositionMode getDepositionMode() const final;
	};
}