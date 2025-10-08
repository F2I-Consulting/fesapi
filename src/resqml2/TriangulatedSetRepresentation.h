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

namespace RESQML2_NS
{
	/**
	 * @brief	A triangulated representation is a representation (most of time a surface) which is
	 * 			constituted by triangles. Usually all triangles are connected to each others by means
	 * 			of their nodes and edges.
	 */
	class TriangulatedSetRepresentation : public AbstractSurfaceRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~TriangulatedSetRepresentation() = default;

		/**
		 * Pushes back a new patch of triangles.
		 *
		 * @exception	std::invalid_argument	If <tt>proxy == nullptr</tt> and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If <tt>localCrs == nullptr</tt> and no default local CRS
		 * 										id defined in the repository.
		 *
		 * @param 		  	nodeCount		   	The node count in this patch.
		 * @param [in]	  	nodes			   	An array of size <tt>3 * nodeCount</tt> containing the
		 * 										xyz values of the nodes. It is ordered first by xyz and
		 * 										then by nodes.
		 * @param 		  	triangleCount	   	The triangle count in this patch.
		 * @param [in]	  	triangleNodeIndices	An array of size <tt>3 * triangleCount</tt> containing
		 * 										the definition of the triangles of the triangulated
		 * 										topology by means of the indices of their vertices in the
		 * 										node list. The three first values give the 3 indices of
		 * 										the 3 vertices of the first triangle. The three following
		 * 										values define the 3 vertices of the second triangle and
		 * 										so on.
		 * @param [in,out]	proxy			   	(Optional) The HDF proxy which defines where the nodes
		 * 										and triangle indices will be stored. If @c nullptr
		 * 										(default), then the repository default HDF proxy will be
		 * 										used.
		 * @param [in]	  	localCrs		   	(Optional) The local CRS where the nodes are defined. If
		 * 										@c nullptr (default value), then the repository default
		 * 										local CRS will be used.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackTrianglePatch(unsigned int nodeCount, double const * nodes, unsigned int triangleCount, unsigned int const * triangleNodeIndices, EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs* localCrs = nullptr) = 0;

		/**
		 * Gets the triangle count in a given patch of this representation.
		 *
		 * @exception	std::out_of_range	If <tt>patchIndex &gt;=</tt> getPatchCount().
		 *
		 * @param 	patchIndex	A patch index.
		 *
		 * @returns	The triangle count of the patch at position @p patchIndex.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getTriangleCountOfPatch(uint64_t patchIndex) const = 0;

		/**
		 * Get the triangle count of all patches of this representation.
		 *
		 * @returns	The triangle count of all patches.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getTriangleCountOfAllPatches() const = 0;

		/**
		 * Gets all the triangle node indices of a particular patch of this representation. See
		 * {@link resqml2::AbstractRepresentation::getXyzPointsOfPatch} method to read the xyz coordinates
		 * of the triangle nodes.
		 *
		 * @exception	std::out_of_range	If <tt>patchIndex &gt;=</tt> getPatchCount().
		 *
		 * @param 	   	patchIndex		   	The index of the patch which contains the triangle node
		 * 									indices we want to get.
		 * @param [out]	triangleNodeIndices	A preallocated array of size <tt>3 *
		 * 									getTriangleCountOfPatch(patchIndex)</tt> to receive the
		 * 									triangle node indices. The three first values give the 3
		 * 									indices of the 3 vertices of the first triangle. The three
		 * 									following values define the 3 vertices of the second triangle
		 * 									and so on.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getTriangleNodeIndicesOfPatch(uint64_t patchIndex, unsigned int * triangleNodeIndices) const = 0;

		/**
		 * Gets all the triangle node indices of all patches of this representation. See
		 * {@link resqml2::AbstractRepresentation::getXyzPointsOfPatch} method to read the xyz coordinates
		 * of the triangle nodes.
		 *
		 * @param [out]	triangleNodeIndices	A preallocated array of size <tt>3 *
		 * 									getTriangleCountOfAllPatches()</tt> to receive the triangle
		 * 									node indices. It is ordered first by nodes, then by
		 * 									triangles and then by patches.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getTriangleNodeIndicesOfAllPatches(unsigned int * triangleNodeIndices) const = 0;

		DLL_IMPORT_OR_EXPORT uint64_t getPatchCount() const override = 0;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "TriangulatedSetRepresentation";

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
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
