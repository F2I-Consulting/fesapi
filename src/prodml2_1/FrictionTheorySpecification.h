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

#include "CompositionalViscositySpecification.h"

#include <limits>

namespace PRODML2_1_NS
{
	/** A friction theory specification. */
	class FrictionTheorySpecification : public CompositionalViscositySpecification
	{
	public:

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		FrictionTheorySpecification(gsoap_eml2_2::prodml21__FrictionTheory* fromGsoap): CompositionalViscositySpecification(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~FrictionTheorySpecification() = default;

		/**
		 * Gets prsv parameter count
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @returns	The prsv parameter count.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getPrsvParameterCount() const noexcept {
			return static_cast<gsoap_eml2_2::prodml21__FrictionTheory*>(gsoapProxy)->PrsvParameter.size();
		}

		/**
		 * Gets prsv parameter a 1
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The prsv parameter a 1.
		 */
		DLL_IMPORT_OR_EXPORT double getPrsvParameterA1(uint64_t index) const {
			return static_cast<gsoap_eml2_2::prodml21__FrictionTheory*>(gsoapProxy)->PrsvParameter.at(index)->a1;
		}

		/**
		 * Gets prsv parameter a 2
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The prsv parameter a 2.
		 */
		DLL_IMPORT_OR_EXPORT double getPrsvParameterA2(uint64_t index) const {
			return static_cast<gsoap_eml2_2::prodml21__FrictionTheory*>(gsoapProxy)->PrsvParameter.at(index)->a2;
		}

		/**
		 * Gets prsv parameter b 1
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The prsv parameter b 1.
		 */
		DLL_IMPORT_OR_EXPORT double getPrsvParameterB1(uint64_t index) const {
			return static_cast<gsoap_eml2_2::prodml21__FrictionTheory*>(gsoapProxy)->PrsvParameter.at(index)->b1;
		}

		/**
		 * Gets prsv parameter b 2
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The prsv parameter b 2.
		 */
		DLL_IMPORT_OR_EXPORT double getPrsvParameterB2(uint64_t index) const {
			return static_cast<gsoap_eml2_2::prodml21__FrictionTheory*>(gsoapProxy)->PrsvParameter.at(index)->b2;
		}

		/**
		 * Gets prsv parameter c 2
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The prsv parameter c 2.
		 */
		DLL_IMPORT_OR_EXPORT double getPrsvParameterC2(uint64_t index) const {
			return static_cast<gsoap_eml2_2::prodml21__FrictionTheory*>(gsoapProxy)->PrsvParameter.at(index)->c2;
		}

		/**
		 * Gets prsv parameter fluid component reference
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The prsv parameter fluid component reference.
		 */
		DLL_IMPORT_OR_EXPORT std::string getPrsvParameterFluidComponentReference(uint64_t index) const {
			return static_cast<gsoap_eml2_2::prodml21__FrictionTheory*>(gsoapProxy)->PrsvParameter.at(index)->fluidComponentReference;
		}

		/**
		 * Pushes a back prsv parameter
		 *
		 * @param 	a1					   	The first double.
		 * @param 	a2					   	The second double.
		 * @param 	b1					   	The first double.
		 * @param 	b2					   	The second double.
		 * @param 	c2					   	The second double.
		 * @param 	fluidComponentReference	The fluid component reference.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackPrsvParameter(double a1, double a2, double b1, double b2, double c2, const std::string & fluidComponentReference);
	};
}
