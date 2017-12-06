#include "AbstractResqmlDataObjectTest.h"
#include "common/EpcDocument.h"
#include "../catch.hpp"
#include "common/AbstractObject.h"

using namespace std;
using namespace resqml2_0_1test;

AbstractResqmlDataObjectTest::AbstractResqmlDataObjectTest(const string & epcDocPath, const string & uuid, const string & title) :
	AbstractObjectTest(epcDocPath, uuid, title) {
}

AbstractResqmlDataObjectTest::AbstractResqmlDataObjectTest(common::EpcDocument* epcDoc, const string & uuid, const string & title) :
	AbstractObjectTest(epcDoc, uuid, title) {
}