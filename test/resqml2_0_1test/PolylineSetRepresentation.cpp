#include "resqml2_0_1test/PolylineSetRepresentation.h"

#include "../catch.hpp"
#include "EpcDocument.h"
#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2_0_1/LocalTime3dCrs.h"
#include "resqml2_0_1/PolylineSetRepresentation.h"
#include "resqml2/HdfProxy.h"
#include "resqml2_0_1test/FaultInterpretationTest.h"
#include "resqml2_0_1test/LocalTime3dCrs.h"

#include <stdexcept>
#include "../config.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;

const char* PolylineSetRepresentation::defaultUuid = "60b04722-8608-4e92-8f1d-596372dd309e";
const char* PolylineSetRepresentation::defaultTitle = "Polyline represenation (in time)";
unsigned int PolylineSetRepresentation::numNodesPerPolylinePerPatch[] = { 3, 2 };
double PolylineSetRepresentation::polylinePoints[] = { 150, 0, 200, 300, 0, 350, 450, 0, 500, 150, 200, 200, 450, 200, 500 };

PolylineSetRepresentation::PolylineSetRepresentation(const string & epcDocPath)
	: AbstractSurfaceRepresentationTest(epcDocPath, defaultUuid, defaultTitle, 5, polylinePoints) {
}

PolylineSetRepresentation::PolylineSetRepresentation(EpcDocument* epcDoc, bool init)
	: AbstractSurfaceRepresentationTest(epcDoc, defaultUuid, defaultTitle, 5, polylinePoints) {
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void PolylineSetRepresentation::initEpcDocHandler() {
	resqml2_0_1::FaultInterpretation * interp = static_cast<resqml2_0_1::FaultInterpretation*>(this->epcDoc->getResqmlAbstractObjectByUuid(uuidFaultInterpretation));
	if (interp == nullptr) {
		FaultInterpretationTest * interpTest = new FaultInterpretationTest(this->epcDoc, true);
		interp = static_cast<resqml2_0_1::FaultInterpretation*>(this->epcDoc->getResqmlAbstractObjectByUuid(uuidFaultInterpretation));
		delete interpTest;
	}

	resqml2_0_1::LocalTime3dCrs * crs = static_cast<resqml2_0_1::LocalTime3dCrs *>(this->epcDoc->getResqmlAbstractObjectByUuid(LocalTime3dCrs::defaultUuid));
	if (crs == nullptr) {
		LocalTime3dCrs * crsTest = new LocalTime3dCrs(this->epcDoc, true);
		crs = static_cast<resqml2_0_1::LocalTime3dCrs *>(this->epcDoc->getResqmlAbstractObjectByUuid(LocalTime3dCrs::defaultUuid));
		delete crsTest;
	}

	resqml2_0_1::PolylineSetRepresentation* rep = epcDoc->createPolylineSetRepresentation(interp, crs, defaultUuid, defaultTitle);
	REQUIRE(rep != nullptr);
	rep->pushBackGeometryPatch(numNodesPerPolylinePerPatch, polylinePoints, 2, false, epcDoc->getHdfProxySet()[0]);
}

void PolylineSetRepresentation::readEpcDocHandler() {
}