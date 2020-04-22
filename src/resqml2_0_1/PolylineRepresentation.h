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

#include "../resqml2/PolylineRepresentation.h"

/** @brief */
namespace RESQML2_0_1_NS
{
	/** A polyline representation. */
	class PolylineRepresentation final : public RESQML2_NS::PolylineRepresentation
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT PolylineRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::PolylineRepresentation(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	interp  	The interpretation which this representation represents.
		 * @param 		  	guid		The guid to set to the new instance. If empty then a new guid
		 * 								will be generated.
		 * @param 		  	title   	A title for the instance to create.
		 * @param 		  	roleKind	Indicates the role of this representation.
		 * @param 		  	isClosed	(Optional) Indicates wether this line representaiton is closed or
		 * 								not.
		 */
		PolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, gsoap_eml2_3::resqml22__LineRole roleKind,
			bool isClosed = false);

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	repo		If non-null, the repo.
		 * @param 		  	guid		The guid to set to the new instance. If empty then a new guid
		 * 								will be generated.
		 * @param 		  	title   	A title for the instance to create.
		 * @param 		  	isClosed	(Optional) Indicates wether this line representaiton is closed or
		 * 								not.
		 */
		PolylineRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title, bool isClosed = false);

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	interp  	The interpretation which this representation represents.
		 * @param 		  	guid		The guid to set to the new instance. If empty then a new guid
		 * 								will be generated.
		 * @param 		  	title   	A title for the instance to create.
		 * @param 		  	isClosed	(Optional) Indicates wether this line representaiton is closed or
		 * 								not.
		 */
		PolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, bool isClosed = false);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PolylineRepresentation(gsoap_resqml2_0_1::_resqml20__PolylineRepresentation* fromGsoap) : RESQML2_NS::PolylineRepresentation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~PolylineRepresentation() {}

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		/**
		 * Get the xyz point count in a given patch.
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	The xyz point count of patch.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(unsigned int patchIndex) const final;

		/**
		 * Get all the XYZ points of a particular patch of this representation. XYZ points are given in
		 * the local CRS.
		 *
		 * @param 		  	patchIndex	Zero-based index of the patch.
		 * @param [in,out]	xyzPoints 	A linearized 2d array where the first (quickest) dimension is
		 * 								coordinate dimension (XYZ) and second dimension is vertex
		 * 								dimension. It must be pre allocated.
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const final;

		/**
		 * Sets a geometry
		 *
		 * @param [in,out]	points	  	The points which constitute the polyline. Ordered by XYZ and then
		 * 								points.
		 * @param 		  	pointCount	The count of points in the polyline. Must be three times the
		 * 								count of the array of doubles "points".
		 * @param [in,out]	proxy	  	(Optional) The HDf proxy defining the HDF file where the double
		 * 								array will be stored.
		 * @param [in,out]	localCrs  	(Optional) If non-null, the local crs.
		 */
		DLL_IMPORT_OR_EXPORT void setGeometry(double const* points, unsigned int pointCount, EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) final;

		/**
		 * Indicates if the representaiton is a closed polyline or a non closed polyline.
		 *
		 * @returns	True if closed, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isClosed() const final;

		/**
		 * Indicates if the polyline is associated to a particular LineRole.
		 *
		 * @returns	True if a line role, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasALineRole() const final;

		/**
		 * Get the role of this polyline. Throw an exception if the polyline has no role (see method
		 * hasALineRole).
		 *
		 * @returns	The line role.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::resqml22__LineRole getLineRole() const final;

		/**
		 * Set the line role of this instance
		 *
		 * @param 	lineRole	The line role.
		 */
		DLL_IMPORT_OR_EXPORT void setLineRole(gsoap_eml2_3::resqml22__LineRole lineRole) final;

	private:
		gsoap_resqml2_0_1::resqml20__PointGeometry* getPointGeometry2_0_1(unsigned int patchIndex) const final;

		/**
		 * Initializes this object
		 *
		 * @param [in,out]	repo		If non-null, the repo.
		 * @param 		  	guid		Unique identifier.
		 * @param 		  	title   	The title.
		 * @param 		  	isClosed	(Optional) True if is closed, false if not.
		 */
		void init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title, bool isClosed = false);
	};
}
