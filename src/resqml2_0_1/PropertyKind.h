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

#include "resqml2/PropertyKind.h"
#include "resqml2_0_1/PropertyKindMapper.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT PropertyKind : public resqml2::PropertyKind
	{
	private:

		void init(soap* soapContext, const std::string & guid, const std::string & title, const std::string & namingSystem);

	public:
		/**
		* Only to be used in partial transfer context
		*/
		PropertyKind(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : resqml2::PropertyKind(partialObject) {}

		/**
		* Creates a local property type which uses a standard uom and which derives from a standard Energistics property type.
		* @param soapContext					The soap context where the underlying gsoap proxy is going to be created.
		* @param guid							The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title							The title of the instance.
		* @param namingSystem					The name of the dictionary within which the property is unique.
		* @param uom							The unit of measure of the property type.
		* @param parentEnergisticsPropertyKind	The name of the parent property type in the Energistics property dictionary.
		*/
		PropertyKind(soap* soapContext, const std::string & guid, const std::string & title,
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind);

		/**
		* Creates a local property type which uses a standard uom and which derives from another local property type.
		* @param soapContext					The soap context where the underlying gsoap proxy is going to be created.
		* @param guid							The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title							The title of the instance.
		* @param namingSystem					The name of the dictionary within which the property is unique.
		* @param uom							The unit of measure of the property type.
		* @param parentPropType					The local parent property type in the EPC document.
		*/
		PropertyKind(soap* soapContext, const std::string & guid, const std::string & title,
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2::PropertyKind * parentPropType);

		/**
		* Creates a local property type which uses a non standard uom and which derives from a standard Energistics property type.
		* @param soapContext					The soap context where the underlying gsoap proxy is going to be created.
		* @param guid							The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title							The title of the instance.
		* @param namingSystem					The name of the dictionary within which the property is unique.
		* @apram nonStandardUom					The non standard uom of the values
		* @param parentEnergisticsPropertyKind	The name of the parent property type in the Energistics property dictionary.
		*/
		PropertyKind(soap* soapContext, const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind);

		/**
		* Creates a local property type which uses a non standard uom which derives from another local property type.
		* @param soapContext					The soap context where the underlying gsoap proxy is going to be created.
		* @param guid							The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title							The title of the instance.
		* @param namingSystem					The name of the dictionary within which the property is unique.
		* @apram nonStandardUom					The non standard uom of the values
		* @param parentPropType					The local parent property type in the EPC document.
		*/
		PropertyKind(soap* soapContext, const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, resqml2::PropertyKind * parentPropType);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		PropertyKind(gsoap_resqml2_0_1::_resqml2__PropertyKind* fromGsoap) :resqml2::PropertyKind(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~PropertyKind() {}

		bool isChildOf(gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind standardPropKind) const;

		bool isAbstract() const;

	protected:
		void setXmlParentPropertyKind(resqml2::PropertyKind* parentPropertyKind);
		
		gsoap_resqml2_0_1::_resqml2__PropertyKind* getSpecializedGsoapProxy() const;

		friend resqml2_0_1::PropertyKind* PropertyKindMapper::addResqmlLocalPropertyKindToEpcDocumentFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application);
	};
}

