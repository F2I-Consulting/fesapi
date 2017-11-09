#pragma once

#include "AbstractValuesPropertyTest.h"
#include <iostream>

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	class ContinuousPropertyTest : public AbstractValuesPropertyTest {
	public:
		ContinuousPropertyTest(const std::string & epcDocPath, const std::string & uuid, const std::string & title, const std::string & uuidRepresentation, const std::string & titleRepresentation);
		ContinuousPropertyTest(common::EpcDocument * epcDoc, const std::string & uuid, const std::string & title, const std::string & uuidRepresentation, const std::string & titleRepresentation);
	};
}