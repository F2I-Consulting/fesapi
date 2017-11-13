#include "AbstractValuesPropertyTest.h"

using namespace std;
using namespace common;
using namespace resqml2_0_1test;

AbstractValuesPropertyTest::AbstractValuesPropertyTest(const string & epcDocPath, const string & uuid, const string & title, const string & uuidRepresentation, const string & titleRepresentation)
	: AbstractPropertyTest(epcDocPath, uuid, title, uuidRepresentation, titleRepresentation) {
}

AbstractValuesPropertyTest::AbstractValuesPropertyTest(EpcDocument * epcDoc, const string & uuid, const string & title, const string & uuidRepresentation, const string & titleRepresentation)
	: AbstractPropertyTest(epcDoc, uuid, title, uuidRepresentation, titleRepresentation) {
}