#include "AbstractColumnLayerGridRepresentationTest.h"

using namespace std;
using namespace common;
using namespace resqml2_0_1test;

AbstractColumnLayerGridRepresentationTest::AbstractColumnLayerGridRepresentationTest(const string & epcDocPath, const string & uuid, const string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs)
	: AbstractGridRepresentationTest(epcDocPath, uuid, title, xyzPointCountOfAllPatches, xyzPointsOfAllPatchesInGlobalCrs) {
}

AbstractColumnLayerGridRepresentationTest::AbstractColumnLayerGridRepresentationTest(EpcDocument * epcDoc, const string & uuid, const string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs)
	: AbstractGridRepresentationTest(epcDoc, uuid, title, xyzPointCountOfAllPatches, xyzPointsOfAllPatchesInGlobalCrs) {
}