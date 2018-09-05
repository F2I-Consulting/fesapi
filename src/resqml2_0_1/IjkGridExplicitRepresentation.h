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

#include "resqml2_0_1/AbstractIjkGridRepresentation.h"

namespace RESQML2_0_1_NS
{
	class DLL_IMPORT_OR_EXPORT IjkGridExplicitRepresentation : public AbstractIjkGridRepresentation
	{
	public:

		/**
		* @param soapContext	The soap context where the underlying gsoap proxy is going to be created.
		*/
		IjkGridExplicitRepresentation(soap* soapContext, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount,
			bool withTruncatedPillars = false);

		IjkGridExplicitRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount,
			bool withTruncatedPillars = false);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		IjkGridExplicitRepresentation(gsoap_resqml2_0_1::_resqml2__IjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
		IjkGridExplicitRepresentation(gsoap_resqml2_0_1::_resqml2__TruncatedIjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~IjkGridExplicitRepresentation() {}

		gsoap_resqml2_0_1::eml20__DataObjectReference* getHdfProxyDor() const;

		/**
		* Get the xyz point count in a given patch.
		*/
		ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all the XYZ points of a particular sequence of K interfaces of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param kInterfaceStart The K index of the starting interface taken from zero to kCellCount.
		* @param kInterfaceEnd The K index of the ending interface taken from zero to kCellCount
		* @param patchIndex	The index of the patch. It is generally zero.
		* @param xyzPoints 	A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated with a size of 3*getXyzPointCountOfKInterfaceOfPatch*(kInterfaceEnd - kInterfaceStart + 1).
		*/
		void getXyzPointsOfKInterfaceSequenceOfPatch(const unsigned int & kInterfaceStart, const unsigned int & kInterfaceEnd, const unsigned int & patchIndex, double * xyzPoints);

		/**
		* Get all the XYZ points of the current block. XYZ points are given in the local CRS. Block information must be loaded.
		* @param patchIndex			The index of the patch. It is generally zero.
		* @param xyzPoints 			A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated with a size of 3*getXyzPointCountOfBlock.
		*/
		void getXyzPointsOfBlockOfPatch(const unsigned int & patchIndex, double * xyzPoints);

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints XYZ double triplets ordered by i then j then split then k. It must be pre allocated with a count of ((iCellCount+1) * (jCellCount+1) + splitCoordinateLineCount) * kCellCount.
		*/
		void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		* Set the geometry of the IJK grid as explicit coordinate line nodes. See Resqml Usage, Technical guide and Enterprise Architect diagrams for details.
		* @param mostComplexPillarGeometry					The most complex pillar geometry which occurs on this reservoir grid.
		* @param kDirectionKind								The direction of the K axis on the earth. It is not directly related to Z of the vertical CRS but to the physical earth (as the vertical CRS is).
		* @param isRightHanded								Indicates that the IJK grid is right handed, as determined by the triple product of tangent vectors in the I, J, and K directions.
		* @param points										XYZ double triplets ordered by i then j then split then k. Count must be ((iCellCount+1) * (jCellCount+1) + splitCoordinateLineCount) * kCellCount.
		* @param proxy										The HDF proxy where all numerical values will be stored.
		* @param splitCoordinateLineCount					The count of split coordinate line. A grid pillar is splitted in up to 4 coordinate lines.
		* @param pillarOfCoordinateLine						For each split coordinate line, indicates which pillar it belongs to. Pillars are identified by their absolute 1d index (iPillar + jPillar*iPillarCount) where iPillarCount == iCellCount+1. Count is splitCoordinateLineCount.
		* @param splitCoordinateLineColumnCumulativeCount	For each split coordinate line, indicates how many columns of the ijk grid are incident to it (minimum is one and maximum is 3) + the count of all incident columns of previous spit coordinate lines in the array.
		*													For example {1, 4, 6} would mean that the first split coordinate line is incident to only one column, the second split coordinate line is incident to 4-1=3 columns and the third column is incident to 6-4=2 columns.
		*													Count is splitCoordinateLineCount.
		* @param splitCoordinateLineColumns					For each split coordinate line, indicates which columns are incident to it. Count is the last value in the splitCoordinateLineColumnCumulativeCount array.
		*													Columns are identified by their absolute 1d index (iColumn + jColumn*iColumnCount) where *Column* == *Cell*.
		* @param definedPillars								For each pillar : 0 if pillar is not defined (i.e points equal to NaN) else the pillar is defined.  This information overrides any pillar geometry information. If null, then all pillars are assumed to be defined.
		*/
		void setGeometryAsCoordinateLineNodes(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * points, COMMON_NS::AbstractHdfProxy* proxy,
			const unsigned long & splitCoordinateLineCount = 0, unsigned int * pillarOfCoordinateLine = nullptr,
			unsigned int * splitCoordinateLineColumnCumulativeCount = nullptr, unsigned int * splitCoordinateLineColumns = nullptr,
			char * definedPillars = nullptr);

		/**
		* Same as setGeometryAsCoordinateLineNodes where the hdf datasets are already written in the the file.
		*/
		void setGeometryAsCoordinateLineNodesUsingExistingDatasets(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			const std::string & points, COMMON_NS::AbstractHdfProxy* proxy,
			const unsigned long & splitCoordinateLineCount = 0, const std::string & pillarOfCoordinateLine = "",
			const std::string & splitCoordinateLineColumnCumulativeCount = "", const std::string & splitCoordinateLineColumns = "",
			const std::string & definedPillars = "");

		geometryKind getGeometryKind() const;
	};
}

