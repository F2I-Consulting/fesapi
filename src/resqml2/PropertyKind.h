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

#include "resqml2/AbstractProperty.h"

namespace RESQML2_NS
{
	class DLL_IMPORT_OR_EXPORT PropertyKind : public COMMON_NS::AbstractObject
	{
	protected:

		/**
		* Default constructor does nothing
		*/
		PropertyKind() {}

		/**
		* Only to be used in partial transfer context
		*/
		PropertyKind(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		PropertyKind(gsoap_resqml2_0_1::_resqml2__PropertyKind* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~PropertyKind() {}

		/**
		* Getter (in read only mode) of the naming system of this property type
		*/
		const std::string & getNamingSystem() const;

		/**
		* Get the unit of measure of the values of this property kind.
		*/
		const gsoap_resqml2_0_1::resqml2__ResqmlUom & getUom() const;

		/**
		* Get the unit of measure of the values of this property kind as a string.
		*/
		std::string getUomAsString() const;

		/**
		 * Get the title of the parent of this property kind.
		 */
		std::string getParentAsString() const;

		/**
		* Indicates if the property kind which is the parent of this property kind is either from the standard catalog of Energistics or from another local property kind.
		*/
		bool isParentAnEnergisticsPropertyKind() const;

		/**
		* Getter for the energistics property kind which is associated to this intance.
		*/
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind getParentEnergisticsPropertyKind() const;

		/**
		* @return	null pointer if no local parent property kind is associated to this property. Otherwise return the data object reference of the associated parent local property kind.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getParentLocalPropertyKindDor() const;

		/**
		* Get the uuid of the local parent property kind which is associated to this property.
		*/
		std::string getParentLocalPropertyKindUuid() const;

		/**
		* Get the uuid of the local parent property kind which is associated to this property.
		*/
		std::string getParentLocalPropertyKindTitle() const;

		/**
		* Getter for the local property kind which is the parent of this instance.
		* If nullptr is returned then it means this instance is associated to an energistics property kind.
		*/
		PropertyKind* getParentLocalPropertyKind() const;

		void setParentPropertyKind(PropertyKind* parentPropertyKind);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* Add a representation values object which uses this property type.
		* Does not add the inverse relationship i.e. from the representation values object to this property type.
		*/
		void addProperty(class AbstractProperty* repVal) {propertySet.push_back(repVal);}

		/**
		* Check if this property kind is a child of a particular standard Energistics Property kind.
		*/
		virtual bool isChildOf(gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind standardPropKind) const = 0;

		/**
		* Check if this property kind is abstract or not.
		*/
		virtual bool isAbstract() const = 0;

		std::vector<epc::Relationship> getAllSourceRelationships() const;
		std::vector<epc::Relationship> getAllTargetRelationships() const;

	protected:
		virtual void setXmlParentPropertyKind(PropertyKind* parentPropertyKind) = 0;

		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);

		// XML backward relationship
		std::vector<class AbstractProperty*> propertySet;
		std::vector<PropertyKind*> childPropertyKind;

		friend void AbstractProperty::setLocalPropertyKind(PropertyKind* propKind);
	};
}


