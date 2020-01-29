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

/** . */
namespace RESQML2_0_1_NS
{
	/**
	 * An IJK Grid parametric representation define the cell corner positions by means of parameters
	 * along the pillars of the grid. Adjacent cell corner are supposed to be located the same so
	 * they are not repeated unless you define split lines or split nodes.
	 */
	class IjkGridParametricRepresentation : public AbstractIjkGridRepresentation
	{
	private:

		/**
		 * Gets xyz points of patch from parametric points
		 *
		 * @param [in,out]	parametricPoint3d	If non-null, the parametric point 3D.
		 * @param [in,out]	xyzPoints		 	If non-null, the xyz points.
		 */
		void getXyzPointsOfPatchFromParametricPoints(gsoap_resqml2_0_1::resqml20__Point3dParametricArray* parametricPoint3d, double * xyzPoints) const;

		/**
		 * From
		 * https://en.wikipedia.org/w/index.php?title=Spline_%28mathematics%29&amp;oldid=288288033#Algorithm_for_computing_natural_cubic_splines
		 */
		class BSpline
		{
		public:
			/** Default constructor */
			BSpline() {};

			/**
			 * Constructor
			 *
			 * @param 	parametersAtControlPoint	The parameters at control point.
			 * @param 	valuesAtControlPoint		The values at control point.
			 */
			BSpline(const std::vector<double> & parametersAtControlPoint, const std::vector<double> & valuesAtControlPoint);
			/** Destructor */
			~BSpline() {}

			/**
			 * Gets value from parameter
			 *
			 * @param 	param	The parameter.
			 *
			 * @returns	The value from parameter.
			 */
			double getValueFromParameter(double param) const;

			/**
			 * Sets parameter and value at control point
			 *
			 * @param 	parametersAtControlPoint	The parameters at control point.
			 * @param 	valuesAtControlPoint		The values at control point.
			 */
			void setParameterAndValueAtControlPoint(const std::vector<double> & parametersAtControlPoint, const std::vector<double> & valuesAtControlPoint);

		private:

			/** Check if parameters increase or decrease */
			void checkIfParametersIncreaseOrDecrease();

			/**
			 * Gets spline index from parameter
			 *
			 * @param 	param	The parameter.
			 *
			 * @returns	The spline index from parameter.
			 */
			std::size_t getSplineIndexFromParameter(double param) const;

			/** True if are parameters increasing */
			bool areParametersIncreasing;

			/** basically each of set of 5 double describe a spline */
			std::vector<double> a;
			/** A std::vector&lt;double&gt; to process */
			std::vector<double> b;
			/** A std::vector&lt;double&gt; to process */
			std::vector<double> c;
			/** A std::vector&lt;double&gt; to process */
			std::vector<double> d;
			/** named x in the wiki link */
			std::vector<double> parameter;

		};

		/** Information about the pillar. */
		class PillarInformation
		{
		public:

			/** Number of maximum control points */
			unsigned int maxControlPointCount;
			/** Number of parametric lines */
			unsigned int parametricLineCount;
			/** Number of split lines */
			unsigned int splitLineCount;
			/** The control points */
			double * controlPoints;
			/** Options for controlling the control point */
			double * controlPointParameters;
			/** The pillar kind */
			short * pillarKind;
			/** The pillar of split coordinate lines */
			unsigned int* pillarOfSplitCoordLines;
			/** The splines */
			std::vector< std::vector< BSpline > > splines;

			/** Default constructor */
			PillarInformation():maxControlPointCount(0), parametricLineCount(0), splitLineCount(0),
					controlPoints(nullptr), controlPointParameters(nullptr), pillarKind(nullptr), pillarOfSplitCoordLines(nullptr) {}

			/** Destructor */
			~PillarInformation() {
				cleanMemory();
			}

			/** Clean memory */
			void cleanMemory() {
				if (controlPoints != nullptr) delete[] controlPoints;
				if (controlPointParameters != nullptr) delete[] controlPointParameters;
				if (pillarKind != nullptr) delete[] pillarKind;
				if (pillarOfSplitCoordLines != nullptr) delete[] pillarOfSplitCoordLines;
			}
		};

