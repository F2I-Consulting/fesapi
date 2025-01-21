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

namespace COMMON_NS {
	class DataObjectRepository;
}

namespace resqml2_test {
	class FaultMultiPatchTriangulatedSetRepresentationTest : public commontest::AbstractTest {
	public:

		static constexpr char const* defaultUuid = "4b8503e8-28e5-44c5-877d-b9eb3295b2b9";
		static constexpr char const* defaultTitle = "FaultMultiPatchTriangulatedSetRepresentationTest";

		/**
		* Creation of a testing object from an EPC document path. At serialize() call,
		* exising .epc file will be erased. 
		* @param repoPath the path of the .epc file (including .epc extension)
		*/
		FaultMultiPatchTriangulatedSetRepresentationTest(const std::string & repoPath);

	protected:
		void initRepo();
		void readRepo();

	private:
		// Patch 0
		static constexpr double explicitPointsFault1Patch0[18] = { 150, 0, 200, 150, 100, 200, 150, 200, 200,
			250, 0, 300, 250, 100, 300, 250, 200, 300 };
		static constexpr uint32_t triangleNodeIndexFaultPatch0[12] = { 0,4,3, 0,1,4, 1,2,4, 2,5,4 };
		// Patch 1
		static constexpr double explicitPointsFault1Patch1[18] = { 250, 0, 300, 250, 100, 300, 250, 200, 300,
			300, 0, 350, 300, 100, 350, 300, 200, 350 };
		static constexpr uint32_t triangleNodeIndexFaultPatch1[12] = { 6,10,9, 6,7,10, 7,8,10, 8,11,10 };
		// Patch 2
		static constexpr double explicitPointsFault1Patch2[18] = { 300, 0, 350, 300, 100, 350, 300, 200, 350,
			450, 0, 500, 450, 100, 500, 450, 200, 500 };
		static constexpr uint32_t triangleNodeIndexFaultPatch2[12] = { 12,16,15, 12,13,16, 13,14,16, 14,17,16 };
		// Patch 3
		static constexpr double explicitPointsFault1Patch3[18] = { 450, 0, 500, 450, 100, 500, 450, 200, 500,
			500, 0, 550, 500, 100, 550 ,500, 200, 550 };
		static constexpr uint32_t triangleNodeIndexFaultPatch3[12] = { 18,22,21, 18,19,22, 19,20,22, 20,23,22 };
		// Patch 4
		static constexpr double explicitPointsFault1Patch4[18] = { 500, 0, 550, 500, 100, 550 ,500, 200, 550,
			600, 0, 650, 600, 100, 650, 600, 200, 650 };
		static constexpr uint32_t triangleNodeIndexFaultPatch4[12] = { 24,28,27, 24,25,28, 25,26,28, 26,29,28 };
	};
}
