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
#include "witsml1_4_1_1/Trajectory.h"

#include <stdexcept>

#include "tools/GuidTools.h"
#include "witsml1_4_1_1/Well.h"
#include "witsml1_4_1_1/CoordinateReferenceSystem.h"

using namespace std;
using namespace WITSML1_4_1_1_NS;
using namespace gsoap_witsml1_4_1_1;
using namespace epc;

const char* Trajectory::XML_TAG = "trajectorys";

Trajectory::Trajectory(Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title):resqmlWellboreTrajectoryRepresentation(nullptr)
{
	if (witsmlWellbore == nullptr) throw invalid_argument("A trajectory must be associated to a well.");
	if (title.empty()) throw invalid_argument("A trajectory must have a name.");

	collection = soap_new_witsml1__obj_USCOREtrajectorys(witsmlWellbore->getGSoapContext(), 1);	
	static_cast<_witsml1__trajectorys*>(collection)->version = SCHEMA_VERSION;

	witsml1__obj_USCOREtrajectory* traj = soap_new_witsml1__obj_USCOREtrajectory(collection->soap, 1);
	static_cast<_witsml1__trajectorys*>(collection)->trajectory.push_back(traj);

	setWellbore(witsmlWellbore);

	traj->uid = soap_new_std__string(collection->soap, 1);
	if (guid.empty()) {
		traj->uid->assign(GuidTools::generateUidAsString());
	} else {
		traj->uid->assign(guid);
	}

	traj->name = title;
}

Trajectory::Trajectory(Wellbore* witsmlWellbore,
		const std::string & guid,
		const std::string & title,
		const std::string & sourceName,
		const time_t & dTimCreation,
		const time_t & dTimLastChange,
		const std::string & comments
	):resqmlWellboreTrajectoryRepresentation(nullptr)
{
	if (witsmlWellbore == nullptr) throw invalid_argument("A trajectory must be associated to a well.");
	if (title.empty()) throw invalid_argument("A trajectory must have a name.");

	collection = soap_new_witsml1__obj_USCOREtrajectorys(witsmlWellbore->getGSoapContext(), 1);	
	static_cast<_witsml1__trajectorys*>(collection)->version = SCHEMA_VERSION;

	witsml1__obj_USCOREtrajectory* traj = soap_new_witsml1__obj_USCOREtrajectory(collection->soap, 1);
	static_cast<_witsml1__trajectorys*>(collection)->trajectory.push_back(traj);

	setWellbore(witsmlWellbore);

	traj->uid = soap_new_std__string(traj->soap, 1);
	if (guid.empty()) {
		traj->uid->assign(GuidTools::generateUidAsString());
	} else {
		traj->uid->assign(guid);
	}

	traj->name = title;

	// create the commonData attribute, if necessary
	if (!sourceName.empty() || dTimCreation>=0 || dTimLastChange>=0 || !comments.empty())
	{
		traj->commonData = newCommonData(sourceName,
			dTimCreation,
			dTimLastChange,
			comments);
	}
}

void Trajectory::setWellbore(Wellbore* witsmlWellbore)
{
	wellbore = witsmlWellbore;
	witsmlWellbore->trajectorySet.push_back(this);

	if (updateXml)
	{
		witsml1__obj_USCOREtrajectory* traj = static_cast<_witsml1__trajectorys*>(collection)->trajectory[0];
		traj->nameWellbore = witsmlWellbore->getTitle();
		traj->uidWellbore = soap_new_std__string(collection->soap, 1);
		traj->uidWellbore->assign(witsmlWellbore->getUuid());

		traj->nameWell = witsmlWellbore->getWell()->getTitle();
		traj->uidWell = soap_new_std__string(collection->soap, 1);
		traj->uidWell->assign(witsmlWellbore->getWell()->getUuid());
	}
}

