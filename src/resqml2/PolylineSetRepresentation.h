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

#include "AbstractRepresentation.h"

/** . */
namespace RESQML2_NS
{
	/** A polyline set representation. */
	class PolylineSetRepresentation : public AbstractRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~PolylineSetRepresentation() {}

		/**
		* Get the number of polylines in a given patch
		*/
		DLL_IMPORT_OR_EXPORT virtual unsigned int getPolylineCountOfPatch(unsigned int patchIndex) const = 0;
		DLL_IMPORT_OR_EXPORT virtual unsigned int getPolylineCountOfAllPatches() const = 0;

		/**
		 * Gets node count per polyline in patch
		 *
		 * @param 		  	patchIndex				Zero-based index of the patch.
		 * @param [in,out]	nodeCountPerPolyline	If non-null, the node count per polyline.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getNodeCountPerPolylineInPatch(unsigned int patchIndex, unsigned int * nodeCountPerPolyline) const = 0;

		/**
		 * Get all the node count par polyline for all teh aptches of the representation.
		 *
		 * @param [in,out]	NodeCountPerPolyline	It must be pre-allocated.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getNodeCountPerPolylineOfAllPatches(unsigned int * NodeCountPerPolyline) const = 0;

		/**
		 * Get the xyz point count in a given patch.
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	The xyz point count of patch.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(unsigned int patchIndex) const final;

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
		DLL_IMPORT_OR_EXPORT virtual void pushBackGeometryPatch(
			unsigned int const * nodeCountPerPolyline, double const * nodes,
			unsigned int polylineCount, bool allPolylinesClosedFlag,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) = 0;

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
		DLL_IMPORT_OR_EXPORT virtual void pushBackGeometryPatch(
			unsigned int const * nodeCountPerPolyline, double const * nodes,
			unsigned int polylineCount, bool * polylineClosedFlags,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) = 0;

		/**
		 * Check if all polylines contained in a single patch are closed or not. Notice that a returned
		 * "false" does not mean they are all not closed. Indeed they can be mixed i.e. some closed and
		 * some not.
		 *
		 * @param 	patchIndex	The index of the patch to check.
		 *
		 * @returns	True if all polylines of the studied patch are closed.
		 */
		DLL_IMPORT_OR_EXPORT bool virtual areAllPolylinesClosedOfPatch(unsigned int patchIndex) const = 0;

		/**
		 * Determine if we are all polylines closed of all patches
		 *
		 * @returns	True if all polylines closed of all patches, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool areAllPolylinesClosedOfAllPatches() const = 0;

		/**
		 * Check if all polylines contained in a single patch are closed or not. Notice that a returned
		 * "false" does not mean they are all closed. Indeed they can be mixed i.e. some closed and some
		 * not.
		 *
		 * @param 	patchIndex	The index of the patch to check.
		 *
		 * @returns	True if all polylines of the studied patch are not closed.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool areAllPolylinesNonClosedOfPatch(unsigned int patchIndex) const = 0;

		/**
		 * Determine if we are all polylines non closed of all patches
		 *
		 * @returns	True if all polylines non closed of all patches, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool areAllPolylinesNonClosedOfAllPatches() const = 0;

		/**
		 * Get all the node count par polyline for all teh aptches of the representation.
		 *
		 * @param 		  	patchIndex			 	It must be pre-allocated.
		 * @param [in,out]	closedFlagPerPolyline	If non-null, true to closed flag per polyline.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getClosedFlagPerPolylineOfPatch(unsigned int patchIndex, bool * closedFlagPerPolyline) const = 0;

		/**
		 * Gets closed flag per polyline of all patches
		 *
		 * @param [in,out]	closedFlagPerPolyline	If non-null, true to closed flag per polyline.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getClosedFlagPerPolylineOfAllPatches(bool * closedFlagPerPolyline) const = 0;

		/**
		 * Indicates if the polylineSet is associated to a particular LineRole.
		 *
		 * @returns	True if a line role, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool hasALineRole() const = 0;

		/**
		 * Get the role of this polylineSet. Throw an exception if the polylineSet has no role (see
		 * method hasALineRole).
		 *
		 * @returns	The line role.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_eml2_3::resqml22__LineRole getLineRole() const = 0;

		/**
		 * Set the line role of this instance
		 *
		 * @param 	lineRole	The line role.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setLineRole(gsoap_eml2_3::resqml22__LineRole lineRole) = 0;

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
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT PolylineSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractRepresentation(partialObject) {}

		/**
		 * Default constructor
		 */
		PolylineSetRepresentation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PolylineSetRepresentation(gsoap_resqml2_0_1::_resqml20__PolylineSetRepresentation* fromGsoap) : AbstractRepresentation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PolylineSetRepresentation(gsoap_eml2_3::_resqml22__PolylineSetRepresentation* fromGsoap) : AbstractRepresentation(fromGsoap) {}
	};
}
