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

#include "AbstractSurfaceRepresentation.h"

/** . */
namespace RESQML2_NS
{
	/** A grid 2D representation. */
	class Grid2dRepresentation : public AbstractSurfaceRepresentation
	{
	public:
		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~Grid2dRepresentation() {}

		/**
		 * Get the number of nodes in the I direction of the lattice 2d grid
		 *
		 * @returns	The node count along i axis.
		 */
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getNodeCountAlongIAxis() const = 0;

		/**
		 * Get the number of nodes in the J direction of the lattice 2d grid
		 *
		 * @returns	The node count along j axis.
		 */
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getNodeCountAlongJAxis() const = 0;

		/**
		 * Get the xyz point count in a given patch.
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	The xyz point count of patch.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const final;

		/**
		 * Get all the XYZ points of a particular patch of this representation. XYZ points are given in
		 * the local CRS.
		 *
		 * @param 		  	patchIndex	Zero-based index of the patch.
		 * @param [in,out]	xyzPoints 	A linearized 2d array where the first (quickest) dimension is
		 * 								coordinate dimension (XYZ) and second dimension is vertex
		 * 								dimension. It must be pre allocated.
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const final;

		/**
		 * Get all the z values of a patch located at a specific index of the geometry points. Z Values
		 * are given in the local CRS.
		 *
		 * @param [in,out]	values	All the z values of the selected patch. i dimension is the quickest.
		 * 							It must be preallocated and won't be freed by this method. Its size
		 * 							must be equel to getNodeCountAlongIAxis() * getNodeCountAlongJAxis().
		 */
		DLL_IMPORT_OR_EXPORT virtual void getZValues(double * values) const = 0;

		/**
		 * Get all the z values of a patch located at a specific index of the geometry points. Z Values
		 * are given in the global CRS.
		 *
		 * @param [in,out]	values	All the z values of the selected patch. i dimension is the quickest.
		 * 							It must be preallocated and won't be freed by this method. Its size
		 * 							must be equel to getNodeCountAlongIAxis() * getNodeCountAlongJAxis().
		 */
		DLL_IMPORT_OR_EXPORT void getZValuesInGlobalCrs(double * values) const;

		/**
		 * Get the X origin of this geometry. X coordinate is given in the local CRS.
		 *
		 * @returns	A double.NAN coordinate if something's wrong. The X origin point otherwise.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getXOrigin() const = 0;

		/**
		 * Get the Y origin of this geometry. Y coordinate is given in the local CRS.
		 *
		 * @returns	A double.NAN coordinate if something's wrong. The Y origin point otherwise.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getYOrigin() const = 0;

		/**
		 * Get the Z origin of this geometry. Z coordinate is given in the local CRS.
		 *
		 * @returns	A double.NAN coordinate if something's wrong. The Z origin point otherwise.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getZOrigin() const = 0;

		/**
		 * Get the X origin of this geometry. X coordinate is given in the global CRS.
		 *
		 * @returns	A double.NAN coordinate if something's wrong. The X origin point otherwise.
		 */
		DLL_IMPORT_OR_EXPORT double getXOriginInGlobalCrs() const;

		/**
		 * Get the Y origin of this geometry. Y coordinate is given in the global CRS.
		 *
		 * @returns	A double.NAN coordinate if something's wrong. The Y origin point otherwise.
		 */
		DLL_IMPORT_OR_EXPORT double getYOriginInGlobalCrs() const;

		/**
		 * Get the Z origin of this geometry. Z coordinate is given in the global CRS.
		 *
		 * @returns	A double.NAN coordinate if something's wrong. The Z origin point otherwise.
		 */
		DLL_IMPORT_OR_EXPORT double getZOriginInGlobalCrs() const;

