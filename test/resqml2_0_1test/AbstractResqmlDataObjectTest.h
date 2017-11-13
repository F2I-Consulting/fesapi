#pragma once

#include <iostream>
#include "AbstractObjectTest.h"

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1 {
	class AbstractResqmlDataObject;
}

namespace resqml2_0_1test {
	class AbstractResqmlDataObjectTest : public AbstractObjectTest {
	public:
		AbstractResqmlDataObjectTest(const std::string & epcDocPath, const std::string & uuid, const std::string & title);
		AbstractResqmlDataObjectTest(common::EpcDocument * epcDoc, const std::string & uuid, const std::string & title);
	};
}