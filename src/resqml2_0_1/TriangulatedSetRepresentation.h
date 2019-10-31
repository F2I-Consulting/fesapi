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

#include "AbstractSurfaceRepresentation.h"

namespace RESQML2_0_1_NS
{
	/**
	 * A triangulated representation is a representation (most of time a surface) which is constituted by triangles.
	 * Usually all triangles are connected to each others by means of their nodes and edges.
	 */
	class TriangulatedSetRepresentation : public AbstractSurfaceRepresentation
	{
	private :
		gsoap_resqml2_0_1::resqml20__PointGeometry* getPointGeometry2_0_1(unsigned int patchIndex) const;
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT TriangulatedSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractSurfaceRepresentation(partialObject) {}

		TriangulatedSetRepresentation(COMMON_NS::DataObjectRepository* repo,
			const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp						The interpretation this representation represents.
		* @param guid						The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		*/
		TriangulatedSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		TriangulatedSetRepresentation(gsoap_resqml2_0_1::_resqml20__TriangulatedSetRepresentation* fromGsoap): AbstractSurfaceRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~TriangulatedSetRepresentation() {}
        
		gsoap_resqml2_0_1::eml20__DataObjectReference* getHdfProxyDor() const;

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
		DLL_IMPORT_OR_EXPORT void pushBackTrianglePatch(unsigned int nodeCount, double * nodes, unsigned int triangleCount, unsigned int * triangleNodeIndices, COMMON_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr);

		/**
		* Get the xyz point count in a given patch.
		* @param patchIndex	The index of the patch of the representation.
		*/
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

        /**
		* Get the triangle count in a given patch
		* @param patchIndex	The index of the patch of the representation.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getTriangleCountOfPatch(const unsigned int & patchIndex) const;

        /**
		* Get the triangle count of all patches of this representation.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getTriangleCountOfAllPatches() const;

		/**
		 * Get all the triangle node indices of a particular patch of this representation.
		 * See getXyzPointsOfPatch method inherited from AbstractRepresentation to read the XYZ coordinates of the triangle nodes.
		 * @param patchIndex 			The index of the patch which contains the triangle node indices we want.
		 * @param triangleNodeIndices	Must be pre-allocated. The count/size of this array should be equal to getTriangleCountOfPatch(patchIndex)*3.
		 */
		DLL_IMPORT_OR_EXPORT void getTriangleNodeIndicesOfPatch(const unsigned int & patchIndex, unsigned int * triangleNodeIndices) const;

		/**
		 * Get all the triangle node indices of all patches of this representation.
		 * See getXyzPointsOfAllPatches method inherited from AbstractRepresentation to read the XYZ coordinates of the triangle nodes.
		 * @param triangleNodeIndices	Must be pre-allocated. The count/size of this array should be equal to getTriangleCountOfAllPatches()*3.
		 */
		DLL_IMPORT_OR_EXPORT void getTriangleNodeIndicesOfAllPatches(unsigned int * triangleNodeIndices) const;
		
		/**
		* Get the patch count in this representation.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const;

		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }
	};
}
