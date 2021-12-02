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

#include "../witsml2/WellboreObject.h"

#include "../eml2/PropertyKind.h"

namespace WITSML2_0_NS
{
	/**
	 * Captures information about the configuration of the permanently installed components in a
	 * wellbore. It does not define the transient drilling strings (see the Tubular object) or the
	 * hanging production components (see the Completion object).
	 *
	 * @tparam	T	Generic type parameter.
	 */
	template <class T>
	class ChannelMetaDataObject : public WITSML2_NS::WellboreObject
	{
	public:

		/**
		 * Constructor for partial transfer
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT ChannelMetaDataObject(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WellboreObject(partialObject) {}

		/** Creates an instance of this class in a gsoap context. */
		ChannelMetaDataObject() : WITSML2_NS::WellboreObject() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		ChannelMetaDataObject(gsoap_eml2_1::eml21__AbstractObject* fromGsoap) : WITSML2_NS::WellboreObject(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~ChannelMetaDataObject() = default;

		/**
		 * @brief	Gets wellbore dor
		 *
		 * @returns	The wellbore dor.
		 */
		COMMON_NS::DataObjectReference getWellboreDor() const
		{
			return COMMON_NS::DataObjectReference(static_cast<T*>(gsoapProxy2_1)->Wellbore);
		}

		/**
		 * Sets a wellbore
		 *
		 * @exception	std::invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @param [in,out]	witsmlWellbore	If non-null, the witsml wellbore.
		 */
		DLL_IMPORT_OR_EXPORT void setWellbore(WITSML2_NS::Wellbore* witsmlWellbore)
		{
			if (witsmlWellbore == nullptr) {
				throw std::invalid_argument("Cannot set a null witsml wellbore to a witsml trajectory");
			}

			static_cast<T*>(gsoapProxy2_1)->Wellbore = witsmlWellbore->newEmlReference();

			getRepository()->addRelationship(this, witsmlWellbore);
		}

		/**
		* Get the Data Object Reference of the PropertyKind linked with this data object.
		*/
		COMMON_NS::DataObjectReference getPropertyKindDor() const
		{
			return COMMON_NS::DataObjectReference(static_cast<T*>(gsoapProxy2_1)->ChannelClass);
		}

		/**
		 * Get the PropertyKind linked with this data object.
		 *
		 * @returns	Null if it fails, else the property kind.
		 */
		EML2_NS::PropertyKind* getPropertyKind() const
		{
			return getRepository()->template getDataObjectByUuid<EML2_NS::PropertyKind>(getPropertyKindDor().getUuid());
		}

		/**
		 * Set the PropertyKind linked with this data object.
		 *
		 * @exception	std::invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @param [in,out]	propKind	If non-null, the property kind.
		 */
		void setPropertyKind(EML2_NS::PropertyKind* propKind)
		{
			if (propKind == nullptr) {
				throw std::invalid_argument("Cannot set a null witsml propKind to a witsml log/channelset/channel");
			}

			static_cast<T*>(gsoapProxy2_1)->ChannelClass = propKind->newEmlReference();

			getRepository()->addRelationship(this, propKind);
		}

/**
 * A macro that defines getter and setter generic optional attribute template
 *
 * @param 	attributeDatatype	The attribute datatype.
 * @param 	attributeName	 	Name of the attribute.
 * @param 	constructor		 	The constructor.
 */
#define GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_TEMPLATE(attributeDatatype, attributeName, constructor)\
		DLL_IMPORT_OR_EXPORT virtual void set##attributeName(const attributeDatatype & attributeName) = 0;\
		std::string get##attributeName() const {\
			if (static_cast<T*>(gsoapProxy2_1)->attributeName == nullptr) { throw std::invalid_argument("The attribute does not exist"); }\
			return *static_cast<T*>(gsoapProxy2_1)->attributeName;\
		}\
		bool has##attributeName() const { return static_cast<T*>(gsoapProxy2_1)->attributeName != nullptr; }
		
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_TEMPLATE(std::string, TimeDepth, gsoap_eml2_1::soap_new_std__string)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_TEMPLATE(std::string, RunNumber, gsoap_eml2_1::soap_new_std__string)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_TEMPLATE(std::string, PassNumber, gsoap_eml2_1::soap_new_std__string)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_TEMPLATE(std::string, LoggingCompanyName, gsoap_eml2_1::soap_new_std__string)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_TEMPLATE(std::string, LoggingCompanyCode, gsoap_eml2_1::soap_new_std__string)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_TEMPLATE(std::string, ToolName, gsoap_eml2_1::soap_new_std__string)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_TEMPLATE(std::string, ToolClass, gsoap_eml2_1::soap_new_std__string)
	};

	/**
	 * Gets time depth
	 *
	 * @tparam	gsoap_eml2_1::witsml20__Channel	Type of the gsoap eml 2 1 witsml 20 channel.
	 *
	 * @returns	The time depth.
	 */
	template<> inline std::string ChannelMetaDataObject<gsoap_eml2_1::witsml20__Channel>::getTimeDepth() const {
		return static_cast<gsoap_eml2_1::witsml20__Channel*>(gsoapProxy2_1)->TimeDepth;
	}

	/**
	 * Query if this object has time depth
	 *
	 * @tparam	gsoap_eml2_1::witsml20__Channel	Type of the gsoap eml 2 1 witsml 20 channel.
	 *
	 * @returns	True if time depth, false if not.
	 */
	template<> inline bool ChannelMetaDataObject<gsoap_eml2_1::witsml20__Channel>::hasTimeDepth() const {
		return true;
	}

	/**
	 * Gets logging company name
	 *
	 * @tparam	gsoap_eml2_1::witsml20__Channel	Type of the gsoap eml 2 1 witsml 20 channel.
	 *
	 * @returns	The logging company name.
	 */
	template<> inline std::string ChannelMetaDataObject<gsoap_eml2_1::witsml20__Channel>::getLoggingCompanyName() const {
		return static_cast<gsoap_eml2_1::witsml20__Channel*>(gsoapProxy2_1)->LoggingCompanyName;
	}

	/**
	 * Query if this object has logging company name
	 *
	 * @tparam	gsoap_eml2_1::witsml20__Channel	Type of the gsoap eml 2 1 witsml 20 channel.
	 *
	 * @returns	True if logging company name, false if not.
	 */
	template<> inline bool ChannelMetaDataObject<gsoap_eml2_1::witsml20__Channel>::hasLoggingCompanyName() const {
		return true;
	}
}
