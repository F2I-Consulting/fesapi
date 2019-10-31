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

namespace RESQML2_0_1_NS
{
	/**
	* This class is mainly useful for describing temporal properties on well objects.
	* The prefered approach to describe temporal properties on Reservoir grids is to use one instance of ContinuousProperty per time step.
	*/
	class ContinuousPropertySeries : public ContinuousProperty
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT ContinuousPropertySeries(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : ContinuousProperty(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param rep						The representation which supports these property values.
		* @param guid						The guid to set to the fault. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param dimension					The dimension of each value (scalar properties == 1).
		* @param attachmentKind				The topological orbit which support each value.
		* @apram uom						The uom of the values
		* @param energisticsPropertyKind	The property type of these property values which must be defined in the standard energistics property kind catalog.
		* @param ts							The associated time series.
		* @param useInterval				Indicates wether the property values will be attached to the time index or to the interval between consecutive time index. 
		*/
		ContinuousPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind,
			const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param rep						The representation which supports these property values.
		* @param guid						The guid to set to the fault. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param dimension					The dimension of each value (scalar properties == 1).
		* @param attachmentKind				The topological orbit which support each value.
		* @apram uom						The uom of the values
		* @param localPropKind				The property type of these property values which must be defined in the EPC document as a local property kind.
		* @param ts							The associated time series.
		* @param useInterval				Indicates wether the property values will be attached to the time index or to the interval between consecutive time index.
		*/
		ContinuousPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind,
			const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, RESQML2_NS::PropertyKind * localPropKind,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		ContinuousPropertySeries(gsoap_resqml2_0_1::_resqml20__ContinuousPropertySeries* fromGsoap): ContinuousProperty(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~ContinuousPropertySeries() {}

		std::string getXmlNamespaceVersion() const {return "2.0.1";}

		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }
	};
}
