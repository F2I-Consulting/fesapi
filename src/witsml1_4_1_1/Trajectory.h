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

#include "witsml1_4_1_1/AbstractObject.h"

#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"

namespace witsml1_4_1_1
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

		resqml2_0_1::WellboreTrajectoryRepresentation* getResqmlWellboreTrajectoryRepresentation() const {return resqmlWellboreTrajectoryRepresentation;}

		soap* getGSoapContext() const {return collection->soap;}

		const std::string & getTitle() const {return static_cast<gsoap_witsml1_4_1_1::witsml1__obj_USCOREtrajectorys*>(collection)->trajectory[0]->name;}

		std::string getUuid() const {return *static_cast<gsoap_witsml1_4_1_1::witsml1__obj_USCOREtrajectorys*>(collection)->trajectory[0]->uid;}
		time_t getCreation() const
		{
			if (static_cast<gsoap_witsml1_4_1_1::_witsml1__trajectorys*>(collection)->trajectory[0]->commonData->dTimCreation)
				return *static_cast<gsoap_witsml1_4_1_1::_witsml1__trajectorys*>(collection)->trajectory[0]->commonData->dTimCreation;
			else
				return -1;
		}
		time_t getLastUpdate() const
		{
			if (static_cast<gsoap_witsml1_4_1_1::_witsml1__trajectorys*>(collection)->trajectory[0]->commonData->dTimLastChange)
				return *static_cast<gsoap_witsml1_4_1_1::_witsml1__trajectorys*>(collection)->trajectory[0]->commonData->dTimLastChange;
			else
				return -1;
		}

		std::vector<epc::Relationship> getAllEpcRelationships() const;

		/**
		* Resolve all relationships of the object in an epc document.
		*/
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

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
		resqml2_0_1::WellboreTrajectoryRepresentation* resqmlWellboreTrajectoryRepresentation;
		
		friend void resqml2_0_1::WellboreTrajectoryRepresentation::setWitsmlTrajectory(Trajectory * witsmlTraj);
	};
}
