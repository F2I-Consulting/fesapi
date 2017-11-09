#include "LocalTime3dCrs.h"
#include "../config.h"
#include "EpcDocument.h"
#include "../catch.hpp"

using namespace resqml2_0_1test;
using namespace common;
using namespace std;

const char* LocalTime3dCrs::defaultUuid = "8f8285a7-f1e7-4964-a9e1-e815c82c65e0";
const char* LocalTime3dCrs::defaultTitle = "Local Time 3d Crs Test";

LocalTime3dCrs::LocalTime3dCrs(const string & epcDocPath)
	: AbstractLocal3dCrsTest(epcDocPath, defaultUuid, defaultTitle)
{
}

LocalTime3dCrs::LocalTime3dCrs(EpcDocument* epcDoc, bool init)
	: AbstractLocal3dCrsTest(epcDoc, defaultUuid, defaultTitle)
{
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void LocalTime3dCrs::initEpcDocHandler()
{
	epcDoc->createLocalTime3dCrs(uuid, title, 1.0, 0.1, 15, .0, gsoap_resqml2_0_1::eml__LengthUom__m, 23031, gsoap_resqml2_0_1::eml__TimeUom__s, gsoap_resqml2_0_1::eml__LengthUom__m, "Unknown", false);
}

void LocalTime3dCrs::readEpcDocHandler()
{
	REQUIRE( epcDoc->getLocalTime3dCrsSet().size() == 1 );
}