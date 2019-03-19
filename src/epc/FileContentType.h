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



#ifndef FILE_CONTENT_TYPE_H
#define FILE_CONTENT_TYPE_H

#if defined(_WIN32) || defined(__APPLE__)
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif

#include "ContentType.h"

namespace epc
{

	class FileContentType
	{
    public:
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		typedef std::unordered_map<std::string, ContentType> ContentTypeMap;
#else
		typedef std::tr1::unordered_map<std::string, ContentType> ContentTypeMap;
#endif

	private:
		static const char* header;
		ContentTypeMap contentTypeMap;
		static const char* footer;

	public:
		// CONSTRUCTORS
		FileContentType();
		~FileContentType() {};

		// ACCESSORS
		ContentType getContentType(const std::string& extensionOrPartName) const;
		const ContentTypeMap& getAllContentType() const;
		std::string toString() const;

		void addContentType(const ContentType & contentType);

		/**
		* Read a content type part from a string.
		*/
		void readFromString(const std::string & textInput);
	};
}

#endif
