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

/** . */
namespace RESQML2_0_1_NS
{
	/**
	* An IJK Grid explicit representation defines each cell corner position by means of XYZ coordinates.
	* Adjacent cell corner are supposed to be located the same so they are not repeated unless you define split lines or split nodes.
	*/
	class IjkGridExplicitRepresentation final : public RESQML2_NS::IjkGridExplicitRepresentation
	{
	public:

		/**
		 * Constructor
		 *
		 * @param [in,out]	repo					The repo where the underlying gsoap proxy is going to
		 * 											be created.
		 * @param 		  	guid					Unique identifier.
		 * @param 		  	title					The title.
		 * @param 		  	iCount					Number of.
		 * @param 		  	jCount					Number of.
		 * @param 		  	kCount					Number of.
		 * @param 		  	withTruncatedPillars	(Optional) True to with truncated pillars.
		 */
		IjkGridExplicitRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount,
			bool withTruncatedPillars = false) :
			RESQML2_NS::IjkGridExplicitRepresentation(repo, guid, title, iCount, jCount, kCount, withTruncatedPillars) {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	interp					If non-null, the interp.
		 * @param 		  	guid					Unique identifier.
		 * @param 		  	title					The title.
		 * @param 		  	iCount					Number of.
		 * @param 		  	jCount					Number of.
		 * @param 		  	kCount					Number of.
		 * @param 		  	withTruncatedPillars	(Optional) True to with truncated pillars.
		 */
		IjkGridExplicitRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount,
			bool withTruncatedPillars = false) :
			RESQML2_NS::IjkGridExplicitRepresentation(interp, guid, title, iCount, jCount, kCount, withTruncatedPillars) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		IjkGridExplicitRepresentation(gsoap_resqml2_0_1::_resqml20__IjkGridRepresentation* fromGsoap) : RESQML2_NS::IjkGridExplicitRepresentation(fromGsoap) {}
		IjkGridExplicitRepresentation(gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation* fromGsoap) : RESQML2_NS::IjkGridExplicitRepresentation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~IjkGridExplicitRepresentation() {}

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		/**
		 * Get the xyz point count in a given patch.
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	The xyz point count of patch.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(unsigned int patchIndex) const final;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints XYZ double triplets ordered by i then j then split then k. It must be pre allocated with a count of ((iCellCount+1) * (jCellCount+1) + splitCoordinateLineCount) * kCellCount.
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const final;

		/**
		 * Set the geometry of the IJK grid as explicit coordinate line nodes. See Resqml Usage,
		 * Technical guide and Enterprise Architect diagrams for details.
		 *
		 * @param 		  	mostComplexPillarGeometry					The most complex pillar geometry
		 * 																which occurs on this reservoir grid.
		 * @param 		  	kDirectionKind								The direction of the K axis on
		 * 																the earth. It is not directly related
		 * 																to Z of the vertical CRS but to the
		 * 																physical earth (as the vertical CRS
		 * 																is).
		 * @param 		  	isRightHanded								Indicates that the IJK grid is
		 * 																right handed, as determined by the
		 * 																triple product of tangent vectors in
		 * 																the I, J, and K directions.
		 * @param [in,out]	points										XYZ double triplets ordered by i
		 * 																then j then split then k. Count must
		 * 																be ((iCellCount+1) * (jCellCount+1) +
		 * 																splitCoordinateLineCount) *
		 * 																kCellCount.
		 * @param [in,out]	proxy										(Optional) The HDF proxy where
		 * 																all numerical values will be stored.
		 * @param 		  	splitCoordinateLineCount					(Optional) The count of split
		 * 																coordinate line. A grid pillar is
		 * 																splitted in up to 4 coordinate lines.
		 * @param [in,out]	pillarOfCoordinateLine						(Optional) For each split
		 * 																coordinate line, indicates which
		 * 																pillar it belongs to. Pillars are
		 * 																identified by their absolute 1d index
		 * 																(iPillar + jPillar*iPillarCount)
		 * 																where iPillarCount == iCellCount+1.
		 * 																Count is splitCoordinateLineCount.
		 * @param [in,out]	splitCoordinateLineColumnCumulativeCount	(Optional) For each split
		 * 																coordinate line, indicates how many
		 * 																columns of the ijk grid are incident
		 * 																to it (minimum is one and maximum is
		 * 																3) + the count of all incident
		 * 																columns of previous spit coordinate
		 * 																lines in the array. For example {1, 4,
		 * 																6} would mean that the first split
		 * 																coordinate line is incident to only
		 * 																one column, the second split
		 * 																coordinate line is incident to 4-1=3
		 * 																columns and the third column is
		 * 																incident to 6-4=2 columns. Count is
		 * 																splitCoordinateLineCount.
		 * @param [in,out]	splitCoordinateLineColumns					(Optional) For each split
		 * 																coordinate line, indicates which
		 * 																columns are incident to it. Count is
		 * 																the last value in the
		 * 																splitCoordinateLineColumnCumulativeCount
		 * 																array. Columns are identified by
		 * 																their absolute 1d index (iColumn +
		 * 																jColumn*iColumnCount) where *Column*
		 * 																== *Cell*.
		 * @param [in,out]	definedPillars								(Optional) For each pillar : 0 if
		 * 																pillar is not defined (i.e points
		 * 																equal to NaN) else the pillar is
		 * 																defined.  This information overrides
		 * 																any pillar geometry information. If
		 * 																null, then all pillars are assumed to
		 * 																be defined.
		 * @param [in,out]	localCrs									(Optional) The local CRS where
		 * 																the points are given. If nullptr then
		 * 																the default CRS will be used.
		 */
		DLL_IMPORT_OR_EXPORT void setGeometryAsCoordinateLineNodes(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			double * points, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned long splitCoordinateLineCount = 0, unsigned int * pillarOfCoordinateLine = nullptr,
			unsigned int * splitCoordinateLineColumnCumulativeCount = nullptr, unsigned int * splitCoordinateLineColumns = nullptr,
			char * definedPillars = nullptr, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) final;

