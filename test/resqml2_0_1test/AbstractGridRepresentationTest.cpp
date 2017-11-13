#include "AbstractGridRepresentationTest.h"

using namespace std;
using namespace common;
using namespace resqml2_0_1test;

AbstractGridRepresentationTest::AbstractGridRepresentationTest(const string & epcDocPath, const string & uuid, const string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs)
	: AbstractRepresentationTest(epcDocPath, uuid, title, xyzPointCountOfAllPatches, xyzPointsOfAllPatchesInGlobalCrs) {
}

AbstractGridRepresentationTest::AbstractGridRepresentationTest(EpcDocument * epcDoc, const string & uuid, const string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs)
	: AbstractRepresentationTest(epcDoc, uuid, title, xyzPointCountOfAllPatches, xyzPointsOfAllPatchesInGlobalCrs) {
}