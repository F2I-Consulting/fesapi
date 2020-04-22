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

#include "../resqml2/IjkGridLatticeRepresentation.h"

namespace RESQML2_2_NS
{
	/** @brief	An ijk grid lattice representation. This class cannot be inherited. */
	class IjkGridLatticeRepresentation final : public RESQML2_NS::IjkGridLatticeRepresentation
	{
	private :
		gsoap_eml2_3::resqml22__Point3dLatticeArray* getArrayLatticeOfPoints3d() const;
	public:

		IjkGridLatticeRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount) :
			RESQML2_NS::IjkGridLatticeRepresentation(repo, guid, title, iCount, jCount, kCount) {}

		IjkGridLatticeRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
				const std::string & guid, const std::string & title,
				unsigned int iCount, unsigned int jCount, unsigned int kCount) :
			RESQML2_NS::IjkGridLatticeRepresentation(interp, guid, title, iCount, jCount, kCount) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		IjkGridLatticeRepresentation(gsoap_eml2_3::_resqml22__IjkGridRepresentation* fromGsoap): RESQML2_NS::IjkGridLatticeRepresentation(fromGsoap) {}
		IjkGridLatticeRepresentation(gsoap_eml2_3::_resqml22__TruncatedIjkGridRepresentation* fromGsoap) : RESQML2_NS::IjkGridLatticeRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~IjkGridLatticeRepresentation() {}

		/**
		* Get the X origin of this geometry.
		* X coordinate is given in the local CRS.
		* @return double.NAN coordinate if something's wrong. The X origin point otherwise.
		*/
		DLL_IMPORT_OR_EXPORT double getXOrigin() const final;

		/**
		* Get the Y origin of this geometry.
		* Y coordinate is given in the local CRS.
		* @return double.NAN coordinate if something's wrong. The Y origin point otherwise.
		*/
		DLL_IMPORT_OR_EXPORT double getYOrigin() const final;

	    /**
		* Get the Z origin of this geometry.
		* Z coordinate is given in the local CRS.
		* @return double.NAN coordinate if something's wrong. The Z origin point otherwise.
		*/
		DLL_IMPORT_OR_EXPORT double getZOrigin() const final;

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
		DLL_IMPORT_OR_EXPORT double getXIOffset() const final;

        /**
        * Get the Y i offset of this geometry.
        * Y coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Y offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getYIOffset() const final;

		/**
        * Get the Z i offset of this geometry.
        * Z coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Z offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getZIOffset() const final;

		/**
        * Get the X j offset of this geometry.
        * X coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The X offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getXJOffset() const final;

        /**
        * Get the Y j offset of this geometry.
        * Y coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Y offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getYJOffset() const final;

		/**
        * Get the Z j offset of this geometry.
        * Z coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Z offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getZJOffset() const final;

		/**
        * Get the X k offset of this geometry.
        * X coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The X offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getXKOffset() const final;

        /**
        * Get the Y k offset of this geometry.
        * Y coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Y offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getYKOffset() const final;

		/**
        * Get the Z k offset of this geometry.
        * Z coordinate is given in the local CRS.
        * @return double.NAN coordinate if something's wrong. The Z offset point otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getZKOffset() const final;

		/**
        * Get the I spacing of the regular (seismic) grid
        * @return double.NAN if something's wrong. The I spacing otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getISpacing() const final;

        /**
        * Get the J spacing of the regular (seismic) grid
        * @return double.NAN if something's wrong. The J spacing otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getJSpacing() const final;

		/**
        * Get the K spacing of the regular (seismic) grid
        * @return double.NAN if something's wrong. The K spacing otherwise.
        */
		DLL_IMPORT_OR_EXPORT double getKSpacing() const final;

		/**
        * Get the label of the first inline.
        */
		DLL_IMPORT_OR_EXPORT int getOriginInline() const final;

		/**
        * Get the label of the first crossline.
        */
		DLL_IMPORT_OR_EXPORT int getOriginCrossline() const final;

		/**
        * Get the inline I offset value.
        */
		DLL_IMPORT_OR_EXPORT int getInlineIOffset() const final;

		/**
        * Get the inline J offset value.
        */
		DLL_IMPORT_OR_EXPORT int getInlineJOffset() const final;

		/**
        * Get the inline K offset value.
        */
		DLL_IMPORT_OR_EXPORT int getInlineKOffset() const final;

		/**
        * Get the crossline I offset value.
        */
		DLL_IMPORT_OR_EXPORT int getCrosslineIOffset() const final;

		/**
        * Get the crossline J offset value.
        */
		DLL_IMPORT_OR_EXPORT int getCrosslineJOffset() const final;

		/**
        * Get the crossline K offset value.
        */
		DLL_IMPORT_OR_EXPORT int getCrosslineKOffset() const final;

		/**
		* Set the geometry of the IJK grid as a regular IJK grid
		*/
		DLL_IMPORT_OR_EXPORT void setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry,
			gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind,
			bool isRightHanded,
			double originX, double originY, double originZ,
			double directionIX, double directionIY, double directionIZ, double spacingI,
			double directionJX, double directionJY, double directionJZ, double spacingJ,
			double directionKX, double directionKY, double directionKZ, double spacingK, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) final;

		/**
		* Push back a patch of seismic 3D coordinates info.
		* The index this patch will be located must be consistent with the index of the geometry patch it is related to.
		*/
		DLL_IMPORT_OR_EXPORT void addSeismic3dCoordinatesToPatch(
			unsigned int patchIndex,
			double startInline, double incrInline, unsigned int countInline,
			double startCrossline, double incrCrossline, unsigned int countCrossline,
			unsigned int countSample, RESQML2_NS::AbstractRepresentation * seismicSupport) final;

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;
	};
}
