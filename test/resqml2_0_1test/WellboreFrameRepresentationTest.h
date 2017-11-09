#pragma once

#include "resqml2_0_1test/AbstractRepresentationTest.h"
#include <iostream>

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	class WellboreFrameRepresentationTest : public AbstractRepresentationTest {
	public:
		static const char* defaultUuid;
		static const char* defaultTitle;

		WellboreFrameRepresentationTest(const std::string & epcDocPath);
		WellboreFrameRepresentationTest(common::EpcDocument * epcDoc, bool init);
	protected:
		void initEpcDocHandler();
		void readEpcDocHandler();
	};
}
