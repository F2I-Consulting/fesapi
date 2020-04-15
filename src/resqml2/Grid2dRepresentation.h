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
	/** A 2d grid representation. */
	class Grid2dRepresentation : public AbstractSurfaceRepresentation
	{
	public:
		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~Grid2dRepresentation() {}

		/**
		 * Gets the number of nodes along the I (fastest) axis of this 2d grid representation.
		 *
		 * @returns	The node count along the I (fastest) axis.
		 */
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getNodeCountAlongIAxis() const = 0;

		/**
		 * Gets the number of nodes along the J (slowest) axis of this 2d grid representation.
		 *
		 * @returns	The node count along the J (slowest) axis.
		 */
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getNodeCountAlongJAxis() const = 0;

		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(unsigned int patchIndex) const final;

		/** Please do note use: please compute x and y values with the lattice information. */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const final;

		/**
		 * Gets all the z values of this 2d grid representation. The z values are given in the local CRS.
		 *
		 * @exception	std::logic_error	If the z values cannot be get from this 2d grid
		 * 									representation.
		 *
		 * @param [out]	values	A preallocated array to receive the z values. Its size must be equal to
		 * 						getNodeCountAlongIAxis() @c * getNodeCountAlongJAxis() and it will not be
		 * 						freed by this method. The I dimension is the fastest.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getZValues(double * values) const = 0;

		/**
		 * Gets all the z values of this 2d grid representation. The z values are given in the global
		 * CRS.
		 *
		 * @exception	std::logic_error	If the z values cannot be get from this 2d grid
		 * 									representation.
		 *
		 * @param [out]	values	A preallocated array to receive the z values. Its size must be equal to
		 * 						getNodeCountAlongIAxis() @c * getNodeCountAlongJAxis() and it will not be
		 * 						freed by this method. The I dimension is the fastest.
		 */
		DLL_IMPORT_OR_EXPORT void getZValuesInGlobalCrs(double * values) const;

		/**
		 * Gets the x coordinate of the origin of this 2d grid representation. The x coordinate is given
		 * in the local CRS.
		 *
		 * @returns	NAN if the origin x coordinate cannot be get, the origin x coordinate otherwise.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getXOrigin() const = 0;

		/**
		 * Gets the y coordinate of the origin of this 2d grid representation. The y coordinate is given
		 * in the local CRS.
		 *
		 * @returns	NAN if the origin y coordinate cannot be get, the origin y coordinate otherwise.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getYOrigin() const = 0;

		/**
		 * Gets the z coordinate of the origin of this 2d grid representation. The z coordinate is given
		 * in the local CRS.
		 *
		 * @returns	NAN if the origin z coordinate cannot be get, the origin z coordinate otherwise.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getZOrigin() const = 0;

		/**
		 * Gets the x coordinate of the origin of this 2d grid representation. The x coordinate is given
		 * in the global CRS.
		 *
		 * @returns	NAN if the origin x coordinate cannot be get, the origin x coordinate otherwise.
		 */
		DLL_IMPORT_OR_EXPORT double getXOriginInGlobalCrs() const;

		/**
		 * Gets the y coordinate of the origin of this 2d grid representation. The y coordinate is given
		 * in the global CRS.
		 *
		 * @returns	NAN if the origin y coordinate cannot be get, the origin y coordinate otherwise.
		 */
		DLL_IMPORT_OR_EXPORT double getYOriginInGlobalCrs() const;

		/**
		 * Gets the z coordinate of the origin of this 2d grid representation. The z coordinate is given
		 * in the global CRS.
		 *
		 * @returns	NAN if the origin z coordinate cannot be get, the origin z coordinate otherwise.
		 */
		DLL_IMPORT_OR_EXPORT double getZOriginInGlobalCrs() const;

		/**
		 * Gets the x offset along the J (slowest) axis. If the J spacing is constant, the returned
		 * offset is exactly the offset between two consecutive nodes lying on the J axis. If not, the
		 * offset length does not have any meaning. The x coordinate is given in the local CRS.
		 *
		 * @exception	std::logic_error	If the x offset along the J axis cannot be get.
		 *
		 * @returns	The x offset along the J (slowest) axis.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getXJOffset() const = 0;

		/**
		 * Gets the y offset along the J (slowest) axis. If the J spacing is constant, the returned
		 * offset is exactly the offset between two consecutive nodes lying on the J axis. If not, the
		 * offset length does not have any meaning. The y coordinate is given in the local CRS.
		 *
		 * @exception	std::logic_error	If the y offset along the J axis cannot be get.
		 *
		 * @returns	The y offset along the J (slowest) axis.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getYJOffset() const = 0;

		/**
		 * Gets the z offset along the J (slowest) axis. If the J spacing is constant, the returned
		 * offset is exactly the offset between two consecutive nodes lying on the J axis. If not, the
		 * offset length does not have any meaning. The z coordinate is given in the local CRS.
		 *
		 * @exception	std::logic_error	If the z offset along the J axis cannot be get.
		 *
		 * @returns	The z offset along the J (slowest) axis.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getZJOffset() const = 0;

		/**
		 * Gets the x offset along the J (slowest) axis. If the J spacing is constant, the returned
		 * offset is exactly the offset between two consecutive nodes lying on the J axis. If not, the
		 * offset length does not have any meaning. The x coordinate is given in the global CRS.
		 *
		 * @exception	std::logic_error	If the x offset along the J axis cannot be get.
		 *
		 * @returns	The x offset along the J (slowest) axis.
		 */
		DLL_IMPORT_OR_EXPORT double getXJOffsetInGlobalCrs() const;

		/**
		 * Gets the y offset along the J (slowest) axis. If the J spacing is constant, the returned
		 * offset is exactly the offset between two consecutive nodes lying on the J axis. If not, the
		 * offset length does not have any meaning. The y coordinate is given in the global CRS.
		 *
		 * @exception	std::logic_error	If the y offset along the J axis cannot be get.
		 *
		 * @returns	The y offset along the J (slowest) axis.
		 */
		DLL_IMPORT_OR_EXPORT double getYJOffsetInGlobalCrs() const;

		/**
		 * Gets the z offset along the J (slowest) axis. If the J spacing is constant, the returned
		 * offset is exactly the offset between two consecutive nodes lying on the J axis. If not, the
		 * offset length does not have any meaning. The z coordinate is given in the global CRS.
		 *
		 * @exception	std::logic_error	If the z offset along the J axis cannot be get.
		 *
		 * @returns	The z offset along the J (slowest) axis.
		 */
		DLL_IMPORT_OR_EXPORT double getZJOffsetInGlobalCrs() const;

		/**
		 * Gets the x offset along the I (fastest) axis. If the J spacing is constant, the returned
		 * offset is exactly the offset between two consecutive nodes lying on the J axis. If not, the
		 * offset length does not have any meaning. The x coordinate is given in the local CRS.
		 *
		 * @exception	std::logic_error	If the x offset along the I axis cannot be get.
		 *
		 * @returns	The x offset along the I (fastest) axis.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getXIOffset() const = 0;

		/**
		 * Gets the y offset along the I (fastest) axis. If the J spacing is constant, the returned
		 * offset is exactly the offset between two consecutive nodes lying on the J axis. If not, the
		 * offset length does not have any meaning. The y coordinate is given in the local CRS.
		 *
		 * @exception	std::logic_error	If the y offset along the I axis cannot be get.
		 *
		 * @returns	The y offset along the I (fastest) axis.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getYIOffset() const = 0;

		/**
		 * Gets the z offset along the I (fastest) axis. If the J spacing is constant, the returned
		 * offset is exactly the offset between two consecutive nodes lying on the J axis. If not, the
		 * offset length does not have any meaning. The z coordinate is given in the local CRS.
		 *
		 * @exception	std::logic_error	If the z offset along the I axis cannot be get.
		 *
		 * @returns	The z offset along the I (fastest) axis.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getZIOffset() const = 0;

		/**
		 * Gets the x offset along the I (fastest) axis. If the J spacing is constant, the returned
		 * offset is exactly the offset between two consecutive nodes lying on the J axis. If not, the
		 * offset length does not have any meaning. The x coordinate is given in the global CRS.
		 *
		 * @exception	std::logic_error	If the x offset along the I axis cannot be get.
		 *
		 * @returns	The x offset along the I (fastest) axis.
		 */
		DLL_IMPORT_OR_EXPORT double getXIOffsetInGlobalCrs() const;

		/**
		 * Gets the y offset along the I (fastest) axis. If the J spacing is constant, the returned
		 * offset is exactly the offset between two consecutive nodes lying on the J axis. If not, the
		 * offset length does not have any meaning. The y coordinate is given in the global CRS.
		 *
		 * @exception	std::logic_error	If the y offset along the I axis cannot be get.
		 *
		 * @returns	The y offset along the I (fastest) axis.
		 */
		DLL_IMPORT_OR_EXPORT double getYIOffsetInGlobalCrs() const;

		/**
		 * Gets the z offset along the I (fastest) axis. If the J spacing is constant, the returned
		 * offset is exactly the offset between two consecutive nodes lying on the J axis. If not, the
		 * offset length does not have any meaning. The z coordinate is given in the global CRS.
		 *
		 * @exception	std::logic_error	If the z offset along the I axis cannot be get.
		 *
		 * @returns	The z offset along the I (fastest) axis.
		 */
		DLL_IMPORT_OR_EXPORT double getZIOffsetInGlobalCrs() const;

		/**
		 * Checks whether the spacing between nodes on J (slowest) dimension is constant or not.
		 *
		 * @exception	std::logic_error	If the J spacing cannot be get.
		 *
		 * @returns	True if the J (slowest) spacing is constant, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isJSpacingConstant() const = 0;

		/**
		 * Checks whether the spacing between nodes on I (fastest) dimension is constant or not.
		 *
		 * @exception	std::logic_error	If the J spacing cannot be get.
		 *
		 * @returns	True if the J (fastest) spacing is constant, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isISpacingConstant() const = 0;

		/**
		 * Gets the constant J (slowest) spacing of this 2d grid representation.
		 *
		 * @exception	std::logic_error	If the J spacing is not constant or cannot be get.
		 *
		 * @returns	The constant J (slowest) spacing of this 2d grid representation.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getJSpacing() const = 0;

		/**
		 * Gets all the J (slowest) spacings of this 2d grid representation.
		 *
		 * @exception	std::logic_error	If the HDF proxy is missing of if the J spacings cannot be
		 * 									get.
		 *
		 * @param [out]	jSpacings	A preallocated array to receive the J spacings. The count of this
		 * 							array must be getNodeCountAlongJAxis() <tt>- 1</tt> and it will not
		 * 							be freed by this method.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getJSpacing(double* jSpacings) const = 0;

		/**
		 * Gets the constant I (fastest) spacing of this 2d grid representation.
		 *
		 * @exception	std::logic_error	If the I spacing is not constant or cannot be get.
		 *
		 * @returns	The constant I (fastest) spacing of this 2d grid representation.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getISpacing() const = 0;

		/**
		 * Gets all the I (fastest) spacings of this 2d grid representation.
		 *
		 * @exception	std::logic_error	If the HDF proxy is missing of if the I spacings cannot be
		 * 									get.
		 *
		 * @param [out]	iSpacings	A preallocated array to receive the I spacings. The count of this
		 * 							array must be getNodeCountAlongJAxis() <tt>- 1</tt> and it will not
		 * 							be freed by this method.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getISpacing(double* iSpacings) const = 0;

		/**
		 * Sets the geometry of this 2d grid representation. The set geometry is a 2d array of 3d
		 * lattice points.
		 *
		 * @exception	std::invalid_argument	If <tt>localCrs == nullptr</tt> and no default CRS is
		 * 										defined in the repository.
		 *
		 * @param 	  	numPointsInFastestDirection	The number of points in the fastest direction.
		 * @param 	  	numPointsInSlowestDirection	The number of points in the slowest direction.
		 * @param 	  	xOrigin					   	The origin x coordinate.
		 * @param 	  	yOrigin					   	The origin y coordinate.
		 * @param 	  	zOrigin					   	The origin z coordinate.
		 * @param 	  	xOffsetInFastestDirection  	The x offset in the fastest direction.
		 * @param 	  	yOffsetInFastestDirection  	The y offset in the fastest direction.
		 * @param 	  	zOffsetInFastestDirection  	The z offset in the fastest direction.
		 * @param 	  	xOffsetInSlowestDirection  	The x offset in the slowest direction.
		 * @param 	  	yOffsetInSlowestDirection  	The y offset in the slowest direction.
		 * @param 	  	zOffsetInSlowestDirection  	The z offset in the slowest direction.
		 * @param 	  	spacingInFastestDirection  	The spacing in the fastest direction.
		 * @param 	  	spacingInSlowestDirection  	The spacing in the slowest direction.
		 * @param [in]	localCrs				   	(Optional) If non-null, the local CRS. If @c nullptr
		 * 											(default), the repository default CRS will be used.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setGeometryAsArray2dOfLatticePoints3d(
			unsigned int numPointsInFastestDirection, unsigned int numPointsInSlowestDirection,
			double xOrigin, double yOrigin, double zOrigin,
			double xOffsetInFastestDirection, double yOffsetInFastestDirection, double zOffsetInFastestDirection,
			double xOffsetInSlowestDirection, double yOffsetInSlowestDirection, double zOffsetInSlowestDirection,
			double spacingInFastestDirection, double spacingInSlowestDirection, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) = 0;

		/**
		 * Sets the geometry of this 2d grid representation. The set geometry is a 2d array of explicit
		 * z based on an existing representation.
		 *
		 * @exception	std::invalid_argument	If <tt>proxy == nullptr</tt> and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If <tt>supportingGrid2dRepresentation == nullptr</tt>.
		 * @exception	std::invalid_argument	If <tt>localCrs == nullptr</tt> and no default CRS is
		 * 										defined in the repository.
		 *
		 * @param [in]	  	zValues						  	An array of <tt>numI * numJ</tt> z values.
		 * @param 		  	numI						  	The number of points in the I (fastest)
		 * 													direction.
		 * @param 		  	numJ						  	The number of points in the J (slowest)
		 * 													direction.
		 * @param [in,out]	proxy						  	The HDF proxy where to store the z values. If
		 * 													@c nullptr, the repository default HDF proxy
		 * 													will be used.
		 * @param [in]	  	supportingGrid2dRepresentation	The supporting 2d grid representation.
		 * @param [in]	  	localCrs					  	(Optional) If non-null, the local CRS. If @c
		 * 													nullptr (default), the repository default CRS
		 * 													will be used.
		 * @param 		  	startIndexI					  	(Optional) The start index in the I (fastest)
		 * 													direction. Default value is @c 0.
		 * @param 		  	startIndexJ					  	(Optional) The start index in the J (slowest)
		 * 													direction. Default value is @c 0.
		 * @param 		  	indexIncrementI				  	(Optional) The index increment in the I
		 * 													(fastest) direction. Default value is @c 1.
		 * @param 		  	indexIncrementJ				  	(Optional) The index increment in the J
		 * 													(slowest) direction. Default value is @c 1.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setGeometryAsArray2dOfExplicitZ(
			double * zValues,
			unsigned int numI, unsigned int numJ, EML2_NS::AbstractHdfProxy* proxy,
			Grid2dRepresentation * supportingGrid2dRepresentation, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr,
			unsigned int startIndexI = 0, unsigned int startIndexJ = 0,
			int indexIncrementI = 1, int indexIncrementJ = 1) = 0;

		/**
		 * Sets the geometry of this 2d grid representation. The set geometry is a 2d array of explicit
		 * z.
		 *
		 * @exception	std::invalid_argument	If <tt>proxy == nullptr</tt> and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If <tt>localCrs == nullptr</tt> and no default CRS is
		 * 										defined in the repository.
		 *
		 * @param [in]	  	zValues 	An array of <tt>numI * numJ</tt> z values.
		 * @param 		  	numI		The number of points in the I (fastest)
		 * 								direction.
		 * @param 		  	numJ		The number of points in the J (slowest)
		 * 								direction.
		 * @param [in,out]	proxy   	The HDF proxy where to store the z values. If
		 * 								@c nullptr, the repository default HDF proxy
		 * 								will be used.
		 * @param 		  	originX 	The origin x coordinate.
		 * @param 		  	originY 	The origin y coordinate.
		 * @param 		  	originZ 	The origin z coordinate.
		 * @param 		  	offsetIX	The x offset in the I (fastest) direction.
		 * @param 		  	offsetIY	The y offset in the I (fastest) direction.
		 * @param 		  	offsetIZ	The z offset in the I (fastest) direction.
		 * @param 		  	spacingI	The spacing in the I (fastest) direction.
		 * @param 		  	offsetJX	The x offset in the J (slowest) direction.
		 * @param 		  	offsetJY	The y offset in the J (slowest) direction.
		 * @param 		  	offsetJZ	The z offset in the J (slowest) direction.
		 * @param 		  	spacingJ	The spacing in the J (slowest) direction.
		 * @param [in]	  	localCrs	(Optional) If non-null, the local CRS. If @c nullptr (default),
		 * 								the repository default CRS will be used.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setGeometryAsArray2dOfExplicitZ(
			double * zValues,
			unsigned int numI, unsigned int numJ, EML2_NS::AbstractHdfProxy* proxy,
			double originX, double originY, double originZ,
			double offsetIX, double offsetIY, double offsetIZ, double spacingI,
			double offsetJX, double offsetJY, double offsetJZ, double spacingJ, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) = 0;

		/**
		 * Gets the supporting representation data object reference.
		 *
		 * @returns	The supporting representation data object reference if there exists one, else empty
		 * 			data object reference.
		 */
		virtual COMMON_NS::DataObjectReference getSupportingRepresentationDor() const = 0;

		/**
		 * Gets the supporting representation of this 2d grid representation.
		 *
		 * @returns	The supporting representation if there exists one, else @c nullptr.
		 */
		DLL_IMPORT_OR_EXPORT Grid2dRepresentation* getSupportingRepresentation() const;

		/**
		 * Gets the index of the origin of the current geometry on the supporting representation. The
		 * index is given by means of the formula <tt>iOrigin + jOrigin *
		 * iNodeCountOnSupportingRepresentation</tt>
		 *
		 * @exception	std::logic_error	If no supporting representation is associated to this 2d grid
		 * 									representation.
		 *
		 * @returns	The index of the origin on the supporting representation.
		 */
		DLL_IMPORT_OR_EXPORT virtual int getIndexOriginOnSupportingRepresentation() const = 0;

		/**
		 * Gets the index of the origin of the current geometry on a particular dimension of the
		 * supporting representation.
		 *
		 * @exception	std::logic_error	 	If no supporting representation is associated to this 2d
		 * 										grid representation.
		 * @exception	std::invalid_argument	If @p dimension differs from @c 0 or @c 1.
		 *
		 * @param 	dimension	The dimension for which we look for the index of the origin. It can be @c
		 * 						0 for J (slowest) dimension or @c 1 for I (fastest) dimension.
		 *
		 * @returns	The index of the origin on the supporting representation on the dimension @p dimension.
		 */
		DLL_IMPORT_OR_EXPORT virtual int getIndexOriginOnSupportingRepresentation(unsigned int dimension) const = 0;

		/**
		 * Gets the number of nodes of the current geometry which is extracted from a particular
		 * dimension of the supporting representation.
		 *
		 * @exception	std::logic_error 	If no supporting representation is associated to this 2d grid
		 * 									representation.
		 * @exception	std::out_of_range	If @p dimension is out of range.
		 *
		 * @param 	dimension	The dimension for which we look for the number of nodes.
		 *
		 * @returns	The number of nodes on the dimension @p dimension.
		 */
		DLL_IMPORT_OR_EXPORT virtual int getNodeCountOnSupportingRepresentation(unsigned int dimension) const = 0;

		/**
		 * Get the index offset of the nodes of the current geometry on a particular dimension of the
		 * supporting representation.
		 *
		 * @exception	std::logic_error 	If no supporting representation is associated to this 2d grid
		 * 									representation.
		 * @exception	std::out_of_range	If @p dimension is out of range.
		 *
		 * @param 	dimension	The dimension for which we look for the index offset.
		 *
		 * @returns	The index offset on the dimension @p dimension.
		 */
		DLL_IMPORT_OR_EXPORT virtual int getIndexOffsetOnSupportingRepresentation(unsigned int dimension) const = 0;

		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const final {return 1;}

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const final { return XML_TAG; }

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
		void loadTargetRelationships() final;
	};
}
