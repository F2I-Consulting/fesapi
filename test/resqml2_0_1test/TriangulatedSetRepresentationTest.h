#pragma once

#include "resqml2_0_1test/AbstractSurfaceRepresentationTest.h"

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	class TriangulatedSetRepresentationTest : public AbstractSurfaceRepresentationTest {
	public:
		TriangulatedSetRepresentationTest(const std::string & epcDocPath, const std::string & uuid, const std::string & title, const ULONG64 & xyzPointCountOfAllPatches = 0, double * xyzPointsOfAllPatchesInGlobalCrs = nullptr);
		TriangulatedSetRepresentationTest(common::EpcDocument* epcDoc, const std::string & uuid, const std::string & title, const ULONG64 & xyzPointCountOfAllPatches = 0, double * xyzPointsOfAllPatchesInGlobalCrs = nullptr);
	};
}