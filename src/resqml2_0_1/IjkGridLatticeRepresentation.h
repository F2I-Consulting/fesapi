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

#include "resqml2_0_1/AbstractIjkGridRepresentation.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT IjkGridLatticeRepresentation : public AbstractIjkGridRepresentation
	{
	private :
		gsoap_resqml2_0_1::resqml2__Point3dLatticeArray* getArrayLatticeOfPoints3d() const;
	public:

		IjkGridLatticeRepresentation(soap* soapContext, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		IjkGridLatticeRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
				const std::string & guid, const std::string & title,
				const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		IjkGridLatticeRepresentation(gsoap_resqml2_0_1::_resqml2__IjkGridRepresentation* fromGsoap): AbstractIjkGridRepresentation(fromGsoap) {}
		IjkGridLatticeRepresentation(gsoap_resqml2_0_1::_resqml2__TruncatedIjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~IjkGridLatticeRepresentation() {}

		/**
		* Indicates wether the instance corresponds to a seismic cube or not.
		*/
		bool isASeismicCube() const;

		/**
		* Indicates wether the instance corresponds to a facies cube or not.
		*/
		bool isAFaciesCube() const;

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
		* Get the X origin of this geometry.
		* X coordinate is given in the local CRS.
		* @return double.NAN coordinate if something's wrong. The X origin point otherwise.
		*/
		double getXOrigin() const;

		/**
		* Get the Y origin of this geometry.
		* Y coordinate is given in the local CRS.
		* @return double.NAN coordinate if something's wrong. The Y origin point otherwise.
		*/
		double getYOrigin() const;

	    /**
		* Get the Z origin of this geometry.
		* Z coordinate is given in the local CRS.
		* @return double.NAN coordinate if something's wrong. The Z origin point otherwise.
		*/
		double getZOrigin() const;

		/**
		* Get the X origin of this geometry.
		* X coordinate is given in the global CRS.
		* @return double.NAN coordinate if something's wrong. The X origin point otherwise.
		*/
		double getXOriginInGlobalCrs() const;

		/**
		* Get the Y origin of this geometry.
		* Y coordinate is given in the global CRS.
		* @return double.NAN coordinate if something's wrong. The Y origin point otherwise.
		*/
		double getYOriginInGlobalCrs() const;

		/**
		* Get the Z origin of this geometry.
		* Z coordinate is given in the global CRS.
		* @return double.NAN coordinate if something's wrong. The Z origin point otherwise.
		*/
		double getZOriginInGlobalCrs() const;

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
        double getXIOffset() const;

        /**
        * Get the Y i offset of this geometry.
        * Y coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Y offset point otherwise.
        */
        double getYIOffset() const;

		/**
        * Get the Z i offset of this geometry.
        * Z coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Z offset point otherwise.
        */
        double getZIOffset() const;

		/**
        * Get the X j offset of this geometry.
        * X coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The X offset point otherwise.
        */
        double getXJOffset() const;

        /**
        * Get the Y j offset of this geometry.
        * Y coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Y offset point otherwise.
        */
        double getYJOffset() const;

		/**
        * Get the Z j offset of this geometry.
        * Z coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Z offset point otherwise.
        */
        double getZJOffset() const;

		/**
        * Get the X k offset of this geometry.
        * X coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The X offset point otherwise.
        */
        double getXKOffset() const;

        /**
        * Get the Y k offset of this geometry.
        * Y coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Y offset point otherwise.
        */
        double getYKOffset() const;

		/**
        * Get the Z k offset of this geometry.
        * Z coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Z offset point otherwise.
        */
        double getZKOffset() const;

		/**
        * Get the I spacing of the regular (seismic) grid
        * @return double.NAN if something's wrong. The I spacing otherwise.
        */
		double getISpacing() const;

        /**
        * Get the J spacing of the regular (seismic) grid
        * @return double.NAN if something's wrong. The J spacing otherwise.
        */
        double getJSpacing() const;

		/**
        * Get the K spacing of the regular (seismic) grid
        * @return double.NAN if something's wrong. The K spacing otherwise.
        */
        double getKSpacing() const;

		/**
        * Get the label of the first inline.
        */
        int getOriginInline() const;

		/**
        * Get the label of the first crossline.
        */
        int getOriginCrossline() const;

		/**
        * Get the inline I offset value.
        */
        int getInlineIOffset() const;

		/**
        * Get the inline J offset value.
        */
        int getInlineJOffset() const;

		/**
        * Get the inline K offset value.
        */
        int getInlineKOffset() const;

		/**
        * Get the crossline I offset value.
        */
        int getCrosslineIOffset() const;

		/**
        * Get the crossline J offset value.
        */
        int getCrosslineJOffset() const;

		/**
        * Get the crossline K offset value.
        */
        int getCrosslineKOffset() const;

		/**
		* Set the geometry of the IJK grid as a regular IJK grid
		*/
		void setGeometryAsCoordinateLineNodes(	const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry,
												const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind,
												const bool & isRightHanded,
												const double & originX, const double & originY, const double & originZ,
												const double & directionIX, const double & directionIY, const double & directionIZ, const double & spacingI,
												const double & directionJX, const double & directionJY, const double & directionJZ, const double & spacingJ,
												const double & directionKX, const double & directionKY, const double & directionKZ, const double & spacingK);

		/**
		* Push back a patch of seismic 3D coordinates info.
		* The index this patch will be located must be consistent with the index of the geometry patch it is related to.
		*/
		void addSeismic3dCoordinatesToPatch(
						const unsigned int patchIndex,
						const double & startInline, const double & incrInline, const unsigned int & countInline,
						const double & startCrossline, const double & incrCrossline, const unsigned int & countCrossline,
			            const unsigned int & countSample, AbstractRepresentation * seismicSupport);

		std::string getHdfProxyUuid() const;

		geometryKind getGeometryKind() const;
	};
}