		/**
		 * Load in pillarInfo parameter all pillar information. It allows to accelerate getter of xyz
		 * points when reading them by K interface
		 *
		 * @param [in,out]	pillarInfo	Information describing the pillar.
		 */
		void loadPillarInformation(PillarInformation & pillarInfo) const;

		/**
		 * Compute the K Direction of the gid according to its control points.
		 *
		 * @param 		  	controlPoints			  	The control points.
		 * @param 		  	controlPointCountPerPillar	The control point count per pillar.
		 * @param [in,out]	pillarKind				  	If non-null, the pillar kind.
		 * @param 		  	localCrs				  	The local crs.
		 *
		 * @returns	The calculated k direction.
		 */
		gsoap_resqml2_0_1::resqml20__KDirection computeKDirection(double const * controlPoints, unsigned int controlPointCountPerPillar, short * pillarKind, RESQML2_NS::AbstractLocal3dCrs const * localCrs);

		/**
		 * Sets geometry as parametric splitted pillar nodes without pillar kind using existing
		 * datasets
		 *
		 * @param 		  	kDirectionKind								The direction kind.
		 * @param 		  	isRightHanded								True if is right handed, false if
		 * 																not.
		 * @param 		  	parameters									Options for controlling the
		 * 																operation.
		 * @param 		  	controlPoints								The control points.
		 * @param 		  	controlPointParameters						Options for controlling the
		 * 																control point.
		 * @param 		  	controlPointCountPerPillar					The control point count per
		 * 																pillar.
		 * @param [in,out]	proxy										If non-null, the proxy.
		 * @param 		  	splitCoordinateLineCount					Number of split coordinate lines.
		 * @param 		  	pillarOfCoordinateLine						The pillar of coordinate line.
		 * @param 		  	splitCoordinateLineColumnCumulativeCount	Number of split coordinate line
		 * 																column cumulatives.
		 * @param 		  	splitCoordinateLineColumns					The split coordinate line columns.
		 * @param [in,out]	localCrs									If non-null, the local crs.
		 */
		void setGeometryAsParametricSplittedPillarNodesWithoutPillarKindUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointCountPerPillar, COMMON_NS::AbstractHdfProxy* proxy,
			unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs);

		/**
		 * Writes a geometry on hdf
		 *
		 * @param 		  	parameters									Options for controlling the
		 * 																operation.
		 * @param 		  	controlPoints								The control points.
		 * @param 		  	controlPointParameters						Options for controlling the
		 * 																control point.
		 * @param 		  	controlPointCountPerPillar					The control point count per
		 * 																pillar.
		 * @param 		  	splitCoordinateLineCount					Number of split coordinate lines.
		 * @param 		  	pillarOfCoordinateLine						The pillar of coordinate line.
		 * @param 		  	splitCoordinateLineColumnCumulativeCount	Number of split coordinate line
		 * 																column cumulatives.
		 * @param 		  	splitCoordinateLineColumns					The split coordinate line columns.
		 * @param [in,out]	proxy										If non-null, the proxy.
		 */
		void writeGeometryOnHdf(double const * parameters,
			double const * controlPoints, double const * controlPointParameters, unsigned int controlPointCountPerPillar,
			unsigned long splitCoordinateLineCount, unsigned int const * pillarOfCoordinateLine,
			unsigned int const * splitCoordinateLineColumnCumulativeCount, unsigned int const * splitCoordinateLineColumns, COMMON_NS::AbstractHdfProxy * proxy);

	protected:
		/** Information describing the pillar */
		PillarInformation* pillarInformation;
	
	public:

