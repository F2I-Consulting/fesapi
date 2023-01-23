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
#include "Package.h"

#include <iostream> 
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#else 
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#endif

#include <zip.h>
#include <unzip.h>

#include "FilePart.h"

static constexpr int CASESENSITIVITY = 0;

using namespace std;
using namespace epc;

class Package::CheshireCat {
public:

	/**
	* Create a Package with pathname.
	*/
	CheshireCat() :
		fileCoreProperties(), fileContentType(), filePrincipalRelationship(), allFileParts(), extendedCoreProperties(), pathName(),
		unzipped(nullptr), zf(nullptr), isZip64(false), name2file()
	{}

	/**
	* Create a Package with CoreProperties file, ContentType file, Relationship file, vector of Part file and pathname.
	*/
	CheshireCat(const FileCoreProperties & pkgFileCP, const FileContentType & pkgFileCT, const FileRelationship & pkgFileRS, const PartMap & pkgFileP, const std::string & pkgPathName) :
		fileCoreProperties(pkgFileCP), fileContentType(pkgFileCT), filePrincipalRelationship(pkgFileRS), allFileParts(pkgFileP), extendedCoreProperties(), pathName(pkgPathName),
		unzipped(nullptr), zf(nullptr), isZip64(false), name2file()
	{}

	~CheshireCat() { close(); }

	void close() {
		if (unzipped != nullptr) {
			unzClose(unzipped);
			unzipped = nullptr;
		}
	}

	FileCoreProperties	fileCoreProperties;											/// Core Properties file
	FileContentType		fileContentType;											/// ContentTypes file
	FileRelationship	filePrincipalRelationship;									/// Relationships file
	PartMap				allFileParts;
	std::unordered_map< string, string > extendedCoreProperties;					/// Set of non standard (extended) core properties

	string				pathName;													/// Pathname of package
	unzFile				unzipped;
	zipFile             zf;
	bool                isZip64;
	std::unordered_map< std::string, unz64_file_pos > name2file;
};

Package::Package()
{
	d_ptr = new Package::CheshireCat();
}

Package::Package(const FileCoreProperties & pkgFileCP, const FileContentType & pkgFileCT, const FileRelationship & pkgFileRS, const PartMap & pkgFileP, const string & pkgPathName)
{
	d_ptr = new Package::CheshireCat(pkgFileCP, pkgFileCT, pkgFileRS, pkgFileP, pkgPathName);
}

Package::~Package()
{
	delete d_ptr;
}

void Package::openForWriting(const std::string & pkgPathName, int append, bool useZip64)
{
	d_ptr->allFileParts.clear();
	d_ptr->fileContentType.clear();

	d_ptr->pathName.assign(pkgPathName);

	// Clean the potential ending slashes
	while (!d_ptr->pathName.empty() &&
		(d_ptr->pathName[d_ptr->pathName.size() - 1] == '/' || d_ptr->pathName[d_ptr->pathName.size() - 1] == '\\')) {
		d_ptr->pathName = d_ptr->pathName.substr(0, d_ptr->pathName.size() - 1);
	}

	addContentType(ContentType(true, "application/vnd.openxmlformats-package.relationships+xml", ".rels"));
	addContentType(ContentType(false, "application/vnd.openxmlformats-package.core-properties+xml", "docProps/core.xml"));

	addRelationship(Relationship("docProps/core.xml", CORE_PROP_REL_TYPE, "CoreProperties"));

	d_ptr->isZip64 = useZip64;
	d_ptr->zf = useZip64 ? zipOpen64(d_ptr->pathName.c_str(), append) : zipOpen(d_ptr->pathName.c_str(), append);

	if (d_ptr->zf == nullptr) {
		throw invalid_argument("The file " + pkgPathName + " could not be opened");
	}
}

bool Package::isOpenedForWriting() const
{
	return d_ptr->zf != nullptr;
}

