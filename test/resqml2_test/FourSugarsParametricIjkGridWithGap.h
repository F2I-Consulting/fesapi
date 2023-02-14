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
	class FourSugarsParametricIjkGridWithGap : public commontest::AbstractTest {
	public:

		static constexpr char const* defaultUuid = "ecd52ad4-ca18-49d4-8394-2e8b9796b9d5";
		static constexpr char const* defaultTitle = "Four faulted sugar cubes parametric with k gap";
		static constexpr double parameters[32] = { 300, 300, 350, 300, 300, 350, /* SPLIT*/ 350, 350,
				400, 400, 450, 400, 400, 450, /* SPLIT*/ 450, 450,
				425, 425, 475, 425, 425, 475, /* SPLIT*/ 475, 475,
				500, 500, 550, 500, 500, 550, /* SPLIT*/ 550, 550 };

		/**
		* Creation of a testing object from an EPC document path. At serialize() call,
		* exising .epc file will be erased. 
		* @param repoPath the path of the .epc file (including .epc extension)
		*/
		FourSugarsParametricIjkGridWithGap(const std::string & repoPath);

	protected:
		void initRepo();
		void readRepo();
	};
}
