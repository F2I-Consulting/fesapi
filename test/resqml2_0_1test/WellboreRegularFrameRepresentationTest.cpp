#include "resqml2_0_1test/WellboreRegularFrameRepresentationTest.h"

#include "catch.hpp"

#include "config.h"
#include "resqml2_0_1test/WellboreInterpretationTest.h"
#include "resqml2_0_1test/WellboreTrajectoryRepresentationTest.h"

#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"
#include "resqml2/AbstractHdfProxy.h"

using namespace std;
using namespace common;
using namespace resqml2_0_1;
using namespace resqml2_0_1test;

const char* WellboreRegularFrameRepresentationTest::defaultUuid = "bbcacfa6-b117-467f-8514-02660df62270";
const char* WellboreRegularFrameRepresentationTest::defaultTitle = "Wellbore Regular Frame Representation";

WellboreRegularFrameRepresentationTest::WellboreRegularFrameRepresentationTest(const string & epcDocPath)
	: AbstractRepresentationTest(epcDocPath, defaultUuid, defaultTitle) {
}

WellboreRegularFrameRepresentationTest::WellboreRegularFrameRepresentationTest(EpcDocument * epcDoc)
	: AbstractRepresentationTest(epcDoc, defaultUuid, defaultTitle) {
}

void WellboreRegularFrameRepresentationTest::initEpcDocHandler() {
	// creating dependencies
	WellboreInterpretationTest * interpTest = new WellboreInterpretationTest(this->epcDoc, true);
	WellboreTrajectoryRepresentationTest * trajTest = new WellboreTrajectoryRepresentationTest(this->epcDoc, true);

	WellboreInterpretation * interp = static_cast<WellboreInterpretation*>(this->epcDoc->getResqmlAbstractObjectByUuid(WellboreInterpretationTest::defaultUuid));
	WellboreTrajectoryRepresentation * traj = static_cast<WellboreTrajectoryRepresentation*>(this->epcDoc->getResqmlAbstractObjectByUuid(WellboreTrajectoryRepresentationTest::defaultUuid));

	// cleaning
	delete interpTest;
	delete trajTest;

	// getting the hdf proxy
	resqml2::AbstractHdfProxy* hdfProxy = this->epcDoc->getHdfProxySet()[0];
	REQUIRE(hdfProxy != nullptr);

	// WellboreFeature frame
	WellboreFrameRepresentation* w1i1FrameRep = this->epcDoc->createWellboreFrameRepresentation(interp, uuid, title, traj);
	w1i1FrameRep->setMdValues(0, 200, 6);
}

void WellboreRegularFrameRepresentationTest::readEpcDocHandler() {
	WellboreFrameRepresentation* w1i1FrameRep = this->epcDoc->getResqmlAbstractObjectByUuid<WellboreFrameRepresentation>(defaultUuid);
	REQUIRE(w1i1FrameRep != nullptr);

	REQUIRE(w1i1FrameRep->areMdValuesRegularlySpaced());
	REQUIRE(w1i1FrameRep->getMdValuesCount() == 6);

	REQUIRE(w1i1FrameRep->getMdFirstValue() == .0);
	REQUIRE(w1i1FrameRep->getMdConstantIncrementValue() == 200);
}
