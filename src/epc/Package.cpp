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

#ifdef _WIN32
#include <windows.h>
#else 
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#endif

#include "zip.h"
#include "unzip.h"

#include "FilePart.h"

#define CASESENSITIVITY (0)

using namespace std; // in order not to prefix by "std::" for each class in the "std" namespace. Never use "using namespace" in *.h file but only in *.cpp file!!!
using namespace epc; // in order not to prefix by "epc::" for each class in the "epc" namespace. Never use "using namespace" in *.h file but only in *.cpp file!!!

const char* Package::CORE_PROP_REL_TYPE = "http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties";
const char* Package::EXTENDED_CORE_PROP_REL_TYPE = "http://schemas.f2i-consulting.com/package/2014/relationships/extended-core-properties";

namespace epc {
#define CACHE_FILE_DESCRIPTOR //When defined all file descriptors are cached to speedup file lookup

#ifdef CACHE_FILE_DESCRIPTOR
	/* unz_file_info_interntal contain internal info about a file in zipfile*/
	typedef struct unz_file_info64_internal_s
	{
		ZPOS64_T offset_curfile;            /* relative offset of local header 8 bytes */
		ZPOS64_T byte_before_the_zipfile;   /* byte before the zipfile, (>0 for sfx) */
#ifdef HAVE_AES
		uLong aes_encryption_mode;
		uLong aes_compression_method;
#endif
	} unz_file_info64_internal;

	/* file_in_zip_read_info_s contain internal information about a file in zipfile */
	typedef struct
	{
		Bytef *read_buffer;                 /* internal buffer for compressed data */
		z_stream stream;                    /* zLib stream structure for inflate */

#ifdef HAVE_BZIP2
		bz_stream bstream;                  /* bzLib stream structure for bziped */
#endif
#ifdef HAVE_AES
		fcrypt_ctx aes_ctx;
#endif

		ZPOS64_T pos_in_zipfile;            /* position in byte on the zipfile, for fseek */
		uLong stream_initialised;           /* flag set if stream structure is initialised */

		ZPOS64_T offset_local_extrafield;   /* offset of the local extra field */
		uInt size_local_extrafield;         /* size of the local extra field */
		ZPOS64_T pos_local_extrafield;      /* position in the local extra field in read */
		ZPOS64_T total_out_64;

		uLong crc32;                        /* crc32 of all data uncompressed */
		uLong crc32_wait;                   /* crc32 we must obtain after decompress all */
		ZPOS64_T rest_read_compressed;      /* number of byte to be decompressed */
		ZPOS64_T rest_read_uncompressed;    /* number of byte to be obtained after decomp */

		zlib_filefunc64_32_def z_filefunc;

		voidpf filestream;                  /* io structore of the zipfile */
		uLong compression_method;           /* compression method (0==store) */
		ZPOS64_T byte_before_the_zipfile;   /* byte before the zipfile, (>0 for sfx) */
		int raw;
	} file_in_zip64_read_info_s;

	/* unz64_s contain internal information about the zipfile */
	typedef struct
	{
		zlib_filefunc64_32_def z_filefunc;
		voidpf filestream;                  /* io structure of the current zipfile */
		voidpf filestream_with_CD;          /* io structure of the disk with the central directory */
		unz_global_info64 gi;               /* public global information */
		ZPOS64_T byte_before_the_zipfile;   /* byte before the zipfile, (>0 for sfx)*/
		ZPOS64_T num_file;                  /* number of the current file in the zipfile*/
		ZPOS64_T pos_in_central_dir;        /* pos of the current file in the central dir*/
		ZPOS64_T current_file_ok;           /* flag about the usability of the current file*/
		ZPOS64_T central_pos;               /* position of the beginning of the central dir*/
		uLong number_disk;                  /* number of the current disk, used for spanning ZIP*/
		ZPOS64_T size_central_dir;          /* size of the central directory  */
		ZPOS64_T offset_central_dir;        /* offset of start of central directory with
											respect to the starting disk number */

		unz_file_info64 cur_file_info;      /* public info about the current file in zip*/
		unz_file_info64_internal cur_file_info_internal;
		/* private info about it*/
		file_in_zip64_read_info_s* pfile_in_zip_read;
		/* structure about the current file if we are decompressing it */
		int encrypted;                      /* is the current file encrypted */
		int isZip64;                        /* is the current file zip64 */
#ifndef NOUNCRYPT
		unsigned long keys[3];              /* keys defining the pseudo-random sequence */
		const unsigned long* pcrc_32_tab;
#endif
	} unz64_s;
#endif
}

class Package::CheshireCat {
public:

	/**
	* Create a Package with pathname.
	*/
	CheshireCat();

