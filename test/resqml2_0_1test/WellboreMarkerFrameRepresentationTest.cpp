#include "resqml2_0_1test/WellboreMarkerFrameRepresentationTest.h"

#include "catch.hpp"

#include "config.h"
#include "resqml2_0_1test/WellboreInterpretationTest.h"
#include "resqml2_0_1test/WellboreTrajectoryRepresentationTest.h"

#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"
#include "resqml2_0_1/WellboreMarker.h"

using namespace std;
using namespace common;
using namespace resqml2_0_1;
using namespace resqml2_0_1test;

const char* WellboreMarkerFrameRepresentationTest::defaultUuid = "8f1c7e38-afc7-4cb8-86bb-a116e9135de4";
const char* WellboreMarkerFrameRepresentationTest::defaultTitle = "Wellbore Marker Frame Representation";

WellboreMarkerFrameRepresentationTest::WellboreMarkerFrameRepresentationTest(const string & epcDocPath)
	: AbstractRepresentationTest(epcDocPath, defaultUuid, defaultTitle) {
}

WellboreMarkerFrameRepresentationTest::WellboreMarkerFrameRepresentationTest(EpcDocument * epcDoc)
	: AbstractRepresentationTest(epcDoc, defaultUuid, defaultTitle) {
}

void WellboreMarkerFrameRepresentationTest::initEpcDocHandler() {
	// creating dependencies
	WellboreInterpretationTest * interpTest = new WellboreInterpretationTest(this->epcDoc, true);
	WellboreTrajectoryRepresentationTest * trajTest = new WellboreTrajectoryRepresentationTest(this->epcDoc, true);

	WellboreInterpretation * interp = epcDoc->getResqmlAbstractObjectByUuid<WellboreInterpretation>(WellboreInterpretationTest::defaultUuid);
	WellboreTrajectoryRepresentation * traj = epcDoc->getResqmlAbstractObjectByUuid<WellboreTrajectoryRepresentation>(WellboreTrajectoryRepresentationTest::defaultUuid);

	// cleaning
	delete interpTest;
	delete trajTest;

	// WellboreFeature marker frame
	WellboreMarkerFrameRepresentation* wmf = epcDoc->createWellboreMarkerFrameRepresentation(interp, uuid, title, traj);
	double markerMdValues[2] = { 350, 550 };
	wmf->setMdValues(markerMdValues, 2, epcDoc->getHdfProxySet()[0]);
	wmf->pushBackNewWellboreMarker("", "", gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind__horizon);
	wmf->pushBackNewWellboreMarker("", "testing Fault", gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind__fault);
}

void WellboreMarkerFrameRepresentationTest::readEpcDocHandler() {
	WellboreMarkerFrameRepresentation* wmf = epcDoc->getResqmlAbstractObjectByUuid<WellboreMarkerFrameRepresentation>(uuid);
	REQUIRE(wmf != nullptr);
	REQUIRE(wmf->getWellboreMarkerCount() == 2);
	REQUIRE((wmf->getWellboreMarkerSet()[0])->getGeologicBoundaryKind() == gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind__horizon);
	REQUIRE((wmf->getWellboreMarkerSet()[1])->getGeologicBoundaryKind() == gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind__fault);
}
