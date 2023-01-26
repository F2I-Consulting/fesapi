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

namespace RESQML2_2_NS
{
	/**
	 * Proxy class for a discrete  property. Such property contains discrete integer values;
	 * typically used to store any type of index. So that the value range can be known before
	 * accessing all values, it also optionally stores the minimum and maximum value in the range.
	 */
	class DiscreteProperty final : public RESQML2_NS::DiscreteProperty
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT DiscreteProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::DiscreteProperty(partialObject) {}

		/**
		 * Creates a discrete property without lookup table associated.
		 *
		 * @exception	std::invalid_argument	If @p or @p localPropKind is null. If @p dimension is zero.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param [in]	propKind	 	The property kind of these property values. It cannot be null.
		 * @param 	  	dimensions		The dimensions of each value of this property. If this parameter
		 *								is empty, then it is assumed this property is a scalar one.
		 */
		DiscreteProperty(RESQML2_NS::AbstractRepresentation* rep, const std::string& guid, const std::string& title,
			gsoap_eml2_3::eml23__IndexableElement attachmentKind, EML2_NS::PropertyKind* propKind,
			std::vector<int> dimensions = std::vector<int>());

		/**
		 * Creates a discrete property with a lookup table associated.
		 *
		 * @exception	std::invalid_argument	If @p or @p localPropKind is null. If @p dimension is zero.
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
		 * @param [in]	propKind	 	The property kind of these property values. It cannot be null.
		 * @param 	  	dimensions		The dimensions of each value of this property. If this parameter
		 *								is empty, then it is assumed this property is a scalar one.
		 */
		DiscreteProperty(RESQML2_NS::AbstractRepresentation* rep, const std::string& guid, const std::string& title,
			gsoap_eml2_3::eml23__IndexableElement attachmentKind, EML2_NS::ColumnBasedTable* strLookup,
			EML2_NS::PropertyKind* propKind,
			std::vector<int> dimensions = std::vector<int>());

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		DiscreteProperty(gsoap_eml2_3::_resqml22__DiscreteProperty* fromGsoap): RESQML2_NS::DiscreteProperty(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~DiscreteProperty() = default;

		COMMON_NS::DataObjectReference getLookupDor() const final {
			return COMMON_NS::DataObjectReference(static_cast<gsoap_eml2_3::resqml22__DiscreteProperty*>(gsoapProxy2_3)->CategoryLookup);
		}

		DLL_IMPORT_OR_EXPORT bool hasMinimumValue(uint64_t index = 0) const final;

		DLL_IMPORT_OR_EXPORT int64_t getMinimumValue(uint64_t index = 0) const final;

		DLL_IMPORT_OR_EXPORT bool hasMaximumValue(uint64_t index = 0) const final;

		DLL_IMPORT_OR_EXPORT int64_t getMaximumValue(uint64_t index = 0) const final;

		DLL_IMPORT_OR_EXPORT void setMinimumValue(int64_t value, uint64_t index = 0) const final;

		DLL_IMPORT_OR_EXPORT void setMaximumValue(int64_t value, uint64_t index = 0) const final;

		bool validatePropertyKindAssociation(EML2_NS::PropertyKind*) final { return true; }

		bool validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind) final { return true; }

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "resqml22";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "DiscreteProperty";

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }
	};
}
