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
	/**
	* This class intends to represent a relationship entry of a rel file of a package part.
	*/
	class Relationship
	{
	private: 
		bool internalTarget;		/// The target mode indicates wether the destination part is external or internal to the package.
		std::string target;			/// The target indicates the destination part path.
		std::string type;			/// The type indicates the name/type of the relationship.
		std::string id;				/// The id uniquely identify the relationship in the context of the rel file. For epc, it also indicates the uuid of the destiantion object.

	public:
		Relationship(const bool & internalTarget = true);
		Relationship(const std::string & rsTarget, const std::string & rsType,const std::string & rsId, const bool & internalTarget = true);
		~Relationship() {}

		/**
		* Serialize the core property into an XML element embeded into a string.
		*/
		std::string toString() const;

		bool isInternalTarget() const;
		const std::string& getTarget() const;
		const std::string& getType() const;
		const std::string& getId() const;

		void setIsExternalTarget();
		void setIsInternalTarget();
		void setTarget(const std::string & rsTarget);

		/**
		* Set an arbitrary type to the relationship
		*/
		void setType(const std::string & rsType);

		// Set predefined types to the relationship
		void setDestinationObjectType()		{type = "http://schemas.energistics.org/package/2012/relationships/destinationObject";}
		void setSourceObjectType()			{type = "http://schemas.energistics.org/package/2012/relationships/sourceObject";}
		void setDestinationMediaType()		{type = "http://schemas.energistics.org/package/2012/relationships/destinationMedia";}
		void setSourceMediaType()			{type = "http://schemas.energistics.org/package/2012/relationships/sourceMedia";}
		void setChunkedPartType()			{type = "http://schemas.energistics.org/package/2012/relationships/chunkedPart";}
		void setExternalPartProxyToMlType()	{type = "http://schemas.energistics.org/package/2012/relationships/externalPartProxyToMl";}
		void setMlToExternalPartProxyType()	{type = "http://schemas.energistics.org/package/2012/relationships/mlToExternalPartProxy";}
		void setExternalResourceType()		{type = "http://schemas.energistics.org/package/2012/relationships/externalResource";}

		/**
		* Set an arbitrary id to the relationship
		*/
		void setId(const std::string & rsId);
	};

	bool operator==(const Relationship& r1, const Relationship& r2);
}

#endif
