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

#include <unordered_map>

#include "ContentType.h"

namespace epc
{
	/** A file content type. */
	class FileContentType
	{
    public:
		/** Defines an alias representing the content type map */
		typedef std::unordered_map<std::string, ContentType> ContentTypeMap;

	private:
		/** The header */
		static const char* header;
		/** The content type map */
		ContentTypeMap contentTypeMap;
		/** The footer */
		static const char* footer;

	public:
		/** CONSTRUCTORS */
		FileContentType();
		/** Destructor */
		~FileContentType() = default;;

		/**
		 * ACCESSORS
		 *
		 * @param 	extensionOrPartName	Name of the extension or part.
		 *
		 * @returns	The content type.
		 */
		ContentType getContentType(const std::string& extensionOrPartName) const;

		/**
		 * Gets all content type
		 *
		 * @returns	all content type.
		 */
		const ContentTypeMap& getAllContentType() const;

		/**
		 * Convert this object into a string representation
		 *
		 * @returns	A std::string that represents this object.
		 */
		std::string toString() const;

		/**
		 * Adds a content type
		 *
		 * @param 	contentType	Type of the content.
		 */
		void addContentType(const ContentType & contentType);

		/**
		 * Read a content type part from a string.
		 *
		 * @param 	textInput	The text input.
		 */
		void readFromString(const std::string & textInput);
	};
}

#endif
