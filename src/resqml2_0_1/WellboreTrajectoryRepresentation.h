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

#include "../resqml2/WellboreTrajectoryRepresentation.h"

/** . */
namespace RESQML2_0_1_NS
{
	/** A wellbore trajectory representation. */
	class WellboreTrajectoryRepresentation final : public RESQML2_NS::WellboreTrajectoryRepresentation
	{
	private:

		/**
		 * Gets specialized gsoap proxy
		 *
		 * @returns	Null if it fails, else the specialized gsoap proxy.
		 */
		gsoap_resqml2_0_1::_resqml20__WellboreTrajectoryRepresentation* getSpecializedGsoapProxy() const;

	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT WellboreTrajectoryRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::WellboreTrajectoryRepresentation(partialObject) {}

		/**
		 * Creates a wellbore trajectory representation.
		 *
		 * @exception	std::invalid_argument	If @p interp or @p mdInfo is @c nullptr.
		 *
		 * @param [in]	interp	The represented wellbore interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the wellbore trajectory representation. If empty then
		 * 						a new guid will be generated.
		 * @param 	  	title 	The title to set to the wellbore trajectory representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param [in]	mdInfo	The MD information of the trajectory, mainly the well reference point.
		 * 						The unit of measure used for the mdInfo coordinates must also be used for
		 * 						the start and end MD of the trajectory. It cannot be null.
		 */
		WellboreTrajectoryRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, RESQML2_NS::MdDatum* mdInfo);