	/**
	* Create a Package with CoreProperties file, ContentType file, Relationship file, vector of Part file and pathname.
	*/
	CheshireCat(const FileCoreProperties & pkgFileCP, const FileContentType & pkgFileCT, const FileRelationship & pkgFileRS, const PartMap & pkgFileP, const std::string & pkgPathName);

	~CheshireCat();

	void close();

	FileCoreProperties	fileCoreProperties;											/// Core Properties file
	FileContentType		fileContentType;											/// ContentTypes file
	FileRelationship	filePrincipalRelationship;									/// Relationships file
	PartMap				allFileParts;												/// Set of parts file
	unordered_map< string, string >			extendedCoreProperties;					/// Set of non standard (extended) core properties
	string				pathName;													/// Pathname of package
	unzFile				unzipped;
	zipFile             zf;
	bool                isZip64;
#ifdef CACHE_FILE_DESCRIPTOR
	std::unordered_map< std::string, unz64_s > name2file;
#endif
};

Package::CheshireCat::CheshireCat() : unzipped(nullptr), zf(nullptr), isZip64(false)
{
}


Package::CheshireCat::CheshireCat(const FileCoreProperties & pkgFileCP, const FileContentType & pkgFileCT, const FileRelationship & pkgFileRS, const PartMap & pkgFileP, const string & pkgPathName) :
fileCoreProperties(pkgFileCP), fileContentType(pkgFileCT), filePrincipalRelationship(pkgFileRS), allFileParts(pkgFileP), pathName(pkgPathName), unzipped(nullptr), zf(nullptr), isZip64(false)
{
}

Package::CheshireCat::~CheshireCat()
{
	close();
}

void Package::CheshireCat::close()
{
	if (unzipped != nullptr) {
		unzClose(unzipped);
		unzipped = nullptr;
	}
}

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
	d_ptr->pathName.assign(pkgPathName);

	// Clean the potential ending slashes
	while (d_ptr->pathName[d_ptr->pathName.size() - 1] == '/' || d_ptr->pathName[d_ptr->pathName.size() - 1] == '\\') {
		d_ptr->pathName = d_ptr->pathName.substr(0, d_ptr->pathName.size() - 1);
	}

	ContentType contentTypeRel(true, "application/vnd.openxmlformats-package.relationships+xml", ".rels");
	addContentType(contentTypeRel);

	ContentType contentTypeCoreProp(false, "application/vnd.openxmlformats-package.core-properties+xml", "docProps/core.xml");
	addContentType(contentTypeCoreProp);

	Relationship relToCoreProp("docProps/core.xml", CORE_PROP_REL_TYPE,"CoreProperties");
	addRelationship(relToCoreProp);

	d_ptr->isZip64 = useZip64;
	d_ptr->zf = useZip64 ? zipOpen64(d_ptr->pathName.c_str(), append) : zipOpen(d_ptr->pathName.c_str(), append);

	if (d_ptr->zf == nullptr) {
		throw invalid_argument("The file " + pkgPathName + " could not be opened");
	}
}

