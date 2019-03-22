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

#include "resqml2/AbstractRepresentation.h"

namespace WITSML1_4_1_1_NS
{
	class Trajectory;
}

namespace RESQML2_0_1_NS
{
	class DLL_IMPORT_OR_EXPORT WellboreTrajectoryRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	private:
		gsoap_resqml2_0_1::_resqml2__WellboreTrajectoryRepresentation* getSpecializedGsoapProxy() const;

	public:

		/**
		* Only to be used in partial transfer context
		*/
		WellboreTrajectoryRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			AbstractRepresentation(partialObject),
			witsmlTrajectory(nullptr) {}


		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp					The WellboreFeature interpretation the instance represents.
		* @param guid					The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param mdInfo					The MD information of the trajectory, mainly the well reference point.
		*/
		WellboreTrajectoryRepresentation(class WellboreInterpretation* interp, const std::string & guid, const std::string & title, RESQML2_NS::MdDatum * mdInfo);

		/**
		* Creates an instance with an existing deviation survey as its origin.
		*/
		WellboreTrajectoryRepresentation(class WellboreInterpretation* interp, const std::string & guid, const std::string & title, DeviationSurveyRepresentation* deviationSurvey);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreTrajectoryRepresentation(gsoap_resqml2_0_1::_resqml2__WellboreTrajectoryRepresentation* fromGsoap): AbstractRepresentation(fromGsoap),
				witsmlTrajectory(nullptr) {}

		~WellboreTrajectoryRepresentation() {}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		/*
		*  Set the geometry of the representation by means of a parametric line without MD information.
		* @param controlPoints					All the control points of all the cubic parametric lines. They are ordered by parametric line first.
		* @param controlPointCount				The count of control points and control point parameters per cubic parametric line.
		* @param lineKind						Integer indicating the parametric line kind: 0 for vertical, 1 for linear spline, 2 for natural cubic spline, 3 for cubic spline, 4 for z linear cubic spline, 5 for minimum-curvature spline, (-1) for null: no line
		* @param proxy							The HDF proxy which indicates in which HDF5 file the control points and its parameters will be stored.
		*										It must be already opened for writing and won't be closed.
		*/
		void setGeometry(double * controlPoints, const double & startMd, const double & endMd, const unsigned int & controlPointCount, const int & lineKind, COMMON_NS::AbstractHdfProxy* proxy);

		/*
		*  Set the geometry of the representation by means of one natural cubic parametric line.
		* @param controlPoints					All the control points of all the cubic parametric lines. They are ordered by parametric line first.
		* @param controlPointCount				The count of control points and control point parameters per cubic parametric line.
		* @param controlPointParameters			The arrays of control point parameters (ordered regarding the control points). It corresponds to the MD values in a WellboreFeature context.
		* @param proxy							The HDF proxy which indicates in which HDF5 file the control points and its parameters will be stored.
		*										It must be already opened for writing and won't be closed.
		*/
		void setGeometry(double * controlPoints, double* controlPointParameters, const unsigned int & controlPointCount,
			COMMON_NS::AbstractHdfProxy* proxy);

		/*
		*  Set the geometry of the representation by means of one cubic parametric line.
		* @param controlPoints					All the control points of all the cubic parametric lines. They are ordered by parametric line first.
		* @param tangentVectors					All the tangent vectors of all the control points of all the cubic parametric lines. They are ordered according to the control points.
		* @param controlPointCount				The count of control points and control point parameters and tangent vectors per cubic parametric line.
		* @param controlPointParameters			The arrays of control point parameters (ordered regarding the control points). It corresponds to the MD values in a WellboreFeature context.
		* @param proxy							The HDF proxy which indicates in which HDF5 file the parameters and the tangent vectors will be stored.
		*										It must be already opened for writing and won't be closed.
		*/
		void setGeometry(double * controlPoints,
			double * tangentVectors, double* controlPointParameters, const unsigned int & controlPointCount,
			COMMON_NS::AbstractHdfProxy* proxy);

		/**
		* 0 for vertical, 1 for linear spline, 2 for natural cubic spline, 3 for cubic spline, 4 for z linear cubic spline, 5 for minimum-curvature spline, (-1) for null: no line
		*/
		int getGeometryKind() const;

		/**
		* Set the Md datum of this trajectory
		*/
		void setMdDatum(RESQML2_NS::MdDatum* mdDatum);

		/**
		* Getter of the md information associated to this WellboreFeature trajectory representation.
		*/
		RESQML2_NS::MdDatum * getMdDatum() const;

		/**
		* Getter of the md information uuid associated to this WellboreFeature trajectory representation.
		*/
		std::string getMdDatumUuid() const;

		/**
		* Get the xyz point count in a given patch.
		*/
		ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		* Indicates if the wellbore trajectory has got md values attached to each trajectory station.
		*/
		bool hasMdValues() const;

		/**
		* Units of measure of the measured depths along this trajectory.
		*/
		gsoap_resqml2_0_1::eml20__LengthUom getMdUom() const;

