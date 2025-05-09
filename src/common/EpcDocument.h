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

#include <string>

#include "../epc/Package.h"

#include "DataObjectRepository.h"
#include "DataFeeder.h"

namespace COMMON_NS
{
	/** @brief EPC is an implementation of the Open Packaging Conventions (OPC), a widely used container-file technology
	 * that allows multiple types of files to be bundled together into a single package.
	 * Built on the widely used ZIP file structure and originally created by Microsoft, OPC is now an open standard supported by these standards organizations:
	 *  - Ecma International (http://www.ecma-international.org/publications/standards/Ecma-376.htm )
	 *  - ISO/IEC 29500-2:2012, which has 4 parts, which are all freely available at this link (http://standards.iso.org/ittf/PubliclyAvailableStandards/index.html ).
	 * An EPC file (or package) is a ZIP file, which may be "unzipped" to view its components.
	 * When implemented as part of an Energistics standard, the zipping/unzipping is done using the OPC libraries (per the EPC Specification).
	 */
	class EpcDocument : public DataFeeder
	{		
	public:

		/**
		 * Constructor
		 *
		 * @param 	fileName	Full pathname of the EPC document in UTF-8 encoding.
		 */
		DLL_IMPORT_OR_EXPORT EpcDocument(const std::string& fileName) { open(fileName); }

		/** The destructor frees all allocated ressources. */
		DLL_IMPORT_OR_EXPORT ~EpcDocument() = default;

		/**
		 * Opens an EPC document.
		 *
		 * @param 	fileName	Full pathname of the EPC document in UTF-8 encoding.
		 */
		DLL_IMPORT_OR_EXPORT void open(const std::string& fileName)
		{
			setFilePath(fileName);
			package.reset(new epc::Package());
		}

		/**
		 * Serializes the content of a data object repository into this EPC document.
		 *
		 * @param 	repo		A data object repository (not const because we may create a Fake Property for solivng a RESQML2.0.1 empty PropertySet issue)
		 */
		DLL_IMPORT_OR_EXPORT void serializeFrom(DataObjectRepository& repo);

		/**
		 * Deserializes this package (data objects and relationships) into a data object repository
		 *
		 * @param [in,out]	repo			   	A data object repository.
		 * @param 		  	hdfPermissionAccess	(Optional) The HDF5 file permission access. It is read
		 * 										only by default.
		 *
		 * @returns	An empty string if success otherwise the warning string.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string deserializeInto(DataObjectRepository& repo, DataObjectRepository::openingMode hdfPermissionAccess = DataObjectRepository::openingMode::READ_ONLY);

		/**
		* Unzip the package (dataobjects + relationships) into a data repository by only creating partial objects.
		* @return			An empty string if success otherwise the warning string.
		*/
		DLL_IMPORT_OR_EXPORT std::string deserializePartiallyInto(DataObjectRepository& repo, DataObjectRepository::openingMode hdfPermissionAccess = DataObjectRepository::openingMode::READ_ONLY);

		/**
		 * Gets the absolute path of the directory where the EPC document is stored.
		 *
		 * @returns	The EPC document storage directory.
		 */
		DLL_IMPORT_OR_EXPORT std::string getStorageDirectory() const;

		/**
		 * Gets the name of the EPC document
		 *
		 * @returns	The name of the EPC document without the @c .epc extension.
		 */
		DLL_IMPORT_OR_EXPORT std::string getName() const;

		/**
		 * Gets the extended core properties of this package
		 * The EpcDocument must have been deserialized at least once to get the extended core proeprties information.
		 *
		 * @returns	A map which associates keys and values of the extended core properties.
		 */
		DLL_IMPORT_OR_EXPORT std::unordered_map< std::string, std::string >& getExtendedCoreProperty();

		/**
		 * Sets or adds an extended core property
		 *
		 * @param 	key  	The key of the property.
		 * @param 	value	The value of the property.
		 */
		DLL_IMPORT_OR_EXPORT void setExtendedCoreProperty(const std::string& key, const std::string& value);

		/**
		 * Gets extended core property count.
		 * The EpcDocument must have been deserialized at least once to get the extended core proeprties information.
		 *
		 * @returns	The count of extended core properties in this EPC document
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getExtendedCorePropertyCount() const;

		/**
		 * Gets an extended core property value according to its key.
		 * The EpcDocument must have been deserialized at least once to get the extended core proeprties information.
		 *
		 * @param 	key	The key of the property.
		 *
		 * @returns	An empty string if the extended core property does not exist. Or the extended core
		 * 			property value if it exists.
		 */
		DLL_IMPORT_OR_EXPORT std::string getExtendedCoreProperty(const std::string& key) const;

		DLL_IMPORT_OR_EXPORT std::string resolvePartial(AbstractObject const* partialObj) const;

	private :
		/**
		 * Sets the EPC document file path which will be used for future serialization and
		 * deserialization. This method will add the standard @c .epc extension if it is not already
		 * present.
		 *
		 * @exception	std::invalid_argument	if the HDF5 file error handling cannot be disabled.
		 *
		 * @param 	fp	Full pathname of the EPC document.
		 */
		void setFilePath(const std::string& fp);

		void deserializeRelFiles(DataObjectRepository& repo);

		static constexpr char const* DOCUMENT_EXTENSION = ".epc";

		/** The package */
		std::unique_ptr<epc::Package> package;
		/** Full pathname of the file */
		std::string filePath;
	};
}
