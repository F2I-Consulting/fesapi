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
#include "witsml2_0/Trajectory.h"

#include "witsml2_0/Wellbore.h"

#include <stdexcept>

using namespace std;
using namespace WITSML2_0_NS;
using namespace gsoap_eml2_1;
using namespace epc;

const char* Trajectory::XML_TAG = "Trajectory";

Trajectory::Trajectory(Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title,
	const witsml2__ChannelStatus & growingStatus) :resqmlWellboreTrajectoryRepresentation(nullptr)
{
	if (witsmlWellbore == nullptr) throw invalid_argument("A trajectory must be associated to a well.");

	gsoapProxy2_1 = soap_new_witsml2__Trajectory(witsmlWellbore->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	static_cast<witsml2__Trajectory*>(gsoapProxy2_1)->GrowingStatus = growingStatus;

	setWellbore(witsmlWellbore);
}

gsoap_eml2_1::eml21__DataObjectReference* Trajectory::getWellboreDor() const
{
	return static_cast<witsml2__Trajectory*>(gsoapProxy2_1)->Wellbore;
}

class Wellbore* Trajectory::getWellbore() const
{
	return getEpcDocument()->getResqmlAbstractObjectByUuid<Wellbore>(getWellboreDor()->Uuid);
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
		witsml2__Trajectory* traj = static_cast<witsml2__Trajectory*>(gsoapProxy2_1);
		traj->Wellbore = witsmlWellbore->newEmlReference();
	}
}

witsml2__TrajectoryStation* Trajectory::getTrajectoryStation(const unsigned int & trajStationIndex) const
{
	witsml2__Trajectory* traj = static_cast<witsml2__Trajectory*>(gsoapProxy2_1);
	if (traj->TrajectoryStation.size() <= trajStationIndex) {
		throw range_error("The trajectory station is out of range");
	}

	return traj->TrajectoryStation[trajStationIndex];
}

double Trajectory::getMd(const unsigned int & trajStationIndex) const
{
	return getTrajectoryStation(trajStationIndex)->Md->__item;
}

gsoap_eml2_1::eml21__LengthUom Trajectory::getMdUom(const unsigned int & trajStationIndex) const
{
	return getTrajectoryStation(trajStationIndex)->Md->uom;
}

std::string Trajectory::getMdDatum(const unsigned int & trajStationIndex) const
{
	return getTrajectoryStation(trajStationIndex)->Md->datum;
}

unsigned int Trajectory::getTrajectoryStationCount() const
{
	return static_cast<witsml2__Trajectory*>(gsoapProxy2_1)->TrajectoryStation.size();
}

witsml2__TrajStationType Trajectory::getTrajStationType(const unsigned int & trajStationIndex) const
{
	return getTrajectoryStation(trajStationIndex)->TypeTrajStation;
}

void Trajectory::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	gsoap_eml2_1::eml21__DataObjectReference* dor = getWellboreDor();
	Wellbore* wellbore = epcDoc->getResqmlAbstractObjectByUuid<Wellbore>(dor->Uuid);
	/*
	if (well == nullptr) { // partial transfer
	getEpcDocument()->createPartial(dor);
	well = getEpcDocument()->getResqmlAbstractObjectByUuid<well>(dor->Uuid);
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

