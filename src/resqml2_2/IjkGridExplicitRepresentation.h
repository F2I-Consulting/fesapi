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

#include "../resqml2/IjkGridExplicitRepresentation.h"

namespace RESQML2_2_NS
{
	/**
	* An IJK Grid explicit representation defines each cell corner position by means of XYZ coordinates.
	* Adjacent cell corner are supposed to be located the same so they are not repeated unless you define split lines or split nodes.
	*/
	class IjkGridExplicitRepresentation final : public RESQML2_NS::IjkGridExplicitRepresentation
	{
	public:

		/**
		 * @brief	Constructor
		 *
		 * @param [in]	repo	The repo where the underlying gsoap proxy is going to be created.
		 * @param 	  	guid	Unique identifier.
		 * @param 	  	title	The title.
		 * @param 	  	iCount	Number of cell in I direction.
		 * @param 	  	jCount	Number of cell in J direction.
		 * @param 	  	kCount	Number of cell in K direction.
		 * @param 		kGaps	(Optional) Boolean array of length KCellCount-1.
		 *						TRUE if there is a gap after the corresponding layer.
		 *						Won't be freed by FESAPI.
		 * @param [in]	proxy	(Optional) The HDF proxy for writing the @p enabledCells
		 * 						values. If @c nullptr (default), then the default HDF proxy will be
		 * 						used.
		 */
		IjkGridExplicitRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount,
			bool* kGaps = nullptr, EML2_NS::AbstractHdfProxy* proxy = nullptr) :
			RESQML2_NS::IjkGridExplicitRepresentation(repo, guid, title, iCount, jCount, kCount, kGaps, proxy) {}

		/**
		 * @brief	Constructor
		 *
		 * @param [in]	interp	If non-nullptr, the interp.
		 * @param 	  	guid	Unique identifier.
		 * @param 	  	title	The title.
		 * @param 	  	iCount	Number of cell in I direction.
		 * @param 	  	jCount	Number of cell in J direction.
		 * @param 	  	kCount	Number of cell in K direction.
		 * @param 		kGaps	(Optional) Boolean array of length KCellCount-1.
		 *						TRUE if there is a gap after the corresponding layer.
		 *						Won't be freed by FESAPI.
		 * @param [in]	proxy	(Optional) The HDF proxy for writing the @p enabledCells
		 * 						values. If @c nullptr (default), then the default HDF proxy will be
		 * 						used.
		 */
		IjkGridExplicitRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount,
			bool* kGaps = nullptr, EML2_NS::AbstractHdfProxy* proxy = nullptr) :
			RESQML2_NS::IjkGridExplicitRepresentation(interp, guid, title, iCount, jCount, kCount, kGaps, proxy) {}

		/**
		 * @brief	Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-nullptr, from gsoap.
		 */
		IjkGridExplicitRepresentation(gsoap_eml2_3::_resqml22__IjkGridRepresentation* fromGsoap) : RESQML2_NS::IjkGridExplicitRepresentation(fromGsoap) {}

		/**
		 * @brief	Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-nullptr, from gsoap.
		 */
		IjkGridExplicitRepresentation(gsoap_eml2_3::_resqml22__TruncatedIjkGridRepresentation* fromGsoap) : RESQML2_NS::IjkGridExplicitRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~IjkGridExplicitRepresentation() = default;

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		/**
		* @copybrief resqml2::AbstractRepresentation::getXyzPointsOfPatch
		*
		* @exception std::logic_error	If the geometry of the grid either does not exist or is not an
		* 								explicit one.
		* @exception std::logic_error	If this grid is truncated and the additional grid points cannot be read.
		*
		* @copydetails resqml2::AbstractIjkGridRepresentation::getXyzPointsOfPatch
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const final;

		DLL_IMPORT_OR_EXPORT void setGeometryAsCoordinateLineNodes(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			double const* points, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t splitCoordinateLineCount = 0, unsigned int const* pillarOfCoordinateLine = nullptr,
			unsigned int const* splitCoordinateLineColumnCumulativeCount = nullptr, unsigned int const* splitCoordinateLineColumns = nullptr,
			int8_t const* definedPillars = nullptr, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr) final;

		DLL_IMPORT_OR_EXPORT void setGeometryAsCoordinateLineNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & points, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			uint64_t splitCoordinateLineCount = 0, const std::string & pillarOfCoordinateLine = "",
			const std::string & splitCoordinateLineColumnCumulativeCount = "", const std::string & splitCoordinateLineColumns = "",
			const std::string & definedPillars = "", EML2_NS::AbstractLocal3dCrs * localCrs = nullptr) final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

	private:
		EML2_NS::AbstractHdfProxy* getPointDatasetPath(std::string & datasetPathInExternalFile, uint64_t & splitCoordinateLineCount) const final;
	};
}
