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

#include "DataObjectRepository.h"

#if defined(_WIN32) && !defined(FESAPI_STATIC)
#if defined(FesapiCpp_EXPORTS) || defined(FesapiCppUnderDev_EXPORTS)
#define DLL_IMPORT_OR_EXPORT __declspec(dllexport)
#else
#define DLL_IMPORT_OR_EXPORT __declspec(dllimport) 
#endif
#else
#define DLL_IMPORT_OR_EXPORT
#endif

/** . */
namespace COMMON_NS
{
	/** An enum string mapper. */
	class EnumStringMapper
	{
	/**
	 * Gets a context for the gsoap
	 *
	 * @returns	The gsoap context.
	 */
	private :
		soap* gsoapContext;

	/**
	 * Enum string mapper
	 *
	 * @returns	A DLL_IMPORT_OR_EXPORT.
	 */
	public :
		DLL_IMPORT_OR_EXPORT EnumStringMapper();
		/** Destructor */
		DLL_IMPORT_OR_EXPORT ~EnumStringMapper();

		/**
		 * Get the name of the energistics property kind as a string based on the enumerated property
		 * kind.
		 *
		 * @param 	energisticsPropertyKind	The energistics property kind.
		 *
		 * @returns	The empty string if no correspondence is found.
		 */
		DLL_IMPORT_OR_EXPORT std::string getEnergisticsPropertyKindName(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind) const;

		/**
		 * Get the Energistics property kind enumerated value from the name (string) of the property
		 * kind.
		 *
		 * @param 	energisticsPropertyKindName	Name of the energistics property kind.
		 *
		 * @returns	The most abstract energistics property kind if no correspondance is found with the
		 * 			property kind string/name.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind(const std::string & energisticsPropertyKindName) const;

		/**
		 * Get the name of the resqml standard property type as a string based on the enumerated
		 * property kind.
		 *
		 * @param 	energisticsUom	The energistics uom.
		 *
		 * @returns	The empty string if no correspondence is found.
		 */
		DLL_IMPORT_OR_EXPORT std::string getEnergisticsUnitOfMeasureName(gsoap_resqml2_0_1::resqml20__ResqmlUom energisticsUom) const;

		/**
		 * Get the Energistics unit of measure enumerated value from the name (string) of the uom.
		 *
		 * @param 	energisticsUomName	Name of the energistics uom.
		 *
		 * @returns	The Euclidian (no uom) energistics uom if no correspondance is found with the uom
		 * 			string/name.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlUom getEnergisticsUnitOfMeasure(const std::string & energisticsUomName) const;

		/**
		 * Get the name of the resqml facet as a string based on the enumerated facet.
		 *
		 * @param 	facet	The facet.
		 *
		 * @returns	The empty string if no correspondence is found.
		 */
		DLL_IMPORT_OR_EXPORT std::string getFacet(gsoap_resqml2_0_1::resqml20__Facet facet) const;

		/**
		 * Get the facet enumerated value from the name (string) of the facet.
		 *
		 * @param 	facet	The facet.
		 *
		 * @returns	The what facet if no correspondance is found with the facet string/name.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__Facet getFacet(const std::string & facet) const;

		/**
		 * Get the name (string) of the witsml uom as a string based on the enumerated uom.
		 *
		 * @param 	witsmlUom	The witsml uom.
		 *
		 * @returns	The empty string if no correspondence is found.
		 */
		DLL_IMPORT_OR_EXPORT std::string lengthUomToString(gsoap_eml2_1::eml21__LengthUom witsmlUom) const;

		/**
		 * Get the name (string) of the witsml uom as a string based on the enumerated uom.
		 *
		 * @param 	witsmlUom	The witsml uom.
		 *
		 * @returns	The empty string if no correspondence is found.
		 */
		DLL_IMPORT_OR_EXPORT std::string verticalCoordinateUomToString(gsoap_eml2_1::eml21__VerticalCoordinateUom witsmlUom) const;

		/**
		 * Get the name (string) of the witsml uom as a string based on the enumerated uom.
		 *
		 * @param 	witsmlUom	The witsml uom.
		 *
		 * @returns	The empty string if no correspondence is found.
		 */
		DLL_IMPORT_OR_EXPORT std::string planeAngleUomToString(gsoap_eml2_1::eml21__PlaneAngleUom witsmlUom) const;
	};
}
