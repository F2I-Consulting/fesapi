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

#include "../common/PropertyKind.h"

namespace WITSML2_0_NS
{
	class PropertyKind : public COMMON_NS::PropertyKind
	{
	public:
		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT PropertyKind(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::PropertyKind(partialObject) {}

		/**
		* Creates a local property type which uses a standard uom and which derives from a standard Energistics property type.
		* @param repo							The repo where the underlying gsoap proxy is going to be created.
		* @param guid							The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title							The title of the instance.
		* @param quantityClass					The quantity class of this property kind. It wil constrain its allowed uom collection. The enum comes from Energistics Unit Of Measure.
		* @param isAbstract						Inidcates if this property kind can be used directly by a property or not.
		* @param parentPropertyKind				The parent property kind if this property kind. By default, it is the Energistics root property kind called "property".
		*/
		PropertyKind(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			gsoap_eml2_1::eml21__QuantityClassKind quantityClass, bool isAbstract = false, COMMON_NS::PropertyKind* parentPropertyKind = nullptr);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		PropertyKind(gsoap_eml2_1::eml21__PropertyKind* fromGsoap) :COMMON_NS::PropertyKind(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~PropertyKind() {}

		DLL_IMPORT_OR_EXPORT bool isChildOf(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind standardPropKind) const;

		DLL_IMPORT_OR_EXPORT bool isAbstract() const;

		DLL_IMPORT_OR_EXPORT bool isParentPartial() const;

		std::string getXmlNamespace() const { return "eml21"; }

	private:
		void setXmlParentPropertyKind(COMMON_NS::PropertyKind* parentPropertyKind);

		PropertyKind* getParentPropertyKind() const;
	};
}
