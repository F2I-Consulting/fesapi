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

#include "AbstractRepresentation.h"

namespace RESQML2_NS
{
	class WellboreInterpretation;

	class WellboreTrajectoryRepresentation : public AbstractRepresentation
	{
	public:

		virtual ~WellboreTrajectoryRepresentation() {}

		/*
		* Set the geometry of the representation by means of a parametric line without MD information.
		* @param startMd						The start MD of the trajectory. Uom is the same as the one for the assocaited MdDatum coordinates.
		* @param endMd							The end MD of the trajectory. Uom is the same as the one for the assocaited MdDatum coordinates.
		* @localCrs								The local CRS where the control points are given.
		*										If null, then the default Local CRS of the DataObject repository will be arbitrarily selected.
		*/
		DLL_IMPORT_OR_EXPORT virtual void setMinimalGeometry(double startMd, double endMd) = 0;

		/*
		* Set the geometry of the representation by means of a parametric line without MD information (only start and end MD).
		* @param controlPoints					All the control points of all the cubic parametric lines. They are ordered by parametric line first.
		* @param startMd						The start MD of the trajectory.
		* @param endMd							The end MD of the trajectory.
		* @param controlPointCount				The count of control points and control point parameters per cubic parametric line.
		* @param lineKind						Integer indicating the parametric line kind: 0 for vertical, 1 for linear spline, 2 for natural cubic spline, 3 for cubic spline, 4 for z linear cubic spline, 5 for minimum-curvature spline, (-1) for null: no line
		* @param proxy							The HDF proxy which indicates in which HDF5 file the control points and its parameters will be stored.
		*										It must be already opened for writing and won't be closed.
		*										If null, then the default HDF Proxy of the DataObject repository will be arbitrarily selected for writing.
		* @localCrs								The local CRS where the control points are given.
		*										If null, then the default Local CRS of the DataObject repository will be arbitrarily selected.
		*/
		DLL_IMPORT_OR_EXPORT virtual void setGeometry(double const* controlPoints, double startMd, double endMd, unsigned int controlPointCount, int lineKind, COMMON_NS::AbstractHdfProxy* proxy = nullptr, AbstractLocal3dCrs* localCrs = nullptr) = 0;

		/*
		* Set the geometry of the representation by means of a parametric line with MD information.
		* @param controlPoints					All the control points of all the cubic parametric lines. They are ordered by parametric line first.
		* @param controlPointParameters			The arrays of control point parameters (ordered regarding the control points). It corresponds to the MD values in a WellboreFeature context.
		* @param controlPointCount				The count of control points and control point parameters per cubic parametric line.
		* @param lineKind						Integer indicating the parametric line kind: 0 for vertical, 1 for linear spline, 2 for natural cubic spline, 3 for cubic spline, 4 for z linear cubic spline, 5 for minimum-curvature spline, (-1) for null: no line
		* @param proxy							The HDF proxy which indicates in which HDF5 file the control points and its parameters will be stored.
		*										It must be already opened for writing and won't be closed.
		*										If null, then the default HDF Proxy of the DataObject repository will be arbitrarily selected for writing.
		* @localCrs								The local CRS where the control points are given.
		*										If null, then the default Local CRS of the DataObject repository will be arbitrarily selected.
		*/
		DLL_IMPORT_OR_EXPORT virtual void setGeometry(double const* controlPoints, double const* controlPointParameters, unsigned int controlPointCount, int lineKind,
			COMMON_NS::AbstractHdfProxy* proxy = nullptr, AbstractLocal3dCrs* localCrs = nullptr) = 0;

		/*
		* Set the geometry of the representation by means of a parametric line with MD and tangent vector information.
		* @param controlPoints					All the control points of all the cubic parametric lines. They are ordered by parametric line first.
		* @param tangentVectors					All the tangent vectors of all the control points of all the cubic parametric lines. They are ordered according to the control points.
		* @param controlPointParameters			The arrays of control point parameters (ordered regarding the control points). It corresponds to the MD values in a WellboreFeature context.
		* @param controlPointCount				The count of control points and control point parameters and tangent vectors per cubic parametric line.
		* @param lineKind						Integer indicating the parametric line kind: 0 for vertical, 1 for linear spline, 2 for natural cubic spline, 3 for cubic spline, 4 for z linear cubic spline, 5 for minimum-curvature spline, (-1) for null: no line
		* @param proxy							The HDF proxy which indicates in which HDF5 file the parameters and the tangent vectors will be stored.
		*										It must be already opened for writing and won't be closed.
		*										If null, then the default HDF Proxy of the DataObject repository will be arbitrarily selected for writing.
		* @localCrs								The local CRS where the control points are given.
		*										If null, then the default Local CRS of the DataObject repository will be arbitrarily selected.
		*/
		DLL_IMPORT_OR_EXPORT virtual void setGeometry(double const* controlPoints,
			double const* tangentVectors, double const* controlPointParameters, unsigned int controlPointCount, int lineKind,
			COMMON_NS::AbstractHdfProxy* proxy = nullptr, AbstractLocal3dCrs* localCrs = nullptr) = 0;

		/**
		* 0 for vertical, 1 for linear spline, 2 for natural cubic spline, 3 for cubic spline, 4 for z linear cubic spline, 5 for minimum-curvature spline, (-1) for null: no line
		*/
		DLL_IMPORT_OR_EXPORT virtual int getGeometryKind() const = 0;

		/**
		* Set the Md datum of this trajectory
		*/
		DLL_IMPORT_OR_EXPORT virtual void setMdDatum(MdDatum * mdDatum) = 0;

