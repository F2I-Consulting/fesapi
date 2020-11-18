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
#include <string>

namespace resqml2_test {
	class Grid2dRepresentationTest : public commontest::AbstractTest {
	public:
		static const char* defaultUuidFeature;
		static const char* defaultTitleFeature;
		static const char* defaultUuidInterp;
		static const char* defaultTitleInterp;
		static const char* defaultUuid;
		static const char* defaultTitle;

		/**
		* Creation of a testing object from an EPC document path. At serialize() call,
		* exising .epc file will be erased. 
		* @param repoPath the path of the .epc file (including .epc extension)
		*/
		Grid2dRepresentationTest(const std::string & repoPath);

	protected:
		void initRepo();
		void readRepo();
	};
}


