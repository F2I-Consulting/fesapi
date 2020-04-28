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

#include "../resqml2/PolylineSetRepresentation.h"

namespace RESQML2_0_1_NS
{
	/** A polyline set representation. */
	class PolylineSetRepresentation final : public RESQML2_NS::PolylineSetRepresentation
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT PolylineSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::PolylineSetRepresentation(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	repo 	If non-null, the repo.
		 * @param 		  	guid 	The guid to set to the new instance. If empty then a new guid will be
		 * 							generated.
		 * @param 		  	title	A title for the instance to create.
		 */
		PolylineSetRepresentation(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The interpretation this representation represents.
		 * @param 	  	guid  	The guid to set to the new instance. If empty then a new guid will be
		 * 						generated.
		 * @param 	  	title 	A title for the instance to create.
		 */
		PolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 * @exception	std::invalid_argument	If @p roleKind is a break line role.
		 *
		 * @param [in]	interp  	The interpretation this representation represents.
		 * @param 	  	guid		The guid to set to the new instance. If empty then a new guid will be
		 * 							generated.
		 * @param 	  	title   	A title for the instance to create.
		 * @param 	  	roleKind	Indicates the role of this representation.
		 */
		PolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, gsoap_eml2_3::resqml22__LineRole roleKind);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PolylineSetRepresentation(gsoap_resqml2_0_1::_resqml20__PolylineSetRepresentation* fromGsoap) : RESQML2_NS::PolylineSetRepresentation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~PolylineSetRepresentation() {}

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		/**
		* Get the number of polylines in a given patch
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getPolylineCountOfPatch(unsigned int patchIndex) const final;
		DLL_IMPORT_OR_EXPORT unsigned int getPolylineCountOfAllPatches() const final;

		/**
		 * Gets node count per polyline in patch
		 *
		 * @param 		  	patchIndex				Zero-based index of the patch.
		 * @param [in,out]	nodeCountPerPolyline	If non-null, the node count per polyline.
		 */
		DLL_IMPORT_OR_EXPORT void getNodeCountPerPolylineInPatch(unsigned int patchIndex, unsigned int * nodeCountPerPolyline) const final;

		/**
		 * Get all the node count par polyline for all the patches of the representation.
		 *
		 * @param [in,out]	NodeCountPerPolyline	It must be pre-allocated.
		 */
		DLL_IMPORT_OR_EXPORT void getNodeCountPerPolylineOfAllPatches(unsigned int * NodeCountPerPolyline) const final;

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
		 * Get the number of triangle patch
		 *
		 * @returns	The patch count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const final;

		/**
		 * Push back a new patch of polylines
		 *
		 * @param [in,out]	nodeCountPerPolyline  	The node count per polyline in this patch. There must
		 * 											be polylineCount values in this array.
		 * @param [in,out]	nodes				  	The XYZ values of the nodes. Ordered by XYZ and then
		 * 											by NodeCount. It must be three times NodeCount.
		 * @param 		  	polylineCount		  	The polyline count in this patch.
		 * @param 		  	allPolylinesClosedFlag	Indicates the closed flags of all the polylines.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy which defines where the
		 * 											nodes and triangle indices will be stored.
		 * @param [in,out]	localCrs			  	(Optional) If non-null, the local crs.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackGeometryPatch(
			unsigned int const * nodeCountPerPolyline, double const * nodes,
			unsigned int polylineCount, bool allPolylinesClosedFlag,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) final;

		/**
		 * Push back a new patch of polylines
		 *
		 * @param [in,out]	nodeCountPerPolyline	The node count per polyline in this patch. There must
		 * 											be polylineCount values in this array.
		 * @param [in,out]	nodes					The XYZ values of the nodes. Ordered by XYZ and then
		 * 											by NodeCount. It must be three times NodeCount.
		 * @param 		  	polylineCount			The polyline count in this patch.
		 * @param [in,out]	polylineClosedFlags 	Indicates the closed flags for each of the polyline.
		 * 											The count of this array must be polylineCount.
		 * @param [in,out]	proxy					(Optional) The HDF proxy which defines where the
		 * 											nodes and triangle indices will be stored.
		 * @param [in,out]	localCrs				(Optional) If non-null, the local crs.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackGeometryPatch(
			unsigned int const * nodeCountPerPolyline, double const * nodes,
			unsigned int polylineCount, bool * polylineClosedFlags,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) final;

		/**
		 * Check if all polylines contained in a single patch are closed or not. Notice that a returned
		 * "false" does not mean they are all not closed. Indeed they can be mixed i.e. some closed and
		 * some not.
		 *
		 * @param 	patchIndex	The index of the patch to check.
		 *
		 * @returns	True if all polylines of the studied patch are closed.
		 */
		DLL_IMPORT_OR_EXPORT bool areAllPolylinesClosedOfPatch(unsigned int patchIndex) const final;

		/**
		 * Determine if we are all polylines closed of all patches
		 *
		 * @returns	True if all polylines closed of all patches, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool areAllPolylinesClosedOfAllPatches() const final;

		/**
		 * Check if all polylines contained in a single patch are closed or not. Notice that a returned
		 * "false" does not mean they are all closed. Indeed they can be mixed i.e. some closed and some
		 * not.
		 *
		 * @param 	patchIndex	The index of the patch to check.
		 *
		 * @returns	True if all polylines of the studied patch are not closed.
		 */
		DLL_IMPORT_OR_EXPORT bool areAllPolylinesNonClosedOfPatch(unsigned int patchIndex) const final;

		/**
		 * Determine if we are all polylines non closed of all patches
		 *
		 * @returns	True if all polylines non closed of all patches, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool areAllPolylinesNonClosedOfAllPatches() const final;

		/**
		 * Get all the node count par polyline for all teh aptches of the representation.
		 *
		 * @param 		  	patchIndex			 	It must be pre-allocated.
		 * @param [in,out]	closedFlagPerPolyline	If non-null, true to closed flag per polyline.
		 */
		DLL_IMPORT_OR_EXPORT void getClosedFlagPerPolylineOfPatch(unsigned int patchIndex, bool * closedFlagPerPolyline) const final;

		/**
		 * Gets closed flag per polyline of all patches
		 *
		 * @param [in,out]	closedFlagPerPolyline	If non-null, true to closed flag per polyline.
		 */
		DLL_IMPORT_OR_EXPORT void getClosedFlagPerPolylineOfAllPatches(bool * closedFlagPerPolyline) const final;

		/**
		 * Indicates if the polylineSet is associated to a particular LineRole.
		 *
		 * @returns	True if a line role, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasALineRole() const final;

		/**
		 * Get the role of this polylineSet. Throw an exception if the polylineSet has no role (see
		 * method hasALineRole).
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
		 * @param [in,out]	repo 	If non-null, the repo.
		 * @param 		  	guid 	Unique identifier.
		 * @param 		  	title	The title.
		 */
		void init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title);
	};
}
