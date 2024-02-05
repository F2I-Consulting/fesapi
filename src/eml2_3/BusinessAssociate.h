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
#pragma once

#include "../common/AbstractObject.h"

namespace EML2_3_NS
{
	/** @brief	Describes any company, person, group, consultant, etc., which is associated within a context (e.g., a well).
	 * The information contained in this module is:
	 *   (1) contact information, such as address, phone numbers, email,
	 *   (2) alternate name, or aliases, and
	 *   (3) associations, such as the business associate that this one is associated with, or a contact who is associated with this business associate.
	 */
	class BusinessAssociate : public COMMON_NS::AbstractObject
	{
	public:

		/**
		 * Constructor. Only to be used in partial transfer context
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		BusinessAssociate(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		 * Creates a BusinessAssociate.
		 *
		 * @exception	std::invalid_argument	If @p repo is null.
		 *
		 * @param [in,out]	repo 	The repository where the underlying gSOAP proxy is going to be
		 * 							created.
		 * @param 		  	guid 	The guid to set to BusinessAssociate. If empty then a new
		 * 							guid will be generated.
		 * @param 		  	title	A title for BusinessAssociate. If empty then \"unknown\"
		 * 							title will be set.
		 */
		BusinessAssociate(COMMON_NS::DataObjectRepository* repo, std::string const& guid, std::string const& title);

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		BusinessAssociate(gsoap_eml2_3::_eml23__BusinessAssociate* fromGsoap) :
			COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		 * Destructor does nothing since the memory is managed by the gsoap context.
		 */
		~BusinessAssociate() = default;

		/** The standard XML tag without XML namespace for serializing this data object */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "BusinessAssociate";

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const { return XML_TAG; }

		/**
		 * Reads the forward relationships of this data object and update the <tt>.rels</tt> of the
		 * associated data repository.
		 */
		void loadTargetRelationships() final {}

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "eml23";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
