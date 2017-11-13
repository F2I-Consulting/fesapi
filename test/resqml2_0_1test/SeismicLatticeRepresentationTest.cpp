#include "resqml2_0_1test/SeismicLatticeRepresentationTest.h"
#include "../catch.hpp"
#include "../config.h" 
#include "resqml2_0_1/SeismicLatticeFeature.h"
#include "resqml2_0_1/GenericFeatureInterpretation.h"
#include "resqml2_0_1/Grid2dRepresentation.h"
#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "resqml2/HdfProxy.h"
#include "resqml2_0_1test/AbstractFeatureTest.h"
#include "resqml2_0_1test/LocalDepth3dCrsTest.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2_0_1;

const char* SeismicLatticeRepresentationTest::defaultUuidFeature = "3e04d513-7d2c-4cc3-853c-a3a651c5eb4a";
const char* SeismicLatticeRepresentationTest::defaultTitleFeature = "Seismic Lattice Feature";
const char* SeismicLatticeRepresentationTest::defaultUuidInterp = "3d7ae7ac-c605-493c-8067-547411fe30de";
const char* SeismicLatticeRepresentationTest::defaultTitleInterp = "Seismic Lattice Interp";
const char* SeismicLatticeRepresentationTest::defaultUuid = "c218fe9a-5080-4322-82fc-d7a1efb6da99";
const char* SeismicLatticeRepresentationTest::defaultTitle = "Seismic Grid 2d Representation";

SeismicLatticeRepresentationTest::SeismicLatticeRepresentationTest(const string & epcDocPath)
	: AbstractSurfaceRepresentationTest(epcDocPath, defaultUuid, defaultTitle, 8, nullptr)
{
}

SeismicLatticeRepresentationTest::SeismicLatticeRepresentationTest(EpcDocument * epcDocument, bool init)
	: AbstractSurfaceRepresentationTest(epcDocument, defaultUuid, defaultTitle, 8, nullptr)
{
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void SeismicLatticeRepresentationTest::initEpcDocHandler()
{
	LocalDepth3dCrs * crs = epcDoc->getResqmlAbstractObjectByUuid<LocalDepth3dCrs>(LocalDepth3dCrsTest::defaultUuid);

	SeismicLatticeFeature* seismicLattice = epcDoc->createSeismicLattice(defaultUuidFeature, defaultTitleFeature, 2, 2, 150, 152, 4, 2);
	GenericFeatureInterpretation* seismicLatticeInterp = epcDoc->createGenericFeatureInterpretation(seismicLattice, defaultUuidInterp, defaultTitleInterp);
	Grid2dRepresentation* seismicLatticeRep = epcDoc->createGrid2dRepresentation(seismicLatticeInterp, crs, uuid, title);
	seismicLatticeRep->setGeometryAsArray2dOfLatticePoints3d(4, 2, 0, 0, 0, 1, 0, 0, 0, 1, 0, 250, 200);
}

void SeismicLatticeRepresentationTest::readEpcDocHandler()
{
	// Feature
	resqml2_0_1::SeismicLatticeFeature* feature = epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::SeismicLatticeFeature>(defaultUuidFeature);
	REQUIRE(feature->getCrosslineIncrement() == 2);
	REQUIRE(feature->getOriginCrossline() == 152);
	REQUIRE(feature->getInlineIncrement() == 2);
	REQUIRE(feature->getOriginInline() == 150);

	// Grid 2D
	resqml2_0_1::Grid2dRepresentation* rep = epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::Grid2dRepresentation>(defaultUuid);
	REQUIRE(rep->getSupportingRepresentation() == nullptr);
	REQUIRE_THROWS(rep->getSeismicSupportOfPatch(0));
	REQUIRE((rep->isISpacingConstant() && rep->isJSpacingConstant()));
	REQUIRE(rep->getXOrigin() == .0);
	REQUIRE(rep->getYOrigin() == .0);
	REQUIRE(rep->getNodeCountAlongIAxis() == 4);
	REQUIRE(rep->getNodeCountAlongJAxis() == 2);
	REQUIRE(rep->getXIOffset() == 1.0);
	REQUIRE(rep->getYIOffset() == 0.0);
	REQUIRE(rep->getXIOffset() == 0.0);
	REQUIRE(rep->getYIOffset() == 1.0);
	REQUIRE(rep->getISpacing() == 250.0);
	REQUIRE(rep->getJSpacing() == 200.0);
	REQUIRE_THROWS(rep->getIndexOriginOnSupportingRepresentation());
	REQUIRE_THROWS(rep->getIndexOffsetOnSupportingRepresentation(0));
	REQUIRE_THROWS(rep->getNodeCountOnSupportingRepresentation(1));
}
