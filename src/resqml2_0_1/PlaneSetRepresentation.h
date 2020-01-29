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

#include "../resqml2/AbstractRepresentation.h"

/** . */
namespace RESQML2_0_1_NS
{
	/** A plane set representation. */
	class PlaneSetRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT PlaneSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractRepresentation(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	interp	The interpretation this representation represents.
		 * @param 		  	guid  	The guid to set to the new instance. If empty then a new guid will be
		 * 							generated.
		 * @param 		  	title 	A title for the instance to create.
		 */
		PlaneSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
				const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PlaneSetRepresentation(gsoap_resqml2_0_1::_resqml20__PlaneSetRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~PlaneSetRepresentation() {}

		/**
		 * Gets hdf proxy dor
		 *
		 * @returns	Null if it fails, else the hdf proxy dor.
		 */
		gsoap_resqml2_0_1::eml20__DataObjectReference* getHdfProxyDor() const { return nullptr; }

		/**
		 * Get the Local 3d CRS dor where the reference point ordinals are given It assumes there is
		 * only one CRS used by this instance.
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	Null if it fails, else the local crs dor.
		 */
		gsoap_resqml2_0_1::eml20__DataObjectReference* getLocalCrsDor(unsigned int patchIndex) const;

		/**
		 * Get the xyz point count in a given patch.
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	The xyz point count of patch.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		 * Get all the XYZ points of a particular patch of this representation. XYZ points are given in
		 * the local CRS.
		 *
		 * @param 		  	patchIndex	Zero-based index of the patch.
		 * @param [in,out]	xyzPoints 	A linearized 2d array where the first (quickest) dimension is
		 * 								coordinate dimension (XYZ) and second dimension is vertex
		 * 								dimension. It must be pre allocated.
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		 * Get the number of triangle patch
		 *
		 * @returns	The patch count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const;

		/**
		 * Push back a new patch which is an horizontal plane
		 *
		 * @param 		  	zCoordinate	The Z coordinate of the horizontal plane.
		 * @param [in,out]	localCrs   	(Optional) If non-null, the local crs.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackHorizontalPlaneGeometryPatch(double zCoordinate, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr);

		/**
		 * Push back a new patch which is not a horizontal plane. It s geometry is given by means of 3
		 * XYZ points.
		 *
		 * @param 		  	x1			The first x value.
		 * @param 		  	y1			The first y value.
		 * @param 		  	z1			The first z value.
		 * @param 		  	x2			The second x value.
		 * @param 		  	y2			The second y value.
		 * @param 		  	z2			The second z value.
		 * @param 		  	x3			The third double.
		 * @param 		  	y3			The third double.
		 * @param 		  	z3			The third double.
		 * @param [in,out]	localCrs	(Optional) If non-null, the local crs.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackTiltedPlaneGeometryPatch(
			double x1, double y1, double z1,
			double x2, double y2, double z2,
			double x3, double y3, double z3,
			RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr);

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
	};
}