std::vector<std::string> Package::openForReading(const std::string & pkgPathName)
{
	std::vector<std::string> result;
	d_ptr->pathName.assign(pkgPathName);
	
	d_ptr->unzipped = unzOpen64(d_ptr->pathName.c_str());

	if (d_ptr->unzipped == nullptr) {
		throw invalid_argument("Cannot unzip " + pkgPathName + ". Please verify the path of the file and if you can open it with a third party archiver.");
    }

	// Cache all file locations
	if (unzGoToFirstFile(d_ptr->unzipped) != UNZ_OK) {
		throw std::invalid_argument("Cannot go to the first file of " + pkgPathName);
	}
	do {
		unz_file_info64 fileInfo;
		int err = unzGetCurrentFileInfo64(d_ptr->unzipped, &fileInfo, nullptr, 0, nullptr, 0, nullptr, 0);
		if (UNZ_OK != err || fileInfo.size_filename == 0) {
			throw std::invalid_argument("Cannot get file information of current file in " + pkgPathName);
		}

		std::string partName;
		partName.resize(fileInfo.size_filename);
		err = unzGetCurrentFileInfo64(d_ptr->unzipped, nullptr, &partName[0], fileInfo.size_filename, nullptr, 0, nullptr, 0);
		if (UNZ_OK != err) {
			throw std::invalid_argument("Cannot get filename of current file in " + pkgPathName);
		}
		unz64_file_pos filePos;
		err = unzGetFilePos64(d_ptr->unzipped, &filePos);
		if (UNZ_OK != err) {
			throw std::invalid_argument("Cannot get file position in EPC of file " + partName);
		}
		d_ptr->name2file[partName] = filePos;
	} while (unzGoToNextFile(d_ptr->unzipped) != UNZ_END_OF_LIST_OF_FILE);

	// Package relationships : core properties
	d_ptr->filePrincipalRelationship.readFromString(extractFile("_rels/.rels"));
	for (const auto& pckRel : d_ptr->filePrincipalRelationship.getAllRelationship()) {
		if (pckRel.getType().compare(CORE_PROP_REL_TYPE) == 0) {
			std::string target = pckRel.getTarget();
			if (target.size() > 1 && target[0] == '/' && target[1] != '/') { // Rule 8 of A.3 paragraph Open Packaging Conventions (ECMA version)
				target = target.substr(1);
			}
			d_ptr->fileCoreProperties.readFromString(extractFile(target));
		}
	}

	// Package relationships : extended core properties	
	if (fileExists("docProps/_rels/core.xml.rels")) {
		FileRelationship extendedCpRelFile;
		extendedCpRelFile.readFromString(extractFile("docProps/_rels/core.xml.rels"));
		for (const auto& extendedCpRel : extendedCpRelFile.getAllRelationship()) {
			std::string target = extendedCpRel.getTarget();
			if (target.size() > 1 && target[0] == '/' && target[1] != '/') { // Rule 8 of A.3 paragraph Open Packaging Conventions (ECMA version)
				target = target.substr(1);
			}
			target = "docProps/" + target; // always prefixed by "docProps/" because core.xml is always in folder docProps by business rule
			if (!fileExists(target)) {
				result.push_back("The extended core properties file " + target + " targeted in docProps/_rels/core.xml.rels is not present in the Epc document");
				continue;
			}

			std::istringstream iss(extractFile(target));
			std::string line;
			while (std::getline(iss, line)) {
				if (line[0] == '\t') { // To find a better condition
					size_t start = line.find('<');
					size_t end = line.find('>');
					if (start != string::npos && end != string::npos) {
						size_t end2 = line.find('<', end + 1);
						if (end2 != string::npos) {
							d_ptr->extendedCoreProperties[line.substr(start + 1, end - start - 1)] = line.substr(end + 1, end2 - end - 1);
						}
					}
				}
			}
		}
	}

	// Package content type
	d_ptr->fileContentType.readFromString(extractFile("[Content_Types].xml"));

	return result;
}

bool Package::isOpenedForReading() const
{
	return d_ptr->unzipped != nullptr;
}

void Package::close()
{
	d_ptr->close();
}

