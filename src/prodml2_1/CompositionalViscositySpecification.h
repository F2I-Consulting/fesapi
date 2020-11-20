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

#include "CompositionalSpecification.h"

namespace PRODML2_1_NS
{
	/** A compositional viscosity specification. */
	class CompositionalViscositySpecification : public CompositionalSpecification
	{
	public:

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		CompositionalViscositySpecification(gsoap_eml2_2::prodml21__AbstractCompositionalViscosityModel* fromGsoap) :CompositionalSpecification(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~CompositionalViscositySpecification() = default;

		/**
		 * Gets thermodynamic phase
		 *
		 * @returns	The thermodynamic phase.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_2::prodml21__ThermodynamicPhase getThermodynamicPhase() const {
			return static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalViscosityModel*>(gsoapProxy)->phase;
		}

		/**
		 * Sets thermodynamic phase
		 *
		 * @param 	phase	The phase.
		 */
		DLL_IMPORT_OR_EXPORT void setThermodynamicPhase(gsoap_eml2_2::prodml21__ThermodynamicPhase phase) {
			static_cast<gsoap_eml2_2::prodml21__AbstractCompositionalViscosityModel*>(gsoapProxy)->phase = phase;
		}
	};
}
