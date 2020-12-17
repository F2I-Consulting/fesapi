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
#include "resqml2_test/WellboreTrajectoryRepresentationTest.h"

#include <stdexcept>

#include "catch.hpp"
#include "resqml2/LocalDepth3dCrs.h"
#include "resqml2/LocalTime3dCrs.h"
#include "resqml2/MdDatum.h"
#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2/WellboreTrajectoryRepresentation.h"
using namespace std;
using namespace resqml2_test;
using namespace COMMON_NS;
using namespace RESQML2_NS;

const char* WellboreTrajectoryRepresentationTest::defaultUuid = "35e83350-5b68-4c1d-bfd8-21791a9c4c41";
const char* WellboreTrajectoryRepresentationTest::defaultTitle = "m m depth";
#define TRAJ_MMELEV_UUID "f91f3a50-aa7d-49de-9c63-d9c4f2344a4a"
#define CRS_MMELEV_UUID "3a096aa1-ce77-4720-a7f7-c45dbdc47459"
#define TRAJ_MMTIME_UUID "2438c6b3-aa46-43f4-b9b3-99ef0412ff81"
#define CRS_MMTIME_UUID "f610c128-a175-4bd1-834b-0d44559ee73b"
#define TRAJ_MFT_INCL_AZI_UUID "c8061fe6-f5b1-4e72-8629-473ae93e552a"
#define TRAJ_MMELEV_INCL_AZI_UUID "4acc783a-3b06-4d1e-9c8f-97d9b1af7742"

