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

#include "../resqml2/StreamlinesFeature.h"

namespace RESQML2_2_NS
{
	/**
	 * @brief	Specification of the vector field upon which the streamlines are based.
	 *
	 * 			Streamlines are commonly used to trace the flow of phases (water / oil / gas / total)
	 *			based upon their flux at a specified time. They may also be used for trace components
	 *			for compositional simulation, e.g., CO2, or temperatures for thermal simulation.
	 */
	class StreamlinesFeature final : public RESQML2_NS::StreamlinesFeature
	{
	public:
		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT StreamlinesFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::StreamlinesFeature(partialObject) {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		StreamlinesFeature(gsoap_eml2_3::_resqml22__StreamlinesFeature* fromGsoap) : RESQML2_NS::StreamlinesFeature(fromGsoap) {}

		/**
		 * @brief	Construct a streamlines feature into a repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 		The guid to set to the streamlines feature. If empty then a new guid will be
		 * 						generated.
		 * @param 	title		The title to set to the streamlines feature. If empty then \"unknown\" title
		 * 						will be set.
		 * @param 	timeIndex	The time index in the time series of the this streamlines feature.
		 * @param 	timeSeries	The time series where the time index of this streamlines feature is given.
		 */
		StreamlinesFeature(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title, uint64_t timeIndex, EML2_NS::TimeSeries* timeSeries);

		/**
		* Destructor does nothing since the memory is managed by the gSOAP context.
		*/
		~StreamlinesFeature() = default;

		/**
		 * Gets the time index in the Time series associated to this streamlines feature.
		 *
		 * @exception	std::logic_error	If this feature is partial.
		 *
		 * @returns	the time index in the Time series associated to this streamlines feature
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getTimeIndex() const final;

		/**
		 * Gets the Time series DOR associated to this streamlines feature.
		 *
		 * @exception	std::logic_error	If this feature is partial or if this feature is standard invalid.
		 *
		 * @returns	The associated streamlines feature DOR.
		 */
		COMMON_NS::DataObjectReference getTimeSeriesDor() const final;

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
