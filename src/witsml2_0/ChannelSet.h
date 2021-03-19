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

#include "ChannelIndexDataObject.h"

namespace WITSML2_0_NS
{
	/**
	 * Grouping of Channels with a compatible index for some purpose. By compatible index, we simply
	 * mean that all of the Channels are either in time or in depth using a common datum
	 */
	class ChannelSet : public ChannelIndexDataObject<gsoap_eml2_1::witsml20__ChannelSet>
	{
	public:

		/**
		 * Constructor for partial transfer
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT ChannelSet(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : ChannelIndexDataObject<gsoap_eml2_1::witsml20__ChannelSet>(partialObject) {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	repo 	If non-null, the repo.
		 * @param 		  	guid 	Unique identifier.
		 * @param 		  	title	The title.
		 */
		ChannelSet(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		ChannelSet(gsoap_eml2_1::witsml20__ChannelSet* fromGsoap) : ChannelIndexDataObject<gsoap_eml2_1::witsml20__ChannelSet>(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~ChannelSet() = default;

		/**
		 * Pushes a back channel index
		 *
		 * @param 	indexType   	Type of the index.
		 * @param 	uom				The uom.
		 * @param 	mnemonic		The mnemonic.
		 * @param 	isIncreasing	(Optional) True if is increasing, false if not.
		 * @param 	datum			(Optional) The datum.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackChannelIndex(gsoap_eml2_1::witsml20__ChannelIndexType indexType, gsoap_eml2_1::eml21__UnitOfMeasure uom, const std::string & mnemonic, bool isIncreasing = true, const std::string & datum = "");

		/**
		 * Pushes a back channel
		 *
		 * @param [in,out]	channel	If non-null, the channel.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackChannel(class Channel * channel);

		/**
		 * Sets data as JSON array
		 *
		 * @param 	jsonArray	Array of jsons.
		 */
		DLL_IMPORT_OR_EXPORT void setDataAsJsonArray(const std::string & jsonArray);

		/**
		 * Sets data as file URI
		 *
		 * @param 	fileUri	URI of the file.
		 */
		DLL_IMPORT_OR_EXPORT void setDataAsFileUri(const std::string & fileUri);

		/**
		 * Query if this object has data as JSON array
		 *
		 * @returns	True if data as JSON array, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasDataAsJsonArray() const;

		/**
		 * Query if this object has data as file URI
		 *
		 * @returns	True if data as file uri, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasDataAsFileUri() const;

		/**
		 * Gets data as JSON array
		 *
		 * @returns	The data as JSON array.
		 */
		DLL_IMPORT_OR_EXPORT const std::string & getDataAsJsonArray() const;

		/**
		 * Gets data as file URI
		 *
		 * @returns	The data as file URI.
		 */
		DLL_IMPORT_OR_EXPORT const std::string & getDataAsFileUri() const;

		/**
		 * Gets the logs
		 *
		 * @returns	Null if it fails, else the logs.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<class Log*> getLogs() const;

		/**
		 * Gets the channels
		 *
		 * @returns	Null if it fails, else the channels.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<class Channel*> getChannels() const;

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
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

		/** Loads target relationships */
		void loadTargetRelationships();

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char XML_NS[] = "witsml20";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
