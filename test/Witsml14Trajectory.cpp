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
#include "Witsml14Trajectory.h"

#include <numeric>

#include "common/DataObjectRepository.h"
#include "witsml1_4/Trajectory.h"

#include "catch.hpp"

using namespace std;

// From http://w3.energistics.org/schema/witsml_v1.4.1_data/XML_Examples/trajectory_no_xsl.xml
constexpr char const* MY_WITSML_FILE="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
"<!--Example of Trajectory data-->\n"
"<trajectorys\n"
	"xmlns=\"http://www.witsml.org/schemas/1series\"\n"
	"xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
	"xsi:schemaLocation=\"http://www.witsml.org/schemas/1series  ../xsd_schemas/obj_trajectory.xsd\"\n"
	"version=\"1.4.1.0\">\n"
"<!--\n"
"These examples are only intended to demonstrate the type of data that can be exchanged.\n"
"They totally artificial and are not intended to demonstrate best practices.\n"
"-->\n"
	"<documentInfo>\n"
		"<documentName>trajectory</documentName>\n"
		"<fileCreationInformation>\n"
		"<fileCreationDate>2001-10-31T08:15:00.000Z</fileCreationDate>\n"
		"<fileCreator>John Smith</fileCreator>\n"
		"</fileCreationInformation>\n"
	"</documentInfo>\n"
	"<trajectory uidWell=\"W-12\" uidWellbore=\"B-01\" uid=\"pe84e\">\n"
		"<nameWell>6507/7-A-42</nameWell>\n"
		"<nameWellbore>A-42</nameWellbore>\n"
		"<name>Plan #2</name>\n"
		"<dTimTrajStart>2001-10-31T08:15:00.000Z</dTimTrajStart>\n"
		"<dTimTrajEnd>2001-11-03T16:30:00.000Z</dTimTrajEnd>\n"
		"<mdMn uom=\"ft\">0</mdMn>\n"
		"<mdMx uom=\"ft\">14089.3</mdMx>\n"
		"<serviceCompany>Anadrill</serviceCompany>\n"
		"<magDeclUsed uom=\"dega\">-4.038</magDeclUsed>\n"
		"<gridCorUsed uom=\"dega\">0.99961</gridCorUsed>\n"
		"<aziVertSect uom=\"dega\">82.700</aziVertSect>\n"
		"<dispNsVertSectOrig uom=\"ft\">0</dispNsVertSectOrig>\n"
		"<dispEwVertSectOrig uom=\"ft\">0</dispEwVertSectOrig>\n"
		"<definitive>true</definitive>\n"
		"<memory>true</memory>\n"
		"<finalTraj>true</finalTraj>\n"
		"<aziRef>grid north</aziRef>\n"
		"<trajectoryStation uid=\"34ht5\">\n"
			"<dTimStn>2001-10-21T08:15:00.000Z</dTimStn>\n"
			"<typeTrajStation>tie in point</typeTrajStation>\n"
			"<md uom=\"ft\">0</md>\n"
			"<tvd uom=\"ft\">0</tvd>\n"
			"<incl uom=\"dega\">0</incl>\n"
			"<azi uom=\"dega\">47.3</azi>\n"
			"<mtf uom=\"dega\">47.3</mtf>\n"
			"<gtf uom=\"dega\">0</gtf>\n"
			"<dispNs uom=\"ft\">0</dispNs>\n"
			"<dispEw uom=\"ft\">0</dispEw>\n"
			"<vertSect uom=\"ft\">0</vertSect>\n"
			"<dls uom=\"dega/ft\">0</dls>\n"
			"<rateTurn uom=\"dega/ft\">0</rateTurn>\n"
			"<rateBuild uom=\"dega/ft\">0</rateBuild>\n"
			"<mdDelta uom=\"ft\">0</mdDelta>\n"
			"<tvdDelta uom=\"ft\">0</tvdDelta>\n"
			"<modelToolError>good gyro</modelToolError>\n"
			"<gravTotalUncert uom=\"m/s2\">0</gravTotalUncert>\n"
			"<dipAngleUncert uom=\"dega\">0</dipAngleUncert>\n"
			"<magTotalUncert uom=\"nT\">0</magTotalUncert>\n"
			"<gravAccelCorUsed>false</gravAccelCorUsed>\n"
			"<magXAxialCorUsed>false</magXAxialCorUsed>\n"
			"<sagCorUsed>false</sagCorUsed>\n"
			"<magDrlstrCorUsed>false</magDrlstrCorUsed>\n"
			"<statusTrajStation>position</statusTrajStation>\n"
			"<rawData>\n"
				"<gravAxialRaw uom=\"ft/s2\">0.116</gravAxialRaw>\n"
				"<gravTran1Raw uom=\"ft/s2\">-0.168</gravTran1Raw>\n"
				"<gravTran2Raw uom=\"ft/s2\">-1654</gravTran2Raw>\n"
				"<magAxialRaw uom=\"nT\">22.77</magAxialRaw>\n"
				"<magTran1Raw uom=\"nT\">22.5</magTran1Raw>\n"
				"<magTran2Raw uom=\"nT\">27.05</magTran2Raw>\n"
			"</rawData>\n"
			"<corUsed>\n"
				"<gravAxialAccelCor uom=\"ft/s2\">0.11</gravAxialAccelCor>\n"
				"<gravTran1AccelCor uom=\"ft/s2\">0.14</gravTran1AccelCor>\n"
				"<gravTran2AccelCor uom=\"ft/s2\">0.13</gravTran2AccelCor>\n"
				"<magAxialDrlstrCor uom=\"nT\">0.17</magAxialDrlstrCor>\n"
				"<magTran1DrlstrCor uom=\"nT\">0.16</magTran1DrlstrCor>\n"
				"<magTran2DrlstrCor uom=\"nT\">0.24</magTran2DrlstrCor>\n"
				"<sagIncCor uom=\"dega\">0</sagIncCor>\n"
				"<sagAziCor uom=\"dega\">0</sagAziCor>\n"
				"<stnMagDeclUsed uom=\"dega\">-4.038</stnMagDeclUsed>\n"
				"<stnGridCorUsed uom=\"dega\">-0.4917</stnGridCorUsed>\n"
				"<dirSensorOffset uom=\"ft\">48.3</dirSensorOffset>\n"
			"</corUsed>\n"
			"<valid>\n"
				"<magTotalFieldCalc uom=\"nT\">51.19</magTotalFieldCalc>\n"
				"<magDipAngleCalc uom=\"dega\">41.5</magDipAngleCalc>\n"
				"<gravTotalFieldCalc uom=\"ft/s2\">0.999</gravTotalFieldCalc>\n"
			"</valid>\n"
			"<matrixCov>\n"
				"<varianceNN uom=\"ft2\">0.005236</varianceNN>\n"
				"<varianceNE uom=\"ft2\">0.005236</varianceNE>\n"
				"<varianceNVert uom=\"ft2\">2.356194</varianceNVert>\n"
				"<varianceEE uom=\"ft2\">0.005236</varianceEE>\n"
				"<varianceEVert uom=\"ft2\">0.005236</varianceEVert>\n"
				"<varianceVertVert uom=\"ft2\">0.785398</varianceVertVert>\n"
				"<biasN uom=\"ft\">0</biasN>\n"
				"<biasE uom=\"ft\">0</biasE>\n"
				"<biasVert uom=\"ft\">0</biasVert>\n"
			"</matrixCov>\n"
			"<location uid=\"loc-1\">\n"
				"<wellCRS uidRef=\"geog1\">ED50</wellCRS>\n"
				"<latitude uom=\"dega\">59.755300</latitude>\n"
				"<longitude uom=\"dega\">1.71347417</longitude>\n"
			"</location>\n"
			"<location uid=\"loc-2\">\n"
				"<wellCRS uidRef=\"proj1\">ED50/UTM Zone 31N</wellCRS>\n"
				"<easting uom=\"m\">427710.69</easting>\n"
				"<northing uom=\"m\">6625015.54</northing>\n"
			"</location>\n"
		"</trajectoryStation>\n"
		"<commonData>\n"
			"<itemState>plan</itemState>\n"
			"<comments>These are the comments associated with the trajectory data object.</comments>\n"
		"</commonData>\n"
	"</trajectory>\n"
