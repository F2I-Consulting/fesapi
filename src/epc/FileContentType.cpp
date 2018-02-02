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
















