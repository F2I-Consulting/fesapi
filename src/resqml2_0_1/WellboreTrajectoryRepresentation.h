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

#include "../resqml2/AbstractRepresentation.h"

/** . */
namespace RESQML2_0_1_NS
{
	/** A wellbore trajectory representation. */
	class WellboreTrajectoryRepresentation : public RESQML2_NS::AbstractRepresentation
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
		DLL_IMPORT_OR_EXPORT WellboreTrajectoryRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :AbstractRepresentation(partialObject) {}

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
		WellboreTrajectoryRepresentation(class WellboreInterpretation * interp, const std::string & guid, const std::string & title, RESQML2_NS::MdDatum * mdInfo);

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
		WellboreTrajectoryRepresentation(class WellboreInterpretation * interp, const std::string & guid, const std::string & title, DeviationSurveyRepresentation * deviationSurvey);

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		WellboreTrajectoryRepresentation(gsoap_resqml2_0_1::_resqml20__WellboreTrajectoryRepresentation* fromGsoap): AbstractRepresentation(fromGsoap) {}

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
		DLL_IMPORT_OR_EXPORT void setMinimalGeometry(double startMd, double endMd);

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
		DLL_IMPORT_OR_EXPORT void setGeometry(double * controlPoints, double startMd, double endMd, unsigned int controlPointCount, int lineKind, COMMON_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr);

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
		DLL_IMPORT_OR_EXPORT void setGeometry(double * controlPoints, double* controlPointParameters, unsigned int controlPointCount, int lineKind,
			COMMON_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr);

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
		DLL_IMPORT_OR_EXPORT void setGeometry(double * controlPoints,
			double * tangentVectors, double* controlPointParameters, unsigned int controlPointCount, int lineKind,
			COMMON_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr);

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
		DLL_IMPORT_OR_EXPORT int getGeometryKind() const;

		/**
		 * Sets the MD datum of this trajectory.
		 *
		 * @exception	std::invalid_argument	If @p mdDatum is @c nullptr.
		 *
		 * @param [in]	mdDatum	The MD damtum to set to this trajectory. It cannot be null.
		 */
		DLL_IMPORT_OR_EXPORT void setMdDatum(RESQML2_NS::MdDatum * mdDatum);

		/**
		 * Gets the MD datum associated to this trajectory.
		 *
		 * @returns	The MD datum associated to this trajectory.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::MdDatum * getMdDatum() const;

		/**
		 * Gets the UUID of the MD datum associated to this trajectory.
		 *
		 * @returns	The UUID of the MD datum associated to this trajectory.
		 */
		DLL_IMPORT_OR_EXPORT std::string getMdDatumUuid() const;

		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const override;

		/**
		 * @copybrief RESQML2_NS::AbstractRepresentation::getXyzPointsOfPatch
		 * 
		 * @exception std::invalid_argument If the HDF proxy is missing.
		 * @exception	std::logic_error 	If this trajectory has no geometry.
		 * 
		 * @copydetails RESQML2_NS::AbstractRepresentation::getXyzPointsOfPatch
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const override ;

		/**
		 * Indicates if the wellbore trajectory has got MD values attached to each trajectory station.
		 *
		 * @exception	std::logic_error	If the geometry of this trajectory is not a parametric line.
		 *
		 * @returns	True if there is some MD values, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasMdValues() const;

		/**
		 * Gets the unit of measure of the MDs along this trajectory.
		 *
		 * @returns	The unit of measure of the MDs along this trajectory.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::eml20__LengthUom getMdUom() const;

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
		DLL_IMPORT_OR_EXPORT void getMdValues(double* values) const;

		/**
		 * Gets the starting MD of this wellbore trajectory. Range may often be from kickoff to TD,
		 * but this is not necessary.
		 *
		 * @returns	The start MD.
		 */
		DLL_IMPORT_OR_EXPORT double getStartMd() const;

		/**
		 * Gets the ending MD of this wellbore trajectory. Range may often be from kickoff to TD, but
		 * this is not necessary.
		 *
		 * @returns	The end MD.
		 */
		DLL_IMPORT_OR_EXPORT double getFinishMd() const;

