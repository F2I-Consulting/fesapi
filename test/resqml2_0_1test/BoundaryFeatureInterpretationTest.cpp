#include "BoundaryFeatureInterpretationTest.h"

using namespace std;
using namespace resqml2_0_1test;

BoundaryFeatureInterpretationTest::BoundaryFeatureInterpretationTest(const string & epcDocPath, const string & uuid, const string & title, const string & uuidFeature, const string & titleFeature)
	: AbstractFeatureInterpretationTest(epcDocPath, uuid, title, uuidFeature, titleFeature) {
}

BoundaryFeatureInterpretationTest::BoundaryFeatureInterpretationTest(common::EpcDocument * epcDoc, const string & uuid, const string & title, const string & uuidFeature, const string & titleFeature)
	: AbstractFeatureInterpretationTest(epcDoc, uuid, title, uuidFeature, titleFeature) {
}