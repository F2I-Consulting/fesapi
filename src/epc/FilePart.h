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
#ifndef FILE_PART_H
#define FILE_PART_H

#include "FileRelationship.h"

namespace epc
{

	/** A file part. */
	class FilePart
	{
	private:
		/** The associated rel file to the part */
		FileRelationship fileRelationship;

	public:

		/** Default constructor */
		FilePart();

		/**
		* Constructor
		* @param inputContent		The content which will be included into a part of the package
		* @param outputPartPath		The path of the part within the package.
		*/
		FilePart(std::string outputPartPath);
		~FilePart() {}

		// ACCESSORS
		const FileRelationship & getFileRelationship() const;

		/**
		 * Gets index relationship
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The index relationship.
		 */
		Relationship getIndexRelationship(int index) const;

		/**
		 * Copy an existing relationship into the relationship set of the part.
		 *
		 * @param 	relationship	The relationship.
		 */
		void addRelationship(const Relationship & relationship);

		/**
		 * Creates a new relationship into the relationship set of the part according to the supplied
		 * parameters
		 *
		 * @param 	rsTarget	  	The RS target.
		 * @param 	rsType		  	Type of the RS.
		 * @param 	rsId		  	Identifier for the RS.
		 * @param 	internalTarget	(Optional) True to internal target.
		 */
		void createRelationship(const std::string & rsTarget, const std::string & rsType,const std::string & rsId, bool internalTarget = true);
	};
}

#endif
