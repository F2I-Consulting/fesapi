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

#include "tools/BSpline.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT IjkGridParametricRepresentation : public AbstractIjkGridRepresentation
	{
	private:
		void getXyzPointsOfPatchFromParametricPoints(gsoap_resqml2_0_1::resqml2__Point3dParametricArray* parametricPoint3d, double * xyzPoints) const;
	
		class PillarInformation
		{
		public:

			unsigned int maxControlPointCount;
			unsigned int parametricLineCount;
			unsigned int splitLineCount;
			double * controlPoints;
			double * controlPointParameters;
			short * pillarKind;
			unsigned int* pillarOfSplitCoordLines;
			std::vector< std::vector< geometry::BSpline > > splines;

			PillarInformation():maxControlPointCount(0), parametricLineCount(0), splitLineCount(0),
					controlPoints(nullptr), controlPointParameters(nullptr), pillarKind(nullptr), pillarOfSplitCoordLines(nullptr) {}

			~PillarInformation() {
				cleanMemory();
			}

			void cleanMemory() {
				if (controlPoints != nullptr) delete[] controlPoints;
				if (controlPointParameters != nullptr) delete[] controlPointParameters;
				if (pillarKind != nullptr) delete[] pillarKind;
				if (pillarOfSplitCoordLines != nullptr) delete[] pillarOfSplitCoordLines;
			}
		};

		/**
		* Load in pillarInfo parameter all pillar information.
		* It allows to accelerate getter of xyz points when reading them by K interface
		*/
		void loadPillarInformation(PillarInformation & pillarInfo) const;
	protected:
		PillarInformation* pillarInformation;
	
	public:
		IjkGridParametricRepresentation(soap* soapContext, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount,
			bool withTruncatedPillars = false);

		IjkGridParametricRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount,
			bool withTruncatedPillars = false);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		IjkGridParametricRepresentation(gsoap_resqml2_0_1::_resqml2__IjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap), pillarInformation(nullptr) {}
		IjkGridParametricRepresentation(gsoap_resqml2_0_1::_resqml2__TruncatedIjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap), pillarInformation(nullptr) {}

		/**
		* Destructor clean pillarInformation memory when allocated
		*/
		virtual ~IjkGridParametricRepresentation() { 
			if (pillarInformation != nullptr) 
				delete pillarInformation; 
		}

		std::string getHdfProxyUuid() const;

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
		* @param xyzPoints 	A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated with a size of 3*getXyzPointCountOfKInterfaceOfPatch.
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
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated with a size of 3*getXyzPointCountOfPatch.
		*/
		void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		* Get the max control point count on a pillar of the grid.
		*/
		unsigned int getControlPointMaxCountPerPillar() const;

		/**
		* Get all the control points of each pillar of the IJK parametric grid.
		* They are ordered first (quickest) by pillar and then (slowest) by control point : cp0 of pillar0, cp0 of pillar1, cp0 of pillar3, ..., cp0 of pillarCount-1, cp1 of pillar0, cp1 of pillar1, etc... Pad with nan values if necessary.
		* For information, pillars are ordered first (quicket) by I and then (slowest) by J.
		*/
		void getControlPoints(double * controlPoints, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		/**
		* Check if the IJK grid contains some paraemeters on some control points.
		* It happens when the grid contains at least one non vertical or a non Z linear parametric line.
		*/
		bool hasControlPointParameters() const;

		/**
		* Get all the control point parameters of each pillar of the IJK parametric grid.
		* They are ordered first (quickest) by pillar and then (slowest) by control point : cp0 of pillar0, cp0 of pillar1, cp0 of pillar3, ..., cp0 of pillarCount-1, cp1 of pillar0, cp1 of pillar1, etc... Pad with nan values if necessary.
		* For information, pillars are ordered first (quicket) by I and then (slowest) by J.
		* Only relevant in case it contains at least one non vertical or non Z linear parametric line.
		*/
		void getControlPointParameters(double * controlPointParameters, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		/**
		* Check if the parametric line kind is constant in the grid.
		*/
		bool isParametricLineKindConstant() const;

		/*
		* Get the constant parametric line count in the grid.
		*/
		short getConstantParametricLineKind() const;

		/**
		* Get the kind of each parametric line representing a pillar :
		*					0 = vertical, 1 = linear spline, 2 = natural cubic spline, 3 = cubic spline, 4 = Z linear cubic spline, 5 = minimum-curvature spline, (-1) = null: no line 
		* Only relevant in case the IJK grid is a parametric one.
		*/
		void getParametricLineKind(short * pillarKind, bool reverseIAxis = false, bool reverseJAxis= false) const;

		/**
		* Get all the parameters of each node of the IJK parametric grid.
		* They are ordered first (quickest) by coordinate line and then (slowest) by K level.
		* Only relevant in case the IJK grid is a parametric one.
		*/
		void getParametersOfNodes(double * parameters, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		/**
		* Set the geometry of the IJK grid as parametric pillar nodes where no pillar is splitted.
		* Defined pillars are deduced from pillarKind == -1;
		* @param mostComplexPillarGeometry					The most complex pillar shape which we can find on this ijk grid.
		* @param kDirectionKind								Indicates if the K direction always go up, dow or is not monotonic.
		* @param isRightHanded								Indicates that the IJK grid is right handed, as determined by the triple product of tangent vectors in the I, J, and K directions.
		* @param parameters									The parameter values (regarding the pillars) of each node of the grid.
		* @param controlPoints								The control points of the pillars of the grid. They are ordered first (quickest) by pillar and then (slowest) by control point : cp0 of pillar0, cp0 of pillar1, cp0 of pillar3, ..., cp0 of pillarCount-1, cp1 of pillar0, cp1 of pillar1, etc... Pad with nan values if necessary.
		* @param controlPointParameters						The value of the parameter at each control points. It must be nullptr for vertical and Z linear cubic parametric lines grid.
		* @param controlPointMaxCountPerPillar				The maximum count of control points which defines a pillar of this grid.
		* @param pillarKind									The kind of each pillar : 0 = vertical, 1 = linear spline, 2 = natural cubic spline, 3 = cubic spline, 4 = Z linear cubic spline, 5 = minimum-curvature spline, (-1) = null: no line 
		* @param proxy										The Hdf proxy where all numerical values will be stored.
		* @param splitCoordinateLineCount					The count of split coordinate line in this grid. A pillar being splitted by a maximum of 3 split coordinate lines (one coordinate line is always non splitted)
		*/
		void setGeometryAsParametricNonSplittedPillarNodes(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, const unsigned int & controlPointMaxCountPerPillar, short * pillarKind, common::AbstractHdfProxy* proxy);

		/**
		* Same as setGeometryAsParametricNonSplittedPillarNodes where the hdf datasets are already written in the the file.
		* @param definedPillars								The string to an hdf dataset where the defined pillars are identified : 0 value for not defined (i.e control points are NaN points, i.e pillarKind == -1) else the pillar is defined. This information overrides any pillar geometry information.
		*/
		void setGeometryAsParametricNonSplittedPillarNodesUsingExistingDatasets(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, const unsigned int & controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars, common::AbstractHdfProxy* proxy);

		/**
		* Set the geometry of the IJK grid as parametric pillar nodes where at least one pillar is supposed to be splitted
		* Defined pillars are deduced from pillarKind == -1;
		* @param mostComplexPillarGeometry					The most complex pillar shape which we can find on this ijk grid.
		* @param kDirectionKind								Indicates if the K direction always go up, dow or is not monotonic.
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
		void setGeometryAsParametricSplittedPillarNodes(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, const unsigned int & controlPointMaxCountPerPillar, short * pillarKind, common::AbstractHdfProxy* proxy,
			const unsigned long & splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
			unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns);

		/**
		* Same as setGeometryAsParametricSplittedPillarNodes where the hdf datasets are already written in the the file.
		* @param definedPillars								The string to an hdf dataset where the defined pillars are identified : 0 value for not defined (i.e control points are NaN points, i.e pillarKind == -1) else the pillar is defined.  This information overrides any pillar geometry information.
		*/
		void setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, const unsigned int & controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars, common::AbstractHdfProxy* proxy,
			const unsigned long & splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns);

		/**
		* Set the geometry of the IJK grid as parametric pillar nodes where at least one pillar is supposed to be splitted and where all pillars are of the same kind.
		* All pillars are assumed to be defined using this method.
		* @param kDirectionKind								Indicates if the K direction always go up, dow or is not monotonic.
		* @param isRightHanded								Indicates that the IJK grid is right handed, as determined by the triple product of tangent vectors in the I, J, and K directions.
		* @param parameters									The parameter values (regarding the pillars) of each node of the grid.
		* @param controlPoints								The control points of the pillars of the grid. They are ordered first (quickest) by pillar and then (slowest) by control point : cp0 of pillar0, cp0 of pillar1, cp0 of pillar3, ..., cp0 of pillarCount-1, cp1 of pillar0, cp1 of pillar1, etc... Pad with nan values if necessary.
		* @param controlPointParameters						The value of the parameter at each control points. It must be nullptr for vertical and Z linear cubic parametric lines grid.
		* @param controlPointCountPerPillar					The count of control points which defines each of the pillar of this grid.
		* @param pillarKind									The constant kind of each pillar : 0 = vertical, 1 = linear spline, 2 = natural cubic spline, 3 = cubic spline, 4 = Z linear cubic spline, 5 = minimum-curvature spline, (-1) = null: no line
		* @param proxy										The Hdf proxy where all numerical values will be stored.
		* @param splitCoordinateLineCount					The count of split coordinate line in this grid. A pillar being splitted by a maximum of 3 split coordinate lines (one coordinate line is always non splitted)
		* @param pillarOfCoordinateLine						For each split coordinate line, indicates the pillar it belongs to.
		* @param splitCoordinateLineColumnCumulativeCount	For each split coordinate line, indicates the count of grid column which are splitted by this coordinate line.
		* @param splitCoordinateLineColumns					For each split coordinate line, indicates the grid columns which are splitted by this coordinate line.
		*/
		void setGeometryAsParametricSplittedPillarNodes(
			const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, const unsigned int & controlPointCountPerPillar, short pillarKind, common::AbstractHdfProxy* proxy,
			const unsigned long & splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
			unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns);

		/**
		* Same as setGeometryAsParametricSplittedPillarNodes where the hdf datasets are already written in the the file.
		*/
		void setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
			const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, const unsigned int & controlPointCountPerPillar, short pillarKind, common::AbstractHdfProxy* proxy,
			const unsigned long & splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns);

		geometryKind getGeometryKind() const;
	};
}

