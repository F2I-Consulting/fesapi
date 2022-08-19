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

#include "../resqml2/DiscreteProperty.h"

namespace RESQML2_0_1_NS
{
	/**
	 * Proxy class for a categorical property. It contains discrete integers. This type of property
	 * is associated either: as an internally stored index to a string through a lookup mapping, or
	 * as an internally stored double to another double value through an explicitly provided table.
	 */
	class CategoricalProperty final : public RESQML2_NS::DiscreteProperty
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT CategoricalProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::DiscreteProperty(partialObject) {}

		/**
		 * Creates a categorical property which is of an Energistics standard property kind
		 *
		 * @exception	std::invalid_argument	If @p rep or @p strLookup is null.
		 *
		 * @param [in]	rep			  			The representation on which this property is attached to. It
		 * 										cannot be null.
		 * @param 	  	guid		  			The guid to set to the property. If empty then a new guid will be
		 * 										generated.
		 * @param 	  	title		  			The title to set to the property. If empty then \"unknown\" title
		 * 										will be set.
		 * @param 	  	attachmentKind			The topological element on which the property values are attached
		 * 										to.
		 * @param [in]	strLookup	  			The string lookup which defines the possible string values and
		 * 										their keys. It cannot be null.
		 * @param [in]	energisticsPropertyKind	The property kind of these property values which must be
		 * 										defined in the standard Energistics property type
		 * 										dictionary.
		 * @param 	  	dimensions	  			The dimensions of each value of this property. If this parameter
		 *										is empty, then it is assumed this property is a scalar one.
		 */
		CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			gsoap_eml2_3::eml23__IndexableElement attachmentKind,
			EML2_NS::ColumnBasedTable* strLookup, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind,
			std::vector<int> dimensions = std::vector<int>());

		/**
		 * Creates a categorical property which is of a local property kind
		 *
		 * @exception	std::invalid_argument	If @p rep, @p strLookup or @p localPropKind is null.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param [in]	strLookup	  	The string lookup which defines the possible string values and
		 * 								their keys. It cannot be null.
		 * @param [in]	localPropKind 	The property kind of these property values which must be defined
		 * 								in the EPC document as a local property kind. It cannot be null.
		 * @param 	  	dimensions	  	The dimensions of each value of this property. If this parameter
		 *								is empty, then it is assumed this property is a scalar one.
		 */
		CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			gsoap_eml2_3::eml23__IndexableElement attachmentKind,
			EML2_NS::ColumnBasedTable* strLookup, EML2_NS::PropertyKind * localPropKind,
			std::vector<int> dimensions = std::vector<int>());

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		CategoricalProperty(gsoap_resqml2_0_1::_resqml20__CategoricalProperty* fromGsoap): RESQML2_NS::DiscreteProperty(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~CategoricalProperty() = default;

		COMMON_NS::DataObjectReference getLookupDor() const final;

		/**
		 * Gets the Energistics property kind which is associated to this intance
		 *
		 * @exception	std::invalid_argument	If the property kind of this property is not an
		 * 										Energistics one.
		 *
		 * @returns	The Energistics property kind.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind() const;

		/**
		* Check if the associated local property kind is allowed for this property.
		*/
		bool validatePropertyKindAssociation(EML2_NS::PropertyKind* pk) final;

		/**
		* Check if the associated standard property kind is allowed for this property.
		*/
		bool validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind pk) final;

		DLL_IMPORT_OR_EXPORT int64_t getNullValue(uint64_t patchIndex = (std::numeric_limits<uint64_t>::max)()) const final;

		DLL_IMPORT_OR_EXPORT bool hasMinimumValue(uint64_t = 0) const final { return false; }

		DLL_IMPORT_OR_EXPORT int64_t getMinimumValue(uint64_t = 0) const final { throw std::logic_error("A RESQML2.0.1 cannot have a minimum value."); }

		DLL_IMPORT_OR_EXPORT bool hasMaximumValue(uint64_t = 0) const final { return false; }

		DLL_IMPORT_OR_EXPORT int64_t getMaximumValue(uint64_t = 0) const final { throw std::logic_error("A RESQML2.0.1 cannot have a maximum value."); }

		DLL_IMPORT_OR_EXPORT void setMinimumValue(int64_t, uint64_t = 0) const final { throw std::logic_error("A RESQML2.0.1 cannot have a minimum value."); }

		DLL_IMPORT_OR_EXPORT void setMaximumValue(int64_t, uint64_t = 0) const final { throw std::logic_error("A RESQML2.0.1 cannot have a maximum value."); }

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "resqml20";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "CategoricalProperty";

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }
	};
}