		/**
		 * Get the X (in local crs) offset on the J axis. If the J spacing is constant, the returned
		 * offset is exactly the offset between two consecutive nodes lying on the J axis. If not, the
		 * offset length does not have any meaning. X coordinate is given in the local CRS.
		 *
		 * @returns	A double.NAN coordinate if something's wrong. The X offset point otherwise.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getXJOffset() const = 0;

		/**
		 * Get the Y (in local crs) offset on the J axis. If the J spacing is constant, the returned
		 * offset is exactly the offset between two consecutive nodes lying on the J axis. If not, the
		 * offset length does not have any meaning. Y coordinate is given in the local CRS.
		 *
		 * @returns	A double.NAN coordinate if something's wrong. The Y offset point otherwise.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getYJOffset() const = 0;

		/**
		 * Get the Z (in local crs) offset on the J axis. If the J spacing is constant, the returned
		 * offset is exactly the offset between two consecutive nodes lying on the J axis. If not, the
		 * offset length does not have any meaning. Z coordinate is given in the local CRS.
		 *
		 * @returns	A double.NAN coordinate if something's wrong. The Z offset point otherwise.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getZJOffset() const = 0;

		/**
		 * Get the X (in global crs) offset between two consecutive nodes lying on the J axis. X
		 * coordinate is given in the global CRS.
		 *
		 * @returns	A double.NAN coordinate if something's wrong. The X offset point otherwise.
		 */
		DLL_IMPORT_OR_EXPORT double getXJOffsetInGlobalCrs() const;

		/**
		 * Get the Y (in global crs) offset between two consecutive nodes lying on the J axis. Y
		 * coordinate is given in the global CRS.
		 *
		 * @returns	A double.NAN coordinate if something's wrong. The Y offset point otherwise.
		 */
		DLL_IMPORT_OR_EXPORT double getYJOffsetInGlobalCrs() const;

		/**
		 * Get the Z (in global crs) offset between two consecutive nodes lying on the J axis. Z
		 * coordinate is given in the global CRS.
		 *
		 * @returns	A double.NAN coordinate if something's wrong. The Z offset point otherwise.
		 */
		DLL_IMPORT_OR_EXPORT double getZJOffsetInGlobalCrs() const;

		/**
		 * Get the X (in local crs) offset between two consecutive nodes lying on the I axis. X
		 * coordinate is given in the local CRS.
		 *
		 * @returns	A double.NAN coordinate if something's wrong. The X offset point otherwise.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getXIOffset() const = 0;

		/**
		 * Get the Y (in local crs) offset between two consecutive nodes lying on the I axis. Y
		 * coordinate is given in the local CRS.
		 *
		 * @returns	A double.NAN coordinate if something's wrong. The Y offset point otherwise.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getYIOffset() const = 0;

		/**
		 * Get the Z (in local crs) offset between two consecutive nodes lying on the I axis. Z
		 * coordinate is given in the local CRS.
		 *
		 * @returns	A double.NAN coordinate if something's wrong. The Z offset point otherwise.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getZIOffset() const = 0;

		/**
		 * Get the X (in global crs) offset between two consecutive nodes lying on the I axis. X
		 * coordinate is given in the global CRS.
		 *
		 * @returns	A double.NAN coordinate if something's wrong. The X offset point otherwise.
		 */
		DLL_IMPORT_OR_EXPORT double getXIOffsetInGlobalCrs() const;

		/**
		 * Get the Y (in global crs) offset between two consecutive nodes lying on the I axis. Y
		 * coordinate is given in the global CRS.
		 *
		 * @returns	A double.NAN coordinate if something's wrong. The Y offset point otherwise.
		 */
		DLL_IMPORT_OR_EXPORT double getYIOffsetInGlobalCrs() const;

		/**
		 * Get the Z (in global crs) offset between two consecutive nodes lying on the I axis. Z
		 * coordinate is given in the global CRS.
		 *
		 * @returns	A double.NAN coordinate if something's wrong. The Z offset point otherwise.
		 */
		DLL_IMPORT_OR_EXPORT double getZIOffsetInGlobalCrs() const;