gsoap_witsml1_4_1_1::witsml1__cs_USCOREtrajectoryStation* Trajectory::newTrajectoryStation(
	witsml1__cs_USCOREwellDatum* mdDatum,
	gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mDUom,
	const double & mD,
	gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom 	angleUom,
	const double & incl,
	const double & azi)
{
	witsml1__cs_USCOREtrajectoryStation* trajectoryStation = soap_new_witsml1__cs_USCOREtrajectoryStation(collection->soap, 1);
	trajectoryStation->typeTrajStation = gsoap_witsml1_4_1_1::witsml1__TrajStationType__unknown;; 

	// md
	trajectoryStation->md = soap_new_witsml1__measuredDepthCoord(collection->soap, 1);
	trajectoryStation->md->uom = mDUom;
	trajectoryStation->md->datum = soap_new_std__string(collection->soap, 1);
	trajectoryStation->md->datum->assign(mdDatum->uid);
	trajectoryStation->md->__item = mD;

	// incl
	trajectoryStation->incl = soap_new_witsml1__planeAngleMeasure(collection->soap, 1);
	trajectoryStation->incl->uom = angleUom;
	trajectoryStation->incl->__item = incl;

	// azi
	trajectoryStation->azi = soap_new_witsml1__planeAngleMeasure(collection->soap, 1);
	trajectoryStation->azi->uom = angleUom;
	trajectoryStation->azi->__item = azi;

	return trajectoryStation;
}

double Trajectory::getMdDatumElevation()
{
	witsml1__obj_USCOREtrajectory* traj = static_cast<_witsml1__trajectorys*>(collection)->trajectory[0];
	if (traj->__obj_USCOREtrajectory_sequence->trajectoryStation.size() && traj->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->md->datum)
	{
		witsml1__cs_USCOREwellDatum* mdDatum = wellbore->getWell()->getDatum(*traj->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->md->datum);
		if (mdDatum->elevation)
			return mdDatum->elevation->__item;
	}

	return std::numeric_limits<double>::quiet_NaN();
}

std::string Trajectory::getMdDatumName()
{
	witsml1__obj_USCOREtrajectory* traj = static_cast<_witsml1__trajectorys*>(collection)->trajectory[0];
	if (traj->__obj_USCOREtrajectory_sequence->trajectoryStation.size() && traj->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->md->datum)
	{
		witsml1__cs_USCOREwellDatum* mdDatum = wellbore->getWell()->getDatum(*traj->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->md->datum);
		return mdDatum->name;
	}

	return "";
}

gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom Trajectory::getMdDatumElevationUom()
{
	witsml1__obj_USCOREtrajectory* traj = static_cast<_witsml1__trajectorys*>(collection)->trajectory[0];
	if (traj->__obj_USCOREtrajectory_sequence->trajectoryStation.size() && traj->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->md->datum)
	{
		witsml1__cs_USCOREwellDatum* mdDatum = wellbore->getWell()->getDatum(*traj->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->md->datum);
		if (mdDatum->elevation)
			return mdDatum->elevation->uom;
	}

	throw invalid_argument("no elevation uom");
}

unsigned int Trajectory::getTrajectoryStationCount() const
{
	if (static_cast<_witsml1__trajectorys*>(collection)->trajectory.size())
		return static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->trajectoryStation.size();
	else
		return 0;
}

void Trajectory::getMds(double * mds) const
{
	__witsml1__obj_USCOREtrajectory_sequence* trajGroup = static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence;
	for (unsigned int ts = 0; ts < trajGroup->trajectoryStation.size(); ++ts)
	{
		mds[ts] = trajGroup->trajectoryStation[ts]->md->__item;
	}
}

gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom Trajectory::getMdUom() const
{
	return static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->md->uom;
}

unsigned int Trajectory::getTvds(double * tvds) const
{
	unsigned int result = 0;
	__witsml1__obj_USCOREtrajectory_sequence* trajGroup = static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence;
	for (unsigned int ts = 0; ts < trajGroup->trajectoryStation.size(); ++ts)
	{
		if (trajGroup->trajectoryStation[ts]->tvd)
		{
			tvds[ts] = trajGroup->trajectoryStation[ts]->tvd->__item;
			++result;
		}
		else
			tvds[ts] = numeric_limits<double>::quiet_NaN();
	}
	return result;
}

gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom Trajectory::getTvdUom() const
{
	return static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->tvd->uom;
}

unsigned int Trajectory::getInclinometries(double * incls) const
{
	unsigned int result = 0;
	__witsml1__obj_USCOREtrajectory_sequence* trajGroup = static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence;
	for (unsigned int ts = 0; ts < trajGroup->trajectoryStation.size(); ++ts)
	{
		if (trajGroup->trajectoryStation[ts]->incl)
		{
			incls[ts] = trajGroup->trajectoryStation[ts]->incl->__item;
			++result;
		}
		else
			incls[ts] = numeric_limits<double>::quiet_NaN();
	}
	return result;
}

gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom Trajectory::getInclinometryUom() const
{
	return static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->incl->uom;
}

unsigned int Trajectory::getAzimuths(double * azims) const
{
	unsigned int result = 0;
	__witsml1__obj_USCOREtrajectory_sequence* trajGroup = static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence;
	for (unsigned int ts = 0; ts < trajGroup->trajectoryStation.size(); ++ts)
	{
		if (trajGroup->trajectoryStation[ts]->azi)
		{
			azims[ts] = trajGroup->trajectoryStation[ts]->azi->__item;
			++result;
		}
		else
			azims[ts] = numeric_limits<double>::quiet_NaN();
	}
	return result;
}

witsml1__PlaneAngleUom Trajectory::getAzimuthUom() const
{
	return static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->azi->uom;
}

witsml1__AziRef Trajectory::getAzimuthReference() const
{
	if (static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->aziRef)
		return *static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->aziRef;
	else
		return witsml1__AziRef__unknown;
}

unsigned int Trajectory::getEastings(double * eastings) const
{
	unsigned int result = 0;
	__witsml1__obj_USCOREtrajectory_sequence* trajGroup = static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence;
	for (unsigned int ts = 0; ts < trajGroup->trajectoryStation.size(); ++ts)
	{
		if (trajGroup->trajectoryStation[ts]->location.size() && trajGroup->trajectoryStation[ts]->location[0]->easting)
		{
			eastings[ts] = trajGroup->trajectoryStation[ts]->location[0]->easting->__item;
			++result;
		}
		else  if (trajGroup->trajectoryStation[ts]->location.size() && trajGroup->trajectoryStation[ts]->location[0]->westing)
		{
			eastings[ts] = - trajGroup->trajectoryStation[ts]->location[0]->westing->__item;
			++result;
		}
		else
			eastings[ts] = numeric_limits<double>::quiet_NaN();
	}
	return result;
}

gsoap_witsml1_4_1_1::witsml1__LengthUom Trajectory::getEastingUom() const
{
	if (static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->trajectoryStation.size() &&
		static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->location.size())
	{
		if (static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->location[0]->easting)
			return static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->location[0]->easting->uom;
		else if (static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->location[0]->westing)
			return static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->location[0]->westing->uom;
	}
	
	throw invalid_argument("no uom");
}

unsigned int Trajectory::getNorthings(double * northings) const
{
	unsigned int result = 0;
	__witsml1__obj_USCOREtrajectory_sequence* trajGroup = static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence;
	for (unsigned int ts = 0; ts < trajGroup->trajectoryStation.size(); ++ts)
	{
		if (trajGroup->trajectoryStation[ts]->location.size() && trajGroup->trajectoryStation[ts]->location[0]->northing)
		{
			northings[ts] = trajGroup->trajectoryStation[ts]->location[0]->northing->__item;
			++result;
		}
		else  if (trajGroup->trajectoryStation[ts]->location.size() && trajGroup->trajectoryStation[ts]->location[0]->southing)
		{
			northings[ts] = - trajGroup->trajectoryStation[ts]->location[0]->southing->__item;
			++result;
		}
		else
			northings[ts] = numeric_limits<double>::quiet_NaN();
	}
	return result;
}

gsoap_witsml1_4_1_1::witsml1__LengthUom Trajectory::getNorthingUom() const
{
	if (static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->trajectoryStation.size() &&
		static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->location.size())
	{
		if (static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->location[0]->northing)
			return static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->location[0]->northing->uom;
		else if (static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->location[0]->southing)
			return static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence->trajectoryStation[0]->location[0]->southing->uom;
	}
	
	throw invalid_argument("no uom");
}

