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

namespace RESQML2_0_1_NS
{
	/** @brief	A rock fluid unit interpretation. This class cannot be inherited. */
	class RockFluidUnitInterpretation final : public RESQML2_NS::RockFluidUnitInterpretation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT RockFluidUnitInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::RockFluidUnitInterpretation(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>feature == nullptr</tt>.
		 *
		 * @param [in]	feature	The feature the instance interprets.
		 * @param 	  	guid   	The guid to set to the interpretation. If empty then a new guid will be
		 * 						generated.
		 * @param 	  	title  	A title for the instance to create.
		 */
		RockFluidUnitInterpretation(RESQML2_NS::RockVolumeFeature * feature, const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		RockFluidUnitInterpretation(gsoap_resqml2_0_1::_resqml20__RockFluidUnitInterpretation* fromGsoap) : RESQML2_NS::RockFluidUnitInterpretation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~RockFluidUnitInterpretation() {}

		DLL_IMPORT_OR_EXPORT bool hasPhase() const final;

		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::resqml22__Phase getPhase() const final;
	};
}
