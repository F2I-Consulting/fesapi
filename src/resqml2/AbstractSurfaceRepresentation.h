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

#include "AbstractRepresentation.h"

namespace RESQML2_NS
{
	class PolylineRepresentation;

	/**
	 * @brief	An abstract surface representation. It is the parent class of structural surface
	 * 			representations, which can be bounded by an outer ring and has inner rings. These
	 * 			surfaces may consist of one or more patches.
	 */
	class AbstractSurfaceRepresentation : public AbstractRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~AbstractSurfaceRepresentation() {}

		/**
		 * Gets the count of boundaries.
		 *
		 * @exception	std::logic_error	If the RESQML version is unknown.
		 *
		 * @returns	The boundaries count.
		 */
		unsigned int getBoundariesCount() const;

		/**
		 * Gets the DOR of an outer ring at a particular index.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getBoundariesCount().
		 * @exception	std::logic_error 	If the RESQML version is unknown.
		 *
		 * @param 	index	Zero-based index of the outer ring we look for.
		 *
		 * @returns	The DOR of the outer ring at position @p index.
		 */
		COMMON_NS::DataObjectReference getOuterRingDor(unsigned int index) const;

		/**
		 * Pushes back an outer ring at the first available boundary index of this surface
		 * representation. The index of the patch referenced by this ring will be the same index than
		 * this ring boundary.
		 *
		 * @exception	std::invalid_argument	If @p outerRing <tt>== nullptr</tt>.
		 * @exception	std::logic_error	 	If the RESQML version is unknown.
		 *
		 * @param [in]	outerRing	A polyline representation of the outer ring to push back.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackOuterRing(PolylineRepresentation * outerRing);

		/**
		 * Sets the surface role of this representation.
		 *
		 * @exception	std::logic_error	If the RESQML version is unknown.
		 *
		 * @param 	surfaceRole	The surface role to set. It can be "map" (representation support for
		 * 						properties) or "pick" (representation support for 3d points picked in 2d
		 * 						or 3d).
		 */
		DLL_IMPORT_OR_EXPORT void setSurfaceRole(gsoap_resqml2_0_1::resqml20__SurfaceRole surfaceRole);

		/**
		 * Gets the surface role of this representation.
		 *
		 * @exception	std::logic_error	If the RESQML version is unknown.
		 *
		 * @returns	The surface role of this representation. It can be "map" (representation support for
		 * 			properties) or "pick" (representation support for 3d points picked in 2d or 3d).
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__SurfaceRole getSurfaceRole() const;

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT AbstractSurfaceRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractRepresentation(partialObject) {}

		/** Default constructor Set the gsoap proxy to nullptr. */
		AbstractSurfaceRepresentation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractSurfaceRepresentation(gsoap_resqml2_0_1::resqml20__AbstractSurfaceRepresentation* fromGsoap) : AbstractRepresentation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractSurfaceRepresentation(gsoap_eml2_3::resqml22__AbstractSurfaceRepresentation* fromGsoap) : AbstractRepresentation(fromGsoap) {}

		/** Loads target relationships */
		virtual void loadTargetRelationships();
	};
}
