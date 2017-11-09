/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#pragma once

#include "resqml2/AbstractRepresentation.h"

namespace witsml1_4_1_1
{
	class Trajectory;
}

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT WellboreTrajectoryRepresentation : public resqml2::AbstractRepresentation
	{
	private:
		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry2_0_1(const unsigned int & patchIndex) const {return nullptr;}

		gsoap_resqml2_0_1::_resqml2__WellboreTrajectoryRepresentation* getSpecializedGsoapProxy() const;

	public:

		/**
		* Only to be used in partial transfer context
		*/
		WellboreTrajectoryRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :AbstractRepresentation(partialObject) {}


		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp					The WellboreFeature interpretation the instance represents.
		* @param guid					The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param mdInfo					The MD information of the trajectory, mainly the well reference point.
		*/
		WellboreTrajectoryRepresentation(class WellboreInterpretation* interp, const std::string & guid, const std::string & title, resqml2::MdDatum * mdInfo);

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
		void setGeometry(double * controlPoints, const double & startMd, const double & endMd, const unsigned int & controlPointCount, const int & lineKind, common::AbstractHdfProxy* proxy);

		/*
		*  Set the geometry of the representation by means of one natural cubic parametric line.
		* @param controlPoints					All the control points of all the cubic parametric lines. They are ordered by parametric line first.
		* @param controlPointCount				The count of control points and control point parameters per cubic parametric line.
		* @param controlPointParameters			The arrays of control point parameters (ordered regarding the control points). It corresponds to the MD values in a WellboreFeature context.
		* @param proxy							The HDF proxy which indicates in which HDF5 file the control points and its parameters will be stored.
		*										It must be already opened for writing and won't be closed.
		*/
		void setGeometry(double * controlPoints, double* controlPointParameters, const unsigned int & controlPointCount,
			common::AbstractHdfProxy* proxy);

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
			common::AbstractHdfProxy* proxy);

		/**
		* 0 for vertical, 1 for linear spline, 2 for natural cubic spline, 3 for cubic spline, 4 for z linear cubic spline, 5 for minimum-curvature spline, (-1) for null: no line
		*/
		int getGeometryKind() const;

		/**
		* Set the Md datum of this trajectory
		*/
		void setMdDatum(resqml2::MdDatum* mdDatum);

		/**
		* Getter of the md information associated to this WellboreFeature trajectory representation.
		*/
		resqml2::MdDatum * getMdDatum() const;

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
		unsigned int getWellboreFrameRepresentationCount() const {return wellboreFrameRepresentationSet.size();}

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

		std::string getHdfProxyUuid() const;

		unsigned int getPatchCount() const {return 1;}

		bool hasGeometry() const;

		void setWitsmlTrajectory(witsml1_4_1_1::Trajectory * witsmlTraj);
		witsml1_4_1_1::Trajectory * getWitsmlTrajectory() {return witsmlTrajectory;}

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

	protected:

		std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		// XML forward relationships
		witsml1_4_1_1::Trajectory * witsmlTrajectory;
		
		// XML backward relationships
		std::vector<WellboreTrajectoryRepresentation*> childrenTrajSet;
		std::vector<class WellboreFrameRepresentation*> wellboreFrameRepresentationSet;
	};
}
