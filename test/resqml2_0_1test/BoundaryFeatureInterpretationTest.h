#pragma once

#include "AbstractFeatureInterpretationTest.h"
#include <iostream>

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	class BoundaryFeatureInterpretationTest : public AbstractFeatureInterpretationTest {
	public:
		BoundaryFeatureInterpretationTest(const std::string & epcDocPath, const std::string & uuid, const std::string & title, const std::string & uuidFeature, const std::string & titleFeature);
		BoundaryFeatureInterpretationTest(common::EpcDocument* epcDoc, const std::string & uuid, const std::string & title, const std::string & uuidFeature, const std::string & iitleFeature);
	};
}