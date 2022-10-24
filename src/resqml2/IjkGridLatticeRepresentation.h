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

#include "AbstractIjkGridRepresentation.h"

namespace RESQML2_NS
{
	/**
	 * @brief	The main use case for this class is the representation of a seismic cubes.
	 *			I is the fastest axis and K is the slowest axis.
	 *			Notice that seismic domain will more likely use a vertical axis as the fastest one
	 *			where a reservori domain will more likely use a vertical axis as the fastest one.
	 */
	class IjkGridLatticeRepresentation : public AbstractIjkGridRepresentation
	{
	public:
		/**
		* Destructor does nothing since the memory is managed by the gSOAP context.
		*/
		virtual ~IjkGridLatticeRepresentation() = default;

		/**
		 * Indicates whether this instance corresponds to a seismic cube or not.
		 *
		 * @returns	True if it is a seismic cube, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isASeismicCube() const;

		/**
		 * Indicates whether this instance corresponds to a facies cube or not.
		 *
		 * @returns	True if it is a facies cube, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isAFaciesCube() const;

		/** Please do note use: not implemented yet. Please use lattice information. */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(uint64_t patchIndex, double* xyzPoints) const final;

		/**
		 * Gets the X coordinate of the origin of this geometry. The X coordinate is given in the local
		 * CRS.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The X coordinate of the origin point if successful, otherwise <tt>double.NAN</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getXOrigin() const = 0;

		/**
		 * Gets the Y coordinate of the origin of this geometry. The Y coordinate is given in the local
		 * CRS.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The Y coordinate of the origin point if successful, otherwise <tt>double.NAN</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getYOrigin() const = 0;

		/**
		 * Gets the Z coordinate of the origin of this geometry. The Z coordinate is given in the local
		 * CRS.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The Z coordinate of the origin point if successful, otherwise <tt>double.NAN</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getZOrigin() const = 0;

		/**
		 * Gets the X coordinate origin of this geometry. The X coordinate is given in the global CRS.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The X coordinate of the origin point if successful, otherwise <tt>double.NAN</tt>.
		 */
		DLL_IMPORT_OR_EXPORT double getXOriginInGlobalCrs() const;

		/**
		 * Gets the Y coordinate origin of this geometry. The Y coordinate is given in the global CRS.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The Y coordinate of the origin point if successful, otherwise <tt>double.NAN</tt>.
		 */
		DLL_IMPORT_OR_EXPORT double getYOriginInGlobalCrs() const;

		/**
		 * Gets the Z coordinate origin of this geometry. The Z coordinate is given in the global CRS.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The Z coordinate of the origin point if successful, otherwise <tt>double.NAN</tt>.
		 */
		DLL_IMPORT_OR_EXPORT double getZOriginInGlobalCrs() const;

