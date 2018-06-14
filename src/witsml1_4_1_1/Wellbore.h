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
#include "witsml1_4_1_1/Trajectory.h"
#include "witsml1_4_1_1/Log.h"
#include "witsml1_4_1_1/FormationMarker.h"

#include "resqml2_0_1/WellboreFeature.h"

namespace WITSML1_4_1_1_NS
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

		RESQML2_0_1_NS::WellboreFeature* getResqmlWellboreFeature() const {return resqmlWellboreFeature;}

		soap* getGSoapContext() const {return collection->soap;}

		const std::vector<Trajectory*>& getTrajectories() const {return trajectorySet;}

		const std::vector<Log*>& getLogs() const {return logSet;}

		const std::vector<FormationMarker*>& getFormationMarkers() const {return formationMarkerSet;}

		const std::string & getTitle() const {return static_cast<gsoap_witsml1_4_1_1::witsml1__obj_USCOREwellbores*>(collection)->wellbore[0]->name;}

		std::string getUuid() const {return *static_cast<gsoap_witsml1_4_1_1::witsml1__obj_USCOREwellbores*>(collection)->wellbore[0]->uid;}
		time_t getCreation() const
		{
			if (static_cast<gsoap_witsml1_4_1_1::_witsml1__wellbores*>(collection)->wellbore[0]->commonData->dTimCreation)
				return mktime(static_cast<gsoap_witsml1_4_1_1::_witsml1__wellbores*>(collection)->wellbore[0]->commonData->dTimCreation);
			else
				return -1;
		}
		time_t getLastUpdate() const
		{
			if (static_cast<gsoap_witsml1_4_1_1::_witsml1__wellbores*>(collection)->wellbore[0]->commonData->dTimLastChange)
				return mktime(static_cast<gsoap_witsml1_4_1_1::_witsml1__wellbores*>(collection)->wellbore[0]->commonData->dTimLastChange);
			else
				return -1;
		}

		void setShape(const gsoap_witsml1_4_1_1::witsml1__WellboreShape & shape);

		std::vector<epc::Relationship> getAllEpcRelationships() const;

		/**
		* Resolve all relationships of the object in an epc document.
		*/
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		// XML forwards relationship
		class Well* well;

		// XML backwards relationship
		RESQML2_0_1_NS::WellboreFeature* resqmlWellboreFeature;
		std::vector<Trajectory*> trajectorySet;
		std::vector<Log*> logSet;
		std::vector<FormationMarker*> formationMarkerSet;
		
		friend void Trajectory::setWellbore(Wellbore* witsmlWellbore);
		friend void Log::setWellbore(Wellbore* witsmlWellbore);
		friend void FormationMarker::setWellbore(Wellbore* witsmlWellbore);
		friend void RESQML2_0_1_NS::WellboreFeature::setWitsmlWellbore(Wellbore * wellbore);
	};
}