std::vector<std::string> Package::openForReading(const std::string & pkgPathName)
{
	std::vector<std::string> result;
	d_ptr->pathName.assign(pkgPathName);
	
	d_ptr->unzipped = unzOpen64(d_ptr->pathName.c_str());

	if (d_ptr->unzipped == nullptr) {
		throw invalid_argument("Cannot unzip " + pkgPathName + ". Please verify the path of the file and if you can open it with a third party archiver.");
    }

#ifdef CACHE_FILE_DESCRIPTOR
	// Speedup part lookup, by caching zipped file descriptor using file name

#ifndef UNZ_MAXFILENAMEINZIP
#define UNZ_MAXFILENAMEINZIP (256)
#endif

    char current_filename[UNZ_MAXFILENAMEINZIP+1];
	int err = unzGoToFirstFile(d_ptr->unzipped);
    while (err == UNZ_OK)
    {
		d_ptr->name2file[current_filename] = *(unz64_s*)d_ptr->unzipped;
		err = unzGoToNextFile(d_ptr->unzipped);
    }
#endif

	// Package relationships : core properties
	string relFile = extractFile("_rels/.rels", "");
	d_ptr->filePrincipalRelationship.readFromString(relFile);
	vector<Relationship> pckRelset = d_ptr->filePrincipalRelationship.getAllRelationship();
	for (size_t i = 0; i < pckRelset.size(); i++)
	{
		if (pckRelset[i].getType().compare(CORE_PROP_REL_TYPE) == 0)
		{
			std::string target = pckRelset[i].getTarget();
			if (target.size() > 1 && target[0] == '/' && target[1] != '/') { // Rule 8 of A.3 paragraph Open Packaging Conventions (ECMA version)
				target = target.substr(1);
			}
			string corePropFile = extractFile(target, "");
			d_ptr->fileCoreProperties.readFromString(corePropFile);
		}
	}

	// Package relationships : extended core properties	
	if (fileExists("docProps/_rels/core.xml.rels"))
	{
		string extendedCpRelFilePath = extractFile("docProps/_rels/core.xml.rels", "");
		FileRelationship extendedCpRelFile;
		extendedCpRelFile.readFromString(extendedCpRelFilePath);
		vector<Relationship> extendedCpRelSet = extendedCpRelFile.getAllRelationship();
		for (size_t i = 0; i < extendedCpRelSet.size(); i++)
		{
			std::string target = extendedCpRelSet[i].getTarget();
			if (target.size() > 1 && target[0] == '/' && target[1] != '/') { // Rule 8 of A.3 paragraph Open Packaging Conventions (ECMA version)
				target = target.substr(1);
			}
			target = "docProps/" + target; // always prefixed by "docProps/" because core.xml is always in folder docProps by business rule
			if (!fileExists(target))
			{
				result.push_back("The extended core properties file " + target + " targeted in docProps/_rels/core.xml.rels is not present in the Epc document");
				continue;
			}
			string extendedCorePropFile = extractFile(target, "");
			std::istringstream iss(extendedCorePropFile);

			std::string line;
			while (std::getline(iss, line))
			{
				if (line[0] == '\t') // To find a better condition
				{
					size_t start = line.find("<");
					size_t end = line.find(">");
					if (start != string::npos && end != string::npos)
					{
						size_t end2 = line.find("<", end + 1);
						if (end2 != string::npos)
						{
							d_ptr->extendedCoreProperties[line.substr(start + 1, end - start - 1)] = line.substr(end + 1, end2 - end - 1);
						}
					}
				}
			}
		}
	}

	// Package content type
	string contentTypeFile = extractFile("[Content_Types].xml", "");
	d_ptr->fileContentType.readFromString(contentTypeFile);

	return result;
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
	FilePart fp(outputPartPath);
	d_ptr->allFileParts[outputPartPath] = fp;
    writeStringIntoNewPart( inputContent, outputPartPath );
	return &(d_ptr->allFileParts[outputPartPath]);
}

const FilePart* Package::findPart(const std::string & outputPartPath) const
{
	PartMap::const_iterator it = d_ptr->allFileParts.find(outputPartPath);
	return it == d_ptr->allFileParts.end() ? nullptr : &(it->second);
}

uLong buildTimeInfo(const char *filename, tm_zip *tmzip, uLong *dostime)
{
    int ret = 0;
#ifdef _WIN32
	FILETIME ftUtc;
    FILETIME ftLocal;
    HANDLE hFind;
    WIN32_FIND_DATAA ff32;

    hFind = FindFirstFileA(filename, &ff32);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        FileTimeToLocalFileTime(&(ff32.ftLastWriteTime), &ftLocal);
        FileTimeToDosDateTime(&ftLocal,((LPWORD)dostime)+1,((LPWORD)dostime)+0);
        FindClose(hFind);
        ret = 1;
    }
	else
	{
		GetSystemTimeAsFileTime(&ftUtc);
        FileTimeToLocalFileTime(&ftUtc, &ftLocal);
        FileTimeToDosDateTime(&ftLocal,((LPWORD)dostime)+1,((LPWORD)dostime)+0);
        FindClose(hFind);
        ret = 1;
	}
#else
#if defined unix || defined __APPLE__
    struct stat s = {0};
    struct tm* filedate;
    time_t tm_t = time(0);
    filedate = localtime(&tm_t);

    tmzip->tm_sec  = filedate->tm_sec;
    tmzip->tm_min  = filedate->tm_min;
    tmzip->tm_hour = filedate->tm_hour;
    tmzip->tm_mday = filedate->tm_mday;
    tmzip->tm_mon  = filedate->tm_mon ;
    tmzip->tm_year = filedate->tm_year;
#endif
#endif
    return ret;
}

