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

#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"

namespace WITSML1_4_1_1_NS
{
	class DLL_IMPORT_OR_EXPORT FormationMarker : public AbstractObject
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		*/
		FormationMarker(class Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			const unsigned int & mdDatumIndex,
			gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mdUom,
			const double & mdTopSample);

		FormationMarker(class Wellbore* witsmlWellbore,
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

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		FormationMarker(gsoap_witsml1_4_1_1::witsml1__obj_USCOREformationMarkers* fromGsoap):AbstractObject(fromGsoap), wellbore(nullptr), resqmlWellboreMarkerFrameRepresentation(nullptr) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~FormationMarker() {}

		void setWellbore(class Wellbore* witsmlWellbore);

		class Wellbore* getWellbore() {return wellbore;}

		RESQML2_0_1_NS::WellboreMarkerFrameRepresentation* getResqmlWellboreMarkerFrameRepresentation() const {return resqmlWellboreMarkerFrameRepresentation;}

		soap* getGSoapContext() const {return collection->soap;}

		const std::string & getTitle() const {return static_cast<gsoap_witsml1_4_1_1::witsml1__obj_USCOREformationMarkers*>(collection)->formationMarker[0]->name;}

		std::string getUuid() const {return *static_cast<gsoap_witsml1_4_1_1::witsml1__obj_USCOREformationMarkers*>(collection)->formationMarker[0]->uid;}
		time_t getCreation() const
		{
			if (static_cast<gsoap_witsml1_4_1_1::_witsml1__formationMarkers*>(collection)->formationMarker[0]->commonData->dTimCreation)
				return mktime(static_cast<gsoap_witsml1_4_1_1::_witsml1__formationMarkers*>(collection)->formationMarker[0]->commonData->dTimCreation);
			else
				return -1;
		}
		time_t getLastUpdate() const
		{
			if (static_cast<gsoap_witsml1_4_1_1::_witsml1__formationMarkers*>(collection)->formationMarker[0]->commonData->dTimLastChange)
				return mktime(static_cast<gsoap_witsml1_4_1_1::_witsml1__formationMarkers*>(collection)->formationMarker[0]->commonData->dTimLastChange);
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

		// XML forwards relationship
		class Wellbore* wellbore;

		// XML backwards relationship
		RESQML2_0_1_NS::WellboreMarkerFrameRepresentation* resqmlWellboreMarkerFrameRepresentation;
		
		friend void RESQML2_0_1_NS::WellboreMarkerFrameRepresentation::setWitsmlFormationMarker(const unsigned int & resqmlMarkerIndex, FormationMarker * witsmlFormationMarker);
	};
}

