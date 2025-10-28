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
#include "PvtSpecification.h"

namespace PRODML2_3_NS
{
	/** A correlation viscosity specification. */
	class CorrelationViscositySpecification : public PvtSpecification
	{
	public:

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		CorrelationViscositySpecification(gsoap_eml2_3::prodml23__AbstractCorrelationViscosityModel* fromGsoap): PvtSpecification(fromGsoap){}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~CorrelationViscositySpecification() = default;

		GETTER_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(gsoap_eml2_3::prodml23__AbstractCorrelationViscosityModel, gsoapProxy, MolecularWeight, gsoap_eml2_3::eml23__MolecularWeightUom)
	};
}
