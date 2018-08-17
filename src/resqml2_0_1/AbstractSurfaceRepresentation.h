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

#include "resqml2/AbstractRepresentation.h"

namespace RESQML2_0_1_NS
{
	class DLL_IMPORT_OR_EXPORT AbstractSurfaceRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractSurfaceRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractRepresentation(partialObject) {}

		/**
		* Default constructor
		* Set the gsoap proxy to nullptr.
		*/
		AbstractSurfaceRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs) : RESQML2_NS::AbstractRepresentation(interp, crs) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractSurfaceRepresentation(gsoap_resqml2_0_1::resqml2__AbstractSurfaceRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}

		/**
		* Try to get a Point3dFromRepresentationLatticeArray from the geometry of a patch of the representation.
		* @return	nullptr if the geoemtry does not contain such an information.
		*/
		gsoap_resqml2_0_1::resqml2__Point3dFromRepresentationLatticeArray* getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(gsoap_resqml2_0_1::resqml2__PointGeometry* patch) const;

		/**
		* Creates an array 2d of lattice points 3d.
		*/
		gsoap_resqml2_0_1::resqml2__PointGeometry* createArray2dOfLatticePoints3d(
			const unsigned int & numPointsInFastestDirection, const unsigned int & numPointsInSlowestDirection,
			const double & xOrigin, const double & yOrigin, const double & zOrigin,
			const double & xOffsetInFastestDirection, const double & yOffsetInFastestDirection, const double & zOffsetInFastestDirection,
			const double & xOffsetInSlowestDirection, const double & yOffsetInSlowestDirection, const double & zOffsetInSlowestDirection,
			const double & spacingInFastestDirection, const double & spacingInSlowestDirection);

		/**
		* Creates a geometry for a grid 2d representation which derives from another existing grid 2d representation.
		* @param	zValues							All the z values to add. It must be numI * numJ count.
		* @param	numI							Number of z values in the first dimension of the array to add.
		* @param	numJ							Number of z values in the second dimension of the array to add.
		* @param	AbstractHdfProxy						The hdf proxy which indicates the hdf file where the values will be stored.
		* @param	supportingRepresentation		The lattice grid representation these Z values use as a support.
		* @param	startGlobalIndex				The first global (representation) index of the baseLatticeGridRepresentation where a z value will be stored.
		* @param	indexIncrementI					The constant index increment between two consecutive nodes on the first dimension of the baseLatticeGridRepresentation where z values will be stored.
		* @param	indexIncrementJ					The constant index increment between two consecutive nodes on the second dimension of the baseLatticeGridRepresentation where z values will be stored.
		*/
		gsoap_resqml2_0_1::resqml2__PointGeometry* createArray2dOfExplicitZ(
			const unsigned int & patchIndex, double * zValues,
			const unsigned int & numI, const unsigned int & numJ, COMMON_NS::AbstractHdfProxy* proxy,
			class Grid2dRepresentation * supportingRepresentation,
			const unsigned int & startGlobalIndex = 0,
			const int & indexIncrementI = 1, const int & indexIncrementJ = 1);

		/**
		* Push back a geometry for a grid 2d representation which defines its own support. This geoemtry does not derive from another existing grid 2d representation.
		* @param	zValues							All the z values to add. It must be numI * numJ count.
		* @param	numI							Number of z values in the first dimension of the array to add.
		* @param	numJ							Number of z values in the second dimension of the array to add.
		* @param	AbstractHdfProxy						The hdf proxy which indicates the hdf file where the values will be stored.
		*/
		gsoap_resqml2_0_1::resqml2__PointGeometry* createArray2dOfExplicitZ(
			const unsigned int & patchIndex, double * zValues,
			const unsigned int & numI, const unsigned int & numJ, COMMON_NS::AbstractHdfProxy* proxy,
			const double & originX, const double & originY, const double & originZ,
			const double & offsetIX, const double & offsetIY, const double & offsetIZ, const double & spacingI,
			const double & offsetJX, const double & offsetJY, const double & offsetJZ, const double & spacingJ);

		virtual void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);

		std::vector<PolylineRepresentation*> outerRingSet; // outer rings are ordered as the patches of the representation are ordered.

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractSurfaceRepresentation() {}

		/**
		 * Push back an outer ring of this representation
		 * The index of the ring must correspond to the index of the patch it delimits.
		 */
		void pushBackOuterRing(PolylineRepresentation * outerRing);

		/**
		* Set the surface role of the representation.
		* map : Representation support for properties.
		* pick : Representation support for 3D points picked in 2D or 3D.
		*/
		void setSurfaceRole(const gsoap_resqml2_0_1::resqml2__SurfaceRole & surfaceRole);

		/**
		* Get the surface role of this representation.
		* map : Representation support for properties.
		* pick : Representation support for 3D points picked in 2D or 3D.
		*/
		const gsoap_resqml2_0_1::resqml2__SurfaceRole & getSurfaceRole() const;

		virtual std::vector<epc::Relationship> getAllTargetRelationships() const;
	};
}

