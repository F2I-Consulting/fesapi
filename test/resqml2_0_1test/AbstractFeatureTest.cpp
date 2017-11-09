#include "AbstractFeatureTest.h"

using namespace std;
using namespace resqml2_0_1test;

AbstractFeatureTest::AbstractFeatureTest(const std::string & epcDocPath, const string & uuid, const string & title) 
	: AbstractResqmlDataObjectTest(epcDocPath, uuid, title) {
}

AbstractFeatureTest::AbstractFeatureTest(common::EpcDocument* epcDoc, const string & uuid, const string & title)
	: AbstractResqmlDataObjectTest(epcDoc, uuid, title) {
}