const FileCoreProperties& Package::getFileCoreProperties() const
{
	return d_ptr->fileCoreProperties;
}

const FileContentType& Package::getFileContentType() const
{
	return d_ptr->fileContentType;
}

const FileRelationship& Package::getPrincipalRelationship() const
{
	return d_ptr->filePrincipalRelationship;
}

const Package::PartMap& Package::getAllFilePart() const
{
	return d_ptr->allFileParts;
}

const string & Package::getPathname() const
{
	return d_ptr->pathName;
}

void Package::setFileFileCoreProperties(const FileCoreProperties & pkgFileCP)
{
	d_ptr->fileCoreProperties = pkgFileCP;
}

unordered_map< string, string > & Package::getExtendedCoreProperty()
{
	return d_ptr->extendedCoreProperties;
}

void Package::addProperty(const CoreProperty::TypeProperty & pkgTypeProperty, const string & pkgPropertyValue)
{
	switch (pkgTypeProperty)
	{
	case CoreProperty::category:
		d_ptr->fileCoreProperties.setCategory(pkgPropertyValue);
		break;
	case CoreProperty::contentStatus:
		d_ptr->fileCoreProperties.setContentStatus(pkgPropertyValue);
		break;
	case CoreProperty::created:
		d_ptr->fileCoreProperties.setCreated(pkgPropertyValue);
		break;
	case CoreProperty::creator:
		d_ptr->fileCoreProperties.setCreator(pkgPropertyValue);
		break;
	case CoreProperty::description:
		d_ptr->fileCoreProperties.setDescription(pkgPropertyValue);
		break;
	case CoreProperty::identifier:
		d_ptr->fileCoreProperties.setIdentifier(pkgPropertyValue);
		break;
	case CoreProperty::keywords:
		d_ptr->fileCoreProperties.addKeywords(pkgPropertyValue);
		break;
	case CoreProperty::language:
		d_ptr->fileCoreProperties.setLanguage(pkgPropertyValue);
		break;
	case CoreProperty::lastModifiedBy:
		d_ptr->fileCoreProperties.setLastModifiedBy(pkgPropertyValue);
		break;
	case CoreProperty::lastPrinted:
		d_ptr->fileCoreProperties.setLastPrinted(pkgPropertyValue);
		break;
	case CoreProperty::modified:
		d_ptr->fileCoreProperties.setModified(pkgPropertyValue);
		break;
	case CoreProperty::revision:
		d_ptr->fileCoreProperties.setRevision(pkgPropertyValue);
		break;
	case CoreProperty::subject:
		d_ptr->fileCoreProperties.setSubject(pkgPropertyValue);
		break;
	case CoreProperty::title:
		d_ptr->fileCoreProperties.setTitle(pkgPropertyValue);
		break;
	case CoreProperty::version:
		d_ptr->fileCoreProperties.setVersion(pkgPropertyValue);
		break;
	default:
		throw invalid_argument("The core property to add does not exist, is unknown or is not supported yet. For your information, its value is " + pkgPropertyValue);
	}
}

void Package::setFileContentType(const FileContentType & pkgFileCT)
{
	d_ptr->fileContentType = pkgFileCT;
}

void Package::addContentType(const ContentType & contentType)
{
	d_ptr->fileContentType.addContentType(contentType);
}

void Package::setPrincipalRelationship(const FileRelationship & pkgFileRS)
{
	d_ptr->filePrincipalRelationship = pkgFileRS;
}

void Package::addRelationship(const Relationship & relationship)
{
	d_ptr->filePrincipalRelationship.addRelationship(relationship);
}

FilePart* Package::createPart(const std::string & inputContent, const std::string & outputPartPath)
{
	d_ptr->allFileParts[outputPartPath] = FilePart(outputPartPath);
    writeStringIntoNewPart(inputContent, outputPartPath);
	return &(d_ptr->allFileParts[outputPartPath]);
}