		/**
		* Getter of the md information associated to this WellboreFeature trajectory representation.
		*/
		DLL_IMPORT_OR_EXPORT RESQML2_NS::MdDatum * getMdDatum() const;

		/**
		* Getter of the md information uuid associated to this WellboreFeature trajectory representation.
		*/
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getMdDatumDor() const = 0;

		/**
		* Indicates if the wellbore trajectory has got md values attached to each trajectory station.
		*/
		DLL_IMPORT_OR_EXPORT virtual bool hasMdValues() const = 0;

		/**
		* Units of measure of the measured depths along this trajectory.
		*/
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::eml20__LengthUom getMdUom() const = 0;

		/**
		* Getter of the md double values associated to each trajectory station of this WellboreFeature trajectory representation.
		*/
		DLL_IMPORT_OR_EXPORT virtual void getMdValues(double* values) const = 0;

		/**
		* Get the measured depth for the start of the wellbore trajectory. Range may often be from kickoff to TD, but this is not necessary.
		*/
		DLL_IMPORT_OR_EXPORT virtual double getStartMd() const = 0;

		/**
		* Get the ending depth for the start of the wellbore trajectory. Range may often be from kickoff to TD, but this is not necessary.
		*/
		DLL_IMPORT_OR_EXPORT virtual double getFinishMd() const = 0;

		/**
		* Indicates if the wellbore trajectory has got tangent vectors attached to each trajectory station.
		*/
		DLL_IMPORT_OR_EXPORT virtual bool hasTangentVectors() const = 0;

		/**
		* Getter of the tangent vectors associated to each trajectory station of this WellboreFeature trajectory representation.
		*/
		DLL_IMPORT_OR_EXPORT virtual void getTangentVectors(double* tangentVectors) = 0;

		//*****************
		//*** PARENTAGE ***
		//*****************

		/**
		* Add a trajectory parent to this trajectory in case of trajectory branching.
		* Does add the inverse relationship i.e. from the parent trajectory to this trajecotry
		*/
		DLL_IMPORT_OR_EXPORT void virtual addParentTrajectory(double kickoffMd, double parentMd, WellboreTrajectoryRepresentation* parentTrajRep) = 0;

		/**
		* Get the parent trajectory of this trajectory
		* @return nullptr if the trajectory has no parent trajectory.
		*/
		DLL_IMPORT_OR_EXPORT WellboreTrajectoryRepresentation* getParentTrajectory() const;

		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getParentTrajectoryDor() const = 0;

		/**
		* Get the MD on the parent wellbore trajectory where this trajectory is starting.
		*/
		DLL_IMPORT_OR_EXPORT virtual double getParentTrajectoryMd() const = 0;

		/**
		* Get a set of all children trajectories of this trajectory
		*/
		DLL_IMPORT_OR_EXPORT std::vector<WellboreTrajectoryRepresentation*> getChildrenTrajectorySet() const;

		//*****************
		//***** FRAME *****
		//*****************

		/**
		* Getter (in read only mode) of all the associated Wellbore frame representations
		*/
		DLL_IMPORT_OR_EXPORT std::vector<class RESQML2_NS::WellboreFrameRepresentation *> getWellboreFrameRepresentationSet() const;

		/**
		* Get the count of wellbore frame representation which are associated with this wellbore trajectory.
		* Necessary for now in SWIG context because I am not sure if I can always wrap a vector of polymorphic class yet.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getWellboreFrameRepresentationCount() const;

		/**
		* Get a particular wellbore frame representation of this wellbore trajectory representation according to its position in the EPC document.
		* Necessary for now in SWIG context because I mm not sure if I can always wrap a vector of polymorphic class yet.
		* Throw an out of bound exception if the index is superior or equal to the count of wellbore frame representation.
		*/
		DLL_IMPORT_OR_EXPORT class RESQML2_NS::WellboreFrameRepresentation * getWellboreFrameRepresentation(unsigned int index) const;

		//*****************
		//***** SURVEY ****
		//*****************

		/**
		* Set the deviation survey which is the source of this trajectory.
		*/
		DLL_IMPORT_OR_EXPORT virtual void setDeviationSurvey(class DeviationSurveyRepresentation* deviationSurvey) = 0;

		/**
		* Get the deviation survey which is the source of this trajectory. It can return a null pointer.
		*/
		DLL_IMPORT_OR_EXPORT class DeviationSurveyRepresentation* getDeviationSurvey() const;

		/**
		* Get the information to resolve the associated deviation survey. It can return an empty reference.
		*/
		virtual COMMON_NS::DataObjectReference getDeviationSurveyDor() const = 0;

		/**
		* Get the information to resolve the associated local CRS.
		*/
		virtual COMMON_NS::DataObjectReference getLocalCrsDor(unsigned int patchIndex) const = 0;

		virtual COMMON_NS::DataObjectReference getHdfProxyDor() const = 0;

		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const {return 1;}

		DLL_IMPORT_OR_EXPORT virtual bool hasGeometry() const = 0;

		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

	protected:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT WellboreTrajectoryRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractRepresentation(partialObject) {}

		WellboreTrajectoryRepresentation() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreTrajectoryRepresentation(gsoap_resqml2_0_1::_resqml20__WellboreTrajectoryRepresentation* fromGsoap) : AbstractRepresentation(fromGsoap) {}
		WellboreTrajectoryRepresentation(gsoap_eml2_3::_resqml22__WellboreTrajectoryRepresentation* fromGsoap) : AbstractRepresentation(fromGsoap) {}

		void loadTargetRelationships();
	};
}
