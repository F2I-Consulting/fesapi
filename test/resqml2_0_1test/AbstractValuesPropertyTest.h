#pragma once

#include "AbstractPropertyTest.h"
#include <string>

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	class AbstractValuesPropertyTest : public AbstractPropertyTest {
	public:
		AbstractValuesPropertyTest(const std::string & epcDocPath, const std::string & uuid, const std::string & title, const std::string & uuidRepresentation, const std::string & titleRepresentation);
		AbstractValuesPropertyTest(common::EpcDocument * epcDoc, const std::string & uuid, const std::string & title, const std::string & uuidRepresentation, const std::string & titleRepresentation);
	};
}