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

#include <unordered_map>

#include "common/DataObjectRepository.h"

namespace RESQML2_0_1_NS
{
	class PropertyKindMapper
	{
	public:
		PropertyKindMapper(COMMON_NS::DataObjectRepository* repository):dataObjRepo(repository) {}
		~PropertyKindMapper() {}

		/**
		* Load in maps all the config files present in a particular directory.
		* Config files are all xml files (extension must be .xml). One of this xml file must be named PropertyKindMapping.xml.
		* PropertyKindMapping.xml is the only file to make the mapping with the standard property types.
		* All others xml files must be local property kinds mapping.
		* @param directory The directory must not end with any slash
		*/
		DLL_IMPORT_OR_EXPORT std::string loadMappingFilesFromDirectory(const std::string & directory);

		/**
		 * Get the name of a resqml standard property kind into a particular application.
		 *
		 * @param  	resqmlStandardPropertyKindName	The enumerated resqml standard property kind name
		 * @apram	application						The name of the application
		 * @return	The property kind name in the particular application. Or an empty string if not found.
		 */
		DLL_IMPORT_OR_EXPORT std::string getApplicationPropertyKindNameFromResqmlStandardPropertyKindName(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind resqmlStandardPropertyKindName, const std::string & application) const;

		/**
		 * @apram	application						The name of the application
		 * @return	The abstract Resqml root property name if no resqml standard property name have been found for this particular application property kind name.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getResqmlStandardPropertyKindNameFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application) const;

		/**
		 * @apram	application						The name of the application
		 * @return	empty string if not found
		 */
		DLL_IMPORT_OR_EXPORT std::string getApplicationPropertyKindNameFromResqmlLocalPropertyKindUuid(const std::string & resqmlLocalPropertyKindUuid, const std::string & application) const;

		/**
		* @return empty string if not found
		*/
		DLL_IMPORT_OR_EXPORT std::string getResqmlLocalPropertyKindUuidFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application) const;

		/**
		* Add a resqml local property type into the EPC document given in constructor if not already present in EPC document.
		* This addition will also add all needed resqml local property type parent into the EPC document.
		*/
		DLL_IMPORT_OR_EXPORT class PropertyKind* addResqmlLocalPropertyKindToEpcDocumentFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application);

		/**
		 * Get the title of the parent of a Resqml Standard PropertyKind.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getPropertyKindParentOfResqmlStandardPropertyKindName(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind resqmlStandardPropertyKindName) const;

		/**
		 * Get the description of a Resqml Standard PropertyKind.
		 */
		DLL_IMPORT_OR_EXPORT std::string getDescriptionOfResqmlStandardPropertyKindName(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind resqmlStandardPropertyKindName) const;

		/**
		* Check if a resqml property kind is a child of another one.
		* @param child	The resqml property kind which is supposed to be the child
		* @param parent	The resqml property kind which is supposed to be the parent
		*/
		DLL_IMPORT_OR_EXPORT bool isChildOf(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind child, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind parent) const;

		/**
		* Check if a resqml property kind is an abstract one or not.
		* @param resqmlStandardPropertyKindName	The resqml property kind to test
		*/
		DLL_IMPORT_OR_EXPORT bool isAbstract(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind resqmlStandardPropertyKindName) const;

	private:
		COMMON_NS::DataObjectRepository * dataObjRepo;

		std::unordered_map<gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind, gsoap_resqml2_0_1::ptm__standardEnergisticsPropertyType*, std::hash<int> > resqmlStandardPropertyKindNameToApplicationPropertyKindName;
		std::unordered_map<std::string, std::unordered_map<std::string, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind> > applicationPropertyKindNameToResqmlStandardPropertyKindName; // First key string is the application name Second key string is the application property kind name.

		std::unordered_map<std::string, std::unordered_map<std::string, std::string> > resqmlLocalPropertyKindUuidToApplicationPropertyKindName; // First key string is the application name, second is the uuid of the resqml local property.
		std::unordered_map<std::string, std::unordered_map<std::string, std::string> > applicationPropertyKindNameToResqmlLocalPropertyKindUuid;

		std::unordered_map<std::string, gsoap_resqml2_0_1::_resqml20__PropertyKind*> resqmlLocalPropertyKindUuidToResqmlLocalPropertyKind;

	};
}
