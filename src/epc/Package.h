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
#ifndef PACKAGE_H
#define PACKAGE_H

#include <vector>
#include <string>

#include <unordered_map>

#include "FileCoreProperties.h"
#include "FileContentType.h"
#include "FileRelationship.h"
#include "FilePart.h"

namespace epc
{
	/** A package. */
	class Package
	{

	private :
		class CheshireCat;               // Not defined here but in the cpp
		/** opaque pointer */
		CheshireCat * d_ptr;
		/** Defines an alias representing the part map */
		typedef std::unordered_map<std::string, FilePart> PartMap;

		/**
		 * This method allows to write a string content to a non existing part of the package. This
		 * method does not create any new FilePart in 'allFileParts' class member.
		 *
		 * @param 	input   	The input.
		 * @param 	partPath	Full pathname of the part file.
		 */
		void writeStringIntoNewPart(const std::string &input, const std::string & partPath);

		static constexpr char const* CORE_PROP_REL_TYPE = "http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties";
		static constexpr char const* EXTENDED_CORE_PROP_REL_TYPE = "http://schemas.f2i-consulting.com/package/2014/relationships/extended-core-properties";

	public:
		/** Create a Package with pathname. */
		Package();
		Package(const Package&) = delete;


		/**
		 * Create a Package with CoreProperties file, ContentType file, Relationship file, vector of
		 * Part file and pathname.
		 *
		 * @param 	pkgFileCP  	The package file cp.
		 * @param 	pkgFileCT  	The package file ct.
		 * @param 	pkgFileRS  	The package file RS.
		 * @param 	pkgFileP   	The package file p.
		 * @param 	pkgPathName	Full pathname of the package file.
		 */
		Package(const FileCoreProperties & pkgFileCP, const FileContentType & pkgFileCT, const FileRelationship & pkgFileRS, const PartMap & pkgFileP, const std::string & pkgPathName);

		Package& operator=(const Package&) = delete;

		/** Destructor : free memory allocated for the parts */
		~Package();

		/**
		 * Open the package for writing purpose
		 *
		 * @param 	pkgPathName	contain on Windows XP a filename like "c:\\zlib\\zlib113.zip" or on an
		 * 						Unix computer "zlib/zlib113.zip".
		 * @param 	append	   	if the file pathname exist and append==APPEND_STATUS_ADDINZIP, we will
		 * 						add files in existing zip (be sure you don't add file that doesn't
		 * 						exist). Else an ovewrite or a creation of the file will be done. If the
		 * 						zipfile cannot be opened, an invalid_argument exception is thrown.
		 * @param 	useZip64   	(Optional) True to use zip 64.
		 */
		void openForWriting(const std::string & pkgPathName, int append, bool useZip64 = false);

		/**
		* Check if the package is already opened for writing.
		*/
		bool isOpenedForWriting() const;

		/**
		 * Open the package for reading purpose
		 *
		 * @param 	pkgPathName	Full pathname of the package file.
		 *
		 * @returns	empty vector if nothing went wrong. Otherwise, return warnings.
		 */
		std::vector<std::string> openForReading(const std::string & pkgPathName);

		/**
		* Check if the package is already opened for reading.
		*/
		bool isOpenedForReading() const;

		/** Close the package */
		void close();

		/**
		 * Gets file core properties
		 *
		 * @returns	CoreProperties file.
		 */
		const FileCoreProperties& getFileCoreProperties() const;

		/**
		 * Gets file content type
		 *
		 * @returns	ContentType file.
		 */
		const FileContentType& getFileContentType() const;

		/**
		 * Gets principal relationship
		 *
		 * @returns	Relationship file.
		 */
		const FileRelationship& getPrincipalRelationship() const;

		/**
		 * vector of part file.
		 *
		 * @returns	all file part.
		 */
		const PartMap & getAllFilePart() const;

		/**
		 * Get a const string reference on the name of the package.
		 *
		 * @returns	The pathname.
		 */
		const std::string & getPathname() const;

		/**
		 * set the CoreProperties file.
		 *
		 * @param 	pkgFileCP	CoreProperties file.
		 */
		void setFileFileCoreProperties(const FileCoreProperties & pkgFileCP);

		/**
		 * Get in read/write access all the non standard core properties of this package All added non
		 * standard core properties will be stored in a single part which will be linked to the standard
		 * core properties part.
		 *
		 * @returns	A map associating keys and values of the extended core properties.
		 */
		std::unordered_map< std::string, std::string > & getExtendedCoreProperty();

		/**
		 * add a Property in the CoreProperties file of package.
		 *
		 * @param 	pkgTypeProperty 	The type of the property to add.
		 * @param 	pkgPropertyValue	The value of the property to add.
		 */
		void addProperty(const CoreProperty::TypeProperty & pkgTypeProperty, const std::string & pkgPropertyValue);

		/**
		 * set the ContentTypes file.
		 *
		 * @param 	pkgFileCT	The ContentType file.
		 */
		void setFileContentType(const FileContentType & pkgFileCT);

		/**
		 * add a ContentType in the ContentTypes file of package.
		 *
		 * @param 	contentType	The ContentType to add.
		 */
		void addContentType(const ContentType & contentType);

		/**
		 * set the Relationships file.
		 *
		 * @param 	pkgFileRS	Relationship file.
		 */
		void setPrincipalRelationship(const FileRelationship & pkgFileRS);

		/**
		 * add a Relationship in the Relationships file of package.
		 *
		 * @param 	relationship	Relationship file.
		 */
		void addRelationship(const Relationship & relationship);

		/**
		 * Creates a part in the package and returns it. This part will be automatically destroy with
		 * the package.
		 *
		 * @param 	inputContent  	The input content.
		 * @param 	outputPartPath	Full pathname of the output part file.
		 *
		 * @returns	a new part.
		 */
		FilePart* createPart(const std::string & inputContent, const std::string & outputPartPath);

		/**
		 * Find a part corresponding to the given path
		 *
		 * @param 	outputPartPath	Full pathname of the output part file.
		 *
		 * @returns	Null if it fails, else the found part.
		 */
		const FilePart* findPart(const std::string & outputPartPath) const;

        /**
         * Check that a given file exists in the zip file
         *
         * @param 	filename	Filename of the file.
         *
         * @returns	True if it succeeds, false if it fails.
         */
        bool fileExists(const std::string & filename) const;

		/**
		 * Extract the content of a given file from the zip file
		 *
		 * @param 	filename	Filename of the file.
		 * @param 	password	(Optional) The password.
		 *
		 * @returns	The extracted file.
		 */
		std::string extractFile(const std::string & filename);

		/** Writes the package */
		void writePackage();
	};
}

#endif
