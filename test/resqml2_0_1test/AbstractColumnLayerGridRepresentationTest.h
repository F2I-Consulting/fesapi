#pragma once

#include "AbstractGridRepresentationTest.h"
#include <iostream>

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	class AbstractColumnLayerGridRepresentationTest : public AbstractGridRepresentationTest {
	public:
		AbstractColumnLayerGridRepresentationTest(const std::string & epcDocPath, const std::string & uuid, const std::string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs);
		AbstractColumnLayerGridRepresentationTest(common::EpcDocument * epcDoc, const std::string & uuid, const std::string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs);
	};
}