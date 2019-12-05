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

namespace PRODML2_1_NS
{
	class FrictionTheorySpecification : public CompositionalViscositySpecification
	{
	public:
		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		FrictionTheorySpecification(gsoap_eml2_2::prodml21__FrictionTheory* fromGsoap): CompositionalViscositySpecification(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~FrictionTheorySpecification() {}

		DLL_IMPORT_OR_EXPORT unsigned int getPrsvParameterCount() const {
			size_t count = static_cast<gsoap_eml2_2::prodml21__FrictionTheory*>(gsoapProxy)->PrsvParameter.size();
			if (count > (std::numeric_limits<unsigned int>::max)()) {
				throw std::out_of_range("There are too much Prsv parameters");
			}
			return static_cast<unsigned int>(count);
		}
		DLL_IMPORT_OR_EXPORT double getPrsvParameterA1(unsigned int index) const
		{
			if (index >= getPrsvParameterCount()) {
				throw std::out_of_range("The index is out of range");
			}

			return static_cast<gsoap_eml2_2::prodml21__FrictionTheory*>(gsoapProxy)->PrsvParameter[index]->a1;
		}
		DLL_IMPORT_OR_EXPORT double getPrsvParameterA2(unsigned int index) const
		{
			if (index >= getPrsvParameterCount()) {
				throw std::out_of_range("The index is out of range");
			}

			return static_cast<gsoap_eml2_2::prodml21__FrictionTheory*>(gsoapProxy)->PrsvParameter[index]->a2;
		}
		DLL_IMPORT_OR_EXPORT double getPrsvParameterB1(unsigned int index) const
		{
			if (index >= getPrsvParameterCount()) {
				throw std::out_of_range("The index is out of range");
			}

			return static_cast<gsoap_eml2_2::prodml21__FrictionTheory*>(gsoapProxy)->PrsvParameter[index]->b1;
		}
		DLL_IMPORT_OR_EXPORT double getPrsvParameterB2(unsigned int index) const
		{
			if (index >= getPrsvParameterCount()) {
				throw std::out_of_range("The index is out of range");
			}

			return static_cast<gsoap_eml2_2::prodml21__FrictionTheory*>(gsoapProxy)->PrsvParameter[index]->b2;
		}
		DLL_IMPORT_OR_EXPORT double getPrsvParameterC2(unsigned int index) const
		{
			if (index >= getPrsvParameterCount()) {
				throw std::out_of_range("The index is out of range");
			}

			return static_cast<gsoap_eml2_2::prodml21__FrictionTheory*>(gsoapProxy)->PrsvParameter[index]->c2;
		}
		DLL_IMPORT_OR_EXPORT std::string getPrsvParameterFluidComponentReference(unsigned int index) const
		{
			if (index >= getPrsvParameterCount()) {
				throw std::out_of_range("The index is out of range");
			}

			return static_cast<gsoap_eml2_2::prodml21__FrictionTheory*>(gsoapProxy)->PrsvParameter[index]->fluidComponentReference;
		}
		DLL_IMPORT_OR_EXPORT void pushBackPrsvParameter(double a1, double a2, double b1, double b2, double c2, const std::string & fluidComponentReference);
	};
}
