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

#include "resqml2_0_1/AbstractSurfaceRepresentation.h"

namespace RESQML2_0_1_NS
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

		/**
		* Get a component of an XYZ structure.
		*
		* @param componentIndex		The XYZ structure component index to get : 0 is X, 1 is Y and 2 is Z
		* @param withoutTranslation	Sometime we jsut wnat to apply rotation but not translation. For example, it is the case for offset which are XYZ "vectors" and not "XYZ" points.
		*/
		double getComponentInGlobalCrs(double x, double y, double z, size_t componentIndex, bool withoutTranslation = false) const;

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
		Grid2dRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
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
		* @param values		All the z values of the selected patch. i dimension is the quickest. It must be preallocated and won't be freed by this method. Its size must be equel to getNodeCountAlongIAxis() * getNodeCountAlongJAxis().
		*/
		void getZValues(double * values) const;

		/**
		* Get all the z values of a patch located at a specific index of the geometry points.
		* Z Values are given in the global CRS.
		* @param values		All the z values of the selected patch. i dimension is the quickest. It must be preallocated and won't be freed by this method. Its size must be equel to getNodeCountAlongIAxis() * getNodeCountAlongJAxis().
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
		* Get the Z origin of this geometry.
		* Z coordinate is given in the local CRS.
		* @return				A double.NAN coordinate if something's wrong. The Z origin point otherwise.
		*/
		double getZOrigin() const;

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
		* Get the Z origin of this geometry.
		* Z coordinate is given in the global CRS.
		* @return				A double.NAN coordinate if something's wrong. The Z origin point otherwise.
		*/
		double getZOriginInGlobalCrs() const;

		/**
		* Get the X (in local crs) offset on the J axis.
		* If the J spacing is constant, the returned offset is exactly the offset between two consecutive nodes lying on the J axis.
		* If not, the offset length does not have any meaning.
		* X coordinate is given in the local CRS.
		* @return				A double.NAN coordinate if something's wrong. The X offset point otherwise.
		*/
		double getXJOffset() const;

		/**
		* Get the Y (in local crs) offset on the J axis.
		* If the J spacing is constant, the returned offset is exactly the offset between two consecutive nodes lying on the J axis.
		* If not, the offset length does not have any meaning.
		* Y coordinate is given in the local CRS.
		* @return				A double.NAN coordinate if something's wrong. The Y offset point otherwise.
		*/
		double getYJOffset() const;

		/**
		* Get the Z (in local crs) offset on the J axis.
		* If the J spacing is constant, the returned offset is exactly the offset between two consecutive nodes lying on the J axis.
		* If not, the offset length does not have any meaning.
		* Z coordinate is given in the local CRS.
		* @return				A double.NAN coordinate if something's wrong. The Z offset point otherwise.
		*/
		double getZJOffset() const;

		/**
		* Get the X (in global crs) offset between two consecutive nodes lying on the J axis.
		* X coordinate is given in the global CRS.
		* @return				A double.NAN coordinate if something's wrong. The X offset point otherwise.
		*/
		double getXJOffsetInGlobalCrs() const;

		/**
		* Get the Y (in global crs) offset between two consecutive nodes lying on the J axis.
		* Y coordinate is given in the global CRS.
		* @return				A double.NAN coordinate if something's wrong. The Y offset point otherwise.
		*/
		double getYJOffsetInGlobalCrs() const;

		/**
		* Get the Z (in global crs) offset between two consecutive nodes lying on the J axis.
		* Z coordinate is given in the global CRS.
		* @return				A double.NAN coordinate if something's wrong. The Z offset point otherwise.
		*/
		double getZJOffsetInGlobalCrs() const;

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
		* Get the Z (in local crs) offset between two consecutive nodes lying on the I axis.
		* Z coordinate is given in the local CRS.
		* @return				A double.NAN coordinate if something's wrong. The Z offset point otherwise.
		*/
		double getZIOffset() const;

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
		* Get the Z (in global crs) offset between two consecutive nodes lying on the I axis.
		* Z coordinate is given in the global CRS.
		* @return				A double.NAN coordinate if something's wrong. The Z offset point otherwise.
		*/
		double getZIOffsetInGlobalCrs() const;

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
		* @param jSpacings	The count of this array should be getNodeCountAlongJAxis - 1. It must be preallocated and won't be freed by this method.
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
		* @param iSpacings	The count of this array shouhd be getNodeCountAlongIAxis - 1. It must be preallocated and won't be freed by this method.
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
				const unsigned int & numI, const unsigned int & numJ, COMMON_NS::AbstractHdfProxy* proxy,
				Grid2dRepresentation * supportingGrid2dRepresentation,
				const unsigned int & startIndexI = 0, const unsigned int & startIndexJ = 0,
				const int & indexIncrementI = 1, const int & indexIncrementJ = 1);

		/**
		* Set the geometry patch for a lattice 2d grid.
		* The set geometry is an array 2d of explicit Z.
		*/
		void setGeometryAsArray2dOfExplicitZ(
				double * zValues,
				const unsigned int & numI, const unsigned int & numJ, COMMON_NS::AbstractHdfProxy* proxy,
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
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);

		// Forward relationships
		Grid2dRepresentation * supportingRepresentation;

		// Backward relationships
		std::vector<AbstractRepresentation *> supportedRepresentationSet;
	};
}