		/**
		 * Checkes wether the spacing between nodes on J dimension is constant or not.
		 *
		 * @returns	True if j spacing constant, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isJSpacingConstant() const = 0;

		/**
		 * Checkes wether the spacing between nodes on I dimension is constant or not.
		 *
		 * @returns	True if i spacing constant, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isISpacingConstant() const = 0;

		/**
		 * Get the constant J (fastest) spacing of this 2d grid representation.
		 *
		 * @returns	The constant spacing in the J direction of the 2d grid representation.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getJSpacing() const = 0;

		/**
		 * Get all the J (fastest) spacings of this 2d grid representation.
		 *
		 * @param [in,out]	jSpacings	The count of this array should be getNodeCountAlongJAxis - 1. It
		 * 								must be preallocated and won't be freed by this method.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getJSpacing(double* jSpacings) const = 0;

		/**
		 * Get the constant I (slowest) spacing of this 2d grid representation.
		 *
		 * @returns	The constant spacing in the I direction of the 2d grid representation.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getISpacing() const = 0;

		/**
		 * Get all the I (fastest) spacings of this 2d grid representation.
		 *
		 * @param [in,out]	iSpacings	The count of this array shouhd be getNodeCountAlongIAxis - 1. It
		 * 								must be preallocated and won't be freed by this method.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getISpacing(double* iSpacings) const = 0;

		/**
		 * Set the geometry patch for a lattice 2d grid. The set geometry is an array 2d of lattice
		 * points3d.
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
		 * @param [in,out]	localCrs				   	(Optional) If non-null, the local crs.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setGeometryAsArray2dOfLatticePoints3d(
			unsigned int numPointsInFastestDirection, unsigned int numPointsInSlowestDirection,
			double xOrigin, double yOrigin, double zOrigin,
			double xOffsetInFastestDirection, double yOffsetInFastestDirection, double zOffsetInFastestDirection,
			double xOffsetInSlowestDirection, double yOffsetInSlowestDirection, double zOffsetInSlowestDirection,
			double spacingInFastestDirection, double spacingInSlowestDirection, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) = 0;

		/**
		 * Set the geometry patch for a lattice 2d grid. The set geometry is an array 2d of explicit Z
		 * based on an existing representation
		 *
		 * @param [in,out]	zValues						  	If non-null, the values.
		 * @param 		  	numI						  	Number of is.
		 * @param 		  	numJ						  	Number of js.
		 * @param [in,out]	proxy						  	If non-null, the proxy.
		 * @param [in,out]	supportingGrid2dRepresentation	If non-null, the supporting grid 2D
		 * 													representation.
		 * @param [in,out]	localCrs					  	(Optional) If non-null, the local crs.
		 * @param 		  	startIndexI					  	(Optional) The start index i.
		 * @param 		  	startIndexJ					  	(Optional) The start index j.
		 * @param 		  	indexIncrementI				  	(Optional) The index increment i.
		 * @param 		  	indexIncrementJ				  	(Optional) The index increment j.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setGeometryAsArray2dOfExplicitZ(
			double * zValues,
			unsigned int numI, unsigned int numJ, EML2_NS::AbstractHdfProxy* proxy,
			Grid2dRepresentation * supportingGrid2dRepresentation, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr,
			unsigned int startIndexI = 0, unsigned int startIndexJ = 0,
			int indexIncrementI = 1, int indexIncrementJ = 1) = 0;

		/**
		 * Set the geometry patch for a lattice 2d grid. The set geometry is an array 2d of explicit Z.
		 *
		 * @param [in,out]	zValues 	If non-null, the values.
		 * @param 		  	numI		Number of is.
		 * @param 		  	numJ		Number of js.
		 * @param [in,out]	proxy   	If non-null, the proxy.
		 * @param 		  	originX 	The origin x coordinate.
		 * @param 		  	originY 	The origin y coordinate.
		 * @param 		  	originZ 	The origin z coordinate.
		 * @param 		  	offsetIX	Zero-based index of the offset.
		 * @param 		  	offsetIY	The offset iy.
		 * @param 		  	offsetIZ	The offset iz.
		 * @param 		  	spacingI	The spacing i.
		 * @param 		  	offsetJX	The offset jx.
		 * @param 		  	offsetJY	The offset jy.
		 * @param 		  	offsetJZ	The offset jz.
		 * @param 		  	spacingJ	The spacing j.
		 * @param [in,out]	localCrs	(Optional) If non-null, the local crs.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setGeometryAsArray2dOfExplicitZ(
			double * zValues,
			unsigned int numI, unsigned int numJ, EML2_NS::AbstractHdfProxy* proxy,
			double originX, double originY, double originZ,
			double offsetIX, double offsetIY, double offsetIZ, double spacingI,
			double offsetJX, double offsetJY, double offsetJZ, double spacingJ, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) = 0;

		virtual COMMON_NS::DataObjectReference getSupportingRepresentationDor() const = 0;

		/**
		 * Get the supporting representation of this representation
		 *
		 * @returns	Null if it fails, else the supporting representation.
		 */
		DLL_IMPORT_OR_EXPORT Grid2dRepresentation* getSupportingRepresentation() const;