"</trajectorys>\n";

void Witsml14Trajectory::test()
{
	COMMON_NS::DataObjectRepository repo;

	auto addedWrapper = repo.addOrReplaceGsoapProxy(MY_WITSML_FILE, "witsml14.obj_trajectorys");
	if (addedWrapper == nullptr) {
		vector<string> warningSet = repo.getWarnings();
		if (!warningSet.empty()) {
			for (size_t i = 0; i < warningSet.size(); ++i) {
				cout << "Warning " << i + 1 << ": " << warningSet[i] << endl;
			}
			cout << endl;
		}
	}

	auto traj = static_cast<WITSML1_4_NS::Trajectory*>(addedWrapper);
	REQUIRE(traj->getUuid() == "pe84e");
	REQUIRE(traj->getTitle() == "Plan #2");
	REQUIRE(traj->getMdMxUom() == gsoap_eml2_1::eml21__LengthUom::ft);
	REQUIRE(traj->getMdMxValue() == 14089.3);

	REQUIRE(traj->getTrajectoryStationCount() == 1);
	REQUIRE(traj->getTrajectoryStationMdUom(0) == gsoap_eml2_1::eml21__LengthUom::ft);
	REQUIRE(traj->getTrajectoryStationMdValue(0) == .0);
	REQUIRE(traj->getTrajectoryStationDispEwUom(0) == gsoap_eml2_1::eml21__LengthUom::ft);
	REQUIRE(traj->getTrajectoryStationDispEwValue(0) == .0);
	REQUIRE(traj->getTrajectoryStationDispNsUom(0) == gsoap_eml2_1::eml21__LengthUom::ft);
	REQUIRE(traj->getTrajectoryStationDispNsValue(0) == .0);
	REQUIRE(traj->getTrajectoryStationAziUom(0) == gsoap_eml2_1::eml21__PlaneAngleUom::dega);
	REQUIRE(traj->getTrajectoryStationAziValue(0) == 47.3);
}