		/**
		* Getter of the md double values associated to each trajectory station of this WellboreFeature trajectory representation.
		*/
		void getMdValues(double* values);

		/**
		* Get the measured depth for the start of the wellbore trajectory. Range may often be from kickoff to TD, but this is not necessary.
		*/
		double getStartMd() const;

		/**
		* Get the ending depth for the start of the wellbore trajectory. Range may often be from kickoff to TD, but this is not necessary.
		*/
		double getFinishMd() const;

		/**
		* Indicates if the wellbore trajectory has got tangent vectors attached to each trajectory station.
		*/
		bool hasTangentVectors() const;

		/**
		* Getter of the tangent vectors associated to each trajectory station of this WellboreFeature trajectory representation.
		*/
		void getTangentVectors(double* tangentVectors);

		/**
		* Add a trajectory parent to this trajectory in case of trajectory branching.
		* Does add the inverse relationship i.e. from the parent trajectory to this trajecotry
		*/
		void addParentTrajectory(const double & kickoffMd, const double & parentMd, WellboreTrajectoryRepresentation* parentTrajRep);

		/**
		* Get the parent trajectory of this trajectory
		* @return nullptr if the trajectory has no parent trajectory.
		*/
		WellboreTrajectoryRepresentation* getParentTrajectory() const;

		/**
		* Get the MD on the parent wellbore trajectory where this trajectory is starting.
		*/
		const double& getParentTrajectoryMd() const;

		/**
		* Get a set of all children trajectories of this trajectory
		*/
		const std::vector<WellboreTrajectoryRepresentation*> & getChildrenTrajectorySet() const;

		/**
		* Add a Wellbore frame representation to this trajectory.
		* Does not add the inverse relationship i.e. from the WellboreFeature frame to this trajectory
		*/
		void addWellboreFrameRepresentation(class WellboreFrameRepresentation* WellboreFrameRepresentation) {wellboreFrameRepresentationSet.push_back(WellboreFrameRepresentation);}

		/**
		* Getter (in read only mode) of all the associated Wellbore frame representations
		*/
		const std::vector<class WellboreFrameRepresentation*>& getWellboreFrameRepresentationSet() const {return wellboreFrameRepresentationSet;}

		/**
		* Get the count of wellbore frame representation which are associated with this wellbore trajectory.
		* Necessary for now in SWIG context because I am not sure if I can always wrap a vector of polymorphic class yet.
		*/
		unsigned int getWellboreFrameRepresentationCount() const {return static_cast<unsigned int>(wellboreFrameRepresentationSet.size());}

		/**
		* Get a particular wellbore frame representation of this wellbore trajectory representation according to its position in the EPC document.
		* Necessary for now in SWIG context because I mm not sure if I can always wrap a vector of polymorphic class yet.
		* Throw an out of bound exception if the index is superior or equal to the count of wellbore frame representation.
		*/
		class WellboreFrameRepresentation* getWellboreFrameRepresentation(const unsigned int & index) const {return wellboreFrameRepresentationSet[index];}

		/**
		* Set the deviation survey which is the source of this trajectory.
		*/
		void setDeviationSurvey(class DeviationSurveyRepresentation* deviationSurvey);

		/**
		* Get the deviation survey which is the source of this trajectory. It can return a null pointer.
		*/
		class DeviationSurveyRepresentation* getDeviationSurvey() const;

		/**
		* Get the information to resolve the associated local CRS.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getLocalCrsDor() const;

		gsoap_resqml2_0_1::eml20__DataObjectReference* getHdfProxyDor() const;

		unsigned int getPatchCount() const {return 1;}

		bool hasGeometry() const;

		void setWitsmlTrajectory(WITSML1_4_1_1_NS::Trajectory * witsmlTraj);
		WITSML1_4_1_1_NS::Trajectory * getWitsmlTrajectory() {return witsmlTrajectory;}

		std::vector<epc::Relationship> getAllSourceRelationships() const;
		std::vector<epc::Relationship> getAllTargetRelationships() const;

	private:
		/**
		* Add a children parent to this trajectory in case of trajectory branching.
		* Does not add the inverse relationship i.e. from the children trajectory to this trajectory
		*/
		void addChildrenTrajectory(WellboreTrajectoryRepresentation* childrenTraj) { childrenTrajSet.push_back(childrenTraj); }

		/**
		* Get the information to resolve the associated deviation survey. It can return a null pointer.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getDeviationSurveyDor() const;
		void resolveTargetRelationships(COMMON_NS::EpcDocument* epcDoc);

	protected:

		// XML forward relationships
		WITSML1_4_1_1_NS::Trajectory * witsmlTrajectory;
		
		// XML backward relationships
		std::vector<WellboreTrajectoryRepresentation*> childrenTrajSet;
		std::vector<class WellboreFrameRepresentation*> wellboreFrameRepresentationSet;
	};
}