		/**
		 * Get the index of the origin of the current geometry on the supporting representation. The
		 * index is given by means of the formula iOrigin + jOrigin*iNodeCountOnSupportingRepresentation
		 *
		 * @returns	The index origin on supporting representation.
		 */
		DLL_IMPORT_OR_EXPORT virtual int getIndexOriginOnSupportingRepresentation() const = 0;

		/**
		* Get the index of the origin of the current geometry on a particular dimension of the supporting representation.
		*/
		DLL_IMPORT_OR_EXPORT virtual int getIndexOriginOnSupportingRepresentation(unsigned int dimension) const = 0;

		/**
		* Get the number of nodes of the current geometry which is extracted from a particular dimension of the supporting representation.
		*/
		DLL_IMPORT_OR_EXPORT virtual int getNodeCountOnSupportingRepresentation(unsigned int dimension) const = 0;

		/**
		* Get the index offset of the nodes of the current geometry on a particular dimension of the supporting representation.
		*/
		DLL_IMPORT_OR_EXPORT virtual int getIndexOffsetOnSupportingRepresentation(unsigned int dimension) const = 0;

		/**
		 * Gets patch count
		 *
		 * @returns	The patch count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const {return 1;}

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
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

	protected:
		
		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT Grid2dRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractSurfaceRepresentation(partialObject) {}

		/**
		 * Default constructor
		 */
		Grid2dRepresentation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		Grid2dRepresentation(gsoap_resqml2_0_1::_resqml20__Grid2dRepresentation* fromGsoap) : AbstractSurfaceRepresentation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		Grid2dRepresentation(gsoap_eml2_3::_resqml22__Grid2dRepresentation* fromGsoap) : AbstractSurfaceRepresentation(fromGsoap) {}

		/**
		 * Get a component of an XYZ structure.
		 *
		 * @param 	x				  	The x coordinate.
		 * @param 	y				  	The y coordinate.
		 * @param 	z				  	The z coordinate.
		 * @param 	componentIndex	  	The XYZ structure component index to get : 0 is X, 1 is Y and 2
		 * 								is Z.
		 * @param 	withoutTranslation	(Optional) Sometime we jsut wnat to apply rotation but not
		 * 								translation. For example, it is the case for offset which are XYZ
		 * 								"vectors" and not "XYZ" points.
		 *
		 * @returns	The component in global crs.
		 */
		double getComponentInGlobalCrs(double x, double y, double z, size_t componentIndex, bool withoutTranslation = false) const;

		/** Loads target relationships */
		void loadTargetRelationships();
	};
}