#pragma once

#include "AbstractRepresentationTest.h"
#include <iostream>

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	class AbstractGridRepresentationTest : public AbstractRepresentationTest {
	public:
		AbstractGridRepresentationTest(const std::string & epcDocPath, const std::string & uuid, const std::string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs);
		AbstractGridRepresentationTest(common::EpcDocument * epcDoc, const std::string & uuid, const std::string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs);
	};
}