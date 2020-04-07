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

#include "PolylineRepresentation.h"

/** . */
namespace RESQML2_NS
{
	class PolylineRepresentation;

	/** An abstract surface representation. */
	class AbstractSurfaceRepresentation : public AbstractRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~AbstractSurfaceRepresentation() {}

		/** Get the count of boundaries. */
		unsigned int getBoundariesCount() const;

		/** Get the DOR of an outer ring at a particular index. */
		COMMON_NS::DataObjectReference getOuterRingDor(unsigned int index) const;

		/**
		 * Push back an outer ring of this representation The index of the ring must correspond to the
		 * index of the patch it delimits.
		 *
		 * @param [in,out]	outerRing	If non-null, the outer ring.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackOuterRing(PolylineRepresentation * outerRing);

		/**
		 * Set the surface role of the representation. map : Representation support for properties. pick
		 * : Representation support for 3D points picked in 2D or 3D.
		 *
		 * @param 	surfaceRole	The surface role.
		 */
		DLL_IMPORT_OR_EXPORT void setSurfaceRole(gsoap_resqml2_0_1::resqml20__SurfaceRole surfaceRole);

		/**
		 * Get the surface role of this representation. map : Representation support for properties.
		 * pick : Representation support for 3D points picked in 2D or 3D.
		 *
		 * @returns	The surface role.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__SurfaceRole getSurfaceRole() const;

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
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
