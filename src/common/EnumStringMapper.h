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

namespace COMMON_NS
{
	/** A class for mapping enum values with strings. */
	class EnumStringMapper
	{
	private :
		soap* gsoapContext;

	public :

		/** Default constructor */
		DLL_IMPORT_OR_EXPORT EnumStringMapper();
		
		/** Destructor */
		DLL_IMPORT_OR_EXPORT ~EnumStringMapper();

		/**
		 * Get the name of a RESQML2.0 property kind as a string based on the property kind enumerated
		 * value
		 *
		 * @param 	energisticsPropertyKind	A RESQML2.0 property kind.
		 *
		 * @returns	A string corresponding to @p energisticsPropertyKind if successful. The empty string
		 * 			if no correspondence is found.
		 */
		DLL_IMPORT_OR_EXPORT std::string getEnergisticsPropertyKindName(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind) const;

		/**
		 * Get the RESQML2.0 property kind enumerated value from the name of a property kind
		 *
		 * @param 	energisticsPropertyKindName	The name of a RESQML2.0 property kind.
		 *
		 * @returns	The RESQML2.0 property kind enumerated value corresponding to @p
		 * 			energisticsPropertyKindName if successful. The most abstract RESQML2.0 property kind
		 * 			enumerated value if no correspondence is found.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind(const std::string & energisticsPropertyKindName) const;

		/**
		 * Get the name of a RESQML2.0 unit of measure as a string based on the unit of measure
		 * enumerated value
		 *
		 * @param 	energisticsUom	A RESQML2.0 unit of measure.
		 *
		 * @returns	A string corresponding to @p energisticsUom if successful. The empty string if no
		 * 			correspondence is found.
		 */
		DLL_IMPORT_OR_EXPORT std::string getEnergisticsUnitOfMeasureName(gsoap_resqml2_0_1::resqml20__ResqmlUom energisticsUom) const;

		/**
		 * Get the RESQML2.0 unit of measure enumerated value from the name of a unit of measure
		 *
		 * @param 	energisticsUomName	The name of a RESQML2.0 unit of measure.
		 *
		 * @returns	The RESQML2.0 unit of measure enumerated value corresponding to @p energisticsUomName
		 * 			if successful. The Euclidian (no unit of measure) RESQML2.0 unit of measure if no
		 * 			correspondence is found.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlUom getEnergisticsUnitOfMeasure(const std::string & energisticsUomName) const;

		/**
		 * Get the name of a RESQML2.0 facet as a string based on the enumerated facet enumerated value
		 *
		 * @param 	facet	A RESQML2.0 facet.
		 *
		 * @returns	A string corresponding to @p facet if successful. The empty string if no
		 * 			correspondence is found.
		 */
		DLL_IMPORT_OR_EXPORT std::string getFacet(gsoap_resqml2_0_1::resqml20__Facet facet) const;

		/**
		 * Get the RESQML2.0 facet enumerated value from the name of a facet.
		 *
		 * @param 	facet	The name of a RESQML2.0 facet.
		 *
		 * @returns	The RESQML2.0 facet enumerated value corresponding to @p facet if successful. The @c
		 * 			what facet enumerated value if no correspendance is found.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__Facet getFacet(const std::string & facet) const;

		/**
		 * Get the name of an EML2.1 length unit of measure as a string based on the unit of measure
		 * enumerated value
		 *
		 * @param 	witsmlUom	An EML2.1 length unit of measure.
		 *
		 * @returns	A string corresponding to @p witsmlUom if successful. The empty string if no
		 * 			correspondence is found.
		 */
		DLL_IMPORT_OR_EXPORT std::string lengthUomToString(gsoap_eml2_1::eml21__LengthUom witsmlUom) const;

		/**
		 * Get the name of an EML2.1 vertical coordinate unit of measure as a string based on the unit
		 * of measure enumerated value
		 *
		 * @param 	witsmlUom	An EML2.1 vertical coordinate unit of measure.
		 *
		 * @returns	A string corresponding to @p witsmlUom if successful. The empty string if no
		 * 			correspondence is found.
		 */
		DLL_IMPORT_OR_EXPORT std::string verticalCoordinateUomToString(gsoap_eml2_1::eml21__VerticalCoordinateUom witsmlUom) const;

		/**
		 * Get the name of an EML2.1 plane angle unit of measure as a string based on the unit of
		 * measure enumerated value
		 *
		 * @param 	witsmlUom	An EML2.1 plane angle unit of measure.
		 *
		 * @returns	A string corresponding to @p witsmlUom if successful. The empty string if no
		 * 			correspondence is found.
		 */
		DLL_IMPORT_OR_EXPORT std::string planeAngleUomToString(gsoap_eml2_1::eml21__PlaneAngleUom witsmlUom) const;
	};
}
