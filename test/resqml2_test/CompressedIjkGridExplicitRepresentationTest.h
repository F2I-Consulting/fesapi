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
	class CompressedIjkGridExplicitRepresentationTest : public commontest::AbstractTest {
	public:

		static constexpr char const* defaultUuid = "f889e5d2-249e-4827-8532-ce60a1d05b99";
		static constexpr char const* defaultTitle = "Compressed Ijk Grid Representation";
		static constexpr uint64_t nodesCountIjkGridRepresentation = 16;
		static constexpr double nodesIjkGridRepresentation[] =
			{ 0, 0, 300, 375, 0, 300, 700, 0, 350, 0, 150, 300, 375, 150, 300, 700, 150, 350, /* SPLIT*/ 375, 0, 350, 375, 150, 350, 0, 0, 500, 375, 0, 500, 700, 0, 550, 0, 150, 500, 375, 150, 500, 700, 150, 550, /* SPLIT*/ 375, 0, 550, 375, 150, 550 };

		/**
		* Creation of a testing object from an EPC document path. At serialize() call,
		* exising .epc file will be erased. 
		* @param repoPath the path of the .epc file (including .epc extension)
		*/
		CompressedIjkGridExplicitRepresentationTest(const std::string & repoPath);

	protected:
		void initRepo();
		void readRepo();
	};
}
