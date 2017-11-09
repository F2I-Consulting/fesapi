#include "resqml2_0_1test/HorizonOnSeismicLine.h"
#include "../catch.hpp"
#include "../config.h"  

#include "resqml2/AbstractLocal3dCrs.h"
#include "resqml2_0_1/PolylineRepresentation.h"
#include "resqml2_0_1/HorizonInterpretation.h"
#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "resqml2/HdfProxy.h"
#include "resqml2_0_1test/HorizonInterpretationTest.h"
#include "resqml2_0_1test/SeismicLineRepresentationTest.h"
#include "LocalDepth3dCrsTest.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

const char* HorizonOnSeismicLine::defaultUuid = "c9bea300-6231-4acb-8b7c-77e4099224d4";
const char* HorizonOnSeismicLine::defaultTitle = "Horizon on seismic line";
double HorizonOnSeismicLine::defaultXyzPoints[12] = { 0, 100, 300, 150, 110, 300, 450, 130, 350, 600, 140, 350 };

HorizonOnSeismicLine::HorizonOnSeismicLine(const string & epcDocPath)
	: AbstractRepresentationTest(epcDocPath, defaultUuid, defaultTitle, 4, defaultXyzPoints)
{
}

HorizonOnSeismicLine::HorizonOnSeismicLine(EpcDocument * epcDocument, bool init)
	: AbstractRepresentationTest(epcDocument, defaultUuid, defaultTitle, 4, defaultXyzPoints)
{
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void HorizonOnSeismicLine::initEpcDocHandler()
{
	resqml2::AbstractHdfProxy * hdfProxy = epcDoc->getHdfProxy(0);

	HorizonInterpretation* horizonInterp = epcDoc->getResqmlAbstractObjectByUuid<HorizonInterpretation>(uuidHorizon0Interp);
	if (horizonInterp == nullptr) {
		HorizonInterpretationTest* horizonInterpTest = new HorizonInterpretationTest(epcDoc, true, uuidHorizon0Interp, titleHorizon0Interp, uuidHorizon0, titleHorizon0);
		horizonInterp = epcDoc->getResqmlAbstractObjectByUuid<HorizonInterpretation>(uuidHorizon0Interp);
		delete horizonInterpTest;
	}
	
	PolylineRepresentation* seismicLineRep = epcDoc->getResqmlAbstractObjectByUuid<PolylineRepresentation>(SeismicLineRepresentationTest::defaultUuid);
	if (seismicLineRep == nullptr) {
		SeismicLineRepresentationTest* seismicLineRepresentationTest = new SeismicLineRepresentationTest(epcDoc, true);
		seismicLineRep = epcDoc->getResqmlAbstractObjectByUuid<PolylineRepresentation>(SeismicLineRepresentationTest::defaultUuid);
		delete seismicLineRepresentationTest;
	}

	resqml2::AbstractLocal3dCrs * crs = seismicLineRep->getLocalCrs();;

	PolylineRepresentation* h1i1SinglePolylineRep = epcDoc->createPolylineRepresentation(horizonInterp, crs, uuid, title);
	h1i1SinglePolylineRep->setGeometry(defaultXyzPoints, 4, hdfProxy);
	double seismicLineAbscissa[4] = { 0.0, 1.0, 3.0, 4.0 };
	h1i1SinglePolylineRep->addSeismic2dCoordinatesToPatch(0, seismicLineAbscissa, 4, seismicLineRep, hdfProxy);
}

void HorizonOnSeismicLine::readEpcDocHandler()
{
	// reading dependencies
	HorizonInterpretationTest* horizonInterpTest = new HorizonInterpretationTest(this->epcDoc, false, uuidHorizon0Interp, titleHorizon0Interp, uuidHorizon0, titleHorizon0);
	SeismicLineRepresentationTest * seismicLineRepTest = new SeismicLineRepresentationTest(this->epcDoc, false);

	PolylineRepresentation* h1i1SinglePolylineRep = epcDoc->getResqmlAbstractObjectByUuid<PolylineRepresentation>(uuid);
	REQUIRE(h1i1SinglePolylineRep->getSeismicSupportOfPatch(0) != nullptr);

	double seismicLineAbscissa[4] = { -1.0, -1.0, -1.0, -1.0 };
	h1i1SinglePolylineRep->getSeismicLineAbscissaOfPointsOfPatch(0, seismicLineAbscissa);
	REQUIRE(seismicLineAbscissa[0] == 0.0);
	REQUIRE(seismicLineAbscissa[1] == 1.0);
	REQUIRE(seismicLineAbscissa[2] == 3.0);
	REQUIRE(seismicLineAbscissa[3] == 4.0);

	// cleaning
	delete horizonInterpTest;
	delete seismicLineRepTest;
}
