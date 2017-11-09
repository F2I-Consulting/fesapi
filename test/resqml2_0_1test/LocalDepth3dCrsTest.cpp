#include "LocalDepth3dCrsTest.h"
#include "../config.h"
#include "EpcDocument.h"
#include "../catch.hpp"

using namespace resqml2_0_1test;
using namespace common;
using namespace std;

const char* LocalDepth3dCrsTest::defaultUuid = "a8effb2c-c94f-4d88-ae76-581ff14a4b96";
const char* LocalDepth3dCrsTest::defaultTitle = "Local Depth 3d Crs Test";

LocalDepth3dCrsTest::LocalDepth3dCrsTest(const string & epcDocPath)
	: AbstractLocal3dCrsTest(epcDocPath, defaultUuid, defaultTitle)
{
}

LocalDepth3dCrsTest::LocalDepth3dCrsTest(EpcDocument* epcDoc, bool init)
	: AbstractLocal3dCrsTest(epcDoc, defaultUuid, defaultTitle)
{
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void LocalDepth3dCrsTest::initEpcDocHandler()
{
	this->epcDoc->createLocalDepth3dCrs(uuid, title, .0, .0, .0, .0, gsoap_resqml2_0_1::eml__LengthUom__m, 23031, gsoap_resqml2_0_1::eml__LengthUom__m, "Unknown", false);
}

void LocalDepth3dCrsTest::readEpcDocHandler()
{
	REQUIRE( epcDoc->getLocalDepth3dCrsSet().size() == 1 );
}