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
	/** A seismic lattice feature. */
	class SeismicLatticeFeature : public AbstractTechnicalFeature
	{
	public:

		/** Destructor does nothing since the memory is manged by the gsoap context. */
		virtual ~SeismicLatticeFeature() {}

		/**
		 * Get the crossline index increment between two consecutive crosslines.
		 *
		 * @returns	The crossline increment.
		 */
		DLL_IMPORT_OR_EXPORT virtual int getCrosslineIncrement() const = 0;

		/**
		 * Get the inline index increment between two consecutive inlines.
		 *
		 * @returns	The inline increment.
		 */
		DLL_IMPORT_OR_EXPORT virtual int getInlineIncrement() const = 0;

		/**
		 * Get the index of the first crossline.
		 *
		 * @returns	The origin crossline.
		 */
		DLL_IMPORT_OR_EXPORT virtual int getOriginCrossline() const = 0;

		/**
		 * Get the index of the first inline.
		 *
		 * @returns	The origin inline.
		 */
		DLL_IMPORT_OR_EXPORT virtual int getOriginInline() const = 0;

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:
		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT SeismicLatticeFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractTechnicalFeature(partialObject) {}

		/**
		 * Default cosntructor
		 */
		SeismicLatticeFeature() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		SeismicLatticeFeature(gsoap_resqml2_0_1::_resqml20__SeismicLatticeFeature* fromGsoap): RESQML2_NS::AbstractTechnicalFeature(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		SeismicLatticeFeature(gsoap_eml2_3::_resqml22__SeismicLatticeFeature* fromGsoap): RESQML2_NS::AbstractTechnicalFeature(fromGsoap) {}
	};
}
