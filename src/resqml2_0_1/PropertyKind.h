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

#include "resqml2/PropertyKind.h"
#include "resqml2_0_1/PropertyKindMapper.h"

namespace RESQML2_0_1_NS
{
	class DLL_IMPORT_OR_EXPORT PropertyKind : public RESQML2_NS::PropertyKind
	{
	private:

		void init(soap* soapContext, const std::string & guid, const std::string & title, const std::string & namingSystem);

	public:
		/**
		* Only to be used in partial transfer context
		*/
		PropertyKind(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::PropertyKind(partialObject) {}

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
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, RESQML2_NS::PropertyKind * parentPropType);

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
			const std::string & namingSystem, const std::string & nonStandardUom, RESQML2_NS::PropertyKind * parentPropType);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		PropertyKind(gsoap_resqml2_0_1::_resqml2__PropertyKind* fromGsoap) :RESQML2_NS::PropertyKind(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~PropertyKind() {}

		bool isChildOf(gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind standardPropKind) const;

		bool isAbstract() const;

		bool isParentPartial() const;

	protected:
		void setXmlParentPropertyKind(RESQML2_NS::PropertyKind* parentPropertyKind);
		
		gsoap_resqml2_0_1::_resqml2__PropertyKind* getSpecializedGsoapProxy() const;

		friend RESQML2_0_1_NS::PropertyKind* PropertyKindMapper::addResqmlLocalPropertyKindToEpcDocumentFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application);
	};
}


