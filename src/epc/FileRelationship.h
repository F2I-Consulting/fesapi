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
#ifndef FILE_RELATIONSHIP_H
#define FILE_RELATIONSHIP_H

#include <vector>

#include "Relationship.h"

namespace epc
{
	/**
	* This class intends to represent any rel file of the package.
	*/
	class FileRelationship
	{
	private:
		std::string pathName;
		std::vector<Relationship> relationship;

	public:
		// CONSTRUCTORS
		FileRelationship() {}
		FileRelationship(const Relationship & frRelationship);
		FileRelationship(const std::vector<Relationship> & frRelationship);
		~FileRelationship() {}

		// ACCESSORS
		bool isEmpty() const;
		const std::string& getPathName() const { return pathName; }
		const std::vector<Relationship>& getAllRelationship() const { return relationship; }
		Relationship getIndexRelationship(size_t index) const;
		std::string toString() const;

		void setPathName(const std::string & frPathName) { pathName = frPathName; }
		void addRelationship(const Relationship & frRelationship);

		/**
		* Read a relationships part from a string.
		*/
		void readFromString(const std::string & textInput);
	};
}

#endif
