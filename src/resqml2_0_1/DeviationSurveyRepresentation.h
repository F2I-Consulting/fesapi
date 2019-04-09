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

#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"

namespace RESQML2_NS
{
	class MdDatum;
}

namespace RESQML2_0_1_NS
{
	class WellboreTrajectoryRepresentation;

	class DeviationSurveyRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DeviationSurveyRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :AbstractRepresentation(partialObject) {}


		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp					The WellboreFeature interpretation the instance represents.
		* @param guid					The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param isFinal				Used to indicate that this is a final version of the deviation survey, as distinct from the interim interpretations.
		* @param mdInfo					The MD information of the survey, mainly the well reference point.
		*/
		DeviationSurveyRepresentation(class WellboreInterpretation* interp, const std::string & guid, const std::string & title, const bool & isFinal, RESQML2_NS::MdDatum * mdInfo);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		DeviationSurveyRepresentation(gsoap_resqml2_0_1::_resqml2__DeviationSurveyRepresentation* fromGsoap) : AbstractRepresentation(fromGsoap) {}

		~DeviationSurveyRepresentation() {}

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const {return XML_TAG;}

		/*
		*  Set the geometry of the representation by means of a parametric line without MD information.
		* @param firstStationLocation			XYZ location of the first station of the deviation survey in the local CRS. It must be three doubles. It is not created and not deleted by this method.
		* @param stationCount					Number of stations (including the first station location).
		* @param mdUom							Units of measure of the measured depths along this deviation survey.
		* @param mds							MD values for the position of the stations. Array length equals station count.
		* @param angleUom						Defines the units of measure for the azimuth and inclination
		* @param azimuths						An array of azimuth angles, one for each survey station. The rotation is relative to the projected CRS north with a positive value indicating a clockwise rotation as seen from above. Array length equals station count.
		* @param inclinations					Dip (or inclination) angle for each station. Array length equals station count.
		* @param proxy							The HDF proxy which indicates in which HDF5 file the numerical values will be stored.
		*										It must be already opened for writing and won't be closed.
		*/
		DLL_IMPORT_OR_EXPORT void setGeometry(double * firstStationLocation, const ULONG64 & stationCount,
			const gsoap_resqml2_0_1::eml20__LengthUom & mdUom, double * mds,
			const gsoap_resqml2_0_1::eml20__PlaneAngleUom & angleUom, double * azimuths, double * inclinations,
			COMMON_NS::AbstractHdfProxy* proxy);

		/**
		* Set the Md datum of this trajectory
		*/
		DLL_IMPORT_OR_EXPORT void setMdDatum(RESQML2_NS::MdDatum* mdDatum);

		/**
		* @return	null pointer if no md datum is associated to this representation. Otherwise return the data object reference of the associated md datum.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getMdDatumDor() const;

		/**
		* Getter of the md information associated to this WellboreFeature trajectory representation.
		*/
		DLL_IMPORT_OR_EXPORT RESQML2_NS::MdDatum * getMdDatum() const;

		/**
		* Getter of the md information uuid associated to this WellboreFeature trajectory representation.
		*/
		DLL_IMPORT_OR_EXPORT std::string getMdDatumUuid() const;

		/**
		* Used to indicate that this is a final version of the deviation survey, as distinct from the interim interpretations.
		*/
		DLL_IMPORT_OR_EXPORT bool isFinal() const;

		/**
		* Get the xyz point count in a given patch.
		*/
		ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		* Units of measure of the measured depths along this deviation survey.
		*/
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::eml20__LengthUom getMdUom() const;

		/**
		* Defines the units of measure for the azimuth and inclination
		*/
		gsoap_resqml2_0_1::eml20__PlaneAngleUom getAngleUom() const;

		/**
		* Getter of the md double values associated to each trajectory station of this WellboreFeature trajectory representation.
		* Uom is given by getMdUom().
		* @param values	It must preallocated with a count of getXyzPointCountOfPatch(0)
		*/
		DLL_IMPORT_OR_EXPORT void getMdValues(double* values);

		/**
		* Getter of the inclination double values associated to each trajectory station of this WellboreFeature trajectory representation.
		* Uom is given by getAngleUom().
		* @param values	It must preallocated with a count of getXyzPointCountOfPatch(0)
		*/
		DLL_IMPORT_OR_EXPORT void getInclinations(double* values);

		/**
		* Getter of the azimuth double values associated to each trajectory station of this WellboreFeature trajectory representation.
		* The rotation is relative to the projected CRS north with a positive value indicating a clockwise rotation as seen from above.
		* Uom is given by getAngleUom().
		* @param values	It must preallocated with a count of getXyzPointCountOfPatch(0)
		*/
		DLL_IMPORT_OR_EXPORT void getAzimuths(double* values);

		/**
		* Getter of all the wellbore frame representations of associated wellbore trajectory which share the same md datum and md uom.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<class WellboreFrameRepresentation*> getWellboreFrameRepresentationSet() const;

		/**
		* Get the count of all the wellbore frame representations of associated wellbore trajectory which share the same md datum and md uom.
		* Necessary for now in SWIG context because I am not sure if I can always wrap a vector of polymorphic class yet.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getWellboreFrameRepresentationCount() const;

		/**
		* Get a particular wellbore frame representation according to its position.
		* Necessary for now in SWIG context because I am not sure if I can always wrap a vector of polymorphic class yet.
		* Throw an out of bound exception if the index is superior or equal to the count of wellbore frame representation.
		*/
		DLL_IMPORT_OR_EXPORT class WellboreFrameRepresentation* getWellboreFrameRepresentation(unsigned int index) const;

		/**
		* Getter (in read only mode) of all the wellbore trajectories which are associated to this deviation survey.
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<class WellboreTrajectoryRepresentation*>& getWellboreTrajectoryRepresentationSet() const;

		/**
		* Get the count of all the wellbore trajectories which are associated to this deviation survey.
		* Necessary for now in SWIG context because I am not sure if I can always wrap a vector of polymorphic class yet.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getWellboreTrajectoryRepresentationCount() const;

		/**
		* Get a particular wellbore trajectory according to its position.
		* Necessary for now in SWIG context because I am not sure if I can always wrap a vector of polymorphic class yet.
		* Throw an out of bound exception if the index is superior or equal to the count of wellbore frame representation.
		*/
		DLL_IMPORT_OR_EXPORT class WellboreTrajectoryRepresentation* getWellboreTrajectoryRepresentation(const unsigned int & index) const;

		gsoap_resqml2_0_1::eml20__DataObjectReference* getHdfProxyDor() const;

		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const {return 1;}

		std::vector<epc::Relationship> getAllSourceRelationships() const;
		std::vector<epc::Relationship> getAllTargetRelationships() const;

		void resolveTargetRelationships(COMMON_NS::EpcDocument* epcDoc);
	protected:

		friend void WellboreTrajectoryRepresentation::setDeviationSurvey(DeviationSurveyRepresentation* deviationSurvey);

		void addTrajectory(class WellboreTrajectoryRepresentation* trajectory);
		
		// XML backward relationships
		std::vector<class WellboreTrajectoryRepresentation*> wbTrajectoryRepSet;
	};
}
