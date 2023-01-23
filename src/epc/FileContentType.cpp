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

using namespace std; // in order not to prefix by "std::" for each class in the "std" namespace. Never use "using namespace" in *.h file but only in*.cpp file!!!
using namespace epc; // in order not to prefix by "epc::" for each class in the "epc" namespace. Never use "using namespace" in *.h file but only in*.cpp file!!!

ContentType FileContentType::getContentType(const std::string& extensionOrPartName) const
{
    auto it = contentTypeMap.find("/" + extensionOrPartName);
    return it == contentTypeMap.end() ? ContentType() : it->second;
}

std::string FileContentType::toString() const
{
	// HEADER
	ostringstream oss;
	oss << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << std::endl;
	oss << "<Types xmlns = \"http://schemas.openxmlformats.org/package/2006/content-types\">" << endl;
	
	// CONTENT
	for (const auto& contentType : contentTypeMap) {
		oss << "\t" << contentType.second.toString() << endl;
	}

	// FOOTER
	oss << "</Types>" << endl;

	return oss.str();
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
			const size_t attEnd = textInput.find('\"', attStart);
			if (attStart != string::npos && attEnd != string::npos)
				extension = textInput.substr(attStart, attEnd - attStart);
		}

		// Content type
		string contentType = "";
		attStart = textInput.find("ContentType=\"", pos);
		if (attStart != string::npos && attStart < end)
		{
			attStart += 13;
			const size_t attEnd = textInput.find('\"', attStart);
			if (attStart != string::npos && attEnd != string::npos)
				contentType = textInput.substr(attStart, attEnd - attStart);
		}

		ContentType entry(true, contentType, extension);
		addContentType(entry);

		pos = textInput.find("Default", end + 1);
	}

	// Override partname
	pos = textInput.find("Override");
	while (pos != string::npos) {
		size_t end = textInput.find("/>", pos + 8);
		if (end == string::npos) {
			end = textInput.find("Override>", pos + 8);
		}
		
		// Extension
		string partName = "";
		size_t attStart = textInput.find("PartName=\"", pos);
		if (attStart != string::npos && attStart < end) {
			attStart += 10;
			const size_t attEnd = textInput.find('\"', attStart);
			if (attStart != string::npos && attEnd != string::npos) {
				partName = textInput.substr(attStart, attEnd - attStart);
			}
		}

		// Content type
		string contentType = "";
		attStart = textInput.find("ContentType=\"", pos);
		if (attStart != string::npos && attStart < end) {
			attStart += 13;
			const size_t attEnd = textInput.find('\"', attStart);
			if (attStart != string::npos && attEnd != string::npos) {
				contentType = textInput.substr(attStart, attEnd - attStart);
			}
		}

		ContentType entry(false, contentType, partName);
		addContentType(entry);

		pos = textInput.find("Override", end + 1);
	}
}