		/**
		 * Constructor
		 *
		 * @param [in,out]	repo					If non-null, the repo.
		 * @param 		  	guid					Unique identifier.
		 * @param 		  	title					The title.
		 * @param 		  	iCount					Number of.
		 * @param 		  	jCount					Number of.
		 * @param 		  	kCount					Number of.
		 * @param 		  	withTruncatedPillars	(Optional) True to with truncated pillars.
		 */
		IjkGridParametricRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount,
			bool withTruncatedPillars = false);

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
		IjkGridParametricRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount,
			bool withTruncatedPillars = false);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		IjkGridParametricRepresentation(gsoap_resqml2_0_1::_resqml20__IjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap), pillarInformation(nullptr) {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		IjkGridParametricRepresentation(gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap), pillarInformation(nullptr) {}

		/** Destructor clean pillarInformation memory when allocated */
		virtual ~IjkGridParametricRepresentation() { 
			if (pillarInformation != nullptr) 
				delete pillarInformation; 
		}

		/**
		 * Gets hdf proxy dor
		 *
		 * @returns	Null if it fails, else the hdf proxy dor.
		 */
		gsoap_resqml2_0_1::eml20__DataObjectReference* getHdfProxyDor() const;

		/**
		 * Get the xyz point count in a given patch.
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	The xyz point count of patch.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		 * Get all the XYZ points of a particular sequence of K interfaces of a particular patch of this
		 * representation. XYZ points are given in the local CRS.
		 *
		 * @param 		  	kInterfaceStart	The K index of the starting interface taken from zero to
		 * 									kCellCount.
		 * @param 		  	kInterfaceEnd  	The K index of the ending interface taken from zero to
		 * 									kCellCount.
		 * @param 		  	patchIndex	   	The index of the patch. It is generally zero.
		 * @param [in,out]	xyzPoints	   	A linearized 2d array where the first (quickest) dimension is
		 * 									coordinate dimension (XYZ) and second dimension is vertex
		 * 									dimension. It must be pre allocated with a size of
		 * 									3*getXyzPointCountOfKInterfaceOfPatch.
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfKInterfaceSequenceOfPatch(const unsigned int & kInterfaceStart, const unsigned int & kInterfaceEnd, const unsigned int & patchIndex, double * xyzPoints);

		/**
		 * Get all the XYZ points of the current block. XYZ points are given in the local CRS. Block
		 * information must be loaded.
		 *
		 * @param 		  	patchIndex	The index of the patch. It is generally zero.
		 * @param [in,out]	xyzPoints 	A linearized 2d array where the first (quickest) dimension is
		 * 								coordinate dimension (XYZ) and second dimension is vertex
		 * 								dimension. It must be pre allocated with a size of
		 * 								3*getXyzPointCountOfBlock.
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfBlockOfPatch(const unsigned int & patchIndex, double * xyzPoints);

		/**
		 * Get all the XYZ points of a particular patch of this representation. XYZ points are given in
		 * the local CRS.
		 *
		 * @param 		  	patchIndex	Zero-based index of the patch.
		 * @param [in,out]	xyzPoints 	A linearized 2d array where the first (quickest) dimension is
		 * 								coordinate dimension (XYZ) and second dimension is vertex
		 * 								dimension. It must be pre allocated with a size of
		 * 								3*getXyzPointCountOfPatch.
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		 * Get the max control point count on a pillar of the grid.
		 *
		 * @returns	The control point maximum count per pillar.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getControlPointMaxCountPerPillar() const;

		/**
		 * Get all the control points of each pillar of the IJK parametric grid. They are ordered first
		 * (quickest) by pillar and then (slowest) by control point : cp0 of pillar0, cp0 of pillar1,
		 * cp0 of pillar3, ..., cp0 of pillarCount-1, cp1 of pillar0, cp1 of pillar1, etc... Pad with
		 * nan values if necessary. For information, pillars are ordered first (quicket) by I and then
		 * (slowest) by J.
		 *
		 * @param [in,out]	controlPoints	If non-null, the control points.
		 * @param 		  	reverseIAxis 	(Optional) True to reverse i axis.
		 * @param 		  	reverseJAxis 	(Optional) True to reverse j axis.
		 * @param 		  	reverseKAxis 	(Optional) True to reverse k axis.
		 */
		DLL_IMPORT_OR_EXPORT void getControlPoints(double * controlPoints, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		/**
		 * Check if the IJK grid contains some paraemeters on some control points. It happens when the
		 * grid contains at least one non vertical or a non Z linear parametric line.
		 *
		 * @returns	True if control point parameters, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasControlPointParameters() const;

		/**
		 * Get all the control point parameters of each pillar of the IJK parametric grid. They are
		 * ordered first (quickest) by pillar and then (slowest) by control point : cp0 of pillar0, cp0
		 * of pillar1, cp0 of pillar3, ..., cp0 of pillarCount-1, cp1 of pillar0, cp1 of pillar1, etc...
		 * Pad with nan values if necessary. For information, pillars are ordered first (quicket) by I
		 * and then (slowest) by J. Only relevant in case it contains at least one non vertical or non Z
		 * linear parametric line.
		 *
		 * @param [in,out]	controlPointParameters	If non-null, options for controlling the control
		 * 											point.
		 * @param 		  	reverseIAxis		  	(Optional) True to reverse i axis.
		 * @param 		  	reverseJAxis		  	(Optional) True to reverse j axis.
		 * @param 		  	reverseKAxis		  	(Optional) True to reverse k axis.
		 */
		DLL_IMPORT_OR_EXPORT void getControlPointParameters(double * controlPointParameters, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		/**
		 * Check if the parametric line kind is constant in the grid.
		 *
		 * @returns	True if parametric line kind constant, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isParametricLineKindConstant() const;

		/**
		 * Get the constant parametric line count in the grid.
		 *
		 * @returns	The constant parametric line kind.
		 */
		DLL_IMPORT_OR_EXPORT short getConstantParametricLineKind() const;

		/**
		 * Get the kind of each parametric line representing a pillar :
		 *   				0 = vertical, 1 = linear spline, 2 = natural cubic spline, 3 = cubic spline, 4 = Z
		 *   				linear cubic spline, 5 = minimum-curvature spline, (-1) = null: no line
		 * Only relevant in case the IJK grid is a parametric one.
		 *
		 * @param [in,out]	pillarKind  	If non-null, the pillar kind.
		 * @param 		  	reverseIAxis	(Optional) True to reverse i axis.
		 * @param 		  	reverseJAxis	(Optional) True to reverse j axis.
		 */
		DLL_IMPORT_OR_EXPORT void getParametricLineKind(short * pillarKind, bool reverseIAxis = false, bool reverseJAxis= false) const;

		/**
		 * Get all the parameters of each node of the IJK parametric grid. They are ordered first
		 * (quickest) by coordinate line and then (slowest) by K level. Only relevant in case the IJK
		 * grid is a parametric one.
		 *
		 * @param [in,out]	parameters  	If non-null, options for controlling the operation.
		 * @param 		  	reverseIAxis	(Optional) True to reverse i axis.
		 * @param 		  	reverseJAxis	(Optional) True to reverse j axis.
		 * @param 		  	reverseKAxis	(Optional) True to reverse k axis.
		 */
		DLL_IMPORT_OR_EXPORT void getParametersOfNodes(double * parameters, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		/**
		 * Get all the parameters of a particular sequence of K interfaces of a particular patch of this
		 * representation.
		 *
		 * @param 		  	kInterfaceStart	The K index of the starting interface taken from zero to
		 * 									kCellCount.
		 * @param 		  	kInterfaceEnd  	The K index of the ending interface taken from zero to
		 * 									kCellCount.
		 * @param 		  	patchIndex	   	The index of the patch. It is generally zero.
		 * @param [in,out]	parameters	   	It must be pre allocated with a size of
		 * 									getXyzPointCountOfKInterfaceOfPatch * (kInterfaceEnd -
		 * 									kInterfaceStart + 1).
		 */
		DLL_IMPORT_OR_EXPORT void getParametersOfNodesOfKInterfaceSequenceOfPatch(unsigned int kInterfaceStart, unsigned int kInterfaceEnd, unsigned int patchIndex, double * parameters);

		/**
		 * Set the geometry of the IJK grid as parametric pillar nodes where no pillar is splitted.
		 * Defined pillars are deduced from pillarKind == -1;
		 *
		 * @param 		  	mostComplexPillarGeometry	 	The most complex pillar shape which we can
		 * 													find on this ijk grid.
		 * @param 		  	isRightHanded				 	Indicates that the IJK grid is right handed,
		 * 													as determined by the triple product of
		 * 													tangent vectors in the I, J, and K directions.
		 * @param [in,out]	parameters					 	The parameter values (regarding the pillars)
		 * 													of each node of the grid.
		 * @param [in,out]	controlPoints				 	The control points of the pillars of the
		 * 													grid. They are ordered first (quickest) by
		 * 													pillar and then (slowest) by control point :
		 * 													cp0 of pillar0, cp0 of pillar1, cp0 of
		 * 													pillar3, ..., cp0 of pillarCount-1, cp1 of
		 * 													pillar0, cp1 of pillar1, etc... Pad with nan
		 * 													values if necessary.
		 * @param [in,out]	controlPointParameters		 	The value of the parameter at each control
		 * 													points. It must be nullptr for vertical and Z
		 * 													linear cubic parametric lines grid.
		 * @param 		  	controlPointMaxCountPerPillar	The maximum count of control points which
		 * 													defines a pillar of this grid.
		 * @param [in,out]	pillarKind					 	The kind of each pillar : 0 = vertical, 1 =
		 * 													linear spline, 2 = natural cubic spline, 3 =
		 * 													cubic spline, 4 = Z linear cubic spline, 5 =
		 * 													minimum-curvature spline, (-1) = null: no
		 * 													line.
		 * @param [in,out]	proxy						 	(Optional) The Hdf proxy where all numerical
		 * 													values will be stored.
		 * @param [in,out]	localCrs					 	(Optional) The count of split coordinate line
		 * 													in this grid. A pillar being splitted by a
		 * 													maximum of 3 split coordinate lines (one
		 * 													coordinate line is always non splitted)
		 */
		DLL_IMPORT_OR_EXPORT void setGeometryAsParametricNonSplittedPillarNodes(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, bool isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, unsigned int controlPointMaxCountPerPillar, short * pillarKind,
			COMMON_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		/**
		 * Same as setGeometryAsParametricNonSplittedPillarNodes where the hdf datasets are already
		 * written in the the file.
		 *
		 * @param 		  	mostComplexPillarGeometry	 	The most complex pillar geometry.
		 * @param 		  	kDirectionKind				 	The direction kind.
		 * @param 		  	isRightHanded				 	True if is right handed, false if not.
		 * @param 		  	parameters					 	Options for controlling the operation.
		 * @param 		  	controlPoints				 	The control points.
		 * @param 		  	controlPointParameters		 	Options for controlling the control point.
		 * @param 		  	controlPointMaxCountPerPillar	The control point maximum count per pillar.
		 * @param 		  	pillarKind					 	The pillar kind.
		 * @param 		  	definedPillars				 	The string to an hdf dataset where the
		 * 													defined pillars are identified : 0 value for
		 * 													not defined (i.e control points are NaN
		 * 													points, i.e pillarKind == -1) else the pillar
		 * 													is defined. This information overrides any
		 * 													pillar geometry information.
		 * @param [in,out]	proxy						 	(Optional) If non-null, the proxy.
		 * @param [in,out]	localCrs					 	(Optional) If non-null, the local crs.
		 */
		DLL_IMPORT_OR_EXPORT void setGeometryAsParametricNonSplittedPillarNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars,
			COMMON_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		/**
		 * Set the geometry of the IJK grid as parametric pillar nodes where at least one pillar is
		 * supposed to be splitted Defined pillars are deduced from pillarKind == -1;
		 *
		 * @param 		  	mostComplexPillarGeometry					The most complex pillar shape
		 * 																which we can find on this ijk grid.
		 * @param 		  	isRightHanded								Indicates that the IJK grid is
		 * 																right handed, as determined by the
		 * 																triple product of tangent vectors in
		 * 																the I, J, and K directions.
		 * @param [in,out]	parameters									The parameter values (regarding
		 * 																the pillars) of each node of the grid.
		 * @param [in,out]	controlPoints								The control points of the pillars
		 * 																of the grid. They are ordered first
		 * 																(quickest) by pillar and then
		 * 																(slowest) by control point : cp0 of
		 * 																pillar0, cp0 of pillar1, cp0 of
		 * 																pillar3, ..., cp0 of pillarCount-1,
		 * 																cp1 of pillar0, cp1 of pillar1,
		 * 																etc... Pad with nan values if
		 * 																necessary.
		 * @param [in,out]	controlPointParameters						The value of the parameter at
		 * 																each control points. It must be
		 * 																nullptr for vertical and Z linear
		 * 																cubic parametric lines grid.
		 * @param 		  	controlPointMaxCountPerPillar				The maximum count of control
		 * 																points which defines a pillar of this
		 * 																grid.
		 * @param [in,out]	pillarKind									The kind of each pillar : 0 =
		 * 																vertical, 1 = linear spline, 2 =
		 * 																natural cubic spline, 3 = cubic
		 * 																spline, 4 = Z linear cubic spline, 5
		 * 																= minimum-curvature spline, (-1) =
		 * 																null: no line.
		 * @param [in,out]	proxy										The Hdf proxy where all numerical
		 * 																values will be stored.
		 * @param 		  	splitCoordinateLineCount					The count of split coordinate
		 * 																line in this grid. A pillar being
		 * 																splitted by a maximum of 3 split
		 * 																coordinate lines (one coordinate line
		 * 																is always non splitted)
		 * @param [in,out]	pillarOfCoordinateLine						For each split coordinate line,
		 * 																indicates the pillar it belongs to.
		 * @param [in,out]	splitCoordinateLineColumnCumulativeCount	For each split coordinate line,
		 * 																indicates the count of grid column
		 * 																which are splitted by this coordinate
		 * 																line.
		 * @param [in,out]	splitCoordinateLineColumns					For each split coordinate line,
		 * 																indicates the grid columns which are
		 * 																splitted by this coordinate line.
		 * @param [in,out]	localCrs									(Optional) If non-null, the local
		 * 																crs.
		 */
		DLL_IMPORT_OR_EXPORT void setGeometryAsParametricSplittedPillarNodes(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, bool isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, unsigned int controlPointMaxCountPerPillar, short * pillarKind, COMMON_NS::AbstractHdfProxy* proxy,
			unsigned long splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
			unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		/**
		 * Same as setGeometryAsParametricSplittedPillarNodes where the hdf datasets are already written
		 * in the the file.
		 *
		 * @param 		  	mostComplexPillarGeometry					The most complex pillar geometry.
		 * @param 		  	kDirectionKind								The direction kind.
		 * @param 		  	isRightHanded								True if is right handed, false if
		 * 																not.
		 * @param 		  	parameters									Options for controlling the
		 * 																operation.
		 * @param 		  	controlPoints								The control points.
		 * @param 		  	controlPointParameters						Options for controlling the
		 * 																control point.
		 * @param 		  	controlPointMaxCountPerPillar				The control point maximum count
		 * 																per pillar.
		 * @param 		  	pillarKind									The pillar kind.
		 * @param 		  	definedPillars								The string to an hdf dataset
		 * 																where the defined pillars are
		 * 																identified : 0 value for not defined
		 * 																(i.e control points are NaN points,
		 * 																i.e pillarKind == -1) else the pillar
		 * 																is defined.  This information
		 * 																overrides any pillar geometry
		 * 																information.
		 * @param [in,out]	proxy										If non-null, the proxy.
		 * @param 		  	splitCoordinateLineCount					Number of split coordinate lines.
		 * @param 		  	pillarOfCoordinateLine						The pillar of coordinate line.
		 * @param 		  	splitCoordinateLineColumnCumulativeCount	Number of split coordinate line
		 * 																column cumulatives.
		 * @param 		  	splitCoordinateLineColumns					The split coordinate line columns.
		 * @param [in,out]	localCrs									(Optional) If non-null, the local
		 * 																crs.
		 */
		DLL_IMPORT_OR_EXPORT void setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars, COMMON_NS::AbstractHdfProxy* proxy,
			unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		/**
		 * Set the geometry of the IJK grid as parametric pillar nodes where at least one pillar is
		 * supposed to be splitted and where all pillars are of the same kind. All pillars are assumed
		 * to be defined using this method.
		 *
		 * @param 		  	isRightHanded								Indicates that the IJK grid is
		 * 																right handed, as determined by the
		 * 																triple product of tangent vectors in
		 * 																the I, J, and K directions.
		 * @param 		  	parameters									The parameter values (regarding
		 * 																the pillars) of each node of the grid.
		 * @param 		  	controlPoints								The control points of the pillars
		 * 																of the grid. They are ordered first
		 * 																(quickest) by pillar and then
		 * 																(slowest) by control point : cp0 of
		 * 																pillar0, cp0 of pillar1, cp0 of
		 * 																pillar3, ..., cp0 of pillarCount-1,
		 * 																cp1 of pillar0, cp1 of pillar1,
		 * 																etc... Pad with nan values if
		 * 																necessary.
		 * @param 		  	controlPointParameters						The value of the parameter at
		 * 																each control points. It must be
		 * 																nullptr for vertical and Z linear
		 * 																cubic parametric lines grid.
		 * @param 		  	controlPointCountPerPillar					The count of control points which
		 * 																defines each of the pillar of this
		 * 																grid.
		 * @param 		  	pillarKind									The constant kind of each pillar
		 * 																: 0 = vertical, 1 = linear spline, 2
		 * 																= natural cubic spline, 3 = cubic
		 * 																spline, 4 = Z linear cubic spline, 5
		 * 																= minimum-curvature spline, (-1) =
		 * 																null: no line.
		 * @param [in,out]	proxy										The Hdf proxy where all numerical
		 * 																values will be stored.
		 * @param 		  	splitCoordinateLineCount					The count of split coordinate
		 * 																line in this grid. A pillar being
		 * 																splitted by a maximum of 3 split
		 * 																coordinate lines (one coordinate line
		 * 																is always non splitted)
		 * @param 		  	pillarOfCoordinateLine						For each split coordinate line,
		 * 																indicates the pillar it belongs to.
		 * @param 		  	splitCoordinateLineColumnCumulativeCount	For each split coordinate line,
		 * 																indicates the count of grid column
		 * 																which are splitted by this coordinate
		 * 																line.
		 * @param 		  	splitCoordinateLineColumns					For each split coordinate line,
		 * 																indicates the grid columns which are
		 * 																splitted by this coordinate line.
		 * @param [in,out]	localCrs									(Optional) If non-null, the local
		 * 																crs.
		 */
		DLL_IMPORT_OR_EXPORT void setGeometryAsParametricSplittedPillarNodes(bool isRightHanded,
			double const * parameters, double const * controlPoints, double const * controlPointParameters, unsigned int controlPointCountPerPillar, short pillarKind, COMMON_NS::AbstractHdfProxy* proxy,
			unsigned long splitCoordinateLineCount, unsigned int const * pillarOfCoordinateLine,
			unsigned int const * splitCoordinateLineColumnCumulativeCount, unsigned int const * splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		/**
		 * Same as setGeometryAsParametricSplittedPillarNodes where the hdf datasets are already written
		 * in the the file.
		 *
		 * @param 		  	kDirectionKind								The direction kind.
		 * @param 		  	isRightHanded								True if is right handed, false if
		 * 																not.
		 * @param 		  	parameters									Options for controlling the
		 * 																operation.
		 * @param 		  	controlPoints								The control points.
		 * @param 		  	controlPointParameters						Options for controlling the
		 * 																control point.
		 * @param 		  	controlPointCountPerPillar					The control point count per
		 * 																pillar.
		 * @param 		  	pillarKind									The pillar kind.
		 * @param [in,out]	proxy										If non-null, the proxy.
		 * @param 		  	splitCoordinateLineCount					Number of split coordinate lines.
		 * @param 		  	pillarOfCoordinateLine						The pillar of coordinate line.
		 * @param 		  	splitCoordinateLineColumnCumulativeCount	Number of split coordinate line
		 * 																column cumulatives.
		 * @param 		  	splitCoordinateLineColumns					The split coordinate line columns.
		 * @param [in,out]	localCrs									(Optional) If non-null, the local
		 * 																crs.
		 */
		DLL_IMPORT_OR_EXPORT void setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointCountPerPillar, short pillarKind, COMMON_NS::AbstractHdfProxy* proxy,
			unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		/**
		 * Check wether the node geometry dataset is compressed or not.
		 *
		 * @returns	True if node geometry compressed, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isNodeGeometryCompressed() const;

		/**
		 * Gets geometry kind
		 *
		 * @returns	The geometry kind.
		 */
		DLL_IMPORT_OR_EXPORT geometryKind getGeometryKind() const;
	};
}