gsoap_witsml1_4_1_1::witsml1__cs_USCOREtrajectoryStation* Trajectory::newTrajectoryStation(
	witsml1__cs_USCOREwellDatum* mdDatum,
	gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mDUom,
	const double & mD,
	witsml1__cs_USCOREwellDatum* tvdDatum,
	gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom tVDUom,
	const double & tVD,
	gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom 	angleUom,
	const double & incl,
	const double & azi)
{
	witsml1__cs_USCOREtrajectoryStation* trajectoryStation = soap_new_witsml1__cs_USCOREtrajectoryStation(collection->soap, 1);
	trajectoryStation->typeTrajStation = gsoap_witsml1_4_1_1::witsml1__TrajStationType__unknown;; 

	// md
	trajectoryStation->md = soap_new_witsml1__measuredDepthCoord(collection->soap, 1);
	trajectoryStation->md->uom = mDUom;
	trajectoryStation->md->datum = soap_new_std__string(collection->soap, 1);
	trajectoryStation->md->datum->assign(mdDatum->uid);
	trajectoryStation->md->__item = mD;

	// tvd
	trajectoryStation->tvd = soap_new_witsml1__wellVerticalDepthCoord(collection->soap, 1);
	trajectoryStation->tvd->uom = tVDUom;
	trajectoryStation->tvd->datum = soap_new_std__string(collection->soap, 1);
	trajectoryStation->tvd->datum->assign(tvdDatum->uid);
	trajectoryStation->tvd->__item = tVD;

	// incl
	trajectoryStation->incl = soap_new_witsml1__planeAngleMeasure(collection->soap, 1);
	trajectoryStation->incl->uom = angleUom;
	trajectoryStation->incl->__item = incl;

	// azi
	trajectoryStation->azi = soap_new_witsml1__planeAngleMeasure(collection->soap, 1);
	trajectoryStation->azi->uom = angleUom;
	trajectoryStation->azi->__item = azi;

	return trajectoryStation;
}

gsoap_witsml1_4_1_1::witsml1__cs_USCOREtrajectoryStation* Trajectory::newTrajectoryStation(
	witsml1__cs_USCOREwellDatum* mdDatum,
	gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mDUom,
	const double & mD,
	witsml1__cs_USCOREwellDatum* tvdDatum,
	gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom tVDUom,
	const double & tVD)
{
	witsml1__cs_USCOREtrajectoryStation* trajectoryStation = soap_new_witsml1__cs_USCOREtrajectoryStation(collection->soap, 1);
	trajectoryStation->typeTrajStation = gsoap_witsml1_4_1_1::witsml1__TrajStationType__unknown;;

	// md
	trajectoryStation->md = soap_new_witsml1__measuredDepthCoord(collection->soap, 1);
	trajectoryStation->md->uom = mDUom;
	trajectoryStation->md->datum = soap_new_std__string(collection->soap, 1);
	trajectoryStation->md->datum->assign(mdDatum->uid);
	trajectoryStation->md->__item = mD;

	// tvd
	trajectoryStation->tvd = soap_new_witsml1__wellVerticalDepthCoord(collection->soap, 1);
	trajectoryStation->tvd->uom = tVDUom;
	trajectoryStation->tvd->datum = soap_new_std__string(collection->soap, 1);
	trajectoryStation->tvd->datum->assign(tvdDatum->uid);
	trajectoryStation->tvd->__item = tVD;

	return trajectoryStation;
}

bool isVerticalLookingAtXyz(const unsigned int & locationCount, double * locationXSet, double * locationYSet)
{
	for (unsigned int i=1; i<locationCount; ++i)
	{
		if (locationXSet[i] != locationXSet[0] || locationYSet[i] != locationYSet[0])
			return false;
	}

	return true;
}
bool isVerticalLookingAtInclAzi(const unsigned int & count, double * inclSet, double * aziSet)
{
	for (unsigned int i=1; i<count; ++i)
	{
		if (inclSet[i] != .0 || aziSet[i] != .0)
			return false;
	}

	return true;
}


