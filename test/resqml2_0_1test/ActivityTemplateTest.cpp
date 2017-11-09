#include "ActivityTemplateTest.h"
#include "resqml2/ActivityTemplate.h"
#include "EpcDocument.h"
#include "../catch.hpp"

using namespace std;
using namespace common;
using namespace resqml2_0_1test;
using namespace resqml2;

ActivityTemplateTest::ActivityTemplateTest(const string & epcDocPath, const string & uuid, const string & title) 
	: AbstractResqmlDataObjectTest(epcDocPath, uuid, title) {
}

ActivityTemplateTest::ActivityTemplateTest(EpcDocument * epcDoc, const string & uuid, const string & title)
	: AbstractResqmlDataObjectTest(epcDoc, uuid, title) {
}

void ActivityTemplateTest::initEpcDocHandler() {
	ActivityTemplate*  genericCreationActivityTemplate = this->epcDoc->createActivityTemplate(this->uuid, this->title);
	REQUIRE( genericCreationActivityTemplate != nullptr );

	for (std::map<string, ParameterTest>::iterator it=this->parameterMap.begin(); it!=this->parameterMap.end(); it++)
	{
		genericCreationActivityTemplate->pushBackParameter((*it).second.title, (*it).second.isInput, (*it).second.isOutput, (*it).second.minOccurs, (*it).second.maxOccurs); 
	}
}

void ActivityTemplateTest::readEpcDocHandler() {
	ActivityTemplate* activityTemplate = static_cast<ActivityTemplate*>(this->epcDoc->getResqmlAbstractObjectByUuid(this->uuid));

	REQUIRE( activityTemplate->getParameterCount() == this->parameterMap.size() );

	std::string parameterTitle;
	for (unsigned int i=0; i<activityTemplate->getParameterCount(); i++)
	{
		parameterTitle = activityTemplate->getParameterTitle(i);
		REQUIRE( activityTemplate->getParameterIsInput(parameterTitle) == this->parameterMap[parameterTitle].isInput );
		REQUIRE( activityTemplate->getParameterIsOutput(parameterTitle) == this->parameterMap[parameterTitle].isOutput );
		REQUIRE( activityTemplate->getParameterMinOccurences(parameterTitle) == this->parameterMap[parameterTitle].minOccurs );
		REQUIRE( activityTemplate->getParameterMaxOccurences(parameterTitle) == this->parameterMap[parameterTitle].maxOccurs );
	}
}