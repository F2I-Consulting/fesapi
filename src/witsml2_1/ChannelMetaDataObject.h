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

#include <stdexcept>

#include "../eml2/PropertyKind.h"

namespace WITSML2_1_NS
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
		ChannelMetaDataObject(gsoap_eml2_3::eml23__AbstractObject* fromGsoap) : WITSML2_NS::WellboreObject(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~ChannelMetaDataObject() = default;

		/**
		 * @brief	Gets wellbore dor
		 *
		 * @returns	The wellbore dor.
		 */
		COMMON_NS::DataObjectReference getWellboreDor() const final
		{
			return COMMON_NS::DataObjectReference(static_cast<T*>(this->gsoapProxy2_3)->Wellbore);
		}

		/**
		 * Sets a wellbore
		 *
		 * @exception	std::invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @param [in,out]	witsmlWellbore	If non-null, the witsml wellbore.
		 */
		DLL_IMPORT_OR_EXPORT void setWellbore(WITSML2_NS::Wellbore* witsmlWellbore) final
		{
			if (witsmlWellbore == nullptr) {
				throw std::invalid_argument("Cannot set a null witsml wellbore to a witsml trajectory");
			}

			static_cast<T*>(this->gsoapProxy2_3)->Wellbore = witsmlWellbore->newEml23Reference();

			getRepository()->addRelationship(this, witsmlWellbore);
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
			if (static_cast<T*>(this->gsoapProxy2_3)->attributeName == nullptr) { throw std::invalid_argument("The attribute does not exist"); }\
			return *static_cast<T*>(this->gsoapProxy2_3)->attributeName;\
		}\
		bool has##attributeName() const { return static_cast<T*>(this->gsoapProxy2_3)->attributeName != nullptr; }
		
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_TEMPLATE(std::string, RunNumber, gsoap_eml2_3::soap_new_std__string)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_TEMPLATE(std::string, PassNumber, gsoap_eml2_3::soap_new_std__string)
	};
}
