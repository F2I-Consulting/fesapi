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

#include "resqml2_0_1/ContinuousProperty.h"

namespace resqml2_0_1
{
	/**
	* This class is mainly useful for describing temporal properties on well objects.
	* The prefered approach to describe temporal properties on Reservoir grids is to use one instance of ContinuousProperty per time step.
	*/
	class DLL_IMPORT_OR_EXPORT ContinuousPropertySeries : public ContinuousProperty
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		ContinuousPropertySeries(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : ContinuousProperty(partialObject) {}

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
		ContinuousPropertySeries(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind,
			resqml2::TimeSeries * ts, const bool & useInterval = false);

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
		ContinuousPropertySeries(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2::PropertyKind * localPropKind,
			resqml2::TimeSeries * ts, const bool & useInterval = false);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		ContinuousPropertySeries(gsoap_resqml2_0_1::_resqml2__ContinuousPropertySeries* fromGsoap): ContinuousProperty(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~ContinuousPropertySeries() {}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		std::string getResqmlVersion() const {return "2.0.1";}
	};
}

