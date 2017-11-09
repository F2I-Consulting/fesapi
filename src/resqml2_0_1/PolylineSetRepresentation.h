/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#pragma once

#include "resqml2/AbstractRepresentation.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT PolylineSetRepresentation : public resqml2::AbstractRepresentation
	{
	private :
		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry2_0_1(const unsigned int & patchIndex) const;
		void init(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
				  const std::string & guid, const std::string & title);

	public:

		/**
		* Only to be used in partial transfer context
		*/
		PolylineSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : resqml2::AbstractRepresentation(partialObject) {}
		
		/**
		* Creates an instance of this class in a gsoap context.
		* @param crs							The local CRS where the geometry of this representation is given.
		* @param guid							The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title							A title for the instance to create.
		*/
		PolylineSetRepresentation(resqml2::AbstractLocal3dCrs * crs,
				const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp							The interpretation this representation represents.
		* @param crs							The local CRS where the geometry of this representation is given.
		* @param guid							The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title							A title for the instance to create.
		*/
		PolylineSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
				const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp							The interpretation this representation represents.
		* @param crs							The local CRS where the geometry of this representation is given.
		* @param guid							The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title							A title for the instance to create.
		* @param roleKind						Indicates the role of this representation.
		*/
		PolylineSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
				const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__LineRole & roleKind);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		PolylineSetRepresentation(gsoap_resqml2_0_1::_resqml2__PolylineSetRepresentation* fromGsoap) : resqml2::AbstractRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~PolylineSetRepresentation() {}

		std::string getHdfProxyUuid() const;

		/**
		* Get the number of polylines in a given patch
		*/
		unsigned int getPolylineCountOfPatch(const unsigned int & patchIndex) const;
		unsigned int getPolylineCountOfAllPatches() const;

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		void getNodeCountPerPolylineInPatch(const unsigned int & patchIndex, unsigned int * NodeCountPerPolyline) const;

		/**
		 * Get all the node count par polyline for all teh aptches of the representation.
		 * @param NodeCountPerPolyline It must be pre-allocated.
		 */
		void getNodeCountPerPolylineOfAllPatches(unsigned int * NodeCountPerPolyline) const;

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
		 * Get the number of triangle patch
		 */
		unsigned int getPatchCount() const;

		/**
		* Push back a new patch of polylines
		* @param NodeCountPerPolyline	The node count per polyline in this patch. There must be polylineCount values in this array.
		* @param nodes					The XYZ values of the nodes. Ordered by XYZ and then by NodeCount. It must be three times NodeCount.
		* @param polylineCount			The polyline count in this patch.
		* @param allPolylinesClosedFlag	Indicates the closed flags of all the polylines.
		* @param proxy					The HDF proxy which defines where the nodes and triangle indices will be stored.
		*/
		void pushBackGeometryPatch(
				unsigned int * NodeCountPerPolyline, double * nodes,
				const unsigned int & polylineCount, const bool & allPolylinesClosedFlag,
				common::AbstractHdfProxy* proxy);

		/**
		* Push back a new patch of polylines
		* @param NodeCountPerPolyline	The node count per polyline in this patch. There must be polylineCount values in this array.
		* @param nodes					The XYZ values of the nodes. Ordered by XYZ and then by NodeCount. It must be three times NodeCount.
		* @param polylineCount			The polyline count in this patch.
		* @param polylineClosedFlags	Indicates the closed flags for each of the polyline. The count of this array must be polylineCount.
		* @param proxy					The HDF proxy which defines where the nodes and triangle indices will be stored.
		*/
		void pushBackGeometryPatch(
				unsigned int * NodeCountPerPolyline, double * nodes,
				const unsigned int & polylineCount, bool * polylineClosedFlags,
				common::AbstractHdfProxy* proxy);

		/**
		* Check if all polylines contained in a single patch are closed or not.
		* Notice that a returned "false" does not mean they are all not closed. Indeed they can be mixed i.e. some closed and some not.
		* @param patchIndex	The index of the patch to check.
		* @return			True if all polylines of the studied patch are closed.
		*/
		bool areAllPolylinesClosedOfPatch(const unsigned int & patchIndex) const;
		bool areAllPolylinesClosedOfAllPatches() const;

		/**
		* Check if all polylines contained in a single patch are closed or not.
		* Notice that a returned "false" does not mean they are all closed. Indeed they can be mixed i.e. some closed and some not.
		* @param patchIndex	The index of the patch to check.
		* @return			True if all polylines of the studied patch are not closed.
		*/
		bool areAllPolylinesNonClosedOfPatch(const unsigned int & patchIndex) const;
		bool areAllPolylinesNonClosedOfAllPatches() const;
		
		/**
		 * Get all the node count par polyline for all teh aptches of the representation.
		 * @param NodeCountPerPolyline It must be pre-allocated.
		 */
		void getClosedFlagPerPolylineOfPatch(const unsigned int & patchIndex, bool * closedFlagPerPolyline) const;
		void getClosedFlagPerPolylineOfAllPatches(bool * closedFlagPerPolyline) const;

		/**
		* Indicates if the polylineSet is associated to a particular LineRole.
		*/
		bool hasALineRole() const;

		/**
		* Get the role of this polylineSet.
		* Throw an exception if the polylineSet has no role (see method hasALineRole).
		*/
        gsoap_resqml2_0_1::resqml2__LineRole getLineRole() const;

		/**
		* Set the line role of this instance
		*/
		void setLineRole(const gsoap_resqml2_0_1::resqml2__LineRole & lineRole);

	};
}
