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

namespace RESQML2_NS
{
	/**
	 * @brief	A representation made up of a set of polylines or a set of polygonal chains (for more
	 * 			information, see PolylineRepresentation).
	 * 			
	 * 			For compactness, it is organized by line patch as a unique polyline set patch.
	 * 			
	 * 			A closed polyline is connected between the first and the last point.
	 */
	class PolylineSetRepresentation : public AbstractRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~PolylineSetRepresentation() {}

		/**
		 * Gets the number of polylines in a given patch.
		 *
		 * @exception	std::out_of_range	If <tt>patchIndex >=</tt> getPatchCount().
		 *
		 * @param 	patchIndex	Zero-based index of the patch for which we want to count the number of
		 * 						polylines.
		 *
		 * @returns	The polyline count of patch @p patchIndex.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getPolylineCountOfPatch(unsigned int patchIndex) const = 0;

		/**
		 * Gets the polyline count of all patches.
		 *
		 * @returns	The polyline count of all patches.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getPolylineCountOfAllPatches() const = 0;

		/**
		 * Gets the node count per polyline in a given patch.
		 *
		 * @exception	std::out_of_range	If <tt>patchIndex &gt;=</tt> getPatchCount().
		 *
		 * @param 	   	patchIndex				Zero-based index of the patch for which we want to count
		 * 										the nodes per polyline.
		 * @param [out]	nodeCountPerPolyline	A preallocated array to receive the node count per
		 * 										polyline. It is ordered by polyline in the patch @p
		 * 										patchIndex. Its size must be
		 * 										<tt>getPolylineCountOfPatch(patchIndex)</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getNodeCountPerPolylineInPatch(unsigned int patchIndex, unsigned int * nodeCountPerPolyline) const = 0;

		/**
		 * Gets all the node count per polyline for all the patches of this representation.
		 *
		 * @param [out]	NodeCountPerPolyline	A preallocated array to receive the node count per
		 * 										polyline per patch. It is ordered first by polyline and then
		 * 										by patch. Its size must be getPolylineCountOfAllPatches().
		 */
		DLL_IMPORT_OR_EXPORT virtual void getNodeCountPerPolylineOfAllPatches(unsigned int * NodeCountPerPolyline) const = 0;

		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(unsigned int patchIndex) const final;

