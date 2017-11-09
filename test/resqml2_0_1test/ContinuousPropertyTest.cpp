#include "ContinuousPropertyTest.h"

using namespace std;
using namespace common;
using namespace resqml2_0_1test;

ContinuousPropertyTest::ContinuousPropertyTest(const string & epcDocPath, const string & uuid, const string & title, const string & uuidRepresentation, const string & titleRepresentation)
	: AbstractValuesPropertyTest(epcDocPath, uuid, title, uuidRepresentation, titleRepresentation) {
}

ContinuousPropertyTest::ContinuousPropertyTest(EpcDocument * epcDoc, const string & uuid, const string & title, const string & uuidRepresentation, const string & titleRepresentation)
	: AbstractValuesPropertyTest(epcDoc, uuid, title, uuidRepresentation, titleRepresentation) {
}