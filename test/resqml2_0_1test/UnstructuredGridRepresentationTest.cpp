#include "UnstructuredGridRepresentationTest.h"

using namespace std;
using namespace common;
using namespace resqml2_0_1test;

const char* UnstructuredGridRepresentationTest::defaultUuid = "d084eef4-137a-423f-a41c-8064868bcfa0";
const char* UnstructuredGridRepresentationTest::defaultTitle = "Unstructured Grid Representation";

UnstructuredGridRepresentationTest::UnstructuredGridRepresentationTest(const string & epcDocPath, const string & uuid, const string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs)
	: AbstractGridRepresentationTest(epcDocPath, uuid, title, xyzPointCountOfAllPatches, xyzPointsOfAllPatchesInGlobalCrs) {
}

UnstructuredGridRepresentationTest::UnstructuredGridRepresentationTest(EpcDocument * epcDoc, const string & uuid, const string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs)
	: AbstractGridRepresentationTest(epcDoc, uuid, title, xyzPointCountOfAllPatches, xyzPointsOfAllPatchesInGlobalCrs) {
}