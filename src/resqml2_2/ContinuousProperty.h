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

namespace RESQML2_2_NS
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
		 * Creates a continuous property which is of a well known unit of measure and a local property
		 * kind.
		 *
		 * @exception	std::invalid_argument	If @p rep or @p propKind is null. If @p dimension is zero.
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
		 * @param [in]	propKind	 	The property kind of these property values. It cannot be null.
		 */
		ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, EML2_NS::PropertyKind * propKind);

		/**
		 * Creates a continuous property which is of local unit of measure and property kind.
		 *
		 * @exception	std::invalid_argument	If @p rep or @p propKind is null.
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
		 * @param [in]	propKind	 	The property kind of these property values. It cannot be null.
		 */
		ContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, const std::string & nonStandardUom, EML2_NS::PropertyKind * propKind);

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		ContinuousProperty(gsoap_eml2_3::_resqml22__ContinuousProperty* fromGsoap): RESQML2_NS::ContinuousProperty(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~ContinuousProperty() {}

		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__ResqmlUom getUom() const final;

		DLL_IMPORT_OR_EXPORT std::string getUomAsString() const final;

		DLL_IMPORT_OR_EXPORT std::string pushBackRefToExistingDataset(EML2_NS::AbstractHdfProxy* proxy, const std::string & datasetName = "") final;

		DLL_IMPORT_OR_EXPORT double getMinimumValue(unsigned int index = 0) const final;

		DLL_IMPORT_OR_EXPORT double getMaximumValue(unsigned int index = 0) const final;

		DLL_IMPORT_OR_EXPORT void setMinimumValue(double value, unsigned int index = 0) const final;

		DLL_IMPORT_OR_EXPORT void setMaximumValue(double value, unsigned int index = 0) const final;

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

		EML2_NS::AbstractHdfProxy* getValuesHdfProxyAndDatasetPathOfPatch(unsigned int patchIndex, std::string & datasetPath) const final;

		size_t getMinimumValueSize() const;
		size_t getMaximumValueSize() const;
	};
}
