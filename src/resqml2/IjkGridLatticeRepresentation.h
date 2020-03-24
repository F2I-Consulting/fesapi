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
	class IjkGridLatticeRepresentation : public AbstractIjkGridRepresentation
	{
	public:
		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~IjkGridLatticeRepresentation() {}

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
		DLL_IMPORT_OR_EXPORT virtual double getXOrigin() const = 0;

		/**
		* Get the Y origin of this geometry.
		* Y coordinate is given in the local CRS.
		* @return double.NAN coordinate if something's wrong. The Y origin point otherwise.
		*/
		DLL_IMPORT_OR_EXPORT virtual double getYOrigin() const = 0;

	    /**
		* Get the Z origin of this geometry.
		* Z coordinate is given in the local CRS.
		* @return double.NAN coordinate if something's wrong. The Z origin point otherwise.
		*/
		DLL_IMPORT_OR_EXPORT virtual double getZOrigin() const = 0;

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
		DLL_IMPORT_OR_EXPORT virtual double getXIOffset() const = 0;

        /**
        * Get the Y i offset of this geometry.
        * Y coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Y offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT virtual double getYIOffset() const = 0;

		/**
        * Get the Z i offset of this geometry.
        * Z coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Z offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT virtual double getZIOffset() const = 0;

		/**
        * Get the X j offset of this geometry.
        * X coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The X offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT virtual double getXJOffset() const = 0;

        /**
        * Get the Y j offset of this geometry.
        * Y coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Y offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT virtual double getYJOffset() const = 0;

		/**
        * Get the Z j offset of this geometry.
        * Z coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Z offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT virtual double getZJOffset() const = 0;

		/**
        * Get the X k offset of this geometry.
        * X coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The X offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT virtual double getXKOffset() const = 0;

        /**
        * Get the Y k offset of this geometry.
        * Y coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Y offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT virtual double getYKOffset() const = 0;

		/**
        * Get the Z k offset of this geometry.
        * Z coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Z offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT virtual double getZKOffset() const = 0;

		/**
        * Get the I spacing of the regular (seismic) grid
        * @return double.NAN if something's wrong. The I spacing otherwise.
        */
		DLL_IMPORT_OR_EXPORT virtual double getISpacing() const = 0;

        /**
        * Get the J spacing of the regular (seismic) grid
        * @return double.NAN if something's wrong. The J spacing otherwise.
        */
		DLL_IMPORT_OR_EXPORT virtual double getJSpacing() const = 0;

		/**
        * Get the K spacing of the regular (seismic) grid
        * @return double.NAN if something's wrong. The K spacing otherwise.
        */
		DLL_IMPORT_OR_EXPORT virtual double getKSpacing() const = 0;

		/**
        * Get the label of the first inline.
        */
		DLL_IMPORT_OR_EXPORT virtual int getOriginInline() const = 0;

		/**
        * Get the label of the first crossline.
        */
		DLL_IMPORT_OR_EXPORT virtual int getOriginCrossline() const = 0;

		/**
        * Get the inline I offset value.
        */
		DLL_IMPORT_OR_EXPORT virtual int getInlineIOffset() const = 0;

		/**
        * Get the inline J offset value.
        */
		DLL_IMPORT_OR_EXPORT virtual int getInlineJOffset() const = 0;

		/**
        * Get the inline K offset value.
        */
		DLL_IMPORT_OR_EXPORT virtual int getInlineKOffset() const = 0;

		/**
        * Get the crossline I offset value.
        */
		DLL_IMPORT_OR_EXPORT virtual int getCrosslineIOffset() const = 0;

		/**
        * Get the crossline J offset value.
        */
		DLL_IMPORT_OR_EXPORT virtual int getCrosslineJOffset() const = 0;

		/**
        * Get the crossline K offset value.
        */
		DLL_IMPORT_OR_EXPORT virtual int getCrosslineKOffset() const = 0;

		/**
		* Set the geometry of the IJK grid as a regular IJK grid
		*/
		DLL_IMPORT_OR_EXPORT virtual void setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry,
			gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind,
			bool isRightHanded,
			double originX, double originY, double originZ,
			double directionIX, double directionIY, double directionIZ, double spacingI,
			double directionJX, double directionJY, double directionJZ, double spacingJ,
			double directionKX, double directionKY, double directionKZ, double spacingK, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) = 0;

		/**
		* Push back a patch of seismic 3D coordinates info.
		* The index this patch will be located must be consistent with the index of the geometry patch it is related to.
		*/
		DLL_IMPORT_OR_EXPORT virtual void addSeismic3dCoordinatesToPatch(
			unsigned int patchIndex,
			double startInline, double incrInline, unsigned int countInline,
			double startCrossline, double incrCrossline, unsigned int countCrossline,
			unsigned int countSample, RESQML2_NS::AbstractRepresentation * seismicSupport) = 0;

		DLL_IMPORT_OR_EXPORT geometryKind getGeometryKind() const;

	protected:
		IjkGridLatticeRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount) :
			AbstractIjkGridRepresentation(repo, guid, title, iCount, jCount, kCount) {}

		IjkGridLatticeRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount) :
			AbstractIjkGridRepresentation(interp, guid, title, iCount, jCount, kCount) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		IjkGridLatticeRepresentation(gsoap_resqml2_0_1::_resqml20__IjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
		IjkGridLatticeRepresentation(gsoap_eml2_3::_resqml22__IjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
		IjkGridLatticeRepresentation(gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
		IjkGridLatticeRepresentation(gsoap_eml2_3::_resqml22__TruncatedIjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
	};
}
