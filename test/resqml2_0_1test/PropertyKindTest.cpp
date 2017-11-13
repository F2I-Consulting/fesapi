#include "PropertyKindTest.h"
#include "../catch.hpp"
#include "EpcDocument.h"
#include "resqml2/PropertyKind.h"
#include <stdexcept>
#include "../config.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2;

const char* PropertyKindTest::defaultUuid = "f1effef1-6bc7-4e82-829b-797713b60cdc";
const char* PropertyKindTest::defaultTitle = "Property Kind Test";

PropertyKindTest::PropertyKindTest(const string & epcDocPath)
	: AbstractResqmlDataObjectTest(epcDocPath, defaultUuid, defaultTitle) {
}

PropertyKindTest::PropertyKindTest(EpcDocument* epcDoc, bool init)
	: AbstractResqmlDataObjectTest(epcDoc, defaultUuid, defaultTitle) {
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void PropertyKindTest::initEpcDocHandler() {
	PropertyKind* propertyKind = this->epcDoc->createPropertyKind(defaultUuid, defaultTitle, "F2I", gsoap_resqml2_0_1::resqml2__ResqmlUom__Euc, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__index);
	REQUIRE(propertyKind != nullptr);
}

void PropertyKindTest::readEpcDocHandler() {
	// getting the PropertyKind
	PropertyKind* propertyKind = this->epcDoc->getResqmlAbstractObjectByUuid<PropertyKind>(uuid);

	REQUIRE(propertyKind->getNamingSystem().compare("F2I") == 0);
	REQUIRE(propertyKind->getUom() == gsoap_resqml2_0_1::resqml2__ResqmlUom__Euc);
	REQUIRE(propertyKind->isParentAnEnergisticsPropertyKind());
	REQUIRE(propertyKind->getParentEnergisticsPropertyKind() == gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__index);
	REQUIRE_THROWS(propertyKind->getParentLocalPropertyKind());
	REQUIRE_THROWS(propertyKind->getParentLocalPropertyKindTitle());
	REQUIRE_THROWS(propertyKind->getParentLocalPropertyKindUuid());
}