		/**
		 * Pushes back a new patch of polylines. Here, the closed flag of all of the polylines is the
		 * same.
		 *
		 * @exception	std::invalid_argument	If <tt>proxy == nullptr</tt> and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If <tt>localCrs == nullptr</tt> and no default local CRS
		 * 										id defined in the repository.
		 *
		 * @param [in]	  	nodeCountPerPolyline  	The node count per polyline in this patch. It is
		 * 											ordered by polyline. There must be @p polylineCount
		 * 											values in this array.
		 * @param [in]	  	nodes				  	The xyz values of the nodes. Ordered by xyz, then by
		 * 											node and then by polyline. It must be three times the
		 * 											total count of nodes.
		 * @param 		  	polylineCount		  	The polyline count in this patch.
		 * @param 		  	allPolylinesClosedFlag	Indicates the closed flags of all the polylines.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy which defines where the
		 * 											nodes will be stored. If @c nullptr (default), then
		 * 											the repository default HDF proxy will be used.
		 * @param [in]	  	localCrs			  	(Optional) The local CRS where the points are
		 * 											defined. If @c nullptr (default value), then the
		 * 											repository default local CRS will be used.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackGeometryPatch(
			unsigned int const * nodeCountPerPolyline, double const * nodes,
			unsigned int polylineCount, bool allPolylinesClosedFlag,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) = 0;

		/**
		 * Pushes back a new patch of polylines.
		 *
		 * @exception	std::invalid_argument	If <tt>proxy == nullptr</tt> and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If <tt>localCrs == nullptr</tt> and no default local CRS
		 * 										id defined in the repository.
		 *
		 * @param [in]	  	nodeCountPerPolyline	The node count per polyline in this patch. It is
		 * 											ordered by polyline. There must be @p polylineCount
		 * 											values in this array.
		 * @param [in]	  	nodes					The xyz values of the nodes. Ordered by xyz, then by
		 * 											node and then by polyline. It must be three times the
		 * 											total count of nodes.
		 * @param 		  	polylineCount			The polyline count in this patch.
		 * @param [in]	  	polylineClosedFlags 	Indicates the closed flags for each of the polyline.
		 * 											The count of this array must be @p polylineCount.
		 * @param [in,out]	proxy					(Optional) The HDF proxy which defines where the
		 * 											nodes will be stored. If @c nullptr (default), then the
		 * 											repository default HDF proxy will be used.
		 * @param [in]	  	localCrs				(Optional) The local CRS where the points are
		 * 											defined. If @c nullptr (default value), then the
		 * 											repository default local CRS will be used.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackGeometryPatch(
			unsigned int const * nodeCountPerPolyline, double const * nodes,
			unsigned int polylineCount, bool * polylineClosedFlags,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) = 0;

		/**
		 * Checks if all polylines contained in a given patch are closed. Notice that a returned "false"
		 * does not mean they are all not closed (it means that at least one polyline is not closed).
		 * Indeed they can be mixed i.e. some closed and some not.
		 *
		 * @exception	std::out_of_range	If <tt>patchIndex &gt;=</tt> getPatchCount().
		 *
		 * @param 	patchIndex	The index of the patch for which we want to know if all polylines are
		 * 						closed.
		 *
		 * @returns	True if all polylines of patch @p patchIndex are closed, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool virtual areAllPolylinesClosedOfPatch(unsigned int patchIndex) const = 0;

		/**
		 * Checks if all polylines of all patches are closed. Notice that a returned "false" does not
		 * mean they are all not closed (it means that at least one polyline in one patch is not
		 * closed). Indeed they can be mixed i.e. some closed and some not.
		 *
		 * @returns	True if all polylines of all patches are closed, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool areAllPolylinesClosedOfAllPatches() const = 0;

		/**
		 * Checks if all polylines contained in a given patch are not closed. Notice that a returned
		 * "false" does not mean they are all closed (it means that at least one polyline is closed).
		 * Indeed they can be mixed i.e. some closed and some not.
		 *
		 * @exception	std::out_of_range	If <tt>patchIndex &gt;=</tt> getPatchCount().
		 *
		 * @param 	patchIndex	The index of the patch for which we want to know if all polylines are not
		 * 						closed.
		 *
		 * @returns	True if all polylines of patch @p patchIndex are not closed, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool areAllPolylinesNonClosedOfPatch(unsigned int patchIndex) const = 0;

		/**
		 * Checks if all polylines of all patches are not closed. Notice that a returned "false" does
		 * not mean they are all closed (it means that at least one polyline in one patch is closed).
		 * Indeed they can be mixed i.e. some closed and some not.
		 *
		 * @returns	True if all polylines of all patches are not closed, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool areAllPolylinesNonClosedOfAllPatches() const = 0;

		/**
		 * Gets the closed flag of all polylines of a given patch.
		 *
		 * @exception	std::out_of_range	If <tt>patchIndex &gt;=</tt> getPatchCount().
		 *
		 * @param 	   	patchIndex			 	The index of the patch for which we want to get the
		 * 										closed flag of the polylines.
		 * @param [out]	closedFlagPerPolyline	A preallocated array to receive the closed flags. It is
		 * 										ordered by polyline. Its size must be
		 * 										<tt>getPolylineCountOfPatch(patchIndex)</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getClosedFlagPerPolylineOfPatch(unsigned int patchIndex, bool * closedFlagPerPolyline) const = 0;

		/**
		 * Gets the closed flag of all polylines of all patches.
		 *
		 * @param [out]	closedFlagPerPolyline	A preallocated array to receive the closed flags. It is
		 * 										ordered first by polyline then by patch. Its size must be
		 * 										getPolylineCountOfAllPatches().
		 */
		DLL_IMPORT_OR_EXPORT virtual void getClosedFlagPerPolylineOfAllPatches(bool * closedFlagPerPolyline) const = 0;

		/**
		 * Indicates if this polyline set reprsentation is associated to a particular line role.
		 *
		 * @returns	True if this polyline set is associated to a line role, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool hasALineRole() const = 0;

		/**
		 * Gets the line role of this polyline set representation.
		 * 
		 * @exception std::logic_error If no line role is associated to this polyline set representation (please use hasALineRole().
		 *
		 * @returns	The line role of this polyline set representation.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_eml2_3::resqml22__LineRole getLineRole() const = 0;

		/**
		 * Sets the line role of this instance.
		 *
		 * @param 	lineRole	The line role to set.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setLineRole(gsoap_eml2_3::resqml22__LineRole lineRole) = 0;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
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
