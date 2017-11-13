#include "AbstractLocal3dCrsTest.h"

using namespace resqml2_0_1test;
using namespace common;
using namespace std;

AbstractLocal3dCrsTest::AbstractLocal3dCrsTest(const string & epcDocPath, const string & uuid, const string & title)
	: AbstractResqmlDataObjectTest(epcDocPath, uuid, title) {
}

AbstractLocal3dCrsTest::AbstractLocal3dCrsTest(EpcDocument* epcDoc, const string & uuid, const string & title)
	: AbstractResqmlDataObjectTest(epcDoc, uuid, title) {
}