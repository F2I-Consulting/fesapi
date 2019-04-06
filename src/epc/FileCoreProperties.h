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

namespace epc
{
	class FileCoreProperties
	{
	private:
		CoreProperty properties[CoreProperty::undefinedCoreProperty];

	public:
		FileCoreProperties();
		~FileCoreProperties() {}

		CoreProperty getProperty(const CoreProperty::TypeProperty & index) const;
		std::string toString() const;

		/**
		* Initialize all the core properties with their default values.
		* If a core property has not default value then this method keep it unchanged.
		*/
		void initDefaultCoreProperties();

		void setCategory(const std::string & value);
		void setContentStatus(const std::string & value);
		void setCreated(const std::string & value);
		void setCreator(const std::string & value);
		void setDescription(const std::string & value);
		void setIdentifier(const std::string & value);
		void setKeywords(const std::string & value);
		void addKeywords(const std::string & value);
		void setLanguage(const std::string & value);
		void setLastModifiedBy(const std::string & value);
		void setLastPrinted(const std::string & value);
		void setModified(const std::string & value);
		void setRevision(const std::string & value);
		void setSubject(const std::string & value);
		void setTitle(const std::string & value);
		void setVersion(const std::string & value);

		/**
		* Read a core properties part from a string.
		*/
		void readFromString(const std::string & textInput);
	};
}

#endif
