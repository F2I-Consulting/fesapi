#include "TriangulatedSetRepresentationTest.h"

using namespace std;
using namespace resqml2_0_1test;

TriangulatedSetRepresentationTest::TriangulatedSetRepresentationTest(const std::string & epcDocPath, const string & uuid, const string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs) 
	: AbstractSurfaceRepresentationTest(epcDocPath, uuid, title, xyzPointCountOfAllPatches, xyzPointsOfAllPatchesInGlobalCrs) {
}

TriangulatedSetRepresentationTest::TriangulatedSetRepresentationTest(common::EpcDocument* epcDoc, const string & uuid, const string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs)
	: AbstractSurfaceRepresentationTest(epcDoc, uuid, title, xyzPointCountOfAllPatches, xyzPointsOfAllPatchesInGlobalCrs) {
}