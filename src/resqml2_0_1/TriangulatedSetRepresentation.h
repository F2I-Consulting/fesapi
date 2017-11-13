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

#include "resqml2_0_1/AbstractSurfaceRepresentation.h"

namespace resqml2_0_1
{
	/**
	 * A triangulated representation is a representation (most of time a surface) which is constituted by triangles.
	 * Usually all triangles are connected to each others by means of their nodes and edges.
	 */
	class DLL_IMPORT_OR_EXPORT TriangulatedSetRepresentation : public AbstractSurfaceRepresentation
	{
	private :
		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry2_0_1(const unsigned int & patchIndex) const;
	public:

		/**
		* Only to be used in partial transfer context
		*/
		TriangulatedSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractSurfaceRepresentation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp						The interpretation this representation represents.
		* @param crs						The local CRS where the geometry of this representation is given.
		* @param guid						The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		*/
		TriangulatedSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		TriangulatedSetRepresentation(gsoap_resqml2_0_1::_resqml2__TriangulatedSetRepresentation* fromGsoap): AbstractSurfaceRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~TriangulatedSetRepresentation() {}
        
		std::string getHdfProxyUuid() const;

		/**
		* Push back a new patch of triangles
		* @param nodeCount				The node count in this patch.
		* @param nodes					The XYZ values of the nodes. Ordered by XYZ and then by NodeCount. It must be three times NodeCount.
		* @param triangleCount			The triangle count in this patch.
		* @param triangleNodeIndices	The definition of the triangles of the triangulated topology by means of the indices of their vertices in the node list.
		*								The three first values give the 3 indices of the 3 vertices of the first triangle.
		*								The three following values define the 3 vertices of the second triangle and so on...
		* @param proxy					The HDF proxy which defines where the nodes and triangle indices will be stored.
		*/
		void pushBackTrianglePatch(const unsigned int & nodeCount, double * nodes, const unsigned int & triangleCount, unsigned int * triangleNodeIndices, common::AbstractHdfProxy* proxy);

		/**
		* Get the xyz point count in a given patch.
		* @param patchIndex	The index of the patch of the representation.
		*/
		ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

        /**
		* Get the triangle count in a given patch
		* @param patchIndex	The index of the patch of the representation.
		*/
		unsigned int getTriangleCountOfPatch(const unsigned int & patchIndex) const;

        /**
		* Get the triangle count of all patches of this representation.
		*/
		unsigned int getTriangleCountOfAllPatches() const;

		/**
		 * Get all the triangle node indices of a particular patch of this representation.
		 * See getXyzPointsOfPatch method inherited from AbstractRepresentation to read the XYZ coordinates of the triangle nodes.
		 * @param patchIndex 			The index of the patch which contains the triangle node indices we want.
		 * @param triangleNodeIndices	Must be pre-allocated. The count/size of this array should be equal to getTriangleCountOfPatch(patchIndex)*3.
		 */
		void getTriangleNodeIndicesOfPatch(const unsigned int & patchIndex, unsigned int * triangleNodeIndices) const;

		/**
		 * Get all the triangle node indices of all patches of this representation.
		 * See getXyzPointsOfAllPatches method inherited from AbstractRepresentation to read the XYZ coordinates of the triangle nodes.
		 * @param triangleNodeIndices	Must be pre-allocated. The count/size of this array should be equal to getTriangleCountOfAllPatches()*3.
		 */
		void getTriangleNodeIndicesOfAllPatches(unsigned int * triangleNodeIndices) const;
        
		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}
		
		/**
		* Get the patch count in this representation.
		*/
		unsigned int getPatchCount() const;
	};
}
