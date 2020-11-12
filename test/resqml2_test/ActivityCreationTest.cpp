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
#include "resqml2_test/ActivityCreationTest.h"

#include "catch.hpp"
#include "resqml2_test/ActivityTemplateGenericCreationTest.h"
#include "resqml2_test/HorizonInterpretationTest.h"

#include "eml2/ActivityTemplate.h"
#include "eml2/Activity.h"
#include "resqml2/HorizonInterpretation.h"

using namespace std;
using namespace resqml2_test;
using namespace COMMON_NS;
using namespace RESQML2_NS;
using namespace EML2_NS;

// Activity
const char* ActivityCreationTest::defaultUuid = "705cd6f5-8ee8-427b-adde-04b0b6afcdf0";
const char* ActivityCreationTest::defaultTitle = "Activity Creation";

ActivityCreationTest::ActivityCreationTest(const string & repoPath)
	: commontest::AbstractObjectTest(repoPath) {
}

ActivityCreationTest::ActivityCreationTest(DataObjectRepository * repo, bool init)
	: commontest::AbstractObjectTest(repo) {
	if (init)
		initRepo();
	else
		readRepo();
}

void ActivityCreationTest::initRepoHandler() {
	// creation of an horizon interpretation
	HorizonInterpretationTest * horizonInterpretationTest = new HorizonInterpretationTest(repo, true);
	RESQML2_NS::HorizonInterpretation * horizonInterpretation = static_cast<RESQML2_NS::HorizonInterpretation*>(repo->getDataObjectByUuid(HorizonInterpretationTest::defaultUuid));

	// creation of the generic creation activity template
	ActivityTemplateGenericCreationTest* activityTemplateTest = new ActivityTemplateGenericCreationTest(repo, true);
	ActivityTemplate * activityTemplate = static_cast<ActivityTemplate*>(repo->getDataObjectByUuid(ActivityTemplateGenericCreationTest::defaultUuid));

	// creation of the creation activity
	Activity* activity = repo->createActivity(activityTemplate, defaultUuid, defaultTitle);
	REQUIRE( activity != nullptr );

	// creation of activity parameters
	activity->pushBackParameter("CreationOutput", horizonInterpretation);

	// cleaning
	delete horizonInterpretationTest;
	delete activityTemplateTest;
}

void ActivityCreationTest::readRepoHandler() {
	// reading dependencies
	HorizonInterpretationTest horizonInterpretationTest(repo, false);
	ActivityTemplateGenericCreationTest activityTemplateTest(repo, false);

	// getting the activity
	Activity* activity = repo->getDataObjectByUuid<Activity>(defaultUuid);
	REQUIRE( activity != nullptr );

	// getting the horizon interpretation
	RESQML2_NS::HorizonInterpretation * horizonInterpretation = repo->getDataObjectByUuid<RESQML2_NS::HorizonInterpretation>(HorizonInterpretationTest::defaultUuid);
	REQUIRE( horizonInterpretation != nullptr );

	// testing the activity
	REQUIRE( activity->getParameterCount() == 1);
	REQUIRE( activity->getParameterCount("CreationInputput") == 0 );
	REQUIRE( activity->getParameterIndexOfTitle("CreationIntput").size() == 0 );
	REQUIRE( activity->getParameterCount("CreationOutput") == 1 );
	REQUIRE( activity->getParameterIndexOfTitle("CreationOutput").size() == 1 );
	REQUIRE( activity->getParameterTitle(0) == "CreationOutput");
	REQUIRE( activity->isAResqmlObjectParameter("CreationOutput") );;
	REQUIRE( activity->getResqmlObjectParameterValue(0) == horizonInterpretation );
	REQUIRE_FALSE( activity->isAFloatingPointQuantityParameter("CreationOutput") );
	REQUIRE_FALSE( activity->isAFloatingPointQuantityParameter(0) );
	REQUIRE_THROWS( activity->getFloatingPointQuantityParameterValue("CreationOutput").size());
	REQUIRE_THROWS( activity->getFloatingPointQuantityParameterValue(0) );
}
