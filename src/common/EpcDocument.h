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
#include <vector>
#include <limits>
#include <stdexcept>

#include "epc/Package.h"

#include "common/DataObjectRepository.h"

namespace COMMON_NS
{
	class AbstractObject;
	class AbstractHdfProxy;

	/**
	* This class allows an access to a memory package representing an EPC document.
	*/
	class EpcDocument
	{		
	public:

		DLL_IMPORT_OR_EXPORT EpcDocument(const std::string & fileName, DataObjectRepository::openingMode hdfPermissionAccess_ = DataObjectRepository::READ_ONLY);

		/**
		* The destructor frees all allocated ressources.
		*/
		DLL_IMPORT_OR_EXPORT virtual ~EpcDocument();

		/**
		* Open an epc document.
		* If already opened, the epc document must be closed before to open a new one.
		* Don't forget to call close() before to destroy this object.
		*/
		DLL_IMPORT_OR_EXPORT void open(const std::string & fileName);
	
		/**
		 * Free all ressources contained in this package.
		 */
		DLL_IMPORT_OR_EXPORT void close();

		/**
		 * Set the file path which will be used for future serialization and deserialization
		 * Will add the standard epc extension to the filePath is not already present.
		 */
		DLL_IMPORT_OR_EXPORT void setFilePath(const std::string & fp);

		/**
		* Serialize the content of a dataobject repository into this EPC document.
		* It also allows to optionally zip this EPC document.
		*/
		DLL_IMPORT_OR_EXPORT void serializeFrom(const DataObjectRepository & repo, bool useZip64 = false);

		/**
		* Unzip the package (dataobjects + relationships) into a data repository
		* @return			An empty string if everything's ok otherwise the error string.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string deserializeInto(DataObjectRepository & repo);

		/**
		* Get the absolute path of the directory where the epc document is stored.
		*/
		DLL_IMPORT_OR_EXPORT std::string getStorageDirectory() const;

		/**
		* Get the name of the epc document.
		*/
		DLL_IMPORT_OR_EXPORT std::string getName() const;

		DLL_IMPORT_OR_EXPORT std::unordered_map< std::string, std::string > & getExtendedCoreProperty();

		DLL_IMPORT_OR_EXPORT void setExtendedCoreProperty(const std::string & key, const std::string & value);

		/**
		* Get an extended core property value according its key.
		* @return An empty string if the extended core property does not exist. Or the extended core property value if it exists
		*/
		DLL_IMPORT_OR_EXPORT std::string getExtendedCoreProperty(const std::string & key);

	private :
		static const char * DOCUMENT_EXTENSION;

		epc::Package* package;
		std::string filePath;
		DataObjectRepository::openingMode hdfPermissionAccess;
	};
}