		/**
		 * Same as setGeometryAsCoordinateLineNodes where the hdf datasets are already written in the
		 * the file.
		 *
		 * @param 		  	mostComplexPillarGeometry					The most complex pillar geometry.
		 * @param 		  	kDirectionKind								The direction kind.
		 * @param 		  	isRightHanded								True if is right handed, false if
		 * 																not.
		 * @param 		  	points										The points.
		 * @param [in,out]	proxy										(Optional) If non-null, the proxy.
		 * @param 		  	splitCoordinateLineCount					(Optional) Number of split
		 * 																coordinate lines.
		 * @param 		  	pillarOfCoordinateLine						(Optional) The pillar of
		 * 																coordinate line.
		 * @param 		  	splitCoordinateLineColumnCumulativeCount	(Optional) Number of split
		 * 																coordinate line column cumulatives.
		 * @param 		  	splitCoordinateLineColumns					(Optional) The split coordinate
		 * 																line columns.
		 * @param 		  	definedPillars								(Optional) The defined pillars.
		 * @param [in,out]	localCrs									(Optional) If non-null, the local
		 * 																crs.
		 */
		DLL_IMPORT_OR_EXPORT void setGeometryAsCoordinateLineNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & points, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned long splitCoordinateLineCount = 0, const std::string & pillarOfCoordinateLine = "",
			const std::string & splitCoordinateLineColumnCumulativeCount = "", const std::string & splitCoordinateLineColumns = "",
			const std::string & definedPillars = "", RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) final;

	private:
		EML2_NS::AbstractHdfProxy* getPointDatasetPath(std::string & datasetPathInExternalFile, unsigned long & splitCoordinateLineCount) const;
	};
}
