#pragma once

#include "AbstractResqmlDataObjectTest.h"
#include <iostream>

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	class AbstractLocal3dCrsTest : public AbstractResqmlDataObjectTest {
	public:
		AbstractLocal3dCrsTest(const std::string & epcDocPath, const std::string & uuid, const std::string & title);
		AbstractLocal3dCrsTest(common::EpcDocument* epcDoc, const std::string & uuid, const std::string & title);
	};
}