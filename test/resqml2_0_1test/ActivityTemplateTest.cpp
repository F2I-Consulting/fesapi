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
#include "ActivityTemplateTest.h"
#include "resqml2/ActivityTemplate.h"
#include "common/EpcDocument.h"
#include "../catch.hpp"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_0_1test;
using namespace RESQML2_NS;

ActivityTemplateTest::ActivityTemplateTest(const string & epcDocPath, const string & uuid, const string & title) 
	: AbstractResqmlDataObjectTest(epcDocPath, uuid, title) {
}

ActivityTemplateTest::ActivityTemplateTest(EpcDocument * epcDoc, const string & uuid, const string & title)
	: AbstractResqmlDataObjectTest(epcDoc, uuid, title) {
}

void ActivityTemplateTest::initEpcDocHandler() {
	ActivityTemplate*  genericCreationActivityTemplate = this->epcDoc->createActivityTemplate(this->uuid, this->title);
	REQUIRE( genericCreationActivityTemplate != nullptr );

	for (std::map<string, ParameterTest>::iterator it=this->parameterMap.begin(); it!=this->parameterMap.end(); ++it)
	{
		genericCreationActivityTemplate->pushBackParameter((*it).second.title, (*it).second.isInput, (*it).second.isOutput, (*it).second.minOccurs, (*it).second.maxOccurs); 
	}
}

void ActivityTemplateTest::readEpcDocHandler() {
	ActivityTemplate* activityTemplate = static_cast<ActivityTemplate*>(this->epcDoc->getDataObjectByUuid(this->uuid));

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

