/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/
#include "AbstractPropertyTest.h"
#include "resqml2/AbstractRepresentation.h"
#include "resqml2/AbstractProperty.h"
#include "../catch.hpp"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_0_1test;
using namespace RESQML2_NS;

AbstractPropertyTest::AbstractPropertyTest(const string & epcDocPath, const string & uuid, const string & title, const string & uuidRepresentation, const string & titleRepresentation)
	: AbstractResqmlDataObjectTest(epcDocPath, uuid, title), uuidRepresentation(uuidRepresentation), titleRepresentation(titleRepresentation) {
}

AbstractPropertyTest::AbstractPropertyTest(EpcDocument * epcDoc, const string & uuid, const string & title, const string & uuidRepresentation, const string & titleRepresentation)
	: AbstractResqmlDataObjectTest(epcDoc, uuid, title), uuidRepresentation(uuidRepresentation), titleRepresentation(titleRepresentation) {
}

void AbstractPropertyTest::readEpcDoc() {
	AbstractObjectTest::readEpcDoc();

	// remark: following REQUIRE directives are not redundant with "cascade testing" since they cover the partial reference case.
	AbstractProperty* property = static_cast<AbstractProperty*>(this->epcDoc->getDataObjectByUuid(this->uuid));
	REQUIRE( property->getRepresentation()->getUuid() == this->uuidRepresentation );
	REQUIRE( property->getRepresentation()->getTitle() == this->titleRepresentation );
}

