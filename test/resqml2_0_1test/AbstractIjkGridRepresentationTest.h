#pragma once

#include "AbstractColumnLayerGridRepresentationTest.h"
#include <iostream>

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	class AbstractIjkGridRepresentationTest : public AbstractColumnLayerGridRepresentationTest {
	public:
		AbstractIjkGridRepresentationTest(const std::string & epcDocPath, const std::string & uuid, const std::string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs);
		AbstractIjkGridRepresentationTest(common::EpcDocument * epcDoc, const std::string & uuid, const std::string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs);
	};
}