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
#pragma once

#include "AbstractTest.h"
#include <map>

namespace resqml2_test {
	class ActivityTemplateGenericCreationTest : public commontest::AbstractTest {
	public:

		// ***************************************************************
		// two followings values are conventions, they must not be changed
		static constexpr char const* defaultUuid = "a41c63bf-78cb-454b-8018-c9df060c5cf3";
		static constexpr char const* defaultTitle = "GenericCreationActivity";

		/**
		* Creation of a testing object from an EPC document path. At serialize() call,
		* exising .epc file will be erased. 
		* @param repoPath the path of the .epc file (including .epc extension)
		*/
		ActivityTemplateGenericCreationTest(const std::string & repoPath);

	protected:
		struct ParameterTest {
			std::string title;
			bool isInput;
			bool isOutput;
			int minOccurs;
			int maxOccurs;
		};

		std::map<std::string, ParameterTest> parameterMap;

		void initRepo();
		void readRepo();
	};
}
