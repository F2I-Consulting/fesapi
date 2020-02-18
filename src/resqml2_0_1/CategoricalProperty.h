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

#include "../resqml2/AbstractDiscreteOrCategoricalProperty.h"

/** . */
namespace RESQML2_0_1_NS
{
	/**
	 * Proxy class for a categorical property. It contains discrete integers. This type of property
	 * is associated either: as an internally stored index to a string through a lookup mapping, or
	 * as an internally stored double to another double value through an explicitly provided table.
	 */
	class CategoricalProperty : public RESQML2_NS::AbstractDiscreteOrCategoricalProperty
	{
	protected:

		/** Default constructor */
		CategoricalProperty() {}

	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT CategoricalProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractDiscreteOrCategoricalProperty(partialObject) {}

		/**
		 * Creates a categorical property which is of a well known Energistics property kind
		 *
		 * @exception	std::invalid_argument	If @p rep or @p strLookup is null.
		 *
		 * @param [in]	rep					   	The representation on which this property is attached to.
		 * 										It cannot be null.
		 * @param 	  	guid				   	The guid to set to the property. If empty then a new guid
		 * 										will be generated.
		 * @param 	  	title				   	The title to set to the property. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 	  	dimension			   	The dimension of each value of this property. Dimension
		 * 										is 1 for a scalar property.
		 * @param 	  	attachmentKind		   	The topological element on which the property values are
		 * 										attached to.
		 * @param [in]	strLookup			   	The string lookup which defines the possible string
		 * 										values and their keys.
		 * @param 	  	energisticsPropertyKind	The property kind of these property values which must be
		 * 										defined in the standard Energistics property type
		 * 										dictionary.
		 */
		CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind,
			class StringTableLookup* strLookup, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

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
		 * @param 	  	dimension	  	The dimension of each value of this property. Dimension is 1 for
		 * 								a scalar property.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param [in]	strLookup	  	The string lookup which defines the possible string values and
		 * 								their keys. It cannot be null.
		 * @param [in]	localPropKind 	The property kind of these property values which must be defined
		 * 								in the EPC document as a local property kind. It cannot be null.
		 */
		CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind,
			class StringTableLookup* strLookup, COMMON_NS::PropertyKind * localPropKind);

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		CategoricalProperty(gsoap_resqml2_0_1::_resqml20__CategoricalProperty* fromGsoap): AbstractDiscreteOrCategoricalProperty(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~CategoricalProperty() {}

		DLL_IMPORT_OR_EXPORT std::string pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & dataset = "", LONG64 nullValue = (std::numeric_limits<LONG64>::max)());

		/**   
		 * Get the string lookup which is associated to this categorical property values. 
		 * @returns A pointer to the string lookup which is associated to this categorical property
		 * 			values.
		 */
		DLL_IMPORT_OR_EXPORT class StringTableLookup* getStringLookup();

		/**
		 * Get the UUID of the string lookup which is associated to this categorical property values.
		 *
		 * @returns	The string lookup UUID.
		 */
		DLL_IMPORT_OR_EXPORT std::string getStringLookupUuid() const;

		/**
		 * Checks if it is allowed to associate a given local property kind to this property.
		 *
		 * @exception	std::invalid_argument	If @p pk is null.
		 *
		 * @param [in]	pk	The local property kind to check.
		 *
		 * @returns	True if it is allowed, false if it is not.
		 */
		bool validatePropertyKindAssociation(COMMON_NS::PropertyKind* pk);

		/**
		 * Checks if it is allowed to associate a given standard Energistics property kind to this
		 * property.
		 *
		 * @param 	pk	The standard Energistics property kind to check.
		 *
		 * @returns	True if it is allowed, false if it is not.
		 */
		bool validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind pk);

		/** The standard XML tag without XML namespace for serializing this data object */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Gets the standard XML tag without XML namespace for serializing this data object
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

	protected:
		/** Loads target relationships */
		virtual void loadTargetRelationships();
	};
}
