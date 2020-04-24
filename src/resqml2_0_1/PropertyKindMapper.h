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

#include "../common/DataObjectRepository.h"

namespace RESQML2_0_1_NS
{
	/** A property kind mapper. */
	class PropertyKindMapper final
	{
	public:

		/**
		 * Constructor
		 *
		 * @param [in,out]	repository	If non-null, the repository.
		 */
		PropertyKindMapper(COMMON_NS::DataObjectRepository* repository):dataObjRepo(repository) {}
		/** Destructor */
		~PropertyKindMapper() {}

		/**
		 * Load in maps all the config files present in a particular directory. Config files are all xml
		 * files (extension must be .xml). One of this xml file must be named PropertyKindMapping.xml.
		 * PropertyKindMapping.xml is the only file to make the mapping with the standard property
		 * types. All others xml files must be local property kinds mapping.
		 *
		 * @param 	directory	The directory must not end with any slash.
		 *
		 * @returns	The mapping files from directory.
		 */
		DLL_IMPORT_OR_EXPORT std::string loadMappingFilesFromDirectory(const std::string & directory);

		/**
		 * @brief	Get the name of a resqml standard property kind into a particular application.
		 *
		 * @param 	resqmlStandardPropertyKindName	The enumerated resqml standard property kind name.
		 * @param 	application					  	The name of the application.
		 *
		 * @returns	The property kind name in the particular application. Or an empty string if not found.
		 */
		DLL_IMPORT_OR_EXPORT std::string getApplicationPropertyKindNameFromResqmlStandardPropertyKindName(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind resqmlStandardPropertyKindName, const std::string & application) const;

		/**
		 * @brief	Gets resqml standard property kind name from application property kind name
		 *
		 * @param 	applicationPropertyKindName	Name of the application property kind.
		 * @param 	application				   	The name of the application.
		 *
		 * @returns	The abstract Resqml root property name if no resqml standard property name have been
		 * 			found for this particular application property kind name.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getResqmlStandardPropertyKindNameFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application) const;

		/**
		 * @brief	Gets application property kind name from resqml local property kind uuid
		 *
		 * @param 	resqmlLocalPropertyKindUuid	The resqml local property kind uuid.
		 * @param 	application				   	The name of the application.
		 *
		 * @returns	empty string if not found.
		 */
		DLL_IMPORT_OR_EXPORT std::string getApplicationPropertyKindNameFromResqmlLocalPropertyKindUuid(const std::string & resqmlLocalPropertyKindUuid, const std::string & application) const;

		/**
		 * Gets resqml local property kind uuid from application property kind name
		 *
		 * @param 	applicationPropertyKindName	Name of the application property kind.
		 * @param 	application				   	The application.
		 *
		 * @returns	empty string if not found.
		 */
		DLL_IMPORT_OR_EXPORT std::string getResqmlLocalPropertyKindUuidFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application) const;

		/**
		 * Add a resqml local property type into the EPC document given in constructor if not already
		 * present in EPC document. This addition will also add all needed resqml local property type
		 * parent into the EPC document.
		 */
		DLL_IMPORT_OR_EXPORT class PropertyKind* addResqmlLocalPropertyKindToEpcDocumentFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application);

		/**
		 * Get the title of the parent of a Resqml Standard PropertyKind.
		 *
		 * @param 	resqmlStandardPropertyKindName	Name of the resqml standard property kind.
		 *
		 * @returns	The property kind parent of resqml standard property kind name.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getPropertyKindParentOfResqmlStandardPropertyKindName(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind resqmlStandardPropertyKindName) const;

		/**
		 * Get the description of a Resqml Standard PropertyKind.
		 *
		 * @param 	resqmlStandardPropertyKindName	Name of the resqml standard property kind.
		 *
		 * @returns	The description of resqml standard property kind name.
		 */
		DLL_IMPORT_OR_EXPORT std::string getDescriptionOfResqmlStandardPropertyKindName(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind resqmlStandardPropertyKindName) const;

		/**
		 * Check if a resqml property kind is a child of another one.
		 *
		 * @param 	child 	The resqml property kind which is supposed to be the child.
		 * @param 	parent	The resqml property kind which is supposed to be the parent.
		 *
		 * @returns	True if child of, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isChildOf(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind child, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind parent) const;

		/**
		 * Check if a resqml property kind is an abstract one or not.
		 *
		 * @param 	resqmlStandardPropertyKindName	The resqml property kind to test.
		 *
		 * @returns	True if abstract, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAbstract(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind resqmlStandardPropertyKindName) const;

	private:
		/** The data object repo */
		COMMON_NS::DataObjectRepository * dataObjRepo;

		/** Name of the resqml standard property kind name to application property kind */
		std::unordered_map<gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind, gsoap_resqml2_0_1::ptm__standardEnergisticsPropertyType*, std::hash<int> > resqmlStandardPropertyKindNameToApplicationPropertyKindName;

		/**
		 * First key string is the application name Second key string is the application property kind
		 * name.
		 */
		std::unordered_map<std::string, std::unordered_map<std::string, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind> > applicationPropertyKindNameToResqmlStandardPropertyKindName;

		/** First key string is the application name, second is the uuid of the resqml local property. */
		std::unordered_map<std::string, std::unordered_map<std::string, std::string> > resqmlLocalPropertyKindUuidToApplicationPropertyKindName;
		/** The application property kind name to resqml local property kind uuid */
		std::unordered_map<std::string, std::unordered_map<std::string, std::string> > applicationPropertyKindNameToResqmlLocalPropertyKindUuid;

		/** The resqml local property kind uuid to resqml local property kind */
		std::unordered_map<std::string, gsoap_resqml2_0_1::_resqml20__PropertyKind*> resqmlLocalPropertyKindUuidToResqmlLocalPropertyKind;

	};
}
