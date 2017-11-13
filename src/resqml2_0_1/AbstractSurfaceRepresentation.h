/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#pragma once

#include "resqml2/AbstractRepresentation.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT AbstractSurfaceRepresentation : public resqml2::AbstractRepresentation
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractSurfaceRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : resqml2::AbstractRepresentation(partialObject) {}

		/**
		* Default constructor
		* Set the gsoap proxy to nullptr.
		*/
		AbstractSurfaceRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs) : resqml2::AbstractRepresentation(interp, crs) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractSurfaceRepresentation(gsoap_resqml2_0_1::resqml2__AbstractSurfaceRepresentation* fromGsoap) : resqml2::AbstractRepresentation(fromGsoap) {}

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
			const unsigned int & numI, const unsigned int & numJ, common::AbstractHdfProxy* proxy,
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
			const unsigned int & numI, const unsigned int & numJ, common::AbstractHdfProxy* proxy,
			const double & originX, const double & originY, const double & originZ,
			const double & offsetIX, const double & offsetIY, const double & offsetIZ, const double & spacingI,
			const double & offsetJX, const double & offsetJY, const double & offsetJZ, const double & spacingJ);

		virtual std::vector<epc::Relationship> getAllEpcRelationships() const;

		virtual void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

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


	};
}
