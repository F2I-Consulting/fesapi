#pragma once

#include "AbstractTest.h"
#include <iostream>

namespace commontest {
	class EpcDocumentTest : public AbstractTest {
	public:
		EpcDocumentTest(const std::string & epcDocPath);
		EpcDocumentTest(common::EpcDocument * epcDoc);
		void initEpcDoc() {}
		void readEpcDoc() {}
	};
}