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

/** . */
namespace RESQML2_NS
{
	/**
	 * A triangulated representation is a representation (most of time a surface) which is
	 * constituted by triangles. Usually all triangles are connected to each others by means of
	 * their nodes and edges.
	 */
	class TriangulatedSetRepresentation : public AbstractSurfaceRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~TriangulatedSetRepresentation() {}

		/**
		 * Push back a new patch of triangles
		 *
		 * @param 		  	nodeCount		   	The node count in this patch.
		 * @param [in,out]	nodes			   	The XYZ values of the nodes. Ordered by XYZ and then by
		 * 										NodeCount. It must be three times NodeCount.
		 * @param 		  	triangleCount	   	The triangle count in this patch.
		 * @param [in,out]	triangleNodeIndices	The definition of the triangles of the triangulated
		 * 										topology by means of the indices of their vertices in the
		 * 										node list. The three first values give the 3 indices of
		 * 										the 3 vertices of the first triangle. The three following
		 * 										values define the 3 vertices of the second triangle and
		 * 										so on...
		 * @param [in,out]	proxy			   	(Optional) The HDF proxy which defines where the nodes
		 * 										and triangle indices will be stored.
		 * @param [in,out]	localCrs		   	(Optional) If non-null, the local crs.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackTrianglePatch(unsigned int nodeCount, double const * nodes, unsigned int triangleCount, unsigned int const * triangleNodeIndices, EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) = 0;

        /**
		* Get the triangle count in a given patch
		* @param patchIndex	The index of the patch of the representation.
		*/
		DLL_IMPORT_OR_EXPORT virtual unsigned int getTriangleCountOfPatch(unsigned int patchIndex) const = 0;

		/**
		 * Get the triangle count of all patches of this representation.
		 *
		 * @returns	The triangle count of all patches.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getTriangleCountOfAllPatches() const = 0;

		/**
		 * Get all the triangle node indices of a particular patch of this representation. See
		 * getXyzPointsOfPatch method inherited from AbstractRepresentation to read the XYZ coordinates
		 * of the triangle nodes.
		 *
		 * @param 		  	patchIndex		   	The index of the patch which contains the triangle node
		 * 										indices we want.
		 * @param [in,out]	triangleNodeIndices	Must be pre-allocated. The count/size of this array
		 * 										should be equal to getTriangleCountOfPatch(patchIndex)*3.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getTriangleNodeIndicesOfPatch(unsigned int patchIndex, unsigned int * triangleNodeIndices) const = 0;

		/**
		 * Get all the triangle node indices of all patches of this representation. See
		 * getXyzPointsOfAllPatches method inherited from AbstractRepresentation to read the XYZ
		 * coordinates of the triangle nodes.
		 *
		 * @param [in,out]	triangleNodeIndices	Must be pre-allocated. The count/size of this array
		 * 										should be equal to getTriangleCountOfAllPatches()*3.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getTriangleNodeIndicesOfAllPatches(unsigned int * triangleNodeIndices) const = 0;

		/**
		 * Get the patch count in this representation.
		 *
		 * @returns	The patch count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const = 0;

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

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT TriangulatedSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractSurfaceRepresentation(partialObject) {}

		/**
		 * Default Constructor
		 */
		TriangulatedSetRepresentation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		TriangulatedSetRepresentation(gsoap_resqml2_0_1::_resqml20__TriangulatedSetRepresentation* fromGsoap) : AbstractSurfaceRepresentation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		TriangulatedSetRepresentation(gsoap_eml2_3::_resqml22__TriangulatedSetRepresentation* fromGsoap) : AbstractSurfaceRepresentation(fromGsoap) {}
	};
}
