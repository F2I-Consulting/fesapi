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
#ifndef RELATIONSHIP_H
#define RELATIONSHIP_H

#include <string>

namespace epc
{
	/** This class intends to represent a relationship entry of a rel file of a package part. */
	class Relationship
	{
	private: 

		/**
		 * / The target mode indicates wether the destination part is external or internal to the
		 * package.
		 */
		bool internalTarget;
		/** / The target indicates the destination part path. */
		std::string target;
		/** / The type indicates the name/type of the relationship. */
		std::string type;

		/**
		 * / The id uniquely identify the relationship in the context of the rel file. For epc, it also
		 * indicates the uuid of the destiantion object.
		 */
		std::string id;

	public:

		/**
		 * Constructor
		 *
		 * @param 	internalTarget	(Optional) True to internal target.
		 */
		Relationship(const bool & internalTarget = true);

		/**
		 * Constructor
		 *
		 * @param 	rsTarget	  	The RS target.
		 * @param 	rsType		  	Type of the RS.
		 * @param 	rsId		  	Identifier for the RS.
		 * @param 	internalTarget	(Optional) True to internal target.
		 */
		Relationship(const std::string & rsTarget, const std::string & rsType,const std::string & rsId, const bool & internalTarget = true);
		/** Destructor */
		~Relationship() {}

		/**
		 * Serialize the core property into an XML element embeded into a string.
		 *
		 * @returns	A std::string that represents this object.
		 */
		std::string toString() const;

		/**
		 * Query if this object is internal target
		 *
		 * @returns	True if internal target, false if not.
		 */
		bool isInternalTarget() const;

		/**
		 * Gets the target
		 *
		 * @returns	The target.
		 */
		const std::string& getTarget() const;

		/**
		 * Gets the type
		 *
		 * @returns	The type.
		 */
		const std::string& getType() const;

		/**
		 * Gets the identifier
		 *
		 * @returns	The identifier.
		 */
		const std::string& getId() const;

		/** Sets is external target */
		void setIsExternalTarget();
		/** Sets is internal target */
		void setIsInternalTarget();

		/**
		 * Sets a target
		 *
		 * @param 	rsTarget	The RS target.
		 */
		void setTarget(const std::string & rsTarget);

		/**
		 * Set an arbitrary type to the relationship
		 *
		 * @param 	rsType	Type of the RS.
		 */
		void setType(const std::string & rsType);

		/** Set predefined types to the relationship */
		void setDestinationObjectType()		{type = "http://schemas.energistics.org/package/2012/relationships/destinationObject";}
		/** Sets source object type */
		void setSourceObjectType()			{type = "http://schemas.energistics.org/package/2012/relationships/sourceObject";}
		/** Sets destination media type */
		void setDestinationMediaType()		{type = "http://schemas.energistics.org/package/2012/relationships/destinationMedia";}
		/** Sets source media type */
		void setSourceMediaType()			{type = "http://schemas.energistics.org/package/2012/relationships/sourceMedia";}
		/** Sets chunked part type */
		void setChunkedPartType()			{type = "http://schemas.energistics.org/package/2012/relationships/chunkedPart";}
		/** Sets external part proxy to miles type */
		void setExternalPartProxyToMlType()	{type = "http://schemas.energistics.org/package/2012/relationships/externalPartProxyToMl";}
		/** Sets miles to external part proxy type */
		void setMlToExternalPartProxyType()	{type = "http://schemas.energistics.org/package/2012/relationships/mlToExternalPartProxy";}
		/** Sets external resource type */
		void setExternalResourceType()		{type = "http://schemas.energistics.org/package/2012/relationships/externalResource";}

		/**
		 * Set an arbitrary id to the relationship
		 *
		 * @param 	rsId	Identifier for the RS.
		 */
		void setId(const std::string & rsId);
	};

	/**
	 * Equality operator
	 *
	 * @param 	r1	The first instance to compare.
	 * @param 	r2	The second instance to compare.
	 *
	 * @returns	True if the parameters are considered equivalent.
	 */
	bool operator==(const Relationship& r1, const Relationship& r2);
}

#endif
