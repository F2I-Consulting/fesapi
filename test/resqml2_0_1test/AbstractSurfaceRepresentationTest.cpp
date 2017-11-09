#include "AbstractSurfaceRepresentationTest.h"

using namespace std;
using namespace resqml2_0_1test;

AbstractSurfaceRepresentationTest::AbstractSurfaceRepresentationTest(const std::string & epcDocPath, const string & uuid, const string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs) 
	: AbstractRepresentationTest(epcDocPath, uuid, title, xyzPointCountOfAllPatches, xyzPointsOfAllPatchesInGlobalCrs) {
}

AbstractSurfaceRepresentationTest::AbstractSurfaceRepresentationTest(common::EpcDocument* epcDoc, const string & uuid, const string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs)
	: AbstractRepresentationTest(epcDoc, uuid, title, xyzPointCountOfAllPatches, xyzPointsOfAllPatchesInGlobalCrs) {
}