		/**
		 * Gets the X coordinate of the I offset of this geometry. The X coordinate is given in the local CRS.
		 * I axis is fastest one in memory, whatever its direction is.
		 * K axis is fastest one in memory, whatever its direction is.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The X coordinate of the I offset if successful, otherwise <tt>double.NAN</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getXIOffset() const = 0;

		/**
		 * Gets the Y coordinate of the I offset of this geometry. The Y coordinate is given in the local CRS.
		 * I axis is fastest one in memory, whatever its direction is.
		 * K axis is fastest one in memory, whatever its direction is.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The Y coordinate of the I offset if successful, otherwise <tt>double.NAN</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getYIOffset() const = 0;

		/**
		 * Gets the Z coordinate of the I offset of this geometry. The Z coordinate is given in the local CRS.
		 * I axis is fastest one in memory, whatever its direction is.
		 * K axis is fastest one in memory, whatever its direction is.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The Z coordinate of the I offset if successful, otherwise <tt>double.NAN</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getZIOffset() const = 0;

		/**
		 * Gets the X coordinate of the J offset of this geometry. The X coordinate is given in the
		 * local CRS.
		 * I axis is fastest one in memory, whatever its direction is.
		 * K axis is fastest one in memory, whatever its direction is.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The X coordinate of the J offset if successful, otherwise <tt>double.NAN</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getXJOffset() const = 0;

		/**
		 * Gets the Y coordinate of the J offset of this geometry. The Y coordinate is given in the
		 * local CRS.
		 * I axis is fastest one in memory, whatever its direction is.
		 * K axis is fastest one in memory, whatever its direction is.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The Y coordinate of the J offset if successful, otherwise <tt>double.NAN</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getYJOffset() const = 0;

		/**
		 * Gets the Z coordinate of the J offset of this geometry. The Z coordinate is given in the
		 * local CRS.
		 * I axis is fastest one in memory, whatever its direction is.
		 * K axis is fastest one in memory, whatever its direction is.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The Z coordinate of the J offset if successful, otherwise <tt>double.NAN</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getZJOffset() const = 0;

		/**
		 * Gets the X coordinate of the K offset of this geometry. The X coordinate is given in the local CRS.
		 * I axis is fastest one in memory, whatever its direction is.
		 * K axis is fastest one in memory, whatever its direction is.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The X coordinate of the K offset if successful, otherwise <tt>double.NAN</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getXKOffset() const = 0;

		/**
		 * Gets the Y coordinate of the K offset of this geometry. The Y coordinate is given in the local CRS.
		 * I axis is fastest one in memory, whatever its direction is.
		 * K axis is fastest one in memory, whatever its direction is.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The Y coordinate of the K offset if successful, otherwise <tt>double.NAN</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getYKOffset() const = 0;

		/**
		 * Gets the Z coordinate of the K offset of this geometry. The Z coordinate is given in the local CRS.
		 * I axis is fastest one in memory, whatever its direction is.
		 * K axis is fastest one in memory, whatever its direction is.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The Z coordinate of the K offset if successful, otherwise <tt>double.NAN</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getZKOffset() const = 0;

		/**
		 * Gets the I spacing of this regular (seismic) grid.
		 * I axis is fastest one in memory, whatever its direction is.
		 * K axis is fastest one in memory, whatever its direction is.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The I spacing if successful, otherwise <tt>double.NAN</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getISpacing() const = 0;

		/**
		 * Gets the J spacing of this regular (seismic) grid.
		 * I axis is fastest one in memory, whatever its direction is.
		 * K axis is fastest one in memory, whatever its direction is.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The J spacing if successful, otherwise <tt>double.NAN</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getJSpacing() const = 0;

		/**
		 * Gets the K spacing of this regular (seismic) grid.
		 * I axis is fastest one in memory, whatever its direction is.
		 * K axis is fastest one in memory, whatever its direction is.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The K spacing if successful, otherwise <tt>double.NAN</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getKSpacing() const = 0;

		/**
		 * Gets the label of the first inline.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The label of the first inline if successful, otherwise 0.
		 */
		DLL_IMPORT_OR_EXPORT virtual int getOriginInline() const = 0;

		/**
		 * Gets the label of the first crossline.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The label of the first crossline if successful, otherwise 0.
		 */
		DLL_IMPORT_OR_EXPORT virtual int getOriginCrossline() const = 0;

		/**
		 * Gets the inline I offset value.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The inline I offset value if successful, otherwise 0.
		 */
		DLL_IMPORT_OR_EXPORT virtual int getInlineIOffset() const = 0;

		/**
		 * Gets the inline J offset value.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The inline J offset value if successful, otherwise 0.
		 */
		DLL_IMPORT_OR_EXPORT virtual int getInlineJOffset() const = 0;

		/**
		 * Gets the inline K offset value.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The inline K offset value if successful, otherwise 0.
		 */
		DLL_IMPORT_OR_EXPORT virtual int getInlineKOffset() const = 0;

		/**
		 * Gets the crossline I offset value.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The crossline I offset value if successful, otherwise 0.
		 */
		DLL_IMPORT_OR_EXPORT virtual int getCrosslineIOffset() const = 0;

		/**
		 * Gets the crossline J offset value.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The crossline J offset value if successful, otherwise 0.
		 */
		DLL_IMPORT_OR_EXPORT virtual int getCrosslineJOffset() const = 0;

		/**
		 * Gets the crossline K offset value.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The crossline K offset value if successful, otherwise 0.
		 */
		DLL_IMPORT_OR_EXPORT virtual int getCrosslineKOffset() const = 0;

