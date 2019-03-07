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

#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif

#include "FileCoreProperties.h"
#include "FileContentType.h"
#include "FileRelationship.h"
#include "FilePart.h"

namespace epc
{
	class Package
	{

	private :
		class CheshireCat;               // Not defined here but in the cpp
		CheshireCat * d_ptr;              // opaque pointer
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		typedef std::unordered_map<std::string, FilePart> PartMap;
#else
		typedef std::tr1::unordered_map<std::string, FilePart> PartMap;
#endif

		/**
		* This method allows to write a string content to a non existing part of the package.
		* This method does not create any new FilePart in 'allFileParts' class member.
		*/
		void writeStringIntoNewPart(const std::string &input, const std::string & partPath);
		
		static const char* CORE_PROP_REL_TYPE;
		static const char* EXTENDED_CORE_PROP_REL_TYPE;

	public:
		/** 
		* Create a Package with pathname.
		*/
		Package();

		/**
		* Create a Package with CoreProperties file, ContentType file, Relationship file, vector of Part file and pathname.
		*/
		Package(const FileCoreProperties & pkgFileCP, const FileContentType & pkgFileCT, const FileRelationship & pkgFileRS, const PartMap & pkgFileP, const std::string & pkgPathName);

		/**
		* Destructor : free memory allocated for the parts
		*/
		~Package();

		/**
		* Open the package for writing purpose
		*/
		void openForWriting(const std::string & pkgPathName, bool useZip64 = false);

		/**
		* Open the package for reading purpose
		* @return empty vector if nothing went wrong. Otherwise, return warnings.
		*/
		std::vector<std::string> openForReading(const std::string & pkgPathName);

		/**
		* Close the package
		*/
		void close();

		/** 
		* @return CoreProperties file.
		*/
		const FileCoreProperties& getFileCoreProperties() const;

		/** 
		* @return ContentType file.
		*/
		const FileContentType& getFileContentType() const;

		/** 
		* @return Relationship file.
		*/
		const FileRelationship& getPrincipalRelationship() const;

		/** 
		* vector of part file.
		*/
		const PartMap & getAllFilePart() const;

		/**
		* Get a const string reference on the name of the package.
		*/
		const std::string & getPathname() const;

		/**
		* @brief set the CoreProperties file.
		* @param pkgFileCP CoreProperties file.
		*/
		void setFileFileCoreProperties(const FileCoreProperties & pkgFileCP);

		/**
		* Get in read/write access all the non standard core properties of this package
		* All added non standard core properties will be stored in a single part which will be linked to the standard core properties part.
		*/
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		std::unordered_map< std::string, std::string > & getExtendedCoreProperty();
#else
		std::tr1::unordered_map< std::string, std::string > & getExtendedCoreProperty();
#endif

		/**
		* @brief add a Property in the CoreProperties file of package.
		* @param pkgTypeProperty	The type of the property to add.
		* @param pkgPropertyValue	The value of the property to add.
		*/
		void addProperty(const CoreProperty::TypeProperty & pkgTypeProperty, const std::string & pkgPropertyValue);

		/**
		* @brief set the ContentTypes file.
		* @param pkgFileCT	The ContentType file.
		*/
		void setFileContentType(const FileContentType & pkgFileCT);

		/**
		* @brief add a ContentType in the ContentTypes file of package.
		* @param contentType The ContentType to add.
		*/
		void addContentType(const ContentType & contentType);

		/**
		* @brief set the Relationships file.
		* @param pkgFileRS Relationship file.
		*/
		void setPrincipalRelationship(const FileRelationship & pkgFileRS);

		/**
		* @brief add a Relationship in the Relationships file of package.
		* @param relationship Relationship file.
		*/
		void addRelationship(const Relationship & relationship);

		/**
		* @brief Creates a part in the package and returns it. This part will be automatically destroy with the package.
		* @return a new part.
		*/
		FilePart* createPart(const std::string & inputContent, const std::string & outputPartPath);

        /**
         * @brief Find a part corresponding to the given path
         */
		const FilePart* findPart(const std::string & outputPartPath) const;
		
        /**
         * Check that a given file exists in the zip file
         */
        bool fileExists(const std::string & filename) const;

        /**
         * Extract the content of a given file from the zip file
         */
		std::string extractFile(const std::string & filename, const std::string & password = "");

		void writePackage();
	};
}

#endif
