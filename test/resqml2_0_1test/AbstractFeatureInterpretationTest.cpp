#include "AbstractFeatureInterpretationTest.h"
#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2/AbstractFeature.h"
#include "../catch.hpp"
#include "AbstractObjectTest.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace resqml2;

AbstractFeatureInterpretationTest::AbstractFeatureInterpretationTest(const string & epcDocPath, const string & uuid, const string & title, const string & uuidFeature, const string & titleFeature)
	: AbstractResqmlDataObjectTest(epcDocPath, uuid, title), uuidFeature(uuidFeature), titleFeature(titleFeature) {
}

AbstractFeatureInterpretationTest::AbstractFeatureInterpretationTest(common::EpcDocument * epcDoc, const string & uuid, const string & title, const string & uuidFeature, const string & titleFeature)
	: AbstractResqmlDataObjectTest(epcDoc, uuid, title), uuidFeature(uuidFeature), titleFeature(titleFeature) {
}

void AbstractFeatureInterpretationTest::readEpcDoc()
{
	AbstractObjectTest::readEpcDoc();

	// remark: following REQUIRE directives are not redundant with "cascade testing" since they cover the partial reference case.
	AbstractFeatureInterpretation* interpretation = static_cast<AbstractFeatureInterpretation*>(epcDoc->getResqmlAbstractObjectByUuid(this->uuid));
	REQUIRE( interpretation->getInterpretedFeature()->getUuid() == this->uuidFeature );
	REQUIRE( interpretation->getInterpretedFeature()->getTitle() == this->titleFeature );

	// partial case handling
	if (interpretation->getInterpretedFeature()->getGsoapProxy() == nullptr)
		REQUIRE( interpretation->getInterpretedFeature()->isPartial() );
	else
		REQUIRE_FALSE( interpretation->getInterpretedFeature()->isPartial() );
}
