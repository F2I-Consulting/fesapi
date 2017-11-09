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

#include "resqml2_0_1/Grid2dSetRepresentation.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT Grid2dRepresentation : public AbstractSurfaceRepresentation
	{
	private :
		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry2_0_1(const unsigned int & patchIndex) const;
		gsoap_resqml2_0_1::resqml2__Point3dLatticeArray* getArrayLatticeOfPoints3d() const;

		/**
		* Set the supporting representation of this representation and sets the opposite relationship
		* i.e. from the supporting rep to the supported rep.
		* Only updates memory, not XML.
		*/
		void setSupportingRepresentation(Grid2dRepresentation * supportingRep);

	public:

		/**
		* Only to be used in partial transfer context
		*/
		Grid2dRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractSurfaceRepresentation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp				The interpretation this representation represents.
		* @param crs				The local CRS where the geometry of this representation is given.
		* @param guid				The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title				A title for the instance to create.
		*/
		Grid2dRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		Grid2dRepresentation(gsoap_resqml2_0_1::_resqml2__Grid2dRepresentation* fromGsoap): AbstractSurfaceRepresentation(fromGsoap), supportingRepresentation(nullptr) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~Grid2dRepresentation() {}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		std::string getHdfProxyUuid() const;

		/**
		* Get the number of nodes in the I direction of the lattice 2d grid
		*/
		ULONG64 getNodeCountAlongIAxis() const;

		/**
		* Get the number of nodes in the J direction of the lattice 2d grid
		*/
		ULONG64 getNodeCountAlongJAxis() const;

		/**
		* Get the xyz point count in a given patch.
		*/
		ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		* Get all the z values of a patch located at a specific index of the geometry points.
		* Z Values are given in the local CRS.
		* @param values		All the z values of the selected patch. i dimension is the quickest.
		*/
		void getZValues(double * values) const;

		/**
		* Get all the z values of a patch located at a specific index of the geometry points.
		* Z Values are given in the global CRS.
		* @param values		All the z values of the selected patch. i dimension is the quickest.
		*/
		void getZValuesInGlobalCrs(double * values) const;

		/**
		* Get the X origin of this geometry.
		* X coordinate is given in the local CRS.
		* @return				A double.NAN coordinate if something's wrong. The X origin point otherwise.
		*/
		double getXOrigin() const;

		/**
		* Get the Y origin of this geometry.
		* Y coordinate is given in the local CRS.
		* @return				A double.NAN coordinate if something's wrong. The Y origin point otherwise.
		*/
		double getYOrigin() const;

		/**
		* Get the X origin of this geometry.
		* X coordinate is given in the global CRS.
		* @return				A double.NAN coordinate if something's wrong. The X origin point otherwise.
		*/
		double getXOriginInGlobalCrs() const;

		/**
		* Get the Y origin of this geometry.
		* Y coordinate is given in the global CRS.
		* @return				A double.NAN coordinate if something's wrong. The Y origin point otherwise.
		*/
		double getYOriginInGlobalCrs() const;

		/**
		* Get the X (in local crs) offset between two consecutive nodes lying on the J axis.
		* X coordinate is given in the local CRS.
		* @return				A double.NAN coordinate if something's wrong. The X offset point otherwise.
		*/
		double getXJOffset() const;

		/**
		* Get the Y (in local crs) offset between two consecutive nodes lying on the J axis.
		* Y coordinate is given in the local CRS.
		* @return				A double.NAN coordinate if something's wrong. The Y offset point otherwise.
		*/
		double getYJOffset() const;

		/**
		* Get the X (in global crs) offset between two consecutive nodes lying on the J axis.
		* X coordinate is given in the global CRS.
		* @return				A double.NAN coordinate if something's wrong. The X offset point otherwise.
		*/
		double getXJOffsetInGlobalCrs() const;

		/**
		* Get the Y  (in global crs) offset between two consecutive nodes lying on the J axis.
		* Y coordinate is given in the global CRS.
		* @return				A double.NAN coordinate if something's wrong. The Y offset point otherwise.
		*/
		double getYJOffsetInGlobalCrs() const;

		/**
		* Get the X (in local crs) offset between two consecutive nodes lying on the I axis.
		* X coordinate is given in the local CRS.
		* @return				A double.NAN coordinate if something's wrong. The X offset point otherwise.
		*/
		double getXIOffset() const;

		/**
		* Get the Y (in local crs) offset between two consecutive nodes lying on the I axis.
		* Y coordinate is given in the local CRS.
		* @return				A double.NAN coordinate if something's wrong. The Y offset point otherwise.
		*/
		double getYIOffset() const;

		/**
		* Get the X (in global crs) offset between two consecutive nodes lying on the I axis.
		* X coordinate is given in the global CRS.
		* @return				A double.NAN coordinate if something's wrong. The X offset point otherwise.
		*/
		double getXIOffsetInGlobalCrs() const;

		/**
		* Get the Y (in global crs) offset between two consecutive nodes lying on the I axis.
		* Y coordinate is given in the global CRS.
		* @return				A double.NAN coordinate if something's wrong. The Y offset point otherwise.
		*/
		double getYIOffsetInGlobalCrs() const;

		/**
		* Checkes wether the spacing between nodes on J dimension is constant or not.
		*/
		bool isJSpacingConstant() const;

		/**
		* Checkes wether the spacing between nodes on I dimension is constant or not.
		*/
		bool isISpacingConstant() const;
		
		/**
		* Get the constant J (fastest) spacing of this 2d grid representation.
		* @return	The constant spacing in the J direction of the 2d grid representation.
		*/
		double getJSpacing() const;

		/**
		* Get all the J (fastest) spacings of this 2d grid representation.
		* @param jSpacings	The count of this array souhld be JCellCount - 1. It must be preallocated.
		* @return			All the spacings in the J direction of the 2d grid representation.
		*/
		void getJSpacing(double* const jSpacings) const;

		/**
		* Get the constant I (slowest) spacing of this 2d grid representation.
		* @return	The constant spacing in the I direction of the 2d grid representation.
		*/
		double getISpacing() const;

		/**
		* Get all the I (fastest) spacings of this 2d grid representation.
		* @param iSpacings	The count of this array souhld be ICellCount - 1. It must be preallocated.
		* @return			All the spacings in the I direction of the 2d grid representation.
		*/
		void getISpacing(double* const iSpacings) const;

		/**
		* Set the geometry patch for a lattice 2d grid.
		* The set geometry is an array 2d of lattice points3d.
		*/
		void setGeometryAsArray2dOfLatticePoints3d(
			const unsigned int & numPointsInFastestDirection, const unsigned int & numPointsInSlowestDirection,
			const double & xOrigin, const double & yOrigin, const double & zOrigin,
			const double & xOffsetInFastestDirection, const double & yOffsetInFastestDirection, const double & zOffsetInFastestDirection,
			const double & xOffsetInSlowestDirection, const double & yOffsetInSlowestDirection, const double & zOffsetInSlowestDirection,
			const double & spacingInFastestDirection, const double & spacingInSlowestDirection);

		/**
		* Set the geometry patch for a lattice 2d grid.
		* The set geometry is an array 2d of explicit Z based on an existing representation
		*/
		void setGeometryAsArray2dOfExplicitZ(
				double * zValues,
				const unsigned int & numI, const unsigned int & numJ, common::AbstractHdfProxy* proxy,
				Grid2dRepresentation * supportingGrid2dRepresentation,
				const unsigned int & startIndexI = 0, const unsigned int & startIndexJ = 0,
				const int & indexIncrementI = 1, const int & indexIncrementJ = 1);

		/**
		* Set the geometry patch for a lattice 2d grid.
		* The set geometry is an array 2d of explicit Z.
		*/
		void setGeometryAsArray2dOfExplicitZ(
				double * zValues,
				const unsigned int & numI, const unsigned int & numJ, common::AbstractHdfProxy* proxy,
				const double & originX, const double & originY, const double & originZ,
				const double & offsetIX, const double & offsetIY, const double & offsetIZ, const double & spacingI,
				const double & offsetJX, const double & offsetJY, const double & offsetJZ, const double & spacingJ);

		/**
		* Get the supporting representation uuid of this representation.
		* Useful when the supporting representation is not accessible. At least we know its uuid.
		*/
		std::string getSupportingRepresentationUuid() const;

		/**
		* Get the supporting representation of this representation
		*/
		Grid2dRepresentation*  getSupportingRepresentation() {return supportingRepresentation;}

		/**
		* Get the index of the origin of the current geometry on the supporting representation.
		* The index is given by means of the formula iOrigin + jOrigin*iNodeCountOnSupportingRepresentation
		*/
		int getIndexOriginOnSupportingRepresentation() const;

		/**
		* Get the index of the origin of the current geometry on a particular dimension of the supporting representation.
		*/
		int getIndexOriginOnSupportingRepresentation(const unsigned int & dimension) const;

		/**
		* Get the number of nodes of the current geometry which is extracted from a particular dimension of the supporting representation.
		*/
		int getNodeCountOnSupportingRepresentation(const unsigned int & dimension) const;

		/**
		* Get the index offset of the nodes of the current geometry on a particular dimension of the supporting representation.
		*/
		int getIndexOffsetOnSupportingRepresentation(const unsigned int & dimension) const;

		unsigned int getPatchCount() const {return 1;}

	private:
		std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		// Forward relationships
		Grid2dRepresentation * supportingRepresentation;

		// Backward relationships
		std::vector<AbstractRepresentation *> supportedRepresentationSet;

		friend void Grid2dSetRepresentation::pushBackGeometryPatch(
				double * zValues,
				const unsigned int & numI, const unsigned int & numJ, common::AbstractHdfProxy* proxy,
				Grid2dRepresentation * supportingGrid2dRepresentation,
				const unsigned int & startIndexI, const unsigned int & startIndexJ,
				const int & indexIncrementI, const int & indexIncrementJ);
	};
}
