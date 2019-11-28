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

#include "WellboreObject.h"

#include <stdexcept>

#include "../common/PropertyKind.h"

namespace WITSML2_0_NS
{
	/**
	* Captures information about the configuration of the permanently installed components in a wellbore. It does not define the transient drilling strings (see the Tubular object) or the hanging production components (see the Completion object).
	*/
	template <class T>
	class ChannelMetaDataObject : public WellboreObject
	{
	public:
		/**
		* Constructor for partial transfer
		*/
		DLL_IMPORT_OR_EXPORT ChannelMetaDataObject(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WellboreObject(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		*/
		ChannelMetaDataObject() : WITSML2_0_NS::WellboreObject() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		ChannelMetaDataObject(gsoap_eml2_1::eml21__AbstractObject* fromGsoap) : WITSML2_0_NS::WellboreObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~ChannelMetaDataObject() {}

		gsoap_eml2_1::eml21__DataObjectReference* getWellboreDor() const
		{
			return static_cast<T*>(gsoapProxy2_1)->Wellbore;
		}

		DLL_IMPORT_OR_EXPORT void setWellbore(Wellbore* witsmlWellbore)
		{
			if (witsmlWellbore == nullptr) {
				throw std::invalid_argument("Cannot set a null witsml wellbore to a witsml trajectory");
			}
			if (getRepository() == nullptr) {
				witsmlWellbore->getRepository()->addOrReplaceDataObject(this);
			}

			static_cast<T*>(gsoapProxy2_1)->Wellbore = witsmlWellbore->newEmlReference();

			getRepository()->addRelationship(this, witsmlWellbore);
		}

		/**
		* Get the Data Object Reference of the PropertyKind linked with this data object.
		*/
		gsoap_eml2_1::eml21__DataObjectReference* getPropertyKindDor() const
		{
			return static_cast<T*>(gsoapProxy2_1)->ChannelClass;
		}

		/**
		* Get the PropertyKind linked with this data object.
		*/
		DLL_IMPORT_OR_EXPORT COMMON_NS::PropertyKind* getPropertyKind() const
		{
			return getRepository()->getDataObjectByUuid<COMMON_NS::PropertyKind>(getPropertyKindDor()->Uuid);
		}

		/**
		* Set the PropertyKind linked with this data object.
		*/
		DLL_IMPORT_OR_EXPORT void setPropertyKind(COMMON_NS::PropertyKind* propKind)
		{
			if (propKind == nullptr) {
				throw std::invalid_argument("Cannot set a null witsml propKind to a witsml log/channelset/channel");
			}
			if (getRepository() == nullptr) {
				propKind->getRepository()->addOrReplaceDataObject(this);
			}

			static_cast<T*>(gsoapProxy2_1)->ChannelClass = propKind->newEmlReference();

			getRepository()->addRelationship(this, propKind);
		}

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

	template<> std::string ChannelMetaDataObject<gsoap_eml2_1::witsml20__Channel>::getTimeDepth() const {
		return static_cast<gsoap_eml2_1::witsml20__Channel*>(gsoapProxy2_1)->TimeDepth;
	}
	template<> bool ChannelMetaDataObject<gsoap_eml2_1::witsml20__Channel>::hasTimeDepth() const {
		return true;
	}
	template<> std::string ChannelMetaDataObject<gsoap_eml2_1::witsml20__Channel>::getLoggingCompanyName() const {
		return static_cast<gsoap_eml2_1::witsml20__Channel*>(gsoapProxy2_1)->LoggingCompanyName;
	}
	template<> bool ChannelMetaDataObject<gsoap_eml2_1::witsml20__Channel>::hasLoggingCompanyName() const {
		return true;
	}
}
