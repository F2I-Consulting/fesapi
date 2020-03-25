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

#include "../resqml2/AbstractRepresentation.h"

/** . */
namespace RESQML2_0_1_NS
{
	/** An abstract surface representation. */
	class AbstractSurfaceRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT AbstractSurfaceRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractRepresentation(partialObject) {}

		/** Default constructor Set the gsoap proxy to nullptr. */
		AbstractSurfaceRepresentation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		AbstractSurfaceRepresentation(gsoap_resqml2_0_1::resqml20__AbstractSurfaceRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}

		/**
		 * Try to get a Point3dFromRepresentationLatticeArray from the geometry of a patch of the
		 * representation.
		 *
		 * @param [in,out]	patch	If non-null, the patch.
		 *
		 * @returns	nullptr if the geoemtry does not contain such an information.
		 */
		gsoap_resqml2_0_1::resqml20__Point3dFromRepresentationLatticeArray* getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(gsoap_resqml2_0_1::resqml20__PointGeometry* patch) const;

		/**
		 * Creates an array 2d of lattice points 3d.
		 *
		 * @param 		  	numPointsInFastestDirection	Number of points in fastest directions.
		 * @param 		  	numPointsInSlowestDirection	Number of points in slowest directions.
		 * @param 		  	xOrigin					   	The origin.
		 * @param 		  	yOrigin					   	The origin.
		 * @param 		  	zOrigin					   	The origin.
		 * @param 		  	xOffsetInFastestDirection  	The offset in fastest direction.
		 * @param 		  	yOffsetInFastestDirection  	The offset in fastest direction.
		 * @param 		  	zOffsetInFastestDirection  	The offset in fastest direction.
		 * @param 		  	xOffsetInSlowestDirection  	The offset in slowest direction.
		 * @param 		  	yOffsetInSlowestDirection  	The offset in slowest direction.
		 * @param 		  	zOffsetInSlowestDirection  	The offset in slowest direction.
		 * @param 		  	spacingInFastestDirection  	The spacing in fastest direction.
		 * @param 		  	spacingInSlowestDirection  	The spacing in slowest direction.
		 * @param [in,out]	localCrs				   	If non-null, the local crs.
		 *
		 * @returns	Null if it fails, else the new array 2D of lattice points 3D.
		 */
		gsoap_resqml2_0_1::resqml20__PointGeometry* createArray2dOfLatticePoints3d(
			unsigned int numPointsInFastestDirection, unsigned int numPointsInSlowestDirection,
			double xOrigin, double yOrigin, double zOrigin,
			double xOffsetInFastestDirection, double yOffsetInFastestDirection, double zOffsetInFastestDirection,
			double xOffsetInSlowestDirection, double yOffsetInSlowestDirection, double zOffsetInSlowestDirection,
			double spacingInFastestDirection, double spacingInSlowestDirection, RESQML2_NS::AbstractLocal3dCrs * localCrs);

		/**
		 * Creates a geometry for a grid 2d representation which derives from another existing grid 2d
		 * representation.
		 *
		 * @param 		  	patchIndex					Zero-based index of the patch.
		 * @param [in,out]	zValues						All the z values to add. It must be numI * numJ
		 * 												count.
		 * @param [in,out]	localCrs					The lcoal cRS where the Z values are.
		 * @param 		  	numI						Number of z values in the first dimension of the
		 * 												array to add.
		 * @param 		  	numJ						Number of z values in the second dimension of the
		 * 												array to add.
		 * @param [in,out]	proxy						The hdf proxy which indicates the hdf file where
		 * 												the values will be stored.
		 * @param [in,out]	supportingRepresentation	The lattice grid representation these Z values
		 * 												use as a support.
		 * @param 		  	startGlobalIndex			(Optional) The first global (representation)
		 * 												index of the baseLatticeGridRepresentation where a z
		 * 												value will be stored.
		 * @param 		  	indexIncrementI				(Optional) The constant index increment between
		 * 												two consecutive nodes on the first dimension of the
		 * 												baseLatticeGridRepresentation where z values will be
		 * 												stored.
		 * @param 		  	indexIncrementJ				(Optional) The constant index increment between
		 * 												two consecutive nodes on the second dimension of the
		 * 												baseLatticeGridRepresentation where z values will be
		 * 												stored.
		 *
		 * @returns	Null if it fails, else the new array 2D of explicit z coordinate.
		 */
		gsoap_resqml2_0_1::resqml20__PointGeometry* createArray2dOfExplicitZ(
			unsigned int patchIndex, double * zValues, RESQML2_NS::AbstractLocal3dCrs * localCrs,
			unsigned int numI, unsigned int numJ, EML2_NS::AbstractHdfProxy* proxy,
			class Grid2dRepresentation * supportingRepresentation,
			unsigned int startGlobalIndex = 0,
			int indexIncrementI = 1, int indexIncrementJ = 1);

		/**
		 * Push back a geometry for a grid 2d representation which defines its own support. This
		 * geoemtry does not derive from another existing grid 2d representation.
		 *
		 * @param 		  	patchIndex	Zero-based index of the patch.
		 * @param [in,out]	zValues   	All the z values to add. It must be numI * numJ count.
		 * @param [in,out]	localCrs  	The lcoal cRS where the Z values are.
		 * @param 		  	numI	  	Number of z values in the first dimension of the array to add.
		 * @param 		  	numJ	  	Number of z values in the second dimension of the array to add.
		 * @param [in,out]	proxy	  	The hdf proxy which indicates the hdf file where the values will
		 * 								be stored.
		 * @param 		  	originX   	The origin x coordinate.
		 * @param 		  	originY   	The origin y coordinate.
		 * @param 		  	originZ   	The origin z coordinate.
		 * @param 		  	offsetIX  	Zero-based index of the offset.
		 * @param 		  	offsetIY  	The offset iy.
		 * @param 		  	offsetIZ  	The offset iz.
		 * @param 		  	spacingI  	The spacing i.
		 * @param 		  	offsetJX  	The offset jx.
		 * @param 		  	offsetJY  	The offset jy.
		 * @param 		  	offsetJZ  	The offset jz.
		 * @param 		  	spacingJ  	The spacing j.
		 *
		 * @returns	Null if it fails, else the new array 2D of explicit z coordinate.
		 */
		gsoap_resqml2_0_1::resqml20__PointGeometry* createArray2dOfExplicitZ(
			unsigned int patchIndex, double * zValues, RESQML2_NS::AbstractLocal3dCrs * localCrs,
			unsigned int numI, unsigned int numJ, EML2_NS::AbstractHdfProxy* proxy,
			double originX, double originY, double originZ,
			double offsetIX, double offsetIY, double offsetIZ, double spacingI,
			double offsetJX, double offsetJY, double offsetJZ, double spacingJ);

		/** Loads target relationships */
		virtual void loadTargetRelationships();

	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~AbstractSurfaceRepresentation() {}

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
		DLL_IMPORT_OR_EXPORT void setSurfaceRole(const gsoap_resqml2_0_1::resqml20__SurfaceRole & surfaceRole);

		/**
		 * Get the surface role of this representation. map : Representation support for properties.
		 * pick : Representation support for 3D points picked in 2D or 3D.
		 *
		 * @returns	The surface role.
		 */
		DLL_IMPORT_OR_EXPORT const gsoap_resqml2_0_1::resqml20__SurfaceRole & getSurfaceRole() const;
	};
}
