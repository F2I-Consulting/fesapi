#include "resqml2_0_1test/ActivityCreationTest.h"

#include "catch.hpp"
#include "resqml2_0_1test/ActivityTemplateGenericCreationTest.h"
#include "resqml2_0_1test/HorizonInterpretationTest.h"

#include "EpcDocument.h"
#include "resqml2/ActivityTemplate.h"
#include "resqml2/Activity.h"
#include "resqml2_0_1/HorizonInterpretation.h"

using namespace std;
using namespace resqml2_0_1test;
using namespace common;
using namespace resqml2;

// Activity
const char* ActivityCreationTest::defaultUuid = "705cd6f5-8ee8-427b-adde-04b0b6afcdf0";
const char* ActivityCreationTest::defaultTitle = "Activity Creation";

ActivityCreationTest::ActivityCreationTest(const string & epcDocPath)
	: AbstractResqmlDataObjectTest(epcDocPath, defaultUuid, defaultTitle) {
}

ActivityCreationTest::ActivityCreationTest(EpcDocument * epcDoc, bool init)
	: AbstractResqmlDataObjectTest(epcDoc, defaultUuid, defaultTitle) {
		if (init)
			this->initEpcDoc();
		else
			this->readEpcDoc();
}

void ActivityCreationTest::initEpcDocHandler() {
	// creation of an horizon interpretation
	HorizonInterpretationTest * horizonInterpretationTest = new HorizonInterpretationTest(this->epcDoc, true);
	resqml2_0_1::HorizonInterpretation * horizonInterpretation = static_cast<resqml2_0_1::HorizonInterpretation*>(this->epcDoc->getResqmlAbstractObjectByUuid(HorizonInterpretationTest::defaultUuid));

	// creation of the generic creation activity template
	ActivityTemplateGenericCreationTest* activityTemplateTest = new ActivityTemplateGenericCreationTest(this->epcDoc, true);
	ActivityTemplate * activityTemplate = static_cast<ActivityTemplate*>(this->epcDoc->getResqmlAbstractObjectByUuid(ActivityTemplateGenericCreationTest::defaultUuid));

	// creation of the creation activity
	Activity* activity = this->epcDoc->createActivity(activityTemplate, this->uuid, this->title);
	REQUIRE( activity != nullptr );

	// creation of activity parameters
	activity->pushBackParameter("CreationOutput", horizonInterpretation);

	// cleaning
	delete horizonInterpretationTest;
	delete activityTemplateTest;
}

void ActivityCreationTest::readEpcDocHandler() {
	// reading dependencies
	HorizonInterpretationTest * horizonInterpretationTest = new HorizonInterpretationTest(this->epcDoc, false);
	ActivityTemplateGenericCreationTest* activityTemplateTest = new ActivityTemplateGenericCreationTest(this->epcDoc, false);

	// getting the activity
	Activity* activity = static_cast<Activity*>(this->epcDoc->getResqmlAbstractObjectByUuid(defaultUuid));
	REQUIRE( activity != nullptr );

	// getting the horizon interpretation
	resqml2_0_1::HorizonInterpretation * horizonInterpretation = static_cast<resqml2_0_1::HorizonInterpretation*>(this->epcDoc->getResqmlAbstractObjectByUuid(HorizonInterpretationTest::defaultUuid));
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

	// cleaning
	delete horizonInterpretationTest;
	delete activityTemplateTest;
}
