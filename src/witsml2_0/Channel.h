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
	/** Channels are the fundamental unit of organization for WITSML logs. */
	class Channel : public ChannelIndexDataObject<gsoap_eml2_1::witsml20__Channel>
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT Channel(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : ChannelIndexDataObject<gsoap_eml2_1::witsml20__Channel>(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>propertyKind == nullptr</tt>.
		 *
		 * @param [in]	propertyKind	  	If non-null, the property kind.
		 * @param 	  	guid			  	The guid to set to this instance. If empty then a new guid
		 * 									will be generated.
		 * @param 	  	title			  	The title.
		 * @param 	  	mnemonic		  	The mnemonic.
		 * @param 	  	uom				  	The uom.
		 * @param 	  	dataType		  	Type of the data.
		 * @param 	  	growingStatus	  	The growing status.
		 * @param 	  	timeDepth		  	Depth of the time.
		 * @param 	  	loggingCompanyName	Name of the logging company.
		 */
		Channel(EML2_NS::PropertyKind * propertyKind, 
			const std::string & guid, const std::string & title,
			const std::string & mnemonic, gsoap_eml2_1::eml21__UnitOfMeasure uom, gsoap_eml2_1::witsml20__EtpDataType dataType, gsoap_eml2_1::witsml20__ChannelStatus growingStatus,
			const std::string & timeDepth, const std::string & loggingCompanyName);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		Channel(gsoap_eml2_1::witsml20__Channel* fromGsoap):ChannelIndexDataObject<gsoap_eml2_1::witsml20__Channel>(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~Channel() {}

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
		 * Gets channel sets
		 *
		 * @returns	Null if it fails, else the channel sets.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<class ChannelSet*> getChannelSets() const;

		/**
		 * Gets property kind
		 *
		 * @returns	Null if it fails, else the property kind.
		 */
		DLL_IMPORT_OR_EXPORT EML2_NS::PropertyKind* getPropertyKind() const;

		/**
		 * @brief	Gets property kind dor
		 *
		 * @returns	The property kind dor.
		 */
		COMMON_NS::DataObjectReference getPropertyKindDor() const;

		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(std::string, Mnemonic)
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(std::string, Uom)
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(gsoap_eml2_1::witsml20__EtpDataType, DataType)
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(gsoap_eml2_1::witsml20__ChannelStatus, GrowingStatus)

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
	};
}
