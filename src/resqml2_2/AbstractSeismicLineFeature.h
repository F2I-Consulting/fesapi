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

#include "../resqml2/AbstractSeismicLineFeature.h"

/** . */
namespace RESQML2_2_NS
{
	/**
	 * Proxy class for an abstract seismic line feature. Defined by one lateral dimension: trace
	 * (lateral). Seismic trace of the 3D seismic survey. To specify its location, the seismic
	 * feature can be associated with the seismic coordinates of the points of a representation.
	 */
	class AbstractSeismicLineFeature : public RESQML2_NS::AbstractSeismicLineFeature
	{
	public:
		/** Destructor does nothing since the memory is manged by the gSOAP context. */
		virtual ~AbstractSeismicLineFeature() {}

		/**
		 * Sets the trace labels.
		 *
		 * @param [in]	values	The labels to set.
		 * @param [in]	proxy	The proxy where to write the labels.
		 */
		DLL_IMPORT_OR_EXPORT void setTraceLabels(const std::vector<std::string> & values, EML2_NS::AbstractHdfProxy * proxy);

		/**
		 * Sets the seismic line set this seismic line belongs to.
		 *
		 * @exception	std::invalid_argument	If @p seisLineSet is @c nullptr.
		 *
		 * @param [in]	seisLineSet	The seismic line set this seismic line belongs to.
		 */
		DLL_IMPORT_OR_EXPORT void setSeismicLineSet(RESQML2_NS::SeismicLineSetFeature * seisLineSet) final;

		/**
		 * Gets the data object reference of the seismic line set this seismic line belongs to.
		 *
		 * @returns	Empty data object reference	if this seismic line does not belong to a seismic line
		 * 			set, else the data object reference of the seismic line set it belongs to.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getSeismicLineSetDor() const final;

		/**
		 * Gets the trace labels in this seismic line.
		 *
		 * @returns	The trace labels.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<std::string> getTraceLabels() const final;

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT AbstractSeismicLineFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractSeismicLineFeature(partialObject) {}

		/**
		 * Default constructor
		 */
		AbstractSeismicLineFeature() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractSeismicLineFeature(gsoap_eml2_3::resqml22__AbstractSeismicLineFeature* fromGsoap) :
			RESQML2_NS::AbstractSeismicLineFeature(fromGsoap) {}

		/** Loads target relationships */
		void loadTargetRelationships() override;
	};
}