void Trajectory::setTrajectoryStations(
		const unsigned int & trajectoryStationCount,
		const unsigned int & mdDatumIndex,
		witsml1__MeasuredDepthUom mDUom,
		double * mDSet,
		witsml1__PlaneAngleUom	angleUom,
		double * inclSet,
		witsml1__AziRef aziRef,
		double * aziSet)
{
	if (mDSet == nullptr)
		throw invalid_argument("There is no mds.");
	if (inclSet == nullptr)
		throw invalid_argument("There is no inclinometries.");
	if (aziSet == nullptr)
		throw invalid_argument("There is no aimuths.");

	witsml1__cs_USCOREwellDatum* mdDatum = wellbore->getWell()->getDatum(mdDatumIndex);
	__witsml1__obj_USCOREtrajectory_sequence* trajectorySequence = soap_new___witsml1__obj_USCOREtrajectory_sequence(collection->soap, 1);

	// set the azimuthal reference
	trajectorySequence->aziRef = (witsml1__AziRef *)soap_malloc(collection->soap, sizeof(witsml1__AziRef));
	*trajectorySequence->aziRef = aziRef; 

	// construction of the trajectory stations and computing of mdMn and mdMx
	double mdMn = mDSet[0];
	double mdMx = mDSet[0];
	for (unsigned int i=0 ; i<trajectoryStationCount ; ++i)
	{
		if (mDSet[i]<mdMn) mdMn = mDSet[i];
		if (mDSet[i]>mdMx) mdMx = mDSet[i];

		witsml1__cs_USCOREtrajectoryStation* trajectoryStation = newTrajectoryStation(mdDatum, mDUom, mDSet[i], angleUom, inclSet[i], aziSet[i]);
		trajectorySequence->trajectoryStation.push_back(trajectoryStation);
	}

	// assignment of trajectory mdMn
	trajectorySequence->mdMn = soap_new_witsml1__measuredDepthCoord(collection->soap, 1);
	trajectorySequence->mdMn->uom = mDUom;
	trajectorySequence->mdMn->datum = soap_new_std__string(collection->soap, 1);
	trajectorySequence->mdMn->datum->assign(mdDatum->uid);
	trajectorySequence->mdMn->__item = mdMn;

	// assignment of trajectory mdMx
	trajectorySequence->mdMx = soap_new_witsml1__measuredDepthCoord(collection->soap, 1);
	trajectorySequence->mdMx->uom = mDUom;
	trajectorySequence->mdMx->datum = soap_new_std__string(collection->soap, 1);
	trajectorySequence->mdMx->datum->assign(mdDatum->uid);
	trajectorySequence->mdMx->__item = mdMx;

	static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence = trajectorySequence;

	// assignment of wellbore shape
	if (isVerticalLookingAtInclAzi(trajectoryStationCount, inclSet, aziSet))
		wellbore->setShape(witsml1__WellboreShape__vertical); 
	else 
		// TODO: deviated ?
		wellbore->setShape(witsml1__WellboreShape__unknown);
}

