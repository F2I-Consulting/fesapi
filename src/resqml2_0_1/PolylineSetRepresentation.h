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

#include "resqml2/AbstractRepresentation.h"

namespace RESQML2_0_1_NS
{
	class PolylineSetRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	private :
		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry2_0_1(const unsigned int & patchIndex) const;
		void init(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
				  const std::string & guid, const std::string & title);

	public:

		/**
		* Only to be used in partial transfer context
		*/
		PolylineSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractRepresentation(partialObject) {}
		
		/**
		* Creates an instance of this class in a gsoap context.
		* @param crs							The local CRS where the geometry of this representation is given.
		* @param guid							The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title							A title for the instance to create.
		*/
		PolylineSetRepresentation(RESQML2_NS::AbstractLocal3dCrs * crs,
				const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp							The interpretation this representation represents.
		* @param crs							The local CRS where the geometry of this representation is given.
		* @param guid							The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title							A title for the instance to create.
		*/
		PolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
				const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp							The interpretation this representation represents.
		* @param crs							The local CRS where the geometry of this representation is given.
		* @param guid							The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title							A title for the instance to create.
		* @param roleKind						Indicates the role of this representation.
		*/
		PolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
				const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__LineRole & roleKind);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		PolylineSetRepresentation(gsoap_resqml2_0_1::_resqml2__PolylineSetRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~PolylineSetRepresentation() {}

		DLL_IMPORT_OR_EXPORT std::string getHdfProxyUuid() const;

		/**
		* Get the number of polylines in a given patch
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getPolylineCountOfPatch(const unsigned int & patchIndex) const;
		DLL_IMPORT_OR_EXPORT unsigned int getPolylineCountOfAllPatches() const;

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const {return XML_TAG;}

		DLL_IMPORT_OR_EXPORT void getNodeCountPerPolylineInPatch(const unsigned int & patchIndex, unsigned int * NodeCountPerPolyline) const;

		/**
		 * Get all the node count par polyline for all teh aptches of the representation.
		 * @param NodeCountPerPolyline It must be pre-allocated.
		 */
		DLL_IMPORT_OR_EXPORT void getNodeCountPerPolylineOfAllPatches(unsigned int * NodeCountPerPolyline) const;

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
		 * Get the number of triangle patch
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const;

		/**
		* Push back a new patch of polylines
		* @param NodeCountPerPolyline	The node count per polyline in this patch. There must be polylineCount values in this array.
		* @param nodes					The XYZ values of the nodes. Ordered by XYZ and then by NodeCount. It must be three times NodeCount.
		* @param polylineCount			The polyline count in this patch.
		* @param allPolylinesClosedFlag	Indicates the closed flags of all the polylines.
		* @param proxy					The HDF proxy which defines where the nodes and triangle indices will be stored.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackGeometryPatch(
				unsigned int * NodeCountPerPolyline, double * nodes,
				const unsigned int & polylineCount, const bool & allPolylinesClosedFlag,
				COMMON_NS::AbstractHdfProxy* proxy);

		/**
		* Push back a new patch of polylines
		* @param NodeCountPerPolyline	The node count per polyline in this patch. There must be polylineCount values in this array.
		* @param nodes					The XYZ values of the nodes. Ordered by XYZ and then by NodeCount. It must be three times NodeCount.
		* @param polylineCount			The polyline count in this patch.
		* @param polylineClosedFlags	Indicates the closed flags for each of the polyline. The count of this array must be polylineCount.
		* @param proxy					The HDF proxy which defines where the nodes and triangle indices will be stored.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackGeometryPatch(
				unsigned int * NodeCountPerPolyline, double * nodes,
				const unsigned int & polylineCount, bool * polylineClosedFlags,
				COMMON_NS::AbstractHdfProxy* proxy);

		/**
		* Check if all polylines contained in a single patch are closed or not.
		* Notice that a returned "false" does not mean they are all not closed. Indeed they can be mixed i.e. some closed and some not.
		* @param patchIndex	The index of the patch to check.
		* @return			True if all polylines of the studied patch are closed.
		*/
		DLL_IMPORT_OR_EXPORT bool areAllPolylinesClosedOfPatch(const unsigned int & patchIndex) const;
		DLL_IMPORT_OR_EXPORT bool areAllPolylinesClosedOfAllPatches() const;

		/**
		* Check if all polylines contained in a single patch are closed or not.
		* Notice that a returned "false" does not mean they are all closed. Indeed they can be mixed i.e. some closed and some not.
		* @param patchIndex	The index of the patch to check.
		* @return			True if all polylines of the studied patch are not closed.
		*/
		DLL_IMPORT_OR_EXPORT bool areAllPolylinesNonClosedOfPatch(const unsigned int & patchIndex) const;
		DLL_IMPORT_OR_EXPORT bool areAllPolylinesNonClosedOfAllPatches() const;
		
		/**
		 * Get all the node count par polyline for all teh aptches of the representation.
		 * @param NodeCountPerPolyline It must be pre-allocated.
		 */
		DLL_IMPORT_OR_EXPORT void getClosedFlagPerPolylineOfPatch(const unsigned int & patchIndex, bool * closedFlagPerPolyline) const;
		DLL_IMPORT_OR_EXPORT void getClosedFlagPerPolylineOfAllPatches(bool * closedFlagPerPolyline) const;

		/**
		* Indicates if the polylineSet is associated to a particular LineRole.
		*/
		DLL_IMPORT_OR_EXPORT bool hasALineRole() const;

		/**
		* Get the role of this polylineSet.
		* Throw an exception if the polylineSet has no role (see method hasALineRole).
		*/
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml2__LineRole getLineRole() const;

		/**
		* Set the line role of this instance
		*/
		DLL_IMPORT_OR_EXPORT void setLineRole(const gsoap_resqml2_0_1::resqml2__LineRole & lineRole);
	};
}
