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

#include "common/AbstractObject.h"

namespace RESQML2_NS
{
	class AbstractProperty;
	/**
	* A set of properties collected together for a specific purpose. For example, a property set can be used to collect all the properties corresponding to the simulation output at a single time, or all the values of a single property kind for all times.
	*/
	class PropertySet : public COMMON_NS::AbstractObject
	{
	protected:

		/**
		* Default constructor does nothing
		*/
		PropertySet() : COMMON_NS::AbstractObject() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		PropertySet(gsoap_resqml2_0_1::_resqml20__PropertySet* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}protected:
			
		virtual void setXmlParent(PropertySet * parent) = 0;
		virtual void pushBackXmlProperty(RESQML2_NS::AbstractProperty * prop) = 0;

		virtual std::vector<gsoap_resqml2_0_1::eml20__DataObjectReference *> getAllPropertiesDors() const = 0;

	public:

		/**
		* Only to be used in partial transfer context
		*/
		PropertySet(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~PropertySet() {}

		/**
		* Set the parent property set of this instance.
		*/
		DLL_IMPORT_OR_EXPORT void setParent(PropertySet * parent);

		virtual gsoap_resqml2_0_1::eml20__DataObjectReference const * getParentDor() const = 0;

		/**
		* Get the parent property set uuid of this instance
		* @return the parent property set uuid or empty string.
		*/
		DLL_IMPORT_OR_EXPORT std::string getParentUuid() const;

		/**
		* Get the parent property set of this instance
		* @return the parent property set or nullptr.
		*/
		DLL_IMPORT_OR_EXPORT PropertySet * getParent() const;

		/**
		* Get the children property set of this instance
		* @return the children property set or empty vector.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<PropertySet *> getChildren() const;

		/**
		* Get the count of all properties directly contained in this property set.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getChildrenCount() const;

		/**
		* Get a particular property of this property set.
		*/
		DLL_IMPORT_OR_EXPORT PropertySet* getChildren(unsigned int index) const;

		/**
		* Push back a property into this property set.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackProperty(RESQML2_NS::AbstractProperty * prop);

		/**
		* Get all properties directly contained in this property set.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_NS::AbstractProperty *> getProperties() const;

		/**
		* Get the count of all properties directly contained in this property set.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getPropertyCount() const;

		/**
		* Get a particular property of this property set.
		*/
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractProperty* getProperty(unsigned int index) const;

		/**
		* If true, indicates that the collection contains properties with defined realization indices.
		*/
		DLL_IMPORT_OR_EXPORT virtual bool hasMultipleRealizations() const = 0;

		/**
		* If true, indicates that the collection contains only property values associated with a single property kind.
		*/
		DLL_IMPORT_OR_EXPORT virtual bool hasSinglePropertyKind() const = 0;

		/**
		* @return The time set kind of this property set.
		*/
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::resqml20__TimeSetKind getTimeSetKind() const = 0;

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

		void loadTargetRelationships();
	};
}
