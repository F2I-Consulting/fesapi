#include "AbstractIjkGridRepresentationTest.h"

using namespace std;
using namespace common;
using namespace resqml2_0_1test;

AbstractIjkGridRepresentationTest::AbstractIjkGridRepresentationTest(const string & epcDocPath, const string & uuid, const string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs)
	: AbstractColumnLayerGridRepresentationTest(epcDocPath, uuid, title, xyzPointCountOfAllPatches, xyzPointsOfAllPatchesInGlobalCrs) {
}

AbstractIjkGridRepresentationTest::AbstractIjkGridRepresentationTest(EpcDocument * epcDoc, const string & uuid, const string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs)
	: AbstractColumnLayerGridRepresentationTest(epcDoc, uuid, title, xyzPointCountOfAllPatches, xyzPointsOfAllPatchesInGlobalCrs) {
}