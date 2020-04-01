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
	 * An IJK Grid explicit representation defines each cell corner position by means of XYZ
	 * coordinates. Adjacent cell corner are supposed to be located the same so they are not
	 * repeated unless you define split lines or split nodes.
	 */
	class IjkGridExplicitRepresentation : public AbstractIjkGridRepresentation
	{
	public:
		/**
		* Destructor does nothing since the memory is managed by the gSOAP context.
		*/
		virtual ~IjkGridExplicitRepresentation() {}

		/**
		* @copybrief AbstractIjkGridRepresentation::getXyzPointsOfKInterfaceSequence
		* 			 
		* @exception std::invalid_argument	If this grid is truncated.
		* 
		* @copydetails AbstractIjkGridRepresentation::getXyzPointsOfKInterfaceSequence									
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfKInterfaceSequence(unsigned int kInterfaceStart, unsigned int kInterfaceEnd, double * xyzPoints) override;

		/**
		* @copybrief AbstractIjkGridRepresentation::getXyzPointsOfBlock
		*
		* @exception std::invalid_argument	If this grid is truncated.
		*
		* @copydetails AbstractIjkGridRepresentation::getXyzPointsOfBlock
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfBlock(double * xyzPoints) override;

		/**
		 * @brief Sets the geometry of this IJK grid as explicit coordinate line nodes. See RESQML Usage,
		 * Technical guide and Enterprise Architect diagrams for details.
		 *
		 * @exception	std::invalid_argument	If @p points is @c nullptr.
		 * @exception	std::invalid_argument	If <tt>(splitCoordinateLineCount != 0 &amp;&amp;
		 * 										(pillarOfCoordinateLine == nullptr ||
		 * 										splitCoordinateLineColumnCumulativeCount == nullptr ||
		 * 										splitCoordinateLineColumns == nullptr))</tt>.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p localCrs is @c nullptr and no default local 3d CRS
		 * 										is defined.
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
		 * @param [in]	  	points										XYZ double triplets ordered by i
		 * 																then j then split then k. Count must
		 * 																be <tt>((iCellCount+1) *
		 * 																(jCellCount+1) +
		 * 																splitCoordinateLineCount) *
		 * 																kCellCount</tt>.
		 * @param [in,out]	proxy										(Optional) The HDF proxy where
		 * 																all numerical values will be stored.
		 * 																If @c nullptr, then the default HDF
		 * 																proxy of the repository will be used.
		 * @param 		  	splitCoordinateLineCount					(Optional) The count of split
		 * 																coordinate line. A grid pillar is
		 * 																splitted in up to 4 coordinate lines.
		 * @param [in]	  	pillarOfCoordinateLine						(Optional) For each split
		 * 																coordinate line, indicates which
		 * 																pillar it belongs to. Pillars are
		 * 																identified by their absolute 1d index
		 * 																<tt>(iPillar + jPillar *
		 * 																iPillarCount)</tt> where
		 * 																<tt>iPillarCount ==
		 * 																iCellCount+1</tt>. Count is
		 * 																splitCoordinateLineCount.
		 * @param [in]	  	splitCoordinateLineColumnCumulativeCount	(Optional) For each split
		 * 																coordinate line, indicates how many
		 * 																columns of the ijk grid are incident
		 * 																to it (minimum is one and maximum is
		 * 																3) + the count of all incident
		 * 																columns of previous spit coordinate
		 * 																lines in the array. For example
		 * 																<tt>{1, 4, 6}</tt> would mean that
		 * 																the first split coordinate line is
		 * 																incident to only one column, the
		 * 																second split coordinate line is
		 * 																incident to <tt>4 - 1 = 3</tt>
		 * 																columns and the third column is
		 * 																incident to <tt>6 - 4 = 2</tt>
		 * 																columns. Count is
		 * 																splitCoordinateLineCount.
		 * @param [in]	  	splitCoordinateLineColumns					(Optional) For each split
		 * 																coordinate line, indicates which
		 * 																columns are incident to it. Count is
		 * 																the last value in the
		 * 																splitCoordinateLineColumnCumulativeCount
		 * 																array. Columns are identified by
		 * 																their absolute 1d index
		 * 																<tt>(iColumn</tt>
		 * 																<tt> + jColumn * iColumnCount)</tt>
		 * 																where
		 * 																Column == Cell.
		 * @param [in]	  	definedPillars								(Optional) For each pillar : 0 if
		 * 																pillar is not defined (i.e points
		 * 																equal to NaN) else the pillar is
		 * 																defined.  This information overrides
		 * 																any pillar geometry information. If
		 * 																null, then all pillars are assumed to
		 * 																be defined.
		 * @param [in]	  	localCrs									(Optional) The local CRS where
		 * 																the points are given. If @c nullptr
		 * 																(default) then the default CRS of the
		 * 																repository will be used.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setGeometryAsCoordinateLineNodes(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			double * points, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned long splitCoordinateLineCount = 0, unsigned int * pillarOfCoordinateLine = nullptr,
			unsigned int * splitCoordinateLineColumnCumulativeCount = nullptr, unsigned int * splitCoordinateLineColumns = nullptr,
			char * definedPillars = nullptr, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) = 0;

		/**
		* @copybrief setGeometryAsCoordinateLineNodes
		* Same as setGeometryAsCoordinateLineNodes where the hdf datasets are already written in the the file.
		* 
		* @copydetails setGeometryAsCoordinateLineNodes
		*/
		DLL_IMPORT_OR_EXPORT virtual void setGeometryAsCoordinateLineNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & points, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			unsigned long splitCoordinateLineCount = 0, const std::string & pillarOfCoordinateLine = "",
			const std::string & splitCoordinateLineColumnCumulativeCount = "", const std::string & splitCoordinateLineColumns = "",
			const std::string & definedPillars = "", RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) = 0;

		DLL_IMPORT_OR_EXPORT bool isNodeGeometryCompressed() const override;

		DLL_IMPORT_OR_EXPORT geometryKind getGeometryKind() const override;

	protected:
		/**
		* @param repo	The repo where the underlying gsoap proxy is going to be created.
		*/
		IjkGridExplicitRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount,
			bool withTruncatedPillars = false) :
			AbstractIjkGridRepresentation(repo, guid, title, iCount, jCount, kCount, withTruncatedPillars) {}

		IjkGridExplicitRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount,
			bool withTruncatedPillars = false) :
			AbstractIjkGridRepresentation(interp, guid, title, iCount, jCount, kCount, withTruncatedPillars) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		IjkGridExplicitRepresentation(gsoap_resqml2_0_1::_resqml20__IjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
		IjkGridExplicitRepresentation(gsoap_eml2_3::_resqml22__IjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
		IjkGridExplicitRepresentation(gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
		IjkGridExplicitRepresentation(gsoap_eml2_3::_resqml22__TruncatedIjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}

		virtual EML2_NS::AbstractHdfProxy* getPointDatasetPath(std::string & datasetPathInExternalFile, unsigned long & splitCoordinateLineCount) const = 0;
	};
}
