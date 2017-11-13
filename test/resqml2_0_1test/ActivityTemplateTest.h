#pragma once

#include "AbstractResqmlDataObjectTest.h"
#include <iostream>
#include <vector>
#include <map>

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	class ActivityTemplateTest : public AbstractResqmlDataObjectTest {
	public:
		ActivityTemplateTest(const std::string & epcDocPath, const std::string & uuid, const std::string & title);
		ActivityTemplateTest(common::EpcDocument * epcDoc, const std::string & uuid, const std::string & title);
	protected:
		struct ParameterTest {
			std::string title;
			bool isInput;
			bool isOutput;
			int minOccurs;
			int maxOccurs;
		};

		std::map<std::string, ParameterTest> parameterMap;

		void initEpcDocHandler();
		void readEpcDocHandler();
	};
}