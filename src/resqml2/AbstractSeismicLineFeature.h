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

#include "AbstractTechnicalFeature.h"

/** . */
namespace RESQML2_NS
{
	class SeismicLineSetFeature;

	/**
	 * Proxy class for an abstract seismic line feature. Defined by one lateral dimension: trace
	 * (lateral). Seismic trace of the 3D seismic survey. To specify its location, the seismic
	 * feature can be associated with the seismic coordinates of the points of a representation.
	 */
	class AbstractSeismicLineFeature : public AbstractTechnicalFeature
	{
	public:
		/** Destructor does nothing since the memory is manged by the gSOAP context. */
		virtual ~AbstractSeismicLineFeature() {}

		/**
		 * Sets the seismic line set this seismic line belongs to.
		 *
		 * @exception	std::invalid_argument	If @p seisLineSet is @c nullptr.
		 *
		 * @param [in]	seisLineSet	The seismic line set this seismic line belongs to.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setSeismicLineSet(SeismicLineSetFeature * seisLineSet) = 0;

		/**
		 * Gets the seismic line set this seismic line belongs to.
		 *
		 * @returns	@c nullptr if this seismic line does not belong to a seismic line set, else the
		 * 			seismic line set it belongs to.
		 */
		DLL_IMPORT_OR_EXPORT SeismicLineSetFeature* getSeismicLineSet() const;

		/**
		 * Gets the data object reference of the seismic line set this seismic line belongs to.
		 *
		 * @returns	Empty data object reference	if this seismic line does not belong to a seismic line
		 * 			set, else the data object reference of the seismic line set it belongs to.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getSeismicLineSetDor() const = 0;

		/**
		 * Gets the total count of traces in this seismic line.
		 *
		 * @returns	The trace count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getTraceCount() const = 0;

		/**
		 * Gets the trace labels in this seismic line.
		 *
		 * @returns	The trace labels.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::vector<std::string> getTraceLabels() const = 0;

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT AbstractSeismicLineFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractTechnicalFeature(partialObject) {}

		/**
		 * Default constructor
		 */
		AbstractSeismicLineFeature() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractSeismicLineFeature(gsoap_resqml2_0_1::_resqml20__SeismicLineFeature* fromGsoap) :
			AbstractTechnicalFeature(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractSeismicLineFeature(gsoap_eml2_3::resqml22__AbstractSeismicLineFeature* fromGsoap) :
			AbstractTechnicalFeature(fromGsoap) {}

		/** Loads target relationships */
		void loadTargetRelationships() override;
	};
}
