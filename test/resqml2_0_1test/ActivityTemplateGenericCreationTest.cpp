#include "ActivityTemplateGenericCreationTest.h"
#include "../config.h"
#include "EpcDocument.h"
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