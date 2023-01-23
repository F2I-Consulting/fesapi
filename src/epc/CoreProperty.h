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
#ifndef CORE_PROPERTY_H
#define CORE_PROPERTY_H

#include <vector>
#include <string>

namespace epc
{
	/** A core property. */
	class CoreProperty
	{		
	public:

		/** Enumeration of the various types of the core properties. */
		enum TypeProperty {
			category = 0,
			contentStatus = 1,
			created = 2,
			creator = 3,
			description = 4,
			identifier = 5,
			keywords = 6,
			language = 7,
			lastModifiedBy = 8,
			lastPrinted = 9,
			modified = 10,
			revision = 11,
			subject = 12,
			title = 13,
			version = 14,
			undefinedCoreProperty = 15
		};

		/** Default constructor */
		CoreProperty();

		/**
		 * Constructor
		 *
		 * @param 	pType	The type.
		 */
		explicit CoreProperty(TypeProperty pType);

		/**
		 * Constructor
		 *
		 * @param 	pType 	The type.
		 * @param 	pValue	The value.
		 */
		CoreProperty(TypeProperty pType, const std::string & pValue);

		/**
		 * Constructor
		 *
		 * @param 	pType 	The type.
		 * @param 	pValue	The value.
		 */
		CoreProperty(TypeProperty pType, const std::vector<std::string> & pValue);
		/** Destructor */
		~CoreProperty() = default;

		/**
		 * Indicate wether a property has got a string value or not
		 *
		 * @returns	True if empty, false if not.
		 */
		bool isEmpty() const;

		/**
		 * Get the type of the core property.
		 *
		 * @returns	The type property.
		 */
		TypeProperty getTypeProperty() const;

		/**
		 * Set the type of the core property
		 *
		 * @param 	corePropertyType	Type of the core property.
		 */
		void setTypeProperty(TypeProperty corePropertyType);

		/**
		 * Get all the string values. Relevant only for some core properties which can have several
		 * string values (such as keywords)
		 *
		 * @returns	all value.
		 */
		const std::vector<std::string>& getAllValue() const;

		/**
		 * Get the first string value of the core property. Usually this method is the common one for
		 * retrieving string value of a core property since most of timeonly one string value is
		 * necessary for one core property.
		 *
		 * @param 	index	(Optional) Zero-based index of the.
		 *
		 * @returns	The value.
		 */
		std::string getValue(size_t index = 0) const;

		/**
		 * Serialize the core property into an XML element embeded into a string.
		 *
		 * @returns	A std::string that represents this object.
		 */
		std::string toString() const;

		/**
		 * Sets a category
		 *
		 * @param 	pValue	The value.
		 */
		void setCategory(std::string pValue);

		/**
		 * Sets content status
		 *
		 * @param 	pValue	The value.
		 */
		void setContentStatus(std::string pValue);

		/**
		 * Sets a created
		 *
		 * @param 	pValue	The value.
		 */
		void setCreated(std::string pValue);

		/**
		 * Sets a creator
		 *
		 * @param 	pValue	The value.
		 */
		void setCreator(std::string pValue);

		/**
		 * Sets a description
		 *
		 * @param 	pValue	The value.
		 */
		void setDescription(std::string pValue);

		/**
		 * Sets an identifier
		 *
		 * @param 	pValue	The value.
		 */
		void setIdentifier(std::string pValue);

		/**
		 * Sets the keywords
		 *
		 * @param 	pValue	The value.
		 */
		void setKeywords(std::string pValue);

		/**
		 * Adds the keywords
		 *
		 * @param 	pValue	The value.
		 */
		void addKeywords(std::string pValue);

		/**
		 * Sets a language
		 *
		 * @param 	pValue	The value.
		 */
		void setLanguage(std::string pValue);

		/**
		 * Sets last modified by
		 *
		 * @param 	pValue	The value.
		 */
		void setLastModifiedBy(std::string pValue);

		/**
		 * Sets last printed
		 *
		 * @param 	pValue	The value.
		 */
		void setLastPrinted(std::string pValue);

		/**
		 * Sets a modified
		 *
		 * @param 	pValue	The value.
		 */
		void setModified(std::string pValue);

		/**
		 * Sets a revision
		 *
		 * @param 	pValue	The value.
		 */
		void setRevision(std::string pValue);

		/**
		 * Sets a subject
		 *
		 * @param 	pValue	The value.
		 */
		void setSubject(std::string pValue);

		/**
		 * Sets a title
		 *
		 * @param 	pValue	The value.
		 */
		void setTitle(std::string pValue);

		/**
		 * Sets a version
		 *
		 * @param 	pValue	The value.
		 */
		void setVersion(std::string pValue);
		
	private:
		/** / The type of the core property */
		TypeProperty type;

		/**
		 * / The string value of the core property. Can be multiple for some core properties (such as
		 * keywords)
		 */
		std::vector<std::string> value;
	};
}

#endif