const FilePart* Package::findPart(const std::string & outputPartPath) const
{
	PartMap::const_iterator it = d_ptr->allFileParts.find(outputPartPath);
	return it == d_ptr->allFileParts.end() ? nullptr : &(it->second);
}


#ifdef _WIN32
void buildTimeInfo(const char *filename, uLong *dostime)
{
	FILETIME ftUtc;
	FILETIME ftLocal;
	HANDLE hFind;
	WIN32_FIND_DATAA ff32;

	hFind = FindFirstFileA(filename, &ff32);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		FileTimeToLocalFileTime(&(ff32.ftLastWriteTime), &ftLocal);
		FileTimeToDosDateTime(&ftLocal, ((LPWORD)dostime) + 1, ((LPWORD)dostime) + 0);
		FindClose(hFind);
	}
	else
	{
		GetSystemTimeAsFileTime(&ftUtc);
		FileTimeToLocalFileTime(&ftUtc, &ftLocal);
		FileTimeToDosDateTime(&ftLocal, ((LPWORD)dostime) + 1, ((LPWORD)dostime) + 0);
		FindClose(hFind);
	}
}
#else
void buildTimeInfo(tm_zip *tmzip)
{
    struct tm* filedate;
    time_t tm_t = time(0);
    filedate = localtime(&tm_t);

    tmzip->tm_sec  = filedate->tm_sec;
    tmzip->tm_min  = filedate->tm_min;
    tmzip->tm_hour = filedate->tm_hour;
    tmzip->tm_mday = filedate->tm_mday;
    tmzip->tm_mon  = filedate->tm_mon ;
    tmzip->tm_year = filedate->tm_year;
}
#endif

void Package::writeStringIntoNewPart(const std::string &input, const std::string & partPath)
{
	// Initialize the parameters for the creation of a file in the zip archive
	zip_fileinfo zi;
	zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour = zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;
	zi.dosDate = 0;
	zi.internal_fa = 0;
	zi.external_fa = 0;
#ifdef _WIN32
	buildTimeInfo(partPath.c_str(), &zi.dosDate);
#else
	buildTimeInfo(&zi.tmz_date);
#endif

	// Open the content type part in the zip archive
	int err = zipOpenNewFileInZip64(d_ptr->zf, partPath.c_str(), &zi,
		nullptr,0,nullptr,0,nullptr /* comment*/,
		Z_DEFLATED,						// method
		Z_DEFAULT_COMPRESSION,				// level
		d_ptr->isZip64);								// Zip64
	if (err != ZIP_OK) {
		throw invalid_argument("Could not open " + partPath + " in the zipfile. Code = " + std::to_string(err));
	}

	// Write the content of the content type part
	if (input.size() > (std::numeric_limits<unsigned int>::max)()) {
		throw invalid_argument("The string to write into " + partPath + " is too long.");
	}
	err = zipWriteInFileInZip(d_ptr->zf, input.c_str(), static_cast<unsigned int>(input.size()));
	if (err < 0) {
		throw invalid_argument("Could not write " + partPath + " in the zipfile. Code = " + std::to_string(err));
	}

	// Close the content type part
	err = zipCloseFileInZip(d_ptr->zf);
	if (err != ZIP_OK) {
		throw invalid_argument("Could not close " + partPath + " in the zipfile. Code = " + std::to_string(err));
	}
}

