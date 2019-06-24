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
#include "Trajectory.h"
#include "../catch.hpp"
#include "common/EpcDocument.h"
#include "witsml2_0/Well.h"
#include <stdexcept>

using namespace std;
using namespace witsml2_0test;
using namespace COMMON_NS;

const char* Trajectory::defaultUuid = "b4f02547-9fca-49ef-83a9-c96a802c857e";
const char* Trajectory::defaultTitle = "Witsml Trajectory Test";

Trajectory::Trajectory(const string & epcDocPath)
	: AbstractObjectTest(epcDocPath) {
}

Trajectory::Trajectory(DataObjectRepository* repo, bool init)
	: AbstractObjectTest(repo) {
	if (init)
		initRepo();
	else
		readRepo();
}

void Trajectory::initRepoHandler() {
	WITSML2_0_NS::Wellbore* wellbore = repo->createPartialWellbore("", "");
	WITSML2_0_NS::Trajectory* traj = repo->createTrajectory(wellbore, defaultUuid, defaultTitle, gsoap_eml2_1::witsml2__ChannelStatus__inactive);
	traj->pushBackTrajectoryStation(gsoap_eml2_1::witsml2__TrajStationType__unknown, 250, gsoap_eml2_1::eml21__LengthUom__m);
	traj->pushBackTrajectoryStation(gsoap_eml2_1::witsml2__TrajStationType__DLS, 500, gsoap_eml2_1::eml21__LengthUom__ft, "my Uid");
	traj->setTrajectoryStationAzi(1, 15, gsoap_eml2_1::eml21__PlaneAngleUom__dega);
}

void Trajectory::readRepoHandler() {
	WITSML2_0_NS::Trajectory* traj = repo->getDataObjectByUuid<WITSML2_0_NS::Trajectory>(defaultUuid);
	REQUIRE(traj != nullptr);
	REQUIRE(traj->getGrowingStatus() == gsoap_eml2_1::witsml2__ChannelStatus__inactive);
	REQUIRE(traj->getTrajectoryStationCount() == 2);
	REQUIRE(traj->getTrajectoryStationTypeTrajStation(0) == gsoap_eml2_1::witsml2__TrajStationType__unknown);
	REQUIRE(traj->getTrajectoryStationTypeTrajStation(1) == gsoap_eml2_1::witsml2__TrajStationType__DLS);
	REQUIRE(traj->getTrajectoryStationMdValue(0) == 250);
	REQUIRE(traj->getTrajectoryStationMdValue(1) == 500);
	REQUIRE(traj->getTrajectoryStationMdUom(0) == gsoap_eml2_1::eml21__LengthUom__m);
	REQUIRE(traj->getTrajectoryStationMdUom(1) == gsoap_eml2_1::eml21__LengthUom__ft);
	REQUIRE(traj->getTrajectoryStationuid(0) == "0");
	REQUIRE(traj->getTrajectoryStationuid(1) == "my Uid");
	REQUIRE(!traj->hasTrajectoryStationAzi(0));
	REQUIRE(traj->hasTrajectoryStationAzi(1));
	REQUIRE(traj->getTrajectoryStationAziValue(1) == 15);
	REQUIRE(traj->getTrajectoryStationAziUom(1) == gsoap_eml2_1::eml21__PlaneAngleUom__dega);
}
