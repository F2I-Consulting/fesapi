/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
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
