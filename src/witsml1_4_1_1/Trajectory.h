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

#include "witsml1_4_1_1/AbstractObject.h"

#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"

namespace WITSML1_4_1_1_NS
{
	class DLL_IMPORT_OR_EXPORT Trajectory : public AbstractObject
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		*/
		Trajectory(class Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title);

		Trajectory(class Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		Trajectory(gsoap_witsml1_4_1_1::witsml1__obj_USCOREtrajectorys* fromGsoap):AbstractObject(fromGsoap), wellbore(nullptr), resqmlWellboreTrajectoryRepresentation(nullptr) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~Trajectory() {}

		double getMdDatumElevation();
		gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom getMdDatumElevationUom();
		std::string getMdDatumName();

		unsigned int getTrajectoryStationCount() const;

		void getMds(double * mds) const;
		gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom getMdUom() const;

		unsigned int getInclinometries(double * incls) const;
		gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom getInclinometryUom() const;

		unsigned int getAzimuths(double * azims) const;
		gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom getAzimuthUom() const;
		gsoap_witsml1_4_1_1::witsml1__AziRef getAzimuthReference() const;

		unsigned int getEastings(double * eastings) const;
		gsoap_witsml1_4_1_1::witsml1__LengthUom getEastingUom() const;

		unsigned int getNorthings(double * northings) const;
		gsoap_witsml1_4_1_1::witsml1__LengthUom getNorthingUom() const;

		unsigned int getTvds(double * tvds) const;
		gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom getTvdUom() const;

		void setTrajectoryStations(
			const unsigned int & trajectoryStationCount,
			const unsigned int & mdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mDUom,
			double * mDSet,
			gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom	angleUom,
			double * inclSet,
			gsoap_witsml1_4_1_1::witsml1__AziRef aziRef,
			double * aziSet);

		void setEastingNorthingTrajectoryStations(
			const unsigned int & trajectoryStationCount,
			const unsigned int & mdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mDUom,
			double * mDSet,
			const unsigned int & tvdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom tVDUom,
			double * tVDSet,
			gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom	angleUom,
			double * inclSet,
			gsoap_witsml1_4_1_1::witsml1__AziRef aziRef,
			double * aziSet,
			gsoap_witsml1_4_1_1::witsml1__LengthUom locationUom,
			double * locationEastingSet,
			double * locationNorthingSet,
			class CoordinateReferenceSystem* wellCrs);

		void setWestingSouthingTrajectoryStations(
			const unsigned int & trajectoryStationCount,
			const unsigned int & mdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mDUom,
			double * mDSet,
			const unsigned int & tvdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom tVDUom,
			double * tVDSet,
			gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom	angleUom,
			double * inclSet,
			gsoap_witsml1_4_1_1::witsml1__AziRef aziRef,
			double * aziSet,
			gsoap_witsml1_4_1_1::witsml1__LengthUom locationUom,
			double * locationWestingSet,
			double * locationSouthingSet,
			class CoordinateReferenceSystem* wellCrs);

		void setProjectedXProjectedYTrajectoryStations(
			const unsigned int & trajectoryStationCount,
			const unsigned int & mdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mDUom,
			double * mDSet,
			const unsigned int & tvdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom tVDUom,
			double * tVDSet,
			gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom	angleUom,
			double * inclSet,
			gsoap_witsml1_4_1_1::witsml1__AziRef aziRef,
			double * aziSet,
			gsoap_witsml1_4_1_1::witsml1__LengthUom locationUom,
			double * locationProjectedXSet,
			double * locationProjectedYSet,
			class CoordinateReferenceSystem* wellCrs);

		void setWellbore(class Wellbore* witsmlWellbore);

		class Wellbore* getWellbore() {return wellbore;}

		RESQML2_0_1_NS::WellboreTrajectoryRepresentation* getResqmlWellboreTrajectoryRepresentation() const {return resqmlWellboreTrajectoryRepresentation;}

		soap* getGSoapContext() const {return collection->soap;}

		const std::string & getTitle() const {return static_cast<gsoap_witsml1_4_1_1::witsml1__obj_USCOREtrajectorys*>(collection)->trajectory[0]->name;}

		std::string getUuid() const {return *static_cast<gsoap_witsml1_4_1_1::witsml1__obj_USCOREtrajectorys*>(collection)->trajectory[0]->uid;}
		time_t getCreation() const
		{
			if (static_cast<gsoap_witsml1_4_1_1::_witsml1__trajectorys*>(collection)->trajectory[0]->commonData->dTimCreation)
				return mktime(static_cast<gsoap_witsml1_4_1_1::_witsml1__trajectorys*>(collection)->trajectory[0]->commonData->dTimCreation);
			else
				return -1;
		}
		time_t getLastUpdate() const
		{
			if (static_cast<gsoap_witsml1_4_1_1::_witsml1__trajectorys*>(collection)->trajectory[0]->commonData->dTimLastChange)
				return mktime(static_cast<gsoap_witsml1_4_1_1::_witsml1__trajectorys*>(collection)->trajectory[0]->commonData->dTimLastChange);
			else
				return -1;
		}

		std::vector<epc::Relationship> getAllEpcRelationships() const;

		/**
		* Resolve all relationships of the object in an epc document.
		*/
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		gsoap_witsml1_4_1_1::witsml1__cs_USCOREtrajectoryStation* newTrajectoryStation(
			gsoap_witsml1_4_1_1::witsml1__cs_USCOREwellDatum* mdDatum,
			gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mDUom,
			const double & mD,
			gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom 	angleUom,
			const double & incl,
			const double & azi);

		gsoap_witsml1_4_1_1::witsml1__cs_USCOREtrajectoryStation* newTrajectoryStation(
			gsoap_witsml1_4_1_1::witsml1__cs_USCOREwellDatum* mdDatum,
			gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mDUom,
			const double & mD,
			gsoap_witsml1_4_1_1::witsml1__cs_USCOREwellDatum* tvdDatum,
			gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom tVDUom,
			const double & tVD,
			gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom 	angleUom,
			const double & incl,
			const double & azi);

		gsoap_witsml1_4_1_1::witsml1__cs_USCOREtrajectoryStation* newTrajectoryStation(
			gsoap_witsml1_4_1_1::witsml1__cs_USCOREwellDatum* mdDatum,
			gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mDUom,
			const double & mD,
			gsoap_witsml1_4_1_1::witsml1__cs_USCOREwellDatum* tvdDatum,
			gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom tVDUom,
			const double & tVD);

		// XML forwards relationship
		class Wellbore* wellbore;

		// XML backwards relationship
		RESQML2_0_1_NS::WellboreTrajectoryRepresentation* resqmlWellboreTrajectoryRepresentation;
		
		friend void RESQML2_0_1_NS::WellboreTrajectoryRepresentation::setWitsmlTrajectory(Trajectory * witsmlTraj);
	};
}

