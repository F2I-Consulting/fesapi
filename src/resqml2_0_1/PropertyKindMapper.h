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

#if defined(_WIN32) || defined(__APPLE__)
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif

#include "common/EpcDocument.h"

namespace RESQML2_0_1_NS
{
	class DLL_IMPORT_OR_EXPORT PropertyKindMapper
	{
	public:
		PropertyKindMapper(COMMON_NS::EpcDocument* epcDoc):epcDocument(epcDoc) {}
		~PropertyKindMapper() {}

		/**
		* Load in maps all the config files present in a particular directory.
		* Config files are all xml files (extension must be .xml). One of this xml file must be named PropertyKindMapping.xml.
		* PropertyKindMapping.xml is the only file to make the mapping with the standard property types.
		* All others xml files must be local property kinds mapping.
		* @param directory The directory must not end with any slash
		*/
		std::string loadMappingFilesFromDirectory(const std::string & directory);

		/**
		 * Get the name of a resqml standard property kind into a particular application.
		 *
		 * @param  	resqmlStandardPropertyKindName	The enumerated resqml standard property kind name
		 * @apram	application						The name of the application
		 * @return	The property kind name in the particular application. Or an empty string if not found.
		 */
		std::string getApplicationPropertyKindNameFromResqmlStandardPropertyKindName(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & resqmlStandardPropertyKindName, const std::string & application) const;

		/**
		 * @apram	application						The name of the application
		 * @return	The abstract Resqml root property name if no resqml standard property name have been found for this particular application property kind name.
		 */
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind getResqmlStandardPropertyKindNameFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application) const;

		/**
		 * @apram	application						The name of the application
		 * @return	empty string if not found
		 */
		std::string getApplicationPropertyKindNameFromResqmlLocalPropertyKindUuid(const std::string & resqmlLocalPropertyKindUuid, const std::string & application) const;

		/**
		* @return empty string if not found
		*/
		std::string getResqmlLocalPropertyKindUuidFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application) const;

		/**
		* Add a resqml local property type into the EPC document given in constructor if not already present in EPC document.
		* This addition will also add all needed resqml local property type parent into the EPC document.
		*/
		class PropertyKind* addResqmlLocalPropertyKindToEpcDocumentFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application);

		/**
		 * Get the title of the parent of a Resqml Standard PropertyKind.
		 */
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind getPropertyKindParentOfResqmlStandardPropertyKindName(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & resqmlStandardPropertyKindName) const;

		/**
		 * Get the description of a Resqml Standard PropertyKind.
		 */
		std::string getDescriptionOfResqmlStandardPropertyKindName(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & resqmlStandardPropertyKindName) const;

		/**
		* Check if a resqml property kind is a child of another one.
		* @param child	The resqml property kind which is supposed to be the child
		* @param parent	The resqml property kind which is supposed to be the parent
		*/
		bool isChildOf(gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind child, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind parent) const;

		/**
		* Check if a resqml property kind is an abstract one or not.
		* @param resqmlStandardPropertyKindName	The resqml property kind to test
		*/
		bool isAbstract(gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind resqmlStandardPropertyKindName) const;

	private:
		COMMON_NS::EpcDocument * epcDocument;


#if (defined(_WIN32) && _MSC_VER >= 1600)
		std::unordered_map<gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind, gsoap_resqml2_0_1::ptm__standardEnergisticsPropertyType*> resqmlStandardPropertyKindNameToApplicationPropertyKindName;
		std::unordered_map<std::string, std::unordered_map<std::string, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind> > applicationPropertyKindNameToResqmlStandardPropertyKindName; // First key string is the application name Second key string is the application property kind name.

		std::unordered_map<std::string, std::unordered_map<std::string, std::string> > resqmlLocalPropertyKindUuidToApplicationPropertyKindName; // First key string is the application name, second is the uuid of the resqml local property.
		std::unordered_map<std::string, std::unordered_map<std::string, std::string> > applicationPropertyKindNameToResqmlLocalPropertyKindUuid;

		std::unordered_map<std::string, gsoap_resqml2_0_1::_resqml2__PropertyKind*> resqmlLocalPropertyKindUuidToResqmlLocalPropertyKind;
#elif defined(__APPLE__)
		std::unordered_map<gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind, gsoap_resqml2_0_1::ptm__standardEnergisticsPropertyType*, std::hash<int> > resqmlStandardPropertyKindNameToApplicationPropertyKindName;
		std::unordered_map<std::string, std::unordered_map<std::string, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind> > applicationPropertyKindNameToResqmlStandardPropertyKindName;

		std::unordered_map<std::string, std::unordered_map<std::string, std::string> > resqmlLocalPropertyKindUuidToApplicationPropertyKindName;
		std::unordered_map<std::string, std::unordered_map<std::string, std::string> > applicationPropertyKindNameToResqmlLocalPropertyKindUuid;

		std::unordered_map<std::string, gsoap_resqml2_0_1::_resqml2__PropertyKind*> resqmlLocalPropertyKindUuidToResqmlLocalPropertyKind;
#else
		std::tr1::unordered_map<gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind, gsoap_resqml2_0_1::ptm__standardEnergisticsPropertyType*, std::tr1::hash<int> > resqmlStandardPropertyKindNameToApplicationPropertyKindName;
		std::tr1::unordered_map< std::string, std::tr1::unordered_map<std::string, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind> > applicationPropertyKindNameToResqmlStandardPropertyKindName;

		std::tr1::unordered_map< std::string, std::tr1::unordered_map<std::string, std::string> > resqmlLocalPropertyKindUuidToApplicationPropertyKindName;
		std::tr1::unordered_map< std::string, std::tr1::unordered_map<std::string, std::string> > applicationPropertyKindNameToResqmlLocalPropertyKindUuid;

		std::tr1::unordered_map<std::string, gsoap_resqml2_0_1::_resqml2__PropertyKind*> resqmlLocalPropertyKindUuidToResqmlLocalPropertyKind;
#endif

	};
}