		/**
		 * Indicates if the wellbore trajectory has got tangent vectors attached to each trajectory
		 * station.
		 *
		 * @exception	std::logic_error	If the geometry of this trajectory is not a parametric line.
		 *
		 * @returns	True if there is some tangent vectors, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasTangentVectors() const;

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
		DLL_IMPORT_OR_EXPORT void getTangentVectors(double* tangentVectors);

		/**
		 * Adds a trajectory parent to this trajectory in case of trajectory branching. Does add the
		 * inverse relationship i.e. from the parent trajectory to this trajectory.
		 *
		 * @exception	std::invalid_argument	If @p parentTrajRep is @c nullptr.
		 *
		 * @param 	  	kickoffMd	 	The kickoff MD.
		 * @param 	  	parentMd	 	The MD on the parent wellbore trajectory where this trajectory is starting.
		 * @param [in]	parentTrajRep	The parent trajectory.
		 */
		DLL_IMPORT_OR_EXPORT void addParentTrajectory(double kickoffMd, double parentMd, WellboreTrajectoryRepresentation* parentTrajRep);

		/**
		 * Gets the parent trajectory of this trajectory
		 *
		 * @returns	The parent trajectory if it exists, else nullptr.
		 */
		DLL_IMPORT_OR_EXPORT WellboreTrajectoryRepresentation* getParentTrajectory() const;

		/**
		 * Gets the MD on the parent wellbore trajectory where this trajectory is starting.
		 *
		 * @exception	std::logic_error	If this wellbore trajectory has no parent trajecory.
		 *
		 * @returns	The parent trajectory MD.
		 */
		DLL_IMPORT_OR_EXPORT double getParentTrajectoryMd() const;

		/**
		 * Gets the set of all children trajectories of this trajectory/
		 *
		 * @returns	A vector of pointers to all the children trajectories of this trajectory.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<WellboreTrajectoryRepresentation *> getChildrenTrajectorySet() const;

		/**
		 * Gets all the associated wellbore frame representations
		 *
		 * @returns A vector of pointers to all the associated wellbore frame representations.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<class RESQML2_NS::WellboreFrameRepresentation *> getWellboreFrameRepresentationSet() const;

		/**
		 * Get the count of wellbore frame representations which are associated with this wellbore
		 * trajectory.
		 *
		 * @exception	std::range_error	If the count is strictly greater than unsigned int max.
		 *
		 * @returns	The count of wellbore frame representations which are associated with this wellbore
		 * 			trajectory.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getWellboreFrameRepresentationCount() const; // It is mainly used in SWIG context for parsing the vector from a non C++ language.

		/**
		 * Gets a particular wellbore frame representation associated to this wellbore trajectory representation
		 * according to its position in the repository. 
		 * 
		 * @exception std::out_of_range If @p index is greater or equal to getWellboreFrameRepresentationCount().
		 * 
		 * @param index The index of the wellbore frame representation we look for.
		 * 				
		 * @returns The wellbore frame representation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT class RESQML2_NS::WellboreFrameRepresentation * getWellboreFrameRepresentation(unsigned int index) const; // It is mainly used in SWIG context for parsing the vector from a non C++ language.

		/**
		 * Sets the deviation survey which is the source of this trajectory.
		 *
		 * @exception	std::invalid_argument	If @p deviationSurvey is @c nullptr.
		 *
		 * @param [in]	deviationSurvey	The deviation survey to set as a source of this trajectory.
		 */
		DLL_IMPORT_OR_EXPORT void setDeviationSurvey(class DeviationSurveyRepresentation* deviationSurvey);

		/** 
		 * Gets the deviation survey which is the source of this trajectory.
		 *
		 * @returns The deviation survey which is the source of this trajectory if exists, else @c nullptr. 
		 */
		DLL_IMPORT_OR_EXPORT class DeviationSurveyRepresentation* getDeviationSurvey() const;

		COMMON_NS::DataObjectReference getLocalCrsDor(unsigned int patchIndex) const override;

		COMMON_NS::DataObjectReference getHdfProxyDor() const override;

		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const override {return 1;}

		/**
		 * Queries if this trajectory has a geometry.
		 *
		 * @returns	True if this trajectory has a geometry, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasGeometry() const;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const override { return XML_TAG; }

	private:

		/**
		 * Get the information to resolve the associated deviation survey. It can return a null pointer.
		 *
		 * @returns	Null if it fails, else the deviation survey dor.
		 */
		gsoap_resqml2_0_1::eml20__DataObjectReference* getDeviationSurveyDor() const;

	protected:
		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
