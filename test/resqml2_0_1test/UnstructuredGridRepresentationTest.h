#pragma once

#include "AbstractGridRepresentationTest.h"
#include <iostream>

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	class UnstructuredGridRepresentationTest : public AbstractGridRepresentationTest {
	public:
		static const char* defaultUuid;
		static const char* defaultTitle;

		UnstructuredGridRepresentationTest(const std::string & epcDocPath, const std::string & uuid, const std::string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs);
		UnstructuredGridRepresentationTest(common::EpcDocument * epcDoc, const std::string & uuid, const std::string & title, const ULONG64 & xyzPointCountOfAllPatches, double * xyzPointsOfAllPatchesInGlobalCrs);
	};
}
