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
	class CoreProperty
	{		
	public:

		/**
		* Enumeration of the various types of the core properties.
		*/
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

		CoreProperty();
		CoreProperty(const TypeProperty & pType);
		CoreProperty(const TypeProperty & pType, const std::string & pValue);
		CoreProperty(const TypeProperty & pType, const std::vector<std::string> & pValue);
		~CoreProperty() {}

		/**
		* Indicate wether a property has got a string value or not
		*/
		bool isEmpty() const;

		/**
		* Get the type of the core property.
		*/
		TypeProperty getTypeProperty() const;

		/**
		* Set the type of the core property
		*/
		void setTypeProperty(const TypeProperty & corePropertyType);

		/**
		* Get the first string value of the core property.
		* Usually this method is the common one for retrieving string value of a core property since most of timeonly one string value is necessary for one core property.
		*/
		std::string getValue(const int & index = 0) const;

		/**
		* Serialize the core property into an XML element embeded into a string.
		*/
		std::string toString() const;

		void setCategory(std::string pValue);
		void setContentStatus(std::string pValue);
		void setCreated(std::string pValue);
		void setCreator(std::string pValue);
		void setDescription(std::string pValue);
		void setIdentifier(std::string pValue);
		void setKeywords(std::string pValue);
		void addKeywords(std::string pValue);
		void setLanguage(std::string pValue);
		void setLastModifiedBy(std::string pValue);
		void setLastPrinted(std::string pValue);
		void setModified(std::string pValue);
		void setRevision(std::string pValue);
		void setSubject(std::string pValue);
		void setTitle(std::string pValue);
		void setVersion(std::string pValue);
		
	private:
		TypeProperty type;				/// The type of the core property
		std::vector<std::string> value;	/// The string value of the core property. Can be multiple for some core properties (such as keywords)
	};
}

#endif
