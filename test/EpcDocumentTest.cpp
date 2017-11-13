#include "EpcDocumentTest.h"

using namespace std;
using namespace common;
using namespace commontest;

EpcDocumentTest::EpcDocumentTest(const string & epcDocPath)
	: AbstractTest(epcDocPath) {
}

EpcDocumentTest::EpcDocumentTest(EpcDocument * epcDoc)
	: AbstractTest(epcDoc) {
}