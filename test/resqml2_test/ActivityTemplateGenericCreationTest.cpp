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
#include "ActivityTemplateGenericCreationTest.h"
#include "eml2/ActivityTemplate.h"
#include "../catch.hpp"

using namespace std;
using namespace COMMON_NS;
using namespace resqml2_test;
using namespace RESQML2_NS;
using namespace EML2_NS;

// ***************************************************************
// two followings values are conventions, they must not be changed
const char* ActivityTemplateGenericCreationTest::defaultUuid = "a41c63bf-78cb-454b-8018-c9df060c5cf3";
const char* ActivityTemplateGenericCreationTest::defaultTitle = "GenericCreationActivity";

ActivityTemplateGenericCreationTest::ActivityTemplateGenericCreationTest(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
		ParameterTest creationInput = {"CreationInput", true, false, 0, -1};
		parameterMap.insert(std::pair<std::string, ParameterTest>("CreationInput", creationInput));
		ParameterTest creationOutput = {"CreationOutput", false, true, 1, -1};
		parameterMap.insert(std::pair<std::string, ParameterTest>("CreationOutput", creationOutput));
}

void ActivityTemplateGenericCreationTest::initRepo() {
	ActivityTemplate*  genericCreationActivityTemplate = repo->createActivityTemplate(defaultUuid, defaultTitle);
	REQUIRE(genericCreationActivityTemplate != nullptr);

	for (std::map<string, ParameterTest>::iterator it = parameterMap.begin(); it != parameterMap.end(); ++it)
	{
		genericCreationActivityTemplate->pushBackParameter((*it).second.title, (*it).second.isInput, (*it).second.isOutput, (*it).second.minOccurs, (*it).second.maxOccurs);
	}
}

void ActivityTemplateGenericCreationTest::readRepo() {
	ActivityTemplate* activityTemplate = static_cast<ActivityTemplate*>(repo->getDataObjectByUuid(defaultUuid));

	REQUIRE(activityTemplate->getParameterCount() == parameterMap.size());

	std::string parameterTitle;
	for (unsigned int i = 0; i<activityTemplate->getParameterCount(); i++)
	{
		parameterTitle = activityTemplate->getParameterTitle(i);
		REQUIRE(activityTemplate->getParameterIsInput(parameterTitle) == parameterMap[parameterTitle].isInput);
		REQUIRE(activityTemplate->getParameterIsOutput(parameterTitle) == parameterMap[parameterTitle].isOutput);
		REQUIRE(activityTemplate->getParameterMinOccurences(parameterTitle) == parameterMap[parameterTitle].minOccurs);
		REQUIRE(activityTemplate->getParameterMaxOccurences(parameterTitle) == parameterMap[parameterTitle].maxOccurs);
	}
}
