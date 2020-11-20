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

#include "../resqml2/TriangulatedSetRepresentation.h"

namespace RESQML2_2_NS
{
	/**
	 * A triangulated representation is a representation (most of time a surface) which is
	 * constituted by triangles. Usually all triangles are connected to each others by means of
	 * their nodes and edges.
	 */
	class TriangulatedSetRepresentation final : public RESQML2_NS::TriangulatedSetRepresentation
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT TriangulatedSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::TriangulatedSetRepresentation(partialObject) {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	repo 	If non-null, the repo.
		 * @param 		  	guid 	Unique identifier.
		 * @param 		  	title	The title.
		 */
		TriangulatedSetRepresentation(COMMON_NS::DataObjectRepository* repo,
			const std::string & guid, const std::string & title);

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
		TriangulatedSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		TriangulatedSetRepresentation(gsoap_eml2_3::_resqml22__TriangulatedSetRepresentation* fromGsoap): RESQML2_NS::TriangulatedSetRepresentation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~TriangulatedSetRepresentation() = default;
        
		COMMON_NS::DataObjectReference getHdfProxyDor() const;

		DLL_IMPORT_OR_EXPORT void pushBackTrianglePatch(unsigned int nodeCount, double const * nodes, unsigned int triangleCount, unsigned int const * triangleNodeIndices,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) final;

		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(unsigned int patchIndex) const final;

		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const final;

		DLL_IMPORT_OR_EXPORT unsigned int getTriangleCountOfPatch(unsigned int patchIndex) const final;

		DLL_IMPORT_OR_EXPORT unsigned int getTriangleCountOfAllPatches() const final;

		DLL_IMPORT_OR_EXPORT void getTriangleNodeIndicesOfPatch(unsigned int patchIndex, unsigned int * triangleNodeIndices) const final;

		DLL_IMPORT_OR_EXPORT void getTriangleNodeIndicesOfAllPatches(unsigned int * triangleNodeIndices) const final;

		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

	private:
		gsoap_eml2_3::resqml22__PointGeometry* getPointGeometry2_2(unsigned int patchIndex) const;
	};
}
