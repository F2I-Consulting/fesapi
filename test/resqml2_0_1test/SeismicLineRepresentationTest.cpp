#include "resqml2_0_1test/SeismicLineRepresentationTest.h"
#include "../catch.hpp"
#include "../config.h" 
#include "resqml2_0_1/SeismicLineFeature.h"
#include "resqml2_0_1/GenericFeatureInterpretation.h"
#include "resqml2_0_1/PolylineRepresentation.h"
#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "resqml2/AbstractHdfProxy.h"
#include "resqml2_0_1test/AbstractFeatureTest.h"
#include "resqml2_0_1test/LocalDepth3dCrsTest.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

const char* SeismicLineRepresentationTest::defaultUuidFeatureSet = "4b463e9b-0369-40e7-a3c0-0f0d4b228a21";
const char* SeismicLineRepresentationTest::defaultTitleFeatureSet = "Seismic Line Set Feature";
const char* SeismicLineRepresentationTest::defaultUuidFeature = "88cbfbc8-d20f-4342-b6a3-e0fdc655fb38";
const char* SeismicLineRepresentationTest::defaultTitleFeature = "Seismic Line Feature";
const char* SeismicLineRepresentationTest::defaultUuidInterp = "195e8333-a2bd-4948-8940-6da8c5773eff";
const char* SeismicLineRepresentationTest::defaultTitleInterp = "Seismic Line Interp";
const char* SeismicLineRepresentationTest::defaultUuid = "99bd4f3e-8f52-43ae-98fb-ab60371e838e";
const char* SeismicLineRepresentationTest::defaultTitle = "Seismic Line Representation";

SeismicLineRepresentationTest::SeismicLineRepresentationTest(const string & epcDocPath)
	: AbstractSurfaceRepresentationTest(epcDocPath, defaultUuid, defaultTitle, 5, nullptr)
{
}

SeismicLineRepresentationTest::SeismicLineRepresentationTest(EpcDocument * epcDocument, bool init)
	: AbstractSurfaceRepresentationTest(epcDocument, defaultUuid, defaultTitle, 5, nullptr)
{
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void SeismicLineRepresentationTest::initEpcDocHandler()
{
	LocalDepth3dCrs * crs = epcDoc->getResqmlAbstractObjectByUuid<LocalDepth3dCrs>(LocalDepth3dCrsTest::defaultUuid);
	if (crs == nullptr) {
		LocalDepth3dCrsTest* crsTest = new LocalDepth3dCrsTest(this->epcDoc, true);
		crs = epcDoc->getResqmlAbstractObjectByUuid<LocalDepth3dCrs>(LocalDepth3dCrsTest::defaultUuid);
		delete crsTest;
	}

	resqml2::AbstractHdfProxy * hdfProxy = epcDoc->getHdfProxy(0);

	SeismicLineSetFeature* seismicLineSet = epcDoc->createSeismicLineSet(defaultUuidFeatureSet, defaultTitleFeatureSet);

	// Seismic Line
	SeismicLineFeature* seismicLine = epcDoc->createSeismicLine(defaultUuidFeature, defaultTitleFeature, 1, 0, 5);
	seismicLine->setSeismicLineSet(seismicLineSet);
	GenericFeatureInterpretation* seismicLineInterp = epcDoc->createGenericFeatureInterpretation(seismicLine, defaultUuidInterp, defaultTitleInterp);
	PolylineRepresentation* seismicLineRep = epcDoc->createPolylineRepresentation(seismicLineInterp, crs, defaultUuid, defaultTitle);
	double seismicLinePoints[15] = { 0, 100, 0, 150, 110, 0, 300, 120, 0, 450, 130, 0, 600, 140, 0 };
	seismicLineRep->setGeometry(seismicLinePoints, 5, hdfProxy);
}

void SeismicLineRepresentationTest::readEpcDocHandler()
{
	// Feature
	resqml2_0_1::SeismicLineFeature* feature = epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::SeismicLineFeature>(defaultUuidFeature);
	REQUIRE(feature->getFirstTraceIndex() == 0);
	REQUIRE(feature->getTraceCount() == 5);
	REQUIRE(feature->getTraceIndexIncrement() == 1);

	// Grid 2D
	resqml2_0_1::PolylineRepresentation* rep = epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::PolylineRepresentation>(defaultUuid);
	REQUIRE_THROWS(rep->getSeismicSupportOfPatch(0));
	REQUIRE(rep->getXyzPointCountOfAllPatches() == 5);
}
