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

#include "../resqml2/CategoricalProperty.h"

namespace RESQML2_2_NS
{
	/**
	 * Proxy class for a categorical property. It contains discrete integers. This type of property
	 * is associated either: as an internally stored index to a string through a lookup mapping, or
	 * as an internally stored double to another double value through an explicitly provided table.
	 */
	class CategoricalProperty final : public RESQML2_NS::CategoricalProperty
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT CategoricalProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::CategoricalProperty(partialObject) {}

		/**
		 * @brief	Creates a categorical property
		 *
		 * @exception	std::invalid_argument	If @p rep, @p strLookup or @p propKind is null. If @p
		 * 										dimension is zero.
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
		 * @param [in]	localPropKind 	The property kind of these property values. It cannot be null.
		 * @param 	  	dimensions	  	The dimensions of each value of this property. If this parameter
		 *								is empty, then it is assumed this property is a scalar one.
		 */
		CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			gsoap_eml2_3::eml23__IndexableElement attachmentKind,
			RESQML2_NS::StringTableLookup* strLookup, EML2_NS::PropertyKind * localPropKind,
			std::vector<int> dimensions = std::vector<int>());

		/**
		 * @brief	Creates a categorical property
		 *
		 * @exception	std::invalid_argument	If @p rep, @p strLookup or @p propKind is null. If @p
		 * 										dimension is zero.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param [in]	dblLookup	  	The double table lookup which associate a discrete function to the property values.
		 * @param [in]	localPropKind 	The property kind of these property values. It cannot be null.
		 * @param 	  	dimensions	  	The dimensions of each value of this property. If this parameter
		 *								is empty, then it is assumed this property is a scalar one.
		 */
		CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			gsoap_eml2_3::eml23__IndexableElement attachmentKind,
			RESQML2_NS::DoubleTableLookup* dblLookup, EML2_NS::PropertyKind * localPropKind,
			std::vector<int> dimensions = std::vector<int>());

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		CategoricalProperty(gsoap_eml2_3::_resqml22__CategoricalProperty* fromGsoap): RESQML2_NS::CategoricalProperty(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~CategoricalProperty() = default;

		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getLookupDor() const final;

		bool validatePropertyKindAssociation(EML2_NS::PropertyKind*) final { return true; }

		bool validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind) final { return true; }

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