void Trajectory::setEastingNorthingTrajectoryStations(
		const unsigned int & trajectoryStationCount,
		const unsigned int & mdDatumIndex,
		witsml1__MeasuredDepthUom mDUom,
		double * mDSet,
		const unsigned int & tvdDatumIndex,
		witsml1__WellVerticalCoordinateUom tVDUom,
		double * tVDSet,
		witsml1__PlaneAngleUom	angleUom,
		double * inclSet,
		witsml1__AziRef aziRef,
		double * aziSet,
		witsml1__LengthUom locationUom,
		double * locationEastingSet,
		double * locationNorthingSet,
		CoordinateReferenceSystem* wellCrs)
{
	if (mDSet == nullptr)
		throw invalid_argument("There is no mds.");
	if (tVDSet == nullptr)
		throw invalid_argument("There is no tvds.");
	if (locationEastingSet == nullptr)
		throw invalid_argument("There is no projected x values.");
	if (locationNorthingSet == nullptr)
		throw invalid_argument("There is no projected y values.");

	witsml1__cs_USCOREwellDatum* mdDatum = wellbore->getWell()->getDatum(mdDatumIndex);
	witsml1__cs_USCOREwellDatum* tvdDatum = wellbore->getWell()->getDatum(tvdDatumIndex);
	__witsml1__obj_USCOREtrajectory_sequence* trajectorySequence = soap_new___witsml1__obj_USCOREtrajectory_sequence(collection->soap, 1);

	// set the azimuthal reference
	trajectorySequence->aziRef = (witsml1__AziRef *)soap_malloc(collection->soap, sizeof(witsml1__AziRef));
	*trajectorySequence->aziRef = aziRef; 

	// construction of the trajectory stations and computing of mdMn and mdMx
	double mdMn = mDSet[0];
	double mdMx = mDSet[0];
	if (inclSet != nullptr && aziSet != nullptr)
	{
		for (unsigned int i = 0; i < trajectoryStationCount; ++i)
		{
			if (mDSet[i] < mdMn) mdMn = mDSet[i];
			if (mDSet[i] > mdMx) mdMx = mDSet[i];

			witsml1__cs_USCOREtrajectoryStation* trajectoryStation = newTrajectoryStation(mdDatum, mDUom, mDSet[i], tvdDatum, tVDUom, tVDSet[i], angleUom, inclSet[i], aziSet[i]);
			witsml1__cs_USCORElocation* location = constructEastingNorthingLocation(locationUom, locationEastingSet[i], locationNorthingSet[i], wellCrs);
			trajectoryStation->location.push_back(location);
			trajectorySequence->trajectoryStation.push_back(trajectoryStation);
		}
	}
	else
	{
		for (unsigned int i = 0; i < trajectoryStationCount; ++i)
		{
			if (mDSet[i] < mdMn) mdMn = mDSet[i];
			if (mDSet[i] > mdMx) mdMx = mDSet[i];

			witsml1__cs_USCOREtrajectoryStation* trajectoryStation = newTrajectoryStation(mdDatum, mDUom, mDSet[i], tvdDatum, tVDUom, tVDSet[i]);
			witsml1__cs_USCORElocation* location = constructEastingNorthingLocation(locationUom, locationEastingSet[i], locationNorthingSet[i], wellCrs);
			trajectoryStation->location.push_back(location);
			trajectorySequence->trajectoryStation.push_back(trajectoryStation);
		}
	}

	// assignment of trajectory mdMn
	trajectorySequence->mdMn = soap_new_witsml1__measuredDepthCoord(collection->soap, 1);
	trajectorySequence->mdMn->uom = mDUom;
	trajectorySequence->mdMn->datum = soap_new_std__string(collection->soap, 1);
	trajectorySequence->mdMn->datum->assign(mdDatum->uid);
	trajectorySequence->mdMn->__item = mdMn;

	// assignment of trajectory mdMx
	trajectorySequence->mdMx = soap_new_witsml1__measuredDepthCoord(collection->soap, 1);
	trajectorySequence->mdMx->uom = mDUom;
	trajectorySequence->mdMx->datum = soap_new_std__string(collection->soap, 1);
	trajectorySequence->mdMx->datum->assign(mdDatum->uid);
	trajectorySequence->mdMx->__item = mdMx;

	static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence = trajectorySequence;

	// assignment of wellbore shape
	if (isVerticalLookingAtXyz(trajectoryStationCount, locationEastingSet, locationNorthingSet))
		wellbore->setShape(witsml1__WellboreShape__vertical); 
	else 
		// TODO: deviated ?
		wellbore->setShape(witsml1__WellboreShape__unknown);
}

