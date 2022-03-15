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

#include "ChannelMetaDataObject.h"

namespace WITSML2_0_NS
{
	/** Primarily a container for one or more channel sets (ChannelSet). */
	class Log : public ChannelMetaDataObject<gsoap_eml2_1::witsml20__Log>
	{
	public:

		/**
		 * Constructor for partial transfer
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT Log(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : ChannelMetaDataObject(partialObject) {}

		/**
		 * @brief	Constructor
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWellbore == nullptr</tt>.
		 *
		 * @param [in]	witsmlWellbore	If non-null, the witsml wellbore.
		 * @param 	  	guid		  	Unique identifier.
		 * @param 	  	title		  	The title.
		 */
		Log(WITSML2_NS::Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		Log(gsoap_eml2_1::witsml20__Log* fromGsoap) : ChannelMetaDataObject(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~Log() = default;

		/**
		 * Pushes a back channel set
		 *
		 * @param [in,out]	channelSet	If non-null, set the channel belongs to.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackChannelSet(class ChannelSet * channelSet);

		/**
		 * Gets channel sets
		 *
		 * @returns	Null if it fails, else the channel sets.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<class ChannelSet*> getChannelSets() const;

/**
 * A macro that defines setter generic optional attribute
 *
 * @param 	attributeDatatype	The attribute datatype.
 * @param 	attributeName	 	Name of the attribute.
 */
#define SETTER_GENERIC_OPTIONAL_ATTRIBUTE(attributeDatatype, attributeName)\
		DLL_IMPORT_OR_EXPORT void set##attributeName(const attributeDatatype & attributeName);

		SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, TimeDepth)
		SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, RunNumber)
		SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, PassNumber)
		SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, LoggingCompanyName)
		SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, LoggingCompanyCode)
		SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, ToolName)
		SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, ToolClass)

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "Log";

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

		/** Loads target relationships */
		void loadTargetRelationships() final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "witsml20";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
