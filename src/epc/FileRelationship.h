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
	/** This class intends to represent any rel file of the package. */
	class FileRelationship
	{
	private:
		/** Full pathname of the file */
		std::string pathName;
		/** The relationship */
		std::vector<Relationship> relationship;

	public:
		/** CONSTRUCTORS */
		FileRelationship() {}

		/**
		 * Constructor
		 *
		 * @param 	frRelationship	The fr relationship.
		 */
		FileRelationship(const Relationship & frRelationship);

		/**
		 * Constructor
		 *
		 * @param 	frRelationship	The fr relationship.
		 */
		FileRelationship(const std::vector<Relationship> & frRelationship);
		/** Destructor */
		~FileRelationship() = default;

		/**
		 * ACCESSORS
		 *
		 * @returns	True if empty, false if not.
		 */
		bool isEmpty() const;

		/**
		 * Gets path name
		 *
		 * @returns	The path name.
		 */
		const std::string& getPathName() const { return pathName; }

		/**
		 * Gets all relationship
		 *
		 * @returns	all relationship.
		 */
		const std::vector<Relationship>& getAllRelationship() const { return relationship; }

		/**
		 * Gets index relationship
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The index relationship.
		 */
		Relationship getIndexRelationship(size_t index) const;

		/**
		 * Convert this object into a string representation
		 *
		 * @returns	A std::string that represents this object.
		 */
		std::string toString() const;

		/**
		 * Sets path name
		 *
		 * @param 	frPathName	Full pathname of the fr file.
		 */
		void setPathName(const std::string & frPathName) { pathName = frPathName; }

		/**
		 * Adds a relationship
		 *
		 * @param 	frRelationship	The fr relationship.
		 */
		void addRelationship(const Relationship & frRelationship);

		/**
		 * Read a relationships part from a string.
		 *
		 * @param 	textInput	The text input.
		 */
		void readFromString(const std::string & textInput);
	};
}

#endif
