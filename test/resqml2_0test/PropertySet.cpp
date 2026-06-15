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
#include "PropertySet.h"

#include "catch.hpp"

#include "resqml2_0_1/PointSetRepresentation.h"
#include "resqml2_0_1/ContinuousProperty.h"
#include "resqml2_0_1/DiscreteProperty.h"
#include "resqml2_0_1/PropertySet.h"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_0test;

static constexpr const char* emptyPropSetUuid = "85116e1e-85b7-4ab0-8913-19fda4b21862";
static constexpr const char* emptyPropSetTitle = "Empty Property Set";
static constexpr const char* propSetUuid = "1d4b4342-288d-47c1-9572-9f330f8e632a";
static constexpr const char* propSetTitle = "Testing child property set";

PropertySet::PropertySet(const string & epcDocPath)
	: commontest::AbstractTest(epcDocPath) {
}

void PropertySet::initRepo() {
	// Add a partial fake rep to allow creation of a fake prop which must rely on a rep.
	auto* fakePointSetRep = repo->createPartial<RESQML2_0_1_NS::PointSetRepresentation>("", "");

	auto* emptyPropertySet = repo->createPropertySet(emptyPropSetUuid, emptyPropSetTitle, false, true, gsoap_resqml2_0_1::resqml20__TimeSetKind::not_x0020a_x0020time_x0020set);
	auto* childPropSet = repo->createPropertySet(propSetUuid, propSetTitle, false, true, gsoap_resqml2_0_1::resqml20__TimeSetKind::not_x0020a_x0020time_x0020set);
	childPropSet->setParent(emptyPropertySet);

	RESQML2_0_1_NS::ContinuousProperty* continuousProp = repo->createPartial<RESQML2_0_1_NS::ContinuousProperty>("96138ac5-2e16-45ab-bc22-99ea7557123f", "partial continuous prop");
	RESQML2_0_1_NS::DiscreteProperty* discreteProp = repo->createPartial<RESQML2_0_1_NS::DiscreteProperty>("1f441142-07e1-4585-aedc-5d63c75fb949", "partial discrete prop");
	childPropSet->pushBackProperty(continuousProp);
	childPropSet->pushBackProperty(discreteProp);
}

void PropertySet::readRepo() {
	auto const* emptyPropertySet = repo->getDataObjectByUuid<RESQML2_0_1_NS::PropertySet>(emptyPropSetUuid);
	REQUIRE(emptyPropertySet->getPropertyCount() == 0);
	REQUIRE(emptyPropertySet->getParent() == nullptr);
	REQUIRE(emptyPropertySet->getChildrenCount() == 1);

	auto const* childPropSet = emptyPropertySet->getChildren(0);
	REQUIRE(childPropSet->getUuid() == propSetUuid);
	REQUIRE(childPropSet->getPropertyCount() == 2);
	REQUIRE(childPropSet->getParent() == emptyPropertySet);
	REQUIRE(childPropSet->getChildrenCount() == 0);
}
