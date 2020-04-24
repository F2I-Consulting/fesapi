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
#ifndef CONTENT_TYPE_H
#define CONTENT_TYPE_H

#include <string>

namespace epc
{
	/** A content type. */
	class ContentType
	{
	private:
		/** The content type string */
		std::string contentTypeString;
		/** Name of the extension or part */
		std::string extensionOrPartName;

	public:
		/** / if false, the content type is associated to a part and overrides another content type. */
		bool isAssociatedToAnExtension;

		/**
		 * The part URI grammar is defined as follows: part-URI  = 1*( "/" segment )
		 * segment   = 1*( pchar )
		 * pchar is defined in RFC 3986
		 * 
		 * The part URI grammar implies the following constraints. The package implementer shall neither
		 * create any part that violates these constraints nor retrieve any data from a package as a
		 * part if the purported part URI violates these constraints.  
		 * *  A part URI shall not be empty. [Note: The Mx.x notation is discussed in ?2. end note]
		 * *  A part URI shall not have empty segments.
		 * *  A part URI shall start with a forward slash (?/?) character.
		 * *  A part URI shall not have a forward slash as the last character.
		 * *  A segment shall not hold any characters other than pchar characters.
		 * Part URI segments have the following additional constraints. The package implementer shall
		 * neither create any part with a part URI comprised of a segment that violates these
		 * constraints nor retrieve any data from a package as a part if the purported part URI contains
		 * a segment that violates these constraints.
		 * *  A segment shall not contain percent-encoded forward slash (?/?), or backward slash (?\?)
		 * characters.
		 * *  A segment shall not contain percent-encoded unreserved characters.
		 * *  A segment shall not end with a dot (?.?) character.
		 * *  A segment shall include at least one non-dot character.
		 */
		ContentType(){};

		/**
		 * Constructor
		 *
		 * @param 	isAssociatedToAnExt	True if is associated to an extent, false if not.
		 * @param 	contentType		   	Type of the content.
		 * @param 	extOrPartName	   	Name of the extent or part.
		 */
		ContentType(bool isAssociatedToAnExt, const std::string & contentType, const std::string & extOrPartName);
		/** Destructor */
		~ContentType() {};

		/**
		 * GETTTERS
		 *
		 * @returns	The content type string.
		 */
		const std::string & getContentTypeString() const;

		/**
		 * Gets extension or part name
		 *
		 * @returns	The extension or part name.
		 */
		const std::string & getExtensionOrPartName() const;

		/**
		 * SETTERS
		 *
		 * @param 	ctString	The ct string.
		 */
		void setContentTypeString(const std::string & ctString) {contentTypeString = ctString;}

		/**
		 * Sets extension or part name
		 *
		 * @param 	extOrPartName	Name of the extent or part.
		 */
		void setExtensionOrPartName(const std::string & extOrPartName) {extensionOrPartName = extOrPartName;}

		/**
		 * Convert this object into a string representation
		 *
		 * @returns	A std::string that represents this object.
		 */
		std::string toString() const;
	};
}

#endif