void Trajectory::setWestingSouthingTrajectoryStations(
		const unsigned int & trajectoryStationCount,
		const unsigned int & mdDatumIndex,
		witsml1__MeasuredDepthUom mDUom,
		double * mDSet,
		const unsigned int & tvdDatumIndex,
		witsml1__WellVerticalCoordinateUom tVDUom,
		double * tVDSet,
		witsml1__PlaneAngleUom	angleUom,
		double * inclSet,
		witsml1__AziRef aziRef,
		double * aziSet,
		witsml1__LengthUom locationUom,
		double * locationWestingSet,
		double * locationSouthingSet,
		CoordinateReferenceSystem* wellCrs)
{
	witsml1__cs_USCOREwellDatum* mdDatum = wellbore->getWell()->getDatum(mdDatumIndex);
	witsml1__cs_USCOREwellDatum* tvdDatum = wellbore->getWell()->getDatum(tvdDatumIndex);
	__witsml1__obj_USCOREtrajectory_sequence* trajectorySequence = soap_new___witsml1__obj_USCOREtrajectory_sequence(collection->soap, 1);

	// set the azimuthal reference
	trajectorySequence->aziRef = (witsml1__AziRef *)soap_malloc(collection->soap, sizeof(witsml1__AziRef));
	*trajectorySequence->aziRef = aziRef; 

	// construction of the trajectory stations and computing of mdMn and mdMx
	double mdMn = mDSet[0];
	double mdMx = mDSet[0];
	for (unsigned int i=0 ; i<trajectoryStationCount ; ++i)
	{
		if (mDSet[i]<mdMn) mdMn = mDSet[i];
		if (mDSet[i]>mdMx) mdMx = mDSet[i];

		witsml1__cs_USCOREtrajectoryStation* trajectoryStation = newTrajectoryStation(mdDatum, mDUom, mDSet[i], tvdDatum, tVDUom, tVDSet[i], angleUom, inclSet[i], aziSet[i]);
		witsml1__cs_USCORElocation* location = constructWestingSouthingLocation(locationUom, locationWestingSet[i], locationSouthingSet[i], wellCrs);
		trajectoryStation->location.push_back(location);
		trajectorySequence->trajectoryStation.push_back(trajectoryStation);
	}

	// assignment of trajectory mdMn
	trajectorySequence->mdMn = soap_new_witsml1__measuredDepthCoord(collection->soap, 1);
	trajectorySequence->mdMn->uom = mDUom;
	trajectorySequence->mdMn->datum = soap_new_std__string(collection->soap, 1);
	trajectorySequence->mdMn->datum->assign(mdDatum->uid);
	trajectorySequence->mdMn->__item = mdMn;

	// assignment of trajectory mdMx
	trajectorySequence->mdMx = soap_new_witsml1__measuredDepthCoord(collection->soap, 1);
	trajectorySequence->mdMx->uom = mDUom;
	trajectorySequence->mdMx->datum = soap_new_std__string(collection->soap, 1);
	trajectorySequence->mdMx->datum->assign(mdDatum->uid);
	trajectorySequence->mdMx->__item = mdMx;

	static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence = trajectorySequence;

	// assignment of wellbore shape
	if (isVerticalLookingAtXyz(trajectoryStationCount, locationWestingSet, locationSouthingSet))
		wellbore->setShape(witsml1__WellboreShape__vertical); 
	else 
		// TODO: deviated ?
		wellbore->setShape(witsml1__WellboreShape__unknown);
}

void Trajectory::setProjectedXProjectedYTrajectoryStations(
		const unsigned int & trajectoryStationCount,
		const unsigned int & mdDatumIndex,
		witsml1__MeasuredDepthUom mDUom,
		double * mDSet,
		const unsigned int & tvdDatumIndex,
		witsml1__WellVerticalCoordinateUom tVDUom,
		double * tVDSet,
		witsml1__PlaneAngleUom	angleUom,
		double * inclSet,
		witsml1__AziRef aziRef,
		double * aziSet,
		witsml1__LengthUom locationUom,
		double * locationProjectedXSet,
		double * locationProjectedYSet,
		CoordinateReferenceSystem* wellCrs)
{
	if (mDSet == nullptr)
		throw invalid_argument("There is no mds.");
	if (tVDSet == nullptr)
		throw invalid_argument("There is no tvds.");
	if (locationProjectedXSet == nullptr)
		throw invalid_argument("There is no projected x values.");
	if (locationProjectedYSet == nullptr)
		throw invalid_argument("There is no projected y values.");

	witsml1__cs_USCOREwellDatum* mdDatum = wellbore->getWell()->getDatum(mdDatumIndex);
	witsml1__cs_USCOREwellDatum* tvdDatum = wellbore->getWell()->getDatum(tvdDatumIndex);
	__witsml1__obj_USCOREtrajectory_sequence* trajectorySequence = soap_new___witsml1__obj_USCOREtrajectory_sequence(collection->soap, 1);

	// set the azimuthal reference
	trajectorySequence->aziRef = (witsml1__AziRef *)soap_malloc(collection->soap, sizeof(witsml1__AziRef));
	*trajectorySequence->aziRef = aziRef; 

	// construction of the trajectory stations and computing of mdMn and mdMx
	double mdMn = mDSet[0];
	double mdMx = mDSet[0];

	if (inclSet != nullptr && aziSet != nullptr)
	{
		for (unsigned int i = 0; i < trajectoryStationCount; ++i)
		{
			if (mDSet[i] < mdMn) mdMn = mDSet[i];
			if (mDSet[i] > mdMx) mdMx = mDSet[i];

			witsml1__cs_USCOREtrajectoryStation* trajectoryStation = newTrajectoryStation(mdDatum, mDUom, mDSet[i], tvdDatum, tVDUom, tVDSet[i], angleUom, inclSet[i], aziSet[i]);
			witsml1__cs_USCORElocation* location = constructProjectedXProjectedYLocation(locationUom, locationProjectedXSet[i], locationProjectedYSet[i], wellCrs);
			trajectoryStation->location.push_back(location);
			trajectorySequence->trajectoryStation.push_back(trajectoryStation);
		}
	}
	else
	{
		for (unsigned int i = 0; i < trajectoryStationCount; ++i)
		{
			if (mDSet[i] < mdMn) mdMn = mDSet[i];
			if (mDSet[i] > mdMx) mdMx = mDSet[i];

			witsml1__cs_USCOREtrajectoryStation* trajectoryStation = newTrajectoryStation(mdDatum, mDUom, mDSet[i], tvdDatum, tVDUom, tVDSet[i]);
			witsml1__cs_USCORElocation* location = constructProjectedXProjectedYLocation(locationUom, locationProjectedXSet[i], locationProjectedYSet[i], wellCrs);
			trajectoryStation->location.push_back(location);
			trajectorySequence->trajectoryStation.push_back(trajectoryStation);
		}
	}

	// assignment of trajectory mdMn
	trajectorySequence->mdMn = soap_new_witsml1__measuredDepthCoord(collection->soap, 1);
	trajectorySequence->mdMn->uom = mDUom;
	trajectorySequence->mdMn->datum = soap_new_std__string(collection->soap, 1);
	trajectorySequence->mdMn->datum->assign(mdDatum->uid);
	trajectorySequence->mdMn->__item = mdMn;

	// assignment of trajectory mdMx
	trajectorySequence->mdMx = soap_new_witsml1__measuredDepthCoord(collection->soap, 1);
	trajectorySequence->mdMx->uom = mDUom;
	trajectorySequence->mdMx->datum = soap_new_std__string(collection->soap, 1);
	trajectorySequence->mdMx->datum->assign(mdDatum->uid);
	trajectorySequence->mdMx->__item = mdMx;

	static_cast<_witsml1__trajectorys*>(collection)->trajectory[0]->__obj_USCOREtrajectory_sequence = trajectorySequence;

	// assignment of wellbore shape
	if (isVerticalLookingAtXyz(trajectoryStationCount, locationProjectedXSet, locationProjectedYSet))
		wellbore->setShape(witsml1__WellboreShape__vertical); 
	else 
		// TODO: deviated ?
		wellbore->setShape(witsml1__WellboreShape__unknown);
}

