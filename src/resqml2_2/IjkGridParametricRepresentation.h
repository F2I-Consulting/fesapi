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

#include "../resqml2/IjkGridParametricRepresentation.h"

namespace RESQML2_2_NS
{
	/**
	* An IJK Grid parametric representation define the cell corner positions by means of parameters along the pillars of the grid.
	* Adjacent cell corner are supposed to be located the same so they are not repeated unless you define split lines or split nodes.
	*/
	class IjkGridParametricRepresentation final : public RESQML2_NS::IjkGridParametricRepresentation
	{
	public:
		IjkGridParametricRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount,
			bool withTruncatedPillars = false) :
			RESQML2_NS::IjkGridParametricRepresentation(repo, guid, title, iCount, jCount, kCount, withTruncatedPillars) {}

		IjkGridParametricRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount,
			bool withTruncatedPillars = false) :
			RESQML2_NS::IjkGridParametricRepresentation(interp, guid, title, iCount, jCount, kCount, withTruncatedPillars) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		IjkGridParametricRepresentation(gsoap_eml2_3::_resqml22__IjkGridRepresentation* fromGsoap) : RESQML2_NS::IjkGridParametricRepresentation(fromGsoap) {}
		IjkGridParametricRepresentation(gsoap_eml2_3::_resqml22__TruncatedIjkGridRepresentation* fromGsoap) : RESQML2_NS::IjkGridParametricRepresentation(fromGsoap) {}

		/**
		* Destructor clean pillarInformation memory when allocated
		*/
		~IjkGridParametricRepresentation() {}

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		/**
		* Get the xyz point count in a given patch.
		*/
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(unsigned int patchIndex) const final;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated with a size of 3*getXyzPointCountOfPatch.
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const final;

		/**
		* Get the max control point count on a pillar of the grid.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getControlPointMaxCountPerPillar() const final;

		/**
		* Check if the IJK grid contains some paraemeters on some control points.
		* It happens when the grid contains at least one non vertical or a non Z linear parametric line.
		*/
		DLL_IMPORT_OR_EXPORT bool hasControlPointParameters() const final;

		/**
		* Check if the parametric line kind is constant in the grid.
		*/
		DLL_IMPORT_OR_EXPORT bool isParametricLineKindConstant() const final;

		/*
		* Get the constant parametric line count in the grid.
		*/
		DLL_IMPORT_OR_EXPORT short getConstantParametricLineKind() const final;

		using RESQML2_NS::IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodes;
		/**
		* Set the geometry of the IJK grid as parametric pillar nodes where at least one pillar is supposed to be splitted
		* Defined pillars are deduced from pillarKind == -1;
		* @param mostComplexPillarGeometry					The most complex pillar shape which we can find on this ijk grid.
		* @param isRightHanded								Indicates that the IJK grid is right handed, as determined by the triple product of tangent vectors in the I, J, and K directions.
		* @param parameters									The parameter values (regarding the pillars) of each node of the grid.
		* @param controlPoints								The control points of the pillars of the grid. They are ordered first (quickest) by pillar and then (slowest) by control point : cp0 of pillar0, cp0 of pillar1, cp0 of pillar3, ..., cp0 of pillarCount-1, cp1 of pillar0, cp1 of pillar1, etc... Pad with nan values if necessary.
		* @param controlPointParameters						The value of the parameter at each control points. It must be nullptr for vertical and Z linear cubic parametric lines grid.
		* @param controlPointMaxCountPerPillar				The maximum count of control points which defines a pillar of this grid.
		* @param pillarKind									The kind of each pillar : 0 = vertical, 1 = linear spline, 2 = natural cubic spline, 3 = cubic spline, 4 = Z linear cubic spline, 5 = minimum-curvature spline, (-1) = null: no line 
		* @param proxy										The Hdf proxy where all numerical values will be stored.
		* @param splitCoordinateLineCount					The count of split coordinate line in this grid. A pillar being splitted by a maximum of 3 split coordinate lines (one coordinate line is always non splitted)
		* @param pillarOfCoordinateLine						For each split coordinate line, indicates the pillar it belongs to.
		* @param splitCoordinateLineColumnCumulativeCount	For each split coordinate line, indicates the count of grid column which are splitted by this coordinate line.
		* @param splitCoordinateLineColumns					For each split coordinate line, indicates the grid columns which are splitted by this coordinate line.
		*/
		DLL_IMPORT_OR_EXPORT void setGeometryAsParametricSplittedPillarNodes(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, bool isRightHanded,
			double const * parameters, double const * controlPoints, double const * controlPointParameters, unsigned int controlPointMaxCountPerPillar, short const * pillarKind, EML2_NS::AbstractHdfProxy* proxy,
			unsigned long splitCoordinateLineCount, unsigned int const * pillarOfCoordinateLine,
			unsigned int const * splitCoordinateLineColumnCumulativeCount, unsigned int const * splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) final;

		/**
		* Same as setGeometryAsParametricSplittedPillarNodes where the hdf datasets are already written in the the file.
		* @param definedPillars								The string to an hdf dataset where the defined pillars are identified : 0 value for not defined (i.e control points are NaN points, i.e pillarKind == -1) else the pillar is defined.  This information overrides any pillar geometry information.
		*/
		DLL_IMPORT_OR_EXPORT void setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars, EML2_NS::AbstractHdfProxy* proxy,
			unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) final;

		/**
		* Same as setGeometryAsParametricSplittedPillarNodes where the hdf datasets are already written in the the file.
		*/
		DLL_IMPORT_OR_EXPORT void setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointCountPerPillar, short pillarKind, EML2_NS::AbstractHdfProxy* proxy,
			unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) final;

	private:
		EML2_NS::AbstractHdfProxy* getParameterDatasetPath(std::string & datasetPathInExternalFile) const final;
		EML2_NS::AbstractHdfProxy* getControlPointDatasetPath(std::string & datasetPathInExternalFile) const final;
		EML2_NS::AbstractHdfProxy* getControlPointParametersDatasetPath(std::string & datasetPathInExternalFile) const final;
		EML2_NS::AbstractHdfProxy* getParametersOfNodesDatasetPath(std::string & datasetPathInExternalFile) const final;

		void getRawParametricLineKind(short * pillarKind) const final;

		void setGeometryAsParametricSplittedPillarNodesWithoutPillarKindUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointCountPerPillar, EML2_NS::AbstractHdfProxy* proxy,
			unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs);
	};
}