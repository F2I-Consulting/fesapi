#include "resqml2_0_1test/WellboreTrajectoryRepresentationTest.h"

#include <stdexcept>

#include "resqml2_0_1test/WellboreInterpretationTest.h"
#include "resqml2_0_1test/MdDatumTest.h"

#include "catch.hpp"
#include "EpcDocument.h"
#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2/MdDatum.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2;

const char* WellboreTrajectoryRepresentationTest::defaultUuid = "35e83350-5b68-4c1d-bfd8-21791a9c4c41";
const char* WellboreTrajectoryRepresentationTest::defaultTitle = "Wellbore Representation Test";

WellboreTrajectoryRepresentationTest::WellboreTrajectoryRepresentationTest(const string & epcDocPath)
	: AbstractRepresentationTest(epcDocPath, defaultUuid, defaultTitle) {
}

WellboreTrajectoryRepresentationTest::WellboreTrajectoryRepresentationTest(EpcDocument* epcDoc, bool init)
	: AbstractRepresentationTest(epcDoc, defaultUuid, defaultTitle) {
	if (init)
			this->initEpcDoc();
		else
			this->readEpcDoc();
}

void WellboreTrajectoryRepresentationTest::initEpcDocHandler() {
	// getting the local depth 3d crs
	WellboreInterpretationTest* interpTest = new WellboreInterpretationTest(this->epcDoc, true);
	MdDatumTest* mdDatumTest = new MdDatumTest(this->epcDoc, true);

	resqml2_0_1::WellboreInterpretation* interp = static_cast<resqml2_0_1::WellboreInterpretation*>(this->epcDoc->getResqmlAbstractObjectByUuid(WellboreInterpretationTest::defaultUuid));
	MdDatum* mdDatum = static_cast<MdDatum*>(this->epcDoc->getResqmlAbstractObjectByUuid(MdDatumTest::defaultUuid));

	// cleaning
	delete interpTest;
	delete mdDatumTest;

	// getting the hdf proxy
	AbstractHdfProxy* hdfProxy = this->epcDoc->getHdfProxySet()[0];

	// creating the representation
	resqml2_0_1::WellboreTrajectoryRepresentation* rep = epcDoc->createWellboreTrajectoryRepresentation(interp, this->uuid, this->title, mdDatum);
	double controlPoints[12] = { 275, 75, 0, 275, 75, 325, 275, 75, 500, 275, 75, 1000 };
	double trajectoryTangentVectors[12] = { 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 };
	double trajectoryMds[4] = { 0, 325, 500, 1000 };
	rep->setGeometry(controlPoints, trajectoryTangentVectors, trajectoryMds, 4, epcDoc->getHdfProxySet()[0]);

}

void WellboreTrajectoryRepresentationTest::readEpcDocHandler() {
	// getting the TimeSeries
	resqml2_0_1::WellboreTrajectoryRepresentation* traj = static_cast<resqml2_0_1::WellboreTrajectoryRepresentation*>(this->epcDoc->getResqmlAbstractObjectByUuid(this->uuid));

	REQUIRE(traj->getMdDatumUuid() == MdDatumTest::defaultUuid);
	REQUIRE(traj->getXyzPointCountOfAllPatches() == 4);
	double trajectoryMds[4];
	traj->getMdValues(trajectoryMds);
	REQUIRE(trajectoryMds[0] == 0);
	REQUIRE(trajectoryMds[1] == 325);
	REQUIRE(trajectoryMds[2] == 500);
	REQUIRE(trajectoryMds[3] == 1000);
	double controlPoints[12];
	traj->getXyzPointsOfAllPatchesInGlobalCrs(controlPoints);
	REQUIRE(controlPoints[0] == 275);
	REQUIRE(controlPoints[1] == 75);
	REQUIRE(controlPoints[2] == 0);
	REQUIRE(controlPoints[3] == 275);
}