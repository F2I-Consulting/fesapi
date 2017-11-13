#include "resqml2_0_1test/WellboreFrameRepresentationTest.h"

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

const char* WellboreFrameRepresentationTest::defaultUuid = "0047500b-cf08-47c0-89e0-84f330c7e132";
const char* WellboreFrameRepresentationTest::defaultTitle = "Wellbore Frame Representation";

WellboreFrameRepresentationTest::WellboreFrameRepresentationTest(const string & epcDocPath)
	: AbstractRepresentationTest(epcDocPath, defaultUuid, defaultTitle) {
}

WellboreFrameRepresentationTest::WellboreFrameRepresentationTest(EpcDocument * epcDoc, bool init)
	: AbstractRepresentationTest(epcDoc, defaultUuid, defaultTitle) {
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void WellboreFrameRepresentationTest::initEpcDocHandler() {
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
	double logMds[5] = { 0, 250, 500, 750, 1200 };
	w1i1FrameRep->setMdValues(logMds, 5, hdfProxy);
}

void WellboreFrameRepresentationTest::readEpcDocHandler() {
	WellboreFrameRepresentation* w1i1FrameRep = this->epcDoc->getResqmlAbstractObjectByUuid<WellboreFrameRepresentation>(defaultUuid);
	REQUIRE(w1i1FrameRep != nullptr);

	REQUIRE(w1i1FrameRep->areMdValuesRegularlySpaced() == false);
	REQUIRE(w1i1FrameRep->getMdValuesCount() == 5);

	double* logMds = new double[w1i1FrameRep->getMdValuesCount()];

	w1i1FrameRep->getMdAsDoubleValues(logMds);
	REQUIRE(logMds[0] == .0);
	REQUIRE(logMds[1] == 250);
	REQUIRE(logMds[2] == 500);
	REQUIRE(logMds[3] == 750);
	REQUIRE(logMds[4] == 1200);

	delete[] logMds;
}
