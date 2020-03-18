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
#ifndef FILE_CORE_PROPERTIES_H
#define FILE_CORE_PROPERTIES_H

#include "CoreProperty.h"

/** . */
namespace epc
{
	/** A file core properties. */
	class FileCoreProperties
	{
	private:
		/** The properties[ core property undefined core property] */
		CoreProperty properties[CoreProperty::undefinedCoreProperty];

	public:
		/** Default constructor */
		FileCoreProperties();
		/** Destructor */
		~FileCoreProperties() {}

		/**
		 * Gets a property
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The property.
		 */
		CoreProperty getProperty(const CoreProperty::TypeProperty & index) const;

		/**
		 * Convert this object into a string representation
		 *
		 * @returns	A std::string that represents this object.
		 */
		std::string toString() const;

		/**
		 * Initialize all the core properties with their default values. If a core property has not
		 * default value then this method keep it unchanged.
		 */
		void initDefaultCoreProperties();

		/**
		 * Sets a category
		 *
		 * @param 	value	The value.
		 */
		void setCategory(const std::string & value);

		/**
		 * Sets content status
		 *
		 * @param 	value	The value.
		 */
		void setContentStatus(const std::string & value);

		/**
		 * Sets a created
		 *
		 * @param 	value	The value.
		 */
		void setCreated(const std::string & value);

		/**
		 * Sets a creator
		 *
		 * @param 	value	The value.
		 */
		void setCreator(const std::string & value);

		/**
		 * Sets a description
		 *
		 * @param 	value	The value.
		 */
		void setDescription(const std::string & value);

		/**
		 * Sets an identifier
		 *
		 * @param 	value	The value.
		 */
		void setIdentifier(const std::string & value);

		/**
		 * Sets the keywords
		 *
		 * @param 	value	The value.
		 */
		void setKeywords(const std::string & value);

		/**
		 * Adds the keywords
		 *
		 * @param 	value	The value.
		 */
		void addKeywords(const std::string & value);

		/**
		 * Sets a language
		 *
		 * @param 	value	The value.
		 */
		void setLanguage(const std::string & value);

		/**
		 * Sets last modified by
		 *
		 * @param 	value	The value.
		 */
		void setLastModifiedBy(const std::string & value);

		/**
		 * Sets last printed
		 *
		 * @param 	value	The value.
		 */
		void setLastPrinted(const std::string & value);

		/**
		 * Sets a modified
		 *
		 * @param 	value	The value.
		 */
		void setModified(const std::string & value);

		/**
		 * Sets a revision
		 *
		 * @param 	value	The value.
		 */
		void setRevision(const std::string & value);

		/**
		 * Sets a subject
		 *
		 * @param 	value	The value.
		 */
		void setSubject(const std::string & value);

		/**
		 * Sets a title
		 *
		 * @param 	value	The value.
		 */
		void setTitle(const std::string & value);

		/**
		 * Sets a version
		 *
		 * @param 	value	The value.
		 */
		void setVersion(const std::string & value);

		/**
		 * Read a core properties part from a string.
		 *
		 * @param 	textInput	The text input.
		 */
		void readFromString(const std::string & textInput);
	};
}

#endif
