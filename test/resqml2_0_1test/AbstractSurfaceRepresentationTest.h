#pragma once

#include "AbstractRepresentationTest.h"
#include <iostream>

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	class AbstractSurfaceRepresentationTest : public AbstractRepresentationTest {
	public:
		AbstractSurfaceRepresentationTest(const std::string & epcDocPath, const std::string & uuid, const std::string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs);
		AbstractSurfaceRepresentationTest(common::EpcDocument* epcDoc, const std::string & uuid, const std::string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs);
	};
}