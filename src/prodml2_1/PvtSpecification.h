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
#include <limits>

#include "../proxies/gsoap_eml2_2H.h"

#include "../nsDefinitions.h"

#if defined(_WIN32) && !defined(FESAPI_STATIC)
#if defined(FesapiCpp_EXPORTS) || defined(FesapiCppUnderDev_EXPORTS)
#define DLL_IMPORT_OR_EXPORT __declspec(dllexport)
#else
#define DLL_IMPORT_OR_EXPORT __declspec(dllimport) 
#endif
#else
#define DLL_IMPORT_OR_EXPORT
#endif

#include "../MacroDefinitions.h"

namespace PRODML2_1_NS
{
	/** A pvt specification. */
	class PvtSpecification
	{
	public:
		/** The gsoap proxy */
		gsoap_eml2_2::prodml21__AbstractPvtModel* gsoapProxy;

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PvtSpecification(gsoap_eml2_2::prodml21__AbstractPvtModel* fromGsoap): gsoapProxy(fromGsoap){}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~PvtSpecification() {}

		/**
		 * Gets coefficient count
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @returns	The coefficient count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getCoefficientCount() const {
			if (static_cast<gsoap_eml2_2::prodml21__AbstractPvtModel*>(gsoapProxy)->PvtModelParameterSet == nullptr) {
				return 0;
			}

			size_t count = static_cast<gsoap_eml2_2::prodml21__AbstractPvtModel*>(gsoapProxy)->PvtModelParameterSet->Coefficient.size();
			if (count > (std::numeric_limits<unsigned int>::max)()) {
				throw std::out_of_range("There are too much coefficient");
			}
			return static_cast<unsigned int>(count);
		}

		/**
		 * Gets coefficient value
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The coefficient value.
		 */
		DLL_IMPORT_OR_EXPORT double getCoefficientValue(unsigned int index) const
		{
			if (index >= getCoefficientCount()) {
				throw std::out_of_range("The index is out of range");
			}

			return static_cast<gsoap_eml2_2::prodml21__AbstractPvtModel*>(gsoapProxy)->PvtModelParameterSet->Coefficient[index]->__item;
		}

		/**
		 * Gets coefficient kind
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The coefficient kind.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_2::prodml21__PvtModelParameterKind getCoefficientKind(unsigned int index) const;

		/**
		 * Query if 'index' has coefficient name
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if coefficient name, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasCoefficientName(unsigned int index) const
		{
			if (index >= getCoefficientCount()) {
				throw std::out_of_range("The index is out of range");
			}

			return static_cast<gsoap_eml2_2::prodml21__AbstractPvtModel*>(gsoapProxy)->PvtModelParameterSet->Coefficient[index]->name != nullptr;
		}

		/**
		 * Gets coefficient name
		 *
		 * @exception	std::invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The coefficient name.
		 */
		DLL_IMPORT_OR_EXPORT std::string getCoefficientName(unsigned int index) const
		{
			if (!hasCoefficientName(index)) {
				throw std::invalid_argument("Ther is no coefficient name at this index");
			}

			return *static_cast<gsoap_eml2_2::prodml21__AbstractPvtModel*>(gsoapProxy)->PvtModelParameterSet->Coefficient[index]->name;
		}

		/**
		 * Pushes a back coefficient
		 *
		 * @param 	value	The value.
		 * @param 	kind 	The kind.
		 * @param 	name 	(Optional) The name.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackCoefficient(double value, gsoap_eml2_2::prodml21__PvtModelParameterKind kind, const std::string & name = "");
	};
}