void Package::writePackage() 
{
	d_ptr->fileCoreProperties.initDefaultCoreProperties();
	writeStringIntoNewPart(d_ptr->fileCoreProperties.toString(), "docProps/core.xml");
	if (!d_ptr->extendedCoreProperties.empty())
	{
		// XML def + namespaces def
		ostringstream oss;
		oss << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << endl;
		oss << "<extendedCoreProperties xmlns=\"http://schemas.f2i-consulting.com/package/2014/metadata/extended-core-properties\"" << endl;
		oss << "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">" << endl;

		// content
		for (std::unordered_map< std::string, std::string >::iterator it = d_ptr->extendedCoreProperties.begin(); it != d_ptr->extendedCoreProperties.end(); ++it) {
			oss << "\t<" << it->first << ">" + it->second + "</" + it->first + ">" << endl;
		}

		// end tag
		oss << "</extendedCoreProperties>" << endl;
		
		writeStringIntoNewPart(oss.str(), "docProps/extendedCore.xml");
		
		// Add the content type for extended core properties part
		addContentType(ContentType(false, "application/x-extended-core-properties+xml", "docProps/extendedCore.xml"));
		
		// Relationhsip with the standard core properties part
		FileRelationship fileRelToExtCoreProp(Relationship("extendedCore.xml", EXTENDED_CORE_PROP_REL_TYPE, "ExtendedCoreProperties"));
		fileRelToExtCoreProp.setPathName("docProps/_rels/core.xml.rels");
		writeStringIntoNewPart(fileRelToExtCoreProp.toString(), fileRelToExtCoreProp.getPathName());
	}

	writeStringIntoNewPart(d_ptr->fileContentType.toString(), "[Content_Types].xml");
	
	// write Principal Relationships file.
	if (!d_ptr->filePrincipalRelationship.isEmpty()) {
		writeStringIntoNewPart(d_ptr->filePrincipalRelationship.toString(), "_rels/.rels");
	}
	
	// Write all the part relationships
	for (PartMap::iterator i = d_ptr->allFileParts.begin(); i != d_ptr->allFileParts.end(); ++i) {
		if (!i->second.getFileRelationship().isEmpty()) {
			writeStringIntoNewPart(i->second.getFileRelationship().toString(), i->second.getFileRelationship().getPathName());
		}
	}

	// Close the zip archive
	int err = zipClose(d_ptr->zf, "");
	if (err != ZIP_OK) {
		throw invalid_argument("Could not close " + d_ptr->pathName.substr(0, d_ptr->pathName.size() - 4) + ". Code = " + std::to_string(err));
	}
}

string do_extract_currentfile(unzFile uf)
{
	std::string data;

	int err = unzOpenCurrentFile(uf);
    if (err != UNZ_OK) {
		throw invalid_argument("Error with zipfile in unzOpenCurrentFile. Code = " + std::to_string(err));
    }

	// Get current file info
	unz_file_info64 file_info;
	err = unzGetCurrentFileInfo64(uf, &file_info, nullptr, 0, nullptr, 0, nullptr, 0);
	if (err == UNZ_OK) {
		// Extract file
		data.resize(file_info.uncompressed_size);
		err = unzReadCurrentFile(uf, &data[0], static_cast<unsigned int>(data.size()));
		if (err < 0) {
			throw invalid_argument("Error with zipfile in unzReadCurrentFile. Code = " + std::to_string(err));
		}
	}
	else {
		throw invalid_argument("Failed to get current file information from ZIP. Code = " + std::to_string(err));
	}

	err = unzCloseCurrentFile(uf);
	if (err != UNZ_OK) {
		throw invalid_argument("Error with zipfile in unzCloseCurrentFile. Code = " + std::to_string(err));
	}

    return data;
}

bool Package::fileExists(const string & filename) const
{
	if (d_ptr->unzipped == nullptr) {
		throw logic_error("The EPC document must be opened first.");
	}
	std::unordered_map< std::string, unz64_file_pos >::const_iterator it = d_ptr->name2file.find(filename);
	if (it == d_ptr->name2file.end()) {
		if (unzLocateFile(d_ptr->unzipped, filename.c_str(), CASESENSITIVITY) != UNZ_OK) {
			return false;
		}
		unz64_file_pos filePos;
		unzGetFilePos64(d_ptr->unzipped, &filePos);
		d_ptr->name2file[filename] = filePos;
	}
	else {
		unzGoToFilePos64(d_ptr->unzipped, &it->second);
	}
	return true;
}

string Package::extractFile(const string & filename)
{
	if (!fileExists(filename))  {
		throw invalid_argument("The file " + filename + " does not exist in the EPC document.");
    }
	
	return do_extract_currentfile(d_ptr->unzipped);
}
