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
#include "FileContentType.h"

#include <sstream>
#include <stdexcept>

using namespace std; // in order not to prefix by "std::" for each class in the "std" namespace. Never use "using namespace" in *.h file but only in*.cpp file!!!
using namespace epc; // in order not to prefix by "epc::" for each class in the "epc" namespace. Never use "using namespace" in *.h file but only in*.cpp file!!!

const char* FileContentType::header = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<Types xmlns=\"http://schemas.openxmlformats.org/package/2006/content-types\">";
const char* FileContentType::footer = "</Types>";

FileContentType::FileContentType()
{
}

ContentType FileContentType::getContentType(const std::string& extensionOrPartName) const
{
    ContentTypeMap::const_iterator it = contentTypeMap.find("/"+ extensionOrPartName);
    if(it==contentTypeMap.end()){
        return ContentType();
    }
    return it->second;
}

const FileContentType::ContentTypeMap& FileContentType::getAllContentType() const
{
	return contentTypeMap;
}

std::string FileContentType::toString() const
{
	// HEADER
	ostringstream oss;
	oss << header << endl;
	
	// CONTENT
	for(ContentTypeMap::const_iterator i=contentTypeMap.begin(); i!=contentTypeMap.end(); i++)
	{
		oss << "\t" << i->second.toString() << endl;
	}

	// FOOTER
	oss << footer << endl;

	return oss.str();
}

void FileContentType::addContentType(const ContentType & contentType)
{
	if (contentTypeMap.find(contentType.getExtensionOrPartName()) == contentTypeMap.end()) {
		contentTypeMap[contentType.getExtensionOrPartName()] = contentType;
	}
}

void FileContentType::readFromString(const string & textInput)
{
	contentTypeMap.clear();

	// Default extension
	size_t pos = textInput.find("Default");
	while (pos != string::npos)
	{
		size_t end = textInput.find("/>", pos + 7);
		if (end == string::npos)
			end = textInput.find("Default>", pos + 7);
		
		// Extension
		string extension = "";
		size_t attStart = textInput.find("Extension=\"", pos);
		if (attStart != string::npos && attStart < end)
		{
			attStart += 11;
			size_t attEnd = textInput.find("\"", attStart);
			if (attStart != string::npos && attEnd != string::npos)
				extension = textInput.substr(attStart, attEnd - attStart);
		}

		// Content type
		string contentType = "";
		attStart = textInput.find("ContentType=\"", pos);
		if (attStart != string::npos && attStart < end)
		{
			attStart += 13;
			size_t attEnd = textInput.find("\"", attStart);
			if (attStart != string::npos && attEnd != string::npos)
				contentType = textInput.substr(attStart, attEnd - attStart);
		}

		ContentType entry(true, contentType, extension);
		addContentType(entry);

		pos = textInput.find("Default", end + 1);
	}

	// Override partname
	pos = textInput.find("Override");
	while (pos != string::npos)
	{
		size_t end = textInput.find("/>", pos + 8);
		if (end == string::npos)
			end = textInput.find("Override>", pos + 8);
		
		// Extension
		string partName = "";
		size_t attStart = textInput.find("PartName=\"", pos);
		if (attStart != string::npos && attStart < end)
		{
			attStart += 10;
			size_t attEnd = textInput.find("\"", attStart);
			if (attStart != string::npos && attEnd != string::npos)
				partName = textInput.substr(attStart, attEnd - attStart);
		}

		// Content type
		string contentType = "";
		attStart = textInput.find("ContentType=\"", pos);
		if (attStart != string::npos && attStart < end)
		{
			attStart += 13;
			size_t attEnd = textInput.find("\"", attStart);
			if (attStart != string::npos && attEnd != string::npos)
				contentType = textInput.substr(attStart, attEnd - attStart);
		}

		ContentType entry(false, contentType, partName);
		addContentType(entry);

		pos = textInput.find("Override", end + 1);
	}
}

