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

namespace RESQML2_0_1_NS
{
	class IjkGridLatticeRepresentation : public AbstractIjkGridRepresentation
	{
	private :
		gsoap_resqml2_0_1::resqml20__Point3dLatticeArray* getArrayLatticeOfPoints3d() const;
	public:

		IjkGridLatticeRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		IjkGridLatticeRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
				const std::string & guid, const std::string & title,
				unsigned int iCount, unsigned int jCount, unsigned int kCount);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		IjkGridLatticeRepresentation(gsoap_resqml2_0_1::_resqml20__IjkGridRepresentation* fromGsoap): AbstractIjkGridRepresentation(fromGsoap) {}
		IjkGridLatticeRepresentation(gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~IjkGridLatticeRepresentation() {}

		/**
		* Indicates wether the instance corresponds to a seismic cube or not.
		*/
		DLL_IMPORT_OR_EXPORT bool isASeismicCube() const;

		/**
		* Indicates wether the instance corresponds to a facies cube or not.
		*/
		DLL_IMPORT_OR_EXPORT bool isAFaciesCube() const;

		/**
		* Get the xyz point count in a given patch.
		*/
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		* Get the X origin of this geometry.
		* X coordinate is given in the local CRS.
		* @return double.NAN coordinate if something's wrong. The X origin point otherwise.
		*/
		DLL_IMPORT_OR_EXPORT double getXOrigin() const;

		/**
		* Get the Y origin of this geometry.
		* Y coordinate is given in the local CRS.
		* @return double.NAN coordinate if something's wrong. The Y origin point otherwise.
		*/
		DLL_IMPORT_OR_EXPORT double getYOrigin() const;

	    /**
		* Get the Z origin of this geometry.
		* Z coordinate is given in the local CRS.
		* @return double.NAN coordinate if something's wrong. The Z origin point otherwise.
		*/
		DLL_IMPORT_OR_EXPORT double getZOrigin() const;

		/**
		* Get the X origin of this geometry.
		* X coordinate is given in the global CRS.
		* @return double.NAN coordinate if something's wrong. The X origin point otherwise.
		*/
		DLL_IMPORT_OR_EXPORT double getXOriginInGlobalCrs() const;

		/**
		* Get the Y origin of this geometry.
		* Y coordinate is given in the global CRS.
		* @return double.NAN coordinate if something's wrong. The Y origin point otherwise.
		*/
		DLL_IMPORT_OR_EXPORT double getYOriginInGlobalCrs() const;

		/**
		* Get the Z origin of this geometry.
		* Z coordinate is given in the global CRS.
		* @return double.NAN coordinate if something's wrong. The Z origin point otherwise.
		*/
		DLL_IMPORT_OR_EXPORT double getZOriginInGlobalCrs() const;

		/*****************************************************
		* Notice that, in seismic context, I is the slowest axis, J is the intermediate axis and K is the fastest axis.
		* In reservoir grid, I is the fastest axis, J is the intermediate axis and K is slowest axis.
		* It should be improved in future Resqml versions.
		*****************************************************/

		/**
        * Get the X i offset of this geometry.
        * X coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The X offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getXIOffset() const;

        /**
        * Get the Y i offset of this geometry.
        * Y coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Y offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getYIOffset() const;

		/**
        * Get the Z i offset of this geometry.
        * Z coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Z offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getZIOffset() const;

		/**
        * Get the X j offset of this geometry.
        * X coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The X offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getXJOffset() const;

        /**
        * Get the Y j offset of this geometry.
        * Y coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Y offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getYJOffset() const;

		/**
        * Get the Z j offset of this geometry.
        * Z coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Z offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getZJOffset() const;

		/**
        * Get the X k offset of this geometry.
        * X coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The X offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getXKOffset() const;

        /**
        * Get the Y k offset of this geometry.
        * Y coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Y offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getYKOffset() const;

		/**
        * Get the Z k offset of this geometry.
        * Z coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Z offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getZKOffset() const;

		/**
        * Get the I spacing of the regular (seismic) grid
        * @return double.NAN if something's wrong. The I spacing otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getISpacing() const;

        /**
        * Get the J spacing of the regular (seismic) grid
        * @return double.NAN if something's wrong. The J spacing otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getJSpacing() const;

		/**
        * Get the K spacing of the regular (seismic) grid
        * @return double.NAN if something's wrong. The K spacing otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getKSpacing() const;

		/**
        * Get the label of the first inline.
        */
		DLL_IMPORT_OR_EXPORT int getOriginInline() const;

		/**
        * Get the label of the first crossline.
        */
		DLL_IMPORT_OR_EXPORT int getOriginCrossline() const;

		/**
        * Get the inline I offset value.
        */
		DLL_IMPORT_OR_EXPORT int getInlineIOffset() const;

		/**
        * Get the inline J offset value.
        */
		DLL_IMPORT_OR_EXPORT int getInlineJOffset() const;

		/**
        * Get the inline K offset value.
        */
		DLL_IMPORT_OR_EXPORT int getInlineKOffset() const;

		/**
        * Get the crossline I offset value.
        */
		DLL_IMPORT_OR_EXPORT int getCrosslineIOffset() const;

		/**
        * Get the crossline J offset value.
        */
		DLL_IMPORT_OR_EXPORT int getCrosslineJOffset() const;

		/**
        * Get the crossline K offset value.
        */
		DLL_IMPORT_OR_EXPORT int getCrosslineKOffset() const;

		/**
		* Set the geometry of the IJK grid as a regular IJK grid
		*/
		DLL_IMPORT_OR_EXPORT void setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry,
			gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind,
			bool isRightHanded,
			double originX, double originY, double originZ,
			double directionIX, double directionIY, double directionIZ, double spacingI,
			double directionJX, double directionJY, double directionJZ, double spacingJ,
			double directionKX, double directionKY, double directionKZ, double spacingK, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		/**
		* Push back a patch of seismic 3D coordinates info.
		* The index this patch will be located must be consistent with the index of the geometry patch it is related to.
		*/
		DLL_IMPORT_OR_EXPORT void addSeismic3dCoordinatesToPatch(
			unsigned int patchIndex,
			double startInline, double incrInline, unsigned int countInline,
			double startCrossline, double incrCrossline, unsigned int countCrossline,
			unsigned int countSample, RESQML2_NS::AbstractRepresentation * seismicSupport);

		gsoap_resqml2_0_1::eml20__DataObjectReference* getHdfProxyDor() const;

		DLL_IMPORT_OR_EXPORT geometryKind getGeometryKind() const;
	};
}
