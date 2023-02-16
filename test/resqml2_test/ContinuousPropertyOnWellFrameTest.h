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

namespace resqml2_test {
	class ContinuousPropertyOnWellFrameTest : public commontest::AbstractTest {
	public:

		static constexpr char const* defaultUuid = "6e4ca2c9-6780-44bd-b4c2-6bb3ef4682d4";
		static constexpr char const* defaultTitle = "Continuous Property on well frame Test";
		static constexpr char const* exoticUuid = "8535b08f-739f-470c-b940-36c1bd5209a4";
		static constexpr char const* exoticTitle = "Continuous Property exotic uom on well frame Test";

		/**
		* Creation of a testing object from an EPC document path. At serialize() call,
		* exising .epc file will be erased.
		* @param repoPath the path of the .epc file (including .epc extension)
		*/
		ContinuousPropertyOnWellFrameTest(const std::string & repoPath);

	protected:
		void initRepo();
		void readRepo();
	};
}