WellboreTrajectoryRepresentationTest::WellboreTrajectoryRepresentationTest(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void WellboreTrajectoryRepresentationTest::initRepo() {
	WellboreInterpretation* interp = repo->createPartial<RESQML2_0_1_NS::WellboreInterpretation>("", "");
	MdDatum* mdDatum = repo->createMdDatum("", "", nullptr, gsoap_eml2_3::eml23__WellboreDatumReference__mean_x0020sea_x0020level, 275, 75, 0);

	// creating the WellboreTrajectoryRepresentation in m and ft and depth
	WellboreTrajectoryRepresentation* rep = repo->createWellboreTrajectoryRepresentation(interp, defaultUuid, defaultTitle, mdDatum);
	double controlPoints[12] = { 275, 75, 0, 275, 75, 325, 275, 75, 500, 275, 75, 1000 };
	double trajectoryTangentVectors[12] = { 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 3.2808 };
	double trajectoryMds[4] = { 0, 325, 500, 1000 };
	rep->setGeometry(controlPoints, trajectoryTangentVectors, trajectoryMds, 4, 0, repo->getHdfProxySet()[0]);

	// creating the WellboreTrajectoryRepresentation in m and m and Time
	auto* timeCrs = repo->createLocalTime3dCrs(CRS_MMTIME_UUID, "", .0, .0, .0, .0, gsoap_resqml2_0_1::eml20__LengthUom__m, 23031, gsoap_resqml2_0_1::eml20__TimeUom__ms, gsoap_resqml2_0_1::eml20__LengthUom__m, "Unknown", true);
	WellboreTrajectoryRepresentation* timeRep = repo->createWellboreTrajectoryRepresentation(interp, TRAJ_MMTIME_UUID, "m m time", mdDatum);
	timeRep->setGeometry(controlPoints, trajectoryMds, 4, 0, repo->getHdfProxySet()[0], timeCrs);

	// creating the WellboreTrajectoryRepresentation in m and m and elevation
	auto* crs = repo->createLocalDepth3dCrs(CRS_MMELEV_UUID, "", .0, .0, .0, .0, gsoap_resqml2_0_1::eml20__LengthUom__m, 23031, gsoap_resqml2_0_1::eml20__LengthUom__m, "Unknown", true);
	WellboreTrajectoryRepresentation* rep2 = repo->createWellboreTrajectoryRepresentation(interp, TRAJ_MMELEV_UUID, "m m elevation", mdDatum);
	double controlPoints2[12] = { 275, 75, 0, 275, 75, -325, 275, 75, -500, 275, 75, -1000 };
	double trajectoryTangentVectors2[12] = { 0, 0, -1, -1, 0, 0, 0, 1, 0, 1, 0, 1 };
	rep2->setGeometry(controlPoints2, trajectoryTangentVectors2, trajectoryMds, 4, 0, repo->getHdfProxySet()[0], crs);

	const auto pi = 3.14159265358979323846;
	// creating the WellboreTrajectoryRepresentation in m and ft and depth
	WellboreTrajectoryRepresentation* rep3 = repo->createWellboreTrajectoryRepresentation(interp, TRAJ_MFT_INCL_AZI_UUID, "m ft depth incl azi", mdDatum);
	double inclinations[4] = { 0, pi / 2, pi / 2, pi / 4 };
	double azimuths[4] = { 0, pi / 2, 0, pi / 2 };
	rep3->setGeometry(controlPoints, inclinations, azimuths, trajectoryMds, 4, 0, repo->getHdfProxySet()[0]);

	// creating the WellboreTrajectoryRepresentation in m and m and elevation
	WellboreTrajectoryRepresentation* rep4 = repo->createWellboreTrajectoryRepresentation(interp, TRAJ_MMELEV_INCL_AZI_UUID, "m m elevation incl azi", mdDatum);
	double inclinations2[4] = { 0, pi / 2, pi / 2, 3 * pi / 4 };
	double azimuths2[4] = { 0, -pi / 2, 0, pi / 2 };
	rep4->setGeometry(controlPoints, inclinations2, azimuths2, trajectoryMds, 4, 0, repo->getHdfProxySet()[0]);

}

void WellboreTrajectoryRepresentationTest::readRepo() {
	// getting the WellboreTrajectoryRepresentation
	WellboreTrajectoryRepresentation* traj = repo->getDataObjectByUuid<WellboreTrajectoryRepresentation>(defaultUuid);

	REQUIRE(traj->getXyzPointCountOfAllPatches() == 4);
	REQUIRE(traj->getGeometryKind() == 0);
	double trajectoryMds[4];
	traj->getMdValues(trajectoryMds);
	REQUIRE(trajectoryMds[0] == 0);
	REQUIRE(trajectoryMds[1] == 325);
	REQUIRE(trajectoryMds[2] == 500);
	REQUIRE(trajectoryMds[3] == 1000);
	double controlPoints[12];
	traj->getXyzPointsOfAllPatches(controlPoints);
	REQUIRE(controlPoints[0] == 275);
	REQUIRE(controlPoints[1] == 75);
	REQUIRE(controlPoints[2] == 0);
	REQUIRE(controlPoints[3] == 275);

	constexpr auto pi = 3.14159265358979323846;
	constexpr auto epsilon = 0.0001;
	double inclinations[4];
	double azimuths[4];
	traj->getInclinationsAndAzimuths(inclinations, azimuths);
	REQUIRE(inclinations[0] > -epsilon);
	REQUIRE(inclinations[0] < epsilon);
	REQUIRE(inclinations[1] > pi / 2 - epsilon);
	REQUIRE(inclinations[1] < pi / 2 + epsilon);
	REQUIRE(inclinations[2] > pi / 2 - epsilon);
	REQUIRE(inclinations[2] < pi / 2 + epsilon);
	REQUIRE(inclinations[3] > pi / 4 - epsilon);
	REQUIRE(inclinations[3] < pi / 4 + epsilon);
	REQUIRE(azimuths[0] > -epsilon);
	REQUIRE(azimuths[0] < epsilon);
	REQUIRE(azimuths[1] > pi / 2 - epsilon);
	REQUIRE(azimuths[1] < pi / 2 + epsilon);
	REQUIRE(azimuths[2] > -epsilon);
	REQUIRE(azimuths[2] < epsilon);
	REQUIRE(azimuths[3] > pi / 2 - epsilon);
	REQUIRE(azimuths[3] < pi / 2 + epsilon);

	traj = repo->getDataObjectByUuid<WellboreTrajectoryRepresentation>(TRAJ_MMTIME_UUID);
	REQUIRE(dynamic_cast<RESQML2_NS::LocalTime3dCrs*>(traj->getLocalCrs(0)) != nullptr);

	traj = repo->getDataObjectByUuid<WellboreTrajectoryRepresentation>(TRAJ_MMELEV_UUID);
	traj->getInclinationsAndAzimuths(inclinations, azimuths);
	REQUIRE(inclinations[0] > -epsilon);
	REQUIRE(inclinations[0] < epsilon);
	REQUIRE(inclinations[1] > pi / 2 - epsilon);
	REQUIRE(inclinations[1] < pi / 2 + epsilon);
	REQUIRE(inclinations[2] > pi / 2 - epsilon);
	REQUIRE(inclinations[2] < pi / 2 + epsilon);
	REQUIRE(inclinations[3] > 3*pi / 4 - epsilon);
	REQUIRE(inclinations[3] < 3*pi / 4 + epsilon);
	REQUIRE(azimuths[0] > -epsilon);
	REQUIRE(azimuths[0] < epsilon);
	REQUIRE(azimuths[1] > -pi / 2 - epsilon);
	REQUIRE(azimuths[1] < -pi / 2 + epsilon);
	REQUIRE(azimuths[2] > -epsilon);
	REQUIRE(azimuths[2] < epsilon);
	REQUIRE(azimuths[3] > pi / 2 - epsilon);
	REQUIRE(azimuths[3] < pi / 2 + epsilon);

	traj = repo->getDataObjectByUuid<WellboreTrajectoryRepresentation>(TRAJ_MFT_INCL_AZI_UUID);
	traj->getInclinationsAndAzimuths(inclinations, azimuths);
	REQUIRE(inclinations[0] > -epsilon);
	REQUIRE(inclinations[0] < epsilon);
	REQUIRE(inclinations[1] > pi / 2 - epsilon);
	REQUIRE(inclinations[1] < pi / 2 + epsilon);
	REQUIRE(inclinations[2] > pi / 2 - epsilon);
	REQUIRE(inclinations[2] < pi / 2 + epsilon);
	REQUIRE(inclinations[3] > pi / 4 - epsilon);
	REQUIRE(inclinations[3] < pi / 4 + epsilon);
	REQUIRE(azimuths[0] > -epsilon);
	REQUIRE(azimuths[0] < epsilon);
	REQUIRE(azimuths[1] > pi / 2 - epsilon);
	REQUIRE(azimuths[1] < pi / 2 + epsilon);
	REQUIRE(azimuths[2] > -epsilon);
	REQUIRE(azimuths[2] < epsilon);
	REQUIRE(azimuths[3] > pi / 2 - epsilon);
	REQUIRE(azimuths[3] < pi / 2 + epsilon);

	traj = repo->getDataObjectByUuid<WellboreTrajectoryRepresentation>(TRAJ_MMELEV_INCL_AZI_UUID);
	traj->getInclinationsAndAzimuths(inclinations, azimuths);
	REQUIRE(inclinations[0] > -epsilon);
	REQUIRE(inclinations[0] < epsilon);
	REQUIRE(inclinations[1] > pi / 2 - epsilon);
	REQUIRE(inclinations[1] < pi / 2 + epsilon);
	REQUIRE(inclinations[2] > pi / 2 - epsilon);
	REQUIRE(inclinations[2] < pi / 2 + epsilon);
	REQUIRE(inclinations[3] > 3 * pi / 4 - epsilon);
	REQUIRE(inclinations[3] < 3 * pi / 4 + epsilon);
	REQUIRE(azimuths[0] > -epsilon);
	REQUIRE(azimuths[0] < epsilon);
	REQUIRE(azimuths[1] > -pi / 2 - epsilon);
	REQUIRE(azimuths[1] < -pi / 2 + epsilon);
	REQUIRE(azimuths[2] > -epsilon);
	REQUIRE(azimuths[2] < epsilon);
	REQUIRE(azimuths[3] > pi / 2 - epsilon);
	REQUIRE(azimuths[3] < pi / 2 + epsilon);
}