void Package::writeStringIntoNewPart(const std::string &input, const std::string & partPath)
{
	// Initialize the parameters for the creation of a file in the zip archive
	zip_fileinfo zi;
	zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour = zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;
	zi.dosDate = 0;
	zi.internal_fa = 0;
	zi.external_fa = 0;
	char* tmp = new char[partPath.length() + 1];
	strcpy(tmp, partPath.c_str());
	buildTimeInfo(tmp,&zi.tmz_date,&zi.dosDate);
	delete [] tmp;

	// Open the content type part in the zip archive
	int err = zipOpenNewFileInZip64(d_ptr->zf, partPath.c_str(), &zi,
		nullptr,0,nullptr,0,nullptr /* comment*/,
		Z_DEFLATED,						// method
		Z_DEFAULT_COMPRESSION,				// level
		d_ptr->isZip64);								// Zip64
	if (err != ZIP_OK) {
		throw invalid_argument("Could not open " + partPath + " in the zipfile");
	}

	// Write the content of the content type part
	err = zipWriteInFileInZip(d_ptr->zf, input.c_str(), input.size());
	if (err < 0) {
		throw invalid_argument("Could not write " + partPath + " in the zipfile");
	}

	// Close the content type part
	err = zipCloseFileInZip(d_ptr->zf);
	if (err != ZIP_OK) {
		throw invalid_argument("Could not close " + partPath + " in the zipfile");
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
		ContentType contentTypeExtendedCoreProp(false, "application/x-extended-core-properties+xml", "docProps/extendedCore.xml");
		addContentType(contentTypeExtendedCoreProp);
		
		// Relationhsip with the standard core properties part
		Relationship relToExtCoreProp("extendedCore.xml", EXTENDED_CORE_PROP_REL_TYPE, "ExtendedCoreProperties");
		FileRelationship fileRelToExtCoreProp(relToExtCoreProp);
		fileRelToExtCoreProp.setPathName("docProps/_rels/core.xml.rels");
		writeStringIntoNewPart(fileRelToExtCoreProp.toString(), fileRelToExtCoreProp.getPathName());
	}

	writeStringIntoNewPart(d_ptr->fileContentType.toString(), "[Content_Types].xml");
	
	// write Principal Relationships file.
	if (!d_ptr->filePrincipalRelationship.isEmpty())
		writeStringIntoNewPart(d_ptr->filePrincipalRelationship.toString(), "_rels/.rels");
	
	// Write all the part relationships
	for (PartMap::iterator i = d_ptr->allFileParts.begin(); i != d_ptr->allFileParts.end(); i++){
		if (!i->second.getFileRelationship().isEmpty())
		{
			writeStringIntoNewPart(i->second.getFileRelationship().toString(), i->second.getFileRelationship().getPathName());
		}
	}

	// Close the zip archive
	int err = zipClose(d_ptr->zf, "");
	if (err != ZIP_OK) {
		throw invalid_argument("Could not close " + d_ptr->pathName.substr(0, d_ptr->pathName.size() - 4));
	}
}

string do_extract_currentfile(unzFile uf, const char* password)
{
    int err=UNZ_OK;
    void* buf;
    const unsigned size_buf = 8192;

    buf = (void*)malloc(size_buf);
    if (buf == nullptr)
    {
    	ostringstream oss;
    	oss << "Error allocating " <<  size_buf << " bytes.";
		throw invalid_argument(oss.str());
    }

    err = unzOpenCurrentFilePassword(uf,password);
    if (err != UNZ_OK)
    {
		free(buf);
		throw invalid_argument("Error with zipfile in unzOpenCurrentFilePassword");
    }

	ostringstream oss;
    do
    {
        err = unzReadCurrentFile(uf,buf,size_buf);
        if (err < 0)
        {
			free(buf);
			throw invalid_argument("Error with zipfile in unzReadCurrentFile");
        }
		if (err > 0)
		{
			oss.write((char*)buf, err);
		}
    }
    while (err > 0);

    if (err == UNZ_OK)
    {
        err = unzCloseCurrentFile (uf);
        if (err != UNZ_OK)
        {
			free(buf);
			throw invalid_argument("Error with zipfile in unzCloseCurrentFile");
        }
    }
    else
        unzCloseCurrentFile(uf); /* don't lose the error */

    free(buf);
    return oss.str();
}

bool Package::fileExists(const string & filename) const
{
	if (d_ptr->unzipped == nullptr) {
		throw logic_error("The EPC document must be opened first.");
	}
	return unzLocateFile(d_ptr->unzipped, filename.c_str(), CASESENSITIVITY) == UNZ_OK;
}

string Package::extractFile(const string & filename, const string & password)
{
#ifdef CACHE_FILE_DESCRIPTOR
	std::unordered_map< std::string, unz64_s >::const_iterator it = d_ptr->name2file.find(filename);
	if (it == d_ptr->name2file.end())
	{
		if (!fileExists(filename))
		{
			throw invalid_argument("The file " + filename + " does not exist in the EPC document.");
		}
		d_ptr->name2file[filename] = *(unz64_s*)d_ptr->unzipped;
	}
	else
	{
		*(unz64_s*)d_ptr->unzipped = it->second;
	}
#else
	if (!fileExists(filename))
    {
		throw invalid_argument("The file " + filename + " does not exist in the EPC document.");
    }
#endif

	if (!password.empty())
		return do_extract_currentfile(d_ptr->unzipped, password.c_str());
	else
		return do_extract_currentfile(d_ptr->unzipped, nullptr);
}