		/**
		 * Creates an instance with an existing deviation survey as its origin.
		 *
		 * @exception	std::invalid_argument	If @p interp or @p deviationSurvey is @c nullptr.
		 *
		 * @param [in]	interp		   	The represented interpretation. It cannot be null.
		 * @param 	  	guid		   	The guid to set to the wellbore trajectory representation. If
		 * 								empty then a new guid will be generated.
		 * @param 	  	title		   	The title to set to the wellbore trajectory representation. If
		 * 								empty then \"unknown\" title will be set.
		 * @param [in]	deviationSurvey	The deviation survey on which this wellbore trajectory relies on.
		 * 								MD data will be retrieve from it. It cannot be null.
		 */
		WellboreTrajectoryRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, RESQML2_NS::DeviationSurveyRepresentation* deviationSurvey);

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		WellboreTrajectoryRepresentation(gsoap_resqml2_0_1::_resqml20__WellboreTrajectoryRepresentation* fromGsoap) : RESQML2_NS::WellboreTrajectoryRepresentation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		~WellboreTrajectoryRepresentation() {}

		/**
		 * Sets the minimal geometry of the representation by means of start and end MDs.
		 *
		 * @param 	startMd	The start MD of the trajectory. Uom is the same as the one for the associated
		 * 					MdDatum coordinates.
		 * @param 	endMd  	The end MD of the trajectory. Uom is the same as the one for the associated
		 * 					MdDatum coordinates.
		 */
		DLL_IMPORT_OR_EXPORT void setMinimalGeometry(double startMd, double endMd) final;

		/**
		 * Sets the geometry of the representation by means of a parametric line without MD information
		 * (only start and end MDs).
		 *
		 * @exception	std::invalid_argument	If @p controlPoints is @c nullptr.
		 * @exception	std::invalid_argument	If @p controlPointCount is 0.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p localCrs is @c nullptr and no default CRS is
		 * 										defined in the repository.
		 *
		 * @param [in]	  	controlPoints	 	All the control points of the cubic parametric line in
		 * 										the order of the MDs. Count is <tt>controlPointCount *
		 * 										3</tt> and for each control point <tt>(x,y,z) =
		 * 										(controlPoints[2i], controlPoints[2i+1],
		 * 										controlPoints[2i+2])</tt>.
		 * @param 		  	startMd			 	The start MD of the trajectory.
		 * @param 		  	endMd			 	The end MD of the trajectory.
		 * @param 		  	controlPointCount	The count of control points and control point parameters
		 * 										per cubic parametric line.
		 * @param 		  	lineKind		 	Integer indicating the parametric line kind: 0 for
		 * 										vertical, 1 for linear spline, 2 for natural cubic spline,
		 * 										3 for cubic spline, 4 for z linear cubic spline, 5 for
		 * 										minimum-curvature spline, (-1) for null: no line.
		 * @param [in,out]	proxy			 	(Optional) The HDF proxy which indicates in which HDF5
		 * 										file the control points and its parameters will be
		 * 										stored. It must be already opened for writing and won't
		 * 										be closed. If null, then the default HDF Proxy of the
		 * 										data object repository will be arbitrarily selected for
		 * 										writing.
		 * @param [in]	  	localCrs		 	(Optional) The local CRS where the control points are
		 * 										given. If @c nullptr (default), then the default Local
		 * 										CRS of the data object repository will be arbitrarily
		 * 										selected.
		 */
		DLL_IMPORT_OR_EXPORT void setGeometry(double const* controlPoints,
			double startMd, double endMd,
			unsigned int controlPointCount, int lineKind, EML2_NS::AbstractHdfProxy* proxy = nullptr,
			RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) final;
		
		/**
		 * Sets the geometry of the representation by means of a parametric line with MD information.
		 *
		 * @exception	std::invalid_argument	If @p controlPoints is @c nullptr.
		 * @exception	std::invalid_argument	If @p controlPointParameters is @c nullptr.
		 * @exception	std::invalid_argument	If @p controlPointCount is 0.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p localCrs is @c nullptr and no default CRS is
		 * 										defined in the repository.
		 *
		 * @param [in]	  	controlPoints		  	All the control points of the cubic parametric line
		 * 											in the order of the MDs. Count is
		 * 											<tt>controlPointCount * 3</tt> and for each control
		 * 											point <tt>(x,y, z) = (controlPoints[2i],
		 * 											controlPoints[2i+1], controlPoints[2i+2])</tt>.
		 * @param [in]	  	controlPointParameters	The arrays of control point parameters (ordered
		 * 											regarding the control points). It corresponds to the
		 * 											MD values in a WellboreFeature context. Count is @p
		 * 											controlPointCount.  
		 * @param 		  	controlPointCount	  	The count of control points and control point
		 * 											parameters per cubic parametric line.
		 * @param 		  	lineKind			  	Integer indicating the parametric line kind: 0 for
		 * 											vertical, 1 for linear spline, 2 for natural cubic
		 * 											spline, 3 for cubic spline, 4 for z linear cubic
		 * 											spline, 5 for minimum-curvature spline, (-1) for
		 * 											null: no line.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy which indicates in which
		 * 											HDF5 file the control points and its parameters will
		 * 											be stored. It must be already opened for writing and
		 * 											won't be closed. If null, then the default HDF Proxy
		 * 											of the DataObject repository will be arbitrarily
		 * 											selected for writing.
		 * @param [in]	  	localCrs			  	(Optional) The local CRS where the control points are
		 * 											given. If @c nullptr (default), then the default
		 * 											Local CRS of the DataObject repository will be
		 * 											arbitrarily selected.
		 */
		DLL_IMPORT_OR_EXPORT void setGeometry(double const* controlPoints, double const* controlPointParameters, unsigned int controlPointCount, int lineKind,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) final;

		/**
		 * Sets the geometry of the representation by means of a parametric line with MD and tangent
		 * vector information.
		 *
		 * @exception	std::invalid_argument	If @p controlPoints is @c nullptr.
		 * @exception	std::invalid_argument	If @p tangentVectors is @c nullptr.
		 * @exception	std::invalid_argument	If @p controlPointParameters is @c nullptr.
		 * @exception	std::invalid_argument	If @p controlPointCount is 0.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If @p localCrs is @c nullptr and no default CRS is
		 * 										defined in the repository.
		 *
		 * @param [in]	  	controlPoints		  	All the control points of the cubic parametric line
		 * 											in the order of the MDs. Count is
		 * 											<tt>controlPointCount * 3</tt> and for each control
		 * 											point <tt>(x,y, z) = (controlPoints[2i],
		 * 											controlPoints[2i+1], controlPoints[2i+2])</tt>.
		 * @param [in]	  	tangentVectors		  	All the tangent vectors of all the control points of
		 * 											all the cubic parametric lines. They are ordered
		 * 											according to the control points. Count is
		 * 											<tt>controlPointCount * 3</tt> and for each tangent
		 * 											vector <tt>(u,v, w) = (tangentVectors[2i],
		 * 											tangentVectors[2i+1], tangentVectors[2i+2])</tt>.
		 * @param [in]	  	controlPointParameters	The arrays of control point parameters (ordered
		 * 											regarding the control points). It corresponds to the
		 * 											MD values in a WellboreFeature context. Count is @p
		 * 											controlPointCount.
		 * @param 		  	controlPointCount	  	The count of control points and control point
		 * 											parameters and tangent vectors per cubic parametric
		 * 											line.
		 * @param 		  	lineKind			  	Integer indicating the parametric line kind: 0 for
		 * 											vertical, 1 for linear spline, 2 for natural cubic
		 * 											spline, 3 for cubic spline, 4 for z linear cubic
		 * 											spline, 5 for minimum-curvature spline, (-1) for
		 * 											null: no line.
		 * @param [in,out]	proxy				  	(Optional) The HDF proxy which indicates in which
		 * 											HDF5 file the parameters and the tangent vectors will
		 * 											be stored. It must be already opened for writing and
		 * 											won't be closed. If null, then the default HDF Proxy
		 * 											of the DataObject repository will be arbitrarily
		 * 											selected for writing.
		 * @param [in]	  	localCrs			  	(Optional) The local CRS where the control points are
		 * 											given. If @c nullptr, then the default Local CRS of
		 * 											the DataObject repository will be arbitrarily
		 * 											selected.
		 */
		DLL_IMPORT_OR_EXPORT void setGeometry(double const* controlPoints,
			double const* tangentVectors, double const* controlPointParameters, unsigned int controlPointCount, int lineKind,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) final;

		/**
		 * Gets the geometry kind.
		 *
		 * @exception	std::logic_error 	If this trajectory has no geometry.
		 * @exception	std::logic_error 	If the geometry of this trajectory is not a parametric line.
		 * @exception	std::out_of_range	If the geometry kind index is not in the range <tt>[-1,
		 * 									5]</tt>.
		 *
		 * @returns	0 for vertical, 1 for linear spline, 2 for natural cubic spline, 3 for cubic spline,
		 * 			4 for z linear cubic spline, 5 for minimum-curvature spline, (-1) for null: no line.
		 */
		DLL_IMPORT_OR_EXPORT int getGeometryKind() const final;

		/**
		 * Sets the MD datum of this trajectory.
		 *
		 * @exception	std::invalid_argument	If @p mdDatum is @c nullptr.
		 *
		 * @param [in]	mdDatum	The MD damtum to set to this trajectory. It cannot be null.
		 */
		DLL_IMPORT_OR_EXPORT void setMdDatum(RESQML2_NS::MdDatum * mdDatum) final;

		/**
		* Gets the data object reference of the MD information associated to this wellbore trajectory representation.
		* 
		* @returns The data object reference of the MD information.
		*/
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getMdDatumDor() const final;

		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(unsigned int patchIndex) const final;

		/**
		 * @copybrief RESQML2_NS::AbstractRepresentation::getXyzPointsOfPatch
		 * 
		 * @exception std::invalid_argument If the HDF proxy is missing.
		 * @exception	std::logic_error 	If this trajectory has no geometry.
		 * 
		 * @copydetails RESQML2_NS::AbstractRepresentation::getXyzPointsOfPatch
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const final;

		/**
		 * Indicates if the wellbore trajectory has got MD values attached to each trajectory station.
		 *
		 * @exception	std::logic_error	If the geometry of this trajectory is not a parametric line.
		 *
		 * @returns	True if there is some MD values, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasMdValues() const final;

		/**
		 * Gets the unit of measure of the MDs along this trajectory.
		 *
		 * @returns	The unit of measure of the MDs along this trajectory.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::eml20__LengthUom getMdUom() const final;

		/**
		 * Gets the MD double values associated to each trajectory station of this trajectory.
		 *
		 * @exception	std::invalid_argument	If this trajectory has no MD value.
		 * @exception	std::invalid_argument	If the HDF proxy is missing.
		 * @exception	std::invalid_argument	If MD values are not defined using a double HDF5 array.
		 *
		 * @param [out]	values	A buffer for receiving the MD values. It must be preallocated with size
		 * 						of getXyzPointCountOfAllPatches().
		 */
		DLL_IMPORT_OR_EXPORT void getMdValues(double* values) const final;

		/**
		 * Gets the starting MD of this wellbore trajectory. Range may often be from kickoff to TD,
		 * but this is not necessary.
		 *
		 * @returns	The start MD.
		 */
		DLL_IMPORT_OR_EXPORT double getStartMd() const final;

		/**
		 * Gets the ending MD of this wellbore trajectory. Range may often be from kickoff to TD, but
		 * this is not necessary.
		 *
		 * @returns	The end MD.
		 */
		DLL_IMPORT_OR_EXPORT double getFinishMd() const final;

		/**
		 * Indicates if the wellbore trajectory has got tangent vectors attached to each trajectory
		 * station.
		 *
		 * @exception	std::logic_error	If the geometry of this trajectory is not a parametric line.
		 *
		 * @returns	True if there is some tangent vectors, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasTangentVectors() const final;

		/**
		 * Gets the tangent vectors associated to each trajectory station of this trajectory.
		 *
		 * @exception	std::invalid_argument	If this trajectory has no tanget vector.
		 * @exception	std::invalid_argument	If the HDF proxy is missing.
		 *
		 * @param [out]	tangentVectors	A buffer for receiving the tangent vectors. It must be
		 * 								preallocated with size of <tt>3 * </tt>
		 * 								getXyzPointCountOfAllPatches().
		 */
		DLL_IMPORT_OR_EXPORT void getTangentVectors(double* tangentVectors) final;

		/**
		 * Adds a trajectory parent to this trajectory in case of trajectory branching. Does add the
		 * inverse relationship i.e. from the parent trajectory to this trajectory.
		 *
		 * @exception	std::invalid_argument	If @p parentTrajRep is @c nullptr.
		 *
		 * @param 	  	kickoffMd	 	The kickoff MD.
		 * @param 	  	parentMd	 	The MD on the parent wellbore trajectory where this trajectory is starting. It can be NaN if same as kickoffMd.
		 * @param [in]	parentTrajRep	The parent trajectory.
		 */
		DLL_IMPORT_OR_EXPORT void addParentTrajectory(double kickoffMd, double parentMd, RESQML2_NS::WellboreTrajectoryRepresentation* parentTrajRep) final;

		/**
		 * Gets the data object reference of the parent trajectory of this trajectory.
		 *
		 * @returns	Empty if this trajectory has no parent trajectory, otherwise the data object
		 * 			reference of the parent trajectory.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getParentTrajectoryDor() const final;

		/**
		 * Gets the MD on the parent wellbore trajectory where this trajectory is starting.
		 *
		 * @exception	std::logic_error	If this wellbore trajectory has no parent trajecory.
		 *
		 * @returns	The parent trajectory MD.
		 */
		DLL_IMPORT_OR_EXPORT double getParentTrajectoryMd() const final;

		/**
		 * Sets the deviation survey which is the source of this trajectory.
		 *
		 * @exception	std::invalid_argument	If @p deviationSurvey is @c nullptr.
		 *
		 * @param [in]	deviationSurvey	The deviation survey to set as a source of this trajectory.
		 */
		DLL_IMPORT_OR_EXPORT void setDeviationSurvey(RESQML2_NS::DeviationSurveyRepresentation* deviationSurvey) final;

		/**
		 * Gets the data object reference of the deviation survey which is the source of this trajectory.
		 *
		 * @returns	The data object reference of the deviation survey which is the source of this
		 * 			trajectory if exists, else empty data object reference.
		 */
		COMMON_NS::DataObjectReference getDeviationSurveyDor() const final;

		COMMON_NS::DataObjectReference getLocalCrsDor(unsigned int patchIndex) const final;

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		/**
		 * Queries if this trajectory has a geometry.
		 *
		 * @returns	True if this trajectory has a geometry, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasGeometry() const final;
	};
}
