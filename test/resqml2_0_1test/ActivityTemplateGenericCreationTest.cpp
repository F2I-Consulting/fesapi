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
#include "../config.h"
#include "common/EpcDocument.h"
#include "resqml2_0_1/ActivityTemplate.h"
#include "../catch.hpp"

using namespace std;
using namespace common;
using namespace resqml2_0_1test;
using namespace resqml2_0_1;

// ***************************************************************
// two followings values are conventions, they must not be changed
const char* ActivityTemplateGenericCreationTest::defaultUuid = "a41c63bf-78cb-454b-8018-c9df060c5cf3";
const char* ActivityTemplateGenericCreationTest::defaultTitle = "GenericCreationActivity";

ActivityTemplateGenericCreationTest::ActivityTemplateGenericCreationTest(const string & epcDocPath)
	: ActivityTemplateTest(epcDocPath, defaultUuid, defaultTitle) {
		ParameterTest creationInput = {"CreationInput", true, false, 0, -1};
		this->parameterMap.insert(std::pair<std::string, ParameterTest>("CreationInput", creationInput));
		ParameterTest creationOutput = {"CreationOutput", false, true, 1, -1};
		this->parameterMap.insert(std::pair<std::string, ParameterTest>("CreationOutput", creationOutput));
}

ActivityTemplateGenericCreationTest::ActivityTemplateGenericCreationTest(EpcDocument * epcDoc, bool init)
	: ActivityTemplateTest(epcDoc, defaultUuid, defaultTitle) {
		ParameterTest creationInput = {"CreationInput", true, false, 0, -1};
		this->parameterMap.insert(std::pair<std::string, ParameterTest>("CreationInput", creationInput));
		ParameterTest creationOutput = {"CreationOutput", false, true, 1, -1};
		this->parameterMap.insert(std::pair<std::string, ParameterTest>("CreationOutput", creationOutput));
		
		if (init)
			this->initEpcDoc();
		else
			this->readEpcDoc();
}