void Trajectory::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	witsml1__obj_USCOREtrajectory* traj = static_cast<_witsml1__trajectorys*>(collection)->trajectory[0];
	if (traj && traj->uidWellbore)
	{
		updateXml = false;
		setWellbore(static_cast<Wellbore*>(epcDoc->getWitsmlAbstractObjectByUuid(*traj->uidWellbore)));
		updateXml = true;
	}

	for (unsigned int i = 0; i < traj->__obj_USCOREtrajectory_sequence->trajectoryStation.size(); ++i)
	{
		for (unsigned int j = 0; j < traj->__obj_USCOREtrajectory_sequence->trajectoryStation[i]->location.size(); ++j)
		{
			if (traj->__obj_USCOREtrajectory_sequence->trajectoryStation[i]->location[j]->wellCRS)
			{
				updateXml = false;
				setCoordinateReferenceSystem(static_cast<CoordinateReferenceSystem*>(epcDoc->getWitsmlAbstractObjectByUuid(
					*traj->__obj_USCOREtrajectory_sequence->trajectoryStation[i]->location[j]->wellCRS->uidRef)));
				updateXml = true;
				return;
			}
		}
	}
}

vector<Relationship> Trajectory::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractObject::getAllEpcRelationships();

	// XML forward relationship
	Relationship relWellbore(wellbore->getPartNameInEpcDocument(), "", wellbore->getUuid());
	relWellbore.setDestinationObjectType();
	result.push_back(relWellbore);
		
	Relationship relWell(wellbore->getWell()->getPartNameInEpcDocument(), "", wellbore->getWell()->getUuid());
	relWell.setDestinationObjectType();
	result.push_back(relWell);

	// XML backward relationship
	if (resqmlWellboreTrajectoryRepresentation)
	{
		Relationship rel(resqmlWellboreTrajectoryRepresentation->getPartNameInEpcDocument(), "", resqmlWellboreTrajectoryRepresentation->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

