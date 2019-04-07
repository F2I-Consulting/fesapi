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
#include "witsml2_1/Trajectory.h"

#include "witsml2_1/Wellbore.h"

#include <stdexcept>

using namespace std;
using namespace WITSML2_1_NS;
using namespace gsoap_eml2_2;
using namespace epc;

const char* Trajectory::XML_TAG = "Trajectory";

Trajectory::Trajectory(Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title,
	const witsml2__ChannelStatus & growingStatus) :resqmlWellboreTrajectoryRepresentation(nullptr)
{
	if (witsmlWellbore == nullptr) throw invalid_argument("A trajectory must be associated to a well.");

	gsoapProxy2_2 = soap_new_witsml2__Trajectory(witsmlWellbore->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	static_cast<witsml2__Trajectory*>(gsoapProxy2_2)->GrowingStatus = growingStatus;

	setWellbore(witsmlWellbore);
}

gsoap_eml2_2::eml22__DataObjectReference* Trajectory::getWellboreDor() const
{
	return static_cast<witsml2__Trajectory*>(gsoapProxy2_2)->Wellbore;
}

class Wellbore* Trajectory::getWellbore() const
{
	return getEpcDocument()->getDataObjectByUuid<Wellbore>(getWellboreDor()->Uuid);
}

void Trajectory::setWellbore(Wellbore* witsmlWellbore)
{
	if (witsmlWellbore == nullptr) {
		throw invalid_argument("Cannot set a null witsml Wellbore to a witsml trajectory");
	}

	// EPC
	witsmlWellbore->trajectorySet.push_back(this);

	// XML
	if (updateXml) {
		witsml2__Trajectory* traj = static_cast<witsml2__Trajectory*>(gsoapProxy2_2);
		traj->Wellbore = witsmlWellbore->newEml22Reference();
	}
}

witsml2__TrajectoryStation* Trajectory::getTrajectoryStation(const unsigned int & trajStationIndex) const
{
	witsml2__Trajectory* traj = static_cast<witsml2__Trajectory*>(gsoapProxy2_2);
	if (traj->TrajectoryStation.size() <= trajStationIndex) {
		throw range_error("The trajectory station is out of range");
	}

	return traj->TrajectoryStation[trajStationIndex];
}

double Trajectory::getMd(const unsigned int & trajStationIndex) const
{
	return getTrajectoryStation(trajStationIndex)->Md->__item;
}

eml22__LengthUom Trajectory::getMdUom(const unsigned int & trajStationIndex) const
{
	return getTrajectoryStation(trajStationIndex)->Md->uom;
}

std::string Trajectory::getMdDatum(const unsigned int & trajStationIndex) const
{
	return getTrajectoryStation(trajStationIndex)->Md->datum;
}

unsigned int Trajectory::getTrajectoryStationCount() const
{
	return static_cast<witsml2__Trajectory*>(gsoapProxy2_2)->TrajectoryStation.size();
}

witsml2__TrajStationType Trajectory::getTrajStationType(const unsigned int & trajStationIndex) const
{
	return getTrajectoryStation(trajStationIndex)->TypeTrajStation;
}

void Trajectory::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	eml22__DataObjectReference* dor = getWellboreDor();
	Wellbore* wellbore = epcDoc->getDataObjectByUuid<Wellbore>(dor->Uuid);
	/*
	if (well == nullptr) { // partial transfer
	getEpcDocument()->createPartial(dor);
	well = getEpcDocument()->getDataObjectByUuid<well>(dor->Uuid);
	}
	*/
	if (wellbore == nullptr) {
		throw invalid_argument("The DOR looks invalid.");
	}
	updateXml = false;
	setWellbore(wellbore);
	updateXml = true;
}

vector<Relationship> Trajectory::getAllEpcRelationships() const
{
	vector<Relationship> result;

	// XML forward relationship
	Wellbore* wellbore = getWellbore();
	Relationship relWellbore(wellbore->getPartNameInEpcDocument(), "", wellbore->getUuid());
	relWellbore.setDestinationObjectType();
	result.push_back(relWellbore);

	// XML backward relationship
	if (resqmlWellboreTrajectoryRepresentation != nullptr)
	{
		Relationship rel(resqmlWellboreTrajectoryRepresentation->getPartNameInEpcDocument(), "", resqmlWellboreTrajectoryRepresentation->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

