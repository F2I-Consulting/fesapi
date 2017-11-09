/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#pragma once

#include "resqml2/AbstractProperty.h"

namespace resqml2
{
	class DLL_IMPORT_OR_EXPORT PropertyKind : public common::AbstractObject
	{
	protected:

		/**
		* Default constructor does nothing
		*/
		PropertyKind() {}

		/**
		* Only to be used in partial transfer context
		*/
		PropertyKind(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : common::AbstractObject(partialObject) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		PropertyKind(gsoap_resqml2_0_1::_resqml2__PropertyKind* fromGsoap) : common::AbstractObject(fromGsoap) {}

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

	protected:
		virtual void setXmlParentPropertyKind(PropertyKind* parentPropertyKind) = 0;

		std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		// XML backward relationship
		std::vector<class AbstractProperty*> propertySet;
		std::vector<PropertyKind*> childPropertyKind;

		friend void AbstractProperty::setLocalPropertyKind(PropertyKind* propKind);
	};
}

