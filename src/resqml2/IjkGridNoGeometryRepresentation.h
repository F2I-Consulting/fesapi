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

#include "AbstractIjkGridRepresentation.h"

namespace RESQML2_NS
{
	/**
	 * @brief	This class is dedicated to IJK grids with undefined <tt>IjkGridGeometry</tt>. There
	 * 			are two main use cases. A first one is block-centered grid, where no geometry is
	 * 			attached to nodes but a property should spatialize cells centers. A second one is
	 * 			LGRs (local refinement grids), where the refined geometry is given thanks to
	 * 			refinement parameters.
	 */
	class IjkGridNoGeometryRepresentation : public AbstractIjkGridRepresentation
	{
	public:
		/**
		* Destructor does nothing since the memory is managed by the gSOAP context.
		*/
		virtual ~IjkGridNoGeometryRepresentation() = default;

		/**
		 * Get the XYZ point count in a given patch of this grid.
		 *
		 * @exception	std::out_of_range	If <tt>patchIndex &gt;= 1</tt> (IJK grids only carry 1 patch).
		 * @exception	std::logic_error 	If getting the XYZ points of this grid is not yet supported.
		 *
		 * @param 	patchIndex	Zero-based index of the patch from which we look for the XYZ points.
		 *
		 * @returns	The XYZ point count of the patch.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getXyzPointCountOfPatch(unsigned int patchIndex) const final;

		/**
		 * Please do not use: not implemented yet. Please use parent window information or geometrical
		 * property information.  
		 *
		 * @exception	std::_out_of_range	If <tt>patchIndex &gt;= 1</tt> (IJK grids only carry 1 patch).
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const final;

		DLL_IMPORT_OR_EXPORT geometryKind getGeometryKind() const final;

	protected:
		IjkGridNoGeometryRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount, bool* kGaps = nullptr, EML2_NS::AbstractHdfProxy* proxy = nullptr) :
			AbstractIjkGridRepresentation(repo, guid, title, iCount, jCount, kCount, kGaps, proxy) {}

		IjkGridNoGeometryRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount, bool* kGaps = nullptr, EML2_NS::AbstractHdfProxy* proxy = nullptr) :
			AbstractIjkGridRepresentation(interp, guid, title, iCount, jCount, kCount, kGaps, proxy) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		IjkGridNoGeometryRepresentation(gsoap_resqml2_0_1::_resqml20__IjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
		IjkGridNoGeometryRepresentation(gsoap_eml2_3::_resqml22__IjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
		IjkGridNoGeometryRepresentation(gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
		IjkGridNoGeometryRepresentation(gsoap_eml2_3::_resqml22__TruncatedIjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
	};
}
