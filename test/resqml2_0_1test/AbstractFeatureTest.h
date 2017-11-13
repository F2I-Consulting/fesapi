#pragma once

#include "AbstractResqmlDataObjectTest.h"
#include <iostream>

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	class AbstractFeatureTest : public AbstractResqmlDataObjectTest {
	public:
		AbstractFeatureTest(const std::string & epcDocPath, const std::string & uuid, const std::string & title);
		AbstractFeatureTest(common::EpcDocument* epcDoc, const std::string & uuid, const std::string & title);
	};
}