		/**
		 * Sets the geometry of this IJK grid as a regular IJK grid.
		 * I axis is fastest one in memory, whatever its direction is.
		 * K axis is fastest one in memory, whatever its direction is.
		 *
		 * @exception	std::invalid_argument	If @p localCrs is @c nullptr and no default local 3d CRS
		 * 										is defined.
		 *
		 * @param 	  	mostComplexPillarGeometry	The most complex pillar shape which we can find on
		 * 											this IJK grid.
		 * @param 	  	kDirectionKind			 	The K direction kind.
		 * @param 	  	isRightHanded			 	Indicates that the IJK grid is right handed, as
		 * 											determined by the triple product of tangent vectors
		 * 											in the I, J, and K directions.
		 * @param 	  	originX					 	The X coordinate of the origin.
		 * @param 	  	originY					 	The Y coordinate of the origin.
		 * @param 	  	originZ					 	The Z coordinate of the origin.
		 * @param 	  	directionIX				 	The X coordinate of the I offset.
		 * @param 	  	directionIY				 	The Y coordinate of the I offset.
		 * @param 	  	directionIZ				 	The Z coordinate of the I offset.
		 * @param 	  	spacingI				 	The spacing in the I direction.
		 * @param 	  	directionJX				 	The X coordinate of the J offset.
		 * @param 	  	directionJY				 	The Y coordinate of the J offset.
		 * @param 	  	directionJZ				 	The Z coordinate of the J offset.
		 * @param 	  	spacingJ				 	The spacing in the J direction.
		 * @param 	  	directionKX				 	The X coordinate of the K offset.
		 * @param 	  	directionKY				 	The Y coordinate of the K offset.
		 * @param 	  	directionKZ				 	The Z coordinate of the K offset.
		 * @param 	  	spacingK				 	The spacing in the K direction.
		 * @param [in]	localCrs				 	(Optional) The local CRS where the points are given.
		 * 											If @c nullptr (default) then the default CRS of the
		 * 											repository will be used.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry,
			gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind,
			bool isRightHanded,
			double originX, double originY, double originZ,
			double directionIX, double directionIY, double directionIZ, double spacingI,
			double directionJX, double directionJY, double directionJZ, double spacingJ,
			double directionKX, double directionKY, double directionKZ, double spacingK, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr) = 0;

		/**
		 * Pushes back a patch of seismic 3D coordinates.
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::invalid_argument	If @p patchIndex does not identify a point geometry.
		 * @exception	std:invalid_argument 	If @p seismicSupport is nullptr.
		 * @exception	std::invalid_argument	If it already exists some seismic 2d coordinates for this
		 * 										patch.
		 *
		 * @param 	  	patchIndex	  	Zero-based index of the patch to push. It must be consistent with
		 * 								the index of the geometry patch it is related to.
		 * @param 	  	startInline   	The start inline.
		 * @param 	  	incrInline	  	The inline increment.
		 * @param 	  	countInline   	The count of inlines.
		 * @param 	  	startCrossline	The start crossline.
		 * @param 	  	incrCrossline 	The crossline increment.
		 * @param 	  	countCrossline	The count of crosslines.
		 * @param 	  	countSample   	The count of samples.
		 * @param [in]	seismicSupport	The seismic support of the patch to push.
		 */
		DLL_IMPORT_OR_EXPORT virtual void addSeismic3dCoordinatesToPatch(
			uint64_t patchIndex,
			double startInline, double incrInline, unsigned int countInline,
			double startCrossline, double incrCrossline, unsigned int countCrossline,
			unsigned int countSample, RESQML2_NS::AbstractRepresentation * seismicSupport) = 0;

		DLL_IMPORT_OR_EXPORT geometryKind getGeometryKind() const final;

	protected:
		IjkGridLatticeRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount) :
			AbstractIjkGridRepresentation(repo, guid, title, iCount, jCount, kCount, nullptr) {}

		IjkGridLatticeRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount) :
			AbstractIjkGridRepresentation(interp, guid, title, iCount, jCount, kCount, nullptr) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		IjkGridLatticeRepresentation(gsoap_resqml2_0_1::_resqml20__IjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
		IjkGridLatticeRepresentation(gsoap_eml2_3::_resqml22__IjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
		IjkGridLatticeRepresentation(gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
		IjkGridLatticeRepresentation(gsoap_eml2_3::_resqml22__TruncatedIjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
	};
}
