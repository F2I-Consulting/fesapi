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

#include "../resqml2/RockFluidUnitInterpretation.h"

/** . */
namespace RESQML2_0_1_NS
{
	class RockFluidUnitInterpretation : public RESQML2_NS::RockFluidUnitInterpretation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT RockFluidUnitInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::RockFluidUnitInterpretation(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	feature	The feature the instance interprets.
		 * @param 		  	guid   	The guid to set to the interpretation. If empty then a new guid will
		 * 							be generated.
		 * @param 		  	title  	A title for the instance to create.
		 */
		RockFluidUnitInterpretation(RESQML2_NS::RockVolumeFeature * feature, const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		RockFluidUnitInterpretation(gsoap_resqml2_0_1::_resqml20__RockFluidUnitInterpretation* fromGsoap) : RESQML2_NS::RockFluidUnitInterpretation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~RockFluidUnitInterpretation() {}

		/**
		 * Indicates if the instance has an information about its deposition mode.
		 *
		 * @returns	True if phase, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasPhase() const;

		/**
		 * Get the deposition mode of the stratigraphic unit interpretation. You should verify its
		 * existency using hasDepositionMode() before to call this function.
		 *
		 * @returns	The phase.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::resqml22__Phase getPhase() const;
	};
}
