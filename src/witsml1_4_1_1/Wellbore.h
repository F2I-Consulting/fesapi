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
#include "witsml1_4_1_1/Trajectory.h"
#include "witsml1_4_1_1/Log.h"
#include "witsml1_4_1_1/FormationMarker.h"

#include "resqml2_0_1/WellboreFeature.h"

namespace witsml1_4_1_1
{
	class DLL_IMPORT_OR_EXPORT Wellbore : public AbstractObject
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		*/
		Wellbore(class Well* witsmlWell,
			const std::string & guid,
			const std::string & title);

		Wellbore(class Well* witsmlWell,
			const std::string & guid,
			const std::string & title,
			gsoap_witsml1_4_1_1::witsml1__WellStatus statusWellbore,
			const bool & isActive,
			gsoap_witsml1_4_1_1::witsml1__WellPurpose purposeWellbore,
			gsoap_witsml1_4_1_1::witsml1__WellboreType typeWellbore,
			const bool & achievedTD,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments
		);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		Wellbore(gsoap_witsml1_4_1_1::witsml1__obj_USCOREwellbores* fromGsoap):AbstractObject(fromGsoap), well(nullptr), resqmlWellboreFeature(nullptr) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~Wellbore() {}

		Trajectory* createTrajectory(
			const std::string & guid,
			const std::string & title);

		Trajectory* createTrajectory(
			const std::string & guid,
			const std::string & title,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments);

		Log* createLog(
			const std::string & guid,
			const std::string & title,
			gsoap_witsml1_4_1_1::witsml1__LogIndexType indexType,
			const std::string & indexCurve);

		Log* createLog(
			const std::string & guid,
			const std::string & title,
			gsoap_witsml1_4_1_1::witsml1__LogIndexType indexType,
			const std::string & indexCurve,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments);
		
		FormationMarker* createFormationMarker(
			const std::string & guid,
			const std::string & title,
			const unsigned int & mdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mdUom,
			const double & mdTopSample);

		FormationMarker* createFormationMarker(
			const std::string & guid,
			const std::string & title,
			const unsigned int & mdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mdUom,
			const double & mdTopSample,
			const unsigned int & tvdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom tvdUom,
			const double & tvdTopSample,
			gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom dipUom,
			const double & dip,
			gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom dipDirectionUom,
			const double & dipDirection,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments);

		void setWell(class Well* witsmlWell);

		class Well* getWell() {return well;}

		resqml2_0_1::WellboreFeature* getResqmlWellboreFeature() const {return resqmlWellboreFeature;}

		soap* getGSoapContext() const {return collection->soap;}

		const std::vector<Trajectory*>& getTrajectories() const {return trajectorySet;}

		const std::vector<Log*>& getLogs() const {return logSet;}

		const std::vector<FormationMarker*>& getFormationMarkers() const {return formationMarkerSet;}

		const std::string & getTitle() const {return static_cast<gsoap_witsml1_4_1_1::witsml1__obj_USCOREwellbores*>(collection)->wellbore[0]->name;}

		std::string getUuid() const {return *static_cast<gsoap_witsml1_4_1_1::witsml1__obj_USCOREwellbores*>(collection)->wellbore[0]->uid;}
		time_t getCreation() const
		{
			if (static_cast<gsoap_witsml1_4_1_1::_witsml1__wellbores*>(collection)->wellbore[0]->commonData->dTimCreation)
				return *static_cast<gsoap_witsml1_4_1_1::_witsml1__wellbores*>(collection)->wellbore[0]->commonData->dTimCreation;
			else
				return -1;
		}
		time_t getLastUpdate() const
		{
			if (static_cast<gsoap_witsml1_4_1_1::_witsml1__wellbores*>(collection)->wellbore[0]->commonData->dTimLastChange)
				return *static_cast<gsoap_witsml1_4_1_1::_witsml1__wellbores*>(collection)->wellbore[0]->commonData->dTimLastChange;
			else
				return -1;
		}

		void setShape(const gsoap_witsml1_4_1_1::witsml1__WellboreShape & shape);

		std::vector<epc::Relationship> getAllEpcRelationships() const;

		/**
		* Resolve all relationships of the object in an epc document.
		*/
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		// XML forwards relationship
		class Well* well;

		// XML backwards relationship
		resqml2_0_1::WellboreFeature* resqmlWellboreFeature;
		std::vector<Trajectory*> trajectorySet;
		std::vector<Log*> logSet;
		std::vector<FormationMarker*> formationMarkerSet;
		
		friend void Trajectory::setWellbore(Wellbore* witsmlWellbore);
		friend void Log::setWellbore(Wellbore* witsmlWellbore);
		friend void FormationMarker::setWellbore(Wellbore* witsmlWellbore);
		friend void resqml2_0_1::WellboreFeature::setWitsmlWellbore(Wellbore * wellbore);
	};
}
