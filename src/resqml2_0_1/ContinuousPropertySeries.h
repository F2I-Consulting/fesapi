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

#include "ContinuousProperty.h"

/** . */
namespace RESQML2_0_1_NS
{
	/**
	 * This class is mainly useful for describing temporal properties on well objects. The prefered
	 * approach to describe temporal properties on Reservoir grids is to use one instance of
	 * ContinuousProperty per time step.
	 */
	class ContinuousPropertySeries : public ContinuousProperty
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT ContinuousPropertySeries(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : ContinuousProperty(partialObject) {}

		/**
		 * Creates a continuous property series which is of a well known Energistics property kind.
		 *
		 * @exception	std::invalid_argument	If @p rep or @p ts is null.
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
		 * 										Energistics units of measure catalog.
		 * @param 	  	energisticsPropertyKind	The property type of these property values which must be
		 * 										defined in the standard Energistics property kind catalog.
		 * @param [in]	ts					   	The time series associated to this property series. It
		 * 										cannot be null.
		 * @param 	  	useInterval			   	(Optional) If true the values are associated with each
		 * 										time interval between two consecutive time entries,
		 * 										instead (default) of each individual time entry.
		 */
		ContinuousPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind,
			const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		/**
		 * Creates a continuous property series which is of a local property kind
		 *
		 * @exception	std::invalid_argument	If @p rep, @p localPropType or @p ts is null.
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
		 * 								units of measure catalog.
		 * @param [in]	localPropKind 	The property type of these property values which must be defined
		 * 								in this repository as a local property kind.
		 * @param [in]	ts			  	The time series associated to this property series. It cannot be
		 * 								null.
		 * @param 	  	useInterval   	(Optional) If true the values are associated with each time
		 * 								interval between two consecutive time entries, instead (default)
		 * 								of each individual time entry.
		 */
		ContinuousPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind,
			const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, COMMON_NS::PropertyKind * localPropKind,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		ContinuousPropertySeries(gsoap_resqml2_0_1::_resqml20__ContinuousPropertySeries* fromGsoap): ContinuousProperty(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~ContinuousPropertySeries() {}

		std::string getXmlNamespaceVersion() const override {return "2.0.1";}

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const override { return XML_TAG; }
	};
}
