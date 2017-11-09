#include "AbstractPropertyTest.h"
#include "resqml2/AbstractRepresentation.h"
#include "resqml2/AbstractProperty.h"
#include "../catch.hpp"

using namespace std;
using namespace common;
using namespace resqml2_0_1test;
using namespace resqml2;

AbstractPropertyTest::AbstractPropertyTest(const string & epcDocPath, const string & uuid, const string & title, const string & uuidRepresentation, const string & titleRepresentation)
	: AbstractResqmlDataObjectTest(epcDocPath, uuid, title), uuidRepresentation(uuidRepresentation), titleRepresentation(titleRepresentation) {
}

AbstractPropertyTest::AbstractPropertyTest(EpcDocument * epcDoc, const string & uuid, const string & title, const string & uuidRepresentation, const string & titleRepresentation)
	: AbstractResqmlDataObjectTest(epcDoc, uuid, title), uuidRepresentation(uuidRepresentation), titleRepresentation(titleRepresentation) {
}

void AbstractPropertyTest::readEpcDoc() {
	AbstractObjectTest::readEpcDoc();

	// remark: following REQUIRE directives are not redundant with "cascade testing" since they cover the partial reference case.
	AbstractProperty* property = static_cast<AbstractProperty*>(this->epcDoc->getResqmlAbstractObjectByUuid(this->uuid));
	REQUIRE( property->getRepresentation()->getUuid() == this->uuidRepresentation );
	REQUIRE( property->getRepresentation()->getTitle() == this->titleRepresentation );
}