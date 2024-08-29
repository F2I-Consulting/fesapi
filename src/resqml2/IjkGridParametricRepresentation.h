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
	 * @brief	An IJK Grid parametric representation define the cell corner positions by means of
	 * 			parameters along the pillars of the grid. Adjacent cell corner are supposed to be
	 * 			located the same so they are not repeated unless you define split lines or split
	 * 			nodes.
	 */
	class IjkGridParametricRepresentation : public AbstractIjkGridRepresentation
	{	
	public:
		/**
		* Destructor cleans the pillars information memory if allocated.
		*/
		DLL_IMPORT_OR_EXPORT virtual ~IjkGridParametricRepresentation() {}

		DLL_IMPORT_OR_EXPORT void getXyzPointsOfKInterfaceSequence(unsigned int kInterfaceStart, unsigned int kInterfaceEnd, double * xyzPoints) final;

		/**
		* @copybrief AbstractIjkGridRepresentation::getXyzPointsOfBlock
		* 			 
		* @exception std::logic_error If the computing of XYZ points is not yet supported from this parametric grid.
		* 							  
		* @copydetails AbstractIjkGridRepresentation::getXyzPointsOfBlock
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfBlock(double * xyzPoints) final;

		/**
		 * Gets the maximum control points count on a pillar of this grid.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this grid.
		 * @exception	std::range_error	 	If the knot count of this grid is strictly greater than
		 * 										unsigned int max.
		 * @exception	std::logic_error	 	If the computing of the maximum control points count is
		 * 										not yet supported for this grid.
		 *
		 * @returns	The maximum control points count on a pillar of this grid.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getControlPointMaxCountPerPillar() const = 0;

		/**
		 * Gets all the control points of each pillar of this IJK parametric grid.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this grid.
		 * @exception	std::range_error	 	If the knot count of this grid is strictly greater than
		 * 										unsigned int max.
		 * @exception	std::logic_error	 	If the reading of the control points of this grid is not
		 * 										supported yet.
		 *
		 * @param [out]	controlPoints	An array for receiving the control points. It must be
		 * 								preallocated with a size of <tt>(getICellCount() + 1) *
		 * 								(getJCellCount() + 1) * getControlPointMaxCountPerPillar() *
		 * 								3</tt>. They are ordered first (quickest) by pillar and then
		 * 								(slowest) by control point : cp0 of pillar0, cp0 of pillar1, cp0
		 * 								of pillar3, ..., cp0 of pillarCount-1, cp1 of pillar0, cp1 of
		 * 								pillar1, etc... Pad with nan values if necessary. For information,
		 * 								pillars are ordered first (quicket) by I and then (slowest) by J.
		 * @param 	   	reverseIAxis 	(Optional) True to reverse i axis. Default value is false.
		 * @param 	   	reverseJAxis 	(Optional) True to reverse j axis. Default value is false.
		 * @param 	   	reverseKAxis 	(Optional) True to reverse k axis. Default value is false.
		 */
		DLL_IMPORT_OR_EXPORT void getControlPoints(double * controlPoints, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		/**
		 * Checks if this IJK parametric grid contains some parameters on some control points. It
		 * happens when the grid contains at least one non vertical or a non Z linear parametric line.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this grid.
		 * @exception	std::logic_error	 	If the checking for the existance of control point
		 * 										parameters is not yet supported for this grid.
		 *
		 * @returns	True if there exists some control point parameters, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool hasControlPointParameters() const = 0;

		/**
		 * Gets all the control point parameters of each pillar of this IJK parametric grid.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this grid.
		 * @exception	std::range_error	 	If the knot count of this grid is strictly greater than
		 * 										unsigned int max.
		 * @exception	std::logic_error	 	If the reading of the control point parameters of this
		 * 										grid is not supported yet.
		 *
		 * @param [out]	controlPointParameters	An array for receiving the control point parameters. It
		 * 										must be preallocated with a size of
		 * 										<tt>(getICellCount()</tt>
		 * 										<tt> + 1) *	(getJCellCount() + 1) * </tt>
		 * 										<tt>getControlPointMaxCountPerPillar()</tt>. They are
		 * 										ordered
		 * 										first (quickest) by pillar and then (slowest) by control
		 * 										point : cp0 of pillar0, cp0 of pillar1, cp0 of pillar3,
		 * 										..., cp0 of pillarCount-1, cp1 of pillar0, cp1 of pillar1,
		 * 										etc... Pad with nan values if necessary. For information,
		 * 										pillars are ordered first (quicket) by I and then
		 * 										(slowest) by J. Only relevant in case it contains at
		 * 										least one non vertical or non Z linear parametric line.
		 * @param 	   	reverseIAxis		  	(Optional) True to reverse i axis. Default value is false.
		 * @param 	   	reverseJAxis		  	(Optional) True to reverse j axis. Default value is false.
		 * @param 	   	reverseKAxis		  	(Optional) True to reverse k axis. Default value is false.
		 */
		DLL_IMPORT_OR_EXPORT void getControlPointParameters(double * controlPointParameters, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		/**
		 * Checks if the parametric lines kind is constant in this IJK parametric grid.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this grid.
		 * @exception	std::logic_error	 	If this grid is not actually a parametric one or if the
		 * 										checking for the parametric lines kind constantness is
		 * 										not supported yet for this grid.
		 *
		 * @returns	True if the parametric lines kind is constant, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isParametricLineKindConstant() const = 0;

		/**
		 * Gets the constant parametric line kind of this IJK parametric grid.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this grid.
		 * @exception	std::logic_error	 	If this grid is not actually a parametric one or if the
		 * 										getting of the constant parametric line kind is not
		 * 										supported yet for this grid.
		 *
		 * @returns	The constant parametric line kind.
		 */
		DLL_IMPORT_OR_EXPORT virtual short getConstantParametricLineKind() const = 0;

		/**
		 * Gets the kind of each parametric line representing a pillar.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this grid.
		 * @exception	std::invalid_argument	If the parametric line kind count is inconsistent with
		 * 										the pillar count.
		 * 										@€xception std::logic_error If getting the parametric
		 * 										lines kind is not yet supported for this grid.
		 *
		 * @param [out]	pillarKind  	An array for receiving the parametric lines kind. It must be
		 * 								preallocated with a size of <tt>(getICellCount() + 1) *
		 * 								(getJCellCount() + 1)</tt>. Semantic of values is: 0 = vertical, 1 =
		 * 								linear spline, 2 = natural cubic spline, 3 = cubic spline, 4 = Z
		 * 								linear cubic spline, 5 = minimum-curvature spline, (-1) = null: no
		 * 								line.
		 * @param 	   	reverseIAxis	(Optional) True to reverse i axis. Default value is false.
		 * @param 	   	reverseJAxis	(Optional) True to reverse j axis. Default value is false.
		 */
		DLL_IMPORT_OR_EXPORT void getParametricLineKind(int16_t* pillarKind, bool reverseIAxis = false, bool reverseJAxis = false) const;

		/**
		 * Gets all the parameters of each node of this IJK parametric grid. They are ordered first
		 * (quickest) by coordinate line and then (slowest) by K level.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this IJK grid.
		 * @exception	std::range_error	 	If the count of split coordinate lines is strictly
		 * 										greater than unsigned int max.
		 * @exception	std::logic_error	 	If the reading of nodes parameters is not yet supported
		 * 										for this grid.
		 *
		 * @param [out]	parameters  	An array for receiving the parameter of each node. It must be
		 * 								preallocated with a size of <tt>((getICellCount() + 1) *
		 * 								(getJCellCount() + 1) + getSplitCoordinateLineCount()) *
		 * 								(getKCellCount() + 1)</tt>. They are ordered first (quickest) by
		 * 								coordinate line and then (slowest) by K level.
		 * @param 	   	reverseIAxis	(Optional) True to reverse i axis. Default value is false.
		 * @param 	   	reverseJAxis	(Optional) True to reverse j axis. Default value is false.
		 * @param 	   	reverseKAxis	(Optional) True to reverse k axis. Default value is false.
		 */
		DLL_IMPORT_OR_EXPORT void getParametersOfNodes(double * parameters, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		/**
		 * Gets all the parameters of each node of a particular sequence of K interfaces of this IJK
		 * parametric grid.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this IJK grid.
		 * @exception	std::logic_error	 	If the reading of nodes parameters is not yet supported
		 * 										for this sequence of K interfaces.
		 * @exception	std::out_of_range	 	If <tt>kInterfaceStart &gt; getKCellCount() ||
		 * 										kInterfaceEnd &gt; getKCellCount())</tt>.
		 * @exception	std::range_error	 	If <tt>kInterfaceStart &gt; kInterfaceEnd</tt>
		 * @exception	std::invalid_argument	If @p parameters is @c nullptr.
		 *
		 * @param 	   	kInterfaceStart	The K index of the starting interface taken from zero to
		 * 								getKCellCount().
		 * @param 	   	kInterfaceEnd  	The K index of the ending interface taken from zero to
		 * 								getKCellCount().
		 * @param [out]	parameters	   	An array for receiving the parameter of each node. It must be pre
		 * 								allocated with a size of
		 * 								<tt>getXyzPointCountOfKInterface() * (kInterfaceEnd -
		 * 								kInterfaceStart + 1)</tt>. They are ordered first (quickest) by
		 * 								coordinate line and then (slowest) by K level.
		 */
		DLL_IMPORT_OR_EXPORT void getParametersOfNodesOfKInterfaceSequence(unsigned int kInterfaceStart, unsigned int kInterfaceEnd, double * parameters);

		/**
		 * Sets the geometry of this IJK grid as parametric pillar nodes where no pillar is splitted.
		 * Defined pillars are deduced from pillarKind == -1.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this grid.
		 * @exception	std::invalid_argument 	If some parameters values are inconsistent.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p localCrs is @c nullptr and no default local 3d CRS
		 * 										is defined.
		 *
		 * @param 		  	mostComplexPillarGeometry	 	The most complex pillar shape which we can
		 * 													find on this IJK grid.
		 * @param 		  	isRightHanded				 	Indicates that this IJK grid is right handed,
		 * 													as determined by the triple product of
		 * 													tangent vectors in the I, J, and K directions.
		 * @param [in]	  	parameters					 	The parameter values (regarding the pillars)
		 * 													of each node of the grid.
		 * @param [in]	  	controlPoints				 	The control points of the pillars of the
		 * 													grid. They are ordered first (quickest) by
		 * 													pillar and then (slowest) by control point :
		 * 													cp0 of pillar0, cp0 of pillar1, cp0 of
		 * 													pillar3, ..., cp0 of pillarCount-1, cp1 of
		 * 													pillar0, cp1 of pillar1, etc... Pad with nan
		 * 													values if necessary.
		 * @param [in]	  	controlPointParameters		 	The value of the parameter at each control
		 * 													points. It must be @c nullptr for vertical
		 * 													and Z linear cubic parametric lines grid.
		 * @param 		  	controlPointMaxCountPerPillar	The maximum count of control points which
		 * 													defines a pillar of this grid.
		 * @param [in]	  	pillarKind					 	The kind of each pillar: 0 = vertical, 1 =
		 * 													linear spline, 2 = natural cubic spline, 3 =
		 * 													cubic spline, 4 = Z linear cubic spline, 5 =
		 * 													minimum-curvature spline, (-1) = null: no
		 * 													line.
		 * @param [in,out]	proxy						 	(Optional) The HDF proxy where all numerical
		 * 													values will be stored. If @c nullptr
		 * 													(default), then the default HDF proxy of the
		 * 													repository will be used.
		 * @param [in]	  	localCrs					 	(Optional) The local CRS where the points are
		 * 													given. If @c nullptr (default) then the
		 * 													default CRS of the repository will be used.
		 */
		DLL_IMPORT_OR_EXPORT void setGeometryAsParametricNonSplittedPillarNodes(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, bool isRightHanded,
			double const * parameters, double const * controlPoints, double const * controlPointParameters, unsigned int controlPointMaxCountPerPillar, short const * pillarKind,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		/**
		 * Sets the geometry of this IJK grid as parametric pillar nodes where no pillar is splitted.
		 * Defined pillars are deduced from pillarKind == -1. Same as
		 * setGeometryAsParametricNonSplittedPillarNodes() where the HDF datasets are already written in
		 * the the file.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this grid.
		 * @exception	std::invalid_argument	If some parameters values are inconsistent.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p localCrs is @c nullptr and no default local 3d CRS
		 * 										is defined.
		 *
		 * @param 		  	mostComplexPillarGeometry	 	The most complex pillar shape which we can
		 * 													find on this IJK grid.
		 * @param 		  	kDirectionKind				 	The K direction kind.
		 * @param 		  	isRightHanded				 	Indicates that this IJK grid is right handed,
		 * 													as determined by the triple product of
		 * 													tangent vectors in the I, J, and K directions.
		 * @param 		  	parameters					 	Path to the HDF dataset containing the
		 * 													parameter values (regarding the pillars)
		 * 													of each node of the grid.
		 * @param 		  	controlPoints				 	Path to the HDF dataset containing the the
		 * 													control points of the pillars of the grid.
		 * @param 		  	controlPointParameters		 	Path to the HDF dataset containing the value
		 * 													of the parameter at each control points.
		 * @param 		  	controlPointMaxCountPerPillar	The maximum count of control points which
		 * 													defines a pillar of this grid.
		 * @param 		  	pillarKind					 	Path to the HDF dataset containing the kind
		 * 													of each pillar.
		 * @param 		  	definedPillars				 	Path to the HDF dataset where the defined
		 * 													pillars are identified : 0 value for not
		 * 													defined (i.e control points are NaN points,
		 * 													i.e pillarKind == -1) else the pillar is
		 * 													defined. This information overrides any
		 * 													pillar geometry information.
		 * @param [in,out]	proxy						 	(Optional) The HDF proxy where all numerical
		 * 													values will be stored. If @c nullptr
		 * 													(default), then the default HDF proxy of the
		 * 													repository will be used.
		 * @param [in]	  	localCrs					 	(Optional) The local CRS where the points are
		 * 													given. If @c nullptr (default) then the
		 * 													default CRS of the repository will be used.
		 */
		DLL_IMPORT_OR_EXPORT void setGeometryAsParametricNonSplittedPillarNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		/**
		 * Sets the geometry of this IJK grid as parametric pillar nodes where at least one pillar is
		 * supposed to be splitted. Defined pillars are deduced from pillarKind == -1.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this grid.
		 * @exception	std::invalid_argument	If some parameters values are inconsistent.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p localCrs is @c nullptr and no default local 3d CRS
		 * 										is defined.
		 *
		 * @param 		  	mostComplexPillarGeometry					The most complex pillar shape
		 * 																which we can find on this ijk grid.
		 * @param 		  	isRightHanded								Indicates that the IJK grid is
		 * 																right handed, as determined by the
		 * 																triple product of tangent vectors in
		 * 																the I, J, and K directions.
		 * @param [in]	  	parameters									The parameter values (regarding
		 * 																the pillars) of each node of the
		 * 																grid.
		 * @param [in]	  	controlPoints								The control points of the pillars
		 * 																of the grid. They are ordered first
		 * 																(quickest) by pillar and then
		 * 																(slowest) by control point : cp0 of
		 * 																pillar0, cp0 of pillar1, cp0 of
		 * 																pillar3, ..., cp0 of pillarCount-1,
		 * 																cp1 of pillar0, cp1 of pillar1,
		 * 																etc... Pad with nan values if
		 * 																necessary.
		 * @param [in]	  	controlPointParameters						The value of the parameter at
		 * 																each control points. It must be
		 * 																nullptr for vertical and Z linear
		 * 																cubic parametric lines grid.
		 * @param 		  	controlPointMaxCountPerPillar				The maximum count of control
		 * 																points which defines a pillar of this
		 * 																grid.
		 * @param [in]	  	pillarKind									The kind of each pillar : 0 =
		 * 																vertical, 1 = linear spline, 2 =
		 * 																natural cubic spline, 3 = cubic
		 * 																spline, 4 = Z linear cubic spline, 5
		 * 																= minimum-curvature spline, (-1) =
		 * 																null: no line.
		 * @param [in,out]	proxy										The HDF proxy where all numerical
		 * 																values will be stored. If @c nullptr,
		 * 																then the default HDF proxy of the
		 * 																repository will be used.
		 * @param 		  	splitCoordinateLineCount					The count of split coordinate
		 * 																line in this grid. A pillar being
		 * 																splitted by a maximum of 3 split
		 * 																coordinate lines (one coordinate line
		 * 																is always non splitted)
		 * @param [in]	  	pillarOfCoordinateLine						For each split coordinate line,
		 * 																indicates the pillar it belongs to.
		 * @param [in]	  	splitCoordinateLineColumnCumulativeCount	For each split coordinate line,
		 * 																indicates the count of grid column
		 * 																which are splitted by this
		 * 																coordinate line.
		 * @param [in]	  	splitCoordinateLineColumns					For each split coordinate line,
		 * 																indicates the grid columns which are
		 * 																splitted by this coordinate line.
		 * @param [in]	  	localCrs									(Optional) The local CRS where
		 * 																the points are given. If @c nullptr
		 * 																(default) then the default CRS of the
		 * 																repository will be used.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setGeometryAsParametricSplittedPillarNodes(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, bool isRightHanded,
			double const * parameters, double const * controlPoints, double const * controlPointParameters, unsigned int controlPointMaxCountPerPillar, short const * pillarKind, EML2_NS::AbstractHdfProxy* proxy,
			uint64_t splitCoordinateLineCount, unsigned int const * pillarOfCoordinateLine,
			unsigned int const * splitCoordinateLineColumnCumulativeCount, unsigned int const * splitCoordinateLineColumns, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr) = 0;

		/**
		 * Sets the geometry of this IJK grid as parametric pillar nodes where at least one pillar is
		 * supposed to be splitted. Defined pillars are deduced from pillarKind == -1. Same as
		 * setGeometryAsParametricSplittedPillarNodes() where the HDF datasets are already written in
		 * the the file.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this grid.
		 * @exception	std::invalid_argument	If some parameters values are inconsistent.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p localCrs is @c nullptr and no default local 3d CRS
		 * 										is defined.
		 *
		 * @param 		  	mostComplexPillarGeometry					The most complex pillar shape
		 * 																which we can find on this ijk grid.
		 * @param 		  	kDirectionKind								The direction kind.
		 * @param 		  	isRightHanded								Indicates that the IJK grid is
		 * 																right handed, as determined by the
		 * 																triple product of tangent vectors in
		 * 																the I, J, and K directions.
		 * @param 		  	parameters									Path to the HDF dataset
		 * 																containing the parameter values
		 * 																(regarding the pillars)
		 * 																of each node of the grid.
		 * @param 		  	controlPoints								Path to the HDF dataset
		 * 																containing the the control points of
		 * 																the pillars of the grid.
		 * @param 		  	controlPointParameters						Path to the HDF dataset
		 * 																containing the value of the parameter
		 * 																at each control points.
		 * @param 		  	controlPointMaxCountPerPillar				The maximum count of control
		 * 																points which defines a pillar of this
		 * 																grid.
		 * @param 		  	pillarKind									Path to the HDF dataset
		 * 																containing the kind of each pillar.
		 * @param 		  	definedPillars								Path to the HDF dataset where the
		 * 																defined pillars are identified : 0
		 * 																value for not defined (i.e control
		 * 																points are NaN points,
		 * 																i.e pillarKind == -1) else the pillar
		 * 																is defined.  This information
		 * 																overrides any pillar geometry
		 * 																information.
		 * @param [in,out]	proxy										The HDF proxy where all numerical
		 * 																values will be stored. If @c nullptr,
		 * 																then the default HDF proxy of the
		 * 																repository will be used.
		 * @param 		  	splitCoordinateLineCount					The count of split coordinate
		 * 																line in this grid. A pillar being
		 * 																splitted by a maximum of 3 split
		 * 																coordinate lines (one coordinate line
		 * 																is always non splitted)
		 * @param 		  	pillarOfCoordinateLine						Path to the HDF dataset
		 * 																indicating for each split coordinate
		 * 																line, which pillar it belongs to.
		 * @param 		  	splitCoordinateLineColumnCumulativeCount	Path to the HDF dataset
		 * 																indicating for each split coordinate
		 * 																line, the count of grid column which
		 * 																are splitted by this coordinate line.
		 * @param 		  	splitCoordinateLineColumns					Path to the HDF dataset
		 * 																indicating for each split coordinate
		 * 																line, the grid columns which are
		 * 																splitted by this coordinate line.
		 * @param [in]	  	localCrs									(Optional) The local CRS where
		 * 																the points are given. If @c nullptr
		 * 																(default) then the default CRS of the
		 * 																repository will be used.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars, EML2_NS::AbstractHdfProxy* proxy,
			uint64_t splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr) = 0;

		/**
		 * Set the geometry of the IJK grid as parametric pillar nodes where at least one pillar is
		 * supposed to be splitted and where all pillars are of the same kind. All pillars are assumed
		 * to be defined using this method.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this grid.
		 * @exception	std::invalid_argument	If some parameters values are inconsistent.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p localCrs is @c nullptr and no default local 3d CRS
		 * 										is defined.
		 *
		 * @param 		  	isRightHanded								Indicates that the IJK grid is
		 * 																right handed, as determined by the
		 * 																triple product of tangent vectors in
		 * 																the I, J, and K directions.
		 * @param [in]	  	parameters									The parameter values (regarding
		 * 																the pillars) of each node of the grid.
		 * @param [in]	  	controlPoints								The control points of the pillars
		 * 																of the grid. They are ordered first
		 * 																(quickest) by pillar and then
		 * 																(slowest) by control point : cp0 of
		 * 																pillar0, cp0 of pillar1, cp0 of
		 * 																pillar3, ..., cp0 of pillarCount-1,
		 * 																cp1 of pillar0, cp1 of pillar1,
		 * 																etc... Pad with nan values if
		 * 																necessary.
		 * @param [in]	  	controlPointParameters						The value of the parameter at
		 * 																each control points. It must be
		 * 																nullptr for vertical and Z linear
		 * 																cubic parametric lines grid.
		 * @param 		  	controlPointCountPerPillar					The maximum count of control
		 * 																points which defines a pillar of this
		 * 																grid.
		 * @param 		  	pillarKind									The constant kind of each pillar
		 * 																: 0 = vertical, 1 = linear spline, 2
		 * 																= natural cubic spline, 3 = cubic
		 * 																spline, 4 = Z linear cubic spline, 5
		 * 																= minimum-curvature spline, (-1) =
		 * 																null: no line.
		 * @param [in,out]	proxy										The HDF proxy where all numerical
		 * 																values will be stored. If @c nullptr,
		 * 																then the default HDF proxy of the
		 * 																repository will be used.
		 * @param 		  	splitCoordinateLineCount					The count of split coordinate
		 * 																line in this grid. A pillar being
		 * 																splitted by a maximum of 3 split
		 * 																coordinate lines (one coordinate line
		 * 																is always non splitted)
		 * @param [in]	  	pillarOfCoordinateLine						For each split coordinate line,
		 * 																indicates the pillar it belongs to.
		 * @param [in]	  	splitCoordinateLineColumnCumulativeCount	For each split coordinate line,
		 * 																indicates the count of grid column
		 * 																which are splitted by this coordinate
		 * 																line.
		 * @param [in]	  	splitCoordinateLineColumns					For each split coordinate line,
		 * 																indicates the grid columns which are
		 * 																splitted by this coordinate line.
		 * @param [in]	  	localCrs									(Optional) The local CRS where
		 * 																the points are given. If @c nullptr
		 * 																(default) then the default CRS of the
		 * 																repository will be used.
		 */
		DLL_IMPORT_OR_EXPORT void setGeometryAsParametricSplittedPillarNodes(bool isRightHanded,
			double const * parameters, double const * controlPoints, double const * controlPointParameters, unsigned int controlPointCountPerPillar, short pillarKind, EML2_NS::AbstractHdfProxy* proxy,
			uint64_t splitCoordinateLineCount, unsigned int const * pillarOfCoordinateLine,
			unsigned int const * splitCoordinateLineColumnCumulativeCount, unsigned int const * splitCoordinateLineColumns, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		/**
		 * Set the geometry of the IJK grid as parametric pillar nodes where at least one pillar is
		 * supposed to be splitted and where all pillars are of the same kind. All pillars are assumed
		 * to be defined using this method.Same as setGeometryAsParametricSplittedPillarNodes where the
		 * HDF datasets are already written in the the file.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this grid.
		 * @exception	std::invalid_argument	If some parameters values are inconsistent.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p localCrs is @c nullptr and no default local 3d CRS
		 * 										is defined.
		 *
		 * @param 		  	kDirectionKind								The K direction kind.
		 * @param 		  	isRightHanded								Indicates that the IJK grid is
		 * 																right handed, as determined by the
		 * 																triple product of tangent vectors in
		 * 																the I, J, and K directions.
		 * @param 		  	parameters									Path to the HDF dataset
		 * 																containing the parameter values
		 * 																(regarding the pillars)
		 * 																of each node of the grid.
		 * @param 		  	controlPoints								Path to the HDF dataset
		 * 																containing the the control points of
		 * 																the pillars of the grid.
		 * @param 		  	controlPointParameters						Path to the HDF dataset
		 * 																containing the value of the parameter
		 * 																at each control points.
		 * @param 		  	controlPointCountPerPillar					The maximum count of control
		 * 																points which defines a pillar of this
		 * 																grid.
		 * @param 		  	pillarKind									The constant kind of each pillar
		 * 																: 0 = vertical, 1 = linear spline, 2
		 * 																= natural cubic spline, 3 = cubic
		 * 																spline, 4 = Z linear cubic spline, 5
		 * 																= minimum-curvature spline, (-1) =
		 * 																null: no line.
		 * @param [in,out]	proxy										The HDF proxy where all numerical
		 * 																values will be stored. If @c nullptr,
		 * 																then the default HDF proxy of the
		 * 																repository will be used.
		 * @param 		  	splitCoordinateLineCount					The count of split coordinate
		 * 																line in this grid. A pillar being
		 * 																splitted by a maximum of 3 split
		 * 																coordinate lines (one coordinate line
		 * 																is always non splitted)
		 * @param 		  	pillarOfCoordinateLine						Path to the HDF dataset
		 * 																indicating for each split coordinate
		 * 																line, which pillar it belongs to.
		 * @param 		  	splitCoordinateLineColumnCumulativeCount	Path to the HDF dataset
		 * 																indicating for each split coordinate
		 * 																line, the count of grid column which
		 * 																are splitted by this coordinate line.
		 * @param 		  	splitCoordinateLineColumns					Path to the HDF dataset
		 * 																indicating for each split coordinate
		 * 																line, the grid columns which are
		 * 																splitted by this coordinate line.
		 * @param [in]	  	localCrs									(Optional) The local CRS where
		 * 																the points are given. If @c nullptr
		 * 																(default) then the default CRS of the
		 * 																repository will be used.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointCountPerPillar, short pillarKind, EML2_NS::AbstractHdfProxy* proxy,
			uint64_t splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr) = 0;

		DLL_IMPORT_OR_EXPORT bool isNodeGeometryCompressed() const final;

		DLL_IMPORT_OR_EXPORT geometryKind getGeometryKind() const final;

	protected:
		IjkGridParametricRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount, bool* kGaps = nullptr, EML2_NS::AbstractHdfProxy* proxy = nullptr) :
			AbstractIjkGridRepresentation(repo, guid, title, iCount, jCount, kCount, kGaps, proxy) {}

		IjkGridParametricRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount, bool* kGaps = nullptr, EML2_NS::AbstractHdfProxy* proxy = nullptr) :
			AbstractIjkGridRepresentation(interp, guid, title, iCount, jCount, kCount, kGaps, proxy) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		IjkGridParametricRepresentation(gsoap_resqml2_0_1::_resqml20__IjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
		IjkGridParametricRepresentation(gsoap_eml2_3::_resqml22__IjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
		IjkGridParametricRepresentation(gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}
		IjkGridParametricRepresentation(gsoap_eml2_3::_resqml22__TruncatedIjkGridRepresentation* fromGsoap) : AbstractIjkGridRepresentation(fromGsoap) {}

		/**
		* Compute the K Direction of the gid according to its control points.
		*/
		gsoap_resqml2_0_1::resqml20__KDirection computeKDirection(double const * controlPoints, unsigned int controlPointCountPerPillar, short const * pillarKind, EML2_NS::AbstractLocal3dCrs const * localCrs);

		void writeGeometryOnHdf(double const * parameters,
			double const * controlPoints, double const * controlPointParameters, unsigned int controlPointCountPerPillar,
			uint64_t splitCoordinateLineCount, unsigned int const * pillarOfCoordinateLine,
			unsigned int const * splitCoordinateLineColumnCumulativeCount, unsigned int const * splitCoordinateLineColumns, EML2_NS::AbstractHdfProxy * proxy);

		virtual EML2_NS::AbstractHdfProxy* getParameterDatasetPath(std::string & datasetPathInExternalFile) const = 0;
		virtual EML2_NS::AbstractHdfProxy* getControlPointDatasetPath(std::string & datasetPathInExternalFile) const = 0;
		virtual EML2_NS::AbstractHdfProxy* getControlPointParametersDatasetPath(std::string & datasetPathInExternalFile) const = 0;
		virtual EML2_NS::AbstractHdfProxy* getParametersOfNodesDatasetPath(std::string & datasetPathInExternalFile) const = 0;
		virtual void getRawParametricLineKind(short * pillarKind) const = 0;
		void getXyzPointsFromParametricPoints(double * xyzPoints) const;

	private:
		/**
		* From https://en.wikipedia.org/w/index.php?title=Spline_%28mathematics%29&oldid=288288033#Algorithm_for_computing_natural_cubic_splines
		*/
		class BSpline
		{
		public:
			BSpline() {};
			BSpline(const std::vector<double>& parametersAtControlPoint, const std::vector<double>& valuesAtControlPoint);
			~BSpline() = default;

			double getValueFromParameter(double param) const;
			void setParameterAndValueAtControlPoint(const std::vector<double>& parametersAtControlPoint, const std::vector<double>& valuesAtControlPoint);

		private:

			void checkIfParametersIncreaseOrDecrease();
			std::size_t getSplineIndexFromParameter(double param) const;

			bool areParametersIncreasing;

			// basically each of set of 5 double describe a spline
			std::vector<double> a;
			std::vector<double> b;
			std::vector<double> c;
			std::vector<double> d;
			std::vector<double> parameter; //named x in the wiki link
		};

		class PillarInformation
		{
		public:
			uint32_t maxControlPointCount = 0;
			uint32_t parametricLineCount = 0;
			uint64_t splitLineCount = 0;
			std::unique_ptr<double[]> controlPoints;
			std::unique_ptr<double[]> controlPointParameters;
			std::unique_ptr<int16_t[]> pillarKind;
			std::unique_ptr<uint32_t[]> pillarOfSplitCoordLines;
			std::vector< std::vector< BSpline > > splines;

			PillarInformation() {}
		};

		/**
		* Load in pillarInformation all pillar information.
		* It allows to accelerate getter of xyz points when reading them by K interface
		*/
		void loadPillarInformation() const;

		void getXyzPointsAlongACoordinateLine(uint64_t pillarIndex, uint64_t coordLineIndex, uint64_t ijNodeCount, uint64_t kNodeCount, double const* parameters, double* xyzPoints) const;

		// Use a pointer to keep the instance of this class const when modified (i.e when computed for getting XYZ Points)
		std::unique_ptr<PillarInformation> pillarInformation{ new PillarInformation() };
	};
}
