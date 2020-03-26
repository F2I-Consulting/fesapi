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

	/** A seismic line feature. */
	class AbstractSeismicLineFeature : public AbstractTechnicalFeature
	{
	public:
		/** Destructor does nothing since the memory is manged by the gsoap context. */
		virtual ~AbstractSeismicLineFeature() {}

		/**
		 * Sets seismic line set
		 *
		 * @param [in,out]	seisLineSet	If non-null, set the seis line belongs to.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setSeismicLineSet(SeismicLineSetFeature * seisLineSet) = 0;

		/** A seismic line set feature*. */
		DLL_IMPORT_OR_EXPORT SeismicLineSetFeature* getSeismicLineSet() const;

		/** A DOR to the seismic line set feature*. */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getSeismicLineSetDor() const = 0;

		/**
		 * Get the total count of traces in this seismic line.
		 *
		 * @returns	The trace count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getTraceCount() const = 0;

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
		void loadTargetRelationships();
	};
}
