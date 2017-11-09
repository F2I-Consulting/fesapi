#pragma once

#include "resqml2_0_1test/AbstractRepresentationTest.h"
#include <iostream>

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	class WellboreMarkerFrameRepresentationTest : public AbstractRepresentationTest {
	public:
		static const char* defaultUuid;
		static const char* defaultTitle;

		WellboreMarkerFrameRepresentationTest(const std::string & epcDocPath);
		WellboreMarkerFrameRepresentationTest(common::EpcDocument * epcDoc);
	protected:
		void initEpcDocHandler();
		void readEpcDocHandler();
	};
}
