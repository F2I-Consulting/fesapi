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

#include "../MacroDefinitions.h"

namespace EML2_3_NS
{
	class BusinessAssociate;
}

namespace WITSML2_1_NS
{
	/** Channels are the fundamental unit of organization for WITSML logs. */
	class Channel : public ChannelIndexDataObject<gsoap_eml2_3::witsml21__Channel>
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT Channel(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : ChannelIndexDataObject<gsoap_eml2_3::witsml21__Channel>(partialObject) {}

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
		 * @param 	  	dataKind		  	Kind of the data.
		 * @param 	  	loggingCompany	The loggingCompany
		 * @param 	  	isActive	  	True if is active, false if not.
		 */
		Channel(EML2_NS::PropertyKind * propertyKind, 
			const std::string & guid, const std::string & title,
			const std::string & mnemonic, gsoap_eml2_3::eml23__UnitOfMeasure uom, gsoap_eml2_3::witsml21__ChannelDataKind dataKind,
			EML2_3_NS::BusinessAssociate* loggingCompany,
			bool isActive);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		Channel(gsoap_eml2_3::witsml21__Channel* fromGsoap):ChannelIndexDataObject<gsoap_eml2_3::witsml21__Channel>(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~Channel() = default;

		/**
		 * Pushes a back channel index
		 *
		 * @param 	indexKind   	Kind of the index.
		 * @param 	uom				The uom.
		 * @param 	mnemonic		The mnemonic.
		 * @param 	isIncreasing	(Optional) True if is increasing, false if not.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackChannelIndex(gsoap_eml2_3::eml23__DataIndexKind indexKind, gsoap_eml2_3::eml23__UnitOfMeasure uom, const std::string & mnemonic, bool isIncreasing = true) final;

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

		/**
		 * Set the PropertyKind linked with this data object.
		 *
		 * @exception	std::invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @param [in,out]	propKind	If non-null, the property kind.
		 */
		DLL_IMPORT_OR_EXPORT void setPropertyKind(EML2_NS::PropertyKind* propKind);

		/**
		 * @brief	Gets LoggingCompany DOR
		 *
		 * @returns	The LoggingCompany dor.
		 */
		COMMON_NS::DataObjectReference getLoggingCompanyDor() const;

		/**
		 * Gets LoggingCompany
		 *
		 * @returns	Null if it fails, else the LoggingCompany.
		 */
		DLL_IMPORT_OR_EXPORT EML2_3_NS::BusinessAssociate* getLoggingCompany() const;

		/**
		 * Set the BusinessAssociate linked with this data object.
		 *
		 * @exception	std::invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @param [in,out]	businessAssociate	If non-null, the BusinessAssociate.
		 */
		DLL_IMPORT_OR_EXPORT void setLoggingCompany(EML2_3_NS::BusinessAssociate* businessAssociate);

		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(std::string, Mnemonic)
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(std::string, Uom)
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(gsoap_eml2_3::witsml21__ChannelDataKind, DataKind)

/**
 * A macro that defines setter generic optional attribute
 *
 * @param 	attributeDatatype	The attribute datatype.
 * @param 	attributeName	 	Name of the attribute.
 */
#define SETTER_GENERIC_OPTIONAL_ATTRIBUTE(attributeDatatype, attributeName)\
		DLL_IMPORT_OR_EXPORT void set##attributeName(const attributeDatatype & attributeName);

		SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, RunNumber)
		SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, PassNumber)

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "Channel";

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
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "witsml21";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
