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
#include "CorrelationViscositySpecification.h"

namespace PRODML2_2_NS
{
	/** A correlation viscosity bubble point specification. */
	class CorrelationViscosityBubblePointSpecification : public CorrelationViscositySpecification
	{
	public:

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		CorrelationViscosityBubblePointSpecification(gsoap_eml2_3::prodml22__AbstractCorrelationViscosityBubblePointModel* fromGsoap): CorrelationViscositySpecification(fromGsoap){}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~CorrelationViscosityBubblePointSpecification() = default;

		GETTER_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::prodml22__AbstractCorrelationViscosityBubblePointModel, gsoapProxy, DeadOilViscosity, gsoap_eml2_3::eml23__DynamicViscosityUom)
		GETTER_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::prodml22__AbstractCorrelationViscosityBubblePointModel, gsoapProxy, BubblePointOilViscosity, gsoap_eml2_3::eml23__DynamicViscosityUom)
		GETTER_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::prodml22__AbstractCorrelationViscosityBubblePointModel, gsoapProxy, SolutionGasOilRatio, std::string)
	};
}
