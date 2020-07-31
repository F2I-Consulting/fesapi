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

#include "../resqml2/ContinuousProperty.h"
#include "../eml2/AbstractHdfProxy.h"

#include <stdexcept>
#include <sstream>

namespace RESQML2_0_1_NS
{
	/**
	 * Proxy class for a continuous property. Most common type of property used for storing rock or
	 * fluid attributes; all are represented as floating point values. So that the value range can
	 * be known before accessing all values, the min and max values of the range are also optionally
	 * stored. BUSINESS RULE: It also contains a unit of measure, which can be different from the
	 * unit of measure of its property type, but it must be convertible into this unit.
	 */
	class ContinuousProperty final : public RESQML2_NS::ContinuousProperty
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT ContinuousProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::ContinuousProperty(partialObject) {}

		/**
		 * Creates a continuous property which is of well known Energistics unit of measure and property
		 * kind.
		 *
		 * @exception	std::invalid_argument	If @p rep is null.
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
		 * @param 	  	uom					   	The property unit of measure taken from the standard
		 * 										Energistics units of measure catalog. Please check
		 * 										COMMON_NS::EnumStringMapper::getEnergisticsUnitOfMeasure
		 * 										in order to minimize the use of non standard unit of
		 * 										measure.
		 * @param 	  	energisticsPropertyKind	The property kind of these property values which must be
		 * 										defined in the standard Energistics property type
		 * 										dictionary.
		 */
		ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		/**
		 * Creates a continuous property which is of a well known unit of measure and a local property
		 * kind.
		 *
		 * @exception	std::invalid_argument	If @p rep or @p localPropType is null.
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
		 * @param 	  	uom			  	The property unit of measure taken from the standard Energistics
		 * 								units of measure catalog. Please check
		 * 								COMMON_NS::EnumStringMapper::getEnergisticsUnitOfMeasure in order
		 * 								to minimize the use of non standard unit of measure.
		 * @param [in]	localPropKind 	The property kind of these property values which must be defined
		 * 								in the EPC document as a local property kind. It cannot be null.
		 */
		ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, EML2_NS::PropertyKind * localPropKind);

		/**
		 * Creates a continuous property which is of a local unit of measure and a well known property
		 * kind.
		 *
		 * @exception	std::invalid_argument	If @p rep is null.
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
		 * @param 	  	nonStandardUom		   	The property unit of measure. Please check
		 * 										COMMON_NS::EnumStringMapper::getEnergisticsUnitOfMeasure
		 * 										in order to minimize the use of non standard unit of
		 * 										measure.
		 * @param 	  	energisticsPropertyKind	The property kind of these property values which must be
		 * 										defined in the standard Energistics property type
		 * 										dictionary.
		 */
		ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, const std::string & nonStandardUom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		/**
		 * Creates a continuous property which is of local unit of measure and property kind.
		 *
		 * @exception	std::invalid_argument	If @p rep or @p localPropType is null.
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
		 * @param 	  	nonStandardUom	The property unit of measure. Please check
		 * 								COMMON_NS::EnumStringMapper::getEnergisticsUnitOfMeasure in order
		 * 								to minimize the use of non standard unit of measure.
		 * @param [in]	localPropKind 	The property kind of these property values which must be defined
		 * 								in the EPC document as a local property kind. It cannot be null.
		 */
		ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, const std::string & nonStandardUom, EML2_NS::PropertyKind * localPropKind);

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		ContinuousProperty(gsoap_resqml2_0_1::_resqml20__ContinuousProperty* fromGsoap): RESQML2_NS::ContinuousProperty(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~ContinuousProperty() {}

		/**
		 * Gets the unit of measure of the values of this property. If <tt>
		 * resqml20__ResqmlUom::resqml20__ResqmlUom__Euc </tt> is returned and if your instance is a 2.0.1 one, you should check if an
		 * extrametadata called "Uom" also exists. If so, it would mean that the property uses a non
		 * standard unit of measure. This is an official workaround for a known issue of Resqml 2.0.1.
		 *
		 * @returns	The unit of measure of the values of this property.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlUom getUom() const final;

		/**
		 * Gets the unit of measure of the values of this property as a string. If "Euc"  is returned,
		 * you should check if an extrametadata called "Uom" also exists. If so, it would mean that the
		 * property uses a non standard uom. This is an official workaround for a known issue of Resqml
		 * 2.0.1.
		 *
		 * @returns	The unit of measure of the values of this property as a string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getUomAsString() const final;

		DLL_IMPORT_OR_EXPORT double getMinimumValue(unsigned int index = 0) const final;

		DLL_IMPORT_OR_EXPORT double getMaximumValue(unsigned int index = 0) const final;

		DLL_IMPORT_OR_EXPORT void setMinimumValue(double value, unsigned int index = 0) const final;

		DLL_IMPORT_OR_EXPORT void setMaximumValue(double value, unsigned int index = 0) const final;

		/**
		 * Gets the Energistics property kind which is associated to this intance
		 *
		 * @exception	std::invalid_argument	If the property kind of this property is not an
		 * 										Energistics one.
		 *
		 * @returns	The Energistics property kind.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind() const;

		bool validatePropertyKindAssociation(EML2_NS::PropertyKind* pk) final;

		bool validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind pk) final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

	private:

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	rep			  	The representation which supports these property values.
		 * @param 		  	guid		  	The guid to set to the fault. If empty then a new guid will
		 * 									be generated.
		 * @param 		  	title		  	A title for the instance to create.
		 * @param 		  	dimension	  	The dimension of each value (scalar properties == 1).
		 * @param 		  	attachmentKind	The topological orbit which supports each value.
		 */
		void init(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind);

		EML2_NS::AbstractHdfProxy* getValuesHdfProxyAndDatasetPathOfPatch(unsigned int patchIndex, std::string & datasetPath) const;

		size_t getMinimumValueSize() const;
		size_t getMaximumValueSize() const;
	};
}
